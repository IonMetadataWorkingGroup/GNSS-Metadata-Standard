/**
 * File: BlockTranslator.cpp
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

#include "BlockTranslator.h"
#include <GnssMetadata/Block.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_BlockNodes)
NODELIST_ENTRY("cycles", TE_SIMPLE_TYPE)
NODELIST_ENTRY("sizeheader", TE_SIMPLE_TYPE)
NODELIST_ENTRY("sizefooter", TE_SIMPLE_TYPE)
NODELIST_ENTRY("chunk", TE_CHUNK)
NODELIST_ENTRY("comment", TE_SIMPLE_TYPE)
NODELIST_ENTRY("artifact", TE_SIMPLE_TYPE)
NODELIST_END

BlockTranslator::BlockTranslator()
		: Translator((NodeEntry*)_BlockNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool BlockTranslator::OnRead(Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	if (pAdaptor == nullptr) return false;
	Block block;

	bool bRetVal = true;

	// Parse the AttributedObject Elements.
	if (!ReadAttributedObject(block, ctxt, elem, false)) return false;

	// Done processing element, if no children, meaning this is
	// an element referencing another element.
	if (elem.NoChildren())
	{
		block.IsReference(true);
	}
	else
	{
		// Parse cycles [1]
		block.Cycles(ReadFirstElement("cycles", elem, true, (size_t)0));

		// Parse sizeheader [0..1]
		block.SizeHeader(ReadFirstElement("sizeheader", elem, false, (size_t)0));

		// Parse sizefooter[0..1]
		block.SizeFooter(ReadFirstElement("sizefooter", elem, false, (size_t)0));

		// Parse chunks [1..*]
		bRetVal &= ReadList<Chunk>(block.Chunks(), "chunk", ctxt, elem);
	}

	// Lastly set the block on the specified object.
	if (bRetVal) pAdaptor->set(&block);
	return bRetVal;
}

/**
 * Write the current object
 */
void BlockTranslator::OnWrite(const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem)
{
	const Block* pblock = dynamic_cast<const Block*>(pObject);
	if (pblock == nullptr) throw TranslationException("BlockTranslator cannot cast Block object");

	XMLElement* pelemc = elem.GetDocument()->NewElement(pszName);

	// Fill out id, artifacts, and comments last in accordance
	// with schema.
	WriteAttributedObject(*pblock, ctxt, *pelemc);

	if (!pblock->IsReference())
	{
		// Write cycles [1]
		WriteElement("cycles", pblock->Cycles(), pelemc, true);

		// Write sizeheader [0..1]
		WriteElement("sizeheader", pblock->SizeHeader(), pelemc, false);

		// Write sizefooter [0..1]
		WriteElement("sizefooter", pblock->SizeFooter(), pelemc, false);

		// Write chunk [1..*]
		WriteList<Chunk>(pblock->Chunks(), "chunk", ctxt, *pelemc);
	}

	elem.InsertEndChild(pelemc);
}
