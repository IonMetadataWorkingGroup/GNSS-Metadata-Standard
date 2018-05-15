/**
 * Author: James T. Curran : jamestcurran@ieee.org
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

#ifndef CLASS_BinarySource
#define CLASS_BinarySource

#include <vector>
#include <string>
#include <cstring>
#include <stdint.h>

#define BinaryFileSource_READ_SIZE 16*1024*1024
#undef min

class BinarySource
{
protected:
   bool mIsOpen;
   uint64_t                       mSourcePos;

   BinarySource();
   virtual bool Load()    = 0;
   virtual bool DoOpen(const std::string streamName)  = 0;
   virtual void DoClose() = 0;

public:
   virtual ~BinarySource();
   
   bool IsOpen() const;
   bool Open(const std::string streamName);
   void Close();
   
   uint32_t Skip(uint32_t bytesToSkip);
   virtual uint32_t Get( void* pData, uint32_t requestedBytes ) = 0;
   
   uint64_t SourcePos();
   
};

#endif //CLASS_BinarySource




