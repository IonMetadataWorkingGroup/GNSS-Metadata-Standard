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

#include "SampleStatisticsSink.h"

template<typename sample_base_t>
SampleStatisticsSink<sample_base_t>::SampleStatisticsSink(std::string fileName)
		: mFileName(fileName)
{
	Open();
}

template<typename sample_base_t>
SampleStatisticsSink<sample_base_t>::~SampleStatisticsSink(void)
{
	// dump the stream statistics
	Report();

	// close the stream, if it is not done so already.
	Close();
}

template<typename sample_base_t>
bool SampleStatisticsSink<sample_base_t>::Open()
{
	// default to closed
	this->mIsOpen = true;

	mStats.Reset();

	return this->mIsOpen;
}

template<typename sample_base_t>
void SampleStatisticsSink<sample_base_t>::Close()
{
	this->mIsOpen = false;

	mStats.Reset();
}

template<typename sample_base_t>
void SampleStatisticsSink<sample_base_t>::DoAddSample(sample_base_t x)
{
	if (!this->mIsOpen) return;

	mStats.AddSample(static_cast<double>(x));
}

template<typename sample_base_t>
void SampleStatisticsSink<sample_base_t>::DoAddSample(sample_base_t x, sample_base_t y)
{
	if (!this->mIsOpen) return;

	mStats.AddSample(static_cast<double>(x));
	mStats.AddSample(static_cast<double>(y));
}

template<typename sample_base_t>
void SampleStatisticsSink<sample_base_t>::Report()
{
	if (!this->mIsOpen) return;

	printf("Stream: %s\n", mFileName.c_str());
	printf("\tMean:     %f\n", mStats.Mean());
	printf("\tVariance: %f\n", mStats.Variance());
	printf("\n");
}
