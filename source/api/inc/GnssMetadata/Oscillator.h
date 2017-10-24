/**
 * File: Oscillator.h
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

#ifndef OSCILLATOR_H_H
#define OSCILLATOR_H_H

#include "AttributedObject.h"
namespace GnssMetadata
{
	class Oscillator : public AttributedObject
	{
	public:
		Oscillator(const IonString& id) : AttributedObject(id) {}

		Oscillator() { }

		Oscillator(const Oscillator& rhs) : AttributedObject(rhs) { }

		const Oscillator& operator=(const Oscillator& rhs)
		{
			if (&rhs == this) return *this;
			AttributedObject::operator =(rhs);
			return *this;
		}
	};
}

#endif
