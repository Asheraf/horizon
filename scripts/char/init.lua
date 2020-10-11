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
package.path = package.path .. ";./scripts/char/packets/sakray/?.lua"
package.path = package.path .. ";./scripts/char/packets/re/?.lua"
package.path = package.path .. ";./scripts/char/packets/zero/?.lua"
package.path = package.path .. ";./scripts/char/packets/ragexe/?.lua"
package.path = package.path .. ";./scripts/char/packets/ad/?.lua"
package.path = package.path .. ";./scripts/char/packets/structs/?.lua"

package.path = package.path .. ";./scripts/char/libs/?.lua"

package.path = package.path .. ";./scripts/lua_modules/share/lua/5.3/?.lua"

package.path = package.path .. ";./config/?.lua"

-- Initializing global variable
-- Ensures that modules are running within project directory and not standalone.
RAGNA_ROOT = true

char_config = require('char-server')
struct = require('struct')

local packet_tables = {
	['sakray'] = {
		[20040419] = require("20040419_packets_sakray"),
		[20040621] = require("20040621_packets_sakray"),
		[20050628] = require("20050628_packets_sakray"),
		[20060102] = require("20060102_packets_sakray"),
		[20061023] = require("20061023_packets_sakray"),
		[20061207] = require("20061207_packets_sakray"),
		[20070821] = require("20070821_packets_sakray"),
		[20090225] = require("20090225_packets_sakray"),
	},
	['re'] = {
		[20080827] = require("20080827_packets_re"),
		[20081217] = require("20081217_packets_re"),
		[20090226] = require("20090226_packets_re"),
		[20090701] = require("20090701_packets_re"),
		[20090825] = require("20090825_packets_re"),
		[20090922] = require("20090922_packets_re"),
		[20100105] = require("20100105_packets_re"),
		[20100713] = require("20100713_packets_re"),
		[20100714] = require("20100714_packets_re"),
		[20100720] = require("20100720_packets_re"),
		[20100728] = require("20100728_packets_re"),
		[20100803] = require("20100803_packets_re"),
		[20101012] = require("20101012_packets_re"),
		[20101221] = require("20101221_packets_re"),
		[20101228] = require("20101228_packets_re"),
		[20110104] = require("20110104_packets_re"),
		[20110111] = require("20110111_packets_re"),
		[20110215] = require("20110215_packets_re"),
		[20110222] = require("20110222_packets_re"),
		[20110228] = require("20110228_packets_re"),
		[20110308] = require("20110308_packets_re"),
		[20110906] = require("20110906_packets_re"),
		[20110920] = require("20110920_packets_re"),
		[20110928] = require("20110928_packets_re"),
		[20111017] = require("20111017_packets_re"),
		[20111025] = require("20111025_packets_re"),
		[20111101] = require("20111101_packets_re"),
		[20111207] = require("20111207_packets_re"),
		[20120214] = require("20120214_packets_re"),
		[20120724] = require("20120724_packets_re"),
		[20121024] = require("20121024_packets_re"),
		[20121128] = require("20121128_packets_re"),
		[20121212] = require("20121212_packets_re"),
		[20130103] = require("20130103_packets_re"),
		[20130327] = require("20130327_packets_re"),
		[20130522] = require("20130522_packets_re"),
		[20140108] = require("20140108_packets_re"),
		[20140625] = require("20140625_packets_re"),
		[20150211] = require("20150211_packets_re"),
		[20150415] = require("20150415_packets_re"),
		[20170104] = require("20170104_packets_re"),
		[20170228] = require("20170228_packets_re"),
		[20170830] = require("20170830_packets_re"),
		[20171220] = require("20171220_packets_re"),
		[20180103] = require("20180103_packets_re"),
		[20180117] = require("20180117_packets_re"),
	},
	['zero'] = {
		[20171220] = require("20171220_packets_zero"),
		[20180103] = require("20180103_packets_zero"),
		[20180117] = require("20180117_packets_zero"),
	},
	['ragexe'] = {
		[20040419] = require("20040419_packets_ragexe"),
		[20040621] = require("20040621_packets_ragexe"),
		[20050628] = require("20050628_packets_ragexe"),
		[20060102] = require("20060102_packets_ragexe"),
		[20061030] = require("20061030_packets_ragexe"),
		[20061207] = require("20061207_packets_ragexe"),
		[20070821] = require("20070821_packets_ragexe"),
		[20090107] = require("20090107_packets_ragexe"),
		[20090225] = require("20090225_packets_ragexe"),
		[20090617] = require("20090617_packets_ragexe"),
		[20090701] = require("20090701_packets_ragexe"),
		[20090825] = require("20090825_packets_ragexe"),
		[20090922] = require("20090922_packets_ragexe"),
		[20100105] = require("20100105_packets_ragexe"),
		[20100713] = require("20100713_packets_ragexe"),
		[20100714] = require("20100714_packets_ragexe"),
		[20100720] = require("20100720_packets_ragexe"),
		[20100727] = require("20100727_packets_ragexe"),
		[20100728] = require("20100728_packets_ragexe"),
		[20100803] = require("20100803_packets_ragexe"),
		[20101012] = require("20101012_packets_ragexe"),
		[20101221] = require("20101221_packets_ragexe"),
		[20101228] = require("20101228_packets_ragexe"),
		[20110104] = require("20110104_packets_ragexe"),
		[20110111] = require("20110111_packets_ragexe"),
		[20110215] = require("20110215_packets_ragexe"),
		[20110222] = require("20110222_packets_ragexe"),
		[20110228] = require("20110228_packets_ragexe"),
		[20110308] = require("20110308_packets_ragexe"),
		[20110906] = require("20110906_packets_ragexe"),
		[20110920] = require("20110920_packets_ragexe"),
		[20110928] = require("20110928_packets_ragexe"),
		[20111017] = require("20111017_packets_ragexe"),
		[20111101] = require("20111101_packets_ragexe"),
		[20111207] = require("20111207_packets_ragexe"),
		[20120214] = require("20120214_packets_ragexe"),
		[20120724] = require("20120724_packets_ragexe"),
		[20121024] = require("20121024_packets_ragexe"),
		[20121128] = require("20121128_packets_ragexe"),
		[20121212] = require("20121212_packets_ragexe"),
		[20130522] = require("20130522_packets_ragexe"),
		[20140108] = require("20140108_packets_ragexe"),
		[20140820] = require("20140820_packets_ragexe"),
		[20150211] = require("20150211_packets_ragexe"),
		[20150415] = require("20150415_packets_ragexe"),
		[20170104] = require("20170104_packets_ragexe"),
		[20170228] = require("20170228_packets_ragexe"),
		[20170906] = require("20170906_packets_ragexe"),
		[20171220] = require("20171220_packets_ragexe"),
		[20180103] = require("20180103_packets_ragexe"),
		[20180117] = require("20180117_packets_ragexe"),
	},
	['ad'] = {
		[20050628] = require("20050628_packets_ad"),
		[20060102] = require("20060102_packets_ad"),
		[20061030] = require("20061030_packets_ad"),
		[20061207] = require("20061207_packets_ad"),
		[20070821] = require("20070821_packets_ad"),
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

print("Ragnarok LUA scripts have been initialized for the 'char' server.")

return packet_tables
