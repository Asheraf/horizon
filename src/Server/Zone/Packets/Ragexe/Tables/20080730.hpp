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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080730
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080730

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
		ADD_PKT(0x0208, -1, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 4, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x0202, -1, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 4, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, -1, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 7, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 8, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 34, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 2, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x00b8, 14, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 2, CZ_CHOPOKGI(sock));
		ADD_PKT(0x022d, -1, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, 30, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 22, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 3, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, -1, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 2, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 6, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 26, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 6, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 6, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 2, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, -1, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x02f6, 4, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 10, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x0362, 7, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, 2, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, 15, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x0237, 2, CZ_KILLER_RANK(sock));
		ADD_PKT(0x00f9, 54, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, -1, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 6, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0127, -1, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0128, 31, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x00c9, 8, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 16, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 6, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 14, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, -1, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 2, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 23, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, 16, CZ_REQNAME2(sock));
		ADD_PKT(0x0108, -1, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, -1, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, -1, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, -1, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 21, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 6, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 15, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 2, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 11, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, 6, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, 14, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00d9, -1, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 4, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 36, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 27, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x017c, 102, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, -1, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, 2, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, -1, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 6, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, -1, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 6, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x01ae, 35, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, -1, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x00ab, -1, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, 186, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, 3, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 6, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 30, CZ_RESTART(sock));
		ADD_PKT(0x01a7, 6, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 79, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, -1, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 11, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x0225, -1, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x0096, 6, CZ_WHISPER(sock));
		ADD_PKT(0x00ea, 6, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, -1, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 2, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, 24, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, -1, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 27, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x015a, 6, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x011e, -1, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, 32, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 28, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, -1, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 182, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x0169, 10, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0098, -1, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, -1, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 6, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, -1, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 6, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, -1, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, -1, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, -1, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, 8, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 11, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, 39, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 7, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 14, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 10, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x0163, 114, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, -1, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, -1, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, 3, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 86, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x01ef, 10, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x01a4, 8, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 3, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x00b6, 2, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 30, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 21, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, -1, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, -1, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 33, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 30, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 17, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 3, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, -1, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 11, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x01cf, 5, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, -1, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, -1, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, -1, ZC_EMOTION(sock));
		ADD_PKT(0x00db, -1, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 6, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x013c, 12, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 6, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01a3, 28, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, 6, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x00fb, -1, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, -1, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 58, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 81, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, 44, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 9, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 3, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x017b, 8, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, -1, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x00b1, -1, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, -1, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, 10, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x00dc, 10, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x010c, -1, ZC_MVP(sock));
		ADD_PKT(0x010b, 33, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, -1, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 10, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, 5, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, -1, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, -1, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x008d, 31, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x019b, -1, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 30, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 17, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 26, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 10, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0086, -1, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 13, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 2, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, -1, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 13, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 4, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 29, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 7, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, -1, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 59, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x019a, 6, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 6, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 27, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x022a, 26, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 4, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, 29, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 10, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 14, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 5, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 10, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 7, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, -1, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, 26, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, -1, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x00b0, 3, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x0287, 5, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, 18, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, 11, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x01a6, 22, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x0166, -1, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 9, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, -1, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 60, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 26, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 10, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x0207, 60, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 58, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 8, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00fe, 282, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x00ac, 20, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 71, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x0167, 282, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 26, ZC_RESURRECTION(sock));
		ADD_PKT(0x00d7, -1, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00c4, 6, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 53, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 6, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x010f, 4, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 26, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 4, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x01c9, 26, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 2, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01e1, 4, ZC_SPIRITS2(sock));
		ADD_PKT(0x020e, 3, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, -1, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 12, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00be, -1, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 53, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 22, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, -1, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 22, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 4, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, -1, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x01a0, 5, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 20, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 3, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 7, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x013e, 32, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x01c8, 4, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x00b5, 282, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 39, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, -1, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080730 */
