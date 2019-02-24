#include "ZoneSession.hpp"

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Packets/PacketHandler.hpp"
#include "Server/Zone/Packets/PacketHandlerFactory.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;
using namespace Horizon::Models::Character;
using namespace Horizon::Zone::Game::Entities;

ZoneSession::ZoneSession(std::shared_ptr<ZoneSocket> socket)
: Session(socket)
{
	_client_type = ZoneServer->general_conf().get_client_type();
	_packet_version = ZoneServer->general_conf().get_packet_version();
}

ZoneSession::~ZoneSession()
{
	//
}

/* Packet Handler */
std::shared_ptr<PacketHandler> ZoneSession::get_packet_handler() { return _packet_handler; }
void ZoneSession::set_packet_handler(std::shared_ptr<PacketHandler> handler) { _packet_handler.swap(handler); }
/* Character */
std::shared_ptr<Character> ZoneSession::get_character() { return _character; }
void ZoneSession::set_character(std::shared_ptr<Character> character) { _character.swap(character); }
/* Game Account */
std::shared_ptr<GameAccount> ZoneSession::get_game_account() { return _game_account; }
void ZoneSession::set_game_account(std::shared_ptr<GameAccount> game_acc) { _game_account.swap(game_acc); }
/* Session Data */
std::shared_ptr<SessionData> ZoneSession::get_session_data() { return _session_data; }
void ZoneSession::set_session_data(std::shared_ptr<SessionData> session_data) { _session_data.swap(session_data); }
/* Player */
boost::shared_ptr<Player> ZoneSession::get_player() { return _player.lock(); }
void ZoneSession::set_player(boost::weak_ptr<Player> p) { _player = p; }

void ZoneSession::initialize()
{
	set_packet_handler(PacketHandlerFactory::create_packet_handler(get_socket(), _client_type, _packet_version));
}

/**
 * Update loop for each Zone Session.
 * @thread called from map thread container.
 */
void ZoneSession::update(uint32_t /*diff*/)
{
	std::shared_ptr<PacketBuffer> buf;

	while ((buf = get_socket()->get_packet_recv_queue().try_pop())) {
		_packet_handler->handle_received_packet(*buf);
	}
}

void ZoneSession::perform_cleanup()
{
	boost::shared_ptr<Player> player = get_player();
	std::shared_ptr<Character> character = get_character();

	character->save(ZoneServer, CHAR_SAVE_ALL);
	player->get_map()->get_map_container()->remove_player(player);
}
