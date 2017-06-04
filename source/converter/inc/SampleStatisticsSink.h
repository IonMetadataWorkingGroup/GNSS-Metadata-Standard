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

#ifndef CLASS_SampleStatisticsSink
#define CLASS_SampleStatisticsSink

#include <string>

#include "SampleSink.h"
#include "statistics.h"


template<typename sample_base_t>
class SampleStatisticsSink : public SampleSinkT<sample_base_t>
{

protected:
   std::string    mFileName;
   statistics     mStats;

   bool Open();
   void DoAddSample( sample_base_t x );
   
public:
   SampleStatisticsSink(std::string fileName);
   virtual ~SampleStatisticsSink(void);

   void Close();
   void Flush(){};
   void Report();
   
};

#include "SampleStatisticsSink.hpp"

#endif // CLASS_SampleStatisticsSink

