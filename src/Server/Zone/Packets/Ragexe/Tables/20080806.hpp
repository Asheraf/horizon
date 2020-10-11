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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080806
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080806

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
		ADD_PKT(0x00e8, 10, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 26, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, -1, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0217, -1, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 3, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 65, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00de, 6, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 6, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, -1, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 27, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, 282, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x01a1, -1, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 6, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x0203, 2, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 15, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 33, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 3, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 28, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 10, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 30, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x01d5, 53, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 4, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 29, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, 2, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, 5, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, -1, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, 11, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 8, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 3, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 5, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x0140, 4, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 3, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0127, 18, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, 14, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, 79, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 97, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, 11, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x00c9, 3, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, -1, CZ_RECALL(sock));
		ADD_PKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x01ba, 6, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 58, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, -1, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, 30, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0233, 42, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0234, 4, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, -1, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 4, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x0130, 4, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 39, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 3, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, -1, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, -1, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, 8, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 8, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 6, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 60, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 10, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x014d, 9, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 12, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0178, -1, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x00fc, 9, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0100, -1, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 54, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, 4, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, -1, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, 2, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x00e0, 4, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00c1, -1, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, -1, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 3, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 7, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 13, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 29, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, -1, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00d0, 60, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x0225, 2, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x0096, 10, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 7, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 6, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 36, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 14, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00e7, 59, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, 10, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 28, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 4, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, 4, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, -1, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x011e, 4, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0194, 13, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x0169, 30, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x013b, 7, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 60, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01e9, 26, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 282, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021a, 3, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, -1, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 4, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 8, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, 11, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 26, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x009a, 6, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 11, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 12, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, 5, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 8, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 2, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 58, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x01a4, 67, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 6, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 44, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 6, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 2, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, -1, ZC_COMBODELAY(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 2, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 6, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x00f6, -1, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x01cf, -1, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x01b9, 14, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 3, ZC_EMOTION(sock));
		ADD_PKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, 54, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 2, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, -1, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 10, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, 3, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 8, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0101, 66, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x01b6, -1, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, -1, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, -1, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0239, 32, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 11, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 35, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 282, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x00a1, 4, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x00a0, 21, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, 9, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x0238, 71, ZC_KILLER_RANK(sock));
		ADD_PKT(0x018d, 6, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, -1, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 186, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 10, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, -1, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x018c, 30, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 26, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010a, 30, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, -1, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 6, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, -1, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, 10, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x007a, 39, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x008d, -1, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x019b, 81, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, -1, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 3, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 6, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 2, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 6, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 53, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, -1, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 2, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x02ec, 68, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x01d9, 27, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, -1, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 6, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0107, 23, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x019a, 8, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, -1, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x01d8, 34, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, -1, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 6, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, -1, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 11, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 7, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, -1, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, -1, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x012d, 8, ZC_OPENSTORE(sock));
		ADD_PKT(0x01d4, 2, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, 10, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x0287, -1, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, 6, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00ca, 2, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x00c7, 26, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, -1, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 6, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 11, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, -1, ZC_POSITION_INFO(sock));
		ADD_PKT(0x01a2, 6, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 3, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 6, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 30, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 6, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, -1, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 7, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, -1, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x023a, 28, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, -1, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x0167, 7, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x0148, 2, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 8, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 2, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 57, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, -1, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 2, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, -1, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 22, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 28, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 7, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 30, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 6, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 14, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, 6, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, -1, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 2, ZC_STARSKILL(sock));
		ADD_PKT(0x0229, 8, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00be, 3, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, -1, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, -1, ZC_STOPMOVE(sock));
		ADD_PKT(0x00a6, 6, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 86, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, 3, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x0224, 17, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 43, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, -1, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, -1, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, -1, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x013e, -1, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 7, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, -1, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, 14, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, -1, ZC_WARPLIST(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080806 */
