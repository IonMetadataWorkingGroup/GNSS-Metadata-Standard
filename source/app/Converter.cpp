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

//declare conversion function
template<typename sample_base_t>
int Convert( std::string xmlFileName );

int main(int argc, char* argv[])
{

	if (argc < 3)
	{
		printf("Call with:\n");
		printf(" - xml_file (full path)\n");
		printf(" - [type]   (output file type: int8_t, int16_t, int32_t, float, double)\n");
		return 0;
	}

	typedef enum 
	{
	   kInt8,
           kInt16,
           kInt32,
           kFloat,
           kDouble
	} outputTypes;

	std::map<std::string,outputTypes> validFileOutputType;
	validFileOutputType[ "int8_t"  ] = kInt8;
	validFileOutputType[ "int16_t" ] = kInt16;
	validFileOutputType[ "int32_t" ] = kInt32;
   validFileOutputType[ "float"   ] = kFloat;
  	validFileOutputType[ "double"  ] = kDouble;

	outputTypes fileOutputType = kInt8;
	if (validFileOutputType.find(argv[2]) != validFileOutputType.end())
		fileOutputType = validFileOutputType[argv[2]];

	printf("Parsing file: '%s'\n", argv[1]);
	
	
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

   //create the converter
   SampleConverter spcv;
   
   //open the Metadata Converter
   // Two argument template:
   // i)  define what sort of sample converter we want: 'SampleFileSink' or anything derived from SampleSink.h
   // ii) define the type 'sample_base_t', any native type: int8_t, float, etc..
   spcv.Open<SampleFileSink, sample_base_t>( md );

   //now you can tell the sample converters to normalize to +/-1.0 for float/double (if you like)
   bool doNormalize = false;
   spcv.SetNormalize( doNormalize );
   
   //perform the conversion - this will stream samples of
   //type sample_base_t to streams of type SampleFileSink
   spcv.Convert();

   //close the converter
   spcv.Close();

   return 0;
}


