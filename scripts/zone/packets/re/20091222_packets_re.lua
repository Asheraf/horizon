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

d:add(0x0806, 4, require('CZ_PARTY_BOOKING_REQ_DELETE'))
d:add(0x0802, 18, require('CZ_PARTY_BOOKING_REQ_REGISTER'))
d:add(0x0804, 8, require('CZ_PARTY_BOOKING_REQ_SEARCH'))
d:add(0x0808, 4, require('CZ_PARTY_BOOKING_REQ_UPDATE'))
d:add(0x080c, 6, require('CZ_SIMPLE_CASH_BTNSHOW'))
d:add(0x0807, 2, require('ZC_PARTY_BOOKING_ACK_DELETE'))
d:add(0x0803, 4, require('ZC_PARTY_BOOKING_ACK_REGISTER'))
d:add(0x0805, -1, require('ZC_PARTY_BOOKING_ACK_SEARCH'))
d:add(0x080b, 18, require('ZC_PARTY_BOOKING_NOTIFY_DELETE'))
d:add(0x0809, 14, require('ZC_PARTY_BOOKING_NOTIFY_INSERT'))
d:add(0x080a, 50, require('ZC_PARTY_BOOKING_NOTIFY_UPDATE'))

return d
