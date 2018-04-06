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


#include <fstream>
#include "SampleFileSink.h"
#include "SampleConverter.h"
#include "SampleInterpreterFactory.h"


SampleConverter::SampleConverter(const bool normalizeSamples):
mIsOpen(false),
mSampleSinkFactory(NULL),
mBaseLoadPeriod(1)
{

   
      
}

SampleConverter::~SampleConverter()
{

   //just check that it has been closed
   Close();

}

void SampleConverter::Close()
{

   if( mIsOpen )
   {
      //delete the lane data
      for( std::vector<LaneInterpreter*>::iterator It = mLaneInterps.begin(); It != mLaneInterps.end(); ++It )
      {
         delete (*It);
         mLaneSources[*It]->Close();
         delete mLaneSources[*It];
         mLaneSources.erase(*It);
      }
      
      //delete the sampel sink factory
      delete mSampleSinkFactory;
      
   }
   mIsOpen = false;
}

void SampleConverter::SetNormalize( const bool yayOrNay )
{

   if( !mIsOpen )
   {
      printf("Error: SetNormalize(): no sampleSinks. Terminating.\n[Did you forget to call SampleConverter::Open( GnssMetadata::Metadata&)?].\n");
      return;
   }

   sampleSinkInfo_map_t ssMap = mSampleSinkFactory->GetSampleSinkInfoMap();
   
   for( sampleSinkInfo_map_t::iterator it = ssMap.begin(); it != ssMap.end(); ++it )
   {
      if( yayOrNay )
      {
         it->second.first->SetNormalize();
      }
      else
      {
         it->second.first->UnsetNormalize();
      }
   }
}

double SampleConverter::BaseLoadPeriod() const
{
   return mBaseLoadPeriod;
}


void SampleConverter::Convert( const uint32_t bytesToProcess )
{

   if( !mIsOpen )
   {
      printf("Error: Convert() :no file open - Terminating.\n[Did you forget to call SampleConverter::Open( GnssMetadata::Metadata&)?].\n");
      return;
   }

   // Do we have anything to do?
   if( mLaneInterps.size() == 0 )
   {
      printf("No Lanes found. Terminating.\n");
      return;
   }


   // otherwise iterate over the lanes and do the unpacking/converting
   for( std::vector<LaneInterpreter*>::iterator lnIt = mLaneInterps.begin(); lnIt != mLaneInterps.end(); lnIt++  )
   {

      //uint64_t bytesProcessed = 0;
   
      //for now, just decode the first Lane
      LaneInterpreter* laneInterpreter= (*lnIt);
      for( std::vector<BlockInterpreter*>::iterator It = laneInterpreter->Blocks().begin(); It != laneInterpreter->Blocks().end(); ++It )
      {
         BlockInterpreter* block = (*It);
         //read the entire block
         /*bytesProcessed = */ block->Interpret( mLaneSources[*lnIt], bytesToProcess );
      }

   }//end for( lnIt )
}




bool SampleConverter::Load( const double secondsToProcess )
{
   
   if( !mIsOpen )
   {
      printf("Error: no file open - Terminating.\n[Did you forget to call SampleConverter::Open( GnssMetadata::Metadata&)?].\n )");
      return false;
   }
   
   // Do we have anything to do?
   if( mLaneInterps.size() == 0 )
   {
      printf("No Lanes found. Terminating.\n");
      return false;
   }
   
   // JTC ToDo:
   //
   // Make sure that secondsToProcess is an integer multiple of BaseLoadPeriod
   //
   //
   
   
   bool readAllOK = true;
   
   // otherwise iterate over the lanes and do the unpacking/converting
   for( std::vector<LaneInterpreter*>::iterator lnIt = mLaneInterps.begin(); lnIt != mLaneInterps.end(); lnIt++  )
   {
      
      //for now, just decode the first Lane
      LaneInterpreter* laneInterpreter= (*lnIt);
      
      uint64_t readBlockSize = 0;
         
      //for( std::vector<BlockInterpreter*>::iterator It = laneInterpreter->Blocks().begin(); It != laneInterpreter->Blocks().end(); ++It )
      {
         std::vector<BlockInterpreter*>::iterator It = laneInterpreter->Blocks().begin();
         BlockInterpreter* block = (*It);
         
         //determine how many chunks to interpret
         uint32_t chunksToLoad = static_cast<uint32_t>( round( secondsToProcess / block->GetChunkPeriod() ) );
         //
         uint32_t chunksLoaded = 0;
         do
         {
            readBlockSize = block->InterpretChunks( mLaneSources[laneInterpreter] );
            chunksLoaded++;
         }
         while( readBlockSize != 0 && chunksLoaded < chunksToLoad );
         
         readAllOK = (readBlockSize != 0) && ( chunksToLoad == chunksLoaded );
      }
      
      
   }//end for( lnIt )

   return readAllOK;
}













