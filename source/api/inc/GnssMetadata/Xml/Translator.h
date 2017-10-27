/**
 * File: Translator.h
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

#ifndef TRANSLATOR_H_H
#define TRANSLATOR_H_H

#include "Context.h"
#include "XmlDefs.h"
#include <tinyxml2.h>
#include <list>

namespace GnssMetadata
{
	class Object;
	struct NodeEntry;
	struct AccessorAdaptorBase;

	/**
	 * All XML translators derive from this class and conform to the interface specifications
	 */
	class Translator
	{
		friend class XmlProcessor;

	protected:
		typedef const char* pcstr;

	public:
		Translator(NodeEntry* nodesAllowed = nullptr) : _nodesAllowed(nodesAllowed) { }
		virtual ~Translator();

		/**
		 * Reads the current node and translates into metadata defined
		 * by the subclass.
		 */
		virtual bool OnRead(Context & ctxt, const tinyxml2::XMLElement & elem, AccessorAdaptorBase* pAdaptor = NULL) = 0;
		/**
		 * Write the current object
		 */
		virtual void OnWrite(const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLNode & elem) = 0;

	protected:
		/**
		 * Accessor returns the array of allowed XML nodes for this
		 * instance of a translator.  Translators are associated with a XML
		 * element, and provides the information on valid sub-elements, if any.
		 * return NULL If sub-elements are not allowed.
		 */
		NodeEntry* GetAllowedNodes() const
		{
			return _nodesAllowed;
		}

		/**
		 * Processes the current element within the context of the attributed object, delegates
		 * out to XmlProcessor to allow other translators to process the data.
		 */
		bool ReadElement(AttributedObject& aobj, Context & ctxt, const tinyxml2::XMLElement & elem, AccessorAdaptorBase* pAdaptor);

		/**
		 * Writes the specified metadata object to XML within specified context
		 */
		void WriteElement(const Object * pObject, pcstr pszName, Context & ctxt, tinyxml2::XMLElement & elem);

		/**
		 * Reads the attributed object id, comments, and artifacts.
		 */
		static bool ReadAttributedObject(AttributedObject& aobj, Context& ctxt, const tinyxml2::XMLElement & elem, bool bIdAttributeRequired = true);

		/**
		 * Writes the attributed object id, comments, and artifacts. By default the id attribute is not required as long as the
		 * object is not a reference.
		 */
		static void WriteAttributedObject(const AttributedObject& aobj, Context& ctxt, tinyxml2::XMLElement & elem, bool bIdAttributeRequired = false);

		static bool ReadFirstElement(const char* pszelem, const tinyxml2::XMLElement& elem, bool bRequired, bool bDefault = false);
		static const char* ReadFirstElement(const char* pszelem, const tinyxml2::XMLElement& elem, bool bRequired, const char* pszDefault = "");
		static size_t ReadFirstElement(const char* pszelem, const tinyxml2::XMLElement& elem, bool bRequired, size_t iDefault = 0);
		static double ReadFirstElement(const char* pszelem, const tinyxml2::XMLElement& elem, bool bRequired, double dDefault = 0.0);

		static void WriteElement(const char* pszElemName, bool bvalue, tinyxml2::XMLElement* pcontainer, bool bRequired, const bool& bDefault = false);
		static void WriteElement(const char* pszElemName, const char* pszValue, tinyxml2::XMLElement* pcontainer, bool bRequired, const char* pszDefault = "");
		static void WriteElement(const char* pszElemName, size_t ivalue, tinyxml2::XMLElement* pcontainer, bool bRequired, const size_t& iDefault = 0);
		static void WriteElement(const char* pszElemName, double dvalue, tinyxml2::XMLElement* pcontainer, bool bRequired, const char* pszFormat = "%0.15le",
				const double& dDefault = 0.0);

		/**
		 * Helper function reads a list of elements.
		 */
		template<typename A>
		bool ReadList(std::list<A>& list, const char* pszName, Context& ctxt, const tinyxml2::XMLElement & elem)
		{
			bool bRetVal = true;
			const tinyxml2::XMLElement* pelem = elem.FirstChildElement(pszName);
			for (; pelem != NULL; pelem = pelem->NextSiblingElement(pszName))
			{
				ListAdaptor<A> adapt(list);
				bRetVal &= ReadElement(*(ctxt.pContainer), ctxt, *pelem, &adapt);
			}
			return bRetVal;
		}

		/**
		 * Helper function writes a list of attributed elements.
		 */
		template<typename A>
		void WriteList(const std::list<A>& list, const char* pszName,
				Context& ctxt, tinyxml2::XMLElement & elem)
		{
			typename std::list<A>::const_iterator iter = list.begin();

			for (; iter != list.end(); iter++)
			{
				WriteElement(&(*iter), pszName, ctxt, elem);
			}
		}

	private:
		NodeEntry* _nodesAllowed;
	};
}
#endif
