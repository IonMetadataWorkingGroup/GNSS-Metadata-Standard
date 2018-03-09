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

#include "EndianFunctions.h"
#include <algorithm>

template<typename chunk_t,typename sample_base_t>
ChunkInterpreter<chunk_t, sample_base_t>::ChunkInterpreter( const uint32_t countWords, const bool rightWordShift ) :
mSourceEndiannessIsDifferent(false),
mRightWordShift(rightWordShift)
{
   // make sure that there is sufficient space for the chunk data
   // no checks made later!
   mDataChunk.resize(countWords);
}

template<typename chunk_t,typename sample_base_t>
ChunkInterpreter<chunk_t, sample_base_t>::~ChunkInterpreter()
{

   //iterate through the sample interpreters and delete them
   for( std::deque<SampleInterpreter*>::iterator it = mSampleInterpreters.begin(); it != mSampleInterpreters.end(); ++it )
      delete (*it);

}

template<typename chunk_t,typename sample_base_t>
void ChunkInterpreter<chunk_t, sample_base_t>::AddSampleInterpreter( SampleInterpreter* splIntrp, const bool front )
{
   //add it to the list, this maintains an ordered list of sample interpreters, which extract a single sample or sample pair
   if( front )
      mSampleInterpreters.push_front( splIntrp );
   else
      mSampleInterpreters.push_back( splIntrp );

   //figure out what the sum of the preceeding bit-widths is
   uint32_t bitOffset = 0;
   for( std::deque<SampleInterpreter*>::iterator it=mSampleInterpreters.begin(); it!=mSampleInterpreters.end(); ++it )
   {
      //indicate the bit offset: this tells the sample-interpreter how many bits into the chunk to start decoding the sample
      (*it)->SetChunkOffset( bitOffset );
      bitOffset += (*it)->BitWidth();

   }

   //now add the sample interpreters to the call-ordered list, and sort based on the call index
   mCallOrderedSampleInterpreters.clear();
   for( std::deque<SampleInterpreter*>::iterator it=mSampleInterpreters.begin(); it!=mSampleInterpreters.end(); ++it )
   {
      mCallOrderedSampleInterpreters.push_back( *it );
   }

   mCallOrderedSampleInterpreters.sort( SampleInterpreter::callOrderSortAscend );

}

template<typename chunk_t,typename sample_base_t>
void* ChunkInterpreter<chunk_t, sample_base_t>::GetChunk()
{
   // we should be sure that enough space is allocated, but as we define
   // the ChunkSize at construction time, shouldn't change...
   return &( mDataChunk[0] );
}

template<typename chunk_t,typename sample_base_t>
uint32_t ChunkInterpreter<chunk_t, sample_base_t>::BytesPerChunk() const
{
   //so that we can read/memcopy into it
   return ( sizeof( chunk_t ) * static_cast<uint32_t>( mDataChunk.size() ) );
}


template<typename chunk_t,typename sample_base_t>
void ChunkInterpreter<chunk_t, sample_base_t>::SetSourceEndianness( const GnssMetadata::Chunk::WordEndian& srcEndianness )
{
   mSourceEndiannessIsDifferent = false;

   //no need to swap char arrays
   if( sizeof( chunk_t ) == 1 )
      return;

   //no need to swap if the source is undefined
   if( srcEndianness == GnssMetadata::Chunk::Undefined )
      return;

   //check my own endianness
    uint16_t number = 0x1;
    uint8_t *numPtr = (uint8_t*)&number;
    GnssMetadata::Chunk::WordEndian myEndianness = ( (numPtr[0] == 1) ? GnssMetadata::Chunk::Little : GnssMetadata::Chunk::Big );

    //printf("I am %s endian.\n",(myEndianness==GnssMetadata::Chunk::Little?"Little":"Big"));

    mSourceEndiannessIsDifferent = ( myEndianness != srcEndianness );
}

template<typename chunk_t,typename sample_base_t>
void ChunkInterpreter<chunk_t, sample_base_t>::ChangeCunkEndianness( )
{

   //printf("Warning: `ChunkInterpreter::ChangeCunkEndianness( )' not yet tested!\n");

   //it seems some compilers don't like dependent definitions of iterators...
   typedef typename std::vector<chunk_t>::iterator iterator;
   for( iterator it = mDataChunk.begin(); it != mDataChunk.end(); ++it )
   {
      (*it) = EndianFunctions::ChangeEndianness( *it );
   }

}


template<typename chunk_t,typename sample_base_t>
void ChunkInterpreter<chunk_t, sample_base_t>::Interpret( )
{

   //the first thing we should do here is correct the endian-ness of the data.
   if( mSourceEndiannessIsDifferent )
       ChangeCunkEndianness();

   //go through the ordered grouping of interpreters, and let each one extract some samples, and push them to the associated sampleSink.
   if( mRightWordShift )
   {
      std::reverse(mDataChunk.begin(),mDataChunk.end());
   }

   for( std::list<SampleInterpreter*>::iterator it=mCallOrderedSampleInterpreters.begin(); it!=mCallOrderedSampleInterpreters.end(); ++it )
   {
      (*it)->Interpret( &mDataChunk[0] );
   }

}
