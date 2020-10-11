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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080910
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080910

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
		ADD_PKT(0x0202, -1, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 2, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 30, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 7, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x01ed, 14, CZ_CHOPOKGI(sock));
		ADD_PKT(0x01a1, 27, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, -1, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 282, CZ_CONTACTNPC(sock));
		ADD_PKT(0x0203, 58, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 5, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x01e7, 11, CZ_DORIDORI(sock));
		ADD_PKT(0x0436, 3, CZ_ENTER2(sock));
		ADD_PKT(0x00ef, -1, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017e, 8, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 4, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, -1, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, 10, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f3, -1, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, 4, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, 5, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 9, CZ_KILLER_RANK(sock));
		ADD_PKT(0x00f9, 4, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x0140, 60, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0364, 2, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 81, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, -1, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, -1, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x007d, 6, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, 6, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x01bc, 3, CZ_RECALL(sock));
		ADD_PKT(0x0161, 3, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x01ba, -1, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 11, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, -1, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, -1, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0437, -1, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, -1, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x035f, 8, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, -1, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, -1, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 8, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 14, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x0130, 12, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x0155, 12, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, -1, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, 2, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, 44, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 6, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x0103, -1, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 20, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, 4, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 26, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 54, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 26, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, 6, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, 15, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 30, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0159, 39, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x01b2, -1, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, 3, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, -1, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00b2, 14, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 10, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x00cf, 30, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 10, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x0112, -1, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0439, 30, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0438, -1, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0367, 30, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, -1, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 7, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, -1, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x015c, 23, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x015e, -1, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x01f5, 102, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, -1, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 8, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, -1, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x0274, 6, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x0095, 6, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, -1, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x00fd, 24, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x00e9, 5, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 12, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 29, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 13, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 8, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, -1, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, -1, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, -1, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x021c, 9, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, 26, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x013a, 7, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, -1, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, 33, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x0219, 4, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 20, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, -1, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, 7, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, -1, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, -1, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 90, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x009c, -1, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 2, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 6, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, -1, ZC_COMBODELAY(sock));
		ADD_PKT(0x00ec, -1, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 4, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, -1, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 7, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0105, -1, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, -1, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01b9, 6, ZC_DISPEL(sock));
		ADD_PKT(0x00db, 28, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 14, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x0206, 2, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 11, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, 3, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, -1, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x0239, 3, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, -1, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 11, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 32, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, -1, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x009d, 4, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x029a, 2, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 71, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 55, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, -1, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x00dd, 10, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 15, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 7, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 33, ZC_MVP(sock));
		ADD_PKT(0x010a, 6, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x014c, 6, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 4, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x008a, 79, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 2, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 27, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, 3, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 3, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 14, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 22, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0075, 3, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 16, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x01d6, 22, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x007b, 6, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 3, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 30, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x01d9, 282, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x02ed, -1, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, -1, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 3, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, -1, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x0078, 10, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 6, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 21, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 3, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, 6, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 4, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0077, 26, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, -1, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0091, -1, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 114, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x012d, -1, ZC_OPENSTORE(sock));
		ADD_PKT(0x01d4, 26, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x01ab, 16, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x00c6, 19, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x0135, -1, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 10, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01aa, -1, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 13, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 6, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, -1, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, -1, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, -1, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 6, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 16, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, -1, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, -1, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 35, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 10, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x016a, 8, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, -1, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 6, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 3, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 11, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d2, 2, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x011f, -1, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 6, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 28, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 31, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 4, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, 8, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, -1, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 29, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, -1, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, -1, ZC_STATUS(sock));
		ADD_PKT(0x00bc, -1, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, -1, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, -1, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 10, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0224, 66, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x01a0, 2, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 97, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 6, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 6, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, -1, ZC_USER_COUNT(sock));
		ADD_PKT(0x00a8, 282, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, -1, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, -1, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 58, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080910 */
