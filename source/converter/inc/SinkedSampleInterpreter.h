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

#ifndef CLASS_SinkedSampleInterpreter
#define CLASS_SinkedSampleInterpreter

#include "SampleInterpreter.h"
#include "SampleSink.h"

#include "EncoderFunctions.h"

template<typename chunk_t, typename sample_base_t>
class SinkedSampleInterpreter : public SampleInterpreter
{
protected:
   uint32_t    mChunkIndex;        //which elelment of the chunk array to access
	uint32_t    mResidualBitIndex;  //how many bits into the mChunkIndex^th element to the start of the sample
	SampleSink* mSampleSink;         //the associated sammple sink, where the interpreted samples will be put
	
   //ToDo: templated typedefs aren't allowed in C++, maybe c11 aliases? This looks clunky...
   // pointer to function which interprets the bits as samples, either I or Q
   sample_base_t (*mEncodingFunc)( const chunk_t*, uint32_t, uint32_t, uint32_t );
   // pointer to function which uses mEncodingFunc to cet either I or IQ  
   // or InQ, nIQ etc, and put them in the sample sink
   void (*mFormatFunc)( sample_base_t (* )( const chunk_t* ,  uint32_t,  uint32_t, uint32_t ), const chunk_t*, uint32_t, uint32_t, uint32_t, SampleSink* );

public:
   // assign the function pointers to implement bit interpretation (encodingFunc) and
   // sample ordering, I, IQ, QI, InQ, nIQ etc. (formatFunc). 
   // Essentially I want run-time polymorphism, but explicitly going through all of the
   // permutations of mConvFunc and mAddFunc would be too long. In contrast it looks like
   // function pointers allow a separation of Conv and Add. 
   SinkedSampleInterpreter( 
                        const uint32_t bitWidth, 
                        sample_base_t (* encodingFunc)( const chunk_t*,  uint32_t,  uint32_t,  uint32_t ),
                        void (*formatFunc)( sample_base_t (* )( const chunk_t* ,  uint32_t,  uint32_t,  uint32_t ), const chunk_t* pChunk, uint32_t, uint32_t, uint32_t, SampleSink* ),
                        SampleSink* sampleSink,
                        const uint16_t callOrder
                     );


public:	
   virtual ~SinkedSampleInterpreter();
   virtual void     SetChunkOffset(  const uint32_t chunkOffsetInBits );
   virtual void     Interpret( const void* vChunk ) const;

};

#include "SinkedSampleInterpreter.hpp"

#endif //SinkedSampleInterpreter


