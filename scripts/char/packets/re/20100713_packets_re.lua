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

d:add(0x0829, 6, require('CH_DELETE_CHAR3'))
d:add(0x082b, 6, require('CH_DELETE_CHAR3_CANCEL'))
d:add(0x0827, 6, require('CH_DELETE_CHAR3_RESERVED'))
d:add(0x0841, 19, require('CH_SELECT_ACCESSIBLE_MAPNAME'))
d:add(0x082a, 10, require('HC_DELETE_CHAR3'))
d:add(0x082c, 14, require('HC_DELETE_CHAR3_CANCEL'))
d:add(0x0828, 14, require('HC_DELETE_CHAR3_RESERVED'))
d:add(0x0840, -1, require('HC_NOTIFY_ACCESSIBLE_MAPNAME'))

return d
