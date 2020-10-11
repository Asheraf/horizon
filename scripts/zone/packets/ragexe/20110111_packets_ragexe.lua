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

d:add(0x023b, 26, require('CZ_ACK_STORE_PASSWORD'))
d:add(0x0202, 5, require('CZ_ADD_FRIENDS'))
d:add(0x0361, 5, require('CZ_CHANGE_DIRECTION2'))
d:add(0x022d, 19, require('CZ_COMMAND_MER'))
d:add(0x0436, 4, require('CZ_ENTER2'))
d:add(0x0367, 36, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x08b3, -1, require('ZC_SHOWSCRIPT'))

return d
