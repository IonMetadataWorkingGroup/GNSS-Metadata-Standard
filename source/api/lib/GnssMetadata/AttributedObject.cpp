/**
 * File: AttributedObject.cpp
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

#include <GnssMetadata/AttributedObject.h>
using namespace GnssMetadata;

/**
 *This should be defined in basetypes.cpp, but that file
 *does not currently exist.
 */
const IonString Object::DefaultFormat = "";

/**
 *  Returns a string representation of the object.
 *
 */
IonString AttributedObject::toString(const IonString & /*sFormat*/) const
{
	return _id;
}

/**
 * Virtual function implemented by derived classes traverses collections of attributed objects looking for object with the
 * specified id. Returns the count of objects found.
 */
size_t AttributedObject::FindObject(SearchItem::List& listResults, const IonString& sid, const AttributedObject& rparent, bool bExcludeReference, int /*nDepth*/) const
{
	size_t count = 0;

	// If it matches the ID an type of object specified, add to list.
	if (this->_id == sid && !(bExcludeReference && _bIsReference))
	{
		AttributedObject::SearchItem si;
		si.pParent = &rparent;
		si.pObject = this;
		listResults.push_back(si);
		count++;
	}
	return count;
}
