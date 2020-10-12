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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081203
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081203

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
		ADD_PKT(0x00c5, 16, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 8, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, -1, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, -1, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 5, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x00ed, 28, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 4, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, -1, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 8, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, -1, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 6, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, -1, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 44, CZ_COMMAND_MER(sock));
		ADD_PKT(0x0090, 6, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 6, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x00cc, 4, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x0436, 2, CZ_ENTER2(sock));
		ADD_PKT(0x00e3, 11, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 3, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x01d5, 26, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f3, -1, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 2, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, 11, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, 34, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 3, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 7, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x01e8, -1, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0126, 8, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 4, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, -1, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, -1, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 10, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, -1, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x0134, 6, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x01bc, 9, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 6, CZ_RECALL_GID(sock));
		ADD_PKT(0x011d, 16, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, -1, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 71, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0233, 32, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0232, 58, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0360, 2, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x015b, 60, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x0155, 8, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, 10, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x00bf, 8, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00e4, 16, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 30, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x014f, 6, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 27, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017a, -1, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x01fd, -1, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x0168, -1, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0159, 3, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, -1, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 55, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, 26, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, -1, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, -1, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, 4, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00a9, -1, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 10, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 2, CZ_RESTART(sock));
		ADD_PKT(0x01ce, -1, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 3, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 30, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x01bb, 30, CZ_SHIFT(sock));
		ADD_PKT(0x0225, -1, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, -1, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, 8, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0438, 65, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0073, 10, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, -1, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 5, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 14, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 8, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, -1, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, 30, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, -1, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, -1, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x015a, 60, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x018f, 3, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 6, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 23, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, -1, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, -1, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, -1, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 6, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x00e9, 11, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0124, 26, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x00f4, -1, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01e9, 10, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 6, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021a, 13, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, -1, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x01cd, 114, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 14, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 26, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 4, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 6, ZC_BROADCAST2(sock));
		ADD_PKT(0x0122, 2, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, -1, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 22, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x0230, 2, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 6, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, -1, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, -1, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 79, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, -1, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x0144, 6, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, -1, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 6, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0137, 2, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x00f6, -1, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x00d8, 3, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 54, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, -1, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, -1, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 5, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 6, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 5, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 9, ZC_FEED_MER(sock));
		ADD_PKT(0x0201, 8, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, -1, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 68, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, -1, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 54, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, -1, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 2, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0235, 5, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 86, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f4, 15, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x009e, 10, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x029a, 7, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x0238, 9, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 14, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, -1, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, -1, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 4, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, -1, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 4, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x010c, 6, ZC_MVP(sock));
		ADD_PKT(0x010b, 14, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x01ee, 39, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x019b, 28, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, -1, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 7, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 7, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 5, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 30, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 3, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 36, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 20, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 28, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 54, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, -1, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x01d9, 14, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x008e, 4, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0107, 24, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x0114, -1, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x0078, 26, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 5, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x02ee, -1, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, 6, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0077, -1, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 3, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0093, -1, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 27, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x01b0, -1, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x0142, -1, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, -1, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x0136, 6, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x01a6, 26, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, -1, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 8, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 11, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 3, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 2, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x01fc, 15, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x00e5, 8, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 2, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, 37, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, -1, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, 97, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 30, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, -1, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 7, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, 30, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00b4, 81, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 8, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 6, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, -1, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, 10, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 6, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x011f, -1, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 10, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 282, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 10, ZC_SPIRITS2(sock));
		ADD_PKT(0x01d7, 6, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 7, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 18, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 3, ZC_STATUS(sock));
		ADD_PKT(0x00bc, 2, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0131, -1, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 23, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, 102, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 7, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 42, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x00c2, -1, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, 186, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 43, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, 19, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 2, ZC_WARPLIST(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081203 */