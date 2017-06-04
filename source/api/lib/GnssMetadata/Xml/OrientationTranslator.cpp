/**
 * File: PositionTranslator.cpp
 * Author: James T. Curran
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


#include "OrientationTranslator.h"
#include <GnssMetadata/Orientation.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;


OrientationTranslator::OrientationTranslator() 
: Translator( NULL)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool OrientationTranslator::OnRead( Context & /*ctxt*/, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	if( pAdaptor != NULL)
	{
		try
		{
            double alpha = atof( elem.Attribute("alpha"));
            double beta = atof( elem.Attribute("beta"));
            double gamma= atof( elem.Attribute("gamma"));
            Orientation ori(alpha, beta, gamma);
			pAdaptor->set(&ori);
		}
		catch(...)
		{
			throw TranslationException("Couldn't parse Orientation element");
		}
		return true;
	}
	else
		return false;
}
/**
 * Write the current object 
 */
void OrientationTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & /*ctxt*/, tinyxml2::XMLNode & elem )
{
	const Orientation* pori = dynamic_cast< const Orientation*>(pObject);
	if( pori == NULL) 
		throw TranslationException("OrientationTranslator cannot cast Position object");

	XMLElement* pelem = elem.GetDocument()->NewElement( pszName);
	
    if( pori->IsDefined())
    {
	    char buff[128];
        sprintf(buff,"%0.8lf", pori->Alpha());
        pelem->SetAttribute("alpha", buff);
        sprintf(buff,"%0.8lf", pori->Beta());
        pelem->SetAttribute("beta", buff);
        sprintf(buff,"%0.3lf", pori->Gamma());
        pelem->SetAttribute("gamma", buff);
        elem.InsertEndChild(pelem);
    }
}
