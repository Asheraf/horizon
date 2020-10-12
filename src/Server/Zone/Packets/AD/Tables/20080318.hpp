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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080318
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080318

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
		ADD_PKT(0x00e6, 15, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, 10, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 3, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 4, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 5, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 6, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, -1, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 4, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 6, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 4, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 5, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 8, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x019d, 14, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 4, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, 6, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 10, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, 42, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 10, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, 4, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 86, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 6, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 114, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, 67, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 7, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 10, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 18, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 90, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 7, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 3, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 3, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, -1, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, 34, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x013f, 54, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x00ff, 10, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, -1, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 8, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 43, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 10, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 4, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 33, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 2, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0127, 67, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, 3, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0128, 3, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x00c8, 2, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 20, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x02f1, 2, CZ_PROGRESS(sock));
		ADD_PKT(0x01bc, 4, CZ_RECALL(sock));
		ADD_PKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 7, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018e, 65, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0233, 2, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 182, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x0232, -1, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, 3, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0170, 6, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 24, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 66, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 4, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x012e, 4, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, 14, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00d9, 14, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 10, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, -1, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 79, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, -1, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, 3, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 10, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017a, 8, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, 4, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, 6, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 27, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, -1, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 54, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 10, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, 26, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, -1, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, 11, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, 28, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, 7, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, 9, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, 4, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00d3, 12, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 3, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 21, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 26, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x00cf, -1, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 14, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 31, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, 2, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 5, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 10, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, 6, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0096, 7, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 3, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 2, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 10, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 2, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 57, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 6, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, 28, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, 6, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 55, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, 28, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 8, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 3, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, 20, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, 26, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, -1, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, 10, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, -1, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, 7, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 3, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 29, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 16, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 30, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 18, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 6, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, 8, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, 26, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 6, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 6, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 4, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 6, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 8, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x0104, 8, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, 8, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 23, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, 6, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 14, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x01cd, 2, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 3, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, -1, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 59, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 9, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 5, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, 16, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 36, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 14, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, -1, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 4, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 2, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 23, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 282, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 12, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, -1, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 30, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 7, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 30, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 11, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 22, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 7, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 2, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 2, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 4, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 30, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 6, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 11, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 9, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 26, ZC_EMOTION(sock));
		ADD_PKT(0x00a4, 27, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, 8, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 6, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 7, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, -1, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 30, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 15, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, 5, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 26, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 4, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, -1, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 9, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0235, -1, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 26, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x017b, 11, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 11, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 53, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, -1, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 10, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 13, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, 16, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 30, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 6, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, 6, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 30, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 22, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 29, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 6, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 27, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, -1, ZC_MVP(sock));
		ADD_PKT(0x010a, 8, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 17, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 9, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 2, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, 71, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 5, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x007a, 282, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, 29, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 8, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 8, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, -1, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 10, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 2, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 30, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 2, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 58, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 22, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 11, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 2, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 6, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 10, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, -1, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 282, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 102, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 6, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 186, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, -1, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 6, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x019a, 4, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 6, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 15, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 2, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 5, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 2, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 13, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, 2, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, -1, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 8, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 60, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0093, 8, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 6, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 81, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 6, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, 2, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 26, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, 60, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, -1, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x0287, 32, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, 31, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 4, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x00c7, 58, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 26, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, -1, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 68, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 14, ZC_POSITION_INFO(sock));
		ADD_PKT(0x02f0, 10, ZC_PROGRESS(sock));
		ADD_PKT(0x02f2, 2, ZC_PROGRESS_CANCEL(sock));
		ADD_PKT(0x022e, 28, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 2, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 282, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 30, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 7, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 2, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, -1, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 5, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 10, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, 32, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 44, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, 8, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 10, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 3, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 35, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 14, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, 10, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 6, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 21, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 4, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 2, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 6, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 6, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 33, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, 6, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 53, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 6, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, -1, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 97, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 39, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 60, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, 3, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 4, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 3, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, -1, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 12, ZC_STATUS(sock));
		ADD_PKT(0x00be, 5, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 3, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0131, 6, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 3, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, 6, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, 39, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 6, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 3, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 17, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 19, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 2, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 22, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, 54, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, 11, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 30, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, 6, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 11, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 6, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 3, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080318 */