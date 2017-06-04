/**
 * File: SourceTranslator.cpp
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


#include "SourceTranslator.h"
#include <GnssMetadata/Source.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_SourceNodes)
NODELIST_ENTRY( "type", TE_STREAM)
NODELIST_ENTRY( "polarization", TE_STREAM)
NODELIST_ENTRY( "origin", TE_POSITION)
NODELIST_ENTRY( "orientation", TE_ORIENTATION)
NODELIST_ENTRY( "idcluster", TE_SIMPLE_TYPE)
NODELIST_ENTRY( "stream", TE_STREAM)
NODELIST_END


// SourceType Values
static const char* _szSourceType[] = {"UndefinedType","Patch", "Dipole", "Helical", "Quadrilfilar", "Simulator"};
Source::SourceType ToSourceType( const char* psz)
{
    for( unsigned int i = 0; i < 6; i++)
	{
		if( strcmp( _szSourceType[i], psz) == 0)
			return (Source::SourceType)i;
	}
	return (Source::SourceType)0;
}

// Word Padding
static const char* _szSourcePolarization[] = {"UndefinedPolarization", "RHCP", "LHCP", "Linear", "Horizontal", "Vertical"};
Source::SourcePolarization ToSourcePolarization( const char* psz)
{
    for( unsigned int i = 0; i < 5; i++)
	{
		if( strcmp( _szSourcePolarization[i], psz) == 0)
			return (Source::SourcePolarization)i;
	}
	return (Source::SourcePolarization)2;
}


SourceTranslator::SourceTranslator() 
: Translator( (NodeEntry*) _SourceNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool SourceTranslator::OnRead( Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor )
{
	if( pAdaptor == NULL)
		return false;
	Source source;

	bool bRetVal = true;

	//Parse the AttributedObject Elements.
	if( !ReadAttributedObject( source, ctxt, elem))
		return false;

	//Done processing element, if no children, meaning this is 
	//an element referencing another element.
	if( elem.NoChildren())
		source.IsReference(true);
	else
	{
		const XMLElement* pchild;

		//Parse type [0..1]
		pchild = elem.FirstChildElement("type");
		if( pchild != NULL)
		{
			source.Type( ToSourceType( pchild->GetText()));
		}

		//Parse polarization [0..1]
		pchild = elem.FirstChildElement("polarization");
		if( pchild != NULL)
		{
			source.Polarization( ToSourcePolarization( pchild->GetText()));
		}

		//Parse origin [0..1]
		pchild = elem.FirstChildElement("origin");
		if( pchild != NULL)
		{
			AccessorAdaptor<Source, Position> adapt(&source, &Source::Origin);
			bRetVal &= ReadElement( source, ctxt, *pchild, &adapt);
		}

      //Parse orientation [0..1]
		pchild = elem.FirstChildElement("orientation");
		if( pchild != NULL)
		{
			AccessorAdaptor<Source, Orientation> adapt(&source, &Source::Orientation);
			bRetVal &= ReadElement( source, ctxt, *pchild, &adapt);
		}

		//Parse idcluster [0..1]
		source.IdCluster( ReadFirstElement("idcluster", elem, false, ""));
	}

	//Lastly set the source on the specified object.
	if( bRetVal)
		pAdaptor->set( &source);
	return bRetVal;
}
/**
 * Write the current object 
 */
void SourceTranslator::OnWrite( const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem )
{
	const Source* psource = dynamic_cast< const Source*>(pObject);
	if( psource == NULL) 
		throw TranslationException("SourceTranslator cannot cast Source object");

	XMLElement* pelemc = elem.GetDocument()->NewElement( pszName);

	//Fill out id, artifacts, and comments last in accordance
	//with schema.
	//Source object must have ID defined in order to support association
	//with bandsrc.
	WriteAttributedObject( *psource, ctxt, *pelemc, true);

	if( !psource->IsReference())
	{
		XMLElement* pelem;

		//Write type [0..1]
		pelem = elem.GetDocument()->NewElement( "type");
		pelem->SetText( _szSourceType[ psource->Type()] );
		pelemc->InsertEndChild( pelem);

		//Write polarization [0..1]
		pelem = elem.GetDocument()->NewElement( "polarization");
		pelem->SetText( _szSourcePolarization[ psource->Polarization()] );
		pelemc->InsertEndChild( pelem);

		//Write origin [0..1]
		WriteElement( &psource->Origin(), "origin", ctxt, *pelemc);
		
      //Write orientation [0..1]
		WriteElement( &psource->Orientation(), "orientation", ctxt, *pelemc);


		//Write idcluster [0..1]
		WriteElement("idcluster",psource->IdCluster().c_str(), pelemc, false, "");
	}
	
	elem.InsertEndChild( pelemc);
}
