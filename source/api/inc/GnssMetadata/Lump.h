/**
 * File: Lump.h
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

#ifndef LUMP_H_H
#define LUMP_H_H

#include "BaseTypes.h"
#include "IonStream.h"
#include "AttributedObject.h"

namespace GnssMetadata
{
	/**
	 * Class defines a collection of sample words organized into a contiguous block. This is known as a Lump in the
	 * current draft specification.
	 */
	class Lump : public AttributedObject
	{
	public:

		enum LumpShift
		{
			shiftLeft,
			shiftRight,
			shiftUndefined
		};

		/**
		 * Default constructor for the lump.
		 */
		Lump(const IonString& id = "", bool bIsReference = false)
				: AttributedObject(id, bIsReference),
				  streamArray(nullptr), streamCount(0), lumpSize(0),
				  _shift(LumpShift::shiftUndefined)
		{}

		Lump(const Lump& rhs)
				: AttributedObject(rhs),
				  streamArray(nullptr), streamCount(0), lumpSize(0),
				  _streamlist(rhs._streamlist),
				  _shift(rhs._shift)
		{}

		const Lump& operator=(const Lump& rhs)
		{
			if (&rhs == this) return *this;
			AttributedObject::operator =(rhs);
			_streamlist = rhs._streamlist;
			_shift = rhs._shift;
			return *this;
		}

		const GnssMetadata::StreamList& Streams() const { return _streamlist; }
		GnssMetadata::StreamList& Streams() { return _streamlist; }

		void Shift(const LumpShift shift) { _shift = shift; }
		LumpShift Shift() const { return _shift; }

		/**
		 * Returns a string representation of the object.
		 */
		virtual IonString toString(const IonString & sFormat = DefaultFormat) const;

		/**
		 * Virtual function traverses collections of attributed objects looking for object with the
		 * specified id.  Returns the count of objects found.
		 */
		virtual size_t FindObject(SearchItem::List& listResults,
		        const IonString& sid, const AttributedObject& rparent, bool bExcludeReference = true, int nDepth = -1) const;

		//TODO: Privatize and write a method.
		GnssMetadata::IonStream** streamArray;
		int streamCount;
		int lumpSize;

	private:
		GnssMetadata::StreamList _streamlist;
		GnssMetadata::Lump::LumpShift _shift;
	};

	typedef std::list<Lump> LumpList;
}

#endif
