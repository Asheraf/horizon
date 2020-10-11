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

if packet_version >= 20180523 then
	local pid = 0x0367
elseif packet_version >= 20180511 then
	local pid = 0x0367
elseif packet_version >= 20180321 then
	local pid = 0x0367
elseif packet_version >= 20180315 then
	local pid = 0x0367
elseif packet_version >= 20180207 then
	local pid = 0x0367
elseif packet_version >= 20180131 then
	local pid = 0x0367
elseif packet_version >= 20180103 then
	local pid = 0x0367
elseif packet_version >= 20171127 then
	local pid = 0x0367
elseif packet_version >= 20171123 then
	local pid = 0x0367
elseif packet_version >= 20171115 then
	local pid = 0x0367
elseif packet_version >= 20171018 then
	local pid = 0x0367
elseif packet_version >= 20170621 then
	local pid = 0x0367
elseif packet_version >= 20170614 then
	local pid = 0x0367
elseif packet_version >= 20170524 then
	local pid = 0x0367
elseif packet_version >= 20170517 then
	local pid = 0x0367
elseif packet_version >= 20170322 then
	local pid = 0x0367
elseif packet_version >= 20170315 then
	local pid = 0x0367
elseif packet_version >= 20170215 then
	local pid = 0x0367
elseif packet_version >= 20170208 then
	local pid = 0x0367
elseif packet_version >= 20170104 then
	local pid = 0x0367
elseif packet_version >= 20161109 then
	local pid = 0x0367
elseif packet_version >= 20161102 then
	local pid = 0x0367
elseif packet_version >= 20160309 then
	local pid = 0x0367
elseif packet_version >= 20160302 then
	local pid = 0x0367
elseif packet_version >= 20160106 then
	local pid = 0x0367
elseif packet_version >= 20150909 then
	local pid = 0x0367
elseif packet_version >= 20150902 then
	local pid = 0x0367
elseif packet_version >= 20150408 then
	local pid = 0x0367
elseif packet_version >= 20150401 then
	local pid = 0x0367
elseif packet_version >= 20150325 then
	local pid = 0x0367
elseif packet_version >= 20150318 then
	local pid = 0x0367
elseif packet_version >= 20150225 then
	local pid = 0x0367
elseif packet_version >= 20150107 then
	local pid = 0x0367
elseif packet_version >= 20141210 then
	local pid = 0x0367
elseif packet_version >= 20141203 then
	local pid = 0x0367
elseif packet_version >= 20141126 then
	local pid = 0x0367
elseif packet_version >= 20141001 then
	local pid = 0x0367
elseif packet_version >= 20140924 then
	local pid = 0x0367
elseif packet_version >= 20140917 then
	local pid = 0x0367
elseif packet_version >= 20140806 then
	local pid = 0x0367
elseif packet_version >= 20140730 then
	local pid = 0x0367
elseif packet_version >= 20140611 then
	local pid = 0x0367
elseif packet_version >= 20140508 then
	local pid = 0x0367
elseif packet_version >= 20140205 then
	local pid = 0x0367
elseif packet_version >= 20140129 then
	local pid = 0x0367
elseif packet_version >= 20140122 then
	local pid = 0x0367
elseif packet_version >= 20140115 then
	local pid = 0x0367
elseif packet_version >= 20140108 then
	local pid = 0x0367
elseif packet_version >= 20131223 then
	local pid = 0x0367
elseif packet_version >= 20130417 then
	local pid = 0x0367
elseif packet_version >= 20130410 then
	local pid = 0x0367
elseif packet_version >= 20130313 then
	local pid = 0x0367
elseif packet_version >= 20130306 then
	local pid = 0x0367
elseif packet_version >= 20130206 then
	local pid = 0x0367
elseif packet_version >= 20130130 then
	local pid = 0x0367
elseif packet_version >= 20130103 then
	local pid = 0x0367
elseif packet_version >= 20120716 then
	local pid = 0x0367
elseif packet_version >= 20120710 then
	local pid = 0x0367
elseif packet_version >= 20120314 then
	local pid = 0x0367
elseif packet_version >= 20120307 then
	local pid = 0x0367
elseif packet_version >= 20120207 then
	local pid = 0x0367
elseif packet_version >= 20120131 then
	local pid = 0x0367
elseif packet_version >= 20120120 then
	local pid = 0x0367
elseif packet_version >= 20120117 then
	local pid = 0x0367
elseif packet_version >= 20120110 then
	local pid = 0x0367
elseif packet_version >= 20120103 then
	local pid = 0x0367
elseif packet_version >= 20111220 then
	local pid = 0x0367
elseif packet_version >= 20111213 then
	local pid = 0x0367
elseif packet_version >= 20111207 then
	local pid = 0x0367
