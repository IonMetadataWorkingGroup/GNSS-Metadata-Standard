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

#include <GnssMetadata/Metadata.h>
#include <GnssMetadata/Xml/XmlProcessor.h>

#include "SampleConverter.h"
#include "SampleSinkFactory.h"
#include "SampleFrontEnd.h"



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

   //create the factory for the sample-sinks used in the converter
   //
   // Dump the samples to file
   SampleSinkFactory<SampleFileSink<sample_base_t> > sampleSinkFactory;

   //create the converter
   SampleConverter spcv( &sampleSinkFactory );

   //open the Metadata Converter
   spcv.Open<sample_base_t>( md );

   //perform the conversion, in parts of 1ms
   for( int i=0; i<10; i++ )
   {
      //load 5000 chunks (equal to 1ms)
      spcv.Load( 5000 );

   }

   //close the converter
   spcv.Close();

   return 0;
}

template<typename sample_base_t>
int Statistics( std::string xmlFileName )
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

   //create the factory for the sample-sinks used in the converter
   //
   // Compute statistics of the samples:
   SampleSinkFactory<SampleStatisticsSink<sample_base_t> > sampleSinkFactory;


   //create the converter
   SampleConverter spcv( &sampleSinkFactory );

   //open the Metadata Converter
   spcv.Open<sample_base_t>( md );

   //perform the conversion, in parts of 1ms
   for( int i=0; i<10; i++ )
   {
      //load 5000 chunks (equal to 1ms)
      spcv.Load( 5000 );

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
   SampleFrontEnd<sample_base_t> frontEnd;

   //create the converter, pass the front-end, it will see it as a sampleSinkFactory
   SampleConverter spcv( &frontEnd );

   //open the Metadata Converter
   spcv.Open<sample_base_t>( md );

   //perform the conversion, in parts of 1ms
   for( int i=0; i<1; i++ )
   {
      //load 5000 chunks (equal to 1ms)
      spcv.Load( 5000 );

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
         const SampleStreamInfo* pSourceInfo = frontEnd.GetSampleStreamInfo( sourceName );

         pSourceInfo->Print();

         nSamples = pSource->GetSamples( pbuff );
         printf("Samples: ");
         for(int i=0;i<20;i++)
            printf("% 4d ", pbuff[i]);
         printf("\n");
      }

      //clear the sample buffers, otherwise the next Load will append the samples
      frontEnd.Clear();

   }


   //close the converter
   spcv.Close();

   return 0;
}

//std::string ToBin(uint8_t& dec,uint8_t nBits)
//{
//	std::string inBin;
//
//	for (int16_t i=nBits-1; i>=0; i--)
//	{
//		if (dec & (0x1 << i))
//			inBin.push_back('1');
//		else
//			inBin.push_back('0');
//	}
//
//	return inBin;
//}


int main(int argc, char* argv[])
{
    int res[3];
    std::string xmlFileName;

    try
    {

        // process JRC data
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        std::cout << "JRC data case\n";
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        change_dir( "JRC" );
        xmlFileName = "150408_125245_UTC.xml";
        res[0] = Convert<int8_t>(    xmlFileName );
        res[1] = Statistics<int8_t>( xmlFileName );
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
        res[1] = Statistics<int8_t>( xmlFileName );
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
        res[1] = Statistics<int8_t>( xmlFileName );
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
        res[1] = Statistics<int8_t>( xmlFileName );
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





	/*printf("Test Encoder Functions:\n");
	uint32_t chidx = 0, cksft = 0, qnt = 5;
	std::string inBin = "Binary";
	
	uint32_t strsz = std::max( static_cast<uint32_t>(inBin.length()), qnt );

	printf("%s   OB   OBA  SM   SMA  TC   TCA  OG   OGA\n", inBin.c_str());

	for (uint8_t i=0; i<(1 << qnt); i++)
	{

		inBin = ToBin(i, qnt);

		uint8_t* pCk = &i;
		int8_t   OB  = SampleEncoderFunctions::OffsetBinary<uint8_t, int8_t>(pCk, chidx, cksft, qnt);
		int8_t   SM  = SampleEncoderFunctions::SignMagnitude<uint8_t, int8_t>(pCk, chidx, cksft, qnt);
		int8_t   TC  = SampleEncoderFunctions::TwosCompliment<uint8_t, int8_t>(pCk, chidx, cksft, qnt);
		int8_t   OBA = SampleEncoderFunctions::OffsetBinaryAdjusted<uint8_t, int8_t>(pCk, chidx, cksft, qnt);
		int8_t   SMA = SampleEncoderFunctions::SignMagnitudeAdjusted<uint8_t, int8_t>(pCk, chidx, cksft, qnt);
		int8_t   TCA = SampleEncoderFunctions::TwosComplimentAdjusted<uint8_t, int8_t>(pCk, chidx, cksft, qnt);
		int8_t   OG  = SampleEncoderFunctions::OffsetGray<uint8_t, int8_t>(pCk, chidx, cksft, qnt);
		int8_t   OGA = SampleEncoderFunctions::OffsetGrayAdjusted<uint8_t, int8_t>(pCk, chidx, cksft, qnt);
				
		std::string padding = "";
		while (inBin.length() + padding.length() < strsz)
			padding.push_back(' ');

		printf("%s%s  %+3d  %+3d  %+3d  %+3d  %+3d  %+3d  %+3d  %+3d\n", inBin.c_str(), padding.c_str(), OB, OBA, SM, SMA, TC, TCA, OG, OGA);
	}

	return 0;*/
	




   		// process SJTU data
		//std::cout << "SJTU data case\n";
		//std::cout << "---------------\n";
		//change_dir( "SJTU" );
		//xmlFileName = "sjtu_l1b1_metadata_test_20151105.xml";
		//res[0] = Convert<int16_t>(    xmlFileName );
		//res[1] = Statistics<int16_t>( xmlFileName );
		//res[2] = FrontEnd<int16_t>(   xmlFileName );
		//std::cout << "Result: "
		//<< (res[0]==0?"ok ":"failed ")
		//<< (res[1]==0?"ok ":"failed ")
		//<< (res[2]==0?"ok ":"failed ")
		//<< "\n\n";
		//change_dir( ".." );
