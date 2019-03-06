/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sxyz (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/
#include "ByteConverter.hpp"

#include "MessageBuffer.hpp"

#include <type_traits>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include <assert.h>
#include <list>
#include <map>

// Root of ByteBuffer exception hierarchy
class ByteBufferException : public std::exception
{
public:
	~ByteBufferException() throw() { }

	char const* what() const throw() override { return msg_.c_str(); }

protected:
	std::string & message() throw() { return msg_; }

private:
	std::string msg_;
};

class ByteBufferPositionException : public ByteBufferException
{
public:
	ByteBufferPositionException(bool add, size_t pos, size_t size, size_t valueSize);

	~ByteBufferPositionException() throw() { }
};

class ByteBufferSourceException : public ByteBufferException
{
public:
	ByteBufferSourceException(size_t pos, size_t size, size_t valueSize);

	~ByteBufferSourceException() throw() { }
};

class ByteBuffer
{
public:
	const static size_t DEFAULT_SIZE = 0x1000;

	// constructor
	ByteBuffer() : _rpos(0), _wpos(0)
	{
		_storage.reserve(DEFAULT_SIZE);
	}

	ByteBuffer(size_t reserve) : _rpos(0), _wpos(0)
	{
		_storage.reserve(reserve);
	}

	ByteBuffer(ByteBuffer&& buf) : _rpos(buf._rpos), _wpos(buf._wpos),
								   _storage(std::move(buf._storage)) { }

	ByteBuffer(ByteBuffer const& right) : _rpos(right._rpos), _wpos(right._wpos),
										  _storage(right._storage) { }

	ByteBuffer(MessageBuffer&& buffer);
	ByteBuffer(MessageBuffer &buffer);

	ByteBuffer& operator=(ByteBuffer const& right)
	{
		if (this != &right)
		{
			_rpos = right._rpos;
			_wpos = right._wpos;
			_storage = right._storage;
		}

		return *this;
	}

	virtual ~ByteBuffer() { }

	void clear()
	{
		_storage.clear();
		_rpos = _wpos = 0;
	}

	template <typename T> void append(T value)
	{
		//EndianConvert(value);
		append((uint8_t *)&value, sizeof(value));
	}

	template <typename T> void put(size_t pos, T value)
	{
		static_assert(std::is_fundamental<T>::value, "append(compound)");
		//EndianConvert(value);
		put(pos, (uint8_t *)&value, sizeof(value));
	}

	ByteBuffer &operator<<(uint8_t value)
	{
		append<uint8_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(uint16_t value)
	{
		append<uint16_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(uint32_t value)
	{
		append<uint32_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(uint64_t value)
	{
		append<uint64_t>(value);
		return *this;
	}

	// signed as in 2e complement
	ByteBuffer &operator<<(int8_t value)
	{
		append<int8_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(int16_t value)
	{
		append<int16_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(int32_t value)
	{
		append<int32_t>(value);
		return *this;
	}

	ByteBuffer &operator<<(int64_t value)
	{
		append<int64_t>(value);
		return *this;
	}

	// floating points
	ByteBuffer &operator<<(float value)
	{
		append<float>(value);
		return *this;
	}

	ByteBuffer &operator<<(double value)
	{
		append<double>(value);
		return *this;
	}

	ByteBuffer &operator>>(bool &value)
	{
		value = read<char>() > 0 ? true : false;
		return *this;
	}

	ByteBuffer &operator>>(uint8_t &value)
	{
		value = read<uint8_t>();
		return *this;
	}

	ByteBuffer &operator>>(uint16_t &value)
	{
		value = read<uint16_t>();
		return *this;
	}

	ByteBuffer &operator>>(uint32_t &value)
	{
		value = read<uint32_t>();
		return *this;
	}

	ByteBuffer &operator>>(uint64_t &value)
	{
		value = read<uint64_t>();
		return *this;
	}

	//signed as in 2e complement
	ByteBuffer &operator>>(int8_t &value)
	{
		value = read<int8_t>();
		return *this;
	}

	ByteBuffer &operator>>(int16_t &value)
	{
		value = read<int16_t>();
		return *this;
	}

	ByteBuffer &operator>>(int32_t &value)
	{
		value = read<int32_t>();
		return *this;
	}

	ByteBuffer &operator>>(int64_t &value)
	{
		value = read<int64_t>();
		return *this;
	}

	ByteBuffer &operator>>(float &value)
	{
		value = read<float>();
		if (!std::isfinite(value))
			throw ByteBufferException();
		return *this;
	}

	ByteBuffer &operator>>(double &value)
	{
		value = read<double>();
		if (!std::isfinite(value))
			throw ByteBufferException();
		return *this;
	}

	uint8_t& operator[](size_t const pos)
	{
		if (pos >= size())
			throw ByteBufferPositionException(false, pos, 1, size());
		return _storage[pos];
	}

	uint8_t const& operator[](size_t const pos) const
	{
		if (pos >= size())
			throw ByteBufferPositionException(false, pos, 1, size());
		return _storage[pos];
	}

	size_t rpos() const { return _rpos; }

	size_t rpos(size_t rpos_)
	{
		_rpos = rpos_;
		return _rpos;
	}

	void finish_reading()
	{
		_rpos = wpos();
	}

	size_t wpos() const { return _wpos; }

	size_t wpos(size_t wpos_)
	{
		_wpos = wpos_;
		return _wpos;
	}

	template<typename T>
	void read_skip() { read_skip(sizeof(T)); }

	void read_skip(size_t skip)
	{
		if (_rpos + skip > size())
			throw ByteBufferPositionException(false, _rpos, skip, size());
		_rpos += skip;
	}

	template <typename T> T read()
	{
		T r = read<T>(_rpos);
		_rpos += sizeof(T);
		return r;
	}

	template <typename T> T read(size_t pos) const
	{
		if (pos + sizeof(T) > size())
			throw ByteBufferPositionException(false, pos, sizeof(T), size());
		T val = *((T const*)&_storage[pos]);
		return val;
	}

	void read(char *dest, size_t len)
	{
		if (_rpos  + len > size())
			throw ByteBufferPositionException(false, _rpos, len, size());
		std::memcpy((void *) dest, &_storage[_rpos], len);
		_rpos += len;
	}

	uint8_t* contents()
	{
		if (_storage.empty())
			throw ByteBufferException();
		return _storage.data();
	}

	uint8_t const* contents() const
	{
		if (_storage.empty())
			throw ByteBufferException();
		return _storage.data();
	}

	size_t size() const { return _storage.size(); }
	size_t buf_len() const { return _rpos; }
	bool empty() const { return _storage.empty(); }

	void resize(size_t newsize)
	{
		_storage.resize(newsize, 0);
		_rpos = 0;
		_wpos = size();
	}

	void reserve(size_t ressize)
	{
		if (ressize > size())
			_storage.reserve(ressize);
	}

	void append(const char *src, size_t size)
	{
		return append((const uint8_t *)src, size);
	}

	template<class T>
	void append(const T *src, size_t size)
	{
		return append((const uint8_t *) src, size);
	}

	template<class T, class SubT>
	void append(const T *t, size_t t_size, const SubT *sub_t, int count)
	{
		append((const uint8_t *) t, t_size);
		append((const uint8_t *) sub_t, sizeof(SubT) * count);
		return ;
	}

	void append(const uint8_t *src, size_t cnt)
	{
		if (!cnt)
			throw ByteBufferSourceException(_wpos, size(), cnt);

		if (!src)
			throw ByteBufferSourceException(_wpos, size(), cnt);

		assert(size() < 10000000);

		size_t const newSize = _wpos + cnt;
		if (_storage.capacity() < newSize) // custom memory allocation rules
		{
			if (newSize < 100)
				_storage.reserve(300);
			else if (newSize < 750)
				_storage.reserve(2500);
			else if (newSize < 6000)
				_storage.reserve(10000);
			else
				_storage.reserve(400000);
		}

		if (_storage.size() < newSize)
			_storage.resize(newSize);
		std::memcpy(&_storage[_wpos], src, cnt);
		_wpos = newSize;
	}

	void append(const ByteBuffer& buffer)
	{
		if (buffer.wpos())
			append(buffer.contents(), buffer.wpos());
	}

	void put(size_t pos, const uint8_t *src, size_t cnt)
	{
		if (pos + cnt > size())
			throw ByteBufferPositionException(true, pos, cnt, size());

		if (!src)
			throw ByteBufferSourceException(_wpos, size(), cnt);

		std::memcpy(&_storage[pos], src, cnt);
	}

	void print_storage() const;

	void textlike() const;

	void hexlike() const;

	template<typename SizeT = uint16_t, typename std::enable_if<std::is_integral<SizeT>::value>::type* = nullptr>
	void emplace_size(std::size_t pos = 2)
	{
		_storage.emplace(_storage.begin() + pos, 0);
		_storage.emplace(_storage.begin() + pos + 1, 0);
		put(pos, (uint8_t *) _storage.size(), sizeof(SizeT));
	}

protected:
	size_t _rpos{0}, _wpos{0};
	std::vector<uint8_t> _storage;
};

template<>
inline void ByteBuffer::read_skip<char const*>()
{
	read_skip<char*>();
}

template<>
inline void ByteBuffer::read_skip<std::string>()
{
	read_skip<char*>();
}

