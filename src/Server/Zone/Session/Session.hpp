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

#ifndef HORIZON_ZONE_SESSION_H
#define HORIZON_ZONE_SESSION_H

#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"

#include <memory>
#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

class SessionData;
class GameAccount;
class PacketBuffer;

namespace Horizon
{
namespace Zone
{
class PacketHandler;
class InterPacketHandler;
class Session : public Socket<Session>
{
	typedef Socket<Session> ZoneSocket;
public:
	Session(std::shared_ptr<tcp::socket> socket);
	~Session() { }
	/* */
	void Start() override;
	bool Update() override;

	/* Zone Connect Handler */
	void ValidateAndHandleConnection(PacketBuffer &buf);
	/* Packet Handler */
	const std::shared_ptr<PacketHandler> &getPacketHandler() const;
	void setPacketHandler(std::shared_ptr<PacketHandler> handler);
	/* */
protected:
	void ReadHandler() override;
	void OnClose() override;
	/* */
private:
	std::shared_ptr<PacketHandler> _packet_handler;
};
}
}
#endif //HORIZON_ZONE_ZONESESSION_H
