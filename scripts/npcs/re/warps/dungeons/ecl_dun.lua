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
--- Ecl_dun Warp Definitions File.
---------------------------------------------------------------------------

Warp("Tenter_TOut", "ecl_fild01", 182, 82, "s:move_to_map('ecl_tdun01', 60, 13)", 2)
Warp("TOut_Tenter", "ecl_tdun01", 61, 11, "s:move_to_map('ecl_fild01', 182, 85)", 2)
Warp("tdun1up_tdun2dn", "ecl_tdun01", 67, 106, "s:move_to_map('ecl_tdun02', 60, 88)", 2)
Warp("tdun2dn_tdun1up", "ecl_tdun02", 60, 90, "s:move_to_map('ecl_tdun01', 70, 105)", 2)
Warp("tdun2up_tdun3dn", "ecl_tdun02", 52, 9, "s:move_to_map('ecl_tdun03', 47, 13)", 2)
Warp("tdun3dn_tdun2up", "ecl_tdun03", 49, 11, "s:move_to_map('ecl_tdun02', 50, 11)", 2)
Warp("tdun3up_tdun4dn", "ecl_tdun03", 50, 46, "s:move_to_map('ecl_tdun04', 26, 24)", 2)
Warp("tdun4dn_tdun3up", "ecl_tdun04", 26, 26, "s:move_to_map('ecl_tdun03', 50, 44)", 2)
Warp("tdun4-1_ttop", "ecl_tdun04", 34, 17, "s:move_to_map('ecl_fild01', 183, 73)", 2)
Warp("ttop_tdun4-1", "ecl_fild01", 183, 70, "s:move_to_map('ecl_tdun04', 33, 19)", 2)
