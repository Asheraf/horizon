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

if packet_version >= 20070711 then
	local pid = 0x0289
elseif packet_version >= 20070423 then
	local pid = 0x0289
elseif packet_version >= 20070227 then
	local pid = 0x0289
elseif packet_version >= 20070102 then
	local pid = 0x0289
elseif packet_version >= 20061204 then
	local pid = 0x0289
elseif packet_version >= 0 then
	local pid = 0x0289
end

local ZC_PC_CASH_POINT_UPDATE = {
	_id = pid,
	_length = 0,
	_buffer = nil
}


function ZC_PC_CASH_POINT_UPDATE.new(o)
	o = o or ZC_PC_CASH_POINT_UPDATE
	setmetatable(o, self)
	self.__index = self
	return o
end

function ZC_PC_CASH_POINT_UPDATE.serialize()

end

return ZC_PC_CASH_POINT_UPDATE

