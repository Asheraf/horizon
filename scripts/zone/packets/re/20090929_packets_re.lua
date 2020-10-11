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

d:add(0x07ea, 2, require('CZ_BATTLE_FIELD_LIST'))
d:add(0x07ee, 6, require('CZ_CANCEL_BATTLE_FIELD'))
d:add(0x07ec, 6, require('CZ_JOIN_BATTLE_FIELD'))
d:add(0x07f0, 8, require('CZ_REQ_BATTLE_STATE_MONITOR'))
d:add(0x07f1, 15, require('ZC_ACK_BATTLE_STATE_MONITOR'))
d:add(0x07eb, -1, require('ZC_BATTLE_FIELD_LIST'))
d:add(0x07f3, 3, require('ZC_BATTLE_JOIN_NOTI_DEFER'))
d:add(0x07f2, 4, require('ZC_BATTLE_NOTI_START_STEP'))
d:add(0x07ef, 8, require('ZC_CANCEL_BATTLE_FIELD'))
d:add(0x07ed, 8, require('ZC_JOIN_BATTLE_FIELD'))

return d
