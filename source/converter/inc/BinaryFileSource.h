/**
 * Author: James T. Curran
 *
 * Copyright(c) 2016 Institute of Navigation
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

#ifndef CLASS_BinaryFileSource
#define CLASS_BinaryFileSource

#include <vector>
#include <fstream>
#include <string>
#include <cstring>

#define BinaryFileSource_READ_SIZE 16*1024*1024

#undef min

class BinaryFileSource
{
   
protected:
   
   bool mIsOpen;
   std::ifstream*                 mBinfile;
   std::vector<uint8_t>           mData;
   std::vector<uint8_t>::iterator mStartBuffer;
   std::vector<uint8_t>::iterator mEndBuffer;
   uint64_t                       mFilePos;
   
public:
   BinaryFileSource():
   mIsOpen(false), mBinfile(NULL), mFilePos(0)
   {};
   
   BinaryFileSource(const std::string filename)
   {
      Open(filename);
   };
   
   ~BinaryFileSource()
   {
      Close();
   }
   
   bool Open(const std::string filename)
   {
      
      mBinfile = new std::ifstream;
      mBinfile->open( filename, std::ios::binary );
      
      mIsOpen = mBinfile->is_open();
      
      if( mIsOpen )
      {
         mData.resize(BinaryFileSource_READ_SIZE);
         mStartBuffer = mData.end();
         mEndBuffer   = mStartBuffer;
      }
      
      return mIsOpen;
   };
   
   
   uint64_t FilePos()
   {
      return mFilePos;
   }
   
   size_t Skip(size_t bytesToSkip)
   {
      return Get(NULL,bytesToSkip);
   }
   
   void Close()
   {
      if( mBinfile != NULL)
      {
         mBinfile->close();
         delete mBinfile;
         mBinfile = NULL;
      }
      mIsOpen = false;
   };
   
   bool IsOpen() const
   {
      return mIsOpen;
   };
   
   bool Load()
   {
      if( !mIsOpen )
      {
         return false;
      }
      
      //read the data
      mStartBuffer = mData.begin();
      mBinfile->read( reinterpret_cast<char*>(&(*mStartBuffer)) , BinaryFileSource_READ_SIZE);
      mEndBuffer = mStartBuffer + mBinfile->gcount();
      
      //make sure that we have actually loaded something (we may have reached eof)
      return !(mStartBuffer == mEndBuffer);
   }
   
   size_t Get( void* pData, size_t requestedBytes )
   {
      if( !mIsOpen )
      {
         return 0;
      }
      
      size_t deliveredBytes = 0;
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
         size_t copyBytes = std::min( size_t(requestedBytes-deliveredBytes), size_t(mEndBuffer-mStartBuffer) );
         
         if( pData != NULL )
         {
            std::memcpy( static_cast<uint8_t*>(pData) + deliveredBytes, &(*mStartBuffer), copyBytes);
         }
         mFilePos       += copyBytes;
         mStartBuffer   += copyBytes;
         deliveredBytes += copyBytes;
      }
      
      return deliveredBytes;
   };
   
};
#endif //CLASS_BinaryFileSource
