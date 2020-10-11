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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080520
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080520

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
		ADD_PKT(0x00e6, 43, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, 10, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 4, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 66, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 11, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, -1, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, -1, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 8, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 3, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 90, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 4, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x019d, 8, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 6, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, 53, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, -1, CZ_CHOPOKGI(sock));
		ADD_PKT(0x035e, -1, CZ_CLOSE_WINDOW(sock));
		ADD_PKT(0x022d, -1, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, 21, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 11, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 3, CZ_CONTACTNPC(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 3, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, -1, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 22, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 26, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, -1, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, 6, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, 12, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 5, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, -1, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x00ff, 4, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x0237, 3, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 3, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 3, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 8, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0127, 2, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, -1, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0128, 2, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 9, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x035c, 2, CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST(sock));
		ADD_PKT(0x0134, 7, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 10, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 35, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 2, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 23, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 7, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 11, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0233, 15, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 97, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x0232, -1, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, 10, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0170, 30, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 59, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 282, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 9, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, -1, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, 4, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, 8, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 5, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, -1, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 6, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 27, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014d, 282, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 39, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 6, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, 7, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, 8, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 6, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 15, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 14, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 27, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x01ae, 8, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x01b2, 54, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, -1, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, 36, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00a9, 79, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 3, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 6, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 53, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 2, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 8, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 30, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x00bb, 13, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 2, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 18, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, 30, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0073, 2, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 4, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, -1, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 3, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 7, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 26, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, 3, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, 14, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 5, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, 4, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 11, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x015a, -1, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, 30, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, -1, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0194, 2, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, -1, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, -1, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, 16, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 10, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, -1, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 6, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 11, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x01c4, -1, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, 17, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x021c, 2, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x0147, 114, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, -1, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x009a, 10, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 3, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0123, 6, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 14, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, -1, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 34, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 23, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 67, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x01d2, -1, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, -1, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 81, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0141, 4, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x020a, 30, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 44, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 8, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 3, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 7, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 26, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x00c0, 2, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 4, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 3, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x013c, 4, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 14, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 26, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 26, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, -1, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 10, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, -1, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 29, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, -1, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x0162, 10, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 5, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 282, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 2, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x017b, 68, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x00a1, 60, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 10, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 186, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 3, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, 55, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x018d, -1, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x00dd, 28, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 30, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 58, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 102, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 22, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 8, ZC_MVP(sock));
		ADD_PKT(0x010a, 3, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, -1, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x00a3, 15, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, 26, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 29, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 6, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x0121, 26, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 4, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x019b, 18, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, -1, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0075, 12, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, -1, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 5, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 2, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 30, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, -1, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 60, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 6, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 14, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 54, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 4, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 10, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 11, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 10, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, -1, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 4, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 17, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 30, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 14, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 6, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, -1, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 28, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, 3, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, -1, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 5, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 10, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0093, 22, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, -1, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 6, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, -1, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, -1, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 7, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, -1, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, 3, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, 57, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 30, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x0135, -1, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 22, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 6, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 28, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 16, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 8, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, -1, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, -1, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 8, ZC_RECOVERY(sock));
		ADD_PKT(0x01fc, -1, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 28, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 7, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 6, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, -1, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, -1, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 24, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x00aa, 2, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 2, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 86, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x00e1, 20, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 9, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 10, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, 2, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, -1, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 9, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 71, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x035d, 10, ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST(sock));
		ADD_PKT(0x010f, 6, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 6, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 5, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, -1, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01ac, 6, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 2, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 32, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, 10, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 282, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 4, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 31, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 26, ZC_STATUS(sock));
		ADD_PKT(0x00be, 8, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, -1, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 6, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 3, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 5, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, 6, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x01a0, 42, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 13, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x016c, 30, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x013e, 20, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 10, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, 6, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 2, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 2, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 8, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080520 */
