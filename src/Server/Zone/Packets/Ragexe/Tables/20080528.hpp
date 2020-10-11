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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080528
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080528

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
		ADD_PKT(0x0208, 26, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 10, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 5, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, -1, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0217, -1, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 60, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, -1, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 8, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 57, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 2, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 17, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 4, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, 10, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x01a1, 7, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, -1, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 81, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, 34, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 11, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x01e7, 39, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 30, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 35, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 29, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x0143, 26, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, 2, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 26, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 2, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, -1, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, -1, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x0237, 19, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 55, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 6, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 53, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 6, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, -1, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0365, -1, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 11, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, -1, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, 6, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x01bc, 7, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 9, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 6, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 14, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, -1, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 5, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, -1, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, -1, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0233, -1, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 11, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, -1, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, 4, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, -1, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, -1, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, -1, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, -1, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, -1, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 8, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x018a, -1, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, 65, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 4, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x0103, 79, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 6, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 6, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, 13, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 30, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 21, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 4, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, 33, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, 26, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, -1, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 282, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 186, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, 114, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, -1, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x01b2, -1, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00ab, 53, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00a9, 6, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 6, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 2, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 22, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 30, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, -1, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 5, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 3, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 16, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, 10, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x019f, 20, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, 7, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, 31, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 6, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, -1, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 58, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 30, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, -1, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 3, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, 182, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 60, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, -1, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 5, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 3, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x015a, 31, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, 10, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, 8, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, 6, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x0095, 2, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 2, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, -1, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 12, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 3, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 2, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, 10, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, -1, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 5, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x0209, 39, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 32, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, -1, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 6, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, 26, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, 3, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 23, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, 26, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0147, -1, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x0163, 68, ZC_BAN_LIST(sock));
		ADD_PKT(0x0219, 30, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, -1, ZC_BROADCAST(sock));
		ADD_PKT(0x00ee, 18, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, 4, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0123, 28, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 6, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x01a4, -1, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 90, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 26, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 11, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 2, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x0144, 3, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 14, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 2, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 18, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 8, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 32, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 2, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 10, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 6, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 5, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 15, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x00c0, 30, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 3, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x013c, 8, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, -1, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, 26, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, 4, ZC_GROUP_LIST(sock));
		ADD_PKT(0x01b6, 33, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 2, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, 66, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 12, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 29, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, -1, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x017b, 4, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 4, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, -1, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 8, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 3, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, -1, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, 7, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 29, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x00b1, 6, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x01ad, 8, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 5, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 7, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 27, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 67, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 30, ZC_MVP(sock));
		ADD_PKT(0x010a, 102, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x014c, 16, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 4, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 9, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 10, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x0121, 4, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 2, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 27, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 6, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, -1, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 24, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 11, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 8, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 17, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 42, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x02ec, 6, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, -1, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 7, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 97, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 7, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 282, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 6, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, -1, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 6, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 6, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 14, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 22, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 3, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x02ee, 3, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, -1, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 6, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 13, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 8, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 22, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0093, 3, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 14, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, -1, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 8, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, 30, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, -1, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x00b0, -1, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 6, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0133, 8, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 10, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00c7, 3, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01aa, -1, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 4, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 2, ZC_POSITION_INFO(sock));
		ADD_PKT(0x013d, -1, ZC_RECOVERY(sock));
		ADD_PKT(0x01fc, 4, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, -1, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 6, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x016a, 6, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 6, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 6, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 26, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x0148, -1, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 2, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 8, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 3, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 10, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 11, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 60, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 2, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 28, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 282, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 14, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, -1, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, -1, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 43, ZC_SPIRITS2(sock));
		ADD_PKT(0x01d7, 9, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 7, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 10, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 2, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, -1, ZC_STATUS(sock));
		ADD_PKT(0x00be, 54, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 14, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 15, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, -1, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 2, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, 28, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, 8, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 9, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 36, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 4, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 20, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 54, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x013e, 6, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 6, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x011a, 8, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, -1, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 7, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080528 */
