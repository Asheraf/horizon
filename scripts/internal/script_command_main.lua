local player, npc, script, is_file = ...

if package.loaded["scripts/modules/script_commands"] ~= nil then
	package.loaded["scripts/modules/script_commands"] = nil
end

script_commands = require('scripts/modules/script_commands')

script_commands:init(player, npc)

if is_file == true then
	main_script = loadfile(script)
else
	main_script = load("local s = ...\n" .. script .. "\nreturn")
end

assert(main_script)

-- Execute script as a co-routine.
script_exec_routine = coroutine.create(main_script)
-- Begin the co-routine.
coroutine.resume(script_exec_routine, script_commands)
