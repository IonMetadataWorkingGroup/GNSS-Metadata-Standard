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

std::map< std::string, BinaryBuffer* > SampleFrontEnd::GetHeaderFooterSources( ) const
{

   std::map<std::string, BinaryBuffer*> hdftMap;
   
   std::map<std::string,BinarySink*> sinkMap = mSampleSinkFactory->GetHeadFootSinkMap();

   for(std::map<std::string,BinarySink*>::iterator sinkIt = sinkMap.begin(); sinkIt != sinkMap.end(); sinkIt++)
   {
      BinaryBuffer* pSampleBuff = dynamic_cast<BinaryBuffer*>( sinkIt->second );
      
      hdftMap[ sinkIt->first ] = pSampleBuff;
   }

   return hdftMap;

}



void SampleFrontEnd::Clear(  )
{
   
   //temporary pointer
   SampleSource* pSampleSource;
   
   sampleSinkInfo_map_t    sinkMap = mSampleSinkFactory->GetSampleSinkInfoMap();
   // iterate through all sample sources and clear the data
   for(sampleSinkInfo_map_t::iterator sinkIt = sinkMap.begin(); sinkIt != sinkMap.end(); sinkIt++)
   {
      pSampleSource = dynamic_cast<SampleSource*>( sinkIt->second.first );
      if( pSampleSource )
      {
         pSampleSource->Clear();
      }
   }

   // now iterate through all of the binary header/footer buffers and clear them too
   std::map<std::string,BinarySink*> hdftSinkMap = mSampleSinkFactory->GetHeadFootSinkMap();
   for(std::map<std::string,BinarySink*>::iterator sinkIt = hdftSinkMap.begin(); sinkIt != hdftSinkMap.end(); sinkIt++)
   {
      BinaryBuffer* pBinource = dynamic_cast<BinaryBuffer*>( sinkIt->second );
      if( pBinource )
      {
         pBinource->Clear();
      }
   }
 
}


