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

#ifndef HORIZON_AUTH_PACKETHANDLER20170315_HPP
#define HORIZON_AUTH_PACKETHANDLER20170315_HPP

#include "Server/Auth/PacketHandler/PacketHandler.hpp"

struct PACKET_AC_ACCEPT_LOGIN_20170315;

namespace Horizon
{
namespace Auth
{
class AuthSocket;
class PacketHandler20170315 : public PacketHandler
{
public:
	explicit PacketHandler20170315(std::shared_ptr<AuthSocket> socket);
	~PacketHandler20170315() override;

	void Send_AC_ACCEPT_LOGIN() override;
	void Handle_TEST_POLY(PacketBuffer &pkt);
	void initialize_handlers() override;
};
}
}

/**
 * Overloaded Packet Definitions
 */
#pragma pack(push, 1)
struct PACKET_AC_ACCEPT_LOGIN_20170315 : public PacketBuffer
{
	PACKET_AC_ACCEPT_LOGIN_20170315() : PacketBuffer(Horizon::Auth::CA_LOGIN) { }

	int16 packet_len{};         ///< Packet length (variable length)
	int32 auth_code{};          ///< Authentication code
	uint32 aid{};               ///< Account ID
	uint32 user_level{};        ///< User level
	uint32 last_login_ip{};     ///< Last login IP
	char last_login_time[26]{}; ///< Last login timestamp
	uint8 sex{};                ///< Account sex
	char unknown1[17]{};
	struct character_server_list {
		uint32 ip;         ///< Server IP address
		int16 port;        ///< Server port
		char name[20];     ///< Server name
		uint16 usercount;  ///< Online users
		uint16 is_new;     ///< Server state
		uint16 type;       ///< Server type @ character_server_types
		char unknown2[128];
	} server_list[];
};
#pragma pack(pop)

#endif //HORIZON_AUTH_PACKETHANDLER20170315_HPP
