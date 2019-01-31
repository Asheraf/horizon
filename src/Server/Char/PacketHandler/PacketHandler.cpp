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
#include "Server/Char/Char.hpp"
#include "Server/Char/PacketHandler/Packets.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Char/Database/Query.hpp"
#include "Server/Common/Models/Configuration/CharServerConfiguration.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/GameAccount.hpp"

#include <boost/bind.hpp>
#include <string>

using namespace Horizon::Char;

/**
 * @brief Packet Handler Constructor.
 */
PacketHandler::PacketHandler(std::shared_ptr<CharSocket> socket)
: Horizon::Base::PacketHandler<CharSocket>(socket)
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
	HANDLER_FUNC(CH_KEEP_ALIVE);
	HANDLER_FUNC(CH_CREATE);
	HANDLER_FUNC(CH_DELETE_START);
	HANDLER_FUNC(CH_DELETE_CANCEL);
	HANDLER_FUNC(CH_DELETE_ACCEPT);
	HANDLER_FUNC(CH_SELECT);
#undef HANDLER_FUNC
}

/*==============*
 * Handler Methods
 *==============*/

/**
 * @brief Receive and handle the CHAR_CONNCET packet.
 * @param[in|out] buf    Validated PacketBuffer received by the char-server.
 */
bool PacketHandler::Handle_CH_CONNECT(PACKET_CH_CONNECT &/*pkt*/)
{
	CharQuery->AllCharactersByAccount(get_socket()->get_session()->get_game_account());
	
	// Send acceptance notice to client.
	Send_HC_ACCOUNT_ID();         // 1st

	// Send character list info.
	Send_HC_SLOT_INFO_ACK();      // 2nd
	Send_HC_CHAR_LIST_ACK();           // 3rd
	Send_HC_BAN_LIST_ACK();       // 4th
	Send_HC_PINCODE_STATE_ACK();  // 5th

	return true;
}

bool PacketHandler::Handle_CH_CREATE(PacketBuffer &buf)
{
	PACKET_CH_CREATE pkt;
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	character_gender_types gender;
	buf >> pkt;

	if (game_account->get_gender() == ACCOUNT_GENDER_MALE) {
		gender = CHARACTER_GENDER_MALE;
	} else {
		gender = CHARACTER_GENDER_FEMALE;
	}

	// Check if the name already exists.
	if (CharQuery->CheckExistingCharByName(pkt.name)) {
		Send_HC_CREATE_ERROR_ACK(HC_CREATE_ERROR_ALREADY_EXISTS);
		return false;
	}

	// Check if the slot is not a premium.
	if (pkt.slot > game_account->get_character_slots()) {
		Send_HC_CREATE_ERROR_ACK(HC_CREATE_ERROR_CHAR_SLOT);
		return false;
	}

	std::shared_ptr<Character> character = std::make_shared<Character>(game_account->get_id(), pkt.name, pkt.slot, gender);
	// Create models and save to sql.
	character->create(CharServer);

	// Status
	std::shared_ptr<Status> status = character->get_status_data();
	status->set_zeny(CharServer->get_char_config().get_start_zeny());

	// View
	std::shared_ptr<View> view = character->get_view_data();
	view->set_hair_style_id(pkt.hair_style);
	view->set_hair_style_id(pkt.hair_color);
	view->save(CharServer);

	// Position
	std::string start_map = CharServer->get_char_config().get_start_map();
	uint16_t start_x = CharServer->get_char_config().get_start_x();
	uint16_t start_y = CharServer->get_char_config().get_start_y();

	std::shared_ptr<Position> p = character->get_position_data();
	p->set_saved_map(start_map);
	p->set_saved_x(start_x);
	p->set_saved_y(start_y);
	p->set_current_map(start_map);
	p->set_current_x(start_x);
	p->set_current_y(start_y);
	p->save(CharServer);

	// Add character to account.
	game_account->add_character(character);
	Send_HC_CREATE_SUCCESS_ACK(character);

	return true;
}

