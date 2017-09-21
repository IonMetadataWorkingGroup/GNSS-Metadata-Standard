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

#ifndef CLASS_ChunkInterpreter
#define CLASS_ChunkInterpreter
#include <deque>

#include <GnssMetadata/Metadata.h>
#include "SampleInterpreterFactory.h"

//pur virtual haldle class
class Chunk
{
protected:
   Chunk( ){};
public:
   Chunk( const uint32_t countWords ){};
   virtual ~Chunk(){};

   virtual    void  AddSampleInterpreter( SampleInterpreter* splIntrp, const bool front = false ) = 0;
   virtual    void  SetSourceEndianness( const GnssMetadata::Chunk::WordEndian& srcEndianness) = 0;
   virtual    void  SetChunkPeriod( const double chunkPeriod ) = 0;
   virtual    void  Interpret( )            = 0;
   virtual    void* GetChunk()              = 0;
   virtual uint32_t BytesPerChunk() const   = 0;
   virtual double   ChunkPeriod() const   = 0;
};


template<typename chunk_t,typename sample_base_t>
class ChunkInterpreter : public Chunk
{
public:
   typedef chunk_t myChunkType_t;

public:
   SampleInterpreterFactory<chunk_t,sample_base_t> mSampleInterpFactory;

protected:	
   // this is an orderd set of SampleInterpreters, the placement in the deque indicates which bits of the chunk are interpreted
	std::deque<SampleInterpreter*> mSampleInterpreters;
   // this is an orderd set of SampleInterpreters, the placement in the list indicates which should be called first
   // -when multiple interpreters send data to the same sink, the order in which they are called matters.
   std::list<SampleInterpreter*>  mCallOrderedSampleInterpreters;
   std::vector<chunk_t>           mDataChunk;
   bool                           mSourceEndiannessIsDifferent;
   bool                           mRightWordShift;
   double                         mChunkPeriod;

protected:
   void ChangeCunkEndianness( );

public:	
   ChunkInterpreter( const uint32_t countWords, const bool rightWordShift = false );
	virtual         ~ChunkInterpreter();
	void            AddSampleInterpreter( SampleInterpreter* splIntrp, const bool front = false );
   void            SetSourceEndianness( const GnssMetadata::Chunk::WordEndian& srcEndianness );
   void            SetChunkPeriod( const double chunkPeriod );
   inline void     Interpret( );
   inline void*    GetChunk();
   inline uint32_t BytesPerChunk() const;
   inline double   ChunkPeriod() const;
};

#include "ChunkInterpreter.hpp"

#endif //CLASS_ChunkInterpreter
