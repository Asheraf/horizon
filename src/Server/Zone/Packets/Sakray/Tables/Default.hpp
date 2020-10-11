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

#ifndef HORIZON_ZONE_PACKET_LENGTH_TABLE
#define HORIZON_ZONE_PACKET_LENGTH_TABLE

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"
#include "Default.hpp"

#include <utility>
#include <memory>

#include "Server/Zone/Packets/Structures/CZ_ACK_CASH_PASSWORD.hpp"
#include "Server/Zone/Packets/Structures/CZ_ACK_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_ACK_GAME_GUARD.hpp"
#include "Server/Zone/Packets/Structures/CZ_ACK_REQ_ADD_FRIENDS.hpp"
#include "Server/Zone/Packets/Structures/CZ_ACK_SELECT_DEALTYPE.hpp"
#include "Server/Zone/Packets/Structures/CZ_ACK_STORE_PASSWORD.hpp"
#include "Server/Zone/Packets/Structures/CZ_ACTIVE_QUEST.hpp"
#include "Server/Zone/Packets/Structures/CZ_ADD_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_ADD_FRIENDS.hpp"
#include "Server/Zone/Packets/Structures/CZ_AGREE_STARPLACE.hpp"
#include "Server/Zone/Packets/Structures/CZ_ALCHEMIST_RANK.hpp"
#include "Server/Zone/Packets/Structures/CZ_ALLY_GUILD.hpp"
#include "Server/Zone/Packets/Structures/CZ_AUCTION_ADD.hpp"
#include "Server/Zone/Packets/Structures/CZ_AUCTION_ADD_CANCEL.hpp"
#include "Server/Zone/Packets/Structures/CZ_AUCTION_ADD_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_AUCTION_BUY.hpp"
#include "Server/Zone/Packets/Structures/CZ_AUCTION_CREATE.hpp"
#include "Server/Zone/Packets/Structures/CZ_AUCTION_ITEM_SEARCH.hpp"
#include "Server/Zone/Packets/Structures/CZ_AUCTION_REQ_MY_INFO.hpp"
#include "Server/Zone/Packets/Structures/CZ_AUCTION_REQ_MY_SELL_STOP.hpp"
#include "Server/Zone/Packets/Structures/CZ_BATTLEFIELD_CHAT.hpp"
#include "Server/Zone/Packets/Structures/CZ_BLACKSMITH_RANK.hpp"
#include "Server/Zone/Packets/Structures/CZ_BOT_CHECK.hpp"
#include "Server/Zone/Packets/Structures/CZ_BROADCAST.hpp"
#include "Server/Zone/Packets/Structures/CZ_CANCEL_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_CANCEL_LOCKON.hpp"
#include "Server/Zone/Packets/Structures/CZ_CHANGE_CHATROOM.hpp"
#include "Server/Zone/Packets/Structures/CZ_CHANGE_DIRECTION.hpp"
#include "Server/Zone/Packets/Structures/CZ_CHANGE_DIRECTION2.hpp"
#include "Server/Zone/Packets/Structures/CZ_CHANGE_EFFECTSTATE.hpp"
#include "Server/Zone/Packets/Structures/CZ_CHANGE_GROUPEXPOPTION.hpp"
#include "Server/Zone/Packets/Structures/CZ_CHANGE_MAPTYPE.hpp"
#include "Server/Zone/Packets/Structures/CZ_CHOOSE_MENU.hpp"
#include "Server/Zone/Packets/Structures/CZ_CHOPOKGI.hpp"
#include "Server/Zone/Packets/Structures/CZ_CLOSE_CoreLog.hpp"
#include "Server/Zone/Packets/Structures/CZ_CLOSE_STORE.hpp"
#include "Server/Zone/Packets/Structures/CZ_CLOSE_WINDOW.hpp"
#include "Server/Zone/Packets/Structures/CZ_COMMAND_MER.hpp"
#include "Server/Zone/Packets/Structures/CZ_COMMAND_PET.hpp"
#include "Server/Zone/Packets/Structures/CZ_CONCLUDE_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_CONFIG.hpp"
#include "Server/Zone/Packets/Structures/CZ_CONTACTNPC.hpp"
#include "Server/Zone/Packets/Structures/CZ_CREATE_CHATROOM.hpp"
#include "Server/Zone/Packets/Structures/CZ_DEATH_QUESTION.hpp"
#include "Server/Zone/Packets/Structures/CZ_DELETE_FRIENDS.hpp"
#include "Server/Zone/Packets/Structures/CZ_DISCONNECT_ALL_CHARACTER.hpp"
#include "Server/Zone/Packets/Structures/CZ_DISCONNECT_CHARACTER.hpp"
#include "Server/Zone/Packets/Structures/CZ_DORIDORI.hpp"
#include "Server/Zone/Packets/Structures/CZ_ENTER.hpp"
#include "Server/Zone/Packets/Structures/CZ_ENTER2.hpp"
#include "Server/Zone/Packets/Structures/CZ_EQUIPWIN_MICROSCOPE.hpp"
#include "Server/Zone/Packets/Structures/CZ_EXEC_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_EXIT_ROOM.hpp"
#include "Server/Zone/Packets/Structures/CZ_GANGSI_RANK.hpp"
#include "Server/Zone/Packets/Structures/CZ_GUILD_CHAT.hpp"
#include "Server/Zone/Packets/Structures/CZ_GUILD_NOTICE.hpp"
#include "Server/Zone/Packets/Structures/CZ_GUILD_ZENY.hpp"
#include "Server/Zone/Packets/Structures/CZ_HUNTINGLIST.hpp"
#include "Server/Zone/Packets/Structures/CZ_INPUT_EDITDLG.hpp"
#include "Server/Zone/Packets/Structures/CZ_INPUT_EDITDLGSTR.hpp"
#include "Server/Zone/Packets/Structures/CZ_IRMAIL_LIST.hpp"
#include "Server/Zone/Packets/Structures/CZ_IRMAIL_SEND.hpp"
#include "Server/Zone/Packets/Structures/CZ_ITEM_CREATE.hpp"
#include "Server/Zone/Packets/Structures/CZ_ITEM_PICKUP.hpp"
#include "Server/Zone/Packets/Structures/CZ_ITEM_PICKUP2.hpp"
#include "Server/Zone/Packets/Structures/CZ_ITEM_PICKUP_NEW_JAPEN.hpp"
#include "Server/Zone/Packets/Structures/CZ_ITEM_THROW.hpp"
#include "Server/Zone/Packets/Structures/CZ_ITEM_THROW2.hpp"
#include "Server/Zone/Packets/Structures/CZ_JOIN_BABY.hpp"
#include "Server/Zone/Packets/Structures/CZ_JOIN_COUPLE.hpp"
#include "Server/Zone/Packets/Structures/CZ_JOIN_GROUP.hpp"
#include "Server/Zone/Packets/Structures/CZ_JOIN_GUILD.hpp"
#include "Server/Zone/Packets/Structures/CZ_KILLER_RANK.hpp"
#include "Server/Zone/Packets/Structures/CZ_KSY_EVENT.hpp"
#include "Server/Zone/Packets/Structures/CZ_LESSEFFECT.hpp"
#include "Server/Zone/Packets/Structures/CZ_LOCALBROADCAST.hpp"
#include "Server/Zone/Packets/Structures/CZ_MAIL_ADD_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_MAIL_DELETE.hpp"
#include "Server/Zone/Packets/Structures/CZ_MAIL_GET_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_MAIL_GET_LIST.hpp"
#include "Server/Zone/Packets/Structures/CZ_MAIL_OPEN.hpp"
#include "Server/Zone/Packets/Structures/CZ_MAIL_RESET_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_MAIL_SEND.hpp"
#include "Server/Zone/Packets/Structures/CZ_MAKE_GROUP.hpp"
#include "Server/Zone/Packets/Structures/CZ_MAKE_GROUP2.hpp"
#include "Server/Zone/Packets/Structures/CZ_MEMORIALDUNGEON_COMMAND.hpp"
#include "Server/Zone/Packets/Structures/CZ_MER_COMMAND.hpp"
#include "Server/Zone/Packets/Structures/CZ_MONSTER_TALK.hpp"
#include "Server/Zone/Packets/Structures/CZ_MOVETO_MAP.hpp"
#include "Server/Zone/Packets/Structures/CZ_MOVE_ITEM_FROM_BODY_TO_CART.hpp"
#include "Server/Zone/Packets/Structures/CZ_MOVE_ITEM_FROM_BODY_TO_STORE.hpp"
#include "Server/Zone/Packets/Structures/CZ_MOVE_ITEM_FROM_BODY_TO_STORE2.hpp"
#include "Server/Zone/Packets/Structures/CZ_MOVE_ITEM_FROM_CART_TO_BODY.hpp"
#include "Server/Zone/Packets/Structures/CZ_MOVE_ITEM_FROM_CART_TO_STORE.hpp"
#include "Server/Zone/Packets/Structures/CZ_MOVE_ITEM_FROM_STORE_TO_BODY.hpp"
#include "Server/Zone/Packets/Structures/CZ_MOVE_ITEM_FROM_STORE_TO_BODY2.hpp"
#include "Server/Zone/Packets/Structures/CZ_MOVE_ITEM_FROM_STORE_TO_CART.hpp"
#include "Server/Zone/Packets/Structures/CZ_NOTIFY_ACTORINIT.hpp"
#include "Server/Zone/Packets/Structures/CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/CZ_PARTY_CONFIG.hpp"
#include "Server/Zone/Packets/Structures/CZ_PARTY_JOIN_REQ.hpp"
#include "Server/Zone/Packets/Structures/CZ_PARTY_JOIN_REQ_ACK.hpp"
#include "Server/Zone/Packets/Structures/CZ_PC_BUY_CASH_POINT_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_PC_PURCHASE_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/CZ_PC_PURCHASE_ITEMLIST_FROMMC.hpp"
#include "Server/Zone/Packets/Structures/CZ_PC_SELL_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/CZ_PETEGG_INFO.hpp"
#include "Server/Zone/Packets/Structures/CZ_PET_ACT.hpp"
#include "Server/Zone/Packets/Structures/CZ_PKMODE_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/CZ_PROGRESS.hpp"
#include "Server/Zone/Packets/Structures/CZ_RECALL.hpp"
#include "Server/Zone/Packets/Structures/CZ_RECALL_GID.hpp"
#include "Server/Zone/Packets/Structures/CZ_REGISTER_GUILD_EMBLEM_IMG.hpp"
#include "Server/Zone/Packets/Structures/CZ_REG_CHANGE_GUILD_POSITIONINFO.hpp"
#include "Server/Zone/Packets/Structures/CZ_REMEMBER_WARPPOINT.hpp"
#include "Server/Zone/Packets/Structures/CZ_REMOVE_AID.hpp"
#include "Server/Zone/Packets/Structures/CZ_RENAME_MER.hpp"
#include "Server/Zone/Packets/Structures/CZ_RENAME_PET.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQMAKINGHOMUN.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQMAKINGITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQNAME.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQNAME2.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQNAME_BYGID.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQNAME_BYGID2.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_ACT.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_ACT2.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_ACTNPC.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_CHAT.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_CHAT_PARTY.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_MOVE.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_MOVE2.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_MOVENPC.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_MOVETOOWNER.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_MOVE_NEW_JAPEN.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_QUIT.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_TIME.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQUEST_TIME2.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_ACCOUNTNAME.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_ALLY_GUILD.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_BAN_GUILD.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_BUY_FROMMC.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_CARTOFF.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_CHANGECART.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_CHANGE_MEMBERPOS.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_CLOSESTORE.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_DELETE_RELATED_GUILD.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_DISCONNECT.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_DISORGANIZE_GUILD.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_EMOTION.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_ENTER_ROOM.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_EXPEL_GROUP_MEMBER.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_EXPEL_MEMBER.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_GIVE_MANNER_BYNAME.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_GIVE_MANNER_POINT.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_GUILD_EMBLEM_IMG.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_GUILD_MEMBER_INFO.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_GUILD_MENU.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_GUILD_MENUINTERFACE.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_HOSTILE_GUILD.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_ITEMCOMPOSITION.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_ITEMCOMPOSITION_LIST.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_ITEMIDENTIFY.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_ITEMREPAIR.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_JOIN_BABY.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_JOIN_COUPLE.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_JOIN_GROUP.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_JOIN_GUILD.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_LEAVE_GROUP.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_LEAVE_GUILD.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_MAIL_RETURN.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_MAKE_GUILD.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_MAKINGARROW.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_MAKINGITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_NEXT_SCRIPT.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_OPENSTORE.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_OPENSTORE2.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_OPEN_MEMBER_INFO.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_PVPPOINT.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_REMAINTIME.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_ROLE_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_STATUS.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_STATUS_GM.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_TAKEOFF_EQUIP.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_USER_COUNT.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_WEAPONREFINE.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_WEAR_EQUIP.hpp"
#include "Server/Zone/Packets/Structures/CZ_REQ_WHISPER_LIST.hpp"
#include "Server/Zone/Packets/Structures/CZ_RESET.hpp"
#include "Server/Zone/Packets/Structures/CZ_RESTART.hpp"
#include "Server/Zone/Packets/Structures/CZ_SELECTAUTOSPELL.hpp"
#include "Server/Zone/Packets/Structures/CZ_SELECT_PETEGG.hpp"
#include "Server/Zone/Packets/Structures/CZ_SELECT_WARPPOINT.hpp"
#include "Server/Zone/Packets/Structures/CZ_SETTING_WHISPER_PC.hpp"
#include "Server/Zone/Packets/Structures/CZ_SETTING_WHISPER_STATE.hpp"
#include "Server/Zone/Packets/Structures/CZ_SHIFT.hpp"
#include "Server/Zone/Packets/Structures/CZ_SHORTCUT_KEY_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/CZ_SKILL_SELECT_RESPONSE.hpp"
#include "Server/Zone/Packets/Structures/CZ_STANDING_RESURRECTION.hpp"
#include "Server/Zone/Packets/Structures/CZ_STATUS_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/CZ_TAEKWON_RANK.hpp"
#include "Server/Zone/Packets/Structures/CZ_TRYCAPTURE_MONSTER.hpp"
#include "Server/Zone/Packets/Structures/CZ_UPGRADE_SKILLLEVEL.hpp"
#include "Server/Zone/Packets/Structures/CZ_USE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/CZ_USE_ITEM2.hpp"
#include "Server/Zone/Packets/Structures/CZ_USE_ITEM_NEW_JAPEN.hpp"
#include "Server/Zone/Packets/Structures/CZ_USE_SKILL.hpp"
#include "Server/Zone/Packets/Structures/CZ_USE_SKILL2.hpp"
#include "Server/Zone/Packets/Structures/CZ_USE_SKILL_NEW_JAPEN.hpp"
#include "Server/Zone/Packets/Structures/CZ_USE_SKILL_TOGROUND.hpp"
#include "Server/Zone/Packets/Structures/CZ_USE_SKILL_TOGROUND2.hpp"
#include "Server/Zone/Packets/Structures/CZ_USE_SKILL_TOGROUND_WITHTALKBOX.hpp"
#include "Server/Zone/Packets/Structures/CZ_USE_SKILL_TOGROUND_WITHTALKBOX2.hpp"
#include "Server/Zone/Packets/Structures/CZ_WHISPER.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACCEPT_ENTER.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACCEPT_ENTER2.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACCEPT_QUIT.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_ACCOUNTNAME.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_ADDITEM_TO_CART.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_ADD_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_AUCTION_ADD_ITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_BAN_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_CHANGE_GUILD_POSITIONINFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_CREATE_CHATROOM.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_DISCONNECT_CHARACTER.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_DISORGANIZE_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_DISORGANIZE_GUILD_RESULT.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_EXCHANGE_ITEM2.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_GIVE_MANNER_POINT.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_GUILD_MEMBER_INFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_GUILD_MENUINTERFACE.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_ITEMCOMPOSITION.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_ITEMIDENTIFY.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_ITEMREFINING.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_ITEMREPAIR.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_LEAVE_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_MAIL_ADD_ITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_MAIL_DELETE.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_MAIL_RETURN.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_MAKE_GROUP.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_OPEN_MEMBER_INFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_PVPPOINT.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_REMEMBER_WARPPOINT.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_REQMAKINGITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_REQNAME.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_REQNAMEALL.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_REQNAME_BYGID.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_REQ_ALLY_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_REQ_CHANGE_MEMBERS.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_REQ_DISCONNECT.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_REQ_HOSTILE_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_REQ_JOIN_GROUP.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_REQ_JOIN_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_STATUS_GM.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_TOUSESKILL.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_WEAPONREFINE.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACK_WHISPER.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACTION_FAILURE.hpp"
#include "Server/Zone/Packets/Structures/ZC_ACTIVE_QUEST.hpp"
#include "Server/Zone/Packets/Structures/ZC_ADD_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_ADD_FRIENDS_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_ADD_ITEM_TO_CART.hpp"
#include "Server/Zone/Packets/Structures/ZC_ADD_ITEM_TO_CART2.hpp"
#include "Server/Zone/Packets/Structures/ZC_ADD_ITEM_TO_STORE.hpp"
#include "Server/Zone/Packets/Structures/ZC_ADD_ITEM_TO_STORE2.hpp"
#include "Server/Zone/Packets/Structures/ZC_ADD_MEMBER_TO_GROUP.hpp"
#include "Server/Zone/Packets/Structures/ZC_ADD_MEMBER_TO_GROUP2.hpp"
#include "Server/Zone/Packets/Structures/ZC_ADD_QUEST.hpp"
#include "Server/Zone/Packets/Structures/ZC_ADD_RELATED_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_ADD_SKILL.hpp"
#include "Server/Zone/Packets/Structures/ZC_AID.hpp"
#include "Server/Zone/Packets/Structures/ZC_ALCHEMIST_POINT.hpp"
#include "Server/Zone/Packets/Structures/ZC_ALCHEMIST_RANK.hpp"
#include "Server/Zone/Packets/Structures/ZC_ALL_QUEST_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_ALL_QUEST_MISSION.hpp"
#include "Server/Zone/Packets/Structures/ZC_ATTACK_FAILURE_FOR_DISTANCE.hpp"
#include "Server/Zone/Packets/Structures/ZC_ATTACK_RANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_AUCTION_ACK_MY_SELL_STOP.hpp"
#include "Server/Zone/Packets/Structures/ZC_AUCTION_ITEM_REQ_SEARCH.hpp"
#include "Server/Zone/Packets/Structures/ZC_AUCTION_RESULT.hpp"
#include "Server/Zone/Packets/Structures/ZC_AUCTION_WINDOWS.hpp"
#include "Server/Zone/Packets/Structures/ZC_AUTORUN_SKILL.hpp"
#include "Server/Zone/Packets/Structures/ZC_AUTOSPELLLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_BABYMSG.hpp"
#include "Server/Zone/Packets/Structures/ZC_BAN_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_BATTLEFIELD_CHAT.hpp"
#include "Server/Zone/Packets/Structures/ZC_BATTLEFIELD_NOTIFY_CAMPINFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_BATTLEFIELD_NOTIFY_HP.hpp"
#include "Server/Zone/Packets/Structures/ZC_BATTLEFIELD_NOTIFY_POINT.hpp"
#include "Server/Zone/Packets/Structures/ZC_BATTLEFIELD_NOTIFY_POSITION.hpp"
#include "Server/Zone/Packets/Structures/ZC_BLACKSMITH_POINT.hpp"
#include "Server/Zone/Packets/Structures/ZC_BLACKSMITH_RANK.hpp"
#include "Server/Zone/Packets/Structures/ZC_BLADESTOP.hpp"
#include "Server/Zone/Packets/Structures/ZC_BOSS_INFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_BROADCAST.hpp"
#include "Server/Zone/Packets/Structures/ZC_BROADCAST2.hpp"
#include "Server/Zone/Packets/Structures/ZC_CANCEL_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_CARTOFF.hpp"
#include "Server/Zone/Packets/Structures/ZC_CART_EQUIPMENT_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_CART_EQUIPMENT_ITEMLIST2.hpp"
#include "Server/Zone/Packets/Structures/ZC_CART_EQUIPMENT_ITEMLIST3.hpp"
#include "Server/Zone/Packets/Structures/ZC_CART_NORMAL_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_CART_NORMAL_ITEMLIST2.hpp"
#include "Server/Zone/Packets/Structures/ZC_CART_NORMAL_ITEMLIST3.hpp"
#include "Server/Zone/Packets/Structures/ZC_CASH_ITEM_DELETE.hpp"
#include "Server/Zone/Packets/Structures/ZC_CASH_TIME_COUNTER.hpp"
#include "Server/Zone/Packets/Structures/ZC_CHANGESTATE_MER.hpp"
#include "Server/Zone/Packets/Structures/ZC_CHANGESTATE_PET.hpp"
#include "Server/Zone/Packets/Structures/ZC_CHANGE_CHATROOM.hpp"
#include "Server/Zone/Packets/Structures/ZC_CHANGE_DIRECTION.hpp"
#include "Server/Zone/Packets/Structures/ZC_CHANGE_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_CLOSE_CoreLog.hpp"
#include "Server/Zone/Packets/Structures/ZC_CLOSE_STORE.hpp"
#include "Server/Zone/Packets/Structures/ZC_COMBODELAY.hpp"
#include "Server/Zone/Packets/Structures/ZC_COMPASS.hpp"
#include "Server/Zone/Packets/Structures/ZC_CONCLUDE_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_CONFIG.hpp"
#include "Server/Zone/Packets/Structures/ZC_CONFIG_NOTIFY.hpp"
#include "Server/Zone/Packets/Structures/ZC_CONGRATULATION.hpp"
#include "Server/Zone/Packets/Structures/ZC_COUPLENAME.hpp"
#include "Server/Zone/Packets/Structures/ZC_COUPLESTATUS.hpp"
#include "Server/Zone/Packets/Structures/ZC_DEATH_QUESTION.hpp"
#include "Server/Zone/Packets/Structures/ZC_DELETEITEM_FROM_MCSTORE.hpp"
#include "Server/Zone/Packets/Structures/ZC_DELETE_FRIENDS.hpp"
#include "Server/Zone/Packets/Structures/ZC_DELETE_ITEM_FROM_CART.hpp"
#include "Server/Zone/Packets/Structures/ZC_DELETE_ITEM_FROM_STORE.hpp"
#include "Server/Zone/Packets/Structures/ZC_DELETE_MEMBER_FROM_GROUP.hpp"
#include "Server/Zone/Packets/Structures/ZC_DELETE_RELATED_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_DEL_QUEST.hpp"
#include "Server/Zone/Packets/Structures/ZC_DESTROY_ROOM.hpp"
#include "Server/Zone/Packets/Structures/ZC_DEVOTIONLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_DISAPPEAR_ENTRY.hpp"
#include "Server/Zone/Packets/Structures/ZC_DISPEL.hpp"
#include "Server/Zone/Packets/Structures/ZC_DIVORCE.hpp"
#include "Server/Zone/Packets/Structures/ZC_EMOTION.hpp"
#include "Server/Zone/Packets/Structures/ZC_ENTER_ROOM.hpp"
#include "Server/Zone/Packets/Structures/ZC_EQUIPITEM_DAMAGED.hpp"
#include "Server/Zone/Packets/Structures/ZC_EQUIPMENT_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_EQUIPMENT_ITEMLIST2.hpp"
#include "Server/Zone/Packets/Structures/ZC_EQUIPMENT_ITEMLIST3.hpp"
#include "Server/Zone/Packets/Structures/ZC_EQUIPWIN_MICROSCOPE.hpp"
#include "Server/Zone/Packets/Structures/ZC_EQUIP_ARROW.hpp"
#include "Server/Zone/Packets/Structures/ZC_EXCHANGEITEM_UNDO.hpp"
#include "Server/Zone/Packets/Structures/ZC_EXEC_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_FEED_MER.hpp"
#include "Server/Zone/Packets/Structures/ZC_FEED_PET.hpp"
#include "Server/Zone/Packets/Structures/ZC_FORMATSTRING_MSG.hpp"
#include "Server/Zone/Packets/Structures/ZC_FRIENDS_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_FRIENDS_STATE.hpp"
#include "Server/Zone/Packets/Structures/ZC_GAME_GUARD.hpp"
#include "Server/Zone/Packets/Structures/ZC_GANGSI_POINT.hpp"
#include "Server/Zone/Packets/Structures/ZC_GANGSI_RANK.hpp"
#include "Server/Zone/Packets/Structures/ZC_GROUPINFO_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_GROUP_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_GUILD_CHAT.hpp"
#include "Server/Zone/Packets/Structures/ZC_GUILD_EMBLEM_IMG.hpp"
#include "Server/Zone/Packets/Structures/ZC_GUILD_INFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_GUILD_INFO2.hpp"
#include "Server/Zone/Packets/Structures/ZC_GUILD_MEMBER_MAP_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_GUILD_NOTICE.hpp"
#include "Server/Zone/Packets/Structures/ZC_GUILD_SKILLINFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_GUILD_ZENY_ACK.hpp"
#include "Server/Zone/Packets/Structures/ZC_HIGHJUMP.hpp"
#include "Server/Zone/Packets/Structures/ZC_HOSKILLINFO_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_HOSKILLINFO_UPDATE.hpp"
#include "Server/Zone/Packets/Structures/ZC_HUNTINGLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_INFO_REMAINTIME.hpp"
#include "Server/Zone/Packets/Structures/ZC_IRMAIL_NOTIFY.hpp"
#include "Server/Zone/Packets/Structures/ZC_IRMAIL_SEND_RES.hpp"
#include "Server/Zone/Packets/Structures/ZC_ISVR_DISCONNECT.hpp"
#include "Server/Zone/Packets/Structures/ZC_ITEMCOMPOSITION_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_ITEMIDENTIFY_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_ITEM_DISAPPEAR.hpp"
#include "Server/Zone/Packets/Structures/ZC_ITEM_ENTRY.hpp"
#include "Server/Zone/Packets/Structures/ZC_ITEM_FALL_ENTRY.hpp"
#include "Server/Zone/Packets/Structures/ZC_ITEM_PICKUP_ACK.hpp"
#include "Server/Zone/Packets/Structures/ZC_ITEM_PICKUP_ACK2.hpp"
#include "Server/Zone/Packets/Structures/ZC_ITEM_PICKUP_ACK3.hpp"
#include "Server/Zone/Packets/Structures/ZC_ITEM_PICKUP_PARTY.hpp"
#include "Server/Zone/Packets/Structures/ZC_ITEM_THROW_ACK.hpp"
#include "Server/Zone/Packets/Structures/ZC_KILLER_POINT.hpp"
#include "Server/Zone/Packets/Structures/ZC_KILLER_RANK.hpp"
#include "Server/Zone/Packets/Structures/ZC_LESSEFFECT.hpp"
#include "Server/Zone/Packets/Structures/ZC_LONGPAR_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_MAIL_RECEIVE.hpp"
#include "Server/Zone/Packets/Structures/ZC_MAIL_REQ_GET_ITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_MAIL_REQ_GET_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_MAIL_REQ_OPEN.hpp"
#include "Server/Zone/Packets/Structures/ZC_MAIL_REQ_SEND.hpp"
#include "Server/Zone/Packets/Structures/ZC_MAIL_WINDOWS.hpp"
#include "Server/Zone/Packets/Structures/ZC_MAKABLEITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_MAKINGARROW_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_MAKINGITEM_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_MAPPROPERTY.hpp"
#include "Server/Zone/Packets/Structures/ZC_MEMBERMGR_INFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_MEMBER_ADD.hpp"
#include "Server/Zone/Packets/Structures/ZC_MEMBER_EXIT.hpp"
#include "Server/Zone/Packets/Structures/ZC_MEMBER_NEWENTRY.hpp"
#include "Server/Zone/Packets/Structures/ZC_MEMORIALDUNGEON_INFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_MEMORIALDUNGEON_NOTIFY.hpp"
#include "Server/Zone/Packets/Structures/ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY.hpp"
#include "Server/Zone/Packets/Structures/ZC_MENU_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_MER_INIT.hpp"
#include "Server/Zone/Packets/Structures/ZC_MER_PAR_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_MER_PROPERTY.hpp"
#include "Server/Zone/Packets/Structures/ZC_MER_SKILLINFO_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_MER_SKILLINFO_UPDATE.hpp"
#include "Server/Zone/Packets/Structures/ZC_MILLENNIUMSHIELD.hpp"
#include "Server/Zone/Packets/Structures/ZC_MONSTER_INFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_MONSTER_TALK.hpp"
#include "Server/Zone/Packets/Structures/ZC_MSG.hpp"
#include "Server/Zone/Packets/Structures/ZC_MSG_STATE_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_MVP.hpp"
#include "Server/Zone/Packets/Structures/ZC_MVP_GETTING_ITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_MVP_GETTING_SPECIAL_EXP.hpp"
#include "Server/Zone/Packets/Structures/ZC_MYGUILD_BASIC_INFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_NORMAL_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_NORMAL_ITEMLIST2.hpp"
#include "Server/Zone/Packets/Structures/ZC_NORMAL_ITEMLIST3.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_ACT.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_ACT2.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_ACTENTRY.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_ACT_POSITION.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_BIND_ON_EQUIP.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_CARTITEM_COUNTINFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_CHAT.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_CHAT_PARTY.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_CRAZYKILLER.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_EFFECT.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_EFFECT2.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_EFFECT3.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_FONT.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_GROUNDSKILL.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_HP_TO_GROUPM.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_INITCHAR.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_MANNER_POINT_GIVEN.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_MAPINFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_MAPPROPERTY.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_MAPPROPERTY2.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_MOVE.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_MOVEENTRY.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_MOVEENTRY2.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_MOVEENTRY3.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_MOVEENTRY4.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_NEWENTRY.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_NEWENTRY2.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_NEWENTRY3.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_NEWENTRY4.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_PCBANG.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_PCBANG_PLAYING_TIME.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_PKINFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_PLAYERCHAT.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_PLAYERMOVE.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_POSITION_TO_GROUPM.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_POSITION_TO_GUILDM.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_RANKING.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_SKILL.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_SKILL2.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_SKILL_POSITION.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_STANDENTRY.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_STANDENTRY2.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_STANDENTRY3.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_STANDENTRY4.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_STANDENTRY_NPC.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_STOREITEM_COUNTINFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_TIME.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_UPDATECHAR.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_UPDATEPLAYER.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_VANISH.hpp"
#include "Server/Zone/Packets/Structures/ZC_NOTIFY_WEAPONITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_NPCACK_ENABLE.hpp"
#include "Server/Zone/Packets/Structures/ZC_NPCACK_MAPMOVE.hpp"
#include "Server/Zone/Packets/Structures/ZC_NPCACK_SERVERMOVE.hpp"
#include "Server/Zone/Packets/Structures/ZC_NPCSPRITE_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_NPC_CHAT.hpp"
#include "Server/Zone/Packets/Structures/ZC_NPC_SHOWEFST_UPDATE.hpp"
#include "Server/Zone/Packets/Structures/ZC_OPENSTORE.hpp"
#include "Server/Zone/Packets/Structures/ZC_OPEN_EDITDLG.hpp"
#include "Server/Zone/Packets/Structures/ZC_OPEN_EDITDLGSTR.hpp"
#include "Server/Zone/Packets/Structures/ZC_OTHER_GUILD_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_PARTY_CONFIG.hpp"
#include "Server/Zone/Packets/Structures/ZC_PARTY_JOIN_REQ.hpp"
#include "Server/Zone/Packets/Structures/ZC_PARTY_JOIN_REQ_ACK.hpp"
#include "Server/Zone/Packets/Structures/ZC_PAR_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_PAR_CHANGE_USER.hpp"
#include "Server/Zone/Packets/Structures/ZC_PCBANG_EFFECT.hpp"
#include "Server/Zone/Packets/Structures/ZC_PC_CASH_POINT_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_PC_CASH_POINT_UPDATE.hpp"
#include "Server/Zone/Packets/Structures/ZC_PC_PURCHASE_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_PC_PURCHASE_ITEMLIST_FROMMC.hpp"
#include "Server/Zone/Packets/Structures/ZC_PC_PURCHASE_MYITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_PC_PURCHASE_RESULT.hpp"
#include "Server/Zone/Packets/Structures/ZC_PC_PURCHASE_RESULT_FROMMC.hpp"
#include "Server/Zone/Packets/Structures/ZC_PC_SELL_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_PC_SELL_RESULT.hpp"
#include "Server/Zone/Packets/Structures/ZC_PETEGG_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_PET_ACT.hpp"
#include "Server/Zone/Packets/Structures/ZC_POSITION_ID_NAME_INFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_POSITION_INFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_PROGRESS.hpp"
#include "Server/Zone/Packets/Structures/ZC_PROGRESS_CANCEL.hpp"
#include "Server/Zone/Packets/Structures/ZC_PROPERTY_HOMUN.hpp"
#include "Server/Zone/Packets/Structures/ZC_PROPERTY_MERCE.hpp"
#include "Server/Zone/Packets/Structures/ZC_PROPERTY_PET.hpp"
#include "Server/Zone/Packets/Structures/ZC_READ_BOOK.hpp"
#include "Server/Zone/Packets/Structures/ZC_RECOVERY.hpp"
#include "Server/Zone/Packets/Structures/ZC_REFUSE_ENTER.hpp"
#include "Server/Zone/Packets/Structures/ZC_REFUSE_ENTER_ROOM.hpp"
#include "Server/Zone/Packets/Structures/ZC_REFUSE_QUIT.hpp"
#include "Server/Zone/Packets/Structures/ZC_REPAIRITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_REPLY_REMAINTIME.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_ADD_FRIENDS.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_ALLY_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_BABY.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_CASH_PASSWORD.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_COUPLE.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_EXCHANGE_ITEM2.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_ITEM_EXPLANATION_ACK.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_JOIN_GROUP.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_JOIN_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_STORE_PASSWORD.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_TAKEOFF_EQUIP_ACK.hpp"
#include "Server/Zone/Packets/Structures/ZC_REQ_WEAR_EQUIP_ACK.hpp"
#include "Server/Zone/Packets/Structures/ZC_RESTART_ACK.hpp"
#include "Server/Zone/Packets/Structures/ZC_RESULT_CASH_PASSWORD.hpp"
#include "Server/Zone/Packets/Structures/ZC_RESULT_MAKE_GUILD.hpp"
#include "Server/Zone/Packets/Structures/ZC_RESULT_STORE_PASSWORD.hpp"
#include "Server/Zone/Packets/Structures/ZC_RESURRECTION.hpp"
#include "Server/Zone/Packets/Structures/ZC_ROLE_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_ROOM_NEWENTRY.hpp"
#include "Server/Zone/Packets/Structures/ZC_SAY_CoreLog.hpp"
#include "Server/Zone/Packets/Structures/ZC_SELECT_DEALTYPE.hpp"
#include "Server/Zone/Packets/Structures/ZC_SETTING_WHISPER_PC.hpp"
#include "Server/Zone/Packets/Structures/ZC_SETTING_WHISPER_STATE.hpp"
#include "Server/Zone/Packets/Structures/ZC_SHANDA_PROTECT.hpp"
#include "Server/Zone/Packets/Structures/ZC_SHORTCUT_KEY_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_SHOWDIGIT.hpp"
#include "Server/Zone/Packets/Structures/ZC_SHOW_IMAGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_SHOW_IMAGE2.hpp"
#include "Server/Zone/Packets/Structures/ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_SKILLINFO_DELETE.hpp"
#include "Server/Zone/Packets/Structures/ZC_SKILLINFO_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_SKILLINFO_UPDATE.hpp"
#include "Server/Zone/Packets/Structures/ZC_SKILLMSG.hpp"
#include "Server/Zone/Packets/Structures/ZC_SKILL_DISAPPEAR.hpp"
#include "Server/Zone/Packets/Structures/ZC_SKILL_ENTRY.hpp"
#include "Server/Zone/Packets/Structures/ZC_SKILL_ENTRY2.hpp"
#include "Server/Zone/Packets/Structures/ZC_SKILL_POSTDELAY.hpp"
#include "Server/Zone/Packets/Structures/ZC_SKILL_POSTDELAY_LIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_SKILL_SELECT_REQUEST.hpp"
#include "Server/Zone/Packets/Structures/ZC_SKILL_UPDATE.hpp"
#include "Server/Zone/Packets/Structures/ZC_SOUND.hpp"
#include "Server/Zone/Packets/Structures/ZC_SPIRITS.hpp"
#include "Server/Zone/Packets/Structures/ZC_SPIRITS2.hpp"
#include "Server/Zone/Packets/Structures/ZC_SPRITE_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_SPRITE_CHANGE2.hpp"
#include "Server/Zone/Packets/Structures/ZC_STARPLACE.hpp"
#include "Server/Zone/Packets/Structures/ZC_STARSKILL.hpp"
#include "Server/Zone/Packets/Structures/ZC_START_BABY.hpp"
#include "Server/Zone/Packets/Structures/ZC_START_CAPTURE.hpp"
#include "Server/Zone/Packets/Structures/ZC_START_COUPLE.hpp"
#include "Server/Zone/Packets/Structures/ZC_STATE_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_STATE_CHANGE3.hpp"
#include "Server/Zone/Packets/Structures/ZC_STATUS.hpp"
#include "Server/Zone/Packets/Structures/ZC_STATUS_CHANGE.hpp"
#include "Server/Zone/Packets/Structures/ZC_STATUS_CHANGE_ACK.hpp"
#include "Server/Zone/Packets/Structures/ZC_STOPMOVE.hpp"
#include "Server/Zone/Packets/Structures/ZC_STORE_ENTRY.hpp"
#include "Server/Zone/Packets/Structures/ZC_STORE_EQUIPMENT_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_STORE_EQUIPMENT_ITEMLIST2.hpp"
#include "Server/Zone/Packets/Structures/ZC_STORE_EQUIPMENT_ITEMLIST3.hpp"
#include "Server/Zone/Packets/Structures/ZC_STORE_NORMAL_ITEMLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_STORE_NORMAL_ITEMLIST2.hpp"
#include "Server/Zone/Packets/Structures/ZC_STORE_NORMAL_ITEMLIST3.hpp"
#include "Server/Zone/Packets/Structures/ZC_TAEKWON_POINT.hpp"
#include "Server/Zone/Packets/Structures/ZC_TAEKWON_RANK.hpp"
#include "Server/Zone/Packets/Structures/ZC_TALKBOX_CHATCONTENTS.hpp"
#include "Server/Zone/Packets/Structures/ZC_THROW_MVPITEM.hpp"
#include "Server/Zone/Packets/Structures/ZC_TRYCAPTURE_MONSTER.hpp"
#include "Server/Zone/Packets/Structures/ZC_UPDATE_CHARSTAT.hpp"
#include "Server/Zone/Packets/Structures/ZC_UPDATE_CHARSTAT2.hpp"
#include "Server/Zone/Packets/Structures/ZC_UPDATE_GDID.hpp"
#include "Server/Zone/Packets/Structures/ZC_UPDATE_MAPINFO.hpp"
#include "Server/Zone/Packets/Structures/ZC_UPDATE_MISSION_HUNT.hpp"
#include "Server/Zone/Packets/Structures/ZC_USER_COUNT.hpp"
#include "Server/Zone/Packets/Structures/ZC_USESKILL_ACK.hpp"
#include "Server/Zone/Packets/Structures/ZC_USE_ITEM_ACK.hpp"
#include "Server/Zone/Packets/Structures/ZC_USE_ITEM_ACK2.hpp"
#include "Server/Zone/Packets/Structures/ZC_USE_SKILL.hpp"
#include "Server/Zone/Packets/Structures/ZC_WAIT_CoreLog.hpp"
#include "Server/Zone/Packets/Structures/ZC_WARPLIST.hpp"
#include "Server/Zone/Packets/Structures/ZC_WHISPER.hpp"
#include "Server/Zone/Packets/Structures/ZC_WHISPER_LIST.hpp"

