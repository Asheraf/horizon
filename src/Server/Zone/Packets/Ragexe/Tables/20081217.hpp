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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081217
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081217

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"

#include "Default.hpp"

#include <utility>

namespace Horizon
{
namespace Zone
{
namespace ShufflePackets
{
/**
 * @brief Shuffle Packet Length Table object that stores
 * the packet length of each packet of this client version.
 * Packets with IDs already existent in the database are over-written.
 * The data is stored in a thread-safe lookup table.
 * RAII techinque ensures that the table is populated on instantiation.
 */
class ShufflePacketLengthTable : public PacketLengthTable
{
public:
	ShufflePacketLengthTable()
	{
		std::shared_ptr<ZoneSocket> sock = get_socket();

#define ADD_PKT(i, j, k) _packet_length_table.insert(i, std::make_pair<uint16_t, NetworkPacket>(j, k))
		ADD_PKT(0x00c5, -1, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, -1, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 9, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0172, -1, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0099, 31, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 4, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 13, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 60, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, -1, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x01ed, 67, CZ_CHOPOKGI(sock));
		ADD_PKT(0x022d, -1, CZ_COMMAND_MER(sock));
		ADD_PKT(0x00eb, 6, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 58, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x00ce, 8, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, -1, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x0436, -1, CZ_ENTER2(sock));
		ADD_PKT(0x00ef, 2, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, -1, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 2, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 2, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, 4, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 3, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, -1, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x00ff, 5, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, 6, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, -1, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x0126, 14, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0127, -1, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, 7, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, 4, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, -1, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x01bc, 4, CZ_RECALL(sock));
		ADD_PKT(0x01bd, -1, CZ_RECALL_GID(sock));
		ADD_PKT(0x011d, -1, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 15, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, -1, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, 4, CZ_REQNAME2(sock));
		ADD_PKT(0x0233, -1, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0232, 3, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, 10, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, -1, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 26, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 11, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, 7, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, 8, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 55, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 7, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 6, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 8, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x014f, -1, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 6, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017a, 24, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x01ae, 2, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, -1, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x00a9, 30, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, -1, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 23, CZ_RESTART(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, -1, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x0112, -1, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0439, 3, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0438, 10, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0367, 6, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0073, -1, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 3, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 79, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, -1, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 6, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, 42, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, 2, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 53, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fe, 15, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, 3, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 29, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 3, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x00fd, 10, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 2, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0098, 9, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x00e9, -1, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x00f4, 14, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 9, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x01e9, -1, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, -1, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021a, -1, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0147, 2, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, 20, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x021b, 28, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 282, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 65, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 6, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 26, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 10, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, -1, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 3, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 22, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x00b6, 26, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x01d2, 10, ZC_COMBODELAY(sock));
		ADD_PKT(0x00ec, 18, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 8, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, -1, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 4, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x00f6, 26, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x00d8, -1, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, -1, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x00c0, 54, ZC_EMOTION(sock));
		ADD_PKT(0x00db, -1, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00f0, 26, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x0201, -1, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 6, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, 6, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 7, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 30, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x016f, -1, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0235, -1, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, -1, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 6, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, -1, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 10, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x009e, -1, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x0238, 22, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 11, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 30, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x010a, 8, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 23, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 6, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x02e1, 6, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x0121, 3, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x019b, 8, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0106, 2, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, -1, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, -1, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 11, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 17, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, -1, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x01d9, 28, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, -1, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x0087, 8, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, -1, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x019a, 17, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0078, -1, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 39, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 30, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x007c, 2, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, -1, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0080, -1, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0091, 3, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x00b0, 8, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 5, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x01a6, 58, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x0166, -1, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 37, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 186, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, -1, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x00da, 21, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 11, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0171, 6, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 2, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 12, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, 7, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 5, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, 90, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x0167, 26, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x00b4, -1, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00d1, 16, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 8, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x010f, 81, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x01c9, 6, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, -1, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, -1, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, -1, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, 5, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 114, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 6, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 30, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, -1, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 14, ZC_STATUS(sock));
		ADD_PKT(0x00bc, 6, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x00a6, 20, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, 6, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, 10, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 60, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 102, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, -1, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 11, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x016c, -1, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x013e, 182, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 7, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 6, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, -1, ZC_WARPLIST(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081217 */
