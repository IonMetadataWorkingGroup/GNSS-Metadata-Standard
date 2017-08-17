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

#ifndef NAMESPACE_EncoderFunctions
#define NAMESPACE_EncoderFunctions

#include <limits>

namespace SampleEncoderFunctions
{
   //
   // There will be a choice to be made here between `atomic' conversions, where 
   // the data for one sample is held entirely within one element of the chunk_t
   // type, as opposed to `non-atomic' conversions, where the bits may be split
   // between adjacent elements of the chunk_t vector, which would require some
   // re-packing of the bits.
   //
   // The atomic will be much faster and more simple, but the standard supports
   // both kinds, so it might make sense to implement both kinds and to allow
   // the sample-imterpreter factory to choose the appropriate one, based on its
   // knowledge of the packing of the bits. If it can be guaranteed that the data
   // will be atomic, then the faster option can be taken.
   //
   // Thoughts?
   //
   //
   // Second comment: it is the callers responsibility to ensure that a cast to
   // sample_base_t is provided (default types, should be) will work, and  that
   // they do not overflow etc.
   //
	
   template<typename chunk_t, typename sample_base_t> 
   sample_base_t Sign( const chunk_t* pChunk, uint32_t chunkIndex, uint32_t shift, uint32_t quantization )
   {
      return ( (pChunk[chunkIndex] >> shift ) & 0x1 ? -1 : 1 );
   };

   template<typename chunk_t, typename sample_base_t> 
   sample_base_t TwosCompliment( const chunk_t* pChunk, uint32_t chunkIndex, uint32_t shift, uint32_t quantization )
   {

      //set ot all ones (assume chunk_t is unsigned), then rightshift
      chunk_t mask = std::numeric_limits<chunk_t>::max() >> ( 8*sizeof(chunk_t) - (quantization) ); 

      //extract the sample bits
      chunk_t bits = ( pChunk[chunkIndex] >> shift ) & mask;
      
      //retrieve the sign of the data
      bool sign =  ( pChunk[chunkIndex] >> (shift+quantization-1) ) & 0x1 ;

      //make a mask for the magnitude data (ones for the upper bits)
      chunk_t signExtension = std::numeric_limits<chunk_t>::max() << quantization;

      //either return the bits or add the sign extension
      return static_cast<sample_base_t>(  ( sign ?  bits | signExtension : bits ) );
   };


   template<typename chunk_t, typename sample_base_t>
   sample_base_t TwosComplimentAdjusted(const chunk_t* pChunk, uint32_t chunkIndex, uint32_t shift, uint32_t quantization)
   {

	   //set ot all ones (assume chunk_t is unsigned), then rightshift
	   chunk_t mask = std::numeric_limits<chunk_t>::max() >> (8 * sizeof(chunk_t) - (quantization));

	   //extract the sample bits, and multiply by 2
	   chunk_t bits = ((pChunk[chunkIndex] >> shift) & mask)<<1;

	   //retrieve the sign of the data
	   bool sign = (pChunk[chunkIndex] >> (shift + quantization - 1)) & 0x1;

	   //make a mask for the magnitude data (ones for the upper bits, noting the << 1 above)
	   sample_base_t signExtension = std::numeric_limits<sample_base_t>::max() << (quantization + 1);

	   //either return the bits or add the sign extension, offset by +1
	   return static_cast<sample_base_t>((sign ? bits | signExtension : bits) + 1 );
   };
   

   template<typename chunk_t, typename sample_base_t>
   sample_base_t SignMagnitude(const chunk_t* pChunk, uint32_t chunkIndex, uint32_t shift, uint32_t quantization)
   {

	   //set to all ones (assume chunk_t is unsigned), then rightshift
	   chunk_t mask = std::numeric_limits<chunk_t>::max() >> (8 * sizeof(chunk_t) - (quantization - 1));

	   //extract the sample bits
	   sample_base_t mag = static_cast<sample_base_t>((pChunk[chunkIndex] >> shift) & mask);

	   //retrieve the sign of the data
	   bool sign = (pChunk[chunkIndex] >> (shift + quantization - 1)) & 0x1;

	   //either return the bits or add the sign extension
	   sample_base_t ans = (sign ? -mag : mag);
	   return ans;

   };

