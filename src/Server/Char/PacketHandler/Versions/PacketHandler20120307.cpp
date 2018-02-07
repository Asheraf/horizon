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
	buf >> pkt;

	std::shared_ptr<Horizon::Models::Characters::Character> character = std::make_shared<Horizon::Models::Characters::Character>(this->getSession()->getGameAccount()->getID(), pkt.name, pkt.slot, getSession()->getGameAccount()->getGender() == ACCOUNT_GENDER_MALE ? CHARACTER_GENDER_MALE : CHARACTER_GENDER_FEMALE);
	std::shared_ptr<Horizon::Models::Characters::Status> status = std::make_shared<Horizon::Models::Characters::Status>();
	status->setZeny(CharServer->getCharConfig()->getStartZeny());
	character->setStatusData(status);
	character->setViewData(std::make_shared<Horizon::Models::Characters::View>(pkt.hair_style, pkt.hair_color));
	character->setPositionData(std::make_shared<Horizon::Models::Characters::Position>(CharServer->getCharConfig()->getStartMap(), CharServer->getCharConfig()->getStartX(), CharServer->getCharConfig()->getStartY()));

	character->setMiscData(std::make_shared<Horizon::Models::Characters::Misc>());
	character->setUISettingsData(std::make_shared<Horizon::Models::Characters::UISettings>());
	character->setAccessData(std::make_shared<Horizon::Models::Characters::Access>());
	character->setCompanionData(std::make_shared<Horizon::Models::Characters::Companion>());
	character->setFamilyData(std::make_shared<Horizon::Models::Characters::Family>());
	character->setGroupData(std::make_shared<Horizon::Models::Characters::Group>());
	// Add character to account.
	this->getSession()->getGameAccount()->addCharacter(character);
	// Save character to sql.
	character->saveAll(CharServer);
	Respond_CHAR_CREATE_ACK(character);
}
