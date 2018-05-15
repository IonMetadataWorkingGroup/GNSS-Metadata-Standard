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
#include <math.h>
#include "BinaryBuffer.h"

BinaryBuffer::BinaryBuffer( std::string fileName ) :
mBufferSize(0),
mBufferPos(0)
{
   DoOpen( fileName );
}


BinaryBuffer::~BinaryBuffer(void)
{
   //flush the stream
   Clear();
   
   //close the stream, if it is not done so already.
   DoClose();

}

bool BinaryBuffer::DoOpen( const std::string fileName )
{
   
   //default to true, doesn't make much sense here, but would be valid if malloc or new[] was used
   this->mIsOpen = true;

   //now try to ensure that there is space in the buffer
   mBuffer.resize(BASE_BUFFER_SIZE);
   mBufferSize = static_cast<int32_t>( mBuffer.size() );
   mBufferPos  = 0;
   
   return this->mIsOpen;
}

void BinaryBuffer::DoClose()
{
   
   this->mIsOpen = false;

   Clear();

}

void BinaryBuffer::Flush()
{
   Clear();
}

void BinaryBuffer::Clear()
{

   if( !this->mIsOpen )
      return;

   mBufferPos = 0;

}

uint32_t BinaryBuffer::Put( void* pData, uint32_t numBytes )
{
	//check that there is enough space
	uint32_t remainingSpace = mBuffer.size() - mBufferPos;
	if( remainingSpace < numBytes )
	{
		uint32_t newSize = static_cast<uint32_t>( BASE_BUFFER_SIZE * ceil( (mBufferPos + numBytes) / static_cast<float>(BASE_BUFFER_SIZE) ) );
		mBuffer.resize( newSize );
	}
	
	//now copy in the data
	memcpy(&mBuffer[mBufferPos],pData,numBytes);
	mBufferPos += numBytes;

   return numBytes;
	
}

uint32_t BinaryBuffer::Get( void** pbuff, uint32_t numBytes )
{
   //point to the vector memory
   (*pbuff) = reinterpret_cast<void*>(&mBuffer[0]);

   //indicate how many samples are there
   return static_cast<uint32_t>(mBufferPos);
}





