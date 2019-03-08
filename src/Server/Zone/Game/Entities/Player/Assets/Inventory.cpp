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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#include "Inventory.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/Character/Inventory.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Packets/PacketHandler.hpp"
#include "Server/Zone/Game/Status/Status.hpp"
#include "Server/Zone/Game/Status/Attributes.hpp"

using namespace Horizon::Zone::Game::Status;
using namespace Horizon::Zone::Game::Entities;
using namespace Horizon::Zone::Game::Assets;

Inventory::Inventory(std::weak_ptr<Player> player, uint32_t max_storage)
: ItemStore(player, max_storage), _packet_handler(player.lock()->get_packet_handler())
{
	_equipped_items[IT_EQPI_ACC_L].first = IT_EQPM_ACC_L;
	_equipped_items[IT_EQPI_ACC_R].first = IT_EQPM_ACC_R;
	_equipped_items[IT_EQPI_SHOES].first = IT_EQPM_SHOES;
	_equipped_items[IT_EQPI_GARMENT].first = IT_EQPM_GARMENT;
	_equipped_items[IT_EQPI_HEAD_LOW].first = IT_EQPM_HEAD_LOW;
	_equipped_items[IT_EQPI_HEAD_MID].first = IT_EQPM_HEAD_MID;
	_equipped_items[IT_EQPI_HEAD_TOP].first = IT_EQPM_HEAD_TOP;
	_equipped_items[IT_EQPI_ARMOR].first = IT_EQPM_ARMOR;
	_equipped_items[IT_EQPI_HAND_L].first = IT_EQPM_HAND_L;
	_equipped_items[IT_EQPI_HAND_R].first = IT_EQPM_HAND_R;
	_equipped_items[IT_EQPI_COSTUME_TOP].first = IT_EQPM_COSTUME_HEAD_TOP;
	_equipped_items[IT_EQPI_COSTUME_MID].first = IT_EQPM_COSTUME_HEAD_MID;
	_equipped_items[IT_EQPI_COSTUME_LOW].first = IT_EQPM_COSTUME_HEAD_LOW;
	_equipped_items[IT_EQPI_COSTUME_GARMENT].first = IT_EQPM_COSTUME_GARMENT;
	_equipped_items[IT_EQPI_AMMO].first = IT_EQPM_AMMO;
	_equipped_items[IT_EQPI_SHADOW_ARMOR].first = IT_EQPM_SHADOW_ARMOR;
	_equipped_items[IT_EQPI_SHADOW_WEAPON].first = IT_EQPM_SHADOW_WEAPON;
	_equipped_items[IT_EQPI_SHADOW_SHIELD].first = IT_EQPM_SHADOW_SHIELD;
	_equipped_items[IT_EQPI_SHADOW_SHOES].first = IT_EQPM_SHADOW_SHOES;
	_equipped_items[IT_EQPI_SHADOW_ACC_R].first = IT_EQPM_SHADOW_ACC_R;
	_equipped_items[IT_EQPI_SHADOW_ACC_L].first = IT_EQPM_SHADOW_ACC_L;
}

Inventory::~Inventory()
{
	//
}

bool Inventory::use_item(uint32_t inventory_index, uint32_t guid)
{
	std::shared_ptr<item_entry_data> inv_item = get_item_at_index(inventory_index);

	if (inv_item == nullptr)
		return false;

	std::shared_ptr<const item_config_data> itemd = ItemDB->get(inv_item->item_id);

	if (itemd == nullptr) {
		get_packet_handler()->Send_ZC_USE_ITEM_ACK(inv_item, false);
		return false;
	}

	get_packet_handler()->Send_ZC_USE_ITEM_ACK(inv_item, true);
	return true;
}

item_equip_result_type Inventory::equip_item(uint32_t inventory_index, uint16_t equip_location_mask)
{
	std::shared_ptr<item_entry_data> inv_item = get_item_at_index(inventory_index);

	if (inv_item == nullptr)
		return IT_EQUIP_FAIL;

	std::shared_ptr<const item_config_data> itemd = ItemDB->get(inv_item->item_id);

	if (itemd == nullptr) {
		get_packet_handler()->Send_ZC_REQ_WEAR_EQUIP_ACK(inv_item, IT_EQUIP_FAIL);
		return IT_EQUIP_FAIL;
	}

	if (inv_item->current_equip_location_mask != 0 || itemd->equip_location_mask != equip_location_mask) {
		get_packet_handler()->Send_ZC_REQ_WEAR_EQUIP_ACK(inv_item, IT_EQUIP_FAIL);
		return IT_EQUIP_FAIL;
	}

	if (itemd->config.bind_on_equip != 0 && inv_item->bound_type == 0) {
		inv_item->bound_type = IT_BIND_CHARACTER;
		get_packet_handler()->Send_ZC_NOTIFY_BIND_ON_EQUIP(inv_item);
	}

	inv_item->current_equip_location_mask = calculate_current_equip_location_mask(itemd);

	for (int i = 0; i < IT_EQPI_MAX; i++) {
		auto &equip = get_equipped_items()[i];

		if ((inv_item->current_equip_location_mask & equip.first)) {
			if (!equip.second.expired())
				unequip_item(equip.second.lock()->inventory_index - 2);
			equip.second = inv_item;
		}
	}

	if (inv_item->type == IT_TYPE_AMMO) {
		get_packet_handler()->Send_ZC_EQUIP_ARROW(inv_item);
		get_packet_handler()->Send_ZC_ACTION_MESSAGE(3);
	} else {
		get_packet_handler()->Send_ZC_REQ_WEAR_EQUIP_ACK(inv_item, IT_EQUIP_SUCCESS);
	}

	get_player()->on_item_equip(inv_item);

	return IT_EQUIP_SUCCESS;
}

