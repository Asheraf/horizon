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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080715
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080715

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
		ADD_PKT(0x0208, 12, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, -1, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x0218, 8, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, -1, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 54, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 2, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 10, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 26, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0102, 4, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x01ed, 15, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, 5, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, -1, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, 3, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00d5, -1, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, -1, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x01e7, -1, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 35, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 22, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 6, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, 11, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f3, 30, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 6, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, 66, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x016b, 26, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, -1, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 14, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 11, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, -1, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 6, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 6, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0127, -1, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0128, 3, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, 11, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 10, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 14, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 28, CZ_RECALL(sock));
		ADD_PKT(0x01bd, -1, CZ_RECALL_GID(sock));
		ADD_PKT(0x011d, 8, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 26, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 6, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, 3, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, 29, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0233, 9, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 6, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, 9, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, 28, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, 26, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 2, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, -1, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, -1, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, 5, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, 4, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, 4, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, -1, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, -1, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 6, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x014f, 6, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 8, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, -1, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0178, 55, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, -1, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x0168, 11, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, -1, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 65, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x00e0, -1, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, 14, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, -1, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, 44, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 23, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 6, CZ_RESTART(sock));
		ADD_PKT(0x01a7, 4, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, -1, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00d0, 6, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 20, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, 3, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x019f, 6, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0073, -1, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, -1, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, -1, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 8, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 7, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, -1, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, 10, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 11, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, -1, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 29, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x015a, 6, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, -1, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, -1, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x018f, 4, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 3, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0194, -1, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 8, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0169, 5, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, 34, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, 54, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, -1, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x0209, 8, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 5, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, -1, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, -1, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x01e9, -1, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 10, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, 10, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, -1, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 6, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 5, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 29, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 6, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 7, ZC_BROADCAST(sock));
		ADD_PKT(0x00ee, 31, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, 10, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, -1, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 11, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 3, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 6, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 20, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 10, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x00b6, 60, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00ec, 10, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0141, 26, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, -1, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 30, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, -1, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x0105, 97, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 57, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, -1, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 2, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 68, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 4, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 7, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 3, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 6, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 10, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 6, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, -1, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 282, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x00fb, 26, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 53, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, -1, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, -1, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0235, 9, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, -1, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 2, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, -1, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x0177, -1, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 21, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 2, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x00a0, -1, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 102, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 6, ZC_KILLER_RANK(sock));
		ADD_PKT(0x018d, -1, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, -1, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 30, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 67, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 4, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 59, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x010c, 10, ZC_MVP(sock));
		ADD_PKT(0x010a, 3, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 6, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, -1, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 42, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, -1, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 3, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x008d, 4, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x019b, 14, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0075, 8, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 6, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x01d6, 6, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, -1, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, -1, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 3, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 58, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x02ed, -1, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 6, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 4, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x01eb, 16, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 30, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 10, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 2, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, -1, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 10, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x02ee, -1, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007f, 22, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0093, -1, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 16, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, -1, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 30, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x0142, 7, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x00b0, 86, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 282, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 6, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, 26, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00ca, -1, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, -1, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 18, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, -1, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, -1, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 14, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 14, ZC_POSITION_INFO(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x0207, -1, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x01f4, 4, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x016a, 4, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, -1, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 2, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x0148, 10, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 21, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00b4, 15, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x01b3, -1, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 24, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, -1, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 26, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, -1, ZC_SPIRITS(sock));
		ADD_PKT(0x00c3, -1, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, -1, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 2, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 2, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, -1, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, -1, ZC_STATUS(sock));
		ADD_PKT(0x00be, 30, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, 28, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 8, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 2, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, -1, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 2, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 90, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x013e, 6, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, -1, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 10, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080715 */
