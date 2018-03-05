/**
 * File: SystemTranslator.cpp
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


#include "SystemTranslator.h"
#include <GnssMetadata/System.h>
#include <GnssMetadata/RfConfiguration.h>
#include <GnssMetadata/Oscillator.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_SystemNodes)
	NODELIST_ENTRY( "freqbase",  TE_FREQUENCY)
	NODELIST_ENTRY( "equipment", TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "type",      TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "source",    TE_SOURCE)
	NODELIST_ENTRY( "cluster",   TE_CLUSTER)
//	NODELIST_ENTRY( "rfconfig",   TE_RFCONFIG)
//	NODELIST_ENTRY( "oscillator", TE_OSCILLATOR)
	NODELIST_ENTRY( "comment",	  TE_SIMPLE_TYPE)
	NODELIST_ENTRY( "artifact",  TE_SIMPLE_TYPE)
NODELIST_END

static const char* _szTypes[] = {"Undefined", "Processor", "Receiver", "Simulator"};
System::SystemType ToSystemType( const char* pszFmt)
{
    for( unsigned int i = 0; i < 4; i++)
	{
		if( strcmp( _szTypes[i], pszFmt) == 0)
			return (System::SystemType)i;
	}
	return (System::SystemType)3;
}


SystemTranslator::SystemTranslator() 
: Translator( (NodeEntry*) _SystemNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool SystemTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	const XMLElement* pchild;
	if( pAdaptor == NULL)
		return false;
	System system;

	bool bRetVal = true;

	//Parse the AttributedObject Elements.
	if( !ReadAttributedObject( system, ctxt, elem))
		return false;

	//Done processing element, if no children, meaning this is 
	//an element referencing another element.
	if( elem.NoChildren())
		system.IsReference(true);
	else
	{
		//Parse freqbase [0..1]
		pchild = elem.FirstChildElement("freqbase");
		AccessorAdaptor<System, Frequency> adpt( &system, &System::BaseFrequency);
		bRetVal = ReadElement( system, ctxt, *pchild, &adpt);

		//Parse Equipment [0..1]
		system.Equipment(ReadFirstElement( "equipment", elem, false, ""));

		//Parse Type Attribute. [0..1]
		System::SystemType stype = ToSystemType( ReadFirstElement("types", elem, false, ""));
		system.Type( stype);

		//Read source elements [1..*]
		bRetVal &= ReadList<Source>(system.Sources(), "source", ctxt, elem);

		//Read cluster elements [0..*]
		bRetVal &= ReadList<Cluster>(system.Clusters(), "cluster", ctxt, elem);
	}

	//Lastly set the channel on the specified object.
	pAdaptor->set( &system);
	return bRetVal;
}
/**
 * Write the current object 
 */
void SystemTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem )
{
	const System* psystem = dynamic_cast< const System*>(pObject);
	if( psystem == NULL) 
		throw TranslationException("SystemTranslator cannot cast System object");

	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	WriteAttributedObject( *psystem, ctxt, *pelemc);

	if( !psystem->IsReference())
	{
		//Write Frequency Base.
		WriteElement( &psystem->BaseFrequency(), "freqbase", ctxt, *pelemc);
	
		//Write Equipment [0..1]
		WriteElement("equipment", psystem->Equipment().c_str(),  pelemc, false, "");

		//Write Type Attribute [0..1]
		WriteElement( "types", _szTypes[psystem->Type()], pelemc, false, "");

		//Write source elements [1..*]
		WriteList<Source>( psystem->Sources(), "source", ctxt,*pelemc);

		//Write cluster elements [0..*]
		WriteList<Cluster>( psystem->Clusters(), "cluster", ctxt,*pelemc);
	}
	
	elem.InsertEndChild( pelemc);
}
