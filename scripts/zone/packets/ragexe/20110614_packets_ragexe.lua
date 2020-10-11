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

d:add(0x0361, 8, require('CZ_CHANGE_DIRECTION2'))
d:add(0x022d, 6, require('CZ_COMMAND_MER'))
d:add(0x0436, 6, require('CZ_ENTER2'))
d:add(0x07e4, 19, require('CZ_ITEMLISTWIN_RES'))
d:add(0x07ec, 5, require('CZ_JOIN_BATTLE_FIELD'))
d:add(0x02c4, 2, require('CZ_PARTY_JOIN_REQ'))
d:add(0x0360, 4, require('CZ_REQUEST_TIME2'))
d:add(0x0815, -1, require('CZ_REQ_CLOSE_BUYING_STORE'))
d:add(0x08c9, 2, require('CZ_REQ_SCHEDULER_CASHITEM'))
d:add(0x0367, 6, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x08ca, -1, require('ZC_ACK_SCHEDULER_CASHITEM'))
d:add(0x08c8, 34, require('ZC_NOTIFY_ACT3'))

return d
