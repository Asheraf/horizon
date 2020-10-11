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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090204
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090204

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
		ADD_PKT(0x00e8, 58, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, -1, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 6, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, -1, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 24, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 2, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 6, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00de, 32, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 86, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x0102, 8, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x0146, 6, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 8, CZ_COMMAND_MER(sock));
		ADD_PKT(0x00eb, -1, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 44, CZ_CONTACTNPC(sock));
		ADD_PKT(0x0203, 67, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, -1, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, -1, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x00ef, 43, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, 26, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x02f3, 27, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 53, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, 26, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, 30, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, -1, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, -1, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 19, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 8, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 39, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, -1, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, -1, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 14, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 8, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, 6, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, 54, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 22, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bd, 65, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 32, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 6, CZ_REMOVE_AID(sock));
		ADD_PKT(0x0368, -1, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, 3, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0437, 6, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, 6, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0234, 16, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 6, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 2, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 6, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 7, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 34, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 26, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x018a, 10, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, 28, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 3, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, -1, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 28, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x014f, 10, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 13, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, -1, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 29, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0168, -1, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 5, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0165, -1, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 6, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, -1, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, -1, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, 33, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, -1, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, -1, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00d3, -1, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x01ce, 11, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 4, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 2, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x01bb, 12, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, 4, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 10, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x0112, 6, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0438, -1, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0367, 6, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, 2, CZ_WHISPER(sock));
		ADD_PKT(0x0083, 6, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 13, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00d6, 8, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x01f5, 54, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, 11, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, -1, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x015a, 14, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x011e, 22, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x00fd, -1, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 6, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x013b, 5, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 33, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, -1, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c4, -1, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x01e9, 79, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x021c, 2, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x0139, 21, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 4, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 114, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, 26, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, -1, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, -1, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x00ee, -1, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 59, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x01ef, 18, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 15, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 3, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, -1, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x00b6, -1, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, -1, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x00ec, -1, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 3, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 6, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 68, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x0125, 20, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x0105, -1, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 42, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x0132, 7, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 26, ZC_DISPEL(sock));
		ADD_PKT(0x013c, 7, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 31, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01a3, 6, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, 3, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, 6, ZC_GROUP_LIST(sock));
		ADD_PKT(0x01b6, 2, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, -1, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0235, 21, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 10, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f4, 6, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 8, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, -1, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x009d, 3, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, -1, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 2, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 14, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, -1, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 18, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, 27, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 10, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 3, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, -1, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, -1, ZC_MVP(sock));
		ADD_PKT(0x010a, -1, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 14, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, -1, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x008a, 2, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 30, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x0121, 6, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 11, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0106, 9, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0189, -1, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 6, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 2, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x007b, 5, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 5, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 4, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x01d9, 22, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x02ed, 23, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, -1, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, -1, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, -1, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, -1, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 17, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x022a, 4, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 20, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, 5, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 10, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 7, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 3, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0092, -1, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x012d, -1, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 6, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, -1, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x01ab, 57, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, -1, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00ca, 6, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 282, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x01a6, -1, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x0166, 4, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 8, ZC_POSITION_INFO(sock));
		ADD_PKT(0x013d, -1, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 30, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 30, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00fe, 29, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 3, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, -1, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00aa, 4, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, -1, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 6, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x0148, 30, ZC_RESURRECTION(sock));
		ADD_PKT(0x00d7, 23, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 7, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x010e, -1, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 10, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x01c9, 14, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01d0, 36, ZC_SPIRITS(sock));
		ADD_PKT(0x01d7, -1, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 6, ZC_STARSKILL(sock));
		ADD_PKT(0x00bd, 60, ZC_STATUS(sock));
		ADD_PKT(0x00bc, 15, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, -1, ZC_STOPMOVE(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 2, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x01f2, 5, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x00c2, -1, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, 10, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, -1, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, 10, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 2, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x0097, 4, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090204 */
