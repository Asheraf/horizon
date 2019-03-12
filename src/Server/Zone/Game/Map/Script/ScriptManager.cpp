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

#include "ScriptManager.hpp"

#include "Common/Definitions/ItemDefinitions.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Player/Assets/Inventory.hpp"
#include "Server/Zone/Game/Entities/NPC/NPC.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Map/Coordinates.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/Status/Status.hpp"
#include "Server/Zone/Game/Status/Attributes.hpp"
#include "Server/Zone/Game/Status/Appearance.hpp"
#include "Server/Zone/Packets/PacketHandler.hpp"

using namespace Horizon::Zone::Game;
using namespace Horizon::Zone::Game::Entities;

ScriptManager::ScriptManager(std::weak_ptr<MapThreadContainer> container)
: _container(container)
{

}

ScriptManager::~ScriptManager()
{

}

void ScriptManager::initialize()
{
	initialize_state(_lua_state);
	load_constants();
	load_scripts();
}

void ScriptManager::initialize_state(sol::state &st)
{
	sol::protected_function_result res;

	st.open_libraries(sol::lib::base);
	st.open_libraries(sol::lib::string);
	st.open_libraries(sol::lib::math);
	st.open_libraries(sol::lib::coroutine);
	st.open_libraries(sol::lib::jit);
	st.open_libraries(sol::lib::table);
	st.open_libraries(sol::lib::package);

	st.set_function("cast_entity_to_player",
					[] (std::shared_ptr<Entity> e)
					{
						return e->template downcast<Player>();
					});

	/**
	 * Map Functions
	 */
	st.new_usertype<Map>("Map",
		"get_name", sol::readonly_property(&Map::get_name),
		"get_width", sol::readonly_property(&Map::get_width),
		"get_height", sol::readonly_property(&Map::get_height),
		"has_obstruction_at", &Map::has_obstruction_at
		);
	st.set_function("get_map_by_name",
		[] (std::string const &name)
		{
			return MapMgr->get_map(name);
		});

	st.set_function("get_map_for_container",
		[this] (std::string const &name)
		{
			std::shared_ptr<Map> map = MapMgr->get_map(name);

			if (map == nullptr
				|| ((void *) map->get_map_container().get() != ((_container.lock()).get())))
				return std::shared_ptr<Map>();

			return map;
		});

	/*
	 * NPC definition and container-based loader.
	 */
	st.set_function("NewNPC",
		[this] (std::string const &name, std::string const &map_name, uint16_t x, uint16_t y, uint32_t job_id, directions dir, std::string const &script_file) {
			std::shared_ptr<Map> map = MapMgr->get_map(map_name);

			if (map == nullptr
				|| ((void *) map->get_map_container().get() != ((_container.lock()).get())))
				return std::shared_ptr<NPC>();

			std::shared_ptr<NPC> npc = std::make_shared<NPC>(name, map, x, y, job_id, dir, script_file);
			npc->initialize();

			return npc;
		});

	st.set_function("DupNPC",
		[this] (std::string const &name, std::string const &map_name, uint16_t x, uint16_t y, uint32_t job_id, directions dir, std::shared_ptr<NPC> duplicate) {
			std::shared_ptr<Map> map = MapMgr->get_map(map_name);

			if (map == nullptr
				|| ((void *) map->get_map_container().get() != ((_container.lock()).get())))
				return std::shared_ptr<NPC>();

			std::shared_ptr<NPC> npc = std::make_shared<NPC>(name, map, x, y, job_id, dir, duplicate);
			npc->initialize();

			return npc;
		});
	st.set_function("SilentNPC",
		[this] (std::string const &name, std::string const &map_name, uint16_t x, uint16_t y, uint32_t job_id, directions dir) {
			std::shared_ptr<Map> map = MapMgr->get_map(map_name);

			if (map == nullptr
				|| ((void *) map->get_map_container().get() != ((_container.lock()).get())))
				return std::shared_ptr<NPC>();

			std::shared_ptr<NPC> npc = std::make_shared<NPC>(name, map, x, y, job_id, dir);
			npc->initialize();

			return npc;
		});

	st.set_function("Warp",
		[this] (std::string const &name, std::string const &map_name, uint16_t x, uint16_t y, std::string const &script, uint16_t trigger_range) {
			std::shared_ptr<Map> map = MapMgr->get_map(map_name);

			if (map == nullptr
				|| ((void *) map->get_map_container().get() != ((_container.lock()).get())))
				return std::shared_ptr<NPC>();

			std::shared_ptr<NPC> npc = std::make_shared<NPC>(name, map, x, y, script, trigger_range);
			npc->initialize();

			return npc;
		});

	/**
	 * Items
	 */
	st.new_usertype<item_entry_data::options>("item_options",
		"index", sol::property(&item_entry_data::options::get_index, &item_entry_data::options::set_index),
		"value", sol::property(&item_entry_data::options::get_value, &item_entry_data::options::set_value)
		);

	st.new_usertype<item_entry_data>("item_entry_data",
		"is_equipment", &item_entry_data::is_equipment,
		"is_stackable", &item_entry_data::is_stackable,
		"is_same_as", &item_entry_data::operator ==,
		"inventory_index", sol::readonly(&item_entry_data::inventory_index),
		"item_id", sol::readonly(&item_entry_data::item_id),
		"type", sol::readonly(&item_entry_data::type),
		"amount", sol::readonly(&item_entry_data::amount),
		"current_equip_location_mask", sol::readonly(&item_entry_data::current_equip_location_mask),
		"actual_equip_location_mask", sol::readonly(&item_entry_data::actual_equip_location_mask),
		"refine_level", sol::property(&item_entry_data::get_refine_level, &item_entry_data::set_refine_level),
		"slot_item_id", sol::property([] (item_entry_data &item) {
			return std::ref(item.slot_item_id);
		}),
		"hire_expire_date", sol::property(&item_entry_data::get_hire_expire_date, &item_entry_data::set_hire_expire_date),
		"bind_type", sol::property(&item_entry_data::get_bind_type, &item_entry_data::set_bind_type),
		"sprite_id", sol::readonly(&item_entry_data::sprite_id),
		"element_type", sol::readonly(&item_entry_data::element_type),
		"option_count", sol::property(&item_entry_data::get_option_count, &item_entry_data::set_option_count),
		"options_data", sol::property([] (item_entry_data &item) {
			return std::ref(item.option_data);
		}),
		"unique_id", sol::readonly(&item_entry_data::unique_id)
		);

	st.new_usertype<item_config_data>("item_config_data",
		"item_id", sol::readonly(&item_config_data::item_id),
		"name", sol::readonly(&item_config_data::name),
		"aegis_name", sol::readonly(&item_config_data::aegis_name),
		"value_buy", sol::readonly(&item_config_data::value_buy),
	  	"value_sell", sol::readonly(&item_config_data::value_sell),
		"type", sol::readonly(&item_config_data::type),
		"item_sub_type", sol::readonly_property([] (item_config_data &item) {
			return item.type == IT_TYPE_WEAPON ? item.sub_type.weapon_t : item.sub_type.ammo_t;
		}),
		"equip_location_mask", sol::readonly(&item_config_data::equip_location_mask),
		"weight", sol::readonly(&item_config_data::weight),
		"attack", sol::readonly(&item_config_data::attack),
		"defense", sol::readonly(&item_config_data::defense),
		"attack_range", sol::readonly(&item_config_data::attack_range),
		"card_slot_count", sol::readonly(&item_config_data::card_slot_count),
		"sprite_id", sol::readonly(&item_config_data::sprite_id),
		"level", sol::readonly_property([] (item_config_data &item) {
			return item.type == IT_TYPE_WEAPON ? item.level.weapon : item.level.armor;
		}),
		"magic_atk", sol::readonly(&item_config_data::magic_atk),
		"req_min_lv", sol::readonly_property([] (item_config_data &item) {
			return item.requirements.min_lv;
		}),
		"req_max_lv", sol::readonly_property([] (item_config_data &item) {
			return item.requirements.max_lv;
		}),
		"req_job_ids", sol::readonly_property([] (item_config_data &item) {
			return item.requirements.job_ids;
		}),
		"req_gender", sol::readonly_property([] (item_config_data &item) {
			return item.requirements.gender;
		}),
		"default_script", sol::readonly(&item_config_data::default_script),
		"equip_script", sol::readonly(&item_config_data::equip_script),
		"unequip_script", sol::readonly(&item_config_data::unequip_script),
		"available", sol::readonly_property([] (item_config_data &item) {
			return item.config.available ? 1 : 0;
		}),
		"refineable", sol::readonly_property([] (item_config_data &item) {
			return item.config.refineable ? 1 : 0;
		}),
		"trade_restriction", sol::readonly_property([] (item_config_data &item) {
			return (uint16_t) item.config.trade_restriction;
		}),
		"allow_item_options", sol::readonly_property([] (item_config_data &item) {
			return item.config.allow_item_options ? 1 : 0;
		}),
		"bind_on_equip", sol::readonly_property([] (item_config_data &item) {
			return item.config.bind_on_equip ? 1 : 0;
		}),
		"drop_announce", sol::readonly_property([] (item_config_data &item) {
			return item.config.drop_announce ? 1 :0;
		})
		);

	st.set_function("get_item_info",
					[] (uint32_t item_id) {
						return ItemDB->get_item_by_id(item_id);
					});

	st.new_usertype<MapCoords>("MapCoords",
		sol::constructors<MapCoords(uint16_t, uint16_t)>(),
		"x", &MapCoords::x,
		"y", &MapCoords::y
		);

	st.new_usertype<NPC>("NPC",
		"get_guid", &NPC::get_guid,
		"get_name", &NPC::get_name,
		"map_coords", &NPC::get_map_coords,
		"get_nearby_entity", &NPC::get_nearby_entity,
		"init", &NPC::initialize,
		"set_map", &NPC::set_map
		);

	st.new_usertype<Assets::Inventory>("Inventory",
		"get_item_by_id", &Assets::Inventory::get_item_by_id,
		"get_item_at_index", &Assets::Inventory::get_item_at_index,
		"add_item", &Assets::Inventory::add_item,
		"get_all_items", &Assets::Inventory::get_item_store
		);

	st.new_usertype<Player>("Player",
		"reinitialize_state", [this] (std::shared_ptr<Player> player)
		{
			initialize_state(player->get_lua_state());
		},
		"get_guid", &Player::get_guid,
		"get_map", &Player::get_map,
		"map_coords", &Player::get_map_coords,
		"get_nearby_entity", &Player::get_nearby_entity,
		"send_npc_dialog", &Player::send_npc_dialog,
		"send_npc_next_dialog", &Player::send_npc_next_dialog,
		"send_npc_close_dialog", &Player::send_npc_close_dialog,
		"send_npc_menu_list", &Player::send_npc_menu_list,
		"move_to_map", &Player::move_to_map,
		"get_inventory", &Player::get_inventory,
		"message", [] (std::shared_ptr<Player> player, std::string const &message)
		{
			player->get_packet_handler()->Send_ZC_NOTIFY_PLAYERCHAT(message);
		},
		"get_status", &Player::get_status
		);

	st.new_usertype<Status::Status>("Status",
		"get_strength", &Status::Status::get_strength,
		"get_agility", &Status::Status::get_agility,
		"get_vitality", &Status::Status::get_vitality,
		"get_dexterity", &Status::Status::get_dexterity,
		"get_intelligence", &Status::Status::get_intelligence,
		"get_luck", &Status::Status::get_luck,
		"get_max_hp", &Status::Status::get_max_hp,
		"get_max_sp", &Status::Status::get_max_sp,
		"get_current_hp", &Status::Status::get_current_hp,
		"get_current_sp", &Status::Status::get_current_sp,
		"get_base_level", &Status::Status::get_base_level,
		"get_job_level", &Status::Status::get_job_level,
		"get_base_experience", &Status::Status::get_base_experience,
		"get_job_experience", &Status::Status::get_job_experience,
		"get_next_base_experience", &Status::Status::get_next_base_experience,
		"get_next_job_experience", &Status::Status::get_next_job_experience,
		"get_movement_speed", &Status::Status::get_movement_speed,
		"get_max_weight", &Status::Status::get_max_weight,
		"get_current_weight", &Status::Status::get_current_weight,
		"get_hair_color", &Status::Status::get_hair_color,
		"get_cloth_color", &Status::Status::get_cloth_color,
		"get_weapon_sprite", &Status::Status::get_weapon_sprite,
		"get_shield_sprite", &Status::Status::get_shield_sprite,
		"get_robe_sprite", &Status::Status::get_robe_sprite,
		"get_head_top_sprite", &Status::Status::get_head_top_sprite,
		"get_head_mid_sprite", &Status::Status::get_head_mid_sprite,
		"get_head_bottom_sprite", &Status::Status::get_head_bottom_sprite,
		"get_hair_style", &Status::Status::get_hair_style,
		"get_body_style", &Status::Status::get_body_style
		);

	st.new_usertype<Status::BaseLevel>("BaseLevel",
		"add", &Status::BaseLevel::add_base,
		"sub", &Status::BaseLevel::sub_base,
		"get", &Status::BaseLevel::get_base,
		"set", &Status::BaseLevel::set_base
		);
	st.new_usertype<Status::JobLevel>("JobLevel",
		"add", &Status::JobLevel::add_base,
		"sub", &Status::JobLevel::sub_base,
		"get", &Status::JobLevel::get_base,
		"set", &Status::JobLevel::set_base
		);
	st.new_usertype<Status::MaxHP>("MaxHP",
		"add_base", &Status::MaxHP::add_base,
		"sub_base", &Status::MaxHP::sub_base,
		"get_base", &Status::MaxHP::get_base,
		"set_base", &Status::MaxHP::set_base
		);
	st.new_usertype<Status::MaxSP>("MaxSP",
		"add_base", &Status::MaxSP::add_base,
		"sub_base", &Status::MaxSP::sub_base,
		"get_base", &Status::MaxSP::get_base,
		"set_base", &Status::MaxSP::set_base
	   );
	st.new_usertype<Status::CurrentHP>("CurrentHP",
		"add", &Status::CurrentHP::add_base,
		"sub", &Status::CurrentHP::sub_base,
		"get", &Status::CurrentHP::get_base,
		"set", &Status::CurrentHP::set_base
		);
	st.new_usertype<Status::CurrentSP>("CurrentSP",
		"add", &Status::CurrentSP::add_base,
		"sub", &Status::CurrentSP::sub_base,
		"get", &Status::CurrentSP::get_base,
		"set", &Status::CurrentSP::set_base
		);
	st.new_usertype<Status::MovementSpeed>("MovementSpeed",
		"add_base", &Status::MovementSpeed::add_base,
		"sub_base", &Status::MovementSpeed::sub_base,
		"get_base", &Status::MovementSpeed::get_base,
		"set_base", &Status::MovementSpeed::set_base
		);
	st.new_usertype<Status::MaxWeight>("MaxWeight",
		"add_base", &Status::MaxWeight::add_base,
		"sub_base", &Status::MaxWeight::sub_base,
		"get_base", &Status::MaxWeight::get_base,
		"set_base", &Status::MaxWeight::set_base
		);
	st.new_usertype<Status::CurrentWeight>("CurrentWeight",
		"add", &Status::CurrentWeight::add_base,
		"sub", &Status::CurrentWeight::sub_base,
		"get", &Status::CurrentWeight::get_base,
		"set", &Status::CurrentWeight::set_base
		);
	st.new_usertype<Status::Strength>("Strength",
		"add_base", &Status::Strength::add_base,
		"sub_base", &Status::Strength::sub_base,
		"get_base", &Status::Strength::get_base,
		"set_base", &Status::Strength::set_base
		);
	st.new_usertype<Status::Agility>("Agility",
		"add_base", &Status::Agility::add_base,
		"sub_base", &Status::Agility::sub_base,
		"get_base", &Status::Agility::get_base,
		"set_base", &Status::Agility::set_base
		);
	st.new_usertype<Status::Vitality>("Vitality",
		"add_base", &Status::Vitality::add_base,
		"sub_base", &Status::Vitality::sub_base,
		"get_base", &Status::Vitality::get_base,
		"set_base", &Status::Vitality::set_base
		);
	st.new_usertype<Status::Intelligence>("Intelligence",
		"add_base", &Status::Intelligence::add_base,
		"sub_base", &Status::Intelligence::sub_base,
		"get_base", &Status::Intelligence::get_base,
		"set_base", &Status::Intelligence::set_base
		);
	st.new_usertype<Status::Dexterity>("Dexterity",
		"add_base", &Status::Dexterity::add_base,
		"sub_base", &Status::Dexterity::sub_base,
		"get_base", &Status::Dexterity::get_base,
		"set_base", &Status::Dexterity::set_base
		);
	st.new_usertype<Status::Luck>("Luck",
		"add_base", &Status::Luck::add_base,
		"sub_base", &Status::Luck::sub_base,
		"get_base", &Status::Luck::get_base,
		"set_base", &Status::Luck::set_base
		);
	st.new_usertype<Status::BaseExperience>("BaseExperience",
		"add", &Status::BaseExperience::add_base,
		"sub", &Status::BaseExperience::sub_base,
		"get", &Status::BaseExperience::get_base,
		"set", &Status::BaseExperience::set_base
		);
	st.new_usertype<Status::JobExperience>("JobExperience",
		"add", &Status::JobExperience::add_base,
		"sub", &Status::JobExperience::sub_base,
		"get", &Status::JobExperience::get_base,
		"set", &Status::JobExperience::set_base
		);
	st.new_usertype<Status::NextBaseExperience>("NextBaseExperience",
		"add", &Status::NextBaseExperience::add_base,
		"sub", &Status::NextBaseExperience::sub_base,
		"get", &Status::NextBaseExperience::get_base,
		"set", &Status::NextBaseExperience::set_base
		);
	st.new_usertype<Status::NextJobExperience>("NextJobExperience",
		"add", &Status::NextJobExperience::add_base,
		"sub", &Status::NextJobExperience::sub_base,
		"get", &Status::NextJobExperience::get_base,
		"set", &Status::NextJobExperience::set_base
		);

	std::vector<std::string> _loadable_files = {
		"scripts/utils/strutils.lua",
		"scripts/definitions/constants.lua"
	};

	for (auto &file : _loadable_files) {
		try {
			res = st.script_file(file);

			if (!res.valid()) {
				sol::error error = res;
				ZoneLog->error("ScriptManager::initialize_state: {}", error.what());
			}
		} catch (sol::error &error) {
			ZoneLog->error("ScriptManager::initialize_state: {}", error.what());
		}
	}

	// Macro to constants
	st["MAX_LEVEL"]            = MAX_LEVEL;
	st["MAX_STATUS_POINTS"]    = MAX_STATUS_POINTS;
	st["MAX_CHARACTER_SLOTS"]  = MAX_CHARACTER_SLOTS;
	st["MAX_VIEW_RANGE"]       = MAX_VIEW_RANGE;
	st["MIN_INVENTORY_SIZE"]   = MIN_INVENTORY_SIZE;
	st["MAX_INVENTORY_SIZE"]   = MAX_INVENTORY_SIZE;
	st["MIN_STORAGE_SIZE"]     = MIN_STORAGE_SIZE;
	st["MAX_STORAGE_SIZE"]     = MAX_STORAGE_SIZE;
	st["MAX_ITEM_STACK_SIZE"]  = MAX_ITEM_STACK_SIZE;
#ifdef RENEWAL
	st["RENEWAL"]              = true;
#else
	st["RENEWAL"]              = false;
#endif
}

