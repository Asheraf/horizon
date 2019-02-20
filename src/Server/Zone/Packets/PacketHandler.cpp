/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
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
#include "Server/Common/Client.hpp"
#include "Server/Zone/Game/Atcommand/AtcommandExecutor.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Unit/Unit.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Map/MapThreadContainer.hpp"
#include "Server/Zone/Game/Map/Script/ScriptMgr.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Zone.hpp"
#include "Utility/Utility.hpp"

#include "Server/Zone/Packets/Ragexe/Packets.hpp"
#include "Server/Zone/Packets/Ragexe/PacketStructs.hpp"

#include <boost/bind.hpp>
#include <algorithm>

using namespace Horizon::Zone;
using namespace Horizon::Zone::Game;
using namespace Horizon::Zone::Game::Entities;
using namespace Horizon::Models::Character;

/**
 * @brief Packet Handler Constructor.
 */
PacketHandler::PacketHandler(std::shared_ptr<ZoneSocket> socket)
: Horizon::Base::PacketHandler<ZoneSocket>(socket)
{
	_session = socket->get_session();
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
#define HANDLER_FUNC(packet) add_packet_handler(Ragexe::packet, boost::bind(&PacketHandler::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CZ_CLIENT_VERSION)
	HANDLER_FUNC(CZ_RESTART)
	HANDLER_FUNC(CZ_REQ_DISCONNECT)
	HANDLER_FUNC(CZ_CHANGE_DIRECTION)
	HANDLER_FUNC(CZ_CHANGE_DIRECTION2)
	// Chat
	HANDLER_FUNC(CZ_REQUEST_CHAT)
	// Script
	HANDLER_FUNC(CZ_CONTACTNPC)
	HANDLER_FUNC(CZ_REQ_NEXT_SCRIPT)
	HANDLER_FUNC(CZ_CLOSE_DIALOG)
	HANDLER_FUNC(CZ_CHOOSE_MENU)
#undef HANDLER_FUNC
}

/*==============*
 * Handler Methods
 *==============*/
bool PacketHandler::Handle_CZ_CLIENT_VERSION(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_CLIENT_VERSION pkt;

	pkt << buf;

	ZoneLog->info("Account '{}' has successfully logged in.", get_socket()->get_session()->get_game_account()->get_id());

	return true;
}

bool PacketHandler::Handle_CZ_REQUEST_TIME(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_REQUEST_TIME pkt(buf.getOpCode());

	pkt << buf;

	Send_ZC_NOTIFY_TIME();

	return true;
}

bool PacketHandler::Handle_CZ_REQNAME(PacketBuffer &buf)
{
	std::shared_ptr<Player> player = get_socket()->get_session()->get_player();
	Ragexe::PACKET_CZ_REQNAME pkt(buf.getOpCode());
	pkt << buf;

	std::shared_ptr<Game::Entity> entity = player->get_nearby_entity(pkt.guid);

	if (entity == nullptr)
		return true;

	std::shared_ptr<Unit> unit = std::dynamic_pointer_cast<Unit>(entity);
	Send_ZC_ACK_REQNAME(unit->get_guid(), unit->get_name());

	return true;
}

bool PacketHandler::verify_new_connection(uint32_t auth_code, uint32_t account_id, uint32_t char_id)
{
	std::shared_ptr<ZoneSession> session = get_socket()->get_session();
	std::shared_ptr<SessionData> session_data = std::make_shared<SessionData>();

	if (!session_data->load(ZoneServer, account_id)) {
		ZoneLog->info("New connection attempt from unauthorized session '{}'.", auth_code);
		session->get_packet_handler()->Send_ZC_REFUSE_ENTER(ZONE_SERV_ERROR_REJECT);
		return false;
	}

	std::shared_ptr<GameAccount> game_account = std::make_shared<GameAccount>();

	if (!game_account->load(ZoneServer, account_id)) {
		ZoneLog->info("New connection attempt from unknown account '{}'.", account_id);
		session->get_packet_handler()->Send_ZC_REFUSE_ENTER(ZONE_SERV_ERROR_REJECT);
		return false;
	}

	session->set_session_data(session_data);
	session->set_game_account(game_account);
	session->set_character(std::make_shared<Character>(char_id));

	if (!session->get_character()->load_all(ZoneServer, char_id)) {
		ZoneLog->info("Attempted connection for non-existent character {} by account {}.", account_id, char_id);
		session->get_packet_handler()->Send_ZC_REFUSE_ENTER(ZONE_SERV_ERROR_REJECT);
		return false;
	}

	return true;
}

