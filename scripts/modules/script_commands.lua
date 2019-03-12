local script_commands = {
	npc = nil,
	player = nil,
	player_guid = 0,
	npc_guid = 0,
	select_idx = 0
}

function script_commands:new (o)
	o = o or script_commands
	setmetatable(o, self)
	self.__index = self
	return o
end

function script_commands:init(player, npc)
	self.player = player
	self.player_guid = player:get_guid()
	self.npc = npc
	self.npc_guid = npc:get_guid()
end

function script_commands:mes(m)
	self.player:send_npc_dialog(self.npc_guid, m)
end

function script_commands:next()
	self.player:send_npc_next_dialog(self.npc_guid)
	coroutine.yield()
end

function script_commands:select(...)
	local menu = ""
	for i, v in pairs({...}) do
		menu = menu .. v .. ":"
	end
	self.player:send_npc_menu_list(self.npc_guid, menu)
	coroutine.yield()
	return self.select_idx
end

function script_commands:item_count(item_id)
	if item_id == nil or type(item_id) ~= "number" or item_id <= 0 then
		error("script_commands:item_count: item_id must be non-negative non-zero number.")
	end
	local items = self.player:get_inventory():get_all_items()
	for k=1, #items do
		local v = items[k]
		if v.item_id == item_id then
			return v.amount
		end
	end
	return 0
end

function script_commands:item_add(item_id, amount)
	return self.player:get_inventory():add_item(item_id, amount)
end

function script_commands:move_to_map(map_name, x, y)
	local coords = MapCoords.new(0, 0)
	if map_name == nil or type(map_name) ~= "string" or type(x) ~= "number" or type(y) ~= "number" or x < 0 or y < 0 then
		print("script_commands:move_to_map: Must provide map name and ensure x and y are not negative.", 2)
		return false
	end

	local map_obj = get_map_by_name(map_name)

	if map_obj == nil then
		print("script_commands:move_to_map: Map " .. map_name .. " does not exist!", 2)
		return false
	end

	if x > 0 and y > 0 then
		coords = MapCoords.new(x, y)
	end

	self.player:move_to_map(map_obj, coords)
	return true
end

function script_commands:close()
	self.player:send_npc_close_dialog(self.npc_guid)
end

return script_commands
