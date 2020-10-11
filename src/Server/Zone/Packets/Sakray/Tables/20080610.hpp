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
		ADD_PKT(0x00e6, -1, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, -1, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 14, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, -1, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, -1, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 16, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, -1, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x0217, 39, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x00ed, -1, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, -1, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x0361, 65, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 32, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, -1, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, 6, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 53, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x022d, 26, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, 6, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, -1, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 12, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 3, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, -1, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 4, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, -1, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, -1, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 3, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 90, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 6, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, 11, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x02f6, 3, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x013f, -1, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x00ff, -1, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, 35, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, -1, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 5, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 39, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 30, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, -1, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 8, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 2, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, -1, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x0365, 2, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 6, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 54, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x0134, 16, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x01bc, 4, CZ_RECALL(sock));
		ADD_PKT(0x01bd, -1, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 10, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, -1, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, -1, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 6, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, 7, CZ_REQNAME2(sock));
		ADD_PKT(0x0369, 14, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0233, 6, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x0108, 15, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, 7, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, -1, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, -1, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0360, 57, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, -1, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 42, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 86, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, -1, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x012e, -1, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, 22, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, -1, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, -1, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 79, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, -1, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, -1, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, -1, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 26, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, -1, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 6, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, -1, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, -1, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 8, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, -1, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, -1, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0165, 114, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 6, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, -1, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x00e0, -1, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ab, -1, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00a9, -1, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, -1, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 60, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 282, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, -1, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 15, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 9, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 14, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 22, CZ_SHIFT(sock));
		ADD_PKT(0x00bb, -1, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, -1, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 19, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, -1, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0073, 6, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, -1, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 34, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 54, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 18, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, -1, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00e7, 6, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, -1, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x017d, 27, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, -1, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, 6, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, 6, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0274, 4, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, -1, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x011e, -1, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, -1, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 44, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, -1, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, -1, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 2, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0098, -1, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x00e9, -1, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 30, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, -1, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, -1, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, -1, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, 6, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x0111, 6, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, 26, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, -1, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0139, 59, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 8, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, -1, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, -1, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0163, 8, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, -1, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, -1, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x01c3, 3, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 6, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, 6, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, 4, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0123, 33, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, 66, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0230, 10, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 10, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x009c, -1, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, 8, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 6, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, -1, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 30, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, -1, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, -1, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, -1, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, -1, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, -1, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 2, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 4, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, -1, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, -1, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 3, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 8, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 14, ZC_DISPEL(sock));
		ADD_PKT(0x00c0, 4, ZC_EMOTION(sock));
		ADD_PKT(0x00db, 2, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, 12, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, 2, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 6, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 10, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 11, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, -1, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, -1, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, 26, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 13, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 3, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, 9, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, 4, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 7, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 14, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f4, 282, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x0177, 282, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x009d, -1, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 8, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 3, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, -1, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 21, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x01ad, 14, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x0154, 27, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 10, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, -1, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x00b7, 12, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, -1, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, -1, ZC_MVP(sock));
		ADD_PKT(0x010a, -1, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 55, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, 53, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x008a, -1, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 32, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, -1, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0121, -1, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x019b, 4, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 31, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 6, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, -1, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 3, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 7, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 2, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, -1, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 6, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 60, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x0087, 8, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 11, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 21, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 5, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 7, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 28, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0078, 6, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, -1, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, -1, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 3, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, -1, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, -1, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, -1, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0077, 10, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, -1, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0093, -1, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 26, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, -1, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, -1, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x012d, -1, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 8, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, 2, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, -1, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, -1, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x00c6, 11, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x00ca, -1, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, -1, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x01a6, 6, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, -1, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 28, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x022e, 6, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, -1, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x013d, -1, ZC_RECOVERY(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x0207, -1, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 67, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 24, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, -1, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, -1, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, -1, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 3, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, -1, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, -1, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, -1, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 6, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00b4, 67, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, 7, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, -1, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, -1, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, -1, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010e, -1, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0120, -1, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 9, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 27, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x01ac, 10, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, -1, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 102, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, -1, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 10, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 7, ZC_STARSKILL(sock));
		ADD_PKT(0x0119, 10, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 2, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, -1, ZC_STATUS(sock));
		ADD_PKT(0x00be, -1, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 58, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, -1, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 2, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a5, 6, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 28, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, -1, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, -1, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, -1, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, -1, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, 2, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, -1, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 11, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, -1, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 10, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 2, ZC_WARPLIST(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20080610 */
