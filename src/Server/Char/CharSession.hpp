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

#ifndef HORIZON_CHAR_CHARSESSION_H
#define HORIZON_CHAR_CHARSESSION_H

#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"
#include "Common/Packet.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

class SessionData;
class GameAccount;

namespace Horizon
{
namespace Char
{

class PacketHandler;
class InterPacketHandler;

class CharSession : public Socket<CharSession>
{
	typedef Socket<CharSession> CharSocket;
public:
	CharSession(std::shared_ptr<tcp::socket> socket);
	~CharSession() { }

	void Start() override;
	bool Update() override;

protected:
	void ReadHandler() override;
	void OnClose() override;

private:
	std::shared_ptr<GameAccount> _game_account;
	std::shared_ptr<SessionData> _session_data;
	std::shared_ptr<PacketHandler> _packet_handler;
	std::shared_ptr<InterPacketHandler> _inter_packet_handler;
};
}
}

#endif //HORIZON_CHAR_CHARSESSION_H