bool PacketHandler::process_player_entry()
{
	std::shared_ptr<ZoneSession> session = get_socket()->get_session();
	std::shared_ptr<Position> position = session->get_character()->get_position_data();

	// Initilaize The Player
	MapCoords mcoords(position->get_current_x(), position->get_current_y());

	std::shared_ptr<Player> player = std::make_shared<Player>(session->get_game_account()->get_id(),
															  mcoords,
															  session);
	session->set_player(player);
	set_player(player);

	std::shared_ptr<Map> map = MapMgr->get_map(position->get_current_map());

	if (!map) {
		ZoneLog->error("Map {} was not found or managed by any container! Login to player {} is denied.", position->get_current_map(), player->get_name());
		return false;
	}
	player->set_map(map);
	map->get_map_container()->add_player(map->get_name(), player);

	// Remove socket from updates on zone server after initial connection
	// it will be managed by the map container thread.
	ClientSocktMgr->set_socket_for_removal(get_socket());

	ZoneLog->info("New connection established for account '{}' using version '{}' from '{}'.",
				  session->get_game_account()->get_id(), session->get_session_data()->get_client_version(), get_socket()->remote_ip_address());

	return true;
}

bool PacketHandler::Handle_CZ_ENTER(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_ENTER pkt(buf.getOpCode());

	pkt << buf;

	if (!verify_new_connection(pkt.auth_code, pkt.account_id, pkt.char_id))
		return false;

	if (!process_player_entry())
		return false;

	// Send initial packets.
	Send_ZC_AID();
	Send_ZC_ACCEPT_ENTER3();

	return true;
}

bool PacketHandler::Handle_CZ_REQUEST_ACT(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_REQUEST_ACT pkt(buf.getOpCode());
	pkt << buf;
	printf("act %d %d\n", pkt.target_guid, pkt.action);

	return true;
}

bool PacketHandler::Handle_CZ_REQUEST_MOVE(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_REQUEST_MOVE pkt;
	pkt << buf;
	get_player()->move_to_pos(pkt.x, pkt.y);
	return true;
}

bool PacketHandler::Handle_CZ_RESTART(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_RESTART pkt(buf.getOpCode());

	pkt << buf;

	switch (pkt.type)
	{
	case 0: std::cout << "Respawn" << std::endl; break;
	case 1:
			Send_ZC_RESTART_ACK(1);
			get_player()->notify_nearby_players_of_self(EVP_NOTIFY_LOGGED_OUT);
			break;
	}

	return true;
}

bool PacketHandler::Handle_CZ_REQ_DISCONNECT(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_REQ_DISCONNECT pkt;

	pkt << buf;
	ZoneLog->info("Character '{}' has logged out. {}", get_session()->get_character()->get_name(), pkt.type);
	Send_ZC_ACK_REQ_DISCONNECT(true);
	get_session()->get_session_data()->remove(ZoneServer);
	get_player()->notify_nearby_players_of_self(EVP_NOTIFY_LOGGED_OUT);
	return true;
}

bool PacketHandler::Handle_CZ_CHOOSE_MENU(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_CHOOSE_MENU pkt;

	pkt << buf;

	if (pkt.choice != -1) {
		auto scr_mgr = get_player()->get_map()->get_map_container()->get_script_manager();
		scr_mgr->continue_npc_script_for_player(get_player(), pkt.guid, pkt.choice);
	}

	return true;
}

