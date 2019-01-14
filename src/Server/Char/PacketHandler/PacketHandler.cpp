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
	HANDLER_FUNC(CHAR_KEEP_ALIVE);
	HANDLER_FUNC(CHAR_CREATE);
	HANDLER_FUNC(CHAR_DELETE_START);
	HANDLER_FUNC(CHAR_DELETE_CANCEL);
	HANDLER_FUNC(CHAR_DELETE_ACCEPT);
	HANDLER_FUNC(CHAR_SELECT);
#undef HANDLER_FUNC
}

/*==============*
 * Handler Methods
 *==============*/

/**
 * @brief Receive and handle the CHAR_CONNCET packet.
 * @param[in|out] buf    Validated PacketBuffer received by the char-server.
 */
void PacketHandler::Handle_CHAR_CONNECT(PACKET_CHAR_CONNECT &/*pkt*/)
{
	CharQuery->AllCharactersByAccount(get_socket()->get_session()->get_game_account());
	
	// Send acceptance notice to client.
	Send_CHAR_ACCOUNT_ID();         // 1st

	// Send character list info.
	Send_CHAR_SLOT_INFO_ACK();      // 2nd
	Send_CHAR_LIST_ACK();           // 3rd
	Send_CHAR_BAN_LIST_ACK();       // 4th
	Send_CHAR_PINCODE_STATE_ACK();  // 5th
}

void PacketHandler::Handle_CHAR_CREATE(PacketBuffer &buf)
{
	PACKET_CHAR_CREATE pkt;
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
		Send_CHAR_CREATE_ERROR_ACK(CHAR_CREATE_ERROR_ALREADY_EXISTS);
		return;
	}

	// Check if the slot is not a premium.
	if (pkt.slot > game_account->get_character_slots()) {
		Send_CHAR_CREATE_ERROR_ACK(CHAR_CREATE_ERROR_CHAR_SLOT);
		return;
	}

	std::shared_ptr<Character> character = std::make_shared<Character>(
			game_account->get_id(), pkt.name, pkt.slot, gender);
	character->set_status_data(std::make_shared<Status>(
			CharServer->getCharConfig().getStartZeny(), pkt.str, pkt.agi, pkt.int_, pkt.vit, pkt.dex, pkt.luk));
	character->set_view_data(std::make_shared<View>(pkt.hair_style, pkt.hair_color));
	character->set_position_data(std::make_shared<Position>(
			CharServer->getCharConfig().getStartMap(), CharServer->getCharConfig().getStartX(), CharServer->getCharConfig().getStartY()));
	
	// Save character to sql.
	character->create(CharServer);
	// Add character to account.
	game_account->add_character(character);
	Send_CHAR_CREATE_SUCCESS_ACK(character);
}

void PacketHandler::Handle_CHAR_DELETE_START(PacketBuffer &buf)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<Character> character = nullptr;
	PACKET_CHAR_DELETE_START pkt;
	character_delete_result result;

	buf >> pkt;

	character = game_account->get_character(pkt.character_id);

	if (character == nullptr) {
		CharLog->warn("Attempted to delete non-existant character for account Id '{}'", game_account->get_id());
		Send_CHAR_DELETE_START_ACK(pkt.character_id, CHAR_DEL_RESULT_DATABASE_ERR, 0);
		return;
	}

	if (character->get_access_data()->get_delete_date() > 0) {
		Send_CHAR_DELETE_START_ACK(pkt.character_id, CHAR_DEL_RESULT_UNKNOWN, 0);
		return;
	}

	if (character->get_group_data()->get_guild_id() > 0) {
		Send_CHAR_DELETE_START_ACK(pkt.character_id, CHAR_DEL_RESULT_GUILD_ERR, 0);
		return;
	}

	if (character->get_group_data()->get_party_id() > 0) {
		Send_CHAR_DELETE_START_ACK(pkt.character_id, CHAR_DEL_RESULT_PARTY_ERR, 0);
		return;
	}

	character->get_access_data()->set_delete_date(CharServer->getCharConfig().getCharacterDeletionTime() + time(nullptr));
	character->get_access_data()->save(CharServer);
	result = CHAR_DEL_RESULT_SUCCESS;
	Send_CHAR_DELETE_START_ACK(character->get_character_id(), result, character->get_access_data()->get_delete_date() - time(nullptr));
}

