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

if packet_version >= 20070622 then
	local pid = 0x02bb
elseif packet_version >= 20070605 then
	local pid = 0x02bb
elseif packet_version >= 0 then
	local pid = 0x02bb
end

local ZC_EQUIPITEM_DAMAGED = {
	_id = pid,
	_length = 0,
	_buffer = nil
}


function ZC_EQUIPITEM_DAMAGED.new(o)
	o = o or ZC_EQUIPITEM_DAMAGED
	setmetatable(o, self)
	self.__index = self
	return o
end

function ZC_EQUIPITEM_DAMAGED.serialize()

end

return ZC_EQUIPITEM_DAMAGED

