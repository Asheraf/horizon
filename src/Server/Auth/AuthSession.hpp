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

#ifndef HORIZON_AUTH_AUTHSESSION_HPP
#define HORIZON_AUTH_AUTHSESSION_HPP

#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"
#include "Common/Horizon.hpp"
#include "Common/Packet.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>
#include "Core/Multithreading/LockedQueue.hpp"

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Auth
{
class InterPacketHandler;
class PacketHandler;
class AuthSession : public Socket<AuthSession>
{
	typedef Socket<AuthSession> AuthSocket;
public:
	explicit AuthSession(std::shared_ptr<tcp::socket> socket);
	~AuthSession() { }

	void Start() override;
	bool Update() override;

	/* Game Account */
	std::shared_ptr<GameAccount> getGameAccount();
	void setGameAccount(std::shared_ptr<GameAccount> game_account);
	/* Char Account */
	std::shared_ptr<SessionData> getSessionData();
	void setSessionData(std::shared_ptr<SessionData> session_data);
	/* Packet Handler */
	std::shared_ptr<PacketHandler> getPacketHandler();
	void setPacketHandler(std::shared_ptr<PacketHandler> packet_handler);
	/* Inter Packet Handler */
	std::shared_ptr<InterPacketHandler> getInterPacketHandler();
	void setInterPacketHandler(std::shared_ptr<InterPacketHandler> packet_handler);

	void ReadHandler() override;
protected:
	int GetPacketVersion(uint16_t op_code, PacketBuffer buf);
	void OnClose() override;

private:
	std::shared_ptr<GameAccount> _game_account;
	std::shared_ptr<SessionData> _session_data;
	std::shared_ptr<PacketHandler> _packet_handler;
	std::shared_ptr<InterPacketHandler> _inter_packet_handler;
};
}
}

#endif /* HORIZON_AUTH_AUTHSESSION_HPP */
