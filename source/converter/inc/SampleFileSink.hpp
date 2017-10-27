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

#include "SampleFileSink.h"

template<typename sample_base_t>
SampleFileSink<sample_base_t>::SampleFileSink(std::string fileName, unsigned int numSamplesPerBuffer)
		:
		        mSampleBuffer(nullptr),
		        mBufferSize(0),
		        mIndexOfNextSample(0),
		        mRequestedNumberOfSamplesPerBuffer(numSamplesPerBuffer),
		        mFileName(fileName)
{
	Open();
}

template<typename sample_base_t>
SampleFileSink<sample_base_t>::~SampleFileSink(void)
{
	// flush the stream
	Flush();

	// close the stream, if it is not done so already.
	Close();
}

template<typename sample_base_t>
bool SampleFileSink<sample_base_t>::Open()
{
	// default to closed
	this->mIsOpen = false;

	// try to open the file
	mSampleFile.open(mFileName.c_str(), std::ios::out | std::ios::binary);

	if (!mSampleFile.is_open())
	{
		printf("Cannot createSampleFileSink - file open fail.\n");
		//return Ctrl::eFailure;
	}

	// choose buffer size, making sure its size in bytes is an integer multiple of BASE_BUFFER_SIZE_IN_BYTES
	unsigned int numBytesPerBuffer = mRequestedNumberOfSamplesPerBuffer;
	numBytesPerBuffer = numBytesPerBuffer - numBytesPerBuffer % BASE_BUFFER_SIZE_IN_BYTES;
	numBytesPerBuffer = (numBytesPerBuffer < BASE_BUFFER_SIZE_IN_BYTES ? BASE_BUFFER_SIZE_IN_BYTES : numBytesPerBuffer);
	mBufferSize = numBytesPerBuffer;

	// now allocate the buffer
	mSampleBuffer = new (std::nothrow) sample_base_t[mBufferSize];
	if (mSampleBuffer == nullptr)
	{
		printf("Cannot create SampleFileSink  - cannot allocate enough memory");
	}
	else
	{
		this->mIsOpen = true;
	}
	return this->mIsOpen;
}

template<typename sample_base_t>
void SampleFileSink<sample_base_t>::Close()
{
	this->mIsOpen = false;

	if (mSampleBuffer != nullptr)
	{
		delete[] reinterpret_cast<char*>(mSampleBuffer);
		mSampleBuffer = nullptr;
	}

	mSampleFile.close();
	mSampleFile.clear();
}

template<typename sample_base_t>
void SampleFileSink<sample_base_t>::DoAddSample(sample_base_t x)
{
	if (!this->mIsOpen) return;

	mSampleBuffer[mIndexOfNextSample] = x;

	mIndexOfNextSample++;

	if (mIndexOfNextSample == mBufferSize) Flush();
}

template<typename sample_base_t>
void SampleFileSink<sample_base_t>::DoAddSample(sample_base_t x, sample_base_t y)
{
	if (!this->mIsOpen) return;

	mSampleBuffer[mIndexOfNextSample] = x;
	mIndexOfNextSample++;
	//assume that we have an even buffer size
	mSampleBuffer[mIndexOfNextSample] = y;
	mIndexOfNextSample++;

	if (mIndexOfNextSample == mBufferSize) Flush();
}

template<typename sample_base_t>
void SampleFileSink<sample_base_t>::Flush()
{
	if (!this->mIsOpen) return;

	mSampleFile.write((char*)mSampleBuffer, mIndexOfNextSample * sizeof(sample_base_t));
	mIndexOfNextSample = 0;
}
