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

#ifndef HORIZON_ZONE_ZERO_20180703_PACKETHANDLER_HPP
#define HORIZON_ZONE_ZERO_20180703_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_ACK_STORE_PASSWORD.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_ADD_FRIENDS.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_CHANGE_DIRECTION.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_COMMAND_MER.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_ENTER.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_GANGSI_RANK.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_ITEMLISTWIN_RES.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_ITEM_PICKUP.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_ITEM_THROW.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_JOIN_BATTLE_FIELD.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_PARTY_BOOKING_REQ_REGISTER.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_PARTY_JOIN_REQ.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_REQNAME.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_REQNAME_BYGID.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_REQUEST_ACT.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_REQUEST_MOVE.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_REQUEST_TIME.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_REQ_CLICK_TO_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_REQ_CLOSE_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_REQ_OPEN_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_REQ_TRADE_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_SEARCH_STORE_INFO.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_SEARCH_STORE_INFO_NEXT_PAGE.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_SSILIST_ITEM_CLICK.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_USE_SKILL.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_USE_SKILL_TOGROUND.hpp"
#include "Server/Zone/Packets/Zero/20180703/Structs/PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX.hpp"
#include "Server/Zone/Packets/Zero/20180627/PacketHandlerZero20180627.hpp"

namespace Horizon
{
namespace Zone
{

class ZoneSocket;

class PacketHandlerZero20180703 : public PacketHandlerZero20180627
{
public:
	PacketHandlerZero20180703(std::shared_ptr<ZoneSocket> socket);
	~PacketHandlerZero20180703();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_ZONE_Zero_20180703_PACKETHANDLER_HPP */
