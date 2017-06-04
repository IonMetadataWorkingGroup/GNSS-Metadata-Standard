/**
 * File: Cluster.h
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

#ifndef CLUSTER_H_H
#define CLUSTER_H_H

#include "BaseTypes.h"
#include "AttributedObject.h"
#include "Position.h"
#include "Orientation.h"

namespace GnssMetadata
{
	/**
	 * Class an entenna cluster array.
	 */
	class Cluster: public AttributedObject
	{
	public:
		/**
		 * Default constructor.
		 */
		Cluster( const IonString& id = "", bool bIsReference = false)
			: AttributedObject( id, bIsReference)
		{
			
		}

		Cluster( const Cluster& rhs) :
			AttributedObject(rhs),
			_position(rhs._position),
         _orientation(rhs._orientation),
			_vendor(rhs._vendor),
			_model(rhs._model),
			_serial(rhs._serial)
		{
			
		}

		const Cluster& operator=( const Cluster& rhs)
		{
			if( &rhs == this)
				return *this;
			AttributedObject::operator =(rhs);
			_position = rhs._position;
         _orientation = rhs._orientation;
			_vendor = rhs._vendor;
			_model = rhs._model;
			_serial = rhs._serial;
			return *this;
		}


		IonString Model( ) const
		{
			return _model;
		}
		void Model( const IonString& model )
		{
			_model = model;
		}
		IonString Vendor( ) const
		{
			return _vendor;
		}
		void Vendor( const IonString& vendor )
		{
			_vendor = vendor;
		}
		IonString Serial( ) const
		{
			return _serial;
		}
		void Serial( const IonString& serial)
		{
			_serial = serial;
		}

		const GnssMetadata::Position& Position( ) const
		{
			return _position;
		}
		GnssMetadata::Position& Position( ) 
		{
			return _position;
		}
		void Position( const GnssMetadata::Position& location )
		{
			_position = location;
		}


      const GnssMetadata::Orientation& Orientation() const
		{
         return _orientation;
		}
		GnssMetadata::Orientation& Orientation( ) 
		{
			return _orientation;
		}

		void Orientation( const GnssMetadata::Orientation& orientation )
		{
			_orientation = orientation;
		}

		/**
		 * Returns a string representation of the object.
		 */
		virtual IonString toString( const IonString & sFormat = DefaultFormat ) const;

	private:
		GnssMetadata::Position    _position;
      GnssMetadata::Orientation _orientation;
		IonString _vendor;
		IonString _model;
		IonString _serial;
	};

	typedef std::list<Cluster> ClusterList;	
	
}


#endif
