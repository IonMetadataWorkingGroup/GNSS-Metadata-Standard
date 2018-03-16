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

#define BinaryFileSource_READ_SIZE 16*1024*1024
#undef min

class BinarySource
{
protected:
   bool mIsOpen;
   
   std::vector<uint8_t>           mData;
   std::vector<uint8_t>::iterator mStartBuffer;
   std::vector<uint8_t>::iterator mEndBuffer;
   uint64_t                       mSourcePos;

   BinarySource():
      mIsOpen(false),
      mSourcePos(0)
      {};

   virtual bool Load()    = 0;
   virtual bool DoOpen(const std::string streamName)  = 0;
   virtual void DoClose() = 0;

public:
   virtual ~BinarySource(){};
   
   bool IsOpen() const
   {
      return mIsOpen;
   };
   
   bool Open(const std::string streamName)
   {

      //call the derived class Open()
      mIsOpen = DoOpen(streamName);
      
      if( mIsOpen )
      {
         mData.resize(BinaryFileSource_READ_SIZE);
         mStartBuffer = mData.end();
         mEndBuffer   = mStartBuffer;
      }
      
      return mIsOpen;
   };
   
   void Close()
   {
      //call the derived class Close()
      DoClose();
      mIsOpen = false;
   };
   
   
   uint64_t SourcePos()
   {
      return mSourcePos;
   };

   uint32_t Skip(uint32_t bytesToSkip)
   {
      return Get(NULL,bytesToSkip);
   }
   
   uint32_t Get( void* pData, uint32_t requestedBytes )
   {
      if( !mIsOpen )
      {
         return 0;
      }
      
      uint32_t deliveredBytes = 0;
      while( deliveredBytes < requestedBytes )
      {
         //make sure we have data
         if( mStartBuffer == mEndBuffer )
         {
            if( !Load() )
            {
               break;
            }
         }
         //now copy out the bytes
         uint32_t copyBytes = std::min( uint32_t(requestedBytes-deliveredBytes), uint32_t(mEndBuffer-mStartBuffer) );
         
         if( pData != NULL )
         {
            std::memcpy( static_cast<uint8_t*>(pData) + deliveredBytes, &(*mStartBuffer), copyBytes);
         }
         mSourcePos     += copyBytes;
         mStartBuffer   += copyBytes;
         deliveredBytes += copyBytes;
      }
      
      return deliveredBytes;
   };
   
   
};

#endif //CLASS_BinarySource




