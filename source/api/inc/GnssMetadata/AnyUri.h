 /**
 * File: AnyUri.h
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

#ifndef ANYURI_H_H
#define ANYURI_H_H

#include "BaseTypes.h"
#include <list>

namespace GnssMetadata
{
	/**
	 * Class represents an XML any URI type.  
	 */
	class AnyUri: public Object
	{
		
	public:
		AnyUri( const IonString& value)
			: _value( value)
		{
		}
		AnyUri() {}

		AnyUri( const AnyUri& rhs)
			: _value( rhs._value)
		{
		}

		/**
		 * Returns true if the URI value is defined.
		 */
		bool IsDefined() const { return _value.length() > 0;}

		/**
		 * Sets the URI Value. 
		 */
		void Value( const IonString& value )
		{
			_value = value;
		}

		/**
		 * Gets the URI Value. 
		 */
		IonString Value( ) const
		{
			return _value;
		}

	/**
		 *  Returns a string representation of the object.
		 *  
		 */
		virtual IonString toString( const IonString & sFormat = DefaultFormat ) const;
		
	private:
		/**
		 * The URI Value. 
		 */
		IonString _value;
		
		
	};

	/**
	 * Container is a list of AnyUri objects
	 */
	typedef std::list<AnyUri> AnyUriList;
}


#endif
