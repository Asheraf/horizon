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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080917
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080917

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
		ADD_PKT(0x00c5, 6, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 6, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0218, -1, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0217, 2, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 14, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 34, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00de, 6, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x019d, 23, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 182, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, 3, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 8, CZ_CHOPOKGI(sock));
		ADD_PKT(0x01a1, 4, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 6, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 26, CZ_CONTACTNPC(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, -1, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x01e7, -1, CZ_DORIDORI(sock));
		ADD_PKT(0x0436, 7, CZ_ENTER2(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x01d5, 18, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x013f, 7, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0363, 13, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, 102, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, 30, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, -1, CZ_KILLER_RANK(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 33, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 12, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, -1, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0365, 13, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x007d, -1, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 21, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x01bc, -1, CZ_RECALL(sock));
		ADD_PKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x018e, -1, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, 6, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, 15, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0437, 10, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0108, 14, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, 3, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0360, 5, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, -1, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 7, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 6, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 29, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 3, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x00bf, 8, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, -1, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x0149, -1, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, -1, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, -1, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 6, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, -1, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, -1, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, 27, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 2, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0100, 26, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 44, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x00b9, 60, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, 59, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, 58, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00c1, 8, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, 4, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 35, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, -1, CZ_RESTART(sock));
		ADD_PKT(0x01ce, -1, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 8, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 3, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 90, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, -1, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x0225, 10, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 28, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0439, -1, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0438, 2, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0073, -1, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x012c, 6, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 10, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, -1, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 27, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, 3, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 23, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x0179, 9, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 6, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, 97, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x0274, -1, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, 21, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x018f, 3, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 10, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x018b, 10, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 2, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 19, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x013b, 6, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, -1, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, -1, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, -1, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 282, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, -1, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 14, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, -1, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0219, 2, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 4, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 31, ZC_BROADCAST2(sock));
		ADD_PKT(0x0122, 30, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0123, 4, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 2, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 71, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x00b6, -1, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, -1, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 6, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 6, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 2, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 6, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 2, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x020a, -1, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x00f6, 2, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x01cf, 5, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 3, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, -1, ZC_DISPEL(sock));
		ADD_PKT(0x00db, -1, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 4, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 66, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 6, ZC_FEED_MER(sock));
		ADD_PKT(0x0206, 81, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, 60, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 11, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 2, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 43, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, 79, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0239, -1, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f4, 55, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 8, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x009d, -1, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x029a, 4, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, -1, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x00dd, 3, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, -1, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x018c, 33, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 10, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, -1, ZC_MVP(sock));
		ADD_PKT(0x010a, -1, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x014c, 14, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, -1, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x008a, -1, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 6, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, -1, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, -1, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 4, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, 6, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 16, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, -1, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 6, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0189, -1, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 11, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, -1, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x007b, 7, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 2, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 10, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, -1, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 29, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x02ed, 10, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 39, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0107, 2, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 2, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 12, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x01de, 86, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, -1, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, -1, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, -1, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x007c, 53, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, -1, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0077, 4, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 11, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0092, 2, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01d4, 28, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 114, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x00ca, 30, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 12, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 14, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 6, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 6, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 30, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 8, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 10, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x013d, 6, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, -1, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0171, 4, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 4, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x016a, -1, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, -1, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, -1, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x00e1, 6, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 10, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00c4, 5, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d2, 30, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 16, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x0120, 9, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 282, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, -1, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, -1, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, -1, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, -1, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x0119, 30, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x00bd, 10, ZC_STATUS(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x01f0, 65, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x01a0, -1, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 32, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, -1, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, 6, ZC_USER_COUNT(sock));
		ADD_PKT(0x00a8, 8, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, 15, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 282, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 60, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, -1, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080917 */
