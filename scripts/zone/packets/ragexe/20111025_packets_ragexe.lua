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

d:add(0x023b, 5, require('CZ_ACK_STORE_PASSWORD'))
d:add(0x0202, 4, require('CZ_ADD_FRIENDS'))
d:add(0x0361, 2, require('CZ_CHANGE_DIRECTION2'))
d:add(0x022d, 2, require('CZ_COMMAND_MER'))
d:add(0x0436, 2, require('CZ_ENTER2'))
d:add(0x0281, -1, require('CZ_GANGSI_RANK'))
d:add(0x0363, 19, require('CZ_ITEM_THROW2'))
d:add(0x07ec, 10, require('CZ_JOIN_BATTLE_FIELD'))
d:add(0x0802, 2, require('CZ_PARTY_BOOKING_REQ_REGISTER'))
d:add(0x08f7, 6, require('CZ_PARTY_RECRUIT_ACK_RECALL'))
d:add(0x08ef, -1, require('CZ_PARTY_RECRUIT_ADD_FILTERLINGLIST'))
d:add(0x08e9, 2, require('CZ_PARTY_RECRUIT_REQ_DELETE'))
d:add(0x08e5, 41, require('CZ_PARTY_RECRUIT_REQ_REGISTER'))
d:add(0x08e7, 10, require('CZ_PARTY_RECRUIT_REQ_SEARCH'))
d:add(0x08eb, 39, require('CZ_PARTY_RECRUIT_REQ_UPDATE'))
d:add(0x08f1, 6, require('CZ_PARTY_RECRUIT_REQ_VOLUNTEER'))
d:add(0x08f4, 6, require('CZ_PARTY_RECRUIT_SHOW_EQUIPMENT'))
d:add(0x08f0, -1, require('CZ_PARTY_RECRUIT_SUB_FILTERLINGLIST'))
d:add(0x0368, 6, require('CZ_REQNAME2'))
d:add(0x0369, 7, require('CZ_REQNAME_BYGID2'))
d:add(0x0437, 5, require('CZ_REQUEST_ACT2'))
d:add(0x035f, 6, require('CZ_REQUEST_MOVE2'))
d:add(0x0360, 6, require('CZ_REQUEST_TIME2'))
d:add(0x0817, 2, require('CZ_REQ_CLICK_TO_BUYING_STORE'))
d:add(0x0815, -1, require('CZ_REQ_CLOSE_BUYING_STORE'))
d:add(0x0819, -1, require('CZ_REQ_TRADE_BUYING_STORE'))
d:add(0x0835, 6, require('CZ_SEARCH_STORE_INFO'))
d:add(0x0838, 12, require('CZ_SEARCH_STORE_INFO_NEXT_PAGE'))
d:add(0x08f5, 2, require('CZ_UNKNOWN_BOOKING_SOMMON_MEMBER_08f5'))
d:add(0x0438, 2, require('CZ_USE_SKILL2'))
d:add(0x0366, 90, require('CZ_USE_SKILL_TOGROUND2'))
d:add(0x0367, 8, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x08ea, 4, require('ZC_PARTY_RECRUIT_ACK_DELETE'))
d:add(0x08e6, 4, require('ZC_PARTY_RECRUIT_ACK_REGISTER'))
d:add(0x08f8, 6, require('ZC_PARTY_RECRUIT_FAILED_RECALL'))
d:add(0x08ee, 6, require('ZC_PARTY_RECRUIT_NOTIFY_DELETE'))
d:add(0x08ec, 73, require('ZC_PARTY_RECRUIT_NOTIFY_INSERT'))
d:add(0x08ed, 43, require('ZC_PARTY_RECRUIT_NOTIFY_UPDATE'))
d:add(0x08f6, 6, require('ZC_PARTY_RECRUIT_RECALL_COST'))
d:add(0x08f2, 12, require('ZC_PARTY_RECRUIT_VOLUNTEER_INFO'))

return d
