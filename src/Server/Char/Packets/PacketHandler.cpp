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
#include "Server/Char/Char.hpp"
#include "Server/Char/Packets/Ragexe/Packets.hpp"
#include "Server/Char/Packets/Ragexe/PacketStructs.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Char/Database/Query.hpp"
#include "Server/Common/Models/Configuration/CharServerConfiguration.hpp"
#include "Server/Common/Models/GameAccount.hpp"

#include <boost/bind.hpp>
#include <string>

using namespace Horizon::Char;
using namespace Horizon::Models::Character;

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
#define HANDLER_FUNC(packet) add_packet_handler(Ragexe::packet, boost::bind(&PacketHandler::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CH_UNKNOWN_PING);
	HANDLER_FUNC(CH_MAKE_CHAR);
	HANDLER_FUNC(CH_DELETE_CHAR);
	HANDLER_FUNC(CH_DELETE_CHAR3_CANCEL);
	HANDLER_FUNC(CH_DELETE_CHAR3);
	HANDLER_FUNC(CH_SELECT_CHAR);
	HANDLER_FUNC(CH_ENTER);
	HANDLER_FUNC(CH_DELETE_CHAR3_RESERVED);
#undef HANDLER_FUNC
}

/*==============*
 * Handler Methods
 *==============*/

/**
 * @brief Receive and handle the CH_ENTER packet.
 * @param[in|out] buf    Validated PacketBuffer received by the char-server.
 */
bool PacketHandler::Handle_CH_ENTER(PacketBuffer &buf)
{
	std::shared_ptr<CharSession> session = get_socket()->get_session();

	Ragexe::PACKET_CH_ENTER pkt;

	pkt << buf;

	std::shared_ptr<SessionData> session_data = std::make_shared<SessionData>();
	if (!session_data->load(CharServer, pkt.account_id)) {
		Send_HC_REFUSE_ENTER(CHAR_ERR_REJECTED_FROM_SERVER);
		return false;
	}

	std::shared_ptr<GameAccount> game_account = std::make_shared<GameAccount>();
	if (!game_account->load(CharServer, pkt.account_id)) {
		Send_HC_REFUSE_ENTER(CHAR_ERR_REJECTED_FROM_SERVER);
		return false;
	}

	session->set_session_data(session_data);
	session->set_game_account(game_account);

	// Send acceptance notice to client.
	Send_HC_ACCOUNT_ID();
	// Send character list info.
	Send_HC_ACCEPT_ENTER2(); // Always sent first.
	Send_HC_ACCEPT_ENTER();  // Sent thereafter.
	Send_HC_BLOCK_CHARACTER();
	Send_HC_SECOND_PASSWD_LOGIN();

	return true;
}

bool PacketHandler::Handle_CH_MAKE_CHAR(PacketBuffer &buf)
{
	Ragexe::PACKET_CH_MAKE_CHAR pkt;
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	character_gender_types gender;

	pkt << buf;

	gender = (character_gender_types) pkt.gender;

	// Check if the name already exists.
	if (CharQuery->CheckExistingCharByName(pkt.name)) {
		Send_HC_REFUSE_MAKECHAR(HC_CREATE_ERROR_ALREADY_EXISTS);
		return false;
	}

	// Check if the slot is not a premium.
	if (pkt.slot > game_account->get_character_slots()) {
		Send_HC_REFUSE_MAKECHAR(HC_CREATE_ERROR_CHAR_SLOT);
		return false;
	}

	std::shared_ptr<Character> character = std::make_shared<Character>(game_account->get_id(), pkt.name, pkt.slot, gender);
	
	// Create models and save to sql.
	character->create(CharServer);

	// Status
	std::shared_ptr<Status> status = character->get_status_data();
	status->set_zeny(CharServer->get_char_config().get_start_zeny());
	status->set_job_class(pkt.job_id);

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
	Send_HC_ACCEPT_MAKECHAR(character);

	return true;
}

