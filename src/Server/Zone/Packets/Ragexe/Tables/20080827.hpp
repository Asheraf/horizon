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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080827
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080827

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
		ADD_PKT(0x00c5, -1, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 10, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0217, 26, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 4, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, -1, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00de, 15, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 60, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 97, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x01ed, 4, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x0090, 3, CZ_CONTACTNPC(sock));
		ADD_PKT(0x0203, 6, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00cc, 10, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 34, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 8, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017e, 11, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, 6, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, 10, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, -1, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x0362, 11, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x019c, 8, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x0140, 14, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0129, 10, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0128, 4, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, 3, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 6, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 14, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x0161, 3, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, -1, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018e, -1, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, 21, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, 2, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0233, 6, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, -1, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x0360, 2, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x015b, 43, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012e, 4, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, -1, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, -1, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 2, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x014f, 9, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, -1, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x0178, -1, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, 16, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 6, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, -1, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0159, 79, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, 39, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, -1, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00e0, 15, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, 282, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, 66, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, -1, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00b2, 102, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 8, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 6, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 53, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, -1, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 3, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, 14, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x019f, 26, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, -1, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0073, -1, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x012c, 26, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 4, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 7, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, -1, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, 18, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 60, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, -1, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, -1, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 28, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 6, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x018b, 4, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x013b, -1, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 54, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, -1, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 2, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x0104, 4, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x0111, 5, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x0139, 30, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 5, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 12, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x021b, 33, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, -1, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, -1, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x0122, 3, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0123, 3, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x0230, 22, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x00df, 6, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 59, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 6, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, -1, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, -1, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, -1, ZC_COMPASS(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x020a, 7, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 6, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 6, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 30, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x01cf, 3, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x00c0, -1, ZC_EMOTION(sock));
		ADD_PKT(0x00db, -1, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 8, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00f0, 11, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01a3, 2, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, 8, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 6, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, -1, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x01b6, -1, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 2, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0235, 7, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 10, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 182, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 68, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009e, -1, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 14, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x00af, 6, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 10, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, -1, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 14, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, -1, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 27, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, -1, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 7, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 6, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, -1, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, -1, ZC_MVP(sock));
		ADD_PKT(0x010a, 2, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x01ee, 31, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, -1, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, -1, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 282, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x019b, 39, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 30, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, -1, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 2, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 11, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, -1, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 6, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x01da, 2, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 282, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 26, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, -1, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x02ed, 2, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 2, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, -1, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 6, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 8, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x022a, 13, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, -1, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, 10, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 4, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 14, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 58, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0092, -1, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, -1, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x0142, -1, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, -1, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 5, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 30, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 16, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, -1, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 6, ZC_PET_ACT(sock));
		ADD_PKT(0x0160, 67, ZC_POSITION_INFO(sock));
		ADD_PKT(0x01a2, 5, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x01fc, 90, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0171, -1, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00fe, -1, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x023a, -1, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 10, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 10, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x00e1, 11, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 2, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00d2, 6, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x0120, 6, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, -1, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 6, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01d7, 4, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, -1, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x00be, 6, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, -1, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x00a6, 29, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x00a5, -1, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, 12, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 42, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 65, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 8, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 86, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x00c2, 17, ZC_USER_COUNT(sock));
		ADD_PKT(0x00a8, -1, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, 8, ZC_USE_SKILL(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080827 */
