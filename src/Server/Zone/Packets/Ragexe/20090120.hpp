/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20090120
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20090120

#include "Core/Multithreading/LockedLookupTable.hpp"

#include "Default.hpp"

#include <utility>

namespace Horizon
{
namespace Zone
{
/**
 * @brief Client Packet Length Table object that stores
 * the packet length of each packet of this client version.
 * Packets with IDs already existent in the database are over-written.
 * The data is stored in a thread-safe lookup table.
 * RAII techinque ensures that the table is populated on instantiation.
 */
class ClientPacketLengthTable : public PacketLengthTable
{
public:
	ClientPacketLengthTable(std::shared_ptr<ZoneSession> s)
	: PacketLengthTable(s)
	{
#define ADD_HPKT(i, j, k) _hpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
#define ADD_TPKT(i, j, k) _tpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
		ADD_HPKT(0x00e6, 58, CZ_ACK_EXCHANGE_ITEM);
		ADD_HPKT(0x0208, -1, CZ_ACK_REQ_ADD_FRIENDS);
		ADD_HPKT(0x00c5, 2, CZ_ACK_SELECT_DEALTYPE);
		ADD_HPKT(0x0172, 10, CZ_ALLY_GUILD);
		ADD_HPKT(0x0217, 14, CZ_BLACKSMITH_RANK);
		ADD_HPKT(0x0099, 4, CZ_BROADCAST);
		ADD_HPKT(0x00de, -1, CZ_CHANGE_CHATROOM);
		ADD_HPKT(0x0361, -1, CZ_CHANGE_DIRECTION2);
		ADD_HPKT(0x00b8, 10, CZ_CHOOSE_MENU);
		ADD_HPKT(0x0090, 3, CZ_CONTACTNPC);
		ADD_HPKT(0x0203, 2, CZ_DELETE_FRIENDS);
		ADD_HPKT(0x00cc, 39, CZ_DISCONNECT_CHARACTER);
		ADD_HPKT(0x01e7, 5, CZ_DORIDORI);
		ADD_HPKT(0x0436, -1, CZ_ENTER2);
		ADD_HPKT(0x00ef, 81, CZ_EXEC_EXCHANGE_ITEM);
		ADD_HPKT(0x00e3, 6, CZ_EXIT_ROOM);
		ADD_HPKT(0x017e, 186, CZ_GUILD_CHAT);
		ADD_HPKT(0x016e, 4, CZ_GUILD_NOTICE);
		ADD_HPKT(0x0143, -1, CZ_INPUT_EDITDLG);
		ADD_HPKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR);
		ADD_HPKT(0x02f6, 18, CZ_IRMAIL_LIST);
		ADD_HPKT(0x02f3, 4, CZ_IRMAIL_SEND);
		ADD_HPKT(0x013f, -1, CZ_ITEM_CREATE);
		ADD_HPKT(0x0362, -1, CZ_ITEM_PICKUP2);
		ADD_HPKT(0x0363, -1, CZ_ITEM_THROW2);
		ADD_HPKT(0x00ff, -1, CZ_JOIN_GROUP);
		ADD_HPKT(0x016b, -1, CZ_JOIN_GUILD);
		ADD_HPKT(0x0237, -1, CZ_KILLER_RANK);
		ADD_HPKT(0x00f9, 12, CZ_MAKE_GROUP);
		ADD_HPKT(0x01e8, -1, CZ_MAKE_GROUP2);
		ADD_HPKT(0x0140, -1, CZ_MOVETO_MAP);
		ADD_HPKT(0x0126, 14, CZ_MOVE_ITEM_FROM_BODY_TO_CART);
		ADD_HPKT(0x0364, 5, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2);
		ADD_HPKT(0x0127, 3, CZ_MOVE_ITEM_FROM_CART_TO_BODY);
		ADD_HPKT(0x0365, 67, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2);
		ADD_HPKT(0x0128, 6, CZ_MOVE_ITEM_FROM_STORE_TO_CART);
		ADD_HPKT(0x00c8, 8, CZ_PC_PURCHASE_ITEMLIST);
		ADD_HPKT(0x0134, 10, CZ_PC_PURCHASE_ITEMLIST_FROMMC);
		ADD_HPKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST);
		ADD_HPKT(0x01bc, 7, CZ_RECALL);
		ADD_HPKT(0x0161, 6, CZ_REG_CHANGE_GUILD_POSITIONINFO);
		ADD_HPKT(0x011d, 182, CZ_REMEMBER_WARPPOINT);
		ADD_HPKT(0x01ba, -1, CZ_REMOVE_AID);
		ADD_HPKT(0x0368, 71, CZ_REQNAME2);
		ADD_HPKT(0x0437, 57, CZ_REQUEST_ACT2);
		ADD_HPKT(0x0108, 6, CZ_REQUEST_CHAT_PARTY);
		ADD_HPKT(0x035f, 6, CZ_REQUEST_MOVE2);
		ADD_HPKT(0x0234, 10, CZ_REQUEST_MOVETOOWNER);
		ADD_HPKT(0x0360, -1, CZ_REQUEST_TIME2);
		ADD_HPKT(0x0170, 10, CZ_REQ_ALLY_GUILD);
		ADD_HPKT(0x0130, -1, CZ_REQ_BUY_FROMMC);
		ADD_HPKT(0x012a, 29, CZ_REQ_CARTOFF);
		ADD_HPKT(0x012e, 28, CZ_REQ_CLOSESTORE);
		ADD_HPKT(0x018a, 3, CZ_REQ_DISCONNECT);
		ADD_HPKT(0x0103, 66, CZ_REQ_EXPEL_GROUP_MEMBER);
		ADD_HPKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER);
		ADD_HPKT(0x014f, -1, CZ_REQ_GUILD_MENU);
		ADD_HPKT(0x017a, 11, CZ_REQ_ITEMCOMPOSITION_LIST);
		ADD_HPKT(0x0178, -1, CZ_REQ_ITEMIDENTIFY);
		ADD_HPKT(0x01fd, -1, CZ_REQ_ITEMREPAIR);
		ADD_HPKT(0x00fc, -1, CZ_REQ_JOIN_GROUP);
		ADD_HPKT(0x01ae, -1, CZ_REQ_MAKINGARROW);
		ADD_HPKT(0x01b2, -1, CZ_REQ_OPENSTORE2);
		ADD_HPKT(0x00ab, -1, CZ_REQ_TAKEOFF_EQUIP);
		ADD_HPKT(0x00c1, 6, CZ_REQ_USER_COUNT);
		ADD_HPKT(0x00d3, 7, CZ_REQ_WHISPER_LIST);
		ADD_HPKT(0x00b2, 97, CZ_RESTART);
		ADD_HPKT(0x011b, 32, CZ_SELECT_WARPPOINT);
		ADD_HPKT(0x00cf, -1, CZ_SETTING_WHISPER_PC);
		ADD_HPKT(0x01bb, 4, CZ_SHIFT);
		ADD_HPKT(0x00bb, -1, CZ_STATUS_CHANGE);
		ADD_HPKT(0x019f, 15, CZ_TRYCAPTURE_MONSTER);
		ADD_HPKT(0x0439, 10, CZ_USE_ITEM2);
		ADD_HPKT(0x0438, -1, CZ_USE_SKILL2);
		ADD_HPKT(0x0096, 30, CZ_WHISPER);
		ADD_TPKT(0x0073, -1, ZC_ACCEPT_ENTER);
		ADD_TPKT(0x0083, 6, ZC_ACCEPT_QUIT);
		ADD_TPKT(0x012c, 282, ZC_ACK_ADDITEM_TO_CART);
		ADD_TPKT(0x00ea, 3, ZC_ACK_ADD_EXCHANGE_ITEM);
		ADD_TPKT(0x00e7, 68, ZC_ACK_EXCHANGE_ITEM);
		ADD_TPKT(0x01f5, 11, ZC_ACK_EXCHANGE_ITEM2);
		ADD_TPKT(0x01fe, -1, ZC_ACK_ITEMREPAIR);
		ADD_TPKT(0x015a, 4, ZC_ACK_LEAVE_GUILD);
		ADD_TPKT(0x0274, 2, ZC_ACK_MAIL_RETURN);
		ADD_TPKT(0x011e, -1, ZC_ACK_REMEMBER_WARPPOINT);
		ADD_TPKT(0x018f, 10, ZC_ACK_REQMAKINGITEM);
		ADD_TPKT(0x0095, 53, ZC_ACK_REQNAME);
		ADD_TPKT(0x018b, 7, ZC_ACK_REQ_DISCONNECT);
		ADD_TPKT(0x0110, 30, ZC_ACK_TOUSESKILL);
		ADD_TPKT(0x0098, 20, ZC_ACK_WHISPER);
		ADD_TPKT(0x013b, -1, ZC_ACTION_FAILURE);
		ADD_TPKT(0x00e9, 54, ZC_ADD_EXCHANGE_ITEM);
		ADD_TPKT(0x0209, 6, ZC_ADD_FRIENDS_LIST);
		ADD_TPKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2);
		ADD_TPKT(0x00f4, 43, ZC_ADD_ITEM_TO_STORE);
		ADD_TPKT(0x0104, -1, ZC_ADD_MEMBER_TO_GROUP);
		ADD_TPKT(0x01e9, 27, ZC_ADD_MEMBER_TO_GROUP2);
		ADD_TPKT(0x021c, 79, ZC_ALCHEMIST_POINT);
		ADD_TPKT(0x0139, 54, ZC_ATTACK_FAILURE_FOR_DISTANCE);
		ADD_TPKT(0x0147, 30, ZC_AUTORUN_SKILL);
		ADD_TPKT(0x01cd, 18, ZC_AUTOSPELLLIST);
		ADD_TPKT(0x0219, -1, ZC_BLACKSMITH_RANK);
		ADD_TPKT(0x009a, 6, ZC_BROADCAST);
		ADD_TPKT(0x01c3, 2, ZC_BROADCAST2);
		ADD_TPKT(0x00ee, 8, ZC_CANCEL_EXCHANGE_ITEM);
		ADD_TPKT(0x0122, 3, ZC_CART_EQUIPMENT_ITEMLIST);
		ADD_TPKT(0x0297, 58, ZC_CART_EQUIPMENT_ITEMLIST2);
		ADD_TPKT(0x01ef, 14, ZC_CART_NORMAL_ITEMLIST2);
		ADD_TPKT(0x0230, 15, ZC_CHANGESTATE_MER);
		ADD_TPKT(0x00df, -1, ZC_CHANGE_CHATROOM);
		ADD_TPKT(0x00b6, -1, ZC_CLOSE_DIALOG);
		ADD_TPKT(0x01d2, 22, ZC_COMBODELAY);
		ADD_TPKT(0x0144, 6, ZC_COMPASS);
		ADD_TPKT(0x00ec, 2, ZC_CONCLUDE_EXCHANGE_ITEM);
		ADD_TPKT(0x01ea, 90, ZC_CONGRATULATION);
		ADD_TPKT(0x0141, 6, ZC_COUPLESTATUS);
		ADD_TPKT(0x020a, -1, ZC_DELETE_FRIENDS);
		ADD_TPKT(0x0125, 2, ZC_DELETE_ITEM_FROM_CART);
		ADD_TPKT(0x00f6, 21, ZC_DELETE_ITEM_FROM_STORE);
		ADD_TPKT(0x00d8, 4, ZC_DESTROY_ROOM);
		ADD_TPKT(0x0132, 2, ZC_DISAPPEAR_ENTRY);
		ADD_TPKT(0x00c0, 6, ZC_EMOTION);
		ADD_TPKT(0x00db, -1, ZC_ENTER_ROOM);
		ADD_TPKT(0x022f, 31, ZC_FEED_MER);
		ADD_TPKT(0x01a3, 6, ZC_FEED_PET);
		ADD_TPKT(0x0201, -1, ZC_FRIENDS_LIST);
		ADD_TPKT(0x0206, 4, ZC_FRIENDS_STATE);
		ADD_TPKT(0x0227, 29, ZC_GAME_GUARD);
		ADD_TPKT(0x0101, -1, ZC_GROUPINFO_CHANGE);
		ADD_TPKT(0x00fb, -1, ZC_GROUP_LIST);
		ADD_TPKT(0x017f, 33, ZC_GUILD_CHAT);
		ADD_TPKT(0x01b6, -1, ZC_GUILD_INFO2);
		ADD_TPKT(0x016f, 6, ZC_GUILD_NOTICE);
		ADD_TPKT(0x0162, -1, ZC_GUILD_SKILLINFO);
		ADD_TPKT(0x0239, -1, ZC_HOSKILLINFO_UPDATE);
		ADD_TPKT(0x02f5, -1, ZC_IRMAIL_NOTIFY);
		ADD_TPKT(0x02f4, 8, ZC_IRMAIL_SEND_RES);
		ADD_TPKT(0x017b, 17, ZC_ITEMCOMPOSITION_LIST);
		ADD_TPKT(0x0177, 2, ZC_ITEMIDENTIFY_LIST);
		ADD_TPKT(0x009d, -1, ZC_ITEM_ENTRY);
		ADD_TPKT(0x009e, -1, ZC_ITEM_FALL_ENTRY);
		ADD_TPKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2);
		ADD_TPKT(0x0238, -1, ZC_KILLER_RANK);
		ADD_TPKT(0x018d, 6, ZC_MAKABLEITEMLIST);
		ADD_TPKT(0x01ad, 60, ZC_MAKINGARROW_LIST);
		ADD_TPKT(0x00dd, 11, ZC_MEMBER_EXIT);
		ADD_TPKT(0x00dc, 26, ZC_MEMBER_NEWENTRY);
		ADD_TPKT(0x018c, 30, ZC_MONSTER_INFO);
		ADD_TPKT(0x010c, 2, ZC_MVP);
		ADD_TPKT(0x010b, 2, ZC_MVP_GETTING_SPECIAL_EXP);
		ADD_TPKT(0x014c, -1, ZC_MYGUILD_BASIC_INFO);
		ADD_TPKT(0x00a3, 5, ZC_NORMAL_ITEMLIST);
		ADD_TPKT(0x01ee, 2, ZC_NORMAL_ITEMLIST2);
		ADD_TPKT(0x02e1, 6, ZC_NOTIFY_ACT2);
		ADD_TPKT(0x007a, -1, ZC_NOTIFY_ACTENTRY);
		ADD_TPKT(0x0121, 2, ZC_NOTIFY_CARTITEM_COUNTINFO);
		ADD_TPKT(0x0109, 5, ZC_NOTIFY_CHAT_PARTY);
		ADD_TPKT(0x019b, 26, ZC_NOTIFY_EFFECT);
		ADD_TPKT(0x0117, 30, ZC_NOTIFY_GROUNDSKILL);
		ADD_TPKT(0x0106, 7, ZC_NOTIFY_HP_TO_GROUPM);
		ADD_TPKT(0x0189, 4, ZC_NOTIFY_MAPINFO);
		ADD_TPKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY);
		ADD_TPKT(0x0086, 10, ZC_NOTIFY_MOVE);
		ADD_TPKT(0x01da, 22, ZC_NOTIFY_MOVEENTRY2);
		ADD_TPKT(0x02ec, -1, ZC_NOTIFY_MOVEENTRY4);
		ADD_TPKT(0x0079, 3, ZC_NOTIFY_NEWENTRY);
		ADD_TPKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2);
		ADD_TPKT(0x022b, 3, ZC_NOTIFY_NEWENTRY3);
		ADD_TPKT(0x02ed, 2, ZC_NOTIFY_NEWENTRY4);
		ADD_TPKT(0x008e, 8, ZC_NOTIFY_PLAYERCHAT);
		ADD_TPKT(0x01eb, -1, ZC_NOTIFY_POSITION_TO_GUILDM);
		ADD_TPKT(0x0114, -1, ZC_NOTIFY_SKILL);
		ADD_TPKT(0x01de, -1, ZC_NOTIFY_SKILL2);
		ADD_TPKT(0x022a, 282, ZC_NOTIFY_STANDENTRY3);
		ADD_TPKT(0x02ee, 21, ZC_NOTIFY_STANDENTRY4);
		ADD_TPKT(0x007c, -1, ZC_NOTIFY_STANDENTRY_NPC);
		ADD_TPKT(0x00f2, 11, ZC_NOTIFY_STOREITEM_COUNTINFO);
		ADD_TPKT(0x0077, -1, ZC_NOTIFY_UPDATEPLAYER);
		ADD_TPKT(0x0093, 4, ZC_NPCACK_ENABLE);
		ADD_TPKT(0x0092, -1, ZC_NPCACK_SERVERMOVE);
		ADD_TPKT(0x012d, 11, ZC_OPENSTORE);
		ADD_TPKT(0x0142, 60, ZC_OPEN_EDITDLG);
		ADD_TPKT(0x01ab, 6, ZC_PAR_CHANGE_USER);
		ADD_TPKT(0x0287, -1, ZC_PC_CASH_POINT_ITEMLIST);
		ADD_TPKT(0x00c6, 6, ZC_PC_PURCHASE_ITEMLIST);
		ADD_TPKT(0x0136, 16, ZC_PC_PURCHASE_MYITEMLIST);
		ADD_TPKT(0x00c7, 2, ZC_PC_SELL_ITEMLIST);
		ADD_TPKT(0x0160, 6, ZC_POSITION_INFO);
		ADD_TPKT(0x022e, 8, ZC_PROPERTY_HOMUN);
		ADD_TPKT(0x01a2, 59, ZC_PROPERTY_PET);
		ADD_TPKT(0x013d, 36, ZC_RECOVERY);
		ADD_TPKT(0x01fc, -1, ZC_REPAIRITEMLIST);
		ADD_TPKT(0x0171, -1, ZC_REQ_ALLY_GUILD);
		ADD_TPKT(0x00e5, 5, ZC_REQ_EXCHANGE_ITEM);
		ADD_TPKT(0x01f4, -1, ZC_REQ_EXCHANGE_ITEM2);
		ADD_TPKT(0x016a, 34, ZC_REQ_JOIN_GUILD);
		ADD_TPKT(0x023a, -1, ZC_REQ_STORE_PASSWORD);
		ADD_TPKT(0x00aa, 53, ZC_REQ_WEAR_EQUIP_ACK);
		ADD_TPKT(0x0167, -1, ZC_RESULT_MAKE_GUILD);
		ADD_TPKT(0x00e1, -1, ZC_ROLE_CHANGE);
		ADD_TPKT(0x00d7, 2, ZC_ROOM_NEWENTRY);
		ADD_TPKT(0x00d1, 6, ZC_SETTING_WHISPER_PC);
		ADD_TPKT(0x00d2, -1, ZC_SETTING_WHISPER_STATE);
		ADD_TPKT(0x010f, -1, ZC_SKILLINFO_LIST);
		ADD_TPKT(0x0120, -1, ZC_SKILL_DISAPPEAR);
		ADD_TPKT(0x011f, 282, ZC_SKILL_ENTRY);
		ADD_TPKT(0x01c9, 10, ZC_SKILL_ENTRY2);
		ADD_TPKT(0x01ac, -1, ZC_SKILL_UPDATE);
		ADD_TPKT(0x01e1, 26, ZC_SPIRITS2);
		ADD_TPKT(0x020e, 6, ZC_STARSKILL);
		ADD_TPKT(0x0229, 9, ZC_STATE_CHANGE3);
		ADD_TPKT(0x00bd, -1, ZC_STATUS);
		ADD_TPKT(0x00be, -1, ZC_STATUS_CHANGE);
		ADD_TPKT(0x0088, -1, ZC_STOPMOVE);
		ADD_TPKT(0x0131, -1, ZC_STORE_ENTRY);
		ADD_TPKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST);
		ADD_TPKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2);
		ADD_TPKT(0x00a5, 54, ZC_STORE_NORMAL_ITEMLIST);
		ADD_TPKT(0x0224, 26, ZC_TAEKWON_POINT);
		ADD_TPKT(0x016d, 10, ZC_UPDATE_CHARSTAT);
		ADD_TPKT(0x00c2, 5, ZC_USER_COUNT);
		ADD_TPKT(0x013e, 23, ZC_USESKILL_ACK);
		ADD_TPKT(0x00a8, -1, ZC_USE_ITEM_ACK);
		ADD_TPKT(0x01c8, -1, ZC_USE_ITEM_ACK2);
		ADD_TPKT(0x011a, 9, ZC_USE_SKILL);
		ADD_TPKT(0x00b5, -1, ZC_WAIT_DIALOG);
		ADD_TPKT(0x0097, -1, ZC_WHISPER);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20090120 */