bool PacketHandler::Handle_CZ_CONTACTNPC(PacketBuffer &buf)
{
	uint32_t current_npc_guid = get_player()->get_npc_contact_guid();
	Ragexe::PACKET_CZ_CONTACTNPC pkt;

	pkt << buf;

	if (current_npc_guid != 0 && current_npc_guid != pkt.guid) {
		ZoneLog->warn("Player {} has attempted to contact npc {} while already engaged in another npc {}. Possible hacking!", get_player()->get_name(), pkt.guid, current_npc_guid);
		return true;
	}

	auto scr_mgr = get_player()->get_map()->get_map_container()->get_script_manager();
	scr_mgr->contact_npc_for_player(get_player(), pkt.guid);

	return true;
}

bool PacketHandler::Handle_CZ_REQ_NEXT_SCRIPT(PacketBuffer &buf)
{
	uint32_t current_npc_guid = get_player()->get_npc_contact_guid();
	Ragexe::PACKET_CZ_REQ_NEXT_SCRIPT pkt;

	pkt << buf;

	if (pkt.guid == current_npc_guid) {
		auto scr_mgr = get_player()->get_map()->get_map_container()->get_script_manager();
		scr_mgr->continue_npc_script_for_player(get_player(), pkt.guid);
	} else {
		ZoneLog->warn("Player {} has attempted to contact npc {} while already engaged in another npc {}. Possible hacking!", get_player()->get_name(), pkt.guid, current_npc_guid);
	}

	return true;
}

bool PacketHandler::Handle_CZ_CLOSE_DIALOG(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_CLOSE_DIALOG pkt;

	pkt << buf;

	if (pkt.guid == get_player()->get_npc_contact_guid()) {
		get_player()->set_npc_contact_guid(0);
	}

	return true;
}

bool PacketHandler::Handle_CZ_INPUT_EDITDLG(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_INPUT_EDITDLG pkt;

	pkt << buf;

	return true;
}

bool PacketHandler::Handle_CZ_INPUT_EDITDLGSTR(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_INPUT_EDITDLGSTR pkt;

	pkt << buf;

	return true;
}

bool PacketHandler::Handle_CZ_CHANGE_DIRECTION(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_CHANGE_DIRECTION pkt;

	pkt << buf;

	return true;
}

bool PacketHandler::Handle_CZ_CHANGE_DIRECTION2(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_CHANGE_DIRECTION2 pkt;

	pkt << buf;

	return true;
}

bool PacketHandler::Handle_CZ_REQUEST_CHAT(PacketBuffer &buf)
{
	uint32_t guid = get_player()->get_guid();
	Ragexe::PACKET_CZ_REQUEST_CHAT pkt;
	int msg_first_char = get_player()->get_name().size() + 3;

	pkt << buf;

	std::string message;

	if (pkt.message[msg_first_char] == '@') {
		AtcommandExecutor atcmd(get_player(), &pkt.message[msg_first_char + 1]);
		atcmd.execute();
		return true;
	}

	Send_ZC_NOTIFY_CHAT(guid, pkt.message, GRID_NOTIFY_AREA_WOS);
	Send_ZC_NOTIFY_PLAYERCHAT(pkt.message);
	
	return true;
}

/*==============*
 * Sender Methods
 *==============*/
