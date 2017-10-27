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

#include "LaneInterpreter.h"

std::vector<BlockInterpreter*> mBlockInterpreters;

LaneInterpreter::LaneInterpreter(std::string fileURL)
		: mFileURL(fileURL)
{
	mBlockInterpreters.resize(0);
}

LaneInterpreter::~LaneInterpreter()
{
	for (const BlockInterpreter* i : mBlockInterpreters) delete i;
}

void LaneInterpreter::AddBlock(BlockInterpreter* newBlock)
{
	mBlockInterpreters.push_back(newBlock);
}

std::vector<BlockInterpreter*>& LaneInterpreter::Blocks()
{
	return mBlockInterpreters;
}

const std::string LaneInterpreter::FileURL() const
{
	return mFileURL;
}
