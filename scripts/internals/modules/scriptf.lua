local scriptf = {
	npc = nil,
	player = nil,
	player_guid = 0,
	npc_guid = 0,
	select_idx = 0
}

function scriptf:new (o)
	o = o or scriptf
	setmetatable(o, self)
	self.__index = self
	return o
end

function scriptf:init(player, npc)
	self.player = player
	self.player_guid = player:get_guid()
	self.npc = npc
	self.npc_guid = npc:get_guid()
end

function scriptf:mes(m)
	self.player:send_npc_dialog(self.npc_guid, m)
end

function scriptf:next()
	self.player:send_npc_next_dialog(self.npc_guid)
	coroutine.yield()
end

function scriptf:select(...)
	local menu = ""
	for i, v in pairs({...}) do
		menu = menu .. v .. ":"
	end
	self.player:send_npc_menu_list(self.npc_guid, menu)
	coroutine.yield()
	return self.select_idx
end

function scriptf:close()
	self.player:send_npc_close_dialog(self.npc_guid)
end

return scriptf
