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

	st.set_function("get_map_by_name",
					[] (std::string name)
					{
						return MapMgr->get_map(name);
					});

	st.new_usertype<item_entry_data>("item_entry_data",
									sol::constructors<item_entry_data()>(),
									"is_equipment", &item_entry_data::is_equipment,
									"is_stackable", &item_entry_data::is_stackable
									 );

	st.new_usertype<Map>("Map",
									"get_name", &Map::get_name,
									"get_width", &Map::get_width,
									"get_height", &Map::get_height,
									"has_obstruction_at", &Map::has_obstruction_at
									);

	st.new_usertype<MapCoords>("MapCoords",
									sol::constructors<MapCoords(uint16_t, uint16_t)>(),
									"x", &MapCoords::x,
									"y", &MapCoords::y
									);

	st.new_usertype<NPC>("NPC",
									sol::constructors<NPC(std::string const &, std::shared_ptr<Map>, MapCoords const &, uint32_t, directions)>(),
									"get_guid", &NPC::get_guid,
									"map_coords", &NPC::get_map_coords,
									"get_nearby_entity", &NPC::get_nearby_entity
						 			);

	st.new_usertype<Assets::Inventory>("Inventory",
									"get_item_by_id", &Assets::Inventory::get_item_by_id,
									"get_item_at_index", &Assets::Inventory::get_item_at_index,
									"add_item", &Assets::Inventory::add_item);

	st.new_usertype<Player>("Player",
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
		"scripts/internals/utils/strutils.lua",
		"scripts/constants.lua"
	};

	for (auto &file : _loadable_files) {
		res = st.script_file(file);

		if (!res.valid()) {
			sol::error error = res;
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
	std::string file_path = "scripts/scripts.lua";

	_lua_state.script_file(file_path);

	try {
		sol::table scripts = _lua_state["scripts"];

		scripts.for_each([this](sol::object const &/*key*/, sol::object const& value) {
			_script_files.push_back(value.as<std::string>());
		});

		ZoneLog->info("Found {} loadable script(s) from file '{}' for map container {:p}.", (int) _script_files.size(), file_path, (void *)_container.lock().get());

		load_scripts_internal();
	} catch (sol::error &e) {
		ZoneLog->error("ScriptManager::load_scripts: {}", e.what());
	}
}

int ScriptManager::load_npcs_from_script(std::string &file_path, std::string const &table_name, sol::table const &info_tables)
{
	using namespace Horizon::Zone::Game::Entities;

	int script_count = 0;

	info_tables.for_each([this, &file_path, &script_count, &table_name](sol::object const &key, sol::object const &value) {
		try {
			npc_db_data nd;
			sol::table npc_info_table = value.as<sol::table>();

			if (npc_info_table[1].get_type() != sol::type::string) {
				ZoneLog->error("Invalid map name for NPC entry {}@{} in file '{}'.", table_name, script_count, file_path);
				return;
			}

			nd.map_name = npc_info_table[1].get<std::string>();

			std::shared_ptr<Map> map = nullptr;
			if ((map = get_map_container()->get_map(nd.map_name)) == nullptr) {
				// Ignore npcs from maps not contained in this thread.
				return;
			}

			if (npc_info_table[2].get_type() != sol::type::number) {
				ZoneLog->error("Invalid 'x' coordinate for NPC entry {}@{} in file '{}'.", table_name, script_count, file_path);
				return;
			}

			nd.x = npc_info_table[2].get<uint16_t>();

			if (npc_info_table[3].get_type() != sol::type::number) {
				ZoneLog->error("Invalid 'y' coordinate for NPC entry {}@{} in file '{}'.", table_name, script_count, file_path);
				return;
			}

			nd.y = npc_info_table[3].get<uint16_t>();

			if (npc_info_table[4].get_type() != sol::type::number) {
				ZoneLog->error("Invalid direction for NPC entry {}@{} in file '{}'.", table_name, script_count, file_path);
				return;
			}

			nd.direction = (directions) npc_info_table[4].get<uint8_t>();

			if (npc_info_table[5].get_type() != sol::type::string) {
				ZoneLog->error("Invalid 'Name' for NPC entry {}@{} in file '{}'.", table_name, script_count, file_path);
				return;
			}

			nd.npc_name = npc_info_table[5].get<std::string>();

			if (npc_info_table[6].get_type() != sol::type::number) {
				ZoneLog->error("Invalid 'Sprite ID' for NPC entry {}@{} in file '{}'.", table_name, script_count, file_path);
				return;
			}

			nd.sprite_id = npc_info_table[6].get<int>();

			if (npc_info_table[7].get_type() != sol::type::none) {
				nd.npc_key = key.as<std::string>();

				sol::type script_file_path_type = npc_info_table[7].get_type();
				if (script_file_path_type != sol::type::none && script_file_path_type != sol::type::string) {
					ZoneLog->error("Invalid 'Script File Path' for NPC entry {}@{} in file '{}'.", table_name, script_count, file_path);
					return;
				}

				nd.script_file_path = npc_info_table[7].get<std::string>();
			} else {
				ZoneLog->error("Invalid 'Script File Path' for NPC entry {}@{} in file '{}'.", table_name, script_count, file_path);
				return;
			}

			nd._npc = std::make_shared<NPC>(nd.npc_name, map, MapCoords(nd.x, nd.y), nd.sprite_id, nd.direction);
			nd._npc->initialize();
			_npc_db.emplace(nd._npc->get_guid(), nd);
			script_count++;
		} catch (sol::error &e) {
			ZoneLog->error("ScriptManager::load_npcs_from_script: Error in file {} table {}[{}]\nlua error: {}", file_path, table_name, script_count, e.what());
		}
	});

	return script_count;
}

void ScriptManager::load_scripts_internal()
{
	for (auto i = _script_files.begin(); i != _script_files.end(); i++) {
		try {
			int script_count = 0;
			std::string file_path = *i;
			_lua_state.script_file(file_path);

			sol::table npc_table = _lua_state["NPC"];

			npc_table.for_each([this, &file_path, &script_count](sol::object const &key, sol::object const& value) {
				if (key.get_type() != sol::type::string) {
					ZoneLog->error("Expected string key for NPC table in file '{}', ignoring...", file_path);
					return;
				}

				std::string table_name = key.as<std::string>();

				if (value.get_type() != sol::type::table) {
					ZoneLog->error("Found unexpected type  for entry {}@{} in file '{}', .", table_name, script_count, file_path);
					return;
				}

				sol::table info_tables = value.as<sol::table>();

				script_count = load_npcs_from_script(file_path, table_name, info_tables);
			});
			ZoneLog->info("Read {} script entries from '{}' for map container {:p}.", script_count, file_path, (void *)_container.lock().get());
		} catch (sol::error &e) {
			ZoneLog->error("ScriptManager::load_scripts_internal: {}", e.what());
		}
	}
}

void ScriptManager::load_constants()
{
	std::string file_path = "scripts/constants.lua";

	try {
		_lua_state.script_file(file_path);
		sol::table const_table = _lua_state.get<sol::table>("constants");
		ZoneLog->info("Read constants from '{}' for map container {:p}.", file_path, (void *)_container.lock().get());
	} catch (sol::error &e) {
		ZoneLog->error("ScriptManager::load_constants: {}", e.what());
	}
}

void ScriptManager::contact_npc_for_player(std::shared_ptr<Player> player, uint32_t npc_guid)
{
	npc_db_data const &nd = _npc_db.at(npc_guid);

	player->set_npc_contact_guid(npc_guid);

	try {
		sol::state &pl_lua = player->get_lua_state();
		sol::load_result fx = pl_lua.load_file("scripts/internals/main.lua");
		sol::protected_function_result result = fx(std::move(player), std::move(nd._npc), nd.script_file_path);
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
	cr_state["scriptf"]["select_idx"] = select_idx;

	sol::protected_function_result result = cr(cr_state["scriptf"]);
	if (!result.valid()) {
		sol::error err = result;
		ZoneLog->error("ScriptManager::continue_npc_script_for_player: {}", err.what());
	}
}

void ScriptManager::perform_command_from_player(std::shared_ptr<Entities::Player> player, std::string cmd)
{
	try {
		sol::state &pl_lua = player->get_lua_state();
		sol::load_result fx = pl_lua.load_file("scripts/commands/commands.lua");
		sol::protected_function_result result = fx(std::move(player), cmd);
		if (!result.valid()) {
			sol::error err = result;
			ZoneLog->error("ScriptManager::perform_command_from_player: {}", err.what());
		}
	} catch (sol::error &e) {
		ZoneLog->error("ScriptManager::perform_command_from_player: {}", e.what());
	}
}
