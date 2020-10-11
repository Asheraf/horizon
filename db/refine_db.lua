---------------------------------------------------------------------------
--       _   _            _                                              --
--      | | | |          (_)                                             --
--      | |_| | ___  _ __ _ _______  _ __                                --
--      |  _  |/ _ \| '__| |_  / _ \| '_  \                              --
--      | | | | (_) | |  | |/ / (_) | | | |                              --
--      \_| |_/\___/|_|  |_/___\___/|_| |_|                              --
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
--- Renewal Refine Database.
---------------------------------------------------------------------------
---------------------------------------------------------------------------
--------------------- Entry Structure -------------------------------------
---------------------------------------------------------------------------
-- Armors|WeaponLevel1~4 = {                                       -- Specifies weapon level or armor type.
-- 															   -- - For armors, values of 100 add 1 armor defense.
-- 															   -- - For weapons, values of 100 add 1 ATK & MATK.
-- 	StatsPerLevel = (int)                                       -- This value is applied for ever level.
-- 	RandomBonusStartLevel = (int)                               -- This value specifies the start point for those levels that give a random bonus value (usually the first unsafe upgrade).
-- 															   -- - RandomBonusStartLevel is only applied for weapons, and not displayed client-side.
-- 	RandomBonusValue = (int)                                    -- A random number between 0 and (Random bonus start level - Upgrade level + 1) * this value is applied for all upgrades past.
-- 	Rates = {                                                   -- Per level configuration of the refine rates.
-- 		Lv1~20 = {                                              -- Lv1 ~ Lv20.
-- 			NormalChance = (int)                                -- (optional, defaults to 100) Chance of successful refine using normal ores (100 = 100%).
-- 			EnrichedChance = (int)                              -- (optional, defaults to 100 for weapons below refine level 20, otherwise 0.) Chance of successful refine using enriched ores (100 = 100%).
-- 			EventNormalChance = (int)                           -- (optional, defaults to 100) Chance of successful refine using normal ores (100 = 100%) during a refine event.
-- 			EventEnrichedChance = (int)                         -- (optional, defaults to 100 for weapons below refine level 10, otherwise 0.) Chance of successful refine using enriched ores (100 = 100%) during a refine event.
-- 			Bonus = (int)                                       -- (optional, defaults to 0) Bonus (Armor) for this level of refine.
-- 		},
-- 		-- Note = Refine levels that use default values need not be listed. (Example = [1] = { NormalChance = 100 Bonus = 0 },)
-- 	},
-- },
---------------------------------------------------------------------------

