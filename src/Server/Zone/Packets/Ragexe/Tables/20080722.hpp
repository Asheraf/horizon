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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080722
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080722

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
		ADD_PKT(0x0208, 2, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 30, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x0202, 2, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 33, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 14, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, -1, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 5, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, -1, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 18, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 57, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 81, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x0102, -1, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x01ed, -1, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 4, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, 14, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00d5, 10, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, 282, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 8, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x01e7, 21, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, -1, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, -1, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 26, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x0143, 6, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x02f3, 2, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, -1, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, -1, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x00ff, 14, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, -1, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 6, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 59, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, -1, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, -1, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0127, 2, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0128, 27, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, 20, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 29, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, -1, CZ_RECALL(sock));
		ADD_PKT(0x0161, 39, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 9, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 42, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 30, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, -1, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, -1, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0233, -1, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 12, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, 282, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, 2, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, 58, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 4, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 17, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x0130, 55, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012e, -1, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, -1, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 26, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x0103, 2, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 6, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x014f, -1, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, -1, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017a, 22, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, 8, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, 7, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 3, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 2, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x00b9, 22, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x00ab, 8, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00a9, -1, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 7, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 3, CZ_RESTART(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 6, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 7, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, -1, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 10, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, -1, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 6, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, -1, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 27, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x015e, -1, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, 2, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, -1, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, 97, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 2, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x015a, -1, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x011e, 12, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 182, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 15, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, -1, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, 19, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 65, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 4, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 5, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 11, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 6, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 34, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, 30, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x0111, -1, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, 4, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x0139, 26, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 43, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, -1, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x0163, 71, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 22, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, -1, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, -1, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 26, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 8, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0123, -1, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, -1, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, -1, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 16, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, -1, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x00b6, 6, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 10, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 28, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 3, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 30, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 2, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 10, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 6, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 6, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 4, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 2, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, -1, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, -1, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 7, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 5, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x00c0, 6, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 23, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 21, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 11, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 15, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, -1, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x00fb, 4, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 282, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x0235, -1, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 6, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, -1, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x0177, 3, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, -1, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, -1, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x00af, 28, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 30, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 6, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, -1, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 5, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x010c, 6, ZC_MVP(sock));
		ADD_PKT(0x010a, -1, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 4, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 35, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, -1, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x008a, 10, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 102, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x0121, 2, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, -1, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x019b, 8, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 6, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 29, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, -1, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 7, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x01d6, -1, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 3, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 2, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 8, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 2, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 29, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 10, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x008e, 54, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 90, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 282, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, -1, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, -1, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, -1, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x01d8, -1, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 66, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 2, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 3, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, -1, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 13, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 53, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, 3, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 8, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x00b0, -1, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, -1, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, 11, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, 5, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 6, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x0166, 2, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, -1, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 4, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 30, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 6, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 3, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x0207, 6, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00fe, 28, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, -1, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x00ac, 44, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, -1, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, -1, ZC_RESTART_ACK(sock));
		ADD_PKT(0x023c, 3, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 54, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 10, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 30, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, 7, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d2, 30, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x010e, -1, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x01c9, 6, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, -1, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d7, 6, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x00be, 17, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 10, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 26, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 26, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a5, 6, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, 4, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 11, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, -1, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 10, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x01f2, 9, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 18, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x013e, -1, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x01c8, -1, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x00b5, 11, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 7, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 23, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080722 */
