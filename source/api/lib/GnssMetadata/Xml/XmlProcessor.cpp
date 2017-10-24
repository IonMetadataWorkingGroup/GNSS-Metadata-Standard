/**
 * File: XmlProcessor.cpp
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

#include <GnssMetadata/Xml/XmlProcessor.h>
#include "XmlDefs.h"
#include "AnyUriTranslator.h"
#include "MetadataTranslator.h"
#include "StreamTranslator.h"
#include "BandTranslator.h"
#include "LumpTranslator.h"
#include "ChunkTranslator.h"
#include "BlockTranslator.h"
#include "LaneTranslator.h"
#include "FrequencyTranslator.h"
#include "FileTranslator.h"
#include "FileSetTranslator.h"
#include "DurationTranslator.h"
#include "PositionTranslator.h"
#include "OrientationTranslator.h"
#include "SystemTranslator.h"
#include "ClusterTranslator.h"
#include "SourceTranslator.h"
#include "SessionTranslator.h"
//#include "RfConfigTranslator.h"
//#include "OscillatorTranslator.h"
using namespace GnssMetadata;
using namespace tinyxml2;

#if !defined(_WIN32) && !defined(WIN64)
#define _snprintf snprintf
#endif

/******************************************************************************
 * Translator Lookup Implementation
 ******************************************************************************/

/**
 * Define a static array of translators.
 */
static struct TranslatorEntry
{
	TranslatorId id;
	Translator& translator;
} _Translators[] =
{
	// NOTE these must be in the same order as the TranslatorId enum.
	{ TE_ANYURI, *(new AnyUriTranslator()) },
	{ TE_FREQUENCY, *(new FrequencyTranslator()) },
	{ TE_DURATION, *(new DurationTranslator()) },
	{ TE_POSITION, *(new PositionTranslator()) },
	{ TE_ORIENTATION, *(new OrientationTranslator()) },
	{ TE_STREAM, *(new StreamTranslator()) },
	{ TE_BAND, *(new BandTranslator()) },
	{ TE_LUMP, *(new LumpTranslator()) },
	{ TE_CHUNK, *(new ChunkTranslator()) },
	{ TE_BLOCK, *(new BlockTranslator()) },
	{ TE_LANE, *(new LaneTranslator()) },
	{ TE_DATAFILE, *(new FileTranslator()) },
	{ TE_FILESET, *(new FileSetTranslator()) },
	{ TE_SYSTEM, *(new SystemTranslator()) },
	{ TE_CLUSTER, *(new ClusterTranslator()) },
	{ TE_SOURCE, *(new SourceTranslator()) },
	{ TE_SESSION, *(new SessionTranslator()) },
	// {TE_RFCONFIG, *(new RfConfigTranslator())},
	{ TE_METADATA, *(new MetadataTranslator()) }
	// {TE_OSCILLATOR, *(new OscillatorTranslator())},
};
#define COUNT_TRANSLATORS (sizeof(_Translators)/sizeof(TranslatorEntry))

/**
 * Helper function iterates Translator list given index.
 */
inline Translator& TranslatorFromId(TranslatorId id)
{
	if (id >= TE_END) throw GnssMetadata::OutOfRangeException("Invalid translator ID");
	return _Translators[id].translator;
}

/**
 * Helper function iterates provided NodeEntry array looking for the correct
 * translator ID.
 */
TranslatorId TranslatorIdFromElemName(const char* szNodeName, NodeEntry* pNodes)
{
	// Iterate to the end of the node entries.
	while (pNodes->idTranslator != TE_END)
	{
		if (strcmp(szNodeName, pNodes->pszNodeName) == 0) return pNodes->idTranslator;

		//Onto next node.
		pNodes++;
	}
	return TE_END;
}

/******************************************************************************
 * XmlProcessor Implementation
 ******************************************************************************/

/**
 * Returns a string representation of the object.
 */
IonString XmlProcessor::toString(const IonString & /*sFormat*/) const
{
	return "XmlProcessor";
}

/**
 * Loads a metadata object with data in the specified file.
 */
