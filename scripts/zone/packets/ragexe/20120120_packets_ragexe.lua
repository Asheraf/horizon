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

d:add(0x023b, 2, require('CZ_ACK_STORE_PASSWORD'))
d:add(0x0202, 12, require('CZ_ADD_FRIENDS'))
d:add(0x0361, 19, require('CZ_CHANGE_DIRECTION2'))
d:add(0x0436, 5, require('CZ_ENTER2'))
d:add(0x0362, -1, require('CZ_ITEM_PICKUP2'))
d:add(0x0363, 2, require('CZ_ITEM_THROW2'))
d:add(0x07ec, 26, require('CZ_JOIN_BATTLE_FIELD'))
d:add(0x0364, 2, require('CZ_MOVE_ITEM_FROM_BODY_TO_STORE2'))
d:add(0x0365, 6, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY2'))
d:add(0x0802, 2, require('CZ_PARTY_BOOKING_REQ_REGISTER'))
d:add(0x02c4, 8, require('CZ_PARTY_JOIN_REQ'))
d:add(0x0368, 6, require('CZ_REQNAME2'))
d:add(0x0437, -1, require('CZ_REQUEST_ACT2'))
d:add(0x0360, 2, require('CZ_REQUEST_TIME2'))
d:add(0x0912, 10, require('CZ_REQ_GUILD_NAME'))
d:add(0x0811, 6, require('CZ_REQ_OPEN_BUYING_STORE'))
d:add(0x0910, 10, require('CZ_REQ_PARTY_NAME'))
d:add(0x0838, 26, require('CZ_SEARCH_STORE_INFO_NEXT_PAGE'))
d:add(0x0366, 2, require('CZ_USE_SKILL_TOGROUND2'))
d:add(0x0367, 10, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x0913, 30, require('ZC_ACK_GUILD_NAME'))
d:add(0x0911, 30, require('ZC_ACK_PARTY_NAME'))

return d
