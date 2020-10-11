-----------------------------------------------------
--       _   _            _                        --
--      | | | |          (_)                       --
--      | |_| | ___  _ __ _ _______  _ __          --
--      |  _  |/ _ \| '__| |_  / _ \| '_  \        --
--      | | | | (_) | |  | |/ / (_) | | | |        --
--      \_| |_/\___/|_|  |_/___\___/|_| |_|        --
-----------------------------------------------------
-- This file is part of Horizon (c).
-- Copyright (c) 2019 Horizon Dev Team.
--
-- Base Author - Sagun Khosla. (sagunxp@gmail.com)
--
-- This library is free software; you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This library is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this library.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------

local default_packets = {
	[0x03dd] = { ['length'] = 18, ['module'] = require('AHC_GAME_GUARD') },
	[0x03de] = { ['length'] = 18, ['module'] = require('CAH_ACK_GAME_GUARD') },
	[0x01c6] = { ['length'] = 4, ['module'] = require('CS_REQ_ENCRYPTION') },
	[0x01c7] = { ['length'] = 2, ['module'] = require('SC_ACK_ENCRYPTION') },
	[0x01b5] = { ['length'] = 18, ['module'] = require('SC_BILLING_INFO') },
	[0x0081] = { ['length'] = 3, ['module'] = require('SC_NOTIFY_BAN') },
}

function default_packets:new(o)
	o = o or default_packets
	setmetatable(o, self)
	self.__index = self
	return o
end

function default_packets:add(id, len, module)
	self[id] = { ["length"] = len, ["module"] = module }
end

return default_packets
