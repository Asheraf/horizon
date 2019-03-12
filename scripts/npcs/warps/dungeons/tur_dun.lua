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
--- Tur_dun Warp Definitions File.
---------------------------------------------------------------------------

Warp("ttl01", "tur_dun01", 154, 241, "s:move_to_map('tur_dun02', 148, 264)", 2)
Warp("ttl01-1", "tur_dun02", 148, 268, "s:move_to_map('tur_dun01', 154, 237)", 2)
Warp("ttl02", "tur_dun02", 167, 19, "s:move_to_map('tur_dun03', 132, 189)", 2)
Warp("ttl02-1", "tur_dun03", 132, 193, "s:move_to_map('tur_dun02', 167, 23)", 2)
Warp("ttl03", "tur_dun03", 217, 71, "s:move_to_map('tur_dun04', 100, 192)", 2)
Warp("ttl03-1", "tur_dun04", 100, 196, "s:move_to_map('tur_dun03', 215, 75)", 2)
Warp("ttl05", "tur_dun05", 89, 69, "s:move_to_map('tur_dun02', 148, 264)", 2)
Warp("ttl06", "tur_dun05", 9, 45, "s:move_to_map('tur_dun01', 154, 237)", 2)
