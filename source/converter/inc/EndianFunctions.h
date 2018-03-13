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

#ifndef NAMESPACE_EndianFunctions
#define NAMESPACE_EndianFunctions

#include <stdint.h>

namespace EndianFunctions
{

   //
   // Some thoughts:
   // - I am afriad I don't have the variety of machines and sample data to test this piece of code,
   //   so use with caution, and feel free to inform me of bugs, I'll do my best
   //
   //
   template<typename T>
   T ChangeEndianness( const T in )
   {
      return in;
   }

	uint16_t ChangeEndianness( const uint16_t in );

	uint32_t ChangeEndianness( const uint32_t in );

	uint64_t ChangeEndianness( const uint64_t in );

	
}//end namespace EndianFunctions

#endif //NAMESPACE_EndianFunctions
