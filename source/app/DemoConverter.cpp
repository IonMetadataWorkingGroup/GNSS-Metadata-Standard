#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#ifdef _WIN32
   #include <direct.h>
   #define change_dir _chdir
#elif defined __linux__ || __APPLE__
   #include <sys/stat.h>
   #include <unistd.h>
   #define change_dir chdir
#endif

#include <iostream>

// include the GNSS Metadata API
#include "GnssMetadata.h"
// include the converter
#include "Converter.h"

template<typename sample_base_t>
int Convert( std::string xmlFileName );

template<typename sample_base_t>
int ComputeStatistics( std::string xmlFileName );

template<typename sample_base_t>
int FrontEnd( std::string xmlFileName );

void PrintEncoderTables();

int main(int argc, char* argv[])
{

    // uncomment to see console print-out of standard binary encoder formats
    //PrintEncoderTables();
    //return 0;
    
    int res[3];
    std::string xmlFileName;

    // if we are passed two arguments, then interpret as:
    // argv[1] -> 'path' 
    // argv[2] -> 'xml-file'
    // then process this file instead of the standard tests below.
    if( argc == 3 )
    {

       // process data from command-line-args
       std::string xmlDirName  = std::string( argv[1] );
       std::string xmlFileName = std::string( argv[2] );
       printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
       std::cout << xmlFileName << std::endl;
       printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
       change_dir( xmlDirName.c_str() );
       res[0] = Convert<int16_t>(    xmlFileName );
       res[1] = ComputeStatistics<int16_t>( xmlFileName );
       res[2] = FrontEnd<int16_t>(   xmlFileName );
       std::cout << "Result: "
       << (res[0]==0?"ok ":"failed ")
       << (res[1]==0?"ok ":"failed ")
       << (res[2]==0?"ok ":"failed ")
       << "\n\n";
       change_dir( ".." );
       
       return 0;
    }

    try
    {
       
       // process JRC data
       printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
       std::cout << "JRC data case\n";
       printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
       change_dir( "JRC" );
       xmlFileName = "150408_125245_UTC.xml";
       res[0] = Convert<int8_t>(    xmlFileName );
       res[1] = ComputeStatistics<int8_t>( xmlFileName );
       res[2] = FrontEnd<int8_t>(   xmlFileName );
       std::cout << "Result: "
       << (res[0]==0?"ok ":"failed ")
       << (res[1]==0?"ok ":"failed ")
       << (res[2]==0?"ok ":"failed ")
       << "\n\n";
       change_dir( ".." );

       
        // process IFEN data
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        std::cout << "IFEN data case\n";
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

        change_dir( "IFEN" );
        xmlFileName = "SX3_AltBOC_DualRF.smfx";
        res[0] = Convert<int8_t>(    xmlFileName );
        res[1] = ComputeStatistics<int8_t>( xmlFileName );
        res[2] = FrontEnd<int8_t>(   xmlFileName );
        std::cout << "Result: "
                  << (res[0]==0?"ok ":"failed ")
                  << (res[1]==0?"ok ":"failed ")
                  << (res[2]==0?"ok ":"failed ")
                  << "\n\n";
        change_dir( ".." );

        // process Fraunhofer data
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        std::cout << "FHG data case\n";
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        change_dir( "FHG" );
        xmlFileName = "L125_III1b_15s.usbx";
        res[0] = Convert<int8_t>(    xmlFileName );
        res[1] = ComputeStatistics<int8_t>( xmlFileName );
        res[2] = FrontEnd<int8_t>(   xmlFileName );
        std::cout << "Result: "
                  << (res[0]==0?"ok ":"failed ")
                  << (res[1]==0?"ok ":"failed ")
                  << (res[2]==0?"ok ":"failed ")
                  << "\n\n";
        change_dir( ".." );

        // Process TRIGR data.
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        std::cout << "TRIGR data case\n";
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        change_dir( "TRIGR" );
        xmlFileName = "WideBand_1bit_L1_L2_E5a_E5b_000.tgx";
        res[0] = Convert<int8_t>(    xmlFileName );
        res[1] = ComputeStatistics<int8_t>( xmlFileName );
        res[2] = FrontEnd<int8_t>(   xmlFileName );
        std::cout << "Result: "
                  << (res[0]==0?"ok ":"failed ")
                  << (res[1]==0?"ok ":"failed ")
                  << (res[2]==0?"ok ":"failed ")
                  << "\n\n";
        change_dir( ".." );

       // Process CODC data.
       printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
       std::cout << "CODC data case\n";
       printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
       change_dir( "CODC" );
       xmlFileName = "20170911_1118Z.sdrx";
       res[0] = Convert<int16_t>(    xmlFileName );
       res[1] = ComputeStatistics<int16_t>( xmlFileName );
       res[2] = FrontEnd<int16_t>(   xmlFileName );
       std::cout << "Result: "
       << (res[0]==0?"ok ":"failed ")
       << (res[1]==0?"ok ":"failed ")
       << (res[2]==0?"ok ":"failed ")
       << "\n\n";
       change_dir( ".." );
       
       // Process CODC data.
       printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
       std::cout << "FITWDP data case\n";
       printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
       change_dir( "FITWDP" );
       xmlFileName = "estec.xml";
       res[0] = Convert<int8_t>(    xmlFileName );
       res[1] = ComputeStatistics<int16_t>( xmlFileName );
       res[2] = FrontEnd<int8_t>(   xmlFileName );
       std::cout << "Result: "
       << (res[0]==0?"ok ":"failed ")
       << (res[1]==0?"ok ":"failed ")
       << (res[2]==0?"ok ":"failed ")
       << "\n\n";
       change_dir( ".." );
       

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

   printf("\n----------------n");
   printf("Running `Convert()' test:\n");

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
   // i)  define what sort of sample converter we want:
   //     'SampleFileSink' will stream received samples to file
   // ii) define the type 'sample_base_t', any native type: int8_t, float, etc..
   spcv.Open< SampleFileSink, sample_base_t>( md );
   

   //perform the conversion, in parts of 1ms
   for( int i=0; i<200; i++ )
   {
      //load equal to 1ms
      spcv.Load( 0.001 );
      
   }

   //close the converter
   spcv.Close();

   return 0;
}


template<typename sample_base_t>
int ComputeStatistics( std::string xmlFileName )
{

   printf("\n----------------n");
   printf("Running `Statistics()' test:\n");

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
   // i)  define what sort of sample converter we want:
   //     'SampleStatisticsSink' will compute stats based on the received samples
   // ii) define the type 'sample_base_t', any native type: int8_t, float, etc..
   spcv.Open< SampleStatisticsSink, sample_base_t>( md );
   
   
   //perform the conversion, in parts of 1ms
   for( int i=0; i<10; i++ )
   {
      //load equal to 1ms
      spcv.Load( 0.001 );

   }

   //close the converter
   spcv.Close();

   return 0;
}


template<typename sample_base_t>
int FrontEnd( std::string xmlFileName )
{

   printf("\n----------------n");
   printf("Running `FrontEnd()' test:\n");

   GnssMetadata::Metadata md;
   GnssMetadata::XmlProcessor xproc;

   if( !xproc.Load( xmlFileName.c_str(), false, md) )
   {
      printf("Could not load metadata. Terminating.\n");
      return -1;
   }

   //create the factory for the sample-sinks used in the converter, this is just a set of named buffers
   SampleFrontEnd frontEnd;
   //open the Metadata Converter, tell it to use a sample_base_t internal type for the samples
   frontEnd.Open<sample_base_t>( md );

   //load 1ms
   frontEnd.Load( 0.001 );

   uint32_t nSamples = 0;
   const sample_base_t* pbuff;

   // ask the front-end for the SampleSource corresponding to the channel
   //(there might be a way to enumerate this better)
   //
   // the sources will have as many samples as correspond all of the
   // previous Load( nChunks ) calls, since the last call to Clear()
   std::map< std::string, std::pair<const SampleSource*, const SampleStreamInfo*> > sourceMap = frontEnd.GetSources();
   for(std::map< std::string, std::pair<const SampleSource*, const SampleStreamInfo*> >::iterator src_it = sourceMap.begin(); src_it != sourceMap.end(); src_it++)
   {
      std::string             sourceName  = src_it->first;
      const SampleSource*     pSource     = frontEnd.GetSource( sourceName );
      const SampleStreamInfo* pSourceInfo = frontEnd.GetSourceInfo( sourceName );

      pSourceInfo->Print();

      nSamples = pSource->GetSamples( pbuff );
      printf("Samples: ");
      for(int i=0;i<20;i++)
         printf("% 4d ", pbuff[i]);
      printf("\n");
   }

   //clear the sample buffers, otherwise the next Load will append the samples
   frontEnd.Clear();


   //close the converter
   frontEnd.Close();

   return 0;
}

void PrintEncoderTables()
{
   
   uint8_t sample;

   for( uint32_t qnt=2; qnt<=5; qnt++)
   {
      printf("%d-Bit Formats\n",qnt);
      printf(" HEX |  OB | OBA |  SM | SMA |  MS | MSA |  TC | TCA |  OG | OGA |\n");
      for(size_t i=0; i<(1<<qnt); i++)
      {
         sample = static_cast<uint8_t>(i);

         printf("  %02x | %+03d | %+03d | %+03d | %+03d | %+03d | %+03d | %+03d | %+03d | %+03d | %+03d |\n",
            sample,
            SampleEncoderFunctions::OffsetBinary<uint8_t,int8_t>(&sample,0,0,qnt),   
            SampleEncoderFunctions::OffsetBinaryAdjusted<uint8_t,int8_t>(&sample,0,0,qnt),   
            SampleEncoderFunctions::SignMagnitude<uint8_t,int8_t>(&sample,0,0,qnt),   
            SampleEncoderFunctions::SignMagnitudeAdjusted<uint8_t,int8_t>(&sample,0,0,qnt),   
            SampleEncoderFunctions::MagnitudeSign<uint8_t,int8_t>(&sample,0,0,2),   
            SampleEncoderFunctions::MagnitudeSignAdjusted<uint8_t,int8_t>(&sample,0,0,qnt),   
            SampleEncoderFunctions::TwosCompliment<uint8_t,int8_t>(&sample,0,0,qnt),   
            SampleEncoderFunctions::TwosComplimentAdjusted<uint8_t,int8_t>(&sample,0,0,qnt),   
            SampleEncoderFunctions::OffsetGray<uint8_t,int8_t>(&sample,0,0,qnt),   
            SampleEncoderFunctions::OffsetGrayAdjusted<uint8_t,int8_t>(&sample,0,0,qnt)
         );   
      }
      printf("\n\n\n");
   }
   
};

