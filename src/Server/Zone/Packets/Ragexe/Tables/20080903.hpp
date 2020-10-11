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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080903
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080903

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
		ADD_PKT(0x00e6, 8, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e8, -1, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 9, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0217, -1, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x0118, 54, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, -1, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 8, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, -1, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x01ed, -1, CZ_CHOPOKGI(sock));
		ADD_PKT(0x00eb, 4, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0203, 11, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 53, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, -1, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 6, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 10, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017e, 32, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 3, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, 5, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, 29, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f3, 21, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x0362, -1, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, 26, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x0140, 10, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0364, 182, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0129, 3, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, 7, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, -1, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 57, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 282, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 55, CZ_RECALL(sock));
		ADD_PKT(0x0161, 7, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x01ba, 9, CZ_REMOVE_AID(sock));
		ADD_PKT(0x0368, 43, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, 33, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0233, 2, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0232, 6, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, 3, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 28, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 3, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, -1, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x012e, 6, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x0103, 5, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 11, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 7, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, -1, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 3, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 4, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x01fd, -1, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, -1, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01b2, 11, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, -1, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, 67, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, -1, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00b2, -1, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 30, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 5, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, -1, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00d0, -1, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 7, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, -1, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x019f, -1, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, 10, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0366, 4, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0096, 60, CZ_WHISPER(sock));
		ADD_PKT(0x0083, 10, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, -1, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x015c, -1, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, -1, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, 24, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x01f5, 4, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, 4, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, -1, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 6, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, 8, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x0274, 35, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 14, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x018b, -1, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 86, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0110, 6, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x00e9, -1, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0124, 10, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x00f4, 15, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 11, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, 6, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, 9, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, -1, ZC_ADD_SKILL(sock));
		ADD_PKT(0x0139, -1, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 26, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, 2, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 20, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, -1, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 8, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 30, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 59, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 8, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 6, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 19, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x0230, -1, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x00df, -1, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 2, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, -1, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 3, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 4, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 2, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 60, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0141, 10, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 29, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, -1, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, -1, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, -1, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 7, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 7, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, -1, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, 2, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 2, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, -1, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, 65, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, 67, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 10, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x016f, -1, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0235, -1, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, -1, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 3, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x0177, 7, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, -1, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x00a0, -1, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 39, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 8, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 4, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, -1, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 2, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 4, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010a, 7, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x014c, 8, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 60, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x02e1, 5, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, -1, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, 13, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 14, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, 81, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, -1, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 2, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0189, -1, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 58, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, -1, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 6, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, -1, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x01d9, 2, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x02ed, 15, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 2, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 8, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 5, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 16, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, -1, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x022a, 26, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 2, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, -1, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 8, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, -1, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 22, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0091, 10, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x012d, 11, ZC_OPENSTORE(sock));
		ADD_PKT(0x0133, 6, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 10, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, -1, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 22, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 6, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x0160, -1, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 30, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 21, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 2, ZC_RECOVERY(sock));
		ADD_PKT(0x01fc, 27, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 54, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 10, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x01f4, 14, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x023a, 3, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, -1, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x023c, 10, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x00e1, 23, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, -1, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00d2, -1, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x0120, -1, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 10, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x00c3, 22, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 102, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 30, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 30, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 10, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 26, ZC_STATUS(sock));
		ADD_PKT(0x00be, -1, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 6, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 15, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 97, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 6, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, -1, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 282, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x01f2, -1, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 26, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, 26, ZC_USER_COUNT(sock));
		ADD_PKT(0x01c8, 8, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 3, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 66, ZC_WARPLIST(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080903 */
