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

d:add(0x009b, 5, require('CZ_CHANGE_DIRECTION'))
d:add(0x00f7, 2, require('CZ_CLOSE_STORE'))
d:add(0x0072, 19, require('CZ_ENTER'))
d:add(0x01d5, 8, require('CZ_INPUT_EDITDLGSTR'))
d:add(0x009f, 6, require('CZ_ITEM_PICKUP'))
d:add(0x00a2, 6, require('CZ_ITEM_THROW'))
d:add(0x019c, 4, require('CZ_LOCALBROADCAST'))
d:add(0x00f3, 8, require('CZ_MOVE_ITEM_FROM_BODY_TO_STORE'))
d:add(0x00f5, 8, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY'))
d:add(0x0094, 6, require('CZ_REQNAME'))
d:add(0x0193, 6, require('CZ_REQNAME_BYGID'))
d:add(0x0089, 7, require('CZ_REQUEST_ACT'))
d:add(0x008c, -1, require('CZ_REQUEST_CHAT'))
d:add(0x0085, 5, require('CZ_REQUEST_MOVE'))
d:add(0x007e, 6, require('CZ_REQUEST_TIME'))
d:add(0x00a7, 8, require('CZ_USE_ITEM'))
d:add(0x0113, 10, require('CZ_USE_SKILL'))
d:add(0x0116, 10, require('CZ_USE_SKILL_TOGROUND'))
d:add(0x0190, 90, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX'))

return d
