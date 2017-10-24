/**
 * File: Metadata.cpp
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

#include <GnssMetadata/Metadata.h>
using namespace GnssMetadata;

/**
 * Returns a string representation of the object.
 */
IonString Metadata::toString(const IonString & /*sFormat*/) const
{
	return "Metadata Object";
}

/**
 * Method combines one metadata object with another. It does not
 * override local id. Only collections are combined.
 */
void Metadata::Splice(Metadata& rhs)
{
	// Splice base class collections.
	Comments().splice(Comments().end(), rhs.Comments());
	Artifacts().splice(Artifacts().end(), rhs.Artifacts());

	//splice all the collections.
	_includes.splice(_includes.end(), rhs._includes);
	_files.splice(_files.end(), rhs._files);
	_filesets.splice(_filesets.end(), rhs._filesets);
	_bands.splice(_bands.end(), rhs._bands);
	_streams.splice(_streams.end(), rhs._streams);
	_lumps.splice(_lumps.end(), rhs._lumps);
	_chunks.splice(_chunks.end(), rhs._chunks);
	_blocks.splice(_blocks.end(), rhs._blocks);
	_lanes.splice(_lanes.end(), rhs._lanes);
	_sessions.splice(_sessions.end(), rhs._sessions);
	_systems.splice(_systems.end(), rhs._systems);
}

/**
 * Virtual function traverses collections of attributed objects looking for object with the
 * specified id. Returns the count of objects found.
 */
size_t Metadata::FindObject(SearchItem::List& listResults, const IonString& sid, const AttributedObject& rparent, bool bExcludeReference, int nDepth) const
{
	// Check this object first.
	size_t count = AttributedObject::FindObject(listResults, sid, rparent, bExcludeReference, nDepth);

	// Now check all collections:
	nDepth--;
	count += SearchList<File>(listResults, _files, sid, rparent, bExcludeReference, nDepth);
	count += SearchList<FileSet>(listResults, _filesets, sid, rparent, bExcludeReference, nDepth);
	count += SearchList<Band>(listResults, _bands, sid, rparent, bExcludeReference, nDepth);
	count += SearchList<IonStream>(listResults, _streams, sid, rparent, bExcludeReference, nDepth);
	count += SearchList<Lump>(listResults, _lumps, sid, rparent, bExcludeReference, nDepth);
	count += SearchList<Chunk>(listResults, _chunks, sid, rparent, bExcludeReference, nDepth);
	count += SearchList<Block>(listResults, _blocks, sid, rparent, bExcludeReference, nDepth);
	count += SearchList<Lane>(listResults, _lanes, sid, rparent, bExcludeReference, nDepth);
	count += SearchList<Session>(listResults, _sessions, sid, rparent, bExcludeReference, nDepth);
	count += SearchList<System>(listResults, _systems, sid, rparent, bExcludeReference, nDepth);

	return count;
}
