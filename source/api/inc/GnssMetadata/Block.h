/**
 * File: Block.h
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

#ifndef BLOCK_H_H
#define BLOCK_H_H

#include "BaseTypes.h"
#include "Chunk.h"

namespace GnssMetadata
{
	class Datafile;

	/**
	 * Class defines a metadata block.
	 */
	class Block: public AttributedObject
	{
		
	public:
		/**
		 * Default constructor.
		 */
		Block( const IonString& id = "", bool bIsReference = false)
			: AttributedObject( id, bIsReference), _cycles( 0), _sizeHeader(0), 
			_sizeFooter(0)
		{
			
		}

		Block( size_t cycles, size_t sizeHeader=0, size_t sizeFooter = 0, const IonString& id="")
			: AttributedObject(id, false), _cycles( cycles), _sizeHeader(sizeHeader), _sizeFooter( sizeFooter)
		{
		}

		Block( const Block& rhs) 
		: AttributedObject(rhs), _cycles( rhs._cycles), _sizeHeader( rhs._sizeHeader), _sizeFooter( rhs._sizeFooter),
		  _chunklist(rhs._chunklist)
		{
			
		}

		const Block& operator=( const Block& rhs)
		{
			if( &rhs == this)
				return *this;
			AttributedObject::operator =(rhs);
			
			_cycles = rhs._cycles;
			_sizeHeader = rhs._sizeHeader;
			_sizeFooter = rhs._sizeFooter; 
			_chunklist = rhs._chunklist;
			return *this;
		}

		/**
		 * Returns true if Subframe state is not in default configuration.
		 */
		bool IsDefined() const 
		{
			return _cycles > 0 && _chunklist.size() > 0;
		}

		/**
		 * Sets the number of cycles.
		 */
		void Cycles( const size_t cycles )
		{
			_cycles = cycles;
		}

		/**
		 * Gets the number of cycles.
		 */
		size_t Cycles( ) const
		{
			return _cycles;
		}

		/**
		 * Gets the size of the header in bytes..
		 */
		size_t SizeHeader( ) const
		{
			return _sizeHeader;
		}
		/**
		 * Sets the size of the footer in bytes.
		 */
		void SizeHeader( const size_t size )
		{
			_sizeHeader = size;
		}

		/**
		 * Gets the size of the footer in bytes..
		 */
		size_t SizeFooter( ) const
		{
			return _sizeFooter;
		}
		/**
		 * Sets the size of the footer in bytes.
		 */
		void SizeFooter( const size_t size )
		{
			_sizeFooter = size;
		}

		const GnssMetadata::ChunkList& Chunks( ) const
		{
			return _chunklist;
		}
		GnssMetadata::ChunkList& Chunks( )
		{
			return _chunklist;
		}



		/**
		 * Returns a string representation of the object.
		 */
		virtual IonString toString( const IonString & sFormat = DefaultFormat ) const;

		/**
		 * Virtual function traverses collections of attributed objects looking for object with the
		 * specified id.  Returns the count of objects found.
		 */
		virtual size_t FindObject( SearchItem::List& listResults, 
			const IonString& sid, const AttributedObject& rparent, bool bExcludeReference=true, int nDepth =-1) const;
				
		//TODO: Privatize and write a method.
		GnssMetadata::Chunk** chunkArray;
		int chunkCount;
		
	private:
		size_t _cycles;
		size_t _sizeHeader;
		size_t _sizeFooter;
		
		GnssMetadata::ChunkList _chunklist;
	};
	
	typedef std::list<Block> BlockList;
}


#endif
