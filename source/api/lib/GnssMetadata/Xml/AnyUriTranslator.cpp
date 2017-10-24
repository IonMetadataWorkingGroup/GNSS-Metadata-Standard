/**
 * File: AnyUriTranslator.cpp
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

#include "AnyUriTranslator.h"
#include <GnssMetadata/AnyUri.h>

#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

#include "XmlDefs.h"

AnyUriTranslator::AnyUriTranslator()
		: Translator(NULL)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool AnyUriTranslator::OnRead(Context & /*ctxt*/, const XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	if (pAdaptor == NULL) return false;

	AnyUri url(elem.GetText());
	pAdaptor->set(&url);
	return true;
}

/**
 * Write the current object
 */
void AnyUriTranslator::OnWrite(const Object * pObject, pcstr pszName, Context & /*ctxt*/, tinyxml2::XMLNode & elem)
{
	const AnyUri* puri = dynamic_cast<const AnyUri*>(pObject);
	if (puri == NULL) throw TranslationException("AnyUriTranslator cannot cast to AnyUri object");

	XMLElement* pelemc = elem.GetDocument()->NewElement(pszName);
	pelemc->SetText(puri->Value().c_str());
	elem.InsertEndChild(pelemc);
}
