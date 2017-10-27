/**
 * File: DurationTranslator.cpp
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

#include "DurationTranslator.h"
#include <GnssMetadata/Duration.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

static const char* _szfmts[] = { "sec", "msec", "usec", "nsec", "psec" };

static Duration::DurationFormat ToFormat(const char* pszFmt)
{
	for (unsigned int i = 0; i < 5; i++)
	{
		if (strcmp(_szfmts[i], pszFmt) == 0) return (Duration::DurationFormat)i;
	}
	return (Duration::DurationFormat)0;
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool DurationTranslator::OnRead(Context & /*ctxt*/, const XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	if (pAdaptor != NULL)
	{
		pcstr format = elem.Attribute("format");
		if (format == NULL)
			format = "sec";

		Duration::DurationFormat fmt = ToFormat(format);
		Duration dur;
		dur.Value(atof(elem.GetText()), fmt);

		//Set the accessor.
		pAdaptor->set(&dur);
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Write the current object
 */
void DurationTranslator::OnWrite(const Object * pObject, pcstr pszName, Context & /*ctxt*/, tinyxml2::XMLNode & elem)
{
	const Duration* pdur = dynamic_cast<const Duration*>(pObject);
	if (pdur == NULL) throw TranslationException("DurationTranslator cannot cast Duration object");

	XMLElement* pelemf = elem.GetDocument()->NewElement(pszName);
	pelemf->SetAttribute("format", _szfmts[pdur->Format()]);
	char buff[64];
	sprintf(buff, "%0.16le", pdur->Value());
	pelemf->SetText(buff);
	elem.InsertEndChild(pelemf);
}
