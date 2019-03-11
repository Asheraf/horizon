/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/
#ifndef HORIZON_ZONE_SESSION_ZONESESSION_HPP
#define HORIZON_ZONE_SESSION_ZONESESSION_HPP

#include "Core/Networking/Session.hpp"
#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"

#include <memory>

namespace Horizon
{
	namespace Models
	{
		class GameAccount;
		class SessionData;

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

class PacketBuffer;

namespace Horizon
{
namespace Zone
{
class ZoneSocket;
class PacketHandler;
class ZoneSession : public Horizon::Networking::Session<ZoneSocket>
{
public:
	ZoneSession(std::shared_ptr<ZoneSocket> socket);
	~ZoneSession();

	/* Packet Handler */
	std::shared_ptr<PacketHandler> get_packet_handler();
	void set_packet_handler(std::shared_ptr<PacketHandler> handler);
	/* Game Account */
	std::shared_ptr<Models::GameAccount> get_game_account();
	void set_game_account(std::shared_ptr<Models::GameAccount> game_account);
	/* Session Data */
	std::shared_ptr<Models::SessionData> get_session_data();
	void set_session_data(std::shared_ptr<Models::SessionData> session_data);
	/* Character */
	std::shared_ptr<Models::Character::Character> get_char_model();
	void set_char_model(std::shared_ptr<Models::Character::Character> character);
	/* Player */
	std::shared_ptr<Horizon::Zone::Game::Entities::Player> get_player();
	void set_player(std::weak_ptr<Horizon::Zone::Game::Entities::Player> player);

	void handle_new_connection(PacketBuffer &buf);

	void update(uint32_t diff);

	void perform_cleanup();

	void initialize();

private:
	std::shared_ptr<PacketHandler> _packet_handler;
	std::shared_ptr<Models::Character::Character> _character;
	std::shared_ptr<Models::SessionData> _session_data;
	std::shared_ptr<Models::GameAccount> _game_account;
	std::weak_ptr<Game::Entities::Player> _player;
	client_type _client_type;
	uint32_t _packet_version;
};
}
}

#endif
