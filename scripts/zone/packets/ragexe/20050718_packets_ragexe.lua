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

d:add(0x024d, 14, require('CZ_AUCTION_ADD'))
d:add(0x024e, 6, require('CZ_AUCTION_ADD_CANCEL'))
d:add(0x024c, 8, require('CZ_AUCTION_ADD_ITEM'))
d:add(0x024f, 10, require('CZ_AUCTION_BUY'))
d:add(0x024b, 4, require('CZ_AUCTION_CREATE'))
d:add(0x0251, 2, require('CZ_AUCTION_ITEM_SEARCH'))
d:add(0x009b, 33, require('CZ_CHANGE_DIRECTION'))
d:add(0x0072, 20, require('CZ_ENTER'))
d:add(0x009f, 17, require('CZ_ITEM_PICKUP'))
d:add(0x00a2, 12, require('CZ_ITEM_THROW'))
d:add(0x0247, 8, require('CZ_MAIL_ADD_ITEM'))
d:add(0x0243, 6, require('CZ_MAIL_DELETE'))
d:add(0x0244, 6, require('CZ_MAIL_GET_ITEM'))
d:add(0x023f, 2, require('CZ_MAIL_GET_LIST'))
d:add(0x0241, 6, require('CZ_MAIL_OPEN'))
d:add(0x0246, 4, require('CZ_MAIL_RESET_ITEM'))
d:add(0x0248, 68, require('CZ_MAIL_SEND'))
d:add(0x00f5, 10, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY'))
d:add(0x0094, 16, require('CZ_REQNAME'))
d:add(0x0089, 10, require('CZ_REQUEST_ACT'))
d:add(0x0085, 13, require('CZ_REQUEST_MOVE'))
d:add(0x00f7, 26, require('CZ_REQUEST_TIME'))
d:add(0x0113, 23, require('CZ_USE_SKILL'))
d:add(0x0116, 14, require('CZ_USE_SKILL_TOGROUND'))
d:add(0x0190, 9, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX'))
d:add(0x0252, -1, require('ZC_AUCTION_ITEM_REQ_SEARCH'))
d:add(0x0250, 3, require('ZC_AUCTION_RESULT'))
d:add(0x024a, 70, require('ZC_MAIL_RECEIVE'))
d:add(0x0245, 7, require('ZC_MAIL_REQ_GET_ITEM'))
d:add(0x0240, 8, require('ZC_MAIL_REQ_GET_LIST'))
d:add(0x0242, -1, require('ZC_MAIL_REQ_OPEN'))
d:add(0x0249, 3, require('ZC_MAIL_REQ_SEND'))

return d
