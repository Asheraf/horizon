
#ifndef HORIZON_ZONE_GAME_SCRIPTMGR
#define HORIZON_ZONE_GAME_SCRIPTMGR

#include <Server/Zone/Game/Definitions/NPCDefinitions.hpp>
#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
	class NPC;
}
class ScriptManager
{
public:
	ScriptManager() { }
	~ScriptManager();

	static ScriptManager *get_instance()
	{
		static ScriptManager script_mgr;
		return &script_mgr;
	}

	void initialize();
	void load_scripts();
	void load_constants();

private:
	void load_scripts_internal();
	template <typename KeyT, typename ValT>
	void load_constants_internal(sol::table const &, std::string &&);

	std::unordered_map<std::string, std::string> _scripts;
	std::unordered_map<std::string, std::unordered_map<std::string, int>> _constants;
	std::unordered_map<uint32_t, std::shared_ptr<Entities::NPC>> _npc_db;
	sol::state _lua_state;
};
}
}
}

#define ScriptMgr ScriptManager::get_instance()

#endif /* HORIZON_ZONE_GAME_SCRIPTMGR */
