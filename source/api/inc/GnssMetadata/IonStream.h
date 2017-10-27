/**
 * File: IonStream.h
 * Author: M.B. Mathews
 *
 * Copyright(c) 2014 Institute of Navigation
 * http://www.ion.org
 *
 * This Metadata API is free software; you can redistribute it and/or
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

#ifndef STREAM_H_H
#define STREAM_H_H

#include "AttributedObject.h"
#include "Band.h"
#include "Duration.h"
#include "BaseTypes.h"
#include <list>

namespace GnssMetadata
{
	/**
	 * A stream is defined as a series of binary values that are derived from samples by multiple channels packed into a specified frame and subframe format.
	 */
	class IonStream : public AttributedObject
	{

	public:
		enum StreamAlignment
		{
			Left,
			Right,
			Undefined
		};

		enum StreamShift
		{
			shiftLeft,
			shiftRight,
			shiftUndefined
		};

		enum SampleFormat
		{
			IF,
			IFn,
			IQ,
			IQn,
			InQ,
			InQn,
			QI,
			QIn,
			QnI,
			QnIn,
			//specialized SampleFormats (include native encoder types)
			Int8IQ
		};

		IonStream(const IonString& id = "", bool bIsReference = false)
				: AttributedObject(id, bIsReference), _alignment(Undefined), _shift(shiftUndefined), _format(IQ),
				  _packedbits(0), _quantization(8), _rateFactor(1)
		{}

		IonStream(const IonStream& rhs)
				: AttributedObject(rhs),
				  _alignment(rhs._alignment),
				  _shift(rhs._shift),
				  _encoding(rhs._encoding),
				  _format(rhs._format), _packedbits(rhs._packedbits),
				  _quantization(rhs._quantization), _rateFactor(rhs._rateFactor),
				  _bandlist(rhs._bandlist)
		{}

		const IonStream& operator=(const IonStream& rhs)
		{
			if (&rhs == this) return *this;
			AttributedObject::operator =(rhs);
			_alignment = rhs._alignment;
			_shift = rhs._shift;
			_encoding = rhs._encoding;
			_format = rhs._format;
			_packedbits = rhs._packedbits;
			_quantization = rhs._quantization;
			_rateFactor = rhs._rateFactor;
			_bandlist = rhs._bandlist;

			return *this;
		}

		StreamAlignment Alignment() const { return _alignment; }
		void Alignment(const StreamAlignment alignment) { _alignment = alignment; }

		IonString Encoding() const { return _encoding; }
		void Encoding(const IonString& encoding) { _encoding = encoding; }

		SampleFormat Format() const { return _format; }
		void Format(const SampleFormat format) { _format = format; }

		void Packedbits(const size_t packedbits) { _packedbits = packedbits; }
		size_t Packedbits() const { return _packedbits; }

		size_t Quantization() const { return _quantization; }
		void Quantization(const size_t quantization) { _quantization = quantization; }

		void Shift(const StreamShift shift) { _shift = shift; }
		StreamShift Shift() const { return _shift; }

		size_t RateFactor() const { return _rateFactor; }
		void RateFactor(const size_t rateFactor) { _rateFactor = rateFactor; }

		const GnssMetadata::BandList& Bands() const { return _bandlist; }
		GnssMetadata::BandList& Bands() { return _bandlist; }

		/**
		 *  Returns a string representation of the object.
		 */
		virtual IonString toString(const IonString & sFormat = DefaultFormat) const;

		/**
		 * Virtual function traverses collections of attributed objects looking for object with the
		 * specified id.  Returns the count of objects found.
		 */
		virtual size_t FindObject(SearchItem::List& listResults,
		        const IonString& sid, const AttributedObject& rparent, bool bExcludeReference = true, int nDepth = -1) const;

	private:
		StreamAlignment _alignment;

		StreamShift _shift;

		IonString _encoding;

		SampleFormat _format;

		/**
		 * The total number of bits per sample.
		 */
		size_t _packedbits;

		size_t _quantization;

		/**
		 * If the rate factor (N) is greater than one, there will be N samples of the stream included per base rate period.
		 */
		size_t _rateFactor;

		GnssMetadata::BandList _bandlist;
	};
	typedef std::list<IonStream> StreamList;
}

#endif
