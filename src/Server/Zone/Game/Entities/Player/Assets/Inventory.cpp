/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Game/Entities/Traits/Attributes.hpp"
#include "Server/Zone/Interface/ZoneClientInterface.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"

using namespace Horizon::Zone::Entities;
using namespace Horizon::Zone::Entities::Traits;
using namespace Horizon::Zone::Assets;

Inventory::Inventory(std::shared_ptr<Player> player, uint32_t max_storage)
: _player(player), _max_storage(max_storage)
{
	_equipments[IT_EQPI_ACC_L].first = IT_EQPM_ACC_L;
	_equipments[IT_EQPI_ACC_R].first = IT_EQPM_ACC_R;
	_equipments[IT_EQPI_SHOES].first = IT_EQPM_SHOES;
	_equipments[IT_EQPI_GARMENT].first = IT_EQPM_GARMENT;
	_equipments[IT_EQPI_HEAD_LOW].first = IT_EQPM_HEAD_LOW;
	_equipments[IT_EQPI_HEAD_MID].first = IT_EQPM_HEAD_MID;
	_equipments[IT_EQPI_HEAD_TOP].first = IT_EQPM_HEAD_TOP;
	_equipments[IT_EQPI_ARMOR].first = IT_EQPM_ARMOR;
	_equipments[IT_EQPI_HAND_L].first = IT_EQPM_HAND_L;
	_equipments[IT_EQPI_HAND_R].first = IT_EQPM_HAND_R;
	_equipments[IT_EQPI_COSTUME_TOP].first = IT_EQPM_COSTUME_HEAD_TOP;
	_equipments[IT_EQPI_COSTUME_MID].first = IT_EQPM_COSTUME_HEAD_MID;
	_equipments[IT_EQPI_COSTUME_LOW].first = IT_EQPM_COSTUME_HEAD_LOW;
	_equipments[IT_EQPI_COSTUME_GARMENT].first = IT_EQPM_COSTUME_GARMENT;
	_equipments[IT_EQPI_AMMO].first = IT_EQPM_AMMO;
	_equipments[IT_EQPI_SHADOW_ARMOR].first = IT_EQPM_SHADOW_ARMOR;
	_equipments[IT_EQPI_SHADOW_WEAPON].first = IT_EQPM_SHADOW_WEAPON;
	_equipments[IT_EQPI_SHADOW_SHIELD].first = IT_EQPM_SHADOW_SHIELD;
	_equipments[IT_EQPI_SHADOW_SHOES].first = IT_EQPM_SHADOW_SHOES;
	_equipments[IT_EQPI_SHADOW_ACC_R].first = IT_EQPM_SHADOW_ACC_R;
	_equipments[IT_EQPI_SHADOW_ACC_L].first = IT_EQPM_SHADOW_ACC_L;
}

Inventory::~Inventory()
{
	//
}

bool Inventory::use_item(uint32_t inventory_index, uint32_t guid)
{
	std::shared_ptr<item_entry_data> inv_item = _inventory_items.at(inventory_index - 2);

	if (inv_item == nullptr)
		return false;

	std::shared_ptr<const item_config_data> itemd = ItemDB->get_item_by_id(inv_item->item_id);

	if (itemd == nullptr) {
		player()->get_session()->clif()->notify_use_item(inv_item, false);
		return false;
	}

	player()->get_session()->clif()->notify_use_item(inv_item, true);
	return true;
}

