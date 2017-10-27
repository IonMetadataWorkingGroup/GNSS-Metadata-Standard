/**
 * File: ClusterTranslator.cpp
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

#include "ClusterTranslator.h"
#include <GnssMetadata/Cluster.h>
#include "XmlDefs.h"
#include <string.h>
#include <stdlib.h>

using namespace GnssMetadata;
using namespace tinyxml2;

NODELIST_BEGIN(_ClusterNodes)
NODELIST_ENTRY("position", TE_POSITION)
NODELIST_ENTRY("orientation",TE_ORIENTATION)
NODELIST_ENTRY("vendor", TE_SIMPLE_TYPE)
NODELIST_ENTRY("model", TE_SIMPLE_TYPE)
NODELIST_ENTRY("serial", TE_SIMPLE_TYPE)
NODELIST_END

ClusterTranslator::ClusterTranslator()
		: Translator((NodeEntry*)_ClusterNodes)
{
}

/**
 * Reads a node from the document and parses into metadata.
 */
bool ClusterTranslator::OnRead(Context & ctxt, const XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	const XMLElement* pchild;

	if (pAdaptor == nullptr) return false;
	Cluster cluster;

	bool bRetVal = true;

	// Parse the AttributedObject Elements.
	if (!ReadAttributedObject(cluster, ctxt, elem)) return false;

	// Done processing element, if no children, meaning this is
	// an element referencing another element.
	if (elem.NoChildren())
	{
		cluster.IsReference(true);
	}
	else
	{
		// Parse Position [0..1]
		pchild = elem.FirstChildElement("position");
		if (pchild != nullptr)
		{
			AccessorAdaptor<Cluster, Position> adapt(&cluster, &Cluster::Position);
			bRetVal &= ReadElement(cluster, ctxt, *pchild, &adapt);
		}

		// Parse Orientation [0..1]
		pchild = elem.FirstChildElement("orientation");
		if (pchild != nullptr)
		{
			AccessorAdaptor<Cluster, Orientation> adapt(&cluster, &Cluster::Orientation);
			bRetVal &= ReadElement(cluster, ctxt, *pchild, &adapt);
		}

		// Parse vendor [0..1]
		cluster.Vendor(ReadFirstElement("vendor", elem, false, ""));

		// Parse model [0..1]
		cluster.Model(ReadFirstElement("model", elem, false, ""));

		// Parse serial[0..1]
		cluster.Serial(ReadFirstElement("serial", elem, false, ""));
	}

	// Lastly set the cluster on the specified object.
	if (bRetVal) pAdaptor->set(&cluster);
	return bRetVal;
}

/**
 * Write the current object
 */
void ClusterTranslator::OnWrite(const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem)
{
	const Cluster* pcluster = dynamic_cast<const Cluster*>(pObject);
	if (pcluster == nullptr) throw TranslationException("ClusterTranslator cannot cast Cluster object");

	XMLElement* pelemc = elem.GetDocument()->NewElement(pszName);

	// Fill out id, artifacts, and comments last in accordance
	// with schema.
	WriteAttributedObject(*pcluster, ctxt, *pelemc);

	if (!pcluster->IsReference())
	{
		// Write Position [0..1]
		WriteElement(&pcluster->Position(), "position", ctxt, *pelemc);

		// Write Orientation [0..1]
		WriteElement(&pcluster->Orientation(), "orientation", ctxt, *pelemc);

		// Write vendor [0..1]
		WriteElement("vendor", pcluster->Vendor().c_str(), pelemc, false, "");

		// Write model [0..1]
		WriteElement("model", pcluster->Model().c_str(), pelemc, false, "");

		// Write model [0..1]
		WriteElement("serial", pcluster->Serial().c_str(), pelemc, false, "");
	}

	elem.InsertEndChild(pelemc);
}
