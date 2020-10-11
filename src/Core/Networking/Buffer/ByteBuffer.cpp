/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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

#include "ByteBuffer.hpp"

#include <iostream>
#include <sstream>

ByteBufferPositionException::ByteBufferPositionException(bool add, size_t pos,
														 size_t size, size_t valueSize)
{
	std::ostringstream ss;

	ss << "Attempted to " << (add ? "put" : "get") << " value with size: "
	<< valueSize << " in ByteBuffer (pos: " << pos << " size: " << size
	<< ")";

	message().assign(ss.str());
}

ByteBufferSourceException::ByteBufferSourceException(size_t pos, size_t size,
													 size_t valueSize)
{
	std::ostringstream ss;

	ss << "Attempted to put a "
	<< (valueSize > 0 ? "NULL-pointer" : "zero-sized value")
	<< " in ByteBuffer (pos: " << pos << " size: " << size << ")";

	message().assign(ss.str());
}

void ByteBuffer::print_storage() const
{
	std::ostringstream o;
	o << "STORAGE_SIZE: " << active_length();
	for (uint32_t i = 0; i < active_length(); ++i)
		o << read<uint8_t>(i) << " - ";
	o << " ";

	std::cout << o.str() << std::endl;
	//TC_LOG_TRACE("network", "%s", o.str().c_str());
}

void ByteBuffer::textlike() const
{
	std::ostringstream o;
	o << "STORAGE_SIZE: " << active_length();
	for (uint32_t i = 0; i < active_length(); ++i)
	{
		char buf[2];
		snprintf(buf, 2, "%c", read<uint8_t>(i));
		o << buf;
	}
	o << " ";
	std::cout << o.str() << std::endl;
	//TC_LOG_TRACE("network", "%s", o.str().c_str());
}

void ByteBuffer::hexlike() const
{
	uint32_t j = 1, k = 1;

	std::ostringstream o;
	o << "STORAGE_SIZE: " << active_length();

	for (uint32_t i = 0; i < active_length(); ++i)
	{
		char buf[3];
		snprintf(buf, 3, "%2X ", read<uint8_t>(i));
		if ((i == (j * 8)) && ((i != (k * 16))))
		{
			o << "| ";
			++j;
		}
		else if (i == (k * 16))
		{
			o << "\n";
			++k;
			++j;
		}

		o << buf;
	}
	o << " ";

	std::cout << o.str() << std::endl;

	//TC_LOG_TRACE("network", "%s", o.str().c_str());
}
