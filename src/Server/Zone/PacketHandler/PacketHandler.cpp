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

#include "PacketHandler.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/PacketHandler/Packets.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Zone.hpp"
#include "Utility/Utility.hpp"

#include <boost/bind.hpp>

using namespace Horizon::Zone;

/**
 * @brief Packet Handler Constructor.
 */
PacketHandler::PacketHandler(std::shared_ptr<ZoneSocket> socket)
: Horizon::Base::PacketHandler<ZoneSocket>(socket)
{
	initialize_handlers();
}

/**
 * @brief Packet Handler destructor.
 */
PacketHandler::~PacketHandler()
{
}

/**
 * @brief Initialize packet handlers.
 */
void PacketHandler::initialize_handlers()
{
#define HANDLER_FUNC(packet) add_packet_handler(packet, boost::bind(&PacketHandler::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CZ_LOGIN_TIMESTAMP);
	HANDLER_FUNC(CZ_RESTART);
	HANDLER_FUNC(CZ_REQ_DISCONNECT);
	HANDLER_FUNC(CZ_CHANGE_DIRECTION);
	HANDLER_FUNC(CZ_CHANGE_DIRECTION2);
#undef HANDLER_FUNC
}

/*==============*
 * Handler Methods
 *==============*/
bool PacketHandler::Handle_CZ_LOGIN_TIMESTAMP(PacketBuffer &buf)
{
	PACKET_CZ_LOGIN_TIMESTAMP pkt;

	buf >> pkt;

	ZoneLog->info("Account '{}' has successfully logged in.", get_socket()->get_session()->get_game_account()->get_id());

	return true;
}

bool PacketHandler::Handle_CZ_REQUEST_TIME(PacketBuffer &buf)
{
	PACKET_CZ_REQUEST_TIME pkt(buf.getOpCode());

	buf >> pkt;

	Send_ZC_NOTIFY_TIME();

	return true;
}

bool PacketHandler::Handle_CZ_REQNAME(PacketBuffer &buf)
{
	PACKET_CZ_REQNAME pkt(buf.getOpCode());

	buf >> pkt;

	// find and return guid name.

	return true;
}

bool PacketHandler::Handle_CZ_ENTER(PacketBuffer &buf)
{
	std::shared_ptr<ZoneSession> session = get_socket()->get_session();

	PACKET_CZ_ENTER pkt(buf.getOpCode());

	buf >> pkt;

	std::shared_ptr<SessionData> session_data = std::make_shared<SessionData>();

	if (!session_data->load(ZoneServer, pkt.account_id)) {
		ZoneLog->info("New connection attempt from unauthorized session '{}'.", pkt.auth_code);
		session->get_packet_handler()->Send_ZC_ERROR(ZONE_SERV_ERROR_REJECT);
		return false;
	}

	std::shared_ptr<GameAccount> game_account = std::make_shared<GameAccount>();

	if (!game_account->load(ZoneServer, pkt.account_id)) {
		ZoneLog->info("New connection attempt from unknown account '{}'.", pkt.account_id);
		session->get_packet_handler()->Send_ZC_ERROR(ZONE_SERV_ERROR_REJECT);
		return false;
	}

	session->set_session_data(session_data);
	session->set_game_account(game_account);

	session->set_character(std::make_shared<Character>(pkt.char_id));

	if (!session->get_character()->load_all(ZoneServer, pkt.char_id)) {
		ZoneLog->info("Attempted connection for non-existent character {} by account {}.", pkt.account_id, pkt.char_id);
		session->get_packet_handler()->Send_ZC_ERROR(ZONE_SERV_ERROR_REJECT);
		return false;
	}

	// Send initial packets.
	Send_ZC_ACCOUNT_ID();
	Send_ZC_ACCEPT_CONNECTION();

	std::shared_ptr<Position> position = session->get_character()->get_position_data();
	
	// Initilaize The Player
	MapCoords mcoords(position->get_current_x(), position->get_current_y());

	std::shared_ptr<Player> player = std::make_shared<Player>(pkt.account_id, mcoords, session);
	session->set_player(player);

	player->set_map(MapMgr->add_player_to_map(position->get_current_map(), player));

	player->initialize();

	// Remove socket from updates on zone server after initial connection
	// it will be managed by the map container thread.
	ClientSocktMgr->set_socket_for_removal(get_socket()->get_socket_id());

	ZoneLog->info("New connection established for account '{}' using version '{}' from '{}'.",
				  pkt.account_id, session->get_session_data()->get_client_version(), get_socket()->remote_ip_address());

	return true;
}

bool PacketHandler::Handle_CZ_REQUEST_ACT(PacketBuffer &buf)
{
	PACKET_CZ_REQUEST_ACT pkt(buf.getOpCode());
	buf >> pkt;
	printf("act %d %d\n", pkt.target_guid, pkt.action);

	return true;
}

bool PacketHandler::Handle_CZ_REQUEST_MOVE(PacketBuffer &buf)
{
	uint16_t x = 0, y = 0;
	uint8_t dir = 0;
	PACKET_CZ_REQUEST_MOVE pkt(buf.getOpCode());

	buf >> pkt;

	UnpackPosition(pkt.packed_destination, &x, &y, &dir);

	get_socket()->get_session()->get_player()->move_to_pos(x, y);

	return true;
}

