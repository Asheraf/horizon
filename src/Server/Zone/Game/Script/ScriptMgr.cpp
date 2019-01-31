
#include "ScriptMgr.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Entities/Unit/NPC/NPC.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"

using namespace Horizon::Zone::Game;

ScriptManager::~ScriptManager()
{

}

void ScriptManager::initialize()
{
	_lua_state.open_libraries(sol::lib::base);
	_lua_state.open_libraries(sol::lib::math);
	_lua_state.open_libraries(sol::lib::coroutine);

	load_constants();
	load_scripts();
}

void ScriptManager::load_scripts()
{
	std::string file_name = "scripts/scripts.lua";

	_lua_state.script_file(file_name);

	try {
		sol::table scripts = _lua_state["scripts"];

		scripts.for_each([this](sol::object const &key, sol::object const& value) {
			_scripts.emplace(key.as<std::string>(), value.as<std::string>());
		});
		
		ZoneLog->info("Found {} loadable script(s) from file '{}'.", _scripts.size(), file_name);

		load_scripts_internal();
	} catch (sol::error &e) {
		ZoneLog->error("ScriptManager::load_scripts: {}", e.what());
	}
}

void ScriptManager::load_scripts_internal()
{
	for (auto i = _scripts.begin(); i != _scripts.end(); i++) {
		try {
			std::string file_name = i->second;
			std::string table_name = i->first;
			_lua_state.script_file(file_name);

			sol::table npc_table = _lua_state[table_name];

			int script_count = 0;

			npc_table.for_each([this, &file_name, &table_name, &script_count](sol::object const &key, sol::object const& value) {
				npc_data nd;

				if (value.get_type() != sol::type::table) {
					ZoneLog->error("Expected table of NPC information for entry {}@{} in file '{}'.", table_name, script_count, file_name);
					return;
				}

				try {
					sol::table npc_info_table = value.as<sol::table>();

					if (npc_info_table[1].get_type() != sol::type::string) {
						ZoneLog->error("Invalid map name for NPC entry {}@{} in file '{}'.", table_name, script_count, file_name);
						return;
					}

					nd.map_name = npc_info_table[1].get<std::string>();

					std::shared_ptr<Map> map = nullptr;
					if ((map = MapMgr->get_map(nd.map_name)) == nullptr) {
						ZoneLog->error("Invalid map name for NPC entry {}@{} '{}' in file '{}'.", table_name, script_count, file_name);
						return;
					}

					if (npc_info_table[2].get_type() != sol::type::number) {
						ZoneLog->error("Invalid 'x' coordinate for NPC entry {}@{} in file '{}'.", table_name, script_count, file_name);
						return;
					}

					nd.x = npc_info_table[2].get<uint16_t>();

					if (npc_info_table[3].get_type() != sol::type::number) {
						ZoneLog->error("Invalid 'y' coordinate for NPC entry {}@{} in file '{}'.", table_name, script_count, file_name);
						return;
					}

					nd.y = npc_info_table[3].get<uint16_t>();

					if (npc_info_table[4].get_type() != sol::type::number) {
						ZoneLog->error("Invalid direction for NPC entry {}@{} in file '{}'.", table_name, script_count, file_name);
						return;
					}

					nd.direction = npc_info_table[4].get<uint8_t>();

					if (npc_info_table[5].get_type() != sol::type::string) {
						ZoneLog->error("Invalid 'Name' for NPC entry {}@{} in file '{}'.", table_name, script_count, file_name);
						return;
					}

					nd.npc_name = npc_info_table[5].get<std::string>();

					if (npc_info_table[6].get_type() != sol::type::number) {
						ZoneLog->error("Invalid 'Sprite ID' for NPC entry {}@{} in file '{}'.", table_name, script_count, file_name);
						return;
					}

					nd.sprite_id = npc_info_table[6].get<int>();

					if (key.get_type() == sol::type::string) {
						nd.npc_key = key.as<std::string>();
					} else if (npc_info_table[7].get_type() != sol::type::none) {
						nd.parent = npc_info_table[7].get<std::string>();
					} else {
						ZoneLog->error("NPC entry {}@{} without a key has no parent to derive its functionality from, in file '{}'.", table_name, script_count, file_name);
						return;
					}

					std::shared_ptr<NPC> npc = std::make_shared<NPC>(script_count, nd);
					npc->set_map(map);

					npc->initialize();

					_npc_db.emplace(nd.npc_name, npc);

					script_count++;
				} catch (sol::error &e) {
					ZoneLog->error("ScriptManager::load_scripts_internal: {}", e.what());
				}
			});
			ZoneLog->info("Done reading {} script entries from '{}'.", script_count, i->second);
		} catch (sol::error &e) {
			ZoneLog->error("ScriptManager::load_scripts_internal: {}", e.what());
		}
	}
}

void ScriptManager::load_constants()
{
	std::string file_name = "scripts/constants.lua";

	try {
		_lua_state.script_file(file_name);

		sol::table const_table = _lua_state["constants"];

		const_table.for_each([this, &const_table](sol::object const &key, sol::object const &/*value*/) {
			load_constants_internal<std::string, int>(const_table, key.as<std::string>());
		});

		// Add constants to lua state.
		for (auto i = _constants.begin(); i != _constants.end(); i++) {
			_lua_state[i->first] = _lua_state.create_table();
			for (auto j = i->second.begin(); j != i->second.end(); j++) {
				_lua_state[i->first][j->first] = j->second;
			}

			ZoneLog->info("Loaded {} script constants in table '{}' from file '{}'.", i->second.size(), i->first, file_name);
		}
	} catch (sol::error &e) {
		ZoneLog->error("ScriptManager::load_constants: {}", e.what());
	}
}

template <typename KeyT, typename ValT>
void ScriptManager::load_constants_internal(sol::table const &const_table, std::string &&list_name)
{
	sol::table lua_list = const_table[list_name];
	std::unordered_map<KeyT, ValT> list_map;

	lua_list.for_each([&](sol::object const &key, sol::object const &value) {
		list_map.emplace(key.as<KeyT>(), value.as<ValT>());
	});

	_constants.emplace(list_name, list_map);
}
