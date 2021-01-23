/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20080528
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20080528

#include "Core/Multithreading/LockedLookupTable.hpp"

#include "Default.hpp"

#include <utility>

namespace Horizon
{
namespace Zone
{
/**
 * @brief Client Packet Length Table object that stores
 * the packet length of each packet of this client version.
 * Packets with IDs already existent in the database are over-written.
 * The data is stored in a thread-safe lookup table.
 * RAII techinque ensures that the table is populated on instantiation.
 */
class ClientPacketLengthTable : public PacketLengthTable
{
public:
	ClientPacketLengthTable(std::shared_ptr<ZoneSession> s)
	: PacketLengthTable(s)
	{
#define ADD_HPKT(i, j, k) _hpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
#define ADD_TPKT(i, j, k) _tpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
		ADD_HPKT(0x00e6, -1, CZ_ACK_EXCHANGE_ITEM);
		ADD_HPKT(0x0208, 26, CZ_ACK_REQ_ADD_FRIENDS);
		ADD_HPKT(0x00c5, 10, CZ_ACK_SELECT_DEALTYPE);
		ADD_HPKT(0x00e8, 5, CZ_ADD_EXCHANGE_ITEM);
		ADD_HPKT(0x0202, -1, CZ_ADD_FRIENDS);
		ADD_HPKT(0x0217, -1, CZ_BLACKSMITH_RANK);
		ADD_HPKT(0x0099, 60, CZ_BROADCAST);
		ADD_HPKT(0x00ed, -1, CZ_CANCEL_EXCHANGE_ITEM);
		ADD_HPKT(0x0118, 8, CZ_CANCEL_LOCKON);
		ADD_HPKT(0x00de, 57, CZ_CHANGE_CHATROOM);
		ADD_HPKT(0x0361, -1, CZ_CHANGE_DIRECTION2);
		ADD_HPKT(0x019d, 2, CZ_CHANGE_EFFECTSTATE);
		ADD_HPKT(0x0102, 17, CZ_CHANGE_GROUPEXPOPTION);
		ADD_HPKT(0x00b8, -1, CZ_CHOOSE_MENU);
		ADD_HPKT(0x01ed, 4, CZ_CHOPOKGI);
		ADD_HPKT(0x0146, 10, CZ_CLOSE_DIALOG);
		ADD_HPKT(0x01a1, 7, CZ_COMMAND_PET);
		ADD_HPKT(0x00eb, -1, CZ_CONCLUDE_EXCHANGE_ITEM);
		ADD_HPKT(0x0090, -1, CZ_CONTACTNPC);
		ADD_HPKT(0x00d5, 81, CZ_CREATE_CHATROOM);
		ADD_HPKT(0x0203, 34, CZ_DELETE_FRIENDS);
		ADD_HPKT(0x00ce, 11, CZ_DISCONNECT_ALL_CHARACTER);
		ADD_HPKT(0x01e7, 39, CZ_DORIDORI);
		ADD_HPKT(0x00ef, 30, CZ_EXEC_EXCHANGE_ITEM);
		ADD_HPKT(0x00e3, 35, CZ_EXIT_ROOM);
		ADD_HPKT(0x017e, 29, CZ_GUILD_CHAT);
		ADD_HPKT(0x0143, 26, CZ_INPUT_EDITDLG);
		ADD_HPKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR);
		ADD_HPKT(0x02f6, 2, CZ_IRMAIL_LIST);
		ADD_HPKT(0x02f3, 26, CZ_IRMAIL_SEND);
		ADD_HPKT(0x013f, 2, CZ_ITEM_CREATE);
		ADD_HPKT(0x0362, -1, CZ_ITEM_PICKUP2);
		ADD_HPKT(0x0363, -1, CZ_ITEM_THROW2);
		ADD_HPKT(0x00ff, -1, CZ_JOIN_GROUP);
		ADD_HPKT(0x0237, 19, CZ_KILLER_RANK);
		ADD_HPKT(0x019c, 55, CZ_LOCALBROADCAST);
		ADD_HPKT(0x00f9, 6, CZ_MAKE_GROUP);
		ADD_HPKT(0x01e8, 53, CZ_MAKE_GROUP2);
		ADD_HPKT(0x0140, 6, CZ_MOVETO_MAP);
		ADD_HPKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2);
		ADD_HPKT(0x0127, -1, CZ_MOVE_ITEM_FROM_CART_TO_BODY);
		ADD_HPKT(0x0365, -1, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2);
		ADD_HPKT(0x0128, 11, CZ_MOVE_ITEM_FROM_STORE_TO_CART);
		ADD_HPKT(0x007d, -1, CZ_NOTIFY_ACTORINIT);
		ADD_HPKT(0x00c8, 6, CZ_PC_PURCHASE_ITEMLIST);
		ADD_HPKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC);
		ADD_HPKT(0x01bc, 7, CZ_RECALL);
		ADD_HPKT(0x01bd, 9, CZ_RECALL_GID);
		ADD_HPKT(0x0161, 6, CZ_REG_CHANGE_GUILD_POSITIONINFO);
		ADD_HPKT(0x011d, 14, CZ_REMEMBER_WARPPOINT);
		ADD_HPKT(0x01ba, -1, CZ_REMOVE_AID);
		ADD_HPKT(0x018e, 5, CZ_REQMAKINGITEM);
		ADD_HPKT(0x0368, -1, CZ_REQNAME2);
		ADD_HPKT(0x0369, -1, CZ_REQNAME_BYGID2);
		ADD_HPKT(0x0233, -1, CZ_REQUEST_ACTNPC);
		ADD_HPKT(0x0108, 11, CZ_REQUEST_CHAT_PARTY);
		ADD_HPKT(0x035f, -1, CZ_REQUEST_MOVE2);
		ADD_HPKT(0x0232, 4, CZ_REQUEST_MOVENPC);
		ADD_HPKT(0x0234, -1, CZ_REQUEST_MOVETOOWNER);
		ADD_HPKT(0x0360, -1, CZ_REQUEST_TIME2);
		ADD_HPKT(0x0170, -1, CZ_REQ_ALLY_GUILD);
		ADD_HPKT(0x015b, -1, CZ_REQ_BAN_GUILD);
		ADD_HPKT(0x0130, -1, CZ_REQ_BUY_FROMMC);
		ADD_HPKT(0x012a, 8, CZ_REQ_CARTOFF);
		ADD_HPKT(0x018a, -1, CZ_REQ_DISCONNECT);
		ADD_HPKT(0x00bf, 65, CZ_REQ_EMOTION);
		ADD_HPKT(0x00d9, 4, CZ_REQ_ENTER_ROOM);
		ADD_HPKT(0x0103, 79, CZ_REQ_EXPEL_GROUP_MEMBER);
		ADD_HPKT(0x00e2, 6, CZ_REQ_EXPEL_MEMBER);
		ADD_HPKT(0x0149, 6, CZ_REQ_GIVE_MANNER_POINT);
		ADD_HPKT(0x014f, 13, CZ_REQ_GUILD_MENU);
		ADD_HPKT(0x014d, 30, CZ_REQ_GUILD_MENUINTERFACE);
		ADD_HPKT(0x017c, 21, CZ_REQ_ITEMCOMPOSITION);
		ADD_HPKT(0x017a, 4, CZ_REQ_ITEMCOMPOSITION_LIST);
		ADD_HPKT(0x0178, 33, CZ_REQ_ITEMIDENTIFY);
		ADD_HPKT(0x01fd, 26, CZ_REQ_ITEMREPAIR);
		ADD_HPKT(0x00fc, -1, CZ_REQ_JOIN_GROUP);
		ADD_HPKT(0x0168, 282, CZ_REQ_JOIN_GUILD);
		ADD_HPKT(0x0100, 186, CZ_REQ_LEAVE_GROUP);
		ADD_HPKT(0x0159, -1, CZ_REQ_LEAVE_GUILD);
		ADD_HPKT(0x0165, 114, CZ_REQ_MAKE_GUILD);
		ADD_HPKT(0x01ae, -1, CZ_REQ_MAKINGARROW);
		ADD_HPKT(0x01b2, -1, CZ_REQ_OPENSTORE2);
		ADD_HPKT(0x00ab, 53, CZ_REQ_TAKEOFF_EQUIP);
		ADD_HPKT(0x00a9, 6, CZ_REQ_WEAR_EQUIP);
		ADD_HPKT(0x00d3, 6, CZ_REQ_WHISPER_LIST);
		ADD_HPKT(0x00b2, 2, CZ_RESTART);
		ADD_HPKT(0x01ce, 22, CZ_SELECTAUTOSPELL);
		ADD_HPKT(0x01a7, 30, CZ_SELECT_PETEGG);
		ADD_HPKT(0x011b, -1, CZ_SELECT_WARPPOINT);
		ADD_HPKT(0x00cf, 5, CZ_SETTING_WHISPER_PC);
		ADD_HPKT(0x00d0, 3, CZ_SETTING_WHISPER_STATE);
		ADD_HPKT(0x01bb, 16, CZ_SHIFT);
		ADD_HPKT(0x00bb, 10, CZ_STATUS_CHANGE);
		ADD_HPKT(0x019f, 20, CZ_TRYCAPTURE_MONSTER);
		ADD_HPKT(0x0112, 7, CZ_UPGRADE_SKILLLEVEL);
		ADD_HPKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2);
		ADD_HPKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2);
		ADD_HPKT(0x0096, 31, CZ_WHISPER);
		ADD_TPKT(0x0073, 6, ZC_ACCEPT_ENTER);
		ADD_TPKT(0x0083, -1, ZC_ACCEPT_QUIT);
		ADD_TPKT(0x012c, 58, ZC_ACK_ADDITEM_TO_CART);
		ADD_TPKT(0x00ea, 30, ZC_ACK_ADD_EXCHANGE_ITEM);
		ADD_TPKT(0x015c, -1, ZC_ACK_BAN_GUILD);
		ADD_TPKT(0x00d6, 3, ZC_ACK_CREATE_CHATROOM);
		ADD_TPKT(0x00e7, 182, ZC_ACK_EXCHANGE_ITEM);
		ADD_TPKT(0x01f5, 60, ZC_ACK_EXCHANGE_ITEM2);
		ADD_TPKT(0x017d, -1, ZC_ACK_ITEMCOMPOSITION);
		ADD_TPKT(0x0179, 5, ZC_ACK_ITEMIDENTIFY);
		ADD_TPKT(0x0188, 3, ZC_ACK_ITEMREFINING);
		ADD_TPKT(0x015a, 31, ZC_ACK_LEAVE_GUILD);
		ADD_TPKT(0x0274, 10, ZC_ACK_MAIL_RETURN);
		ADD_TPKT(0x00fa, 8, ZC_ACK_MAKE_GROUP);
		ADD_TPKT(0x011e, 6, ZC_ACK_REMEMBER_WARPPOINT);
		ADD_TPKT(0x0095, 2, ZC_ACK_REQNAME);
		ADD_TPKT(0x0195, 2, ZC_ACK_REQNAMEALL);
		ADD_TPKT(0x0194, -1, ZC_ACK_REQNAME_BYGID);
		ADD_TPKT(0x018b, 12, ZC_ACK_REQ_DISCONNECT);
		ADD_TPKT(0x00fd, 3, ZC_ACK_REQ_JOIN_GROUP);
		ADD_TPKT(0x0169, 2, ZC_ACK_REQ_JOIN_GUILD);
		ADD_TPKT(0x0110, 10, ZC_ACK_TOUSESKILL);
		ADD_TPKT(0x0098, -1, ZC_ACK_WHISPER);
		ADD_TPKT(0x013b, 5, ZC_ACTION_FAILURE);
		ADD_TPKT(0x0209, 39, ZC_ADD_FRIENDS_LIST);
		ADD_TPKT(0x0124, 32, ZC_ADD_ITEM_TO_CART);
		ADD_TPKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2);
		ADD_TPKT(0x00f4, -1, ZC_ADD_ITEM_TO_STORE);
		ADD_TPKT(0x01c4, 6, ZC_ADD_ITEM_TO_STORE2);
		ADD_TPKT(0x0104, 26, ZC_ADD_MEMBER_TO_GROUP);
		ADD_TPKT(0x01e9, 3, ZC_ADD_MEMBER_TO_GROUP2);
		ADD_TPKT(0x0111, 23, ZC_ADD_SKILL);
		ADD_TPKT(0x021c, -1, ZC_ALCHEMIST_POINT);
		ADD_TPKT(0x021a, 26, ZC_ALCHEMIST_RANK);
		ADD_TPKT(0x0147, -1, ZC_AUTORUN_SKILL);
		ADD_TPKT(0x0163, 68, ZC_BAN_LIST);
		ADD_TPKT(0x0219, 30, ZC_BLACKSMITH_RANK);
		ADD_TPKT(0x009a, -1, ZC_BROADCAST);
		ADD_TPKT(0x00ee, 18, ZC_CANCEL_EXCHANGE_ITEM);
		ADD_TPKT(0x0122, 4, ZC_CART_EQUIPMENT_ITEMLIST);
		ADD_TPKT(0x0123, 28, ZC_CART_NORMAL_ITEMLIST);
		ADD_TPKT(0x01ef, 6, ZC_CART_NORMAL_ITEMLIST2);
		ADD_TPKT(0x01a4, -1, ZC_CHANGESTATE_PET);
		ADD_TPKT(0x00df, 90, ZC_CHANGE_CHATROOM);
		ADD_TPKT(0x009c, 26, ZC_CHANGE_DIRECTION);
		ADD_TPKT(0x00b6, 11, ZC_CLOSE_DIALOG);
		ADD_TPKT(0x00f8, 2, ZC_CLOSE_STORE);
		ADD_TPKT(0x0144, 3, ZC_COMPASS);
		ADD_TPKT(0x00ec, 14, ZC_CONCLUDE_EXCHANGE_ITEM);
		ADD_TPKT(0x01ea, 2, ZC_CONGRATULATION);
		ADD_TPKT(0x0141, 18, ZC_COUPLESTATUS);
		ADD_TPKT(0x0137, 8, ZC_DELETEITEM_FROM_MCSTORE);
		ADD_TPKT(0x020a, 32, ZC_DELETE_FRIENDS);
		ADD_TPKT(0x0125, 2, ZC_DELETE_ITEM_FROM_CART);
		ADD_TPKT(0x00f6, 10, ZC_DELETE_ITEM_FROM_STORE);
		ADD_TPKT(0x0105, 6, ZC_DELETE_MEMBER_FROM_GROUP);
		ADD_TPKT(0x00d8, 5, ZC_DESTROY_ROOM);
		ADD_TPKT(0x01cf, 15, ZC_DEVOTIONLIST);
		ADD_TPKT(0x00c0, 30, ZC_EMOTION);
		ADD_TPKT(0x00db, 3, ZC_ENTER_ROOM);
		ADD_TPKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST);
		ADD_TPKT(0x013c, 8, ZC_EQUIP_ARROW);
		ADD_TPKT(0x00f0, -1, ZC_EXEC_EXCHANGE_ITEM);
		ADD_TPKT(0x022f, -1, ZC_FEED_MER);
		ADD_TPKT(0x01a3, -1, ZC_FEED_PET);
		ADD_TPKT(0x0201, 26, ZC_FRIENDS_LIST);
		ADD_TPKT(0x0227, -1, ZC_GAME_GUARD);
		ADD_TPKT(0x00fb, 4, ZC_GROUP_LIST);
		ADD_TPKT(0x01b6, 33, ZC_GUILD_INFO2);
		ADD_TPKT(0x016f, 2, ZC_GUILD_NOTICE);
		ADD_TPKT(0x0162, 66, ZC_GUILD_SKILLINFO);
		ADD_TPKT(0x0235, 12, ZC_HOSKILLINFO_LIST);
		ADD_TPKT(0x0239, 29, ZC_HOSKILLINFO_UPDATE);
		ADD_TPKT(0x02f5, -1, ZC_IRMAIL_NOTIFY);
		ADD_TPKT(0x017b, 4, ZC_ITEMCOMPOSITION_LIST);
		ADD_TPKT(0x0177, 4, ZC_ITEMIDENTIFY_LIST);
		ADD_TPKT(0x00a1, -1, ZC_ITEM_DISAPPEAR);
		ADD_TPKT(0x009d, 8, ZC_ITEM_ENTRY);
		ADD_TPKT(0x009e, 3, ZC_ITEM_FALL_ENTRY);
		ADD_TPKT(0x00a0, -1, ZC_ITEM_PICKUP_ACK);
		ADD_TPKT(0x029a, 7, ZC_ITEM_PICKUP_ACK2);
		ADD_TPKT(0x00af, 29, ZC_ITEM_THROW_ACK);
		ADD_TPKT(0x00b1, 6, ZC_LONGPAR_CHANGE);
		ADD_TPKT(0x01ad, 8, ZC_MAKINGARROW_LIST);
		ADD_TPKT(0x0154, 5, ZC_MEMBERMGR_INFO);
		ADD_TPKT(0x00dd, 7, ZC_MEMBER_EXIT);
		ADD_TPKT(0x00dc, 27, ZC_MEMBER_NEWENTRY);
		ADD_TPKT(0x00b7, -1, ZC_MENU_LIST);
		ADD_TPKT(0x018c, -1, ZC_MONSTER_INFO);
		ADD_TPKT(0x0196, 67, ZC_MSG_STATE_CHANGE);
		ADD_TPKT(0x010c, 30, ZC_MVP);
		ADD_TPKT(0x010a, 102, ZC_MVP_GETTING_ITEM);
		ADD_TPKT(0x014c, 16, ZC_MYGUILD_BASIC_INFO);
		ADD_TPKT(0x00a3, 4, ZC_NORMAL_ITEMLIST);
		ADD_TPKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2);
		ADD_TPKT(0x008a, 9, ZC_NOTIFY_ACT);
		ADD_TPKT(0x02e1, 10, ZC_NOTIFY_ACT2);
		ADD_TPKT(0x0121, 4, ZC_NOTIFY_CARTITEM_COUNTINFO);
		ADD_TPKT(0x008d, 2, ZC_NOTIFY_CHAT);
		ADD_TPKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY);
		ADD_TPKT(0x019b, 27, ZC_NOTIFY_EFFECT);
		ADD_TPKT(0x0117, 6, ZC_NOTIFY_GROUNDSKILL);
		ADD_TPKT(0x0106, -1, ZC_NOTIFY_HP_TO_GROUPM);
		ADD_TPKT(0x0075, -1, ZC_NOTIFY_INITCHAR);
		ADD_TPKT(0x0189, 24, ZC_NOTIFY_MAPINFO);
		ADD_TPKT(0x0199, 11, ZC_NOTIFY_MAPPROPERTY);
		ADD_TPKT(0x01d6, 8, ZC_NOTIFY_MAPPROPERTY2);
		ADD_TPKT(0x0086, 17, ZC_NOTIFY_MOVE);
		ADD_TPKT(0x007b, 42, ZC_NOTIFY_MOVEENTRY);
		ADD_TPKT(0x01da, -1, ZC_NOTIFY_MOVEENTRY2);
		ADD_TPKT(0x02ec, 6, ZC_NOTIFY_MOVEENTRY4);
		ADD_TPKT(0x0079, -1, ZC_NOTIFY_NEWENTRY);
		ADD_TPKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2);
		ADD_TPKT(0x022b, 7, ZC_NOTIFY_NEWENTRY3);
		ADD_TPKT(0x02ed, 97, ZC_NOTIFY_NEWENTRY4);
		ADD_TPKT(0x008e, 7, ZC_NOTIFY_PLAYERCHAT);
		ADD_TPKT(0x0087, 282, ZC_NOTIFY_PLAYERMOVE);
		ADD_TPKT(0x0107, 6, ZC_NOTIFY_POSITION_TO_GROUPM);
		ADD_TPKT(0x01eb, -1, ZC_NOTIFY_POSITION_TO_GUILDM);
		ADD_TPKT(0x019a, 6, ZC_NOTIFY_RANKING);
		ADD_TPKT(0x0114, 6, ZC_NOTIFY_SKILL);
		ADD_TPKT(0x01de, 14, ZC_NOTIFY_SKILL2);
		ADD_TPKT(0x0078, 22, ZC_NOTIFY_STANDENTRY);
		ADD_TPKT(0x01d8, 3, ZC_NOTIFY_STANDENTRY2);
		ADD_TPKT(0x02ee, 3, ZC_NOTIFY_STANDENTRY4);
		ADD_TPKT(0x007c, -1, ZC_NOTIFY_STANDENTRY_NPC);
		ADD_TPKT(0x00f2, 6, ZC_NOTIFY_STOREITEM_COUNTINFO);
		ADD_TPKT(0x007f, 13, ZC_NOTIFY_TIME);
		ADD_TPKT(0x0077, 8, ZC_NOTIFY_UPDATEPLAYER);
		ADD_TPKT(0x0080, 22, ZC_NOTIFY_VANISH);
		ADD_TPKT(0x0093, 3, ZC_NPCACK_ENABLE);
		ADD_TPKT(0x0091, 14, ZC_NPCACK_MAPMOVE);
		ADD_TPKT(0x0092, -1, ZC_NPCACK_SERVERMOVE);
		ADD_TPKT(0x01b0, 8, ZC_NPCSPRITE_CHANGE);
		ADD_TPKT(0x012d, 30, ZC_OPENSTORE);
		ADD_TPKT(0x0142, -1, ZC_OPEN_EDITDLG);
		ADD_TPKT(0x00b0, -1, ZC_PAR_CHANGE);
		ADD_TPKT(0x01ab, 6, ZC_PAR_CHANGE_USER);
		ADD_TPKT(0x0133, 8, ZC_PC_PURCHASE_ITEMLIST_FROMMC);
		ADD_TPKT(0x0136, 10, ZC_PC_PURCHASE_MYITEMLIST);
		ADD_TPKT(0x00c7, 3, ZC_PC_SELL_ITEMLIST);
		ADD_TPKT(0x01aa, -1, ZC_PET_ACT);
		ADD_TPKT(0x0166, 4, ZC_POSITION_ID_NAME_INFO);
		ADD_TPKT(0x0160, 2, ZC_POSITION_INFO);
		ADD_TPKT(0x013d, -1, ZC_RECOVERY);
		ADD_TPKT(0x01fc, 4, ZC_REPAIRITEMLIST);
		ADD_TPKT(0x0207, -1, ZC_REQ_ADD_FRIENDS);
		ADD_TPKT(0x0171, 6, ZC_REQ_ALLY_GUILD);
		ADD_TPKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM);
		ADD_TPKT(0x016a, 6, ZC_REQ_JOIN_GUILD);
		ADD_TPKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK);
		ADD_TPKT(0x00aa, 6, ZC_REQ_WEAR_EQUIP_ACK);
		ADD_TPKT(0x00b3, 6, ZC_RESTART_ACK);
		ADD_TPKT(0x0167, 26, ZC_RESULT_MAKE_GUILD);
		ADD_TPKT(0x0148, -1, ZC_RESURRECTION);
		ADD_TPKT(0x00e1, 2, ZC_ROLE_CHANGE);
		ADD_TPKT(0x00d7, 8, ZC_ROOM_NEWENTRY);
		ADD_TPKT(0x00b4, 3, ZC_SAY_DIALOG);
		ADD_TPKT(0x00c4, -1, ZC_SELECT_DEALTYPE);
		ADD_TPKT(0x00d1, 10, ZC_SETTING_WHISPER_PC);
		ADD_TPKT(0x00d2, 11, ZC_SETTING_WHISPER_STATE);
		ADD_TPKT(0x01b3, 60, ZC_SHOW_IMAGE2);
		ADD_TPKT(0x010f, -1, ZC_SKILLINFO_LIST);
		ADD_TPKT(0x010e, 2, ZC_SKILLINFO_UPDATE);
		ADD_TPKT(0x0120, 28, ZC_SKILL_DISAPPEAR);
		ADD_TPKT(0x011f, 282, ZC_SKILL_ENTRY);
		ADD_TPKT(0x01c9, 14, ZC_SKILL_ENTRY2);
		ADD_TPKT(0x01ac, -1, ZC_SKILL_UPDATE);
		ADD_TPKT(0x01d0, -1, ZC_SPIRITS);
		ADD_TPKT(0x01e1, 43, ZC_SPIRITS2);
		ADD_TPKT(0x01d7, 9, ZC_SPRITE_CHANGE2);
		ADD_TPKT(0x020e, 7, ZC_STARSKILL);
		ADD_TPKT(0x0119, 10, ZC_STATE_CHANGE);
		ADD_TPKT(0x0229, 2, ZC_STATE_CHANGE3);
		ADD_TPKT(0x00bd, -1, ZC_STATUS);
		ADD_TPKT(0x00be, 54, ZC_STATUS_CHANGE);
		ADD_TPKT(0x00bc, 14, ZC_STATUS_CHANGE_ACK);
		ADD_TPKT(0x0088, 15, ZC_STOPMOVE);
		ADD_TPKT(0x0131, -1, ZC_STORE_ENTRY);
		ADD_TPKT(0x00a6, 2, ZC_STORE_EQUIPMENT_ITEMLIST);
		ADD_TPKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2);
		ADD_TPKT(0x00a5, 28, ZC_STORE_NORMAL_ITEMLIST);
		ADD_TPKT(0x01f0, 8, ZC_STORE_NORMAL_ITEMLIST2);
		ADD_TPKT(0x0224, 9, ZC_TAEKWON_POINT);
		ADD_TPKT(0x0226, 36, ZC_TAEKWON_RANK);
		ADD_TPKT(0x01a0, 4, ZC_TRYCAPTURE_MONSTER);
		ADD_TPKT(0x016d, -1, ZC_UPDATE_CHARSTAT);
		ADD_TPKT(0x01f2, 20, ZC_UPDATE_CHARSTAT2);
		ADD_TPKT(0x016c, 54, ZC_UPDATE_GDID);
		ADD_TPKT(0x013e, 6, ZC_USESKILL_ACK);
		ADD_TPKT(0x00a8, 6, ZC_USE_ITEM_ACK);
		ADD_TPKT(0x011a, 8, ZC_USE_SKILL);
		ADD_TPKT(0x00b5, -1, ZC_WAIT_DIALOG);
		ADD_TPKT(0x011c, -1, ZC_WARPLIST);
		ADD_TPKT(0x0097, 7, ZC_WHISPER);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20080528 */