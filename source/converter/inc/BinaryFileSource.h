/**
 * Author: James T. Curran
 *
 * Copyright(c) 2016 Institute of Navigation
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

#ifndef CLASS_BinaryFileSource
#define CLASS_BinaryFileSource

#include "BinarySource.h"
#include <fstream>


class BinaryFileSource : public BinarySource
{
   
protected:
   std::ifstream*                 mBinfile;
   
   
   std::vector<uint8_t>           mData;
   std::vector<uint8_t>::iterator mStartBuffer;
   std::vector<uint8_t>::iterator mEndBuffer;

   bool DoOpen(const std::string streamName);
   void DoClose();
   bool Load();

public:
   BinaryFileSource();
   BinaryFileSource(const std::string filename);
   virtual ~BinaryFileSource();
   
   uint32_t Get( void* pData, uint32_t requestedBytes );
   void Clear();

};
#endif //CLASS_BinaryFileSource




