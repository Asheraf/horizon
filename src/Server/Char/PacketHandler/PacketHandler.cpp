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
#include "Server/Char/Session/Session.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Char/Database/Query.hpp"
#include "Server/Common/Models/Configuration/CharServerConfiguration.hpp"

#include <boost/bind.hpp>

/**
 * @brief Packet Handler Constructor.
 */
Horizon::Char::PacketHandler::PacketHandler(std::shared_ptr<Session> session)
: Horizon::Base::PacketHandler<Session>(session)
{
	InitializeHandlers();
}

/**
 * @brief Packet Handler destructor.
 */
Horizon::Char::PacketHandler::~PacketHandler()
{
}

/**
 * @brief Initialize packet handlers.
 */
void Horizon::Char::PacketHandler::InitializeHandlers()
{
#define HANDLER_FUNC(packet) addPacketHandler(packet, boost::bind(&PacketHandler::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CHAR_KEEP_ALIVE);
	HANDLER_FUNC(CHAR_CREATE);
#undef HANDLER_FUNC
}

/*==============*
 * Handler Methods
 *==============*/

/**
 * @brief Receive and handle the CHAR_CONNCET packet.
 * @param[in|out] buf    Validated PacketBuffer received by the char-server.
 */
void Horizon::Char::PacketHandler::Handle_CHAR_CONNECT(PACKET_CHAR_CONNECT &/*pkt*/)
{
	CharQuery->AllCharactersByAccount(getSession()->getGameAccount());
	
	// Send acceptance notice to client.
	Respond_CHAR_ACCOUNT_ID();         // 1st

	// Send character list info.
	Respond_CHAR_SLOT_INFO_ACK();      // 2nd
	Respond_CHAR_LIST_ACK();           // 3rd
	Respond_CHAR_BAN_LIST_ACK();       // 4th
	Respond_CHAR_PINCODE_STATE_ACK();  // 5th
}

void Horizon::Char::PacketHandler::Handle_CHAR_CREATE(PacketBuffer &buf)
{
	PACKET_CHAR_CREATE pkt;
	buf >> pkt;

	std::shared_ptr<Horizon::Models::Characters::Character> character = std::make_shared<Horizon::Models::Characters::Character>(
			getSession()->getGameAccount()->getID(), pkt.name, pkt.slot, getSession()->getGameAccount()->getGender() == ACCOUNT_GENDER_MALE ? CHARACTER_GENDER_MALE : CHARACTER_GENDER_FEMALE);
	character->setStatusData(std::make_shared<Horizon::Models::Characters::Status>(
			CharServer->getCharConfig()->getStartZeny(), pkt.str, pkt.agi, pkt.int_, pkt.vit, pkt.dex, pkt.luk));
	character->setViewData(std::make_shared<Horizon::Models::Characters::View>(pkt.hair_style, pkt.hair_color));
	character->setPositionData(std::make_shared<Horizon::Models::Characters::Position>(
			CharServer->getCharConfig()->getStartMap(), CharServer->getCharConfig()->getStartX(), CharServer->getCharConfig()->getStartY()));

	character->setMiscData(std::make_shared<Horizon::Models::Characters::Misc>());
	character->setUISettingsData(std::make_shared<Horizon::Models::Characters::UISettings>());
	character->setAccessData(std::make_shared<Horizon::Models::Characters::Access>());
	character->setCompanionData(std::make_shared<Horizon::Models::Characters::Companion>());
	character->setFamilyData(std::make_shared<Horizon::Models::Characters::Family>());
	character->setGroupData(std::make_shared<Horizon::Models::Characters::Group>());
	// Add character to account.
	getSession()->getGameAccount()->addCharacter(character);
	// Save character to sql.
	character->saveAll(CharServer);
	Respond_CHAR_CREATE_ACK(character);
}

/**
 * @brief Receive and handle the CHAR_KEEP_ALIVE packet.
 * @param[in|out] buf    Validated PacketBuffer received by the char-server.
 */
void Horizon::Char::PacketHandler::Handle_CHAR_KEEP_ALIVE(PacketBuffer &/*buf*/)
{
	// We do nothing here as yet, its just a keep-alive.
	// PACKET_CHAR_KEEP_ALIVE pkt;
	// buf >> pkt;
}

/*==============*
 * Responder Methods
 *==============*/

