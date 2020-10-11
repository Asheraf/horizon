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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081119
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081119

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
		ADD_PKT(0x0202, 7, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 13, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0217, 28, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x0118, 11, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 44, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 5, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 9, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, -1, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x0146, 14, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x0090, 30, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, -1, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x00ef, -1, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, 2, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x00ff, -1, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x0237, -1, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 30, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 2, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x0140, -1, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 14, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 4, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0129, 3, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, 6, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 10, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 16, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, -1, CZ_RECALL(sock));
		ADD_PKT(0x0161, 67, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 14, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018e, 3, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, 34, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, 10, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x035f, 59, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, 8, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0170, 30, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 10, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x012a, -1, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 7, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, -1, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x0103, 6, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 6, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 18, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x017c, -1, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x01fd, 20, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 2, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 8, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0165, 17, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x00e0, 5, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, -1, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00a9, 4, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 4, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 54, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 15, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, -1, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 5, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x0225, -1, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, -1, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0439, -1, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0438, -1, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0083, 282, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x00ea, 42, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 10, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, -1, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0179, 10, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 8, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, -1, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x0274, 11, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x018f, 28, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 3, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x018b, 60, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0110, 6, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, -1, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, -1, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 6, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0124, 182, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 97, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 65, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01e9, -1, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, 60, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 31, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, -1, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 8, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x01c3, 4, ZC_BROADCAST2(sock));
		ADD_PKT(0x0122, 2, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0123, 58, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 10, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 4, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 2, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 53, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 14, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00f8, 3, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, -1, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 6, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 30, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, -1, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, -1, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x00f6, 5, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 30, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, -1, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, -1, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x01b9, -1, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 2, ZC_EMOTION(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x022f, 30, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 6, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, 11, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 8, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, 6, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x017f, 4, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 31, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x0162, -1, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 58, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 29, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 2, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 7, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x009d, -1, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 5, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 35, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, -1, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 6, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x018c, 26, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 26, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 3, ZC_MVP(sock));
		ADD_PKT(0x010a, 4, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x00a3, 8, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x008a, 7, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x019b, 3, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0106, 10, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0189, -1, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 86, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x007b, -1, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 4, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 60, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 6, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x01d9, 10, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 2, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, -1, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, -1, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 10, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 2, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 23, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 11, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 16, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 8, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 9, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 8, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 26, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, 10, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 186, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, -1, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0093, -1, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x01b0, -1, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, -1, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, -1, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01ab, 7, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x00c6, 6, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x00ca, 29, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x00c7, 6, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, -1, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x0166, -1, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x022e, -1, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x013d, 79, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 2, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01f4, -1, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, 53, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x023a, -1, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00b3, 14, ZC_RESTART_ACK(sock));
		ADD_PKT(0x023c, 5, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 2, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 22, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 19, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, 71, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, -1, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, -1, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 2, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010e, 81, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 10, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x01ac, -1, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 27, ZC_SPIRITS(sock));
		ADD_PKT(0x0119, 6, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 11, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 13, ZC_STATUS(sock));
		ADD_PKT(0x00be, 2, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 7, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 4, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, -1, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x0296, 6, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, -1, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, 3, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x01f2, 90, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x00c2, -1, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, 32, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 5, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, 10, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, -1, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, -1, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081119 */
