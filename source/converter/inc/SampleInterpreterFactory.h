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

#ifndef CLASS_SampleInterpreterFactory
#define CLASS_SampleInterpreterFactory

#include <stdint.h>
#include <string>
#include <map>
#include "SinkedSampleInterpreter.h"
#include <GnssMetadata/Metadata.h>



template<typename chunk_t, typename sample_base_t>
class SampleInterpreterFactory
{

protected:

   //make a typedef for the encoder function pointers (too many template args for compiler)
   typedef sample_base_t (* encFuncPtr_t)( const chunk_t*, uint32_t, uint32_t, uint32_t );
   //create a map of the encoder functions:
   std::map< const std::string, encFuncPtr_t> mEncoderFunctionMap;
   
   //make a typedef for the format function pointers (too many template args for compiler)
   typedef void (* fmtFuncPtr_t)( sample_base_t (* )( const chunk_t* , uint32_t, uint32_t, uint32_t ) , const chunk_t*, uint32_t, uint32_t, uint32_t, SampleSink*);
   //create a map of the format functions
   std::map< const GnssMetadata::IonStream::SampleFormat, fmtFuncPtr_t > mFormatFunctionMap;

public:
   SampleInterpreterFactory();
	~SampleInterpreterFactory();

   static uint32_t BitWidth( const GnssMetadata::IonStream::SampleFormat& fmt, const size_t& qnt );
   
   bool Create(
               SampleSink* sampleSink,
               const GnssMetadata::IonStream::SampleFormat& fmt,
               const std::string&  enc,
               const uint8_t& qnt, 
               SampleInterpreter* &smplIntrp,
               const uint16_t callOrder
               );
	
};

#include "SampleInterpreterFactory.hpp"

#endif //CLASS_SampleInterpreterFactory