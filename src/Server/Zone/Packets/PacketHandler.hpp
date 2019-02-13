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
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"
#include <memory>

class PacketBuffer;
class SessionData;

namespace Horizon
{
namespace Zone
{
enum zone_server_reject_types : uint8_t
{
	ZONE_SERV_ERROR_REJECT = 3,
};
enum zc_ack_guild_menuinterface_mask_types
{
	GMIF_BASIC_INFO     = 0x00,
	GMIF_MEMBER_MANAGER = 0x01,
	GMIF_POSITIONS      = 0x02,
	GMIF_SKILLS         = 0x04,
	GMIF_EXPULSION_LIST = 0x10,
	GMIF_ALLGUILDLIST   = 0x40,
	GMIF_NOTICE         = 0x80,
	GMIF_MEMBER         = GMIF_ALLGUILDLIST | GMIF_EXPULSION_LIST | GMIF_SKILLS | GMIF_POSITIONS | GMIF_MEMBER_MANAGER,
	GMIF_MASTER         = GMIF_NOTICE | GMIF_MEMBER,
};
enum cz_req_guild_menu_types
{
	CZ_REQ_GUILD_BASIC_INFO     = 0,
	CZ_REQ_GUILD_MEMBER_MANAGER = 1,
	CZ_REQ_GUILD_POSITIONS      = 2,
	CZ_REQ_GUILD_SKILLS         = 3,
	CZ_REQ_GUILD_EXPULSION_LIST = 4,
	CZ_REQ_GM_ALLGUILDLIST      = 5,
	CZ_REQ_GUILD_NOTICE         = 6
};
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
	virtual bool Handle_CZ_CLIENT_VERSION(PacketBuffer &buf);
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
	virtual bool Handle_CZ_REQUEST_CHAT(PacketBuffer &buf);

	virtual bool verify_new_connection(uint32_t auth_code, uint32_t account_id, uint32_t char_id);
	virtual void process_player_entry();
	/**
	 * Senders
	 */
	virtual void Send_ZC_REFUSE_ENTER(zone_server_reject_types error);
	virtual void Send_ZC_RESTART_ACK(uint8_t type);
	virtual void Send_ZC_ACK_REQ_DISCONNECT(bool allowed);
	virtual void Send_ZC_AID();
	virtual void Send_ZC_ACCEPT_ENTER3();
	virtual void Send_ZC_NPCACK_MAPMOVE(std::string const &map_name, uint16_t x, uint16_t y);
	virtual void Send_ZC_NOTIFY_TIME();
	virtual void Send_ZC_NOTIFY_MOVE(uint32_t guid, MapCoords from, MapCoords to);
	virtual void Send_ZC_NOTIFY_PLAYERMOVE(uint16_t x, uint16_t y);
	virtual void Send_ZC_STOPMOVE(uint32_t guid, uint16_t x, uint16_t y);
	virtual void Send_ZC_PAR_CHANGE(uint16_t type, uint16_t value);
	virtual void Send_ZC_SAY_DIALOG(uint16_t npc_id, std::string &message);
	virtual void Send_ZC_WAIT_DIALOG(uint16_t npc_id);
	virtual void Send_ZC_MENU_LIST(uint16_t npc_id, std::string &menu_list);
	virtual void Send_ZC_OPEN_EDITDLG(uint16_t npc_id);
	virtual void Send_ZC_OPEN_EDITDLGSTR(uint16_t npc_id);
	virtual void Send_ZC_STATUS();
	virtual void Send_ZC_NOTIFY_NEWENTRY5();
	virtual void Send_ZC_UPDATE_MAPINFO(uint16_t x, uint16_t y, const char *map_name, uint16_t type);
	virtual void Send_ZC_NOTIFY_GROUNDSKILL(uint16_t skill_id, uint32_t guid, uint16_t level, uint16_t x, uint16_t y, uint32_t duration);
	virtual void Send_ZC_NOTIFY_STANDENTRY(entity_viewport_entry const &entry);
	virtual void Send_ZC_NOTIFY_MOVEENTRY(entity_viewport_entry const &entry);
	virtual void Send_ZC_NOTIFY_CHAT(uint32_t guid, std::string message, player_notifier_types type);
	virtual void Send_ZC_NOTIFY_PLAYERCHAT(std::string message);
	virtual void Send_ZC_NPC_CHAT(uint32_t guid, std::string message, player_notifier_types type);
};
}
}

#endif //HORIZON_PACKETHANDLER_HPP

