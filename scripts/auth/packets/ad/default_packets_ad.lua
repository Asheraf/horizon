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
	[0x0069] = { ['length'] = -1, ['module'] = require('AC_ACCEPT_LOGIN') },
	[0x026a] = { ['length'] = 4, ['module'] = require('AC_ACK_EKEY_FAIL_AUTHREFUSE') },
	[0x026b] = { ['length'] = 4, ['module'] = require('AC_ACK_EKEY_FAIL_INPUTEKEY') },
	[0x026d] = { ['length'] = 4, ['module'] = require('AC_ACK_EKEY_FAIL_NEEDCARDPASS') },
	[0x0267] = { ['length'] = 4, ['module'] = require('AC_ACK_EKEY_FAIL_NOTEXIST') },
	[0x026c] = { ['length'] = 4, ['module'] = require('AC_ACK_EKEY_FAIL_NOTICE') },
	[0x0269] = { ['length'] = 4, ['module'] = require('AC_ACK_EKEY_FAIL_NOTUSEDEKEY') },
	[0x0268] = { ['length'] = 4, ['module'] = require('AC_ACK_EKEY_FAIL_NOTUSESEKEY') },
	[0x026f] = { ['length'] = 2, ['module'] = require('AC_ACK_FIRST_LOGIN') },
	[0x0259] = { ['length'] = 3, ['module'] = require('AC_ACK_GAME_GUARD') },
	[0x01dc] = { ['length'] = -1, ['module'] = require('AC_ACK_HASH') },
	[0x0272] = { ['length'] = 44, ['module'] = require('AC_ACK_PT_ID_INFO') },
	[0x01be] = { ['length'] = 2, ['module'] = require('AC_ASK_PNGAMEROOM') },
	[0x023d] = { ['length'] = 6, ['module'] = require('AC_EVENT_RESULT') },
	[0x01f1] = { ['length'] = -1, ['module'] = require('AC_NOTIFY_ERROR') },
	[0x006a] = { ['length'] = 23, ['module'] = require('AC_REFUSE_LOGIN') },
	[0x02ad] = { ['length'] = 8, ['module'] = require('AC_REQUEST_SECOND_PASSWORD') },
	[0x0270] = { ['length'] = 2, ['module'] = require('AC_REQ_LOGIN_ACCOUNT_INFO') },
	[0x0263] = { ['length'] = 11, ['module'] = require('AC_REQ_LOGIN_CARDPASS') },
	[0x0262] = { ['length'] = 11, ['module'] = require('AC_REQ_LOGIN_NEWEKEY') },
	[0x0261] = { ['length'] = 11, ['module'] = require('AC_REQ_LOGIN_OLDEKEY') },
	[0x0271] = { ['length'] = 40, ['module'] = require('CA_ACK_LOGIN_ACCOUNT_INFO') },
	[0x0266] = { ['length'] = 30, ['module'] = require('CA_ACK_LOGIN_CARDPASS') },
	[0x0265] = { ['length'] = 20, ['module'] = require('CA_ACK_LOGIN_NEWEKEY') },
	[0x0264] = { ['length'] = 20, ['module'] = require('CA_ACK_LOGIN_OLDEKEY') },
	[0x027f] = { ['length'] = 8, ['module'] = require('CA_CLIENT_TYPE') },
	[0x0200] = { ['length'] = 26, ['module'] = require('CA_CONNECT_INFO_CHANGED') },
	[0x0204] = { ['length'] = 18, ['module'] = require('CA_EXE_HASHCHECK') },
	[0x0064] = { ['length'] = 55, ['module'] = require('CA_LOGIN') },
	[0x01dd] = { ['length'] = 47, ['module'] = require('CA_LOGIN2') },
	[0x01fa] = { ['length'] = 48, ['module'] = require('CA_LOGIN3') },
	[0x027c] = { ['length'] = 60, ['module'] = require('CA_LOGIN4') },
	[0x02b0] = { ['length'] = 85, ['module'] = require('CA_LOGIN_HAN') },
	[0x0277] = { ['length'] = 84, ['module'] = require('CA_LOGIN_PCBANG') },
	[0x01bf] = { ['length'] = 3, ['module'] = require('CA_REPLY_PNGAMEROOM') },
	[0x0258] = { ['length'] = 2, ['module'] = require('CA_REQ_GAME_GUARD_CHECK') },
	[0x01db] = { ['length'] = 2, ['module'] = require('CA_REQ_HASH') },
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
