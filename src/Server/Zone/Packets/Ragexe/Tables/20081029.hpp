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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081029
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081029

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
		ADD_PKT(0x0208, -1, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 8, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 39, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, -1, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0099, 6, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 30, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 4, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 67, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, -1, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, -1, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, 44, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x022d, -1, CZ_COMMAND_MER(sock));
		ADD_PKT(0x00eb, 3, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 8, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 2, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x00ce, 282, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 10, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 26, CZ_DORIDORI(sock));
		ADD_PKT(0x0436, -1, CZ_ENTER2(sock));
		ADD_PKT(0x00ef, -1, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 6, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x016e, 10, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, -1, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, 11, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x0362, -1, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x01e8, 59, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 18, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, -1, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 29, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0129, 2, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, 9, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 2, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, -1, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, 6, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 15, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 26, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 14, CZ_RECALL(sock));
		ADD_PKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 8, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x0368, 8, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, -1, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0437, -1, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, 16, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, -1, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, 6, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, -1, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, 6, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 28, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, -1, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 27, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 5, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x0155, 4, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, -1, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x00bf, 16, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00e4, 26, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 10, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 3, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014d, 6, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 6, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x01fd, 8, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x0100, -1, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, 7, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 2, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x01b2, -1, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00ab, 30, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00a9, -1, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00b2, 42, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 10, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x011b, 4, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, -1, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, -1, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 90, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, 30, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x019f, 20, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0438, 12, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0366, 6, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0367, 6, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, 6, CZ_WHISPER(sock));
		ADD_PKT(0x0073, -1, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 33, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 5, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 27, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 11, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x017d, 9, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0188, 10, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, 5, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, 30, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x00fa, 65, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, 30, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, 14, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 6, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x018b, 5, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 10, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 8, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0098, -1, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x0209, 4, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 15, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, -1, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x0104, 11, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, 28, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 97, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, 6, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, 10, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, -1, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 5, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x01cd, 26, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 6, ZC_BAN_LIST(sock));
		ADD_PKT(0x009a, 19, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 3, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, -1, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 2, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 26, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 18, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, -1, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 22, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, -1, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 6, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 7, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x01d2, 4, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 6, ZC_COMPASS(sock));
		ADD_PKT(0x01ea, 2, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x020a, -1, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x00f6, 57, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x00d8, 6, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, -1, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 8, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, -1, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, -1, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 14, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x0295, 5, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x022f, 10, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 58, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, 22, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0101, 6, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, -1, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, -1, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 2, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 7, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0235, 282, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x02f5, 6, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, -1, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x009e, -1, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x029a, 20, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x00dc, -1, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 10, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 33, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x010c, 2, ZC_MVP(sock));
		ADD_PKT(0x010b, 2, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 26, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 30, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 10, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 5, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 26, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, 6, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x0109, 3, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x0117, 13, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 3, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0199, 8, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x0086, 6, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x01da, 6, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 8, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 68, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, -1, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 23, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x02ed, -1, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 12, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, -1, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, -1, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x019a, 11, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x022a, 4, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 60, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, -1, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 2, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 6, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 9, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0093, -1, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0092, 29, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x0142, 8, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 60, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x0133, 102, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 2, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 4, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, -1, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 30, ZC_PET_ACT(sock));
		ADD_PKT(0x0160, -1, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 60, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, -1, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 53, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 8, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, -1, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0171, -1, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 3, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00fe, -1, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 19, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, 2, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00b3, -1, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0148, -1, ZC_RESURRECTION(sock));
		ADD_PKT(0x00b4, -1, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, 67, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x01b3, 36, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010e, 10, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x01c9, 14, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01d0, 21, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 86, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, 2, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, -1, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0229, 6, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, -1, ZC_STATUS(sock));
		ADD_PKT(0x00be, -1, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, -1, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, -1, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 3, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0224, 10, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, -1, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 4, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 6, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x00a8, -1, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, 35, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 26, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x0097, 3, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081029 */
