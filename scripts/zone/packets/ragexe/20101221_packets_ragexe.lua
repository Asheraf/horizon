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

d:add(0x023b, 2, require('CZ_ACK_STORE_PASSWORD'))
d:add(0x0202, 18, require('CZ_ADD_FRIENDS'))
d:add(0x0361, 2, require('CZ_CHANGE_DIRECTION2'))
d:add(0x0436, 12, require('CZ_ENTER2'))
d:add(0x0281, 26, require('CZ_GANGSI_RANK'))
d:add(0x07e4, 2, require('CZ_ITEMLISTWIN_RES'))
d:add(0x0362, 2, require('CZ_ITEM_PICKUP2'))
d:add(0x0363, 19, require('CZ_ITEM_THROW2'))
d:add(0x0802, 26, require('CZ_PARTY_BOOKING_REQ_REGISTER'))
d:add(0x0368, 10, require('CZ_REQNAME2'))
d:add(0x0437, 8, require('CZ_REQUEST_ACT2'))
d:add(0x035f, 2, require('CZ_REQUEST_MOVE2'))
d:add(0x0817, 7, require('CZ_REQ_CLICK_TO_BUYING_STORE'))
d:add(0x0815, 2, require('CZ_REQ_CLOSE_BUYING_STORE'))
d:add(0x0811, -1, require('CZ_REQ_OPEN_BUYING_STORE'))
d:add(0x0366, 2, require('CZ_USE_SKILL_TOGROUND2'))
d:add(0x0367, -1, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x08b1, -1, require('ZC_MCSTORE_NOTMOVEITEM_LIST'))

return d
