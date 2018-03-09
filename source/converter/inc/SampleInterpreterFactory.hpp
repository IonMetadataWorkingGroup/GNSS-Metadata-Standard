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
 
#include "EncoderFunctions.h"
#include "FormatFunctions.h"
#include <GnssMetadata/Metadata.h>

template<typename chunk_t, typename sample_base_t>
SampleInterpreterFactory<chunk_t,sample_base_t>::SampleInterpreterFactory()
{
   
   // "introduce" the EncoderFunctions to the Factory
   mEncoderFunctionMap[ "SIGN" ] = (encFuncPtr_t)&SampleEncoderFunctions::Sign;

   mEncoderFunctionMap["OB"]  = (encFuncPtr_t)&SampleEncoderFunctions::OffsetBinary;
   mEncoderFunctionMap["SM"]  = (encFuncPtr_t)&SampleEncoderFunctions::SignMagnitude;
   mEncoderFunctionMap["TC"] = (encFuncPtr_t)&SampleEncoderFunctions::TwosCompliment;
   mEncoderFunctionMap["OG"] = (encFuncPtr_t)&SampleEncoderFunctions::OffsetGray;

   mEncoderFunctionMap["OBA"] = (encFuncPtr_t)&SampleEncoderFunctions::OffsetBinaryAdjusted;
   mEncoderFunctionMap["SMA"] = (encFuncPtr_t)&SampleEncoderFunctions::SignMagnitudeAdjusted;
   mEncoderFunctionMap["TCA"] = (encFuncPtr_t)&SampleEncoderFunctions::TwosComplimentAdjusted;
   mEncoderFunctionMap["OGA"] = (encFuncPtr_t)&SampleEncoderFunctions::OffsetGrayAdjusted;

   //specialized EncoderFunctions (native types)
   mEncoderFunctionMap["INT8"] = (encFuncPtr_t)&SampleEncoderFunctions::Int8;

   // "introduce" the FormatFunctions to the Factory
   mFormatFunctionMap[ GnssMetadata::IonStream::IF   ] = &SampleFormatFunctions::IF<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::IonStream::IFn  ] = &SampleFormatFunctions::IFn<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::IonStream::IQ   ] = &SampleFormatFunctions::IQ<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::IonStream::IQn  ] = &SampleFormatFunctions::IQn<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::IonStream::InQ  ] = &SampleFormatFunctions::InQ<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::IonStream::InQn ] = &SampleFormatFunctions::InQn<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::IonStream::QI   ] = &SampleFormatFunctions::IQ<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::IonStream::QIn  ] = &SampleFormatFunctions::QIn<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::IonStream::QnI  ] = &SampleFormatFunctions::QnI<chunk_t,sample_base_t>;
   mFormatFunctionMap[ GnssMetadata::IonStream::QnIn ] = &SampleFormatFunctions::QnIn<chunk_t,sample_base_t>;
   
   //specialized FormatFunctions (native types)
   mFormatFunctionMap[ GnssMetadata::IonStream::Int8IQ ] = &SampleFormatFunctions::Int8IQ<chunk_t,sample_base_t>;

}

template<typename chunk_t, typename sample_base_t>
SampleInterpreterFactory<chunk_t,sample_base_t>::~SampleInterpreterFactory()
{


}

template<typename chunk_t, typename sample_base_t>
bool SampleInterpreterFactory<chunk_t,sample_base_t>::Create(
                     SampleSink* sampleSink,
                     const GnssMetadata::IonStream::SampleFormat& fmt,
                     const std::string&  enc,
                     const uint8_t& qnt, 
                     SampleInterpreter* &smplIntrp,
                     const uint16_t callOrder
                     )
{
   
   //make sure that we can create the sample interpreter
   if( mEncoderFunctionMap.find( enc ) == mEncoderFunctionMap.end() )
   {
      printf("Error: no support for `%s' encoder.",enc.c_str());
      return false;
   }
   if( mFormatFunctionMap.find( fmt ) == mFormatFunctionMap.end() )
   {
      printf("Error: no support for format type (%d).",fmt);
      return false;
   }

   //it would be possible here to create specializations, which combine FormatFunctions and EncoderFunctions
   
   //try Int8 IF
   if( (fmt == GnssMetadata::IonStream::IF) && ( enc == "TC" ) && ( BitWidth( fmt, qnt ) == 8 ) )
   {
      //otherwise proceed with a generic SampleInterpreter
      smplIntrp = new SinkedSampleInterpreter<chunk_t,sample_base_t>(
                                                                     BitWidth( fmt, qnt ),
                                                                     mEncoderFunctionMap["INT8"],
                                                                     mFormatFunctionMap[ GnssMetadata::IonStream::IF ],
                                                                     sampleSink,
                                                                     callOrder
                                                                     );
      return true;
   }
   
   //try Int8 I,Q
   if( (fmt == GnssMetadata::IonStream::IQ) && ( enc == "TC" ) && ( BitWidth( fmt, qnt ) == 16 ) )
   {
      //otherwise proceed with a generic SampleInterpreter
      smplIntrp = new SinkedSampleInterpreter<chunk_t,sample_base_t>(
                                                                     BitWidth( fmt, qnt ),
                                                                     NULL,
                                                                     mFormatFunctionMap[ GnssMetadata::IonStream::Int8IQ ],
                                                                     sampleSink,
                                                                     callOrder
                                                                     );
      return true;
   }
   
   //otherwise proceed with a generic SampleInterpreter
   smplIntrp = new SinkedSampleInterpreter<chunk_t,sample_base_t>( 
                        BitWidth( fmt, qnt ), 
                        mEncoderFunctionMap[enc], 
                        mFormatFunctionMap[fmt],
                        sampleSink,
                        callOrder
                     );

   return true;

}

template<typename chunk_t, typename sample_base_t>
uint32_t SampleInterpreterFactory<chunk_t,sample_base_t>::BitWidth( const GnssMetadata::IonStream::SampleFormat& fmt, const size_t& qnt )
{

   //move to static function of a factory later?
   switch( fmt )
   {
      case GnssMetadata::IonStream::IF  :
      case GnssMetadata::IonStream::IFn :
         return static_cast<uint32_t>(qnt);
      default:
         return 2 * static_cast<uint32_t>(qnt);
   }

}

