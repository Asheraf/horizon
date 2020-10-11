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

d:add(0x029f, 3, require('CZ_MER_COMMAND'))
d:add(0x02a1, 4, require('CZ_UNUSED_MER_UPGRADE_SKILLLEVEL'))
d:add(0x02a0, 10, require('CZ_UNUSED_MER_USE_SKILL'))
d:add(0x029b, 70, require('ZC_MER_INIT'))
d:add(0x02a2, 8, require('ZC_MER_PAR_CHANGE'))
d:add(0x029c, 66, require('ZC_MER_PROPERTY'))
d:add(0x029d, -1, require('ZC_MER_SKILLINFO_LIST'))
d:add(0x029e, 11, require('ZC_MER_SKILLINFO_UPDATE'))

return d
