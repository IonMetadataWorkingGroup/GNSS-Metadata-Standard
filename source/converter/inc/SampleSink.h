/**
 * Author: James T. Curran
 *  
 * Copyright(c) 2015 Institute of Navigation
 * http://www.ion.org
 *  
 * This Metadata Converter is free software; you can redistribute it and/or
 * modify it under the terms of the Lesser GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Metadata API.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef CLASS_SampleSink
#define CLASS_SampleSink

#include <stdint.h>

#define BASE_BUFFER_SIZE_IN_BYTES 1024 * 1024

class SampleSink
{
protected:
   bool         mIsOpen, mDoNormalize;
   double       mConfigScaleValue, mScaleValue;
   virtual bool Open() = 0;
   
   SampleSink():
   mDoNormalize(false),
   mConfigScaleValue(1), // the value that would be used if "doNormalize" is called
   mScaleValue(1)        // the value that is currently being used (default to 1.0)
   { };

public:
   
   virtual ~SampleSink(){};
   
   virtual void SetScaleValue( const double scale )
   {
      mConfigScaleValue = scale;
      if( mDoNormalize )
      {
         mScaleValue = mConfigScaleValue;
      }
   };
   virtual void SetNormalize()
   {
      mScaleValue = mConfigScaleValue;
      mDoNormalize = true;
   };
   virtual void UnsetNormalize()
   {
      mScaleValue  = 1.0;
      mDoNormalize = false;
   };
   
   virtual void AddSample( int8_t  x ) = 0;
   virtual void AddSample( int16_t x ) = 0;
   virtual void AddSample( int32_t x ) = 0;
   virtual void AddSample( int64_t x ) = 0;
   virtual void AddSample( float   x ) = 0;
   virtual void AddSample( double  x ) = 0;
   
   virtual void AddSample( int8_t  x, int8_t  y ) = 0;
   virtual void AddSample( int16_t x, int16_t y ) = 0;
   virtual void AddSample( int32_t x, int32_t y ) = 0;
   virtual void AddSample( int64_t x, int64_t y ) = 0;
   virtual void AddSample( float   x, float   y ) = 0;
   virtual void AddSample( double  x, double  y ) = 0;

   virtual void Close() = 0;
   virtual void Flush(){};

};

template<typename sample_base_t>
class SampleSinkT : public SampleSink
{
protected:
   virtual void DoAddSample( sample_base_t x ) = 0;
   virtual void DoAddSample( sample_base_t x, sample_base_t y ) = 0;

public:
   
   virtual ~SampleSinkT(){}

   // This is a little ugly, but accommodates the parsing of multiple SampleFileSinks, which
   // have different template arguments, in one container. Hopefully the optimizer can take 
   // care of removing the extra function calls. Is there a better way?
   void AddSample( int8_t  x ){ DoAddSample( static_cast<sample_base_t>( x ) ); }
   void AddSample( int16_t x ){ DoAddSample( static_cast<sample_base_t>( x ) ); }
   void AddSample( int32_t x ){ DoAddSample( static_cast<sample_base_t>( x ) ); }
   void AddSample( int64_t x ){ DoAddSample( static_cast<sample_base_t>( x ) ); }
   void AddSample( float   x ){ DoAddSample( static_cast<sample_base_t>( x * mScaleValue ) ); }
   void AddSample( double  x ){ DoAddSample( static_cast<sample_base_t>( x * mScaleValue ) ); }
   
   void AddSample( int8_t  x, int8_t  y ){ DoAddSample( static_cast<sample_base_t>( x ), static_cast<sample_base_t>( y ) ); }
   void AddSample( int16_t x, int16_t y ){ DoAddSample( static_cast<sample_base_t>( x ), static_cast<sample_base_t>( y ) ); }
   void AddSample( int32_t x, int32_t y ){ DoAddSample( static_cast<sample_base_t>( x ), static_cast<sample_base_t>( y ) ); }
   void AddSample( int64_t x, int64_t y ){ DoAddSample( static_cast<sample_base_t>( x ), static_cast<sample_base_t>( y ) ); }
   void AddSample( float   x, float   y ){ DoAddSample( static_cast<sample_base_t>( x * mScaleValue ), static_cast<sample_base_t>( y * mScaleValue ) ); }
   void AddSample( double  x, double  y ){ DoAddSample( static_cast<sample_base_t>( x * mScaleValue ), static_cast<sample_base_t>( y * mScaleValue ) ); }
   
   
};

#endif // CLASS_SampleSink
