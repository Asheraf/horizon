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

-- Package paths (defined relative to the root directory of server execution)
package.path = package.path .. ";./scripts/auth/packets/sakray/?.lua"
package.path = package.path .. ";./scripts/auth/packets/re/?.lua"
package.path = package.path .. ";./scripts/auth/packets/zero/?.lua"
package.path = package.path .. ";./scripts/auth/packets/ragexe/?.lua"
package.path = package.path .. ";./scripts/auth/packets/ad/?.lua"
package.path = package.path .. ";./scripts/auth/packets/structs/?.lua"

package.path = package.path .. ";./scripts/auth/libs/?.lua"

package.path = package.path .. ";./scripts/lua_modules/share/lua/5.3/?.lua"

package.path = package.path .. ";./config/?.lua"

-- Initializing global variable
-- Ensures that modules are running within project directory and not standalone.
RAGNA_ROOT = true

auth_config = require('auth-server')
struct = require('struct')

local packet_tables = {
	['sakray'] = {
		[20031223] = require("20031223_packets_sakray"),
		[20040322] = require("20040322_packets_sakray"),
		[20040517] = require("20040517_packets_sakray"),
		[20040531] = require("20040531_packets_sakray"),
		[20050628] = require("20050628_packets_sakray"),
		[20050912] = require("20050912_packets_sakray"),
		[20060109] = require("20060109_packets_sakray"),
		[20060126] = require("20060126_packets_sakray"),
		[20060424] = require("20060424_packets_sakray"),
		[20060626] = require("20060626_packets_sakray"),
		[20060731] = require("20060731_packets_sakray"),
		[20060821] = require("20060821_packets_sakray"),
		[20070227] = require("20070227_packets_sakray"),
		[20070514] = require("20070514_packets_sakray"),
		[20080102] = require("20080102_packets_sakray"),
		[20080715] = require("20080715_packets_sakray"),
		[20080722] = require("20080722_packets_sakray"),
	},
	['re'] = {
		[20090701] = require("20090701_packets_re"),
		[20100413] = require("20100413_packets_re"),
		[20100601] = require("20100601_packets_re"),
		[20100615] = require("20100615_packets_re"),
		[20101228] = require("20101228_packets_re"),
		[20110706] = require("20110706_packets_re"),
		[20110726] = require("20110726_packets_re"),
		[20111025] = require("20111025_packets_re"),
		[20120612] = require("20120612_packets_re"),
		[20120626] = require("20120626_packets_re"),
		[20120702] = require("20120702_packets_re"),
		[20120716] = require("20120716_packets_re"),
		[20130103] = require("20130103_packets_re"),
		[20130115] = require("20130115_packets_re"),
		[20130130] = require("20130130_packets_re"),
		[20130220] = require("20130220_packets_re"),
		[20130605] = require("20130605_packets_re"),
		[20170228] = require("20170228_packets_re"),
		[20170614] = require("20170614_packets_re"),
		[20170621] = require("20170621_packets_re"),
		[20170705] = require("20170705_packets_re"),
		[20171115] = require("20171115_packets_re"),
		[20171213] = require("20171213_packets_re"),
		[20180704] = require("20180704_packets_re"),
	},
	['zero'] = {
		[20171018] = require("20171018_packets_zero"),
		[20171113] = require("20171113_packets_zero"),
		[20171123] = require("20171123_packets_zero"),
		[20180627] = require("20180627_packets_zero"),
	},
	['ragexe'] = {
		[20031223] = require("20031223_packets_ragexe"),
		[20040322] = require("20040322_packets_ragexe"),
		[20040517] = require("20040517_packets_ragexe"),
		[20040531] = require("20040531_packets_ragexe"),
		[20050628] = require("20050628_packets_ragexe"),
		[20050912] = require("20050912_packets_ragexe"),
		[20060109] = require("20060109_packets_ragexe"),
		[20060126] = require("20060126_packets_ragexe"),
		[20060424] = require("20060424_packets_ragexe"),
		[20060626] = require("20060626_packets_ragexe"),
		[20060731] = require("20060731_packets_ragexe"),
		[20060821] = require("20060821_packets_ragexe"),
		[20070227] = require("20070227_packets_ragexe"),
		[20070514] = require("20070514_packets_ragexe"),
		[20080102] = require("20080102_packets_ragexe"),
		[20080715] = require("20080715_packets_ragexe"),
		[20080722] = require("20080722_packets_ragexe"),
		[20090701] = require("20090701_packets_ragexe"),
		[20100413] = require("20100413_packets_ragexe"),
		[20100601] = require("20100601_packets_ragexe"),
		[20100615] = require("20100615_packets_ragexe"),
		[20101228] = require("20101228_packets_ragexe"),
		[20110705] = require("20110705_packets_ragexe"),
		[20110726] = require("20110726_packets_ragexe"),
		[20111025] = require("20111025_packets_ragexe"),
		[20120612] = require("20120612_packets_ragexe"),
		[20120626] = require("20120626_packets_ragexe"),
		[20120702] = require("20120702_packets_ragexe"),
		[20120716] = require("20120716_packets_ragexe"),
		[20130103] = require("20130103_packets_ragexe"),
		[20130115] = require("20130115_packets_ragexe"),
		[20130130] = require("20130130_packets_ragexe"),
		[20130220] = require("20130220_packets_ragexe"),
		[20130605] = require("20130605_packets_ragexe"),
		[20170228] = require("20170228_packets_ragexe"),
		[20170614] = require("20170614_packets_ragexe"),
		[20170621] = require("20170621_packets_ragexe"),
		[20170705] = require("20170705_packets_ragexe"),
		[20171115] = require("20171115_packets_ragexe"),
		[20171213] = require("20171213_packets_ragexe"),
		[20180704] = require("20180704_packets_ragexe"),
	},
	['ad'] = {
		[20050628] = require("20050628_packets_ad"),
		[20050912] = require("20050912_packets_ad"),
		[20060109] = require("20060109_packets_ad"),
		[20060126] = require("20060126_packets_ad"),
		[20060424] = require("20060424_packets_ad"),
		[20060626] = require("20060626_packets_ad"),
		[20060731] = require("20060731_packets_ad"),
		[20060821] = require("20060821_packets_ad"),
		[20070227] = require("20070227_packets_ad"),
		[20070514] = require("20070514_packets_ad"),
	},
}

function get_packet_table(client, packet_version)
	local tkeys = {}
	
	for k in pairs(packet_tables[client]) do 
		table.insert(tkeys, k) 
	end

	-- sort the keys
	table.sort(tkeys, 
		function (a, b) 
			return a > b 
		end
	)

	-- use the keys to retrieve the values in the sorted order
	for _, k in ipairs(tkeys) do 
		if tonumber(packet_version) >= k then 
			return packet_tables[client][k]
		end
	end
end

print("Ragnarok LUA scripts have been initialized for the 'auth' server.")

return packet_tables
