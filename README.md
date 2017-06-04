# GNSS-Metadata-Standard


This project uses CMake. To create a project for your IDE follow the steps below.


Windows:

run the following commands:

> cd GNSS-Metadata-Standard   
> mkdir build   
> cd build   
> cmake ../ -G "Visual Studio 14 2015 Win64"   

Then open the .sln project and build the 'Release' configuration


Mac OS (Xcode)

> cd GNSS-Metadata-Standard   
> mkdir build   
> cd build   
> cmake ../ -G Xcode   


Then open the .xcodeproj project and build the 'Release' configuration

Unix (make) or Mac OS (make)

> cd GNSS-Metadata-Standard   
> mkdir build   
> cd build   
> cmake ../ -DCMAKE_BUILD_TYPE=Release   
> make   



To thest the code, change to the 'install' directory and run the acompanying matlab scrupt called 'check_converter.m'.
If everything has build OK then you should see the following output:

>>check_converter   
FGH:   OK   
IFEN:  OK   
JRC:   OK   
TRIGR: OK   
>>   


