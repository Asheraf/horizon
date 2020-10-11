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
package.path = package.path .. ";./scripts/common/packets/sakray/?.lua"
package.path = package.path .. ";./scripts/common/packets/re/?.lua"
package.path = package.path .. ";./scripts/common/packets/zero/?.lua"
package.path = package.path .. ";./scripts/common/packets/ragexe/?.lua"
package.path = package.path .. ";./scripts/common/packets/ad/?.lua"
package.path = package.path .. ";./scripts/common/packets/structs/?.lua"

package.path = package.path .. ";./scripts/common/libs/?.lua"

package.path = package.path .. ";./scripts/lua_modules/share/lua/5.3/?.lua"

package.path = package.path .. ";./config/?.lua"

-- Initializing global variable
-- Ensures that modules are running within project directory and not standalone.
RAGNA_ROOT = true

common_config = require('common-server')
struct = require('struct')

local packet_tables = {
	['sakray'] = {
		[20080624] = require("20080624_packets_sakray"),
	},
	['re'] = {
		[20130605] = require("20130605_packets_re"),
		[20130612] = require("20130612_packets_re"),
		[20131030] = require("20131030_packets_re"),
	},
	['zero'] = {
	},
	['ragexe'] = {
		[20080624] = require("20080624_packets_ragexe"),
		[20130605] = require("20130605_packets_ragexe"),
		[20130612] = require("20130612_packets_ragexe"),
		[20131030] = require("20131030_packets_ragexe"),
	},
	['ad'] = {
		[20080624] = require("20080624_packets_ad"),
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

print("Ragnarok LUA scripts have been initialized for the 'common' server.")

return packet_tables
