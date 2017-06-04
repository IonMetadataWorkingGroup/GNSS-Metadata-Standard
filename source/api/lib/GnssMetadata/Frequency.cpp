/**
 * File: Frequency.cpp
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


#include <GnssMetadata/Frequency.h>
#include <string.h>
#include <stdio.h>
using namespace GnssMetadata;

#if !defined (_WIN32) && !defined (_WIN64)
    #define _snprintf snprintf
#endif

/**
 * Returns a string representation of the object.
 */
IonString Frequency::toString( const IonString& sFormat ) const
{
	const char* szFormat[] = { "Hz", "kHz", "MHz", "GHz", "Ratio"};

	char buff[256];
	switch (_format)
	{
	case Ratio:
	{
		const IonString& fmt = (sFormat == DefaultFormat) ? "%ld/%ld" : sFormat;
		_snprintf(buff, sizeof(buff), fmt.c_str(), _value.ratioVal.numerator, _value.ratioVal.denominator);
	}
		break;
	default:
	{
		const IonString& fmt = (sFormat == DefaultFormat) ? "%0.3lf %s" : sFormat;
		_snprintf(buff, sizeof(buff), fmt.c_str(), _value.doubleVal, szFormat[_format]);
	}
		break;
	}
	return IonString( buff);
}



/**
 * Returns a double in Hertz representation of the frequency value.
 */
double Frequency::toHertz( void ) const
{
	double unit[] = { 1.0, 1.0e3, 1.e6, 1.e9, 1.0};
	double val;

	switch (_format)
	{
	case Ratio:
	{
		val=unit[int(_format)]*double(_value.ratioVal.numerator)/double(_value.ratioVal.denominator);
	}
		break;
	default:
	{
		val=unit[int(_format)]*_value.doubleVal;
	}
		break;
	}
	return val;
}
