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

local d = require('default_packets_re')

d:add(0x088c, 36, require('CZ_ACK_STORE_PASSWORD'))
d:add(0x0960, 26, require('CZ_ADD_FRIENDS'))
d:add(0x0945, 5, require('CZ_CHANGE_DIRECTION'))
d:add(0x088d, 5, require('CZ_COMMAND_MER'))
d:add(0x0860, 19, require('CZ_ENTER'))
d:add(0x0944, 4, require('CZ_GANGSI_RANK'))
d:add(0x0890, -1, require('CZ_ITEMLISTWIN_RES'))
d:add(0x0437, 6, require('CZ_ITEM_PICKUP'))
d:add(0x096a, 6, require('CZ_ITEM_THROW'))
d:add(0x0891, 8, require('CZ_JOIN_BATTLE_FIELD'))
d:add(0x0879, 8, require('CZ_MOVE_ITEM_FROM_BODY_TO_STORE'))
d:add(0x093d, 8, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY'))
d:add(0x086c, 18, require('CZ_PARTY_BOOKING_REQ_REGISTER'))
d:add(0x0917, 26, require('CZ_PARTY_JOIN_REQ'))
d:add(0x087d, 6, require('CZ_REQNAME'))
d:add(0x089c, 6, require('CZ_REQNAME_BYGID'))
d:add(0x0939, 7, require('CZ_REQUEST_ACT'))
d:add(0x087c, 5, require('CZ_REQUEST_MOVE'))
d:add(0x08a0, 6, require('CZ_REQUEST_TIME'))
d:add(0x0367, 6, require('CZ_REQ_CLICK_TO_BUYING_STORE'))
d:add(0x0881, 2, require('CZ_REQ_CLOSE_BUYING_STORE'))
d:add(0x091d, -1, require('CZ_REQ_OPEN_BUYING_STORE'))
d:add(0x089e, -1, require('CZ_REQ_TRADE_BUYING_STORE'))
d:add(0x0967, -1, require('CZ_SEARCH_STORE_INFO'))
d:add(0x08a7, 2, require('CZ_SEARCH_STORE_INFO_NEXT_PAGE'))
d:add(0x0865, 12, require('CZ_SSILIST_ITEM_CLICK'))
d:add(0x0933, 10, require('CZ_USE_SKILL'))
d:add(0x0955, 10, require('CZ_USE_SKILL_TOGROUND'))
d:add(0x08a4, 90, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX'))

return d