#if CLIENT_VERSION >= 20090617
#include "20090617.hpp"
#elif CLIENT_VERSION >= 20090610
#include "20090610.hpp"
#elif CLIENT_VERSION >= 20090603
#include "20090603.hpp"
#elif CLIENT_VERSION >= 20090520
#include "20090520.hpp"
#elif CLIENT_VERSION >= 20090514
#include "20090514.hpp"
#elif CLIENT_VERSION >= 20090408
#include "20090408.hpp"
#elif CLIENT_VERSION >= 20090330
#include "20090330.hpp"
#elif CLIENT_VERSION >= 20090320
#include "20090320.hpp"
#elif CLIENT_VERSION >= 20090218
#include "20090218.hpp"
#elif CLIENT_VERSION >= 20090114
#include "20090114.hpp"
#elif CLIENT_VERSION >= 20090107
#include "20090107.hpp"
#elif CLIENT_VERSION >= 20081210
#include "20081210.hpp"
#elif CLIENT_VERSION >= 20081126
#include "20081126.hpp"
#elif CLIENT_VERSION >= 20081112
#include "20081112.hpp"
#elif CLIENT_VERSION >= 20080910
#include "20080910.hpp"
#elif CLIENT_VERSION >= 20080618
#include "20080618.hpp"
#elif CLIENT_VERSION >= 20080610
#include "20080610.hpp"
#elif CLIENT_VERSION >= 20080527
#include "20080527.hpp"
#elif CLIENT_VERSION >= 20080325
#include "20080325.hpp"
#elif CLIENT_VERSION >= 20080318
#include "20080318.hpp"
#elif CLIENT_VERSION >= 20080311
#include "20080311.hpp"
#elif CLIENT_VERSION >= 20080304
#include "20080304.hpp"
#elif CLIENT_VERSION >= 20080226
#include "20080226.hpp"
#elif CLIENT_VERSION >= 20080219
#include "20080219.hpp"
#elif CLIENT_VERSION >= 20080108
#include "20080108.hpp"
#elif CLIENT_VERSION >= 20080102
#include "20080102.hpp"
#elif CLIENT_VERSION >= 20071127
#include "20071127.hpp"
#elif CLIENT_VERSION >= 20071120
#include "20071120.hpp"
#elif CLIENT_VERSION >= 20071113
#include "20071113.hpp"
#elif CLIENT_VERSION >= 20071106
#include "20071106.hpp"
#elif CLIENT_VERSION >= 20071023
#include "20071023.hpp"
#elif CLIENT_VERSION >= 20071002
#include "20071002.hpp"
#elif CLIENT_VERSION >= 20070918
#include "20070918.hpp"
#elif CLIENT_VERSION >= 20070911
#include "20070911.hpp"
#elif CLIENT_VERSION >= 20070904
#include "20070904.hpp"
#elif CLIENT_VERSION >= 20070828
#include "20070828.hpp"
#elif CLIENT_VERSION >= 20070821
#include "20070821.hpp"
#elif CLIENT_VERSION >= 20070813
#include "20070813.hpp"
#elif CLIENT_VERSION >= 20070807
#include "20070807.hpp"
#elif CLIENT_VERSION >= 20070731
#include "20070731.hpp"
#elif CLIENT_VERSION >= 20070724
#include "20070724.hpp"
#elif CLIENT_VERSION >= 20070711
#include "20070711.hpp"
#elif CLIENT_VERSION >= 20070628
#include "20070628.hpp"
#elif CLIENT_VERSION >= 20070622
#include "20070622.hpp"
#elif CLIENT_VERSION >= 20070618
#include "20070618.hpp"
#elif CLIENT_VERSION >= 20070611
#include "20070611.hpp"
#elif CLIENT_VERSION >= 20070605
#include "20070605.hpp"
#elif CLIENT_VERSION >= 20070604
#include "20070604.hpp"
#elif CLIENT_VERSION >= 20070507
#include "20070507.hpp"
#elif CLIENT_VERSION >= 20070212
#include "20070212.hpp"
#elif CLIENT_VERSION >= 20070205
#include "20070205.hpp"
#elif CLIENT_VERSION >= 20070129
#include "20070129.hpp"
#elif CLIENT_VERSION >= 20070122
#include "20070122.hpp"
#elif CLIENT_VERSION >= 20070108
#include "20070108.hpp"
#elif CLIENT_VERSION >= 20070102
#include "20070102.hpp"
#elif CLIENT_VERSION >= 20061226
#include "20061226.hpp"
#elif CLIENT_VERSION >= 20061218
#include "20061218.hpp"
#elif CLIENT_VERSION >= 20061211
#include "20061211.hpp"
#elif CLIENT_VERSION >= 20061204
#include "20061204.hpp"
#elif CLIENT_VERSION >= 20061030
#include "20061030.hpp"
#elif CLIENT_VERSION >= 20060927
#include "20060927.hpp"
#elif CLIENT_VERSION >= 20060918
#include "20060918.hpp"
#elif CLIENT_VERSION >= 20060911
#include "20060911.hpp"
#elif CLIENT_VERSION >= 20060904
#include "20060904.hpp"
#elif CLIENT_VERSION >= 20060710
#include "20060710.hpp"
#elif CLIENT_VERSION >= 20060703
#include "20060703.hpp"
#elif CLIENT_VERSION >= 20060626
#include "20060626.hpp"
#elif CLIENT_VERSION >= 20060607
#include "20060607.hpp"
#elif CLIENT_VERSION >= 20060327
#include "20060327.hpp"
#elif CLIENT_VERSION >= 20060313
#include "20060313.hpp"
#elif CLIENT_VERSION >= 20060306
#include "20060306.hpp"
#elif CLIENT_VERSION >= 20060102
#include "20060102.hpp"
#elif CLIENT_VERSION >= 20051107
#include "20051107.hpp"
#elif CLIENT_VERSION >= 20051024
#include "20051024.hpp"
#elif CLIENT_VERSION >= 20051017
#include "20051017.hpp"
#elif CLIENT_VERSION >= 20051013
#include "20051013.hpp"
#elif CLIENT_VERSION >= 20051010
#include "20051010.hpp"
#elif CLIENT_VERSION >= 20050829
#include "20050829.hpp"
#elif CLIENT_VERSION >= 20050817
#include "20050817.hpp"
#elif CLIENT_VERSION >= 20050808
#include "20050808.hpp"
#elif CLIENT_VERSION >= 20050801
#include "20050801.hpp"
#elif CLIENT_VERSION >= 20050719
#include "20050719.hpp"
#elif CLIENT_VERSION >= 20050718
#include "20050718.hpp"
#elif CLIENT_VERSION >= 20050628
#include "20050628.hpp"
#elif CLIENT_VERSION >= 20050622
#include "20050622.hpp"
#elif CLIENT_VERSION >= 20050608
#include "20050608.hpp"
#elif CLIENT_VERSION >= 20050531
#include "20050531.hpp"
#elif CLIENT_VERSION >= 20050530
#include "20050530.hpp"
#elif CLIENT_VERSION >= 20050523
#include "20050523.hpp"
#elif CLIENT_VERSION >= 20050509
#include "20050509.hpp"
#elif CLIENT_VERSION >= 20050425
#include "20050425.hpp"
#elif CLIENT_VERSION >= 20050411
#include "20050411.hpp"
#elif CLIENT_VERSION >= 20050404
#include "20050404.hpp"
#elif CLIENT_VERSION >= 20050328
#include "20050328.hpp"
#elif CLIENT_VERSION >= 20050110
#include "20050110.hpp"
#elif CLIENT_VERSION >= 20050103
#include "20050103.hpp"
#elif CLIENT_VERSION >= 20041213
#include "20041213.hpp"
#elif CLIENT_VERSION >= 20041129
#include "20041129.hpp"
#elif CLIENT_VERSION >= 20041115
#include "20041115.hpp"
#elif CLIENT_VERSION >= 20041108
#include "20041108.hpp"
#elif CLIENT_VERSION >= 20041101
#include "20041101.hpp"
#elif CLIENT_VERSION >= 20041025
#include "20041025.hpp"
#elif CLIENT_VERSION >= 20041005
#include "20041005.hpp"
#elif CLIENT_VERSION >= 20040920
#include "20040920.hpp"
#elif CLIENT_VERSION >= 20040906
#include "20040906.hpp"
#elif CLIENT_VERSION >= 20040817
#include "20040817.hpp"
#elif CLIENT_VERSION >= 20040816
#include "20040816.hpp"
#elif CLIENT_VERSION >= 20040809
#include "20040809.hpp"
#elif CLIENT_VERSION >= 20040726
#include "20040726.hpp"
#elif CLIENT_VERSION >= 20040713
#include "20040713.hpp"
#elif CLIENT_VERSION >= 20040705
#include "20040705.hpp"
#elif CLIENT_VERSION >= 20040628
#include "20040628.hpp"
#elif CLIENT_VERSION >= 20040426
#include "20040426.hpp"
#elif CLIENT_VERSION >= 20040423
#include "20040423.hpp"
#elif CLIENT_VERSION >= 20040422
#include "20040422.hpp"
#elif CLIENT_VERSION >= 20040420
#include "20040420.hpp"
#elif CLIENT_VERSION >= 20040308
#include "20040308.hpp"
#elif CLIENT_VERSION >= 20040302
#include "20040302.hpp"
#elif CLIENT_VERSION >= 20040216
#include "20040216.hpp"
#elif CLIENT_VERSION >= 20040107
#include "20040107.hpp"
#elif CLIENT_VERSION >= 20031218
#include "20031218.hpp"
#elif CLIENT_VERSION >= 20031208
#include "20031208.hpp"
#elif CLIENT_VERSION >= 20031124
#include "20031124.hpp"
#elif CLIENT_VERSION >= 20031117
#include "20031117.hpp"
#elif CLIENT_VERSION >= 20031110
#include "20031110.hpp"
#elif CLIENT_VERSION >= 20031103
#include "20031103.hpp"
#elif CLIENT_VERSION >= 20031029
#include "20031029.hpp"
#endif

