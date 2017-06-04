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

set( api_sources 
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/AnyUriTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/BandTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/BlockTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/ChunkTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/ClusterTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/Context.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/DurationTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/FileSetTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/FileTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/FrequencyTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/LaneTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/LumpTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/MetadataTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/OscillatorTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/PositionTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/OrientationTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/RfConfigTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/SessionTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/SourceTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/StreamTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/SystemTranslator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/Translator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/XmlDefs.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml/XmlProcessor.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/AnyUri.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/AttributedObject.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Band.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/BaseTypes.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Block.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Chunk.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Cluster.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Comment.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Date.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Duration.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/File.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Frequency.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Lane.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Lump.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Metadata.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Orientation.h
    ${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Oscillator.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Position.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/RfConfiguration.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Session.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Source.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/IonStream.h
	${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/System.h
    AnyUri.cpp
    AttributedObject.cpp
    Band.cpp
    BaseTypes.cpp
    Block.cpp
    Chunk.cpp
    Cluster.cpp
    CMakeLists.txt
    Comment.cpp
    Date.cpp
    Duration.cpp
    File.cpp
    Frequency.cpp
    Lane.cpp
    Lump.cpp
    Metadata.cpp
	Orientation.cpp
    Position.cpp
    Session.cpp
    Source.cpp
    IonStream.cpp
    System.cpp
    Xml/AnyUriTranslator.cpp
    Xml/BandTranslator.cpp
    Xml/BlockTranslator.cpp
    Xml/ChunkTranslator.cpp
    Xml/ClusterTranslator.cpp
    Xml/DurationTranslator.cpp
    Xml/FileSetTranslator.cpp
    Xml/FileTranslator.cpp
    Xml/FrequencyTranslator.cpp
    Xml/LaneTranslator.cpp
    Xml/LumpTranslator.cpp
    Xml/MetadataTranslator.cpp
    Xml/OscillatorTranslator.cpp
    Xml/PositionTranslator.cpp
	Xml/OrientationTranslator.cpp
    Xml/RfConfigTranslator.cpp
    Xml/SessionTranslator.cpp
    Xml/SourceTranslator.cpp
    Xml/StreamTranslator.cpp
    Xml/SystemTranslator.cpp
    Xml/Translator.cpp
    Xml/XmlProcessor.cpp
)
	
include_directories(
    ${CMAKE_SOURCE_DIR}/source/api/inc
    ${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata
    ${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml
    ${CMAKE_SOURCE_DIR}/source/api/inc/tinyxml2
)

add_library(api ${api_sources})














