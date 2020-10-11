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

d:add(0x0815, 6, require('CZ_REQ_CLOSE_BUYING_STORE'))
d:add(0x0819, 10, require('CZ_REQ_TRADE_BUYING_STORE'))
d:add(0x0818, -1, require('ZC_ACK_ITEMLIST_BUYING_STORE'))
d:add(0x0814, 2, require('ZC_BUYING_STORE_ENTRY'))
d:add(0x0816, 6, require('ZC_DISAPPEAR_BUYING_STORE_ENTRY'))
d:add(0x081d, 22, require('ZC_EL_INIT'))
d:add(0x081e, 8, require('ZC_EL_PAR_CHANGE'))
d:add(0x081a, 4, require('ZC_FAILED_TRADE_BUYING_STORE_TO_BUYER'))
d:add(0x081c, 6, require('ZC_ITEM_DELETE_BUYING_STORE'))
d:add(0x0813, -1, require('ZC_MYITEMLIST_BUYING_STORE'))
d:add(0x081b, 4, require('ZC_UPDATE_ITEM_FROM_BUYING_STORE'))

return d
