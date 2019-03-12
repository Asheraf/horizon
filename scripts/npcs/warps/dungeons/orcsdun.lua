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
--- Orcsdun Warp Definitions File.
---------------------------------------------------------------------------

Warp("orc001", "in_orcs01", 108, 86, "s:move_to_map('gef_fild10', 223, 203)", 2)
Warp("orc002", "in_orcs01", 124, 171, "s:move_to_map('gef_fild10', 138, 329)", 2)
Warp("orc003", "in_orcs01", 162, 55, "s:move_to_map('gef_fild10', 214, 53)", 2)
Warp("orc004", "in_orcs01", 29, 116, "s:move_to_map('gef_fild10', 137, 286)", 2)
Warp("orc005", "in_orcs01", 30, 154, "s:move_to_map('gef_fild10', 65, 335)", 2)
Warp("orc01", "in_orcs01", 30, 182, "s:move_to_map('orcsdun01', 32, 170)", 2)
Warp("orc01-1", "orcsdun01", 32, 172, "s:move_to_map('in_orcs01', 30, 180)", 2)
Warp("orc02", "in_orcs01", 108, 114, "s:move_to_map('orcsdun02', 180, 17)", 2)
Warp("orc02-1", "orcsdun02", 180, 15, "s:move_to_map('in_orcs01', 108, 112)", 2)
Warp("orc03", "orcsdun01", 183, 8, "s:move_to_map('orcsdun02', 21, 185)", 2)
Warp("orc03-1", "orcsdun02", 21, 188, "s:move_to_map('orcsdun01', 183, 11)", 2)
