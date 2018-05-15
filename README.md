# GNSS-Metadata-Standard

  Linux & OSX:  [![Build Status](https://travis-ci.org/IonMetadataWorkingGroup/GNSS-Metadata-Standard.svg?branch=travis)](https://travis-ci.org/IonMetadataWorkingGroup/GNSS-Metadata-Standard)


  Windows:  [![Build status](https://ci.appveyor.com/api/projects/status/7oy9xv60ko04gfub/branch/travis?svg=true)](https://ci.appveyor.com/project/JamesTCurran/gnss-metadata-standard/branch/travis)

The 'master' branch is frozen between major updates inlucind requests for comment, and opdated once or twice annually. 

Ongoing development and latests updates are available on the 'deve' branch. If you wish to submit code or pull-requests, please use the 'deve' branch. Pull requests for 'master' will be rejected. 

This project uses CMake. To create a project for your IDE follow the steps below.


Windows:
> cd GNSS-Metadata-Standard   
> mkdir build   
> cd build   
> cmake ../ -G "Visual Studio 14 2015 Win64"   
Then open the .sln project and build the 'Release' configuration

Mac OS (Xcode):
> cd GNSS-Metadata-Standard   
> mkdir build   
> cd build   
> cmake ../ -G Xcode   
Then open the .xcodeproj project and build the 'Release' configuration

Unix (make) or Mac OS (make):
> cd GNSS-Metadata-Standard   
> mkdir build   
> cd build   
> cmake ../ -DCMAKE_BUILD_TYPE=Release   
> make   



To thest the code, change to the 'install' directory and run the acompanying matlab/octave script called 'check_converter.m'.  
If everything has build OK then you should see the following output:  
  
>check_converter
>Deleting old files: ......Done.
>Running the test converter ("Converter"): Checking the converted output: 
>CODC:            OK
>FHG:             OK
>FITWDP:          OK
>IFEN:            OK
>JRC:             OK
>TRIGR:           OK
>
>Test completed.
>

To add the the "GNSS-Metadata-Standard Converter" to your  CMake managed project, 
add the following lines to your CMakeLists.txt file:

> include_directories(   
>    path_to_where_you_copied_the_repository/GNSS-Metadata-Standard/source/api/inc   
>    path_to_where_you_copied_the_repository/GNSS-Metadata-Standard/source/converter/inc   
> )   
> add_subdirectory(   
>    path_to_where_you_copied_the_repository/GNSS-Metadata-Standard/source   
> )   
>    
> target_link_libraries( your_library_or_executable api xml cnv )   
 
and include the following in your main.cpp file

> #include "GnssMetadata.h"       
> #include "Converter.h"


To add the only the "GNSS-Metadata-Standard API" to your  CMake managed project,    
add the following lines to your CMakeLists.txt file:   

> include_directories(   
>    path_to_where_you_copied_the_repository/GNSS-Metadata-Standard/source/api/inc   
> )   
> add_subdirectory(   
>    path_to_where_you_copied_the_repository/GNSS-Metadata-Standard/source   
> )    
>    
> target_link_libraries( your_library_or_executable api xml )   

and include the following in your main.cpp file   

> #include "GnssMetadata.h"   
