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
	[0x0068] = { ['length'] = 46, ['module'] = require('CH_DELETE_CHAR') },
	[0x01fb] = { ['length'] = 56, ['module'] = require('CH_DELETE_CHAR2') },
	[0x0065] = { ['length'] = 17, ['module'] = require('CH_ENTER') },
	[0x0067] = { ['length'] = 37, ['module'] = require('CH_MAKE_CHAR') },
	[0x028f] = { ['length'] = 6, ['module'] = require('CH_REQ_CHANGE_CHARNAME') },
	[0x028d] = { ['length'] = 34, ['module'] = require('CH_REQ_IS_VALID_CHARNAME') },
	[0x0066] = { ['length'] = 3, ['module'] = require('CH_SELECT_CHAR') },
	[0x028c] = { ['length'] = 46, ['module'] = require('CH_SELECT_CHAR_GOINGTOBEUSED') },
	[0x0187] = { ['length'] = 6, ['module'] = require('CH_UNKNOWN_PING') },
	[0x006f] = { ['length'] = 2, ['module'] = require('HC_ACCEPT_DELETECHAR') },
	[0x006b] = { ['length'] = -1, ['module'] = require('HC_ACCEPT_ENTER') },
	[0x006d] = { ['length'] = 110, ['module'] = require('HC_ACCEPT_MAKECHAR') },
	[0x0290] = { ['length'] = 4, ['module'] = require('HC_ACK_CHANGE_CHARNAME') },
	[0x028e] = { ['length'] = 4, ['module'] = require('HC_ACK_IS_VALID_CHARNAME') },
	[0x020d] = { ['length'] = -1, ['module'] = require('HC_BLOCK_CHARACTER') },
	[0x028b] = { ['length'] = -1, ['module'] = require('HC_CHARNOTBEENSELECTED') },
	[0x0071] = { ['length'] = 28, ['module'] = require('HC_NOTIFY_ZONESVR') },
	[0x0070] = { ['length'] = 3, ['module'] = require('HC_REFUSE_DELETECHAR') },
	[0x006c] = { ['length'] = 3, ['module'] = require('HC_REFUSE_ENTER') },
	[0x006e] = { ['length'] = 3, ['module'] = require('HC_REFUSE_MAKECHAR') },
	[0x02ca] = { ['length'] = 3, ['module'] = require('HC_REFUSE_SELECTCHAR') },
	[0x023e] = { ['length'] = 8, ['module'] = require('HC_REQUEST_CHARACTER_PASSWORD') },
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
