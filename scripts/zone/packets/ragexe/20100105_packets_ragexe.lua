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

d:add(0x023b, 36, require('CZ_ACK_STORE_PASSWORD'))
d:add(0x0202, 26, require('CZ_ADD_FRIENDS'))
d:add(0x0361, -1, require('CZ_CHANGE_DIRECTION2'))
d:add(0x022d, 5, require('CZ_COMMAND_MER'))
d:add(0x0436, 19, require('CZ_ENTER2'))
d:add(0x07d4, 4, require('CZ_ES_CANCEL'))
d:add(0x07d3, 4, require('CZ_ES_CHOOSE'))
d:add(0x07d1, 2, require('CZ_ES_GET_LIST'))
d:add(0x0281, 4, require('CZ_GANGSI_RANK'))
d:add(0x02f6, -1, require('CZ_IRMAIL_LIST'))
d:add(0x02f3, -1, require('CZ_IRMAIL_SEND'))
d:add(0x07e4, -1, require('CZ_ITEMLISTWIN_RES'))
d:add(0x0362, -1, require('CZ_ITEM_PICKUP2'))
d:add(0x0363, -1, require('CZ_ITEM_THROW2'))
d:add(0x07ec, 8, require('CZ_JOIN_BATTLE_FIELD'))
d:add(0x0364, -1, require('CZ_MOVE_ITEM_FROM_BODY_TO_STORE2'))
d:add(0x0365, -1, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY2'))
d:add(0x0802, 18, require('CZ_PARTY_BOOKING_REQ_REGISTER'))
d:add(0x02c4, 26, require('CZ_PARTY_JOIN_REQ'))
d:add(0x0288, 10, require('CZ_PC_BUY_CASH_POINT_ITEM'))
d:add(0x0368, -1, require('CZ_REQNAME2'))
d:add(0x0369, -1, require('CZ_REQNAME_BYGID2'))
d:add(0x0437, 7, require('CZ_REQUEST_ACT2'))
d:add(0x035f, -1, require('CZ_REQUEST_MOVE2'))
d:add(0x0360, -1, require('CZ_REQUEST_TIME2'))
d:add(0x07f0, 8, require('CZ_REQ_BATTLE_STATE_MONITOR'))
d:add(0x0438, 10, require('CZ_USE_SKILL2'))
d:add(0x0366, -1, require('CZ_USE_SKILL_TOGROUND2'))
d:add(0x0367, -1, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x07f1, 15, require('ZC_ACK_BATTLE_STATE_MONITOR'))
d:add(0x0158, -1, require('ZC_ACK_OPEN_MEMBER_INFO'))
d:add(0x07f3, 4, require('ZC_BATTLE_JOIN_NOTI_DEFER'))
d:add(0x07f2, 6, require('ZC_BATTLE_NOTI_START_STEP'))
d:add(0x07d6, 4, require('ZC_ES_GOTO'))
d:add(0x07d2, -1, require('ZC_ES_LIST'))
d:add(0x07d5, 4, require('ZC_ES_READY'))
d:add(0x07d0, 6, require('ZC_ES_RESULT'))
d:add(0x02f5, -1, require('ZC_IRMAIL_NOTIFY'))
d:add(0x02f4, -1, require('ZC_IRMAIL_SEND_RES'))
d:add(0x00aa, 7, require('ZC_REQ_WEAR_EQUIP_ACK'))
d:add(0x0442, 8, require('ZC_SKILL_SELECT_REQUEST'))

return d
