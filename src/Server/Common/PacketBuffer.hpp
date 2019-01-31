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

#ifndef HORIZON_COMMON_PACKETBUFFER_H
#define HORIZON_COMMON_PACKETBUFFER_H

#include "Core/Networking/Buffer/ByteBuffer.hpp"
#include "Core/Multithreading/ThreadSafeQueue.hpp"

#include <stdint.h>
#include <boost/function.hpp>
#include <unordered_map>

class PacketBuffer;

typedef ThreadSafeQueue<PacketBuffer> PacketQueueType;

#pragma pack(push, 1)
struct Packet
{
	Packet(uint16_t id) : packet_id(id) { }
	uint16_t packet_id;
};
#pragma pack(pop)

class PacketBuffer : public ByteBuffer
{
public:
	PacketBuffer() : ByteBuffer(0), packet_id(0x0000)
	{
	}

	PacketBuffer(uint16_t id, uint8_t *data, size_t size)
	: ByteBuffer(size), packet_id(id)
	{
		append(&*data, size);
	}

	PacketBuffer(uint16_t id, size_t reserve = 200)
	: ByteBuffer(reserve), packet_id(id)
	{
	}

	PacketBuffer(PacketBuffer &&packet) : ByteBuffer(std::move(packet)), packet_id(packet.packet_id)
	{
	}

	PacketBuffer(PacketBuffer const &right) : ByteBuffer(right), packet_id(right.packet_id)
	{
	}

	PacketBuffer & operator = (PacketBuffer const &right)
	{
		if (this != &right) {
			packet_id = right.packet_id;
			ByteBuffer::operator=(right);
		}

		return *this;
	}

	PacketBuffer & operator = (PacketBuffer &&right)
	{
		if (this != &right) {
			packet_id = right.packet_id;
			ByteBuffer::operator=(std::move(right));
		}

		return *this;
	}

	template<class PACKET_TYPE>
	PacketBuffer & operator << (PACKET_TYPE &pkt)
	{
		append<PACKET_TYPE>(&pkt, sizeof(PACKET_TYPE));
		return *this;
	}

	template<class PACKET_TYPE>
	PacketBuffer & operator << (std::pair<PACKET_TYPE *, std::size_t> &pkt)
	{
		append<PACKET_TYPE>(pkt.first, pkt.second);
		return *this;
	}

	template <class PACKET_TYPE>
	void read(PACKET_TYPE *dest, size_t len)
	{
		if (_rpos  + len > size())
			throw ByteBufferPositionException(false, _rpos, len, size());

		std::memcpy(dest, &_storage[_rpos], len);

		_rpos += len;
	}

	template <class PACKET_TYPE>
	PacketBuffer & operator >> (PACKET_TYPE &pkt)
	{
		read(&pkt, sizeof(PACKET_TYPE));
		return *this;
	}

	void initialize(uint16_t id, size_t newres = 200)
	{
		clear();
		_storage.reserve(newres);
		packet_id = id;
	}

	uint16_t getOpCode() { return packet_id; };
	void SetOpcode(uint16_t code) { packet_id = code; }

protected:
	uint16_t packet_id;
};


#endif /* PACKET_H */
