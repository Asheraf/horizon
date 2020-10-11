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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090318
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090318

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
		ADD_PKT(0x0208, 31, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, -1, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x0218, 28, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 10, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x019d, 13, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 10, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x022d, 10, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, 30, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 15, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 26, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, -1, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 9, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 86, CZ_DORIDORI(sock));
		ADD_PKT(0x0436, 8, CZ_ENTER2(sock));
		ADD_PKT(0x00e3, 55, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 26, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x01d5, 2, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, -1, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, -1, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, -1, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x00ff, 4, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, -1, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x019c, 8, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 11, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x0140, -1, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 8, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 30, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, -1, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0365, -1, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 12, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 8, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 6, CZ_RECALL(sock));
		ADD_PKT(0x01bd, -1, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 7, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, -1, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 6, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, -1, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0369, -1, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0437, -1, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0108, 4, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, 67, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, 6, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, 6, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 4, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, -1, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x0130, 7, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 13, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x00bf, 18, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 4, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x0103, -1, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x0149, 22, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, 58, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 39, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 282, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 10, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, -1, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, -1, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x0159, 8, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x01b2, 6, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00ab, 14, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, -1, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, -1, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, -1, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, -1, CZ_RESTART(sock));
		ADD_PKT(0x01a7, 60, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 24, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 44, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 30, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 6, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, 7, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 2, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 53, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, -1, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0438, -1, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0367, 30, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, 11, CZ_WHISPER(sock));
		ADD_PKT(0x0083, 65, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x00ea, 6, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00d6, -1, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x017d, 28, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 3, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x015a, 2, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x00fa, 20, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, -1, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0195, 4, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 6, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x0169, 29, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, 10, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 4, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 2, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 6, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 8, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 10, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x01c4, 16, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, 8, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, 28, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 20, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021a, 23, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x013a, 10, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x01cd, -1, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 3, ZC_BAN_LIST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 282, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0123, 6, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 9, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x009c, -1, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00f8, -1, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, -1, ZC_COMBODELAY(sock));
		ADD_PKT(0x00ec, 27, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 2, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 11, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 16, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x0125, -1, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, -1, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0132, -1, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x00c0, 4, ZC_EMOTION(sock));
		ADD_PKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 30, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, -1, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x0206, 71, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x00fb, -1, ZC_GROUP_LIST(sock));
		ADD_PKT(0x01b6, 33, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, -1, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0239, 97, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 10, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 2, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x0177, 5, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 4, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, -1, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, -1, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 10, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, 15, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 6, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 3, ZC_KILLER_RANK(sock));
		ADD_PKT(0x018d, 14, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dc, 3, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 29, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x014c, -1, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x01ee, 7, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 7, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 114, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 3, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, -1, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x0109, 81, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x0117, 2, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 2, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0189, 90, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 67, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 8, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 4, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, -1, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, -1, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 3, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x02ed, 2, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x0087, 3, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x019a, 14, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 2, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, -1, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 57, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 26, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 5, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, 8, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 10, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0080, -1, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0092, 30, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 7, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x01d4, 6, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, -1, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 23, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x00c6, 6, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, 4, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 4, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x00c7, 54, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 6, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x0166, -1, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x01fc, 8, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 9, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, -1, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 68, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, -1, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x023a, -1, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00aa, 8, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, -1, ZC_RESTART_ACK(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 11, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 6, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00d1, 2, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x01b3, 6, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, 26, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 6, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x01c9, 54, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, -1, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 26, ZC_SPIRITS(sock));
		ADD_PKT(0x00c3, 6, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 6, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 27, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00be, 10, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 2, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, -1, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 6, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x01f0, 6, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 6, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 53, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 79, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 11, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 11, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x00c2, -1, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, -1, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, -1, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, 43, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, 8, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 282, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 6, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090318 */
