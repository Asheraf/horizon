
#include "Player.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/PacketHandler/PacketHandler.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"

using namespace Horizon::Models::Character;
using namespace Horizon::Zone::Game::Entities;

Player::Player(uint32_t guid, std::shared_ptr<ZoneSession> session)
: Unit(guid, ENTITY_PLAYER), _session(session)
{
	//
}

Player::Player(uint32_t guid, MapCoords mcoords, std::shared_ptr<ZoneSession> session)
: Unit(guid, ENTITY_PLAYER, mcoords), _session(session)
{
	//
}

Player::Player(uint32_t guid, MapCoords mcoords, GridCoords gcoords, std::shared_ptr<ZoneSession> session)
: Unit(guid, ENTITY_PLAYER, mcoords, gcoords), _session(session)
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
	update_status();
	update_viewport();
	//get_session()->get_packet_handler()->Send_ZC_INITIAL_STATUS();
}

void Player::update_position(uint16_t x, uint16_t y)
{
	std::shared_ptr<Position> p = get_character()->get_position_data();
	get_session()->get_packet_handler()->Send_ZC_NOTIFY_PLAYERMOVE(x, y);
	p->set_current_x(x);
	p->set_current_y(y);
}

void Player::stop_movement()
{
	MapCoords &coords = get_map_coords();
	get_session()->get_packet_handler()->Send_ZC_STOPMOVE(get_guid(), coords.x(), coords.y());
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
	get_session()->get_packet_handler()->Send_ZC_PAR_CHANGE(0, DEFAULT_WALK_SPEED);
	get_session()->get_packet_handler()->Send_ZC_PAR_CHANGE(24, 1000);
	get_session()->get_packet_handler()->Send_ZC_PAR_CHANGE(25, 1500);
}

void Player::update_viewport()
{
	GridViewPortUpdater updater(shared_from_this());
	GridReferenceContainerVisitor<GridViewPortUpdater, GridReferenceContainer<AllEntityTypes>> update_caller(updater);

	MapCoords lower_bounds = get_map_coords().at_range<MAX_CELLS_PER_MAP>(-14);
	MapCoords upper_bounds = get_map_coords().at_range<MAX_CELLS_PER_MAP>(14);

	get_map()->visit(lower_bounds.scale<MAX_CELLS_PER_GRID, MAX_GRIDS_PER_MAP>(), upper_bounds.scale<MAX_CELLS_PER_GRID, MAX_GRIDS_PER_MAP>(), update_caller);
}

void Player::add_entity_to_viewport(Entity *entity)
{
	get_session()->get_packet_handler()->Send_ZC_NOTIFY_STANDENTRY10(entity);
}
