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

d:add(0x02c8, 3, require('CZ_PARTY_CONFIG'))
d:add(0x02c4, 26, require('CZ_PARTY_JOIN_REQ'))
d:add(0x02c7, 7, require('CZ_PARTY_JOIN_REQ_ACK'))
d:add(0x02b3, 107, require('ZC_ADD_QUEST'))
d:add(0x02c2, -1, require('ZC_FORMATSTRING_MSG'))
d:add(0x02c9, 3, require('ZC_PARTY_CONFIG'))
d:add(0x02c6, 30, require('ZC_PARTY_JOIN_REQ'))
d:add(0x02c5, 30, require('ZC_PARTY_JOIN_REQ_ACK'))

return d
