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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090129
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090129

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
		ADD_PKT(0x00e6, 3, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00c5, -1, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 14, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 13, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0172, 6, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 10, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 282, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00de, 5, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0102, -1, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x00eb, 71, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x0203, 10, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 14, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 12, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, -1, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 30, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, -1, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 14, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 6, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x02f6, 2, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 8, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 6, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x00ff, 6, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, 8, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 6, CZ_KILLER_RANK(sock));
		ADD_PKT(0x00f9, 10, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 10, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 30, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, -1, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 7, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 30, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, 10, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0128, -1, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, 26, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 6, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x01bc, -1, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 10, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 54, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, -1, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 30, CZ_REMOVE_AID(sock));
		ADD_PKT(0x0368, 6, CZ_REQNAME2(sock));
		ADD_PKT(0x0437, -1, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, -1, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, -1, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, -1, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0234, -1, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 4, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 30, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x0130, 8, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 4, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x012e, -1, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00e4, 20, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, -1, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x014f, 26, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 2, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 4, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, -1, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0168, 27, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0165, 6, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x00b9, 31, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, 7, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00ab, 6, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, 8, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00d3, 2, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, -1, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 14, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 5, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, -1, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 10, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, 9, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 44, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, -1, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0439, -1, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0438, 39, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0367, 29, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, 3, CZ_WHISPER(sock));
		ADD_PKT(0x0083, -1, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 4, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, -1, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x0179, 33, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x015a, -1, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, -1, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x018b, -1, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 7, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 11, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, -1, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 32, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 32, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 86, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 28, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x00f4, -1, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 6, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x01e9, 6, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x0139, -1, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x0147, 4, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, 8, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 9, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 55, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 58, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, -1, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 24, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, 20, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, -1, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x01ef, -1, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, -1, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 27, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 2, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x00b6, 2, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 60, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, -1, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, -1, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 4, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 2, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x0125, 6, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, -1, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 14, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 15, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x0132, -1, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 3, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, -1, ZC_EMOTION(sock));
		ADD_PKT(0x013c, 3, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 26, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, -1, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 4, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, 3, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, -1, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x016f, 10, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0239, 66, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f4, -1, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 22, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x009e, 7, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x029a, 2, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 4, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 6, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 29, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, -1, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, 10, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 21, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, -1, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, -1, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 2, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 10, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 27, ZC_MVP(sock));
		ADD_PKT(0x010a, 22, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, -1, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 5, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, -1, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x02e1, -1, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x0121, -1, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x0109, 6, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 4, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, -1, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0189, 2, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 26, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 26, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, -1, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 14, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 2, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x0079, -1, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 37, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, -1, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, -1, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 6, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 8, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 23, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 23, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 4, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 182, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 3, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x01d8, -1, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, -1, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 13, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, -1, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 8, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 3, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 8, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0092, 2, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x012d, 79, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 30, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, 8, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 8, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, 57, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, 68, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x0135, 59, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 26, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x0160, -1, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, -1, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, -1, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 53, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 2, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x0207, 7, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00fe, 2, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 7, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, 10, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00aa, -1, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 2, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 11, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x00d7, -1, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 2, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00d1, -1, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x010e, 6, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x011f, -1, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 102, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01d0, 10, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, -1, ZC_SPIRITS2(sock));
		ADD_PKT(0x01d7, 16, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 2, ZC_STARSKILL(sock));
		ADD_PKT(0x0229, -1, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bc, 8, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 6, ZC_STOPMOVE(sock));
		ADD_PKT(0x00a6, 2, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 6, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, -1, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, 6, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 16, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, -1, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x00c2, 60, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, -1, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 54, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, 282, ZC_USE_SKILL(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090129 */
