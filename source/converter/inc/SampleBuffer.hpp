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

#include "SampleBuffer.h"

template<typename sample_base_t>
SampleBuffer<sample_base_t>::SampleBuffer( std::string fileName ) :
mMaxBufferSize( BASE_BUFFER_SIZE_IN_BYTES )
{
   Open( );
}


template<typename sample_base_t>
SampleBuffer<sample_base_t>::~SampleBuffer(void)
{
   //flush the stream
   Flush();
   
   //close the stream, if it is not done so already.
   Close();

};

template<typename sample_base_t>
bool SampleBuffer<sample_base_t>::Open( )
{
   
   //default to true, doesn't make much sense here, but would be valid if malloc or new[] was used
   this->mIsOpen = true;


   //choose buffer size, making sure its size in bytes is an integer multiple of BASE_BUFFER_SIZE_IN_BYTES
   unsigned int numBytesPerBuffer = mMaxBufferSize; 
   numBytesPerBuffer = numBytesPerBuffer - numBytesPerBuffer % BASE_BUFFER_SIZE_IN_BYTES;
   mMaxBufferSize    = ( numBytesPerBuffer < BASE_BUFFER_SIZE_IN_BYTES ? BASE_BUFFER_SIZE_IN_BYTES : numBytesPerBuffer );

   //now try to ensure that there is space in the buffer
   mSampleBuffer.reserve(mMaxBufferSize);
  
   return this->mIsOpen;
};


template<typename sample_base_t>
void SampleBuffer<sample_base_t>::Close()
{
   
   this->mIsOpen = false;

   Flush();

};

template<typename sample_base_t>
void SampleBuffer<sample_base_t>::Flush()
{

   if( !this->mIsOpen )
      return;

   mSampleBuffer.clear();
   mSampleBuffer.resize(0);
   mSampleBuffer.reserve(mMaxBufferSize);

};

template<typename sample_base_t>
void SampleBuffer<sample_base_t>::DoAddSample( sample_base_t x )
{
   
   if( !this->mIsOpen )
      return;
   
   mSampleBuffer.push_back( x );
   
};

template<typename sample_base_t>
void SampleBuffer<sample_base_t>::DoAddSample( sample_base_t x, sample_base_t Y )
{
   
   if( !this->mIsOpen )
      return;
   
   mSampleBuffer.push_back( x );
   mSampleBuffer.push_back( Y );
   
};


template<typename sample_base_t>
uint32_t SampleBuffer<sample_base_t>:: DoGetSamples( const void** pbuff ) const
{
   //point to the vector memory
   *pbuff = &mSampleBuffer[0];

   //indicate how many samples are there
   return static_cast<uint32_t>(mSampleBuffer.size());
};





