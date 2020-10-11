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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080708
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080708

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
		ADD_PKT(0x00e6, 33, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, 16, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 16, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x0172, 102, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, -1, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 182, CZ_BROADCAST(sock));
		ADD_PKT(0x0118, 4, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, -1, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 54, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, 28, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 6, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, -1, CZ_COMMAND_PET(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 10, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, 4, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 8, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, -1, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 27, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 30, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, -1, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 11, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 5, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, 2, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, 10, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x013f, 4, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, 6, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, 4, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, -1, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, 8, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 11, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 30, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 8, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0126, 24, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 4, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0365, -1, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 7, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 6, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 43, CZ_RECALL_GID(sock));
		ADD_PKT(0x011d, 2, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018e, 4, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0369, 39, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x035f, 6, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, 12, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0360, -1, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 14, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 8, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 6, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x0155, 8, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, 2, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, 10, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, 54, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 28, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 15, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 2, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 6, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, -1, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x017c, 7, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, -1, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x01fd, 2, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, -1, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, -1, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 22, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, -1, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, -1, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x01b2, -1, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, 16, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00c1, 29, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, 10, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00b2, 3, CZ_RESTART(sock));
		ADD_PKT(0x01a7, 6, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 14, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00d0, 68, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 6, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, -1, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x019f, -1, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0366, 71, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, -1, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 6, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 10, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 8, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 81, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 15, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 6, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, 3, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, 31, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, -1, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 2, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, -1, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x0274, 67, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, 6, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x018f, 21, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, -1, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 10, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 65, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0169, 9, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0098, 39, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 6, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 10, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 6, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x01c5, 10, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 8, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 5, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x01e9, 3, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, -1, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021a, 79, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 12, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 8, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, -1, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, -1, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 6, ZC_BAN_LIST(sock));
		ADD_PKT(0x009a, -1, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 6, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, 282, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 67, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 2, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 6, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x00df, 29, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, -1, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 2, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x01d2, -1, ZC_COMBODELAY(sock));
		ADD_PKT(0x00ec, -1, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 6, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x0125, 3, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, -1, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x01cf, 14, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x01b9, -1, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 6, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 10, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, 11, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 26, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, 22, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, -1, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, -1, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 6, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, -1, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 10, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 30, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, -1, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 2, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x02f5, 26, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 6, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 7, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, -1, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 14, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x00a0, 90, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, 6, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 42, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x00b1, -1, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 3, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, 66, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 11, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, -1, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 21, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 4, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, -1, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, -1, ZC_MVP(sock));
		ADD_PKT(0x010b, -1, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 6, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, -1, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, 23, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 53, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x007a, -1, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, -1, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, -1, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 29, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, -1, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 3, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 8, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 4, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 59, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 32, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 114, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x02ed, 6, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 28, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 5, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x019a, -1, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 7, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 3, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 4, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, -1, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x02ee, 36, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, -1, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, -1, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0077, -1, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 9, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0092, 18, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, -1, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x0142, -1, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, -1, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, -1, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 30, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x0133, 4, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 8, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 5, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 27, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 57, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 2, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 2, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 26, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, -1, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, -1, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x00da, 19, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x0207, 14, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, -1, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x01f4, 6, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x023a, 9, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 11, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 3, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 6, ZC_RESTART_ACK(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 2, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 10, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, -1, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00c4, 186, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, -1, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, -1, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 6, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, 35, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x0120, 30, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, -1, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 4, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01d0, 33, ZC_SPIRITS(sock));
		ADD_PKT(0x00c3, 9, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 27, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 4, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 20, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 6, ZC_STATUS(sock));
		ADD_PKT(0x00be, 2, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 2, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, -1, ZC_STOPMOVE(sock));
		ADD_PKT(0x00a6, 30, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 282, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x01f0, 55, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 6, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 10, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 7, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 30, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 6, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x013e, -1, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x01c8, 2, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, 2, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 58, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 15, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 26, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080708 */
