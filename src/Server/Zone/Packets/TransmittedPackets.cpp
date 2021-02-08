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


#include "TransmittedPackets.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Utility/Utility.hpp"

using namespace Horizon::Zone;

/**
 * ZC_ACK_REQMAKINGITEM
 */
void ZC_ACK_REQMAKINGITEM::deliver() { }

ByteBuffer &ZC_ACK_REQMAKINGITEM::serialize()
{
	return buf();
}

/**
 * ZC_ACK_DISCONNECT_CHARACTER
 */
void ZC_ACK_DISCONNECT_CHARACTER::deliver() { }

ByteBuffer &ZC_ACK_DISCONNECT_CHARACTER::serialize()
{
	return buf();
}

/**
 * ZC_DISAPPEAR_ENTRY
 */
void ZC_DISAPPEAR_ENTRY::deliver() { }

ByteBuffer &ZC_DISAPPEAR_ENTRY::serialize()
{
	return buf();
}

/**
 * ZC_REFINE_ADD_ITEM
 */
void ZC_REFINE_ADD_ITEM::deliver() { }

ByteBuffer &ZC_REFINE_ADD_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_FRIENDS_STATE
 */
void ZC_FRIENDS_STATE::deliver() { }

ByteBuffer &ZC_FRIENDS_STATE::serialize()
{
	return buf();
}

/**
 * ZC_ACK_INVENTORY_EXPAND_RESULT
 */
void ZC_ACK_INVENTORY_EXPAND_RESULT::deliver() { }

ByteBuffer &ZC_ACK_INVENTORY_EXPAND_RESULT::serialize()
{
	return buf();
}

/**
 * ZC_HUNTINGLIST
 */
void ZC_HUNTINGLIST::deliver() { }

ByteBuffer &ZC_HUNTINGLIST::serialize()
{
	return buf();
}

/**
 * ZC_SKILL_UPDATE
 */
void ZC_SKILL_UPDATE::deliver() { }

ByteBuffer &ZC_SKILL_UPDATE::serialize()
{
	return buf();
}

/**
 * ZC_DEFINE_CHECK
 */
void ZC_DEFINE_CHECK::deliver() { }

ByteBuffer &ZC_DEFINE_CHECK::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_VOLUNTEER_INFO
 */
void ZC_PARTY_RECRUIT_VOLUNTEER_INFO::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_VOLUNTEER_INFO::serialize()
{
	return buf();
}

/**
 * ZC_DISPEL
 */
void ZC_DISPEL::deliver() { }

ByteBuffer &ZC_DISPEL::serialize()
{
	return buf();
}

/**
 * ZC_SEARCH_STORE_OPEN_INFO
 */
void ZC_SEARCH_STORE_OPEN_INFO::deliver() { }

ByteBuffer &ZC_SEARCH_STORE_OPEN_INFO::serialize()
{
	return buf();
}

/**
 * ZC_AUCTION_RESULT
 */
void ZC_AUCTION_RESULT::deliver() { }

ByteBuffer &ZC_AUCTION_RESULT::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ITEMIDENTIFY
 */
void ZC_ACK_ITEMIDENTIFY::deliver() { }

ByteBuffer &ZC_ACK_ITEMIDENTIFY::serialize()
{
	return buf();
}

/**
 * ZC_QUEST_NOTIFY_EFFECT
 */
void ZC_QUEST_NOTIFY_EFFECT::deliver() { }

ByteBuffer &ZC_QUEST_NOTIFY_EFFECT::serialize()
{
	return buf();
}

/**
 * ZC_CLOSE_BARGAIN_SALE_TOOL
 */
void ZC_CLOSE_BARGAIN_SALE_TOOL::deliver() { }

ByteBuffer &ZC_CLOSE_BARGAIN_SALE_TOOL::serialize()
{
	return buf();
}

/**
 * ZC_MSG_VALUE
 */
void ZC_MSG_VALUE::deliver() { }

ByteBuffer &ZC_MSG_VALUE::serialize()
{
	return buf();
}

/**
 * ZC_OFFLINE_STORE_VISIBLE
 */
void ZC_OFFLINE_STORE_VISIBLE::deliver() { }

ByteBuffer &ZC_OFFLINE_STORE_VISIBLE::serialize()
{
	return buf();
}

/**
 * ZC_INFO_REMAINTIME
 */
void ZC_INFO_REMAINTIME::deliver() { }

ByteBuffer &ZC_INFO_REMAINTIME::serialize()
{
	return buf();
}

/**
 * ZC_SIMPLE_CASH_POINT_ITEMLIST
 */
void ZC_SIMPLE_CASH_POINT_ITEMLIST::deliver() { }

ByteBuffer &ZC_SIMPLE_CASH_POINT_ITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_NEWENTRY
 */
void ZC_NOTIFY_NEWENTRY::deliver() { }

ByteBuffer &ZC_NOTIFY_NEWENTRY::serialize()
{
	return buf();
}

/**
 * ZC_START_BABY
 */
void ZC_START_BABY::deliver() { }

ByteBuffer &ZC_START_BABY::serialize()
{
	return buf();
}

/**
 * ZC_CASH_ITEM_DELETE
 */
void ZC_CASH_ITEM_DELETE::deliver() { }

ByteBuffer &ZC_CASH_ITEM_DELETE::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_RECALL_COST
 */
void ZC_PARTY_RECRUIT_RECALL_COST::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_RECALL_COST::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MANNER_POINT_GIVEN
 */
void ZC_NOTIFY_MANNER_POINT_GIVEN::deliver() { }

ByteBuffer &ZC_NOTIFY_MANNER_POINT_GIVEN::serialize()
{
	return buf();
}

/**
 * ZC_REQ_AU_BOT
 */
void ZC_REQ_AU_BOT::deliver() { }

ByteBuffer &ZC_REQ_AU_BOT::serialize()
{
	return buf();
}

/**
 * ZC_DELETE_ITEM_FROM_CART
 */
void ZC_DELETE_ITEM_FROM_CART::deliver() { }

ByteBuffer &ZC_DELETE_ITEM_FROM_CART::serialize()
{
	return buf();
}

/**
 * ZC_MVP_GETTING_ITEM
 */
void ZC_MVP_GETTING_ITEM::deliver() { }

ByteBuffer &ZC_MVP_GETTING_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_REQ_WEAR_EQUIP_ACK
 */
void ZC_REQ_WEAR_EQUIP_ACK::deliver(int16_t index, int16_t equip_location_mask, item_equip_result_type result)
{
	_index = index;
	_equip_location_mask = equip_location_mask;
	_result = (int8_t) result;

	serialize();
	transmit();
}

ByteBuffer &ZC_REQ_WEAR_EQUIP_ACK::serialize()
{
	buf() << _packet_id;
	buf() << _index;
	buf() << _equip_location_mask;
	buf() << _result;
	return buf();
}

/**
 * ZC_ACK_REQNAMEALL2
 */
void ZC_ACK_REQNAMEALL2::deliver(int32_t guid, std::string name, std::string party_name, std::string guild_name, std::string position_name, int32_t title_id)
{
	_guid = guid;
	strncpy(_name, name.c_str(), MAX_UNIT_NAME_LENGTH);
	strncpy(_party_name, party_name.c_str(), MAX_UNIT_NAME_LENGTH);
	strncpy(_guild_name, guild_name.c_str(), MAX_UNIT_NAME_LENGTH);
	strncpy(_position_name, position_name.c_str(), MAX_UNIT_NAME_LENGTH);
	_title_id = title_id;
	
	serialize();
	transmit();
}

ByteBuffer &ZC_ACK_REQNAMEALL2::serialize()
{
	buf() << _packet_id;
	buf() << _guid;
	buf().append(_name, MAX_UNIT_NAME_LENGTH);
	buf().append(_party_name, MAX_UNIT_NAME_LENGTH);
	buf().append(_guild_name, MAX_UNIT_NAME_LENGTH);
	buf().append(_position_name, MAX_UNIT_NAME_LENGTH);
	buf() << _title_id;
	
	return buf();
}

/**
 * ZC_NOTIFY_EFFECT2
 */
void ZC_NOTIFY_EFFECT2::deliver() { }

ByteBuffer &ZC_NOTIFY_EFFECT2::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_EFFECT3
 */
void ZC_NOTIFY_EFFECT3::deliver() { }

ByteBuffer &ZC_NOTIFY_EFFECT3::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_CRAZYKILLER
 */
void ZC_NOTIFY_CRAZYKILLER::deliver() { }

ByteBuffer &ZC_NOTIFY_CRAZYKILLER::serialize()
{
	return buf();
}

/**
 * ZC_CARTOFF
 */
void ZC_CARTOFF::deliver() { }

ByteBuffer &ZC_CARTOFF::serialize()
{
	return buf();
}

/**
 * ZC_ACK_WEAR_EQUIP_V5
 */
void ZC_ACK_WEAR_EQUIP_V5::deliver(int16_t inventory_index, int32_t location, int16_t look, int8_t result)
{
	_inventory_index = inventory_index;
	_equip_location = location;
	_look = look;
	_result = result;

	serialize();
	transmit();
}

ByteBuffer &ZC_ACK_WEAR_EQUIP_V5::serialize()
{
	buf() << _packet_id;
	buf() << _inventory_index;
	buf() << _equip_location;
	buf() << _look;
	buf() << _result;
	return buf();
}

/**
 * ZC_MER_PAR_CHANGE
 */
void ZC_MER_PAR_CHANGE::deliver() { }

ByteBuffer &ZC_MER_PAR_CHANGE::serialize()
{
	return buf();
}

/**
 * ZC_EXEC_EXCHANGE_ITEM
 */
void ZC_EXEC_EXCHANGE_ITEM::deliver() { }

ByteBuffer &ZC_EXEC_EXCHANGE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_ACK_APPLY_BARGAIN_SALE_ITEM
 */
void ZC_ACK_APPLY_BARGAIN_SALE_ITEM::deliver() { }

ByteBuffer &ZC_ACK_APPLY_BARGAIN_SALE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_ENTER_ROOM
 */
void ZC_ENTER_ROOM::deliver() { }

ByteBuffer &ZC_ENTER_ROOM::serialize()
{
	return buf();
}

/**
 * ZC_REPLY_REMAINTIME
 */
void ZC_REPLY_REMAINTIME::deliver() { }

ByteBuffer &ZC_REPLY_REMAINTIME::serialize()
{
	return buf();
}

/**
 * ZC_AID
 */
void ZC_AID::deliver(int32_t aid)
{
	_account_id = aid;
	
	serialize();
	transmit();
}

ByteBuffer &ZC_AID::serialize()
{
	buf() << _packet_id;
	buf() << _account_id;
	return buf();
}

/**
 * ZC_THROW_MVPITEM
 */
void ZC_THROW_MVPITEM::deliver() { }

ByteBuffer &ZC_THROW_MVPITEM::serialize()
{
	return buf();
}

/**
 * ZC_EQUIP_ARROW
 */
void ZC_EQUIP_ARROW::deliver(int16_t inventory_index)
{
	_index = inventory_index;
	serialize();
	transmit();
}

ByteBuffer &ZC_EQUIP_ARROW::serialize()
{
	buf() << _packet_id;
	buf() << _index;
	return buf();
}

/**
 * ZC_ADD_ITEM_TO_CART2
 */
void ZC_ADD_ITEM_TO_CART2::deliver() { }

ByteBuffer &ZC_ADD_ITEM_TO_CART2::serialize()
{
	return buf();
}

/**
 * ZC_EXCHANGEITEM_UNDO
 */
void ZC_EXCHANGEITEM_UNDO::deliver() { }

ByteBuffer &ZC_EXCHANGEITEM_UNDO::serialize()
{
	return buf();
}

/**
 * ZC_SHOWSCRIPT
 */
void ZC_SHOWSCRIPT::deliver() { }

ByteBuffer &ZC_SHOWSCRIPT::serialize()
{
	return buf();
}

/**
 * ZC_HOSKILLINFO_LIST
 */
void ZC_HOSKILLINFO_LIST::deliver() { }

ByteBuffer &ZC_HOSKILLINFO_LIST::serialize()
{
	return buf();
}

/**
 * ZC_SETTING_WHISPER_STATE
 */
void ZC_SETTING_WHISPER_STATE::deliver() { }

ByteBuffer &ZC_SETTING_WHISPER_STATE::serialize()
{
	return buf();
}

/**
 * ZC_SETTING_WHISPER_PC
 */
void ZC_SETTING_WHISPER_PC::deliver() { }

ByteBuffer &ZC_SETTING_WHISPER_PC::serialize()
{
	return buf();
}

/**
 * ZC_INVENTORY_ITEMLIST_EQUIP
 */
void ZC_INVENTORY_ITEMLIST_EQUIP::deliver() { }

ByteBuffer &ZC_INVENTORY_ITEMLIST_EQUIP::serialize()
{
	return buf();
}

/**
 * ZC_GANGSI_RANK
 */
void ZC_GANGSI_RANK::deliver() { }

ByteBuffer &ZC_GANGSI_RANK::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_SUB_FILTERLINGLIST
 */
void ZC_PARTY_RECRUIT_SUB_FILTERLINGLIST::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_SUB_FILTERLINGLIST::serialize()
{
	return buf();
}

/**
 * ZC_ADD_ITEM_TO_STORE
 */
void ZC_ADD_ITEM_TO_STORE::deliver() { }

ByteBuffer &ZC_ADD_ITEM_TO_STORE::serialize()
{
	return buf();
}

/**
 * ZC_AUTORUN_SKILL
 */
void ZC_AUTORUN_SKILL::deliver() { }

ByteBuffer &ZC_AUTORUN_SKILL::serialize()
{
	return buf();
}

/**
 * ZC_REQ_ACH_REWARD_ACK
 */
void ZC_REQ_ACH_REWARD_ACK::deliver() { }

ByteBuffer &ZC_REQ_ACH_REWARD_ACK::serialize()
{
	return buf();
}

/**
 * ZC_NPC_SHOWEFST_UPDATE
 */
void ZC_NPC_SHOWEFST_UPDATE::deliver() { }

ByteBuffer &ZC_NPC_SHOWEFST_UPDATE::serialize()
{
	return buf();
}

/**
 * ZC_CHANGE_GROUP_MASTER
 */
void ZC_CHANGE_GROUP_MASTER::deliver() { }

ByteBuffer &ZC_CHANGE_GROUP_MASTER::serialize()
{
	return buf();
}

/**
 * ZC_TRYCAPTURE_MONSTER
 */
void ZC_TRYCAPTURE_MONSTER::deliver() { }

ByteBuffer &ZC_TRYCAPTURE_MONSTER::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_PICKUP_ACK
 */
void ZC_ITEM_PICKUP_ACK::deliver() { }

ByteBuffer &ZC_ITEM_PICKUP_ACK::serialize()
{
	return buf();
}

/**
 * ZC_PRNPC_STATE
 */
void ZC_PRNPC_STATE::deliver() { }

ByteBuffer &ZC_PRNPC_STATE::serialize()
{
	return buf();
}

/**
 * ZC_PC_PURCHASE_ITEMLIST_FROMMC2
 */
void ZC_PC_PURCHASE_ITEMLIST_FROMMC2::deliver() { }

ByteBuffer &ZC_PC_PURCHASE_ITEMLIST_FROMMC2::serialize()
{
	return buf();
}

/**
 * ZC_ADD_EXCHANGE_ITEM4
 */
void ZC_ADD_EXCHANGE_ITEM4::deliver() { }

ByteBuffer &ZC_ADD_EXCHANGE_ITEM4::serialize()
{
	return buf();
}

/**
 * ZC_NPC_CHAT
 */
void ZC_NPC_CHAT::deliver(int32_t guid, std::string const &message, int32_t color)
{
	_guid = guid;
	_message = message;
	_color = color;

	serialize();
	transmit();
}

ByteBuffer &ZC_NPC_CHAT::serialize()
{
	buf() << _packet_id;
	buf() << _guid;
	buf() << rgb2bgr(_color);
	buf().append(_message.c_str(), _message.size());
	return buf();
}

/**
 * ZC_ALL_QUEST_LIST3
 */
void ZC_ALL_QUEST_LIST3::deliver() { }

ByteBuffer &ZC_ALL_QUEST_LIST3::serialize()
{
	return buf();
}

/**
 * ZC_ALL_QUEST_LIST2
 */
void ZC_ALL_QUEST_LIST2::deliver() { }

ByteBuffer &ZC_ALL_QUEST_LIST2::serialize()
{
	return buf();
}

/**
 * ZC_ALL_QUEST_LIST4
 */
void ZC_ALL_QUEST_LIST4::deliver() { }

ByteBuffer &ZC_ALL_QUEST_LIST4::serialize()
{
	return buf();
}

/**
 * ZC_ADD_EXCHANGE_ITEM2
 */
void ZC_ADD_EXCHANGE_ITEM2::deliver() { }

ByteBuffer &ZC_ADD_EXCHANGE_ITEM2::serialize()
{
	return buf();
}

/**
 * ZC_ADD_EXCHANGE_ITEM3
 */
void ZC_ADD_EXCHANGE_ITEM3::deliver() { }

ByteBuffer &ZC_ADD_EXCHANGE_ITEM3::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_REFUSE_VOLUNTEER_TO_PM
 */
void ZC_PARTY_RECRUIT_REFUSE_VOLUNTEER_TO_PM::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_REFUSE_VOLUNTEER_TO_PM::serialize()
{
	return buf();
}

/**
 * ZC_ACK_GUILD_NAME
 */
void ZC_ACK_GUILD_NAME::deliver() { }

ByteBuffer &ZC_ACK_GUILD_NAME::serialize()
{
	return buf();
}

/**
 * ZC_OFFLINE_STORE_VANISH
 */
void ZC_OFFLINE_STORE_VANISH::deliver() { }

ByteBuffer &ZC_OFFLINE_STORE_VANISH::serialize()
{
	return buf();
}

/**
 * ZC_STATE_CHANGE3
 */
void ZC_STATE_CHANGE3::deliver() { }

ByteBuffer &ZC_STATE_CHANGE3::serialize()
{
	return buf();
}

/**
 * ZC_SHORTCUT_KEY_LIST_V3
 */
void ZC_SHORTCUT_KEY_LIST_V3::deliver() { }

ByteBuffer &ZC_SHORTCUT_KEY_LIST_V3::serialize()
{
	return buf();
}

/**
 * ZC_SHORTCUT_KEY_LIST_V2
 */
void ZC_SHORTCUT_KEY_LIST_V2::deliver() { }

ByteBuffer &ZC_SHORTCUT_KEY_LIST_V2::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_SKILL2
 */
void ZC_NOTIFY_SKILL2::deliver() { }

ByteBuffer &ZC_NOTIFY_SKILL2::serialize()
{
	return buf();
}

/**
 * ZC_CHANGE_CHATROOM
 */
void ZC_CHANGE_CHATROOM::deliver() { }

ByteBuffer &ZC_CHANGE_CHATROOM::serialize()
{
	return buf();
}

/**
 * ZC_STORE_ENTRY
 */
void ZC_STORE_ENTRY::deliver() { }

ByteBuffer &ZC_STORE_ENTRY::serialize()
{
	return buf();
}

/**
 * ZC_STORE_ITEMLIST_NORMAL_V5
 */
void ZC_STORE_ITEMLIST_NORMAL_V5::deliver() { }

ByteBuffer &ZC_STORE_ITEMLIST_NORMAL_V5::serialize()
{
	return buf();
}

/**
 * ZC_ACK_STATUS_GM
 */
void ZC_ACK_STATUS_GM::deliver() { }

ByteBuffer &ZC_ACK_STATUS_GM::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_ACT2
 */
void ZC_NOTIFY_ACT2::deliver() { }

ByteBuffer &ZC_NOTIFY_ACT2::serialize()
{
	return buf();
}

/**
 * ZC_MEMBER_EXIT
 */
void ZC_MEMBER_EXIT::deliver() { }

ByteBuffer &ZC_MEMBER_EXIT::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_THROW_ACK
 */
void ZC_ITEM_THROW_ACK::deliver(int16_t inventory_index, int16_t amount)
{
	_inventory_index = inventory_index;
	_amount = amount;

	serialize();
	transmit();
}

ByteBuffer &ZC_ITEM_THROW_ACK::serialize()
{
	buf() << _packet_id;
	buf() << _inventory_index;
	buf() << _amount;
	return buf();
}

/**
 * ZC_START_COLLECTION
 */
void ZC_START_COLLECTION::deliver() { }

ByteBuffer &ZC_START_COLLECTION::serialize()
{
	return buf();
}

/**
 * ZC_OPEN_EDITDLGSTR
 */
void ZC_OPEN_EDITDLGSTR::deliver(int32_t guid)
{
	_guid = guid;
	serialize();
	transmit();
}

ByteBuffer &ZC_OPEN_EDITDLGSTR::serialize()
{
	buf() << _packet_id;
	buf() << _guid;
	return buf();
}

/**
 * ZC_SPIRITS2
 */
void ZC_SPIRITS2::deliver() { }

ByteBuffer &ZC_SPIRITS2::serialize()
{
	return buf();
}

/**
 * ZC_PROPERTY_PET
 */
void ZC_PROPERTY_PET::deliver() { }

ByteBuffer &ZC_PROPERTY_PET::serialize()
{
	return buf();
}

/**
 * ZC_EQUIPMENT_ITEMLIST
 */
void ZC_EQUIPMENT_ITEMLIST::deliver(std::vector<item_entry_data> &items)
{
	_items = items;

	serialize();
	transmit();
}

