/**
 * File: Position.h
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

#ifndef POSITION_H_H
#define POSITION_H_H

#include "BaseTypes.h"

namespace GnssMetadata
{
	/**
	 * Class represents the Latitude, Longitude, and height for a position.
	 */
	class Position: public Object
	{
		
	public:
		Position( double lat, double lon, double height) 
			: _latitude(lat), _longitude(lon), _height( height)
		{}
	
		Position() 
			: _latitude(0.0), _longitude(0.0), _height( 0.0)
		{}

		Position(const Position& rhs) 
			: _latitude(rhs._latitude), _longitude(rhs._longitude), _height( rhs._height)
		{}

        /**
         * Returns true if is defined, meaning non-zero value.
         */
        bool IsDefined() const;

		/**
		 * Sets the latitude in meters.
		 */
		void Latitude( const double latitude )
		{
			ValidateRange<double>( latitude, -90, 90,"Latitude");
			_latitude = latitude;
		}

		/**
		 * Gets the latitude in meters.
		 */
		double Latitude( ) const
		{
			return _latitude;
		}

		/**
		 * Sets the longitude in meters.
		 */
		void Longitude( const double longitude )
		{
			ValidateRange<double>( longitude, -360, 360,"Longitude");
			_longitude = longitude;
		}

		/**
		 * Gets the longitude in meters.
		 */
		double Longitude( ) const
		{
			return _longitude;
		}

		/**
		 * Sets the height in meters.  Typically above the geoid.
		 */
		void Height( const double height )
		{
			ValidateRange<double>( height, -5000, 50e6,"Latitude");
			_height = height;
		}

		/**
		 * Gets the height in meters.
		 */
		double Height( ) const
		{
			return _height;
		}


		/**
		 * Returns a string representation of the object.
		 */
		virtual IonString toString( const IonString& sFormat =  DefaultFormat ) const;
		
	private:
		
		/**
		 * Latitude in degrees.
		 */
		double _latitude;
		
		/**
		 * Longitude in degrees.
		 */
		double _longitude;
		
		/**
		 * Height in meters
		 */
		double _height;		
	};
	
}


#endif
