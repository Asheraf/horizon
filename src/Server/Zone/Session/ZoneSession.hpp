
#ifndef HORIZON_ZONE_SESSION_ZONESESSION_HPP
#define HORIZON_ZONE_SESSION_ZONESESSION_HPP

#include "Core/Networking/Session.hpp"
#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"

#include <boost/smart_ptr.hpp>
#include <memory>

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

class GameAccount;
class SessionData;

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
	std::shared_ptr<GameAccount> get_game_account();
	void set_game_account(std::shared_ptr<GameAccount> game_account);
	/* Session Data */
	std::shared_ptr<SessionData> get_session_data();
	void set_session_data(std::shared_ptr<SessionData> session_data);
	/* Character */
	std::shared_ptr<Horizon::Models::Character::Character> get_character();
	void set_character(std::shared_ptr<Horizon::Models::Character::Character> character);
	/* Player */
	boost::shared_ptr<Horizon::Zone::Game::Entities::Player> get_player();
	void set_player(boost::weak_ptr<Horizon::Zone::Game::Entities::Player> player);

	void handle_new_connection(PacketBuffer &buf);
	
	void update(uint32_t diff);

	void perform_cleanup();

	void initialize();

private:
	std::shared_ptr<PacketHandler> _packet_handler;
	std::shared_ptr<Horizon::Models::Character::Character> _character;
	std::shared_ptr<SessionData> _session_data;
	std::shared_ptr<GameAccount> _game_account;
	boost::weak_ptr<Horizon::Zone::Game::Entities::Player> _player;
	client_types _client_type;
	uint32_t _packet_version;
};
}
}

#endif
