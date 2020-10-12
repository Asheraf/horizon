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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080617
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080617

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
		ADD_PKT(0x00e6, 9, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, -1, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 9, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x0218, 68, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 102, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 4, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x0361, 2, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x00b8, 9, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x0146, 23, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x01a1, -1, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 5, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00ce, 11, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, -1, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 6, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 30, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 58, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 39, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, -1, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, -1, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 2, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0363, 58, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x016b, 6, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 5, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x01e8, 14, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, -1, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 43, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 15, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0129, -1, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0128, 3, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, -1, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, 15, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 8, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 36, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, -1, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 44, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 2, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 10, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 3, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, -1, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0233, 10, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 54, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, 4, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, 6, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, 6, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x015b, 20, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 6, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 12, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, 31, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, 18, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00e4, 86, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 30, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 6, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x014f, -1, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x017c, 26, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0178, 10, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, -1, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x0168, -1, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, -1, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, -1, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 2, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, 9, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, 3, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, -1, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, 6, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00a9, -1, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00b2, 10, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 27, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 6, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x00cf, 30, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00bb, -1, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 7, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x0112, 59, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0367, 29, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0073, 32, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 34, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x00ea, 90, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00d6, -1, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 6, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x0179, 6, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, 11, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, -1, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, -1, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x011e, 33, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0194, -1, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x00fd, -1, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, 24, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, -1, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, -1, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, -1, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 4, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 8, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 11, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, -1, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x01e9, 6, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 2, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, 97, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, -1, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 3, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 18, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, -1, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x021b, 10, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 8, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, -1, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 6, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 81, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, 12, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0123, 6, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 10, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 4, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, -1, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 30, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, -1, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, -1, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 17, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 7, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, -1, ZC_COMPASS(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 71, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, -1, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 6, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 26, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, -1, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, -1, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, -1, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 10, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, -1, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 60, ZC_EMOTION(sock));
		ADD_PKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x013c, 12, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, -1, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 4, ZC_FEED_MER(sock));
		ADD_PKT(0x0206, 30, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, -1, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 3, ZC_GROUP_LIST(sock));
		ADD_PKT(0x01b6, 26, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 2, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, 22, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, -1, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x02f5, 26, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, -1, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 4, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 60, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 13, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, -1, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 6, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x0238, 6, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, -1, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, -1, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, -1, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dc, -1, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 31, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, -1, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010b, 8, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 17, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 3, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, 23, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 2, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, -1, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 6, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x008d, 282, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, 7, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 4, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, -1, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 55, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, -1, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x01da, 2, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x02ec, 42, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, -1, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 22, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 6, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 60, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 6, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0107, 3, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 7, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 11, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 15, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 14, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, -1, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 6, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 8, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x00f2, 10, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 5, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, -1, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 2, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0093, -1, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 2, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 7, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, -1, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, 3, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, -1, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, -1, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, 8, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, -1, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 8, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x0135, 13, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x01a6, -1, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x0166, -1, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 11, ZC_POSITION_INFO(sock));
		ADD_PKT(0x013d, -1, ZC_RECOVERY(sock));
		ADD_PKT(0x01fc, 186, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 11, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, -1, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 28, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00fe, -1, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 10, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, 10, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 6, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, -1, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, -1, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, -1, ZC_RESURRECTION(sock));
		ADD_PKT(0x00b4, -1, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 11, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 14, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 30, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 3, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01d0, 53, ZC_SPIRITS(sock));
		ADD_PKT(0x00c3, -1, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 8, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x0229, -1, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 79, ZC_STATUS(sock));
		ADD_PKT(0x00be, -1, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 6, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 10, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 3, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x0296, 19, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, -1, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, 16, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0226, 3, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, -1, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x016c, 10, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, -1, ZC_USER_COUNT(sock));
		ADD_PKT(0x01c8, 65, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, 6, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, -1, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 10, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080617 */