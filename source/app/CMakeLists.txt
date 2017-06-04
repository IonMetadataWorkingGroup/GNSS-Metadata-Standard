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
	
	
include_directories(
    ${CMAKE_SOURCE_DIR}/source/api/inc
    ${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata
    ${CMAKE_SOURCE_DIR}/source/api/inc/GnssMetadata/Xml
    ${CMAKE_SOURCE_DIR}/source/api/inc/tinyxml2
    ${CMAKE_SOURCE_DIR}/source/converter/inc
)


###############################################################################
set( API_sources 
    TestAPI.cpp
)
	
add_executable(TestAPI ${API_sources} )
target_link_libraries(TestAPI api xml)
set_target_properties( TestAPI
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/install"
)
# change the path so as not to include Debug/Release
set_target_properties(TestAPI PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/install"
)
set_target_properties(TestAPI PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/install"
)
 

###############################################################################
set( TestConverter_sources 
    TestConverter.cpp
)
add_executable(TestConverter ${TestConverter_sources} )
target_link_libraries(TestConverter cnv api xml )
set_target_properties( TestConverter
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/install"
)
# change the path so as not to include Debug/Release
set_target_properties(TestConverter PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/install"
)
set_target_properties(TestConverter PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/install"
)
 
 
############################################################################### 
 set( ConverterApp_sources 
    Converter.cpp
)
add_executable(Converter ${ConverterApp_sources} )
target_link_libraries(Converter cnv api xml )
set_target_properties( Converter
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/install"
)
# change the path so as not to include Debug/Release
set_target_properties(Converter PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/install"
)
set_target_properties(Converter PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/install"
)


