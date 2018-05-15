/**
 * Author: James T. Curran
 *  
 * Copyright(c) 2018 Institute of Navigation
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

#ifndef CLASS_BinaryBuffer
#define CLASS_BinaryBuffer

#include <vector>
#include <string>
#include <stdint.h>

#include "BinarySink.h"

#define BASE_BUFFER_SIZE 1024 * 1024

class BinaryBuffer : public BinarySink
{

protected:
   std::vector<uint8_t> mBuffer;
   int32_t              mBufferSize;
   int32_t              mBufferPos;
      
   bool DoOpen(const std::string streamName);
   void DoClose();   

public:
   BinaryBuffer( std::string fileName );
   virtual ~BinaryBuffer(void);

   void     Flush();
   void     Clear();
   uint32_t Put( void* pData, uint32_t numBytes );
   uint32_t Get( void** pbuff, uint32_t numBytes = BASE_BUFFER_SIZE );

   
};


#endif // CLASS_BinaryBuffer

