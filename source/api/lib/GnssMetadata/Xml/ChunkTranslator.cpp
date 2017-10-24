/**
 * File: ChunkTranslator.cpp
 * Author: M.B. Mathews
 *
 * Copyright(c) 2014 Institute of Navigation
 * http://www.ion.org
 *
 * This Metadata API is free software; you can redistribute it and/or
 * modify it under the terms of the Lesser GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Metadata API.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ChunkTranslator.h"
#include <GnssMetadata/Chunk.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_ChunkNodes)
NODELIST_ENTRY("sizeword", TE_SIMPLE_TYPE)
NODELIST_ENTRY("countwords", TE_SIMPLE_TYPE)
NODELIST_ENTRY("endian", TE_SIMPLE_TYPE)
NODELIST_ENTRY("padding", TE_SIMPLE_TYPE)
NODELIST_ENTRY("wordshift", TE_SIMPLE_TYPE)
NODELIST_ENTRY("lump", TE_LUMP)
NODELIST_ENTRY("comment", TE_SIMPLE_TYPE)
NODELIST_ENTRY("artifact", TE_SIMPLE_TYPE)
NODELIST_END

// Endian Values
static const char* _szEndian[] = { "Big", "Little", "Undefined" };

Chunk::WordEndian ToEndian(const char* pszFmt)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		if (strcmp(_szEndian[i], pszFmt) == 0) return (Chunk::WordEndian)i;
	}
	return (Chunk::WordEndian)2;
}

// Word Padding
static const char* _szWordPadding[] = { "None", "Head", "Tail" };

Chunk::WordPadding ToWordPadding(const char* pszFmt)
{
	for (unsigned int i = 0; i < 3; i++)
	{
		if (strcmp(_szWordPadding[i], pszFmt) == 0) return (Chunk::WordPadding)i;
	}
	return (Chunk::WordPadding)2;
}

// Word Shift
static const char* _szWordShift[] = { "Left", "Right" };

Chunk::WordShift ToWordShift(const char* pszFmt)
{
	for (unsigned int i = 0; i < 2; i++)
	{
		if (strcmp(_szWordShift[i], pszFmt) == 0) return (Chunk::WordShift)i;
	}
	return (Chunk::WordShift)2;
}

ChunkTranslator::ChunkTranslator()
		: Translator((NodeEntry*)_ChunkNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool ChunkTranslator::OnRead(Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	const XMLElement* pchild;
	if (pAdaptor == NULL) return false;
	Chunk chunk;

	bool bRetVal = true;

	// Parse the AttributedObject Elements.
	if (!ReadAttributedObject(chunk, ctxt, elem, false))
		return false;

	// Done processing element, if no children, meaning this is
	// an element referencing another element.
	if (elem.NoChildren())
	{
		chunk.IsReference(true);
	}
	else
	{
		// Parse sizeword [1]
		chunk.SizeWord(ReadFirstElement("sizeword", elem, true, (size_t)0));

		// Parse countwords [1]
		chunk.CountWords(ReadFirstElement("countwords", elem, true, (size_t)0));

		// Parse endian [0..1]
		pchild = elem.FirstChildElement("endian");
		if (pchild != NULL)
		{
			chunk.Endian(ToEndian(pchild->GetText()));
		}

		// Parse padding [0..1]
		pchild = elem.FirstChildElement("padding");
		if (pchild != NULL)
		{
			chunk.Padding(ToWordPadding(pchild->GetText()));
		}

		// Parse shift [0..1]
		pchild = elem.FirstChildElement("wordshift");
		if (pchild != NULL)
		{
			chunk.Shift(ToWordShift(pchild->GetText()));
		}

		// Parse lumps [1..*]
		bRetVal &= ReadList<Lump>(chunk.Lumps(), "lump", ctxt, elem);
	}

	// Lastly set the chunk on the specified object.
	if (bRetVal) pAdaptor->set(&chunk);
	return bRetVal;
}

/**
 * Write the current object
 */
void ChunkTranslator::OnWrite(const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem)
{
	const Chunk* pchunk = dynamic_cast<const Chunk*>(pObject);
	if (pchunk == NULL) throw TranslationException("ChunkTranslator cannot cast Chunk object");

	XMLElement* pelemc = elem.GetDocument()->NewElement(pszName);

	// Fill out id, artifacts, and comments last in accordance
	// with schema.
	WriteAttributedObject(*pchunk, ctxt, *pelemc);

	if (!pchunk->IsReference())
	{
		XMLElement* pelem;

		// Write sizeword [1]
		WriteElement("sizeword", pchunk->SizeWord(), pelemc, true);

		// Write countwords [1]
		WriteElement("countwords", pchunk->CountWords(), pelemc, true);

		// Write endian [0..1]
		pelem = elem.GetDocument()->NewElement("endian");
		pelem->SetText(_szEndian[pchunk->Endian()]);
		pelemc->InsertEndChild(pelem);

		// Write padding [0..1]
		pelem = elem.GetDocument()->NewElement("padding");
		pelem->SetText(_szWordPadding[pchunk->Padding()]);
		pelemc->InsertEndChild(pelem);

		// Write wordshift [0..1]
		pelem = elem.GetDocument()->NewElement("wordshift");
		pelem->SetText(_szWordShift[pchunk->Shift()]);
		pelemc->InsertEndChild(pelem);

		// Write lumps [1..*]
		WriteList<Lump>(pchunk->Lumps(), "lump", ctxt, *pelemc);
	}

	elem.InsertEndChild(pelemc);
}
