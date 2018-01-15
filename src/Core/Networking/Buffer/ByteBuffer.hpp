
#include "ByteConverter.hpp"

#include "MessageBuffer.hpp"

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
		static_assert(std::is_fundamental<T>::value, "append(compound)");
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

	ByteBuffer &operator<<(const std::string &value)
	{
		if (size_t len = value.length())
			append((uint8_t const*)value.c_str(), len);
		append((uint8_t)0);
		return *this;
	}

	ByteBuffer &operator<<(const char *str)
	{
		if (size_t len = (str ? strlen(str) : 0))
			append((uint8_t const*)str, len);
		append((uint8_t)0);
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

	ByteBuffer &operator>>(std::string& value)
	{
		value.clear();
		while (rpos() < size())                         // prevent crash at wrong string format in packet
		{
			char c = read<char>();
			if (c == 0)
				break;
			value += c;
		}
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

	void rfinish()
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
		EndianConvert(val);
		return val;
	}

	void read(uint8_t *dest, size_t len)
	{
		if (_rpos  + len > size())
			throw ByteBufferPositionException(false, _rpos, len, size());
		std::memcpy(dest, &_storage[_rpos], len);
		_rpos += len;
	}

	void readPackGUID(uint64_t& guid)
	{
		if (rpos() + 1 > size())
			throw ByteBufferPositionException(false, _rpos, 1, size());

		guid = 0;

		uint8_t guidmark = 0;
		(*this) >> guidmark;

		for (int i = 0; i < 8; ++i)
		{
			if (guidmark & (uint8_t(1) << i))
			{
				if (rpos() + 1 > size())
					throw ByteBufferPositionException(false, _rpos, 1, size());

				uint8_t bit;
				(*this) >> bit;
				guid |= (uint64_t(bit) << (i * 8));
			}
		}
	}

	uint32_t ReadPackedTime()
	{
		uint32_t packedDate = read<uint32_t>();
		tm lt = tm();

		lt.tm_min = packedDate & 0x3F;
		lt.tm_hour = (packedDate >> 6) & 0x1F;
		//lt.tm_wday = (packedDate >> 11) & 7;
		lt.tm_mday = ((packedDate >> 14) & 0x3F) + 1;
		lt.tm_mon = (packedDate >> 20) & 0xF;
		lt.tm_year = ((packedDate >> 24) & 0x1F) + 100;

		return uint32_t(mktime(&lt));
	}

	ByteBuffer& ReadPackedTime(uint32_t& time)
	{
		time = ReadPackedTime();
		return *this;
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

	void append(const char *src, size_t cnt)
	{
		return append((const uint8_t *)src, cnt);
	}

	template<class T> void append(const T *src, size_t cnt)
	{
		return append((const uint8_t *)src, cnt * sizeof(T));
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

	// can be used in SMSG_MONSTER_MOVE opcode
	void appendPackXYZ(float x, float y, float z)
	{
		uint32_t packed = 0;
		packed |= ((int)(x / 0.25f) & 0x7FF);
		packed |= ((int)(y / 0.25f) & 0x7FF) << 11;
		packed |= ((int)(z / 0.25f) & 0x3FF) << 22;
		*this << packed;
	}

	void appendPackGUID(uint64_t guid)
	{
		uint8_t packGUID[8+1];
		packGUID[0] = 0;
		size_t size = 1;
		for (uint8_t i = 0;guid != 0;++i)
		{
			if (guid & 0xFF)
			{
				packGUID[0] |= uint8_t(1 << i);
				packGUID[size] =  uint8_t(guid & 0xFF);
				++size;
			}

			guid >>= 8;
		}
		append(packGUID, size);
	}

	void AppendPackedTime(time_t time)
	{
		tm lt;
		localtime_r(&time, &lt);
		append<uint32_t>((lt.tm_year - 100) << 24 | lt.tm_mon  << 20 | (lt.tm_mday - 1) << 14 | lt.tm_wday << 11 | lt.tm_hour << 6 | lt.tm_min);
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

protected:
	size_t _rpos, _wpos;
	std::vector<uint8_t> _storage;
};

template <typename T>
inline ByteBuffer &operator<<(ByteBuffer &b, std::vector<T> v)
{
	b << (uint32_t)v.size();
	for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i) {
		b << *i;
	}
	return b;
}

template <typename T>
inline ByteBuffer &operator>>(ByteBuffer &b, std::vector<T> &v)
{
	uint32_t vsize;
	b >> vsize;
	v.clear();
	while (vsize--) {
		T t;
		b >> t;
		v.push_back(t);
	}
	return b;
}

template <typename T>
inline ByteBuffer &operator<<(ByteBuffer &b, std::list<T> v)
{
	b << (uint32_t)v.size();
	for (typename std::list<T>::iterator i = v.begin(); i != v.end(); ++i) {
		b << *i;
	}
	return b;
}

template <typename T>
inline ByteBuffer &operator>>(ByteBuffer &b, std::list<T> &v)
{
	uint32_t vsize;
	b >> vsize;
	v.clear();
	while (vsize--) {
		T t;
		b >> t;
		v.push_back(t);
	}
	return b;
}

template <typename K, typename V>
inline ByteBuffer &operator<<(ByteBuffer &b, std::map<K, V> &m)
{
	b << (uint32_t)m.size();
	for (typename std::map<K, V>::iterator i = m.begin(); i != m.end(); ++i) {
		b << i->first << i->second;
	}
	return b;
}

template <typename K, typename V>
inline ByteBuffer &operator>>(ByteBuffer &b, std::map<K, V> &m)
{
	uint32_t msize;
	b >> msize;
	m.clear();
	while (msize--) {
		K k;
		V v;
		b >> k >> v;
		m.insert(make_pair(k, v));
	}
	return b;
}

/// @todo Make a ByteBuffer.cpp and move all this inlining to it.
template<> inline std::string ByteBuffer::read<std::string>()
{
	std::string tmp;
	*this >> tmp;
	return tmp;
}

template<>
inline void ByteBuffer::read_skip<char*>()
{
	std::string temp;
	*this >> temp;
}

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

