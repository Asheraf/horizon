
#include "Player.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/PacketHandler/PacketHandler.hpp"
#include "Server/Common/Models/GameAccount.hpp"

using namespace Horizon::Models::Character;
using namespace Horizon::Zone::Game::Entities;

Player::Player(uint32_t guid, std::shared_ptr<ZoneSession> session)
: Unit(guid, ENTITY_PLAYER), _session(session)
{
	//
}

Player::Player(uint32_t guid, std::string const &map_name, MapCoords mcoords, std::shared_ptr<ZoneSession> session)
: Unit(guid, ENTITY_PLAYER, map_name, mcoords), _session(session)
{
	//
}

Player::Player(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords, std::shared_ptr<ZoneSession> session)
: Unit(guid, ENTITY_PLAYER, map_name, mcoords, gcoords), _session(session)
{
	//
}

Player::~Player()
{
	//
}

void Player::initialize()
{
	Unit::initialize();
	//get_session()->get_packet_handler()->Send_ZC_INITIAL_STATUS();
}

void Player::update_position(uint16_t x, uint16_t y)
{
	get_session()->get_packet_handler()->Send_ZC_NOTIFY_PLAYERMOVE(x, y);
	get_character()->get_position_data()->set_current_x(x);
	get_character()->get_position_data()->set_current_y(y);
}

void Player::stop_movement()
{
	MapCoords &coords = get_map_coords();
	get_session()->get_packet_handler()->Send_ZC_STOPMOVE(coords.x(), coords.y());
}

std::shared_ptr<Character> Player::get_character()
{
	return get_session()->get_character();
}

void Player::update(uint32_t diff)
{
	Unit::update(diff);	
}

void Player::update_status()
{
	get_session()->get_packet_handler()->Send_ZC_PAR_CHANGE(0, 200);
//	get_session()->get_packet_handler()->Send_ZC_PAR_CHANGE(24, 1000);
//	get_session()->get_packet_handler()->Send_ZC_PAR_CHANGE(25, 1500);
}
