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
--- Anthell Warp Definitions File.
---------------------------------------------------------------------------

Warp("moc_ant1-1", "cmd_fild08", 335, 355, "s:move_to_map('anthell01', 35, 262)", 2)
Warp("moc_ant1-2", "anthell01", 35, 267, "s:move_to_map('cmd_fild08', 330, 355)", 2)
Warp("moc_ant2-1", "cmd_fild08", 348, 82, "s:move_to_map('anthell02', 168, 170)", 2)
Warp("moc_ant2-2", "anthell02", 172, 169, "s:move_to_map('cmd_fild08', 344, 82)", 2)
Warp("ant01", "anthell01", 253, 32, "s:move_to_map('anthell02', 34, 263)", 2)
Warp("ant01-1", "anthell02", 32, 267, "s:move_to_map('anthell01', 253, 35)", 2)
