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

#ifndef NAMESPACE_FormatFunctions
#define NAMESPACE_FormatFunctions


namespace SampleFormatFunctions
{

   //
   // Some thoughts:
   // - I have included both I and IQ extraction functinos, rather than simply re-use the I-only case
   //   the reason being that it might be efficient in the future to allow the direct LUT of an IQ pair
   //   when we have low-resolution quantization. This this interface should easily support this.
   //
   //

   template<typename chunk_t> void ComputeOffsets( uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth,
                                                   uint8_t& shiftFirst, uint8_t& shiftSecond, uint32_t& chunkIndexFirst, uint32_t& chunkIndexSecond
                                                   )
   {
      //the first part should be straightforward
      shiftFirst = static_cast<uint8_t>( 8 * sizeof(chunk_t) - residualBitIndex - bitWidth/2 );
      chunkIndexFirst = chunkIndex;
   
      //the second part might be in the next element of pChunk
      if( (8*sizeof(chunk_t)) >= (residualBitIndex + bitWidth) )
      {   
         shiftSecond      = static_cast<uint8_t>( 8 * sizeof(chunk_t) - (residualBitIndex + bitWidth) );
         chunkIndexSecond = chunkIndex;
      }
      else
      {
         shiftSecond      = static_cast<uint8_t>( 8*sizeof(chunk_t) - (residualBitIndex + bitWidth - 8*sizeof(chunk_t)) );
         chunkIndexSecond = chunkIndex + 1;
      }

   }


   //////////////////////////////////////////////////
   // 
   // Extraction of real data is straightforward, as  
   //
   template<typename chunk_t, typename sample_base_t> void IF( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
	   //how many bits into the chunk element is the I sample
      uint8_t shift   = static_cast<uint8_t>( 8 * sizeof(chunk_t) - residualBitIndex - bitWidth );

      sample_base_t IF =  (*encoderFunc)( pChunk, chunkIndex, shift, bitWidth );

      sampleSink->AddSample( IF );
	
   }

   template<typename chunk_t, typename sample_base_t> void IFn( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
	   //how many bits into the chunk element is the I sample
      uint8_t shift   = static_cast<uint8_t>( 8 * sizeof(chunk_t) - residualBitIndex - bitWidth );

      sample_base_t IF = -(*encoderFunc)( pChunk, chunkIndex, shift, bitWidth );

      sampleSink->AddSample( IF );
	
   }


   template<typename chunk_t, typename sample_base_t> void IQ( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
      uint8_t  shiftFirst, shiftSecond;
      uint32_t chunkIndexFirst, chunkIndexSecond;
      ComputeOffsets<chunk_t>( chunkIndex, residualBitIndex, bitWidth, shiftFirst, shiftSecond, chunkIndexFirst, chunkIndexSecond );

      sample_base_t I = (*encoderFunc)( pChunk, chunkIndexFirst, shiftFirst, bitWidth/2 );
      sample_base_t Q = (*encoderFunc)( pChunk, chunkIndexSecond, shiftSecond, bitWidth/2 );

      sampleSink->AddSample( I, Q );
      //sampleSink->AddSample( Q );
	
   }

   template<typename chunk_t, typename sample_base_t> void IQn( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
      uint8_t  shiftFirst, shiftSecond;
      uint32_t chunkIndexFirst, chunkIndexSecond;
      ComputeOffsets<chunk_t>( chunkIndex, residualBitIndex, bitWidth, shiftFirst, shiftSecond, chunkIndexFirst, chunkIndexSecond );

      sample_base_t I =  (*encoderFunc)( pChunk, chunkIndexFirst, shiftFirst, bitWidth/2 );
      sample_base_t Q = -(*encoderFunc)( pChunk, chunkIndexSecond, shiftSecond, bitWidth/2 );

      sampleSink->AddSample( I, Q );
      //sampleSink->AddSample( Q );
	
   }

   template<typename chunk_t, typename sample_base_t> void InQ( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
      uint8_t  shiftFirst, shiftSecond;
      uint32_t chunkIndexFirst, chunkIndexSecond;
      ComputeOffsets<chunk_t>( chunkIndex, residualBitIndex, bitWidth, shiftFirst, shiftSecond, chunkIndexFirst, chunkIndexSecond );

      sample_base_t I = -(*encoderFunc)( pChunk, chunkIndexFirst, shiftFirst, bitWidth/2 );
      sample_base_t Q =  (*encoderFunc)( pChunk, chunkIndexSecond, shiftSecond, bitWidth/2 );

      sampleSink->AddSample( I, Q );
      //sampleSink->AddSample( Q );
	
   }

   template<typename chunk_t, typename sample_base_t> void InQn( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
      uint8_t  shiftFirst, shiftSecond;
      uint32_t chunkIndexFirst, chunkIndexSecond;
      ComputeOffsets<chunk_t>( chunkIndex, residualBitIndex, bitWidth, shiftFirst, shiftSecond, chunkIndexFirst, chunkIndexSecond );

      sample_base_t I = -(*encoderFunc)( pChunk, chunkIndexFirst, shiftFirst, bitWidth/2 );
      sample_base_t Q = -(*encoderFunc)( pChunk, chunkIndexSecond, shiftSecond, bitWidth/2 );

      sampleSink->AddSample( I, Q );
      //sampleSink->AddSample( Q );
	
   }

