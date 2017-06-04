/**
 * File: SessionTranslator.cpp
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


#include "SessionTranslator.h"
#include <GnssMetadata/Session.h>
#include <GnssMetadata/RfConfiguration.h>
#include <GnssMetadata/Oscillator.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_SessionNodes)
	NODELIST_ENTRY( "toa",      TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "position",		 TE_POSITION)
	//TODO Attitude
	NODELIST_ENTRY( "poc",			 TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "contact",		 TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "campaign",		 TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "scenario",      TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "system",		 TE_SYSTEM)
	NODELIST_ENTRY( "comment",		 TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "artifact",		 TE_SIMPLE_TYPE)
NODELIST_END

SessionTranslator::SessionTranslator() 
: Translator( (NodeEntry*) _SessionNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool SessionTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	const XMLElement* pchild;
	bool bRetVal = true;
	Session session;

	if( pAdaptor == NULL)
		return false;


	//Parse the AttributedObject Elements.
	if( !ReadAttributedObject( session, ctxt, elem))
		return false;

	//Done processing element, if no children, meaning this is 
	//an element referencing another element.
	if( elem.NoChildren())
		session.IsReference(true);
	else
	{
		//Parse TOA	[0..1]
		pchild = elem.FirstChildElement("toa");
		if( pchild != NULL)
		{
			session.Toa(Date(pchild->GetText()));
		}

		//Parse Position [0..1]
		pchild = elem.FirstChildElement("position");
		if( pchild != NULL)
		{
			AccessorAdaptor<Session, Position> adapt(&session, &Session::Position);
			bRetVal &= ReadElement( session, ctxt, *pchild, &adapt);
		}

		//TODO Parse attitude [0..1]

		//Parse poc [0..1]
		session.Poc( ReadFirstElement("poc", elem, false, ""));

		//Parse contact [0..1]
		session.Contact( ReadFirstElement("contact", elem, false, ""));

		//Parse campaign [0..1]
		session.Campaign( ReadFirstElement("campaign", elem, false, ""));

		//Parse scenario [0..1]
		session.Scenario( ReadFirstElement("scenario", elem, false, ""));

		//Parse Systems [0..1]
		bRetVal &= ReadList<System>(session.Systems(), "system", ctxt, elem);
    }

	//Lastly set the session on the specified object.
	pAdaptor->set( &session);
	return bRetVal;
}
/**
 * Write the current object 
 */
void SessionTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem )
{
	const Session* psession = dynamic_cast< const Session*>(pObject);
	if( psession == NULL) 
		throw TranslationException("SessionTranslator cannot cast Session object");
	else if( psession->Id().length() == 0)
		return;
	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *psession, ctxt, *pelemc);

	if( !psession->IsReference())
	{
		XMLElement* pelem;
		
		//Write toa
		pelem = elem.GetDocument()->NewElement( "toa");
		pelem->SetText( psession->Toa().toString().c_str());
		pelemc->InsertEndChild( pelem);

		//Write Position
		WriteElement( &psession->Position(), "position", ctxt, *pelemc);

		//TODO Write Attitude 

		//Write poc
		WriteElement("poc",psession->Poc().c_str(), pelemc, false, "");

		//Write conact
		WriteElement("contact",psession->Contact().c_str(), pelemc, false, "");

		//Write campaign
		WriteElement("campaign",psession->Campaign().c_str(), pelemc, false, "");

		//Write scenario
		WriteElement("scenario",psession->Scenario().c_str(), pelemc, false, "");

		//Write system
		WriteList<System>( psession->Systems(), "system", ctxt,*pelemc);		//Write location
	}
	

	elem.InsertEndChild( pelemc);
}
