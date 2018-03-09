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

template<typename chunk_t,typename sample_base_t>
SinkedSampleInterpreter<chunk_t,sample_base_t>::SinkedSampleInterpreter( 
                     const uint32_t bitWidth, 
                     sample_base_t (* encodingFunc)( const chunk_t*,  uint32_t,  uint32_t,  uint32_t ),
                     void (*formatFunc)( sample_base_t (* )( const chunk_t* ,  uint32_t,  uint32_t,  uint32_t ), const chunk_t* pChunk, uint32_t, uint32_t, uint32_t, SampleSink* ),
                     SampleSink* sampleSink,
                     const uint16_t callOrder
                  ):
SampleInterpreter(bitWidth, callOrder),
mChunkIndex(0), 
mResidualBitIndex(0),
mSampleSink(sampleSink),
mEncodingFunc( encodingFunc ),
mFormatFunc( formatFunc )
{

}

template<typename chunk_t,typename sample_base_t>
SinkedSampleInterpreter<chunk_t,sample_base_t>::~SinkedSampleInterpreter( )
{ 

}

template<typename chunk_t,typename sample_base_t>
void SinkedSampleInterpreter<chunk_t,sample_base_t>::SetChunkOffset( const uint32_t chunkOffsetInBits )
{
   mChunkIndex       = chunkOffsetInBits / ( 8 * sizeof( chunk_t ) );
   mResidualBitIndex = chunkOffsetInBits - mChunkIndex * ( 8 * sizeof( chunk_t ) );
}

template<typename chunk_t,typename sample_base_t>
void SinkedSampleInterpreter<chunk_t,sample_base_t>::Interpret( const void* vChunk ) const
{

   const chunk_t* pChunk = reinterpret_cast<const chunk_t*>( vChunk );
   (*mFormatFunc)( mEncodingFunc, pChunk, mChunkIndex, mResidualBitIndex, mBitWidth, mSampleSink );

}


