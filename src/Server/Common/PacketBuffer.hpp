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
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
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

struct Packet
{
	Packet(uint16_t id) : packet_id(id) { }
	virtual ~Packet() { }
	
	uint16_t packet_id{0};
};

class PacketBuffer : public ByteBuffer
{
public:
	PacketBuffer() : ByteBuffer(0), packet_id(0x0000)
	{
	}

	PacketBuffer(uint8_t *data, size_t size)
	: ByteBuffer(size)
	{
		append(reinterpret_cast<char *>(data), size);
		memcpy(&packet_id, data, sizeof(uint16_t));
	}

	PacketBuffer(uint16_t id, size_t reserve = 50)
	: ByteBuffer(reserve), packet_id(id)
	{
		append(id);
	}

	PacketBuffer(PacketBuffer &&buf) : ByteBuffer(std::move(buf)), packet_id(buf.packet_id)
	{
	}

	PacketBuffer(PacketBuffer const &right) : ByteBuffer(right), packet_id(right.packet_id)
	{
	}

	PacketBuffer operator = (PacketBuffer const &right)
	{
		if (this != &right) {
			append(right.packet_id);
			packet_id = right.packet_id;
			ByteBuffer::operator=(right);
		}

		return *this;
	}

	PacketBuffer operator = (PacketBuffer &&right)
	{
		if (this != &right) {
			packet_id = right.packet_id;
			ByteBuffer::operator=(std::move(right));
		}

		return *this;
	}

	uint16_t getOpCode() { return packet_id; };
	void SetOpcode(uint16_t code) { packet_id = code; }

protected:
	uint16_t packet_id;
};


#endif /* PACKET_H */
