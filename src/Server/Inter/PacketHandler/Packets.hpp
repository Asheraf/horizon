/**           _   _            _
 *          | | | |          (_)
 *          | |_| | ___  _ __ _ _______  _ __
 *          |  _  |/ _ \| '__| |_  / _ \| '_ \
 *          | | | | (_) | |  | |/ / (_) | | | |
 *          \_| |_/\___/|_|  |_/___\___/|_| |_|
 *
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 ****************************************************/

#ifndef HORIZON_INTERPACKETS_H
#define HORIZON_INTERPACKETS_H

namespace Horizon
{
namespace Inter
{
enum packets
{
	/* Common Inter Packets */
	INTER_CONNECT_INIT          = 0x01,
	INTER_CONNECT_AUTH          = 0x02,
	INTER_ACK_RECEIVED          = 0x03,
	INTER_SESSION_GET           = 0x04,
	INTER_SESSION_RECV          = 0x05,
	INTER_SESSION_SET           = 0x06,
	INTER_SESSION_DEL           = 0x07,
	/* Inter-Auth Packets */
	AI_CHARSERV_GET_INFO        = 0x09,
};
}
}

#pragma pack(push, 1)
struct PACKET_INTER_CONNECT_INIT : public Packet
{
	PACKET_INTER_CONNECT_INIT() : Packet(Horizon::Inter::INTER_CONNECT_INIT) {}
};

struct PACKET_INTER_CONNECT_AUTH : public Packet
{
	PACKET_INTER_CONNECT_AUTH() : Packet(Horizon::Inter::INTER_CONNECT_AUTH) {}

	uint16_t packet_len{};
	unsigned char password[];
};

struct PACKET_INTER_ACK_RECEIVED : public Packet
{
	PACKET_INTER_ACK_RECEIVED() : Packet(Horizon::Inter::INTER_ACK_RECEIVED) {}

	uint16_t ack_packet_id{};
	uint8_t response{};
};

/**
 * Inter-Auth packets
 */
struct PACKET_INTER_SESSION
{
	uint32_t game_account_id{};
	int auth_code{};
	uint32_t client_version{};
	uint8_t client_type{};
};

struct PACKET_INTER_SESSION_SET : public Packet
{
	PACKET_INTER_SESSION_SET() : Packet(Horizon::Inter::INTER_SESSION_SET) { }

	uint32_t session_id{};
	struct PACKET_INTER_SESSION s;
};

struct PACKET_INTER_SESSION_DEL : public Packet
{
	PACKET_INTER_SESSION_DEL() : Packet(Horizon::Inter::INTER_SESSION_DEL) { }

	uint32_t session_id{};
};

struct PACKET_AI_GET_CHAR_SERVER_INFO : public Packet
{
	PACKET_AI_GET_CHAR_SERVER_INFO() : Packet(Horizon::Inter::AI_CHARSERV_GET_INFO) { }

	uint32_t server_id;
	uint32_t user_count;
	uint32_t server_type;
};
#pragma pack(pop)
#endif //HORIZON_INTERPACKETS_H
