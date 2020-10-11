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

if packet_version >= 20180131 then
	local pid = 0x091c
elseif packet_version >= 20180117 then
	local pid = 0x091c
elseif packet_version >= 20180103 then
	local pid = 0x091c
elseif packet_version >= 20171227 then
	local pid = 0x091c
elseif packet_version >= 20171121 then
	local pid = 0x091c
elseif packet_version >= 20171115 then
	local pid = 0x091c
elseif packet_version >= 20171018 then
	local pid = 0x091c
elseif packet_version >= 20170823 then
	local pid = 0x091c
elseif packet_version >= 20170816 then
	local pid = 0x091c
elseif packet_version >= 20170201 then
	local pid = 0x091c
elseif packet_version >= 20170125 then
	local pid = 0x091c
elseif packet_version >= 20170104 then
	local pid = 0x091c
elseif packet_version >= 20161228 then
	local pid = 0x091c
elseif packet_version >= 20160913 then
	local pid = 0x091c
elseif packet_version >= 20160907 then
	local pid = 0x091c
elseif packet_version >= 20160817 then
	local pid = 0x091c
elseif packet_version >= 20160810 then
	local pid = 0x091c
elseif packet_version >= 20160727 then
	local pid = 0x091c
elseif packet_version >= 20160720 then
	local pid = 0x091c
elseif packet_version >= 20160713 then
	local pid = 0x091c
elseif packet_version >= 20160629 then
	local pid = 0x091c
elseif packet_version >= 20160622 then
	local pid = 0x091c
elseif packet_version >= 20160106 then
	local pid = 0x091c
elseif packet_version >= 20151021 then
	local pid = 0x091c
elseif packet_version >= 20151014 then
	local pid = 0x091c
elseif packet_version >= 20150527 then
	local pid = 0x091c
elseif packet_version >= 20150520 then
	local pid = 0x091c
elseif packet_version >= 20150408 then
	local pid = 0x091c
elseif packet_version >= 20150401 then
	local pid = 0x091c
elseif packet_version >= 20150318 then
	local pid = 0x091c
elseif packet_version >= 20150311 then
	local pid = 0x091c
elseif packet_version >= 20150107 then
	local pid = 0x091c
elseif packet_version >= 20141210 then
	local pid = 0x091c
elseif packet_version >= 20141203 then
	local pid = 0x091c
elseif packet_version >= 20141008 then
	local pid = 0x091c
elseif packet_version >= 20141001 then
	local pid = 0x091c
elseif packet_version >= 20140416 then
	local pid = 0x091c
elseif packet_version >= 20140409 then
	local pid = 0x091c
elseif packet_version >= 20140319 then
	local pid = 0x091c
elseif packet_version >= 20140312 then
	local pid = 0x091c
elseif packet_version >= 20140108 then
	local pid = 0x091c
elseif packet_version >= 20131120 then
	local pid = 0x091c
elseif packet_version >= 20131113 then
	local pid = 0x091c
elseif packet_version >= 20131016 then
	local pid = 0x091c
elseif packet_version >= 20131008 then
	local pid = 0x091c
elseif packet_version >= 20130925 then
	local pid = 0x091c
elseif packet_version >= 20130917 then
	local pid = 0x091c
elseif packet_version >= 20130103 then
	local pid = 0x091c
elseif packet_version >= 20121227 then
	local pid = 0x091c
elseif packet_version >= 20121218 then
	local pid = 0x091c
elseif packet_version >= 20121212 then
	local pid = 0x091c
elseif packet_version >= 20121205 then
	local pid = 0x091c
elseif packet_version >= 20121128 then
	local pid = 0x091c
elseif packet_version >= 20120801 then
	local pid = 0x091c
elseif packet_version >= 20120724 then
	local pid = 0x091c
elseif packet_version >= 20120417 then
	local pid = 0x091c
elseif packet_version >= 20120410 then
	local pid = 0x091c
elseif packet_version >= 20120207 then
	local pid = 0x096c
elseif packet_version >= 0 then
	local pid = 0x096c
end

local ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM = {
	_id = pid,
	_length = 0,
	_buffer = nil
}


function ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM.new(o)
	o = o or ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM
	setmetatable(o, self)
	self.__index = self
	return o
end

function ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM.serialize()

end

return ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM

