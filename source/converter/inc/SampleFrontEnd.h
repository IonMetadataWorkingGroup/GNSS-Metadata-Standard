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

#ifndef CLASS_SampleFrontEnd
#define CLASS_SampleFrontEnd

#include "SampleSinkFactory.h"
#include "SampleBuffer.h"
#include "BinaryBuffer.h"
#include "SampleConverter.h"

class SampleFrontEnd : public SampleConverter
{

public:

   //typedef for a map indexed by Stream name, and containing a pair: sampleSource and an info-structure
	typedef std::map< std::string, std::pair<const SampleSource*, const SampleStreamInfo*> > taggedSampleStreamWithInfo;

   //constructor
   SampleFrontEnd()  {};

   // when calling Open() we define the type of the output samples (int8_t, float, double, ... )
   template<typename sample_base_t>
   bool Open( GnssMetadata::Metadata& md, std::string path_prefix="" )
   {
      return SampleConverter::Open<SampleBuffer,sample_base_t, BinaryBuffer>( md, path_prefix );
   }
   
   // return a SampelSource by name
   const SampleSource*     GetSource(const std::string sinkName) const;
   const SampleStreamInfo* GetSourceInfo( const std::string sinkName ) const;
   //
   std::map< std::string, std::pair<const SampleSource*, const SampleStreamInfo*> > GetSources( ) const;
   
   // get a map of header/footer sources, indexed by LaneID string
   std::map< std::string, BinaryBuffer* > GetHeaderFooterSources( ) const;

   // clear buffers corresponding to all SampleSources
   // simultanious clear of all sources will keep sample data aligned
   void Clear( );
	
};

#include "SampleFrontEnd.hpp"

#endif //CLASS_SampleFrontEnd

