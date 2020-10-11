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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080603
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080603

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
		ADD_PKT(0x00e6, 2, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, 10, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, -1, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 8, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 6, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 5, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0217, 6, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 4, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 7, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, -1, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x019d, -1, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 26, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, 6, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 30, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x01a1, -1, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 54, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00d5, -1, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, 7, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 102, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 2, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 14, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 11, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 30, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x0143, 7, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, 9, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 9, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 11, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x00ff, 7, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x0237, -1, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 10, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, -1, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, -1, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 12, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0129, 6, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0128, -1, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 6, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, 30, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 30, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 282, CZ_RECALL(sock));
		ADD_PKT(0x01bd, -1, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 16, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 3, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018e, 10, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0233, 6, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0232, 2, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x015b, 32, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 4, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 11, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 12, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x018a, 2, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, 3, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, -1, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x0103, 10, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 7, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, 3, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 2, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 6, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 28, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, -1, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, -1, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 18, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, -1, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, -1, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0165, -1, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x00b9, 66, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, 57, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, 2, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, -1, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, 81, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, 114, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, -1, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, -1, CZ_RESTART(sock));
		ADD_PKT(0x01ce, -1, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x00cf, 6, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 10, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, -1, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, 6, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 14, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 6, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, 14, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0096, 10, CZ_WHISPER(sock));
		ADD_PKT(0x0073, -1, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 13, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 5, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 6, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, -1, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, 4, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, -1, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, 3, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 27, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 14, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, 4, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, 2, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, -1, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, -1, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, -1, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, 12, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 54, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 53, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x018b, 182, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 97, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 4, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x013b, -1, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 4, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, -1, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 54, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 30, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x0104, 3, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x0111, 11, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, 13, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, 30, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 2, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 39, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x01cd, 4, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 44, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 10, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 4, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 29, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 58, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 6, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 9, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 30, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, -1, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x01a4, 10, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 4, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 4, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 39, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 10, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 4, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 22, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, -1, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 5, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 6, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 11, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 6, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, -1, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x00d8, -1, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, -1, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 16, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 8, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 26, ZC_EMOTION(sock));
		ADD_PKT(0x00db, -1, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x0295, 30, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 53, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 6, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 22, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 26, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, 29, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 3, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 6, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, 17, ZC_GROUP_LIST(sock));
		ADD_PKT(0x01b6, -1, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, -1, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, 30, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, -1, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 2, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, 28, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 58, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x009d, 6, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 4, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 8, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, 28, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, 10, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 21, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 2, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 9, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, 4, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 20, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 11, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x018c, 8, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, -1, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 31, ZC_MVP(sock));
		ADD_PKT(0x010a, 34, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 6, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, -1, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x008a, 68, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 8, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x0121, -1, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 6, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, 5, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, 2, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, -1, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0075, 6, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, 7, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 33, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, -1, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 3, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, -1, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 10, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 4, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x022b, 18, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, -1, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 27, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, -1, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x019a, -1, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 7, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 6, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 14, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 11, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x02ee, 2, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, -1, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 86, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, -1, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0091, -1, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 26, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, -1, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, -1, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 2, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x00b0, 6, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 31, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 60, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 10, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 43, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 2, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 186, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 10, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 28, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 2, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, 24, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 71, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0171, 282, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 2, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 7, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x016a, -1, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x00ac, 3, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 10, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 30, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 67, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x00d7, -1, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, 33, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, 6, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 5, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 7, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 2, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, 5, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 6, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, -1, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 3, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 4, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 59, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 2, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, -1, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, -1, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 5, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, -1, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, -1, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, -1, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 6, ZC_STATUS(sock));
		ADD_PKT(0x00be, 3, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 26, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 60, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 35, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, 10, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x00a5, 9, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 14, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 2, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 29, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 14, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, -1, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, -1, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, 90, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, -1, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x01c8, 8, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 6, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 8, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 5, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080603 */
