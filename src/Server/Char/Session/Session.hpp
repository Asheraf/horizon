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

#ifndef HORIZON_CHAR_SESSION_H
#define HORIZON_CHAR_SESSION_H

#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"
#include "Core/Multithreading/ThreadSafeQueue.hpp"
#include "Server/Common/Models/Character/Character.hpp"

#include <memory>
#include <cstdio>
#include <boost/asio/ip/tcp.hpp>
#include <boost/optional.hpp>

using boost::asio::ip::tcp;

class SessionData;
class GameAccount;
class PacketBuffer;

namespace Horizon
{
namespace Char
{
class PacketHandler;
class InterPacketHandler;
class Session : public Socket<Session>
{
	typedef Socket<Session> CharSocket;
public:
	Session(std::shared_ptr<tcp::socket> socket);
	~Session();
	
	/* */
	void start() override;
	bool update() override;

	/* Char Connect Handler */
	void handleNewConnection(PacketBuffer &buf);
	/* Packet Handler */
	std::shared_ptr<PacketHandler> getPacketHandler();
	void setPacketHandler(std::shared_ptr<PacketHandler> handler);
protected:
	void readHandler() override;
	void onClose() override;
	/* */
private:
	std::shared_ptr<PacketHandler> _packet_handler;
	ThreadSafeQueue<PacketBuffer> _packet_queue;
};
}
}

#endif //HORIZON_CHAR_SESSION_H
