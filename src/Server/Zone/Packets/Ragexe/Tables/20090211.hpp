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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090211
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090211

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
		ADD_PKT(0x00c5, 32, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, -1, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 27, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 66, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 11, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 26, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 6, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 22, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00de, -1, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x0102, 282, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, 33, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 2, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 31, CZ_COMMAND_MER(sock));
		ADD_PKT(0x00eb, 6, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 4, CZ_CONTACTNPC(sock));
		ADD_PKT(0x0203, 29, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x01e7, 8, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, -1, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 21, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x0143, -1, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x02f6, 5, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 10, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 14, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, -1, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, 30, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x0237, -1, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x0126, 2, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0127, -1, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, 30, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, -1, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x00c8, 9, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 3, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 30, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bd, -1, CZ_RECALL_GID(sock));
		ADD_PKT(0x011d, -1, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 10, CZ_REMOVE_AID(sock));
		ADD_PKT(0x0369, -1, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0437, 54, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0234, 6, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, -1, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, -1, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, -1, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, -1, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 12, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x018a, 71, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 5, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 10, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 54, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x014f, -1, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 30, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017a, -1, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0100, -1, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 5, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, 26, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x00e0, 11, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00c1, 30, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00b2, 2, CZ_RESTART(sock));
		ADD_PKT(0x01ce, -1, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x011b, -1, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, -1, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x01bb, 26, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, -1, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, -1, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 7, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, -1, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0439, 6, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0367, 15, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, -1, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 8, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, -1, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, -1, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 282, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00d6, 59, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, 2, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 6, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, 6, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 10, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 5, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x015a, -1, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x00fa, 114, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, -1, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x0095, 11, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0194, 3, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x00fd, 2, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 17, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x013b, 18, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 10, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0124, 4, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x00f4, 53, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x0104, 26, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, -1, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 6, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, 11, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x0139, -1, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, -1, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, -1, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 22, ZC_BAN_LIST(sock));
		ADD_PKT(0x0219, 6, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 4, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 2, ZC_BROADCAST2(sock));
		ADD_PKT(0x0297, -1, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x01ef, 4, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 10, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, -1, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 3, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x00b6, 2, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 65, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x0144, 4, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 15, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 14, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, -1, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x0125, 8, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00d8, 3, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 4, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 27, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, -1, ZC_DISPEL(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, -1, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 5, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, -1, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 20, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, 7, ZC_GROUP_LIST(sock));
		ADD_PKT(0x01b6, -1, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x0235, -1, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 3, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f4, 7, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 14, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x00a1, 30, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, -1, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 10, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, -1, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, 102, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 3, ZC_KILLER_RANK(sock));
		ADD_PKT(0x018d, 28, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, -1, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 4, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dc, 67, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 54, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x010c, 2, ZC_MVP(sock));
		ADD_PKT(0x010b, -1, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x01ee, 6, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 282, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, -1, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x0121, 12, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x019b, -1, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x01d6, -1, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x007b, 2, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 26, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x01d9, 11, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 16, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, -1, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x0087, 8, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x01eb, 6, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 33, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, -1, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x022a, 26, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, -1, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, -1, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 6, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0077, -1, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, -1, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0092, 6, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x0142, -1, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 7, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x0133, 10, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00ca, 21, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 44, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 57, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01aa, 79, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 6, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, -1, ZC_POSITION_INFO(sock));
		ADD_PKT(0x01a2, 4, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x00da, 19, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, -1, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, -1, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00e5, 6, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00fe, -1, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, -1, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x00ac, 6, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, -1, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x0167, 14, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, 4, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 22, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 23, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 10, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, -1, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, 6, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 4, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x01b3, 8, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010e, 86, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 8, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 3, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 6, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 68, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 8, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 10, ZC_SPIRITS2(sock));
		ADD_PKT(0x020e, 4, ZC_STARSKILL(sock));
		ADD_PKT(0x00bd, -1, ZC_STATUS(sock));
		ADD_PKT(0x00be, 6, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 81, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 37, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 7, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 6, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 36, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x01f0, 4, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 10, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 10, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01f2, -1, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 16, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x013e, 2, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 20, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, -1, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x0097, -1, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090211 */
