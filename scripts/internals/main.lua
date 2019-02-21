local player, npc, script = ...

if package.loaded['scripts/internals/modules/scriptf'] ~= nil then
	package.loaded['scripts/internals/modules/scriptf'] = nil
end

scriptf = require("scripts/internals/modules/scriptf"):new(nil)

scriptf:init(player, npc)

script_exec_routine = coroutine.create(loadfile(script))
coroutine.resume(script_exec_routine, scriptf)
