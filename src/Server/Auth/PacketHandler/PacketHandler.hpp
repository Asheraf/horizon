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

#ifndef HORIZON_AUTH_PACKETHANDLER_HPP
#define HORIZON_AUTH_PACKETHANDLER_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Base/PacketHandler/PacketHandler.hpp"
#include "Server/Auth/PacketHandler/Packets.hpp"

#include <memory>
#include <unordered_map>
#include <boost/function.hpp>
#include <future>
#include <boost/system/error_code.hpp>

class SessionData;
class GameAccount;

namespace Horizon
{
namespace Auth
{
class AuthSocket;
class PacketHandler : public Horizon::Base::PacketHandler<AuthSocket>
{
public:
	explicit PacketHandler(std::shared_ptr<AuthSocket> socket);
	virtual ~PacketHandler();
	/**
	 *
	 */
	bool validate_session_data(std::shared_ptr<GameAccount> game_account, uint32_t client_version, uint8_t client_type);

	/**
	 * Client To Auth
	 */
	virtual bool Handle_CA_LOGIN(PacketBuffer &packet);
	virtual bool Handle_CA_REQ_HASH(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN2(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN3(PacketBuffer &packet);
	virtual bool Handle_CA_CONNECT_INFO_CHANGED(PacketBuffer &packet);
	virtual bool Handle_CA_EXE_HASHCHECK(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN_PCBANG(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN4(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN_HAN(PacketBuffer &packet);
	virtual bool Handle_CA_SSO_LOGIN_REQ(PacketBuffer &packet);
	virtual bool Handle_CA_LOGIN_OTP(PacketBuffer &packet);

	/**
	 * Auth To Client
	 */
	virtual void Send_AC_ACCEPT_LOGIN();
	virtual void Send_AC_REFUSE_LOGIN(login_error_codes error_code);
	virtual void Send_SC_NOTIFY_BAN();
	virtual void Send_AC_ACK_HASH();
	virtual void Send_AC_REFUSE_LOGIN_R2();
	virtual void Send_CA_CHARSERVERCONNECT();

	virtual void initialize_handlers();
};
}
}

#endif //HORIZON_AUTH_PACKETHANDLER_HPP
