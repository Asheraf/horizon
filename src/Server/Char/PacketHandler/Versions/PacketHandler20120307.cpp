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

#include "PacketHandler20120307.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Char/Char.hpp"
#include "Server/Char/Database/Query.hpp"
#include "Server/Char/PacketHandler/Packets.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/Configuration/CharServerConfiguration.hpp"

using namespace Horizon::Models::Character;

Horizon::Char::PacketHandler20120307::PacketHandler20120307(std::shared_ptr<CharSocket> socket)
: PacketHandler(socket)
{
	initialize_handlers();
}

Horizon::Char::PacketHandler20120307::~PacketHandler20120307()
{
	//
}

void Horizon::Char::PacketHandler20120307::initialize_handlers()
{
#define HANDLER_FUNC(packet) add_packet_handler(PacketVer20120307::packets::packet, boost::bind(&PacketHandler20120307::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CH_CREATE);
#undef HANDLER_FUNC
}

bool Horizon::Char::PacketHandler20120307::Handle_CH_CREATE(PacketBuffer &buf)
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	PacketVer20120307::PACKET_CH_CREATE pkt;
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
		return true;
	}

	// Check if the slot is not a premium.
	if (pkt.slot > game_account->get_character_slots()) {
		Send_HC_CREATE_ERROR_ACK(HC_CREATE_ERROR_CHAR_SLOT);
		return true;
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
