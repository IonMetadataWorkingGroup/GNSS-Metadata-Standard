#
#  Author: Cillian O'Driscoll, cillian dot odriscoll (at) gmail dot com
#          James T. Curran, jamestcurran (at) ieee.org
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
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/AnyUriTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/BandTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/BlockTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/ChunkTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/ClusterTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/Context.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/DurationTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/FileSetTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/FileTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/FrequencyTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/LaneTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/LumpTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/MetadataTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/OscillatorTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/PositionTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/OrientationTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/RfConfigTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/SessionTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/SourceTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/StreamTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/SystemTranslator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/Translator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/XmlDefs.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml/XmlProcessor.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/AnyUri.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/AttributedObject.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Band.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/BaseTypes.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Block.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Chunk.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Cluster.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Comment.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Date.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Duration.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/File.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Frequency.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Lane.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Lump.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Metadata.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Orientation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Oscillator.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Position.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/RfConfiguration.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Session.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Source.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/IonStream.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/System.h
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
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/GnssMetadata/Xml
    ${CMAKE_CURRENT_SOURCE_DIR}/../../inc/tinyxml2
)

add_library(api ${api_sources})














