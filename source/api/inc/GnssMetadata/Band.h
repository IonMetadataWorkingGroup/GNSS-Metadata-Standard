/**
 * File: Band.h
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

#ifndef BAND_H_H
#define BAND_H_H

#include "AttributedObject.h"
#include "Frequency.h"
#include "Duration.h"
#include "BaseTypes.h"
#include <list>

namespace GnssMetadata
{
	/**
	 * Band defines a finite spectrum of bandwidth that has been translated and processed in some manner resulting in a translated frequency output. Formerly known as band.
	 */
	class Band : public AttributedObject
	{

	public:
		Band(const IonString& id) : AttributedObject(id), _inverted(false) {}
		Band() : _inverted(false) { }

		Band(const Band& rhs)
				: AttributedObject(rhs),
				        _centerFrequency(rhs._centerFrequency),
				        _translatedFrequency(rhs._translatedFrequency),
				        _delayBias(rhs._delayBias),
				        _inverted(rhs._inverted),
				        _bandwidth(rhs._bandwidth)
		{}

		const Band& operator=(const Band& rhs)
		{
			if (&rhs == this) return *this;
			AttributedObject::operator =(rhs);
			_centerFrequency = rhs._centerFrequency;
			_translatedFrequency = rhs._translatedFrequency;
			_delayBias = rhs._delayBias;
			_inverted = rhs._inverted;
			_bandwidth = rhs._bandwidth;
			return *this;
		}

		const Frequency& CenterFrequency() const { return _centerFrequency; }
		Frequency& CenterFrequency() { return _centerFrequency; }
		void CenterFrequency(const Frequency& centerFrequency) { _centerFrequency = centerFrequency; }

		const Frequency& TranslatedFrequency() const { return _translatedFrequency; }
		Frequency& TranslatedFrequency() { return _translatedFrequency; }
		void TranslatedFrequency(const Frequency& translatedFrequency) { _translatedFrequency = translatedFrequency; }

		const Duration& DelayBias() const { return _delayBias; }
		Duration& DelayBias() { return _delayBias; }
		void DelayBias(const Duration& delayBias) { _delayBias = delayBias; }

		bool Inverted() const { return _inverted; }
		void Inverted(const bool inverted) { _inverted = inverted; }

		const Frequency& Bandwidth() const { return _bandwidth; }
		Frequency& Bandwidth() { return _bandwidth; }
		void Bandwidth(const Frequency& bandwidth) { _bandwidth = bandwidth; }

		/**
		 *  Returns a string representation of the object.
		 *
		 */
		virtual IonString toString(const IonString & sFormat = DefaultFormat) const;

	private:
		Frequency _centerFrequency;
		Frequency _translatedFrequency;
		Duration _delayBias;

		/**
		 * True if spectrum is inverted. Default is false.
		 */
		bool _inverted;

		Frequency _bandwidth;
	};

	typedef std::list<Band> BandList;
}

#endif