bool PacketHandler::Handle_CZ_RESTART(PacketBuffer &buf)
{
	PACKET_CZ_RESTART pkt(buf.getOpCode());

	buf >> pkt;

	switch (pkt.type)
	{
	case 0: std::cout << "Respawn" << std::endl; break;
	case 1: Send_ZC_RESTART_ACK(1); break;
	}

	return true;
}

bool PacketHandler::Handle_CZ_REQ_DISCONNECT(PacketBuffer &buf)
{
	PACKET_CZ_REQ_DISCONNECT pkt;
	auto session = get_socket()->get_session();
	auto player = session->get_player();

	buf >> pkt;

	session->get_session_data()->remove(ZoneServer);

	session->get_character()->save(ZoneServer, CHAR_SAVE_ALL);

	if (player->get_map())
		MapMgr->remove_player_from_map(player->get_map()->get_name(), player);

	ZoneLog->info("Character '{}' has logged out. {}", session->get_character()->get_name(), pkt.type);

	Send_ZC_ACK_REQ_DISCONNECT(true);
	return true;
}

bool PacketHandler::Handle_CZ_CHOOSE_MENU(PacketBuffer &buf)
{
	PACKET_CZ_CHOOSE_MENU pkt;

	buf >> pkt;

	return true;
}

bool PacketHandler::Handle_CZ_REQ_NEXT_SCRIPT(PacketBuffer &buf)
{
	PACKET_CZ_REQ_NEXT_SCRIPT pkt;

	buf >> pkt;

	return true;
}

bool PacketHandler::Handle_CZ_INPUT_EDITDLG(PacketBuffer &buf)
{
	PACKET_CZ_INPUT_EDITDLG pkt;

	buf >> pkt;

	return true;
}

bool PacketHandler::Handle_CZ_INPUT_EDITDLGSTR(PacketBuffer &buf)
{
	PACKET_CZ_INPUT_EDITDLGSTR pkt;

	buf >> pkt;

	char message[pkt.packet_length - 6];
	buf.read(message, sizeof(message));

	return true;
}

bool PacketHandler::Handle_CZ_CLOSE_DIALOG(PacketBuffer &buf)
{
	PACKET_CZ_CLOSE_DIALOG pkt;

	buf >> pkt;

	return true;
}

bool PacketHandler::Handle_CZ_CHANGE_DIRECTION(PacketBuffer &buf)
{
	return true;
}

bool PacketHandler::Handle_CZ_CHANGE_DIRECTION2(PacketBuffer &buf)
{
	return true;
}

/*==============*
 * Sender Methods
 *==============*/
void PacketHandler::Send_ZC_ERROR(zone_server_reject_types error)
{
	PACKET_ZC_ERROR pkt;
	pkt.error = error;
	send_packet(pkt);
}

void PacketHandler::Send_ZC_RESTART_ACK(uint8_t type)
{
	auto session = get_socket()->get_session();
	auto player = session->get_player();

	PACKET_ZC_RESTART_ACK pkt;

	pkt.type = type;

	if (player->get_map())
		MapMgr->remove_player_from_map(player->get_map()->get_name(), player);

	session->get_character()->save(ZoneServer, CHAR_SAVE_ALL);

	ZoneLog->info("Character '{}' has moved to the character server.", session->get_character()->get_name());

	send_packet(pkt);
}

void PacketHandler::Send_ZC_ACK_REQ_DISCONNECT(bool allowed)
{
	PACKET_ZC_ACK_REQ_DISCONNECT pkt;
	pkt.type = allowed ? 0 : 1;
	send_packet(pkt);
}

void PacketHandler::Send_ZC_ACCOUNT_ID()
{
	PACKET_ZC_ACCOUNT_ID pkt;
	pkt.account_id = get_socket()->get_session()->get_game_account()->get_id();
	send_packet(pkt);
}

void PacketHandler::Send_ZC_ACCEPT_CONNECTION()
{
	std::shared_ptr<Position> position = get_socket()->get_session()->get_character()->get_position_data();

	PACKET_ZC_ACCEPT_CONNECTION pkt;
	int x = position->get_current_x();
	int y = position->get_current_y();

	if (x == 0 && y == 0) {
		if ((x = position->get_saved_x()) == 0)
			x = 0;
		if ((y = position->get_saved_y()) == 0)
			y = 0;
	}

	pkt.start_time = time(nullptr);
	PackPosition(pkt.packed_position, x, y, 4);
	pkt.x_size = pkt.y_size = 5;
	pkt.font = 0;
	pkt.gender = get_socket()->get_session()->get_game_account()->get_gender();
	send_packet(pkt);
}

void PacketHandler::Send_ZC_NPCACK_MAPMOVE(std::string const &map_name, uint16_t x, uint16_t y)
{
	PACKET_ZC_NPCACK_MAPMOVE pkt;
	strncpy(pkt.map_name, map_name.c_str(), MAP_NAME_LENGTH_EXT);
	pkt.x = x;
	pkt.y = y;
	send_packet(pkt);
}