namespace Horizon
{
namespace Zone
{
/**
 * @brief Packet Length Table object that stores
 * the packet length of each packet of this client version.
 * The data is stored in a thread-safe lookup table.
 * RAII techinque ensures that the table is populated on instantiation.
 */
class PacketLengthTable
{
public:
	PacketLengthTable(std::shared_ptr<ZoneSocket> sock)
	: _socket(sock)
	{
#define ADD_PKT(i, j, k) _packet_length_table.insert(i, std::make_pair<uint16_t, NetworkPacket>(j, k))
		ADD_PKT(0x02ab, 36, CZ_ACK_CASH_PASSWORD(sock));
		ADD_PKT(0x00e6, 3, CZ_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0228, 18, CZ_ACK_GAME_GUARD(sock));
		ADD_PKT(0x0208, 14, CZ_ACK_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x00c5, 7, CZ_ACK_SELECT_DEALTYPE(sock));
		ADD_PKT(0x023b, 36, CZ_ACK_STORE_PASSWORD(sock));
		ADD_PKT(0x02b6, 7, CZ_ACTIVE_QUEST(sock));
		ADD_PKT(0x00e8, 8, CZ_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0202, 26, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x0254, 3, CZ_AGREE_STARPLACE(sock));
		ADD_PKT(0x0218, 2, CZ_ALCHEMIST_RANK(sock));
		ADD_PKT(0x0172, 10, CZ_ALLY_GUILD(sock));
		ADD_PKT(0x024d, 12, CZ_AUCTION_ADD(sock));
		ADD_PKT(0x024e, 6, CZ_AUCTION_ADD_CANCEL(sock));
		ADD_PKT(0x024c, 8, CZ_AUCTION_ADD_ITEM(sock));
		ADD_PKT(0x024f, 10, CZ_AUCTION_BUY(sock));
		ADD_PKT(0x024b, 4, CZ_AUCTION_CREATE(sock));
		ADD_PKT(0x0251, 34, CZ_AUCTION_ITEM_SEARCH(sock));
		ADD_PKT(0x025c, 4, CZ_AUCTION_REQ_MY_INFO(sock));
		ADD_PKT(0x025d, 6, CZ_AUCTION_REQ_MY_SELL_STOP(sock));
		ADD_PKT(0x02db, -1, CZ_BATTLEFIELD_CHAT(sock));
		ADD_PKT(0x0217, 2, CZ_BLACKSMITH_RANK(sock));
		ADD_PKT(0x02e6, 6, CZ_BOT_CHECK(sock));
		ADD_PKT(0x0099, -1, CZ_BROADCAST(sock));
		ADD_PKT(0x00ed, 2, CZ_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0118, 2, CZ_CANCEL_LOCKON(sock));
		ADD_PKT(0x00de, -1, CZ_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009b, 26, CZ_CHANGE_DIRECTION(sock));
		ADD_PKT(0x0361, -1, CZ_CHANGE_DIRECTION2(sock));
		ADD_PKT(0x019d, 6, CZ_CHANGE_EFFECTSTATE(sock));
		ADD_PKT(0x0102, 6, CZ_CHANGE_GROUPEXPOPTION(sock));
		ADD_PKT(0x0198, 8, CZ_CHANGE_MAPTYPE(sock));
		ADD_PKT(0x00b8, 7, CZ_CHOOSE_MENU(sock));
		ADD_PKT(0x01ed, 2, CZ_CHOPOKGI(sock));
		ADD_PKT(0x0146, 6, CZ_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f7, 2, CZ_CLOSE_STORE(sock));
		ADD_PKT(0x035e, 2, CZ_CLOSE_WINDOW(sock));
		ADD_PKT(0x022d, 5, CZ_COMMAND_MER(sock));
		ADD_PKT(0x01a1, 3, CZ_COMMAND_PET(sock));
		ADD_PKT(0x00eb, 2, CZ_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x02d8, 10, CZ_CONFIG(sock));
		ADD_PKT(0x0090, 7, CZ_CONTACTNPC(sock));
		ADD_PKT(0x00d5, -1, CZ_CREATE_CHATROOM(sock));
		ADD_PKT(0x0286, 4, CZ_DEATH_QUESTION(sock));
		ADD_PKT(0x0203, 10, CZ_DELETE_FRIENDS(sock));
		ADD_PKT(0x00ce, 2, CZ_DISCONNECT_ALL_CHARACTER(sock));
		ADD_PKT(0x00cc, 6, CZ_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x01e7, 2, CZ_DORIDORI(sock));
		ADD_PKT(0x0072, 25, CZ_ENTER(sock));
		ADD_PKT(0x0436, 19, CZ_ENTER2(sock));
		ADD_PKT(0x02d6, 6, CZ_EQUIPWIN_MICROSCOPE(sock));
		ADD_PKT(0x00ef, 2, CZ_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x00e3, 2, CZ_EXIT_ROOM(sock));
		ADD_PKT(0x0281, 4, CZ_GANGSI_RANK(sock));
		ADD_PKT(0x017e, -1, CZ_GUILD_CHAT(sock));
		ADD_PKT(0x016e, 186, CZ_GUILD_NOTICE(sock));
		ADD_PKT(0x01b7, 6, CZ_GUILD_ZENY(sock));
		ADD_PKT(0x0279, 2, CZ_HUNTINGLIST(sock));
		ADD_PKT(0x0143, 10, CZ_INPUT_EDITDLG(sock));
		ADD_PKT(0x01d5, -1, CZ_INPUT_EDITDLGSTR(sock));
		ADD_PKT(0x02f6, -1, CZ_IRMAIL_LIST(sock));
		ADD_PKT(0x02f3, -1, CZ_IRMAIL_SEND(sock));
		ADD_PKT(0x013f, 26, CZ_ITEM_CREATE(sock));
		ADD_PKT(0x009f, 14, CZ_ITEM_PICKUP(sock));
		ADD_PKT(0x0362, -1, CZ_ITEM_PICKUP2(sock));
		ADD_PKT(0x02e4, 8, CZ_ITEM_PICKUP_NEW_JAPEN(sock));
		ADD_PKT(0x00a2, 15, CZ_ITEM_THROW(sock));
		ADD_PKT(0x0363, -1, CZ_ITEM_THROW2(sock));
		ADD_PKT(0x01f7, 14, CZ_JOIN_BABY(sock));
		ADD_PKT(0x01e3, 14, CZ_JOIN_COUPLE(sock));
		ADD_PKT(0x00ff, 10, CZ_JOIN_GROUP(sock));
		ADD_PKT(0x016b, 10, CZ_JOIN_GUILD(sock));
		ADD_PKT(0x0237, 2, CZ_KILLER_RANK(sock));
		ADD_PKT(0x02a5, 8, CZ_KSY_EVENT(sock));
		ADD_PKT(0x021d, 6, CZ_LESSEFFECT(sock));
		ADD_PKT(0x019c, -1, CZ_LOCALBROADCAST(sock));
		ADD_PKT(0x0247, 8, CZ_MAIL_ADD_ITEM(sock));
		ADD_PKT(0x0243, 6, CZ_MAIL_DELETE(sock));
		ADD_PKT(0x0244, 6, CZ_MAIL_GET_ITEM(sock));
		ADD_PKT(0x023f, 2, CZ_MAIL_GET_LIST(sock));
		ADD_PKT(0x0241, 6, CZ_MAIL_OPEN(sock));
		ADD_PKT(0x0246, 4, CZ_MAIL_RESET_ITEM(sock));
		ADD_PKT(0x0248, -1, CZ_MAIL_SEND(sock));
		ADD_PKT(0x00f9, 26, CZ_MAKE_GROUP(sock));
		ADD_PKT(0x01e8, 28, CZ_MAKE_GROUP2(sock));
		ADD_PKT(0x02cf, 6, CZ_MEMORIALDUNGEON_COMMAND(sock));
		ADD_PKT(0x029f, 3, CZ_MER_COMMAND(sock));
		ADD_PKT(0x01cb, 9, CZ_MONSTER_TALK(sock));
		ADD_PKT(0x0140, 22, CZ_MOVETO_MAP(sock));
		ADD_PKT(0x0126, 8, CZ_MOVE_ITEM_FROM_BODY_TO_CART(sock));
		ADD_PKT(0x00f3, 8, CZ_MOVE_ITEM_FROM_BODY_TO_STORE(sock));
		ADD_PKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2(sock));
		ADD_PKT(0x0127, 8, CZ_MOVE_ITEM_FROM_CART_TO_BODY(sock));
		ADD_PKT(0x0129, 8, CZ_MOVE_ITEM_FROM_CART_TO_STORE(sock));
		ADD_PKT(0x00f5, 8, CZ_MOVE_ITEM_FROM_STORE_TO_BODY(sock));
		ADD_PKT(0x0365, -1, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(sock));
		ADD_PKT(0x0128, 8, CZ_MOVE_ITEM_FROM_STORE_TO_CART(sock));
		ADD_PKT(0x007d, 2, CZ_NOTIFY_ACTORINIT(sock));
		ADD_PKT(0x035c, 2, CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST(sock));
		ADD_PKT(0x02c8, 3, CZ_PARTY_CONFIG(sock));
		ADD_PKT(0x02c4, 26, CZ_PARTY_JOIN_REQ(sock));
		ADD_PKT(0x02c7, 7, CZ_PARTY_JOIN_REQ_ACK(sock));
		ADD_PKT(0x0288, 10, CZ_PC_BUY_CASH_POINT_ITEM(sock));
		ADD_PKT(0x00c8, -1, CZ_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0134, -1, CZ_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x00c9, -1, CZ_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x01a8, 4, CZ_PETEGG_INFO(sock));
		ADD_PKT(0x01a9, 6, CZ_PET_ACT(sock));
		ADD_PKT(0x0138, 3, CZ_PKMODE_CHANGE(sock));
		ADD_PKT(0x02f1, 2, CZ_PROGRESS(sock));
		ADD_PKT(0x01bc, 26, CZ_RECALL(sock));
		ADD_PKT(0x01bd, 26, CZ_RECALL_GID(sock));
		ADD_PKT(0x0153, -1, CZ_REGISTER_GUILD_EMBLEM_IMG(sock));
		ADD_PKT(0x0161, -1, CZ_REG_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x011d, 2, CZ_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x01ba, 26, CZ_REMOVE_AID(sock));
		ADD_PKT(0x0231, 26, CZ_RENAME_MER(sock));
		ADD_PKT(0x01a5, 26, CZ_RENAME_PET(sock));
		ADD_PKT(0x01ca, 3, CZ_REQMAKINGHOMUN(sock));
		ADD_PKT(0x018e, 10, CZ_REQMAKINGITEM(sock));
		ADD_PKT(0x0094, 14, CZ_REQNAME(sock));
		ADD_PKT(0x0368, -1, CZ_REQNAME2(sock));
		ADD_PKT(0x0193, 2, CZ_REQNAME_BYGID(sock));
		ADD_PKT(0x0369, -1, CZ_REQNAME_BYGID2(sock));
		ADD_PKT(0x0089, 8, CZ_REQUEST_ACT(sock));
		ADD_PKT(0x0437, 7, CZ_REQUEST_ACT2(sock));
		ADD_PKT(0x0233, 11, CZ_REQUEST_ACTNPC(sock));
		ADD_PKT(0x00f3, -1, CZ_REQUEST_CHAT(sock));
		ADD_PKT(0x0108, -1, CZ_REQUEST_CHAT_PARTY(sock));
		ADD_PKT(0x0085, 11, CZ_REQUEST_MOVE(sock));
		ADD_PKT(0x035f, -1, CZ_REQUEST_MOVE2(sock));
		ADD_PKT(0x0232, 9, CZ_REQUEST_MOVENPC(sock));
		ADD_PKT(0x0234, 6, CZ_REQUEST_MOVETOOWNER(sock));
		ADD_PKT(0x02e5, 8, CZ_REQUEST_MOVE_NEW_JAPEN(sock));
		ADD_PKT(0x0082, 2, CZ_REQUEST_QUIT(sock));
		ADD_PKT(0x00f7, 22, CZ_REQUEST_TIME(sock));
		ADD_PKT(0x0360, -1, CZ_REQUEST_TIME2(sock));
		ADD_PKT(0x01df, 6, CZ_REQ_ACCOUNTNAME(sock));
		ADD_PKT(0x0170, 14, CZ_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x015b, 54, CZ_REQ_BAN_GUILD(sock));
		ADD_PKT(0x0130, 6, CZ_REQ_BUY_FROMMC(sock));
		ADD_PKT(0x012a, 2, CZ_REQ_CARTOFF(sock));
		ADD_PKT(0x01af, 4, CZ_REQ_CHANGECART(sock));
		ADD_PKT(0x0155, -1, CZ_REQ_CHANGE_MEMBERPOS(sock));
		ADD_PKT(0x012e, 2, CZ_REQ_CLOSESTORE(sock));
		ADD_PKT(0x0183, 10, CZ_REQ_DELETE_RELATED_GUILD(sock));
		ADD_PKT(0x018a, 4, CZ_REQ_DISCONNECT(sock));
		ADD_PKT(0x015d, 42, CZ_REQ_DISORGANIZE_GUILD(sock));
		ADD_PKT(0x00bf, 3, CZ_REQ_EMOTION(sock));
		ADD_PKT(0x00d9, 14, CZ_REQ_ENTER_ROOM(sock));
		ADD_PKT(0x00e4, 6, CZ_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0103, 30, CZ_REQ_EXPEL_GROUP_MEMBER(sock));
		ADD_PKT(0x00e2, 26, CZ_REQ_EXPEL_MEMBER(sock));
		ADD_PKT(0x0212, 26, CZ_REQ_GIVE_MANNER_BYNAME(sock));
		ADD_PKT(0x0149, 9, CZ_REQ_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x0151, 6, CZ_REQ_GUILD_EMBLEM_IMG(sock));
		ADD_PKT(0x0175, 6, CZ_REQ_GUILD_MEMBER_INFO(sock));
		ADD_PKT(0x014f, 6, CZ_REQ_GUILD_MENU(sock));
		ADD_PKT(0x014d, 2, CZ_REQ_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x0180, 6, CZ_REQ_HOSTILE_GUILD(sock));
		ADD_PKT(0x017c, 6, CZ_REQ_ITEMCOMPOSITION(sock));
		ADD_PKT(0x017a, 4, CZ_REQ_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0178, 4, CZ_REQ_ITEMIDENTIFY(sock));
		ADD_PKT(0x01fd, 15, CZ_REQ_ITEMREPAIR(sock));
		ADD_PKT(0x01f9, 6, CZ_REQ_JOIN_BABY(sock));
		ADD_PKT(0x01e5, 6, CZ_REQ_JOIN_COUPLE(sock));
		ADD_PKT(0x00fc, 6, CZ_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0168, 14, CZ_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0100, 2, CZ_REQ_LEAVE_GROUP(sock));
		ADD_PKT(0x0159, 54, CZ_REQ_LEAVE_GUILD(sock));
		ADD_PKT(0x0273, 30, CZ_REQ_MAIL_RETURN(sock));
		ADD_PKT(0x0165, 30, CZ_REQ_MAKE_GUILD(sock));
		ADD_PKT(0x01ae, 4, CZ_REQ_MAKINGARROW(sock));
		ADD_PKT(0x025b, 6, CZ_REQ_MAKINGITEM(sock));
		ADD_PKT(0x00b9, 6, CZ_REQ_NEXT_SCRIPT(sock));
		ADD_PKT(0x012f, -1, CZ_REQ_OPENSTORE(sock));
		ADD_PKT(0x01b2, -1, CZ_REQ_OPENSTORE2(sock));
		ADD_PKT(0x0157, 6, CZ_REQ_OPEN_MEMBER_INFO(sock));
		ADD_PKT(0x020f, 10, CZ_REQ_PVPPOINT(sock));
		ADD_PKT(0x01c0, 2, CZ_REQ_REMAINTIME(sock));
		ADD_PKT(0x00e0, 30, CZ_REQ_ROLE_CHANGE(sock));
		ADD_PKT(0x00ba, 2, CZ_REQ_STATUS(sock));
		ADD_PKT(0x0213, 26, CZ_REQ_STATUS_GM(sock));
		ADD_PKT(0x00ab, 4, CZ_REQ_TAKEOFF_EQUIP(sock));
		ADD_PKT(0x00c1, 2, CZ_REQ_USER_COUNT(sock));
		ADD_PKT(0x0222, 6, CZ_REQ_WEAPONREFINE(sock));
		ADD_PKT(0x00a9, 6, CZ_REQ_WEAR_EQUIP(sock));
		ADD_PKT(0x00d3, 2, CZ_REQ_WHISPER_LIST(sock));
		ADD_PKT(0x0197, 4, CZ_RESET(sock));
		ADD_PKT(0x00b2, 3, CZ_RESTART(sock));
		ADD_PKT(0x01ce, 6, CZ_SELECTAUTOSPELL(sock));
		ADD_PKT(0x01a7, 4, CZ_SELECT_PETEGG(sock));
		ADD_PKT(0x011b, 20, CZ_SELECT_WARPPOINT(sock));
		ADD_PKT(0x00cf, 27, CZ_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d0, 3, CZ_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x01bb, 26, CZ_SHIFT(sock));
		ADD_PKT(0x02ba, 11, CZ_SHORTCUT_KEY_CHANGE(sock));
		ADD_PKT(0x0443, 8, CZ_SKILL_SELECT_RESPONSE(sock));
		ADD_PKT(0x0292, 2, CZ_STANDING_RESURRECTION(sock));
		ADD_PKT(0x00bb, 5, CZ_STATUS_CHANGE(sock));
		ADD_PKT(0x0225, 2, CZ_TAEKWON_RANK(sock));
		ADD_PKT(0x019f, 6, CZ_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x0112, 4, CZ_UPGRADE_SKILLLEVEL(sock));
		ADD_PKT(0x00a7, 8, CZ_USE_ITEM(sock));
		ADD_PKT(0x0439, 8, CZ_USE_ITEM2(sock));
		ADD_PKT(0x02e2, 14, CZ_USE_ITEM_NEW_JAPEN(sock));
		ADD_PKT(0x0113, 22, CZ_USE_SKILL(sock));
		ADD_PKT(0x0438, 10, CZ_USE_SKILL2(sock));
		ADD_PKT(0x02e3, 25, CZ_USE_SKILL_NEW_JAPEN(sock));
		ADD_PKT(0x0116, 10, CZ_USE_SKILL_TOGROUND(sock));
		ADD_PKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2(sock));
		ADD_PKT(0x0190, 19, CZ_USE_SKILL_TOGROUND_WITHTALKBOX(sock));
		ADD_PKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2(sock));
		ADD_PKT(0x0096, -1, CZ_WHISPER(sock));
		ADD_PKT(0x0073, 11, ZC_ACCEPT_ENTER(sock));
		ADD_PKT(0x02eb, 13, ZC_ACCEPT_ENTER2(sock));
		ADD_PKT(0x0083, 2, ZC_ACCEPT_QUIT(sock));
		ADD_PKT(0x01e0, 30, ZC_ACK_ACCOUNTNAME(sock));
		ADD_PKT(0x012c, 3, ZC_ACK_ADDITEM_TO_CART(sock));
		ADD_PKT(0x00ea, 5, ZC_ACK_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0256, 5, ZC_ACK_AUCTION_ADD_ITEM(sock));
		ADD_PKT(0x015c, 90, ZC_ACK_BAN_GUILD(sock));
		ADD_PKT(0x0174, -1, ZC_ACK_CHANGE_GUILD_POSITIONINFO(sock));
		ADD_PKT(0x00d6, 3, ZC_ACK_CREATE_CHATROOM(sock));
		ADD_PKT(0x00cd, 3, ZC_ACK_DISCONNECT_CHARACTER(sock));
		ADD_PKT(0x015f, 42, ZC_ACK_DISORGANIZE_GUILD(sock));
		ADD_PKT(0x015e, 6, ZC_ACK_DISORGANIZE_GUILD_RESULT(sock));
		ADD_PKT(0x00e7, 3, ZC_ACK_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f5, 9, ZC_ACK_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x014a, 6, ZC_ACK_GIVE_MANNER_POINT(sock));
		ADD_PKT(0x0176, 106, ZC_ACK_GUILD_MEMBER_INFO(sock));
		ADD_PKT(0x014e, 6, ZC_ACK_GUILD_MENUINTERFACE(sock));
		ADD_PKT(0x017d, 7, ZC_ACK_ITEMCOMPOSITION(sock));
		ADD_PKT(0x0179, 5, ZC_ACK_ITEMIDENTIFY(sock));
		ADD_PKT(0x0188, 8, ZC_ACK_ITEMREFINING(sock));
		ADD_PKT(0x01fe, 5, ZC_ACK_ITEMREPAIR(sock));
		ADD_PKT(0x015a, 66, ZC_ACK_LEAVE_GUILD(sock));
		ADD_PKT(0x0255, 5, ZC_ACK_MAIL_ADD_ITEM(sock));
		ADD_PKT(0x0257, 8, ZC_ACK_MAIL_DELETE(sock));
		ADD_PKT(0x0274, 8, ZC_ACK_MAIL_RETURN(sock));
		ADD_PKT(0x00fa, 3, ZC_ACK_MAKE_GROUP(sock));
		ADD_PKT(0x0158, -1, ZC_ACK_OPEN_MEMBER_INFO(sock));
		ADD_PKT(0x0210, 22, ZC_ACK_PVPPOINT(sock));
		ADD_PKT(0x011e, 3, ZC_ACK_REMEMBER_WARPPOINT(sock));
		ADD_PKT(0x018f, 6, ZC_ACK_REQMAKINGITEM(sock));
		ADD_PKT(0x0095, 30, ZC_ACK_REQNAME(sock));
		ADD_PKT(0x0195, 102, ZC_ACK_REQNAMEALL(sock));
		ADD_PKT(0x0194, 30, ZC_ACK_REQNAME_BYGID(sock));
		ADD_PKT(0x0173, 3, ZC_ACK_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x0156, -1, ZC_ACK_REQ_CHANGE_MEMBERS(sock));
		ADD_PKT(0x018b, 4, ZC_ACK_REQ_DISCONNECT(sock));
		ADD_PKT(0x0181, 3, ZC_ACK_REQ_HOSTILE_GUILD(sock));
		ADD_PKT(0x00fd, 27, ZC_ACK_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x0169, 3, ZC_ACK_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x0214, 42, ZC_ACK_STATUS_GM(sock));
		ADD_PKT(0x0110, 10, ZC_ACK_TOUSESKILL(sock));
		ADD_PKT(0x0223, 8, ZC_ACK_WEAPONREFINE(sock));
		ADD_PKT(0x0098, 3, ZC_ACK_WHISPER(sock));
		ADD_PKT(0x013b, 4, ZC_ACTION_FAILURE(sock));
		ADD_PKT(0x02b7, 7, ZC_ACTIVE_QUEST(sock));
		ADD_PKT(0x00e9, 19, ZC_ADD_EXCHANGE_ITEM(sock));
		ADD_PKT(0x0209, 36, ZC_ADD_FRIENDS_LIST(sock));
		ADD_PKT(0x0124, 21, ZC_ADD_ITEM_TO_CART(sock));
		ADD_PKT(0x01c5, 22, ZC_ADD_ITEM_TO_CART2(sock));
		ADD_PKT(0x00f4, 21, ZC_ADD_ITEM_TO_STORE(sock));
		ADD_PKT(0x01c4, 22, ZC_ADD_ITEM_TO_STORE2(sock));
		ADD_PKT(0x0104, 79, ZC_ADD_MEMBER_TO_GROUP(sock));
		ADD_PKT(0x01e9, 81, ZC_ADD_MEMBER_TO_GROUP2(sock));
		ADD_PKT(0x02b3, 107, ZC_ADD_QUEST(sock));
		ADD_PKT(0x0185, 34, ZC_ADD_RELATED_GUILD(sock));
		ADD_PKT(0x0111, 39, ZC_ADD_SKILL(sock));
		ADD_PKT(0x0283, 6, ZC_AID(sock));
		ADD_PKT(0x021c, 10, ZC_ALCHEMIST_POINT(sock));
		ADD_PKT(0x021a, 282, ZC_ALCHEMIST_RANK(sock));
		ADD_PKT(0x02b1, -1, ZC_ALL_QUEST_LIST(sock));
		ADD_PKT(0x02b2, -1, ZC_ALL_QUEST_MISSION(sock));
		ADD_PKT(0x0139, 16, ZC_ATTACK_FAILURE_FOR_DISTANCE(sock));
		ADD_PKT(0x013a, 4, ZC_ATTACK_RANGE(sock));
		ADD_PKT(0x025e, 4, ZC_AUCTION_ACK_MY_SELL_STOP(sock));
		ADD_PKT(0x0252, -1, ZC_AUCTION_ITEM_REQ_SEARCH(sock));
		ADD_PKT(0x0250, 3, ZC_AUCTION_RESULT(sock));
		ADD_PKT(0x025f, 6, ZC_AUCTION_WINDOWS(sock));
		ADD_PKT(0x0147, 39, ZC_AUTORUN_SKILL(sock));
		ADD_PKT(0x01cd, 30, ZC_AUTOSPELLLIST(sock));
		ADD_PKT(0x0216, 6, ZC_BABYMSG(sock));
		ADD_PKT(0x0163, -1, ZC_BAN_LIST(sock));
		ADD_PKT(0x02dc, -1, ZC_BATTLEFIELD_CHAT(sock));
		ADD_PKT(0x02dd, 32, ZC_BATTLEFIELD_NOTIFY_CAMPINFO(sock));
		ADD_PKT(0x02e0, 34, ZC_BATTLEFIELD_NOTIFY_HP(sock));
		ADD_PKT(0x02de, 6, ZC_BATTLEFIELD_NOTIFY_POINT(sock));
		ADD_PKT(0x02df, 36, ZC_BATTLEFIELD_NOTIFY_POSITION(sock));
		ADD_PKT(0x021b, 10, ZC_BLACKSMITH_POINT(sock));
		ADD_PKT(0x0219, 282, ZC_BLACKSMITH_RANK(sock));
		ADD_PKT(0x01d1, 14, ZC_BLADESTOP(sock));
		ADD_PKT(0x0293, 70, ZC_BOSS_INFO(sock));
		ADD_PKT(0x009a, -1, ZC_BROADCAST(sock));
		ADD_PKT(0x01c3, -1, ZC_BROADCAST2(sock));
		ADD_PKT(0x00ee, 2, ZC_CANCEL_EXCHANGE_ITEM(sock));
		ADD_PKT(0x012b, 2, ZC_CARTOFF(sock));
		ADD_PKT(0x0122, -1, ZC_CART_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0297, -1, ZC_CART_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x02d2, -1, ZC_CART_EQUIPMENT_ITEMLIST3(sock));
		ADD_PKT(0x0123, -1, ZC_CART_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ef, -1, ZC_CART_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x02e9, -1, ZC_CART_NORMAL_ITEMLIST3(sock));
		ADD_PKT(0x0299, 6, ZC_CASH_ITEM_DELETE(sock));
		ADD_PKT(0x0298, 8, ZC_CASH_TIME_COUNTER(sock));
		ADD_PKT(0x0230, 12, ZC_CHANGESTATE_MER(sock));
		ADD_PKT(0x01a4, 11, ZC_CHANGESTATE_PET(sock));
		ADD_PKT(0x00df, -1, ZC_CHANGE_CHATROOM(sock));
		ADD_PKT(0x009c, 9, ZC_CHANGE_DIRECTION(sock));
		ADD_PKT(0x01b4, 12, ZC_CHANGE_GUILD(sock));
		ADD_PKT(0x00b6, 6, ZC_CLOSE_CoreLog(sock));
		ADD_PKT(0x00f8, 2, ZC_CLOSE_STORE(sock));
		ADD_PKT(0x01d2, 10, ZC_COMBODELAY(sock));
		ADD_PKT(0x0144, 23, ZC_COMPASS(sock));
		ADD_PKT(0x00ec, 3, ZC_CONCLUDE_EXCHANGE_ITEM(sock));
		ADD_PKT(0x02d9, 10, ZC_CONFIG(sock));
		ADD_PKT(0x02da, 3, ZC_CONFIG_NOTIFY(sock));
		ADD_PKT(0x01ea, 6, ZC_CONGRATULATION(sock));
		ADD_PKT(0x01e6, 26, ZC_COUPLENAME(sock));
		ADD_PKT(0x0141, 14, ZC_COUPLESTATUS(sock));
		ADD_PKT(0x0285, 6, ZC_DEATH_QUESTION(sock));
		ADD_PKT(0x0137, 6, ZC_DELETEITEM_FROM_MCSTORE(sock));
		ADD_PKT(0x020a, 10, ZC_DELETE_FRIENDS(sock));
		ADD_PKT(0x0125, 8, ZC_DELETE_ITEM_FROM_CART(sock));
		ADD_PKT(0x00f6, 8, ZC_DELETE_ITEM_FROM_STORE(sock));
		ADD_PKT(0x0105, 31, ZC_DELETE_MEMBER_FROM_GROUP(sock));
		ADD_PKT(0x0184, 10, ZC_DELETE_RELATED_GUILD(sock));
		ADD_PKT(0x02b4, 6, ZC_DEL_QUEST(sock));
		ADD_PKT(0x00d8, 6, ZC_DESTROY_ROOM(sock));
		ADD_PKT(0x01cf, 28, ZC_DEVOTIONLIST(sock));
		ADD_PKT(0x0132, 6, ZC_DISAPPEAR_ENTRY(sock));
		ADD_PKT(0x01b9, 6, ZC_DISPEL(sock));
		ADD_PKT(0x0205, 26, ZC_DIVORCE(sock));
		ADD_PKT(0x00c0, 7, ZC_EMOTION(sock));
		ADD_PKT(0x00db, -1, ZC_ENTER_ROOM(sock));
		ADD_PKT(0x02bb, 8, ZC_EQUIPITEM_DAMAGED(sock));
		ADD_PKT(0x00a4, -1, ZC_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0295, -1, ZC_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x02d0, -1, ZC_EQUIPMENT_ITEMLIST3(sock));
		ADD_PKT(0x02d7, -1, ZC_EQUIPWIN_MICROSCOPE(sock));
		ADD_PKT(0x013c, 4, ZC_EQUIP_ARROW(sock));
		ADD_PKT(0x00f1, 2, ZC_EXCHANGEITEM_UNDO(sock));
		ADD_PKT(0x00f0, 3, ZC_EXEC_EXCHANGE_ITEM(sock));
		ADD_PKT(0x022f, 5, ZC_FEED_MER(sock));
		ADD_PKT(0x01a3, 5, ZC_FEED_PET(sock));
		ADD_PKT(0x02c2, -1, ZC_FORMATSTRING_MSG(sock));
		ADD_PKT(0x0201, -1, ZC_FRIENDS_LIST(sock));
		ADD_PKT(0x0206, 11, ZC_FRIENDS_STATE(sock));
		ADD_PKT(0x0227, 18, ZC_GAME_GUARD(sock));
		ADD_PKT(0x0280, 12, ZC_GANGSI_POINT(sock));
		ADD_PKT(0x0282, 284, ZC_GANGSI_RANK(sock));
		ADD_PKT(0x0101, 6, ZC_GROUPINFO_CHANGE(sock));
		ADD_PKT(0x00fb, -1, ZC_GROUP_LIST(sock));
		ADD_PKT(0x017f, -1, ZC_GUILD_CHAT(sock));
		ADD_PKT(0x0152, -1, ZC_GUILD_EMBLEM_IMG(sock));
		ADD_PKT(0x0150, 110, ZC_GUILD_INFO(sock));
		ADD_PKT(0x01b6, 114, ZC_GUILD_INFO2(sock));
		ADD_PKT(0x01ec, 26, ZC_GUILD_MEMBER_MAP_CHANGE(sock));
		ADD_PKT(0x016f, 182, ZC_GUILD_NOTICE(sock));
		ADD_PKT(0x0162, -1, ZC_GUILD_SKILLINFO(sock));
		ADD_PKT(0x01b8, 3, ZC_GUILD_ZENY_ACK(sock));
		ADD_PKT(0x01ff, 10, ZC_HIGHJUMP(sock));
		ADD_PKT(0x0235, -1, ZC_HOSKILLINFO_LIST(sock));
		ADD_PKT(0x0239, 11, ZC_HOSKILLINFO_UPDATE(sock));
		ADD_PKT(0x027a, -1, ZC_HUNTINGLIST(sock));
		ADD_PKT(0x01c2, 10, ZC_INFO_REMAINTIME(sock));
		ADD_PKT(0x02f5, -1, ZC_IRMAIL_NOTIFY(sock));
		ADD_PKT(0x02f4, -1, ZC_IRMAIL_SEND_RES(sock));
		ADD_PKT(0x02d5, 2, ZC_ISVR_DISCONNECT(sock));
		ADD_PKT(0x017b, -1, ZC_ITEMCOMPOSITION_LIST(sock));
		ADD_PKT(0x0177, -1, ZC_ITEMIDENTIFY_LIST(sock));
		ADD_PKT(0x00a1, 6, ZC_ITEM_DISAPPEAR(sock));
		ADD_PKT(0x009d, 17, ZC_ITEM_ENTRY(sock));
		ADD_PKT(0x009e, 17, ZC_ITEM_FALL_ENTRY(sock));
		ADD_PKT(0x00a0, 23, ZC_ITEM_PICKUP_ACK(sock));
		ADD_PKT(0x029a, 27, ZC_ITEM_PICKUP_ACK2(sock));
		ADD_PKT(0x02d4, 29, ZC_ITEM_PICKUP_ACK3(sock));
		ADD_PKT(0x02b8, 22, ZC_ITEM_PICKUP_PARTY(sock));
		ADD_PKT(0x00af, 6, ZC_ITEM_THROW_ACK(sock));
		ADD_PKT(0x0236, 10, ZC_KILLER_POINT(sock));
		ADD_PKT(0x0238, 282, ZC_KILLER_RANK(sock));
		ADD_PKT(0x021e, 6, ZC_LESSEFFECT(sock));
		ADD_PKT(0x00b1, 8, ZC_LONGPAR_CHANGE(sock));
		ADD_PKT(0x024a, 70, ZC_MAIL_RECEIVE(sock));
		ADD_PKT(0x0245, 3, ZC_MAIL_REQ_GET_ITEM(sock));
		ADD_PKT(0x0240, -1, ZC_MAIL_REQ_GET_LIST(sock));
		ADD_PKT(0x0242, -1, ZC_MAIL_REQ_OPEN(sock));
		ADD_PKT(0x0249, 3, ZC_MAIL_REQ_SEND(sock));
		ADD_PKT(0x0260, 6, ZC_MAIL_WINDOWS(sock));
		ADD_PKT(0x018d, -1, ZC_MAKABLEITEMLIST(sock));
		ADD_PKT(0x01ad, -1, ZC_MAKINGARROW_LIST(sock));
		ADD_PKT(0x025a, -1, ZC_MAKINGITEM_LIST(sock));
		ADD_PKT(0x02e7, -1, ZC_MAPPROPERTY(sock));
		ADD_PKT(0x0154, -1, ZC_MEMBERMGR_INFO(sock));
		ADD_PKT(0x0182, 106, ZC_MEMBER_ADD(sock));
		ADD_PKT(0x00dd, 29, ZC_MEMBER_EXIT(sock));
		ADD_PKT(0x00dc, 28, ZC_MEMBER_NEWENTRY(sock));
		ADD_PKT(0x02cd, 71, ZC_MEMORIALDUNGEON_INFO(sock));
		ADD_PKT(0x02ce, 10, ZC_MEMORIALDUNGEON_NOTIFY(sock));
		ADD_PKT(0x02cb, 65, ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO(sock));
		ADD_PKT(0x02cc, 4, ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(sock));
		ADD_PKT(0x00b7, -1, ZC_MENU_LIST(sock));
		ADD_PKT(0x029b, 80, ZC_MER_INIT(sock));
		ADD_PKT(0x02a2, 8, ZC_MER_PAR_CHANGE(sock));
		ADD_PKT(0x029c, 66, ZC_MER_PROPERTY(sock));
		ADD_PKT(0x029d, -1, ZC_MER_SKILLINFO_LIST(sock));
		ADD_PKT(0x029e, 11, ZC_MER_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0440, 10, ZC_MILLENNIUMSHIELD(sock));
		ADD_PKT(0x018c, 29, ZC_MONSTER_INFO(sock));
		ADD_PKT(0x01cc, 9, ZC_MONSTER_TALK(sock));
		ADD_PKT(0x0291, 4, ZC_MSG(sock));
		ADD_PKT(0x0196, 9, ZC_MSG_STATE_CHANGE(sock));
		ADD_PKT(0x010c, 6, ZC_MVP(sock));
		ADD_PKT(0x010a, 4, ZC_MVP_GETTING_ITEM(sock));
		ADD_PKT(0x010b, 6, ZC_MVP_GETTING_SPECIAL_EXP(sock));
		ADD_PKT(0x014c, -1, ZC_MYGUILD_BASIC_INFO(sock));
		ADD_PKT(0x00a3, -1, ZC_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01ee, -1, ZC_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x02e8, -1, ZC_NORMAL_ITEMLIST3(sock));
		ADD_PKT(0x008a, 29, ZC_NOTIFY_ACT(sock));
		ADD_PKT(0x02e1, 33, ZC_NOTIFY_ACT2(sock));
		ADD_PKT(0x007a, 58, ZC_NOTIFY_ACTENTRY(sock));
		ADD_PKT(0x008b, 23, ZC_NOTIFY_ACT_POSITION(sock));
		ADD_PKT(0x02d3, 4, ZC_NOTIFY_BIND_ON_EQUIP(sock));
		ADD_PKT(0x0121, 14, ZC_NOTIFY_CARTITEM_COUNTINFO(sock));
		ADD_PKT(0x008d, -1, ZC_NOTIFY_CHAT(sock));
		ADD_PKT(0x0109, -1, ZC_NOTIFY_CHAT_PARTY(sock));
		ADD_PKT(0x0220, 10, ZC_NOTIFY_CRAZYKILLER(sock));
		ADD_PKT(0x019b, 10, ZC_NOTIFY_EFFECT(sock));
		ADD_PKT(0x01f3, 10, ZC_NOTIFY_EFFECT2(sock));
		ADD_PKT(0x0284, 14, ZC_NOTIFY_EFFECT3(sock));
		ADD_PKT(0x02ef, 8, ZC_NOTIFY_FONT(sock));
		ADD_PKT(0x0117, 18, ZC_NOTIFY_GROUNDSKILL(sock));
		ADD_PKT(0x0106, 10, ZC_NOTIFY_HP_TO_GROUPM(sock));
		ADD_PKT(0x0075, -1, ZC_NOTIFY_INITCHAR(sock));
		ADD_PKT(0x014b, 27, ZC_NOTIFY_MANNER_POINT_GIVEN(sock));
		ADD_PKT(0x0189, 4, ZC_NOTIFY_MAPINFO(sock));
		ADD_PKT(0x0199, 4, ZC_NOTIFY_MAPPROPERTY(sock));
		ADD_PKT(0x01d6, 4, ZC_NOTIFY_MAPPROPERTY2(sock));
		ADD_PKT(0x0086, 16, ZC_NOTIFY_MOVE(sock));
		ADD_PKT(0x007b, 60, ZC_NOTIFY_MOVEENTRY(sock));
		ADD_PKT(0x01da, 60, ZC_NOTIFY_MOVEENTRY2(sock));
		ADD_PKT(0x022c, 65, ZC_NOTIFY_MOVEENTRY3(sock));
		ADD_PKT(0x02ec, 67, ZC_NOTIFY_MOVEENTRY4(sock));
		ADD_PKT(0x0079, 53, ZC_NOTIFY_NEWENTRY(sock));
		ADD_PKT(0x01d9, 53, ZC_NOTIFY_NEWENTRY2(sock));
		ADD_PKT(0x022b, 57, ZC_NOTIFY_NEWENTRY3(sock));
		ADD_PKT(0x02ed, 59, ZC_NOTIFY_NEWENTRY4(sock));
		ADD_PKT(0x0278, 2, ZC_NOTIFY_PCBANG(sock));
		ADD_PKT(0x02bc, 6, ZC_NOTIFY_PCBANG_PLAYING_TIME(sock));
		ADD_PKT(0x021f, 66, ZC_NOTIFY_PKINFO(sock));
		ADD_PKT(0x008e, -1, ZC_NOTIFY_PLAYERCHAT(sock));
		ADD_PKT(0x0087, 12, ZC_NOTIFY_PLAYERMOVE(sock));
		ADD_PKT(0x0107, 10, ZC_NOTIFY_POSITION_TO_GROUPM(sock));
		ADD_PKT(0x01eb, 10, ZC_NOTIFY_POSITION_TO_GUILDM(sock));
		ADD_PKT(0x019a, 14, ZC_NOTIFY_RANKING(sock));
		ADD_PKT(0x0114, 31, ZC_NOTIFY_SKILL(sock));
		ADD_PKT(0x01de, 33, ZC_NOTIFY_SKILL2(sock));
		ADD_PKT(0x0115, 35, ZC_NOTIFY_SKILL_POSITION(sock));
		ADD_PKT(0x0078, 55, ZC_NOTIFY_STANDENTRY(sock));
		ADD_PKT(0x01d8, 54, ZC_NOTIFY_STANDENTRY2(sock));
		ADD_PKT(0x022a, 58, ZC_NOTIFY_STANDENTRY3(sock));
		ADD_PKT(0x02ee, 60, ZC_NOTIFY_STANDENTRY4(sock));
		ADD_PKT(0x007c, 42, ZC_NOTIFY_STANDENTRY_NPC(sock));
		ADD_PKT(0x00f2, 6, ZC_NOTIFY_STOREITEM_COUNTINFO(sock));
		ADD_PKT(0x007f, 6, ZC_NOTIFY_TIME(sock));
		ADD_PKT(0x0076, 9, ZC_NOTIFY_UPDATECHAR(sock));
		ADD_PKT(0x0077, 5, ZC_NOTIFY_UPDATEPLAYER(sock));
		ADD_PKT(0x0080, 7, ZC_NOTIFY_VANISH(sock));
		ADD_PKT(0x0221, -1, ZC_NOTIFY_WEAPONITEMLIST(sock));
		ADD_PKT(0x0093, 2, ZC_NPCACK_ENABLE(sock));
		ADD_PKT(0x0091, 22, ZC_NPCACK_MAPMOVE(sock));
		ADD_PKT(0x0092, 28, ZC_NPCACK_SERVERMOVE(sock));
		ADD_PKT(0x01b0, 11, ZC_NPCSPRITE_CHANGE(sock));
		ADD_PKT(0x02c1, -1, ZC_NPC_CHAT(sock));
		ADD_PKT(0x028a, 18, ZC_NPC_SHOWEFST_UPDATE(sock));
		ADD_PKT(0x012d, 4, ZC_OPENSTORE(sock));
		ADD_PKT(0x0142, 6, ZC_OPEN_EDITDLG(sock));
		ADD_PKT(0x01d4, 6, ZC_OPEN_EDITDLGSTR(sock));
		ADD_PKT(0x0164, -1, ZC_OTHER_GUILD_LIST(sock));
		ADD_PKT(0x02c9, 3, ZC_PARTY_CONFIG(sock));
		ADD_PKT(0x02c6, 30, ZC_PARTY_JOIN_REQ(sock));
		ADD_PKT(0x02c5, 30, ZC_PARTY_JOIN_REQ_ACK(sock));
		ADD_PKT(0x00b0, 8, ZC_PAR_CHANGE(sock));
		ADD_PKT(0x01ab, 12, ZC_PAR_CHANGE_USER(sock));
		ADD_PKT(0x027b, 14, ZC_PCBANG_EFFECT(sock));
		ADD_PKT(0x0287, -1, ZC_PC_CASH_POINT_ITEMLIST(sock));
		ADD_PKT(0x0289, 12, ZC_PC_CASH_POINT_UPDATE(sock));
		ADD_PKT(0x00c6, -1, ZC_PC_PURCHASE_ITEMLIST(sock));
		ADD_PKT(0x0133, -1, ZC_PC_PURCHASE_ITEMLIST_FROMMC(sock));
		ADD_PKT(0x0136, -1, ZC_PC_PURCHASE_MYITEMLIST(sock));
		ADD_PKT(0x00ca, 3, ZC_PC_PURCHASE_RESULT(sock));
		ADD_PKT(0x0135, 7, ZC_PC_PURCHASE_RESULT_FROMMC(sock));
		ADD_PKT(0x00c7, -1, ZC_PC_SELL_ITEMLIST(sock));
		ADD_PKT(0x00cb, 3, ZC_PC_SELL_RESULT(sock));
		ADD_PKT(0x01a6, -1, ZC_PETEGG_LIST(sock));
		ADD_PKT(0x01aa, 10, ZC_PET_ACT(sock));
		ADD_PKT(0x0166, -1, ZC_POSITION_ID_NAME_INFO(sock));
		ADD_PKT(0x0160, -1, ZC_POSITION_INFO(sock));
		ADD_PKT(0x02f0, 10, ZC_PROGRESS(sock));
		ADD_PKT(0x02f2, 2, ZC_PROGRESS_CANCEL(sock));
		ADD_PKT(0x022e, 71, ZC_PROPERTY_HOMUN(sock));
		ADD_PKT(0x027d, 62, ZC_PROPERTY_MERCE(sock));
		ADD_PKT(0x01a2, 37, ZC_PROPERTY_PET(sock));
		ADD_PKT(0x0294, 10, ZC_READ_BOOK(sock));
		ADD_PKT(0x013d, 6, ZC_RECOVERY(sock));
		ADD_PKT(0x0074, 3, ZC_REFUSE_ENTER(sock));
		ADD_PKT(0x00da, 3, ZC_REFUSE_ENTER_ROOM(sock));
		ADD_PKT(0x0084, 2, ZC_REFUSE_QUIT(sock));
		ADD_PKT(0x01fc, -1, ZC_REPAIRITEMLIST(sock));
		ADD_PKT(0x01c1, 14, ZC_REPLY_REMAINTIME(sock));
		ADD_PKT(0x0207, 34, ZC_REQ_ADD_FRIENDS(sock));
		ADD_PKT(0x0171, 30, ZC_REQ_ALLY_GUILD(sock));
		ADD_PKT(0x01f6, 34, ZC_REQ_BABY(sock));
		ADD_PKT(0x02aa, 4, ZC_REQ_CASH_PASSWORD(sock));
		ADD_PKT(0x01e2, 34, ZC_REQ_COUPLE(sock));
		ADD_PKT(0x00e5, 26, ZC_REQ_EXCHANGE_ITEM(sock));
		ADD_PKT(0x01f4, 32, ZC_REQ_EXCHANGE_ITEM2(sock));
		ADD_PKT(0x00ae, -1, ZC_REQ_ITEM_EXPLANATION_ACK(sock));
		ADD_PKT(0x00fe, 30, ZC_REQ_JOIN_GROUP(sock));
		ADD_PKT(0x016a, 30, ZC_REQ_JOIN_GUILD(sock));
		ADD_PKT(0x023a, 4, ZC_REQ_STORE_PASSWORD(sock));
		ADD_PKT(0x00ac, 7, ZC_REQ_TAKEOFF_EQUIP_ACK(sock));
		ADD_PKT(0x00aa, 7, ZC_REQ_WEAR_EQUIP_ACK(sock));
		ADD_PKT(0x00b3, 3, ZC_RESTART_ACK(sock));
		ADD_PKT(0x02ac, 6, ZC_RESULT_CASH_PASSWORD(sock));
		ADD_PKT(0x0167, 3, ZC_RESULT_MAKE_GUILD(sock));
		ADD_PKT(0x023c, 6, ZC_RESULT_STORE_PASSWORD(sock));
		ADD_PKT(0x0148, 8, ZC_RESURRECTION(sock));
		ADD_PKT(0x00e1, 30, ZC_ROLE_CHANGE(sock));
		ADD_PKT(0x00d7, -1, ZC_ROOM_NEWENTRY(sock));
		ADD_PKT(0x00b4, -1, ZC_SAY_CoreLog(sock));
		ADD_PKT(0x00c4, 6, ZC_SELECT_DEALTYPE(sock));
		ADD_PKT(0x00d1, 4, ZC_SETTING_WHISPER_PC(sock));
		ADD_PKT(0x00d2, 4, ZC_SETTING_WHISPER_STATE(sock));
		ADD_PKT(0x027e, -1, ZC_SHANDA_PROTECT(sock));
		ADD_PKT(0x02b9, 191, ZC_SHORTCUT_KEY_LIST(sock));
		ADD_PKT(0x01b1, 7, ZC_SHOWDIGIT(sock));
		ADD_PKT(0x0145, 19, ZC_SHOW_IMAGE(sock));
		ADD_PKT(0x01b3, 67, ZC_SHOW_IMAGE2(sock));
		ADD_PKT(0x035d, -1, ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST(sock));
		ADD_PKT(0x0441, 4, ZC_SKILLINFO_DELETE(sock));
		ADD_PKT(0x010f, -1, ZC_SKILLINFO_LIST(sock));
		ADD_PKT(0x010e, 11, ZC_SKILLINFO_UPDATE(sock));
		ADD_PKT(0x0215, 6, ZC_SKILLMSG(sock));
		ADD_PKT(0x0120, 6, ZC_SKILL_DISAPPEAR(sock));
		ADD_PKT(0x011f, 16, ZC_SKILL_ENTRY(sock));
		ADD_PKT(0x01c9, 97, ZC_SKILL_ENTRY2(sock));
		ADD_PKT(0x043d, 8, ZC_SKILL_POSTDELAY(sock));
		ADD_PKT(0x043e, -1, ZC_SKILL_POSTDELAY_LIST(sock));
		ADD_PKT(0x0442, 8, ZC_SKILL_SELECT_REQUEST(sock));
		ADD_PKT(0x01ac, 6, ZC_SKILL_UPDATE(sock));
		ADD_PKT(0x01d3, 35, ZC_SOUND(sock));
		ADD_PKT(0x01d0, 8, ZC_SPIRITS(sock));
		ADD_PKT(0x01e1, 8, ZC_SPIRITS2(sock));
		ADD_PKT(0x00c3, 8, ZC_SPRITE_CHANGE(sock));
		ADD_PKT(0x01d7, 11, ZC_SPRITE_CHANGE2(sock));
		ADD_PKT(0x0253, 3, ZC_STARPLACE(sock));
		ADD_PKT(0x020e, 32, ZC_STARSKILL(sock));
		ADD_PKT(0x01f8, 2, ZC_START_BABY(sock));
		ADD_PKT(0x019e, 2, ZC_START_CAPTURE(sock));
		ADD_PKT(0x01e4, 2, ZC_START_COUPLE(sock));
		ADD_PKT(0x0119, 13, ZC_STATE_CHANGE(sock));
		ADD_PKT(0x0229, 15, ZC_STATE_CHANGE3(sock));
		ADD_PKT(0x00bd, 44, ZC_STATUS(sock));
		ADD_PKT(0x00be, 5, ZC_STATUS_CHANGE(sock));
		ADD_PKT(0x00bc, 6, ZC_STATUS_CHANGE_ACK(sock));
		ADD_PKT(0x0088, 10, ZC_STOPMOVE(sock));
		ADD_PKT(0x0131, 86, ZC_STORE_ENTRY(sock));
		ADD_PKT(0x00a6, -1, ZC_STORE_EQUIPMENT_ITEMLIST(sock));
		ADD_PKT(0x0296, -1, ZC_STORE_EQUIPMENT_ITEMLIST2(sock));
		ADD_PKT(0x02d1, -1, ZC_STORE_EQUIPMENT_ITEMLIST3(sock));
		ADD_PKT(0x00a5, -1, ZC_STORE_NORMAL_ITEMLIST(sock));
		ADD_PKT(0x01f0, -1, ZC_STORE_NORMAL_ITEMLIST2(sock));
		ADD_PKT(0x02ea, -1, ZC_STORE_NORMAL_ITEMLIST3(sock));
		ADD_PKT(0x0224, 10, ZC_TAEKWON_POINT(sock));
		ADD_PKT(0x0226, 282, ZC_TAEKWON_RANK(sock));
		ADD_PKT(0x0191, 86, ZC_TALKBOX_CHATCONTENTS(sock));
		ADD_PKT(0x010d, 2, ZC_THROW_MVPITEM(sock));
		ADD_PKT(0x01a0, 3, ZC_TRYCAPTURE_MONSTER(sock));
		ADD_PKT(0x016d, 14, ZC_UPDATE_CHARSTAT(sock));
		ADD_PKT(0x01f2, 20, ZC_UPDATE_CHARSTAT2(sock));
		ADD_PKT(0x016c, 43, ZC_UPDATE_GDID(sock));
		ADD_PKT(0x0192, 24, ZC_UPDATE_MAPINFO(sock));
		ADD_PKT(0x02b5, -1, ZC_UPDATE_MISSION_HUNT(sock));
		ADD_PKT(0x00c2, 6, ZC_USER_COUNT(sock));
		ADD_PKT(0x013e, 24, ZC_USESKILL_ACK(sock));
		ADD_PKT(0x00a8, 7, ZC_USE_ITEM_ACK(sock));
		ADD_PKT(0x01c8, 13, ZC_USE_ITEM_ACK2(sock));
		ADD_PKT(0x011a, 15, ZC_USE_SKILL(sock));
		ADD_PKT(0x00b5, 6, ZC_WAIT_CoreLog(sock));
		ADD_PKT(0x011c, 68, ZC_WARPLIST(sock));
		ADD_PKT(0x0097, -1, ZC_WHISPER(sock));
		ADD_PKT(0x00d4, -1, ZC_WHISPER_LIST(sock));
#undef ADD_PKT
	}

	~PacketLengthTable() { }

	ShufflePacketLengthTable *instance()
	{
		static ShufflePacketLengthTable p;
		return &p;
	}

	std::shared_ptr<ZoneSocket> get_socket() { return _socket.lock(); }

protected:
	LockedLookupTable<uint16_t, std::pair<uint16_t, NetworkPacket>> _packet_length_table;
	std::weak_ptr<ZoneSocket> _socket;

};
}
}
#endif /* HORIZON_ZONE_PACKET_LENGTH_TABLE */
