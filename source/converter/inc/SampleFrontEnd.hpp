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
#include "SampleFrontEnd.h"

template<typename sample_base_t>
const SampleSource* SampleFrontEnd<sample_base_t>::GetSource(const std::string sinkName) const
{
	std::map<std::string, std::pair<SampleSink*, SampleStreamInfo*>>::const_iterator mit = this->mSampleSinks.find(sinkName);

	if (mit == this->mSampleSinks.end())
	{
		printf("Error: cannot find sample source!\n");
		return NULL;
	}

	const SampleSource* sampleSource = dynamic_cast<const SampleSource*>(mit->second.first);

	return sampleSource;
}

template<typename sample_base_t>
const SampleStreamInfo* SampleFrontEnd<sample_base_t>::GetSourceInfo(const std::string sinkName) const
{
	std::map<std::string, std::pair<SampleSink*, SampleStreamInfo*>>::const_iterator mit = this->mSampleSinks.find(sinkName);

	if (mit == this->mSampleSinks.end())
	{
		printf("Error: cannot find sample source!\n");
		return NULL;
	}

	return mit->second.second;
}

template<typename sample_base_t>
std::map<std::string, std::pair<const SampleSource*, const SampleStreamInfo*> > SampleFrontEnd<sample_base_t>::GetSources() const
{
	const SampleSource* pSampleBuff;
	std::map<std::string, std::pair<const SampleSource*, const SampleStreamInfo*> > sourceMap;

	for (std::map<std::string, std::pair<SampleSink*, SampleStreamInfo*>>::const_iterator mit = this->mSampleSinks.begin(); mit != this->mSampleSinks.end();
	        mit++)
	{
		pSampleBuff = dynamic_cast<const SampleSource*>(mit->second.first);
		sourceMap[mit->first] = std::make_pair(pSampleBuff, mit->second.second);
	}

	return sourceMap;
}

template<typename sample_base_t>
void SampleFrontEnd<sample_base_t>::Clear()
{
	// temporary pointer
	SampleBuffer<sample_base_t>* pSampleBuff;

	for (std::map<std::string, std::pair<SampleSink*, SampleStreamInfo*>>::iterator mit = this->mSampleSinks.begin(); mit != this->mSampleSinks.end(); mit++)
	{
		pSampleBuff = dynamic_cast<SampleBuffer<sample_base_t>*>(mit->second.first);
		if (pSampleBuff)
			pSampleBuff->Flush();
	}
}
