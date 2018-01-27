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

namespace Horizon
{
namespace Char
{
class CharSession : public Socket<CharSession>
{
	friend class CharMain;
	typedef Socket<CharSession> CharSocket;
	typedef void (CharSession::*CharPacketHandler) (PacketBuffer &pkt);
public:
	CharSession(std::shared_ptr<tcp::socket> socket);
	~CharSession() { }

	void Start() override;
	bool Update() override;

protected:
	std::unordered_map<uint16_t, CharPacketHandler> handlers;
	void ReadHandler() override;
	void OnClose() override;
};
}
}

#endif //HORIZON_CHAR_CHARSESSION_H
