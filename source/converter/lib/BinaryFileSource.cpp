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

#include "BinaryFileSource.h"
#include <algorithm> 

BinaryFileSource::BinaryFileSource():
mBinfile(NULL)
{
   
}

BinaryFileSource::BinaryFileSource(const std::string filename)
{
   Open(filename);
}

BinaryFileSource::~BinaryFileSource()
{
   Close();
}

bool BinaryFileSource::DoOpen(const std::string streamName)
{
   
   mBinfile = new std::ifstream;
   mBinfile->open( streamName, std::ios::binary );
   
   mIsOpen = mBinfile->is_open();
   
   if( mIsOpen )
   {
      mData.resize(BinaryFileSource_READ_SIZE);
      mStartBuffer = mData.end();
      mEndBuffer   = mStartBuffer;
   }
   
   return mIsOpen;
}

void BinaryFileSource::DoClose()
{
   if( mBinfile != NULL)
   {
      mBinfile->close();
      delete mBinfile;
      mBinfile = NULL;
   }

}


uint32_t BinaryFileSource::Get( void* pData, uint32_t requestedBytes )
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
}


bool BinaryFileSource::Load()
{
   if( !mIsOpen )
   {
      return false;
   }
   //read the data
   mStartBuffer = mData.begin();
   mBinfile->read( reinterpret_cast<char*>(&(*mStartBuffer)) , BinaryFileSource_READ_SIZE);
   mEndBuffer = mStartBuffer + static_cast<uint32_t>( mBinfile->gcount() );
   
   //make sure that we have actually loaded something (we may have reached eof)
   return !(mStartBuffer == mEndBuffer);
}