Armors = {
	StatsPerLevel = 0,
	RandomBonusStartLevel = 0,
	RandomBonusValue = 0,
	Rates = {
		[1] = {
			Bonus = 100
		},
		[2] = {
			Bonus = 100
		},
		[3] = {
			Bonus = 100
		},
		[4] = {
			Bonus = 100
		},
		[5] = {
			NormalChance = 60,
			EnrichedChance = 90,
			EventNormalChance = 60,
			EventEnrichedChance = 95,
			Bonus = 200
		},
		[6] = {
			NormalChance = 40,
			EnrichedChance = 70,
			EventNormalChance = 40,
			EventEnrichedChance = 80,
			Bonus = 200
		},
		[7] = {
			NormalChance = 40,
			EnrichedChance = 70,
			EventNormalChance = 40,
			EventEnrichedChance = 80,
			Bonus = 200
		},
		[8] = {
			NormalChance = 20,
			EnrichedChance = 40,
			EventNormalChance = 20,
			EventEnrichedChance = 60,
			Bonus = 200
		},
		[9] = {
			NormalChance = 20,
			EnrichedChance = 40,
			EventNormalChance = 20,
			EventEnrichedChance = 50,
			Bonus = 300
		},
		[10] = {
			NormalChance = 9,
			EnrichedChance = 20,
			EventNormalChance = 9,
			EventEnrichedChance = 35,
			Bonus = 300
		},
		[11] = {
			NormalChance = 8,
			EventNormalChance = 20,
			EventEnrichedChance = 20,
			Bonus = 300
		},
		[12] = {
			NormalChance = 8,
			EventNormalChance = 20,
			EventEnrichedChance = 20,
			Bonus = 300
		},
		[13] = {
			NormalChance = 8,
			EventNormalChance = 16,
			EventEnrichedChance = 16,
			Bonus = 400
		},
		[14] = {
			NormalChance = 8,
			EventNormalChance = 16,
			EventEnrichedChance = 16,
			Bonus = 400
		},
		[15] = {
			NormalChance = 7,
			EventNormalChance = 15,
			EventEnrichedChance = 15,
			Bonus = 400
		},
		[16] = {
			NormalChance = 7,
			EventNormalChance = 15,
			EventEnrichedChance = 15,
			Bonus = 400
		},
		[17] = {
			NormalChance = 7,
			EventNormalChance = 14,
			EventEnrichedChance = 14,
			Bonus = 500
		},
		[18] = {
			NormalChance = 7,
			EventNormalChance = 14,
			EventEnrichedChance = 14,
			Bonus = 500
		},
		[19] = {
			NormalChance = 5,
			EventNormalChance = 10,
			EventEnrichedChance = 10,
			Bonus = 500
		},
		[20] = {
			NormalChance = 5,
			EventNormalChance = 10,
			EventEnrichedChance = 10,
			Bonus = 500
		}
	}
}
WeaponLevel1 = {
	StatsPerLevel = 200,
	RandomBonusStartLevel = 8,
	RandomBonusValue = 300,
	Rates = {
		[8] = {
			NormalChance = 60,
			EnrichedChance = 90,
			EventNormalChance = 60,
			EventEnrichedChance = 95
		},
		[9] = {
			NormalChance = 40,
			EnrichedChance = 70,
			EventNormalChance = 40,
			EventEnrichedChance = 85
		},
		[10] = {
			NormalChance = 19,
			EnrichedChance = 30,
			EventNormalChance = 19,
			EventEnrichedChance = 55
		},
		[11] = {
			NormalChance = 18,
			EventNormalChance = 40,
			EventEnrichedChance = 40
		},
		[12] = {
			NormalChance = 18,
			EventNormalChance = 40,
			EventEnrichedChance = 40
		},
		[13] = {
			NormalChance = 18,
			EventNormalChance = 35,
			EventEnrichedChance = 35
		},
		[14] = {
			NormalChance = 18,
			EventNormalChance = 35,
			EventEnrichedChance = 35
		},
		[15] = {
			NormalChance = 18,
			EventNormalChance = 30,
			EventEnrichedChance = 30
		},
		[16] = {
			NormalChance = 17,
			EventNormalChance = 30,
			EventEnrichedChance = 30,
			Bonus = 300
		},
		[17] = {
			NormalChance = 17,
			EventNormalChance = 20,
			EventEnrichedChance = 20,
			Bonus = 300
		},
		[18] = {
			NormalChance = 17,
			EventNormalChance = 20,
			EventEnrichedChance = 20,
			Bonus = 300
		},
		[19] = {
			NormalChance = 15,
			EventNormalChance = 15,
			EventEnrichedChance = 15,
			Bonus = 300
		},
		[20] = {
			NormalChance = 15,
			EventNormalChance = 15,
			EventEnrichedChance = 15,
			Bonus = 300
		}
	}
}
WeaponLevel2 = {
	StatsPerLevel = 300,
	RandomBonusStartLevel = 7,
	RandomBonusValue = 500,
	Rates = {
		[7] = {
			NormalChance = 60,
			EnrichedChance = 90,
			EventNormalChance = 60,
			EventEnrichedChance = 95
		},
		[8] = {
			NormalChance = 40,
			EnrichedChance = 70,
			EventNormalChance = 40,
			EventEnrichedChance = 85
		},
		[9] = {
			NormalChance = 20,
			EnrichedChance = 40,
			EventNormalChance = 20,
			EventEnrichedChance = 60
		},
		[10] = {
			NormalChance = 19,
			EnrichedChance = 30,
			EventNormalChance = 19,
			EventEnrichedChance = 45
		},
		[11] = {
			NormalChance = 18,
			EventNormalChance = 40,
			EventEnrichedChance = 40
		},
		[12] = {
			NormalChance = 18,
			EventNormalChance = 40,
			EventEnrichedChance = 40
		},
		[13] = {
			NormalChance = 18,
			EventNormalChance = 35,
			EventEnrichedChance = 35
		},
		[14] = {
			NormalChance = 18,
			EventNormalChance = 35,
			EventEnrichedChance = 35
		},
		[15] = {
			NormalChance = 18,
			EventNormalChance = 30,
			EventEnrichedChance = 30
		},
		[16] = {
			NormalChance = 17,
			EventNormalChance = 30,
			EventEnrichedChance = 30,
			Bonus = 600
		},
		[17] = {
			NormalChance = 17,
			EventNormalChance = 20,
			EventEnrichedChance = 20,
			Bonus = 600
		},
		[18] = {
			NormalChance = 17,
			EventNormalChance = 20,
			EventEnrichedChance = 20,
			Bonus = 600
		},
		[19] = {
			NormalChance = 15,
			EventNormalChance = 15,
			EventEnrichedChance = 15,
			Bonus = 600
		},
		[20] = {
			NormalChance = 15,
			EventNormalChance = 15,
			EventEnrichedChance = 15,
			Bonus = 600
		}
	}
}
WeaponLevel3 = {
	StatsPerLevel = 500,
	RandomBonusStartLevel = 6,
	RandomBonusValue = 800,
	Rates = {
		[6] = {
			NormalChance = 60,
			EnrichedChance = 90,
			EventNormalChance = 60,
			EventEnrichedChance = 95
		},
		[7] = {
			NormalChance = 50,
			EnrichedChance = 80,
			EventNormalChance = 50,
			EventEnrichedChance = 90
		},
		[8] = {
			NormalChance = 20,
			EnrichedChance = 40,
			EventNormalChance = 20,
			EventEnrichedChance = 70
		},
		[9] = {
			NormalChance = 20,
			EnrichedChance = 40,
			EventNormalChance = 20,
			EventEnrichedChance = 60
		},
		[10] = {
			NormalChance = 19,
			EnrichedChance = 30,
			EventNormalChance = 19,
			EventEnrichedChance = 45
		},
		[11] = {
			NormalChance = 18,
			EventNormalChance = 40,
			EventEnrichedChance = 40
		},
		[12] = {
			NormalChance = 18,
			EventNormalChance = 40,
			EventEnrichedChance = 40
		},
		[13] = {
			NormalChance = 18,
			EventNormalChance = 35,
			EventEnrichedChance = 35
		},
		[14] = {
			NormalChance = 18,
			EventNormalChance = 35,
			EventEnrichedChance = 35
		},
		[15] = {
			NormalChance = 18,
			EventNormalChance = 30,
			EventEnrichedChance = 30
		},
		[16] = {
			NormalChance = 17,
			EventNormalChance = 30,
			EventEnrichedChance = 30,
			Bonus = 900
		},
		[17] = {
			NormalChance = 17,
			EventNormalChance = 20,
			EventEnrichedChance = 20,
			Bonus = 900
		},
		[18] = {
			NormalChance = 17,
			EventNormalChance = 20,
			EventEnrichedChance = 20,
			Bonus = 900
		},
		[19] = {
			NormalChance = 15,
			EventNormalChance = 15,
			EventEnrichedChance = 15,
			Bonus = 900
		},
		[20] = {
			NormalChance = 15,
			EventNormalChance = 15,
			EventEnrichedChance = 15,
			Bonus = 900
		}
	}
}
WeaponLevel4 = {
	StatsPerLevel = 700,
	RandomBonusStartLevel = 5,
	RandomBonusValue = 1400,
	Rates = {
		[5] = {
			NormalChance = 60,
			EnrichedChance = 90,
			EventNormalChance = 60,
			EventEnrichedChance = 95
		},
		[6] = {
			NormalChance = 40,
			EnrichedChance = 70,
			EventNormalChance = 40,
			EventEnrichedChance = 80
		},
		[7] = {
			NormalChance = 40,
			EnrichedChance = 70,
			EventNormalChance = 40,
			EventEnrichedChance = 80
		},
		[8] = {
			NormalChance = 20,
			EnrichedChance = 40,
			EventNormalChance = 20,
			EventEnrichedChance = 60
		},
		[9] = {
			NormalChance = 20,
			EnrichedChance = 40,
			EventNormalChance = 20,
			EventEnrichedChance = 50
		},
		[10] = {
			NormalChance = 9,
			EnrichedChance = 20,
			EventNormalChance = 9,
			EventEnrichedChance = 35
		},
		[11] = {
			NormalChance = 8,
			EventNormalChance = 20,
			EventEnrichedChance = 20
		},
		[12] = {
			NormalChance = 8,
			EventNormalChance = 20,
			EventEnrichedChance = 20
		},
		[13] = {
			NormalChance = 8,
			EventNormalChance = 16,
			EventEnrichedChance = 16
		},
		[14] = {
			NormalChance = 8,
			EventNormalChance = 16,
			EventEnrichedChance = 16
		},
		[15] = {
			NormalChance = 7,
			EventNormalChance = 15,
			EventEnrichedChance = 15
		},
		[16] = {
			NormalChance = 7,
			EventNormalChance = 15,
			EventEnrichedChance = 15,
			Bonus = 1200
		},
		[17] = {
			NormalChance = 7,
			EventNormalChance = 14,
			EventEnrichedChance = 14,
			Bonus = 1200
		},
		[18] = {
			NormalChance = 7,
			EventNormalChance = 14,
			EventEnrichedChance = 14,
			Bonus = 1200
		},
		[19] = {
			NormalChance = 5,
			EventNormalChance = 10,
			EventEnrichedChance = 10,
			Bonus = 1200
		},
		[20] = {
			NormalChance = 5,
			EventNormalChance = 10,
			EventEnrichedChance = 10,
			Bonus = 1200
		}
	}
}
