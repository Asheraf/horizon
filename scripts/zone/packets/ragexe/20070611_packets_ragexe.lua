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

d:add(0x02a9, 58, require('CZ_HACKSHIELD_CRC_MSG'))
d:add(0x02a7, 22, require('CZ_HACKSH_CPX_MSG'))
d:add(0x02ba, 9, require('CZ_SHORTCUT_KEY_CHANGE'))
d:add(0x02a8, 162, require('ZC_HACKSHIELD_CRC_MSG'))
d:add(0x02a6, 22, require('ZC_HACKSH_CPX_MSG'))
d:add(0x02b9, 191, require('ZC_SHORTCUT_KEY_LIST'))

return d
