/**
 * File: Lane.h
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

#ifndef LANE_H_H
#define LANE_H_H

#include "BaseTypes.h"
#include "Session.h"
#include "System.h"
#include "Block.h"
#include "AttributedObject.h"

namespace GnssMetadata
{
	/**
	 * Class defines a Lane configuration of file format and equipment configuration.
	 */
	class Lane : public AttributedObject
	{
	public:
		struct BandSource
		{
			BandSource() {}
			BandSource(IonString sidBand, IonString sidSource) : idBand(sidBand), idSource(sidSource) {}
			IonString idBand;
			IonString idSource;
		};
		typedef std::list<BandSource> BandSourceList;

	public:
		/**
		 * Default constructor for the lane.
		 */
		Lane(const IonString& id = "", bool bIsReference = false) : AttributedObject(id, bIsReference) {}

		Lane(const Lane& rhs)
				: AttributedObject(rhs),
				  _sessionlist(rhs._sessionlist),
				  _systemlist(rhs._systemlist),
				  _blocklist(rhs._blocklist),
				  _bandsources(rhs._bandsources)
		{}

		const Lane& operator=(const Lane& rhs)
		{
			if (&rhs == this) return *this;
			AttributedObject::operator =(rhs);
			_sessionlist = rhs._sessionlist;
			_systemlist = rhs._systemlist;
			_blocklist = rhs._blocklist;
			_bandsources = rhs._bandsources;
			return *this;
		}

		bool operator==(const Lane rhs) const { return Id() == rhs.Id(); }

		const GnssMetadata::SessionList& Sessions() const { return _sessionlist; }
		GnssMetadata::SessionList& Sessions() { return _sessionlist; }

		const GnssMetadata::SystemList& Systems() const { return _systemlist; }
		GnssMetadata::SystemList& Systems() { return _systemlist; }

		const GnssMetadata::BlockList& Blocks() const { return _blocklist; }
		GnssMetadata::BlockList& Blocks() { return _blocklist; }

		const BandSourceList& BandSources() const { return _bandsources; }
		BandSourceList& BandSources() { return _bandsources; }

		/**
		 * Adds a band source definition to the lane.
		 */
		void AddBandSource(const Band& band, const Source& source, bool bValidate = false)
		{
			AddBandSource(band.Id(), source.Id(), bValidate);
		}

		/**
		 * Adds a band source definition to the lane.
		 */
		void AddBandSource(IonString sidBand, IonString sidSource, bool bValidate = false)
		{
			if (bValidate)
			{
				//TODO validate the existence of sidBand and sidSource objects
				//within the lane definition.
			}

			BandSource bsrc(sidBand, sidSource);
			_bandsources.push_back(bsrc);
		}

		/**
		 * Returns a string representation of the object.
		 */
		virtual IonString toString(const IonString & sFormat = DefaultFormat) const;

		/**
		 * Virtual function traverses collections of attributed objects looking for object with the
		 * specified id. Returns the count of objects found.
		 */
		virtual size_t FindObject(SearchItem::List& listResults,
		        const IonString& sid, const AttributedObject& rparent, bool bExcludeReference = true, int nDepth = -1) const;

		GnssMetadata::Block** blockArray;
		int blockCount;

	private:
		GnssMetadata::SessionList _sessionlist;
		GnssMetadata::SystemList _systemlist;
		GnssMetadata::BlockList _blocklist;
		BandSourceList _bandsources;
	};

	typedef std::list<Lane> LaneList;
}

#endif
