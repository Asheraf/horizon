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

d:add(0x023b, 6, require('CZ_ACK_STORE_PASSWORD'))
d:add(0x0361, 18, require('CZ_CHANGE_DIRECTION2'))
d:add(0x022d, 2, require('CZ_COMMAND_MER'))
d:add(0x0436, 19, require('CZ_ENTER2'))
d:add(0x0281, 2, require('CZ_GANGSI_RANK'))
d:add(0x07e4, 2, require('CZ_ITEMLISTWIN_RES'))
d:add(0x0362, 2, require('CZ_ITEM_PICKUP2'))
d:add(0x0363, 2, require('CZ_ITEM_THROW2'))
d:add(0x07ec, 7, require('CZ_JOIN_BATTLE_FIELD'))
d:add(0x0364, 2, require('CZ_MOVE_ITEM_FROM_BODY_TO_STORE2'))
d:add(0x0365, -1, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY2'))
d:add(0x0802, 8, require('CZ_PARTY_BOOKING_REQ_REGISTER'))
d:add(0x02c4, 10, require('CZ_PARTY_JOIN_REQ'))
d:add(0x08dd, 27, require('CZ_REPLY_ENTRY_QUEUE_ADMISSION'))
d:add(0x08e0, 51, require('CZ_REPLY_LOBBY_ADMISSION'))
d:add(0x0369, 8, require('CZ_REQNAME_BYGID2'))
d:add(0x0360, 2, require('CZ_REQUEST_TIME2'))
d:add(0x0815, 5, require('CZ_REQ_CLOSE_BUYING_STORE'))
d:add(0x08d7, 28, require('CZ_REQ_ENTRY_QUEUE_APPLY'))
d:add(0x08da, 26, require('CZ_REQ_ENTRY_QUEUE_CANCEL'))
d:add(0x0835, 26, require('CZ_SEARCH_STORE_INFO'))
d:add(0x083c, 26, require('CZ_SSILIST_ITEM_CLICK'))
d:add(0x0367, 6, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x08d8, 27, require('ZC_ACK_ENTRY_QUEUE_APPLY'))
d:add(0x08db, 27, require('ZC_ACK_ENTRY_QUEUE_CANCEL'))
d:add(0x08e2, 23, require('ZC_NAVIGATION_ACTIVE'))
d:add(0x08dc, 26, require('ZC_NOTIFY_ENTRY_QUEUE_ADMISSION'))
d:add(0x08d9, 30, require('ZC_NOTIFY_ENTRY_QUEUE_APPLY'))
d:add(0x08df, 50, require('ZC_NOTIFY_LOBBY_ADMISSION'))
d:add(0x08de, 27, require('ZC_REPLY_ACK_ENTRY_QUEUE_ADMISSION'))
d:add(0x08e1, 51, require('ZC_REPLY_ACK_LOBBY_ADMISSION'))

return d
