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

d:add(0x0202, 18, require('CZ_ADD_FRIENDS'))
d:add(0x0361, 2, require('CZ_CHANGE_DIRECTION2'))
d:add(0x022d, 7, require('CZ_COMMAND_MER'))
d:add(0x0436, 6, require('CZ_ENTER2'))
d:add(0x0281, 2, require('CZ_GANGSI_RANK'))
d:add(0x0907, 5, require('CZ_INVENTORY_TAB'))
d:add(0x0362, 8, require('CZ_ITEM_PICKUP2'))
d:add(0x0363, 90, require('CZ_ITEM_THROW2'))
d:add(0x07ec, -1, require('CZ_JOIN_BATTLE_FIELD'))
d:add(0x0365, 2, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY2'))
d:add(0x0802, 2, require('CZ_PARTY_BOOKING_REQ_REGISTER'))
d:add(0x02c4, 2, require('CZ_PARTY_JOIN_REQ'))
d:add(0x08fb, 6, require('CZ_PARTY_RECRUIT_CANCEL_VOLUNTEER'))
d:add(0x0368, 2, require('CZ_REQNAME2'))
d:add(0x0369, -1, require('CZ_REQNAME_BYGID2'))
d:add(0x0437, 2, require('CZ_REQUEST_ACT2'))
d:add(0x0360, 2, require('CZ_REQUEST_TIME2'))
d:add(0x0811, 2, require('CZ_REQ_OPEN_BUYING_STORE'))
d:add(0x0819, 2, require('CZ_REQ_TRADE_BUYING_STORE'))
d:add(0x0835, 19, require('CZ_SEARCH_STORE_INFO'))
d:add(0x0838, 2, require('CZ_SEARCH_STORE_INFO_NEXT_PAGE'))
d:add(0x083c, 2, require('CZ_SSILIST_ITEM_CLICK'))
d:add(0x0438, 2, require('CZ_USE_SKILL2'))
d:add(0x0366, 12, require('CZ_USE_SKILL_TOGROUND2'))
d:add(0x0367, 4, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x0903, -1, require('ZC_CART_ITEMLIST_EQUIP'))
d:add(0x0902, -1, require('ZC_CART_ITEMLIST_NORMAL'))
d:add(0x0901, -1, require('ZC_INVENTORY_ITEMLIST_EQUIP'))
d:add(0x0900, -1, require('ZC_INVENTORY_ITEMLIST_NORMAL'))
d:add(0x0908, 5, require('ZC_INVENTORY_TAB'))
d:add(0x0906, -1, require('ZC_MICROSCOPE'))
d:add(0x0909, 6, require('ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER'))
d:add(0x0905, -1, require('ZC_STORE_ITEMLIST_EQUIP'))
d:add(0x0904, -1, require('ZC_STORE_ITEMLIST_NORMAL'))

return d
