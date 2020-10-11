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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090218
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090218

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
		ADD_PKT(0x0208, 30, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 2, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x0202, -1, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 9, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 55, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, -1, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 8, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 3, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 4, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 4, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 22, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x0102, 7, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x0146, 3, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 67, CZ_COMMAND_MER(sock));
		ADD_PKT(0x00eb, 10, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 2, CZ_CONTACTNPC(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x01e7, -1, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 16, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, -1, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 6, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 30, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, -1, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 4, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, 11, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x00ff, 6, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, 4, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x00f9, 8, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 10, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0126, -1, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 6, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 44, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, -1, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 14, CZ_RECALL(sock));
		ADD_PKT(0x0161, 2, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x01ba, -1, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 8, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0437, -1, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, 10, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x035f, 2, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0234, 7, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x015b, 4, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x018a, 2, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00d9, 7, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, -1, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, -1, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 3, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 10, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014d, -1, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 3, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x01fd, 26, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x0100, 81, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, -1, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 4, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x01b2, 58, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, -1, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00c1, 54, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00d3, 2, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, -1, CZ_RESTART(sock));
		ADD_PKT(0x01a7, 10, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x00d0, 2, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 6, CZ_SHIFT(sock));
		ADD_PKT(0x0225, 2, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, -1, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0439, -1, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, 39, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 2, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 3, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, -1, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, 6, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 26, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, 9, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, -1, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x00fa, -1, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, 60, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x0095, 60, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 3, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 8, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x00fd, -1, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, 29, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, 26, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, -1, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 5, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x00f4, 14, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x0104, -1, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x0111, -1, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x013a, 8, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0163, 27, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 15, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, -1, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 10, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x0123, 22, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, -1, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, -1, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 8, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 27, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x00b6, -1, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, -1, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 3, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, -1, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, -1, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 66, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 3, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 2, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 28, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 30, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x00d8, -1, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x0132, -1, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x00db, 8, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x0295, 4, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 28, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x022f, 12, ZC_FEED_MER(sock));
		ADD_PKT(0x0201, 5, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 7, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 17, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, 20, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 8, ZC_GROUP_LIST(sock));
		ADD_PKT(0x01b6, 27, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x0162, 4, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 79, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, -1, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 8, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 11, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 30, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 6, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 4, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 68, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, -1, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 6, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 6, ZC_KILLER_RANK(sock));
		ADD_PKT(0x018d, -1, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, 90, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 8, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, -1, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 30, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x010c, -1, ZC_MVP(sock));
		ADD_PKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, -1, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 2, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 6, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, 31, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x0109, 8, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x0075, 2, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x0086, 7, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, -1, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x02ec, -1, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 2, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 12, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x0087, 21, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 4, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 33, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, -1, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x01de, 11, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x022a, 6, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x007c, 10, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 3, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0093, 14, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0092, -1, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x0287, -1, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, 8, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 26, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 22, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, -1, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 23, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 182, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 86, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 2, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 6, ZC_POSITION_INFO(sock));
		ADD_PKT(0x01a2, 7, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x0446, 14, ZC_QUEST_NOTIFY_EFFECT(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x0207, 9, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 4, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 37, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00aa, 5, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x0167, -1, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, -1, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 26, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, -1, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x01b3, -1, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, 6, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, -1, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, -1, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, -1, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 282, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 13, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 30, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, -1, ZC_SPIRITS2(sock));
		ADD_PKT(0x01d7, 59, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 10, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 97, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x00bd, 2, ZC_STATUS(sock));
		ADD_PKT(0x00be, -1, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, -1, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 4, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, -1, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 6, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 19, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, -1, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x016d, 4, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 18, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 11, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, 14, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, -1, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, -1, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, 3, ZC_USE_SKILL(sock));
		ADD_PKT(0x011c, 14, ZC_WARPLIST(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090218 */