item_equip_result_type Inventory::equip_item(uint32_t inventory_index, uint16_t equip_location_mask)
{
	uint32_t job_id = player()->job_id();
	std::shared_ptr<item_entry_data> inv_item = _inventory_items.at(inventory_index - 2);

	if (inv_item == nullptr) {
		HLog(debug) << "Inventory::equip_item: Could not wear item at inventory index " << inventory_index << " - Inventory data not found.";
		return IT_EQUIP_FAIL;
	}

	std::shared_ptr<const item_config_data> itemd = ItemDB->get_item_by_id(inv_item->item_id);

	if (itemd == nullptr) {
		player()->get_session()->clif()->notify_equip_item(inv_item, IT_EQUIP_FAIL);
		return IT_EQUIP_FAIL;
	}

	if (inv_item->current_equip_location_mask != 0 || itemd->equip_location_mask != equip_location_mask) {
		player()->get_session()->clif()->notify_equip_item(inv_item, IT_EQUIP_FAIL);
		return IT_EQUIP_FAIL;
	}

	auto req_job_it = std::find_if(itemd->requirements.job_ids.begin(), itemd->requirements.job_ids.end(),
		[job_id](uint32_t id) {
			return job_id == id;
		});
	if (req_job_it == itemd->requirements.job_ids.end()) {
		player()->get_session()->clif()->notify_equip_item(inv_item, IT_EQUIP_FAIL);
		return IT_EQUIP_FAIL;
	}

	if (itemd->config.bind_on_equip != 0 && inv_item->bind_type == IT_BIND_NONE) {
		inv_item->bind_type = IT_BIND_CHARACTER;
		player()->get_session()->clif()->notify_bind_on_equip(inv_item->inventory_index);
	}

	inv_item->current_equip_location_mask = calculate_current_equip_location_mask(itemd);

	add_to_equipment_list(inv_item);

	if (inv_item->type == IT_TYPE_AMMO) {
		player()->get_session()->clif()->notify_equip_arrow(inv_item);
		player()->get_session()->clif()->notify_action_failure(3);
	} else {
		HLog(debug) << "Inventory Item " << inv_item->inventory_index << " - " << inv_item->item_id << "worn.";
		
		player()->get_session()->clif()->notify_equip_item(inv_item, IT_EQUIP_SUCCESS);
		
		player()->on_item_equip(inv_item);
		
		print_inventory();
	}

	return IT_EQUIP_SUCCESS;
}

item_unequip_result_type Inventory::unequip_item(uint32_t inventory_index)
{
	std::shared_ptr<item_entry_data> inv_item = _inventory_items.at(inventory_index - 2);

	if (inv_item == nullptr) {
		player()->get_session()->clif()->notify_unequip_item(inv_item, IT_UNEQUIP_FAIL);
		return IT_UNEQUIP_FAIL;
	}

	std::shared_ptr<const item_config_data> itemd = ItemDB->get_item_by_id(inv_item->item_id);

	if (itemd == nullptr) {
		player()->get_session()->clif()->notify_unequip_item(inv_item, IT_UNEQUIP_FAIL);
		return IT_UNEQUIP_FAIL;
	}

	player()->get_session()->clif()->notify_unequip_item(inv_item, IT_UNEQUIP_SUCCESS);

	remove_from_equipment_list(inv_item);

	player()->on_item_unequip(inv_item);

	print_inventory();
	return IT_UNEQUIP_SUCCESS;
}

void Inventory::add_to_equipment_list(std::shared_ptr<item_entry_data> item)
{
	for (int i = 0; i < (item_equip_location_index) IT_EQPI_MAX; i++) {
		auto &equip = equipments()[i];
		std::shared_ptr<item_entry_data> id = equip.second.lock();

		// Unequip the existing item and wear the new item.
		if ((item->current_equip_location_mask & equip.first)) {
			if (!equip.second.expired() && unequip_item(id->inventory_index) == IT_UNEQUIP_FAIL)
				return;
			equip.second = item;
		}
	}
}

void Inventory::remove_from_equipment_list(std::shared_ptr<item_entry_data> item)
{
	for (int i = 0; i < (item_equip_location_index)  IT_EQPI_MAX; i++) {
		auto &equip = equipments()[i];
		std::shared_ptr<const item_entry_data> id = equip.second.lock();

		if ((item->current_equip_location_mask & equip.first)) {
			item->current_equip_location_mask &= ~equip.first;
			equip.second.reset();
		}
	}
}

