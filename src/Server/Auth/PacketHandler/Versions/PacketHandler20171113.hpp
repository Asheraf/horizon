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

#ifndef HORIZON_AUTH_PACKETHANDLER20171113_HPP
#define HORIZON_AUTH_PACKETHANDLER20171113_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Auth/PacketHandler/PacketHandler.hpp"
#include "PacketHandler20170315.hpp"

struct PACKET_CA_LOGIN_OTP_20171113;

namespace Horizon
{
namespace Auth
{
class AuthSocket;
class PacketHandler20171113 : public PacketHandler20170315
{
public:
	explicit PacketHandler20171113(std::shared_ptr<AuthSocket> socket);
	~PacketHandler20171113() override;

	void initialize_handlers() override;

	bool Handle_CA_LOGIN_OTP(PacketBuffer &buf) override;
	bool Handle_Poly(PacketBuffer &buf);
};
}
}

/**
 * Overloaded Packet Definitions
 */
#pragma pack(push, 1)
/**
 * Packet structure for CA_LOGIN_OTP.
 */
struct PACKET_CA_LOGIN_OTP_20171113 : public PACKET_CA_LOGIN_OTP
{
	PACKET_CA_LOGIN_OTP_20171113() : PACKET_CA_LOGIN_OTP() { }

	uint32 devFlags{};      ///< flags including dev flag
	char login[25]{};       ///< Username
	char password[32]{};    ///< Password encrypted by rijndael
	char flagsStr[5]{};     ///< Unknown flags. Normally string: G000
};

#pragma pack(pop)

#endif //HORIZON_AUTH_PACKETHANDLER20171113_HPP