void PacketHandler::Handle_CHAR_DELETE_ACCEPT(PacketBuffer &buf)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<Character> character = nullptr;
	PACKET_CHAR_DELETE_ACCEPT pkt;

	buf >> pkt;

 	character = game_account->get_character(pkt.character_id);

	if (character == nullptr) {
		CharLog->warn("Attempted to delete non-existant character for account Id '{}'", game_account->get_id());
		Send_CHAR_DELETE_ACCEPT_ACK(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_UNKNOWN);
		return;
	}

	if (character->get_access_data()->get_delete_date() > time(nullptr)) {
		CharLog->warn("Attempted to delete character Id {} which is not ready for deletion, in account '{}'", character->get_character_id(), game_account->get_id());
		Send_CHAR_DELETE_ACCEPT_ACK(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_TIME_ERR);
		return;
	}

	const char *birth_date = game_account->get_birthdate().c_str();
	if (std::strncmp(&birth_date[2], &pkt.birthdate[0], 2)        // YY
		|| std::strncmp(&birth_date[5], &pkt.birthdate[2], 2)     // MM
		|| std::strncmp(&birth_date[8], &pkt.birthdate[4], 2)) {  // DD
		Send_CHAR_DELETE_ACCEPT_ACK(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_BIRTHDAY_ERR);
		return;
	}

	Send_CHAR_DELETE_ACCEPT_ACK(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_SUCCESS);

	game_account->remove_character(pkt.character_id);
	character->set_deleted(true);
	character->save(CharServer);
	Send_CHAR_RESEND_CHAR_LIST();
}

void PacketHandler::Handle_CHAR_DELETE_CANCEL(PacketBuffer &buf)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<Character> character;
	PACKET_CHAR_DELETE_CANCEL pkt;

	buf >> pkt;

	character = game_account->get_character(pkt.character_id);

	if (character == nullptr) {
		CharLog->warn("Attempted to delete non-existant character for account Id '{}'", game_account->get_id());
		Send_CHAR_DELETE_CANCEL_ACK(pkt.character_id, false);
		return;
	}

	if (character->get_access_data()->get_delete_date() == 0) {
		CharLog->warn("Attempted to delete character that wasn't set for deletion in account Id '{}'", game_account->get_id());
		Send_CHAR_DELETE_CANCEL_ACK(pkt.character_id, false);
		return;
	}

	character->get_access_data()->set_delete_date(0);
	character->get_access_data()->save(CharServer);

	Send_CHAR_DELETE_CANCEL_ACK(pkt.character_id, true);
}

void PacketHandler::Handle_CHAR_SELECT(PacketBuffer &buf)
{
	PACKET_CHAR_SELECT pkt;
	AccountCharacterMapType characters = get_socket()->get_session()->get_game_account()->get_all_characters();
	std::shared_ptr<Character> character;

	buf >> pkt;

	if (characters.empty())
		return;

	for (auto &it : characters) {
		character = it.second;

		if (character == nullptr)
			continue;

		if (character->get_slot() == pkt.slot)
			break;
	}

	Send_CHAR_SEND_ZONE_INFO(character);
}

/**
 * @brief Receive and handle the CHAR_KEEP_ALIVE packet.
 * @param[in|out] buf    Validated PacketBuffer received by the char-server.
 */
void PacketHandler::Handle_CHAR_KEEP_ALIVE(PacketBuffer &/*buf*/)
{
	// We do nothing here as yet, its just a keep-alive.
	// PACKET_CHAR_KEEP_ALIVE pkt;
	// buf >> pkt;
}

/*==============*
 * Sender Methods
 *==============*/

/**
 * @brief Send to the client with the CHAR_CONNECT_ERROR packet.
 * @param[in] error    error code to be sent, @see character_connect_errors.
 */
void PacketHandler::Send_CHAR_CONNECT_ERROR(character_connect_errors error)
{
	PACKET_CHAR_CONNECT_ERROR pkt;
	pkt.error = error;
	send_packet(pkt);
}

/**
 * @brief Send to the client with the Account ID to initiate client connection.
 * @note This packet has no ID but is required by the client.
 * @param[in] account_id   Account ID of the session.
 */
void PacketHandler::Send_CHAR_ACCOUNT_ID()
{
	PACKET_CHAR_ACCOUNT_ID pkt;
	pkt.account_id = get_socket()->get_session()->get_game_account()->get_id();
	send_packet(pkt);
}

/**
 * @brief Send to the client with the CHAR_SLOT_INFO_ACK packet on client connection.
 * @see packets
 */