uint32_t Inventory::calculate_current_equip_location_mask(std::shared_ptr<const item_config_data> item)
{
	job_class_mask job_mask = JobDB->job_id_to_mask((job_class_type) player()->job_id());
	uint32_t current_equip_location_mask = item->equip_location_mask;

	if (item->type == IT_TYPE_WEAPON) {
		if (item->sub_type.weapon_t == IT_WT_DAGGER ||
			item->sub_type.weapon_t == IT_WT_1HSWORD ||
			item->sub_type.weapon_t == IT_WT_1HAXE) {
			if ((job_mask & JMASK_ASSASSIN) == JMASK_ASSASSIN
				 || (job_mask & JMASK_KAGEROUOBORO) == JMASK_KAGEROUOBORO) {
				if (item->equip_location_mask == IT_EQPM_HAND_R)
					current_equip_location_mask = IT_EQPM_ARMS;
				if (item->equip_location_mask == IT_EQPM_SHADOW_WEAPON)
					current_equip_location_mask = IT_EQPM_SHADOW_ARMS;
			}
		}
	}

	if (current_equip_location_mask == IT_EQPM_ACC)
		current_equip_location_mask = equipments()[IT_EQPI_ACC_L].second.expired() ? IT_EQPM_ACC_L : IT_EQPM_ACC_R;
	else if (current_equip_location_mask == IT_EQPM_ARMS && item->equip_location_mask == IT_EQPM_WEAPON)
		current_equip_location_mask = equipments()[IT_EQPI_HAND_L].second.expired() ? IT_EQPM_HAND_L : IT_EQPM_HAND_R;
	else if (current_equip_location_mask == IT_EQPM_SHADOW_ACC)
		current_equip_location_mask = equipments()[IT_EQPI_SHADOW_ACC_L].second.expired() ? IT_EQPM_SHADOW_ACC_L : IT_EQPM_SHADOW_ACC_R;
	else if (current_equip_location_mask == IT_EQPM_SHADOW_ARMS && item->equip_location_mask == IT_EQPM_SHADOW_WEAPON)
		current_equip_location_mask = equipments()[IT_EQPI_SHADOW_WEAPON].second.expired() ? IT_EQPM_SHADOW_WEAPON : IT_EQPM_SHADOW_SHIELD;

	return current_equip_location_mask;
}

void Inventory::print_inventory()
{
	HLog(debug) << " -- Inventory List --";
	for (auto i : _inventory_items)
		HLog(debug) << "Idx: " << i->inventory_index << " ItemID: " << i->item_id << " Amount: " << i->amount;


	HLog(debug) << " -- Equipments List --";
	for (int i = 0; i < IT_EQPI_MAX; i++) {
		auto &equip = equipments()[i];
		std::shared_ptr<const item_entry_data> id = equip.second.lock();
		if (id != nullptr)
			HLog(debug) << "Loc:" << std::hex << id->current_equip_location_mask << " Loc2: " << id->actual_equip_location_mask << " Idx: " << std::dec << id->inventory_index << " ItemID: " << id->item_id << " Amount: " << id->amount;
	}
}


void Inventory::notify_all()
{
	notify_only_equipments();
	notify_without_equipments();
}

void Inventory::notify_without_equipments()
{
	std::vector<std::shared_ptr<const item_entry_data>> normal_items;

	for (auto nit = _inventory_items.begin(); nit != _inventory_items.end(); nit++) {
		if ((*nit)->is_equipment() == false)
			normal_items.push_back((*nit));
	}

	player()->get_session()->clif()->notify_normal_item_list(normal_items);

}

void Inventory::notify_only_equipments()
{
	std::vector<std::shared_ptr<const item_entry_data>> equipments;

	for (auto eit = _inventory_items.begin(); eit != _inventory_items.end(); eit++) {
		if ((*eit)->is_equipment())
			equipments.push_back(*eit);
	}

	player()->get_session()->clif()->notify_equipment_item_list(equipments);
}

