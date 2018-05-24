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

#include "BinaryFileSink.h"

BinaryFileSink::BinaryFileSink():
mBinfile(NULL)
{
   
}

BinaryFileSink::BinaryFileSink(const std::string filename)
{
   Open(filename);
}

BinaryFileSink::~BinaryFileSink()
{
   Close();
}

bool BinaryFileSink::DoOpen(const std::string streamName)
{
   
   mBinfile = new std::ofstream;
   mBinfile->open( streamName, std::ios::binary );
   
   mIsOpen = mBinfile->is_open();
   
   return mIsOpen;
}

void BinaryFileSink::DoClose()
{
   if( mBinfile != NULL)
   {
      mBinfile->close();
      delete mBinfile;
      mBinfile = NULL;
   }
   
}

void BinaryFileSink::Flush()
{
   if( mBinfile != NULL)
   {
      mBinfile->flush();
   }
   
}

uint32_t BinaryFileSink::Put( void* pData, uint32_t numBytes )
{
   if( !mIsOpen )
   {
      return 0;
   }
   
   mBinfile->write( reinterpret_cast<char*>(pData), numBytes);
   
   return (mBinfile->good() ? numBytes : 0);
}






