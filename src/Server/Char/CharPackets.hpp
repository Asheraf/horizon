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

#ifndef HORIZON_CHARPACKETS_H
#define HORIZON_CHARPACKETS_H

namespace Horizon
{
namespace Char
{
enum packets
{
	/**
	 * Receivable Packets
	 */
	CH_ENTER              =  0x65,
	CH_SELECT_CHAR        =  0x66,
	CH_MAKE_CHAR          =  0x67,
	CH_DELETE_CHAR        =  0x68,
	/**
	 * Sendable Packets
	 */
	HC_ACCEPT_ENTER       =  0x6B,
	HC_REFUSE_ENTER       =  0x6C,
	HC_ACCEPT_MAKECHAR    =  0x6D,
	HC_REFUSE_MAKECHAR    =  0x6E,
	HC_ACCEPT_DELETECHAR  =  0x6F,
	HC_REFUSE_DELETECHAR  =  0x70,
	HC_NOTIFY_ZONESVR     =  0x71,
};
}
}

#endif //HORIZON_CHARPACKETS_H
