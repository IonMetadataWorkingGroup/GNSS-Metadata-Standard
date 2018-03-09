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


#include <stdint.h>
#include "EndianFunctions.h"


namespace EndianFunctions
{

   //
   // Some thoughts:
   // - I am afriad I don't have the variety of machines and sample data to test this piece of code,
   //   so use with caution, and feel free to inform me of bugs, I'll do my best
   //
   //
   uint8_t ChangeEndianness( const uint8_t in )
	{
		return in;
    }

	uint16_t ChangeEndianness( const uint16_t in )
	{
		return  ( in >> 8 ) |   //move byte 1 to 0
				  ( in << 8 );    //move byte 0 to 1
    }

	uint32_t ChangeEndianness( const uint32_t in )
	{
		return  (( in >> 24 ) & 0x000000ff ) |	// move byte 3 to byte 0
				  (( in >>  8 ) & 0x0000ff00 ) |	// move byte 1 to byte 2
				  (( in <<  8 ) & 0x00ff0000 ) |	// move byte 2 to byte 1
				  (( in << 24 ) & 0xff000000 );	// move byte 0 to byte 3;
    }

	uint64_t ChangeEndianness( const uint64_t in )
	{

		return  (( in >> 56 ) &  0x00000000000000ff) |  // move byte 7 to byte 0
				  (( in >> 40 ) &  0x000000000000ff00) |  // move byte 6 to byte 1
				  (( in >> 24 ) &  0x0000000000ff0000) |  // move byte 5 to byte 2
				  (( in >>  8 ) &  0x00000000ff000000) |  // move byte 4 to byte 3
				  (( in <<  8 ) &  0x000000ff00000000) |  // move byte 3 to byte 4
				  (( in << 24 ) &  0x0000ff0000000000) |  // move byte 2 to byte 5
				  (( in << 40 ) &  0x00ff000000000000) |  // move byte 1 to byte 6
				  (( in << 56 ) &  0xff00000000000000);   // move byte 0 to byte 7
    }
	
}//end namespace EndianFunctions
