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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080507
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080507

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
		ADD_PKT(0x00e6, 79, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, 60, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 8, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 86, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 19, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, -1, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 28, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 8, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 8, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 6, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 2, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 15, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, -1, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, 6, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 29, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, -1, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 36, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 4, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, -1, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, 7, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, -1, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, -1, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 54, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 4, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017e, 32, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x0143, 2, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, 5, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, -1, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 20, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x00ff, 282, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x0237, -1, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 18, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 5, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 14, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 4, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, -1, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0127, 6, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, -1, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0128, -1, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 10, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 16, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x01bc, 39, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 4, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 4, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 81, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, -1, CZ_REMOVE_AID(sock));
		ADD_PKT(0x0233, 68, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 6, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x015b, 4, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 14, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 10, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, 102, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x00bf, 11, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 3, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 6, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 30, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x014f, -1, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 3, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017a, 6, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x01fd, 6, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, -1, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 10, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 27, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 15, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, -1, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x00b9, 30, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, -1, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00ab, 4, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, -1, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, 26, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00b2, 6, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 65, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, -1, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, -1, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 14, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x00bb, -1, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 9, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 26, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0073, 97, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 30, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 10, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 26, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 6, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x015e, 9, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, 90, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 4, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x0179, 43, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 2, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, 7, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x0274, -1, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, 30, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, 9, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, 7, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 22, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 2, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 53, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, -1, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 8, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 282, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, 3, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, 13, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 2, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x0209, 5, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 2, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x00f4, 8, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 31, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x01e9, -1, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, -1, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, 8, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, 3, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 9, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 182, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 4, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, 10, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 8, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 12, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x01c3, 7, ZC_BROADCAST2(sock));
		ADD_PKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0123, -1, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 7, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, -1, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 11, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 3, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 6, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00f8, 6, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 58, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 7, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 3, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 12, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 6, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x020a, 71, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 2, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x0105, -1, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 17, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 2, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x00c0, -1, ZC_EMOTION(sock));
		ADD_PKT(0x00a4, 33, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, 6, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 6, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x01a3, 5, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, 67, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, 58, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 28, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 11, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 7, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, -1, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, 30, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0239, 5, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 5, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, -1, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 53, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 30, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 11, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 59, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 6, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 23, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, 12, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x00b1, -1, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 6, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x0154, 16, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00b7, 20, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 21, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 10, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 2, ZC_MVP(sock));
		ADD_PKT(0x010a, 31, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x014c, -1, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 10, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, 2, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 26, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 22, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 3, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, -1, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 66, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, 26, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, -1, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 6, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 8, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0199, 8, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, -1, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 32, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, -1, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 10, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 6, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, -1, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 57, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 60, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 6, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 10, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 2, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0107, 6, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 114, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 8, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 4, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, -1, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 6, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, -1, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, -1, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, 54, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 3, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0093, 26, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 6, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 7, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 6, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, -1, ZC_OPENSTORE(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 11, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, 26, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 3, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 3, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 8, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x01a6, 6, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 6, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 7, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, -1, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 8, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 27, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, -1, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 3, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 10, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 2, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, -1, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x023a, 28, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 67, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 6, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 4, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 4, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, 30, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, -1, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 4, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 39, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00c4, 29, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, -1, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, -1, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 2, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 10, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 54, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 6, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 6, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 10, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01e1, 3, ZC_SPIRITS2(sock));
		ADD_PKT(0x01d7, 2, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0229, 5, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 7, ZC_STATUS(sock));
		ADD_PKT(0x00be, -1, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 14, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0131, 35, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 10, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 3, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x01a0, 23, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 22, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, -1, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, -1, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, 21, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 3, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, 29, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, 3, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 5, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 282, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 30, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080507 */
