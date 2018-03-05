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
#include "Core/Multithreading/ThreadSafeQueue.hpp"

#include <memory>
#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

class SessionData;
class GameAccount;
class PacketBuffer;

namespace Horizon
{
	namespace Models
	{
		namespace Character
		{
			class Character;
		}
	}
	
	namespace Zone
	{
		namespace Game
		{
			namespace Entities
			{
				class Player;
			}
		}
	}
}

using namespace Horizon::Zone::Game::Entities;
using namespace Horizon::Models::Character;

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
	void start() override;
	bool update() override;

	/* Zone Connect Handler */
	void handleNewConnection(PacketBuffer &buf);
	/* Packet Handler */
	std::shared_ptr<PacketHandler> getPacketHandler();
	void setPacketHandler(std::shared_ptr<PacketHandler> handler);
	/* Character */
	std::shared_ptr<Character> getCharacter();
	void setCharacter(std::shared_ptr<Character> const &c);
	/* Player */
	std::shared_ptr<Player> getPlayer();
	void setPlayer(std::shared_ptr<Player> const &p);
	/* */
protected:
	void readHandler() override;
	void onClose() override;
	/* */
private:
	std::shared_ptr<PacketHandler> _packet_handler;
	ThreadSafeQueue<PacketBuffer> _packet_queue;
	std::shared_ptr<Player> _player;
	std::shared_ptr<Character> _character;
};
}
}
#endif //HORIZON_ZONE_ZONESESSION_H
