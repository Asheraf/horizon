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

#ifndef HORIZON_ZONE_PACKETS_HPP
#define HORIZON_ZONE_PACKETS_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/PacketBuffer.hpp"

namespace Horizon
{
namespace Zone
{
enum packets
{
	/* ZC */
	ZC_ERROR              = 0x006a,
	ZC_ACCOUNT_ID         = 0x0283,
	ZC_ACCEPT_CONNECTION  = 0x0a18,
	ZC_NPCACK_MAPMOVE     = 0x0091,
	ZC_NOTIFY_TIME        = 0x007f,
	ZC_ACK_REQNAME        = 0x0095,
	ZC_ACK_REQNAMEALL     = 0x0195,

	/* CZ */
	CZ_LOGIN_TIMESTAMP    = 0x044a,
	CZ_MAP_LOAD_END_ACK   = 0x007d,
	CZ_GUILD_CHECK_MASTER = 0x014d,
	CZ_GUILD_REQUEST_INFO = 0x014f,
};
}
}

#pragma pack(push, 1)
enum zone_server_reject_types : uint8_t
{
	ZONE_SERV_ERROR_REJECT = 3,
};

struct PACKET_ZC_ERROR : public Packet
{
	PACKET_ZC_ERROR() : Packet(Horizon::Zone::packets::ZC_ERROR) { }
	uint8_t error{ZONE_SERV_ERROR_REJECT};
};

struct PACKET_ZC_ACCOUNT_ID : public Packet
{
	PACKET_ZC_ACCOUNT_ID() : Packet(Horizon::Zone::packets::ZC_ACCOUNT_ID) { }
	uint32_t account_id{0};
};

struct PACKET_ZC_ACCEPT_CONNECTION : public Packet
{
	PACKET_ZC_ACCEPT_CONNECTION() : Packet(Horizon::Zone::packets::ZC_ACCEPT_CONNECTION) { }
	uint32_t start_time{0};
	uint8_t packed_position[3]{0};
	uint8_t x_size{0};
	uint8_t y_size{0};
	uint16_t font{0};
	uint8_t gender{0};
};

struct PACKET_ZC_NPCACK_MAPMOVE : public Packet
{
	PACKET_ZC_NPCACK_MAPMOVE() : Packet(Horizon::Zone::packets::ZC_NPCACK_MAPMOVE) { }
	char map_name[MAP_NAME_LENGTH_EXT]{0};
	uint16_t x{0};
	uint16_t y{0};
};

struct PACKET_CZ_LOGIN_TIMESTAMP : public Packet
{
	PACKET_CZ_LOGIN_TIMESTAMP() : Packet(Horizon::Zone::packets::CZ_LOGIN_TIMESTAMP) { }
	uint32_t timestamp{0};
};

struct PACKET_CZ_REQUEST_TIME : public Packet
{
	PACKET_CZ_REQUEST_TIME(uint16_t op_code) : Packet(op_code) { }
	uint32_t timestamp{0};
};

struct PACKET_ZC_NOTIFY_TIME : public Packet
{
	PACKET_ZC_NOTIFY_TIME() : Packet(Horizon::Zone::packets::ZC_NOTIFY_TIME) { }
	uint32_t timestamp{0};
};

struct PACKET_CZ_REQNAME : public Packet
{
	PACKET_CZ_REQNAME(uint16_t op_code) : Packet(op_code) { }
	uint32_t guid{0};
};

struct PACKET_ZC_ACK_REQNAME : public Packet
{
	PACKET_ZC_ACK_REQNAME() : Packet(Horizon::Zone::packets::ZC_ACK_REQNAME) { }
	uint32_t guid;
	char name[MAX_CHAR_NAME_LENGTH];
};

struct PACKET_ZC_ACK_REQNAMEALL : public Packet
{
	PACKET_ZC_ACK_REQNAMEALL() : Packet(Horizon::Zone::packets::ZC_ACK_REQNAMEALL) { }
	uint32_t guid;
	char name[MAX_CHAR_NAME_LENGTH];
	char party_name[MAX_PARTY_NAME_LENGTH];
	char guild_name[MAX_GUILD_NAME_LENGTH];
	char guild_position_name[MAX_GUILD_POSITION_NAME_LENGTH];
};

#pragma pack(pop)

#endif // HORIZON_ZONE_PACKETS_HPP
