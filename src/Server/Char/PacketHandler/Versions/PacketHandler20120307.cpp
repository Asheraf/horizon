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

#include "Server/Common/PacketBuffer.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Char/Char.hpp"
#include "Server/Char/PacketHandler/Packets.hpp"
#include "Server/Char/Session/Session.hpp"
#include "Server/Char/Database/Query.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/Configuration/CharServerConfiguration.hpp"

Horizon::Char::PacketHandler20120307::PacketHandler20120307(std::shared_ptr<Session> session)
: PacketHandler(session)
{
	InitializeHandlers();
}

Horizon::Char::PacketHandler20120307::~PacketHandler20120307()
{
	//
}

void Horizon::Char::PacketHandler20120307::InitializeHandlers()
{
#define HANDLER_FUNC(packet) addPacketHandler(PacketVer20120307::packets::packet, boost::bind(&PacketHandler20120307::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CHAR_CREATE);
#undef HANDLER_FUNC
}

void Horizon::Char::PacketHandler20120307::Handle_CHAR_CREATE(PacketBuffer &buf)
{
	PacketVer20120307::PACKET_CHAR_CREATE pkt;
	character_gender_types gender;
	buf >> pkt;

	if (getSession()->getGameAccount()->getGender() == ACCOUNT_GENDER_MALE) {
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
	if (pkt.slot > getSession()->getGameAccount()->getCharacterSlots()) {
		Send_CHAR_CREATE_ERROR_ACK(CHAR_CREATE_ERROR_CHAR_SLOT);
		return;
	}

	std::shared_ptr<Horizon::Models::Characters::Character> character = std::make_shared<Horizon::Models::Characters::Character>(getSession()->getGameAccount()->getID(), pkt.name, pkt.slot, gender);
	character->setStatusData(std::make_shared<Horizon::Models::Characters::Status>(CharServer->getCharConfig().getStartZeny()));
	character->setViewData(std::make_shared<Horizon::Models::Characters::View>(pkt.hair_style, pkt.hair_color));
	character->setPositionData(std::make_shared<Horizon::Models::Characters::Position>(CharServer->getCharConfig().getStartMap(), CharServer->getCharConfig().getStartX(), CharServer->getCharConfig().getStartY()));

	// Save character to sql.
	character->create(CharServer);
	// Add character to account.
	getSession()->getGameAccount()->addCharacter(character);
	Send_CHAR_CREATE_SUCCESS_ACK(character);
}
