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

d:add(0x026a, 4, require('AC_ACK_EKEY_FAIL_AUTHREFUSE'))
d:add(0x026b, 4, require('AC_ACK_EKEY_FAIL_INPUTEKEY'))
d:add(0x026d, 4, require('AC_ACK_EKEY_FAIL_NEEDCARDPASS'))
d:add(0x0267, 4, require('AC_ACK_EKEY_FAIL_NOTEXIST'))
d:add(0x026c, 4, require('AC_ACK_EKEY_FAIL_NOTICE'))
d:add(0x0269, 4, require('AC_ACK_EKEY_FAIL_NOTUSEDEKEY'))
d:add(0x0268, 4, require('AC_ACK_EKEY_FAIL_NOTUSESEKEY'))
d:add(0x026f, 2, require('AC_ACK_FIRST_LOGIN'))
d:add(0x0272, 44, require('AC_ACK_PT_ID_INFO'))
d:add(0x0270, 2, require('AC_REQ_LOGIN_ACCOUNT_INFO'))
d:add(0x0263, 11, require('AC_REQ_LOGIN_CARDPASS'))
d:add(0x0262, 11, require('AC_REQ_LOGIN_NEWEKEY'))
d:add(0x0261, 11, require('AC_REQ_LOGIN_OLDEKEY'))
d:add(0x0271, 38, require('CA_ACK_LOGIN_ACCOUNT_INFO'))
d:add(0x0266, 30, require('CA_ACK_LOGIN_CARDPASS'))
d:add(0x0265, 20, require('CA_ACK_LOGIN_NEWEKEY'))
d:add(0x0264, 20, require('CA_ACK_LOGIN_OLDEKEY'))

return d
