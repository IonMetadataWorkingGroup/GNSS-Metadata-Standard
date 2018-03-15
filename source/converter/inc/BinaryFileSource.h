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

   bool DoOpen(const std::string streamName)
   {
      
      mBinfile = new std::ifstream;
      mBinfile->open( streamName, std::ios::binary );
      
      mIsOpen = mBinfile->is_open();
      

      
      return mIsOpen;
   };
   
   void DoClose()
   {
      if( mBinfile != NULL)
      {
         mBinfile->close();
         delete mBinfile;
         mBinfile = NULL;
      }

   };
   
   bool Load()
   {
      if( !mIsOpen )
      {
         return false;
      }
      //read the data
      mStartBuffer = mData.begin();
      mBinfile->read( reinterpret_cast<char*>(&(*mStartBuffer)) , BinaryFileSource_READ_SIZE);
      mEndBuffer = mStartBuffer + mBinfile->gcount();
      
      //make sure that we have actually loaded something (we may have reached eof)
      return !(mStartBuffer == mEndBuffer);
   }

public:
   BinaryFileSource():
   mBinfile(NULL)
   {};
   
   BinaryFileSource(const std::string filename)
   {
      Open(filename);
   };
   
   virtual ~BinaryFileSource()
   {
      Close();
   }
   

   
};
#endif //CLASS_BinaryFileSource




