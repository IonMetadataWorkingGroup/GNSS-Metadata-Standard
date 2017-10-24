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

#ifndef CLASS_LaneInterpreter
#define CLASS_LaneInterpreter

#include <string>
#include <vector>
#include <GnssMetadata/Metadata.h>
#include "SampleSink.h"
#include "BlockInterpreter.h"

class LaneInterpreter
{
protected:
	std::string mFileURL;
	std::vector<BlockInterpreter*> mBlockInterpreters;

public:
	LaneInterpreter(std::string fileURL);
	virtual ~LaneInterpreter();

	virtual void AddBlock(BlockInterpreter* newBlock);
	virtual std::vector<BlockInterpreter*>& Blocks();
	const std::string FileURL() const;
};

#endif //CLASS_LaneInterpreter
