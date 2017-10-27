/**
 * File: Chunk.h
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

#ifndef CHUNK_H_H
#define CHUNK_H_H

#include "BaseTypes.h"
#include "Lump.h"

namespace GnssMetadata
{
	/**
	 * Chunk defines the packing of lumps.
	 */
	class Chunk : public AttributedObject
	{
	public:
		enum WordEndian
		{
			Big,
			Little,
			Undefined

		};

		enum WordPadding
		{
			None,
			Head,
			Tail
		};

		enum WordShift
		{
			Left,
			Right
		};

	public:
		Chunk(const IonString& id = "", bool bIsReference = false)
				: AttributedObject(id, bIsReference), _countWords(0), _sizeWord(0), _endian(Undefined), _padding(None), _shift(Left)
		{}

		Chunk(const Chunk& rhs)
				: AttributedObject(rhs), _countWords(rhs._countWords), _sizeWord(rhs._sizeWord), _endian(rhs._endian),
				        _padding(rhs._padding), _shift(rhs._shift), _lumplist(rhs._lumplist)
		{}

		const Chunk& operator=(const Chunk& rhs)
		{
			if (&rhs == this) return *this;
			AttributedObject::operator =(rhs);

			_countWords = rhs._countWords;
			_sizeWord = rhs._sizeWord;
			_endian = rhs._endian;
			_padding = rhs._padding;
			_shift = rhs._shift;
			_lumplist = rhs._lumplist;
			return *this;
		}

		/**
		 * Returns true if Chunk state is not in default configuration.
		 */
		bool IsDefined() const { return _countWords > 1 && _sizeWord > 0 && _lumplist.size() > 0; }

		/**
		 * Gets the count of Words in the chunk.
		 */
		size_t CountWords() const { return _countWords; }

		/**
		 * Sets the count of Words in the chunk.
		 */
		void CountWords(const size_t count) { _countWords = count; }

		/**
		 * Gets the size of Word in bytes.
		 */
		size_t SizeWord() const { return _sizeWord; }

		/**
		 * Sets the size of Word in bytes.
		 */
		void SizeWord(const size_t sizeWord) { _sizeWord = sizeWord; }

		/**
		 * Gets the endian ordering of the words.
		 */
		WordEndian Endian() const { return _endian; }

		/**
		 * Sets the endian ordering of the words.
		 */
		void Endian(const WordEndian endian) { _endian = endian; }

		/**
		 * Gets the word padding.
		 */
		WordPadding Padding() const { return _padding; }

		/**
		 * Sets the word padding.
		 */
		void Padding(const WordPadding bits) { _padding = bits; }

		/**
		 * Gets the word shift.
		 */
		WordShift Shift() const { return _shift; }

		/**
		 * Sets the word shift.
		 */
		void Shift(const WordShift shift) { _shift = shift; }

		const GnssMetadata::LumpList& Lumps() const { return _lumplist; }
		GnssMetadata::LumpList& Lumps() { return _lumplist; }

		/**
		 * Returns a string representation of the object.
		 */
		virtual IonString toString(const IonString & sFormat = DefaultFormat) const;

		/**
		 * Virtual function traverses collections of attributed objects looking for object with the
		 * specified id.  Returns the count of objects found.
		 */
		virtual size_t FindObject(SearchItem::List& listResults, const IonString& sid, const AttributedObject& rparent, bool bExcludeReference = true, int nDepth = -1) const;

	private:
		size_t _countWords;
		size_t _sizeWord;
		WordEndian _endian;
		WordPadding _padding;
		WordShift _shift;
		GnssMetadata::LumpList _lumplist;
	};

	typedef std::list<Chunk> ChunkList;
}

#endif
