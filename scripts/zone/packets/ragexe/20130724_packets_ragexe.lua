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

d:add(0x0860, 36, require('CZ_ACK_STORE_PASSWORD'))
d:add(0x092b, 26, require('CZ_ADD_FRIENDS'))
d:add(0x0966, 5, require('CZ_CHANGE_DIRECTION'))
d:add(0x0874, 5, require('CZ_COMMAND_MER'))
d:add(0x0893, 19, require('CZ_ENTER'))
d:add(0x08ab, 4, require('CZ_GANGSI_RANK'))
d:add(0x092e, -1, require('CZ_ITEMLISTWIN_RES'))
d:add(0x094a, 6, require('CZ_ITEM_PICKUP'))
d:add(0x0891, 6, require('CZ_ITEM_THROW'))
d:add(0x0437, 8, require('CZ_JOIN_BATTLE_FIELD'))
d:add(0x095d, 8, require('CZ_MOVE_ITEM_FROM_BODY_TO_STORE'))
d:add(0x085e, 8, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY'))
d:add(0x085a, 18, require('CZ_PARTY_BOOKING_REQ_REGISTER'))
d:add(0x0927, 26, require('CZ_PARTY_JOIN_REQ'))
d:add(0x0867, 6, require('CZ_REQNAME'))
d:add(0x0954, 6, require('CZ_REQNAME_BYGID'))
d:add(0x0876, 7, require('CZ_REQUEST_ACT'))
d:add(0x0953, 5, require('CZ_REQUEST_MOVE'))
d:add(0x035f, 6, require('CZ_REQUEST_TIME'))
d:add(0x0924, 6, require('CZ_REQ_CLICK_TO_BUYING_STORE'))
d:add(0x023b, 2, require('CZ_REQ_CLOSE_BUYING_STORE'))
d:add(0x086a, -1, require('CZ_REQ_OPEN_BUYING_STORE'))
d:add(0x095c, -1, require('CZ_REQ_TRADE_BUYING_STORE'))
d:add(0x0965, -1, require('CZ_SEARCH_STORE_INFO'))
d:add(0x0890, 2, require('CZ_SEARCH_STORE_INFO_NEXT_PAGE'))
d:add(0x0956, 12, require('CZ_SSILIST_ITEM_CLICK'))
d:add(0x0958, 10, require('CZ_USE_SKILL'))
d:add(0x089c, 10, require('CZ_USE_SKILL_TOGROUND'))
d:add(0x0921, 90, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX'))

return d
