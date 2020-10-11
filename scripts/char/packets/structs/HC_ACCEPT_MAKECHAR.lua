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

if packet_version >= 20170906 then
	local pid = 0x006d
elseif packet_version >= 20170830 then
	local pid = 0x006d
elseif packet_version >= 20170104 then
	local pid = 0x006d
elseif packet_version >= 20140820 then
	local pid = 0x006d
elseif packet_version >= 20140625 then
	local pid = 0x006d
elseif packet_version >= 20140108 then
	local pid = 0x006d
elseif packet_version >= 20111101 then
	local pid = 0x006d
elseif packet_version >= 20111025 then
	local pid = 0x006d
elseif packet_version >= 20110928 then
	local pid = 0x006d
elseif packet_version >= 20110111 then
	local pid = 0x006d
elseif packet_version >= 20110104 then
	local pid = 0x006d
elseif packet_version >= 20100803 then
	local pid = 0x006d
elseif packet_version >= 20100728 then
	local pid = 0x006d
elseif packet_version >= 20100727 then
	local pid = 0x006d
elseif packet_version >= 20100720 then
	local pid = 0x006d
elseif packet_version >= 20100105 then
	local pid = 0x006d
elseif packet_version >= 20090617 then
	local pid = 0x006d
elseif packet_version >= 20090107 then
	local pid = 0x006d
elseif packet_version >= 20081217 then
	local pid = 0x006d
elseif packet_version >= 20080827 then
	local pid = 0x006d
elseif packet_version >= 20061030 then
	local pid = 0x006d
elseif packet_version >= 20061023 then
	local pid = 0x006d
elseif packet_version >= 20060102 then
	local pid = 0x006d
elseif packet_version >= 0 then
	local pid = 0x006d
end

local HC_ACCEPT_MAKECHAR = {
	_id = pid,
	_length = 0,
	_buffer = nil
}


function HC_ACCEPT_MAKECHAR.new(o)
	o = o or HC_ACCEPT_MAKECHAR
	setmetatable(o, self)
	self.__index = self
	return o
end

function HC_ACCEPT_MAKECHAR.serialize()

end

return HC_ACCEPT_MAKECHAR

