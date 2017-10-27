/**
 * File: BaseTypes.h
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

#ifndef BASETYPES_H_H
#define BASETYPES_H_H

#include <string>
#include <stdexcept>


namespace GnssMetadata
{
	/**
	* Standard string type used throughout the API.
	*/
	typedef std::string IonString;

	/**
	 * Base class of all GnssMetadata objects and primitives.
	 */
	class Object
	{
	public:
		static const IonString DefaultFormat;
		virtual ~Object() = 0;
	public:
		/**
		 * Returns a string representation of the object.
		 */
		virtual IonString toString( const IonString& sFormat =  DefaultFormat ) const = 0;
	};
	

	/**
	 * Standard API exception
	 */
	class ApiException : public std::runtime_error
	{
	public:
		enum ErrorType
		{
			Unspecified,
			ArgumentError,
			OutOfRange,
			TranslationError,
			NotImplemented
		};
	public:
		ApiException( const IonString& _What, ErrorType errType = Unspecified )
			: std::runtime_error( _What), _error(errType)
		{
		}

		ApiException( const std::runtime_error& _That) : std::runtime_error( _That),
			_error( Unspecified)
		{
		}
		ErrorType Error() const { return _error;}
	private:
		ErrorType _error;
	};

	/**
	 * Exception thrown whenever an invalid argument encountered.
	 */
	class ArgumentException : public ApiException
	{
	public:
		ArgumentException( const IonString& _What = "Argument Error",
			ErrorType errType = ArgumentError)
			: ApiException( _What, errType)
		{
		}
	};

	/**
	 * Exception thrown whenever an argument is out of range.
	 */
	class OutOfRangeException : public ArgumentException
	{
	public:
		OutOfRangeException( const IonString& _What = "Argument out of range")
			: ArgumentException( _What, OutOfRange)
		{
		}
	};


	/**
	 * Exception thrown whenever a file parsing error occurs.
	 */
	class TranslationException : public ApiException
	{
	public:
		TranslationException( const IonString& _What = "Translation Error", int  iderror = 0)
			: ApiException( _What, TranslationError), XmlError( iderror)
		{
		
		}
		size_t XmlError;
	};

	/**
	 * Exception thrown whenever not implemented code is encountered.
	 */
	class NotImplementedException : public ApiException
	{
	public:
		NotImplementedException( const IonString& _What = "Not Implemented")
			: ApiException( _What, NotImplemented)
		{
		}
	};

	/**
	* Template validates the range of a value. Throwns OutOfRangeException if invalid.
	*/
	template< class ctype> void ValidateRange( const ctype& val, const ctype& min, 
		const ctype& max, const char* const& paramName)
	{
		if( val < min || val > max ) throw GnssMetadata::OutOfRangeException( paramName);
	}


}


#endif