bool PacketHandler::Handle_CH_DELETE_START(PacketBuffer &buf)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<Character> character = nullptr;
	PACKET_CH_DELETE_START pkt;
	character_delete_result result;

	buf >> pkt;

	character = game_account->get_character(pkt.character_id);

	if (character == nullptr) {
		CharLog->warn("Attempted to delete non-existant character for account Id '{}'", game_account->get_id());
		Send_HC_DELETE_START_ACK(pkt.character_id, CHAR_DEL_RESULT_DATABASE_ERR, 0);
		return false;
	}

	if (character->get_access_data()->get_delete_date() > 0) {
		Send_HC_DELETE_START_ACK(pkt.character_id, CHAR_DEL_RESULT_UNKNOWN, 0);
		return false;
	}

	if (character->get_group_data()->get_guild_id() > 0) {
		Send_HC_DELETE_START_ACK(pkt.character_id, CHAR_DEL_RESULT_GUILD_ERR, 0);
		return false;
	}

	if (character->get_group_data()->get_party_id() > 0) {
		Send_HC_DELETE_START_ACK(pkt.character_id, CHAR_DEL_RESULT_PARTY_ERR, 0);
		return false;
	}

	character->get_access_data()->set_delete_date(CharServer->get_char_config().get_character_deletion_time() + std::time(0));
	character->save(CharServer, CHAR_SAVE_ACCESS_DATA);
	result = CHAR_DEL_RESULT_SUCCESS;
	Send_HC_DELETE_START_ACK(character->get_character_id(), result, character->get_access_data()->get_delete_date() - std::time(0));
	return true;
}

bool PacketHandler::Handle_CH_DELETE_ACCEPT(PacketBuffer &buf)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<Character> character = nullptr;
	PACKET_CH_DELETE_ACCEPT pkt;

	buf >> pkt;

 	character = game_account->get_character(pkt.character_id);

	if (character == nullptr) {
		CharLog->warn("Attempted to delete non-existant character for account Id '{}'", game_account->get_id());
		Send_HC_DELETE_ACCEPT_ACK(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_UNKNOWN);
		return false;
	}

	if (character->get_access_data()->get_delete_date() > std::time(0)) {
		CharLog->warn("Attempted to delete character Id {} which is not ready for deletion, in account '{}'", character->get_character_id(), game_account->get_id());
		Send_HC_DELETE_ACCEPT_ACK(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_TIME_ERR);
		return false;
	}

	const char *birth_date = game_account->get_birth_date().c_str();
	if (std::strncmp(&birth_date[2], &pkt.birthdate[0], 2)        // YY
		|| std::strncmp(&birth_date[5], &pkt.birthdate[2], 2)     // MM
		|| std::strncmp(&birth_date[8], &pkt.birthdate[4], 2)) {  // DD
		Send_HC_DELETE_ACCEPT_ACK(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_BIRTHDAY_ERR);
		return false;
	}

	Send_HC_DELETE_ACCEPT_ACK(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_SUCCESS);

	game_account->remove_character(pkt.character_id);
	character->set_deleted_at(std::time(0));
	character->save(CharServer);
	Send_HC_RESEND_CHAR_LIST();

	return true;
}

bool PacketHandler::Handle_CH_DELETE_CANCEL(PacketBuffer &buf)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<Character> character;
	PACKET_CH_DELETE_CANCEL pkt;

	buf >> pkt;

	character = game_account->get_character(pkt.character_id);

	if (character == nullptr) {
		CharLog->warn("Attempted to delete non-existant character for account Id '{}'", game_account->get_id());
		Send_HC_DELETE_CANCEL_ACK(pkt.character_id, false);
		return false;
	}

	if (character->get_access_data()->get_delete_date() == 0) {
		CharLog->warn("Attempted to delete character that wasn't set for deletion in account Id '{}'", game_account->get_id());
		Send_HC_DELETE_CANCEL_ACK(pkt.character_id, false);
		return false;
	}

	character->get_access_data()->set_delete_date(0);
	character->save(CharServer, CHAR_SAVE_ACCESS_DATA);

	Send_HC_DELETE_CANCEL_ACK(pkt.character_id, true);
	return true;
}

