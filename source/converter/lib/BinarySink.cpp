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

#include "BinarySink.h"

BinarySink::BinarySink():
mIsOpen(false)
{
   
};

BinarySink::~BinarySink()
{
   
};
   
bool BinarySink::IsOpen() const
{
   return mIsOpen;
};

bool BinarySink::Open(const std::string streamName)
{

   //call the derived class Open()
   mIsOpen = DoOpen(streamName);
   
   return mIsOpen;
};

void BinarySink::Close()
{
   //call the derived class Close()
   Flush();
   DoClose();
   mIsOpen = false;
};


