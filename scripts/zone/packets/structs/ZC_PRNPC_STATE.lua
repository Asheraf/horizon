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

if RAGNA_ROOT == nil then print('Error: Running outside of project directory') os.exit() end

if packet_version >= 20180228 then
	local pid = 0x091b
elseif packet_version >= 20180221 then
	local pid = 0x091b
elseif packet_version >= 20180103 then
	local pid = 0x091b
elseif packet_version >= 20171227 then
	local pid = 0x091b
elseif packet_version >= 20171220 then
	local pid = 0x091b
elseif packet_version >= 20171206 then
	local pid = 0x091b
elseif packet_version >= 20171204 then
	local pid = 0x091b
elseif packet_version >= 20171108 then
	local pid = 0x091b
elseif packet_version >= 20171101 then
	local pid = 0x091b
elseif packet_version >= 20171018 then
	local pid = 0x091b
elseif packet_version >= 20170920 then
	local pid = 0x091b
elseif packet_version >= 20170913 then
	local pid = 0x091b
elseif packet_version >= 20170726 then
	local pid = 0x091b
elseif packet_version >= 20170719 then
	local pid = 0x091b
elseif packet_version >= 20170621 then
	local pid = 0x091b
elseif packet_version >= 20170614 then
	local pid = 0x091b
elseif packet_version >= 20170524 then
	local pid = 0x091b
elseif packet_version >= 20170517 then
	local pid = 0x091b
elseif packet_version >= 20170426 then
	local pid = 0x091b
elseif packet_version >= 20170419 then
	local pid = 0x091b
elseif packet_version >= 20170322 then
	local pid = 0x091b
elseif packet_version >= 20170315 then
	local pid = 0x091b
elseif packet_version >= 20170201 then
	local pid = 0x091b
elseif packet_version >= 20170125 then
	local pid = 0x091b
elseif packet_version >= 20170118 then
	local pid = 0x091b
elseif packet_version >= 20170111 then
	local pid = 0x091b
elseif packet_version >= 20170104 then
	local pid = 0x091b
elseif packet_version >= 20161109 then
	local pid = 0x091b
elseif packet_version >= 20161102 then
	local pid = 0x091b
elseif packet_version >= 20161026 then
	local pid = 0x091b
elseif packet_version >= 20160907 then
	local pid = 0x091b
elseif packet_version >= 20160831 then
	local pid = 0x091b
elseif packet_version >= 20160817 then
	local pid = 0x091b
elseif packet_version >= 20160803 then
	local pid = 0x091b
elseif packet_version >= 20160713 then
	local pid = 0x091b
elseif packet_version >= 20160706 then
	local pid = 0x091b
elseif packet_version >= 20160330 then
	local pid = 0x091b
elseif packet_version >= 20160323 then
	local pid = 0x091b
elseif packet_version >= 20160120 then
	local pid = 0x091b
elseif packet_version >= 20160113 then
	local pid = 0x091b
elseif packet_version >= 20160106 then
	local pid = 0x091b
elseif packet_version >= 20151230 then
	local pid = 0x091b
elseif packet_version >= 20151223 then
	local pid = 0x091b
elseif packet_version >= 20150610 then
	local pid = 0x091b
elseif packet_version >= 20150603 then
	local pid = 0x091b
elseif packet_version >= 20150415 then
	local pid = 0x091b
elseif packet_version >= 20150408 then
	local pid = 0x091b
elseif packet_version >= 20150401 then
	local pid = 0x091b
elseif packet_version >= 20150107 then
	local pid = 0x091b
elseif packet_version >= 20140219 then
	local pid = 0x091b
elseif packet_version >= 20140212 then
	local pid = 0x091b
elseif packet_version >= 20140108 then
	local pid = 0x091b
elseif packet_version >= 20130306 then
	local pid = 0x091b
elseif packet_version >= 20130227 then
	local pid = 0x091b
elseif packet_version >= 20130115 then
	local pid = 0x091b
elseif packet_version >= 20130109 then
	local pid = 0x091b
elseif packet_version >= 20130103 then
	local pid = 0x091b
elseif packet_version >= 20121205 then
	local pid = 0x091b
elseif packet_version >= 20121128 then
	local pid = 0x091b
elseif packet_version >= 20120503 then
	local pid = 0x091b
elseif packet_version >= 20120502 then
	local pid = 0x091b
elseif packet_version >= 20120424 then
	local pid = 0x091b
elseif packet_version >= 20120404 then
	local pid = 0x096b
elseif packet_version >= 20120328 then
	local pid = 0x091b
elseif packet_version >= 20120207 then
	local pid = 0x096b
elseif packet_version >= 0 then
	local pid = 0x096b
end

local ZC_PRNPC_STATE = {
	_id = pid,
	_length = 0,
	_buffer = nil
}


function ZC_PRNPC_STATE.new(o)
	o = o or ZC_PRNPC_STATE
	setmetatable(o, self)
	self.__index = self
	return o
end

function ZC_PRNPC_STATE.serialize()

end

return ZC_PRNPC_STATE