character_delete_result PacketHandler::delete_character(uint32_t character_id)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<Character> character = nullptr;
	character = game_account->get_character(character_id);

	if (character == nullptr) {
		CharLog->warn("Attempted to delete non-existant character for account Id '{}'", game_account->get_id());
		return CHAR_DEL_RESULT_DATABASE_ERR;
	}

	if (character->get_access_data()->get_delete_date() > 0)
		return CHAR_DEL_RESULT_UNKNOWN;

	if (character->get_group_data()->get_guild_id() > 0)
		return CHAR_DEL_RESULT_GUILD_ERR;

	if (character->get_group_data()->get_party_id() > 0)
		return CHAR_DEL_RESULT_PARTY_ERR;

	character->get_access_data()->set_delete_date(CharServer->get_char_config().get_character_deletion_time() + std::time(0));
	character->save(CharServer, CHAR_SAVE_ACCESS_DATA);

	return CHAR_DEL_RESULT_SUCCESS;
}

bool PacketHandler::Handle_CH_DELETE_CHAR3_RESERVED(PacketBuffer &buf)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<Character> character = nullptr;
	Ragexe::PACKET_CH_DELETE_CHAR3_RESERVED pkt;
	character_delete_result result;

	pkt << buf;

	if ((character = game_account->get_character(pkt.character_id)) == nullptr) {
		CharLog->warn("Attempted to delete non-existant character for account Id '{}'", game_account->get_id());
		Send_HC_DELETE_CHAR3_RESERVED(pkt.character_id, CHAR_DEL_RESULT_DATABASE_ERR, 0);
		return false;
	}

	if ((result = delete_character(pkt.character_id)) == CHAR_DEL_RESULT_SUCCESS) {
		Send_HC_DELETE_CHAR3_RESERVED(pkt.character_id, result, character->get_access_data()->get_delete_date() - std::time(0));
		return true;
	}

	Send_HC_DELETE_CHAR3_RESERVED(pkt.character_id, result, 0);
	return false;
}

bool PacketHandler::Handle_CH_DELETE_CHAR(PacketBuffer &buf)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<Character> character = nullptr;
	Ragexe::PACKET_CH_DELETE_CHAR pkt;
	character_delete_result result;

	pkt << buf;

	if ((character = game_account->get_character(pkt.character_id)) == nullptr) {
		CharLog->warn("Attempted to delete non-existant character for account Id '{}'", game_account->get_id());
		Send_HC_DELETE_CHAR3_RESERVED(pkt.character_id, CHAR_DEL_RESULT_DATABASE_ERR, 0);
		return false;
	}

	if ((result = delete_character(pkt.character_id)) == CHAR_DEL_RESULT_SUCCESS) {
		Send_HC_DELETE_CHAR3_RESERVED(pkt.character_id, result, character->get_access_data()->get_delete_date() - std::time(0));
		return true;
	}

	Send_HC_DELETE_CHAR3_RESERVED(pkt.character_id, result, 0);
	return false;
}

bool PacketHandler::Handle_CH_DELETE_CHAR3(PacketBuffer &buf)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<Character> character = nullptr;
	Ragexe::PACKET_CH_DELETE_CHAR3 pkt;

	pkt << buf;

 	character = game_account->get_character(pkt.character_id);

	if (character == nullptr) {
		CharLog->warn("Attempted to delete non-existant character for account Id '{}'", game_account->get_id());
		Send_HC_DELETE_CHAR3(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_UNKNOWN);
		return false;
	}

	if (character->get_access_data()->get_delete_date() > std::time(0)) {
		CharLog->warn("Attempted to delete character Id {} which is not ready for deletion, in account '{}'", character->get_character_id(), game_account->get_id());
		Send_HC_DELETE_CHAR3(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_TIME_ERR);
		return false;
	}

	const char *birth_date = game_account->get_birth_date().c_str();
	if (std::strncmp(&birth_date[2], &pkt.birthdate[0], 2)        // YY
		|| std::strncmp(&birth_date[5], &pkt.birthdate[2], 2)     // MM
		|| std::strncmp(&birth_date[8], &pkt.birthdate[4], 2)) {  // DD
		Send_HC_DELETE_CHAR3(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_BIRTHDAY_ERR);
		return false;
	}

	Send_HC_DELETE_CHAR3(pkt.character_id, CHAR_DEL_ACCEPT_RESULT_SUCCESS);

	game_account->remove_character(pkt.character_id);
	character->set_deleted_at(std::time(0));
	character->save(CharServer);
	Send_HC_ACCEPT_ENTER();

	return true;
}

