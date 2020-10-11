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

if packet_version >= 20050110 then
	local pid = 0x00f3
elseif packet_version >= 20050104 then
	local pid = 0x00f3
elseif packet_version >= 20050103 then
	local pid = 0x00f3
elseif packet_version >= 20041220 then
	local pid = 0x00f3
elseif packet_version >= 20041216 then
	local pid = 0x00f3
elseif packet_version >= 20041129 then
	local pid = 0x00f3
elseif packet_version >= 20041025 then
	local pid = 0x00f3
elseif packet_version >= 20041005 then
	local pid = 0x00f3
elseif packet_version >= 20040920 then
	local pid = 0x00f3
elseif packet_version >= 20040906 then
	local pid = 0x00f3
elseif packet_version >= 20040804 then
	local pid = 0x00f3
elseif packet_version >= 20040726 then
	local pid = 0x00f3
elseif packet_version >= 20040107 then
	local pid = 0x008c
elseif packet_version >= 0 then
	local pid = 0x00f3
end

local CZ_REQUEST_CHAT = {
	_id = pid,
	_length = 0,
	_buffer = nil
}


function CZ_REQUEST_CHAT.new(o)
	o = o or CZ_REQUEST_CHAT
	setmetatable(o, self)
	self.__index = self
	return o
end

function CZ_REQUEST_CHAT.deserialize(buf)

end

return CZ_REQUEST_CHAT

