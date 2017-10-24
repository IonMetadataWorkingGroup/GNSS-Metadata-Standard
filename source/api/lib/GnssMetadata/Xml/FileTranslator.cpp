/**
 * File: FileTranslator.cpp
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

#include "FileTranslator.h"
#include <GnssMetadata/File.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_FileNodes)
NODELIST_ENTRY("comment", TE_SIMPLE_TYPE)
NODELIST_ENTRY("artifact", TE_SIMPLE_TYPE)
NODELIST_ENTRY("url", TE_SIMPLE_TYPE)
NODELIST_ENTRY("timestamp", TE_SIMPLE_TYPE)
NODELIST_ENTRY("offset", TE_SIMPLE_TYPE)
NODELIST_ENTRY("owner", TE_SIMPLE_TYPE)
NODELIST_ENTRY("copyright", TE_SIMPLE_TYPE)
NODELIST_ENTRY("next", TE_SIMPLE_TYPE)
NODELIST_ENTRY("previous", TE_SYSTEM)
NODELIST_ENTRY("lane", TE_LANE)
NODELIST_END

FileTranslator::FileTranslator()
		: Translator((NodeEntry*)_FileNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool FileTranslator::OnRead(Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	const XMLElement* pchild;
	if (pAdaptor == NULL) return false;
	File file;

	bool bRetVal = true;

	// Parse the AttributedObject Elements.
	if (!ReadAttributedObject(file, ctxt, elem, false)) return false;

	// Done processing element, if	 children, meaning this is
	// an element referencing another element.
	if (elem.NoChildren())
	{
		file.IsReference(true);
	}
	else
	{
		// Parse url [1]
		file.Url().Value(ReadFirstElement("url", elem, true, ""));

		// Parse timestamp [1]
		pchild = elem.FirstChildElement("timestamp");
		if (pchild == NULL) throw TranslationException("FileTranslator::OnRead -> timestamp not found");
		file.TimeStamp(Date(pchild->GetText()));

		// Parse offset [0..1]
		file.Offset(ReadFirstElement("offset", elem, false, (size_t)0));

		// Parse owner [0..1]
		file.Owner(ReadFirstElement("owner", elem, false, ""));

		// Parse copyright [0..1]
		file.Copyright(ReadFirstElement("copyright", elem, false, ""));

		// Parse next [0..1]
		file.Next().Value(ReadFirstElement("next", elem, false, ""));

		// Parse previous [0..1]
		file.Previous().Value(ReadFirstElement("previous", elem, false, ""));

		// Parse Lane [1]
		pchild = elem.FirstChildElement("lane");
		AccessorAdaptor<File, Lane> adpt(&file, &File::Lane);
		bRetVal = ReadElement(file, ctxt, *pchild, &adpt);
	}

	// Lastly set the datafile on the specified object.
	if (bRetVal) pAdaptor->set(&file);
	return bRetVal;
}

/**
 * Write the current object
 */
void FileTranslator::OnWrite(const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem)
{
	const File* pfile = dynamic_cast<const File*>(pObject);
	if (pfile == NULL) throw TranslationException("FileTranslator cannot cast File object");

	XMLElement* pelemc = elem.GetDocument()->NewElement(pszName);

	// Fill out id, artifacts, and comments last in accordance
	// with schema.
	WriteAttributedObject(*pfile, ctxt, *pelemc);

	if (!pfile->IsReference())
	{
		XMLElement* pelem;

		// Write url [1]
		WriteElement("url", pfile->Url().Value().c_str(), pelemc, true);

		// Write timestamp [1]
		pelem = elem.GetDocument()->NewElement("timestamp");
		pelem->SetText(pfile->TimeStamp().toString().c_str());
		pelemc->InsertEndChild(pelem);

		// Write offset [0..1]
		WriteElement("offset", pfile->Offset(), pelemc, false, 0);

		// Write owner [0..1]
		WriteElement("owner", pfile->Owner().c_str(), pelemc, false, "");

		// Write copyright [0..1]
		WriteElement("owner", pfile->Copyright().c_str(), pelemc, false, "");

		// Write next [0..1]
		WriteElement("next", pfile->Next().Value().c_str(), pelemc, false, "");

		// Write previous [0..1]
		WriteElement("previous", pfile->Previous().Value().c_str(), pelemc, false, "");

		// Write Lane [1]
		WriteElement(&pfile->Lane(), "lane", ctxt, *pelemc);
	}

	elem.InsertEndChild(pelemc);
}