item_unequip_result_type Inventory::unequip_item(uint32_t inventory_index)
{
	std::shared_ptr<item_entry_data> inv_item = get_item_at_index(inventory_index);

	if (inv_item == nullptr) {
		get_packet_handler()->Send_ZC_REQ_TAKEOFF_EQUIP_ACK(inv_item, IT_UNEQUIP_FAIL);
		return IT_UNEQUIP_FAIL;
	}

	std::shared_ptr<const item_config_data> itemd = ItemDB->get(inv_item->item_id);

	if (itemd == nullptr) {
		get_packet_handler()->Send_ZC_REQ_TAKEOFF_EQUIP_ACK(inv_item, IT_UNEQUIP_FAIL);
		return IT_UNEQUIP_FAIL;
	}

	get_packet_handler()->Send_ZC_REQ_TAKEOFF_EQUIP_ACK(inv_item, IT_UNEQUIP_SUCCESS);
	
	for (int i = 0; i < IT_EQPI_MAX; i++) {
		auto &equip = get_equipped_items()[i];

		if ((inv_item->current_equip_location_mask & equip.first)) {
			inv_item->current_equip_location_mask &= ~equip.first;
			equip.second.reset();
		}
	}

	get_player()->on_item_unequip(inv_item);
	
	return IT_UNEQUIP_SUCCESS;
}

itemstore_addition_result_type Inventory::add_item(uint32_t item_id, uint16_t amount, bool is_identified)
{
	item_entry_data data;
	std::shared_ptr<const item_config_data> item = ItemDB->get(item_id);
	std::shared_ptr<const job_db_data> job = JobDB->get(get_player()->get_job_id());
	std::shared_ptr<CurrentWeight> current_weight = get_player()->get_status()->get_current_weight();

	if (item == nullptr)
		return ITEMSTORE_ADD_INVALID;

	if (*current_weight + (amount * item->weight) > job->max_weight) {
		notify_add(data, amount, ITEMSTORE_ADD_OVER_WEIGHT);
		return ITEMSTORE_ADD_OVER_WEIGHT;
	}

	if (item->config.stack.inventory && amount > item->config.stack.max_amount) {
		notify_add(data, amount, ITEMSTORE_ADD_OVER_STACK_LIMIT);
		return ITEMSTORE_ADD_OVER_STACK_LIMIT;
	}

	// Copy item properties from static db entry.
	data.item_id = item->item_id;
	data.type = item->type;
	data.actual_equip_location_mask = item->equip_location_mask;
	data.bound_type = IT_BIND_NONE;
	data.info.is_identified = is_identified;
	data.info.is_favorite = 0;

	itemstore_addition_result_type result = add_to_itemstore(data, amount);

	if (result == ITEMSTORE_ADD_SUCCESS) {
		current_weight->add_base(item->weight * amount, true);
	}
	
	return result;
}

uint32_t Inventory::calculate_current_equip_location_mask(std::shared_ptr<const item_config_data> item)
{
	job_class_mask job_mask = JobDB->job_id_to_mask((job_class_type) get_player()->get_job_id());
	uint32_t current_equip_location_mask = item->equip_location_mask;

	if (item->type == IT_TYPE_WEAPON) {
		if (item->sub_type.weapon_t == WT_DAGGER ||
			item->sub_type.weapon_t == WT_1HSWORD ||
			item->sub_type.weapon_t == WT_1HAXE) {
			if ((job_mask & JMASK_2) == JMASK_ASSASSIN
				|| (job_mask & JMASK_2) == JMASK_KAGEROUOBORO) {
				if (item->equip_location_mask == IT_EQPM_HAND_R)
					current_equip_location_mask = IT_EQPM_ARMS;
				if (item->equip_location_mask == IT_EQPM_SHADOW_WEAPON)
					current_equip_location_mask = IT_EQPM_SHADOW_ARMS;
			}
		}
	}

	if (current_equip_location_mask == IT_EQPM_ACC)
		current_equip_location_mask = get_equipped_items()[IT_EQPI_ACC_L].second.expired() ? IT_EQPM_ACC_L : IT_EQPM_ACC_R;
	else if (current_equip_location_mask == IT_EQPM_ARMS && item->equip_location_mask == IT_EQPM_WEAPON)
		current_equip_location_mask = get_equipped_items()[IT_EQPI_HAND_L].second.expired() ? IT_EQPM_HAND_L : IT_EQPM_HAND_R;
	else if (current_equip_location_mask == IT_EQPM_SHADOW_ACC)
		current_equip_location_mask = get_equipped_items()[IT_EQPI_SHADOW_ACC_L].second.expired() ? IT_EQPM_SHADOW_ACC_L : IT_EQPM_SHADOW_ACC_R;
	else if (current_equip_location_mask == IT_EQPM_SHADOW_ARMS && item->equip_location_mask == IT_EQPM_SHADOW_WEAPON)
		current_equip_location_mask = get_equipped_items()[IT_EQPI_SHADOW_WEAPON].second.expired() ? IT_EQPM_SHADOW_WEAPON : IT_EQPM_SHADOW_SHIELD;

	return current_equip_location_mask;
}


