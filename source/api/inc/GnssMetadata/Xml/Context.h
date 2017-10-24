/**
 * File: Context.h
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

#ifndef CONTEXT_H_H
#define CONTEXT_H_H

namespace GnssMetadata
{
	class AttributedObject;
	class XmlProcessor;
	class Translator;

	/**
	 * Class defines the current collection context
	 */
	class Context
	{
	public:
		Context(XmlProcessor& _proc, Translator* _pParent, AttributedObject* _pContainer)
				: proc(_proc), pParent(_pParent), pContainer(_pContainer)
		{
		}

		/**
		 * XmlProcessor Reference.
		 */
		XmlProcessor& proc;

		/**
		 * Pointer to the parent translator
		 */
		Translator* pParent;

		/**
		 * Pointer to the attributed object being operated on.
		 */
		AttributedObject* pContainer;
	};
}

#endif
