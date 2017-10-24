/**
 * File: Orientation.h
 * Author: James T Curran
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

#ifndef ORIENTATION_H_H
#define ORIENTATION_H_H

#include "BaseTypes.h"

namespace GnssMetadata
{
	/**
	 * Class represents the angles Alpha, Beta and Gamma for an orientation.
	 */
	class Orientation : public Object
	{

	public:
		Orientation(double alpha, double beta, double gamma) : _alpha(alpha), _beta(beta), _gamma(gamma) {}

		Orientation() : _alpha(0.0), _beta(0.0), _gamma(0.0) {}

		Orientation(const Orientation& rhs) : _alpha(rhs._alpha), _beta(rhs._beta), _gamma(rhs._gamma) {}

		/**
		 * Returns true if is defined, meaning non-zero value.
		 */
		bool IsDefined() const;

		/**
		 * Sets Alpha in degrees
		 */
		void Alpha(const double alpha)
		{
			ValidateRange<double>(alpha, 0, 360, "alpha");
			_alpha = alpha;
		}

		/**
		 * Gets Alpha in degrees
		 */
		double Alpha() const { return _alpha; }

		/**
		 * Sets Beta in degrees
		 */
		void Beta(const double beta)
		{
			ValidateRange<double>(beta, 0, 360, "beta");
			_beta = beta;
		}

		/**
		 * Gets Beta in degrees
		 */
		double Beta() const { return _beta; }

		/**
		 * Sets Gamma in degrees
		 */
		void Gamma(const double gamma)
		{
			ValidateRange<double>(gamma, 0, 360, "gamma");
			_gamma = gamma;
		}

		/**
		 * Gets Gamma in degrees
		 */
		double Gamma() const { return _gamma; }

		/**
		 * Returns a string representation of the object.
		 */
		virtual IonString toString(const IonString& sFormat = DefaultFormat) const;

	private:

		/**
		 * Alpha in degrees.
		 */
		double _alpha;

		/**
		 * Beta in degrees.
		 */
		double _beta;

		/**
		 * Gamma in degrees.
		 */
		double _gamma;
	};
}

#endif