   template<typename chunk_t, typename sample_base_t>
   sample_base_t SignMagnitudeAdjusted(const chunk_t* pChunk, uint32_t chunkIndex, uint32_t shift, uint32_t quantization)
   {

	   //set to all ones (assume chunk_t is unsigned), then rightshift
	   chunk_t mask = std::numeric_limits<chunk_t>::max() >> (8 * sizeof(chunk_t) - (quantization - 1));

	   //extract the sample bits
	   sample_base_t mag = static_cast<sample_base_t>(
		  (  ((pChunk[chunkIndex] >> shift) & mask) << 1 ) | 0x1
		   );

	   //retrieve the sign of the data
	   bool sign = (pChunk[chunkIndex] >> (shift + quantization - 1)) & 0x1;

	   //either return the bits or add the sign extension
	   sample_base_t ans = (sign ? -mag : mag);
	   return ans;
   };

   template<typename chunk_t, typename sample_base_t>
   sample_base_t OffsetBinary(const chunk_t* pChunk, uint32_t chunkIndex, uint32_t shift, uint32_t quantization)
   {
	   //make a mask for the magnitude data
	   chunk_t mask = std::numeric_limits<chunk_t>::max() >> (8 * sizeof(chunk_t) - (quantization));

	   //simply extract the bits
	   chunk_t bits = (pChunk[chunkIndex] >> shift) & mask;

	   chunk_t offset = 0x1 << (quantization - 1);

	   return static_cast<sample_base_t>(bits) - static_cast<sample_base_t>(offset);
   };

   template<typename chunk_t, typename sample_base_t>
   sample_base_t OffsetBinaryAdjusted(const chunk_t* pChunk, uint32_t chunkIndex, uint32_t shift, uint32_t quantization)
   {
	   //make a mask for the magnitude data
	   chunk_t mask = std::numeric_limits<chunk_t>::max() >> (8 * sizeof(chunk_t) - (quantization));

	   //simply extract the bits, then multiply by 2
	   chunk_t bits = ((pChunk[chunkIndex] >> shift) & mask)<<1;

	   chunk_t offset = (0x1 << quantization) - 1;

	   return static_cast<sample_base_t>(bits) - static_cast<sample_base_t>(offset);
   };


   template<typename chunk_t, typename sample_base_t>
   sample_base_t OffsetGray(const chunk_t* pChunk, uint32_t chunkIndex, uint32_t shift, uint32_t quantization)
   {
	   //make a mask for the magnitude data
	   chunk_t mask = std::numeric_limits<chunk_t>::max() >> (8 * sizeof(chunk_t) - (quantization));

	   //simply extract the bits
	   chunk_t gray = (pChunk[chunkIndex] >> shift) & mask;

	   for (chunk_t b = 1U << quantization; b > 1; b >>= 1)
	   {
		   if (gray & b)
			   gray ^= (b >> 1);
	   }

	   chunk_t offset = 0x1 << (quantization - 1);

	   return static_cast<sample_base_t>(gray) - static_cast<sample_base_t>(offset);
   };

   template<typename chunk_t, typename sample_base_t>
   sample_base_t OffsetGrayAdjusted(const chunk_t* pChunk, uint32_t chunkIndex, uint32_t shift, uint32_t quantization)
   {
	   //make a mask for the magnitude data
	   chunk_t mask = std::numeric_limits<chunk_t>::max() >> (8 * sizeof(chunk_t) - (quantization));

	   //simply extract the bits
	   chunk_t gray = (pChunk[chunkIndex] >> shift) & mask;

	   for (chunk_t b = 1U << quantization; b > 1; b >>= 1)
	   {
		   if (gray & b)
			   gray ^= (b >> 1);
	   }

	   chunk_t offset = (0x1 << quantization) - 1;

	   return static_cast<sample_base_t>(gray << 1) - static_cast<sample_base_t>(offset);
   };


   template<typename chunk_t, typename sample_base_t>
   sample_base_t IntegerEight(const chunk_t* pChunk, uint32_t chunkIndex, uint32_t shift, uint32_t quantization)
   {

	   int8_t sample =  static_cast<int8_t>( (pChunk[chunkIndex] >> shift) & 0xff );

	   return static_cast<sample_base_t>(sample);
   };


};// end namespace SampleEncoderFunctions


#endif //NAMESPACE_EncoderFunctions