void PacketHandler::Send_CHAR_SLOT_INFO_ACK()
{
	std::shared_ptr<SessionData> session_data = get_socket()->get_session()->get_session_data();
	PACKET_CHAR_SLOT_INFO_ACK pkt;

	pkt.total_slots = MAX_CHARACTER_SLOTS;
	pkt.premium_slots = session_data->get_character_slots();
	pkt.char_slots_1 = session_data->get_character_slots();
	pkt.char_slots_2 = session_data->get_character_slots();

	send_packet(pkt);

	CharLog->info("Sent character-slot information to AID {}", session_data->get_game_account_id());
}

/**
 * @brief Send to the client with the CHAR_LIST_ACK packet on client connection.
 * @see packets
 */
void PacketHandler::Send_CHAR_LIST_ACK()
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	PACKET_CHAR_LIST_ACK pkt;
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

void PacketHandler::Send_CHAR_RESEND_CHAR_LIST()
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	PACKET_CHAR_RESEND_CHAR_LIST pkt;
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
 * @brief Send to the client with the CHAR_BAN_LIST_ACK packet on client connection.
 * @see packets
 */
void PacketHandler::Send_CHAR_BAN_LIST_ACK()
{
	PACKET_CHAR_BAN_LIST_ACK pkt;
	send_packet(pkt);
	CharLog->info("Send character ban-list information to AID {}", get_socket()->get_session()->get_game_account()->get_id());
}

/**
 * @brief Send to the client with the CHAR_PINCODE_STATE_ACK packet on client connection.
 * @see packets
 */
void PacketHandler::Send_CHAR_PINCODE_STATE_ACK()
{
	PACKET_CHAR_PINCODE_STATE_ACK pkt;
	pkt.pincode_seed = rand() % 0xFFFF;
	pkt.account_id = get_socket()->get_session()->get_game_account()->get_id();
	pkt.state = PINCODE_CORRECT;
	send_packet(pkt);
}

void PacketHandler::Send_CHAR_CREATE_SUCCESS_ACK(std::shared_ptr<Character> character)
{
	PACKET_CHAR_CREATE_SUCCESS_ACK pkt;

	pkt.data.create(character);

	if (get_socket()->get_session()->get_game_account()->get_gender() == ACCOUNT_GENDER_MALE)
		pkt.data.gender = CHARACTER_GENDER_MALE;
	else
		pkt.data.gender = CHARACTER_GENDER_FEMALE;

	send_packet(pkt);
}

void PacketHandler::Send_CHAR_DELETE_START_ACK(uint32_t character_id, character_delete_result result, time_t deletion_date)
{
	PACKET_CHAR_DELETE_START_ACK pkt;
	pkt.character_id = character_id;
	pkt.result = result;
	pkt.deletion_date = deletion_date;
	send_packet(pkt);
}

void PacketHandler::Send_CHAR_DELETE_ACCEPT_ACK(uint32_t character_id, character_delete_accept_result result)
{
	PACKET_CHAR_DELETE_ACCEPT_ACK pkt;
	pkt.character_id = character_id;
	pkt.result = result;
	send_packet(pkt);
}

void PacketHandler::Send_CHAR_DELETE_CANCEL_ACK(uint32_t character_id, bool success)
{
	PACKET_CHAR_DELETE_CANCEL_ACK pkt;
	pkt.character_id = character_id;
	pkt.result = success ? 1 : 2;
	send_packet(pkt);
}

void PacketHandler::Send_CHAR_CREATE_ERROR_ACK(char_create_error_types error)
{
	PACKET_CHAR_CREATE_ERROR_ACK pkt;
	pkt.error_code = (uint8_t) error;
	send_packet(pkt);
}

void PacketHandler::Send_CHAR_SEND_ZONE_INFO(std::shared_ptr<Character> character)
{
	PACKET_CHAR_SEND_ZONE_INFO pkt;
	std::string map_name;

	if ((map_name = character->get_position_data()->get_current_map()).empty())
		if ((map_name = character->get_position_data()->get_saved_map()).empty())
			map_name = CharServer->getCharConfig().getStartMap().c_str();

	map_name += ".gat";

	pkt.char_id = character->get_character_id();
	pkt.ip_address = inet_addr(CharServer->getCharConfig().getZoneServerIP().c_str());
	pkt.port = CharServer->getCharConfig().getZoneServerPort();
	strncpy(pkt.mapname,
			map_name.c_str(),
			MAP_NAME_LENGTH_EXT);

	send_packet(pkt);
}
