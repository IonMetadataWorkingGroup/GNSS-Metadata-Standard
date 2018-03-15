#
#  Author: Cillian O'Driscoll, cillian dot odriscoll (at) gmail dot com
#   
#  Copyright(c) 2015 Institute of Navigation
#  http://www.ion.org
#   
#  This Metadata Converter is free software; you can redistribute it and/or
#  modify it under the terms of the Lesser GNU General Public License
#  as published by the Free Software Foundation; either version 3
#  of the License, or (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  Lesser GNU General Public License for more details.
# 
#  You should have received a copy of the Lesser GNU General Public License
#  along with Metadata API.  If not, see <http://www.gnu.org/licenses/>.
# 

set( cnv_lib_sources 
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/BinaryFileSource.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/BinarySource.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/BlockInterpreter.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/ChunkInterpreter.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/ChunkInterpreter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/EncoderFunctions.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/EndianFunctions.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/FormatFunctions.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/LaneInterpreter.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleBuffer.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleBuffer.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleConverter.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleConverter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleFileSink.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleFileSink.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleFrontEnd.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleFrontEnd.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleInterpreter.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleInterpreterFactory.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleInterpreterFactory.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleSink.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleSinkFactory.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleSinkFactory.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleSource.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleStreamInfo.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleStatisticsSink.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SampleStatisticsSink.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SinkedSampleInterpreter.h
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/SinkedSampleInterpreter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../inc/statistics.h
    BlockInterpreter.cpp
    EndianFunctions.cpp
    LaneInterpreter.cpp
    SampleConverter.cpp
    statistics.cpp
)
	
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../api/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../api/inc/GnssMetadata
    ${CMAKE_CURRENT_SOURCE_DIR}/../../api/inc/GnssMetadata/Xml
    ${CMAKE_CURRENT_SOURCE_DIR}/../../api/inc/tinyxml2
    ${CMAKE_CURRENT_SOURCE_DIR}/../inc
)

add_library(cnv ${cnv_lib_sources} )

