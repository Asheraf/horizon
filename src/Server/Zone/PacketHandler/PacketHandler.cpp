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
#include "Server/Zone/Session/Session.hpp"
#include "Server/Zone/Zone.hpp"
#include "Utility/Utility.hpp"

#include <boost/bind.hpp>

/**
 * @brief Packet Handler Constructor.
 */
Horizon::Zone::PacketHandler::PacketHandler(std::shared_ptr<Session> session)
: Horizon::Base::PacketHandler<Session>(session)
{
	InitializeHandlers();
}

/**
 * @brief Packet Handler destructor.
 */
Horizon::Zone::PacketHandler::~PacketHandler()
{
}

/**
 * @brief Initialize packet handlers.
 */
void Horizon::Zone::PacketHandler::InitializeHandlers()
{
#define HANDLER_FUNC(packet) addPacketHandler(packet, boost::bind(&PacketHandler::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CZ_LOGIN_TIMESTAMP);
#undef HANDLER_FUNC
}

/*==============*
 * Handler Methods
 *==============*/
void Horizon::Zone::PacketHandler::Handle_CZ_LOGIN_TIMESTAMP(PacketBuffer &buf)
{
	PACKET_CZ_LOGIN_TIMESTAMP pkt;
	buf >> pkt;
	ZoneLog->info("Account '{}' has successfully logged in.", getSession()->getGameAccount()->getID());
}

void Horizon::Zone::PacketHandler::Handle_CZ_REQUEST_TIME(PacketBuffer &buf)
{
	PACKET_CZ_REQUEST_TIME pkt(buf.getOpCode());
	buf >> pkt;
	Send_ZC_NOTIFY_TIME();
}

void Horizon::Zone::PacketHandler::Handle_CZ_REQNAME(PacketBuffer &buf)
{
	PACKET_CZ_REQNAME pkt(buf.getOpCode());
	buf >> pkt;
	// find and return guid name.
}

void Horizon::Zone::PacketHandler::Handle_CZ_ENTER(PacketBuffer &buf)
{
	std::shared_ptr<Session> session = getSession();
	PACKET_CZ_ENTER pkt(buf.getOpCode());
	buf >> pkt;

	session->setSessionData(ZoneInterAPI->GetSessionFromInter(pkt.auth_code));
	if (session->getSessionData() == nullptr) {
		ZoneLog->info("New connection attempt from unauthorized session '{}'.", pkt.auth_code);
		session->getPacketHandler()->Send_ZC_ERROR(ZONE_SERV_ERROR_REJECT);
		return;
	}

	session->setGameAccount(ZoneInterAPI->GetGameAccountFromInter(pkt.account_id));
	if (session->getGameAccount() == nullptr) {
		ZoneLog->info("New connection attempt from unknown account '{}'.", pkt.account_id);
		session->getPacketHandler()->Send_ZC_ERROR(ZONE_SERV_ERROR_REJECT);
		return;
	}

	session->setCharacter(std::make_shared<Character>());
	if (!session->getCharacter()->loadAll(ZoneServer, pkt.char_id)) {
		ZoneLog->info("Attempted connection for non-existent character {} by account {}.", pkt.account_id, pkt.char_id);
		session->getPacketHandler()->Send_ZC_ERROR(ZONE_SERV_ERROR_REJECT);
		return;
	}

	session->setPlayer(std::make_shared<Player>(pkt.account_id, session->getCharacter()));

	Send_ZC_ACCOUNT_ID();
	Send_ZC_ACCEPT_CONNECTION();
	
	//getPacketHandler()->Send_ZC_NPCACK_MAPMOVE("prontera", 101, 120);
	ZoneLog->info("New connection established for account '{}' using version '{}' from '{}'.",
				  pkt.account_id, session->getSessionData()->getClientVersion(), session->getRemoteIPAddress());
}

void Horizon::Zone::PacketHandler::Handle_CZ_REQUEST_ACT(PacketBuffer &buf)
{
	PACKET_CZ_REQUEST_ACT pkt(buf.getOpCode());
	buf >> pkt;
	printf("act %d %d\n", pkt.target_guid, pkt.action);
}

void Horizon::Zone::PacketHandler::Handle_CZ_REQUEST_MOVE(PacketBuffer &buf)
{
	uint16_t x = 0, y = 0;
	uint8_t dir = 0;
	PACKET_CZ_REQUEST_MOVE pkt(buf.getOpCode());

	buf >> pkt;

	UnpackPosition(pkt.packed_destination, &x, &y, &dir);

	printf("move %d %d %d\n", x, y, dir);
}

/*==============*
 * Sender Methods
 *==============*/
void Horizon::Zone::PacketHandler::Send_ZC_ERROR(zone_server_reject_types error)
{
	PACKET_ZC_ERROR pkt;
	pkt.error = error;
	SendPacket(pkt);
}

void Horizon::Zone::PacketHandler::Send_ZC_ACCOUNT_ID()
{
	PACKET_ZC_ACCOUNT_ID pkt;
	pkt.account_id = getSession()->getGameAccount()->getID();
	SendPacket(pkt);
}

void Horizon::Zone::PacketHandler::Send_ZC_ACCEPT_CONNECTION()
{
	PACKET_ZC_ACCEPT_CONNECTION pkt;
	int x = getSession()->getCharacter()->getPositionData()->getCurrentX();
	int y = getSession()->getCharacter()->getPositionData()->getCurrentY();

	if (x == 0 && y == 0) {
		if ((x = getSession()->getCharacter()->getPositionData()->getSavedX()) == 0)
			x = 53;
		if ((y = getSession()->getCharacter()->getPositionData()->getSavedY()) == 0)
			y = 111;
	}

	pkt.start_time = time(nullptr);
	PackPosition(pkt.packed_position, x, y, 4);
	pkt.x_size = pkt.y_size = 5;
	pkt.font = 0;
	pkt.gender = getSession()->getGameAccount()->getGender();
	SendPacket(pkt);
}

void Horizon::Zone::PacketHandler::Send_ZC_NPCACK_MAPMOVE(std::string const &map_name, uint16_t x, uint16_t y)
{
	PACKET_ZC_NPCACK_MAPMOVE pkt;
	strncpy(pkt.map_name, map_name.c_str(), MAP_NAME_LENGTH_EXT);
	pkt.x = x;
	pkt.y = y;
	SendPacket(pkt);
}

void Horizon::Zone::PacketHandler::Send_ZC_NOTIFY_TIME()
{
	PACKET_ZC_NOTIFY_TIME pkt;
	pkt.timestamp = time(nullptr);
	SendPacket(pkt);
}
