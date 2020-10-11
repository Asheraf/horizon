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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080513
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080513

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
		ADD_PKT(0x00e6, 26, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, -1, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 6, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 10, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 3, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 2, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 6, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 65, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x00ed, 8, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, -1, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x019d, 11, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 11, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, 8, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 14, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 2, CZ_COMMAND_MER(sock));
		ADD_PKT(0x00eb, 6, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 7, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 8, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, 4, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 9, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 26, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 6, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 28, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017e, 3, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 15, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, 97, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 3, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 29, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x00ff, 22, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x019c, 81, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 10, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 6, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0127, -1, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, 7, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x007d, 2, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x0134, 282, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 10, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 20, CZ_RECALL(sock));
		ADD_PKT(0x0161, 6, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, -1, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 22, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 2, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0233, 6, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 30, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x0232, 17, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0170, 102, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 79, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x012a, 6, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 27, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, 5, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 10, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 33, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 16, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 2, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 71, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014d, -1, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 7, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, -1, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, -1, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, -1, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x0168, 2, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 6, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x00b9, -1, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x00e0, 10, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, 26, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00a9, 3, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 26, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 58, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 4, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 18, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 58, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 2, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 114, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x0225, 10, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, -1, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, 10, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0096, 6, CZ_WHISPER(sock));
		ADD_PKT(0x0073, -1, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 5, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 2, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00d6, 16, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, 2, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 60, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x0179, -1, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 10, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, -1, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, 15, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, 7, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, 4, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, -1, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, 6, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 9, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, -1, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 4, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 3, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 2, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 9, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, 4, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, -1, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 18, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 2, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 8, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 22, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 3, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 3, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 3, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, 8, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x021c, 5, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, -1, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, -1, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 282, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, -1, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 42, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 4, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 6, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 28, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 66, ZC_BROADCAST2(sock));
		ADD_PKT(0x0122, 10, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, -1, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 2, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 8, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 6, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 2, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 6, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, -1, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00f8, -1, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 8, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 4, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 11, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x020a, 2, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 57, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 6, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 5, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 53, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, -1, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x00c0, 186, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 30, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 14, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 11, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 43, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, -1, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 6, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 4, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, 2, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, -1, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 54, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, -1, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x0162, 3, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0239, -1, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 3, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, -1, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, -1, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 29, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, -1, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 14, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 2, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x018d, 2, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dc, 12, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 6, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 3, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010a, 30, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 4, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x00a3, -1, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 11, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 55, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, -1, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, 27, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 2, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, 6, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 68, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 5, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 2, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 30, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 10, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 28, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 35, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, -1, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 11, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 5, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 8, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 11, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, -1, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, -1, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 21, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 282, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, -1, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 10, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 30, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 3, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, -1, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 8, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x01d8, -1, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 5, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x007c, 7, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 39, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 10, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0080, 6, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0093, 2, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 5, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, -1, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x012d, 34, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 15, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, 6, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, 6, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 30, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, -1, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, 8, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00ca, -1, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 9, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 4, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 4, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 60, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, -1, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x022e, 4, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 54, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 31, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 26, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, -1, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x01f4, 67, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, 6, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 6, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, -1, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 10, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 4, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, -1, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 6, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 6, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, -1, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 4, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 54, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 6, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, -1, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, 17, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 14, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, -1, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 30, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 44, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 10, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, -1, ZC_SPIRITS2(sock));
		ADD_PKT(0x01d7, -1, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 32, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 23, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x00bd, -1, ZC_STATUS(sock));
		ADD_PKT(0x00bc, 22, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 7, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, -1, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 30, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 53, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, 4, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, 26, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 3, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x01a0, 24, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x01f2, -1, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 14, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x013e, 7, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 90, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, -1, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 8, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, -1, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080513 */
