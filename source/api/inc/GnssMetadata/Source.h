/**
 * File: Source.h
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

#ifndef SOURCE_H_H
#define SOURCE_H_H

#include "BaseTypes.h"
#include "AttributedObject.h"
#include "Position.h"
#include "Orientation.h"

namespace GnssMetadata
{
	/**
	 * Class defines a source.
	 */
	class Source : public AttributedObject
	{
	public:
		enum SourcePolarization
		{
			UndefinedPolarization,
			RHCP,
			LHCP,
			Linear,
			Horizontal,
			Vertical
		};

		enum SourceType
		{
			UndefinedType,
			Patch,
			Dipole,
			Helical,
			Quadrifilar,
			Simulator
		};

		/**
		 * Default constructor.
		 */
		Source(SourceType type = UndefinedType, SourcePolarization polarization = UndefinedPolarization, const IonString& id = "", bool bIsReference = false)
				: AttributedObject(id, bIsReference), _type(type), _polarization(polarization)
		{}

		Source(const Source& rhs)
				: AttributedObject(rhs),
				  _type(rhs._type),
				  _polarization(rhs._polarization),
				  _origin(rhs._origin),
				  _orientation(rhs._orientation),
				  _idCluster(rhs._idCluster)
		{}

		const Source& operator=(const Source& rhs)
		{
			if (&rhs == this) return *this;
			AttributedObject::operator =(rhs);
			_type = rhs._type;
			_polarization = rhs._polarization;
			_origin = rhs._origin;
			_orientation = rhs._orientation;
			_idCluster = rhs._idCluster;
			return *this;
		}

		SourceType Type() const { return _type; }
		void Type(const SourceType type) { _type = type; }

		SourcePolarization Polarization() const { return _polarization; }
		void Polarization(const SourcePolarization polarization) { _polarization = polarization; }

		const GnssMetadata::Position& Origin() const { return _origin; }
		GnssMetadata::Position& Origin() { return _origin; }
		void Origin(const GnssMetadata::Position& origin) { _origin = origin; }

		const GnssMetadata::Orientation& Orientation() const { return _orientation; }
		GnssMetadata::Orientation& Orientation() { return _orientation; }
		void Orientation(const GnssMetadata::Orientation& orientation) { _orientation = orientation; }

		IonString IdCluster() const { return _idCluster; }
		void IdCluster(const IonString& id) { _idCluster = id; }

		/**
		 * Returns a string representation of the object.
		 */
		virtual IonString toString(const IonString & sFormat = DefaultFormat) const;

	private:
		SourceType _type;
		SourcePolarization _polarization;
		GnssMetadata::Position _origin;
		GnssMetadata::Orientation _orientation;
		IonString _idCluster;
	};

	typedef std::list<Source> SourceList;
}

#endif