bool PacketHandler::Handle_CH_SELECT(PacketBuffer &buf)
{
	PACKET_CH_SELECT pkt;
	AccountCharacterMapType characters = get_socket()->get_session()->get_game_account()->get_all_characters();
	std::shared_ptr<Character> character;

	buf >> pkt;

	if (characters.empty()) {
		Send_HC_CONNECT_ERROR(character_connect_errors::CHAR_ERR_REJECTED_FROM_SERVER);
		return false;
	}

	for (auto &it : characters) {
		character = it.second;

		if (character == nullptr)
			continue;

		if (character->get_slot() == pkt.slot)
			break;
	}

	Send_HC_SEND_ZONE_INFO(character);

	// Close the socket as the character has been transfered and there is no connection.
	get_socket()->delayed_close_socket();
	return true;
}

/**
 * @brief Receive and handle the CA_KEEP_ALIVE packet.
 * @param[in|out] buf    Validated PacketBuffer received by the char-server.
 */
bool PacketHandler::Handle_CH_KEEP_ALIVE(PacketBuffer &/*buf*/)
{
	// We do nothing here as yet, its just a keep-alive.
//	PACKET_CH_KEEP_ALIVE pkt;
//
//	buf >> pkt;

	_last_ping_time = std::time(0);
	
	return true;
}

/*==============*
 * Sender Methods
 *==============*/

/**
 * @brief Send to the client with the AC_CONNECT_ERROR packet.
 * @param[in] error    error code to be sent, @see character_connect_errors.
 */
void PacketHandler::Send_HC_CONNECT_ERROR(character_connect_errors error)
{
	PACKET_HC_CONNECT_ERROR pkt;
	pkt.error = error;
	send_packet(pkt);
}

/**
 * @brief Send to the client with the Account ID to initiate client connection.
 * @note This packet has no ID but is required by the client.
 * @param[in] account_id   Account ID of the session.
 */
void PacketHandler::Send_HC_ACCOUNT_ID()
{
	PACKET_CHAR_ACCOUNT_ID pkt;
	pkt.account_id = get_socket()->get_session()->get_game_account()->get_id();
	send_packet(pkt);
}

/**
 * @brief Send to the client with the AC_SLOT_INFO_ACK packet on client connection.
 * @see packets
 */
void PacketHandler::Send_HC_SLOT_INFO_ACK()
{
	std::shared_ptr<SessionData> session_data = get_socket()->get_session()->get_session_data();
	PACKET_HC_SLOT_INFO_ACK pkt;

	pkt.total_slots = MAX_CHARACTER_SLOTS;
	pkt.premium_slots = session_data->get_character_slots();
	pkt.char_slots_1 = session_data->get_character_slots();
	pkt.char_slots_2 = session_data->get_character_slots();

	send_packet(pkt);

	CharLog->info("Sent character-slot information to AID {}", session_data->get_game_account_id());
}

/**
 * @brief Send to the client with the AC_CHAR_LIST_ACK packet on client connection.
 * @see packets
 */
void PacketHandler::Send_HC_CHAR_LIST_ACK()
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	PACKET_HC_CHAR_LIST_ACK pkt;
	PacketBuffer buf;
	std::vector<character_list_data> char_list;
	int char_list_length = 0;

	for (auto &c : game_account->get_all_characters()) {
		character_list_data c_data;
		c_data.create(c.second);
		c_data.gender = game_account->get_gender();
		char_list.push_back(c_data);
		char_list_length += sizeof(c_data);
	}

	pkt.packet_len += char_list_length;

	buf.append(&pkt, sizeof(pkt));

	for (auto c : char_list) {
		buf.append(&c, sizeof(c));
	}

	send_packet(buf, pkt.packet_len);

	CharLog->info("Sent character-list information to AID {}", game_account->get_id());
}

