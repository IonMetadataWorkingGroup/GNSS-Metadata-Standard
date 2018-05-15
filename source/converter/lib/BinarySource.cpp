/**
 * Author: James T. Curran : jamestcurran@ieee.org
 *
 * Copyright(c) 2018 Institute of Navigation
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

#include "BinarySource.h"

BinarySource::BinarySource():
mIsOpen(false),
mSourcePos(0)
{
   
};

BinarySource::~BinarySource()
{
   
};
   
bool BinarySource::IsOpen() const
{
   return mIsOpen;
};

bool BinarySource::Open(const std::string streamName)
{

   //call the derived class Open()
   mIsOpen = DoOpen(streamName);
   
   return mIsOpen;
};

void BinarySource::Close()
{
   //call the derived class Close()
   DoClose();
   mIsOpen = false;
};

uint32_t BinarySource::Skip(uint32_t bytesToSkip)
{
   return Get(NULL,bytesToSkip);
}

uint64_t BinarySource::SourcePos()
{
   return mSourcePos;
};
