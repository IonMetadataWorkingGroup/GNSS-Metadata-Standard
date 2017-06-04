/**
 * File: Duration.cpp
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

#include <GnssMetadata/Duration.h>
#include <stdio.h>
using namespace GnssMetadata;

#if !defined (_WIN32) && !defined (_WIN64)
    #define _snprintf snprintf
#endif

/**
 *  Returns a string representation of the object.
 *  
 */
IonString Duration::toString( const IonString & sFormat ) const
{
	const char* szFormat[]={"sec.", "msec.", "usec.", "nsec.", "psec."};
	char buff[255];

	const IonString& sfmt = (sFormat == DefaultFormat) ? "%0.3lf %s" : sFormat;
	_snprintf( buff, sizeof(buff), sfmt.c_str(), _value, szFormat[_format]);
	return IonString(buff);	
}