void PacketHandler::Send_ZC_NOTIFY_TIME()
{
	PACKET_ZC_NOTIFY_TIME pkt;
	pkt.timestamp = time(nullptr);
	send_packet(pkt);
}

void PacketHandler::Send_ZC_NOTIFY_UNITMOVE(uint32_t guid, uint16_t x1, uint16_t y1)
{
	int x0 = 0, y0 = 0;
	std::shared_ptr<Character> character = get_socket()->get_session()->get_character();
	PACKET_ZC_NOTIFY_UNITMOVE pkt;

	pkt.guid = guid;
	x0 = character->get_position_data()->get_current_x();
	y0 = character->get_position_data()->get_current_y();
	PackPosition(pkt.packed_pos, x0, y0, x1, y1, 8, 8);
	pkt.timestamp = (uint32_t) time(nullptr);
	send_packet(pkt);
}

void PacketHandler::Send_ZC_NOTIFY_PLAYERMOVE(uint16_t x1, uint16_t y1)
{
	int x0 = 0, y0 = 0;
	std::shared_ptr<Player> player = get_socket()->get_session()->get_player();
	PACKET_ZC_NOTIFY_PLAYERMOVE pkt;

	pkt.timestamp = get_sys_time();
	x0 = player->get_map_coords().x();
	y0 = player->get_map_coords().y();
	PackPosition(pkt.packed_pos, x0, y0, x1, y1, 8, 8);

	send_packet(pkt);
}

void PacketHandler::Send_ZC_STOPMOVE(uint32_t guid, uint16_t x, uint16_t y)
{
	PACKET_ZC_STOPMOVE pkt;
	pkt.guid = guid;
	pkt.x = x;
	pkt.y = y;
	send_packet(pkt);
}

void PacketHandler::Send_ZC_PAR_CHANGE(uint16_t type, uint16_t value)
{
	PACKET_ZC_PAR_CHANGE pkt;
	pkt.type = type;
	pkt.value = value;
	send_packet(pkt);
}

void PacketHandler::Send_ZC_SAY_DIALOG(uint16_t npc_id, std::string &message)
{
	PACKET_ZC_SAY_DIALOG pkt;
	PacketBuffer buf;

	pkt.npc_id = npc_id;

	buf << pkt;
	buf.append(message.c_str(), message.length());

	send_packet(buf);
}

void PacketHandler::Send_ZC_WAIT_DIALOG(uint16_t npc_id)
{
	PACKET_ZC_WAIT_DIALOG pkt;

	pkt.npc_id = npc_id;

	send_packet(pkt);
}

void PacketHandler::Send_ZC_MENU_LIST(uint16_t npc_id, std::string &menu_list)
{
	PACKET_ZC_MENU_LIST pkt;
	PacketBuffer buf;

	pkt.npc_id = npc_id;
	pkt.packet_length = sizeof(PACKET_ZC_MENU_LIST) + menu_list.size();

	buf.append(pkt);
	buf.append(menu_list.c_str(), menu_list.size());

	send_packet(buf);
}

void PacketHandler::Send_ZC_OPEN_EDITDLG(uint16_t npc_id)
{
	PACKET_ZC_OPEN_EDITDLG pkt;

	pkt.npc_id = npc_id;

	send_packet(pkt);
}

void PacketHandler::Send_ZC_OPEN_EDITDLGSTR(uint16_t npc_id)
{
	PACKET_ZC_OPEN_EDITDLGSTR pkt;

	pkt.npc_id = npc_id;

	send_packet(pkt);
}


void PacketHandler::Send_ZC_INITIAL_STATUS()
{
	PACKET_ZC_INITIAL_STATUS pkt;
	send_packet(pkt);
}

void PacketHandler::Send_ZC_SPAWN_UNIT()
{
	PACKET_ZC_SPAWN_UNIT pkt;
	send_packet(pkt);
}

void PacketHandler::Send_ZC_UPDATE_MAPINFO(uint16_t x, uint16_t y, const char *map_name, uint16_t type)
{
	PACKET_ZC_UPDATE_MAPINFO pkt;
	pkt.x = x;
	pkt.y = y;
	memcpy(pkt.map_name, map_name, sizeof(MAP_NAME_LENGTH_EXT));
	pkt.type = type;
	send_packet(pkt);
}

void PacketHandler::Send_ZC_NOTIFY_GROUNDSKILL(uint16_t skill_id, uint32_t guid, uint16_t level, uint16_t x, uint16_t y, uint32_t duration)
{
	PACKET_ZC_NOTIFY_GROUNDSKILL pkt;

	pkt.skill_id = skill_id;
	pkt.guid = guid;
	pkt.level = level;
	pkt.x = x;
	pkt.y = y;
	pkt.duration = duration;
	send_packet(pkt);
}

void PacketHandler::Send_ZC_NOTIFY_STANDENTRY10(Game::Entity *entity)
{
	PACKET_ZC_NOTIFY_STANDENTRY10 pkt(ZC_NOTIFY_STANDENTRY10);
	// set here params.
	send_packet(pkt);
}
