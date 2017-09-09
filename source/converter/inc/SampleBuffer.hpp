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
mBufferSize(0),
mBufferPos(0)
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

   //now try to ensure that there is space in the buffer
   mSampleBuffer.resize(BASE_BUFFER_SIZE);
   mBufferSize = mSampleBuffer.size();
   mBufferPos  = -1;
   
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

   mBufferPos = -1;

};

template<typename sample_base_t>
void SampleBuffer<sample_base_t>::DoAddSample( sample_base_t x )
{
   
   if( !this->mIsOpen )
      return;
   
   //advance the pointer
   mBufferPos++;
   
   //is there still space?
   if( mBufferPos >= mSampleBuffer.size() )
   {
      mSampleBuffer.resize( mSampleBuffer.size() + BASE_BUFFER_SIZE_IN_BYTES );
      mBufferSize = mSampleBuffer.size();
      
   }
   
   mSampleBuffer[mBufferPos] = x;
   
};

template<typename sample_base_t>
void SampleBuffer<sample_base_t>::DoAddSample( sample_base_t x, sample_base_t y )
{
   
   if( !this->mIsOpen )
      return;
   
   //advance the pointer
   mBufferPos += 2;
   
   //is there still space?
   if( mBufferPos >= mBufferSize )
   {
      mSampleBuffer.resize( mBufferSize + BASE_BUFFER_SIZE_IN_BYTES );
      mBufferSize = mSampleBuffer.size();
   }
   
   mSampleBuffer[mBufferPos-1] = x;
   mSampleBuffer[mBufferPos]   = y;
   
};


template<typename sample_base_t>
uint32_t SampleBuffer<sample_base_t>:: DoGetSamples( const void** pbuff ) const
{
   //point to the vector memory
   *pbuff = &mSampleBuffer[0];

   //indicate how many samples are there
   return static_cast<uint32_t>(mBufferPos+1);
};





