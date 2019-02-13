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

#ifndef HORIZON_ZONE_ZERO_PACKETS_HPP
#define HORIZON_ZONE_ZERO_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Zero
{
enum packets
{
	CZ_OPEN_RODEXBOX = 0x0ac0,
	CZ_PRIVATE_AIRSHIP_REQUEST = 0x0a49,
	CZ_REQ_REFRESH_RODEX = 0x0ac1,
	ZC_ACK_REQNAME = 0x0adf,
	ZC_ACK_RODEX_LIST = 0x0ac2,
	ZC_ADD_MEMBER_TO_GROUP = 0x0104,
	ZC_ALT_EQUIPMENT_EQUIP = 0x0a98,
	ZC_EQUIPWIN_OTHER = 0x0adc,
	ZC_GROUP_LIST = 0x00fb,
	ZC_ITEM_FALL_ENTRY = 0x0add,
	ZC_ITEM_PREVIEW = 0x0ab9,
	ZC_NOTIFY_EXP = 0x0acc,
	ZC_NPCACK_SERVERMOVE = 0x0ac7,
	ZC_OVERWEIGHT_PERCENT = 0x0ade,
	ZC_PARTY_MEMBER_JOB_LEVEL = 0x0abd,
	ZC_PAR_CHANGE = 0x0acb,
	ZC_REFINE_STATUS = 0x0ada,
	ZC_UNKNOWN_CLEAN_ITEMS_LISTS = 0x0ac8,
	ZC_WARPLIST = 0x0abe,
};
}
}
}
#endif /* HORIZON_ZONE_ZERO_PACKETS_HPP */