void ScriptManager::finalize()
{
	_script_files.clear();
	_npc_db.clear();
}

void ScriptManager::load_scripts()
{
	std::string file_path = "scripts/npcs/include.lua";

	try {
		_lua_state.script_file(file_path);

		sol::table scripts = _lua_state["definitions"];

		scripts.for_each([this, &file_path](sol::object const &/*key*/, sol::object const& value) {
			std::string script_file = value.as<std::string>();
			sol::protected_function fn = _lua_state.load_file(script_file);
			sol::protected_function_result result = fn();
			if (!result.valid()) {
				sol::error error = result;
				ZoneLog->warn("Failed to load file '{}' from '{}', reason: {}", script_file, file_path, error.what());
			}
		});
	} catch (sol::error &e) {
		ZoneLog->warn("Failed to load included script files from '{}', reason: {}", file_path, e.what());
	}
}
void ScriptManager::load_constants()
{
	std::string file_path = "scripts/definitions/constants.lua";

	try {
		_lua_state.script_file(file_path);
		sol::table const_table = _lua_state.get<sol::table>("constants");
		ZoneLog->info("Read constants from '{}' for map container {:p}.", file_path, (void *)_container.lock().get());
	} catch (sol::error &e) {
		ZoneLog->error("Failed to read constants from '{}', reason: {}", file_path, e.what());
	}
}

