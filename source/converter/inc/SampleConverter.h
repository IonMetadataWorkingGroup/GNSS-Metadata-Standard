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
#ifndef CLASS_SampleConverter
#define CLASS_SampleConverter

#include <stdint.h>
#include <vector>
#include <string>
#include "LaneInterpreter.h"
#include "BlockInterpreter.h"
#include "ChunkInterpreter.h"
#include "SampleSinkFactory.h"
#include "BinaryFileSource.h"

#include <GnssMetadata/Metadata.h>

class SampleConverter
{
protected:

   bool                   mIsOpen;
   BaseSampleSinkFactory* mSampleSinkFactory;

   // interpreters for the lane objects - one per lane
   std::vector<LaneInterpreter*>             mLaneInterps;
   // a map of binary file sources, one per lane interpreter
   std::map<LaneInterpreter*,BinarySource*>  mLaneSources;
   
   // shortest common load period (in integer samples) for all lanes/blocks/chunks
   double mBaseLoadPeriod;
   
   //indicate whether or not to scale output samples to +/-1.0;
   bool mNormalizeSampleStreams;

   //block interpreter, creates one block interpeter object per block type, templated to sample output type (int8_t, float, etc...)
   template<typename sample_base_t>
   bool CreateBlockInterpreter( GnssMetadata::Metadata& md, SampleStreamInfo commonSampleInfo, GnssMetadata::Block* block, BlockInterpreter** blockInterp );
   
   // chunk interpreter, templated to the chunk type chunk_t -> uint8_t, uint16_t, uint32_t ...
   // second template argument defines the sample output type (int8_t, float, etc...)
   template<typename chunk_t, typename sample_base_t>
   bool CreateChunkInterpreter( GnssMetadata::Metadata& md, SampleStreamInfo commonSampleInfo, GnssMetadata::Chunk* chunk, Chunk** chunkInterp  );

public:
   SampleConverter( const bool normalizeSamples = false );
   virtual ~SampleConverter(void);

   // when opening the sampleconverter, we define the samplesink (where the samples go: file/buffer etc.)
   // and also define the output sample type: int8_t, float, etc...
   template <template<typename > class sample_sink_t, typename sample_base_t>
   bool Open( GnssMetadata::Metadata& md, std::string path_prefix="" );
   void Close(); //close, tidy up

   //convert at least 'bytesToProcess' of the input Lane file:
   void Convert( const uint32_t bytesToProcess = 0 );

   // query for the minimum interval of time that spans an integer number of samples on all streams
   double BaseLoadPeriod() const;

   // load a block of data from the Lane file such that we have at least 'secondsToLoad' with of samples
   bool Load( const double secondsToLoad );
 
};

#include "SampleConverter.hpp"

#endif // CLASS_SampleConverter
