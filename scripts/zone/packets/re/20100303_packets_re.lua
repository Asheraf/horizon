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

d:add(0x0817, -1, require('CZ_REQ_CLICK_TO_BUYING_STORE'))
d:add(0x0815, -1, require('CZ_REQ_CLOSE_BUYING_STORE'))
d:add(0x0811, -1, require('CZ_REQ_OPEN_BUYING_STORE'))
d:add(0x0819, 4, require('CZ_REQ_TRADE_BUYING_STORE'))
d:add(0x0818, 6, require('ZC_ACK_ITEMLIST_BUYING_STORE'))
d:add(0x0814, 6, require('ZC_BUYING_STORE_ENTRY'))
d:add(0x0812, 86, require('ZC_FAILED_OPEN_BUYING_STORE_TO_BUYER'))
d:add(0x0813, 6, require('ZC_MYITEMLIST_BUYING_STORE'))
d:add(0x0810, 3, require('ZC_OPEN_BUYING_STORE'))

return d
