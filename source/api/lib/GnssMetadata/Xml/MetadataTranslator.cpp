/**
 * File: MetadataTranslator.cpp
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

#include "XmlDefs.h"
#include "MetadataTranslator.h"
#include <GnssMetadata/Metadata.h>
#include <GnssMetadata/Xml/XmlProcessor.h>

#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

/******************************************************************************
 * Metadata Nodes definition
 ******************************************************************************/
NODELIST_BEGIN( _MetadataNodes)
NODELIST_ENTRY("include", TE_ANYURI)
NODELIST_ENTRY("file", TE_DATAFILE)
NODELIST_ENTRY("fileset", TE_FILESET)
NODELIST_ENTRY("band", TE_BAND)
NODELIST_ENTRY("system", TE_SYSTEM)
NODELIST_ENTRY("stream", TE_STREAM)
NODELIST_ENTRY("lump", TE_LUMP)
NODELIST_ENTRY("chunk", TE_CHUNK)
NODELIST_ENTRY("block", TE_BLOCK)
NODELIST_ENTRY("lane", TE_LANE)
NODELIST_ENTRY("session", TE_SESSION)
//TODO Add FileSet
NODELIST_END

MetadataTranslator::MetadataTranslator()
		: Translator((NodeEntry*)_MetadataNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool MetadataTranslator::OnRead(Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* /*pAdaptor*/)
{
	// Parse the datafiles
	bool bRetVal = true;

	Metadata& metadata = dynamic_cast<Metadata&>(*ctxt.pContainer);

	bRetVal &= ReadList<AnyUri>(metadata.Includes(), "include", ctxt, elem);
	bRetVal &= ReadList<File>(metadata.Files(), "file", ctxt, elem);
	bRetVal &= ReadList<FileSet>(metadata.FileSets(), "fileset", ctxt, elem);
	bRetVal &= ReadList<Band>(metadata.Bands(), "band", ctxt, elem);
	bRetVal &= ReadList<IonStream>(metadata.Streams(), "stream", ctxt, elem);
	bRetVal &= ReadList<Lump>(metadata.Lumps(), "lump", ctxt, elem);
	bRetVal &= ReadList<Chunk>(metadata.Chunks(), "chunk", ctxt, elem);
	bRetVal &= ReadList<Block>(metadata.Blocks(), "block", ctxt, elem);
	bRetVal &= ReadList<Lane>(metadata.Lanes(), "lane", ctxt, elem);
	bRetVal &= ReadList<Session>(metadata.Sessions(), "session", ctxt, elem);
	bRetVal &= ReadList<System>(metadata.Systems(), "system", ctxt, elem);

	// Parse Artifacts and Comments.
	bRetVal &= ReadAttributedObject(metadata, ctxt, elem, false);
	return bRetVal;
}

/**
 * Write the current object
 */
void MetadataTranslator::OnWrite(const Object * pObject, pcstr pszName, Context & ctxt, XMLNode & elem)
{
	const Metadata* pmetadata = dynamic_cast<const Metadata*>(pObject);
	if (pmetadata == NULL) throw TranslationException("MetadataTranslator cannot cast Metadata object");

	XMLElement* pelemc = elem.GetDocument()->NewElement(pszName);

	// Set the namespace for the Metadata.
	pelemc->SetAttribute("xmlns", METADATA_NAMESPACE);

	// Fill out id, artifacts, and comments last in accordance
	// with schema.
	WriteAttributedObject(*pmetadata, ctxt, *pelemc);

	WriteList<AnyUri>(pmetadata->Includes(), "include", ctxt, *pelemc);
	WriteList<Band>(pmetadata->Bands(), "band", ctxt, *pelemc);
	WriteList<IonStream>(pmetadata->Streams(), "stream", ctxt, *pelemc);
	WriteList<Lump>(pmetadata->Lumps(), "lump", ctxt, *pelemc);
	WriteList<Chunk>(pmetadata->Chunks(), "chunks", ctxt, *pelemc);
	WriteList<Block>(pmetadata->Blocks(), "blocks", ctxt, *pelemc);
	WriteList<Lane>(pmetadata->Lanes(), "lane", ctxt, *pelemc);
	WriteList<System>(pmetadata->Systems(), "system", ctxt, *pelemc);
	WriteList<Session>(pmetadata->Sessions(), "session", ctxt, *pelemc);
	WriteList<File>(pmetadata->Files(), "file", ctxt, *pelemc);
	WriteList<FileSet>(pmetadata->FileSets(), "fileset", ctxt, *pelemc);

	elem.InsertEndChild(pelemc);
}
