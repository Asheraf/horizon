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

#ifndef HORIZON_ZONE_RE_PACKETS_HPP
#define HORIZON_ZONE_RE_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE
{
enum packets
{
	CZ_REQ_PVPPOINT = 0x020f,
	CZ_REQ_SEND_RODEX = 0x09ec,
	CZ_USE_SKILL_TOGROUND = 0x0116,
	ZC_ACK_PVPPOINT = 0x0210,
	ZC_ACK_REQNAME_BYGID = 0x0194,
	ZC_ACK_RODEX_LIST = 0x09f0,
	ZC_ADD_MEMBER_TO_GROUP = 0x0a43,
	ZC_ADD_QUEST_EX = 0x09f9,
	ZC_AUTOSPELLLIST = 0x01cd,
	ZC_CHECK_RECEIVE_CHARACTER_NAME = 0x0a14,
	ZC_GROUP_LIST = 0x0a44,
	ZC_GUILD_INFO = 0x0150,
	ZC_MEMBERMGR_INFO = 0x0154,
	ZC_MEMBER_ADD = 0x0182,
	ZC_OPEN_UI = 0x0a38,
	ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM = 0x091c,
	ZC_PRNPC_STATE = 0x091b,
	ZC_STORE_ITEMLIST_EQUIP_V6 = 0x0a10,
	ZC_UPDATE_MISSION_HUNT_EX = 0x09fa,
};
}
}
}
#endif /* HORIZON_ZONE_RE_PACKETS_HPP */
