//
//  Packets.h
//  Horizon
//
//  Created by SagunKho on 18/06/2017.
//  Copyright © 2017 Horizon. All rights reserved.
//

#ifndef Packets_h
#define Packets_h

#include <stdint.h>

#include "Core/Networking/Buffer/ByteBuffer.hpp"

#pragma pack(push, 1)
struct Packet
{
	Packet(uint16_t id) : op_code(id) { }
	uint16_t op_code;
};
#pragma pack(pop)

class PacketBuffer : public ByteBuffer
{
public:
	PacketBuffer() : ByteBuffer(0), op_code(0x0000)
	{
	}

	PacketBuffer(uint16_t id, MessageBuffer&& buffer)
	: ByteBuffer(std::move(buffer)), op_code(id)
	{
	}

	PacketBuffer(uint16_t id, size_t reserve = 200)
	: ByteBuffer(reserve), op_code(id)
	{
	}

	PacketBuffer(PacketBuffer &&packet) : ByteBuffer(std::move(packet)), op_code(packet.op_code)
	{
	}

	PacketBuffer(PacketBuffer const &right) : ByteBuffer(right), op_code(right.op_code)
	{
	}

	PacketBuffer & operator = (PacketBuffer const &right)
	{
		if (this != &right) {
			op_code = right.op_code;
			ByteBuffer::operator=(right);
		}

		return *this;
	}

	PacketBuffer & operator = (PacketBuffer &&right)
	{
		if (this != &right) {
			op_code = right.op_code;
			ByteBuffer::operator=(std::move(right));
		}

		return *this;
	}

	void Initialize(uint16_t id, size_t newres = 200)
	{
		clear();
		_storage.reserve(newres);
		op_code = id;
	}

	uint16_t getOpCode() { return op_code; };
	void SetOpcode(uint16_t code) { op_code = code; }

protected:
	uint16_t op_code;
};


#endif /* Packets_h */
