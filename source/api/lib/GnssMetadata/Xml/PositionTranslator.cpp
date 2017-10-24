/**
 * File: PositionTranslator.cpp
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

#include "PositionTranslator.h"
#include <GnssMetadata/Position.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

PositionTranslator::PositionTranslator()
		: Translator( NULL)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool PositionTranslator::OnRead(Context & /*ctxt*/, const XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	if (pAdaptor != NULL)
	{
		try
		{
			double lat = atof(elem.Attribute("lat"));
			double lon = atof(elem.Attribute("lon"));
			double height = atof(elem.Attribute("height"));
			Position pos(lat, lon, height);
			pAdaptor->set(&pos);
		}
		catch (...)
		{
			throw TranslationException("Couldn't parse Position element");
		}
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
void PositionTranslator::OnWrite(const Object * pObject, pcstr pszName, Context & /*ctxt*/, tinyxml2::XMLNode & elem)
{
	const Position* ppos = dynamic_cast<const Position*>(pObject);
	if (ppos == NULL) throw TranslationException("PositionTranslator cannot cast Position object");

	XMLElement* pelem = elem.GetDocument()->NewElement(pszName);

	if (ppos->IsDefined())
	{
		char buff[128];
		sprintf(buff, "%0.8lf", ppos->Latitude());
		pelem->SetAttribute("lat", buff);
		sprintf(buff, "%0.8lf", ppos->Longitude());
		pelem->SetAttribute("lon", buff);
		sprintf(buff, "%0.3lf", ppos->Height());
		pelem->SetAttribute("height", buff);
		elem.InsertEndChild(pelem);
	}
}
