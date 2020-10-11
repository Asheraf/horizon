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

local d = require('default_packets_ad')

d:add(0x0218, 2, require('CZ_ALCHEMIST_RANK'))
d:add(0x0217, 2, require('CZ_BLACKSMITH_RANK'))
d:add(0x021c, 10, require('ZC_ALCHEMIST_POINT'))
d:add(0x021a, 282, require('ZC_ALCHEMIST_RANK'))
d:add(0x0216, 6, require('ZC_BABYMSG'))
d:add(0x021b, 10, require('ZC_BLACKSMITH_POINT'))
d:add(0x0219, 282, require('ZC_BLACKSMITH_RANK'))

return d
