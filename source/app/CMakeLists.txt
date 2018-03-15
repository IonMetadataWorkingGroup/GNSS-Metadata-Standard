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

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../api/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../converter/inc
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
set( DemoConverter_sources 
    DemoConverter.cpp
)
add_executable(DemoConverter ${DemoConverter_sources} )
target_link_libraries(DemoConverter cnv api xml )
set_target_properties( DemoConverter
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/install"
)
# change the path so as not to include Debug/Release
set_target_properties(DemoConverter PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/install"
)
set_target_properties(DemoConverter PROPERTIES
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
