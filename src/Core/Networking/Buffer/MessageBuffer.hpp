/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef MessageBuffer_hpp
#define MessageBuffer_hpp

#include <cstring>
#include <vector>

class MessageBuffer
{
	typedef std::vector<uint8_t>::size_type size_type;

public:
	uint32_t MAX_BUFFER_LENGTH{1024};
	
	MessageBuffer() : _wpos(0), _rpos(0), _storage()
	{
		_storage.resize(MAX_BUFFER_LENGTH);
	}

	explicit MessageBuffer(std::size_t initialSize) : _wpos(0), _rpos(0), _storage()
	{
		_storage.resize(initialSize);
	}

	MessageBuffer(MessageBuffer const& right) : _wpos(right._wpos), _rpos(right._rpos), _storage(right._storage)
	{
	}

	MessageBuffer(MessageBuffer&& right) : _wpos(right._wpos), _rpos(right._rpos), _storage(right.Move()) { }

	void Reset()
	{
		_wpos = 0;
		_rpos = 0;
	}

	void Resize(size_type bytes)
	{
		_storage.resize(bytes);
	}

	uint8_t* GetBasePointer() { return _storage.data(); }

	uint8_t* GetReadPointer() { return GetBasePointer() + _rpos; }

	uint8_t* GetWritePointer() { return GetBasePointer() + _wpos; }

	void ReadCompleted(size_type bytes) { _rpos += bytes; }

	void WriteCompleted(size_type bytes) { _wpos += bytes; }

	size_type GetActiveSize() const { return _wpos - _rpos; }

	size_type GetRemainingSpace() const { return _storage.size() - _wpos; }

	size_type GetBufferSize() const { return _storage.size(); }

	// Discards inactive data
	void Normalize()
	{
		if (_rpos)
		{
			if (_rpos != _wpos)
				memmove(GetBasePointer(), GetReadPointer(), GetActiveSize());
			_wpos -= _rpos;
			_rpos = 0;
		}
	}

	// Ensures there's "some" free space, make sure to call Normalize() before this
	void EnsureFreeSpace()
	{
		// resize buffer if it's already full
		if (GetRemainingSpace() == 0)
			_storage.resize(_storage.size() * 3 / 2);
	}

	void Write(void const* data, std::size_t size)
	{
		if (size)
		{
			memcpy(GetWritePointer(), data, size);
			WriteCompleted(size);
		}
	}

	std::vector<uint8_t>&& Move()
	{
		_wpos = 0;
		_rpos = 0;
		return std::move(_storage);
	}

	MessageBuffer& operator=(MessageBuffer const& right)
	{
		if (this != &right)
		{
			_wpos = right._wpos;
			_rpos = right._rpos;
			_storage = right._storage;
		}

		return *this;
	}

	MessageBuffer& operator=(MessageBuffer&& right)
	{
		if (this != &right)
		{
			_wpos = right._wpos;
			_rpos = right._rpos;
			_storage = right.Move();
		}

		return *this;
	}

private:
	size_type _wpos;
	size_type _rpos;
	std::vector<uint8_t> _storage;
};

#endif /* MessageBuffer_hpp */
