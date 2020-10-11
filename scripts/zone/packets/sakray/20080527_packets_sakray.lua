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

local d = require('default_packets_sakray')

d:add(0x0361, -1, require('CZ_CHANGE_DIRECTION2'))
d:add(0x035e, 2, require('CZ_CLOSE_WINDOW'))
d:add(0x0362, -1, require('CZ_ITEM_PICKUP2'))
d:add(0x0363, -1, require('CZ_ITEM_THROW2'))
d:add(0x0364, -1, require('CZ_MOVE_ITEM_FROM_BODY_TO_STORE2'))
d:add(0x0365, -1, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY2'))
d:add(0x035c, 2, require('CZ_OPEN_SIMPLE_CASHSHOP_ITEMLIST'))
d:add(0x0368, -1, require('CZ_REQNAME2'))
d:add(0x0369, -1, require('CZ_REQNAME_BYGID2'))
d:add(0x035f, -1, require('CZ_REQUEST_MOVE2'))
d:add(0x0360, -1, require('CZ_REQUEST_TIME2'))
d:add(0x0366, -1, require('CZ_USE_SKILL_TOGROUND2'))
d:add(0x0367, -1, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x035d, -1, require('ZC_SIMPLE_CASHSHOP_POINT_ITEMLIST'))

return d
