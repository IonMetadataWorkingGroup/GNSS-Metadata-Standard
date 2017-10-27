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
#include "SampleSinkFactory.h"

template<typename sample_sink_t>
SampleSinkFactory<sample_sink_t>::SampleSinkFactory()
{
	mSampleSinks.clear();
}

template<typename sample_sink_t>
SampleSinkFactory<sample_sink_t>::~SampleSinkFactory()
{
	for (const auto& it : mSampleSinks)
	{
		delete it.second.first;
		delete it.second.second;
	}
}

template<typename sample_sink_t>
void SampleSinkFactory<sample_sink_t>::TryGet(const std::string sinkName)
{
	// if we don't aleady have a SampleSink for this stream, then create one
	if (mSampleSinks.find(sinkName) == mSampleSinks.end())
	{
		std::string fileName = sinkName + ".dat";
		mSampleSinks[sinkName] = std::make_pair(new sample_sink_t(fileName), new SampleStreamInfo);
	}
}

template<typename sample_sink_t>
SampleSink* SampleSinkFactory<sample_sink_t>::GetSampleSink(const std::string sinkName)
{
	TryGet(sinkName);

	return mSampleSinks[sinkName].first;
}

template<typename sample_sink_t>
SampleStreamInfo* SampleSinkFactory<sample_sink_t>::GetSampleStreamInfo(const std::string sinkName)
{
	TryGet(sinkName);

	return mSampleSinks[sinkName].second;
}
