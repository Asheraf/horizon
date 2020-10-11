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

d:add(0x0447, 2, require('CZ_BLOCKING_PLAY_CANCEL'))
d:add(0x07d4, 4, require('CZ_ES_CANCEL'))
d:add(0x07d3, 4, require('CZ_ES_CHOOSE'))
d:add(0x07d1, 2, require('CZ_ES_GET_LIST'))
d:add(0x07d6, 4, require('ZC_ES_GOTO'))
d:add(0x07d2, -1, require('ZC_ES_LIST'))
d:add(0x07d5, 4, require('ZC_ES_READY'))
d:add(0x07d0, 6, require('ZC_ES_RESULT'))

return d
