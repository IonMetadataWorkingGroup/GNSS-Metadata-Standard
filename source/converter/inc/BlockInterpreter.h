/**
 * Author: James T. Curran
 *  
 * Copyright(c) 2015 Institute of Navigation
 * http://www.ion.org
 *  
 * This Metadata Converter is free software; you can redistribute it and/or
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

#ifndef CLASS_BlockInterpreter
#define CLASS_BlockInterpreter
#include <vector>
#include <GnssMetadata/Metadata.h>
#include "ChunkInterpreter.h"
#include <BinaryFileSource.h>

class BlockInterpreter
{


protected:	

   uint32_t            mCycles;
   uint32_t            mChunkIndex;
	uint32_t            mHeaderBytes;
   uint32_t            mFooterBytes;

   std::vector<Chunk*> mChunkInterpreters;
   
   double              mCommonChunkPeriod;
	
public:	
   BlockInterpreter( const uint32_t cycles, const uint32_t headerBytes, const uint32_t footerBytes );
	virtual  ~BlockInterpreter();

   virtual void AddChunk(Chunk* newChunk);
   virtual uint64_t Interpret( BinaryFileSource& packedFile, uint64_t bytesToProcess );
   virtual uint64_t InterpretChunks( BinaryFileSource& packedFile );
   
   std::vector<Chunk*>& ChunkInterpreters();
   
   
   double GetChunkPeriod() const;
   void SetChunkPeriod(const double chunkPeriod);
};

#endif //CLASS_BlockInterpreter







