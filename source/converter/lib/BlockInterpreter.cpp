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

#include "BlockInterpreter.h"

BlockInterpreter::BlockInterpreter( const uint32_t cycles, const uint32_t headerBytes, const uint32_t footerBytes ) : 
mCycles(cycles),
mChunkIndex(0),
mHeaderBytes(headerBytes),
mFooterBytes(footerBytes),
mCommonChunkPeriod(1),
mHeadFootSink(NULL)
{

	mChunkInterpreters.resize(0);

}

BlockInterpreter::~BlockInterpreter()
{

   for( std::vector<Chunk*>::iterator It = mChunkInterpreters.begin(); It != mChunkInterpreters.end(); ++It )
      delete (*It);

}

void BlockInterpreter::SetHeadFootSink( BinarySink* pHeadFootSink )
{
   
   mHeadFootSink = pHeadFootSink;
};

void BlockInterpreter::AddChunk(Chunk* newChunk)
{

	mChunkInterpreters.push_back(newChunk);

}

double BlockInterpreter::GetChunkPeriod() const
{
   return mCommonChunkPeriod;
}

void BlockInterpreter::SetChunkPeriod(const double chunkPeriod)
{
   mCommonChunkPeriod = chunkPeriod;
}

std::vector<Chunk*>& BlockInterpreter::ChunkInterpreters()
{
   return mChunkInterpreters;
}


uint64_t BlockInterpreter::Interpret( BinarySource* packedFile, uint64_t bytesToProcess )
{

   uint64_t bytesProcessed   = 0;
   uint64_t thisConvertBytes = 0;
   
   //if we are passed '0' then interpret the entire file
   if( bytesToProcess == 0 )
   {
      do
      {
         // a collection of chunks represents the minimum possible convertion size
         // so always convert at least this much
         thisConvertBytes = InterpretChunks( packedFile );
         bytesProcessed += thisConvertBytes;
         
      }
      while( thisConvertBytes > 0 );
   }
   //otherwise interpret 'bytesToProcess' or the entire file, whichever is smaller
   else
   {
      while( bytesProcessed < bytesToProcess && thisConvertBytes > 0 )
      {
         // a collection of chunks represents the minimum possible convertion size
         // so always convert at least this much
         thisConvertBytes = InterpretChunks( packedFile );
         bytesProcessed += thisConvertBytes;
      }
   }
   
   return bytesProcessed;
}



uint64_t BlockInterpreter::InterpretChunks( BinarySource* packedFile )
{

   uint64_t startBytes = packedFile->SourcePos();
   
   if(mChunkIndex == 0)
   {
      //first process the header-bytes
      if( mHeaderBytes > 0 )
      {
         std::vector<uint8_t> headerBytes;
         headerBytes.resize(mHeaderBytes);
         packedFile->Get( &headerBytes[0], mHeaderBytes );
         if( mHeadFootSink != NULL )
         {
            mHeadFootSink->Put(&headerBytes[0], mHeaderBytes);
         }
      }
   }
   
   //now cycle through each chunk in the block and interpret
   for( std::vector<Chunk*>::iterator ckIt = mChunkInterpreters.begin(); ckIt != mChunkInterpreters.end(); ++ckIt )
   {
      mChunkIndex++;

      //get the chunk memory from the chunk interpreter
      char*    pChunk = static_cast<char*>( (*ckIt)->GetChunk() );
      uint32_t nBytes = (*ckIt)->BytesPerChunk();
      
      //read one chunk
      if( packedFile->Get( pChunk, nBytes ) == static_cast<std::streamsize>(nBytes) )
      {
         (*ckIt)->Interpret( );
      }
      else
      {
         //not enough data
         break;
      }
      
   }

   if(mChunkIndex == mCycles)
   {
      //first process the header-bytes
      if( mFooterBytes > 0 )
      {
         std::vector<uint8_t> footerBytes;
         footerBytes.resize(mFooterBytes);
         packedFile->Get( &footerBytes[0], mFooterBytes );
         if( mHeadFootSink != NULL )
         {
            mHeadFootSink->Put(&footerBytes[0], mFooterBytes);
         }
      }
      
      mChunkIndex = 0;
   }
   
   //a full chunk-set was read, return number of bytes read
   return ( packedFile->SourcePos() - startBytes );
}







