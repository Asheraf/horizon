/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#include "ItemStore.hpp"
#include "Common/Definitions/EntityDefinitions.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"

using namespace Horizon::Zone::Game::Assets;
using namespace Horizon::Zone::Game::Entities;

itemstore_addition_result_type ItemStore::add_to_itemstore(item_entry_data &item, uint16_t amount)
{
	if (_item_store.size() >= get_max_storage()) {
		notify_add(item, amount, ITEMSTORE_ADD_NO_INV_SPACE);
		return ITEMSTORE_ADD_NO_INV_SPACE;
	}

	if (amount > MAX_ITEM_STACK_SIZE) {
		notify_add(item, amount, ITEMSTORE_ADD_OVER_QUANTITY);
		return ITEMSTORE_ADD_OVER_QUANTITY;
	}

	if (item.is_stackable()) {
		auto invitem = std::find_if(_item_store.begin(), _item_store.end(), [&item] (std::shared_ptr<item_entry_data> invit) { return *invit == item; });
		if (invitem != _item_store.end()) {
			if ((*invitem)->amount + amount > MAX_ITEM_STACK_SIZE) {
				int left_amt = (*invitem)->amount - MAX_ITEM_STACK_SIZE;
				(*invitem)->amount += left_amt;
				amount -= left_amt;
				add_to_itemstore(item, amount);
				amount = left_amt;
			} else {
				(*invitem)->amount += amount;
			}
			notify_add(*(*invitem), amount, ITEMSTORE_ADD_SUCCESS);
		} else {
			item.amount += amount;
			item.inventory_index = _item_store.size() + 2;
			_item_store.push_back(std::make_shared<item_entry_data>(item));
			notify_add(item, amount, ITEMSTORE_ADD_SUCCESS);
		}
	} else {
		for (int i = 0; i < amount; i++) {
			std::shared_ptr<item_entry_data> itd = std::make_shared<item_entry_data>(item);
			itd->unique_id = get_player()->new_unique_id();
			itd->amount = 1;
			itd->inventory_index = _item_store.size() + 2;
			_item_store.push_back(itd);
			notify_add(*itd, itd->amount, ITEMSTORE_ADD_SUCCESS);
		}
	}

	return ITEMSTORE_ADD_SUCCESS;
}

std::shared_ptr<item_entry_data> ItemStore::get_item_by_id(uint32_t id)
{
	for (auto it = _item_store.begin(); it != _item_store.end(); it++) {
		if ((*it)->item_id == id)
			return *it;
	}

	return std::shared_ptr<item_entry_data>();
}

std::shared_ptr<item_entry_data> ItemStore::get_item_at_index(uint32_t index)
{
	try {
		return _item_store.at(index);
	} catch (std::exception &/*e*/) {
		return std::shared_ptr<item_entry_data>();
	}
}