bool XmlProcessor::Load(const char* szFilename, const bool bProcessIncludes, Metadata & metadata)
{
	tinyxml2::XMLDocument doc;

	// TODO Figure out how to support non file URLS (e.g. hyperlinks).

	// Parse file with Tiny XML processor.
	XMLError err = doc.LoadFile(szFilename);
	if (err != XML_SUCCESS)
	{
		char buff[512];
		_snprintf(buff, 512, "XML parsing error in file, %s", szFilename);
		throw TranslationException(buff, err);
	}

	// Find the metadata element. There should be only one per file.
	const XMLElement* pmetadata = doc.FirstChildElement("metadata");
	if (pmetadata == NULL)
	{
		char buff[512];
		_snprintf(buff, 512, "Metadata element not found in file, %s", szFilename);
		throw TranslationException(buff);
	}

	// Translate the XML data using the standard metadata translator.
	Context ctxt(*this, NULL, &metadata);
	Translator& trans = TranslatorFromId(TE_METADATA);
	bool bRetVal = trans.OnRead(ctxt, *pmetadata, NULL);

	// If successful and caller requests processing of include
	// elements.  Process them recursively as well.
	if (bRetVal && bProcessIncludes)
	{
		Metadata mdchild;
		AnyUriList::const_iterator iter = metadata.Includes().begin();
		for (; iter != metadata.Includes().end() && bRetVal; iter++)
		{
			bRetVal = Load(iter->Value().c_str(), bProcessIncludes, mdchild);

			// If successful, combine metadata with parent.
			if (bRetVal) metadata.Splice(mdchild);
		}

		// If we were successful processing includes, remove includes, since
		// the data is now contained within the metadata object.
		if (bRetVal) mdchild.Includes().clear();
	}

	return bRetVal;

}

/**
 * Save the metadata object to the specified XML file.
 */
void XmlProcessor::Save(const char* szFilename, const Metadata & metadata)
{
	tinyxml2::XMLDocument doc;
	XMLDeclaration* decl = doc.NewDeclaration();
	doc.InsertFirstChild(decl);

	Context ctxt(*this, NULL, NULL);

	// Translate metadata into XML and Save if successful.
	Translator& trans = TranslatorFromId(TE_METADATA);
	trans.OnWrite(&metadata, "metadata", ctxt, doc);

	XMLError err = doc.SaveFile(szFilename);
	if (err != XML_SUCCESS) throw TranslationException("Tiny XML Translation Error", err);
}

/**
 * Processes the current element within the context of the attributed object.
 */
bool XmlProcessor::ReadElement(Context & ctxt, const tinyxml2::XMLElement & elem, AccessorAdaptorBase* pAdaptor)
{
	TranslatorId id = TE_END;
	const char* szNodeName = elem.Name();

	// Use the current translator if available to lookup appropriate
	// translator for the current element. If not available,
	// do a global search.
	if (ctxt.pParent != NULL)
	{
		id = TranslatorIdFromElemName(szNodeName, ctxt.pParent->GetAllowedNodes());
	}
	else // Do a global lookup.
	{
		for (unsigned int i = 0; i < COUNT_TRANSLATORS && id == TE_END; i++)
		{
			NodeEntry* pNodes = _Translators[i].translator.GetAllowedNodes();
			if (pNodes == NULL) continue;

			id = TranslatorIdFromElemName(szNodeName, pNodes);
		}
	}

	// Get the translator and attempt to process the current element.
	Translator& trans = TranslatorFromId(id);
	return trans.OnRead(ctxt, elem, pAdaptor);
}

/**
 * Writes the specified metadata object to xml within specified context
 */
void XmlProcessor::WriteElement(const Object * pObject, const char* pszName, Context & ctxt, tinyxml2::XMLElement & elem)
{
	TranslatorId id = TE_END;

	// Use the current translator if available to lookup appropriate
	// translator for the current element. If not available,
	// do a global search.
	if (ctxt.pParent != NULL)
	{
		id = TranslatorIdFromElemName(pszName, ctxt.pParent->GetAllowedNodes());
	}
	else // Do a global lookup.
	{
		for (unsigned int i = 0; i < COUNT_TRANSLATORS && id == TE_END; i++)
		{
			NodeEntry* pNodes = _Translators[i].translator.GetAllowedNodes();
			if (pNodes == NULL) continue;

			id = TranslatorIdFromElemName(pszName, pNodes);
		}
	}

	// Get the translator and attempt to process the current element.
	Translator& trans = TranslatorFromId(id);
	return trans.OnWrite(pObject, pszName, ctxt, elem);
}