bool PacketHandler::Handle_CH_DELETE_CHAR3_CANCEL(PacketBuffer &buf)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<Character> character;
	Ragexe::PACKET_CH_DELETE_CHAR3_CANCEL pkt;

	pkt << buf;

	character = game_account->get_character(pkt.character_id);

	if (character == nullptr) {
		CharLog->warn("Attempted to delete non-existant character for account Id '{}'", game_account->get_id());
		Send_HC_DELETE_CHAR3_CANCEL(pkt.character_id, false);
		return false;
	}

	if (character->get_access_data()->get_delete_date() == 0) {
		CharLog->warn("Attempted to delete character that wasn't set for deletion in account Id '{}'", game_account->get_id());
		Send_HC_DELETE_CHAR3_CANCEL(pkt.character_id, false);
		return false;
	}

	character->get_access_data()->set_delete_date(0);
	character->save(CharServer, CHAR_SAVE_ACCESS_DATA);

	Send_HC_DELETE_CHAR3_CANCEL(pkt.character_id, true);
	return true;
}

bool PacketHandler::Handle_CH_SELECT_CHAR(PacketBuffer &buf)
{
	Ragexe::PACKET_CH_SELECT_CHAR pkt;
	AccountCharacterMapType characters = get_socket()->get_session()->get_game_account()->get_characters();
	std::shared_ptr<Character> character;

	pkt << buf;

	if (characters.empty()) {
		Send_HC_REFUSE_ENTER(CHAR_ERR_REJECTED_FROM_SERVER);
		return false;
	}

	for (auto &it : characters) {
		character = it.second;

		if (character == nullptr)
			continue;

		if (character->get_slot() == pkt.slot)
			break;
	}

	Send_HC_NOTIFY_ZONESVR(character);

	// Close the socket as the character has been transfered and there is no connection.
	get_socket()->delayed_close_socket();
	return true;
}

/**
 * @brief Receive and handle the CA_KEEP_ALIVE packet.
 * @param[in|out] buf    Validated PacketBuffer received by the char-server.
 */
bool PacketHandler::Handle_CH_UNKNOWN_PING(PacketBuffer &/*buf*/)
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
void PacketHandler::Send_HC_REFUSE_ENTER(character_connect_errors error)
{
	Ragexe::PACKET_HC_REFUSE_ENTER pkt;
	pkt.error = error;
	send_packet(pkt.serialize());
}

/**
 * @brief Send to the client with the Account ID to initiate client connection.
 * @note This packet has no ID but is required by the client.
 * @param[in] account_id   Account ID of the session.
 */
void PacketHandler::Send_HC_ACCOUNT_ID()
{
	Ragexe::PACKET_HC_ACCOUNT_ID pkt;
	pkt.account_id = get_socket()->get_session()->get_game_account()->get_id();
	send_packet(pkt.serialize());
}

/**
 * @brief Sends character slot information to the client.
 * @see packets
 */
void PacketHandler::Send_HC_ACCEPT_ENTER2()
{
	std::shared_ptr<SessionData> session_data = get_socket()->get_session()->get_session_data();
	Ragexe::PACKET_HC_ACCEPT_ENTER2 pkt;

	pkt.total_slots = MAX_CHARACTER_SLOTS;
	pkt.packet_length = pkt.get_length();
	pkt.premium_slots = session_data->get_character_slots();
	pkt.char_slots_1 = session_data->get_character_slots();
	pkt.char_slots_2 = session_data->get_character_slots();

	send_packet(pkt.serialize());

	CharLog->info("Sent character-slot information to AID {}", session_data->get_game_account_id());
}

/**
 * @brief Send to the client with the HC_ACCEPT_ENTER packet on client connection.
 * @see packets
 */
