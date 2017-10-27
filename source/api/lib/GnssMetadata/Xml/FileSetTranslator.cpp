/**
 * File: FileSetTranslator.cpp
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

#include "FileSetTranslator.h"
#include <GnssMetadata/File.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_FileSetNodes)
NODELIST_ENTRY("file", TE_ANYURI)
NODELIST_END

FileSetTranslator::FileSetTranslator()
		: Translator((NodeEntry*)_FileSetNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool FileSetTranslator::OnRead(Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	if (pAdaptor == nullptr) return false;
	FileSet fileset;

	bool bRetVal = true;

	// Parse the AttributedObject Elements.
	if (!ReadAttributedObject(fileset, ctxt, elem))
		return false;

	// Done processing element, if no children, meaning this is
	// an element referencing another element.
	if (elem.NoChildren())
	{
		fileset.IsReference(true);
	}
	else
	{
		// Parse file URL.
		bRetVal &= ReadList<AnyUri>(fileset.FileUrls(), "file", ctxt, elem);
	}

	// Lastly set the fileset on the specified object.
	if (bRetVal) pAdaptor->set(&fileset);
	return bRetVal;
}

/**
 * Write the current object
 */
void FileSetTranslator::OnWrite(const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem)
{
	const FileSet* pfileset = dynamic_cast<const FileSet*>(pObject);
	if (pfileset == nullptr) throw TranslationException("FileSetTranslator cannot cast FileSet object");

	XMLElement* pelemc = elem.GetDocument()->NewElement(pszName);

	// Fill out id, artifacts, and comments last in accordance
	// with schema.
	WriteAttributedObject(*pfileset, ctxt, *pelemc);

	if (!pfileset->IsReference())
	{
		// Write band
		WriteList<AnyUri>(pfileset->FileUrls(), "file", ctxt, *pelemc);
	}

	elem.InsertEndChild(pelemc);
}
