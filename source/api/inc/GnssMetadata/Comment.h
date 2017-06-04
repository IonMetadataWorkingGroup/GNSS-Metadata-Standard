/**
 * File: Comment.h
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

#ifndef COMMENT_H_H
#define COMMENT_H_H

#include "BaseTypes.h"
#include <list>

namespace GnssMetadata
{
	/**
	* Class defines a comment attribute for GNSS metadata.
	*/
	class Comment: public Object
	{
		
	public:
		enum CommentFormat
		{
			html,
			text
		};
	public:
		/**
		 * Standard constructor.
		 */
		Comment( const IonString& value, CommentFormat format)
			: _format( format), _value( value)
		{
			
		}

		Comment( const Comment& rhs)
			: _format( rhs._format), _value( rhs._value)
		{}

		/**
		 * Gets the format of the comment.
		 */
		CommentFormat Format( ) const
		{
			return _format;
		}

		/**
		 * Sets the comment value and format.
		 */
		void Value( const IonString& value, const CommentFormat /*format*/ )
		{
			_value = value;
		}

		/**
		 * Gets the comments value.
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
		CommentFormat _format;
		
		/**
		 * The comment string value. 
		 */
		IonString _value;
		
		
	};

	/**
	 * Collection is a list of comments.
	 */
	typedef std::list<Comment> CommentList;
}


#endif
