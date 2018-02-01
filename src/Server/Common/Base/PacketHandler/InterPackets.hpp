
#ifndef HORIZON_BASE_INTERPACKETS_HPP
#define HORIZON_BASE_INTERPACKETS_HPP

#include "Server/Common/PacketBuffer.hpp"

namespace Horizon
{
namespace Base
{
enum inter_packets
{
	INTER_CONNECT_INIT          = 0x01,
	INTER_CONNECT_AUTH          = 0x02,
	INTER_ACK_RECEIVED          = 0x03,
	INTER_SESSION_GET           = 0x04,
	INTER_SESSION_RECV          = 0x05,
	INTER_SESSION_SET           = 0x06,
	INTER_SESSION_DEL           = 0x07,
	INTER_SESSION_REQ           = 0x08
};
}
}

enum inter_connect_client_type : char
{
	INTER_CONNECT_CLIENT_AUTH = 0,
	INTER_CONNECT_CLIENT_CHAR = 1,
	INTER_CONNECT_CLIENT_ZONE = 2
};

#pragma pack(push, 1)
struct PACKET_INTER_CONNECT_INIT : public Packet
{
	PACKET_INTER_CONNECT_INIT() : Packet(Horizon::Base::inter_packets::INTER_CONNECT_INIT) {}
};

struct PACKET_INTER_CONNECT_AUTH : public Packet
{
	PACKET_INTER_CONNECT_AUTH() : Packet(Horizon::Base::inter_packets::INTER_CONNECT_AUTH) {}

	uint16_t packet_len{};
	inter_connect_client_type client_type;
	unsigned char password[];
};

struct PACKET_INTER_ACK_RECEIVED : public Packet
{
	PACKET_INTER_ACK_RECEIVED() : Packet(Horizon::Base::inter_packets::INTER_ACK_RECEIVED) {}

	uint16_t ack_packet_id{};
	uint8_t response{};
};

struct PACKET_INTER_SESSION
{
	uint32_t game_account_id{};
	uint32_t auth_code{};
	uint32_t client_version{};
	uint8_t client_type{};
	uint8_t group_id{};
	uint8_t character_slots{};
};

struct PACKET_INTER_SESSION_SET : public Packet
{
	PACKET_INTER_SESSION_SET() : Packet(Horizon::Base::inter_packets::INTER_SESSION_SET) { }

	struct PACKET_INTER_SESSION s;
};

struct PACKET_INTER_SESSION_REQ : public Packet
{
	PACKET_INTER_SESSION_REQ() : Packet(Horizon::Base::inter_packets::INTER_SESSION_REQ) { }

	uint32_t auth_code{};
};

struct PACKET_INTER_SESSION_GET : public Packet
{
	PACKET_INTER_SESSION_GET() : Packet(Horizon::Base::INTER_SESSION_GET) { }

	struct PACKET_INTER_SESSION s;
};

struct PACKET_INTER_SESSION_DEL : public Packet
{
	PACKET_INTER_SESSION_DEL() : Packet(Horizon::Base::inter_packets::INTER_SESSION_DEL) { }

	uint32_t auth_code{};
};

#pragma pack(pop)

#endif // HORIZON_BASE_INTERPACKETS_HPP