ByteBuffer &ZC_EQUIPMENT_ITEMLIST::serialize()
{
	buf() << _packet_id;
	buf() << int16_t(2 + (_items.size() * sizeof(item_entry_data)));
	for (auto it = _items.begin(); it != _items.end(); it++) {
		item_entry_data id = *it;
		int8_t config = 0;
		buf() << id.inventory_index;
		buf() << ((int16_t) id.item_id);
		buf() << ((int8_t) id.type);
		buf() << id.actual_equip_location_mask;
		buf() << id.current_equip_location_mask;
		buf() << id.refine_level;
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
			buf() << (int16_t) id.slot_item_id[i];
		buf() << id.hire_expire_date;
		buf() << (int16_t) id.bind_type;
		buf() << id.sprite_id;

		buf() << id.option_count;

		for (int i = 0; i < MAX_ITEM_OPTIONS; i++) {
			buf() << id.option_data[i].index;
			buf() << id.option_data[i].value;
			buf() << id.option_data[i].param;
		}

		config |= id.info.is_identified;
		config |= id.info.is_broken << 1;
		config |= id.info.is_favorite << 2;
		buf() << config;
	}

	return buf();
}

/**
 * ZC_ACK_OPENSTORE2
 */
void ZC_ACK_OPENSTORE2::deliver() { }

ByteBuffer &ZC_ACK_OPENSTORE2::serialize()
{
	return buf();
}

/**
 * ZC_DISAPPEAR_BUYING_STORE_ENTRY
 */
void ZC_DISAPPEAR_BUYING_STORE_ENTRY::deliver() { }

ByteBuffer &ZC_DISAPPEAR_BUYING_STORE_ENTRY::serialize()
{
	return buf();
}

/**
 * ZC_WARPLIST
 */
void ZC_WARPLIST::deliver() { }

ByteBuffer &ZC_WARPLIST::serialize()
{
	return buf();
}

/**
 * ZC_WAIT_DIALOG2
 */
void ZC_WAIT_DIALOG2::deliver() { }

ByteBuffer &ZC_WAIT_DIALOG2::serialize()
{
	return buf();
}

/**
 * ZC_BLADESTOP
 */
void ZC_BLADESTOP::deliver() { }

ByteBuffer &ZC_BLADESTOP::serialize()
{
	return buf();
}

/**
 * ZC_MSG_STATE_CHANGE
 */
void ZC_MSG_STATE_CHANGE::deliver() { }

ByteBuffer &ZC_MSG_STATE_CHANGE::serialize()
{
	return buf();
}

/**
 * ZC_SOUND
 */
void ZC_SOUND::deliver() { }

ByteBuffer &ZC_SOUND::serialize()
{
	return buf();
}

/**
 * ZC_NPCSPRITE_CHANGE
 */
void ZC_NPCSPRITE_CHANGE::deliver() { }

ByteBuffer &ZC_NPCSPRITE_CHANGE::serialize()
{
	return buf();
}

/**
 * ZC_SPIRITS_ATTRIBUTE
 */
void ZC_SPIRITS_ATTRIBUTE::deliver() { }

ByteBuffer &ZC_SPIRITS_ATTRIBUTE::serialize()
{
	return buf();
}

/**
 * ZC_ALT_EQUIPMENT_EQUIP
 */
void ZC_ALT_EQUIPMENT_EQUIP::deliver() { }

ByteBuffer &ZC_ALT_EQUIPMENT_EQUIP::serialize()
{
	return buf();
}

/**
 * ZC_FORMATSTRING_MSG
 */
void ZC_FORMATSTRING_MSG::deliver() { }

ByteBuffer &ZC_FORMATSTRING_MSG::serialize()
{
	return buf();
}

/**
 * ZC_ACK_INVENTORY_EXPAND
 */
void ZC_ACK_INVENTORY_EXPAND::deliver() { }

ByteBuffer &ZC_ACK_INVENTORY_EXPAND::serialize()
{
	return buf();
}

/**
 * ZC_REFINE_OPEN_WINDOW
 */
void ZC_REFINE_OPEN_WINDOW::deliver() { }

ByteBuffer &ZC_REFINE_OPEN_WINDOW::serialize()
{
	return buf();
}

/**
 * ZC_INVENTORY_START
 */
void ZC_INVENTORY_START::deliver() { }

ByteBuffer &ZC_INVENTORY_START::serialize()
{
	return buf();
}

/**
 * ZC_CLOSE_DIALOG
 */
void ZC_CLOSE_DIALOG::deliver(int32_t guid)
{
	_guid = guid;
	serialize();
	transmit();
}

ByteBuffer &ZC_CLOSE_DIALOG::serialize()
{
	buf() << _packet_id;
	buf() << _guid;
	return buf();
}

/**
 * ZC_DELETE_RELATED_GUILD
 */
void ZC_DELETE_RELATED_GUILD::deliver() { }

ByteBuffer &ZC_DELETE_RELATED_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_SE_PC_BUY_CASHITEM_RESULT
 */
void ZC_SE_PC_BUY_CASHITEM_RESULT::deliver() { }

ByteBuffer &ZC_SE_PC_BUY_CASHITEM_RESULT::serialize()
{
	return buf();
}

/**
 * ZC_UPDATE_ITEM_FROM_BUYING_STORE2
 */
void ZC_UPDATE_ITEM_FROM_BUYING_STORE2::deliver() { }

ByteBuffer &ZC_UPDATE_ITEM_FROM_BUYING_STORE2::serialize()
{
	return buf();
}

/**
 * ZC_PCBANG_EFFECT
 */
void ZC_PCBANG_EFFECT::deliver() { }

ByteBuffer &ZC_PCBANG_EFFECT::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_FAILED_RECALL
 */
void ZC_PARTY_RECRUIT_FAILED_RECALL::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_FAILED_RECALL::serialize()
{
	return buf();
}

/**
 * ZC_SEEK_PARTY_MEMBER
 */
void ZC_SEEK_PARTY_MEMBER::deliver() { }

ByteBuffer &ZC_SEEK_PARTY_MEMBER::serialize()
{
	return buf();
}

/**
 * ZC_UNKNOWN_CLEAN_ITEMS_LISTS
 */
void ZC_UNKNOWN_CLEAN_ITEMS_LISTS::deliver() { }

ByteBuffer &ZC_UNKNOWN_CLEAN_ITEMS_LISTS::serialize()
{
	return buf();
}

/**
 * ZC_ACK_BANKING_WITHDRAW
 */
void ZC_ACK_BANKING_WITHDRAW::deliver() { }

ByteBuffer &ZC_ACK_BANKING_WITHDRAW::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REMOVE_RODEX_ITEM
 */
void ZC_ACK_REMOVE_RODEX_ITEM::deliver() { }

ByteBuffer &ZC_ACK_REMOVE_RODEX_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_MACRO_ITEMPICKUP_FAIL
 */
void ZC_MACRO_ITEMPICKUP_FAIL::deliver() { }

ByteBuffer &ZC_MACRO_ITEMPICKUP_FAIL::serialize()
{
	return buf();
}

/**
 * ZC_AUCTION_ITEM_REQ_SEARCH
 */
void ZC_AUCTION_ITEM_REQ_SEARCH::deliver() { }

ByteBuffer &ZC_AUCTION_ITEM_REQ_SEARCH::serialize()
{
	return buf();
}

/**
 * ZC_REFUSE_ENTER
 */
void ZC_REFUSE_ENTER::deliver(zc_server_reject_type error)
{
	_error = error;

	serialize();
	transmit();
}

ByteBuffer &ZC_REFUSE_ENTER::serialize()
{
	buf() << _packet_id;
	buf() << (int8_t) _error;
	return buf();
}

/**
 * ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST
 */
void ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST::deliver() { }

ByteBuffer &ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_INVENTORY_ITEMLIST_NORMAL_V5
 */
void ZC_INVENTORY_ITEMLIST_NORMAL_V5::deliver(std::vector<std::shared_ptr<const item_entry_data>> const &items)
{
	_items = items;
	serialize();
	transmit();
}

ByteBuffer &ZC_INVENTORY_ITEMLIST_NORMAL_V5::serialize()
{
	int size = 4;
	
	buf() << _packet_id;
	buf() << (int16_t) ((_items.size() * 24) + 4);

	for (auto it = _items.begin(); it != _items.end(); it++) {
		std::shared_ptr<const item_entry_data> id = *it;
		uint8_t config = 0;

		buf() << id->inventory_index;
		buf() << ((uint16_t) id->item_id);
		buf() << ((uint8_t) id->type);
		buf() << id->amount;
		buf() << id->current_equip_location_mask; // 11

		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
			buf() << (uint16_t) id->slot_item_id[i]; // 4 * 2

		buf() << id->hire_expire_date; // 23

		config |= id->info.is_identified;
		config |= id->info.is_favorite << 1;
		buf() << config; // 24
	}

	return buf();
}

/**
 * ZC_USESKILL_ACK
 */
void ZC_USESKILL_ACK::deliver() { }

ByteBuffer &ZC_USESKILL_ACK::serialize()
{
	return buf();
}

/**
 * ZC_ACK_CHANGE_TITLE
 */
void ZC_ACK_CHANGE_TITLE::deliver() { }

ByteBuffer &ZC_ACK_CHANGE_TITLE::serialize()
{
	return buf();
}

/**
 * ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO
 */
void ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO::deliver() { }

ByteBuffer &ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO::serialize()
{
	return buf();
}

/**
 * ZC_REQ_WEAR_EQUIP_ACK2
 */
void ZC_REQ_WEAR_EQUIP_ACK2::deliver(int16_t inventory_index, int32_t equip_location_mask, int16_t sprite_id, item_equip_result_type result)
{
	_inventory_index = inventory_index;
	_equip_location_mask = equip_location_mask;
	_sprite_id = sprite_id;
	_result = (int8_t) result;

	serialize();
	transmit();
}

ByteBuffer &ZC_REQ_WEAR_EQUIP_ACK2::serialize()
{
	buf() << _packet_id;
	buf() << _inventory_index;
	buf() << _equip_location_mask;
	buf() << _sprite_id;
	buf() << _result;
	return buf();
}

/**
 * ZC_RESTART_ACK
 */
void ZC_RESTART_ACK::deliver(int8_t type)
{
	_type = type;

	serialize();
	transmit();
}

ByteBuffer &ZC_RESTART_ACK::serialize()
{
	buf() << _packet_id;
	buf() << _type;
	return buf();
}

/**
 * ZC_UPDATE_GDID
 */
void ZC_UPDATE_GDID::deliver() { }

ByteBuffer &ZC_UPDATE_GDID::serialize()
{
	return buf();
}

/**
 * ZC_SHOW_IMAGE2
 */
void ZC_SHOW_IMAGE2::deliver() { }

ByteBuffer &ZC_SHOW_IMAGE2::serialize()
{
	return buf();
}

/**
 * ZC_FRIENDS_LIST
 */
void ZC_FRIENDS_LIST::deliver() { }

ByteBuffer &ZC_FRIENDS_LIST::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_INITCHAR
 */
void ZC_NOTIFY_INITCHAR::deliver() { }

ByteBuffer &ZC_NOTIFY_INITCHAR::serialize()
{
	return buf();
}

/**
 * ZC_START_CAPTURE
 */
void ZC_START_CAPTURE::deliver() { }

ByteBuffer &ZC_START_CAPTURE::serialize()
{
	return buf();
}

/**
 * ZC_DRESSROOM_OPEN
 */
void ZC_DRESSROOM_OPEN::deliver() { }

ByteBuffer &ZC_DRESSROOM_OPEN::serialize()
{
	return buf();
}

/**
 * ZC_ACTION_MOVE
 */
void ZC_ACTION_MOVE::deliver() { }

ByteBuffer &ZC_ACTION_MOVE::serialize()
{
	return buf();
}

/**
 * ZC_STORE_ITEMLIST_EQUIP
 */
void ZC_STORE_ITEMLIST_EQUIP::deliver() { }

ByteBuffer &ZC_STORE_ITEMLIST_EQUIP::serialize()
{
	return buf();
}

/**
 * ZC_ACK_OPEN_ROULETTE
 */
void ZC_ACK_OPEN_ROULETTE::deliver() { }

ByteBuffer &ZC_ACK_OPEN_ROULETTE::serialize()
{
	return buf();
}

/**
 * ZC_STORE_NORMAL_ITEMLIST
 */
void ZC_STORE_NORMAL_ITEMLIST::deliver() { }

ByteBuffer &ZC_STORE_NORMAL_ITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_AIRSHIP_SERVERMOVE
 */
void ZC_AIRSHIP_SERVERMOVE::deliver() { }

ByteBuffer &ZC_AIRSHIP_SERVERMOVE::serialize()
{
	return buf();
}

/**
 * ZC_PC_SELL_RESULT
 */
void ZC_PC_SELL_RESULT::deliver() { }

ByteBuffer &ZC_PC_SELL_RESULT::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MOVEENTRY
 */
void ZC_NOTIFY_MOVEENTRY::deliver() { }

ByteBuffer &ZC_NOTIFY_MOVEENTRY::serialize()
{
	return buf();
}

/**
 * ZC_ACK_CLOSE_BANKING
 */
void ZC_ACK_CLOSE_BANKING::deliver() { }

ByteBuffer &ZC_ACK_CLOSE_BANKING::serialize()
{
	return buf();
}

/**
 * ZC_BROADCAST
 */
void ZC_BROADCAST::deliver() { }

ByteBuffer &ZC_BROADCAST::serialize()
{
	return buf();
}

/**
 * ZC_ES_NOTI_MYINFO
 */
void ZC_ES_NOTI_MYINFO::deliver() { }

ByteBuffer &ZC_ES_NOTI_MYINFO::serialize()
{
	return buf();
}

/**
 * ZC_MERGE_ITEM_OPEN
 */
void ZC_MERGE_ITEM_OPEN::deliver() { }

ByteBuffer &ZC_MERGE_ITEM_OPEN::serialize()
{
	return buf();
}

/**
 * ZC_STORE_NORMAL_ITEMLIST2
 */
void ZC_STORE_NORMAL_ITEMLIST2::deliver() { }

ByteBuffer &ZC_STORE_NORMAL_ITEMLIST2::serialize()
{
	return buf();
}

/**
 * ZC_SELECTCART
 */
void ZC_SELECTCART::deliver() { }

ByteBuffer &ZC_SELECTCART::serialize()
{
	return buf();
}

/**
 * ZC_PROPERTY_HOMUN
 */
void ZC_PROPERTY_HOMUN::deliver() { }

ByteBuffer &ZC_PROPERTY_HOMUN::serialize()
{
	return buf();
}

/**
 * ZC_REPLY_ACK_ENTRY_QUEUE_ADMISSION
 */
void ZC_REPLY_ACK_ENTRY_QUEUE_ADMISSION::deliver() { }

ByteBuffer &ZC_REPLY_ACK_ENTRY_QUEUE_ADMISSION::serialize()
{
	return buf();
}

/**
 * ZC_IRMAIL_SEND_RES
 */
void ZC_IRMAIL_SEND_RES::deliver() { }

ByteBuffer &ZC_IRMAIL_SEND_RES::serialize()
{
	return buf();
}

/**
 * ZC_ACK_BANKING_DEPOSIT
 */
void ZC_ACK_BANKING_DEPOSIT::deliver() { }

ByteBuffer &ZC_ACK_BANKING_DEPOSIT::serialize()
{
	return buf();
}

/**
 * ZC_MCSTORE_NOTMOVEITEM_LIST
 */
void ZC_MCSTORE_NOTMOVEITEM_LIST::deliver() { }

ByteBuffer &ZC_MCSTORE_NOTMOVEITEM_LIST::serialize()
{
	return buf();
}

/**
 * ZC_HACKSHIELD_CRC_MSG
 */
void ZC_HACKSHIELD_CRC_MSG::deliver() { }

ByteBuffer &ZC_HACKSHIELD_CRC_MSG::serialize()
{
	return buf();
}

/**
 * ZC_FATIGUE_CHN
 */
void ZC_FATIGUE_CHN::deliver() { }

ByteBuffer &ZC_FATIGUE_CHN::serialize()
{
	return buf();
}

/**
 * ZC_NPCACK_MAPMOVE
 */
void ZC_NPCACK_MAPMOVE::deliver(std::string map_name, int16_t x, int16_t y)
{
	if (map_name.size() + 4 > MAP_NAME_LENGTH_EXT) {
		HLog(error) << "Copying '.gat' to map name " << map_name << " would exceed length.";
		return;
	}

	map_name.append(".gat");
	strncpy(_map_name, map_name.c_str(), MAP_NAME_LENGTH_EXT);
	_x = x;
	_y = y;

	serialize();
	transmit();
}

ByteBuffer &ZC_NPCACK_MAPMOVE::serialize()
{
	buf() << _packet_id;
	buf().append(_map_name, MAP_NAME_LENGTH_EXT);
	buf() << _x;
	buf() << _y;
	return buf();
}

/**
 * ZC_ITEM_ENTRY
 */
void ZC_ITEM_ENTRY::deliver() { }

ByteBuffer &ZC_ITEM_ENTRY::serialize()
{
	return buf();
}

/**
 * ZC_SKILL_SELECT_REQUEST
 */
void ZC_SKILL_SELECT_REQUEST::deliver() { }

ByteBuffer &ZC_SKILL_SELECT_REQUEST::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_ACK_DELETE
 */
void ZC_PARTY_RECRUIT_ACK_DELETE::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_ACK_DELETE::serialize()
{
	return buf();
}

/**
 * ZC_CONFIG
 */
void ZC_CONFIG::deliver() { }

ByteBuffer &ZC_CONFIG::serialize()
{
	return buf();
}

/**
 * ZC_SKILL_ENTRY
 */
void ZC_SKILL_ENTRY::deliver() { }

ByteBuffer &ZC_SKILL_ENTRY::serialize()
{
	return buf();
}

/**
 * ZC_ACK_EXCHANGE_ITEM
 */
void ZC_ACK_EXCHANGE_ITEM::deliver() { }

ByteBuffer &ZC_ACK_EXCHANGE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_DEATH_QUESTION
 */
void ZC_DEATH_QUESTION::deliver() { }

ByteBuffer &ZC_DEATH_QUESTION::serialize()
{
	return buf();
}

/**
 * ZC_BLACKSMITH_POINT
 */
void ZC_BLACKSMITH_POINT::deliver() { }

ByteBuffer &ZC_BLACKSMITH_POINT::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_DISAPPEAR
 */
void ZC_ITEM_DISAPPEAR::deliver() { }

ByteBuffer &ZC_ITEM_DISAPPEAR::serialize()
{
	return buf();
}

/**
 * ZC_ACK_OPEN_MEMBER_INFO
 */
void ZC_ACK_OPEN_MEMBER_INFO::deliver() { }

ByteBuffer &ZC_ACK_OPEN_MEMBER_INFO::serialize()
{
	return buf();
}

/**
 * ZC_INVENTORY_END
 */
void ZC_INVENTORY_END::deliver() { }

ByteBuffer &ZC_INVENTORY_END::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ZENY_FROM_RODEX
 */
void ZC_ACK_ZENY_FROM_RODEX::deliver() { }

ByteBuffer &ZC_ACK_ZENY_FROM_RODEX::serialize()
{
	return buf();
}

/**
 * ZC_GUILD_SKILLINFO
 */
void ZC_GUILD_SKILLINFO::deliver() { }

ByteBuffer &ZC_GUILD_SKILLINFO::serialize()
{
	return buf();
}

/**
 * ZC_EFST_SET_ENTER
 */
void ZC_EFST_SET_ENTER::deliver() { }

ByteBuffer &ZC_EFST_SET_ENTER::serialize()
{
	return buf();
}

/**
 * ZC_BATTLEFIELD_CHAT
 */
void ZC_BATTLEFIELD_CHAT::deliver() { }

ByteBuffer &ZC_BATTLEFIELD_CHAT::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_RANKING
 */
void ZC_NOTIFY_RANKING::deliver() { }

ByteBuffer &ZC_NOTIFY_RANKING::serialize()
{
	return buf();
}

/**
 * ZC_SKILL_ENTRY3
 */
void ZC_SKILL_ENTRY3::deliver() { }

ByteBuffer &ZC_SKILL_ENTRY3::serialize()
{
	return buf();
}

/**
 * ZC_SKILL_ENTRY2
 */
void ZC_SKILL_ENTRY2::deliver() { }

ByteBuffer &ZC_SKILL_ENTRY2::serialize()
{
	return buf();
}

/**
 * ZC_SKILL_ENTRY5
 */
void ZC_SKILL_ENTRY5::deliver() { }

ByteBuffer &ZC_SKILL_ENTRY5::serialize()
{
	return buf();
}

/**
 * ZC_SKILL_ENTRY4
 */
void ZC_SKILL_ENTRY4::deliver() { }

ByteBuffer &ZC_SKILL_ENTRY4::serialize()
{
	return buf();
}

/**
 * ZC_NPROTECTGAMEGUARDCSAUTH
 */
void ZC_NPROTECTGAMEGUARDCSAUTH::deliver() { }

ByteBuffer &ZC_NPROTECTGAMEGUARDCSAUTH::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REQNAME_BYGID
 */
void ZC_ACK_REQNAME_BYGID::deliver() { }

ByteBuffer &ZC_ACK_REQNAME_BYGID::serialize()
{
	return buf();
}

/**
 * ZC_MEMORIALDUNGEON_INFO
 */
void ZC_MEMORIALDUNGEON_INFO::deliver() { }

ByteBuffer &ZC_MEMORIALDUNGEON_INFO::serialize()
{
	return buf();
}

/**
 * ZC_USE_SKILL
 */
void ZC_USE_SKILL::deliver() { }

ByteBuffer &ZC_USE_SKILL::serialize()
{
	return buf();
}

/**
 * ZC_SHOW_IMAGE
 */
void ZC_SHOW_IMAGE::deliver() { }

ByteBuffer &ZC_SHOW_IMAGE::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ITEM_FROM_RODEX
 */
void ZC_ACK_ITEM_FROM_RODEX::deliver() { }

ByteBuffer &ZC_ACK_ITEM_FROM_RODEX::serialize()
{
	return buf();
}

/**
 * ZC_DYNAMICNPC_CREATE_RESULT
 */
void ZC_DYNAMICNPC_CREATE_RESULT::deliver() { }

ByteBuffer &ZC_DYNAMICNPC_CREATE_RESULT::serialize()
{
	return buf();
}

/**
 * ZC_USE_ITEM_ACK2
 */
