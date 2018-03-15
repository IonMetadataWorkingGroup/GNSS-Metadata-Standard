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
#include "SampleFrontEnd.h"

const SampleSource* SampleFrontEnd::GetSource( const std::string sinkName ) const
{

   if( ! mSampleSinkFactory->HasSampleSink( sinkName ) )
   {
      printf("Error: cannot find sample source!\n");
      return NULL;
   }
   
   const SampleSource* sampleSource = dynamic_cast<const SampleSource*>( mSampleSinkFactory->GetSampleSink( sinkName ) );
   
   return sampleSource;
 
}

const SampleStreamInfo* SampleFrontEnd::GetSourceInfo( const std::string sinkName ) const
{
   
   if( ! mSampleSinkFactory->HasSampleSink( sinkName ) )
   {
      printf("Error: cannot find sample source!\n");
      return NULL;
   }
   
   return mSampleSinkFactory->GetSampleStreamInfo( sinkName );
 
}


std::map< std::string, std::pair<const SampleSource*, const SampleStreamInfo*> > SampleFrontEnd::GetSources( ) const
{

   const SampleSource* pSampleBuff;
   std::map< std::string, std::pair<const SampleSource*, const SampleStreamInfo*> > sourceMap;
   
   sampleSinkInfo_map_t    sinkMap = mSampleSinkFactory->GetSampleSinkInfoMap();
   for(sampleSinkInfo_map_t::iterator sinkIt = sinkMap.begin(); sinkIt != sinkMap.end(); sinkIt++)
   {
      pSampleBuff = dynamic_cast<const SampleSource*>( sinkIt->second.first );
      
      sourceMap[ sinkIt->first ] = std::make_pair( pSampleBuff, sinkIt->second.second );
   }
   
   return sourceMap;
   
}


void SampleFrontEnd::Clear(  )
{
   
   //temporary pointer
   SampleSource* pSampleSource;
   
   sampleSinkInfo_map_t    sinkMap = mSampleSinkFactory->GetSampleSinkInfoMap();

   for(sampleSinkInfo_map_t::iterator sinkIt = sinkMap.begin(); sinkIt != sinkMap.end(); sinkIt++)
   {
      pSampleSource = dynamic_cast<SampleSource*>( sinkIt->second.first );
      if( pSampleSource )
         pSampleSource->Clear();
   }
 
}


