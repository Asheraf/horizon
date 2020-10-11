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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090311
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090311

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
		ADD_PKT(0x0208, 8, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 8, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, -1, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0217, -1, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 6, CZ_BROADCAST(sock));
		ADD_PKT(0x0118, 27, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, -1, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x019d, -1, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, -1, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, -1, CZ_CHOPOKGI(sock));
		ADD_PKT(0x022d, 28, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, 26, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 11, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 26, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 30, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, 7, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 3, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x01e7, 10, CZ_DORIDORI(sock));
		ADD_PKT(0x0436, 10, CZ_ENTER2(sock));
		ADD_PKT(0x00ef, -1, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 15, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x02f6, 65, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 2, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 3, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x016b, 6, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0140, 2, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, -1, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 3, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 10, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0365, 60, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 8, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, 8, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 58, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 29, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bd, 22, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 14, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 30, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018e, 10, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0369, 5, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0437, 30, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, -1, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x035f, -1, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, -1, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0360, -1, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 2, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 33, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 3, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, -1, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, -1, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 2, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x0103, 2, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x0149, 29, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, -1, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x017c, 8, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0178, 6, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, 10, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x0100, -1, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 18, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x01ae, -1, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, -1, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, 44, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, 5, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00c1, 10, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, 6, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 12, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 186, CZ_RESTART(sock));
		ADD_PKT(0x01a7, 6, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 4, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 14, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00bb, 43, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 4, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 8, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, 6, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0438, 5, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0366, 16, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0096, 9, CZ_WHISPER(sock));
		ADD_PKT(0x0073, -1, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, -1, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00d6, 2, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, -1, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x017d, 2, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 32, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x015a, 8, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, -1, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, -1, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, 2, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, 4, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 3, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 54, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, -1, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, 9, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x013b, -1, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 22, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 4, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x01c5, 6, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, -1, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, -1, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, -1, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x013a, 8, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x01cd, 6, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x021b, -1, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, -1, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, -1, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 15, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, -1, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0230, -1, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x00df, -1, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 29, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, -1, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 10, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 2, ZC_COMBODELAY(sock));
		ADD_PKT(0x00ec, -1, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 59, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 3, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, -1, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 282, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 10, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x00d8, 2, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x0132, 28, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, -1, ZC_DISPEL(sock));
		ADD_PKT(0x00db, -1, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 3, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, 81, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00f0, 34, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 23, ZC_FEED_MER(sock));
		ADD_PKT(0x0206, -1, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, 36, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, -1, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 6, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 7, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0235, -1, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x02f5, 60, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 39, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x00a1, 27, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 54, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 114, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x029a, 32, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00b1, -1, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 4, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x0154, 26, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dc, -1, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 2, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, -1, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x014c, 4, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x01ee, 6, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 21, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, -1, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x008d, -1, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x019b, -1, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 282, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x01d6, 30, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x022c, 2, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 7, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 15, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 31, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x02ed, 6, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x0087, -1, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x01de, 67, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 2, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x022a, 3, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 3, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, -1, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 6, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0077, -1, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 6, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x012d, -1, ZC_OPENSTORE(sock));
		ADD_PKT(0x01d4, 53, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, 57, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 26, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, -1, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, 60, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 2, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 7, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, -1, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 27, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x0166, 26, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 6, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, -1, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x013d, -1, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, -1, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 3, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 7, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 11, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 20, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x023a, 79, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, -1, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 6, ZC_RESTART_ACK(sock));
		ADD_PKT(0x023c, 6, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 26, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 14, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00b4, 37, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00d1, 6, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, -1, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x0120, -1, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, -1, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 4, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01e1, 5, ZC_SPIRITS2(sock));
		ADD_PKT(0x01d7, -1, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 12, ZC_STARSKILL(sock));
		ADD_PKT(0x00be, 2, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, -1, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 4, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 17, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, -1, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x0226, 55, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01f2, 4, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x00c2, 12, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, 4, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 30, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, 3, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 3, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 58, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, -1, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090311 */
