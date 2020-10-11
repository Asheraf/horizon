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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080701
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080701

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
		ADD_PKT(0x00e6, 6, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, 2, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00e8, -1, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0218, -1, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0217, 7, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, -1, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 67, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 5, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 27, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, -1, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x00b8, 20, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 14, CZ_CHOPOKGI(sock));
		ADD_PKT(0x022d, 10, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, 3, CZ_COMMAND_PET(sock));
		ADD_PKT(0x0090, 10, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 7, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, -1, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 33, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x00ef, -1, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 26, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 4, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x01d5, 3, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f3, -1, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 30, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, -1, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, 5, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x0237, 29, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 282, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 6, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, -1, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, -1, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 3, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 43, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 9, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, -1, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, 18, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 5, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, 2, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 39, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bd, 6, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x01ba, -1, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, -1, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0369, 26, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0232, 28, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0360, 10, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, -1, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 6, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x012e, -1, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, 6, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00e4, -1, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, -1, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x0149, 14, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014d, -1, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, -1, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 29, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x01fd, 13, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 22, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 6, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0159, 7, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, 54, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 7, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, -1, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x00e0, 9, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, -1, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, 6, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, 6, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, -1, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x01a7, 2, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x00bb, 60, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, -1, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 36, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, -1, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0096, 10, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 71, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00d6, 15, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, -1, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, 33, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 59, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fe, 30, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x0095, 6, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 26, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 42, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 66, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0169, 5, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0098, 8, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 4, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x0209, -1, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x0104, -1, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, -1, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 17, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021a, 6, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 26, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 282, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, 10, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x021b, -1, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x009a, 3, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 10, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 14, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, -1, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, -1, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 7, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x00df, 34, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 67, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 8, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, -1, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 2, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, -1, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 55, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 97, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0137, 9, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, -1, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 10, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 11, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x01cf, 3, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, -1, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 14, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, -1, ZC_EMOTION(sock));
		ADD_PKT(0x00db, -1, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 86, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 6, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 11, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 31, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, 9, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 2, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 2, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, 5, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, -1, ZC_GROUP_LIST(sock));
		ADD_PKT(0x01b6, 12, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 44, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, 81, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 6, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 30, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 8, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x017b, 2, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 2, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 6, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, -1, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, -1, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 30, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x00b1, 3, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 2, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x0154, 11, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 6, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 6, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 22, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 14, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 15, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 7, ZC_MVP(sock));
		ADD_PKT(0x010b, 3, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 26, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 28, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, 8, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x007a, 2, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, 8, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 2, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, 31, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x0106, 10, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 30, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0199, 7, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 30, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 2, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x01da, 32, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x0079, 4, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 39, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, -1, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, -1, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x019a, 58, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 10, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 20, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 6, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, -1, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x007c, 5, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 4, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0077, 2, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 4, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, -1, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, -1, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 8, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, -1, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 6, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, 8, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, 7, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 10, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, -1, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x0133, 11, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 54, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00c7, 182, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 4, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x0166, 4, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 5, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 30, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 2, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, -1, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, -1, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, -1, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 8, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, -1, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x016a, -1, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, 13, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 14, ZC_RESTART_ACK(sock));
		ADD_PKT(0x023c, 60, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x00d7, 10, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 26, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 16, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, -1, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, -1, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 11, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01d0, 3, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, -1, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, -1, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 14, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 10, ZC_STARSKILL(sock));
		ADD_PKT(0x0229, -1, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 60, ZC_STATUS(sock));
		ADD_PKT(0x00be, 6, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, -1, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 19, ZC_STOPMOVE(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 4, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x01a0, -1, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 3, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 12, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 7, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, -1, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, 26, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, -1, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, 11, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x0097, 282, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080701 */
