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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081008
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081008

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
		ADD_PKT(0x00e6, 10, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0208, 3, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 28, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00e8, -1, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 26, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0218, 3, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0217, -1, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x0118, 182, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, -1, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x0361, 6, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x0102, 9, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x00b8, 10, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 8, CZ_CHOPOKGI(sock));
		ADD_PKT(0x022d, 26, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, -1, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 19, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0090, 2, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, -1, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0203, 6, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 8, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00ef, 2, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 6, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 39, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x0143, 7, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, 6, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, 30, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, -1, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 10, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x0362, -1, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x00ff, -1, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x0237, 23, CZ_KILLER_RANK(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x00f9, -1, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, -1, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x0140, -1, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, -1, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x0364, 22, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0128, -1, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, -1, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x0134, 29, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01bc, -1, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 26, CZ_RECALL_GID(sock));
		ADD_PKT(0x0161, 10, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 14, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, -1, CZ_REMOVE_AID(sock));
		ADD_PKT(0x018e, -1, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0368, -1, CZ_REQNAME2(sock));
		ADD_PKT(0x0437, -1, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0108, 11, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x035f, -1, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, -1, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, 60, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x0170, 10, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, -1, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 6, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, -1, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x0155, 81, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, 5, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x018a, -1, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x00bf, 7, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 4, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, -1, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 27, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, -1, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0149, 58, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x014f, -1, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 10, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017c, -1, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0178, -1, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x00fc, -1, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, -1, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 26, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, -1, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x00b9, 97, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x01b2, -1, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x00e0, 9, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00c1, 26, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x00a9, 6, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 8, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x00b2, 282, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 53, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 14, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x00cf, 6, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x01bb, 7, CZ_SHIFT(sock));
		ADD_PKT(0x019f, 8, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0439, 114, CZ_USE_ITEM2(sock));
		ADD_PKT(0x0366, 14, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0096, 57, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 33, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x0083, 21, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x012c, 14, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 28, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x015c, 2, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x00d6, 8, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x015e, 6, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, 2, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x017d, 53, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 6, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0274, 6, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, 2, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x018f, -1, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0195, 39, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, -1, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x018b, -1, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x00fd, 10, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, -1, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0098, 2, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 2, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x00e9, 6, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0124, -1, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, -1, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x01c4, -1, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, 8, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x0111, 6, ZC_ADD_SKILL(sock));
		ADD_PKT(0x021c, -1, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x0139, -1, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, -1, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x0147, -1, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x021b, -1, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 6, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x009a, 6, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, 186, ZC_BROADCAST2(sock));
		ADD_PKT(0x0297, 6, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x0230, 10, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x009c, -1, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x01d2, 4, ZC_COMBODELAY(sock));
		ADD_PKT(0x00ec, 20, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01ea, 11, ZC_CONGRATULATION(sock));
		ADD_PKT(0x0141, 8, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0137, 10, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 5, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0105, -1, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x00d8, -1, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, -1, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x01b9, 18, ZC_DISPEL(sock));
		ADD_PKT(0x00db, -1, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x0295, 6, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x013c, -1, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f0, 7, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 30, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 3, ZC_FEED_PET(sock));
		ADD_PKT(0x0227, 4, ZC_GAME_GUARD(sock));
		ADD_PKT(0x00fb, 28, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, -1, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x01b6, 31, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x0162, -1, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x0235, 6, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 19, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x02f4, 7, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x017b, 6, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, 6, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 2, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 6, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x00a0, -1, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x00af, -1, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0238, -1, ZC_KILLER_RANK(sock));
		ADD_PKT(0x00b1, -1, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x00dd, -1, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 33, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x018c, 58, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x010c, -1, ZC_MVP(sock));
		ADD_PKT(0x010a, 10, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x00a3, 8, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x02e1, -1, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 2, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x019b, 8, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x0117, 6, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 60, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, 32, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x0199, 67, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x0086, -1, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 3, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 55, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 13, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 4, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, -1, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, -1, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 3, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 4, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x008e, 4, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0107, 3, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, -1, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 4, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, -1, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 7, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x01d8, -1, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 6, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, -1, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007f, 2, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0091, 14, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 2, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 4, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x0142, 43, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, -1, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x00b0, 5, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x00c6, 5, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0136, 6, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 4, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a6, 30, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 12, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, 3, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, -1, ZC_POSITION_INFO(sock));
		ADD_PKT(0x022e, 17, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x01a2, 2, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x00da, -1, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x0207, 2, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 17, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x00e5, 3, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 3, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00fe, -1, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x00ac, 30, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 3, ZC_RESTART_ACK(sock));
		ADD_PKT(0x0167, 14, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, 3, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, -1, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, -1, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, -1, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00c4, -1, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, -1, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, -1, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01b3, -1, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x010f, 2, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x01ac, 5, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d0, 10, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, -1, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, 24, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, -1, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x0119, 7, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, -1, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, -1, ZC_STATUS(sock));
		ADD_PKT(0x0131, 4, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x01f0, 9, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x0224, 282, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, -1, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x01a0, -1, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 15, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x016c, -1, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x00a8, 42, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, 35, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, -1, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, -1, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x0097, 6, ZC_WHISPER(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20081008 */
