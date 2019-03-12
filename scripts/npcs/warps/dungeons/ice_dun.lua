---------------------------------------------------------------------------
--       _   _            _                        --
--      | | | |          (_)                       --
--      | |_| | ___  _ __ _ _______  _ __          --
--      |  _  |/ _ \| '__| |_  / _ \| '_  \        --
--      | | | | (_) | |  | |/ / (_) | | | |        --
--      \_| |_/\___/|_|  |_/___\___/|_| |_|        --
---------------------------------------------------------------------------
-- This file is part of Horizon (c).
-- Copyright (c) 2018 Horizon Dev Team.
--
-- Base Author - Sagun K. (sagunxp@gmail.com)
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
---------------------------------------------------------------------------
--- Ice_dun Warp Definitions File.
---------------------------------------------------------------------------

Warp("ice001", "ice_dun01", 157, 10, "s:move_to_map('ra_fild01', 233, 327)", 2)
Warp("ice002", "ice_dun01", 146, 161, "s:move_to_map('ice_dun02', 151, 139)", 2)
Warp("ice003", "ice_dun02", 151, 145, "s:move_to_map('ice_dun01', 146, 157)", 2)
Warp("ice004", "ice_dun02", 150, 285, "s:move_to_map('ice_dun03', 149, 24)", 2)
Warp("ice005", "ice_dun03", 149, 19, "s:move_to_map('ice_dun02', 150, 280)", 2)
Warp("ice006", "ice_dun04", 33, 140, "s:move_to_map('ice_dun03', 149, 130)", 2)