inventory_addition_result_type Inventory::add_item(uint32_t item_id, uint16_t amount, bool is_identified)
{
	item_entry_data data;
	std::shared_ptr<const item_config_data> item = ItemDB->get_item_by_id(item_id);
	std::shared_ptr<const job_db_data> job = JobDB->get(player()->job_id());
	std::shared_ptr<CurrentWeight> current_weight = player()->status()->current_weight();
	std::shared_ptr<MaxWeight> max_weight = player()->status()->max_weight();

	if (item == nullptr)
		return INVENTORY_ADD_INVALID;

	if (*current_weight + (amount * item->weight) > max_weight->total()) {
		notify_add(data, amount, INVENTORY_ADD_OVER_WEIGHT);
		return INVENTORY_ADD_OVER_WEIGHT;
	}

	if (item->config.stack.inventory && amount > item->config.stack.max_amount) {
		notify_add(data, amount, INVENTORY_ADD_OVER_STACK_LIMIT);
		return INVENTORY_ADD_OVER_STACK_LIMIT;
	}

	// Copy item properties from static db entry.
	data.item_id = item->item_id;
	data.type = item->type;
	data.actual_equip_location_mask = item->equip_location_mask;
	data.bind_type = IT_BIND_NONE;
	data.info.is_identified = is_identified;
	data.info.is_favorite = 0;

	if (_inventory_items.size() >= max_storage()) {
		notify_add(data, amount, INVENTORY_ADD_NO_INV_SPACE);
		return INVENTORY_ADD_NO_INV_SPACE;
	}

	if (amount > MAX_ITEM_STACK_SIZE) {
		notify_add(data, amount, INVENTORY_ADD_OVER_QUANTITY);
		return INVENTORY_ADD_OVER_QUANTITY;
	}

	// Check if item is stackable
	if (data.is_stackable()) {
		// Check if item exists in inventory.
		auto invitem = std::find_if(_inventory_items.begin(), _inventory_items.end(), 
			[&data] (std::shared_ptr<item_entry_data> invit) { return (invit->amount < MAX_ITEM_STACK_SIZE && *invit == data); }
		);
		// If item was found in inventory...
		if (invitem != _inventory_items.end()) {
			// Check if amount exeeds stack size.
			if ((*invitem)->amount + amount > MAX_ITEM_STACK_SIZE) {
				// Add appropriately
				int left_amt = (*invitem)->amount - MAX_ITEM_STACK_SIZE;
				(*invitem)->amount += left_amt;
				amount -= left_amt;
				add_item(item_id, amount, is_identified);
			} else {
				(*invitem)->amount += amount;
				notify_add(*(*invitem), amount, INVENTORY_ADD_SUCCESS);

				current_weight->add_base(item->weight * amount);
				player()->get_session()->clif()->notify_complex_attribute_update(STATUS_CURRENT_WEIGHT, current_weight->total());
			}
		} else {
			data.amount += amount;
			data.inventory_index = _inventory_items.size() + 2;
			_inventory_items.push_back(std::make_shared<item_entry_data>(data));
			notify_add(data, amount, INVENTORY_ADD_SUCCESS);

			current_weight->add_base(item->weight * amount);
			player()->get_session()->clif()->notify_complex_attribute_update(STATUS_CURRENT_WEIGHT, current_weight->total());
		}
	} else {
		for (int i = 0; i < amount; i++) {
			std::shared_ptr<item_entry_data> itd = std::make_shared<item_entry_data>(data);
			itd->unique_id = player()->new_unique_id();
			itd->amount = 1;
			itd->inventory_index = _inventory_items.size() + 2;
			_inventory_items.push_back(itd);
			notify_add(*itd, itd->amount, INVENTORY_ADD_SUCCESS);
		}
		current_weight->add_base(item->weight * amount);
		player()->get_session()->clif()->notify_complex_attribute_update(STATUS_CURRENT_WEIGHT, current_weight->total());
	}

	return INVENTORY_ADD_SUCCESS;
}

