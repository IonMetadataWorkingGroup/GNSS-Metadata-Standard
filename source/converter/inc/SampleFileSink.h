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

#ifndef CLASS_SampleFileSink
#define CLASS_SampleFileSink

#include <fstream>
#include <string>

#include "SampleSink.h"

template<typename sample_base_t>
class SampleFileSink : public SampleSinkT<sample_base_t>
{

protected:
   sample_base_t* mSampleBuffer;
   unsigned int   mBufferSize;
   unsigned int   mIndexOfNextSample;
   unsigned int   mRequestedNumberOfSamplesPerBuffer;

   std::string    mFileName;
   std::ofstream  mSampleFile;

   bool Open();
   inline void DoAddSample( sample_base_t x );
   inline void DoAddSample( sample_base_t x, sample_base_t y );
   
public:
   SampleFileSink(std::string fileName, unsigned int numSamplesPerBuffer = BASE_BUFFER_SIZE_IN_BYTES);
   virtual ~SampleFileSink(void);

   inline void Flush();
   void Close();
   
};

#include "SampleFileSink.hpp"

#endif // CLASS_SampleFileSink

