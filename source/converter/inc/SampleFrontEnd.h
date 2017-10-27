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

#ifndef CLASS_SampleFrontEnd
#define CLASS_SampleFrontEnd

#include "SampleSinkFactory.h"
#include "SampleBuffer.h"
#include "SampleConverter.h"

template<typename sample_base_t>
class SampleFrontEnd : public SampleSinkFactory<SampleBuffer<sample_base_t> >, public SampleConverter
{

public:

	typedef std::map<std::string, std::pair<const SampleSource*, const SampleStreamInfo*> > taggedSampleStreamWithInfo;

	SampleFrontEnd()
			: SampleConverter(this)
	{
	}

	// return a SampelSource by name
	const SampleSource* GetSource(const std::string sinkName) const;
	const SampleStreamInfo* GetSourceInfo(const std::string sinkName) const;
	//
	std::map<std::string, std::pair<const SampleSource*, const SampleStreamInfo*> > GetSources() const;

	// clear buffers corresponding to all SampleSources
	// simultanious clear of all sources will keep sample data aligned
	void Clear();

};

#include "SampleFrontEnd.hpp"

#endif //CLASS_SampleFrontEnd
