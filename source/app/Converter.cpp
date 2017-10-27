
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#ifdef _WIN32
   #include <direct.h>
#elif defined __linux__
   #include <sys/stat.h>
   #include <unistd.h>
#endif

#include <iostream>

// include the GNSS Metadata API
#include "GnssMetadata.h"
// include the converter
#include "Converter.h"

// process triple frequency data from JRC
template<typename sample_base_t>
int Convert( std::string xmlFileName )
{

   GnssMetadata::Metadata md;
   GnssMetadata::XmlProcessor xproc;

   if( !xproc.Load( xmlFileName.c_str(), false, md) )
   {
      printf("Could not load metadata. Terminating.\n");
      return -1;
   }

   //create the factory for the sample-sinks used in the converter
   //
   // Dump the samples to file
   SampleSinkFactory<SampleFileSink<sample_base_t> > sampleSinkFactory;

   //create the converter
   SampleConverter spcv( &sampleSinkFactory );

   //open the Metadata Converter
   spcv.Open<sample_base_t>( md );

   //perform the conversion
   spcv.Convert();


   //close the converter
   spcv.Close();

   return 0;
}



int main(int argc, char* argv[])
{

	if (argc < 2)
	{
		printf("Call with:\n");
		printf(" - xml_file (full path)\n");
		printf(" - [type]   (output file type: int8_t, int16_t, int32_t, int64_t, float, double)\n");
		return 0;
	}



	typedef enum 
	{
		kInt8, kInt16, kInt32, kInt64, kFloat, kDouble
	} outputTypes;

	std::map<std::string,outputTypes> validFileOutputType;
	validFileOutputType[ "int8_t"  ] = kInt8;
	validFileOutputType[ "int16_t" ] = kInt16;
	validFileOutputType[ "int32_t" ] = kInt32;
	validFileOutputType[ "int64_t" ] = kInt64;
   validFileOutputType[ "float"   ] = kFloat;
  	validFileOutputType[ "double"  ] = kDouble;

	outputTypes fileOutputType = kInt8;
	if (validFileOutputType.find(argv[2]) != validFileOutputType.end())
		fileOutputType = validFileOutputType[argv[2]];

	printf("Parsing file: '%s'", argv[1]);
	
	
	try
    {

        //
        std::cout << "--- GNSS MetaData Converter ---\n";
		
		   switch (fileOutputType)
		   {
            case kInt8:
               Convert<int8_t>(argv[1]);
               break;
            case kInt16:
               Convert<int16_t>(argv[1]);
               break;
            case kInt32:
               Convert<int32_t>(argv[1]);
               break;
            case kInt64:
               Convert<int64_t>(argv[1]);
               break;
		      case kFloat:
      	      Convert<float>(argv[1]);
 			      break;
 		      case kDouble:
 			      Convert<double>(argv[1]);
 			      break;
		   }
		
		


	}
	catch ( GnssMetadata::ApiException &e)
	{
		std::cout << "caught API exception: " << e.what( ) << "\n";
	}
	catch (std::exception &e)
	{
		std::cout << "caught exception: " << e.what( ) << "\n";
	}
	catch( ... )
	{
		std::cout << "unknown exception\n";
	}
		return 0;
}


