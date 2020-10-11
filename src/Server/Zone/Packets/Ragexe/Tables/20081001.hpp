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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081001
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081001

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
		ADD_PKT(0x0208, 6, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 8, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, 2, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0217, 7, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, 4, CZ_BROADCAST(sock));
		ADD_PKT(0x0118, 26, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, 4, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0102, -1, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, -1, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, -1, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, -1, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x01a1, 2, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 22, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, -1, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, 2, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, -1, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 6, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, -1, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, -1, CZ_DORIDORI(sock));
		ADD_PKT(0x00ef, 6, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 4, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, 9, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, -1, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x01d5, 21, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, 10, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x0362, 5, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, 5, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, 12, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x0237, -1, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, 13, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, 7, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 54, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, 10, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 3, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0365, -1, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 8, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 10, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, 7, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, 6, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 6, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 30, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x01ba, 5, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, 16, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, 3, CZ_REQNAME2(sock));
		ADD_PKT(0x0437, 33, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, -1, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x035f, 30, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, 8, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0360, -1, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x0170, 2, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 11, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x012a, 10, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x018a, 3, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00e4, 11, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e2, 3, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 35, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, 16, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, -1, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, 4, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0178, 14, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, -1, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x00fc, 8, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 7, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 67, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 8, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x01ae, -1, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x00b9, 20, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, 10, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00ab, -1, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, 6, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, -1, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 18, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 3, CZ_RESTART(sock));
		ADD_PKT(0x01a7, 7, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x00d0, -1, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 32, CZ_SHIFT(sock));
		ADD_PKT(0x0225, -1, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x0112, -1, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x0439, 12, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0438, -1, CZ_USE_SKILL2(sock));
		ADD_PKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, 55, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 60, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, -1, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x00ea, -1, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015e, 14, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, -1, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, 71, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, -1, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, -1, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x0274, 186, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x018f, 4, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0194, 8, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, 2, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, -1, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 39, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0110, -1, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x00e9, 102, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, -1, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 3, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 2, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, -1, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 5, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0111, 4, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, 39, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x0139, 6, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 3, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, 11, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x0163, 282, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, 58, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x009a, -1, ZC_BROADCAST(sock));
		ADD_PKT(0x00ee, -1, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x01ef, -1, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x01a4, -1, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x009c, 14, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x00b6, -1, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x01d2, 28, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, -1, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 30, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 3, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 6, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 5, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 27, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, -1, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x0105, 58, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, 2, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 15, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x00db, 4, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, 54, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 2, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 182, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, -1, ZC_FEED_PET(sock));
		ADD_PKT(0x0206, -1, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, -1, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0101, -1, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, -1, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, 8, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 6, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x016f, -1, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, 6, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x02f5, -1, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, 8, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x0177, 5, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 26, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 27, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, -1, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 32, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x00af, 16, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, 14, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, 5, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x00dd, 282, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x018c, -1, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x0196, -1, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 9, ZC_MVP(sock));
		ADD_PKT(0x010b, -1, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x00a3, -1, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x008a, -1, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 6, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 3, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x019b, -1, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0106, 10, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 2, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0199, -1, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, -1, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 8, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, -1, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 8, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, -1, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x0079, 7, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 14, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 6, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, -1, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x0087, -1, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 30, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 30, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x0114, 11, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, -1, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x01d8, 8, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x02ee, 6, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x0077, 5, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, -1, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0093, -1, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x01d4, 12, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00ca, 10, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, -1, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, 13, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, -1, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, -1, ZC_PET_ACT(sock));
		ADD_PKT(0x0160, 6, ZC_POSITION_INFO(sock));
		ADD_PKT(0x01a2, 6, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x00da, 19, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x01fc, -1, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x0207, -1, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 282, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, -1, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 10, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, 22, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x00ac, -1, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, -1, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, -1, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 2, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x0148, 81, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 10, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, 28, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00c4, 10, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 6, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 10, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, 22, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x01e1, 14, ZC_SPIRITS2(sock));
		ADD_PKT(0x01d7, 4, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x020e, 2, ZC_STARSKILL(sock));
		ADD_PKT(0x0229, 6, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 23, ZC_STATUS(sock));
		ADD_PKT(0x00be, -1, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x0088, -1, ZC_STOPMOVE(sock));
		ADD_PKT(0x00a6, 11, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, 19, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x00a5, -1, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x0224, -1, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 3, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, 2, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 10, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x016c, 8, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00c2, -1, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, -1, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 59, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, 6, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, 6, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 4, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, -1, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, 4, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081001 */
