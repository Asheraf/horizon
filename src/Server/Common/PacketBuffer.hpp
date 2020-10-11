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

#ifndef HORIZON_COMMON_PACKETBUFFER_H
#define HORIZON_COMMON_PACKETBUFFER_H

#include "Core/Networking/Buffer/ByteBuffer.hpp"
#include "Core/Multithreading/ThreadSafeQueue.hpp"

#include <stdint.h>
#include <boost/function.hpp>
#include <unordered_map>

class PacketBuffer;

typedef ThreadSafeQueue<PacketBuffer> PacketQueueType;

class PacketBuffer : public ByteBuffer
{
public:
	PacketBuffer() : ByteBuffer(0), _packet_id(0x0000)
	{
	}

	PacketBuffer(uint8_t *data, size_t size)
	: ByteBuffer(size)
	{
		append(reinterpret_cast<char *>(data), size);
		memcpy(&_packet_id, data, sizeof(uint16_t));
	}

	PacketBuffer(uint16_t id, size_t reserve = 50)
	: ByteBuffer(reserve), _packet_id(id)
	{
		append(id);
	}

	PacketBuffer(PacketBuffer &&buf) : ByteBuffer(std::move(buf)), _packet_id(buf._packet_id)
	{
	}

	PacketBuffer(PacketBuffer const &right) : ByteBuffer(right), _packet_id(right._packet_id)
	{
	}

	PacketBuffer operator = (PacketBuffer const &right)
	{
		if (this != &right) {
			append(right._packet_id);
			_packet_id = right._packet_id;
			ByteBuffer::operator=(right);
		}

		return *this;
	}

	PacketBuffer operator = (PacketBuffer &&right)
	{
		if (this != &right) {
			_packet_id = right._packet_id;
			ByteBuffer::operator=(std::move(right));
		}

		return *this;
	}

	uint16_t getOpCode() { return _packet_id; };
	void SetOpcode(uint16_t code) { _packet_id = code; }

protected:
	uint16_t _packet_id;
};


#endif /* PACKET_H */