void PacketHandler::Send_HC_RESEND_CHAR_LIST()
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	PACKET_HC_CHAR_LIST_ACK pkt;
	PacketBuffer buf;
	std::vector<character_list_data> char_list;
	int char_list_length = 0;

	for (auto &c : game_account->get_all_characters()) {
		character_list_data c_data;
		c_data.create(c.second);
		c_data.gender = game_account->get_gender();
		char_list.push_back(c_data);
		char_list_length += sizeof(c_data);
	}

	pkt.packet_len += char_list_length;

	buf.append(&pkt, sizeof(pkt));

	for (auto c : char_list) {
		buf.append(&c, sizeof(c));
	}

	send_packet(buf, pkt.packet_len);

	CharLog->info("Re-sent character-list information to AID {}", game_account->get_id());
}

/**
 * @brief Send to the client with the AC_BAN_LIST_ACK packet on client connection.
 * @see packets
 */
void PacketHandler::Send_HC_BAN_LIST_ACK()
{
	PACKET_HC_BAN_LIST_ACK pkt;
	send_packet(pkt);
	CharLog->info("Send character ban-list information to AID {}", get_socket()->get_session()->get_game_account()->get_id());
}

/**
 * @brief Send to the client with the AC_PINCODE_STATE_ACK packet on client connection.
 * @see packets
 */
void PacketHandler::Send_HC_PINCODE_STATE_ACK()
{
	PACKET_HC_PINCODE_STATE_ACK pkt;
	pkt.pincode_seed = rand() % 0xFFFF;
	pkt.account_id = get_socket()->get_session()->get_game_account()->get_id();
	pkt.state = PINCODE_CORRECT;
	send_packet(pkt);
}

void PacketHandler::Send_HC_CREATE_SUCCESS_ACK(std::shared_ptr<Character> character)
{
	PACKET_HC_CREATE_SUCCESS_ACK pkt;

	pkt.data.create(character);

	if (get_socket()->get_session()->get_game_account()->get_gender() == ACCOUNT_GENDER_MALE)
		pkt.data.gender = CHARACTER_GENDER_MALE;
	else
		pkt.data.gender = CHARACTER_GENDER_FEMALE;

	send_packet(pkt);
}

void PacketHandler::Send_HC_DELETE_START_ACK(uint32_t character_id, character_delete_result result, time_t deletion_date)
{
	PACKET_HC_DELETE_START_ACK pkt;
	pkt.character_id = character_id;
	pkt.result = result;
	pkt.deletion_date = deletion_date;
	send_packet(pkt);
}

void PacketHandler::Send_HC_DELETE_ACCEPT_ACK(uint32_t character_id, character_delete_accept_result result)
{
	PACKET_HC_DELETE_ACCEPT_ACK pkt;
	pkt.character_id = character_id;
	pkt.result = result;
	send_packet(pkt);
}

void PacketHandler::Send_HC_DELETE_CANCEL_ACK(uint32_t character_id, bool success)
{
	PACKET_HC_DELETE_CANCEL_ACK pkt;
	pkt.character_id = character_id;
	pkt.result = success ? 1 : 2;
	send_packet(pkt);
}

void PacketHandler::Send_HC_CREATE_ERROR_ACK(char_create_error_types error)
{
	PACKET_HC_CREATE_ERROR_ACK pkt;
	pkt.error_code = (uint8_t) error;
	send_packet(pkt);
}

void PacketHandler::Send_HC_SEND_ZONE_INFO(std::shared_ptr<Character> character)
{
	PACKET_HC_SEND_ZONE_INFO pkt;
	std::string map_name;

	if ((map_name = character->get_position_data()->get_current_map()).empty())
		if ((map_name = character->get_position_data()->get_saved_map()).empty())
			map_name = CharServer->get_char_config().get_start_map().c_str();

	map_name += ".gat";

	pkt.char_id = character->get_character_id();
	pkt.ip_address = inet_addr(CharServer->get_char_config().get_zone_server_ip().c_str());
	pkt.port = CharServer->get_char_config().get_zone_server_port();
	strncpy(pkt.mapname,
			map_name.c_str(),
			MAP_NAME_LENGTH_EXT);

	send_packet(pkt);
}
