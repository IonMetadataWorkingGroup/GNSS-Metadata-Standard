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
mCommonChunkPeriod(1)
{

	mChunkInterpreters.resize(0);

};

BlockInterpreter::~BlockInterpreter()
{

   for( std::vector<Chunk*>::iterator It = mChunkInterpreters.begin(); It != mChunkInterpreters.end(); ++It )
      delete (*It);

};

void BlockInterpreter::AddChunk(Chunk* newChunk)
{

	mChunkInterpreters.push_back(newChunk);

};

const double BlockInterpreter::GetChunkPeriod() const
{
   return mCommonChunkPeriod;
};

void BlockInterpreter::SetChunkPeriod(const double chunkPeriod)
{
   mCommonChunkPeriod = chunkPeriod;
};

std::vector<Chunk*>& BlockInterpreter::ChunkInterpreters()
{
   return mChunkInterpreters;
};


bool BlockInterpreter::Interpret( BinaryFileSource& packedFile, uint32_t& bytesProcessed, uint32_t bytesToProcess )
{
   
   //first skip the header-bytes
   packedFile.Skip(mHeaderBytes);
   
   bool continueChunkInterpret = true;
   while( continueChunkInterpret )
   {
      
      //keep a track of how many chunk-patterns have been interpreted
      uint32_t chunkPatternCount = 0;
      
      //now cycle through each chunk in the block and interpret
      for( std::vector<Chunk*>::iterator ckIt = mChunkInterpreters.begin(); ckIt != mChunkInterpreters.end(); ++ckIt )
      {
         //get the chunk memory from the chunk interpreter
         char*    pChunk = static_cast<char*>( (*ckIt)->GetChunk() );
         uint32_t nBytes = (*ckIt)->BytesPerChunk();
         
         //read one chunk
         if( packedFile.Get( pChunk, nBytes ) == static_cast<std::streamsize>(nBytes) )
         {

            (*ckIt)->Interpret( );
            bytesProcessed += nBytes;
            
            if( bytesToProcess != 0 && ( bytesProcessed >= bytesToProcess ) )
            {
               //not very clean, but keep for now (later process integer blocks?)
               return false;
            }
         }
         else
         {
            //out of data
            return false;
         }
         
      }
      
      if( mCycles != 0 )
      {
         chunkPatternCount++;
         continueChunkInterpret = (chunkPatternCount < mCycles);
      }
      
   }
   
   //finally skip the footer-bytes
   packedFile.Skip( mFooterBytes );
   
   //otherwise, a full block was read
   return true;
};



bool BlockInterpreter::InterpretChunks( BinaryFileSource& packedFile )
{
   
   if(mChunkIndex == 0)
   {
      //first skip the header-bytes
      packedFile.Skip( mHeaderBytes );
   }
   
   //now cycle through each chunk in the block and interpret
   for( std::vector<Chunk*>::iterator ckIt = mChunkInterpreters.begin(); ckIt != mChunkInterpreters.end(); ++ckIt )
   {
      mChunkIndex++;

      //get the chunk memory from the chunk interpreter
      char*    pChunk = static_cast<char*>( (*ckIt)->GetChunk() );
      uint32_t nBytes = (*ckIt)->BytesPerChunk();
      
      //read one chunk
      if( packedFile.Get( pChunk, nBytes ) == static_cast<std::streamsize>(nBytes) )
      {
         (*ckIt)->Interpret( );
      }
      else
      {
         //not enough data
         return false;
      }
      
   }

   if(mChunkIndex == mCycles)
   {
      //finally skip the footer-bytes
      packedFile.Skip( mFooterBytes );
      mChunkIndex = 0;
   }
   
   //a full chunk set was read
   return true;
};