void ScriptManager::contact_npc_for_player(std::shared_ptr<Player> player, uint32_t npc_guid)
{
	npc_db_data const &nd = _npc_db.at(npc_guid);

	if (nd.script_is_file)
		player->set_npc_contact_guid(npc_guid);

	try {
		sol::state &pl_lua = player->get_lua_state();
		sol::protected_function fx = pl_lua.load_file("scripts/internal/script_command_main.lua");
		sol::protected_function_result result = fx(std::move(player), std::move(nd._npc), nd.script, nd.script_is_file);
		if (!result.valid()) {
			sol::error err = result;
			ZoneLog->error("ScriptManager::contact_npc_for_player: {}", err.what());
		}
	} catch (sol::error &e) {
		ZoneLog->error("{}", e.what());
	}
}

void ScriptManager::continue_npc_script_for_player(std::shared_ptr<Entities::Player> player, uint32_t npc_guid, uint32_t select_idx)
{
	sol::state &pl_lua = player->get_lua_state();
	sol::thread cr_thread = pl_lua["script_exec_routine"];
	sol::state_view cr_state = cr_thread.state();
	sol::coroutine cr = cr_state["script_exec"];

	// Set npc menu selection index (if any, defaulted to 0).
	cr_state["script_commands"]["select_idx"] = select_idx;

	sol::protected_function_result result = cr(cr_state["script_commands"]);
	if (!result.valid()) {
		sol::error err = result;
		ZoneLog->error("ScriptManager::continue_npc_script_for_player: {}", err.what());
	}
}

void ScriptManager::perform_command_from_player(std::shared_ptr<Entities::Player> player, std::string const &cmd)
{
	try {
		sol::state &pl_lua = player->get_lua_state();
		sol::load_result fx = pl_lua.load_file("scripts/internal/at_command_main.lua");
		sol::protected_function_result result = fx(std::move(player), cmd);
		if (!result.valid()) {
			sol::error err = result;
			ZoneLog->error("ScriptManager::perform_command_from_player: {}", err.what());
		}
	} catch (sol::error &e) {
		ZoneLog->error("ScriptManager::perform_command_from_player: {}", e.what());
	}
}
