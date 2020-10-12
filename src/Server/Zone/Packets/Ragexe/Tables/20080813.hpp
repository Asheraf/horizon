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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080813
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080813

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
		ADD_PKT(0x0208, 3, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00e8, 282, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 60, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 11, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, -1, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00de, 67, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 6, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 10, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, 4, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 11, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x00eb, -1, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 33, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 29, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 60, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, -1, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 7, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 53, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, -1, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 8, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 9, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, 26, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f3, 10, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 4, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, 3, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x016b, -1, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 54, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x0140, 30, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, -1, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0127, 17, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, -1, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, 30, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, -1, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 4, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 43, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 22, CZ_RECALL_GID(sock));
		ADD_PKT(0x011d, 11, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, -1, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, -1, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0369, -1, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0233, -1, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 10, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x0234, -1, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0170, -1, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, -1, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, -1, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, -1, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, -1, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, -1, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x014d, 10, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, -1, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 66, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x00fc, 6, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 6, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 2, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 4, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, -1, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x00b9, -1, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x00e0, 2, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00c1, 2, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00d3, -1, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, -1, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 7, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 2, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00d0, 55, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 79, CZ_SHIFT(sock));
		ADD_PKT(0x0225, -1, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x0367, 59, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, 30, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 6, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 39, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, -1, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x015c, -1, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 86, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, 19, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 4, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, -1, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 102, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, 20, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x00fa, 10, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, -1, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x0194, 7, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 30, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0169, 4, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, 24, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, 14, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, -1, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, -1, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0124, 8, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 23, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 10, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 4, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x01e9, 15, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 27, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021a, -1, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 10, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 6, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, -1, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, -1, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 6, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, -1, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 186, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, -1, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, -1, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 14, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 4, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, -1, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 6, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 22, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, -1, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, -1, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, -1, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, -1, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x0144, 68, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 28, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0141, 26, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, -1, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, -1, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 2, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 2, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 2, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x0132, 4, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, -1, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, -1, ZC_EMOTION(sock));
		ADD_PKT(0x0295, 6, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 23, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 2, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, -1, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, -1, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 2, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, 35, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x0235, -1, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 12, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, -1, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, -1, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 71, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 36, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009e, 5, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, -1, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 14, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 30, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 3, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 282, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00b7, 6, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 8, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 26, ZC_MVP(sock));
		ADD_PKT(0x010a, 3, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 58, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, -1, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 2, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 2, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 4, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, -1, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x019b, -1, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 4, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 6, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, -1, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 2, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 4, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 4, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x02ec, 28, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 6, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 7, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x02ed, -1, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x0107, 17, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 6, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 6, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x01de, 3, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x01d8, 3, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x02ee, -1, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007f, 26, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 31, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 3, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0092, 6, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 8, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, -1, ZC_OPENSTORE(sock));
		ADD_PKT(0x01d4, -1, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, -1, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x0287, 97, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, 67, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00ca, -1, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 14, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 5, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 282, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 14, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x022e, 18, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x013d, -1, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 26, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 16, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 11, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 2, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 6, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 53, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x016a, 6, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, -1, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 13, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 4, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 18, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, -1, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, 6, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 6, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 9, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 3, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00d1, 11, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, -1, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 6, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x0120, 60, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 58, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, -1, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 32, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 5, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, -1, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x020e, 6, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 14, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 3, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 90, ZC_STATUS(sock));
		ADD_PKT(0x00be, 65, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, 10, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, 26, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 8, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 6, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 2, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x016c, 14, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, 14, ZC_USER_COUNT(sock));
		ADD_PKT(0x00a8, 2, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 16, ZC_WAIT_CoreLog(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080813 */