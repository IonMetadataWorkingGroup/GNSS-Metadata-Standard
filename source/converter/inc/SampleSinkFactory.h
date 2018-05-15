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

#ifndef CLASS_SampleSinkFactory
#define CLASS_SampleSinkFactory

#include <map>
#include <string>
#include "SampleSink.h"
#include "BinarySink.h"
#include "SampleStreamInfo.h"

typedef std::map< std::string, std::pair<SampleSink*,SampleStreamInfo*> > sampleSinkInfo_map_t;

class BaseSampleSinkFactory
{
protected:
   std::map<std::string,std::pair<SampleSink*,SampleStreamInfo*>> mSampleSinks;
   std::map<std::string,BinarySink*> mHeadFootSinks;
   
public:
   BaseSampleSinkFactory(){};
   virtual ~BaseSampleSinkFactory(){};
   
   virtual SampleSink* GetSampleSink(const std::string sinkName) = 0;
   virtual SampleStreamInfo* GetSampleStreamInfo(const std::string sinkName) = 0;

   virtual BinarySink* GetHeadFootSink(const std::string sinkName) = 0;
   
   bool HasSampleSink(const std::string sinkName)
   {
      //if we don't aleady have a SampleSink for this stream, then create one
      if( mSampleSinks.find( sinkName ) == mSampleSinks.end() )
      {
         return false;
      }
      return true;
   }
   
   
   sampleSinkInfo_map_t GetSampleSinkInfoMap()
   {
      sampleSinkInfo_map_t sinkMap;
      
      for(std::map<std::string,std::pair<SampleSink*,SampleStreamInfo*>>::const_iterator mit = mSampleSinks.begin(); mit != mSampleSinks.end(); mit++)
      {
         sinkMap[ mit->first ] = std::make_pair( mit->second.first, mit->second.second );
      }
      
      return sinkMap;
   };
   
   bool HasHeadFootSink(const std::string sinkName)
   {
      //if we don't aleady have a SampleSink for this stream, then create one
      if( mHeadFootSinks.find( sinkName ) == mHeadFootSinks.end() )
      {
         return false;
      }
      return true;
   }
   
};


template<typename sample_sink_t>
class SampleSinkFactory : public BaseSampleSinkFactory
{

protected:
   
   void TryGetSampleSink(const std::string sinkName);
   void TryGetHeadFootSink(const std::string sinkName);

public:
   SampleSinkFactory();
   ~SampleSinkFactory();

   SampleSink*       GetSampleSink(const std::string sinkName);
   SampleStreamInfo* GetSampleStreamInfo(const std::string sinkName);
	
   BinarySink*       GetHeadFootSink(const std::string sinkName);
};

#include "SampleSinkFactory.hpp"

#endif //CLASS_SampleSinkFactory