   template<typename chunk_t, typename sample_base_t> void QI( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
      uint8_t  shiftFirst, shiftSecond;
      uint32_t chunkIndexFirst, chunkIndexSecond;
      ComputeOffsets<chunk_t>( chunkIndex, residualBitIndex, bitWidth, shiftFirst, shiftSecond, chunkIndexFirst, chunkIndexSecond );

      sample_base_t I = (*encoderFunc)( pChunk, chunkIndexSecond, shiftSecond, bitWidth/2 );
      sample_base_t Q = (*encoderFunc)( pChunk, chunkIndexFirst, shiftFirst, bitWidth/2 );

      sampleSink->AddSample( I, Q );
      //sampleSink->AddSample( Q );
	
   }

   template<typename chunk_t, typename sample_base_t> void QIn( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
      uint8_t  shiftFirst, shiftSecond;
      uint32_t chunkIndexFirst, chunkIndexSecond;
      ComputeOffsets<chunk_t>( chunkIndex, residualBitIndex, bitWidth, shiftFirst, shiftSecond, chunkIndexFirst, chunkIndexSecond );

      sample_base_t I = -(*encoderFunc)( pChunk, chunkIndexSecond, shiftSecond, bitWidth/2 );
      sample_base_t Q = (*encoderFunc)( pChunk, chunkIndexFirst, shiftFirst, bitWidth/2 );

      sampleSink->AddSample( I, Q );
      //sampleSink->AddSample( Q );
	
   }

   template<typename chunk_t, typename sample_base_t> void QnI( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
      uint8_t  shiftFirst, shiftSecond;
      uint32_t chunkIndexFirst, chunkIndexSecond;
      ComputeOffsets<chunk_t>( chunkIndex, residualBitIndex, bitWidth, shiftFirst, shiftSecond, chunkIndexFirst, chunkIndexSecond );

      sample_base_t I = (*encoderFunc)( pChunk, chunkIndexSecond, shiftSecond, bitWidth/2 );
      sample_base_t Q = -(*encoderFunc)( pChunk, chunkIndexFirst, shiftFirst, bitWidth/2 );

      sampleSink->AddSample( I, Q );
      //sampleSink->AddSample( Q );
	
   }

   template<typename chunk_t, typename sample_base_t> void QnIn( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
      uint8_t  shiftFirst, shiftSecond;
      uint32_t chunkIndexFirst, chunkIndexSecond;
      ComputeOffsets<chunk_t>( chunkIndex, residualBitIndex, bitWidth, shiftFirst, shiftSecond, chunkIndexFirst, chunkIndexSecond );
      
      sample_base_t I = -(*encoderFunc)( pChunk, chunkIndexSecond, shiftSecond, bitWidth/2 );
      sample_base_t Q = -(*encoderFunc)( pChunk, chunkIndexFirst, shiftFirst, bitWidth/2 );
      
      sampleSink->AddSample( I, Q );
      
   }
   

   // Specialized FormatFunctions (including native type encoder functions
   template<typename chunk_t, typename sample_base_t> void Int8IQ( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
      uint8_t  shiftFirst, shiftSecond;
      uint32_t chunkIndexFirst, chunkIndexSecond;
      ComputeOffsets<chunk_t>( chunkIndex, residualBitIndex, bitWidth, shiftFirst, shiftSecond, chunkIndexFirst, chunkIndexSecond );
      
      sample_base_t I =  static_cast<int8_t>( (pChunk[chunkIndexFirst]  >> shiftFirst)  & 0xff );
      sample_base_t Q =  static_cast<int8_t>( (pChunk[chunkIndexSecond] >> shiftSecond) & 0xff );
      
      sampleSink->AddSample( I, Q );
      
   }
   
   template<typename chunk_t, typename sample_base_t> void Int16IQ( sample_base_t (*encoderFunc)( const chunk_t* , uint32_t, uint32_t, uint32_t ), const chunk_t* pChunk, uint32_t chunkIndex, uint32_t residualBitIndex, uint32_t bitWidth, SampleSink* sampleSink )
   {
      uint8_t  shiftFirst, shiftSecond;
      uint32_t chunkIndexFirst, chunkIndexSecond;
      ComputeOffsets<chunk_t>( chunkIndex, residualBitIndex, bitWidth, shiftFirst, shiftSecond, chunkIndexFirst, chunkIndexSecond );
      
      //note that sample_base_t should always be int16_t when this is called.
      sample_base_t I =  static_cast<sample_base_t>( static_cast<int16_t>( (pChunk[chunkIndexFirst]  >> shiftFirst)  & 0xffff ) );
      sample_base_t Q =  static_cast<sample_base_t>( static_cast<int16_t>( (pChunk[chunkIndexSecond] >> shiftSecond) & 0xffff ) );
      
      sampleSink->AddSample( I, Q );
      
   }
   

}//end namespace SampleFormatFunctions

#endif //NAMESPACE_FormatFunctions
