/**
 * File: Metadata.h
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

#ifndef METADATA_H_H
#define METADATA_H_H

#include "AttributedObject.h"
#include "Band.h"
#include "File.h"
#include "Lane.h"
#include "Block.h"
#include "Chunk.h"
#include "Lump.h"
#include "AnyUri.h"
#include "IonStream.h"
#include "Session.h"
#include "System.h"
#include "BaseTypes.h"

namespace GnssMetadata
{
	/**
	 * Container class for all GNSS Metadata information. This class is the starting
	 * point for creating metadata for datafiles.
	 */
	class Metadata: public AttributedObject
	{
	public:
		Metadata( const IonString& id) : AttributedObject( id){}
		Metadata() {}
		Metadata(const Metadata& rhs) 
			: AttributedObject( rhs), _includes(rhs._includes), _files( rhs._files),
			_filesets( rhs._filesets), _bands(rhs._bands), _streams(rhs._streams), 
			_lumps( rhs._lumps), _chunks(rhs._chunks), _blocks(rhs._blocks),
			_lanes(rhs._lanes), _sessions( rhs._sessions),
			_systems(rhs._systems)
		{}	


		const Metadata& operator=( const Metadata& rhs)
		{
			if( &rhs == this)
				return *this;
			AttributedObject::operator =(rhs);

			_includes = rhs._includes;
			_files = rhs._files;
			_filesets = rhs._filesets;
			_bands = rhs._bands; 
			_streams = rhs._streams; 
			_lumps = rhs._lumps;
			_chunks = rhs._chunks;
			_blocks = rhs._blocks;
			_lanes = rhs._lanes;
			_sessions = rhs._sessions;
			_systems = rhs._systems;
			return *this;
		}

		/**
		 * Method combines one metadata object with another. It does not 
		 * override local id.  Only collections are combined.
		 */
		void  Splice( Metadata& rhs);

		const AnyUriList& Includes() const 
		{
			return _includes;
		}
		AnyUriList& Includes()
		{
			return _includes;
		}

		const FileList& Files( ) const
		{
			return _files;
		}
		FileList& Files( )
		{
			return _files;
		}

		const FileSetList& FileSets( ) const
		{
			return _filesets;
		}
		FileSetList& FileSets( )
		{
			return _filesets;
		}


		const BandList& Bands( ) const
		{
			return _bands;
		}
		BandList& Bands( ) 
		{
			return _bands;
		}

		const StreamList& Streams( ) const
		{
			return _streams;
		}
		StreamList& Streams( )
		{
			return _streams;
		}

		const LumpList& Lumps( ) const
		{
			return _lumps;
		}
		LumpList& Lumps( )
		{
			return _lumps;
		}

		const ChunkList& Chunks( ) const
		{
			return _chunks;
		}
		ChunkList& Chunks( )
		{
			return _chunks;
		}

		const BlockList& Blocks( ) const
		{
			return _blocks;
		}
		BlockList& Blocks( )
		{
			return _blocks;
		}

		const LaneList& Lanes( ) const
		{
			return _lanes;
		}
		LaneList& Lanes( )
		{
			return _lanes;
		}

		const SessionList& Sessions( ) const
		{
			return _sessions;
		}
		SessionList& Sessions( )
		{
			return _sessions;
		}

		const SystemList& Systems( ) const
		{
			return _systems;
		}
		SystemList& Systems( )
		{
			return _systems;
		}
		
		/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual IonString toString( const IonString & sFormat = DefaultFormat ) const;

		/**
		 * Virtual function traverses collections of attributed objects looking for object with the
		 * specified id.  Returns the count of objects found.
		 */
		virtual size_t FindObject( SearchItem::List& listResults, 
			const IonString& sid, const AttributedObject& rparent, bool bExcludeReference=true, int nDepth =-1) const;

	private:
		AnyUriList  _includes;

		FileList _files;

		FileSetList  _filesets;

		BandList  _bands;

		StreamList _streams;

		LumpList _lumps;

		ChunkList _chunks;

		BlockList _blocks;

		LaneList _lanes;
		
		SessionList _sessions;

		SystemList _systems;	
	};
	
}


#endif
