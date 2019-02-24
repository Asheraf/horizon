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

#include "ScriptMgr.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Map/Coordinates.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Unit/NPC/NPC.hpp"

using namespace Horizon::Zone::Game;
using namespace Horizon::Zone::Game::Entities;

ScriptManager::ScriptManager(boost::weak_ptr<MapThreadContainer> container)
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
	st.open_libraries(sol::lib::base);
	st.open_libraries(sol::lib::math);
	st.open_libraries(sol::lib::coroutine);
	st.open_libraries(sol::lib::jit);
	st.open_libraries(sol::lib::table);
	st.open_libraries(sol::lib::package);

	st.create_table(player_tbl_name);


	st.set_function("cast_entity_to_player",
					[] (boost::shared_ptr<Entity> e)
					{
						return boost::dynamic_pointer_cast<Player>(e);
					});

	st.new_usertype<MapCoords>("MapCoords",
							   "x", &MapCoords::x,
							   "y", &MapCoords::y);

	st.new_usertype<NPC>("NPC",
						 "get_guid", &NPC::get_guid,
						 "map_coords", &NPC::get_map_coords,
						 "get_nearby_entity", &NPC::get_nearby_entity);

	st.new_usertype<Player>("Player",
							"get_guid", &Player::get_guid,
							"map_coords", &Player::get_map_coords,
							"get_nearby_entity", &Player::get_nearby_entity,
							"send_npc_dialog", &Player::send_npc_dialog,
							"send_npc_next_dialog", &Player::send_npc_next_dialog,
							"send_npc_close_dialog", &Player::send_npc_close_dialog,
							"send_npc_menu_list", &Player::send_npc_menu_list
							);
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
		
		ZoneLog->info("Found {} loadable script(s) from file '{}'.", (int) _script_files.size(), file_path);

		load_scripts_internal();
	} catch (sol::error &e) {
		ZoneLog->error("ScriptManager::load_scripts: {}", e.what());
	}
}

int ScriptManager::load_npcs_from_script(std::string &file_path, std::string const &table_name, sol::table const &info_tables)
{
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

			std::shared_ptr<Horizon::Zone::Game::Entities::NPC> npc = std::make_shared<Horizon::Zone::Game::Entities::NPC>(script_count, nd);
			npc->set_map(map);
			npc->initialize();
			nd._npc = npc;
			_npc_db.emplace(npc->get_guid(), nd);
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
			ZoneLog->info("Done reading {} script entries from '{}'.", script_count, file_path);
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
		ZoneLog->info("Loaded {} constants tables '{}' for map container.", const_table.size(), file_path);
	} catch (sol::error &e) {
		ZoneLog->error("ScriptManager::load_constants: {}", e.what());
	}
}

void ScriptManager::contact_npc_for_player(boost::shared_ptr<Player> player, uint32_t npc_guid)
{
	npc_db_data const &nd = _npc_db.at(npc_guid);

	player->set_npc_contact_guid(npc_guid);

	try {
		sol::state &pl_lua = player->get_lua_state();

		initialize_state(pl_lua);

		sol::load_result fx = pl_lua.load_file("scripts/internals/main.lua");
		fx(std::move(player), std::move(nd._npc), nd.script_file_path);
	} catch (sol::error &e) {
		ZoneLog->error("{}", e.what());
	}
}

void ScriptManager::continue_npc_script_for_player(boost::shared_ptr<Entities::Player> player, uint32_t npc_guid, uint32_t select_idx)
{
	npc_db_data const &nd = _npc_db.at(npc_guid);

	sol::state &pl_lua = player->get_lua_state();
	sol::thread cr_thread = pl_lua["script_exec_routine"];
	sol::state_view cr_state = cr_thread.state();
	sol::coroutine cr = cr_state["script_exec"];
	cr_state["scriptf"]["select_idx"] = select_idx;
	cr(cr_state["scriptf"]);
}

/**
 * @brief Prepares player handling for the player table in an lua state
 * This function is not thread safe, called from a map thread container.
 * @param[in] lua Lua State
 * @param[in] player Shared pointer to a player entity.
 */
void ScriptManager::add_player(boost::shared_ptr<Player> player)
{
	sol::table player_table = _lua_state.get<sol::table>(player_tbl_name);

	player_table.set(player->get_guid(), std::move(player));
}

/**
 * @brief Removes player object from the player table in an lua state
 * This function is not thread safe.
 * @param[in] lua Lua State
 * @param[in] player Shared pointer to a player entity.
 */
void ScriptManager::remove_player(boost::shared_ptr<Player> player)
{
	sol::table player_table = _lua_state.get<sol::table>(player_tbl_name);
	player_table.set(player->get_guid(), "nil");
	_lua_state.script(R"(collectgarbage())");
}
