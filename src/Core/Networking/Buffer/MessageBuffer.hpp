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
	uint32_t MAX_BUFFER_LENGTH{1536};
	
	MessageBuffer() : _wpos(0), _rpos(0), _storage()
	{
		_storage.resize(MAX_BUFFER_LENGTH);
	}

	explicit MessageBuffer(std::size_t initial_size)
	: _wpos(0), _rpos(0), _storage()
	{
		_storage.resize(initial_size);
	}

	MessageBuffer(MessageBuffer const &right)
	: _wpos(right._wpos), _rpos(right._rpos), _storage(right._storage)
	{
	}

	MessageBuffer(MessageBuffer &&right)
	: _wpos(right._wpos), _rpos(right._rpos), _storage(right.move())
	{
	}

	void reset()
	{
		_wpos = 0;
		_rpos = 0;
	}

	void resize(size_type bytes)
	{
		_storage.resize(bytes);
	}

	uint8_t *get_base_pointer() { return _storage.data(); }
	uint8_t *get_read_pointer() { return get_base_pointer() + _rpos; }
	uint8_t *get_write_pointer() { return get_base_pointer() + _wpos; }

	void read_completed(size_type bytes) { _rpos += bytes; }
	void write_completed(size_type bytes) { _wpos += bytes; }

	size_type get_active_size() const { return _wpos - _rpos; }
	size_type get_remaining_space() const { return _storage.size() - _wpos; }
	size_type get_buffer_size() const { return _storage.size(); }

	// Discards inactive data
	void normalize()
	{
		if (_rpos) {
			if (_rpos != _wpos)
				memmove(get_base_pointer(), get_read_pointer(), get_active_size());
			_wpos -= _rpos;
			_rpos = 0;
		}
	}

	// Ensures there's "some" free space, make sure to call normalize() before this
	void ensureFreeSpace()
	{
		// resize buffer if it's already full
		if (get_remaining_space() == 0)
			_storage.resize(_storage.size() * 3 / 2);
	}

	void write(void const* data, std::size_t size)
	{
		if (size) {
			memcpy(get_write_pointer(), data, size);
			write_completed(size);
		}
	}

	std::vector<uint8_t> &&move()
	{
		_wpos = 0;
		_rpos = 0;

		return std::move(_storage);
	}

	const std::vector<uint8_t> &copy() { return _storage; }

	MessageBuffer &operator=(MessageBuffer const &right)
	{
		if (this != &right) {
			_wpos = right._wpos;
			_rpos = right._rpos;
			_storage = right._storage;
		}

		return *this;
	}

	MessageBuffer& operator=(MessageBuffer &&right)
	{
		if (this != &right) {
			_wpos = right._wpos;
			_rpos = right._rpos;
			_storage = right.move();
		}

		return *this;
	}

private:
	size_type _wpos;
	size_type _rpos;
	std::vector<uint8_t> _storage;
};

#endif /* MessageBuffer_hpp */