void PacketHandler::Send_HC_ACCEPT_ENTER()
{
	std::shared_ptr<CharSession> session = get_socket()->get_session();
	std::shared_ptr<GameAccount> game_account = session->get_game_account();

	Ragexe::PACKET_HC_ACCEPT_ENTER pkt;

	CharQuery->load_all_characters_for_account(session->get_game_account());
	
	auto char_list = game_account->get_characters();

	pkt.packet_length = pkt.get_length(char_list.size());

	PacketBuffer buf = pkt.serialize();

	for (auto &c : char_list) {
		Ragexe::PACKET_HC_ACCEPT_ENTER::character_list_data character;
		character.create_from_model(c.second);
		character.serialize(buf);
	}

	send_packet(buf);

	CharLog->info("Sent character-list information to AID {}", game_account->get_id());
}

/**
 * @brief Send to the client with the AC_BAN_LIST_ACK packet on client connection.
 * @see packets
 */
void PacketHandler::Send_HC_BLOCK_CHARACTER()
{
	Ragexe::PACKET_HC_BLOCK_CHARACTER pkt;
	send_packet(pkt.serialize());
	CharLog->info("Send character ban-list information to AID {}", get_socket()->get_session()->get_game_account()->get_id());
}

/**
 * @brief Send to the client with the AC_PINCODE_STATE_ACK packet on client connection.
 * @see packets
 */
void PacketHandler::Send_HC_SECOND_PASSWD_LOGIN()
{
	Ragexe::PACKET_HC_SECOND_PASSWD_LOGIN pkt;
	pkt.pincode_seed = rand() % 0xFFFF;
	pkt.account_id = get_socket()->get_session()->get_game_account()->get_id();
	pkt.state = PINCODE_CORRECT;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_HC_ACCEPT_MAKECHAR(std::shared_ptr<Character> character)
{
	Ragexe::PACKET_HC_ACCEPT_MAKECHAR pkt;

	pkt.character.create_from_model(character);

	if (get_socket()->get_session()->get_game_account()->get_gender() == ACCOUNT_GENDER_MALE)
		pkt.character.gender = CHARACTER_GENDER_MALE;
	else
		pkt.character.gender = CHARACTER_GENDER_FEMALE;

	PacketBuffer buf = pkt.serialize();
	pkt.character.serialize(buf);

	send_packet(buf);
}

void PacketHandler::Send_HC_DELETE_CHAR3_RESERVED(uint32_t character_id, character_delete_result result, time_t deletion_date)
{
	Ragexe::PACKET_HC_DELETE_CHAR3_RESERVED pkt;
	pkt.character_id = character_id;
	pkt.result = result;
	pkt.deletion_date = deletion_date;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_HC_DELETE_CHAR3(uint32_t character_id, character_delete_accept_result result)
{
	Ragexe::PACKET_HC_DELETE_CHAR3 pkt;
	pkt.character_id = character_id;
	pkt.result = result;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_HC_DELETE_CHAR3_CANCEL(uint32_t character_id, bool success)
{
	Ragexe::PACKET_HC_DELETE_CHAR3_CANCEL pkt;
	pkt.character_id = character_id;
	pkt.result = success ? 1 : 2;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_HC_REFUSE_MAKECHAR(char_create_error_types error)
{
	Ragexe::PACKET_HC_REFUSE_MAKECHAR pkt;
	pkt.error_code = error;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_HC_NOTIFY_ZONESVR(std::shared_ptr<Character> character)
{
	Ragexe::PACKET_HC_NOTIFY_ZONESVR pkt;
	std::string map_name;

	if ((map_name = character->get_position_data()->get_current_map()).empty())
		if ((map_name = character->get_position_data()->get_saved_map()).empty())
			map_name = CharServer->get_char_config().get_start_map().c_str();

	map_name += ".gat";

	pkt.char_id = character->get_character_id();
	pkt.ip_address = inet_addr(CharServer->get_char_config().get_zone_server_ip().c_str());
	pkt.port = CharServer->get_char_config().get_zone_server_port();
	strncpy(pkt.map_name, map_name.c_str(), MAP_NAME_LENGTH_EXT);

	send_packet(pkt.serialize());
}