void Inventory::notify_add(item_entry_data const &data, uint16_t amount, inventory_addition_result_type result)
{
	item_inventory_addition_notif_type notif_type;

	switch (result)
	{
	case INVENTORY_ADD_SUCCESS: notif_type = ITEM_INV_ADD_SUCCESS; break;
	case INVENTORY_ADD_INVALID: notif_type = ITEM_INV_ADD_INVALID; break;
	case INVENTORY_ADD_OVER_WEIGHT: notif_type = ITEM_INV_ADD_OVER_WEIGHT; break;
	case INVENTORY_ADD_NO_INV_SPACE: notif_type = ITEM_INV_ADD_NO_INV_SPACE; break;
	case INVENTORY_ADD_OVER_QUANTITY: notif_type = ITEM_INV_ADD_OVER_QUANTITY; break;
	case INVENTORY_ADD_OVER_STACK_LIMIT: notif_type = ITEM_INV_ADD_OVER_STACK_LIMIT; break;
	}

	player()->get_session()->clif()->notify_pickup_item(data, amount, notif_type);
}

void Inventory::notify_deletion(uint16_t idx, uint16_t amount, inventory_deletion_reason_type reason)
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
//	std::vector<item_entry_data> &model_items = player()->get_char_model()->get_inventory_model()->get_model_items();
	uint32_t changes = 0;

//	// Add / Subtract existing or new items.
//	for (auto &state_it : _item_store) {
//		auto model_it = std::find_if(model_items.begin(), model_items.end(), [&state_it](item_entry_data &model_item) {
//			return model_item == *state_it;
//		});
//
//		if (model_it != model_items.end()) {
//			bool changed = false;
//			if (model_it->amount != state_it->amount) {
//				model_it->amount = state_it->amount;
//				changed = true;
//			}
//			if (model_it->current_equip_location_mask != state_it->current_equip_location_mask) {
//				model_it->current_equip_location_mask = state_it->current_equip_location_mask;
//				changed = true;
//			}
//			if (changed)
//				changes++;
//		} else {
//			model_items.push_back(*state_it);
//			changes++;
//		}
//	}
//
//	// Delete non-existing items.
//	for (auto model_it = model_items.begin(); model_it != model_items.end(); model_it++) {
//		auto state_it = std::find_if(_item_store.begin(), _item_store.end(), [&model_it](std::shared_ptr<item_entry_data> state_it) {
//			return *state_it == *model_it;
//		});
//
//		if (state_it == _item_store.end()) {
//			model_it = model_items.erase(model_it);
//			changes++;
//		}
//	}

	return changes;
}

uint32_t Inventory::sync_from_model()
{
//	if (_item_store.size() > 0) {
//		HLog(warning) << "Horizon::Zone::Assets::Inventory::sync_from_model:\n"
//			"Attempt to sync when item store is not empty. Current size: " << _item_store.size();
//		return 0;
//	}
//
//	std::vector<item_entry_data> &model_items = player()->get_char_model()->get_inventory_model()->get_model_items();
//
//	for (auto &mitem : model_items) {
//		std::shared_ptr<item_entry_data> item = std::make_shared<item_entry_data>(mitem);
//		std::shared_ptr<const item_config_data> itemd = ItemDB->get_item_by_id(item->item_id);
//		item->type = mitem.type = itemd->type;
//		item->sprite_id = mitem.sprite_id = itemd->sprite_id;
//		item->actual_equip_location_mask = mitem.actual_equip_location_mask = itemd->equip_location_mask;
//		_item_store.push_back(item);
//		if (item->current_equip_location_mask > 0)
//			add_to_equipment_list(item);
//		// set without notifying client of weight, @see Player::on_map_enter is to be called after this
//		// method to ensure client notifications.
//		player()->get_status()->get_current_weight()->add_base(itemd->weight * item->amount, false);
//	}

	return _inventory_items.size();
}