elseif packet_version >= 20111122 then
	local pid = 0x0367
elseif packet_version >= 20111101 then
	local pid = 0x0367
elseif packet_version >= 20111025 then
	local pid = 0x0367
elseif packet_version >= 20111017 then
	local pid = 0x0367
elseif packet_version >= 20111010 then
	local pid = 0x0367
elseif packet_version >= 20111004 then
	local pid = 0x0367
elseif packet_version >= 20110906 then
	local pid = 0x0367
elseif packet_version >= 20110831 then
	local pid = 0x0367
elseif packet_version >= 20110816 then
	local pid = 0x0367
elseif packet_version >= 20110809 then
	local pid = 0x0367
elseif packet_version >= 20110802 then
	local pid = 0x0367
elseif packet_version >= 20110726 then
	local pid = 0x0367
elseif packet_version >= 20110718 then
	local pid = 0x0367
elseif packet_version >= 20110627 then
	local pid = 0x0367
elseif packet_version >= 20110620 then
	local pid = 0x0367
elseif packet_version >= 20110614 then
	local pid = 0x0367
elseif packet_version >= 20110531 then
	local pid = 0x0367
elseif packet_version >= 20110523 then
	local pid = 0x0367
elseif packet_version >= 20110517 then
	local pid = 0x0367
elseif packet_version >= 20110419 then
	local pid = 0x0367
elseif packet_version >= 20110405 then
	local pid = 0x0367
elseif packet_version >= 20110329 then
	local pid = 0x0367
elseif packet_version >= 20110322 then
	local pid = 0x0367
elseif packet_version >= 20110315 then
	local pid = 0x0367
elseif packet_version >= 20110131 then
	local pid = 0x0367
elseif packet_version >= 20110125 then
	local pid = 0x0367
elseif packet_version >= 20110118 then
	local pid = 0x0367
elseif packet_version >= 20110111 then
	local pid = 0x0367
elseif packet_version >= 20110104 then
	local pid = 0x0367
elseif packet_version >= 20101228 then
	local pid = 0x0367
elseif packet_version >= 20101221 then
	local pid = 0x0367
elseif packet_version >= 20101123 then
	local pid = 0x0367
elseif packet_version >= 20100105 then
	local pid = 0x0367
elseif packet_version >= 20090406 then
	local pid = 0x0367
elseif packet_version >= 20090401 then
	local pid = 0x0367
elseif packet_version >= 20090325 then
	local pid = 0x0367
elseif packet_version >= 20090318 then
	local pid = 0x0367
elseif packet_version >= 20090218 then
	local pid = 0x0367
elseif packet_version >= 20090211 then
	local pid = 0x0367
elseif packet_version >= 20090204 then
	local pid = 0x0367
elseif packet_version >= 20090129 then
	local pid = 0x0367
elseif packet_version >= 20090107 then
	local pid = 0x0367
elseif packet_version >= 20081217 then
	local pid = 0x0367
elseif packet_version >= 20081105 then
	local pid = 0x0367
elseif packet_version >= 20081029 then
	local pid = 0x0367
elseif packet_version >= 20081022 then
	local pid = 0x0367
elseif packet_version >= 20081015 then
	local pid = 0x0367
elseif packet_version >= 20081001 then
	local pid = 0x0367
elseif packet_version >= 20080924 then
	local pid = 0x0367
elseif packet_version >= 20080917 then
	local pid = 0x0367
elseif packet_version >= 20080910 then
	local pid = 0x0367
elseif packet_version >= 20080827 then
	local pid = 0x0367
elseif packet_version >= 20080820 then
	local pid = 0x0367
elseif packet_version >= 20080813 then
	local pid = 0x0367
elseif packet_version >= 20080708 then
	local pid = 0x0367
elseif packet_version >= 20080624 then
	local pid = 0x0367
elseif packet_version >= 20080618 then
	local pid = 0x0367
elseif packet_version >= 20080617 then
	local pid = 0x0367
elseif packet_version >= 20080528 then
	local pid = 0x0367
elseif packet_version >= 20080527 then
	local pid = 0x0367
elseif packet_version >= 0 then
	local pid = 0x0367
end

local CZ_USE_SKILL_TOGROUND_WITHTALKBOX2 = {
	_id = pid,
	_length = 0,
	_buffer = nil
}


function CZ_USE_SKILL_TOGROUND_WITHTALKBOX2.new(o)
	o = o or CZ_USE_SKILL_TOGROUND_WITHTALKBOX2
	setmetatable(o, self)
	self.__index = self
	return o
end

function CZ_USE_SKILL_TOGROUND_WITHTALKBOX2.deserialize(buf)

end

return CZ_USE_SKILL_TOGROUND_WITHTALKBOX2

