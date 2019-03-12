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
--- Ama_dun Warp Definitions File.
---------------------------------------------------------------------------

Warp("ama_dun1-1", "ama_dun01", 235, 144, "s:move_to_map('ama_dun02', 33, 40)", 2)
Warp("ama_dun1-2", "ama_dun02", 30, 40, "s:move_to_map('ama_dun01', 232, 144)", 2)
Warp("ama_dun2-1", "ama_dun02", 196, 123, "s:move_to_map('ama_dun03', 120, 12)", 2)
Warp("ama_dun2-2", "ama_dun03", 120, 9, "s:move_to_map('ama_dun02', 196, 120)", 2)
