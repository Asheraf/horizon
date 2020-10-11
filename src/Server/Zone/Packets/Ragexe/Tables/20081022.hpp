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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081022
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081022

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
		ADD_PKT(0x00e6, -1, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, 27, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 5, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 27, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 2, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0099, 26, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, -1, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, -1, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 2, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 15, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 22, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x01ed, -1, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 4, CZ_COMMAND_MER(sock));
		ADD_PKT(0x00d5, 26, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x00ce, -1, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 15, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, -1, CZ_DORIDORI(sock));
		ADD_PKT(0x0436, 13, CZ_ENTER2(sock));
		ADD_PKT(0x00ef, 11, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, 22, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f3, -1, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x0362, 6, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x019c, 2, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 3, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 6, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0126, 4, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0129, -1, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0128, 7, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 6, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, 8, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 6, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, -1, CZ_RECALL(sock));
		ADD_PKT(0x0161, 3, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 16, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018e, -1, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, 10, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, 53, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0437, 6, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, -1, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 9, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x0232, 102, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0360, 26, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 19, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x012a, -1, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x012e, 33, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00e4, 10, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 3, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 2, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, -1, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014d, 65, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 8, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, -1, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0100, 14, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 3, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, -1, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 26, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x01b2, 30, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00ab, 60, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00a9, 8, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00b2, 10, CZ_RESTART(sock));
		ADD_PKT(0x011b, -1, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 5, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 6, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 6, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, -1, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, -1, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x0439, -1, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0438, 30, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0367, 10, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, -1, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 12, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 282, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, -1, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 6, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00d6, 8, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, -1, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, 14, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, -1, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x015a, 8, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 8, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 2, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, -1, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x00fd, 27, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, 30, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x00e9, -1, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 10, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 6, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x00f4, 2, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x021a, 9, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 67, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0163, 54, ZC_BAN_LIST(sock));
		ADD_PKT(0x009a, 2, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 26, ZC_BROADCAST2(sock));
		ADD_PKT(0x0122, 6, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, -1, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0230, 8, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x00df, 4, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x00b6, 8, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, -1, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 29, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 4, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, -1, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 3, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x020a, 7, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, -1, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x01cf, 6, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, -1, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 21, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 36, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 6, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x013c, 30, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, -1, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0201, 6, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0101, -1, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 60, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 10, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 31, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x0162, -1, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 3, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x02f5, -1, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x00a1, -1, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009e, 6, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x029a, 6, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 16, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x01ad, -1, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x00dc, 5, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, -1, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 11, ZC_MVP(sock));
		ADD_PKT(0x010a, -1, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, -1, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 2, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x01ee, 23, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, -1, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 90, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 53, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, 5, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, -1, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, 43, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x0117, 14, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0075, -1, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, -1, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 6, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 30, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 28, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x022b, -1, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 30, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 44, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 14, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, -1, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x01de, 2, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, -1, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x022a, 282, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x007c, -1, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 7, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 10, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 4, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 29, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, -1, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x01b0, -1, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x0142, 10, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x00b0, -1, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 6, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 42, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 6, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00c7, 2, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 3, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x0160, 8, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 3, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 79, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x00da, 28, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 6, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0171, 8, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00fe, 2, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 7, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, -1, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 2, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, -1, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 4, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, -1, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 81, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, -1, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x01b3, 10, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010e, -1, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x011f, -1, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01ac, -1, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01e1, 39, ZC_SPIRITS2(sock));
		ADD_PKT(0x01d7, 55, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 67, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, -1, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 2, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 4, ZC_STATUS(sock));
		ADD_PKT(0x00be, 28, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 4, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 11, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 5, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 6, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 16, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, -1, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 5, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x016d, 30, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 59, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x00c2, -1, ZC_USER_COUNT(sock));
		ADD_PKT(0x00a8, 3, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, 26, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 6, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, -1, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 6, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081022 */
