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

#ifndef HORIZON_ZONE_PACKETHANDLER_HPP
#define HORIZON_ZONE_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Base/PacketHandler/PacketHandler.hpp"
#include "Server/Zone/PacketHandler/Packets.hpp"
#include <memory>

class PacketBuffer;
class SessionData;

namespace Horizon
{
namespace Zone
{
class ZoneSocket;
class PacketHandler : public Horizon::Base::PacketHandler<ZoneSocket>
{
public:
	explicit PacketHandler(std::shared_ptr<ZoneSocket> socket);
	virtual ~PacketHandler();

	virtual void initialize_handlers();
	/**
	 * Handlers
	 */
	virtual void Handle_CZ_ENTER(PacketBuffer &buf);
	virtual void Handle_CZ_LOGIN_TIMESTAMP(PacketBuffer &buf);
	virtual void Handle_CZ_REQUEST_TIME(PacketBuffer &buf);
	virtual void Handle_CZ_REQNAME(PacketBuffer &buf);
	virtual void Handle_CZ_REQUEST_ACT(PacketBuffer &buf);
	virtual void Handle_CZ_REQUEST_MOVE(PacketBuffer &buf);
	/**
	 * Senders
	 */
	virtual void Send_ZC_ERROR(zone_server_reject_types error);
	virtual void Send_ZC_ACCOUNT_ID();
	virtual void Send_ZC_ACCEPT_CONNECTION();
	virtual void Send_ZC_NPCACK_MAPMOVE(std::string const &map_name, uint16_t x, uint16_t y);
	virtual void Send_ZC_NOTIFY_TIME();
	virtual void Send_ZC_NOTIFY_UNITMOVE(uint32_t guid, uint16_t x, uint16_t y);
	virtual void Send_ZC_NOTIFY_PLAYERMOVE(uint16_t x, uint16_t y);
	virtual void Send_ZC_STOPMOVE(uint32_t guid, uint16_t x, uint16_t y);
	virtual void Send_ZC_PAR_CHANGE(uint16_t type, uint16_t value);
	virtual void Send_ZC_INITIAL_STATUS();
	virtual void Send_ZC_SPAWN_UNIT();
	virtual void Send_ZC_UPDATE_MAPINFO(uint16_t x, uint16_t y, const char *map_name, uint16_t type);
	virtual void Send_ZC_NOTIFY_GROUNDSKILL(uint16_t skill_id, uint32_t guid, uint16_t level, uint16_t x, uint16_t y, uint32_t duration);
};
}
}

#endif //HORIZON_PACKETHANDLER_HPP

