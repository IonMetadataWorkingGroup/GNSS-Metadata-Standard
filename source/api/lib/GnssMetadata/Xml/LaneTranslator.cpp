/**
 * File: LaneTranslator.cpp
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


#include "LaneTranslator.h"
#include <GnssMetadata/Lane.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_LaneNodes)
	NODELIST_ENTRY( "bandsrc",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "session",	TE_SESSION)
	NODELIST_ENTRY( "system",	TE_SYSTEM)
	NODELIST_ENTRY( "block",	TE_BLOCK)
	NODELIST_ENTRY( "comment",	TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "artifact", TE_SIMPLE_TYPE)
NODELIST_END


LaneTranslator::LaneTranslator() 
: Translator( (NodeEntry*) _LaneNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool LaneTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	if( pAdaptor == NULL)
		return false;
	Lane lane;

	bool bRetVal = true;

	//Parse the AttributedObject Elements.
	if( !ReadAttributedObject( lane, ctxt, elem, false))
		return false;

	//Done processing element, if no children, meaning this is 
	//an element referencing another element.
	if( elem.NoChildren())
		lane.IsReference(true);
	else
	{
		//Parse bandsrc [1..*]
		const tinyxml2::XMLElement* pelem = elem.FirstChildElement("bandsrc"); 
		for( ;pelem != NULL; pelem = pelem->NextSiblingElement("bandsrc")) 
		{ 
			const char* pszidband = pelem->Attribute("idband");
			const char* pszidsrc = pelem->Attribute("idsrc");
			lane.AddBandSource(pszidband, pszidsrc);
		} 

		//Parse session [0..*]
		bRetVal &= ReadList<Session>(lane.Sessions(), "session", ctxt, elem);

		//Parse system [1..*]
		bRetVal &= ReadList<System>(lane.Systems(), "system", ctxt, elem);

		//Parse block [1..*]
		bRetVal &= ReadList<Block>(lane.Blocks(), "block", ctxt, elem);
	}

	//Lastly set the lane on the specified object.
	if( bRetVal)
		pAdaptor->set( &lane);
	return bRetVal;
}
/**
 * Write the current object 
 */
void LaneTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem )
{
	const Lane* plane = dynamic_cast< const Lane*>(pObject);
	if( plane == NULL) 
		throw TranslationException("LaneTranslator cannot cast Lane object");

	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *plane, ctxt, *pelemc);

	if( !plane->IsReference())
	{
		//Write bandsrc [1..*]
		Lane::BandSourceList::const_iterator iter = plane->BandSources().begin();
        for(; iter != plane->BandSources().end(); iter++)
		{
			XMLElement* pelem = elem.GetDocument()->NewElement("bandsrc");
			pelem->SetAttribute("idband", iter->idBand.c_str());
			pelem->SetAttribute("idsrc", iter->idSource.c_str());
			pelemc->InsertEndChild(pelem);
		}

		//Write session [0..*]
		WriteList<Session>( plane->Sessions(), "session", ctxt,*pelemc);

		//Write system [1..*]
		WriteList<System>( plane->Systems(), "system", ctxt,*pelemc);

		//Write block [1..*]
		WriteList<Block>( plane->Blocks(), "block", ctxt,*pelemc);
	}
	
	elem.InsertEndChild( pelemc);
}
