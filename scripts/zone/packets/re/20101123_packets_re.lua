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

d:add(0x0361, 5, require('CZ_CHANGE_DIRECTION2'))
d:add(0x0362, 6, require('CZ_ITEM_PICKUP2'))
d:add(0x0363, 6, require('CZ_ITEM_THROW2'))
d:add(0x0364, 8, require('CZ_MOVE_ITEM_FROM_BODY_TO_STORE2'))
d:add(0x0365, 8, require('CZ_MOVE_ITEM_FROM_STORE_TO_BODY2'))
d:add(0x0368, 6, require('CZ_REQNAME2'))
d:add(0x0369, 6, require('CZ_REQNAME_BYGID2'))
d:add(0x035f, 5, require('CZ_REQUEST_MOVE2'))
d:add(0x0360, 6, require('CZ_REQUEST_TIME2'))
d:add(0x0366, 10, require('CZ_USE_SKILL_TOGROUND2'))
d:add(0x0367, 90, require('CZ_USE_SKILL_TOGROUND_WITHTALKBOX2'))
d:add(0x0859, -1, require('ZC_EQUIPWIN_MICROSCOPE2'))
d:add(0x0856, -1, require('ZC_NOTIFY_MOVEENTRY8'))
d:add(0x0858, -1, require('ZC_NOTIFY_NEWENTRY6'))
d:add(0x0857, -1, require('ZC_NOTIFY_STANDENTRY7'))

return d
