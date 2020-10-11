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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090325
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090325

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
		ADD_PKT(0x00e6, 86, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, 2, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, -1, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 3, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 3, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0118, 6, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 6, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 6, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 30, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x01ed, 5, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, 3, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 19, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, -1, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 10, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00d5, 12, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, 2, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 4, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 6, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, -1, CZ_DORIDORI(sock));
		ADD_PKT(0x0436, -1, CZ_ENTER2(sock));
		ADD_PKT(0x00ef, 30, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 7, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x02a7, 404, CZ_HACKSH_CPX_MSG(sock));
		ADD_PKT(0x02f6, 26, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x013f, 29, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0363, 6, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, 6, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, 2, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 43, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 4, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0126, 282, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 66, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0128, 7, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 10, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, 58, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 2, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 2, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, -1, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 30, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 2, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, -1, CZ_REMOVE_AID(sock));
		ADD_PKT(0x0437, 4, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, 4, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, -1, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, -1, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, -1, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0360, 6, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x015b, 8, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, -1, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 26, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 8, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0149, 6, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, 16, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, -1, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, -1, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, -1, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, 2, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, 10, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 22, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0159, 34, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x01ae, 18, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00ab, -1, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00a9, 8, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 6, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 32, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 26, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 3, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 3, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 282, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 37, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x0225, -1, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 4, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, 71, CZ_WHISPER(sock));
		ADD_PKT(0x0083, 6, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x00ea, 4, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 8, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00e7, 55, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, -1, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, -1, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fe, 44, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, 3, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x00fa, -1, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x018f, 2, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 4, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 7, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 28, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 30, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0169, 3, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0098, 26, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, -1, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, -1, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 4, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x01c4, 8, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, -1, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, -1, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, -1, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, 11, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, -1, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x013a, 2, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0163, 8, ZC_BAN_LIST(sock));
		ADD_PKT(0x00ee, 8, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0123, 10, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, -1, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x01a4, 6, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 6, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 79, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x01d2, 54, ZC_COMBODELAY(sock));
		ADD_PKT(0x00ec, -1, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 6, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, -1, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x0105, 2, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, -1, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01b9, 6, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, -1, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 9, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 10, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x022f, 39, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 8, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, 18, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x01b6, 6, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 67, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x02a6, 404, ZC_HACKSH_CPX_MSG(sock));
		ADD_PKT(0x0239, -1, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, -1, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 6, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 13, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, -1, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, -1, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009e, 8, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, -1, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 27, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 6, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, 24, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x00dd, 30, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x010a, 26, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 17, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 10, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x01ee, 4, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, -1, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, -1, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, -1, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 65, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, -1, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 22, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, -1, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 6, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 3, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, -1, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 3, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 11, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 2, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 15, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 3, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 15, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 14, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 14, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 6, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, -1, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01d8, -1, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 6, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 6, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, 182, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 32, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 2, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 4, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0091, 21, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 6, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, -1, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, 4, ZC_OPENSTORE(sock));
		ADD_PKT(0x01d4, 7, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 53, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 282, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x00c7, 53, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 23, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 14, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 4, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, -1, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 16, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 31, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x01fc, -1, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 7, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 10, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 6, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, 67, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 30, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x00ac, 7, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, -1, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x0167, 8, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x0148, -1, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 7, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 10, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, -1, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00d1, -1, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 5, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 3, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, -1, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 9, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x01c9, 28, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 28, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, -1, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, -1, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, -1, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 14, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x0119, -1, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 39, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00be, 6, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 6, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0131, -1, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 4, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x01f0, 60, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 4, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 2, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, -1, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 9, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, -1, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x00a8, 6, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, -1, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x011c, -1, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, -1, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090325 */
