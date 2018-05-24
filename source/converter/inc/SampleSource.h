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


#ifndef CLASS_SampleSource
#define CLASS_SampleSource

#include <stdint.h>

class SampleSource
{
protected:

   virtual bool Open() = 0;

public:
   
   virtual ~SampleSource(){};
  
   virtual uint32_t GetSamples( const  int8_t*& pbuff )  const = 0;
   virtual uint32_t GetSamples( const  int16_t*& pbuff ) const = 0;
   virtual uint32_t GetSamples( const  int32_t*& pbuff ) const = 0;
   virtual uint32_t GetSamples( const  int64_t*& pbuff ) const = 0;
   virtual uint32_t GetSamples( const  float*& pbuff )   const = 0;
   virtual uint32_t GetSamples( const  double*& pbuff )  const = 0;

   virtual void Close() = 0;
   virtual void Clear() = 0;

};

template<typename sample_base_t>
class SampleSourceT : public SampleSource
{
protected:

   virtual uint32_t DoGetSamples( const void** buff ) const = 0;

public:
   
   virtual ~SampleSourceT(){};
  
   virtual uint32_t GetSamples( const  int8_t*& pbuff ) const { return DoGetSamples( reinterpret_cast<const void**>(&pbuff) ); };
   virtual uint32_t GetSamples( const int16_t*& pbuff ) const { return DoGetSamples( reinterpret_cast<const void**>(&pbuff) ); };
   virtual uint32_t GetSamples( const int32_t*& pbuff ) const { return DoGetSamples( reinterpret_cast<const void**>(&pbuff) ); };
   virtual uint32_t GetSamples( const int64_t*& pbuff ) const { return DoGetSamples( reinterpret_cast<const void**>(&pbuff) ); };
   virtual uint32_t GetSamples( const   float*& pbuff ) const { return DoGetSamples( reinterpret_cast<const void**>(&pbuff) ); };
   virtual uint32_t GetSamples( const  double*& pbuff ) const { return DoGetSamples( reinterpret_cast<const void**>(&pbuff) ); };

};

#endif // CLASS_SampleSource
