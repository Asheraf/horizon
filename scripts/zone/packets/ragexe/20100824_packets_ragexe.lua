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

d:add(0x0846, 4, require('CZ_REQ_SE_CASH_TAB_CODE'))
d:add(0x0844, 2, require('CZ_SE_CASHSHOP_OPEN'))
d:add(0x0848, -1, require('CZ_SE_PC_BUY_CASHITEM_LIST'))
d:add(0x0847, -1, require('ZC_ACK_SE_CASH_ITEM_LIST'))
d:add(0x0845, 10, require('ZC_SE_CASHSHOP_OPEN'))
d:add(0x0849, 12, require('ZC_SE_PC_BUY_CASHITEM_RESULT'))

return d
