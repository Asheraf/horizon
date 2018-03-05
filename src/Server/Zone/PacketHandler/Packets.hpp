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
	ZC_ERROR                      = 0x006a,
	ZC_ACCOUNT_ID                 = 0x0283,
	ZC_ACCEPT_CONNECTION          = 0x0a18,
	ZC_NPCACK_MAPMOVE             = 0x0091,
	ZC_NOTIFY_TIME                = 0x007f,
	ZC_ACK_REQNAME                = 0x0095,
	ZC_ACK_REQNAMEALL             = 0x0195,
	ZC_ACK_GUILD_MENUINTERFACE    = 0x014e,

	/* CZ */
	CZ_LOGIN_TIMESTAMP            = 0x044a,
	CZ_MAP_LOAD_END_ACK           = 0x007d,
	CZ_REQ_GUILD_MENUINTERFACE    = 0x014d,
	CZ_REQ_GUILD_MENU             = 0x014f,
};
	
#pragma pack(push, 1)
struct PACKET_CZ_ENTER : public Packet
{
	PACKET_CZ_ENTER(uint16_t id) : Packet(id) { }
	uint32_t account_id;
	uint32_t char_id;
	uint32_t auth_code;
	uint32_t client_time;
	uint8_t gender;
};
struct PACKET_CZ_REQUEST_ACT : public Packet
{
	PACKET_CZ_REQUEST_ACT(uint16_t id) : Packet(id) { }
	uint32_t target_guid;
	uint8_t action;
};
struct PACKET_CZ_REQUEST_MOVE : public Packet
{
	PACKET_CZ_REQUEST_MOVE(uint16_t id) : Packet(id) { }
	uint8_t packed_destination[3];
};

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

struct PACKET_CZ_REQ_GUILD_MENUINTERFACE : public Packet
{
	PACKET_CZ_REQ_GUILD_MENUINTERFACE() : Packet(Horizon::Zone::packets::CZ_REQ_GUILD_MENUINTERFACE) { }
};

enum zc_ack_guild_menuinterface_mask_types
{
	GMIF_BASIC_INFO     = 0x00,
	GMIF_MEMBER_MANAGER = 0x01,
	GMIF_POSITIONS      = 0x02,
	GMIF_SKILLS         = 0x04,
	GMIF_EXPULSION_LIST = 0x10,
	GMIF_ALLGUILDLIST   = 0x40,
	GMIF_NOTICE         = 0x80,
	GMIF_MEMBER         = GMIF_ALLGUILDLIST | GMIF_EXPULSION_LIST | GMIF_SKILLS | GMIF_POSITIONS | GMIF_MEMBER_MANAGER,
	GMIF_MASTER         = GMIF_NOTICE | GMIF_MEMBER,
};

struct PACKET_ZC_ACK_GUILD_MENUINTERFACE : public Packet
{
	PACKET_ZC_ACK_GUILD_MENUINTERFACE() : Packet(Horizon::Zone::packets::ZC_ACK_GUILD_MENUINTERFACE) { }
	uint32_t menu_interface_mask;
};

enum cz_req_guild_menu_types
{
	CZ_REQ_GUILD_BASIC_INFO     = 0,
	CZ_REQ_GUILD_MEMBER_MANAGER = 1,
	CZ_REQ_GUILD_POSITIONS      = 2,
	CZ_REQ_GUILD_SKILLS         = 3,
	CZ_REQ_GUILD_EXPULSION_LIST = 4,
	CZ_REQ_GM_ALLGUILDLIST      = 5,
	CZ_REQ_GUILD_NOTICE         = 6
};

struct PACKET_CZ_REQ_GUILD_MENU : public Packet
{
	PACKET_CZ_REQ_GUILD_MENU() : Packet(Horizon::Zone::packets::CZ_REQ_GUILD_MENU) { }
	cz_req_guild_menu_types info_type;
};

#pragma pack(pop)
}
}


#endif // HORIZON_ZONE_PACKETS_HPP
