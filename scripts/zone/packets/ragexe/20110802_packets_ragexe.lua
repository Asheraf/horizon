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

local d = require('default_packets_ragexe')

d:add(0x022d, 6, require('CZ_COMMAND_MER'))
d:add(0x0436, 5, require('CZ_ENTER2'))
d:add(0x07e4, 4, require('CZ_ITEMLISTWIN_RES'))
d:add(0x0362, 2, require('CZ_ITEM_PICKUP2'))
d:add(0x07ec, 6, require('CZ_JOIN_BATTLE_FIELD'))
d:add(0x0802, 8, require('CZ_PARTY_BOOKING_REQ_REGISTER'))
d:add(0x02c4, 5, require('CZ_PARTY_JOIN_REQ'))
d:add(0x0368, 2, require('CZ_REQNAME2'))
d:add(0x0437, 18, require('CZ_REQUEST_ACT2'))
d:add(0x035f, 6, require('CZ_REQUEST_MOVE2'))
d:add(0x0360, 90, require('CZ_REQUEST_TIME2'))
d:add(0x0815, 6, require('CZ_REQ_CLOSE_BUYING_STORE'))
d:add(0x0811, 2, require('CZ_REQ_OPEN_BUYING_STORE'))
d:add(0x0819, 7, require('CZ_REQ_TRADE_BUYING_STORE'))
d:add(0x0835, 26, require('CZ_SEARCH_STORE_INFO'))
d:add(0x0838, 2, require('CZ_SEARCH_STORE_INFO_NEXT_PAGE'))
d:add(0x0438, -1, require('CZ_USE_SKILL2'))
d:add(0x0366, 12, require('CZ_USE_SKILL_TOGROUND2'))
d:add(0x0367, 5, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x08ce, 10, require('ZC_FAILED_GET_ITEM_FROM_ZONEDA'))
d:add(0x09dc, 2, require('ZC_NOTIFY_NEWENTRY10'))
d:add(0x08cd, 10, require('ZC_STOPMOVE_FORCE'))

return d
