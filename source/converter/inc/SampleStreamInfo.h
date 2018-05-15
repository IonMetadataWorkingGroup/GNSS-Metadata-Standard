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


#ifndef CLASS_SampleSourceInfo
#define CLASS_SampleSourceInfo

#include <GnssMetadata/Metadata.h>

class SampleStreamInfo
{
public:
   GnssMetadata::Frequency mCenterFrequency;
   GnssMetadata::Frequency mTranslatedFrequency;
   GnssMetadata::Frequency mSampleFrequency;
   GnssMetadata::Frequency mBaseFrequency;
   GnssMetadata::Duration  mDelayBias;
   
   std::string             mLaneID;
	
   size_t mQuantization;
   bool   mIsComplexSamples;

public:
   
   SampleStreamInfo() :
   mQuantization(0), mIsComplexSamples(false)
   {};
   
   virtual ~SampleStreamInfo(){};
  
   void Print() const
   {
      printf("LaneID:              %s\n", mLaneID.c_str());
      printf("CenterFrequency:     %s\n",mCenterFrequency.toString(  ).c_str());
      printf("TranslatedFrequency: %s\n",mTranslatedFrequency.toString( ).c_str());
      printf("DelayBias:           %s\n",mDelayBias.toString().c_str());
      printf("SampleFrequency:     %s, %s\n",mSampleFrequency.toString( ).c_str(), ( mIsComplexSamples ? "complex" : "real" ));
      printf("Quantization:        %d\n",static_cast<int>(mQuantization));
      //printf("BaseFrequency:       %s\n",mBaseFrequency.toString());      
   }
};

#endif // CLASS_SampleSourceInfo
