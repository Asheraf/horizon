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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081105
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081105

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
		ADD_PKT(0x00e6, 39, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00c5, -1, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, -1, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0218, 30, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 30, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 10, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x00ed, -1, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 16, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 6, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 8, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 8, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01a1, 2, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, -1, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, -1, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x00cc, -1, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 8, CZ_DORIDORI(sock));
		ADD_PKT(0x0436, 60, CZ_ENTER2(sock));
		ADD_PKT(0x00ef, 14, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 15, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 67, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 6, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x01d5, 2, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, 10, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x013f, 29, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, 5, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x016b, 43, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 8, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 28, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 60, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0129, -1, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, 6, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 3, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 9, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, -1, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 4, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 2, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, -1, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x0368, -1, CZ_REQNAME2(sock));
		ADD_PKT(0x0437, 282, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, 6, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x035f, 30, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0234, 20, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 14, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x015b, -1, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 54, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 30, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, 6, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00e4, 12, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, -1, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 6, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, -1, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x017c, 2, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 71, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x01fd, 2, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x0100, 6, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x01ae, -1, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, 2, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x00ab, -1, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, 9, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00b2, 11, CZ_RESTART(sock));
		ADD_PKT(0x01ce, -1, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x011b, 15, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00d0, 6, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, -1, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x019f, 6, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0439, 4, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0438, 4, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, -1, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 7, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 4, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, -1, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 11, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 6, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 6, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x017d, -1, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 3, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, -1, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, -1, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, 3, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, -1, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, -1, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0195, -1, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 20, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 18, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, -1, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0098, 16, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 6, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 10, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, -1, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x01c5, 14, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 2, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 6, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, -1, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, -1, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 10, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, -1, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x013a, 8, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x01cd, -1, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 28, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 3, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 5, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, -1, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x0122, 10, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, -1, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, -1, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 24, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 10, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, -1, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x009c, 30, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 2, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x01d2, 10, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 53, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 86, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 57, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0125, 4, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, -1, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x00d8, 26, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x0132, -1, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x00db, 28, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 10, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, 6, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00f0, 8, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, -1, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 44, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0101, -1, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x01b6, -1, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 26, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, 8, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 59, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x02f5, 90, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 2, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x0177, 8, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 8, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 6, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0154, 4, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 26, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 5, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x018c, 4, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 21, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, -1, ZC_MVP(sock));
		ADD_PKT(0x010a, 36, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x014c, 3, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, -1, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, 10, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, -1, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, -1, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, -1, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, 3, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 79, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, 6, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x0117, 14, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 8, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x0086, -1, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, -1, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 30, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x008e, 5, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0107, 5, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x0114, 10, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 22, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 7, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 30, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, -1, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 14, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, -1, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, -1, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0091, 22, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, -1, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x0142, 3, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, 2, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x01ab, 3, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, -1, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 7, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, -1, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 3, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x01a6, 58, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 29, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 6, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 2, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, -1, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 282, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, -1, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x0207, 5, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00fe, 5, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 102, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, -1, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00aa, 4, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 11, ZC_RESTART_ACK(sock));
		ADD_PKT(0x023c, 6, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x00e1, 28, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00b4, 32, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 23, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 6, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, -1, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010e, 30, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x011f, 2, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01d0, -1, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 3, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, 10, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x0229, 2, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 6, ZC_STATUS(sock));
		ADD_PKT(0x0088, 2, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, -1, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a5, 42, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, 3, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x01a0, -1, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 10, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, -1, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 29, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x013e, 6, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x01c8, -1, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, 7, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 4, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 26, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, -1, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081105 */