void Inventory::notify_all()
{
	notify_only_equipments();
	notify_without_equipments();
}

void Inventory::notify_without_equipments()
{
	std::vector<std::shared_ptr<const item_entry_data>> normal_items;

	for (auto nit = _item_store.begin(); nit != _item_store.end(); nit++) {
		if ((*nit)->is_equipment() == false)
			normal_items.push_back((*nit));
	}

	get_packet_handler()->Send_ZC_NORMAL_ITEMLIST(normal_items);
}

void Inventory::notify_only_equipments()
{
	std::vector<std::shared_ptr<const item_entry_data>> equipments;

	for (auto eit = _item_store.begin(); eit != _item_store.end(); eit++) {
		if ((*eit)->is_equipment())
			equipments.push_back(*eit);
	}

	get_packet_handler()->Send_ZC_EQUIPMENT_ITEMLIST(equipments);
}

void Inventory::notify_add(item_entry_data const &data, uint16_t amount, itemstore_addition_result_type result)
{
	item_inventory_addition_notif_type notif_type;

	switch (result)
	{
	case ITEMSTORE_ADD_SUCCESS: notif_type = ITEM_INV_ADD_SUCCESS; break;
	case ITEMSTORE_ADD_INVALID: notif_type = ITEM_INV_ADD_INVALID; break;
	case ITEMSTORE_ADD_OVER_WEIGHT: notif_type = ITEM_INV_ADD_OVER_WEIGHT; break;
	case ITEMSTORE_ADD_NO_INV_SPACE: notif_type = ITEM_INV_ADD_NO_INV_SPACE; break;
	case ITEMSTORE_ADD_OVER_QUANTITY: notif_type = ITEM_INV_ADD_OVER_QUANTITY; break;
	case ITEMSTORE_ADD_OVER_STACK_LIMIT: notif_type = ITEM_INV_ADD_OVER_STACK_LIMIT; break;
	}

	get_packet_handler()->Send_ZC_ITEM_PICKUP_ACK(data, amount, notif_type);
}

void Inventory::notify_deletion(uint16_t idx, uint16_t amount, itemstore_deletion_reason_type reason)
{

}

void Inventory::notify_drop(uint16_t idx, uint16_t amount)
{

}

void Inventory::notify_move_fail(uint16_t idx, bool silent)
{

}

uint32_t Inventory::sync_to_model()
{
	std::vector<item_entry_data> &model_items = get_player()->get_char_model()->get_inventory_model()->get_model_items();
	uint32_t changes = 0;

	// Add / Subtract existing or new items.
	for (auto &state_it : _item_store) {
		auto model_it = std::find_if(model_items.begin(), model_items.end(), [&state_it](item_entry_data &model_item) {
			return model_item == *state_it;
		});

		if (model_it != model_items.end()) {
			if (model_it->amount != state_it->amount) {
				model_it->amount = state_it->amount;
				changes++;
			}
		} else {
			model_items.push_back(*state_it);
			changes++;
		}
	}

	// Delete non-existing items.
	for (auto model_it = model_items.begin(); model_it != model_items.end(); model_it++) {
		auto state_it = std::find_if(_item_store.begin(), _item_store.end(), [&model_it](std::shared_ptr<item_entry_data> state_it) {
			return *state_it == *model_it;
		});

		if (state_it == _item_store.end()) {
			model_it = model_items.erase(model_it);
			changes++;
		}
	}

	return changes;
}

uint32_t Inventory::sync_from_model()
{
	if (_item_store.size() > 0) {
		ZoneLog->warn("Horizon::Zone::Game::Assets::Inventory::sync_from_model:\n"
			"Attempt to sync when item store is not empty. Current size: {}.", _item_store.size());
		return 0;
	}

	std::vector<item_entry_data> &model_items = get_player()->get_char_model()->get_inventory_model()->get_model_items();

	for (auto &mitem : model_items) {
		std::shared_ptr<item_entry_data> item = std::make_shared<item_entry_data>(mitem);
		std::shared_ptr<const item_config_data> itemd = ItemDB->get(item->item_id);
		item->type = itemd->type;
		item->sprite_id = itemd->sprite_id;
		item->actual_equip_location_mask = itemd->equip_location_mask;
		_item_store.push_back(item);
		get_player()->get_status()->get_current_weight()->add_base(itemd->weight * item->amount);
	}
	
	return _item_store.size();
}
