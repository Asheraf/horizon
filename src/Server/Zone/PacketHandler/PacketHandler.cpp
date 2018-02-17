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
#include "Server/Zone/PacketHandler/Packets.hpp"
#include "Server/Zone/Session/Session.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/GameAccount.hpp"
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
	pkt.start_time = time(nullptr);
	PackPosition(pkt.packed_position, 51, 111, 4);
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
