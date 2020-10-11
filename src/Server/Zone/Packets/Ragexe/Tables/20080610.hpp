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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080610
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080610

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
		ADD_PKT(0x00e6, 6, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, 15, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 114, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, -1, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, -1, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 30, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 3, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 53, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 9, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, -1, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 22, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x0102, -1, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, -1, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, 5, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x01a1, 10, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, -1, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 6, CZ_CONTACTNPC(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 22, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 28, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 4, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 9, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, -1, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 2, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x0143, 10, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, 5, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 30, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 7, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x00ff, -1, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x0237, 4, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 6, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 27, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 11, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 97, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0129, 8, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0128, 31, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 26, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x0134, 67, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 9, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 2, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 3, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 5, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 28, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018e, 59, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0233, 66, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 2, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x0232, 30, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x015b, 54, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 30, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, -1, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x018a, -1, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x0103, -1, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 282, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 8, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x017c, -1, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, -1, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x01fd, 10, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, -1, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 11, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 2, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 3, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, 4, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 43, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, -1, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, 2, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, 6, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, 16, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, -1, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, 282, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00b2, 13, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 3, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x00cf, 57, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, -1, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x00bb, 36, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 32, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, -1, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, 6, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0096, -1, CZ_WHISPER(sock));
		ADD_PKT(0x0083, 6, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, -1, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00d6, 26, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, -1, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, 14, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, -1, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, -1, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 29, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, -1, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, 24, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, 4, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x011e, 5, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, 6, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, -1, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 2, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, -1, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 6, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, 3, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, 26, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 22, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 8, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 6, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 58, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 26, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x01c4, 33, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, -1, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, -1, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, -1, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, 8, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, 23, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 5, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 30, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 8, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, 102, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, -1, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 6, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 90, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 2, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, 15, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 6, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 23, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01a4, 4, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, 10, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 6, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 3, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 30, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x0144, 81, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 6, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 4, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 6, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, -1, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 186, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 86, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 6, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 26, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 30, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 2, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 14, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 6, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 39, ZC_EMOTION(sock));
		ADD_PKT(0x00a4, 10, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 60, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, -1, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0201, -1, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0227, 10, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, 2, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 4, ZC_GROUP_LIST(sock));
		ADD_PKT(0x01b6, 55, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x0162, 18, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 6, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, -1, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f5, -1, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 30, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 2, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 31, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x009d, 3, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 10, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 26, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 11, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x018d, 65, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, 10, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 13, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, -1, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 2, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 2, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, 282, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, 10, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, -1, ZC_MVP(sock));
		ADD_PKT(0x010a, -1, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 26, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 4, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, 10, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, 8, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x008a, 28, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 26, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 53, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, 5, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, 60, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, -1, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0106, 9, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 8, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0189, -1, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 4, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 6, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, -1, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x01da, 12, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x02ec, 6, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 3, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 8, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 2, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 7, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 10, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, -1, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x01eb, 4, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 6, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 11, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01d8, -1, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x02ee, -1, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x00f2, 39, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x0077, 14, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0093, 5, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 21, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 20, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 4, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, 8, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 32, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, 20, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, -1, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 11, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x0287, 2, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x00c6, 8, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, 7, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, 11, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, -1, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, -1, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x01a6, 3, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 6, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 27, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, 5, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, -1, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, -1, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, 7, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, 10, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, 7, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 10, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, -1, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, 2, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 4, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x00ac, 7, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 4, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 6, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 9, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, 4, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 2, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00b4, 6, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00d1, 6, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, -1, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, -1, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, 30, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 8, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, 79, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 10, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, -1, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, -1, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 7, ZC_SPIRITS(sock));
		ADD_PKT(0x00c3, 42, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, -1, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x0229, 21, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 18, ZC_STATUS(sock));
		ADD_PKT(0x00be, 44, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 2, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 19, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 12, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 17, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, 7, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x0224, 4, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, -1, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 11, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 3, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x016c, 28, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, 2, ZC_USER_COUNT(sock));
		ADD_PKT(0x00a8, -1, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, -1, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, 26, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 3, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 14, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 8, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080610 */
