/**
 * File: BandTranslator.cpp
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

#include "BandTranslator.h"
#include <GnssMetadata/Band.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_BandNodes)
NODELIST_ENTRY("centerfreq", TE_FREQUENCY)
NODELIST_ENTRY("translatedfreq", TE_FREQUENCY)
NODELIST_ENTRY("inverted", TE_SIMPLE_TYPE)
NODELIST_ENTRY("delaybias", TE_DURATION)
NODELIST_ENTRY("bandwidth", TE_FREQUENCY)
NODELIST_ENTRY("comment", TE_SIMPLE_TYPE)
NODELIST_ENTRY("artifact", TE_SIMPLE_TYPE)
NODELIST_END

BandTranslator::BandTranslator()
		: Translator((NodeEntry*)_BandNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool BandTranslator::OnRead(Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	const XMLElement* pchild;
	if (pAdaptor == NULL) return false;
	Band band;

	bool bRetVal = true;

	// Parse the AttributedObject Elements.
	if (!ReadAttributedObject(band, ctxt, elem)) return false;

	// Done processing element, if no children, meaning this is
	// an element referencing another element.
	if (elem.NoChildren())
	{
		band.IsReference(true);
	}
	else
	{
		// Parse CenterFrequency
		pchild = elem.FirstChildElement("centerfreq");
		AccessorAdaptor<Band, Frequency> adpt(&band, &Band::CenterFrequency);
		bRetVal = ReadElement(band, ctxt, *pchild, &adpt);

		// Parse Translated Frequency
		pchild = elem.FirstChildElement("translatedfreq");
		AccessorAdaptor<Band, Frequency> adpt1(&band, &Band::TranslatedFrequency);
		bRetVal &= ReadElement(band, ctxt, *pchild, &adpt1);

		// Inverted Element
		band.Inverted(ReadFirstElement("inverted", elem, false, false));

		// delaybias
		pchild = elem.FirstChildElement("delaybias");
		if (pchild != NULL)
		{
			AccessorAdaptor<Band, Duration> adpt(&band, &Band::DelayBias);
			bRetVal &= ReadElement(band, ctxt, *pchild, &adpt);
		}

		// Parse bandwidth
		pchild = elem.FirstChildElement("bandwidth");
		if (pchild != NULL)
		{
			AccessorAdaptor<Band, Frequency> adpt(&band, &Band::Bandwidth);
			bRetVal = ReadElement(band, ctxt, *pchild, &adpt);
		}
	}

	// Lastly set the band on the specified object.
	if (bRetVal) pAdaptor->set(&band);
	return bRetVal;
}

/**
 * Write the current object
 */
void BandTranslator::OnWrite(const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem)
{
	const Band* pband = dynamic_cast<const Band*>(pObject);
	if (pband == NULL) throw TranslationException("BandTranslator cannot cast Band object");

	XMLElement* pelemc = elem.GetDocument()->NewElement(pszName);

	// Fill out id, artifacts, and comments last in accordance
	// with schema.
	// Band must define id so it can be referenced in bandsrc.
	WriteAttributedObject(*pband, ctxt, *pelemc, true);

	if (!pband->IsReference())
	{
		// Write CenterFrequency
		WriteElement(&pband->CenterFrequency(), "centerfreq", ctxt, *pelemc);

		// Write Translated Frequency
		WriteElement(&pband->TranslatedFrequency(), "translatedfreq", ctxt, *pelemc);

		// Inverted Element
		WriteElement("inverted", pband->Inverted(), pelemc, false, false);

		// Write delaybias
		WriteElement(&pband->DelayBias(), "delaybias", ctxt, *pelemc);

		// Write bandwidth
		WriteElement(&pband->Bandwidth(), "bandwidth", ctxt, *pelemc);
	}

	elem.InsertEndChild(pelemc);
}
