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
#include "Server/Zone/Game/Models/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Interface/InterAPI.hpp"
#include "Server/Zone/PacketHandler/Packets.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
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
#undef HANDLER_FUNC
}

/*==============*
 * Handler Methods
 *==============*/
void PacketHandler::Handle_CZ_LOGIN_TIMESTAMP(PacketBuffer &buf)
{
	PACKET_CZ_LOGIN_TIMESTAMP pkt;
	buf >> pkt;
	ZoneLog->info("Account '{}' has successfully logged in.", get_socket()->get_session()->get_game_account()->get_id());
}

void PacketHandler::Handle_CZ_REQUEST_TIME(PacketBuffer &buf)
{
	PACKET_CZ_REQUEST_TIME pkt(buf.getOpCode());
	buf >> pkt;
	Send_ZC_NOTIFY_TIME();
}

void PacketHandler::Handle_CZ_REQNAME(PacketBuffer &buf)
{
	PACKET_CZ_REQNAME pkt(buf.getOpCode());
	buf >> pkt;
	// find and return guid name.
}

void PacketHandler::Handle_CZ_ENTER(PacketBuffer &buf)
{
	std::shared_ptr<ZoneSession> session = get_socket()->get_session();
	PACKET_CZ_ENTER pkt(buf.getOpCode());
	buf >> pkt;

	session->set_session_data(ZoneInterAPI->get_session_data(pkt.auth_code));
	if (session->get_session_data() == nullptr) {
		ZoneLog->info("New connection attempt from unauthorized session '{}'.", pkt.auth_code);
		session->get_packet_handler()->Send_ZC_ERROR(ZONE_SERV_ERROR_REJECT);
		return;
	}

	session->set_game_account(ZoneInterAPI->get_game_account(pkt.account_id));
	if (session->get_game_account() == nullptr) {
		ZoneLog->info("New connection attempt from unknown account '{}'.", pkt.account_id);
		session->get_packet_handler()->Send_ZC_ERROR(ZONE_SERV_ERROR_REJECT);
		return;
	}

	session->set_character(std::make_shared<Character>());
	if (!session->get_character()->load_all(ZoneServer, pkt.char_id)) {
		ZoneLog->info("Attempted connection for non-existent character {} by account {}.", pkt.account_id, pkt.char_id);
		session->get_packet_handler()->Send_ZC_ERROR(ZONE_SERV_ERROR_REJECT);
		return;
	}

	// Send initial packets.
	Send_ZC_ACCOUNT_ID();
	Send_ZC_ACCEPT_CONNECTION();

	// Initilaize The Player
	MapCoords mcoords(session->get_character()->get_position_data()->get_current_x(),
					  session->get_character()->get_position_data()->get_current_y());

	std::shared_ptr<Player> player = std::make_shared<Player>(pkt.account_id,
															  session->get_character()->get_position_data()->get_current_map(),
															  mcoords,
															  session);
	session->set_player(player);
	player->initialize();
	ZoneServer->add_player(session->get_game_account()->get_id(), player);
	
	//get_packet_handler()->Send_ZC_NPCACK_MAPMOVE("prontera", 101, 120);
	ZoneLog->info("New connection established for account '{}' using version '{}' from '{}'.",
				  pkt.account_id, session->get_session_data()->get_client_version(), get_socket()->remote_ip_address());
}

void PacketHandler::Handle_CZ_REQUEST_ACT(PacketBuffer &buf)
{
	PACKET_CZ_REQUEST_ACT pkt(buf.getOpCode());
	buf >> pkt;
	printf("act %d %d\n", pkt.target_guid, pkt.action);
}

void PacketHandler::Handle_CZ_REQUEST_MOVE(PacketBuffer &buf)
{
	uint16_t x = 0, y = 0;
	uint8_t dir = 0;
	PACKET_CZ_REQUEST_MOVE pkt(buf.getOpCode());

	buf >> pkt;

	UnpackPosition(pkt.packed_destination, &x, &y, &dir);

	get_socket()->get_session()->get_player()->move_to_pos(x, y);
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

	pkt.timestamp = (uint32_t) time(nullptr);
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