void PacketHandler::Send_ZC_REFUSE_ENTER(zone_server_reject_types error)
{
	Ragexe::PACKET_ZC_REFUSE_ENTER pkt;
	pkt.error = error;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_RESTART_ACK(uint8_t type)
{
	Ragexe::PACKET_ZC_RESTART_ACK pkt;
	pkt.type = type;
	send_packet(pkt.serialize());

	ZoneLog->info("Character '{}' has moved to the character server.", get_session()->get_character()->get_name());
}

void PacketHandler::Send_ZC_ACK_REQ_DISCONNECT(bool allowed)
{
	Ragexe::PACKET_ZC_ACK_REQ_DISCONNECT pkt;
	pkt.type = allowed ? 0 : 1;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_AID()
{
	Ragexe::PACKET_ZC_AID pkt;
	pkt.account_id = get_session()->get_game_account()->get_id();
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_ACCEPT_ENTER3()
{
	std::shared_ptr<Character> character = get_socket()->get_session()->get_character();
	std::shared_ptr<Position> position = character->get_position_data();
	std::shared_ptr<UISettings> ui_settings = character->get_ui_settings();

	Ragexe::PACKET_ZC_ACCEPT_ENTER3 pkt;
	int x = position->get_current_x();
	int y = position->get_current_y();

	if (x == 0 && y == 0) {
		if ((x = position->get_saved_x()) == 0)
			x = 0;
		if ((y = position->get_saved_y()) == 0)
			y = 0;
	}

	pkt.start_time = (uint32_t) get_sys_time();
	pkt.x_size = pkt.y_size = 5;
	pkt.font = ui_settings->get_font();
	pkt.gender = character->get_gender();
	send_packet(pkt.serialize(x, y, DIR_SOUTH));
}

void PacketHandler::Send_ZC_ACCEPT_ENTER2()
{
	std::shared_ptr<Models::Character::Character> character = get_socket()->get_session()->get_character();
	std::shared_ptr<Models::Character::Position> position = character->get_position_data();
	std::shared_ptr<Models::Character::UISettings> ui_settings = character->get_ui_settings();

	Ragexe::PACKET_ZC_ACCEPT_ENTER2 pkt;
	int x = position->get_current_x();
	int y = position->get_current_y();

	if (x == 0 && y == 0) {
		if ((x = position->get_saved_x()) == 0)
			x = 0;
		if ((y = position->get_saved_y()) == 0)
			y = 0;
	}

	pkt.start_time = (uint32_t) get_sys_time();
	pkt.x_size = pkt.y_size = 5;
	pkt.font = ui_settings->get_font();
	send_packet(pkt.serialize(x, y, DIR_SOUTH));
}

void PacketHandler::Send_ZC_NPCACK_MAPMOVE(std::string &map_name, uint16_t x, uint16_t y)
{
	Ragexe::PACKET_ZC_NPCACK_MAPMOVE pkt;

	if (map_name.size() + 4 > MAP_NAME_LENGTH_EXT) {
		ZoneLog->error("Copying '.gat' to map name {} would exceed length.", map_name);
		return;
	}

	map_name.append(".gat");

	strncpy(pkt.map_name, map_name.c_str(), MAP_NAME_LENGTH_EXT);

	pkt.x = x;
	pkt.y = y;

	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_TIME()
{
	Ragexe::PACKET_ZC_NOTIFY_TIME pkt;
	pkt.timestamp = (uint32_t) get_sys_time();
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_MOVE(uint32_t guid, MapCoords from, MapCoords to)
{
	std::shared_ptr<Character> character = get_session()->get_character();
	Ragexe::PACKET_ZC_NOTIFY_MOVE pkt;

	pkt.guid = guid;

	send_packet(pkt.serialize(from.x(), from.y(), to.x(), to.y()));
}

void PacketHandler::Send_ZC_NOTIFY_PLAYERMOVE(uint16_t to_x, uint16_t to_y)
{
	MapCoords mcoords = get_player()->get_map_coords();
	Ragexe::PACKET_ZC_NOTIFY_PLAYERMOVE pkt;

	send_packet(pkt.serialize(mcoords.x(), mcoords.y(), to_x, to_y));
}

void PacketHandler::Send_ZC_STOPMOVE(uint32_t guid, uint16_t x, uint16_t y)
{
	Ragexe::PACKET_ZC_STOPMOVE pkt;
	pkt.guid = guid;
	pkt.x = x;
	pkt.y = y;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_PAR_CHANGE(uint16_t type, uint16_t value)
{
	Ragexe::PACKET_ZC_PAR_CHANGE pkt;
	pkt.type = type;
	pkt.value = value;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_SAY_DIALOG(uint32_t npc_id, std::string &message)
{
	Ragexe::PACKET_ZC_SAY_DIALOG pkt;
	pkt.packet_length = 8 + message.size();
	pkt.guid = npc_id;
	send_packet(pkt.serialize(message));
}

void PacketHandler::Send_ZC_WAIT_DIALOG(uint32_t npc_id)
{
	Ragexe::PACKET_ZC_WAIT_DIALOG pkt;
	pkt.guid = npc_id;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_CLOSE_DIALOG(uint32_t npc_id)
{
	Ragexe::PACKET_ZC_CLOSE_DIALOG pkt;
	pkt.guid = npc_id;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_MENU_LIST(uint32_t npc_id, std::string const &menu_list)
{
	Ragexe::PACKET_ZC_MENU_LIST pkt;
	pkt.packet_length = 8 + menu_list.size();
	pkt.guid = npc_id;
	send_packet(pkt.serialize(menu_list));
}

void PacketHandler::Send_ZC_OPEN_EDITDLG(uint32_t npc_id)
{
	Ragexe::PACKET_ZC_OPEN_EDITDLG pkt;

	pkt.guid = npc_id;

	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_OPEN_EDITDLGSTR(uint32_t npc_id)
{
	Ragexe::PACKET_ZC_OPEN_EDITDLGSTR pkt;
	pkt.guid = npc_id;
	send_packet(pkt.serialize());
}


void PacketHandler::Send_ZC_STATUS()
{
	Ragexe::PACKET_ZC_STATUS pkt;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_NEWENTRY5()
{
	Ragexe::PACKET_ZC_NOTIFY_NEWENTRY5 pkt;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_UPDATE_MAPINFO(uint16_t x, uint16_t y, const char *map_name, uint16_t type)
{
	Ragexe::PACKET_ZC_UPDATE_MAPINFO pkt;
	pkt.x = x;
	pkt.y = y;
	memcpy(pkt.map_name, map_name, sizeof(MAP_NAME_LENGTH_EXT));
	pkt.type = type;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_GROUNDSKILL(uint16_t skill_id, uint32_t guid, uint16_t level, uint16_t x, uint16_t y, uint32_t duration)
{
	Ragexe::PACKET_ZC_NOTIFY_GROUNDSKILL pkt;

	pkt.skill_id = skill_id;
	pkt.guid = guid;
	pkt.level = level;
	pkt.x = x;
	pkt.y = y;
	pkt.duration = duration;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_STANDENTRY(entity_viewport_entry const &/*entry*/)
{
	Ragexe::PACKET_ZC_NOTIFY_STANDENTRY10 pkt;
	// set here params.
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_MOVEENTRY(entity_viewport_entry const &/*entry*/)
{
	Ragexe::PACKET_ZC_NOTIFY_MOVEENTRY10 pkt;
	// set here params.
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_CHAT(uint32_t guid, std::string message, player_notifier_types type)
{
	Ragexe::PACKET_ZC_NOTIFY_CHAT pkt;
	PacketBuffer buf;

	pkt.guid = guid;
	buf = pkt.serialize(message);

	get_player()->template notify_in_area<PacketBuffer>(buf, type);
}

void PacketHandler::Send_ZC_NOTIFY_PLAYERCHAT(std::string message)
{
	Ragexe::PACKET_ZC_NOTIFY_PLAYERCHAT pkt;

	pkt.packet_length = 4 + message.size();
	send_packet(pkt.serialize(message));
}

void PacketHandler::Send_ZC_NPC_CHAT(uint32_t guid, std::string message, player_notifier_types type)
{
	Ragexe::PACKET_ZC_NPC_CHAT pkt;

	pkt.guid = guid;

	PacketBuffer buf = pkt.serialize(message);

	get_player()->template notify_in_area<PacketBuffer>(buf, type);
}

void PacketHandler::Send_ZC_ACK_REQNAME(uint32_t guid, std::string name)
{
	Ragexe::PACKET_ZC_ACK_REQNAME pkt;
	pkt.guid = guid;
	std::strncpy(pkt.name, name.c_str(), sizeof(pkt.name));
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_VANISH(uint32_t guid, uint8_t type)
{
	Ragexe::PACKET_ZC_NOTIFY_VANISH pkt;
	pkt.guid = guid;
	pkt.type = type;
	send_packet(pkt.serialize());
}
