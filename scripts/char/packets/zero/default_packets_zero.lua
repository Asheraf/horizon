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
	[0x08fd] = { ['length'] = 6, ['module'] = require('CH_ACK_CHANGE_CHARACTERNAME') },
	[0x08c5] = { ['length'] = 6, ['module'] = require('CH_AVAILABLE_SECOND_PASSWD') },
	[0x09a1] = { ['length'] = 2, ['module'] = require('CH_CHARLIST_REQ') },
	[0x07e7] = { ['length'] = 32, ['module'] = require('CH_CHECKBOT') },
	[0x0068] = { ['length'] = 46, ['module'] = require('CH_DELETE_CHAR') },
	[0x01fb] = { ['length'] = 56, ['module'] = require('CH_DELETE_CHAR2') },
	[0x0829] = { ['length'] = 12, ['module'] = require('CH_DELETE_CHAR3') },
	[0x082b] = { ['length'] = 6, ['module'] = require('CH_DELETE_CHAR3_CANCEL') },
	[0x098f] = { ['length'] = -1, ['module'] = require('CH_DELETE_CHAR3_EXT') },
	[0x0827] = { ['length'] = 6, ['module'] = require('CH_DELETE_CHAR3_RESERVED') },
	[0x08bc] = { ['length'] = 10, ['module'] = require('CH_DELETE_SECOND_PASSWD') },
	[0x08be] = { ['length'] = 14, ['module'] = require('CH_EDIT_SECOND_PASSWD') },
	[0x0065] = { ['length'] = 17, ['module'] = require('CH_ENTER') },
	[0x0275] = { ['length'] = 37, ['module'] = require('CH_ENTER2') },
	[0x07e5] = { ['length'] = 4, ['module'] = require('CH_ENTER_CHECKBOT') },
	[0x0a39] = { ['length'] = 36, ['module'] = require('CH_MAKE_CHAR') },
	[0x0970] = { ['length'] = 31, ['module'] = require('CH_MAKE_CHAR_NOT_STATS') },
	[0x08ba] = { ['length'] = 10, ['module'] = require('CH_MAKE_SECOND_PASSWD') },
	[0x08c3] = { ['length'] = 10, ['module'] = require('CH_NOT_AVAILABLE_SECOND_PASSWD') },
	[0x08fc] = { ['length'] = 30, ['module'] = require('CH_REQ_CHANGE_CHARACTERNAME') },
	[0x08d4] = { ['length'] = 8, ['module'] = require('CH_REQ_CHANGE_CHARACTER_SLOT') },
	[0x028f] = { ['length'] = 6, ['module'] = require('CH_REQ_CHANGE_CHARNAME') },
	[0x099c] = { ['length'] = 6, ['module'] = require('CH_REQ_CHARINFO_PER_PAGE') },
	[0x028d] = { ['length'] = 34, ['module'] = require('CH_REQ_IS_VALID_CHARNAME') },
	[0x08b8] = { ['length'] = 10, ['module'] = require('CH_SECOND_PASSWD_ACK') },
	[0x0841] = { ['length'] = 4, ['module'] = require('CH_SELECT_ACCESSIBLE_MAPNAME') },
	[0x0066] = { ['length'] = 3, ['module'] = require('CH_SELECT_CHAR') },
	[0x028c] = { ['length'] = 46, ['module'] = require('CH_SELECT_CHAR_GOINGTOBEUSED') },
	[0x0187] = { ['length'] = 6, ['module'] = require('CH_UNKNOWN_PING') },
	[0x08b0] = { ['length'] = 17, ['module'] = require('CH_WAITING_LOGIN') },
	[0x006f] = { ['length'] = 2, ['module'] = require('HC_ACCEPT_DELETECHAR') },
	[0x006b] = { ['length'] = -1, ['module'] = require('HC_ACCEPT_ENTER') },
	[0x082d] = { ['length'] = -1, ['module'] = require('HC_ACCEPT_ENTER2') },
	[0x006d] = { ['length'] = 157, ['module'] = require('HC_ACCEPT_MAKECHAR') },
	[0x08d5] = { ['length'] = -1, ['module'] = require('HC_ACK_CHANGE_CHARACTER_SLOT') },
	[0x0290] = { ['length'] = 4, ['module'] = require('HC_ACK_CHANGE_CHARNAME') },
	[0x099d] = { ['length'] = -1, ['module'] = require('HC_ACK_CHARINFO_PER_PAGE') },
	[0x028e] = { ['length'] = 4, ['module'] = require('HC_ACK_IS_VALID_CHARNAME') },
	[0x08c6] = { ['length'] = 4, ['module'] = require('HC_AVAILABLE_SECOND_PASSWD') },
	[0x020d] = { ['length'] = -1, ['module'] = require('HC_BLOCK_CHARACTER') },
	[0x0448] = { ['length'] = -1, ['module'] = require('HC_CHARACTER_LIST') },
	[0x09a0] = { ['length'] = 6, ['module'] = require('HC_CHARLIST_NOTIFY') },
	[0x028b] = { ['length'] = -1, ['module'] = require('HC_CHARNOTBEENSELECTED') },
	[0x07e8] = { ['length'] = -1, ['module'] = require('HC_CHECKBOT') },
	[0x07e9] = { ['length'] = 5, ['module'] = require('HC_CHECKBOT_RESULT') },
	[0x082a] = { ['length'] = 10, ['module'] = require('HC_DELETE_CHAR3') },
	[0x082c] = { ['length'] = 10, ['module'] = require('HC_DELETE_CHAR3_CANCEL') },
	[0x0828] = { ['length'] = 14, ['module'] = require('HC_DELETE_CHAR3_RESERVED') },
	[0x08bd] = { ['length'] = 8, ['module'] = require('HC_DELETE_SECOND_PASSWD') },
	[0x08bf] = { ['length'] = 8, ['module'] = require('HC_EDIT_SECOND_PASSWD') },
	[0x08bb] = { ['length'] = 8, ['module'] = require('HC_MAKE_SECOND_PASSWD') },
	[0x0840] = { ['length'] = -1, ['module'] = require('HC_NOTIFY_ACCESSIBLE_MAPNAME') },
	[0x0ac5] = { ['length'] = 156, ['module'] = require('HC_NOTIFY_ZONESVR') },
	[0x08c4] = { ['length'] = 8, ['module'] = require('HC_NOT_AVAILABLE_SECOND_PASSWD') },
	[0x099e] = { ['length'] = 12, ['module'] = require('HC_QUEUE_ORDER') },
	[0x0070] = { ['length'] = 3, ['module'] = require('HC_REFUSE_DELETECHAR') },
	[0x006c] = { ['length'] = 3, ['module'] = require('HC_REFUSE_ENTER') },
	[0x006e] = { ['length'] = 3, ['module'] = require('HC_REFUSE_MAKECHAR') },
	[0x02ca] = { ['length'] = 3, ['module'] = require('HC_REFUSE_SELECTCHAR') },
	[0x023e] = { ['length'] = 8, ['module'] = require('HC_REQUEST_CHARACTER_PASSWORD') },
	[0x08b9] = { ['length'] = 12, ['module'] = require('HC_SECOND_PASSWD_LOGIN') },
	[0x09c2] = { ['length'] = -1, ['module'] = require('HC_SECRETSCAN_DATA') },
	[0x08e3] = { ['length'] = 157, ['module'] = require('HC_UPDATE_CHARINFO') },
	[0x08af] = { ['length'] = 10, ['module'] = require('HC_WAITING_LOGIN') },
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
