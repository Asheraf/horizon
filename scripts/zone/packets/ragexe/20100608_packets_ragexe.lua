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

d:add(0x083b, 2, require('CZ_CLOSE_SEARCH_STORE_INFO'))
d:add(0x0838, 2, require('CZ_SEARCH_STORE_INFO_NEXT_PAGE'))
d:add(0x083c, 12, require('CZ_SSILIST_ITEM_CLICK'))
d:add(0x0839, 66, require('ZC_ACK_BAN_GUILD_SSO'))
d:add(0x083a, 4, require('ZC_OPEN_SEARCH_STORE_INFO'))
d:add(0x083d, 6, require('ZC_SSILIST_ITEM_CLICK_ACK'))

return d
