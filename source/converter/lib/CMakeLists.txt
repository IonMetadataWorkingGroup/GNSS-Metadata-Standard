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
	${CMAKE_SOURCE_DIR}/source/converter/inc/BlockInterpreter.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/ChunkInterpreter.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/ChunkInterpreter.hpp
	${CMAKE_SOURCE_DIR}/source/converter/inc/EncoderFunctions.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/EndianFunctions.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/FormatFunctions.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/LaneInterpreter.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleBuffer.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleBuffer.hpp
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleConverter.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleConverter.hpp
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleFileSink.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleFileSink.hpp
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleFrontEnd.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleFrontEnd.hpp
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleInterpreter.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleInterpreterFactory.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleInterpreterFactory.hpp
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleSink.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleSinkFactory.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleSinkFactory.hpp
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleSource.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleStreamInfo.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleStatisticsSink.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SampleStatisticsSink.hpp
	${CMAKE_SOURCE_DIR}/source/converter/inc/SinkedSampleInterpreter.h
	${CMAKE_SOURCE_DIR}/source/converter/inc/SinkedSampleInterpreter.hpp
	${CMAKE_SOURCE_DIR}/source/converter/inc/statistics.h
    BlockInterpreter.cpp
    EndianFunctions.cpp
    LaneInterpreter.cpp
    SampleConverter.cpp
    statistics.cpp
)
	
include_directories(
    ${CMAKE_SOURCE_DIR}/source/api/inc
    ${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata
    ${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml
    ${CMAKE_SOURCE_DIR}/source/api/inc/tinyxml2
    ${CMAKE_SOURCE_DIR}/source/converter/inc
)

add_library(cnv ${cnv_lib_sources} )

