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

#ifndef HORIZON_AUTH_SESSION_HPP
#define HORIZON_AUTH_SESSION_HPP

#include "Server/Common/Horizon.hpp"
#include "Core/Multithreading/LockedQueue.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"
#include "Core/Networking/Socket.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Auth
{
class InterPacketHandler;
class PacketHandler;
class Session : public Socket<Session>
{
	typedef Socket<Session> AuthSocket;
public:
	explicit Session(std::shared_ptr<tcp::socket> socket);
	~Session() { }
	/* */
	void Start() override;
	bool Update() override;

	/* Packet Handler */
	std::shared_ptr<PacketHandler> &getPacketHandler();
	void setPacketHandler(std::shared_ptr<PacketHandler> handler);
	/* */
protected:
	void ReadHandler() override;
	void OnClose() override;
	/* */
	int GetPacketVersion(uint16_t op_code, PacketBuffer buf);
	/* */
private:
	std::shared_ptr<PacketHandler> _packet_handler;
};
}
}

#endif /* HORIZON_AUTH_SESSION_HPP */
