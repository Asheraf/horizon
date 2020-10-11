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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090401
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090401

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
		ADD_PKT(0x0208, -1, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0202, 4, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0217, 102, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 10, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 8, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 282, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, -1, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x01ed, -1, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 27, CZ_COMMAND_MER(sock));
		ADD_PKT(0x00eb, -1, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00d5, -1, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, 26, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, -1, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 7, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 8, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 8, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, -1, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x0143, 30, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 58, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 14, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, -1, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, -1, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 2, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 2, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x01e8, 6, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0126, 3, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 30, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, -1, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, 6, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0128, 3, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, -1, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 29, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 6, CZ_RECALL(sock));
		ADD_PKT(0x01bd, -1, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 10, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, -1, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018e, 7, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0437, -1, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, 10, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x035f, 11, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0234, 7, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, -1, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 36, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 6, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 7, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012e, 14, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x00d9, 3, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 6, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e2, 3, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, -1, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, 2, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 6, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x0178, -1, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, -1, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, -1, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 23, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 10, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, 2, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, -1, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, 9, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, 4, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, -1, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00c1, 67, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, -1, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 2, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 42, CZ_RESTART(sock));
		ADD_PKT(0x01ce, -1, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 27, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, -1, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 16, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 8, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x00bb, -1, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 66, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, -1, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, 3, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0439, 5, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0366, 8, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0367, 26, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, 6, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 6, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x012c, 6, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, -1, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 11, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, 26, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, 53, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 10, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fe, 28, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, 6, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, 15, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, -1, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, -1, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 4, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0098, -1, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x0209, -1, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x01c5, 32, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 18, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 81, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 3, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x00ee, 2, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0123, -1, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x00df, 33, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, -1, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00f8, 2, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, -1, ZC_COMBODELAY(sock));
		ADD_PKT(0x00ec, 60, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x020a, 31, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x00f6, 4, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 10, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 14, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x0132, 11, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, -1, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 10, ZC_EMOTION(sock));
		ADD_PKT(0x00db, -1, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x013c, 34, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 7, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 17, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, 58, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, -1, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 22, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, 7, ZC_GROUP_LIST(sock));
		ADD_PKT(0x01b6, 8, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, -1, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, 54, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0449, 4, ZC_HACKSH_ERROR_MSG(sock));
		ADD_PKT(0x0239, 12, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f4, -1, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 26, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 8, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 2, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, -1, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x029a, 9, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 54, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 6, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 3, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, -1, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, -1, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x00dd, -1, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 282, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 3, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 11, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x010c, 2, ZC_MVP(sock));
		ADD_PKT(0x010a, 6, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 6, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 6, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 4, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 15, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x019b, 4, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0106, 24, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, -1, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 2, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x007b, 8, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 6, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x022b, -1, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 28, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 39, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 16, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 2, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 20, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 28, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 18, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x01d8, 19, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 10, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 3, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, 14, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 2, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, -1, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 2, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, -1, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 26, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x012d, 43, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 10, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, -1, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, 10, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 4, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 10, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, -1, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 97, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 5, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, -1, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, -1, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, -1, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 17, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 2, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 21, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x0207, -1, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 67, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x01f4, -1, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, -1, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, -1, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, 15, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00b3, 4, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 53, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x00e1, 6, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 6, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00c4, 9, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d2, 30, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, -1, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x0120, -1, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 2, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, -1, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 23, ZC_SPIRITS(sock));
		ADD_PKT(0x00c3, 10, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, -1, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x0229, 33, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00be, 30, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 65, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0131, 37, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 59, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 4, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, 6, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, -1, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x00c2, 30, ZC_USER_COUNT(sock));
		ADD_PKT(0x00a8, -1, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, 6, ZC_USE_SKILL(sock));
		ADD_PKT(0x0097, 30, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090401 */
