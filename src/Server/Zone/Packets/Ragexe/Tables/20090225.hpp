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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090225
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090225

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
		ADD_PKT(0x0208, 6, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00e8, 7, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0218, -1, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, -1, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 8, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, -1, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 5, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 10, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 11, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, 2, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 11, CZ_COMMAND_MER(sock));
		ADD_PKT(0x00eb, 6, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x0203, 11, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x01e7, 7, CZ_DORIDORI(sock));
		ADD_PKT(0x0436, 4, CZ_ENTER2(sock));
		ADD_PKT(0x00ef, 2, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 7, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 30, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 186, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x02f6, 19, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x013f, -1, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, 3, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, 13, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x016b, -1, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, -1, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0126, 10, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 30, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 4, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0134, 4, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x01bc, -1, CZ_RECALL(sock));
		ADD_PKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 10, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018e, 5, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0369, 2, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0437, 16, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, 60, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x035f, 26, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, 8, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, -1, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 8, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x015b, -1, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 8, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 7, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x012e, 2, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, 6, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, 4, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 58, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, -1, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, 7, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x017c, -1, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0178, 68, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, 29, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x0100, 6, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x01ae, 6, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, 6, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, -1, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00c1, -1, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00d3, 10, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 6, CZ_RESTART(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 30, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 79, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, -1, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x0225, -1, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 5, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0438, 3, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0096, -1, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 282, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 8, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x00ea, 12, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, -1, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 4, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, 21, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x01f5, -1, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, 31, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 6, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 10, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x015a, 6, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, 8, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, 3, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, 3, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x0095, 33, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 8, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, -1, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 21, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0169, 26, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, -1, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 3, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, -1, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 2, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x00f4, 2, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 7, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, 26, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x021c, 9, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 6, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 28, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 2, ZC_BROADCAST(sock));
		ADD_PKT(0x00ee, 4, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0123, -1, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 2, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 30, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, -1, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 2, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 65, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 6, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 3, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 26, ZC_COMBODELAY(sock));
		ADD_PKT(0x00ec, 5, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 17, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, -1, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 10, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 7, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 2, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x00d8, 97, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, -1, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 39, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 2, ZC_DISPEL(sock));
		ADD_PKT(0x00db, 10, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 31, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, 8, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x0201, -1, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 14, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 86, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, -1, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, -1, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 3, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 18, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 10, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, -1, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 22, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x02f5, 6, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, -1, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, -1, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, -1, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, -1, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 6, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 30, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x01ad, -1, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 17, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, -1, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 26, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 2, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 4, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x014c, 57, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x02e1, 3, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, -1, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, 10, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 34, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 6, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0075, -1, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0086, -1, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x02ec, 2, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 20, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x022b, -1, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 29, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x0087, 6, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, -1, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, -1, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x01de, 59, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x022a, -1, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x007c, 19, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 8, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0077, 7, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 36, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0093, -1, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x012d, 22, ZC_OPENSTORE(sock));
		ADD_PKT(0x01ab, 10, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 2, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, 14, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, 8, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 30, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, -1, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 3, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, -1, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, -1, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 4, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, -1, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 26, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, -1, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 6, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 6, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 4, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 7, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, -1, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 37, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x023a, 8, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 14, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 2, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x0148, 10, ZC_RESURRECTION(sock));
		ADD_PKT(0x00d7, -1, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 30, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00d2, 2, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x0120, 15, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 6, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 6, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, -1, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, -1, ZC_SPIRITS(sock));
		ADD_PKT(0x01d7, 5, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, -1, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x00bd, -1, ZC_STATUS(sock));
		ADD_PKT(0x00bc, 27, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, -1, ZC_STOPMOVE(sock));
		ADD_PKT(0x00a6, 10, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x00a5, 12, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, -1, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, -1, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, 9, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, 6, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x01c8, 53, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, 9, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 32, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 26, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 4, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090225 */
