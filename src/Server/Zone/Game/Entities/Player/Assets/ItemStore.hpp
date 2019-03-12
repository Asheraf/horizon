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

#ifndef HORIZON_ZONE_GAME_ASSETS_ITEMSTORE_HPP
#define HORIZON_ZONE_GAME_ASSETS_ITEMSTORE_HPP

#include "Server/Common/Definitions/ItemDefinitions.hpp"

#include <boost/optional/optional.hpp>
#include <memory>
#include <utility>
#include <vector>

namespace Horizon
{
namespace Zone
{
namespace Game
{
	namespace Entities
	{
		class Player;
	}
namespace Assets
{
enum itemstore_addition_result_type
{
	ITEMSTORE_ADD_SUCCESS          = 0, /// Success
	ITEMSTORE_ADD_INVALID          = 1, /// Invalid itemid not found or negative amount
	ITEMSTORE_ADD_OVER_WEIGHT      = 2, /// Overweight
	ITEMSTORE_ADD_NO_INV_SPACE     = 3, /// No free place found
	ITEMSTORE_ADD_OVER_QUANTITY    = 4, /// Max amount reached
	ITEMSTORE_ADD_OVER_STACK_LIMIT = 5, /// Stack limitation
};
enum itemstore_deletion_reason_type
{
	ITEMSTORE_DEL_NORMAL         = 0, /// Normal
	ITEMSTORE_DEL_SKILLUSE       = 1, /// Item used for a skill
	ITEMSTORE_DEL_FAILREFINE     = 2, /// Refine failed
	ITEMSTORE_DEL_MATERIALCHANGE = 3, /// Material changed
	ITEMSTORE_DEL_TOSTORAGE      = 4, /// Moved to storage
	ITEMSTORE_DEL_TOCART         = 5, /// Moved to cart
	ITEMSTORE_DEL_SOLD           = 6, /// Item sold
	ITEMSTORE_DEL_ANALYSIS       = 7, /// Consumed by Four Spirit Analysis (SO_EL_ANALYSIS) skill
};
class ItemStore
{
typedef std::vector<std::shared_ptr<item_entry_data>> item_storage_type;
public:
	ItemStore(std::weak_ptr<Entities::Player> p, uint32_t max_storage)
	: _max_storage(max_storage), _player(p)
	{ }

	virtual ~ItemStore() { }

	std::shared_ptr<Entities::Player> get_player() { return _player.lock(); }

	itemstore_addition_result_type add_to_itemstore(item_entry_data &item, uint16_t amount);

	void set_max_storage(uint32_t max_storage) { _max_storage = max_storage; }
	uint32_t get_max_storage() { return _max_storage; }

	std::shared_ptr<item_entry_data> get_item_by_id(uint32_t id);
	std::shared_ptr<item_entry_data> get_item_at_index(uint32_t index);

	item_storage_type get_item_store() { return _item_store; }

	virtual void notify_without_equipments() = 0;
	virtual void notify_only_equipments() = 0;
	virtual void notify_add(item_entry_data const &data, uint16_t amount, itemstore_addition_result_type result) = 0;
	virtual void notify_deletion(uint16_t idx, uint16_t amount, itemstore_deletion_reason_type reason) = 0;
	virtual void notify_drop(uint16_t idx, uint16_t amount) = 0;
	virtual void notify_move_fail(uint16_t idx, bool silent) = 0;
	virtual uint32_t sync_to_model() = 0;
	virtual uint32_t sync_from_model() = 0;

protected:
	item_storage_type _item_store;
	uint32_t _max_storage;
private:
	std::weak_ptr<Entities::Player> _player;
};
}
}
}
}
#endif /* HORIZON_ZONE_GAME_ASSETS_ITEMSTORE_HPP */
