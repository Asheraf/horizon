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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081015
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081015

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
		ADD_PKT(0x00e6, 4, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, -1, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, -1, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x0202, -1, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, -1, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0099, 3, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 11, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 6, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 8, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x0102, -1, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 2, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, 20, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 6, CZ_COMMAND_MER(sock));
		ADD_PKT(0x00eb, 10, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 6, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 6, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x01e7, 4, CZ_DORIDORI(sock));
		ADD_PKT(0x0436, 7, CZ_ENTER2(sock));
		ADD_PKT(0x00ef, 3, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, -1, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 10, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 7, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, -1, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, 4, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 7, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, -1, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0363, 17, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x0237, -1, CZ_KILLER_RANK(sock));
		ADD_PKT(0x00f9, 22, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x0364, 11, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0129, 3, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 30, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 2, CZ_RECALL(sock));
		ADD_PKT(0x01bd, -1, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 21, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018e, 14, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0437, 55, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, 3, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 22, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x0234, -1, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0170, 23, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 30, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, -1, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x00bf, 21, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, -1, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 27, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 8, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x0149, 6, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014d, 5, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 6, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 6, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0100, -1, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0165, 8, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 2, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, -1, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x00e0, -1, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00c1, -1, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, -1, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, -1, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, -1, CZ_RESTART(sock));
		ADD_PKT(0x01ce, -1, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 4, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 4, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, 11, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 10, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, -1, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0439, 11, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0367, 58, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, 12, CZ_WHISPER(sock));
		ADD_PKT(0x0073, -1, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 26, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 2, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, -1, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 7, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, 8, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, 10, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, 16, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 26, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 67, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x015a, 26, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, -1, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, -1, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x018f, 6, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 6, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, -1, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 114, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x00fd, 3, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 6, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, 10, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, -1, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, -1, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 15, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 4, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0104, -1, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x0111, -1, ZC_ADD_SKILL(sock));
		ADD_PKT(0x0139, 18, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 10, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0163, 2, ZC_BAN_LIST(sock));
		ADD_PKT(0x0219, -1, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 5, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 2, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0230, -1, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x00b6, 79, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 5, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, -1, ZC_COMBODELAY(sock));
		ADD_PKT(0x00ec, 14, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 39, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, -1, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, -1, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 4, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x0132, 9, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 6, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 182, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 2, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 8, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00f0, 27, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, 8, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, 3, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 17, ZC_GROUP_LIST(sock));
		ADD_PKT(0x01b6, 26, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x0162, 2, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 26, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, -1, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 71, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 6, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 3, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, -1, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x009d, -1, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x00af, 81, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 8, ZC_KILLER_RANK(sock));
		ADD_PKT(0x01ad, 26, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x00dc, 7, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 22, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 2, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 8, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010a, 16, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 6, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x00a3, -1, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x008a, 30, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x007a, 6, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x008d, 20, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x019b, -1, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 32, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 29, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 90, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 7, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x007b, -1, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 282, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x0079, 53, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x022b, 282, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 5, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 66, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0107, -1, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 2, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, -1, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 10, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x022a, 19, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x007c, 10, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 3, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, -1, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 9, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 7, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, -1, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 30, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x0142, -1, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x00b0, 30, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 2, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 4, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, 28, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, -1, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x00c7, 15, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 12, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, -1, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, -1, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x022e, -1, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 34, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x01fc, 44, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, -1, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, -1, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 6, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, -1, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x023a, 54, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 3, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, -1, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 30, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, 18, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x00e1, 30, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 35, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00c4, 26, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 3, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x01b3, 2, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 53, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x011f, 6, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01ac, 8, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, -1, ZC_SPIRITS(sock));
		ADD_PKT(0x00c3, -1, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 60, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 6, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 6, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 6, ZC_STATUS(sock));
		ADD_PKT(0x00bc, 8, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0131, 10, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a5, 10, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 11, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 8, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x00c2, 5, ZC_USER_COUNT(sock));
		ADD_PKT(0x00a8, -1, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, 6, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011c, 3, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, -1, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081015 */
