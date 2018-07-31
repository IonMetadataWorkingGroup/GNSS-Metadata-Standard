# GNSS-Metadata-Standard

In recent years there has been a proliferation of software defined radio (SDR) data collection systems and processing platforms designed for Global Navigation Satellite System (GNSS) receiver applications or those that support GNSS bands. For post-processing, correctly interpreting the GNSS SDR sampled datasets produced or consumed by these systems has historically been a cumbersome and error-prone process. This is because these systems necessarily produce datasets of various formats, the subtleties of which are often lost in translation when communicating between the producer and consumer of these datasets. The GNSS-Metadata-Standard is an effort to standardize the metadata associated with GNSS SDR sampled data files and the layout of the binary sample files.

The GNSS SDR Metadata Standard defines parameters and schema to express the contents of SDR sample data files. The standard is designed to promote the interoperability of GNSS SDR data collection systems and processors. The metadata files are human readable and in XML format. This repository hosts a set of compliant open source C++ API for reading metadata and binary samples.

The repository contains two libraries: 
1. An API library that can be used for loading and writing Metadata to/from file and
2. A converter library that can be used for parsing packed binary SDR data and converting it to machine-format (int, float, etc.) streams

A selectoin of demonstration applicatoins are provided, including:
1. A demonstration of reading/writing XML Metadata, named *TestAPI*
2. A demonstration of the basic binary convertion utilities, named *DemoConverter*
3. A simple binary sample file converter utility, named *Converter* that can be used for converting packed binary SDR files to mahcine-format (int, float, etc.) files


The 'master' branch is frozen between major updates, and opdated once or twice annually. Ongoing development and latests updates are available on the 'devel' branch. If you wish to submit code or pull-requests, please use the 'devel' branch.  Pull requests for 'master' will be rejected during ongoing review and RFC process. For more information on the standard, and to download sample data files, please visit http://sdr.ion.org/

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
