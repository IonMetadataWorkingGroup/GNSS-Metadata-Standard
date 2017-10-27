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

#ifndef CLASS_SampleBuffer
#define CLASS_SampleBuffer

#include <vector>
#include <string>
#include <stdint.h>

#include "SampleSink.h"
#include "SampleSource.h"

#define BASE_BUFFER_SIZE 1024 * 1024

template<typename sample_base_t>
class SampleBuffer : public SampleSinkT<sample_base_t>, public SampleSourceT<sample_base_t>
{

protected:
	std::vector<sample_base_t> mSampleBuffer;
	int32_t mBufferSize;
	int32_t mBufferPos;

	bool Open();
	inline void DoAddSample(sample_base_t x);
	inline void DoAddSample(sample_base_t x, sample_base_t y);
	inline uint32_t DoGetSamples(const void** buff) const;

public:
	SampleBuffer(std::string fileName);
	virtual ~SampleBuffer(void);

	void Flush();
	void Close();

};

#include "SampleBuffer.hpp"

#endif // CLASS_SampleBuffer
