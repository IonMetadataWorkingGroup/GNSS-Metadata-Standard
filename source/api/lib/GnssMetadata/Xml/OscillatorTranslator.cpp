/**
 * File: OscillatorTranslator.cpp
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


#include "OscillatorTranslator.h"
#include <GnssMetadata/Oscillator.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_SystemNodes)
	NODELIST_ENTRY( "comment",	  TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "artifact",	  TE_SIMPLE_TYPE)
NODELIST_END

OscillatorTranslator::OscillatorTranslator() 
: Translator( (NodeEntry*) _SystemNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool OscillatorTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	if( pAdaptor == NULL)
		return false;

	//For now, just process AttributedObject elements.
	Oscillator osc;
	bool bRetVal = ReadAttributedObject( osc, ctxt, elem);

	if( bRetVal)
		pAdaptor->set( &osc);
	return bRetVal;
}
/**
 * Write the current object 
 */
void OscillatorTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem )
{
	const Oscillator* posc = dynamic_cast< const Oscillator*>(pObject);
	if( posc == NULL) 
		throw TranslationException("OscillatorTranslator cannot cast to Oscillator object");

	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);
	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *posc, ctxt, *pelemc);

	elem.InsertEndChild( pelemc);
}