void ZC_USE_ITEM_ACK2::deliver(int16_t index, int16_t item_id, int32_t target_guid, int16_t amount, bool success)
{
	_index = index;
	_item_id = item_id;
	_target_guid = target_guid;
	_amount = amount;
	_success = success;

	serialize();
	transmit();
}

ByteBuffer &ZC_USE_ITEM_ACK2::serialize()
{
	buf() << _packet_id;
	buf() << _index;
	buf() << _item_id;
	buf() << _target_guid;
	buf() << _amount;
	buf() << _success;
	return buf();
}


/**
 * ZC_USESKILL_ACK2
 */
void ZC_USESKILL_ACK2::deliver() { }

ByteBuffer &ZC_USESKILL_ACK2::serialize()
{
	return buf();
}

/**
 * ZC_ACK_BAN_GUILD_SSO
 */
void ZC_ACK_BAN_GUILD_SSO::deliver() { }

ByteBuffer &ZC_ACK_BAN_GUILD_SSO::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_WEAPONITEMLIST
 */
void ZC_NOTIFY_WEAPONITEMLIST::deliver() { }

ByteBuffer &ZC_NOTIFY_WEAPONITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_PC_PURCHASE_ITEMLIST
 */
void ZC_PC_PURCHASE_ITEMLIST::deliver() { }

ByteBuffer &ZC_PC_PURCHASE_ITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_MSG_SKILL
 */
void ZC_MSG_SKILL::deliver() { }

ByteBuffer &ZC_MSG_SKILL::serialize()
{
	return buf();
}

/**
 * ZC_CASH_TIME_COUNTER
 */
void ZC_CASH_TIME_COUNTER::deliver() { }

ByteBuffer &ZC_CASH_TIME_COUNTER::serialize()
{
	return buf();
}

/**
 * ZC_WHISPER_LIST
 */
void ZC_WHISPER_LIST::deliver() { }

ByteBuffer &ZC_WHISPER_LIST::serialize()
{
	return buf();
}

/**
 * ZC_REFINE_STATUS
 */
void ZC_REFINE_STATUS::deliver() { }

ByteBuffer &ZC_REFINE_STATUS::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_EFFECT
 */
void ZC_NOTIFY_EFFECT::deliver() { }

ByteBuffer &ZC_NOTIFY_EFFECT::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_BOOKING_ACK_REGISTER
 */
void ZC_PARTY_BOOKING_ACK_REGISTER::deliver() { }

ByteBuffer &ZC_PARTY_BOOKING_ACK_REGISTER::serialize()
{
	return buf();
}

/**
 * ZC_GPK_DYNCODE
 */
void ZC_GPK_DYNCODE::deliver() { }

ByteBuffer &ZC_GPK_DYNCODE::serialize()
{
	return buf();
}

/**
 * ZC_UPDATE_TAIWANCASH
 */
void ZC_UPDATE_TAIWANCASH::deliver() { }

ByteBuffer &ZC_UPDATE_TAIWANCASH::serialize()
{
	return buf();
}

/**
 * ZC_ALCHEMIST_POINT
 */
void ZC_ALCHEMIST_POINT::deliver() { }

ByteBuffer &ZC_ALCHEMIST_POINT::serialize()
{
	return buf();
}

/**
 * ZC_ACK_PVPPOINT
 */
void ZC_ACK_PVPPOINT::deliver() { }

ByteBuffer &ZC_ACK_PVPPOINT::serialize()
{
	return buf();
}

/**
 * ZC_INVENTORY_ITEMLIST_EQUIP_V6
 */
void ZC_INVENTORY_ITEMLIST_EQUIP_V6::deliver(std::vector<std::shared_ptr<const item_entry_data>> const &items)
{
	_items = items;
	serialize();
	transmit();
}

ByteBuffer &ZC_INVENTORY_ITEMLIST_EQUIP_V6::serialize()
{
	buf() << _packet_id;
	buf() << (int16_t) ((65 * _items.size()) + 4);

	for (auto it = _items.begin(); it != _items.end(); it++) {
		std::shared_ptr<const item_entry_data> id = *it;
		uint8_t config = 0;
		buf() << id->inventory_index;
		buf() << ((uint16_t) id->item_id);
		buf() << ((uint8_t) id->type);
		buf() << id->actual_equip_location_mask;
		buf() << id->current_equip_location_mask;
		buf() << id->refine_level; //14
		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
			buf() << (uint16_t) id->slot_item_id[i]; // 30
		buf() << id->hire_expire_date;
		buf() << (uint16_t) id->bind_type; // 36
		buf() << id->sprite_id; // 38

		buf() << id->option_count; // 39

		for (int i = 0; i < MAX_ITEM_OPTIONS; i++) {
			buf() << id->option_data[i].index;
			buf() << id->option_data[i].value;
			buf() << id->option_data[i].param;
		} // 39 + 25 = 64

		config |= id->info.is_identified;
		config |= id->info.is_broken << 1;
		config |= id->info.is_favorite << 2;
		buf() << config; // 65
	}

	return buf();
}

/**
 * ZC_BATTLEFIELD_NOTIFY_POSITION
 */
void ZC_BATTLEFIELD_NOTIFY_POSITION::deliver() { }

ByteBuffer &ZC_BATTLEFIELD_NOTIFY_POSITION::serialize()
{
	return buf();
}

/**
 * ZC_ACK_OPEN_GUILD_STORAGE
 */
void ZC_ACK_OPEN_GUILD_STORAGE::deliver() { }

ByteBuffer &ZC_ACK_OPEN_GUILD_STORAGE::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ITEMREPAIR
 */
void ZC_ACK_ITEMREPAIR::deliver() { }

ByteBuffer &ZC_ACK_ITEMREPAIR::serialize()
{
	return buf();
}

/**
 * ZC_INVENTORY_ITEMLIST_EQUIP_V5
 */
void ZC_INVENTORY_ITEMLIST_EQUIP_V5::deliver() { }

ByteBuffer &ZC_INVENTORY_ITEMLIST_EQUIP_V5::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_DELETE_BUYING_STORE
 */
void ZC_ITEM_DELETE_BUYING_STORE::deliver() { }

ByteBuffer &ZC_ITEM_DELETE_BUYING_STORE::serialize()
{
	return buf();
}

/**
 * ZC_EQUIPWIN_MICROSCOPE
 */
void ZC_EQUIPWIN_MICROSCOPE::deliver() { }

ByteBuffer &ZC_EQUIPWIN_MICROSCOPE::serialize()
{
	return buf();
}

/**
 * ZC_SPRITE_CHANGE
 */
void ZC_SPRITE_CHANGE::deliver(int32_t guid, entity_appearance_type look_type, int32_t look_id, int32_t look_shield)
{
	_guid = guid;
	_look_type = (int8_t) look_type;
#if (CLIENT_TYPE == 'M' && PACKET_VERSION >= 20181121) \
|| (CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180704) \
|| (CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20181114)
	_look_id = (int32_t) look_id;
	_shield_id = look_shield;
#elif PACKET_VERSION >= 4
	_look_id = (int16_t) look_id;
	_shield_id = (int16_t) look_shield;
#else
	_look_id = (int8_t) look_id;
#endif

	serialize();
	transmit();
}

ByteBuffer &ZC_SPRITE_CHANGE::serialize()
{
	buf() << _packet_id;
	buf() << _guid;
	buf() << _look_type;
#if (CLIENT_TYPE == 'M' && PACKET_VERSION >= 20181121) \
	|| (CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180704) \
	|| (CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20181114)
		buf() << (int32_t) _look_id;
	buf() << (int32_t) _shield_id;
#elif PACKET_VERSION >= 4
	buf() << (int16_t) _look_id;
	buf() << (int16_t) _shield_id;
#else
	buf() << (int8_t) _look_id;
#endif
	return buf();
}

/**
 * ZC_NOTIFY_BIND_ON_EQUIP
 */
void ZC_NOTIFY_BIND_ON_EQUIP::deliver(int16_t index)
{
	_index = index;

	serialize();
	transmit();
}

ByteBuffer &ZC_NOTIFY_BIND_ON_EQUIP::serialize()
{
	buf() << _packet_id;
	buf() << _index;
	return buf();
}

/**
 * ZC_PC_PURCHASE_RESULT
 */
void ZC_PC_PURCHASE_RESULT::deliver() { }

ByteBuffer &ZC_PC_PURCHASE_RESULT::serialize()
{
	return buf();
}

/**
 * ZC_EQUIPITEM_DAMAGED
 */
void ZC_EQUIPITEM_DAMAGED::deliver() { }

ByteBuffer &ZC_EQUIPITEM_DAMAGED::serialize()
{
	return buf();
}

/**
 * ZC_FAILED_TRADE_BUYING_STORE_TO_BUYER
 */
void ZC_FAILED_TRADE_BUYING_STORE_TO_BUYER::deliver() { }

ByteBuffer &ZC_FAILED_TRADE_BUYING_STORE_TO_BUYER::serialize()
{
	return buf();
}

/**
 * ZC_OPENSTORE
 */
void ZC_OPENSTORE::deliver() { }

ByteBuffer &ZC_OPENSTORE::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_LOBBY_ADMISSION
 */
void ZC_NOTIFY_LOBBY_ADMISSION::deliver() { }

ByteBuffer &ZC_NOTIFY_LOBBY_ADMISSION::serialize()
{
	return buf();
}

/**
 * ZC_ACK_WHISPER02
 */
void ZC_ACK_WHISPER02::deliver(zc_whisper_result_type result, int32_t recipient_char_id)
{
	_result = (int8_t) result;
	_recipient_char_id = recipient_char_id;	
	serialize();
	transmit();
}

