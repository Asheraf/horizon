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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081126
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081126

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
		ADD_PKT(0x00e6, 68, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e8, 30, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 14, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 102, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 282, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, -1, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0118, 54, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 27, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 18, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x00b8, 2, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 5, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, 60, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 20, CZ_COMMAND_MER(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 19, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x00cc, 14, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 6, CZ_DORIDORI(sock));
		ADD_PKT(0x0436, 9, CZ_ENTER2(sock));
		ADD_PKT(0x00e3, 8, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x016e, 3, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x01d5, 8, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 4, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x0363, 6, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, 10, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, -1, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 28, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0126, 10, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 6, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0129, 2, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, 4, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 29, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 22, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x0134, 282, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, -1, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 5, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, -1, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, -1, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, -1, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x035f, -1, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, -1, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0170, -1, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 54, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 6, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x00e4, 6, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 5, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, -1, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x017a, 3, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x01fd, 32, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, -1, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 14, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0165, 21, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 10, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x01b2, 182, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, 6, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00a9, 28, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, -1, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, -1, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 6, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 5, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x00cf, -1, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x0225, 23, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 7, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0073, 30, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 6, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 6, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 3, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, -1, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 10, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, 7, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, 6, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 26, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x0274, -1, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0194, 3, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 14, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 31, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 10, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x00e9, -1, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 3, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01e9, 186, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x021a, -1, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 18, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x0147, -1, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, 5, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 30, ZC_BAN_LIST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x0122, 66, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 9, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, -1, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, -1, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, -1, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, -1, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 86, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 7, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x0144, -1, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 4, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 4, ZC_CONGRATULATION(sock));
		ADD_PKT(0x00f6, 7, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, -1, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 6, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 8, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 55, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 24, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 6, ZC_EMOTION(sock));
		ADD_PKT(0x0295, 7, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 16, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 2, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, 67, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 3, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 39, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, -1, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 3, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, -1, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 65, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 32, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0235, -1, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, -1, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, -1, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 11, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 4, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, -1, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x009e, 26, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x0238, 2, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 16, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 6, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, 8, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x00dd, 97, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00b7, 26, ZC_MENU_LIST(sock));
		ADD_PKT(0x0440, 10, ZC_MILLENNIUMSHIELD(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, -1, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010a, -1, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x00a3, -1, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, 17, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, -1, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x019b, -1, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 81, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 8, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 2, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x01d6, 11, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x007b, 30, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x01d9, 8, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 6, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x0107, 6, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, -1, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, -1, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 10, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, -1, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, -1, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 6, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, -1, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0077, 53, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 14, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 26, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x01b0, 10, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x0142, 2, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, 29, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x00ca, -1, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 2, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 29, ZC_PET_ACT(sock));
		ADD_PKT(0x022e, 9, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 7, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, -1, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 2, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0171, -1, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00fe, 27, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 26, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, 10, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 6, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 2, ZC_RESTART_ACK(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, -1, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 2, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, -1, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 10, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, 15, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 11, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 2, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 12, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x0441, 4, ZC_SKILLINFO_DELETE(sock));
		ADD_PKT(0x010e, -1, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, -1, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 60, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 4, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01d0, 31, ZC_SPIRITS(sock));
		ADD_PKT(0x020e, 10, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 11, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 7, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, -1, ZC_STATUS(sock));
		ADD_PKT(0x00be, -1, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 4, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, -1, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 15, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 6, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 26, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x01a0, 4, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x01f2, -1, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 6, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, 2, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, -1, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 10, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, -1, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x00b5, 3, ZC_WAIT_CoreLog(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081126 */
