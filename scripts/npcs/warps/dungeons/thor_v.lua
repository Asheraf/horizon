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
--- Thor_v Warp Definitions File.
---------------------------------------------------------------------------

Warp("thor_v1-1", "ve_fild03", 168, 240, "s:move_to_map('thor_v01', 21, 229)", 2)
Warp("thor_v1-2", "thor_v01", 21, 224, "s:move_to_map('ve_fild03', 168, 235)", 2)
Warp("thor_v2-1", "thor_v01", 201, 37, "s:move_to_map('thor_v02', 78, 203)", 2)
Warp("thor_v2-2", "thor_v02", 192, 60, "s:move_to_map('thor_v03', 35, 262)", 2)
Warp("thor_v3-1", "thor_v02", 73, 203, "s:move_to_map('thor_v01', 196, 37)", 2)
Warp("thor_v3-2", "thor_v03", 30, 262, "s:move_to_map('thor_v02', 187, 58)", 2)