/**
 * @brief Respond to the client with the CHAR_CONNECT_ERROR packet.
 * @param[in] error    error code to be sent, @see character_connect_errors.
 */
void Horizon::Char::PacketHandler::Respond_CHAR_CONNECT_ERROR(character_connect_errors error)
{
	PACKET_CHAR_CONNECT_ERROR pkt;
	pkt.error = error;
	SendPacket(pkt);
}

/**
 * @brief Respond to the client with the Account ID to initiate client connection.
 * @note This packet has no ID but is required by the client.
 * @param[in] account_id   Account ID of the session.
 */
void Horizon::Char::PacketHandler::Respond_CHAR_ACCOUNT_ID()
{
	PACKET_CHAR_ACCOUNT_ID pkt;
	pkt.account_id = getSession()->getSessionData()->getGameAccountID();
	SendPacket(pkt);
}

/**
 * @brief Respond to the client with the CHAR_SLOT_INFO_ACK packet on client connection.
 * @see Horizon::Char::packets
 */
void Horizon::Char::PacketHandler::Respond_CHAR_SLOT_INFO_ACK()
{
	PACKET_CHAR_SLOT_INFO_ACK pkt;
	pkt.total_slots = MAX_CHARACTER_SLOTS;
	pkt.premium_slots = getSession()->getSessionData()->getCharacterSlots();
	pkt.char_slots_1 = getSession()->getSessionData()->getCharacterSlots();
	pkt.char_slots_2 = getSession()->getSessionData()->getCharacterSlots();
	SendPacket(pkt);
	CharLog->info("Sent character-slot information to AID {}", getSession()->getSessionData()->getGameAccountID());
}

/**
 * @brief Respond to the client with the CHAR_LIST_ACK packet on client connection.
 * @see Horizon::Char::packets
 */
void Horizon::Char::PacketHandler::Respond_CHAR_LIST_ACK()
{
	PACKET_CHAR_LIST_ACK pkt;
	PacketBuffer buf;
	std::vector<character_list_data> char_list;
	int char_list_length = 0;

	for (auto c : getSession()->getGameAccount()->getAllCharacters()) {
		character_list_data c_data;
		c_data.create(c.second);
		c_data.gender = getSession()->getGameAccount()->getGender() == ACCOUNT_GENDER_NONE
			? c.second->getGender()
			: getSession()->getGameAccount()->getGender();
		char_list.push_back(c_data);
		char_list_length += sizeof(c_data);
	}

	pkt.packet_len += char_list_length;

	buf.append(&pkt, sizeof(pkt));

	for (auto c : char_list) {
		buf.append(&c, sizeof(c));
	}

	SendPacket(buf, pkt.packet_len);

	CharLog->info("Sent character-list information to AID {}", getSession()->getSessionData()->getGameAccountID());
}

/**
 * @brief Respond to the client with the CHAR_BAN_LIST_ACK packet on client connection.
 * @see Horizon::Char::packets
 */
void Horizon::Char::PacketHandler::Respond_CHAR_BAN_LIST_ACK()
{
	PACKET_CHAR_BAN_LIST_ACK pkt;
	SendPacket(pkt);
	CharLog->info("Send character ban-list information to AID {}", getSession()->getGameAccount()->getID());
}

/**
 * @brief Respond to the client with the CHAR_PINCODE_STATE_ACK packet on client connection.
 * @see Horizon::Char::packets
 */
void Horizon::Char::PacketHandler::Respond_CHAR_PINCODE_STATE_ACK()
{
	PACKET_CHAR_PINCODE_STATE_ACK pkt;
	pkt.pincode_seed = rand() % 0xFFFF;
	pkt.account_id = getSession()->getSessionData()->getGameAccountID();
	pkt.state = PINCODE_CORRECT;
	SendPacket(pkt);
}

void Horizon::Char::PacketHandler::Respond_CHAR_CREATE_ACK(std::shared_ptr<Horizon::Models::Characters::Character> character)
{
	PACKET_CHAR_CREATE_ACK pkt;

	pkt.data.create(character);
	pkt.data.gender = getSession()->getGameAccount()->getGender() == ACCOUNT_GENDER_NONE
	? character->getGender()
	: getSession()->getGameAccount()->getGender();

	SendPacket(pkt);
}
