local player, cmd = ...

if package.loaded["scripts/modules/at_commands"] then
	package.loaded["scripts/modules/at_commands"] = nil
end

at_commands = require("scripts/modules/at_commands")

assert(at_commands)

at_commands:init(player, cmd)

at_commands:run()