ByteBuffer &ZC_ACK_WHISPER02::serialize()
{
	buf() << _packet_id;
	buf() << _result;
	buf() << _recipient_char_id;
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_REFUSE_VOLUNTEER
 */
void ZC_PARTY_RECRUIT_REFUSE_VOLUNTEER::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_REFUSE_VOLUNTEER::serialize()
{
	return buf();
}

/**
 * ZC_STOPMOVE_FORCE
 */
void ZC_STOPMOVE_FORCE::deliver() { }

ByteBuffer &ZC_STOPMOVE_FORCE::serialize()
{
	return buf();
}

/**
 * ZC_BATTLE_JOIN_NOTI_DEFER
 */
void ZC_BATTLE_JOIN_NOTI_DEFER::deliver() { }

ByteBuffer &ZC_BATTLE_JOIN_NOTI_DEFER::serialize()
{
	return buf();
}

/**
 * ZC_WHISPER
 */
void ZC_WHISPER::deliver(std::string name, std::string message, bool is_admin)
{
	strncpy(_name, name.c_str(), MAX_UNIT_NAME_LENGTH);
	_message = new char[message.size()];
	strncpy(_message, message.c_str(), message.size());
	_is_admin = (int32_t) is_admin;
	_packet_length = 8 + MAX_UNIT_NAME_LENGTH + message.size();

	serialize();
	transmit();
	
	delete[] _message;
}

ByteBuffer &ZC_WHISPER::serialize()
{
	buf() << _packet_id;
	buf() << _packet_length;
	buf().append(_name, MAX_UNIT_NAME_LENGTH);
	buf() << _is_admin;
	buf().append(_message, _packet_length - 8 - MAX_UNIT_NAME_LENGTH);
	return buf();
}

/**
 * ZC_BABYMSG
 */
void ZC_BABYMSG::deliver() { }

ByteBuffer &ZC_BABYMSG::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_VANISH
 */
void ZC_NOTIFY_VANISH::deliver(int32_t guid, entity_viewport_notification_type type)
{
	_guid = guid;
	_type = (int8_t) type;

	serialize();
	transmit();
}

ByteBuffer &ZC_NOTIFY_VANISH::serialize()
{
	buf() << _packet_id;
	buf() << _guid;
	buf() << _type;
	return buf();
}

/**
 * ZC_MAKINGARROW_LIST
 */
void ZC_MAKINGARROW_LIST::deliver() { }

ByteBuffer &ZC_MAKINGARROW_LIST::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REQ_JOIN_GUILD
 */
void ZC_ACK_REQ_JOIN_GUILD::deliver() { }

ByteBuffer &ZC_ACK_REQ_JOIN_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_CART_ITEMLIST_EQUIP_V6
 */
void ZC_CART_ITEMLIST_EQUIP_V6::deliver() { }

ByteBuffer &ZC_CART_ITEMLIST_EQUIP_V6::serialize()
{
	return buf();
}

/**
 * ZC_EFST_SET_ENTER2
 */
void ZC_EFST_SET_ENTER2::deliver() { }

ByteBuffer &ZC_EFST_SET_ENTER2::serialize()
{
	return buf();
}

/**
 * ZC_AUTOSPELLLIST
 */
void ZC_AUTOSPELLLIST::deliver() { }

ByteBuffer &ZC_AUTOSPELLLIST::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_STANDENTRY11
 */
void ZC_NOTIFY_STANDENTRY11::deliver(entity_viewport_entry entry)
{
	_entry = entry;
	serialize();
	transmit();
}

ByteBuffer &ZC_NOTIFY_STANDENTRY11::serialize()
{
	char packed_pos[3]{0};
	
	buf() << _packet_id;
	buf() << (int16_t) 104;
	buf() << (int8_t) _entry.unit_type;
	buf() << _entry.guid;
	buf() << _entry.character_id;
	buf() << _entry.speed;
	buf() << _entry.body_state;
	buf() <<_entry.health_state;
	buf() << _entry.effect_state;
	buf() << _entry.job_id;
	buf() << _entry.hair_style_id;
	buf() << _entry.weapon_id;
	buf() << _entry.headgear_bottom_id;
	buf() << _entry.headgear_top_id;
	buf() << _entry.headgear_mid_id;
	buf() << _entry.hair_color_id;
	buf() << _entry.cloth_color_id;
	buf() << (int16_t) _entry.head_direction;
	buf() << _entry.robe_id;
	buf() << _entry.guild_id;
	buf() << _entry.guild_emblem_version;
	buf() << _entry.honor;
	buf() << _entry.virtue;
	buf() << _entry.in_pk_mode;
	buf() << _entry.gender;
	PackPosition((int8_t *) packed_pos, _entry.current_x, _entry.current_y, _entry.current_dir);
	buf().append(packed_pos, sizeof(packed_pos));
	buf() << _entry.x_size;
	buf() << _entry.y_size;
	buf() << (int8_t) _entry.posture;
	buf() << _entry.base_level;
	buf() << _entry.font;
	buf() << _entry.max_hp;
	buf() << _entry.hp;
	buf() << _entry.is_boss;
	buf() << _entry.body_style_id;
	buf().append(_entry.name, sizeof(_entry.name));
	
	return buf();
}

/**
 * ZC_NOTIFY_STANDENTRY10
 */
void ZC_NOTIFY_STANDENTRY10::deliver() { }

ByteBuffer &ZC_NOTIFY_STANDENTRY10::serialize()
{
	return buf();
}

/**
 * ZC_KILLER_RANK
 */
void ZC_KILLER_RANK::deliver() { }

ByteBuffer &ZC_KILLER_RANK::serialize()
{
	return buf();
}

/**
 * ZC_ROOM_NEWENTRY
 */
void ZC_ROOM_NEWENTRY::deliver() { }

ByteBuffer &ZC_ROOM_NEWENTRY::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_FALL_ENTRY
 */
void ZC_ITEM_FALL_ENTRY::deliver() { }

ByteBuffer &ZC_ITEM_FALL_ENTRY::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_PLAYERMOVE
 */
void ZC_NOTIFY_PLAYERMOVE::deliver(int16_t from_x, int16_t from_y, int16_t to_x, int16_t to_y) 
{
	PackPosition(_packed_pos, from_x, from_y, to_x, to_y, 8, 8);
	_timestamp = (int32_t) get_sys_time();

	serialize();
	transmit();
}

ByteBuffer &ZC_NOTIFY_PLAYERMOVE::serialize()
{
	buf() << _packet_id;
	buf() << _timestamp;
	buf().append((char *) _packed_pos, sizeof(_packed_pos));
	return buf();
}

/**
 * ZC_SKILLMSG
 */
void ZC_SKILLMSG::deliver() { }

ByteBuffer &ZC_SKILLMSG::serialize()
{
	return buf();
}

/**
 * ZC_DELETE_FRIENDS
 */
void ZC_DELETE_FRIENDS::deliver() { }

ByteBuffer &ZC_DELETE_FRIENDS::serialize()
{
	return buf();
}

/**
 * ZC_LESSEFFECT
 */
void ZC_LESSEFFECT::deliver() { }

ByteBuffer &ZC_LESSEFFECT::serialize()
{
	return buf();
}

/**
 * ZC_ACK_CLOSE_ROULETTE
 */
void ZC_ACK_CLOSE_ROULETTE::deliver() { }

ByteBuffer &ZC_ACK_CLOSE_ROULETTE::serialize()
{
	return buf();
}

/**
 * ZC_GUILD_MEMBER_MAP_CHANGE
 */
void ZC_GUILD_MEMBER_MAP_CHANGE::deliver() { }

ByteBuffer &ZC_GUILD_MEMBER_MAP_CHANGE::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ADD_ITEM_RODEX
 */
void ZC_ACK_ADD_ITEM_RODEX::deliver() { }

ByteBuffer &ZC_ACK_ADD_ITEM_RODEX::serialize()
{
	return buf();
}

/**
 * ZC_ALL_QUEST_LIST
 */
void ZC_ALL_QUEST_LIST::deliver() { }

ByteBuffer &ZC_ALL_QUEST_LIST::serialize()
{
	return buf();
}

/**
 * ZC_CUSTOM_HAT_EFFECT
 */
void ZC_CUSTOM_HAT_EFFECT::deliver() { }

ByteBuffer &ZC_CUSTOM_HAT_EFFECT::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_PLAYERCHAT
 */
void ZC_NOTIFY_PLAYERCHAT::deliver(std::string &message)
{
	_message = message;
	_packet_length = 4 + message.size();

	serialize();
	transmit();
}

ByteBuffer &ZC_NOTIFY_PLAYERCHAT::serialize()
{
	buf() << _packet_id;
	buf() << _packet_length;
	buf().append(_message.c_str(), _message.size());
	return buf();
}

/**
 * ZC_HUNTING_QUEST_INFO
 */
void ZC_HUNTING_QUEST_INFO::deliver() { }

ByteBuffer &ZC_HUNTING_QUEST_INFO::serialize()
{
	return buf();
}

/**
 * ZC_REQ_JOIN_GROUP
 */
void ZC_REQ_JOIN_GROUP::deliver() { }

ByteBuffer &ZC_REQ_JOIN_GROUP::serialize()
{
	return buf();
}

/**
 * ZC_SHANDA_PROTECT
 */
void ZC_SHANDA_PROTECT::deliver() { }

ByteBuffer &ZC_SHANDA_PROTECT::serialize()
{
	return buf();
}

/**
 * ZC_STARPLACE
 */
void ZC_STARPLACE::deliver() { }

ByteBuffer &ZC_STARPLACE::serialize()
{
	return buf();
}

/**
 * ZC_ADD_QUEST
 */
void ZC_ADD_QUEST::deliver() { }

ByteBuffer &ZC_ADD_QUEST::serialize()
{
	return buf();
}

/**
 * ZC_REFUSE_ENTER_ROOM
 */
void ZC_REFUSE_ENTER_ROOM::deliver() { }

ByteBuffer &ZC_REFUSE_ENTER_ROOM::serialize()
{
	return buf();
}

/**
 * ZC_ACH_UPDATE
 */
void ZC_ACH_UPDATE::deliver() { }

ByteBuffer &ZC_ACH_UPDATE::serialize()
{
	return buf();
}

/**
 * ZC_ADD_FRIENDS_LIST
 */
void ZC_ADD_FRIENDS_LIST::deliver() { }

ByteBuffer &ZC_ADD_FRIENDS_LIST::serialize()
{
	return buf();
}

/**
 * ZC_MONSTER_INFO
 */
void ZC_MONSTER_INFO::deliver() { }

ByteBuffer &ZC_MONSTER_INFO::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_NOTIFY_DELETE
 */
void ZC_PARTY_RECRUIT_NOTIFY_DELETE::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_NOTIFY_DELETE::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_SKILL
 */
void ZC_NOTIFY_SKILL::deliver() { }

ByteBuffer &ZC_NOTIFY_SKILL::serialize()
{
	return buf();
}

/**
 * ZC_STORE_NORMAL_ITEMLIST3
 */
void ZC_STORE_NORMAL_ITEMLIST3::deliver() { }

ByteBuffer &ZC_STORE_NORMAL_ITEMLIST3::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_NEWENTRY3
 */
void ZC_NOTIFY_NEWENTRY3::deliver() { }

ByteBuffer &ZC_NOTIFY_NEWENTRY3::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_NEWENTRY2
 */
void ZC_NOTIFY_NEWENTRY2::deliver() { }

ByteBuffer &ZC_NOTIFY_NEWENTRY2::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_NEWENTRY7
 */
void ZC_NOTIFY_NEWENTRY7::deliver() { }

ByteBuffer &ZC_NOTIFY_NEWENTRY7::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_NEWENTRY6
 */
void ZC_NOTIFY_NEWENTRY6::deliver() { }

ByteBuffer &ZC_NOTIFY_NEWENTRY6::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_NEWENTRY5
 */
void ZC_NOTIFY_NEWENTRY5::deliver() 
{
	serialize();
	transmit();
}

ByteBuffer &ZC_NOTIFY_NEWENTRY5::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_NEWENTRY4
 */
void ZC_NOTIFY_NEWENTRY4::deliver() { }

ByteBuffer &ZC_NOTIFY_NEWENTRY4::serialize()
{
	return buf();
}

/**
 * ZC_MVP_GETTING_SPECIAL_EXP
 */
void ZC_MVP_GETTING_SPECIAL_EXP::deliver() { }

ByteBuffer &ZC_MVP_GETTING_SPECIAL_EXP::serialize()
{
	return buf();
}

/**
 * ZC_PC_PURCHASE_RESULT_FROMMC
 */
void ZC_PC_PURCHASE_RESULT_FROMMC::deliver() { }

ByteBuffer &ZC_PC_PURCHASE_RESULT_FROMMC::serialize()
{
	return buf();
}

/**
 * ZC_ACK_BEFORE_WORLD_INFO
 */
void ZC_ACK_BEFORE_WORLD_INFO::deliver() { }

ByteBuffer &ZC_ACK_BEFORE_WORLD_INFO::serialize()
{
	return buf();
}

/**
 * ZC_NPCACK_ENABLE
 */
void ZC_NPCACK_ENABLE::deliver() { }

ByteBuffer &ZC_NPCACK_ENABLE::serialize()
{
	return buf();
}

/**
 * ZC_ACK_CLAN_LEAVE
 */
void ZC_ACK_CLAN_LEAVE::deliver() { }

ByteBuffer &ZC_ACK_CLAN_LEAVE::serialize()
{
	return buf();
}

/**
 * ZC_ES_GOTO
 */
void ZC_ES_GOTO::deliver() { }

ByteBuffer &ZC_ES_GOTO::serialize()
{
	return buf();
}

/**
 * ZC_STYLE_CHANGE_RES
 */
void ZC_STYLE_CHANGE_RES::deliver() { }

ByteBuffer &ZC_STYLE_CHANGE_RES::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_ACTENTRY
 */
void ZC_NOTIFY_ACTENTRY::deliver() { }

ByteBuffer &ZC_NOTIFY_ACTENTRY::serialize()
{
	return buf();
}

/**
 * ZC_ACK_DISORGANIZE_GUILD_RESULT
 */
void ZC_ACK_DISORGANIZE_GUILD_RESULT::deliver() { }

ByteBuffer &ZC_ACK_DISORGANIZE_GUILD_RESULT::serialize()
{
	return buf();
}

/**
 * ZC_ACK_CLOSE_GUILD_STORAGE
 */
void ZC_ACK_CLOSE_GUILD_STORAGE::deliver() { }

ByteBuffer &ZC_ACK_CLOSE_GUILD_STORAGE::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_BOOKING_ACK_SEARCH
 */
void ZC_PARTY_BOOKING_ACK_SEARCH::deliver() { }

ByteBuffer &ZC_PARTY_BOOKING_ACK_SEARCH::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REQ_JOIN_GROUP
 */
void ZC_ACK_REQ_JOIN_GROUP::deliver() { }

ByteBuffer &ZC_ACK_REQ_JOIN_GROUP::serialize()
{
	return buf();
}

/**
 * ZC_ACK_TAKEOFF_EQUIP_V5
 */
void ZC_ACK_TAKEOFF_EQUIP_V5::deliver(int16_t inventory_index, int32_t equip_location_mask, item_unequip_result_type result) 
{
	_inventory_index = inventory_index;
	_equip_location_mask = equip_location_mask;
	_result = (int8_t) result;

	serialize();
	transmit();
}

ByteBuffer &ZC_ACK_TAKEOFF_EQUIP_V5::serialize()
{
	buf() << _packet_id;
	buf() << _inventory_index;
	buf() << _equip_location_mask;
	buf() << _result;
	return buf();
}

/**
 * ZC_BATTLEFIELD_NOTIFY_CAMPINFO
 */
void ZC_BATTLEFIELD_NOTIFY_CAMPINFO::deliver() { }

ByteBuffer &ZC_BATTLEFIELD_NOTIFY_CAMPINFO::serialize()
{
	return buf();
}

/**
 * ZC_RESULT_CASH_PASSWORD
 */
void ZC_RESULT_CASH_PASSWORD::deliver() { }

ByteBuffer &ZC_RESULT_CASH_PASSWORD::serialize()
{
	return buf();
}

/**
 * ZC_CLEAR_DIALOG
 */
void ZC_CLEAR_DIALOG::deliver() { }

ByteBuffer &ZC_CLEAR_DIALOG::serialize()
{
	return buf();
}

/**
 * ZC_MENU_LIST
 */
void ZC_MENU_LIST::deliver(int32_t guid, std::string const &menu)
{
	_menu_items = menu;
	_packet_length = menu.size() + 8;
	_guid = guid;

	serialize();
	transmit();
}

ByteBuffer &ZC_MENU_LIST::serialize()
{
	buf() << _packet_id;
	buf() << _packet_length;
	buf() << _guid;
	buf().append(_menu_items.c_str(), _menu_items.size());
	return buf();
}

/**
 * ZC_NOTIFY_GROUNDSKILL
 */
void ZC_NOTIFY_GROUNDSKILL::deliver(int16_t skill_id, int32_t guid, int16_t level, int16_t x, int16_t y, int32_t duration)
{
	_skill_id = skill_id;
	_guid = guid;
	_level = level;
	_x = x;
	_y = y;
	_duration = duration;

	serialize();
	transmit();
}

ByteBuffer &ZC_NOTIFY_GROUNDSKILL::serialize()
{
	buf() << _packet_id;
	buf() << _skill_id;
	buf() << _guid;
	buf() << _level;
	buf() << _x;
	buf() << _y;
	buf() << _duration;
	return buf();
}

/**
 * ZC_CANCEL_EXCHANGE_ITEM
 */
void ZC_CANCEL_EXCHANGE_ITEM::deliver() { }

ByteBuffer &ZC_CANCEL_EXCHANGE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_ENTRY_QUEUE_APPLY
 */
void ZC_NOTIFY_ENTRY_QUEUE_APPLY::deliver() { }

ByteBuffer &ZC_NOTIFY_ENTRY_QUEUE_APPLY::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_BOOKING_NOTIFY_INSERT
 */
void ZC_PARTY_BOOKING_NOTIFY_INSERT::deliver() { }

ByteBuffer &ZC_PARTY_BOOKING_NOTIFY_INSERT::serialize()
{
	return buf();
}

/**
 * ZC_COSTUME_SPRITE_CHANGE
 */
void ZC_COSTUME_SPRITE_CHANGE::deliver() { }

ByteBuffer &ZC_COSTUME_SPRITE_CHANGE::serialize()
{
	return buf();
}

/**
 * ZC_AUCTION_ACK_MY_SELL_STOP
 */
void ZC_AUCTION_ACK_MY_SELL_STOP::deliver() { }

ByteBuffer &ZC_AUCTION_ACK_MY_SELL_STOP::serialize()
{
	return buf();
}

/**
 * ZC_REQ_JOIN_GUILD
 */
void ZC_REQ_JOIN_GUILD::deliver() { }

ByteBuffer &ZC_REQ_JOIN_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_GAMEGUARD_LINGO_KEY
 */
void ZC_GAMEGUARD_LINGO_KEY::deliver() { }

ByteBuffer &ZC_GAMEGUARD_LINGO_KEY::serialize()
{
	return buf();
}

/**
 * ZC_DELETE_ITEM_FROM_STORE
 */
void ZC_DELETE_ITEM_FROM_STORE::deliver() { }

ByteBuffer &ZC_DELETE_ITEM_FROM_STORE::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MOVEENTRY7
 */
void ZC_NOTIFY_MOVEENTRY7::deliver() { }

ByteBuffer &ZC_NOTIFY_MOVEENTRY7::serialize()
{
	return buf();
}

/**
 * ZC_PREMIUM_CAMPAIGN_INFO
 */
void ZC_PREMIUM_CAMPAIGN_INFO::deliver() { }

ByteBuffer &ZC_PREMIUM_CAMPAIGN_INFO::serialize()
{
	return buf();
}

/**
 * ZC_COMPASS
 */
void ZC_COMPASS::deliver() { }

ByteBuffer &ZC_COMPASS::serialize()
{
	return buf();
}

/**
 * ZC_STOPMOVE
 */
void ZC_STOPMOVE::deliver(int32_t guid, int16_t x, int16_t y)
{
	_guid = guid;
	_x = x;
	_y = y;

	serialize();
	transmit();
}

ByteBuffer &ZC_STOPMOVE::serialize()
{
	buf() << _packet_id;
	buf() << _guid;
	buf() << _x;
	buf() << _y;
	return buf();
}

/**
 * ZC_GUILDSTORAGE_ITEMLIST_NORMAL_V5
 */
void ZC_GUILDSTORAGE_ITEMLIST_NORMAL_V5::deliver() { }

ByteBuffer &ZC_GUILDSTORAGE_ITEMLIST_NORMAL_V5::serialize()
{
	return buf();
}

/**
 * ZC_STORE_ITEMLIST_NORMAL
 */
void ZC_STORE_ITEMLIST_NORMAL::deliver() { }

ByteBuffer &ZC_STORE_ITEMLIST_NORMAL::serialize()
{
	return buf();
}

/**
 * ZC_UPDATE_RANKING_POINT
 */
void ZC_UPDATE_RANKING_POINT::deliver() { }

ByteBuffer &ZC_UPDATE_RANKING_POINT::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_PKINFO
 */
void ZC_NOTIFY_PKINFO::deliver() { }

ByteBuffer &ZC_NOTIFY_PKINFO::serialize()
{
	return buf();
}

/**
 * ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY
 */
void ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY::deliver() { }

ByteBuffer &ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY::serialize()
{
	return buf();
}

/**
 * ZC_HIGHJUMP
 */
void ZC_HIGHJUMP::deliver() { }

ByteBuffer &ZC_HIGHJUMP::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REQNAMEALL
 */
void ZC_ACK_REQNAMEALL::deliver(int32_t guid, std::string name, std::string party_name, std::string guild_name, std::string position_name)
{
	_guid = guid;
	strncpy(_name, name.c_str(), MAX_UNIT_NAME_LENGTH);
	strncpy(_party_name, party_name.c_str(), MAX_UNIT_NAME_LENGTH);
	strncpy(_guild_name, guild_name.c_str(), MAX_UNIT_NAME_LENGTH);
	strncpy(_position_name, position_name.c_str(), MAX_UNIT_NAME_LENGTH);
	
	serialize();
	transmit();
}

ByteBuffer &ZC_ACK_REQNAMEALL::serialize()
{
	buf() << _packet_id;
	buf() << _guid;
	buf().append(_name, MAX_UNIT_NAME_LENGTH);
	buf().append(_party_name, MAX_UNIT_NAME_LENGTH);
	buf().append(_guild_name, MAX_UNIT_NAME_LENGTH);
	buf().append(_position_name, MAX_UNIT_NAME_LENGTH);
	
	return buf();
}

/**
 * ZC_BAN_LIST
 */
void ZC_BAN_LIST::deliver() { }

ByteBuffer &ZC_BAN_LIST::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ROULEITTE_INFO
 */
void ZC_ACK_ROULEITTE_INFO::deliver() { }

ByteBuffer &ZC_ACK_ROULEITTE_INFO::serialize()
{
	return buf();
}

/**
 * ZC_UNUSED_SRPACKET_INIT
 */
void ZC_UNUSED_SRPACKET_INIT::deliver() { }

ByteBuffer &ZC_UNUSED_SRPACKET_INIT::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_CONFIG
 */
void ZC_PARTY_CONFIG::deliver() { }

ByteBuffer &ZC_PARTY_CONFIG::serialize()
{
	return buf();
}

/**
 * ZC_BROADCAST4
 */
void ZC_BROADCAST4::deliver() { }

ByteBuffer &ZC_BROADCAST4::serialize()
{
	return buf();
}

/**
 * ZC_GUILD_NOTICE
 */
void ZC_GUILD_NOTICE::deliver() { }

ByteBuffer &ZC_GUILD_NOTICE::serialize()
{
	return buf();
}

/**
 * ZC_BROADCAST2
 */
void ZC_BROADCAST2::deliver() { }

ByteBuffer &ZC_BROADCAST2::serialize()
{
	return buf();
}

/**
 * ZC_ADD_RELATED_GUILD
 */
void ZC_ADD_RELATED_GUILD::deliver() { }

ByteBuffer &ZC_ADD_RELATED_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_ACK_OPEN_WRITE_RODEX
 */
void ZC_ACK_OPEN_WRITE_RODEX::deliver() { }

ByteBuffer &ZC_ACK_OPEN_WRITE_RODEX::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_HP_TO_GROUPM
 */
void ZC_NOTIFY_HP_TO_GROUPM::deliver() { }

ByteBuffer &ZC_NOTIFY_HP_TO_GROUPM::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_PICKUP_ACK3
 */
void ZC_ITEM_PICKUP_ACK3::deliver() { }

ByteBuffer &ZC_ITEM_PICKUP_ACK3::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_PICKUP_ACK2
 */
void ZC_ITEM_PICKUP_ACK2::deliver() { }

ByteBuffer &ZC_ITEM_PICKUP_ACK2::serialize()
{
	return buf();
}

/**
 * ZC_INVENTORY_ITEMLIST_NORMAL
 */
void ZC_INVENTORY_ITEMLIST_NORMAL::deliver() { }

ByteBuffer &ZC_INVENTORY_ITEMLIST_NORMAL::serialize()
{
	return buf();
}

/**
 * ZC_EL_INIT
 */
void ZC_EL_INIT::deliver() { }

ByteBuffer &ZC_EL_INIT::serialize()
{
	return buf();
}

/**
 * ZC_AOE_EFFECT_SKILL
 */
void ZC_AOE_EFFECT_SKILL::deliver() { }

ByteBuffer &ZC_AOE_EFFECT_SKILL::serialize()
{
	return buf();
}

/**
 * ZC_SPIRITS
 */
void ZC_SPIRITS::deliver() { }

ByteBuffer &ZC_SPIRITS::serialize()
{
	return buf();
}

/**
 * ZC_CART_ITEMLIST_NORMAL_V5
 */
void ZC_CART_ITEMLIST_NORMAL_V5::deliver() { }

ByteBuffer &ZC_CART_ITEMLIST_NORMAL_V5::serialize()
{
	return buf();
}

/**
 * ZC_CHANGESTATE_PET
 */
void ZC_CHANGESTATE_PET::deliver() { }

ByteBuffer &ZC_CHANGESTATE_PET::serialize()
{
	return buf();
}

/**
 * ZC_ATTACK_FAILURE_FOR_DISTANCE
 */
void ZC_ATTACK_FAILURE_FOR_DISTANCE::deliver() { }

ByteBuffer &ZC_ATTACK_FAILURE_FOR_DISTANCE::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_BARGAIN_SALE_CLOSE
 */
void ZC_NOTIFY_BARGAIN_SALE_CLOSE::deliver() { }

ByteBuffer &ZC_NOTIFY_BARGAIN_SALE_CLOSE::serialize()
{
	return buf();
}

/**
 * ZC_GOLDPCCAFE_POINT
 */
void ZC_GOLDPCCAFE_POINT::deliver() { }

ByteBuffer &ZC_GOLDPCCAFE_POINT::serialize()
{
	return buf();
}

/**
 * ZC_REQ_ADD_FRIENDS
 */
void ZC_REQ_ADD_FRIENDS::deliver() { }

ByteBuffer &ZC_REQ_ADD_FRIENDS::serialize()
{
	return buf();
}

/**
 * ZC_GANGSI_POINT
 */
void ZC_GANGSI_POINT::deliver() { }

ByteBuffer &ZC_GANGSI_POINT::serialize()
{
	return buf();
}

/**
 * ZC_ACK_AUCTION_ADD_ITEM
 */
void ZC_ACK_AUCTION_ADD_ITEM::deliver() { }

ByteBuffer &ZC_ACK_AUCTION_ADD_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_BOOKING_NOTIFY_DELETE
 */
void ZC_PARTY_BOOKING_NOTIFY_DELETE::deliver() { }

ByteBuffer &ZC_PARTY_BOOKING_NOTIFY_DELETE::serialize()
{
	return buf();
}

/**
 * ZC_REQ_STORE_PASSWORD
 */
void ZC_REQ_STORE_PASSWORD::deliver() { }

ByteBuffer &ZC_REQ_STORE_PASSWORD::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_UPDATECHAR
 */
void ZC_NOTIFY_UPDATECHAR::deliver() { }

ByteBuffer &ZC_NOTIFY_UPDATECHAR::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER
 */
void ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER::serialize()
{
	return buf();
}

/**
 * ZC_REQ_EXCHANGE_ITEM
 */
void ZC_REQ_EXCHANGE_ITEM::deliver() { }

ByteBuffer &ZC_REQ_EXCHANGE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_SELECT_DEALTYPE
 */
void ZC_SELECT_DEALTYPE::deliver() { }

ByteBuffer &ZC_SELECT_DEALTYPE::serialize()
{
	return buf();
}

/**
 * ZC_ALL_ACH_LIST
 */
void ZC_ALL_ACH_LIST::deliver() { }

ByteBuffer &ZC_ALL_ACH_LIST::serialize()
{
	return buf();
}

/**
 * ZC_MSG_COLOR
 */
void ZC_MSG_COLOR::deliver() { }

ByteBuffer &ZC_MSG_COLOR::serialize()
{
	return buf();
}

/**
 * ZC_REQ_TAKEOFF_EQUIP_ACK
 */
void ZC_REQ_TAKEOFF_EQUIP_ACK::deliver(int16_t index, int16_t equip_location_mask, item_unequip_result_type result)
{
	_index = index;
	_equip_location_mask = equip_location_mask;
	_result = (int8_t) result;

	serialize();
	transmit();
}

ByteBuffer &ZC_REQ_TAKEOFF_EQUIP_ACK::serialize()
{
	buf() << _packet_id;
	buf() << _index;
	buf() << _equip_location_mask;
	buf() << _result;
	return buf();
}

/**
 * ZC_REQ_EXCHANGE_ITEM2
 */
void ZC_REQ_EXCHANGE_ITEM2::deliver() { }

ByteBuffer &ZC_REQ_EXCHANGE_ITEM2::serialize()
{
	return buf();
}

/**
 * ZC_DELETEITEM_FROM_MCSTORE2
 */
void ZC_DELETEITEM_FROM_MCSTORE2::deliver() { }

ByteBuffer &ZC_DELETEITEM_FROM_MCSTORE2::serialize()
{
	return buf();
}

/**
 * ZC_ES_RESULT
 */
void ZC_ES_RESULT::deliver() { }

ByteBuffer &ZC_ES_RESULT::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_CARTITEM_COUNTINFO
 */
void ZC_NOTIFY_CARTITEM_COUNTINFO::deliver() { }

ByteBuffer &ZC_NOTIFY_CARTITEM_COUNTINFO::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_ENTRY_QUEUE_ADMISSION
 */
void ZC_NOTIFY_ENTRY_QUEUE_ADMISSION::deliver() { }

ByteBuffer &ZC_NOTIFY_ENTRY_QUEUE_ADMISSION::serialize()
{
	return buf();
}

/**
 * ZC_MAPPROPERTY_R2
 */
void ZC_MAPPROPERTY_R2::deliver(zc_map_properties p) 
{
	memcpy(&_p, &p, sizeof(int32_t));

	serialize();
	transmit();
}

ByteBuffer &ZC_MAPPROPERTY_R2::serialize()
{
	buf() << _packet_id;
	buf() << _type;
	buf() << _p;
	return buf();
}

/**
 * ZC_JOIN_BATTLE_FIELD
 */
void ZC_JOIN_BATTLE_FIELD::deliver() { }

ByteBuffer &ZC_JOIN_BATTLE_FIELD::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MOVEENTRY10
 */
void ZC_NOTIFY_MOVEENTRY10::deliver() { }

ByteBuffer &ZC_NOTIFY_MOVEENTRY10::serialize()
{
	return buf();
}

/**
 * ZC_SE_CASHSHOP_OPEN2
 */
void ZC_SE_CASHSHOP_OPEN2::deliver() { }

ByteBuffer &ZC_SE_CASHSHOP_OPEN2::serialize()
{
	return buf();
}

/**
 * ZC_CART_ITEMLIST_NORMAL
 */
void ZC_CART_ITEMLIST_NORMAL::deliver() { }

ByteBuffer &ZC_CART_ITEMLIST_NORMAL::serialize()
{
	return buf();
}

/**
 * ZC_MER_INIT
 */
void ZC_MER_INIT::deliver() { }

ByteBuffer &ZC_MER_INIT::serialize()
{
	return buf();
}

/**
 * ZC_TALKBOX_CHATCONTENTS
 */
void ZC_TALKBOX_CHATCONTENTS::deliver() { }

ByteBuffer &ZC_TALKBOX_CHATCONTENTS::serialize()
{
	return buf();
}

/**
 * ZC_PC_SELL_ITEMLIST
 */
void ZC_PC_SELL_ITEMLIST::deliver() { }

ByteBuffer &ZC_PC_SELL_ITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_PCBANG_PLAYING_TIME
 */
void ZC_NOTIFY_PCBANG_PLAYING_TIME::deliver() { }

ByteBuffer &ZC_NOTIFY_PCBANG_PLAYING_TIME::serialize()
{
	return buf();
}

/**
 * ZC_UPDATE_CHARSTAT
 */
void ZC_UPDATE_CHARSTAT::deliver() { }

ByteBuffer &ZC_UPDATE_CHARSTAT::serialize()
{
	return buf();
}

/**
 * ZC_NPCACK_SERVERMOVE
 */
void ZC_NPCACK_SERVERMOVE::deliver() { }

ByteBuffer &ZC_NPCACK_SERVERMOVE::serialize()
{
	return buf();
}

/**
 * ZC_ACK_BAN_GUILD
 */
void ZC_ACK_BAN_GUILD::deliver() { }

ByteBuffer &ZC_ACK_BAN_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_JOIN_REQ_ACK
 */
void ZC_PARTY_JOIN_REQ_ACK::deliver() { }

ByteBuffer &ZC_PARTY_JOIN_REQ_ACK::serialize()
{
	return buf();
}

/**
 * ZC_ADD_ITEM_TO_CART3
 */
void ZC_ADD_ITEM_TO_CART3::deliver() { }

ByteBuffer &ZC_ADD_ITEM_TO_CART3::serialize()
{
	return buf();
}

/**
 * ZC_PROPERTY_MERCE
 */
void ZC_PROPERTY_MERCE::deliver() { }

ByteBuffer &ZC_PROPERTY_MERCE::serialize()
{
	return buf();
}

/**
 * ZC_MICROSCOPE
 */
void ZC_MICROSCOPE::deliver() { }

ByteBuffer &ZC_MICROSCOPE::serialize()
{
	return buf();
}

/**
 * ZC_ADD_ITEM_TO_STORE2
 */
void ZC_ADD_ITEM_TO_STORE2::deliver() { }

ByteBuffer &ZC_ADD_ITEM_TO_STORE2::serialize()
{
	return buf();
}

/**
 * ZC_SKILLINFO_UPDATE2
 */
void ZC_SKILLINFO_UPDATE2::deliver() { }

ByteBuffer &ZC_SKILLINFO_UPDATE2::serialize()
{
	return buf();
}

/**
 * ZC_BOSS_INFO
 */
void ZC_BOSS_INFO::deliver() { }

ByteBuffer &ZC_BOSS_INFO::serialize()
{
	return buf();
}

/**
 * ZC_ALL_QUEST_MISSION
 */
void ZC_ALL_QUEST_MISSION::deliver() { }

ByteBuffer &ZC_ALL_QUEST_MISSION::serialize()
{
	return buf();
}

/**
 * ZC_PC_PURCHASE_MYITEMLIST
 */
void ZC_PC_PURCHASE_MYITEMLIST::deliver() { }

ByteBuffer &ZC_PC_PURCHASE_MYITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_USER_COUNT
 */
void ZC_USER_COUNT::deliver() { }

ByteBuffer &ZC_USER_COUNT::serialize()
{
	return buf();
}

/**
 * ZC_ITEMCOMPOSITION_LIST
 */
void ZC_ITEMCOMPOSITION_LIST::deliver() { }

ByteBuffer &ZC_ITEMCOMPOSITION_LIST::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REQ_HOSTILE_GUILD
 */
void ZC_ACK_REQ_HOSTILE_GUILD::deliver() { }

ByteBuffer &ZC_ACK_REQ_HOSTILE_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_SKILLINFO_UPDATE
 */
void ZC_SKILLINFO_UPDATE::deliver() { }

ByteBuffer &ZC_SKILLINFO_UPDATE::serialize()
{
	return buf();
}

/**
 * ZC_ADD_SKILL
 */
void ZC_ADD_SKILL::deliver() { }

ByteBuffer &ZC_ADD_SKILL::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_EXP
 */
void ZC_NOTIFY_EXP::deliver() { }

ByteBuffer &ZC_NOTIFY_EXP::serialize()
{
	return buf();
}

/**
 * ZC_CONGRATULATION
 */
void ZC_CONGRATULATION::deliver() { }

ByteBuffer &ZC_CONGRATULATION::serialize()
{
	return buf();
}

/**
 * ZC_CHANGE_GUILD
 */
void ZC_CHANGE_GUILD::deliver() { }

ByteBuffer &ZC_CHANGE_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_PROGRESS_CANCEL
 */
void ZC_PROGRESS_CANCEL::deliver() { }

ByteBuffer &ZC_PROGRESS_CANCEL::serialize()
{
	return buf();
}

/**
 * ZC_LONGPAR_CHANGE
 */
void ZC_LONGPAR_CHANGE::deliver(status_point_type type, int16_t value)
{
	_type = type;
	_value = value;

	serialize();
	transmit();
}

ByteBuffer &ZC_LONGPAR_CHANGE::serialize()
{
	buf() << _packet_id;
	buf() << (int16_t) _type;
	buf() << _value;
	return buf();
}

/**
 * ZC_SKILL_POSTDELAY_LIST
 */
void ZC_SKILL_POSTDELAY_LIST::deliver() { }

ByteBuffer &ZC_SKILL_POSTDELAY_LIST::serialize()
{
	return buf();
}

/**
 * ZC_INVENTORY_EXPANSION_INFO
 */
void ZC_INVENTORY_EXPANSION_INFO::deliver() { }

ByteBuffer &ZC_INVENTORY_EXPANSION_INFO::serialize()
{
	return buf();
}

/**
 * ZC_STORE_ITEMLIST_NORMAL_V2
 */
void ZC_STORE_ITEMLIST_NORMAL_V2::deliver() { }

ByteBuffer &ZC_STORE_ITEMLIST_NORMAL_V2::serialize()
{
	return buf();
}

/**
 * ZC_OPEN_UI
 */
void ZC_OPEN_UI::deliver() { }

ByteBuffer &ZC_OPEN_UI::serialize()
{
	return buf();
}

/**
 * ZC_STORE_ITEMLIST_NORMAL_V6
 */
void ZC_STORE_ITEMLIST_NORMAL_V6::deliver() { }

ByteBuffer &ZC_STORE_ITEMLIST_NORMAL_V6::serialize()
{
	return buf();
}

/**
 * ZC_ACK_MAIL_RETURN
 */
void ZC_ACK_MAIL_RETURN::deliver() { }

ByteBuffer &ZC_ACK_MAIL_RETURN::serialize()
{
	return buf();
}

/**
 * ZC_BATTLEFIELD_NOTIFY_HP2
 */
void ZC_BATTLEFIELD_NOTIFY_HP2::deliver() { }

ByteBuffer &ZC_BATTLEFIELD_NOTIFY_HP2::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MAPPROPERTY2
 */
void ZC_NOTIFY_MAPPROPERTY2::deliver() { }

ByteBuffer &ZC_NOTIFY_MAPPROPERTY2::serialize()
{
	return buf();
}

/**
 * ZC_SIMPLE_CASH_BTNSHOW
 */
void ZC_SIMPLE_CASH_BTNSHOW::deliver() { }

ByteBuffer &ZC_SIMPLE_CASH_BTNSHOW::serialize()
{
	return buf();
}

/**
 * ZC_MSG
 */
void ZC_MSG::deliver() { }

ByteBuffer &ZC_MSG::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM
 */
void ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM::serialize()
{
	return buf();
}

/**
 * ZC_FEED_MER
 */
void ZC_FEED_MER::deliver() { }

ByteBuffer &ZC_FEED_MER::serialize()
{
	return buf();
}

/**
 * ZC_SEARCH_STORE_INFO_ACK
 */
void ZC_SEARCH_STORE_INFO_ACK::deliver() { }

ByteBuffer &ZC_SEARCH_STORE_INFO_ACK::serialize()
{
	return buf();
}

/**
 * ZC_NPC_MARKET_OPEN
 */
void ZC_NPC_MARKET_OPEN::deliver() { }

ByteBuffer &ZC_NPC_MARKET_OPEN::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_PICKUP_ACK_V6
 */
void ZC_ITEM_PICKUP_ACK_V6::deliver() { }

ByteBuffer &ZC_ITEM_PICKUP_ACK_V6::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_PICKUP_ACK_V7
 */
void ZC_ITEM_PICKUP_ACK_V7::deliver(item_entry_data id, int16_t amount, item_inventory_addition_notif_type result)
{
	_id = id;
	_amount = amount;
	_result = result;

	serialize();
	transmit();
}

ByteBuffer &ZC_ITEM_PICKUP_ACK_V7::serialize()
{
	buf() << _packet_id;
	buf() << _id.inventory_index;
	buf() << _amount;
	buf() << (int16_t) _id.item_id;
	buf() << (int8_t) (_id.info.is_identified ? 1 : 0);
	buf() << (int8_t) (_id.info.is_broken ? 1 : 0 );
	buf() << _id.refine_level;

	for (int i = 0; i < MAX_ITEM_SLOTS; i++)
		buf() << (int16_t) _id.slot_item_id[i];

	buf() << _id.actual_equip_location_mask;
	buf() << (int8_t) _id.type;
	buf() << (int8_t) _result;
	buf() << _id.hire_expire_date;
	buf() << (int16_t) _id.bind_type;

	for (int i = 0; i < MAX_ITEM_OPTIONS; i++) {
		buf() << _id.option_data[i].index;
		buf() << _id.option_data[i].value;
		buf() << _id.option_data[i].param;
	}

	buf() << (int8_t) (_id.info.is_favorite ? 1 : 0);
	buf() << _id.sprite_id;
	return buf();
}

/**
 * ZC_SKILL_DISAPPEAR
 */
void ZC_SKILL_DISAPPEAR::deliver() { }

ByteBuffer &ZC_SKILL_DISAPPEAR::serialize()
{
	return buf();
}

/**
 * ZC_CART_EQUIPMENT_ITEMLIST
 */
void ZC_CART_EQUIPMENT_ITEMLIST::deliver() { }

ByteBuffer &ZC_CART_EQUIPMENT_ITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_CONCLUDE_EXCHANGE_ITEM
 */
void ZC_CONCLUDE_EXCHANGE_ITEM::deliver() { }

ByteBuffer &ZC_CONCLUDE_EXCHANGE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_PET_ACT
 */
void ZC_PET_ACT::deliver() { }

ByteBuffer &ZC_PET_ACT::serialize()
{
	return buf();
}

/**
 * ZC_OTHER_GUILD_LIST
 */
void ZC_OTHER_GUILD_LIST::deliver() { }

ByteBuffer &ZC_OTHER_GUILD_LIST::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ENTRY_QUEUE_APPLY
 */
void ZC_ACK_ENTRY_QUEUE_APPLY::deliver() { }

ByteBuffer &ZC_ACK_ENTRY_QUEUE_APPLY::serialize()
{
	return buf();
}

/**
 * ZC_HACKSH_CPX_MSG
 */
void ZC_HACKSH_CPX_MSG::deliver() { }

ByteBuffer &ZC_HACKSH_CPX_MSG::serialize()
{
	return buf();
}

/**
 * ZC_BATTLE_JOIN_DISABLE_STATE
 */
void ZC_BATTLE_JOIN_DISABLE_STATE::deliver() { }

ByteBuffer &ZC_BATTLE_JOIN_DISABLE_STATE::serialize()
{
	return buf();
}

/**
 * ZC_UPDATE_CHARSTAT2
 */
void ZC_UPDATE_CHARSTAT2::deliver() { }

ByteBuffer &ZC_UPDATE_CHARSTAT2::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_POSITION_TO_GUILDM
 */
void ZC_NOTIFY_POSITION_TO_GUILDM::deliver() { }

ByteBuffer &ZC_NOTIFY_POSITION_TO_GUILDM::serialize()
{
	return buf();
}

/**
 * ZC_MONSTER_TALK
 */
void ZC_MONSTER_TALK::deliver() { }

ByteBuffer &ZC_MONSTER_TALK::serialize()
{
	return buf();
}

/**
 * ZC_ACCEPT_QUIT
 */
void ZC_ACCEPT_QUIT::deliver() { }

ByteBuffer &ZC_ACCEPT_QUIT::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_PICKUP_ACK_V5
 */
void ZC_ITEM_PICKUP_ACK_V5::deliver() { }

ByteBuffer &ZC_ITEM_PICKUP_ACK_V5::serialize()
{
	return buf();
}

/**
 * ZC_FEED_PET
 */
void ZC_FEED_PET::deliver() { }

ByteBuffer &ZC_FEED_PET::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_BOOKING_ACK_DELETE
 */
void ZC_PARTY_BOOKING_ACK_DELETE::deliver() { }

ByteBuffer &ZC_PARTY_BOOKING_ACK_DELETE::serialize()
{
	return buf();
}

/**
 * ZC_PROGRESS_ACTOR
 */
void ZC_PROGRESS_ACTOR::deliver() { }

ByteBuffer &ZC_PROGRESS_ACTOR::serialize()
{
	return buf();
}

/**
 * ZC_SKILL_POSTDELAY
 */
void ZC_SKILL_POSTDELAY::deliver() { }

ByteBuffer &ZC_SKILL_POSTDELAY::serialize()
{
	return buf();
}

/**
 * ZC_REQ_TAKEOFF_EQUIP_ACK2
 */
void ZC_REQ_TAKEOFF_EQUIP_ACK2::deliver(int16_t inventory_index, int32_t equip_location_mask, item_unequip_result_type result)
{
	_inventory_index = inventory_index;
	_equip_location_mask = equip_location_mask;
	_result = (int8_t) result;

	serialize();
	transmit();
}

ByteBuffer &ZC_REQ_TAKEOFF_EQUIP_ACK2::serialize()
{
	buf() << _packet_id;
	buf() << _inventory_index;
	buf() << _equip_location_mask;
	buf() << _result;
	return buf();
}

/**
 * ZC_STARSKILL
 */
void ZC_STARSKILL::deliver() { }

ByteBuffer &ZC_STARSKILL::serialize()
{
	return buf();
}

/**
 * ZC_SE_CASHSHOP_UPDATE
 */
void ZC_SE_CASHSHOP_UPDATE::deliver() { }

ByteBuffer &ZC_SE_CASHSHOP_UPDATE::serialize()
{
	return buf();
}

/**
 * ZC_GUILDSTORAGE_ITEMLIST_EQUIP_V5
 */
void ZC_GUILDSTORAGE_ITEMLIST_EQUIP_V5::deliver() { }

ByteBuffer &ZC_GUILDSTORAGE_ITEMLIST_EQUIP_V5::serialize()
{
	return buf();
}

/**
 * ZC_OPEN_RODEX_THROUGH_NPC_ONLY
 */
void ZC_OPEN_RODEX_THROUGH_NPC_ONLY::deliver() { }

ByteBuffer &ZC_OPEN_RODEX_THROUGH_NPC_ONLY::serialize()
{
	return buf();
}

/**
 * ZC_GUILDSTORAGE_ITEMLIST_EQUIP_V6
 */
void ZC_GUILDSTORAGE_ITEMLIST_EQUIP_V6::deliver() { }

ByteBuffer &ZC_GUILDSTORAGE_ITEMLIST_EQUIP_V6::serialize()
{
	return buf();
}

/**
 * ZC_READ_BOOK
 */
void ZC_READ_BOOK::deliver() { }

ByteBuffer &ZC_READ_BOOK::serialize()
{
	return buf();
}

/**
 * ZC_BATTLE_NOTI_START_STEP
 */
void ZC_BATTLE_NOTI_START_STEP::deliver() { }

ByteBuffer &ZC_BATTLE_NOTI_START_STEP::serialize()
{
	return buf();
}

/**
 * ZC_FASTMOVE
 */
void ZC_FASTMOVE::deliver() { }

ByteBuffer &ZC_FASTMOVE::serialize()
{
	return buf();
}

/**
 * ZC_POSITION_INFO
 */
void ZC_POSITION_INFO::deliver() { }

ByteBuffer &ZC_POSITION_INFO::serialize()
{
	return buf();
}

/**
 * ZC_INVENTORY_TAB
 */
void ZC_INVENTORY_TAB::deliver() { }

ByteBuffer &ZC_INVENTORY_TAB::serialize()
{
	return buf();
}

/**
 * ZC_DELETE_MEMBER_FROM_GROUP
 */
void ZC_DELETE_MEMBER_FROM_GROUP::deliver() { }

ByteBuffer &ZC_DELETE_MEMBER_FROM_GROUP::serialize()
{
	return buf();
}

/**
 * ZC_MER_PROPERTY
 */
void ZC_MER_PROPERTY::deliver() { }

ByteBuffer &ZC_MER_PROPERTY::serialize()
{
	return buf();
}

/**
 * ZC_ACCEPT_ENTER3
 */
void ZC_ACCEPT_ENTER3::deliver(int16_t x, int16_t y, int16_t dir, int16_t font, int8_t gender)
{
	PackPosition((int8_t *) _packed_pos, x, y, dir);
	_start_time = (int32_t) get_sys_time();
	
	_x_size = _y_size = 5;
	_font = font;
	_gender = gender;

	serialize();
	transmit();
}

ByteBuffer &ZC_ACCEPT_ENTER3::serialize()
{
	buf() << _packet_id;
	buf() << _start_time;
	buf().append(_packed_pos, sizeof(_packed_pos));
	buf() << _x_size << _y_size << _font << _gender;
	
	return buf();
}

/**
 * ZC_ACCEPT_ENTER2
 */
void ZC_ACCEPT_ENTER2::deliver(int16_t x, int16_t y, int16_t dir, int16_t font)
{
	PackPosition((int8_t *) _packed_pos, x, y, dir);
	_start_time = (int32_t) get_sys_time();
	_x_size = _y_size = 5;
	_font = font;

	serialize();
	transmit();
}

ByteBuffer &ZC_ACCEPT_ENTER2::serialize()
{
	buf() << _packet_id;
	buf() << _start_time;
	buf().append(_packed_pos, sizeof(_packed_pos));
	buf() << _x_size << _y_size << _font;
	return buf();
}

/**
 * ZC_SAY_DIALOG2
 */
void ZC_SAY_DIALOG2::deliver() { }

ByteBuffer &ZC_SAY_DIALOG2::serialize()
{
	return buf();
}

/**
 * ZC_GUILD_CHAT
 */
void ZC_GUILD_CHAT::deliver() { }

ByteBuffer &ZC_GUILD_CHAT::serialize()
{
	return buf();
}

/**
 * ZC_STATUS
 */
void ZC_STATUS::deliver(struct zc_status_data &data)
{ 
	_data = data;

	serialize();
	transmit();
}

ByteBuffer &ZC_STATUS::serialize()
{
	buf() << _packet_id;
	buf() << _data.status_points;
	buf() << _data.strength;
	buf() << _data.strength_req_stats;
	buf() << _data.agility;
	buf() << _data.agility_req_stats;
	buf() << _data.vitality;
	buf() << _data.vitality_req_stats;
	buf() << _data.intelligence;
	buf() << _data.intelligence_req_stats;
	buf() << _data.dexterity;
	buf() << _data.dexterity_req_stats;
	buf() << _data.luck;
	buf() << _data.luck_req_stats;
	buf() << _data.status_atk;
	buf() << _data.equip_atk;
	buf() << _data.equip_matk;
	buf() << _data.status_matk;
	buf() << _data.soft_def;
	buf() << _data.hard_def;
	buf() << _data.soft_mdef;
	buf() << _data.hard_mdef;
	buf() << _data.hit;
	buf() << _data.flee;
	buf() << _data.perfect_dodge;
	buf() << _data.critical;
	buf() << _data.attack_speed;
	buf() << _data.plus_aspd; // always 0 apparently.
	return buf();
}

/**
 * ZC_HP_INFO_TINY
 */
void ZC_HP_INFO_TINY::deliver() { }

ByteBuffer &ZC_HP_INFO_TINY::serialize()
{
	return buf();
}

/**
 * ZC_DIVORCE
 */
void ZC_DIVORCE::deliver() { }

ByteBuffer &ZC_DIVORCE::serialize()
{
	return buf();
}

/**
 * ZC_ACK_MAKE_GROUP
 */
void ZC_ACK_MAKE_GROUP::deliver() { }

ByteBuffer &ZC_ACK_MAKE_GROUP::serialize()
{
	return buf();
}

/**
 * ZC_OFFLINE_STORE_ITEMS
 */
void ZC_OFFLINE_STORE_ITEMS::deliver() { }

ByteBuffer &ZC_OFFLINE_STORE_ITEMS::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REQ_ALLY_GUILD
 */
void ZC_ACK_REQ_ALLY_GUILD::deliver() { }

ByteBuffer &ZC_ACK_REQ_ALLY_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_EQUIPWIN_OTHER
 */
void ZC_EQUIPWIN_OTHER::deliver() { }

ByteBuffer &ZC_EQUIPWIN_OTHER::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ITEMCOMPOSITION
 */
void ZC_ACK_ITEMCOMPOSITION::deliver() { }

ByteBuffer &ZC_ACK_ITEMCOMPOSITION::serialize()
{
	return buf();
}

/**
 * ZC_PROGRESS
 */
void ZC_PROGRESS::deliver() { }

ByteBuffer &ZC_PROGRESS::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_PICKUP_PARTY
 */
void ZC_ITEM_PICKUP_PARTY::deliver() { }

ByteBuffer &ZC_ITEM_PICKUP_PARTY::serialize()
{
	return buf();
}

/**
 * ZC_C_MARKERINFO
 */
void ZC_C_MARKERINFO::deliver() { }

ByteBuffer &ZC_C_MARKERINFO::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ITEMLIST_BUYING_STORE
 */
void ZC_ACK_ITEMLIST_BUYING_STORE::deliver() { }

ByteBuffer &ZC_ACK_ITEMLIST_BUYING_STORE::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_SKILL_POSITION
 */
void ZC_NOTIFY_SKILL_POSITION::deliver() { }

ByteBuffer &ZC_NOTIFY_SKILL_POSITION::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_NEWENTRY11
 */
void ZC_NOTIFY_NEWENTRY11::deliver(entity_viewport_entry entry)
{
	_entry = entry;
	serialize();
	transmit();
}

ByteBuffer &ZC_NOTIFY_NEWENTRY11::serialize()
{
#if (CLIENT_TYPE == 'M' && PACKET_VERSION >= 20181121) \
|| (CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180704) \
|| (CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20181114)
	_packet_length = 107;
#else
	_packet_length = 103;
#endif

	buf() << _packet_id;
	buf() << _packet_length;
	buf() << (int8_t) _entry.unit_type;
	buf() << _entry.guid;
	buf() << _entry.character_id;
	buf() << _entry.speed;
	buf() << _entry.body_state;
	buf() << _entry.health_state;
	buf() << _entry.effect_state;
	buf() << _entry.job_id;
	buf() << _entry.hair_style_id;
	buf() << _entry.weapon_id;
#if (CLIENT_TYPE == 'M' && PACKET_VERSION >= 20181121) \
|| (CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180704) \
|| (CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20181114)
	buf() << _entry.shield_id;
#endif
	buf() << _entry.headgear_bottom_id;
	buf() << _entry.headgear_top_id;
	buf() << _entry.headgear_mid_id;
	buf() << _entry.hair_color_id;
	buf() << _entry.cloth_color_id;
	buf() << (int16_t)_entry.head_direction;
	buf() << _entry.robe_id;
	buf() << _entry.guild_id;
	buf() << _entry.guild_emblem_version;
	buf() << _entry.honor;
	buf() << _entry.virtue;
	buf() << _entry.in_pk_mode;
	buf() << _entry.gender;

	char packed_pos[3]{0};
	PackPosition((int8_t *) packed_pos, _entry.current_x, _entry.current_y, _entry.current_dir);

	buf().append(packed_pos, sizeof(packed_pos));
	buf() << _entry.x_size;
	buf() << _entry.y_size;
	buf() << _entry.base_level;
	buf() << _entry.font;
	buf() << _entry.max_hp;
	buf() << _entry.hp;
	buf() << _entry.is_boss;
	buf() << _entry.body_style_id;
	buf().append(_entry.name, MAX_UNIT_NAME_LENGTH);

	return buf();
}

/**
 * ZC_REQ_ITEM_EXPLANATION_ACK
 */
void ZC_REQ_ITEM_EXPLANATION_ACK::deliver() { }

ByteBuffer &ZC_REQ_ITEM_EXPLANATION_ACK::serialize()
{
	return buf();
}

/**
 * ZC_RESULT_PACKAGE_ITEM_TEST
 */
void ZC_RESULT_PACKAGE_ITEM_TEST::deliver() { }

ByteBuffer &ZC_RESULT_PACKAGE_ITEM_TEST::serialize()
{
	return buf();
}

/**
 * ZC_STORE_EQUIPMENT_ITEMLIST2
 */
void ZC_STORE_EQUIPMENT_ITEMLIST2::deliver() { }

ByteBuffer &ZC_STORE_EQUIPMENT_ITEMLIST2::serialize()
{
	return buf();
}

/**
 * ZC_STORE_EQUIPMENT_ITEMLIST3
 */
void ZC_STORE_EQUIPMENT_ITEMLIST3::deliver() { }

ByteBuffer &ZC_STORE_EQUIPMENT_ITEMLIST3::serialize()
{
	return buf();
}

/**
 * ZC_WHISPER02
 */
void ZC_WHISPER02::deliver() { }

ByteBuffer &ZC_WHISPER02::serialize()
{
	return buf();
}

/**
 * ZC_OPEN_EDITDLG
 */
void ZC_OPEN_EDITDLG::deliver(int32_t guid)
{
	_guid = guid;
	serialize();
	transmit();
}

ByteBuffer &ZC_OPEN_EDITDLG::serialize()
{
	buf() << _packet_id;
	buf() << _guid;
	return buf();
}

/**
 * ZC_GUILD_EMBLEM_IMG
 */
void ZC_GUILD_EMBLEM_IMG::deliver() { }

ByteBuffer &ZC_GUILD_EMBLEM_IMG::serialize()
{
	return buf();
}

/**
 * ZC_ACK_CHANGE_GUILD_POSITIONINFO
 */
void ZC_ACK_CHANGE_GUILD_POSITIONINFO::deliver() { }

ByteBuffer &ZC_ACK_CHANGE_GUILD_POSITIONINFO::serialize()
{
	return buf();
}

/**
 * ZC_NAVIGATION_ACTIVE
 */
void ZC_NAVIGATION_ACTIVE::deliver() { }

ByteBuffer &ZC_NAVIGATION_ACTIVE::serialize()
{
	return buf();
}

/**
 * ZC_CART_NORMAL_ITEMLIST
 */
void ZC_CART_NORMAL_ITEMLIST::deliver() { }

ByteBuffer &ZC_CART_NORMAL_ITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_REQ_CASH_PASSWORD
 */
void ZC_REQ_CASH_PASSWORD::deliver() { }

ByteBuffer &ZC_REQ_CASH_PASSWORD::serialize()
{
	return buf();
}

/**
 * ZC_EQUIPWIN_MICROSCOPE_V7
 */
void ZC_EQUIPWIN_MICROSCOPE_V7::deliver() { }

ByteBuffer &ZC_EQUIPWIN_MICROSCOPE_V7::serialize()
{
	return buf();
}

/**
 * ZC_EQUIPWIN_MICROSCOPE_V6
 */
void ZC_EQUIPWIN_MICROSCOPE_V6::deliver() { }

ByteBuffer &ZC_EQUIPWIN_MICROSCOPE_V6::serialize()
{
	return buf();
}

/**
 * ZC_EQUIPWIN_MICROSCOPE_V5
 */
void ZC_EQUIPWIN_MICROSCOPE_V5::deliver() { }

ByteBuffer &ZC_EQUIPWIN_MICROSCOPE_V5::serialize()
{
	return buf();
}

/**
 * ZC_TAEKWON_POINT
 */
void ZC_TAEKWON_POINT::deliver() { }

ByteBuffer &ZC_TAEKWON_POINT::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REMOVE_BARGAIN_SALE_ITEM
 */
void ZC_ACK_REMOVE_BARGAIN_SALE_ITEM::deliver() { }

ByteBuffer &ZC_ACK_REMOVE_BARGAIN_SALE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_GROUP_ISALIVE
 */
void ZC_GROUP_ISALIVE::deliver() { }

ByteBuffer &ZC_GROUP_ISALIVE::serialize()
{
	return buf();
}

/**
 * ZC_SEARCH_STORE_INFO_FAILED
 */
void ZC_SEARCH_STORE_INFO_FAILED::deliver() { }

ByteBuffer &ZC_SEARCH_STORE_INFO_FAILED::serialize()
{
	return buf();
}

/**
 * ZC_UPDATE_MAPINFO
 */
void ZC_UPDATE_MAPINFO::deliver(int16_t x, int16_t y, const char *map_name, int16_t type)
{
	_x = x;
	_y = y;
	_type = type;
	strncpy(_map_name, map_name, MAP_NAME_LENGTH_EXT);
	serialize();
	transmit();
}

ByteBuffer &ZC_UPDATE_MAPINFO::serialize()
{
	buf() << _packet_id;
	buf() << _x;
	buf() << _y;
	buf() << _type;
	buf().append(_map_name, MAP_NAME_LENGTH_EXT);
	return buf();
}

/**
 * ZC_NOTIFY_POSITION_TO_GROUPM
 */
void ZC_NOTIFY_POSITION_TO_GROUPM::deliver() { }

ByteBuffer &ZC_NOTIFY_POSITION_TO_GROUPM::serialize()
{
	return buf();
}

/**
 * ZC_MEMBERMGR_INFO
 */
void ZC_MEMBERMGR_INFO::deliver() { }

ByteBuffer &ZC_MEMBERMGR_INFO::serialize()
{
	return buf();
}

/**
 * ZC_CART_ITEMLIST_EQUIP
 */
void ZC_CART_ITEMLIST_EQUIP::deliver() { }

ByteBuffer &ZC_CART_ITEMLIST_EQUIP::serialize()
{
	return buf();
}

/**
 * ZC_GUILD_INFO
 */
void ZC_GUILD_INFO::deliver() { }

ByteBuffer &ZC_GUILD_INFO::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REQ_DISCONNECT
 */
void ZC_ACK_REQ_DISCONNECT::deliver(bool wait)
{
	_waiting = wait ? 1 : 0;

	serialize();
	transmit();
}

ByteBuffer &ZC_ACK_REQ_DISCONNECT::serialize()
{
	buf() << _packet_id;
	buf() << _waiting;
	return buf();
}

/**
 * ZC_MEMBER_ADD
 */
void ZC_MEMBER_ADD::deliver() { }

ByteBuffer &ZC_MEMBER_ADD::serialize()
{
	return buf();
}

/**
 * ZC_STATUS_CHANGE
 */
void ZC_STATUS_CHANGE::deliver(status_point_type type, int8_t value)
{
	_type = type;
	_value = value;

	serialize();
	transmit();
}

ByteBuffer &ZC_STATUS_CHANGE::serialize()
{
	buf() << _packet_id;
	buf() << (int16_t) _type;
	buf() << _value;
	return buf();
}

/**
 * ZC_NOTIFY_NEWENTRY10
 */
void ZC_NOTIFY_NEWENTRY10::deliver() { }

ByteBuffer &ZC_NOTIFY_NEWENTRY10::serialize()
{
	return buf();
}

/**
 * ZC_ACK_TOUSESKILL
 */
void ZC_ACK_TOUSESKILL::deliver() { }

ByteBuffer &ZC_ACK_TOUSESKILL::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_NOTIFY_INSERT
 */
void ZC_PARTY_RECRUIT_NOTIFY_INSERT::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_NOTIFY_INSERT::serialize()
{
	return buf();
}

/**
 * ZC_REQ_ALLY_GUILD
 */
void ZC_REQ_ALLY_GUILD::deliver() { }

ByteBuffer &ZC_REQ_ALLY_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_OPEN_BUYING_STORE
 */
void ZC_OPEN_BUYING_STORE::deliver() { }

ByteBuffer &ZC_OPEN_BUYING_STORE::serialize()
{
	return buf();
}

/**
 * ZC_BROADCASTING_SPECIAL_ITEM_OBTAIN
 */
void ZC_BROADCASTING_SPECIAL_ITEM_OBTAIN::deliver() { }

ByteBuffer &ZC_BROADCASTING_SPECIAL_ITEM_OBTAIN::serialize()
{
	return buf();
}

/**
 * ZC_MAPPROPERTY
 */
void ZC_MAPPROPERTY::deliver() { }

ByteBuffer &ZC_MAPPROPERTY::serialize()
{
	return buf();
}

/**
 * ZC_ADD_MEMBER_TO_GROUP2
 */
void ZC_ADD_MEMBER_TO_GROUP2::deliver() { }

ByteBuffer &ZC_ADD_MEMBER_TO_GROUP2::serialize()
{
	return buf();
}

/**
 * ZC_BATTLEFIELD_NOTIFY_HP
 */
void ZC_BATTLEFIELD_NOTIFY_HP::deliver() { }

ByteBuffer &ZC_BATTLEFIELD_NOTIFY_HP::serialize()
{
	return buf();
}

/**
 * ZC_ACK_GENERATE_ROULETTE
 */
void ZC_ACK_GENERATE_ROULETTE::deliver() { }

ByteBuffer &ZC_ACK_GENERATE_ROULETTE::serialize()
{
	return buf();
}

/**
 * ZC_PC_CASH_POINT_UPDATE
 */
void ZC_PC_CASH_POINT_UPDATE::deliver() { }

ByteBuffer &ZC_PC_CASH_POINT_UPDATE::serialize()
{
	return buf();
}

/**
 * ZC_USE_ITEM_ACK
 */
void ZC_USE_ITEM_ACK::deliver(int16_t index, int16_t amount, bool success)
{
	_index = index;
	_amount = amount;
	_success = success;

	serialize();
	transmit();
}

ByteBuffer &ZC_USE_ITEM_ACK::serialize()
{
	buf() << _packet_id;
	buf() << _index;
	buf() << _amount;
	buf() << _success;
	return buf();
}

/**
 * ZC_BLACKSMITH_RANK
 */
void ZC_BLACKSMITH_RANK::deliver() { }

ByteBuffer &ZC_BLACKSMITH_RANK::serialize()
{
	return buf();
}

/**
 * ZC_ADD_ITEM_TO_STORE3
 */
void ZC_ADD_ITEM_TO_STORE3::deliver() { }

ByteBuffer &ZC_ADD_ITEM_TO_STORE3::serialize()
{
	return buf();
}

/**
 * ZC_MAIL_REQ_SEND
 */
void ZC_MAIL_REQ_SEND::deliver() { }

ByteBuffer &ZC_MAIL_REQ_SEND::serialize()
{
	return buf();
}

/**
 * ZC_REFUSE_QUIT
 */
void ZC_REFUSE_QUIT::deliver() { }

ByteBuffer &ZC_REFUSE_QUIT::serialize()
{
	return buf();
}

/**
 * ZC_MAIL_REQ_GET_ITEM
 */
void ZC_MAIL_REQ_GET_ITEM::deliver() { }

ByteBuffer &ZC_MAIL_REQ_GET_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_ACK_COUNT_BARGAIN_SALE_ITEM
 */
void ZC_ACK_COUNT_BARGAIN_SALE_ITEM::deliver() { }

ByteBuffer &ZC_ACK_COUNT_BARGAIN_SALE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_SSILIST_ITEM_CLICK_ACK
 */
void ZC_SSILIST_ITEM_CLICK_ACK::deliver() { }

ByteBuffer &ZC_SSILIST_ITEM_CLICK_ACK::serialize()
{
	return buf();
}

/**
 * ZC_ITEMLISTWIN_OPEN
 */
void ZC_ITEMLISTWIN_OPEN::deliver() { }

ByteBuffer &ZC_ITEMLISTWIN_OPEN::serialize()
{
	return buf();
}

/**
 * ZC_INVENTORY_MOVE_FAILED
 */
void ZC_INVENTORY_MOVE_FAILED::deliver(int16_t index, int16_t silent)
{
	_index = index;
	_silent = silent;

	serialize();
	transmit();
}

ByteBuffer &ZC_INVENTORY_MOVE_FAILED::serialize()
{
	buf() << _packet_id;
	buf() << _index;
	buf() << _silent;
	return buf();
}

/**
 * ZC_FAILED_OPEN_BUYING_STORE_TO_BUYER
 */
void ZC_FAILED_OPEN_BUYING_STORE_TO_BUYER::deliver() { }

ByteBuffer &ZC_FAILED_OPEN_BUYING_STORE_TO_BUYER::serialize()
{
	return buf();
}

/**
 * ZC_MAIL_REQ_GET_LIST
 */
void ZC_MAIL_REQ_GET_LIST::deliver() { }

ByteBuffer &ZC_MAIL_REQ_GET_LIST::serialize()
{
	return buf();
}

/**
 * ZC_TRYCOLLECTION
 */
void ZC_TRYCOLLECTION::deliver() { }

ByteBuffer &ZC_TRYCOLLECTION::serialize()
{
	return buf();
}

/**
 * ZC_REQ_GROUPINFO_CHANGE_V2
 */
void ZC_REQ_GROUPINFO_CHANGE_V2::deliver() { }

ByteBuffer &ZC_REQ_GROUPINFO_CHANGE_V2::serialize()
{
	return buf();
}

/**
 * ZC_OVERWEIGHT_PERCENT
 */
void ZC_OVERWEIGHT_PERCENT::deliver() { }

ByteBuffer &ZC_OVERWEIGHT_PERCENT::serialize()
{
	return buf();
}

/**
 * ZC_PROPERTY_HOMUN_2
 */
void ZC_PROPERTY_HOMUN_2::deliver() { }

ByteBuffer &ZC_PROPERTY_HOMUN_2::serialize()
{
	return buf();
}

/**
 * ZC_ACK_MAIL_ADD_ITEM
 */
void ZC_ACK_MAIL_ADD_ITEM::deliver() { }

ByteBuffer &ZC_ACK_MAIL_ADD_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_OFFLINE_STORE_OWNER_ITEMS_READY
 */
void ZC_OFFLINE_STORE_OWNER_ITEMS_READY::deliver() { }

ByteBuffer &ZC_OFFLINE_STORE_OWNER_ITEMS_READY::serialize()
{
	return buf();
}

/**
 * ZC_STATUS_CHANGE_ACK
 */
void ZC_STATUS_CHANGE_ACK::deliver(status_point_type type, int8_t amount, bool success)
{
	_type = (int16_t) type;
	_success = success ? 1 : 0;
	_amount = amount;
	serialize();
	transmit();
}

ByteBuffer &ZC_STATUS_CHANGE_ACK::serialize()
{
	buf() << _packet_id;
	buf() << _type;
	buf() << _success;
	buf() << _amount;
	return buf();
}

/**
 * ZC_RESULT_STORE_PASSWORD
 */
void ZC_RESULT_STORE_PASSWORD::deliver() { }

ByteBuffer &ZC_RESULT_STORE_PASSWORD::serialize()
{
	return buf();
}

/**
 * ZC_ACCEPT_ENTER
 */
void ZC_ACCEPT_ENTER::deliver() { }

ByteBuffer &ZC_ACCEPT_ENTER::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_PREVIEW
 */
void ZC_ITEM_PREVIEW::deliver() { }

ByteBuffer &ZC_ITEM_PREVIEW::serialize()
{
	return buf();
}

/**
 * ZC_AIRSHIP_MAPMOVE
 */
void ZC_AIRSHIP_MAPMOVE::deliver() { }

ByteBuffer &ZC_AIRSHIP_MAPMOVE::serialize()
{
	return buf();
}

/**
 * ZC_SPRITE_CHANGE2
 */
void ZC_SPRITE_CHANGE2::deliver() { }

ByteBuffer &ZC_SPRITE_CHANGE2::serialize()
{
	return buf();
}

/**
 * ZC_ADD_QUEST_EX
 */
void ZC_ADD_QUEST_EX::deliver() { }

ByteBuffer &ZC_ADD_QUEST_EX::serialize()
{
	return buf();
}

/**
 * ZC_ES_READY
 */
void ZC_ES_READY::deliver() { }

ByteBuffer &ZC_ES_READY::serialize()
{
	return buf();
}

/**
 * ZC_MAIL_RECEIVE
 */
void ZC_MAIL_RECEIVE::deliver() { }

ByteBuffer &ZC_MAIL_RECEIVE::serialize()
{
	return buf();
}

/**
 * ZC_GROUP_LIST
 */
void ZC_GROUP_LIST::deliver() { }

ByteBuffer &ZC_GROUP_LIST::serialize()
{
	return buf();
}

/**
 * ZC_MILLENNIUMSHIELD
 */
void ZC_MILLENNIUMSHIELD::deliver() { }

ByteBuffer &ZC_MILLENNIUMSHIELD::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_MEMBER_JOB_LEVEL
 */
void ZC_PARTY_MEMBER_JOB_LEVEL::deliver() { }

ByteBuffer &ZC_PARTY_MEMBER_JOB_LEVEL::serialize()
{
	return buf();
}

/**
 * ZC_OFFLINE_STORE_OWNER_ITEMS
 */
void ZC_OFFLINE_STORE_OWNER_ITEMS::deliver() { }

ByteBuffer &ZC_OFFLINE_STORE_OWNER_ITEMS::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_CLAN_CHAT
 */
void ZC_NOTIFY_CLAN_CHAT::deliver() { }

ByteBuffer &ZC_NOTIFY_CLAN_CHAT::serialize()
{
	return buf();
}

/**
 * ZC_NPC_BARTER_OPEN
 */
void ZC_NPC_BARTER_OPEN::deliver() { }

ByteBuffer &ZC_NPC_BARTER_OPEN::serialize()
{
	return buf();
}

/**
 * ZC_START_COUPLE
 */
void ZC_START_COUPLE::deliver() { }

ByteBuffer &ZC_START_COUPLE::serialize()
{
	return buf();
}

/**
 * ZC_REPAIRITEMLIST
 */
void ZC_REPAIRITEMLIST::deliver() { }

ByteBuffer &ZC_REPAIRITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_DELETE_ITEM_FROM_BODY
 */
void ZC_DELETE_ITEM_FROM_BODY::deliver(int16_t index, int16_t amount, item_deletion_reason_type reason)
{
	_index = index;
	_amount = amount;
	_reason = reason;

	serialize();
	transmit();
}

ByteBuffer &ZC_DELETE_ITEM_FROM_BODY::serialize()
{
	buf() << _packet_id;
	buf() << (int16_t) _reason;
	buf() << _index;
	buf() << _amount;
	return buf();
}

/**
 * ZC_MYITEMLIST_BUYING_STORE
 */
void ZC_MYITEMLIST_BUYING_STORE::deliver() { }

ByteBuffer &ZC_MYITEMLIST_BUYING_STORE::serialize()
{
	return buf();
}

/**
 * ZC_SRPACKETR2_INIT
 */
void ZC_SRPACKETR2_INIT::deliver() { }

ByteBuffer &ZC_SRPACKETR2_INIT::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MOVEENTRY4
 */
void ZC_NOTIFY_MOVEENTRY4::deliver() { }

ByteBuffer &ZC_NOTIFY_MOVEENTRY4::serialize()
{
	return buf();
}

/**
 * ZC_CONFIG_NOTIFY
 */
void ZC_CONFIG_NOTIFY::deliver() { }

ByteBuffer &ZC_CONFIG_NOTIFY::serialize()
{
	return buf();
}

/**
 * ZC_PETEGG_LIST
 */
void ZC_PETEGG_LIST::deliver() { }

ByteBuffer &ZC_PETEGG_LIST::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MOVEENTRY3
 */
void ZC_NOTIFY_MOVEENTRY3::deliver() { }

ByteBuffer &ZC_NOTIFY_MOVEENTRY3::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MOVEENTRY2
 */
void ZC_NOTIFY_MOVEENTRY2::deliver() { }

ByteBuffer &ZC_NOTIFY_MOVEENTRY2::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MOVEENTRY9
 */
void ZC_NOTIFY_MOVEENTRY9::deliver() { }

ByteBuffer &ZC_NOTIFY_MOVEENTRY9::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MOVEENTRY8
 */
void ZC_NOTIFY_MOVEENTRY8::deliver() { }

ByteBuffer &ZC_NOTIFY_MOVEENTRY8::serialize()
{
	return buf();
}

/**
 * ZC_SE_CASHSHOP_OPEN
 */
void ZC_SE_CASHSHOP_OPEN::deliver() { }

ByteBuffer &ZC_SE_CASHSHOP_OPEN::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_CLAN_CONNECTINFO
 */
void ZC_NOTIFY_CLAN_CONNECTINFO::deliver() { }

ByteBuffer &ZC_NOTIFY_CLAN_CONNECTINFO::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MOVEENTRY11
 */
void ZC_NOTIFY_MOVEENTRY11::deliver(entity_viewport_entry entry)
{
	_entry = entry;
	serialize();
	transmit();
}

ByteBuffer &ZC_NOTIFY_MOVEENTRY11::serialize()
{
	char packed_pos[6]{0};
	
	_entry.move_start_time = (uint32_t) get_sys_time();
	
	buf() << _packet_id;
	buf() << (int16_t) 110;
	buf() << (int8_t) _entry.unit_type;
	buf() << _entry.guid;
	buf() << _entry.character_id;
	buf() << _entry.speed;
	buf() << _entry.body_state;
	buf() << _entry.health_state;
	buf() << _entry.effect_state;
	buf() << _entry.job_id;
	buf() << _entry.hair_style_id;
	buf() << _entry.weapon_id;
	buf() << _entry.headgear_bottom_id;
	buf() << _entry.move_start_time;
	buf() << _entry.headgear_top_id;
	buf() << _entry.headgear_mid_id;
	buf() << _entry.hair_color_id;
	buf() << _entry.cloth_color_id;
	buf() << (int16_t) _entry.head_direction;
	buf() << _entry.robe_id;
	buf() << _entry.guild_id;
	buf() << _entry.guild_emblem_version;
	buf() << _entry.honor;
	buf() << _entry.virtue;
	buf() << _entry.in_pk_mode;
	buf() << _entry.gender;
	PackPosition((int8_t *) packed_pos, _entry.current_x, _entry.current_y, _entry.to_x, _entry.to_y, 8, 8);
	buf().append(packed_pos, sizeof(packed_pos));
	buf() << _entry.x_size;
	buf() << _entry.y_size;
	buf() << _entry.base_level;
	buf() << _entry.font;
	buf() << -1;
	buf() << -1;
	buf() << _entry.is_boss;
	buf() << _entry.body_style_id;
	buf().append(_entry.name, sizeof(_entry.name));
	
	return buf();
}

/**
 * ZC_ATTACK_RANGE
 */
void ZC_ATTACK_RANGE::deliver(int16_t range)
{
	_range = range;

	serialize();
	transmit();
}

ByteBuffer &ZC_ATTACK_RANGE::serialize()
{
	buf() << _packet_id;
	buf() << _range;
	return buf();
}

/**
 * ZC_NPC_MARKET_PURCHASE_RESULT
 */
void ZC_NPC_MARKET_PURCHASE_RESULT::deliver() { }

ByteBuffer &ZC_NPC_MARKET_PURCHASE_RESULT::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MAPINFO
 */
void ZC_NOTIFY_MAPINFO::deliver() { }

ByteBuffer &ZC_NOTIFY_MAPINFO::serialize()
{
	return buf();
}

/**
 * ZC_MVP
 */
void ZC_MVP::deliver() { }

ByteBuffer &ZC_MVP::serialize()
{
	return buf();
}

/**
 * ZC_DESTROY_ROOM
 */
void ZC_DESTROY_ROOM::deliver() { }

ByteBuffer &ZC_DESTROY_ROOM::serialize()
{
	return buf();
}

/**
 * ZC_REQ_BABY
 */
void ZC_REQ_BABY::deliver() { }

ByteBuffer &ZC_REQ_BABY::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ADD_EXCHANGE_ITEM
 */
void ZC_ACK_ADD_EXCHANGE_ITEM::deliver() { }

ByteBuffer &ZC_ACK_ADD_EXCHANGE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_ACK_REGISTER
 */
void ZC_PARTY_RECRUIT_ACK_REGISTER::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_ACK_REGISTER::serialize()
{
	return buf();
}

/**
 * ZC_ACTION_FAILURE
 */
void ZC_ACTION_FAILURE::deliver(int16_t message_type)
{
	_message_type = message_type;
	serialize();
	transmit();
}

ByteBuffer &ZC_ACTION_FAILURE::serialize()
{
	buf() << _packet_id;
	buf() << _message_type;
	return buf();
}

/**
 * ZC_HP_INFO
 */
void ZC_HP_INFO::deliver() { }

ByteBuffer &ZC_HP_INFO::serialize()
{
	return buf();
}

/**
 * ZC_ACK_GUILD_MEMBER_INFO
 */
void ZC_ACK_GUILD_MEMBER_INFO::deliver() { }

ByteBuffer &ZC_ACK_GUILD_MEMBER_INFO::serialize()
{
	return buf();
}

/**
 * ZC_ACK_EXCHANGE_ITEM2
 */
void ZC_ACK_EXCHANGE_ITEM2::deliver() { }

ByteBuffer &ZC_ACK_EXCHANGE_ITEM2::serialize()
{
	return buf();
}

/**
 * ZC_RECV_ROULETTE_ITEM
 */
void ZC_RECV_ROULETTE_ITEM::deliver() { }

ByteBuffer &ZC_RECV_ROULETTE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_ADD_EXCHANGE_ITEM
 */
void ZC_ADD_EXCHANGE_ITEM::deliver() { }

ByteBuffer &ZC_ADD_EXCHANGE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_OPEN_BARGAIN_SALE_TOOL
 */
void ZC_OPEN_BARGAIN_SALE_TOOL::deliver() { }

ByteBuffer &ZC_OPEN_BARGAIN_SALE_TOOL::serialize()
{
	return buf();
}

/**
 * ZC_SKILLINFO_LIST
 */
void ZC_SKILLINFO_LIST::deliver() { }

ByteBuffer &ZC_SKILLINFO_LIST::serialize()
{
	return buf();
}

/**
 * ZC_MEMORIALDUNGEON_NOTIFY
 */
void ZC_MEMORIALDUNGEON_NOTIFY::deliver() { }

ByteBuffer &ZC_MEMORIALDUNGEON_NOTIFY::serialize()
{
	return buf();
}

/**
 * ZC_ENTRY_QUEUE_INIT
 */
void ZC_ENTRY_QUEUE_INIT::deliver() { }

ByteBuffer &ZC_ENTRY_QUEUE_INIT::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ENTRY_QUEUE_CANCEL
 */
void ZC_ACK_ENTRY_QUEUE_CANCEL::deliver() { }

ByteBuffer &ZC_ACK_ENTRY_QUEUE_CANCEL::serialize()
{
	return buf();
}

/**
 * ZC_ROLE_CHANGE
 */
void ZC_ROLE_CHANGE::deliver() { }

ByteBuffer &ZC_ROLE_CHANGE::serialize()
{
	return buf();
}

/**
 * ZC_ALCHEMIST_RANK
 */
void ZC_ALCHEMIST_RANK::deliver() { }

ByteBuffer &ZC_ALCHEMIST_RANK::serialize()
{
	return buf();
}

/**
 * ZC_ACK_SCHEDULER_CASHITEM
 */
void ZC_ACK_SCHEDULER_CASHITEM::deliver() { }

ByteBuffer &ZC_ACK_SCHEDULER_CASHITEM::serialize()
{
	return buf();
}

/**
 * ZC_SKILL_POSTDELAY_LIST2
 */
void ZC_SKILL_POSTDELAY_LIST2::deliver() { }

ByteBuffer &ZC_SKILL_POSTDELAY_LIST2::serialize()
{
	return buf();
}

/**
 * ZC_GAME_GUARD
 */
void ZC_GAME_GUARD::deliver() { }

ByteBuffer &ZC_GAME_GUARD::serialize()
{
	return buf();
}

/**
 * ZC_NORMAL_ITEMLIST
 */
void ZC_NORMAL_ITEMLIST::deliver(std::vector<item_entry_data> &items)
{
	_items = items;

	serialize();
	transmit();
}

ByteBuffer &ZC_NORMAL_ITEMLIST::serialize()
{
	buf() << _packet_id;
	buf() << int16_t(2 + (_items.size() * sizeof(item_entry_data)));
	
	for (auto it = _items.begin(); it != _items.end(); it++) {
		item_entry_data id = *it;
		buf() << id.inventory_index;
		buf() << (int16_t) id.item_id;
		buf() << (int8_t) id.type;
		buf() << ((int8_t) id.info.is_identified ? 1 : 0);
		buf() << id.amount;
		buf() << (int16_t) id.current_equip_location_mask;
		
		for (int i = 0; i < sizeof(id.slot_item_id); i++)
			buf() << (int16_t) id.slot_item_id[i];
	}

	return buf();
}

/**
 * ZC_CHECK_RECEIVE_CHARACTER_NAME
 */
void ZC_CHECK_RECEIVE_CHARACTER_NAME::deliver() { }

ByteBuffer &ZC_CHECK_RECEIVE_CHARACTER_NAME::serialize()
{
	return buf();
}

/**
 * ZC_MER_SKILLINFO_LIST
 */
void ZC_MER_SKILLINFO_LIST::deliver() { }

ByteBuffer &ZC_MER_SKILLINFO_LIST::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_OFFLINE_STORE
 */
void ZC_NOTIFY_OFFLINE_STORE::deliver() { }

ByteBuffer &ZC_NOTIFY_OFFLINE_STORE::serialize()
{
	return buf();
}

/**
 * ZC_CLANINFO
 */
void ZC_CLANINFO::deliver() { }

ByteBuffer &ZC_CLANINFO::serialize()
{
	return buf();
}

/**
 * ZC_PC_CASH_POINT_ITEMLIST
 */
void ZC_PC_CASH_POINT_ITEMLIST::deliver() { }

ByteBuffer &ZC_PC_CASH_POINT_ITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_STANDENTRY3
 */
void ZC_NOTIFY_STANDENTRY3::deliver() { }

ByteBuffer &ZC_NOTIFY_STANDENTRY3::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_STANDENTRY2
 */
void ZC_NOTIFY_STANDENTRY2::deliver() { }

ByteBuffer &ZC_NOTIFY_STANDENTRY2::serialize()
{
	return buf();
}

/**
 * ZC_ACK_OPEN_BANKING
 */
void ZC_ACK_OPEN_BANKING::deliver() { }

ByteBuffer &ZC_ACK_OPEN_BANKING::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_STANDENTRY7
 */
void ZC_NOTIFY_STANDENTRY7::deliver() { }

ByteBuffer &ZC_NOTIFY_STANDENTRY7::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_STANDENTRY5
 */
void ZC_NOTIFY_STANDENTRY5::deliver() { }

ByteBuffer &ZC_NOTIFY_STANDENTRY5::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_STANDENTRY4
 */
void ZC_NOTIFY_STANDENTRY4::deliver() { }

ByteBuffer &ZC_NOTIFY_STANDENTRY4::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_STANDENTRY8
 */
void ZC_NOTIFY_STANDENTRY8::deliver() { }

ByteBuffer &ZC_NOTIFY_STANDENTRY8::serialize()
{
	return buf();
}

/**
 * ZC_PLAY_NPC_BGM
 */
void ZC_PLAY_NPC_BGM::deliver() { }

ByteBuffer &ZC_PLAY_NPC_BGM::serialize()
{
	return buf();
}

/**
 * ZC_PRIVATE_AIRSHIP_RESPONSE
 */
void ZC_PRIVATE_AIRSHIP_RESPONSE::deliver() { }

ByteBuffer &ZC_PRIVATE_AIRSHIP_RESPONSE::serialize()
{
	return buf();
}

/**
 * ZC_PERSONAL_INFOMATION
 */
void ZC_PERSONAL_INFOMATION::deliver() { }

ByteBuffer &ZC_PERSONAL_INFOMATION::serialize()
{
	return buf();
}

/**
 * ZC_REQ_COUPLE
 */
void ZC_REQ_COUPLE::deliver() { }

ByteBuffer &ZC_REQ_COUPLE::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_UPDATEPLAYER
 */
void ZC_NOTIFY_UPDATEPLAYER::deliver() { }

ByteBuffer &ZC_NOTIFY_UPDATEPLAYER::serialize()
{
	return buf();
}

/**
 * ZC_SHORTCUT_KEY_LIST
 */
void ZC_SHORTCUT_KEY_LIST::deliver() { }

ByteBuffer &ZC_SHORTCUT_KEY_LIST::serialize()
{
	return buf();
}

/**
 * ZC_ACK_PARTY_NAME
 */
void ZC_ACK_PARTY_NAME::deliver() { }

ByteBuffer &ZC_ACK_PARTY_NAME::serialize()
{
	return buf();
}

/**
 * ZC_DEVOTIONLIST
 */
void ZC_DEVOTIONLIST::deliver() { }

ByteBuffer &ZC_DEVOTIONLIST::serialize()
{
	return buf();
}

/**
 * ZC_PAR_CHANGE_USER
 */
void ZC_PAR_CHANGE_USER::deliver() { }

ByteBuffer &ZC_PAR_CHANGE_USER::serialize()
{
	return buf();
}

/**
 * ZC_MAKINGITEM_LIST
 */
void ZC_MAKINGITEM_LIST::deliver() { }

ByteBuffer &ZC_MAKINGITEM_LIST::serialize()
{
	return buf();
}

/**
 * ZC_REMOVE_EFFECT
 */
void ZC_REMOVE_EFFECT::deliver() { }

ByteBuffer &ZC_REMOVE_EFFECT::serialize()
{
	return buf();
}

/**
 * ZC_GUILD_ZENY_ACK
 */
void ZC_GUILD_ZENY_ACK::deliver() { }

ByteBuffer &ZC_GUILD_ZENY_ACK::serialize()
{
	return buf();
}

/**
 * ZC_STORE_ITEMLIST_EQUIP_V5
 */
void ZC_STORE_ITEMLIST_EQUIP_V5::deliver() { }

ByteBuffer &ZC_STORE_ITEMLIST_EQUIP_V5::serialize()
{
	return buf();
}

/**
 * ZC_SAY_DIALOG
 */
void ZC_SAY_DIALOG::deliver(int32_t npc_id, std::string &message)
{
	_packet_length = 8 + message.size();
	_guid = npc_id;
	_message = message;
}

ByteBuffer &ZC_SAY_DIALOG::serialize()
{
	buf() << _packet_id;
	buf() << _packet_length;
	buf() << _guid;
	buf().append(_message.c_str(), _message.size());
	return buf();
}

/**
 * ZC_ACK_READ_RODEX
 */
void ZC_ACK_READ_RODEX::deliver() { }

ByteBuffer &ZC_ACK_READ_RODEX::serialize()
{
	return buf();
}

/**
 * ZC_GROUPINFO_CHANGE
 */
void ZC_GROUPINFO_CHANGE::deliver() { }

ByteBuffer &ZC_GROUPINFO_CHANGE::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ADDITEM_TO_CART
 */
void ZC_ACK_ADDITEM_TO_CART::deliver() { }

ByteBuffer &ZC_ACK_ADDITEM_TO_CART::serialize()
{
	return buf();
}

/**
 * ZC_STORE_ITEMLIST_EQUIP_V2
 */
void ZC_STORE_ITEMLIST_EQUIP_V2::deliver() { }

ByteBuffer &ZC_STORE_ITEMLIST_EQUIP_V2::serialize()
{
	return buf();
}

/**
 * ZC_ACK_DISORGANIZE_GUILD
 */
void ZC_ACK_DISORGANIZE_GUILD::deliver() { }

ByteBuffer &ZC_ACK_DISORGANIZE_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_OPEN_SEARCH_STORE_INFO
 */
void ZC_OPEN_SEARCH_STORE_INFO::deliver() { }

ByteBuffer &ZC_OPEN_SEARCH_STORE_INFO::serialize()
{
	return buf();
}

/**
 * ZC_NORMAL_ITEMLIST2
 */
void ZC_NORMAL_ITEMLIST2::deliver() { }

ByteBuffer &ZC_NORMAL_ITEMLIST2::serialize()
{
	return buf();
}

/**
 * ZC_NORMAL_ITEMLIST3
 */
void ZC_NORMAL_ITEMLIST3::deliver() { }

ByteBuffer &ZC_NORMAL_ITEMLIST3::serialize()
{
	return buf();
}

/**
 * ZC_IRMAIL_NOTIFY
 */
void ZC_IRMAIL_NOTIFY::deliver() { }

ByteBuffer &ZC_IRMAIL_NOTIFY::serialize()
{
	return buf();
}

/**
 * ZC_ACTIVE_QUEST
 */
void ZC_ACTIVE_QUEST::deliver() { }

ByteBuffer &ZC_ACTIVE_QUEST::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_ACT3
 */
void ZC_NOTIFY_ACT3::deliver() { }

ByteBuffer &ZC_NOTIFY_ACT3::serialize()
{
	return buf();
}

/**
 * ZC_COUPLESTATUS
 */
void ZC_COUPLESTATUS::deliver(int32_t type, int32_t base, int32_t bonus)
{
	_type = type;
	_base = base;
	_bonus = bonus;

	serialize();
	transmit();
}

ByteBuffer &ZC_COUPLESTATUS::serialize()
{
	buf() << _packet_id;
	buf() << _type;
	buf() << _base;
	buf() << _bonus;
	return buf();
}

/**
 * ZC_PET_EVOLUTION_RESULT
 */
void ZC_PET_EVOLUTION_RESULT::deliver() { }

ByteBuffer &ZC_PET_EVOLUTION_RESULT::serialize()
{
	return buf();
}

/**
 * ZC_FORMATSTRING_MSG_COLOR
 */
void ZC_FORMATSTRING_MSG_COLOR::deliver() { }

ByteBuffer &ZC_FORMATSTRING_MSG_COLOR::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_ADD_FILTERLINGLIST
 */
void ZC_PARTY_RECRUIT_ADD_FILTERLINGLIST::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_ADD_FILTERLINGLIST::serialize()
{
	return buf();
}

/**
 * ZC_PERSONAL_INFOMATION_CHN
 */
void ZC_PERSONAL_INFOMATION_CHN::deliver() { }

ByteBuffer &ZC_PERSONAL_INFOMATION_CHN::serialize()
{
	return buf();
}

/**
 * ZC_BATTLEFIELD_NOTIFY_POINT
 */
void ZC_BATTLEFIELD_NOTIFY_POINT::deliver() { }

ByteBuffer &ZC_BATTLEFIELD_NOTIFY_POINT::serialize()
{
	return buf();
}

/**
 * ZC_ACK_SE_CASH_ITEM_LIST
 */
void ZC_ACK_SE_CASH_ITEM_LIST::deliver() { }

ByteBuffer &ZC_ACK_SE_CASH_ITEM_LIST::serialize()
{
	return buf();
}

/**
 * ZC_CHANGE_DIRECTION
 */
void ZC_CHANGE_DIRECTION::deliver() { }

ByteBuffer &ZC_CHANGE_DIRECTION::serialize()
{
	return buf();
}

/**
 * ZC_REPLY_ACK_LOBBY_ADMISSION
 */
void ZC_REPLY_ACK_LOBBY_ADMISSION::deliver() { }

ByteBuffer &ZC_REPLY_ACK_LOBBY_ADMISSION::serialize()
{
	return buf();
}

/**
 * ZC_ISVR_DISCONNECT
 */
void ZC_ISVR_DISCONNECT::deliver() { }

ByteBuffer &ZC_ISVR_DISCONNECT::serialize()
{
	return buf();
}

/**
 * ZC_CLOSE_STORE
 */
void ZC_CLOSE_STORE::deliver() { }

ByteBuffer &ZC_CLOSE_STORE::serialize()
{
	return buf();
}

/**
 * ZC_DEL_QUEST
 */
void ZC_DEL_QUEST::deliver() { }

ByteBuffer &ZC_DEL_QUEST::serialize()
{
	return buf();
}

/**
 * ZC_RECOVERY
 */
void ZC_RECOVERY::deliver() { }

ByteBuffer &ZC_RECOVERY::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MAPPROPERTY
 */
void ZC_NOTIFY_MAPPROPERTY::deliver() { }

ByteBuffer &ZC_NOTIFY_MAPPROPERTY::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REQ_CHANGE_MEMBERS
 */
void ZC_ACK_REQ_CHANGE_MEMBERS::deliver() { }

ByteBuffer &ZC_ACK_REQ_CHANGE_MEMBERS::serialize()
{
	return buf();
}

/**
 * ZC_EL_PAR_CHANGE
 */
void ZC_EL_PAR_CHANGE::deliver() { }

ByteBuffer &ZC_EL_PAR_CHANGE::serialize()
{
	return buf();
}

/**
 * ZC_TAEKWON_RANK
 */
void ZC_TAEKWON_RANK::deliver() { }

ByteBuffer &ZC_TAEKWON_RANK::serialize()
{
	return buf();
}

/**
 * ZC_ALT_EQUIPMENT_REMOVE
 */
void ZC_ALT_EQUIPMENT_REMOVE::deliver() { }

ByteBuffer &ZC_ALT_EQUIPMENT_REMOVE::serialize()
{
	return buf();
}

/**
 * ZC_KILLER_POINT
 */
void ZC_KILLER_POINT::deliver() { }

ByteBuffer &ZC_KILLER_POINT::serialize()
{
	return buf();
}

/**
 * ZC_MER_SKILLINFO_UPDATE
 */
void ZC_MER_SKILLINFO_UPDATE::deliver() { }

ByteBuffer &ZC_MER_SKILLINFO_UPDATE::serialize()
{
	return buf();
}

/**
 * ZC_HO_PAR_CHANGE
 */
void ZC_HO_PAR_CHANGE::deliver() { }

ByteBuffer &ZC_HO_PAR_CHANGE::serialize()
{
	return buf();
}

/**
 * ZC_COMBODELAY
 */
void ZC_COMBODELAY::deliver() { }

ByteBuffer &ZC_COMBODELAY::serialize()
{
	return buf();
}

/**
 * ZC_SECRETSCAN_DATA
 */
void ZC_SECRETSCAN_DATA::deliver() { }

ByteBuffer &ZC_SECRETSCAN_DATA::serialize()
{
	return buf();
}

/**
 * ZC_ACK_LEAVE_GUILD
 */
void ZC_ACK_LEAVE_GUILD::deliver() { }

ByteBuffer &ZC_ACK_LEAVE_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_ACT
 */
void ZC_NOTIFY_ACT::deliver() { }

ByteBuffer &ZC_NOTIFY_ACT::serialize()
{
	return buf();
}

/**
 * ZC_SE_PC_BUY_TAIWANCASHITEM_RESULT
 */
void ZC_SE_PC_BUY_TAIWANCASHITEM_RESULT::deliver() { }

ByteBuffer &ZC_SE_PC_BUY_TAIWANCASHITEM_RESULT::serialize()
{
	return buf();
}

/**
 * ZC_HOSKILLINFO_UPDATE
 */
void ZC_HOSKILLINFO_UPDATE::deliver() { }

ByteBuffer &ZC_HOSKILLINFO_UPDATE::serialize()
{
	return buf();
}

/**
 * ZC_EMOTION
 */
void ZC_EMOTION::deliver() { }

ByteBuffer &ZC_EMOTION::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_STANDENTRY_NPC
 */
void ZC_NOTIFY_STANDENTRY_NPC::deliver() { }

ByteBuffer &ZC_NOTIFY_STANDENTRY_NPC::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REMEMBER_WARPPOINT
 */
void ZC_ACK_REMEMBER_WARPPOINT::deliver() { }

ByteBuffer &ZC_ACK_REMEMBER_WARPPOINT::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_STOREITEM_COUNTINFO
 */
void ZC_NOTIFY_STOREITEM_COUNTINFO::deliver() { }

ByteBuffer &ZC_NOTIFY_STOREITEM_COUNTINFO::serialize()
{
	return buf();
}

/**
 * ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER
 */
void ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER::deliver() { }

ByteBuffer &ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER::serialize()
{
	return buf();
}

/**
 * ZC_ACK_MAIL_DELETE
 */
void ZC_ACK_MAIL_DELETE::deliver() { }

ByteBuffer &ZC_ACK_MAIL_DELETE::serialize()
{
	return buf();
}

/**
 * ZC_PERSONAL_INFOMATION2
 */
void ZC_PERSONAL_INFOMATION2::deliver() { }

ByteBuffer &ZC_PERSONAL_INFOMATION2::serialize()
{
	return buf();
}

/**
 * ZC_UI_ACTION
 */
void ZC_UI_ACTION::deliver() { }

ByteBuffer &ZC_UI_ACTION::serialize()
{
	return buf();
}

/**
 * ZC_ACK_SE_CASH_ITEM_LIST2
 */
void ZC_ACK_SE_CASH_ITEM_LIST2::deliver() { }

ByteBuffer &ZC_ACK_SE_CASH_ITEM_LIST2::serialize()
{
	return buf();
}

/**
 * ZC_ACK_GUILDSTORAGE_LOG
 */
void ZC_ACK_GUILDSTORAGE_LOG::deliver() { }

ByteBuffer &ZC_ACK_GUILDSTORAGE_LOG::serialize()
{
	return buf();
}

/**
 * ZC_MYGUILD_BASIC_INFO
 */
void ZC_MYGUILD_BASIC_INFO::deliver() { }

ByteBuffer &ZC_MYGUILD_BASIC_INFO::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_JOIN_REQ
 */
void ZC_PARTY_JOIN_REQ::deliver() { }

ByteBuffer &ZC_PARTY_JOIN_REQ::serialize()
{
	return buf();
}

/**
 * ZC_SKILLINFO_DELETE
 */
void ZC_SKILLINFO_DELETE::deliver() { }

ByteBuffer &ZC_SKILLINFO_DELETE::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_MOVE
 */
void ZC_NOTIFY_MOVE::deliver(int32_t guid, int16_t from_x, int16_t from_y, int16_t to_x, int16_t to_y)
{
	_guid = guid;
	_timestamp = (int32_t) get_sys_time();
	PackPosition((int8_t *) _packed_pos, from_x, from_y, to_x, to_y, 8, 8);
	
}

ByteBuffer &ZC_NOTIFY_MOVE::serialize()
{
	buf() << _packet_id;
	buf() << _guid;
	buf().append(_packed_pos, sizeof(_packed_pos));
	buf() << _timestamp;
	return buf();
}

/**
 * ZC_CHANGESTATE_MER
 */
void ZC_CHANGESTATE_MER::deliver() { }

ByteBuffer &ZC_CHANGESTATE_MER::serialize()
{
	return buf();
}

/**
 * ZC_ACK_GUILD_MENUINTERFACE
 */
void ZC_ACK_GUILD_MENUINTERFACE::deliver() { }

ByteBuffer &ZC_ACK_GUILD_MENUINTERFACE::serialize()
{
	return buf();
}

/**
 * ZC_ACK_GIVE_MANNER_POINT
 */
void ZC_ACK_GIVE_MANNER_POINT::deliver() { }

ByteBuffer &ZC_ACK_GIVE_MANNER_POINT::serialize()
{
	return buf();
}

/**
 * ZC_GUILD_POSITION
 */
void ZC_GUILD_POSITION::deliver() { }

ByteBuffer &ZC_GUILD_POSITION::serialize()
{
	return buf();
}

/**
 * ZC_EQUIPMENT_ITEMLIST2
 */
void ZC_EQUIPMENT_ITEMLIST2::deliver() { }

ByteBuffer &ZC_EQUIPMENT_ITEMLIST2::serialize()
{
	return buf();
}

/**
 * ZC_EQUIPMENT_ITEMLIST3
 */
void ZC_EQUIPMENT_ITEMLIST3::deliver() { }

ByteBuffer &ZC_EQUIPMENT_ITEMLIST3::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_RECRUIT_NOTIFY_UPDATE
 */
void ZC_PARTY_RECRUIT_NOTIFY_UPDATE::deliver() { }

ByteBuffer &ZC_PARTY_RECRUIT_NOTIFY_UPDATE::serialize()
{
	return buf();
}

/**
 * ZC_PARTY_BOOKING_NOTIFY_UPDATE
 */
void ZC_PARTY_BOOKING_NOTIFY_UPDATE::deliver() { }

ByteBuffer &ZC_PARTY_BOOKING_NOTIFY_UPDATE::serialize()
{
	return buf();
}

/**
 * ZC_UPDATE_MISSION_HUNT
 */
void ZC_UPDATE_MISSION_HUNT::deliver() { }

ByteBuffer &ZC_UPDATE_MISSION_HUNT::serialize()
{
	return buf();
}

/**
 * ZC_RESURRECTION
 */
void ZC_RESURRECTION::deliver() { }

ByteBuffer &ZC_RESURRECTION::serialize()
{
	return buf();
}

/**
 * ZC_MAIL_REQ_OPEN
 */
void ZC_MAIL_REQ_OPEN::deliver() { }

ByteBuffer &ZC_MAIL_REQ_OPEN::serialize()
{
	return buf();
}

/**
 * ZC_ADD_ITEM_TO_CART
 */
void ZC_ADD_ITEM_TO_CART::deliver() { }

ByteBuffer &ZC_ADD_ITEM_TO_CART::serialize()
{
	return buf();
}

/**
 * ZC_FAILED_GET_ITEM_FROM_ZONEDA
 */
void ZC_FAILED_GET_ITEM_FROM_ZONEDA::deliver() { }

ByteBuffer &ZC_FAILED_GET_ITEM_FROM_ZONEDA::serialize()
{
	return buf();
}

/**
 * ZC_ACK_RODEX_LIST
 */
void ZC_ACK_RODEX_LIST::deliver() { }

ByteBuffer &ZC_ACK_RODEX_LIST::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_CHAT
 */
void ZC_NOTIFY_CHAT::deliver(int32_t guid, std::string message)
{
	_guid = guid;
	_packet_length = 8 + message.size();
	_message = message;

	serialize();
	transmit();
}

ByteBuffer &ZC_NOTIFY_CHAT::serialize()
{
	buf() << _packet_id;
	buf() << _packet_length;
	buf() << _guid;
	buf().append(_message.c_str(), _message.size());
	
	return buf();
}

/**
 * ZC_STORE_ITEMLIST_EQUIP_V6
 */
void ZC_STORE_ITEMLIST_EQUIP_V6::deliver() { }

ByteBuffer &ZC_STORE_ITEMLIST_EQUIP_V6::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_STANDENTRY
 */
void ZC_NOTIFY_STANDENTRY::deliver() { }

ByteBuffer &ZC_NOTIFY_STANDENTRY::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_FONT
 */
void ZC_NOTIFY_FONT::deliver() { }

ByteBuffer &ZC_NOTIFY_FONT::serialize()
{
	return buf();
}

/**
 * ZC_HACKSH_ERROR_MSG
 */
void ZC_HACKSH_ERROR_MSG::deliver() { }

ByteBuffer &ZC_HACKSH_ERROR_MSG::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_PCBANG
 */
void ZC_NOTIFY_PCBANG::deliver() { }

ByteBuffer &ZC_NOTIFY_PCBANG::serialize()
{
	return buf();
}

/**
 * ZC_GPK_AUTH
 */
void ZC_GPK_AUTH::deliver() { }

ByteBuffer &ZC_GPK_AUTH::serialize()
{
	return buf();
}

/**
 * ZC_STATE_CHANGE
 */
void ZC_STATE_CHANGE::deliver() { }

ByteBuffer &ZC_STATE_CHANGE::serialize()
{
	return buf();
}

/**
 * ZC_ADD_MEMBER_TO_GROUP
 */
void ZC_ADD_MEMBER_TO_GROUP::deliver() { }

ByteBuffer &ZC_ADD_MEMBER_TO_GROUP::serialize()
{
	return buf();
}

/**
 * ZC_GUILD_INFO2
 */
void ZC_GUILD_INFO2::deliver() { }

ByteBuffer &ZC_GUILD_INFO2::serialize()
{
	return buf();
}

/**
 * ZC_MEMBER_NEWENTRY
 */
void ZC_MEMBER_NEWENTRY::deliver() { }

ByteBuffer &ZC_MEMBER_NEWENTRY::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_BARGAIN_SALE_SELLING
 */
void ZC_NOTIFY_BARGAIN_SALE_SELLING::deliver() { }

ByteBuffer &ZC_NOTIFY_BARGAIN_SALE_SELLING::serialize()
{
	return buf();
}

/**
 * ZC_ACK_DELETE_RODEX
 */
void ZC_ACK_DELETE_RODEX::deliver() { }

ByteBuffer &ZC_ACK_DELETE_RODEX::serialize()
{
	return buf();
}

/**
 * ZC_PC_PURCHASE_ITEMLIST_FROMMC
 */
void ZC_PC_PURCHASE_ITEMLIST_FROMMC::deliver() { }

ByteBuffer &ZC_PC_PURCHASE_ITEMLIST_FROMMC::serialize()
{
	return buf();
}

/**
 * ZC_ACK_REQNAME
 */
void ZC_ACK_REQNAME::deliver(int32_t guid, const char *name)
{
	_guid = guid;
	strncpy(_name, name, MAX_UNIT_NAME_LENGTH);
	serialize();
	transmit();
}

ByteBuffer &ZC_ACK_REQNAME::serialize()
{
	buf() << _packet_id;
	buf().append(_name, MAX_UNIT_NAME_LENGTH);
	return buf();
}

/**
 * ZC_USE_SKILL2
 */
void ZC_USE_SKILL2::deliver() { }

ByteBuffer &ZC_USE_SKILL2::serialize()
{
	return buf();
}

/**
 * ZC_ITEM_FALL_ENTRY4
 */
void ZC_ITEM_FALL_ENTRY4::deliver() { }

ByteBuffer &ZC_ITEM_FALL_ENTRY4::serialize()
{
	return buf();
}

/**
 * ZC_STORE_EQUIPMENT_ITEMLIST
 */
void ZC_STORE_EQUIPMENT_ITEMLIST::deliver() { }

ByteBuffer &ZC_STORE_EQUIPMENT_ITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_ACK_CREATE_CHATROOM
 */
void ZC_ACK_CREATE_CHATROOM::deliver() { }

ByteBuffer &ZC_ACK_CREATE_CHATROOM::serialize()
{
	return buf();
}

/**
 * ZC_PAR_CHANGE
 */
void ZC_PAR_CHANGE::deliver(status_point_type type, int16_t value)
{
	_type = type;
	_value = value;

	serialize();
	transmit();
}

ByteBuffer &ZC_PAR_CHANGE::serialize()
{
	buf() << _packet_id;
	buf() << (int16_t) _type;
	buf() << _value;
	return buf();
}

/**
 * ZC_CART_EQUIPMENT_ITEMLIST2
 */
void ZC_CART_EQUIPMENT_ITEMLIST2::deliver() { }

ByteBuffer &ZC_CART_EQUIPMENT_ITEMLIST2::serialize()
{
	return buf();
}

/**
 * ZC_CART_EQUIPMENT_ITEMLIST3
 */
void ZC_CART_EQUIPMENT_ITEMLIST3::deliver() { }

ByteBuffer &ZC_CART_EQUIPMENT_ITEMLIST3::serialize()
{
	return buf();
}

/**
 * ZC_ACK_WHISPER
 */
void ZC_ACK_WHISPER::deliver() { }

ByteBuffer &ZC_ACK_WHISPER::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_UNREAD_RODEX
 */
void ZC_NOTIFY_UNREAD_RODEX::deliver() { }

ByteBuffer &ZC_NOTIFY_UNREAD_RODEX::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ACCOUNTNAME
 */
void ZC_ACK_ACCOUNTNAME::deliver() { }

ByteBuffer &ZC_ACK_ACCOUNTNAME::serialize()
{
	return buf();
}

/**
 * ZC_ALT_EQUIPMENT_ITEMS
 */
void ZC_ALT_EQUIPMENT_ITEMS::deliver() { }

ByteBuffer &ZC_ALT_EQUIPMENT_ITEMS::serialize()
{
	return buf();
}

/**
 * ZC_CART_NORMAL_ITEMLIST2
 */
void ZC_CART_NORMAL_ITEMLIST2::deliver() { }

ByteBuffer &ZC_CART_NORMAL_ITEMLIST2::serialize()
{
	return buf();
}

/**
 * ZC_CART_NORMAL_ITEMLIST3
 */
void ZC_CART_NORMAL_ITEMLIST3::deliver() { }

ByteBuffer &ZC_CART_NORMAL_ITEMLIST3::serialize()
{
	return buf();
}

/**
 * ZC_ACK_WEAPONREFINE
 */
void ZC_ACK_WEAPONREFINE::deliver() { }

ByteBuffer &ZC_ACK_WEAPONREFINE::serialize()
{
	return buf();
}

/**
 * ZC_UPDATE_ROULETTE_COIN
 */
void ZC_UPDATE_ROULETTE_COIN::deliver() { }

ByteBuffer &ZC_UPDATE_ROULETTE_COIN::serialize()
{
	return buf();
}

/**
 * ZC_BUYING_STORE_ENTRY
 */
void ZC_BUYING_STORE_ENTRY::deliver() { }

ByteBuffer &ZC_BUYING_STORE_ENTRY::serialize()
{
	return buf();
}

/**
 * ZC_BANKING_CHECK
 */
void ZC_BANKING_CHECK::deliver() { }

ByteBuffer &ZC_BANKING_CHECK::serialize()
{
	return buf();
}

/**
 * ZC_EQUIPWIN_MICROSCOPE2
 */
void ZC_EQUIPWIN_MICROSCOPE2::deliver() { }

ByteBuffer &ZC_EQUIPWIN_MICROSCOPE2::serialize()
{
	return buf();
}

/**
 * ZC_DISPATCH_TIMING_INFO_CHN
 */
void ZC_DISPATCH_TIMING_INFO_CHN::deliver() { }

ByteBuffer &ZC_DISPATCH_TIMING_INFO_CHN::serialize()
{
	return buf();
}

/**
 * ZC_CANCEL_BATTLE_FIELD
 */
void ZC_CANCEL_BATTLE_FIELD::deliver() { }

ByteBuffer &ZC_CANCEL_BATTLE_FIELD::serialize()
{
	return buf();
}

/**
 * ZC_RECOVERY2
 */
void ZC_RECOVERY2::deliver() { }

ByteBuffer &ZC_RECOVERY2::serialize()
{
	return buf();
}

/**
 * ZC_UPDATE_ITEM_FROM_BUYING_STORE
 */
void ZC_UPDATE_ITEM_FROM_BUYING_STORE::deliver() { }

ByteBuffer &ZC_UPDATE_ITEM_FROM_BUYING_STORE::serialize()
{
	return buf();
}

/**
 * ZC_RESULT_MAKE_GUILD
 */
void ZC_RESULT_MAKE_GUILD::deliver() { }

ByteBuffer &ZC_RESULT_MAKE_GUILD::serialize()
{
	return buf();
}

/**
 * ZC_ES_LIST
 */
void ZC_ES_LIST::deliver() { }

ByteBuffer &ZC_ES_LIST::serialize()
{
	return buf();
}

/**
 * ZC_BATTLE_FIELD_LIST
 */
void ZC_BATTLE_FIELD_LIST::deliver() { }

ByteBuffer &ZC_BATTLE_FIELD_LIST::serialize()
{
	return buf();
}

/**
 * ZC_ACK_SEND_RODEX
 */
void ZC_ACK_SEND_RODEX::deliver() { }

ByteBuffer &ZC_ACK_SEND_RODEX::serialize()
{
	return buf();
}

/**
 * ZC_AUCTION_WINDOWS
 */
void ZC_AUCTION_WINDOWS::deliver() { }

ByteBuffer &ZC_AUCTION_WINDOWS::serialize()
{
	return buf();
}

/**
 * ZC_ACK_ITEMREFINING
 */
void ZC_ACK_ITEMREFINING::deliver() { }

ByteBuffer &ZC_ACK_ITEMREFINING::serialize()
{
	return buf();
}

/**
 * ZC_SEEK_PARTY
 */
void ZC_SEEK_PARTY::deliver() { }

ByteBuffer &ZC_SEEK_PARTY::serialize()
{
	return buf();
}

/**
 * ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO
 */
void ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO::deliver() { }

ByteBuffer &ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO::serialize()
{
	return buf();
}

/**
 * ZC_SHOWDIGIT
 */
void ZC_SHOWDIGIT::deliver() { }

ByteBuffer &ZC_SHOWDIGIT::serialize()
{
	return buf();
}

/**
 * ZC_ACK_RANKING
 */
void ZC_ACK_RANKING::deliver() { }

ByteBuffer &ZC_ACK_RANKING::serialize()
{
	return buf();
}

/**
 * ZC_MAIL_WINDOWS
 */
void ZC_MAIL_WINDOWS::deliver() { }

ByteBuffer &ZC_MAIL_WINDOWS::serialize()
{
	return buf();
}

/**
 * ZC_DELETEITEM_FROM_MCSTORE
 */
void ZC_DELETEITEM_FROM_MCSTORE::deliver() { }

ByteBuffer &ZC_DELETEITEM_FROM_MCSTORE::serialize()
{
	return buf();
}

/**
 * ZC_ITEMIDENTIFY_LIST
 */
void ZC_ITEMIDENTIFY_LIST::deliver() { }

ByteBuffer &ZC_ITEMIDENTIFY_LIST::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_CHAT_PARTY
 */
void ZC_NOTIFY_CHAT_PARTY::deliver() { }

ByteBuffer &ZC_NOTIFY_CHAT_PARTY::serialize()
{
	return buf();
}

/**
 * ZC_MSG_STATE_CHANGE2
 */
void ZC_MSG_STATE_CHANGE2::deliver() { }

ByteBuffer &ZC_MSG_STATE_CHANGE2::serialize()
{
	return buf();
}

/**
 * ZC_MSG_STATE_CHANGE3
 */
void ZC_MSG_STATE_CHANGE3::deliver() { }

ByteBuffer &ZC_MSG_STATE_CHANGE3::serialize()
{
	return buf();
}

/**
 * ZC_WAIT_DIALOG
 */
void ZC_WAIT_DIALOG::deliver(int32_t guid)
{
	_guid = guid;
	serialize();
	transmit();
}

ByteBuffer &ZC_WAIT_DIALOG::serialize()
{
	buf() << _packet_id;
	buf() << _guid;
	return buf();
}

/**
 * ZC_COUPLENAME
 */
void ZC_COUPLENAME::deliver() { }

ByteBuffer &ZC_COUPLENAME::serialize()
{
	return buf();
}

/**
 * ZC_UPDATE_MISSION_HUNT_EX
 */
void ZC_UPDATE_MISSION_HUNT_EX::deliver() { }

ByteBuffer &ZC_UPDATE_MISSION_HUNT_EX::serialize()
{
	return buf();
}

/**
 * ZC_MAKABLEITEMLIST
 */
void ZC_MAKABLEITEMLIST::deliver() { }

ByteBuffer &ZC_MAKABLEITEMLIST::serialize()
{
	return buf();
}

/**
 * ZC_CART_ITEMLIST_EQUIP_V5
 */
void ZC_CART_ITEMLIST_EQUIP_V5::deliver() { }

ByteBuffer &ZC_CART_ITEMLIST_EQUIP_V5::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_TIME
 */
void ZC_NOTIFY_TIME::deliver() 
{
	_timestamp = (int32_t) get_sys_time();
	serialize();
	transmit();
}

ByteBuffer &ZC_NOTIFY_TIME::serialize()
{
	buf() << _packet_id;
	buf() << _timestamp;
	return buf();
}

/**
 * ZC_POSITION_ID_NAME_INFO
 */
void ZC_POSITION_ID_NAME_INFO::deliver() { }

ByteBuffer &ZC_POSITION_ID_NAME_INFO::serialize()
{
	return buf();
}

/**
 * ZC_ACK_BATTLE_STATE_MONITOR
 */
void ZC_ACK_BATTLE_STATE_MONITOR::deliver() { }

ByteBuffer &ZC_ACK_BATTLE_STATE_MONITOR::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_HP_TO_GROUPM_R2
 */
void ZC_NOTIFY_HP_TO_GROUPM_R2::deliver() { }

ByteBuffer &ZC_NOTIFY_HP_TO_GROUPM_R2::serialize()
{
	return buf();
}

/**
 * ZC_ACK_MERGE_ITEM
 */
void ZC_ACK_MERGE_ITEM::deliver() { }

ByteBuffer &ZC_ACK_MERGE_ITEM::serialize()
{
	return buf();
}

/**
 * ZC_NOTIFY_ACT_POSITION
 */
void ZC_NOTIFY_ACT_POSITION::deliver() { }

ByteBuffer &ZC_NOTIFY_ACT_POSITION::serialize()
{
	return buf();
}

