-- At command functions!

-- @warp/mapmove/rura/movemap <map> <x> <y>
-- @jump
local function mapmove(player, args)
	local map, coords = args[2], MapCoords.new(0, 0)
	local map_obj = nil
	if args[1] ~= "jump" then
		if map == nil then
			player:message("Please specify a map name!")
			return false
		end

		map_obj = get_map_by_name(map)

		if map_obj == nil then
			player:message("Map " .. map .. " does not exist!")
			return false
		end

		if args[3] ~= nil or args[4] ~= nil then
			coords = MapCoords.new(tonumber(args[3]), tonumber(args[4]))
		end
		player:move_to_map(map_obj, coords)
		player:message("Moved to " .. map)
	else
		map_obj = player:map()
		player:move_to_map(map_obj, coords)
		coords = player:map_coords()
		player:message("Jumped to " .. coords:x() .. " " .. coords:y())
	end
	return true
end

local function item(player, args)
	local inventory = player:inventory()
	local item_id, amount = tonumber(args[2]), tonumber(args[3])
	if item_id == nil or amount == nil or item_id <= 0 then
		player:message("Usage: @item <item_id> <amount>")
		return false
	end
	if amount <= 0 then
		player:message("The amount must be greater than 0.")
		return false
	end
	local result = inventory:add_item(item_id, amount, true)
	if result == 1 then
		player:message("Item with Id " .. item_id .. " does not exist.")
	elseif result == 2 then
		player:message("Could not product the item as you are overweight.")
	elseif result == 4 then
		player:message("You do not have enough inventory space.")
	elseif result == 5 then
		player:message("The specified amount is over the allowed quantity.")
	elseif result == 7 then
		player:message("The specified amount is over the allowed stack size.")
	elseif result ~= 0 then
		player:message("An unknown error occured during the item production!")
	end
	return true
end

local function iteminfo(player, args)
	local item_id = tonumber(args[2])
	if item_id <= 0 then
		player:message("Usage: @iteminfo <item_id>")
		return false
	end

	local item = get_item_info(item_id)

	if item == nil then
		player:message("Item with ID " .. item_id .. " was not found.")
		return true
	end

	player:message("Item '" .. item.name .. "'/'" .. item.aegis_name .. "[".. item.card_slot_count .. "] (".. item.item_id ..") Type: ".. item.type)
	player:message("Value Buy: " .. item.value_buy .. " | Value Sell " .. item.value_sell)
	player:message("Weight: " .. tonumber(item.weight / 10))
end

local function change_base_level_cmd(player, args)
	local blvl = player:status():base_level()
	local bexp = player:status():base_experience()
	local nbexp = player:status():next_base_experience()
	local amount = tonumber(args[2])
	if amount == nil or amount == 0 then
		player:message("Usage: @blvl <amount>")
	end
	if amount > 0 then
		for i = 1, amount do
			if (blvl:get() >= MAX_LEVEL) then
				nbexp:set(99999999, true) -- Aegis sets 99.9M value on reaching max level.
				bexp:set(0, true)
				player:message("Max Level " .. MAX_LEVEL .. " reached.")
				break
			end
			bexp:set(nbexp:get(), true)
		end
	else
		amount = math.abs(amount)
		if (blvl:get() - amount <= 1) then
			blvl:set(1, true)
		else
			blvl:set(blvl:get() - amount, true)
		end
		bexp:set(0, true)
	end
end

local function reinitialize_state(player)
	player:reinitialize_state()
	player:message("Script/LUA state has been reloaded.")
end

local at_commands = {
	player = nil,
	cmd = nil,
	player_guid = 0,
	cmd_args = nil,

	-- COMMAND FUNCTIONS --
	cmd_tbl = {
		["reloadstate"] = reinitialize_state,
		["mapmove"] = mapmove,
		["rura"] = mapmove,
		["warp"] = mapmove,
		["jump"] = mapmove,
		["item"] = item,
		["blvl"] = change_base_level_cmd,
		["iteminfo"] = iteminfo
	}
}

function at_commands:new (o)
	o = o or at_commands
	setmetatable(o, self)
	self.__index = self
	return o
end

function at_commands:init(player, cmd)
	self.player = player
	self.player_guid = player:guid()
	self.cmd = cmd
	self.cmd_args = explode(" ", cmd)
end

function at_commands:run()
	if self.cmd_tbl[self.cmd_args[1]] ~= nil then
		self.cmd_tbl[self.cmd_args[1]](self.player, self.cmd_args)
	else
		print("Command " .. self.cmd_args[1] .. " was not found.")
	end
end

return at_commands
