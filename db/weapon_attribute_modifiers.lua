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
--- Weapon Attribute modifiers
---------------------------------------------------------------------------
weapon_attribute_modifiers = {
	[1] = {
				 -- Neut Watr Erth Fire Wind Pois Holy Dark Gho  Und
		Neutral = { 100, 100, 100, 100, 100, 100, 100, 100,  70, 100 },
		Water   = { 100,  25, 100, 150,  90, 100,  75, 100, 100, 100 },
		Earth   = { 100, 100,  25,  90, 150, 100,  75, 100, 100, 100 },
		Fire    = { 100,  90, 150,  25, 100, 100,  75, 100, 100, 125 },
		Wind    = { 100, 175,  90, 100,  25, 100,  75, 100, 100, 100 },
		Poison  = { 100, 100, 125, 125, 125,   0,  75,  50, 100, -25 },
		Holy    = { 100, 100, 100, 100, 100, 100,   0, 125, 100, 150 },
		Dark    = { 100, 100, 100, 100, 100,  50, 125,   0, 100, -25 },
		Ghost   = {  70, 100, 100, 100, 100, 100,  75,  75, 125, 100 },
		Undead  = { 100, 100, 100, 100, 100,  50, 100,   0, 100,   0 }
	},
	[2] = {
				 -- Neut Watr Erth Fire Wind Pois Holy Dark Gho  Und
		Neutral = { 100, 100, 100, 100, 100, 100, 100, 100,  50, 100 },
		Water   = { 100,   0, 100, 175,  80, 100,  50,  75, 100, 100 },
		Earth   = { 100, 100,   0,  80, 175, 100,  50,  75, 100, 100 },
		Fire    = { 100,  80, 175,   0, 100, 100,  50,  75, 100, 150 },
		Wind    = { 100, 175,  80, 100,   0, 100,  50,  75, 100, 100 },
		Poison  = { 100,  75, 125, 125, 125,   0,  50,  25,  75, -50 },
		Holy    = { 100, 100, 100, 100, 100, 100, -25, 150, 100, 175 },
		Dark    = { 100, 100, 100, 100, 100,  25, 150, -25, 100, -50 },
		Ghost   = {  50,  75,  75,  75,  75,  75,  50,  50, 150, 125 },
		Undead  = { 100,  75,  75,  75,  75,  25, 125,   0, 100,   0 }
	},
	[3] = {
				 -- Neut Watr Erth Fire Wind Pois Holy Dark Gho  Und
		Neutral = { 100, 100, 100, 100, 100, 100, 100, 100,   0, 100 },
		Water   = { 100, -25, 100, 200,  70, 100,  25,  50, 100, 125 },
		Earth   = { 100, 100, -25,  70, 200, 100,  25,  50, 100, 100 },
		Fire    = { 100,  70, 200, -25, 100, 100,  25,  50, 100, 175 },
		Wind    = { 100, 200,  70, 100, -25, 100,  25,  50, 100, 100 },
		Poison  = { 100,  50, 100, 100, 100,   0,  25,   0,  50, -75 },
		Holy    = { 100, 100, 100, 100, 100, 125, -50, 175, 100, 200 },
		Dark    = { 100, 100, 100, 100, 100,   0, 175, -50, 100, -75 },
		Ghost   = {   0,  50,  50,  50,  50,  50,  25,  25, 175, 150 },
		Undead  = { 100,  50,  50,  50,  50,   0, 150,   0, 100,   0 }
	},
	[4] = {
				 -- Neut Watr Erth Fire Wind Pois Holy Dark Gho  Und
		Neutral = { 100, 100, 100, 100, 100, 100, 100, 100,   0, 100 },
		Water   = { 100, -50, 100, 200,  60,  75,   0,  25, 100, 150 },
		Earth   = { 100, 100, -50,  60, 200,  75,   0,  25, 100,  50 },
		Fire    = { 100,  60, 200, -50, 100,  75,   0,  25, 100, 200 },
		Wind    = { 100, 200,  60, 100, -50,  75,   0,  25, 100, 100 },
		Poison  = { 100,  25,  75,  75,  75,   0,   0, -25,  25,-100 },
		Holy    = { 100,  75,  75,  75,  75, 125,-100, 200, 100, 200 },
		Dark    = { 100,  75,  75,  75,  75, -25, 200,-100, 100,-100 },
		Ghost   = {   0,  25,  25,  25,  25,  25,   0,   0, 200, 175 },
		Undead  = { 100,  25,  25,  25,  25, -25, 175,   0, 100,   0 }
	},
	-- Aegis PVP attributes (Unused as they're same as Lv 1).
	[5] = {
				 -- Neut Watr Erth Fire Wind Pois Holy Dark Gho  Und
		Neutral = { 100, 100, 100, 100, 100, 100, 100, 100,  70, 100 },
		Water   = { 100,  25, 100, 150,  90, 100,  75, 100, 100, 100 },
		Earth   = { 100, 100,  25,  90, 150, 100,  75, 100, 100, 100 },
		Fire    = { 100,  90, 150,  25, 100, 100,  75, 100, 100, 125 },
		Wind    = { 100, 175,  90, 100,  25, 100,  75, 100, 100, 100 },
		Poison  = { 100, 100, 125, 125, 125,   0,  75,  50, 100, -25 },
		Holy    = { 100, 100, 100, 100, 100, 100,   0, 125, 100, 150 },
		Dark    = { 100, 100, 100, 100, 100,  50, 125,   0, 100, -25 },
		Ghost   = {  70, 100, 100, 100, 100, 100,  75,  75, 125, 100 },
		Undead  = { 100, 100, 100, 100, 100,  50, 100,   0, 100,   0 }
	},
}

