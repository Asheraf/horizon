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
namespace Game
{
	class Entity;
}
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
	virtual bool Handle_CZ_ENTER(PacketBuffer &buf);
	virtual bool Handle_CZ_LOGIN_TIMESTAMP(PacketBuffer &buf);
	virtual bool Handle_CZ_REQUEST_TIME(PacketBuffer &buf);
	virtual bool Handle_CZ_REQNAME(PacketBuffer &buf);
	virtual bool Handle_CZ_REQUEST_ACT(PacketBuffer &buf);
	virtual bool Handle_CZ_REQUEST_MOVE(PacketBuffer &buf);
	virtual bool Handle_CZ_RESTART(PacketBuffer &buf);
	virtual bool Handle_CZ_REQ_DISCONNECT(PacketBuffer &buf);
	virtual bool Handle_CZ_CHOOSE_MENU(PacketBuffer &buf);
	virtual bool Handle_CZ_REQ_NEXT_SCRIPT(PacketBuffer &buf);
	virtual bool Handle_CZ_INPUT_EDITDLG(PacketBuffer &buf);
	virtual bool Handle_CZ_INPUT_EDITDLGSTR(PacketBuffer &buf);
	virtual bool Handle_CZ_CLOSE_DIALOG(PacketBuffer &buf);
	virtual bool Handle_CZ_CHANGE_DIRECTION(PacketBuffer &buf);
	virtual bool Handle_CZ_CHANGE_DIRECTION2(PacketBuffer &buf);

	/**
	 * Senders
	 */
	virtual void Send_ZC_ERROR(zone_server_reject_types error);
	virtual void Send_ZC_RESTART_ACK(uint8_t type);
	virtual void Send_ZC_ACK_REQ_DISCONNECT(bool allowed);
	virtual void Send_ZC_ACCOUNT_ID();
	virtual void Send_ZC_ACCEPT_CONNECTION();
	virtual void Send_ZC_NPCACK_MAPMOVE(std::string const &map_name, uint16_t x, uint16_t y);
	virtual void Send_ZC_NOTIFY_TIME();
	virtual void Send_ZC_NOTIFY_UNITMOVE(uint32_t guid, uint16_t x, uint16_t y);
	virtual void Send_ZC_NOTIFY_PLAYERMOVE(uint16_t x, uint16_t y);
	virtual void Send_ZC_STOPMOVE(uint32_t guid, uint16_t x, uint16_t y);
	virtual void Send_ZC_PAR_CHANGE(uint16_t type, uint16_t value);
	virtual void Send_ZC_SAY_DIALOG(uint16_t npc_id, std::string &message);
	virtual void Send_ZC_WAIT_DIALOG(uint16_t npc_id);
	virtual void Send_ZC_MENU_LIST(uint16_t npc_id, std::string &menu_list);
	virtual void Send_ZC_OPEN_EDITDLG(uint16_t npc_id);
	virtual void Send_ZC_OPEN_EDITDLGSTR(uint16_t npc_id);
	virtual void Send_ZC_INITIAL_STATUS();
	virtual void Send_ZC_SPAWN_UNIT();
	virtual void Send_ZC_UPDATE_MAPINFO(uint16_t x, uint16_t y, const char *map_name, uint16_t type);
	virtual void Send_ZC_NOTIFY_GROUNDSKILL(uint16_t skill_id, uint32_t guid, uint16_t level, uint16_t x, uint16_t y, uint32_t duration);
	virtual void Send_ZC_NOTIFY_STANDENTRY10(Game::Entity *entity);
};
}
}

#endif //HORIZON_PACKETHANDLER_HPP

