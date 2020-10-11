------------------ Hercules Database ------------------------------------------
--       _   _                     _
--      | | | |                   | |
--      | |_| | ___ _ __ ___ _   _| | ___  ___
--      |  _  |/ _ \ '__/ __| | | | |/ _ \/ __|
--      | | | |  __/ | | (__| |_| | |  __/\__ \
--      \_| |_/\___|_|  \___|\__,_|_|\___||___/
------------------ License ----------------------------------------------------
-- This file is part of Hercules.
-- http://herc.ws - http://github.com/HerculesWS/Hercules
--
-- Copyright (C) 2014-2017  Hercules Dev Team
--
-- Hercules is free software: you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with this program.  If not, see <http://www.gnu.org/licenses/>.
-------------------------------------------------------------------------------
-- Renewal Skill Database [Hercules]
-------------------------------------------------------------------------------
-- @Format Notes:
-- - All string entries are case-sensitive and must be quoted.
-- - All setting names are case-sensitive and must be keyed accurately.


--[[
-------------------------------------------------------------------------------
----------------------------- Entry Structure ---------------------------------
-------------------------------------------------------------------------------
{
	// ------------------------------ Mandatory Fields ----------------------------
	Id = ID,                                      (int)     (Required)
	Name = "Skill Name"                          (string)  (Required)
	MaxLevel: Skill Level                       (int)     (Required)
	// ------------------------------ Optional Fields -----------------------------
	Description = "Skill Description"            (string)  (optional but recommended)
	Range: Skill Range                          (int) (optional, defaults to 0) (can be grouped by Levels)
	                                            Note: Range < 5 is considered Melee range.
	Hit: Hit Type                               (int) (optional, default "BDT_NORMAL")
	                                            Types - "BDT_SKILL", "BDT_MULTIHIT" or "BDT_NORMAL",
	Behavior = {                                (bool, defaults to "Passive")
		Passive
		SkillBehavior.UseOnEnemy
		SkillBehavior.UseOnPlace
		SkillBehavior.UseOnSelf
		SkillBehavior.UseOnFriend
		SkillBehavior.LearntFromQuest
		SkillBehavior.LearntFromNPC
		SkillBehavior.LearntFromWedding
		SkillBehavior.LearntFromBuff
		SkillBehavior.GuildSkill
		SkillBehavior.SongDanceSkill
		SkillBehavior.EnsembleSkill
		SkillBehavior.TrapSkill
		SkillBehavior.WithoutSelf
		SkillBehavior.PartyOnly
		SkillBehavior.GuildOnly
		SkillBehavior.NoEnemy
		SkillBehavior.IgnoreLandProtector
		SkillBehavior.RequiresPartner
		SkillBehavior.ShowSkillScale
		SkillBehavior.AllowReplicate
		SkillBehavior.IgnoreTargetPlayers
		SkillBehavior.IgnoreTargetMobs
		SkillBehavior.IgnoreTargetSkills
	},

	AttackType = AttackType.*                   (AttackType, defaults to AttackType.None)
	                                            Types = "None", "Weapon", "Magic" or "Misc",
	Element = Element.*                         (Element) (Optional field - Default Element.Neutral)
	                                            (can be grouped by Levels)
	                                            Types =
	                                            Element.Neutral,
	                                            Element.Water,
	                                            Element.Earth,
	                                            Element.Fire,
	                                            Element.Wind,
	                                            Element.Poison,
	                                            Element.Holy,
	                                            Element.Dark,
	                                            Element.Ghost,
	                                            Element.Undead,
	                                            Element.WeaponElement - Uses weapon's element.
	                                            Element.EndowedElement - Uses Endowed element.
	DamageBehavior = {                          (bool, default to DamageBehavior.NonOffensive)
		DamageBehavior.NonOffensive             This skill will not cause any damage.
		DamageBehavior.AreaOfEffect             Has splash area (requires source modification)
		DamageBehavior.SplitBetweenTargets      Damage should be split among targets (requires 'SplashArea' in order to work)
		DamageBehavior.IgnoreCards              Skill ignores caster's % damage cards (misc type always ignores)
		DamageBehavior.IgnoreElement            Skill ignores elemental adjustments
		DamageBehavior.IgnoreDefense            Skill ignores target's defense (misc type always ignores)
		DamageBehavior.IgnoreFlee               Skill ignores target's flee (magic type always ignores)
		DamageBehavior.IgnoreDefCards           Skill ignores target's def cards
	},
	SplashRange: Damage Splash Area             (int, defaults to 0) (can be grouped by Levels)
	                                            Note: -1 for screen-wide.
	NumberOfHits: Number of Hits                (int, defaults to 1) (can be grouped by Levels)
	                                            Note: when positive, damage is increased by hits,
	                                            negative values just show number of hits without
	                                            increasing total damage.
	InterruptCast: Cast Interruption            (bool, defaults to false)
	CastDefRate: Cast Defense Reduction         (int, defaults to 0)
	SkillInstances: Skill instances             (int, defaults to 0) (can be grouped by Levels)
	                                            Notes: max amount of skill instances to place on the ground when
	                                            player_land_skill_limit/monster_land_skill_limit is enabled. For skills
	                                            that attack using a path, this is the path length to be used.
	KnockBackTiles: Knock-back by 'n' Tiles     (int, defaults to 0) (can be grouped by Levels)
	CastTime: Skill cast Time (in ms)           (int, defaults to 0) (can be grouped by Levels)
	AfterCastActDelay: Skill Delay (in ms)      (int, defaults to 0) (can be grouped by Levels)
	AfterCastWalkDelay: Walk Delay (in ms)      (int, defaults to 0) (can be grouped by Levels)
	SkillData1: Skill Data/Duration (in ms)     (int, defaults to 0) (can be grouped by Levels)
	SkillData2: Skill Data/Duration (in ms)     (int, defaults to 0) (can be grouped by Levels)
	CoolDown: Skill Cooldown (in ms)            (int, defaults to 0) (can be grouped by Levels)
	FixedCastTime: Fixed Cast Time (in ms)      (int, defaults to 0) (can be grouped by Levels)
	                                            Note: when 0, uses 20% of cast time and less than
	                                            0 means no fixed cast time.
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffects,
		CastTimeOptions.IgnoreItemBonus
		                                        Note: Delay setting 'IgnoreDex' only makes sense when
		                                        delay_dependon_dex is enabled.
	},
	SkillDelayOptions = {
		SkillDelayOptions.IgnoreDex,
		SkillDelayOptions.IgnoreStatusEffect,
		SkillDelayOptions.IgnoreItemBonus
		                                        Note: Delay setting 'IgnoreDex' only makes sense when
		                                        delay_dependon_dex is enabled.
	},
	Requirements = {
		HPCost: HP Cost                         (int, defaults to 0) (can be grouped by Levels)
		SPCost: SP Cost                         (int, defaults to 0) (can be grouped by Levels)
		HPRateCost: HP % Cost                   (int, defaults to 0) (can be grouped by Levels)
		                                        Note: If positive, it is a percent of your current hp,
		                                        otherwise it is a percent of your max hp.
		SPRateCost: SP % Cost                   (int, defaults to 0) (can be grouped by Levels)
		                                        Note: If positive, it is a percent of your current sp,
		                                        otherwise it is a percent of your max sp.
		ZenyCost: Zeny Cost                     (int, defaults to 0) (can be grouped by Levels)
		WeaponTypes = {                          (bool or string, defaults to "All")
			WeaponType.Fist
			WeaponType.Dagger
			WeaponType.OneHandedSword
			WeaponType.TwoHandedSword
			WeaponType.OneHandedSpear
			WeaponType.TwoHandedSpear
			WeaponType.OneHandedAxe
			WeaponType.TwoHandedAxe
			WeaponType.OneHandedMace
			WeaponType.TwoHandedMace
			WeaponType.OneHandedStaff
			WeaponType.Bow
			WeaponType.Knuckle
			WeaponType.MusicalInstrument
			WeaponType.Whip
			WeaponType.Book
			WeaponType.Katar
			WeaponType.Revolver
			WeaponType.Rifle
			WeaponType.GatlingGun
			WeaponType.Shotgun
			WeaponType.GrenadeLauncher
			WeaponType.FuumaShuriken
			WeaponType.TwoHandedStaff
		},
		AmmoTypes = {
			AmmoType.Arrow
			AmmoType.Throwable_Dagger
			AmmoType.Bullet
			AmmoType.Shell
			AmmoType.Grenade
			AmmoType.Shuriken
			AmmoType.Kunai
			AmmoType.CannonBall
			AmmoType.ThrowableItem
		},
		AmmoAmount: Ammunition Amount           (int, defaults to 0) (can be grouped by Levels)
		State = "Required State"                 (string, defaults to "None") (can be grouped by Levels)
            Types : 'None' - Nothing special
            'Moveable' - Requires to be able to move
            'NotOverweight' - Requires to be less than 50% weight
            'InWater' - Requires to be standing on a water cell
            'HasCart' - Requires a Pushcart
            'Mounted' - Requires to ride either a peco or a dragon
            'HasFalcon' - Requires a Falcon
            'Sight' - Requires Sight skill activated
            'Hiding' - Requires Hiding skill activated
            'Cloaking' - Requires Cloaking skill activated
            'CriticalExplosion' - Requires Fury skill activated
            'CartBoost' - Requires a Pushcart and Cart Boost skill activated
            'Shield' - Requires a 0,shield equipped
            'Warg' - Requires a Warg
            'MountedDragon' - Requires to ride a MountedDragon
            'MountedWarg' - Requires to ride a Warg
            'InMadoGear' - Requires to have an active mado
            'PoisonedWeapon' - Requires to be under Poisoning Weapon.
            'PerformingRollingCutter' - Requires at least one Rotation Counter from Rolling Cutter.
            'HasElementalSpirit' - Requires to have an Elemental Spirit summoned.
            'MHEleanorIsFighting' - Requires Eleanor fighthing mode
            'MHEleanorIsGrappling' - Requires Eleanor grappling mode
		SpiritSphereCost: Spirit Sphere Cost    (int, defaults to 0) (can be grouped by Levels)
		Items = {
			ItemID or Aegis_Name : Amount       (int, defaults to 0) (can be grouped by Levels)
			                                    Item example = "ID717" or "Blue_Gemstone".
			                                    Notes: Items with amount 0 will not be consumed.
			                                    Amount can also be grouped by levels.
		}
	},
	Placement = {
		Id = { UnitID, UnitID2 },                 (int, defaults to 0) (can be grouped by Levels)
		Layout = Unit Layout                     (int, defaults to 0) (can be grouped by Levels)
		Range =  Unit Range                       (int, defaults to 0) (can be grouped by Levels)
		Interval = Unit Interval                 (int, defaults to 0) (can be grouped by Levels)
		Target = "Unit Target"                   (string, defaults to "None")
		                                        Types:
		                                        All             - affects everyone
		                                        NotEnemy        - affects anyone who isn't an enemy
		                                        Friend          - affects party, guildmates and neutral players
		                                        Party           - affects party only
		                                        Guild           - affects guild only
		                                        Ally            - affects party and guildmates only
		                                        Sameguild       - affects guild but not allies
		                                        Enemy           - affects enemies only
		                                        None            - affects nobody
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget,
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
			PlacementBehavior.Immovable,
			PlacementBehavior.AffectOnContact,
		}
	}
}
*******************************************************************************/
]]--

assert(require("db/definitions/constants.lua"))
assert(require("db/definitions/skill_constants.lua"))

skill_db = {
[ "NV_BASIC" ] = {
	Id = 1,
	Description = "Basic Skill",
	MaxLevel = 9,
	NumberOfHits = 0
},
[ "SM_SWORD" ] = {
	Id = 2,
	Description = "Sword Mastery",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
{
	Id = 3,
	Name = "SM_TWOHAND",
	Description = "Two-Handed Sword Mastery",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "SM_RECOVERY" ] = {
	Id = 4,
	Description = "Increase HP Recovery",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "SM_BASH" ] = {
	Id = 5,
	Description = "Bash",
	MaxLevel = 10,
	Range = -1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = {
			[1] = 8,
			[2] = 8,
			[3] = 8,
			[4] = 8,
			[5] = 8,
			[6] = 15,
			[7] = 15,
			[8] = 15,
			[9] = 15,
			[10] = 15
		},
		WeaponTypes = {
			WeaponType.Fist,
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar,
			WeaponType.Revolver,
			WeaponType.Rifle,
			WeaponType.GatlingGun,
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher,
			WeaponType.FuumaShuriken
		}
	}
},
[ "SM_PROVOKE" ] = {
	Id = 6,
	Description = "Provoke",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 30000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 4,
			[2] = 5,
			[3] = 6,
			[4] = 7,
			[5] = 8,
			[6] = 9,
			[7] = 10,
			[8] = 11,
			[9] = 12,
			[10] = 13
		}
	}
},
[ "SM_MAGNUM" ] = {
	Id = 7,
	Description = "Magnum Break",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	KnockBackTiles = 2,
	AfterCastActDelay = 2000,
	SkillData1 = 2000,
	SkillData2 = 10000,
	FixedCastTime = 0,
	Requirements = {
		HPCost = {
			[1] = 20,
			[2] = 20,
			[3] = 19,
			[4] = 19,
			[5] = 18,
			[6] = 18,
			[7] = 17,
			[8] = 17,
			[9] = 16,
			[10] = 16
		},
		SPCost = 30
	}
},
[ "SM_ENDURE" ] = {
	Id = 8,
	Description = "Endure",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 10000,
		[2] = 13000,
		[3] = 16000,
		[4] = 19000,
		[5] = 22000,
		[6] = 25000,
		[7] = 28000,
		[8] = 31000,
		[9] = 34000,
		[10] = 37000
	},
	SkillData2 = 10000,
	CoolDown = 10000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "MG_SRECOVERY" ] = {
	Id = 9,
	Description = "Increase SP Recovery",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "MG_SIGHT" ] = {
	Id = 10,
	Description = "Sight",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	InterruptCast = true,
	SkillData1 = 10000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "MG_NAPALMBEAT" ] = {
	Id = 11,
	Description = "Napalm Beat",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Ghost,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.SplitBetweenTargets
	},
	SplashRange = 1,
	InterruptCast = true,
	CastTime = 400,
	AfterCastActDelay = {
		[1] = 1000,
		[2] = 1000,
		[3] = 1000,
		[4] = 900,
		[5] = 900,
		[6] = 800,
		[7] = 800,
		[8] = 700,
		[9] = 600,
		[10] = 500
	},
	FixedCastTime = 100,
	Requirements = {
		SPCost = {
			[1] = 9,
			[2] = 9,
			[3] = 9,
			[4] = 12,
			[5] = 12,
			[6] = 12,
			[7] = 15,
			[8] = 15,
			[9] = 15,
			[10] = 18
		}
	}
},
[ "MG_SAFETYWALL" ] = {
	Id = 12,
	Description = "Safety Wall",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Ghost,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 3200,
		[2] = 2880,
		[3] = 2560,
		[4] = 2240,
		[5] = 1920,
		[6] = 1600,
		[7] = 1280,
		[8] = 960,
		[9] = 640,
		[10] = 320
	},
	SkillData1 = {
		[1] = 5000,
		[2] = 10000,
		[3] = 15000,
		[4] = 20000,
		[5] = 25000,
		[6] = 30000,
		[7] = 35000,
		[8] = 40000,
		[9] = 45000,
		[10] = 50000
	},
	FixedCastTime = {
		[1] = 800,
		[2] = 720,
		[3] = 640,
		[4] = 560,
		[5] = 480,
		[6] = 400,
		[7] = 320,
		[8] = 240,
		[9] = 160,
		[10] = 80
	},
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 30,
			[3] = 30,
			[4] = 35,
			[5] = 35,
			[6] = 35,
			[7] = 40,
			[8] = 40,
			[9] = 40,
			[10] = 40
		},
		Items = {
			Item[ "Blue_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = 0x7e,
		Interval = -1,
		Target = "All"
	}
},
[ "MG_SOULSTRIKE" ] = {
	Id = 13,
	Description = "Soul Strike",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Ghost,
	NumberOfHits = {
		[1] = 1,
		[2] = 1,
		[3] = 2,
		[4] = 2,
		[5] = 3,
		[6] = 3,
		[7] = 4,
		[8] = 4,
		[9] = 5,
		[10] = 5
	},
	InterruptCast = true,
	CastTime = 400,
	AfterCastActDelay = {
		[1] = 1200,
		[2] = 1200,
		[3] = 1600,
		[4] = 1600,
		[5] = 2000,
		[6] = 2000,
		[7] = 2400,
		[8] = 2400,
		[9] = 2800,
		[10] = 2500
	},
	FixedCastTime = 100,
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 14,
			[3] = 24,
			[4] = 20,
			[5] = 30,
			[6] = 26,
			[7] = 36,
			[8] = 32,
			[9] = 42,
			[10] = 38
		}
	}
},
[ "MG_COLDBOLT" ] = {
	Id = 14,
	Description = "Cold Bolt",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = {
		[1] = 640,
		[2] = 960,
		[3] = 1280,
		[4] = 1600,
		[5] = 1920,
		[6] = 2100,
		[7] = 1560,
		[8] = 2880,
		[9] = 3200,
		[10] = 3520
	},
	AfterCastActDelay = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	FixedCastTime = {
		[1] = 160,
		[2] = 240,
		[3] = 320,
		[4] = 400,
		[5] = 480,
		[6] = 700,
		[7] = 640,
		[8] = 720,
		[9] = 800,
		[10] = 880
	},
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		}
	}
},
[ "MG_FROSTDIVER" ] = {
	Id = 15,
	Description = "Frost Diver",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	InterruptCast = true,
	CastTime = 640,
	AfterCastActDelay = 1500,
	SkillData2 = {
		[1] = 3000,
		[2] = 6000,
		[3] = 9000,
		[4] = 12000,
		[5] = 15000,
		[6] = 18000,
		[7] = 21000,
		[8] = 24000,
		[9] = 27000,
		[10] = 30000
	},
	FixedCastTime = 160,
	Requirements = {
		SPCost = {
			[1] = 25,
			[2] = 24,
			[3] = 23,
			[4] = 22,
			[5] = 21,
			[6] = 20,
			[7] = 19,
			[8] = 18,
			[9] = 17,
			[10] = 16
		}
	}
},
[ "MG_STONECURSE" ] = {
	Id = 16,
	Description = "Stone Curse",
	MaxLevel = 10,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 800,
	SkillData1 = 5000,
	SkillData2 = 20000,
	FixedCastTime = 200,
	Requirements = {
		SPCost = {
			[1] = 25,
			[2] = 24,
			[3] = 23,
			[4] = 22,
			[5] = 21,
			[6] = 20,
			[7] = 19,
			[8] = 18,
			[9] = 17,
			[10] = 16
		},
		Items = {
			Item[ "Red_Gemstone" ] = 1
		}
	}
},
[ "MG_FIREBALL" ] = {
	Id = 17,
	Description = "Fire Ball",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	InterruptCast = true,
	CastTime = {
		[1] = 1280,
		[2] = 1280,
		[3] = 1280,
		[4] = 1280,
		[5] = 1280,
		[6] = 800,
		[7] = 800,
		[8] = 800,
		[9] = 800,
		[10] = 800
	},
	AfterCastActDelay = {
		[1] = 1500,
		[2] = 1500,
		[3] = 1500,
		[4] = 1500,
		[5] = 1500,
		[6] = 1000,
		[7] = 1000,
		[8] = 1000,
		[9] = 1000,
		[10] = 1000
	},
	FixedCastTime = {
		[1] = 320,
		[2] = 320,
		[3] = 320,
		[4] = 320,
		[5] = 320,
		[6] = 200,
		[7] = 200,
		[8] = 200,
		[9] = 200,
		[10] = 200
	},
	Requirements = {
		SPCost = 25
	}
},
[ "MG_FIREWALL" ] = {
	Id = 18,
	Description = "Fire Wall",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	InterruptCast = true,
	SkillInstances = 3,
	KnockBackTiles = 2,
	CastTime = {
		[1] = 1600,
		[2] = 1440,
		[3] = 1280,
		[4] = 1120,
		[5] = 960,
		[6] = 880,
		[7] = 800,
		[8] = 720,
		[9] = 640,
		[10] = 560
	},
	SkillData1 = {
		[1] = 5000,
		[2] = 6000,
		[3] = 7000,
		[4] = 8000,
		[5] = 9000,
		[6] = 10000,
		[7] = 11000,
		[8] = 12000,
		[9] = 13000,
		[10] = 14000
	},
	FixedCastTime = {
		[1] = 400,
		[2] = 360,
		[3] = 320,
		[4] = 280,
		[5] = 240,
		[6] = 220,
		[7] = 200,
		[8] = 180,
		[9] = 160,
		[10] = 140
	},
	Requirements = {
		SPCost = 40
	},
	Placement = {
		Id = 0x7f,
		Layout = -1,
		Interval = 20,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "MG_FIREBOLT" ] = {
	Id = 19,
	Description = "Fire Bolt",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = {
		[1] = 640,
		[2] = 960,
		[3] = 1280,
		[4] = 1600,
		[5] = 1920,
		[6] = 2100,
		[7] = 1560,
		[8] = 2880,
		[9] = 3200,
		[10] = 3520
	},
	AfterCastActDelay = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	FixedCastTime = {
		[1] = 160,
		[2] = 240,
		[3] = 320,
		[4] = 400,
		[5] = 480,
		[6] = 700,
		[7] = 640,
		[8] = 720,
		[9] = 800,
		[10] = 880
	},
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		}
	}
},
[ "MG_LIGHTNINGBOLT" ] = {
	Id = 20,
	Description = "Lightning Bolt",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = {
		[1] = 640,
		[2] = 960,
		[3] = 1280,
		[4] = 1600,
		[5] = 1920,
		[6] = 2100,
		[7] = 1560,
		[8] = 2880,
		[9] = 3200,
		[10] = 3520
	},
	AfterCastActDelay = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	FixedCastTime = {
		[1] = 160,
		[2] = 240,
		[3] = 320,
		[4] = 400,
		[5] = 480,
		[6] = 700,
		[7] = 640,
		[8] = 720,
		[9] = 800,
		[10] = 880
	},
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		}
	}
},
[ "MG_THUNDERSTORM" ] = {
	Id = 21,
	Description = "Thunderstorm",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = {
		[1] = 640,
		[2] = 1280,
		[3] = 1920,
		[4] = 2560,
		[5] = 3200,
		[6] = 3840,
		[7] = 4480,
		[8] = 5120,
		[9] = 5760,
		[10] = 6400
	},
	AfterCastActDelay = {
		[1] = 2000,
		[2] = 2000,
		[3] = 2000,
		[4] = 2000,
		[5] = 2000,
		[6] = 2000,
		[7] = 2000,
		[8] = 2000,
		[9] = 2000,
		[10] = 2000
	},
	SkillData1 = 500,
	FixedCastTime = {
		[1] = 160,
		[2] = 320,
		[3] = 480,
		[4] = 640,
		[5] = 800,
		[6] = 960,
		[7] = 1120,
		[8] = 1280,
		[9] = 1440,
		[10] = 1600
	},
	Requirements = {
		SPCost = {
			[1] = 29,
			[2] = 34,
			[3] = 39,
			[4] = 44,
			[5] = 49,
			[6] = 54,
			[7] = 59,
			[8] = 64,
			[9] = 69,
			[10] = 74
		}
	},
	Placement = {
		Id = 0x86,
		Range = 2,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "AL_DP" ] = {
	Id = 22,
	Description = "Divine Protection",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "AL_DEMONBANE" ] = {
	Id = 23,
	Description = "Demon Bane",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "AL_RUWACH" ] = {
	Id = 24,
	Description = "Ruwach",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	InterruptCast = true,
	SkillData1 = 10000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "AL_PNEUMA" ] = {
	Id = 25,
	Description = "Pneuma",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 10000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	},
	Placement = {
		Id = 0x85,
		Layout = 1,
		Interval = -1,
		Target = "All"
	}
},
[ "AL_TELEPORT" ] = {
	Id = 26,
	Description = "Teleport",
	MaxLevel = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 9,
			[3] = 8,
			[4] = 7,
			[5] = 6,
			[6] = 5,
			[7] = 4,
			[8] = 3,
			[9] = 2,
			[10] = 1
		}
	}
},
[ "AL_WARP" ] = {
	Id = 27,
	Description = "Warp Portal",
	MaxLevel = 4,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 3,
	SkillData1 = {
		[1] = 5000,
		[2] = 10000,
		[3] = 15000,
		[4] = 20000,
		[5] = 25000,
		[6] = 30000,
		[7] = 35000,
		[8] = 40000,
		[9] = 45000,
		[10] = 50000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 35,
			[2] = 32,
			[3] = 29,
			[4] = 26,
			[5] = 23,
			[6] = 20,
			[7] = 17,
			[8] = 14,
			[9] = 11,
			[10] = 8
		},
		Items = {
			Item[ "Blue_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = { 0x81, 0x80 },
		Interval = -1,
		Target = "All",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget,
			PlacementBehavior.CannotOverlap
		}
	}
},
[ "AL_HEAL" ] = {
	Id = 28,
	Description = "Heal",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.Ignore_Soft_Def
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 13,
			[2] = 16,
			[3] = 19,
			[4] = 22,
			[5] = 25,
			[6] = 28,
			[7] = 31,
			[8] = 34,
			[9] = 37,
			[10] = 40
		}
	}
},
[ "AL_INCAGI" ] = {
	Id = 29,
	Description = "Increase AGI",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 800,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 60000,
		[2] = 80000,
		[3] = 100000,
		[4] = 120000,
		[5] = 140000,
		[6] = 160000,
		[7] = 180000,
		[8] = 200000,
		[9] = 220000,
		[10] = 240000
	},
	FixedCastTime = 200,
	Requirements = {
		HPCost = 15,
		SPCost = {
			[1] = 18,
			[2] = 21,
			[3] = 24,
			[4] = 27,
			[5] = 30,
			[6] = 33,
			[7] = 36,
			[8] = 39,
			[9] = 42,
			[10] = 45
		}
	}
},
[ "AL_DECAGI" ] = {
	Id = 30,
	Description = "Decrease AGI",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 750,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 40000,
		[2] = 50000,
		[3] = 60000,
		[4] = 70000,
		[5] = 80000,
		[6] = 90000,
		[7] = 100000,
		[8] = 110000,
		[9] = 120000,
		[10] = 130000
	},
	FixedCastTime = 250,
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 17,
			[3] = 19,
			[4] = 21,
			[5] = 23,
			[6] = 25,
			[7] = 27,
			[8] = 29,
			[9] = 31,
			[10] = 33
		}
	}
},
[ "AL_HOLYWATER" ] = {
	Id = 31,
	Description = "Aqua Benedicta",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 800,
	AfterCastActDelay = 500,
	FixedCastTime = 200,
	Requirements = {
		SPCost = 10,
		State = PlayerState.InWater
	}
},
[ "AL_CRUCIS" ] = {
	Id = 32,
	Description = "Signum Crucis",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 15,
	InterruptCast = true,
	CastTime = 350,
	AfterCastActDelay = 2000,
	FixedCastTime = 150,
	Requirements = {
		SPCost = 35
	}
},
[ "AL_ANGELUS" ] = {
	Id = 33,
	Description = "Angelus",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	InterruptCast = true,
	CastTime = 350,
	AfterCastActDelay = 3500,
	SkillData1 = {
		[1] = 30000,
		[2] = 60000,
		[3] = 90000,
		[4] = 120000,
		[5] = 150000,
		[6] = 180000,
		[7] = 210000,
		[8] = 240000,
		[9] = 270000,
		[10] = 300000
	},
	FixedCastTime = 150,
	Requirements = {
		SPCost = {
			[1] = 23,
			[2] = 26,
			[3] = 29,
			[4] = 32,
			[5] = 35,
			[6] = 38,
			[7] = 41,
			[8] = 44,
			[9] = 47,
			[10] = 50
		}
	}
},
[ "AL_BLESSING" ] = {
	Id = 34,
	Description = "Blessing",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 60000,
		[2] = 80000,
		[3] = 100000,
		[4] = 120000,
		[5] = 140000,
		[6] = 160000,
		[7] = 180000,
		[8] = 200000,
		[9] = 220000,
		[10] = 240000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 28,
			[2] = 32,
			[3] = 36,
			[4] = 40,
			[5] = 44,
			[6] = 48,
			[7] = 52,
			[8] = 56,
			[9] = 60,
			[10] = 64
		}
	}
},
[ "AL_CURE" ] = {
	Id = 35,
	Description = "Cure",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData2 = 6000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15
	}
},
[ "MC_INCCARRY" ] = {
	Id = 36,
	Description = "Enlarge Weight Limit",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "MC_DISCOUNT" ] = {
	Id = 37,
	Description = "Discount",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "MC_OVERCHARGE" ] = {
	Id = 38,
	Description = "Overcharge",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "MC_PUSHCART" ] = {
	Id = 39,
	Description = "Pushcart",
	MaxLevel = 10,
	Range = 1,
	NumberOfHits = 0
},
[ "MC_IDENTIFY" ] = {
	Id = 40,
	Description = "Item Appraisal",
	MaxLevel = 1,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 10
	}
},
[ "MC_VENDING" ] = {
	Id = 41,
	Description = "Vending",
	MaxLevel = 10,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 30,
		State = PlayerState.HasCart
	}
},
[ "MC_MAMMONITE" ] = {
	Id = 42,
	Description = "Mammonite",
	MaxLevel = 10,
	Range = -1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = 5,
		ZenyCost = {
			[1] = 100,
			[2] = 200,
			[3] = 300,
			[4] = 400,
			[5] = 500,
			[6] = 600,
			[7] = 700,
			[8] = 800,
			[9] = 900,
			[10] = 1000
		}
	}
},
{
	Id = 43,
	Name = "AC_OWL",
	Description = "Owl's Eye",
	MaxLevel = 10,
	NumberOfHits = 0
},
{
	Id = 44,
	Name = "AC_VULTURE",
	Description = "Vulture's Eye",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "AC_CONCENTRATION" ] = {
	Id = 45,
	Description = "Improve Concentration",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	SkillData1 = {
		[1] = 60000,
		[2] = 80000,
		[3] = 100000,
		[4] = 120000,
		[5] = 140000,
		[6] = 160000,
		[7] = 180000,
		[8] = 200000,
		[9] = 220000,
		[10] = 240000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 25,
			[2] = 30,
			[3] = 35,
			[4] = 40,
			[5] = 45,
			[6] = 50,
			[7] = 55,
			[8] = 60,
			[9] = 65,
			[10] = 70
		}
	}
},
[ "AC_DOUBLE" ] = {
	Id = 46,
	Description = "Double Strafe",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 2,
	AfterCastActDelay = 100,
	SkillData1 = 100,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 12,
		WeaponTypes = {
			WeaponType.Bow
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	}
},
[ "AC_SHOWER" ] = {
	Id = 47,
	Description = "Arrow Shower",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.IgnoreLandProtector,
		SkillBehavior.AllowReplicate,
		SkillBehavior.IgnoreTargetSkills
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 2,
		[3] = 2,
		[4] = 2,
		[5] = 2,
		[6] = 3,
		[7] = 3,
		[8] = 3,
		[9] = 3,
		[10] = 3
	},
	KnockBackTiles = 2,
	AfterCastActDelay = 100,
	SkillData1 = 100,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15,
		WeaponTypes = {
			WeaponType.Bow
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	},
	Placement = {
		Id = 0x86,
		Range = {
			[1] = 1,
			[2] = 1,
			[3] = 1,
			[4] = 1,
			[5] = 1,
			[6] = 2,
			[7] = 2,
			[8] = 2,
			[9] = 2,
			[10] = 2
		},
		Interval = 1000,
		Target = "Enemy"
	}
},
[ "TF_DOUBLE" ] = {
	Id = 48,
	Description = "Double Attack",
	MaxLevel = 10,
	Range = -1,
	Hit = "BDT_MULTIHIT",
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 2
},
[ "TF_MISS" ] = {
	Id = 49,
	Description = "Improve Dodge",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "TF_STEAL" ] = {
	Id = 50,
	Description = "Steal",
	MaxLevel = 10,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 10
	}
},
[ "TF_HIDING" ] = {
	Id = 51,
	Description = "Hiding",
	MaxLevel = 10,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 60000,
		[3] = 90000,
		[4] = 120000,
		[5] = 150000,
		[6] = 180000,
		[7] = 210000,
		[8] = 240000,
		[9] = 270000,
		[10] = 300000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "TF_POISON" ] = {
	Id = 52,
	Description = "Envenom",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.Poison,
	SkillData2 = {
		[1] = 15000,
		[2] = 20000,
		[3] = 25000,
		[4] = 30000,
		[5] = 35000,
		[6] = 40000,
		[7] = 45000,
		[8] = 50000,
		[9] = 55000,
		[10] = 60000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 12
	}
},
[ "TF_DETOXIFY" ] = {
	Id = 53,
	Description = "Detoxify",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Weapon,
	Element = Element.Poison,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 10
	}
},
[ "ALL_RESURRECTION" ] = {
	Id = 54,
	Description = "Resurrection",
	MaxLevel = 4,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 4800,
		[2] = 3200,
		[3] = 1600,
		[4] = 0,
		[5] = 1,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	AfterCastActDelay = {
		[1] = 0,
		[2] = 1000,
		[3] = 2000,
		[4] = 3000,
		[5] = 4000,
		[6] = 5000,
		[7] = 6000,
		[8] = 7000,
		[9] = 8000,
		[10] = 9000
	},
	FixedCastTime = {
		[1] = 1200,
		[2] = 800,
		[3] = 400,
		[4] = 0,
		[5] = 1,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	Requirements = {
		SPCost = 60,
		Items = {
			Item[ "Blue_Gemstone" ] = 1
		}
	}
},
[ "KN_SPEARMASTERY" ] = {
	Id = 55,
	Description = "Spear Mastery",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "KN_PIERCE" ] = {
	Id = 56,
	Description = "Pierce",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 3,
	Requirements = {
		SPCost = 7,
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "KN_BRANDISHSPEAR" ] = {
	Id = 57,
	Description = "Brandish Spear",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	KnockBackTiles = 3,
	CastTime = 350,
	FixedCastTime = 350,
	Requirements = {
		SPCost = 12,
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		},
		State = PlayerState.Mounted
	}
},
[ "KN_SPEARSTAB" ] = {
	Id = 58,
	Description = "Spear Stab",
	MaxLevel = 10,
	Range: -4,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	KnockBackTiles = 6,
	Requirements = {
		SPCost = 9,
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "KN_SPEARBOOMERANG" ] = {
	Id = 59,
	Description = "Spear Boomerang",
	MaxLevel = 5,
	Range = {
		[1] = 3,
		[2] = 5,
		[3] = 7,
		[4] = 9,
		[5] = 11,
		[6] = 13,
		[7] = 15,
		[8] = 17,
		[9] = 19,
		[10] = 21
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "KN_TWOHANDQUICKEN" ] = {
	Id = 60,
	Description = "Twohand Quicken",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 60000,
		[3] = 90000,
		[4] = 120000,
		[5] = 150000,
		[6] = 180000,
		[7] = 210000,
		[8] = 240000,
		[9] = 270000,
		[10] = 300000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 14,
			[2] = 18,
			[3] = 22,
			[4] = 26,
			[5] = 30,
			[6] = 34,
			[7] = 38,
			[8] = 42,
			[9] = 46,
			[10] = 50
		},
		WeaponTypes = {
			WeaponType.TwoHandedSword
		}
	}
},
[ "KN_AUTOCOUNTER" ] = {
	Id = 61,
	Description = "Counter Attack",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.Ignore_Soft_Def
	},
	SkillData1 = {
		[1] = 400,
		[2] = 800,
		[3] = 1200,
		[4] = 1600,
		[5] = 2000,
		[6] = 2400,
		[7] = 2800,
		[8] = 3200,
		[9] = 3600,
		[10] = 4000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 3,
		WeaponTypes = {
			WeaponType.Fist,
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar,
			WeaponType.Revolver,
			WeaponType.Rifle,
			WeaponType.GatlingGun,
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher,
			WeaponType.FuumaShuriken
		}
	}
},
[ "KN_BOWLINGBASH" ] = {
	Id = 62,
	Description = "Bowling Bash",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	KnockBackTiles = 1,
	CastTime = 350,
	FixedCastTime = 350,
	Requirements = {
		SPCost = {
			[1] = 13,
			[2] = 14,
			[3] = 15,
			[4] = 16,
			[5] = 17,
			[6] = 18,
			[7] = 19,
			[8] = 20,
			[9] = 21,
			[10] = 22
		}
	}
},
[ "KN_RIDING" ] = {
	Id = 63,
	Description = "Peco Peco Riding",
	MaxLevel = 1,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "KN_CAVALIERMASTERY" ] = {
	Id = 64,
	Description = "Cavalier Mastery",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "PR_MACEMASTERY" ] = {
	Id = 65,
	Description = "Mace Mastery",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "PR_IMPOSITIO" ] = {
	Id = 66,
	Description = "Impositio Manus",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 3000,
	SkillData1 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 13,
			[2] = 16,
			[3] = 19,
			[4] = 22,
			[5] = 25,
			[6] = 28,
			[7] = 31,
			[8] = 34,
			[9] = 37,
			[10] = 40
		}
	}
},
[ "PR_SUFFRAGIUM" ] = {
	Id = 67,
	Description = "Suffragium",
	MaxLevel = 3,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 30000,
		[2] = 20000,
		[3] = 10000,
		[4] = 1,
		[5] = 1,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 8
	}
},
[ "PR_ASPERSIO" ] = {
	Id = 68,
	Description = "Aspersio",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		IgnoreElement = true,
		DamageBehavior.Ignore_Soft_Def
	},
	InterruptCast = true,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 60000,
		[2] = 90000,
		[3] = 120000,
		[4] = 150000,
		[5] = 180000,
		[6] = 210000,
		[7] = 240000,
		[8] = 270000,
		[9] = 300000,
		[10] = 330000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 14,
			[2] = 18,
			[3] = 22,
			[4] = 26,
			[5] = 30,
			[6] = 34,
			[7] = 38,
			[8] = 42,
			[9] = 46,
			[10] = 50
		},
		Items = {
			Item[ "Holy_Water" ] = 1
		}
	}
},
{
	Id = 69,
	Name = "PR_BENEDICTIO",
	Description = "B.S. Sacramenti",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.EnsembleSkill,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect,
		DamageBehavior.Ignore_Soft_Def
	},
	SplashRange = 1,
	InterruptCast = true,
	SkillData1 = {
		[1] = 40000,
		[2] = 80000,
		[3] = 120000,
		[4] = 160000,
		[5] = 200000,
		[6] = 240000,
		[7] = 280000,
		[8] = 320000,
		[9] = 360000,
		[10] = 400000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20
	}
},
[ "PR_SANCTUARY" ] = {
	Id = 70,
	Description = "Sanctuary",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.Ignore_Soft_Def
	},
	InterruptCast = true,
	KnockBackTiles = 1,
	CastTime = 4000,
	SkillData1 = {
		[1] = 4000,
		[2] = 7000,
		[3] = 10000,
		[4] = 13000,
		[5] = 16000,
		[6] = 19000,
		[7] = 22000,
		[8] = 25000,
		[9] = 28000,
		[10] = 31000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 18,
			[3] = 21,
			[4] = 24,
			[5] = 27,
			[6] = 30,
			[7] = 33,
			[8] = 36,
			[9] = 39,
			[10] = 42
		},
		Items = {
			Item[ "Blue_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = 0x83,
		Layout = -1,
		Range = 1,
		Interval = 1000,
		Target = "All",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "PR_SLOWPOISON" ] = {
	Id = 71,
	Description = "Slow Poison",
	MaxLevel = 4,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 10000,
		[2] = 20000,
		[3] = 30000,
		[4] = 40000,
		[5] = 50000,
		[6] = 60000,
		[7] = 70000,
		[8] = 80000,
		[9] = 90000,
		[10] = 100000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 6,
			[2] = 8,
			[3] = 10,
			[4] = 12,
			[5] = 14,
			[6] = 16,
			[7] = 18,
			[8] = 20,
			[9] = 22,
			[10] = 24
		}
	}
},
[ "PR_STRECOVERY" ] = {
	Id = 72,
	Description = "Status Recovery",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 2000,
	SkillData2 = 30000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 5
	}
},
[ "PR_KYRIE" ] = {
	Id = 73,
	Description = "Kyrie Eleison",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1600,
	AfterCastActDelay = 2000,
	SkillData1 = 120000,
	FixedCastTime = 400,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 20,
			[3] = 20,
			[4] = 25,
			[5] = 25,
			[6] = 25,
			[7] = 30,
			[8] = 30,
			[9] = 30,
			[10] = 35
		}
	}
},
[ "PR_MAGNIFICAT" ] = {
	Id = 74,
	Description = "Magnificat",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	InterruptCast = true,
	CastTime = 3200,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	FixedCastTime = 800,
	Requirements = {
		SPCost = 40
	}
},
[ "PR_GLORIA" ] = {
	Id = 75,
	Description = "Gloria",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	InterruptCast = true,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20
	}
},
[ "PR_LEXDIVINA" ] = {
	Id = 76,
	Description = "Lex Divina",
	MaxLevel = 10,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	InterruptCast = true,
	AfterCastActDelay = 3000,
	SkillData1 = {
		[1] = 30000,
		[2] = 35000,
		[3] = 40000,
		[4] = 45000,
		[5] = 50000,
		[6] = 60000,
		[7] = 60000,
		[8] = 60000,
		[9] = 60000,
		[10] = 60000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 20,
			[3] = 20,
			[4] = 20,
			[5] = 20,
			[6] = 18,
			[7] = 16,
			[8] = 14,
			[9] = 12,
			[10] = 10
		}
	}
},
[ "PR_TURNUNDEAD" ] = {
	Id = 77,
	Description = "Turn Undead",
	MaxLevel = 10,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.Ignore_Equip_Atk,
		DamageBehavior.Ignore_Soft_Def
	},
	InterruptCast = true,
	CastTime = 800,
	AfterCastActDelay = 3000,
	FixedCastTime = 200,
	Requirements = {
		SPCost = 20
	}
},
[ "PR_LEXAETERNA" ] = {
	Id = 78,
	Description = "Lex Aeterna",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	InterruptCast = true,
	AfterCastActDelay = 3000,
	SkillData1 = 600000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "PR_MAGNUS" ] = {
	Id = 79,
	Description = "Magnus Exorcismus",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = 12000,
	AfterCastActDelay = 4000,
	SkillData1 = {
		[1] = 5000,
		[2] = 6000,
		[3] = 7000,
		[4] = 8000,
		[5] = 9000,
		[6] = 10000,
		[7] = 11000,
		[8] = 12000,
		[9] = 13000,
		[10] = 14000
	},
	FixedCastTime = 3000,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 42,
			[3] = 44,
			[4] = 46,
			[5] = 48,
			[6] = 50,
			[7] = 52,
			[8] = 54,
			[9] = 56,
			[10] = 58
		},
		Items = {
			Item[ "Blue_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = 0x84,
		Layout = -1,
		Range = 1,
		Interval = 3000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "WZ_FIREPILLAR" ] = {
	Id = 80,
	Description = "Fire Pillar",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.Ignore_Soft_Def
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 1,
		[4] = 1,
		[5] = 1,
		[6] = 2,
		[7] = 2,
		[8] = 2,
		[9] = 2,
		[10] = 2
	},
	NumberOfHits = {
		[1] = -3,
		[2] = -4,
		[3] = -5,
		[4] = -6,
		[5] = -7,
		[6] = -8,
		[7] = -9,
		[8] = -10,
		[9] = -11,
		[10] = -12
	},
	InterruptCast = true,
	SkillInstances = 5,
	CastTime = {
		[1] = 1920,
		[2] = 1728,
		[3] = 1536,
		[4] = 1344,
		[5] = 1152,
		[6] = 960,
		[7] = 768,
		[8] = 576,
		[9] = 384,
		[10] = 192
	},
	AfterCastActDelay = 1000,
	SkillData1 = 30000,
	SkillData2 = {
		[1] = 600,
		[2] = 800,
		[3] = 1000,
		[4] = 1200,
		[5] = 1400,
		[6] = 1600,
		[7] = 1800,
		[8] = 2000,
		[9] = 2200,
		[10] = 2400
	},
	FixedCastTime = {
		[1] = 480,
		[2] = 432,
		[3] = 384,
		[4] = 336,
		[5] = 288,
		[6] = 240,
		[7] = 192,
		[8] = 144,
		[9] = 96,
		[10] = 48
	},
	Requirements = {
		SPCost = 75
	},
	Placement = {
		Id = { 0x87, 0x88 },
		Range = 1,
		Interval = 2000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "WZ_SIGHTRASHER" ] = {
	Id = 81,
	Description = "Sightrasher",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	SplashRange = 3,
	InterruptCast = true,
	KnockBackTiles = 5,
	AfterCastActDelay = 2000,
	SkillData1 = 500,
	FixedCastTime = 80,
	Requirements = {
		SPCost = {
			[1] = 35,
			[2] = 37,
			[3] = 39,
			[4] = 41,
			[5] = 43,
			[6] = 45,
			[7] = 47,
			[8] = 49,
			[9] = 51,
			[10] = 53
		},
		State = PlayerState.Sight
	}
},
[ "WZ_METEOR" ] = {
	Id = 83,
	Description = "Meteor Storm",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	SplashRange = {
		[1] = 3,
		[2] = 3,
		[3] = 3,
		[4] = 3,
		[5] = 3,
		[6] = 3,
		[7] = 3,
		[8] = 3,
		[9] = 3,
		[10] = 3
	},
	NumberOfHits = {
		[1] = 1,
		[2] = 1,
		[3] = 2,
		[4] = 2,
		[5] = 3,
		[6] = 3,
		[7] = 4,
		[8] = 4,
		[9] = 5,
		[10] = 5
	},
	InterruptCast = true,
	CastTime = 9600,
	AfterCastActDelay = {
		[1] = 2000,
		[2] = 3000,
		[3] = 3000,
		[4] = 4000,
		[5] = 4000,
		[6] = 5000,
		[7] = 5000,
		[8] = 6000,
		[9] = 6000,
		[10] = 7000
	},
	SkillData1 = 500,
	SkillData2 = 5000,
	FixedCastTime = 2400,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 24,
			[3] = 30,
			[4] = 34,
			[5] = 40,
			[6] = 44,
			[7] = 50,
			[8] = 54,
			[9] = 60,
			[10] = 64
		}
	},
	Placement = {
		Id = 0x86,
		Range = 3,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "WZ_JUPITEL" ] = {
	Id = 84,
	Description = "Jupitel Thunder",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	NumberOfHits = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	InterruptCast = true,
	KnockBackTiles = {
		[1] = 2,
		[2] = 3,
		[3] = 3,
		[4] = 4,
		[5] = 4,
		[6] = 5,
		[7] = 5,
		[8] = 6,
		[9] = 6,
		[10] = 7
	},
	CastTime = {
		[1] = 1600,
		[2] = 1920,
		[3] = 2240,
		[4] = 2560,
		[5] = 2880,
		[6] = 3200,
		[7] = 3520,
		[8] = 3840,
		[9] = 4160,
		[10] = 4480
	},
	FixedCastTime = {
		[1] = 400,
		[2] = 480,
		[3] = 560,
		[4] = 640,
		[5] = 720,
		[6] = 800,
		[7] = 880,
		[8] = 960,
		[9] = 1040,
		[10] = 1120
	},
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 23,
			[3] = 26,
			[4] = 29,
			[5] = 32,
			[6] = 35,
			[7] = 38,
			[8] = 41,
			[9] = 44,
			[10] = 47
		}
	}
},
[ "WZ_VERMILION" ] = {
	Id = 85,
	Description = "Lord of Vermilion",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	NumberOfHits: -10,
	InterruptCast = true,
	CastTime = {
		[1] = 9600,
		[2] = 9280,
		[3] = 8960,
		[4] = 8640,
		[5] = 8320,
		[6] = 8000,
		[7] = 7680,
		[8] = 7360,
		[9] = 7040,
		[10] = 6720
	},
	AfterCastActDelay = 5000,
	SkillData1 = 4000,
	SkillData2 = {
		[1] = 5500,
		[2] = 6000,
		[3] = 6500,
		[4] = 7000,
		[5] = 7500,
		[6] = 8000,
		[7] = 8500,
		[8] = 9000,
		[9] = 9500,
		[10] = 10000
	},
	FixedCastTime = {
		[1] = 2400,
		[2] = 2320,
		[3] = 2240,
		[4] = 2160,
		[5] = 2080,
		[6] = 2000,
		[7] = 1920,
		[8] = 1840,
		[9] = 1760,
		[10] = 1680
	},
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 64,
			[3] = 68,
			[4] = 72,
			[5] = 76,
			[6] = 80,
			[7] = 84,
			[8] = 88,
			[9] = 92,
			[10] = 96
		}
	},
	Placement = {
		Id = 0x86,
		Layout = 5,
		Range = {
			[1] = 1,
			[2] = 1,
			[3] = 1,
			[4] = 1,
			[5] = 1,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		},
		Interval = 1250,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "WZ_WATERBALL" ] = {
	Id = 86,
	Description = "Water Ball",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	InterruptCast = true,
	CastTime = {
		[1] = 640,
		[2] = 1280,
		[3] = 1920,
		[4] = 2560,
		[5] = 3200,
		[6] = 3200,
		[7] = 3200,
		[8] = 3200,
		[9] = 3200,
		[10] = 3200
	},
	FixedCastTime = {
		[1] = 160,
		[2] = 320,
		[3] = 480,
		[4] = 640,
		[5] = 800,
		[6] = 800,
		[7] = 800,
		[8] = 800,
		[9] = 800,
		[10] = 800
	},
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 20,
			[3] = 20,
			[4] = 25,
			[5] = 25,
			[6] = 25,
			[7] = 25,
			[8] = 25,
			[9] = 25,
			[10] = 25
		},
		State = PlayerState.InWater
	}
},
[ "WZ_ICEWALL" ] = {
	Id = 87,
	Description = "Ice Wall",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 5000,
		[2] = 10000,
		[3] = 15000,
		[4] = 20000,
		[5] = 25000,
		[6] = 30000,
		[7] = 35000,
		[8] = 40000,
		[9] = 45000,
		[10] = 50000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20
	},
	Placement = {
		Id = 0x8d,
		Layout = -1,
		Interval = -1,
		Target = "All",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "WZ_FROSTNOVA" ] = {
	Id = 88,
	Description = "Frost Nova",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	InterruptCast = true,
	CastTime = {
		[1] = 640,
		[2] = 640,
		[3] = 576,
		[4] = 576,
		[5] = 512,
		[6] = 512,
		[7] = 448,
		[8] = 448,
		[9] = 384,
		[10] = 384
	},
	AfterCastActDelay = 200,
	SkillData2 = {
		[1] = 4000,
		[2] = 5000,
		[3] = 6000,
		[4] = 8000,
		[5] = 10000,
		[6] = 12000,
		[7] = 13000,
		[8] = 15000,
		[9] = 16000,
		[10] = 17000
	},
	FixedCastTime = {
		[1] = 160,
		[2] = 160,
		[3] = 144,
		[4] = 144,
		[5] = 128,
		[6] = 128,
		[7] = 112,
		[8] = 112,
		[9] = 96,
		[10] = 96
	},
	Requirements = {
		SPCost = {
			[1] = 45,
			[2] = 43,
			[3] = 41,
			[4] = 39,
			[5] = 37,
			[6] = 35,
			[7] = 33,
			[8] = 31,
			[9] = 29,
			[10] = 27
		}
	}
},
[ "WZ_STORMGUST" ] = {
	Id = 89,
	Description = "Storm Gust",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	InterruptCast = true,
	KnockBackTiles = 2,
	CastTime = {
		[1] = 3840,
		[2] = 4480,
		[3] = 5120,
		[4] = 5760,
		[5] = 6400,
		[6] = 7040,
		[7] = 7680,
		[8] = 8320,
		[9] = 8960,
		[10] = 9600
	},
	AfterCastActDelay = 5000,
	SkillData1 = 4600,
	SkillData2 = 12000,
	FixedCastTime = {
		[1] = 960,
		[2] = 1120,
		[3] = 1280,
		[4] = 1440,
		[5] = 1600,
		[6] = 1760,
		[7] = 1920,
		[8] = 2080,
		[9] = 2240,
		[10] = 2400
	},
	Requirements = {
		SPCost = 78
	},
	Placement = {
		Id = 0x86,
		Layout = 4,
		Range = 1,
		Interval = 450,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "WZ_EARTHSPIKE" ] = {
	Id = 90,
	Description = "Earth Spike",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = {
		[1] = 448,
		[2] = 896,
		[3] = 1344,
		[4] = 1792,
		[5] = 2240,
		[6] = 2240,
		[7] = 2240,
		[8] = 2240,
		[9] = 2240,
		[10] = 2240
	},
	AfterCastActDelay = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	FixedCastTime = {
		[1] = 112,
		[2] = 224,
		[3] = 336,
		[4] = 448,
		[5] = 560,
		[6] = 560,
		[7] = 560,
		[8] = 560,
		[9] = 560,
		[10] = 560
	},
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		}
	}
},
{
	Id = 91,
	Name = "WZ_HEAVENDRIVE",
	Description = "Heaven's Drive",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = {
		[1] = 640,
		[2] = 1280,
		[3] = 1920,
		[4] = 2560,
		[5] = 3200,
		[6] = 3200,
		[7] = 3200,
		[8] = 3200,
		[9] = 3200,
		[10] = 3200
	},
	AfterCastActDelay = 1000,
	SkillData1 = 500,
	FixedCastTime = {
		[1] = 160,
		[2] = 320,
		[3] = 480,
		[4] = 640,
		[5] = 800,
		[6] = 800,
		[7] = 800,
		[8] = 800,
		[9] = 800,
		[10] = 800
	},
	Requirements = {
		SPCost = {
			[1] = 28,
			[2] = 32,
			[3] = 36,
			[4] = 40,
			[5] = 44,
			[6] = 48,
			[7] = 52,
			[8] = 56,
			[9] = 60,
			[10] = 64
		}
	},
	Placement = {
		Id = 0x86,
		Layout = 2,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "WZ_QUAGMIRE" ] = {
	Id = 92,
	Description = "Quagmire",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 3,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 5000,
		[2] = 10000,
		[3] = 15000,
		[4] = 20000,
		[5] = 25000,
		[6] = 30000,
		[7] = 35000,
		[8] = 40000,
		[9] = 45000,
		[10] = 50000
	},
	SkillData2 = {
		[1] = 5000,
		[2] = 10000,
		[3] = 15000,
		[4] = 20000,
		[5] = 25000,
		[6] = 30000,
		[7] = 35000,
		[8] = 40000,
		[9] = 45000,
		[10] = 50000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 5,
			[2] = 10,
			[3] = 15,
			[4] = 20,
			[5] = 25,
			[6] = 30,
			[7] = 35,
			[8] = 40,
			[9] = 45,
			[10] = 50
		}
	},
	Placement = {
		Id = 0x8e,
		Layout = 2,
		Interval = -1,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "WZ_ESTIMATION" ] = {
	Id = 93,
	Description = "Sense",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 10
	}
},
[ "BS_IRON" ] = {
	Id = 94,
	Description = "Iron Tempering",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_STEEL" ] = {
	Id = 95,
	Description = "Steel Tempering",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_ENCHANTEDSTONE" ] = {
	Id = 96,
	Description = "Enchanted Stone Craft",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_ORIDEOCON" ] = {
	Id = 97,
	Description = "Oridecon Research",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_DAGGER" ] = {
	Id = 98,
	Description = "Smith Dagger",
	MaxLevel = 3,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_SWORD" ] = {
	Id = 99,
	Description = "Smith Sword",
	MaxLevel = 3,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
{
	Id = 100,
	Name = "BS_TWOHANDSWORD",
	Description = "Smith Two-handed Sword",
	MaxLevel = 3,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_AXE" ] = {
	Id = 101,
	Description = "Smith Axe",
	MaxLevel = 3,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_MACE" ] = {
	Id = 102,
	Description = "Smith Mace",
	MaxLevel = 3,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_KNUCKLE" ] = {
	Id = 103,
	Description = "Smith Knucklebrace",
	MaxLevel = 3,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_SPEAR" ] = {
	Id = 104,
	Description = "Smith Spear",
	MaxLevel = 3,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_HILTBINDING" ] = {
	Id = 105,
	Description = "Hilt Binding",
	MaxLevel = 1,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_FINDINGORE" ] = {
	Id = 106,
	Description = "Ore Discovery",
	MaxLevel = 1,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_WEAPONRESEARCH" ] = {
	Id = 107,
	Description = "Weaponry Research",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_REPAIRWEAPON" ] = {
	Id = 108,
	Description = "Weapon Repair",
	MaxLevel = 1,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2500,
	FixedCastTime = 2500,
	Requirements = {
		SPCost = 30
	}
},
[ "BS_SKINTEMPER" ] = {
	Id = 109,
	Description = "Skin Tempering",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_HAMMERFALL" ] = {
	Id = 110,
	Description = "Hammer Fall",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 2,
		[3] = 2,
		[4] = 2,
		[5] = 2,
		[6] = 14,
		[7] = 14,
		[8] = 14,
		[9] = 14,
		[10] = 14
	},
	SkillData2 = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		WeaponTypes = {
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace
		}
	}
},
[ "BS_ADRENALINE" ] = {
	Id = 111,
	Description = "Adrenaline Rush",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	SkillData1 = {
		[1] = 30000,
		[2] = 60000,
		[3] = 90000,
		[4] = 120000,
		[5] = 150000,
		[6] = 180000,
		[7] = 210000,
		[8] = 240000,
		[9] = 270000,
		[10] = 300000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 23,
			[3] = 26,
			[4] = 29,
			[5] = 32,
			[6] = 35,
			[7] = 38,
			[8] = 41,
			[9] = 44,
			[10] = 47
		},
		WeaponTypes = {
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace
		}
	}
},
[ "BS_WEAPONPERFECT" ] = {
	Id = 112,
	Description = "Weapon Perfection",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	SkillData1 = {
		[1] = 10000,
		[2] = 20000,
		[3] = 30000,
		[4] = 40000,
		[5] = 50000,
		[6] = 60000,
		[7] = 70000,
		[8] = 80000,
		[9] = 90000,
		[10] = 100000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 16,
			[3] = 14,
			[4] = 12,
			[5] = 10,
			[6] = 8,
			[7] = 6,
			[8] = 4,
			[9] = 2,
			[10] = 1
		}
	}
},
{
	Id = 113,
	Name = "BS_OVERTHRUST",
	Description = "Power-Thrust",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	SkillData1 = {
		[1] = 20000,
		[2] = 40000,
		[3] = 60000,
		[4] = 80000,
		[5] = 100000,
		[6] = 120000,
		[7] = 140000,
		[8] = 160000,
		[9] = 180000,
		[10] = 200000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 16,
			[3] = 14,
			[4] = 12,
			[5] = 10,
			[6] = 8,
			[7] = 6,
			[8] = 4,
			[9] = 2,
			[10] = 1
		}
	}
},
[ "BS_MAXIMIZE" ] = {
	Id = 114,
	Description = "Maximize Power",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 1000,
		[2] = 2000,
		[3] = 3000,
		[4] = 4000,
		[5] = 5000,
		[6] = 6000,
		[7] = 7000,
		[8] = 8000,
		[9] = 9000,
		[10] = 10000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "HT_SKIDTRAP" ] = {
	Id = 115,
	Description = "Skid Trap",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	KnockBackTiles = {
		[1] = 6,
		[2] = 7,
		[3] = 8,
		[4] = 9,
		[5] = 10,
		[6] = 11,
		[7] = 12,
		[8] = 13,
		[9] = 14,
		[10] = 15
	},
	SkillData1 = {
		[1] = 300000,
		[2] = 240000,
		[3] = 180000,
		[4] = 120000,
		[5] = 60000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Booby_Trap" ] = 1
		}
	},
	Placement = {
		Id = 0x90,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "HT_LANDMINE" ] = {
	Id = 116,
	Description = "Land Mine",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Misc,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 1,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 200000,
		[2] = 160000,
		[3] = 120000,
		[4] = 80000,
		[5] = 40000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData2 = 5000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Booby_Trap" ] = 1
		}
	},
	Placement = {
		Id = 0x93,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "HT_ANKLESNARE" ] = {
	Id = 117,
	Description = "Ankle Snare",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 250000,
		[2] = 200000,
		[3] = 150000,
		[4] = 100000,
		[5] = 50000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData2 = {
		[1] = 4000,
		[2] = 8000,
		[3] = 12000,
		[4] = 16000,
		[5] = 20000,
		[6] = 24000,
		[7] = 28000,
		[8] = 32000,
		[9] = 36000,
		[10] = 40000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 12,
		Items = {
			Item[ "Booby_Trap" ] = 1
		}
	},
	Placement = {
		Id = 0x91,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "HT_SHOCKWAVE" ] = {
	Id = 118,
	Description = "Shockwave Trap",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	SkillData1 = {
		[1] = 200000,
		[2] = 160000,
		[3] = 120000,
		[4] = 80000,
		[5] = 40000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 45,
		Items = {
			Item[ "Booby_Trap" ] = 2
		}
	},
	Placement = {
		Id = 0x94,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "HT_SANDMAN" ] = {
	Id = 119,
	Description = "Sandman",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	SkillData1 = {
		[1] = 150000,
		[2] = 120000,
		[3] = 90000,
		[4] = 60000,
		[5] = 30000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData2 = {
		[1] = 12000,
		[2] = 14000,
		[3] = 16000,
		[4] = 18000,
		[5] = 20000,
		[6] = 22000,
		[7] = 24000,
		[8] = 26000,
		[9] = 28000,
		[10] = 30000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 12,
		Items = {
			Item[ "Booby_Trap" ] = 1
		}
	},
	Placement = {
		Id = 0x95,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "HT_FLASHER" ] = {
	Id = 120,
	Description = "Flasher",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	SkillData1 = {
		[1] = 150000,
		[2] = 120000,
		[3] = 90000,
		[4] = 60000,
		[5] = 30000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData2 = {
		[1] = 10000,
		[2] = 11000,
		[3] = 12000,
		[4] = 13000,
		[5] = 14000,
		[6] = 15000,
		[7] = 16000,
		[8] = 17000,
		[9] = 18000,
		[10] = 19000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 12,
		Items = {
			Item[ "Booby_Trap" ] = 2
		}
	},
	Placement = {
		Id = 0x96,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "HT_FREEZINGTRAP" ] = {
	Id = 121,
	Description = "Freezing Trap",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 1,
	SkillData1 = {
		[1] = 150000,
		[2] = 120000,
		[3] = 90000,
		[4] = 60000,
		[5] = 30000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData2 = {
		[1] = 3000,
		[2] = 6000,
		[3] = 9000,
		[4] = 12000,
		[5] = 15000,
		[6] = 18000,
		[7] = 21000,
		[8] = 24000,
		[9] = 27000,
		[10] = 30000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Booby_Trap" ] = 2
		}
	},
	Placement = {
		Id = 0x97,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "HT_BLASTMINE" ] = {
	Id = 122,
	Description = "Blast Mine",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Misc,
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.SplitBetweenTargets,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 1,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 25000,
		[2] = 20000,
		[3] = 15000,
		[4] = 10000,
		[5] = 5000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Booby_Trap" ] = 1
		}
	},
	Placement = {
		Id = 0x8f,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "HT_CLAYMORETRAP" ] = {
	Id = 123,
	Description = "Claymore Trap",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Misc,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.SplitBetweenTargets,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 2,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 20000,
		[2] = 40000,
		[3] = 60000,
		[4] = 80000,
		[5] = 100000,
		[6] = 120000,
		[7] = 140000,
		[8] = 160000,
		[9] = 180000,
		[10] = 200000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 15,
		Items = {
			Item[ "Booby_Trap" ] = 2
		}
	},
	Placement = {
		Id = 0x98,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "HT_REMOVETRAP" ] = {
	Id = 124,
	Description = "Remove Trap",
	MaxLevel = 1,
	Range = 2,
	Hit = "BDT_SKILL",
	SkillType = {
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 5
	}
},
[ "HT_TALKIEBOX" ] = {
	Id = 125,
	Description = "Talkie Box",
	MaxLevel = 1,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 600000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 1,
		Items = {
			Item[ "Booby_Trap" ] = 1
		}
	},
	Placement = {
		Id = 0x99,
		Range = 1,
		Interval = 1000,
		Target = "All"
	}
},
[ "HT_BEASTBANE" ] = {
	Id = 126,
	Description = "Beast Bane",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "HT_FALCON" ] = {
	Id = 127,
	Description = "Falconry Mastery",
	MaxLevel = 1,
	AttackType = AttackType.Misc,
	NumberOfHits = 0
},
[ "HT_STEELCROW" ] = {
	Id = 128,
	Description = "Steel Crow",
	MaxLevel = 10,
	AttackType = AttackType.Misc,
	NumberOfHits = 0
},
[ "HT_BLITZBEAT" ] = {
	Id = 129,
	Description = "Blitz Beat",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 1,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = 800,
	AfterCastActDelay = 1000,
	FixedCastTime = 200,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 13,
			[3] = 16,
			[4] = 19,
			[5] = 22,
			[6] = 25,
			[7] = 28,
			[8] = 31,
			[9] = 34,
			[10] = 37
		},
		State = PlayerState.HasFalcon
	}
},
[ "HT_DETECTING" ] = {
	Id = 130,
	Description = "Detect",
	MaxLevel = 4,
	Range = {
		[1] = 3,
		[2] = 5,
		[3] = 7,
		[4] = 9,
		[5] = 11,
		[6] = 13,
		[7] = 15,
		[8] = 17,
		[9] = 19,
		[10] = 21
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	Requirements = {
		SPCost = 8,
		State = PlayerState.HasFalcon
	}
},
[ "HT_SPRINGTRAP" ] = {
	Id = 131,
	Description = "Spring Trap",
	MaxLevel = 5,
	Range = {
		[1] = 4,
		[2] = 5,
		[3] = 6,
		[4] = 7,
		[5] = 8,
		[6] = 9,
		[7] = 10,
		[8] = 11,
		[9] = 12,
		[10] = 13
	},
	Hit = "BDT_SKILL",
	SkillType = {
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 10,
		State = PlayerState.HasFalcon
	}
},
[ "AS_RIGHT" ] = {
	Id = 132,
	Description = "Righthand Mastery",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "AS_LEFT" ] = {
	Id = 133,
	Description = "Lefthand Mastery",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "AS_KATAR" ] = {
	Id = 134,
	Description = "Katar Mastery",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "AS_CLOAKING" ] = {
	Id = 135,
	Description = "Cloaking",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 500,
		[2] = 1000,
		[3] = 2000,
		[4] = 3000,
		[5] = 4000,
		[6] = 5000,
		[7] = 6000,
		[8] = 7000,
		[9] = 8000,
		[10] = 9000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15
	}
},
[ "AS_SONICBLOW" ] = {
	Id = 136,
	Description = "Sonic Blow",
	MaxLevel = 10,
	Range = 1,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -8,
	AfterCastWalkDelay = 2000,
	SkillData2 = 5000,
	FixedCastTime = 0,
	SkillDelayOptions = {
		SkillDelayOptions.IgnoreStatusEffects
	},
	Requirements = {
		SPCost = {
			[1] = 16,
			[2] = 18,
			[3] = 20,
			[4] = 22,
			[5] = 24,
			[6] = 26,
			[7] = 28,
			[8] = 30,
			[9] = 32,
			[10] = 34
		},
		WeaponTypes = {
			WeaponType.Katar
		}
	}
},
[ "AS_GRIMTOOTH" ] = {
	Id = 137,
	Description = "Grimtooth",
	MaxLevel = 5,
	Range = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	Requirements = {
		SPCost = 3,
		WeaponTypes = {
			WeaponType.Katar
		},
		State = PlayerState.Hiding
	}
},
[ "AS_ENCHANTPOISON" ] = {
	Id = 138,
	Description = "Enchant Poison",
	MaxLevel = 10,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.OnlyParty
	},
	AttackType = AttackType.Weapon,
	Element = Element.Poison,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	SkillData2 = {
		[1] = 10000,
		[2] = 20000,
		[3] = 30000,
		[4] = 40000,
		[5] = 50000,
		[6] = 60000,
		[7] = 70000,
		[8] = 80000,
		[9] = 90000,
		[10] = 100000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20
	}
},
[ "AS_POISONREACT" ] = {
	Id = 139,
	Description = "Poison React",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	SkillData1 = {
		[1] = 20000,
		[2] = 25000,
		[3] = 30000,
		[4] = 35000,
		[5] = 40000,
		[6] = 45000,
		[7] = 50000,
		[8] = 55000,
		[9] = 60000,
		[10] = 65000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 25,
			[2] = 30,
			[3] = 35,
			[4] = 40,
			[5] = 45,
			[6] = 50,
			[7] = 55,
			[8] = 60,
			[9] = 45,
			[10] = 45
		}
	}
},
[ "AS_VENOMDUST" ] = {
	Id = 140,
	Description = "Venom Dust",
	MaxLevel = 10,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	Element = Element.Poison,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 5000,
		[2] = 10000,
		[3] = 15000,
		[4] = 20000,
		[5] = 25000,
		[6] = 30000,
		[7] = 35000,
		[8] = 40000,
		[9] = 45000,
		[10] = 50000
	},
	SkillData2 = {
		[1] = 15000,
		[2] = 20000,
		[3] = 25000,
		[4] = 30000,
		[5] = 35000,
		[6] = 40000,
		[7] = 45000,
		[8] = 50000,
		[9] = 55000,
		[10] = 60000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20,
		Items = {
			Item[ "Red_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = 0x92,
		Layout = -1,
		Range = 1,
		Interval = 1000,
		Target = "Enemy"
	}
},
[ "AS_SPLASHER" ] = {
	Id = 141,
	Description = "Venom Splasher",
	MaxLevel = 10,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		IgnoreElement = true,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 2,
	InterruptCast = true,
	CastTime = 500,
	SkillData1 = {
		[1] = 5000,
		[2] = 5500,
		[3] = 6000,
		[4] = 6500,
		[5] = 7000,
		[6] = 7500,
		[7] = 8000,
		[8] = 8500,
		[9] = 9000,
		[10] = 9500
	},
	SkillData2 = {
		[1] = 15000,
		[2] = 20000,
		[3] = 25000,
		[4] = 30000,
		[5] = 35000,
		[6] = 40000,
		[7] = 45000,
		[8] = 50000,
		[9] = 55000,
		[10] = 60000
	},
	CoolDown = {
		[1] = 7500,
		[2] = 8000,
		[3] = 8500,
		[4] = 9000,
		[5] = 9500,
		[6] = 10000,
		[7] = 10500,
		[8] = 11000,
		[9] = 11500,
		[10] = 12000
	},
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		},
		Items = {
			Item[ "Red_Gemstone" ] = 1
		}
	}
},
[ "NV_FIRSTAID" ] = {
	Id = 142,
	Description = "First Aid",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 3
	}
},
[ "NV_TRICKDEAD" ] = {
	Id = 143,
	Description = "Play Dead",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 600000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 5
	}
},
{
	Id = 144,
	Name = "SM_MOVINGRECOVERY",
	Description = "Moving HP-Recovery",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.LearntFromQuest
	},
	NumberOfHits = 0
},
[ "SM_FATALBLOW" ] = {
	Id = 145,
	Description = "Fatal Blow",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	NumberOfHits = 0,
	SkillData2 = 5000,
	FixedCastTime = 0
},
[ "SM_AUTOBERSERK" ] = {
	Id = 146,
	Description = "Auto Berserk",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 1
	}
},
[ "AC_MAKINGARROW" ] = {
	Id = 147,
	Description = "Arrow Crafting",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	Requirements = {
		SPCost = 10,
		State = PlayerState.NotOverweight
	}
},
[ "AC_CHARGEARROW" ] = {
	Id = 148,
	Description = "Arrow Repel",
	MaxLevel = 1,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	KnockBackTiles = 6,
	FixedCastTime = 1500,
	Requirements = {
		SPCost = 15,
		WeaponTypes = {
			WeaponType.Bow
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	}
},
[ "TF_SPRINKLESAND" ] = {
	Id = 149,
	Description = "Sand Attack",
	MaxLevel = 1,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	Element = Element.Earth,
	SkillData2 = 10000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 9
	}
},
[ "TF_BACKSLIDING" ] = {
	Id = 150,
	Description = "Back Slide",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	KnockBackTiles = 5,
	Requirements = {
		SPCost = 7
	}
},
[ "TF_PICKSTONE" ] = {
	Id = 151,
	Description = "Find Stone",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	FixedCastTime = 500,
	Requirements = {
		SPCost = 3,
		State = PlayerState.NotOverweight
	}
},
[ "TF_THROWSTONE" ] = {
	Id = 152,
	Description = "Stone Fling",
	MaxLevel = 1,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	AfterCastActDelay = 100,
	SkillData1 = 5000,
	SkillData2 = 8000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 2,
		Items = {
			Item[ "Stone" ] = 1
		}
	}
},
[ "MC_CARTREVOLUTION" ] = {
	Id = 153,
	Description = "Cart Revolution",
	MaxLevel = 1,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	KnockBackTiles = 2,
	Requirements = {
		SPCost = 12,
		State = PlayerState.HasCart
	}
},
[ "MC_CHANGECART" ] = {
	Id = 154,
	Description = "Change Cart",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 40,
		State = PlayerState.HasCart
	}
},
[ "MC_LOUD" ] = {
	Id = 155,
	Description = "Crazy Uproar",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 300000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 8
	}
},
[ "AL_HOLYLIGHT" ] = {
	Id = 156,
	Description = "Holy Light",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	InterruptCast = true,
	CastTime = 1600,
	FixedCastTime = 400,
	Requirements = {
		SPCost = 15
	}
},
[ "MG_ENERGYCOAT" ] = {
	Id = 157,
	Description = "Energy Coat",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 300000,
	FixedCastTime = 5000,
	Requirements = {
		SPCost = 30
	}
},
[ "NPC_PIERCINGATT" ] = {
	Id = 158,
	Description = "Piercing Attack",
	MaxLevel = 10,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement
},
[ "NPC_MENTALBREAKER" ] = {
	Id = 159,
	Description = "Spirit Destruction",
	MaxLevel = 5,
	Range = -1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	}
},
[ "NPC_RANGEATTACK" ] = {
	Id = 160,
	Description = "Stand off attack",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon
},
[ "NPC_ATTRICHANGE" ] = {
	Id = 161,
	Description = "Attribute Change",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 1800000,
	FixedCastTime = 0
},
[ "NPC_CHANGEWATER" ] = {
	Id = 162,
	Description = "Water Attribute Change",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 1800000,
	FixedCastTime = 0
},
[ "NPC_CHANGEGROUND" ] = {
	Id = 163,
	Description = "Earth Attribute Change",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 1800000,
	FixedCastTime = 0
},
[ "NPC_CHANGEFIRE" ] = {
	Id = 164,
	Description = "Fire Attribute Change",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 1800000,
	FixedCastTime = 0
},
[ "NPC_CHANGEWIND" ] = {
	Id = 165,
	Description = "Wind Attribute Change",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 1800000,
	FixedCastTime = 0
},
[ "NPC_CHANGEPOISON" ] = {
	Id = 166,
	Description = "Poison Attribute Change",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Poison,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 1800000,
	FixedCastTime = 0
},
[ "NPC_CHANGEHOLY" ] = {
	Id = 167,
	Description = "Holy Attribute Change",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 1800000,
	FixedCastTime = 0
},
[ "NPC_CHANGEDARKNESS" ] = {
	Id = 168,
	Description = "Shadow Attribute Change",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Dark,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 1800000,
	FixedCastTime = 0
},
[ "NPC_CHANGETELEKINESIS" ] = {
	Id = 169,
	Description = "Ghost Attribute Change",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Ghost,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 1800000,
	FixedCastTime = 0
},
[ "NPC_CRITICALSLASH" ] = {
	Id = 170,
	Description = "Defense disregard attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.Ignore_Soft_Def
	}
},
{
	Id = 171,
	Name = "NPC_COMBOATTACK",
	Description = "Multi-stage Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = {
		[1] = -2,
		[2] = -3,
		[3] = -4,
		[4] = -5,
		[5] = -6,
		[6] = -7,
		[7] = -8,
		[8] = -9,
		[9] = -10,
		[10] = -11
	}
},
[ "NPC_GUIDEDATTACK" ] = {
	Id = 172,
	Description = "Guided Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	}
},
[ "NPC_SELFDESTRUCTION" ] = {
	Id = 173,
	Description = "Suicide bombing",
	MaxLevel = 10,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Misc,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.Ignore_Soft_Def
		DamageBehavior.IgnoreFlee,
		IgnoreDefCards = true
	},
	SplashRange = 5,
	KnockBackTiles = 3,
	SkillData1 = 3500,
	FixedCastTime = 0
},
[ "NPC_SPLASHATTACK" ] = {
	Id = 174,
	Description = "Splash attack",
	MaxLevel = 1,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3
},
[ "NPC_SUICIDE" ] = {
	Id = 175,
	Description = "Suicide",
	MaxLevel = 10,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.IgnoreFlee
	}
},
[ "NPC_POISON" ] = {
	Id = 176,
	Description = "Poison Attack",
	MaxLevel = 5,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SkillData2 = 60000,
	FixedCastTime = 0
},
[ "NPC_BLINDATTACK" ] = {
	Id = 177,
	Description = "Blind Attack",
	MaxLevel = 5,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SkillData2 = 30000,
	FixedCastTime = 0
},
[ "NPC_SILENCEATTACK" ] = {
	Id = 178,
	Description = "Silence Attack",
	MaxLevel = 5,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SkillData2 = 30000,
	FixedCastTime = 0
},
[ "NPC_STUNATTACK" ] = {
	Id = 179,
	Description = "Stun Attack",
	MaxLevel = 5,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SkillData2 = 5000,
	FixedCastTime = 0
},
[ "NPC_PETRIFYATTACK" ] = {
	Id = 180,
	Description = "Petrify Attack",
	MaxLevel = 5,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SkillData2 = 20000,
	FixedCastTime = 0
},
[ "NPC_CURSEATTACK" ] = {
	Id = 181,
	Description = "Curse Attack",
	MaxLevel = 5,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Dark,
	SkillData2 = 30000,
	FixedCastTime = 0
},
[ "NPC_SLEEPATTACK" ] = {
	Id = 182,
	Description = "Sleep attack",
	MaxLevel = 5,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SkillData2 = 30000,
	FixedCastTime = 0
},
[ "NPC_RANDOMATTACK" ] = {
	Id = 183,
	Description = "Random Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement
},
[ "NPC_WATERATTACK" ] = {
	Id = 184,
	Description = "Water Attribute Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Water
},
[ "NPC_GROUNDATTACK" ] = {
	Id = 185,
	Description = "Earth Attribute Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Earth
},
[ "NPC_FIREATTACK" ] = {
	Id = 186,
	Description = "Fire Attribute Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire
},
[ "NPC_WINDATTACK" ] = {
	Id = 187,
	Description = "Wind Attribute Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Wind
},
[ "NPC_POISONATTACK" ] = {
	Id = 188,
	Description = "Poison Attribute Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Poison
},
[ "NPC_HOLYATTACK" ] = {
	Id = 189,
	Description = "Holy Attribute Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Holy
},
[ "NPC_DARKNESSATTACK" ] = {
	Id = 190,
	Description = "Shadow Attribute Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Dark
},
[ "NPC_TELEKINESISATTACK" ] = {
	Id = 191,
	Description = "Ghost Attribute Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Ghost
},
[ "NPC_MAGICALATTACK" ] = {
	Id = 192,
	Description = "Demon Shock Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SkillData1 = 15000,
	FixedCastTime = 0
},
[ "NPC_METAMORPHOSIS" ] = {
	Id = 193,
	Description = "Metamorphosis",
	MaxLevel = 10,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "NPC_PROVOCATION" ] = {
	Id = 194,
	Description = "Provocation",
	MaxLevel = 10,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "NPC_SMOKING" ] = {
	Id = 195,
	Description = "Smoking",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		IgnoreElement = true,
		DamageBehavior.IgnoreFlee
	}
},
[ "NPC_SUMMONSLAVE" ] = {
	Id = 196,
	Description = "Follower Summons",
	MaxLevel = 10,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "NPC_EMOTION" ] = {
	Id = 197,
	Description = "Emotion",
	MaxLevel = 10,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "NPC_TRANSFORMATION" ] = {
	Id = 198,
	Description = "Transformation",
	MaxLevel = 10,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "NPC_BLOODDRAIN" ] = {
	Id = 199,
	Description = "Sucking Blood",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Dark,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	}
},
[ "NPC_ENERGYDRAIN" ] = {
	Id = 200,
	Description = "Energy Drain",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Dark
},
[ "NPC_KEEPING" ] = {
	Id = 201,
	Description = "Keeping",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 60000,
		[2] = 70000,
		[3] = 80000,
		[4] = 90000,
		[5] = 100000,
		[6] = 110000,
		[7] = 120000,
		[8] = 130000,
		[9] = 140000,
		[10] = 150000
	},
	FixedCastTime = 0
},
[ "NPC_DARKBREATH" ] = {
	Id = 202,
	Description = "Dark Breath",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Misc,
	Element = Element.Dark
},
[ "NPC_DARKBLESSING" ] = {
	Id = 203,
	Description = "Dark Blessing",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Dark,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "NPC_BARRIER" ] = {
	Id = 204,
	Description = "Barrier",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 60000,
		[2] = 70000,
		[3] = 80000,
		[4] = 90000,
		[5] = 100000,
		[6] = 110000,
		[7] = 120000,
		[8] = 130000,
		[9] = 140000,
		[10] = 150000
	},
	FixedCastTime = 0
},
[ "NPC_DEFENDER" ] = {
	Id = 205,
	Description = "Defender",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 60000,
		[2] = 70000,
		[3] = 80000,
		[4] = 90000,
		[5] = 100000,
		[6] = 110000,
		[7] = 120000,
		[8] = 130000,
		[9] = 140000,
		[10] = 150000
	},
	FixedCastTime = 0
},
[ "NPC_LICK" ] = {
	Id = 206,
	Description = "Lick",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData2 = 5000,
	FixedCastTime = 0
},
[ "NPC_HALLUCINATION" ] = {
	Id = 207,
	Description = "Hallucination",
	MaxLevel = 10,
	Range = 9,
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 40000,
		[3] = 50000,
		[4] = 60000,
		[5] = 70000,
		[6] = 80000,
		[7] = 90000,
		[8] = 100000,
		[9] = 110000,
		[10] = 120000
	},
	FixedCastTime = 0
},
[ "NPC_REBIRTH" ] = {
	Id = 208,
	Description = "Rebirth",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "NPC_SUMMONMONSTER" ] = {
	Id = 209,
	Description = "Monster Summons",
	MaxLevel = 10,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "RG_SNATCHER" ] = {
	Id = 210,
	Description = "Gank",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 0
},
[ "RG_STEALCOIN" ] = {
	Id = 211,
	Description = "Mug",
	MaxLevel = 10,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 15
	}
},
[ "RG_BACKSTAP" ] = {
	Id = 212,
	Description = "Back Stab",
	MaxLevel = 10,
	Range = -1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	AfterCastActDelay = 500,
	SkillData1 = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 16
	}
},
[ "RG_TUNNELDRIVE" ] = {
	Id = 213,
	Description = "Stalk",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "RG_RAID" ] = {
	Id = 214,
	Description = "Sightless Mind",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	SkillData1 = 5000,
	SkillData2 = 20000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20,
		State = PlayerState.Hiding
	}
},
[ "RG_STRIPWEAPON" ] = {
	Id = 215,
	Description = "Divest Weapon",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 560,
		[2] = 720,
		[3] = 880,
		[4] = 1140,
		[5] = 1200,
		[6] = 1200,
		[7] = 1200,
		[8] = 1200,
		[9] = 1200,
		[10] = 1200
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 75000,
		[2] = 90000,
		[3] = 105000,
		[4] = 120000,
		[5] = 135000,
		[6] = 150000,
		[7] = 165000,
		[8] = 180000,
		[9] = 195000,
		[10] = 210000
	},
	FixedCastTime = {
		[1] = 140,
		[2] = 180,
		[3] = 220,
		[4] = 260,
		[5] = 300,
		[6] = 300,
		[7] = 300,
		[8] = 300,
		[9] = 300,
		[10] = 300
	},
	Requirements = {
		SPCost = {
			[1] = 17,
			[2] = 19,
			[3] = 21,
			[4] = 23,
			[5] = 25,
			[6] = 27,
			[7] = 29,
			[8] = 31,
			[9] = 33,
			[10] = 35
		}
	}
},
[ "RG_STRIPSHIELD" ] = {
	Id = 216,
	Description = "Divest Shield",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 560,
		[2] = 720,
		[3] = 880,
		[4] = 1140,
		[5] = 1200,
		[6] = 1200,
		[7] = 1200,
		[8] = 1200,
		[9] = 1200,
		[10] = 1200
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 75000,
		[2] = 90000,
		[3] = 105000,
		[4] = 120000,
		[5] = 135000,
		[6] = 150000,
		[7] = 165000,
		[8] = 180000,
		[9] = 195000,
		[10] = 210000
	},
	FixedCastTime = {
		[1] = 140,
		[2] = 180,
		[3] = 220,
		[4] = 260,
		[5] = 300,
		[6] = 300,
		[7] = 300,
		[8] = 300,
		[9] = 300,
		[10] = 300
	},
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		}
	}
},
[ "RG_STRIPARMOR" ] = {
	Id = 217,
	Description = "Divest Armor",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 560,
		[2] = 720,
		[3] = 880,
		[4] = 1140,
		[5] = 1200,
		[6] = 1200,
		[7] = 1200,
		[8] = 1200,
		[9] = 1200,
		[10] = 1200
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 75000,
		[2] = 90000,
		[3] = 105000,
		[4] = 120000,
		[5] = 135000,
		[6] = 150000,
		[7] = 165000,
		[8] = 180000,
		[9] = 195000,
		[10] = 210000
	},
	FixedCastTime = {
		[1] = 140,
		[2] = 180,
		[3] = 220,
		[4] = 260,
		[5] = 300,
		[6] = 300,
		[7] = 300,
		[8] = 300,
		[9] = 300,
		[10] = 300
	},
	Requirements = {
		SPCost = {
			[1] = 17,
			[2] = 19,
			[3] = 21,
			[4] = 23,
			[5] = 25,
			[6] = 27,
			[7] = 29,
			[8] = 31,
			[9] = 33,
			[10] = 35
		}
	}
},
[ "RG_STRIPHELM" ] = {
	Id = 218,
	Description = "Divest Helm",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 560,
		[2] = 720,
		[3] = 880,
		[4] = 1140,
		[5] = 1200,
		[6] = 1200,
		[7] = 1200,
		[8] = 1200,
		[9] = 1200,
		[10] = 1200
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 75000,
		[2] = 90000,
		[3] = 105000,
		[4] = 120000,
		[5] = 135000,
		[6] = 150000,
		[7] = 165000,
		[8] = 180000,
		[9] = 195000,
		[10] = 210000
	},
	FixedCastTime = {
		[1] = 140,
		[2] = 180,
		[3] = 220,
		[4] = 260,
		[5] = 300,
		[6] = 300,
		[7] = 300,
		[8] = 300,
		[9] = 300,
		[10] = 300
	},
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		}
	}
},
[ "RG_INTIMIDATE" ] = {
	Id = 219,
	Description = "Snatch",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = {
			[1] = 13,
			[2] = 16,
			[3] = 19,
			[4] = 22,
			[5] = 25,
			[6] = 28,
			[7] = 31,
			[8] = 34,
			[9] = 37,
			[10] = 40
		}
	}
},
[ "RG_GRAFFITI" ] = {
	Id = 220,
	Description = "Scribble",
	MaxLevel = 1,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 180000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15,
		Items = {
			Item[ "Red_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = 0xb0,
		Interval = -1,
		Target = "All"
	}
},
[ "RG_FLAGGRAFFITI" ] = {
	Id = 221,
	Description = "Piece",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 10
	}
},
[ "RG_CLEANER" ] = {
	Id = 222,
	Description = "Remover",
	MaxLevel = 1,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 5,
	Requirements = {
		SPCost = 5
	}
},
[ "RG_GANGSTER" ] = {
	Id = 223,
	Description = "Slyness",
	MaxLevel = 1,
	SplashRange = 1,
	NumberOfHits = 0
},
[ "RG_COMPULSION" ] = {
	Id = 224,
	Description = "Haggle",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "RG_PLAGIARISM" ] = {
	Id = 225,
	Description = "Intimidate",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "AM_AXEMASTERY" ] = {
	Id = 226,
	Description = "Axe Mastery",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "AM_LEARNINGPOTION" ] = {
	Id = 227,
	Description = "Potion Research",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "AM_PHARMACY" ] = {
	Id = 228,
	Description = "Prepare Potion",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	Requirements = {
		SPCost = 5,
		Items = {
			Item[ "Medicine_Bowl" ] = 1
		}
	}
},
[ "AM_DEMONSTRATION" ] = {
	Id = 229,
	Description = "Bomb",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.Ignore_Equip_Atk
	},
	InterruptCast = true,
	CastTime = 800,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 40000,
		[2] = 45000,
		[3] = 50000,
		[4] = 55000,
		[5] = 60000,
		[6] = 65000,
		[7] = 70000,
		[8] = 75000,
		[9] = 80000,
		[10] = 85000
	},
	FixedCastTime = 200,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Fire_Bottle" ] = 1
		}
	},
	Placement = {
		Id = 0xb1,
		Range = 1,
		Interval = 500,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "AM_ACIDTERROR" ] = {
	Id = 230,
	Description = "Acid Terror",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.Ignore_Equip_Atk,
		DamageBehavior.IgnoreFlee
	},
	InterruptCast = true,
	CastTime = 500,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 3,
		[2] = 7,
		[3] = 10,
		[4] = 12,
		[5] = 13,
		[6] = 13,
		[7] = 13,
		[8] = 13,
		[9] = 13,
		[10] = 13
	},
	SkillData2 = 120000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = 15,
		Items = {
			Item[ "Acid_Bottle" ] = 1
		}
	}
},
[ "AM_POTIONPITCHER" ] = {
	Id = 231,
	Description = "Aid Potion",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.OnlyParty,
		SkillBehavior.OnlyGuild
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 500,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 1,
		Items = {
			Item[ "Red_Potion" ] = 1,
			Item[ "Orange_Potion" ] = 1,
			Item[ "Yellow_Potion" ] = 1,
			Item[ "White_Potion" ] = 1,
			Item[ "Blue_Potion" ] = 1,
			Item[ "Fruit_Of_Mastela" ] = 1,
			Item[ "Royal_Jelly" ] = 1,
			Item[ "Seed_Of_Yggdrasil" ] = 1,
			Item[ "Yggdrasilberry" ] = 1,
			Item[ "Berserk_Potion" ] = 1
		}
	}
},
[ "AM_CANNIBALIZE" ] = {
	Id = 232,
	Description = "Summon Flora",
	MaxLevel = 5,
	Range = 4,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillInstances = 5,
	CastTime = 1600,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 300000,
		[2] = 240000,
		[3] = 180000,
		[4] = 120000,
		[5] = 60000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = 400,
	Requirements = {
		SPCost = 20,
		Items = {
			Item[ "MenEater_Plant_Bottle" ] = 1
		}
	}
},
[ "AM_SPHEREMINE" ] = {
	Id = 233,
	Description = "Summon Marine Sphere",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillInstances = 3,
	CastTime = 1600,
	AfterCastActDelay = 500,
	SkillData1 = 30000,
	FixedCastTime = 400,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Mini_Bottle" ] = 1
		}
	}
},
[ "AM_CP_WEAPON" ] = {
	Id = 234,
	Description = "Alchemical Weapon",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 120000,
		[2] = 240000,
		[3] = 360000,
		[4] = 480000,
		[5] = 600000,
		[6] = 720000,
		[7] = 840000,
		[8] = 960000,
		[9] = 1080000,
		[10] = 1200000
	},
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 30,
		Items = {
			Item[ "Coating_Bottle" ] = 1
		}
	}
},
[ "AM_CP_SHIELD" ] = {
	Id = 235,
	Description = "Synthesized Shield",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 120000,
		[2] = 240000,
		[3] = 360000,
		[4] = 480000,
		[5] = 600000,
		[6] = 720000,
		[7] = 840000,
		[8] = 960000,
		[9] = 1080000,
		[10] = 1200000
	},
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 25,
		Items = {
			Item[ "Coating_Bottle" ] = 1
		}
	}
},
[ "AM_CP_ARMOR" ] = {
	Id = 236,
	Description = "Synthetic Armor",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 120000,
		[2] = 240000,
		[3] = 360000,
		[4] = 480000,
		[5] = 600000,
		[6] = 720000,
		[7] = 840000,
		[8] = 960000,
		[9] = 1080000,
		[10] = 1200000
	},
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 25,
		Items = {
			Item[ "Coating_Bottle" ] = 1
		}
	}
},
[ "AM_CP_HELM" ] = {
	Id = 237,
	Description = "Biochemical Helm",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 120000,
		[2] = 240000,
		[3] = 360000,
		[4] = 480000,
		[5] = 600000,
		[6] = 720000,
		[7] = 840000,
		[8] = 960000,
		[9] = 1080000,
		[10] = 1200000
	},
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 25,
		Items = {
			Item[ "Coating_Bottle" ] = 1
		}
	}
},
[ "AM_BIOETHICS" ] = {
	Id = 238,
	Description = "Bioethics",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.LearntFromQuest
	},
	NumberOfHits = 0
},
[ "AM_CALLHOMUN" ] = {
	Id = 243,
	Description = "Call Homunculus",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 1,
	NumberOfHits = 0,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Germination_Breed" ] = 1
		}
	}
},
[ "AM_REST" ] = {
	Id = 244,
	Description = "Vaporize",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	Requirements = {
		SPCost = 50
	}
},
[ "AM_RESURRECTHOMUN" ] = {
	Id = 247,
	Description = "Homunculus Resurrection",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 1,
	NumberOfHits = 0,
	CastTime = 2000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 74,
			[2] = 68,
			[3] = 62,
			[4] = 56,
			[5] = 50,
			[6] = 44,
			[7] = 38,
			[8] = 32,
			[9] = 26,
			[10] = 20
		}
	}
},
[ "CR_TRUST" ] = {
	Id = 248,
	Description = "Faith",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "CR_AUTOGUARD" ] = {
	Id = 249,
	Description = "Guard",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 300000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		},
		State = PlayerState.Equipped_Shield
	}
},
[ "CR_SHIELDCHARGE" ] = {
	Id = 250,
	Description = "Smite",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	KnockBackTiles = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	SkillData2 = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		State = PlayerState.Equipped_Shield
	}
},
[ "CR_SHIELDBOOMERANG" ] = {
	Id = 251,
	Description = "Shield Boomerang",
	MaxLevel = 5,
	Range = {
		[1] = 3,
		[2] = 5,
		[3] = 7,
		[4] = 9,
		[5] = 11,
		[6] = 13,
		[7] = 15,
		[8] = 17,
		[9] = 19,
		[10] = 21
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	AfterCastActDelay = 700,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 12,
		State = PlayerState.Equipped_Shield
	}
},
[ "CR_REFLECTSHIELD" ] = {
	Id = 252,
	Description = "Shield Reflect",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	SkillData1 = 300000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 35,
			[2] = 40,
			[3] = 45,
			[4] = 50,
			[5] = 55,
			[6] = 60,
			[7] = 65,
			[8] = 70,
			[9] = 75,
			[10] = 80
		},
		State = PlayerState.Equipped_Shield
	}
},
[ "CR_HOLYCROSS" ] = {
	Id = 253,
	Description = "Holy Cross",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.Holy,
	NumberOfHits: -2,
	SkillData2 = {
		[1] = 10000,
		[2] = 11000,
		[3] = 12000,
		[4] = 13000,
		[5] = 14000,
		[6] = 15000,
		[7] = 16000,
		[8] = 17000,
		[9] = 18000,
		[10] = 19000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 11,
			[2] = 12,
			[3] = 13,
			[4] = 14,
			[5] = 15,
			[6] = 16,
			[7] = 17,
			[8] = 18,
			[9] = 19,
			[10] = 20
		}
	}
},
[ "CR_GRANDCROSS" ] = {
	Id = 254,
	Description = "Grand Cross",
	MaxLevel = 10,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.Ignore_Equip_Atk,
		DamageBehavior.IgnoreFlee
	},
	CastDefRate = 33,
	CastTime = 1500,
	AfterCastActDelay = 1500,
	AfterCastWalkDelay = 900,
	SkillData1 = 900,
	SkillData2 = {
		[1] = 10000,
		[2] = 11000,
		[3] = 12000,
		[4] = 13000,
		[5] = 14000,
		[6] = 15000,
		[7] = 16000,
		[8] = 17000,
		[9] = 18000,
		[10] = 19000
	},
	FixedCastTime = 1500,
	Requirements = {
		SPCost = {
			[1] = 37,
			[2] = 44,
			[3] = 51,
			[4] = 58,
			[5] = 65,
			[6] = 72,
			[7] = 79,
			[8] = 86,
			[9] = 93,
			[10] = 100
		},
		HPRateCost = 20
	},
	Placement = {
		Id = 0x86,
		Layout = -1,
		Interval = 300,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "CR_DEVOTION" ] = {
	Id = 255,
	Description = "Sacrifice",
	MaxLevel = 5,
	Range = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf,
		SkillBehavior.OnlyParty
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1500,
	SkillData2 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	FixedCastTime = 1500,
	Requirements = {
		SPCost = 25
	}
},
[ "CR_PROVIDENCE" ] = {
	Id = 256,
	Description = "Resistant Souls",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1500,
	SkillData1 = 180000,
	FixedCastTime = 1500,
	Requirements = {
		SPCost = 30
	}
},
[ "CR_DEFENDER" ] = {
	Id = 257,
	Description = "Defending Aura",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 800,
	SkillData1 = 180000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 30,
		State = PlayerState.Equipped_Shield
	}
},
[ "CR_SPEARQUICKEN" ] = {
	Id = 258,
	Description = "Spear Quicken",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 60000,
		[3] = 90000,
		[4] = 120000,
		[5] = 150000,
		[6] = 180000,
		[7] = 210000,
		[8] = 240000,
		[9] = 270000,
		[10] = 300000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 24,
			[2] = 28,
			[3] = 32,
			[4] = 36,
			[5] = 40,
			[6] = 44,
			[7] = 48,
			[8] = 52,
			[9] = 56,
			[10] = 60
		},
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "MO_IRONHAND" ] = {
	Id = 259,
	Description = "Iron Fists",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "MO_SPIRITSRECOVERY" ] = {
	Id = 260,
	Description = "Spiritual Cadence",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "MO_CALLSPIRITS" ] = {
	Id = 261,
	Description = "Summon Spirit Sphere",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 500,
	SkillData1 = 600000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = 8
	}
},
[ "MO_ABSORBSPIRITS" ] = {
	Id = 262,
	Description = "Absorb Spirit Sphere",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 5
	}
},
[ "MO_TRIPLEATTACK" ] = {
	Id = 263,
	Description = "Raging Trifecta Blow",
	MaxLevel = 10,
	Range = -1,
	Hit = "BDT_MULTIHIT",
	SkillInfo = {
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -3,
	FixedCastTime = 0,
	SkillDelayOptions = {
		SkillDelayOptions.IgnoreStatusEffects
	}
},
[ "MO_BODYRELOCATION" ] = {
	Id = 264,
	Description = "Snap",
	MaxLevel = 1,
	Range = 18,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 14,
		SpiritSphereCost = 1
	}
},
[ "MO_DODGE" ] = {
	Id = 265,
	Description = "Dodge",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "MO_INVESTIGATE" ] = {
	Id = 266,
	Description = "Occult Impaction",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	CastTime = 500,
	AfterCastActDelay = 500,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 14,
			[3] = 17,
			[4] = 19,
			[5] = 20,
			[6] = 20,
			[7] = 20,
			[8] = 20,
			[9] = 20,
			[10] = 20
		},
		SpiritSphereCost = 1
	}
},
[ "MO_FINGEROFFENSIVE" ] = {
	Id = 267,
	Description = "Throw Spirit Sphere",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	CastTime = 500,
	AfterCastActDelay = 500,
	AfterCastWalkDelay = {
		[1] = 0,
		[2] = 200,
		[3] = 400,
		[4] = 600,
		[5] = 800,
		[6] = 1000,
		[7] = 1200,
		[8] = 1400,
		[9] = 1600,
		[10] = 1800
	},
	FixedCastTime = 500,
	Requirements = {
		SPCost = 10,
		SpiritSphereCost = {
			[1] = 1,
			[2] = 2,
			[3] = 3,
			[4] = 4,
			[5] = 5,
			[6] = 6,
			[7] = 7,
			[8] = 8,
			[9] = 9,
			[10] = 10
		}
	}
},
[ "MO_STEELBODY" ] = {
	Id = 268,
	Description = "Mental Strength",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 2500,
	SkillData1 = {
		[1] = 30000,
		[2] = 60000,
		[3] = 90000,
		[4] = 120000,
		[5] = 150000,
		[6] = 180000,
		[7] = 210000,
		[8] = 240000,
		[9] = 270000,
		[10] = 300000
	},
	FixedCastTime = 2500,
	Requirements = {
		SPCost = 200,
		SpiritSphereCost = 5
	}
},
[ "MO_BLADESTOP" ] = {
	Id = 269,
	Description = "Root",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 500,
		[2] = 700,
		[3] = 900,
		[4] = 1100,
		[5] = 1300,
		[6] = 1500,
		[7] = 1700,
		[8] = 1900,
		[9] = 2100,
		[10] = 2300
	},
	SkillData2 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		WeaponTypes = {
			WeaponType.Fist,
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar,
			WeaponType.Revolver,
			WeaponType.Rifle,
			WeaponType.GatlingGun,
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher,
			WeaponType.FuumaShuriken
		},
		SpiritSphereCost = 1
	}
},
[ "MO_EXPLOSIONSPIRITS" ] = {
	Id = 270,
	Description = "Fury",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	SkillData1 = 180000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15,
		SpiritSphereCost = 5
	}
},
[ "MO_EXTREMITYFIST" ] = {
	Id = 271,
	Description = "Asura Strike",
	MaxLevel = 5,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.Ignore_Soft_Def
		DamageBehavior.IgnoreFlee
	},
	InterruptCast = true,
	CastTime = {
		[1] = 2000,
		[2] = 1750,
		[3] = 1500,
		[4] = 1250,
		[5] = 1000,
		[6] = 500,
		[7] = 1000,
		[8] = 1000,
		[9] = 1000,
		[10] = 1000
	},
	AfterCastActDelay = {
		[1] = 3000,
		[2] = 2500,
		[3] = 2000,
		[4] = 1500,
		[5] = 1000,
		[6] = 500,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData1 = 10000,
	SkillData2 = 300000,
	FixedCastTime = {
		[1] = 2000,
		[2] = 1750,
		[3] = 1500,
		[4] = 1250,
		[5] = 1000,
		[6] = 500,
		[7] = 1000,
		[8] = 1000,
		[9] = 1000,
		[10] = 1000
	},
	Requirements = {
		SPCost = 1,
		WeaponTypes = {
			WeaponType.Fist,
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar,
			WeaponType.Revolver,
			WeaponType.Rifle,
			WeaponType.GatlingGun,
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher,
			WeaponType.FuumaShuriken
		},
		State = PlayerState.CriticalExplosion,
		SpiritSphereCost = 5
	}
},
[ "MO_CHAINCOMBO" ] = {
	Id = 272,
	Description = "Raging Quadruple Blow",
	MaxLevel = 5,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -4,
	SkillDelayOptions = {
		SkillDelayOptions.IgnoreStatusEffects
	},
	Requirements = {
		SPCost = {
			[1] = 11,
			[2] = 12,
			[3] = 13,
			[4] = 14,
			[5] = 15,
			[6] = 16,
			[7] = 17,
			[8] = 18,
			[9] = 19,
			[10] = 20
		},
		WeaponTypes = {
			WeaponType.Fist,
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar,
			WeaponType.Revolver,
			WeaponType.Rifle,
			WeaponType.GatlingGun,
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher,
			WeaponType.FuumaShuriken
		}
	}
},
[ "MO_COMBOFINISH" ] = {
	Id = 273,
	Description = "Raging Thrust",
	MaxLevel = 5,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	SkillDelayOptions = {
		SkillDelayOptions.IgnoreStatusEffects
	},
	Requirements = {
		SPCost = {
			[1] = 11,
			[2] = 12,
			[3] = 13,
			[4] = 14,
			[5] = 15,
			[6] = 16,
			[7] = 17,
			[8] = 18,
			[9] = 19,
			[10] = 20
		},
		WeaponTypes = {
			WeaponType.Fist,
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar,
			WeaponType.Revolver,
			WeaponType.Rifle,
			WeaponType.GatlingGun,
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher,
			WeaponType.FuumaShuriken
		},
		SpiritSphereCost = 1
	}
},
[ "SA_ADVANCEDBOOK" ] = {
	Id = 274,
	Description = "Study",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "SA_CASTCANCEL" ] = {
	Id = 275,
	Description = "Cast Cancel",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 2
	}
},
[ "SA_MAGICROD" ] = {
	Id = 276,
	Description = "Magic Rod",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 400,
		[2] = 600,
		[3] = 800,
		[4] = 1000,
		[5] = 1200,
		[6] = 1400,
		[7] = 1600,
		[8] = 1800,
		[9] = 2000,
		[10] = 2200
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 2
	}
},
[ "SA_SPELLBREAKER" ] = {
	Id = 277,
	Description = "Spell Breaker",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 560,
	FixedCastTime = 140,
	Requirements = {
		SPCost = 10
	}
},
[ "SA_FREECAST" ] = {
	Id = 278,
	Description = "Free Cast",
	MaxLevel = 10,
	AttackType = AttackType.Magic,
	NumberOfHits = 0
},
[ "SA_AUTOSPELL" ] = {
	Id = 279,
	Description = "Hindsight",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 120000,
		[2] = 150000,
		[3] = 180000,
		[4] = 210000,
		[5] = 240000,
		[6] = 270000,
		[7] = 300000,
		[8] = 330000,
		[9] = 360000,
		[10] = 390000
	},
	FixedCastTime = 3000,
	Requirements = {
		SPCost = 35
	}
},
[ "SA_FLAMELAUNCHER" ] = {
	Id = 280,
	Description = "Endow Blaze",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.OnlyParty,
		SkillBehavior.OnlyGuild
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 1200000,
		[2] = 1200000,
		[3] = 1200000,
		[4] = 1200000,
		[5] = 1800000,
		[6] = 1800000,
		[7] = 1800000,
		[8] = 1800000,
		[9] = 1800000,
		[10] = 1800000
	},
	FixedCastTime = 3000,
	Requirements = {
		SPCost = 40,
		Items = {
			Item[ "Boody_Red" ] = 1
		}
	}
},
[ "SA_FROSTWEAPON" ] = {
	Id = 281,
	Description = "Endow Tsunami",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.OnlyParty,
		SkillBehavior.OnlyGuild
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 1200000,
		[2] = 1200000,
		[3] = 1200000,
		[4] = 1200000,
		[5] = 1800000,
		[6] = 1800000,
		[7] = 1800000,
		[8] = 1800000,
		[9] = 1800000,
		[10] = 1800000
	},
	FixedCastTime = 3000,
	Requirements = {
		SPCost = 40,
		Items = {
			Item[ "Crystal_Blue" ] = 1
		}
	}
},
[ "SA_LIGHTNINGLOADER" ] = {
	Id = 282,
	Description = "Endow Tornado",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.OnlyParty,
		SkillBehavior.OnlyGuild
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 1200000,
		[2] = 1200000,
		[3] = 1200000,
		[4] = 1200000,
		[5] = 1800000,
		[6] = 1800000,
		[7] = 1800000,
		[8] = 1800000,
		[9] = 1800000,
		[10] = 1800000
	},
	FixedCastTime = 3000,
	Requirements = {
		SPCost = 40,
		Items = {
			Item[ "Wind_Of_Verdure" ] = 1
		}
	}
},
[ "SA_SEISMICWEAPON" ] = {
	Id = 283,
	Description = "Endow Quake",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.OnlyParty,
		SkillBehavior.OnlyGuild
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 1200000,
		[2] = 1200000,
		[3] = 1200000,
		[4] = 1200000,
		[5] = 1800000,
		[6] = 1800000,
		[7] = 1800000,
		[8] = 1800000,
		[9] = 1800000,
		[10] = 1800000
	},
	FixedCastTime = 3000,
	Requirements = {
		SPCost = 40,
		Items = {
			Item[ "Yellow_Live" ] = 1
		}
	}
},
[ "SA_DRAGONOLOGY" ] = {
	Id = 284,
	Description = "Dragonology",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "SA_VOLCANO" ] = {
	Id = 285,
	Description = "Volcano",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 4000,
	SkillData1 = {
		[1] = 60000,
		[2] = 120000,
		[3] = 180000,
		[4] = 240000,
		[5] = 300000,
		[6] = 360000,
		[7] = 420000,
		[8] = 480000,
		[9] = 540000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 48,
			[2] = 46,
			[3] = 44,
			[4] = 42,
			[5] = 40,
			[6] = 38,
			[7] = 36,
			[8] = 34,
			[9] = 32,
			[10] = 30
		},
		Items = {
			Item[ "Yellow_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = 0x9a,
		Layout = 3,
		Interval = -1,
		Target = "All",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SA_DELUGE" ] = {
	Id = 286,
	Description = "Deluge",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 4000,
	SkillData1 = {
		[1] = 60000,
		[2] = 120000,
		[3] = 180000,
		[4] = 240000,
		[5] = 300000,
		[6] = 360000,
		[7] = 420000,
		[8] = 480000,
		[9] = 540000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 48,
			[2] = 46,
			[3] = 44,
			[4] = 42,
			[5] = 40,
			[6] = 38,
			[7] = 36,
			[8] = 34,
			[9] = 32,
			[10] = 30
		},
		Items = {
			Item[ "Yellow_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = 0x9b,
		Layout = 3,
		Interval = -1,
		Target = "All",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SA_VIOLENTGALE" ] = {
	Id = 287,
	Description = "Whirlwind",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 4000,
	SkillData1 = {
		[1] = 60000,
		[2] = 120000,
		[3] = 180000,
		[4] = 240000,
		[5] = 300000,
		[6] = 360000,
		[7] = 420000,
		[8] = 480000,
		[9] = 540000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 48,
			[2] = 46,
			[3] = 44,
			[4] = 42,
			[5] = 40,
			[6] = 38,
			[7] = 36,
			[8] = 34,
			[9] = 32,
			[10] = 30
		},
		Items = {
			Item[ "Yellow_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = 0x9c,
		Layout = 3,
		Interval = -1,
		Target = "All",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SA_LANDPROTECTOR" ] = {
	Id = 288,
	Description = "Magnetic Earth",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 4000,
	SkillData1 = {
		[1] = 165000,
		[2] = 210000,
		[3] = 255000,
		[4] = 300000,
		[5] = 345000,
		[6] = 390000,
		[7] = 435000,
		[8] = 480000,
		[9] = 525000,
		[10] = 570000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 66,
			[2] = 62,
			[3] = 58,
			[4] = 54,
			[5] = 50,
			[6] = 46,
			[7] = 42,
			[8] = 38,
			[9] = 34,
			[10] = 30
		},
		Items = {
			Item[ "Blue_Gemstone" ] = 1,
			Item[ "Yellow_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = 0x9d,
		Layout = {
			[1] = 3,
			[2] = 3,
			[3] = 4,
			[4] = 4,
			[5] = 5,
			[6] = 5,
			[7] = 6,
			[8] = 6,
			[9] = 7,
			[10] = 7
		},
		Interval = -1,
		Target = "All",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SA_DISPELL" ] = {
	Id = 289,
	Description = "Dispell",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.WithoutSelf,
		SkillBehavior.OnlyParty,
		SkillBehavior.OnlyGuild
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = {
		[1] = 0,
		[2] = 0,
		[3] = 0,
		[4] = 0,
		[5] = 0,
		[6] = -1,
		[7] = -1,
		[8] = -1,
		[9] = -1,
		[10] = -1
	},
	InterruptCast = true,
	CastTime = 1600,
	FixedCastTime = 400,
	Requirements = {
		SPCost = 1,
		Items = {
			Item[ "Yellow_Gemstone" ] = 1
		}
	}
},
{
	Id = 290,
	Name = "SA_ABRACADABRA",
	Description = "Hocus-pocus",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 50,
		Items = {
			Item[ "Yellow_Gemstone" ] = 2
		}
	}
},
[ "SA_MONOCELL" ] = {
	Id = 291,
	Description = "Monocell",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_CLASSCHANGE" ] = {
	Id = 292,
	Description = "Class Change",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_SUMMONMONSTER" ] = {
	Id = 293,
	Description = "Monster Chant",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_REVERSEORCISH" ] = {
	Id = 294,
	Description = "Grampus Morph",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 1200000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_DEATH" ] = {
	Id = 295,
	Description = "Grim Reaper",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_FORTUNE" ] = {
	Id = 296,
	Description = "Gold Digger",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_TAMINGMONSTER" ] = {
	Id = 297,
	Description = "Beastly Hypnosis",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_QUESTION" ] = {
	Id = 298,
	Description = "Questioning",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_GRAVITY" ] = {
	Id = 299,
	Description = "Gravity",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_LEVELUP" ] = {
	Id = 300,
	Description = "Leveling",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_INSTANTDEATH" ] = {
	Id = 301,
	Description = "Suicide",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_FULLRECOVERY" ] = {
	Id = 302,
	Description = "Rejuvenation",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "SA_COMA" ] = {
	Id = 303,
	Description = "Coma",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	InterruptCast = true,
	Requirements = {
		SPCost = 1
	}
},
[ "BD_ADAPTATION" ] = {
	Id = 304,
	Description = "Amp",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData2 = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 1
	}
},
[ "BD_ENCORE" ] = {
	Id = 305,
	Description = "Encore",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 1,
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "BD_LULLABY" ] = {
	Id = 306,
	Description = "Lullaby",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.EnsembleSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	SkillData2 = 15000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20,
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0x9e,
		Layout = 4,
		Interval = 6000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.Immovable
		}
	}
},
[ "BD_RICHMANKIM" ] = {
	Id = 307,
	Description = "Mental Sensing",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.EnsembleSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	SkillData2 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20,
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0x9f,
		Layout = 4,
		Interval = -1,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.Immovable
		}
	}
},
[ "BD_ETERNALCHAOS" ] = {
	Id = 308,
	Description = "Down Tempo",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.EnsembleSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	SkillData2 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 30,
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xa0,
		Layout = 4,
		Interval = -1,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.Immovable
		}
	}
},
[ "BD_DRUMBATTLEFIELD" ] = {
	Id = 309,
	Description = "Battle Theme",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.EnsembleSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	SkillData2 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 38,
			[2] = 41,
			[3] = 44,
			[4] = 47,
			[5] = 50,
			[6] = 53,
			[7] = 56,
			[8] = 59,
			[9] = 62,
			[10] = 65
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xa1,
		Layout = 4,
		Interval = -1,
		Target = "Party",
		Behavior = {
			PlacementBehavior.Immovable
		}
	}
},
[ "BD_RINGNIBELUNGEN" ] = {
	Id = 310,
	Description = "Harmonic Lick",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.EnsembleSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	SkillData2 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 38,
			[2] = 41,
			[3] = 44,
			[4] = 47,
			[5] = 50,
			[6] = 53,
			[7] = 56,
			[8] = 59,
			[9] = 62,
			[10] = 65
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xa2,
		Layout = 4,
		Interval = -1,
		Target = "Party",
		Behavior = {
			PlacementBehavior.Immovable
		}
	}
},
[ "BD_ROKISWEIL" ] = {
	Id = 311,
	Description = "Classical Pluck",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.EnsembleSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	SkillData2 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15,
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xa3,
		Layout = 4,
		Interval = -1,
		Target = "All",
		Behavior = {
			PlacementBehavior.Immovable
		}
	}
},
[ "BD_INTOABYSS" ] = {
	Id = 312,
	Description = "Power Chord",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.EnsembleSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	SkillData2 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xa4,
		Layout = 4,
		Interval = -1,
		Target = "Party",
		Behavior = {
			PlacementBehavior.Immovable
		}
	}
},
[ "BD_SIEGFRIED" ] = {
	Id = 313,
	Description = "Acoustic Rhythm",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.EnsembleSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	SkillData2 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20,
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xa5,
		Layout = 4,
		Interval = -1,
		Target = "Party",
		Behavior = {
			PlacementBehavior.Immovable
		}
	}
},
[ "BA_MUSICALLESSON" ] = {
	Id = 315,
	Description = "Music Lessons",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BA_MUSICALSTRIKE" ] = {
	Id = 316,
	Description = "Melody Strike",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	CastTime = 1200,
	FixedCastTime = 300,
	Requirements = {
		SPCost = {
			[1] = 1,
			[2] = 3,
			[3] = 5,
			[4] = 7,
			[5] = 9,
			[6] = 11,
			[7] = 13,
			[8] = 15,
			[9] = 17,
			[10] = 19
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	}
},
[ "BA_DISSONANCE" ] = {
	Id = 317,
	Description = "Unchained Serenade",
	MaxLevel = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.SongDanceSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.IgnoreFlee
	},
	SkillData1 = 30000,
	SkillData2 = 3000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 21,
			[3] = 24,
			[4] = 27,
			[5] = 30,
			[6] = 33,
			[7] = 36,
			[8] = 39,
			[9] = 42,
			[10] = 45
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument
		}
	},
	Placement = {
		Id = 0xa6,
		Layout = 3,
		Interval = 3000,
		Target = "Enemy"
	}
},
[ "BA_FROSTJOKER" ] = {
	Id = 318,
	Description = "Unbarring Octave",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	AfterCastActDelay = 4000,
	SkillData2 = {
		[1] = 10000,
		[2] = 11000,
		[3] = 12000,
		[4] = 13000,
		[5] = 14000,
		[6] = 15000,
		[7] = 16000,
		[8] = 17000,
		[9] = 18000,
		[10] = 19000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		}
	}
},
[ "BA_WHISTLE" ] = {
	Id = 319,
	Description = "Perfect Tablature",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.SongDanceSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	SkillData2 = 20000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 24,
			[2] = 28,
			[3] = 32,
			[4] = 36,
			[5] = 40,
			[6] = 44,
			[7] = 48,
			[8] = 52,
			[9] = 56,
			[10] = 60
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xa7,
		Layout = 3,
		Interval = 3000,
		Target = "All",
		Behavior = {,
			PlacementBehavior.AffectOnContact
		}
	}
},
[ "BA_ASSASSINCROSS" ] = {
	Id = 320,
	Description = "Impressive Riff",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.SongDanceSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 120000,
	SkillData2 = 20000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 38,
			[2] = 41,
			[3] = 44,
			[4] = 47,
			[5] = 50,
			[6] = 53,
			[7] = 56,
			[8] = 59,
			[9] = 62,
			[10] = 65
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xa8,
		Layout = 3,
		Interval = 3000,
		Target = "All",
		Behavior = {,
			PlacementBehavior.AffectOnContact
		}
	}
},
[ "BA_POEMBRAGI" ] = {
	Id = 321,
	Description = "Magic Strings",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.SongDanceSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 180000,
	SkillData2 = 20000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xa9,
		Layout = 3,
		Interval = 3000,
		Target = "All",
		Behavior = {,
			PlacementBehavior.AffectOnContact
		}
	}
},
[ "BA_APPLEIDUN" ] = {
	Id = 322,
	Description = "Song of Lutie",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.SongDanceSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 180000,
	SkillData2 = 20000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xaa,
		Layout = 3,
		Interval = 6000,
		Target = "All",
		Behavior = {,
			PlacementBehavior.AffectOnContact
		}
	}
},
[ "DC_DANCINGLESSON" ] = {
	Id = 323,
	Description = "Dance Lessons",
	MaxLevel = 10,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "DC_THROWARROW" ] = {
	Id = 324,
	Description = "Slinging Arrow",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	CastTime = 1200,
	FixedCastTime = 300,
	Requirements = {
		SPCost = {
			[1] = 1,
			[2] = 3,
			[3] = 5,
			[4] = 7,
			[5] = 9,
			[6] = 11,
			[7] = 13,
			[8] = 15,
			[9] = 17,
			[10] = 19
		},
		WeaponTypes = {
			WeaponType.Whip
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	}
},
[ "DC_UGLYDANCE" ] = {
	Id = 325,
	Description = "Hip Shaker",
	MaxLevel = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.SongDanceSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 30000,
	SkillData2 = 3000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 23,
			[2] = 26,
			[3] = 29,
			[4] = 32,
			[5] = 35,
			[6] = 38,
			[7] = 41,
			[8] = 44,
			[9] = 47,
			[10] = 50
		},
		WeaponTypes = {
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xab,
		Layout = 3,
		Interval = 3000,
		Target = "Enemy"
	}
},
[ "DC_SCREAM" ] = {
	Id = 326,
	Description = "Dazzler",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	AfterCastActDelay = 4000,
	SkillData2 = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		}
	}
},
[ "DC_HUMMING" ] = {
	Id = 327,
	Description = "Focus Ballet",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.SongDanceSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	SkillData2 = 20000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 24,
			[3] = 26,
			[4] = 28,
			[5] = 30,
			[6] = 32,
			[7] = 34,
			[8] = 36,
			[9] = 38,
			[10] = 40
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xac,
		Layout = 3,
		Interval = 3000,
		Target = "All",
		Behavior = {
			PlacementBehavior.AffectOnContact
		}
	}
},
[ "DC_DONTFORGETME" ] = {
	Id = 328,
	Description = "Slow Grace",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.SongDanceSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 180000,
	SkillData2 = 20000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 28,
			[2] = 31,
			[3] = 34,
			[4] = 37,
			[5] = 40,
			[6] = 43,
			[7] = 46,
			[8] = 49,
			[9] = 52,
			[10] = 55
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xad,
		Layout = 3,
		Interval = 3000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AffectOnContact
		}
	}
},
[ "DC_FORTUNEKISS" ] = {
	Id = 329,
	Description = "Lady Luck",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.SongDanceSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 120000,
	SkillData2 = 20000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 43,
			[2] = 46,
			[3] = 49,
			[4] = 52,
			[5] = 55,
			[6] = 58,
			[7] = 61,
			[8] = 64,
			[9] = 67,
			[10] = 70
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xae,
		Layout = 3,
		Interval = 3000,
		Target = "All",
		Behavior = {
			PlacementBehavior.AffectOnContact
		}
	}
},
{
	Id = 330,
	Name = "DC_SERVICEFORYOU",
	Description = "Gypsy's Kiss",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.SongDanceSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 180000,
	SkillData2 = 20000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xaf,
		Layout = 3,
		Interval = 3000,
		Target = "All",
		Behavior = {
			PlacementBehavior.AffectOnContact
		}
	}
},
[ "NPC_RANDOMMOVE" ] = {
	Id = 331,
	Description = "Random Move",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0
},
[ "NPC_SPEEDUP" ] = {
	Id = 332,
	Description = "Speed UP",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0
},
[ "NPC_REVENGE" ] = {
	Id = 333,
	Description = "Revenge",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0
},
[ "WE_MALE" ] = {
	Id = 334,
	Description = "I Will Protect You",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromWedding
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1500,
	FixedCastTime = 1500,
	Requirements = {
		SPCost = 1,
		HPRateCost: -10
	}
},
[ "WE_FEMALE" ] = {
	Id = 335,
	Description = "I Look up to You",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromWedding
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1500,
	FixedCastTime = 1500,
	Requirements = {
		SPCost = 1,
		SPRateCost: -10
	}
},
[ "WE_CALLPARTNER" ] = {
	Id = 336,
	Description = "I miss You",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromWedding
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 3,
	InterruptCast = true,
	SkillInstances = 1,
	SkillData1 = 20000,
	FixedCastTime = 0,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex
	},
	Requirements = {
		SPCost = 1
	},
	Placement = {
		Id = 0xb2,
		Range = -1,
		Interval = -1
	}
},
[ "ITM_TOMAHAWK" ] = {
	Id = 337,
	Description = "Throw Tomahawk",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = 1
	}
},
[ "NPC_DARKCROSS" ] = {
	Id = 338,
	Description = "Cross of Darkness",
	MaxLevel = 10,
	Range = -1,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Dark,
	NumberOfHits: -2
},
[ "NPC_GRANDDARKNESS" ] = {
	Id = 339,
	Description = "Grand cross of Darkness",
	MaxLevel = 10,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Dark,
	DamageBehavior = {
		DamageBehavior.Ignore_Equip_Atk,
		DamageBehavior.IgnoreFlee
	},
	AfterCastWalkDelay = 900,
	SkillData1 = 900,
	SkillData2 = {
		[1] = 10000,
		[2] = 11000,
		[3] = 12000,
		[4] = 13000,
		[5] = 14000,
		[6] = 15000,
		[7] = 16000,
		[8] = 17000,
		[9] = 18000,
		[10] = 19000
	},
	FixedCastTime = 0,
	Placement = {
		Id = 0x86,
		Layout = -1,
		Interval = 300,
		Target = "Enemy"
	}
},
[ "NPC_DARKSTRIKE" ] = {
	Id = 340,
	Description = "Soul Strike of Darkness",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Dark,
	NumberOfHits = {
		[1] = 1,
		[2] = 1,
		[3] = 2,
		[4] = 2,
		[5] = 3,
		[6] = 3,
		[7] = 4,
		[8] = 4,
		[9] = 5,
		[10] = 5
	},
	InterruptCast = true
},
[ "NPC_DARKTHUNDER" ] = {
	Id = 341,
	Description = "Darkness Jupitel",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Dark,
	NumberOfHits = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	InterruptCast = true,
	KnockBackTiles = {
		[1] = 2,
		[2] = 3,
		[3] = 3,
		[4] = 4,
		[5] = 4,
		[6] = 5,
		[7] = 5,
		[8] = 6,
		[9] = 6,
		[10] = 7
	}
},
[ "NPC_STOP" ] = {
	Id = 342,
	Description = "Stop",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	SkillData1 = 10000,
	FixedCastTime = 0
},
[ "NPC_WEAPONBRAKER" ] = {
	Id = 343,
	Description = "Break weapon",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement
},
[ "NPC_ARMORBRAKE" ] = {
	Id = 344,
	Description = "Break armor",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement
},
[ "NPC_HELMBRAKE" ] = {
	Id = 345,
	Description = "Break helm",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement
},
[ "NPC_SHIELDBRAKE" ] = {
	Id = 346,
	Description = "Break shield",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement
},
[ "NPC_UNDEADATTACK" ] = {
	Id = 347,
	Description = "Undead Element Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Undead
},
[ "NPC_CHANGEUNDEAD" ] = {
	Id = 348,
	Description = "Undead Attribute Change",
	MaxLevel = 5,
	Range = 9,
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	Element = Element.Undead,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 30000,
	FixedCastTime = 0
},
[ "NPC_POWERUP" ] = {
	Id = 349,
	Description = "Power Up",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	FixedCastTime = 0
},
[ "NPC_AGIUP" ] = {
	Id = 350,
	Description = "Agility UP",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	FixedCastTime = 0
},
[ "NPC_SIEGEMODE" ] = {
	Id = 351,
	Description = "Siege Mode",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0
},
[ "NPC_CALLSLAVE" ] = {
	Id = 352,
	Description = "Recall Slaves",
	MaxLevel = 1,
	Range = 2,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0
},
[ "NPC_INVISIBLE" ] = {
	Id = 353,
	Description = "Invisible",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	SkillData1 = 30000,
	FixedCastTime = 0
},
[ "NPC_RUN" ] = {
	Id = 354,
	Description = "Run",
	MaxLevel = 20,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	FixedCastTime = 0
},
[ "LK_AURABLADE" ] = {
	Id = 355,
	Description = "Aura Blade",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 40000,
		[2] = 60000,
		[3] = 80000,
		[4] = 100000,
		[5] = 120000,
		[6] = 140000,
		[7] = 160000,
		[8] = 180000,
		[9] = 200000,
		[10] = 220000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 26,
			[3] = 34,
			[4] = 42,
			[5] = 50,
			[6] = 58,
			[7] = 66,
			[8] = 74,
			[9] = 82,
			[10] = 90
		},
		WeaponTypes = {
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Bow,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar,
			WeaponType.Revolver,
			WeaponType.Rifle,
			WeaponType.GatlingGun,
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher,
			WeaponType.FuumaShuriken
		}
	}
},
[ "LK_PARRYING" ] = {
	Id = 356,
	Description = "Parrying",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 15000,
		[2] = 20000,
		[3] = 25000,
		[4] = 30000,
		[5] = 35000,
		[6] = 40000,
		[7] = 45000,
		[8] = 50000,
		[9] = 55000,
		[10] = 60000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 50,
		WeaponTypes = {
			WeaponType.TwoHandedSword
		}
	}
},
[ "LK_CONCENTRATION" ] = {
	Id = 357,
	Description = "Concentration",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 25000,
		[2] = 30000,
		[3] = 35000,
		[4] = 40000,
		[5] = 45000,
		[6] = 50000,
		[7] = 55000,
		[8] = 60000,
		[9] = 65000,
		[10] = 70000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 14,
			[2] = 18,
			[3] = 22,
			[4] = 26,
			[5] = 30,
			[6] = 34,
			[7] = 38,
			[8] = 42,
			[9] = 46,
			[10] = 50
		}
	}
},
[ "LK_TENSIONRELAX" ] = {
	Id = 358,
	Description = "Relax",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 180000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15
	}
},
[ "LK_BERSERK" ] = {
	Id = 359,
	Description = "Frenzy",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 300000,
	SkillData2 = 15000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 200
	}
},
[ "HP_ASSUMPTIO" ] = {
	Id = 361,
	Description = "Assumptio",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 1,
	InterruptCast = true,
	CastTime = {
		[1] = 800,
		[2] = 1200,
		[3] = 1600,
		[4] = 2000,
		[5] = 2400,
		[6] = 2400,
		[7] = 2400,
		[8] = 2400,
		[9] = 2400,
		[10] = 2400
	},
	AfterCastActDelay = {
		[1] = 1100,
		[2] = 1200,
		[3] = 1300,
		[4] = 1400,
		[5] = 1500,
		[6] = 1600,
		[7] = 1700,
		[8] = 1800,
		[9] = 1900,
		[10] = 2000
	},
	SkillData1 = {
		[1] = 20000,
		[2] = 40000,
		[3] = 60000,
		[4] = 80000,
		[5] = 100000,
		[6] = 120000,
		[7] = 140000,
		[8] = 160000,
		[9] = 180000,
		[10] = 200000
	},
	FixedCastTime = {
		[1] = 200,
		[2] = 300,
		[3] = 400,
		[4] = 500,
		[5] = 600,
		[6] = 700,
		[7] = 800,
		[8] = 900,
		[9] = 1000,
		[10] = 1100
	},
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 30,
			[3] = 40,
			[4] = 50,
			[5] = 60,
			[6] = 70,
			[7] = 80,
			[8] = 90,
			[9] = 100,
			[10] = 110
		}
	}
},
[ "HP_BASILICA" ] = {
	Id = 362,
	Description = "Basilica",
	MaxLevel = 5,
	Range = 4,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	KnockBackTiles = 2,
	AfterCastActDelay = {
		[1] = 2000,
		[2] = 3000,
		[3] = 4000,
		[4] = 5000,
		[5] = 6000,
		[6] = 7000,
		[7] = 8000,
		[8] = 9000,
		[9] = 10000,
		[10] = 11000
	},
	SkillData1 = {
		[1] = 20000,
		[2] = 25000,
		[3] = 30000,
		[4] = 35000,
		[5] = 40000,
		[6] = 45000,
		[7] = 50000,
		[8] = 55000,
		[9] = 60000,
		[10] = 65000
	},
	SkillData2 = {
		[1] = 20000,
		[2] = 25000,
		[3] = 30000,
		[4] = 35000,
		[5] = 40000,
		[6] = 45000,
		[7] = 50000,
		[8] = 55000,
		[9] = 60000,
		[10] = 65000
	},
	FixedCastTime = {
		[1] = 5000,
		[2] = 6000,
		[3] = 7000,
		[4] = 8000,
		[5] = 9000,
		[6] = 10000,
		[7] = 11000,
		[8] = 12000,
		[9] = 13000,
		[10] = 14000
	},
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 90,
			[3] = 100,
			[4] = 110,
			[5] = 120,
			[6] = 130,
			[7] = 140,
			[8] = 150,
			[9] = 160,
			[10] = 170
		},
		Items = {
			Item[ "Yellow_Gemstone" ] = 1,
			Item[ "Red_Gemstone" ] = 1,
			Item[ "Blue_Gemstone" ] = 1,
			Item[ "Holy_Water" ] = 1
		}
	},
	Placement = {
		Id = 0xb4,
		Range = 2,
		Interval = 300,
		Target = "All"
	}
},
[ "HP_MEDITATIO" ] = {
	Id = 363,
	Description = "Meditatio",
	MaxLevel = 10,
	AttackType = AttackType.Magic,
	NumberOfHits = 0
},
[ "HW_SOULDRAIN" ] = {
	Id = 364,
	Description = "Soul Drain",
	MaxLevel = 10,
	AttackType = AttackType.Magic
},
[ "HW_MAGICCRASHER" ] = {
	Id = 365,
	Description = "Stave Crasher",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	InterruptCast = true,
	CastTime = 240,
	AfterCastActDelay = 300,
	FixedCastTime = 60,
	Requirements = {
		SPCost = 8
	}
},
[ "HW_MAGICPOWER" ] = {
	Id = 366,
	Description = "Mystical Amplification",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 30000,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffects,
	},
	Requirements = {
		SPCost = {
			[1] = 14,
			[2] = 18,
			[3] = 22,
			[4] = 26,
			[5] = 30,
			[6] = 34,
			[7] = 38,
			[8] = 42,
			[9] = 46,
			[10] = 50
		}
	}
},
[ "PA_PRESSURE" ] = {
	Id = 367,
	Description = "Gloria Domini",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		IgnoreElement = true,
		DamageBehavior.IgnoreFlee,
		IgnoreDefCards = true
	},
	CastTime = 1600,
	AfterCastActDelay = {
		[1] = 2000,
		[2] = 2500,
		[3] = 3000,
		[4] = 3500,
		[5] = 4000,
		[6] = 4500,
		[7] = 5000,
		[8] = 5500,
		[9] = 6000,
		[10] = 6500
	},
	SkillData2 = {
		[1] = 2000,
		[2] = 3000,
		[3] = 4000,
		[4] = 5000,
		[5] = 6000,
		[6] = 7000,
		[7] = 8000,
		[8] = 9000,
		[9] = 10000,
		[10] = 11000
	},
	FixedCastTime = 400,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 35,
			[3] = 40,
			[4] = 45,
			[5] = 50,
			[6] = 55,
			[7] = 60,
			[8] = 65,
			[9] = 70,
			[10] = 75
		}
	}
},
{
	Id = 368,
	Name = "PA_SACRIFICE",
	Description = "Martyr's Reckoning",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.Ignore_Equip_Atk,
		DamageBehavior.Ignore_Soft_Def
		DamageBehavior.IgnoreFlee
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 100
	}
},
[ "PA_GOSPEL" ] = {
	Id = 369,
	Description = "Battle Chant",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.IgnoreFlee
	},
	InterruptCast = true,
	SkillData1 = 60000,
	SkillData2 = 60000,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 80,
			[3] = 80,
			[4] = 80,
			[5] = 80,
			[6] = 100,
			[7] = 100,
			[8] = 100,
			[9] = 100,
			[10] = 100
		}
	},
	Placement = {
		Id = 0xb3,
		Layout = -1,
		Interval = 10000,
		Target = "All",
		Behavior = {
			PlacementBehavior.CannotOverlap
		}
	}
},
[ "CH_PALMSTRIKE" ] = {
	Id = 370,
	Description = "Raging Palm Strike",
	MaxLevel = 5,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	InterruptCast = true,
	KnockBackTiles = 3,
	AfterCastActDelay = 300,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex
	},
	Requirements = {
		SPCost = {
			[1] = 2,
			[2] = 4,
			[3] = 6,
			[4] = 8,
			[5] = 10,
			[6] = 12,
			[7] = 14,
			[8] = 16,
			[9] = 18,
			[10] = 20
		},
		State = PlayerState.CriticalExplosion
	}
},
[ "CH_TIGERFIST" ] = {
	Id = 371,
	Description = "Glacier Fist",
	MaxLevel = 5,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SkillData2 = {
		[1] = 2000,
		[2] = 4000,
		[3] = 6000,
		[4] = 8000,
		[5] = 10000,
		[6] = 12000,
		[7] = 14000,
		[8] = 16000,
		[9] = 18000,
		[10] = 20000
	},
	SkillDelayOptions = {
		SkillDelayOptions.IgnoreStatusEffects
	},
	Requirements = {
		SPCost = {
			[1] = 4,
			[2] = 6,
			[3] = 8,
			[4] = 10,
			[5] = 12,
			[6] = 14,
			[7] = 16,
			[8] = 18,
			[9] = 20,
			[10] = 22
		},
		SpiritSphereCost = 1
	}
},
[ "CH_CHAINCRUSH" ] = {
	Id = 372,
	Description = "Chain Crush Combo",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = {
		[1] = -1,
		[2] = -1,
		[3] = -2,
		[4] = -2,
		[5] = -3,
		[6] = -3,
		[7] = -4,
		[8] = -4,
		[9] = -5,
		[10] = -5
	},
	SkillDelayOptions = {
		SkillDelayOptions.IgnoreStatusEffects
	},
	Requirements = {
		SPCost = {
			[1] = 4,
			[2] = 6,
			[3] = 8,
			[4] = 10,
			[5] = 12,
			[6] = 14,
			[7] = 16,
			[8] = 18,
			[9] = 20,
			[10] = 22
		},
		SpiritSphereCost = 2
	}
},
[ "PF_HPCONVERSION" ] = {
	Id = 373,
	Description = "Indulge",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	Requirements = {
		SPCost = {
			[1] = 1,
			[2] = 2,
			[3] = 3,
			[4] = 4,
			[5] = 5,
			[6] = 6,
			[7] = 7,
			[8] = 8,
			[9] = 9,
			[10] = 10
		}
	}
},
[ "PF_SOULCHANGE" ] = {
	Id = 374,
	Description = "Soul Exhale",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.WithoutSelf,
		SkillBehavior.OnlyParty,
		SkillBehavior.OnlyGuild
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	FixedCastTime = 3000,
	Requirements = {
		SPCost = 5
	}
},
[ "PF_SOULBURN" ] = {
	Id = 375,
	Description = "Soul Siphon",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.Ignore_Equip_Atk,
		IgnoreElement = true,
		IgnoreDefCards = true
	},
	InterruptCast = true,
	CoolDown = {
		[1] = 10000,
		[2] = 10000,
		[3] = 10000,
		[4] = 10000,
		[5] = 15000,
		[6] = 15000,
		[7] = 15000,
		[8] = 15000,
		[9] = 15000,
		[10] = 15000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 90,
			[3] = 100,
			[4] = 110,
			[5] = 120,
			[6] = 130,
			[7] = 140,
			[8] = 150,
			[9] = 160,
			[10] = 170
		}
	}
},
[ "ASC_KATAR" ] = {
	Id = 376,
	Description = "Advanced Katar Mastery",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "ASC_EDP" ] = {
	Id = 378,
	Description = "Enchant Deadly Poison",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.Poison,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 40000,
		[2] = 45000,
		[3] = 50000,
		[4] = 55000,
		[5] = 60000,
		[6] = 65000,
		[7] = 70000,
		[8] = 75000,
		[9] = 80000,
		[10] = 85000
	},
	SkillData2 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 70,
			[3] = 80,
			[4] = 90,
			[5] = 100,
			[6] = 110,
			[7] = 120,
			[8] = 130,
			[9] = 140,
			[10] = 150
		},
		WeaponTypes = {
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Bow,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar,
			WeaponType.Revolver,
			WeaponType.Rifle,
			WeaponType.GatlingGun,
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher,
			WeaponType.FuumaShuriken
		},
		Items = {
			Item[ "Poison_Bottle" ] = 1
		}
	}
},
[ "ASC_BREAKER" ] = {
	Id = 379,
	Description = "Soul Destroyer",
	MaxLevel = 10,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Misc,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	InterruptCast = true,
	CastTime = 250,
	AfterCastActDelay = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	FixedCastTime = 250,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 20,
			[3] = 20,
			[4] = 20,
			[5] = 20,
			[6] = 30,
			[7] = 30,
			[8] = 30,
			[9] = 30,
			[10] = 30
		}
	}
},
[ "SN_SIGHT" ] = {
	Id = 380,
	Description = "Falcon Eyes",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 30000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 20,
			[3] = 25,
			[4] = 25,
			[5] = 30,
			[6] = 30,
			[7] = 35,
			[8] = 35,
			[9] = 40,
			[10] = 40
		}
	}
},
[ "SN_FALCONASSAULT" ] = {
	Id = 381,
	Description = "Falcon Assault",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	InterruptCast = true,
	CastTime = 500,
	AfterCastActDelay = 3000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 34,
			[3] = 38,
			[4] = 42,
			[5] = 46,
			[6] = 50,
			[7] = 54,
			[8] = 58,
			[9] = 62,
			[10] = 66
		},
		State = PlayerState.HasFalcon
	}
},
[ "SN_SHARPSHOOTING" ] = {
	Id = 382,
	Description = "Focused Arrow Strike",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SplashRange = 2,
	InterruptCast = true,
	SkillInstances = 13,
	CastTime = 1000,
	AfterCastActDelay = 1500,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 21,
			[3] = 24,
			[4] = 27,
			[5] = 30,
			[6] = 33,
			[7] = 36,
			[8] = 39,
			[9] = 42,
			[10] = 45
		},
		WeaponTypes = {
			WeaponType.Bow
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	}
},
[ "SN_WINDWALK" ] = {
	Id = 383,
	Description = "Wind Walker",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	InterruptCast = true,
	CastTime = {
		[1] = 1500,
		[2] = 1800,
		[3] = 2100,
		[4] = 2400,
		[5] = 2700,
		[6] = 3000,
		[7] = 3300,
		[8] = 3600,
		[9] = 3900,
		[10] = 4200
	},
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 130000,
		[2] = 160000,
		[3] = 190000,
		[4] = 220000,
		[5] = 250000,
		[6] = 280000,
		[7] = 310000,
		[8] = 340000,
		[9] = 370000,
		[10] = 400000
	},
	FixedCastTime = {
		[1] = 500,
		[2] = 600,
		[3] = 700,
		[4] = 800,
		[5] = 900,
		[6] = 1000,
		[7] = 1100,
		[8] = 1200,
		[9] = 1300,
		[10] = 1400
	},
	Requirements = {
		SPCost = {
			[1] = 46,
			[2] = 52,
			[3] = 58,
			[4] = 64,
			[5] = 70,
			[6] = 76,
			[7] = 82,
			[8] = 88,
			[9] = 94,
			[10] = 100
		}
	}
},
[ "WS_MELTDOWN" ] = {
	Id = 384,
	Description = "Shattering Strike",
	MaxLevel = 10,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 15000,
		[2] = 20000,
		[3] = 25000,
		[4] = 30000,
		[5] = 35000,
		[6] = 40000,
		[7] = 45000,
		[8] = 50000,
		[9] = 55000,
		[10] = 60000
	},
	SkillData2 = 5000,
	FixedCastTime = {
		[1] = 5,
		[2] = 5,
		[3] = 6,
		[4] = 6,
		[5] = 7,
		[6] = 7,
		[7] = 8,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	Requirements = {
		SPCost = {
			[1] = 50,
			[2] = 50,
			[3] = 60,
			[4] = 60,
			[5] = 70,
			[6] = 70,
			[7] = 80,
			[8] = 80,
			[9] = 90,
			[10] = 90
		}
	}
},
[ "WS_CARTBOOST" ] = {
	Id = 387,
	Description = "Cart Boost",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20,
		State = PlayerState.HasCart
	}
},
[ "ST_CHASEWALK" ] = {
	Id = 389,
	Description = "Stealth",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 500,
	SkillData1 = 10000,
	SkillData2 = 30000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = 10
	}
},
[ "ST_REJECTSWORD" ] = {
	Id = 390,
	Description = "Counter Instinct",
	MaxLevel = 5,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	InterruptCast = true,
	SkillData1 = 300000,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 15,
			[3] = 20,
			[4] = 25,
			[5] = 30,
			[6] = 35,
			[7] = 40,
			[8] = 45,
			[9] = 50,
			[10] = 55
		}
	}
},
[ "CR_ALCHEMY" ] = {
	Id = 392,
	Description = "Alchemy",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true
},
[ "CR_SYNTHESISPOTION" ] = {
	Id = 393,
	Description = "Potion Synthesis",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true
},
[ "CG_ARROWVULCAN" ] = {
	Id = 394,
	Description = "Vulcan Arrow",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -9,
	InterruptCast = true,
	CastTime = {
		[1] = 1600,
		[2] = 1760,
		[3] = 1920,
		[4] = 2080,
		[5] = 2240,
		[6] = 2400,
		[7] = 2560,
		[8] = 2720,
		[9] = 2880,
		[10] = 3040
	},
	AfterCastActDelay = 2000,
	AfterCastWalkDelay = 2000,
	FixedCastTime = {
		[1] = 400,
		[2] = 440,
		[3] = 480,
		[4] = 520,
		[5] = 560,
		[6] = 600,
		[7] = 640,
		[8] = 680,
		[9] = 720,
		[10] = 760
	},
	SkillDelayOptions = {
		SkillDelayOptions.IgnoreStatusEffects
	},
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	}
},
[ "CG_MOONLIT" ] = {
	Id = 395,
	Description = "Sheltering Bliss",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.EnsembleSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 3,
	InterruptCast = true,
	KnockBackTiles = 2,
	SkillData1 = {
		[1] = 20000,
		[2] = 25000,
		[3] = 30000,
		[4] = 35000,
		[5] = 40000,
		[6] = 45000,
		[7] = 50000,
		[8] = 55000,
		[9] = 60000,
		[10] = 65000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 40,
			[3] = 50,
			[4] = 60,
			[5] = 70,
			[6] = 80,
			[7] = 90,
			[8] = 100,
			[9] = 110,
			[10] = 120
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xb5,
		Layout = 4,
		Interval = -1,
		Target = "All",
		Behavior = {
			PlacementBehavior.Immovable
		}
	}
},
[ "CG_MARIONETTE" ] = {
	Id = 396,
	Description = "Marionette Control",
	MaxLevel = 1,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf,
		SkillBehavior.OnlyParty
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 100
	}
},
[ "LK_SPIRALPIERCE" ] = {
	Id = 397,
	Description = "Spiral Pierce",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 5,
	CastTime = {
		[1] = 150,
		[2] = 250,
		[3] = 350,
		[4] = 450,
		[5] = 500,
		[6] = 500,
		[7] = 500,
		[8] = 500,
		[9] = 500,
		[10] = 500
	},
	AfterCastActDelay = {
		[1] = 1200,
		[2] = 1400,
		[3] = 1600,
		[4] = 1800,
		[5] = 2000,
		[6] = 2200,
		[7] = 2400,
		[8] = 2600,
		[9] = 2800,
		[10] = 3000
	},
	SkillData2 = 1000,
	FixedCastTime = {
		[1] = 150,
		[2] = 250,
		[3] = 350,
		[4] = 450,
		[5] = 500,
		[6] = 500,
		[7] = 500,
		[8] = 500,
		[9] = 500,
		[10] = 500
	},
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 21,
			[3] = 24,
			[4] = 27,
			[5] = 30,
			[6] = 33,
			[7] = 36,
			[8] = 39,
			[9] = 42,
			[10] = 45
		},
		WeaponTypes = {
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "LK_HEADCRUSH" ] = {
	Id = 398,
	Description = "Traumatic Blow",
	MaxLevel = 5,
	Range = 4,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = 500,
	SkillData2 = 120000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 23
	}
},
[ "LK_JOINTBEAT" ] = {
	Id = 399,
	Description = "Vital Strike",
	MaxLevel = 10,
	Range = 4,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = {
		[1] = 800,
		[2] = 800,
		[3] = 800,
		[4] = 800,
		[5] = 1000,
		[6] = 1000,
		[7] = 1000,
		[8] = 1000,
		[9] = 1000,
		[10] = 1000
	},
	SkillData2 = 30000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 12,
			[3] = 14,
			[4] = 14,
			[5] = 16,
			[6] = 16,
			[7] = 18,
			[8] = 18,
			[9] = 20,
			[10] = 20
		},
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "HW_NAPALMVULCAN" ] = {
	Id = 400,
	Description = "Napalm Vulcan",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Ghost,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.SplitBetweenTargets
	},
	SplashRange = 1,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = 800,
	AfterCastActDelay = 1000,
	SkillData2 = 45000,
	FixedCastTime = 200,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 25,
			[3] = 40,
			[4] = 55,
			[5] = 70,
			[6] = 85,
			[7] = 100,
			[8] = 115,
			[9] = 130,
			[10] = 145
		}
	}
},
[ "CH_SOULCOLLECT" ] = {
	Id = 401,
	Description = "Zen",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 600000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 20
	}
},
[ "PF_MINDBREAKER" ] = {
	Id = 402,
	Description = "Mind Breaker",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = {
		[1] = 800,
		[2] = 900,
		[3] = 1000,
		[4] = 1100,
		[5] = 1200,
		[6] = 1300,
		[7] = 1400,
		[8] = 1500,
		[9] = 1600,
		[10] = 1700
	},
	SkillData1 = 30000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 15,
			[3] = 18,
			[4] = 21,
			[5] = 24,
			[6] = 27,
			[7] = 30,
			[8] = 33,
			[9] = 36,
			[10] = 39
		}
	}
},
[ "PF_MEMORIZE" ] = {
	Id = 403,
	Description = "Foresight",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	FixedCastTime = 5000,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffects
	},
	Requirements = {
		SPCost = 1
	}
},
[ "PF_FOGWALL" ] = {
	Id = 404,
	Description = "Blinding Mist",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 2,
	SkillData1 = 20000,
	SkillData2 = 10000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 25
	},
	Placement = {
		Id = 0xb6,
		Layout = -1,
		Interval = -1,
		Target = "All"
	}
},
[ "PF_SPIDERWEB" ] = {
	Id = 405,
	Description = "Fiber Lock",
	MaxLevel = 1,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillInstances = 3,
	SkillData1 = 30000,
	SkillData2 = 8000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 50,
		Items = {
			Item[ "Spiderweb" ] = 1
		}
	},
	Placement = {
		Id = 0xb7,
		Interval = -1,
		Target = "Enemy"
	}
},
[ "ASC_METEORASSAULT" ] = {
	Id = 406,
	Description = "Meteor Assault",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.Ignore_Equip_Atk
	},
	SplashRange = 2,
	CastTime = 250,
	AfterCastActDelay = 500,
	SkillData2 = {
		[1] = 10000,
		[2] = 5000,
		[3] = 120000,
		[4] = 120000,
		[5] = 120000,
		[6] = 120000,
		[7] = 120000,
		[8] = 120000,
		[9] = 120000,
		[10] = 120000
	},
	FixedCastTime = 250,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 12,
			[3] = 14,
			[4] = 16,
			[5] = 18,
			[6] = 20,
			[7] = 22,
			[8] = 24,
			[9] = 26,
			[10] = 28
		}
	}
},
[ "ASC_CDP" ] = {
	Id = 407,
	Description = "Create Deadly Poison",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	AfterCastActDelay = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 50
	}
},
[ "WE_BABY" ] = {
	Id = 408,
	Description = "Baby",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromWedding
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 300000,
	FixedCastTime = 2000,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex
	},
	Requirements = {
		SPCost = 1,
		SPRateCost: -10
	}
},
[ "WE_CALLPARENT" ] = {
	Id = 409,
	Description = "Call Parent",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromWedding
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 3,
	InterruptCast = true,
	SkillInstances = 1,
	SkillData1 = 20000,
	FixedCastTime = 0,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex
	},
	Requirements = {
		SPCost = 1
	},
	Placement = {
		Id = 0xb2,
		Range = -1,
		Interval = -1
	}
},
[ "WE_CALLBABY" ] = {
	Id = 410,
	Description = "Call Baby",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromWedding
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 3,
	InterruptCast = true,
	SkillInstances = 1,
	SkillData1 = 20000,
	FixedCastTime = 0,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex
	},
	Requirements = {
		SPCost = 1
	},
	Placement = {
		Id = 0xb2,
		Range = -1,
		Interval = -1
	}
},
[ "TK_RUN" ] = {
	Id = 411,
	Description = "Running",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	KnockBackTiles = 4,
	CastTime = {
		[1] = 3000,
		[2] = 2500,
		[3] = 2000,
		[4] = 1500,
		[5] = 100,
		[6] = 500,
		[7] = 0,
		[8] = 0,
		[9] = 0,
		[10] = 0
	},
	AfterCastActDelay = 300,
	SkillData1 = 1000,
	SkillData2 = 150000,
	FixedCastTime = {
		[1] = 3000,
		[2] = 2500,
		[3] = 2000,
		[4] = 1500,
		[5] = 1000,
		[6] = 500,
		[7] = 0,
		[8] = 0,
		[9] = 0,
		[10] = 0
	},
	Requirements = {
		SPCost = {
			[1] = 100,
			[2] = 90,
			[3] = 80,
			[4] = 70,
			[5] = 60,
			[6] = 50,
			[7] = 40,
			[8] = 30,
			[9] = 20,
			[10] = 10
		},
		State = PlayerState.Moveable
	}
},
[ "TK_READYSTORM" ] = {
	Id = 412,
	Description = "Tornado Stance",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 1
	}
},
[ "TK_STORMKICK" ] = {
	Id = 413,
	Description = "Tornado Kick",
	MaxLevel = 7,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	NumberOfHits: -3,
	Requirements = {
		SPCost = {
			[1] = 14,
			[2] = 12,
			[3] = 10,
			[4] = 8,
			[5] = 6,
			[6] = 4,
			[7] = 2,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "TK_READYDOWN" ] = {
	Id = 414,
	Description = "Heel Drop Stance",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 1
	}
},
[ "TK_DOWNKICK" ] = {
	Id = 415,
	Description = "Heel Drop",
	MaxLevel = 7,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -3,
	SkillData2 = 3000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 14,
			[2] = 12,
			[3] = 10,
			[4] = 8,
			[5] = 6,
			[6] = 4,
			[7] = 2,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "TK_READYTURN" ] = {
	Id = 416,
	Description = "Roundhouse Stance",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 1
	}
},
[ "TK_TURNKICK" ] = {
	Id = 417,
	Description = "Roundhouse Kick",
	MaxLevel = 7,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	NumberOfHits: -3,
	KnockBackTiles = 2,
	SkillData2 = 2000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 14,
			[2] = 12,
			[3] = 10,
			[4] = 8,
			[5] = 6,
			[6] = 4,
			[7] = 2,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "TK_READYCOUNTER" ] = {
	Id = 418,
	Description = "Counter Kick Stance",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 1
	}
},
[ "TK_COUNTER" ] = {
	Id = 419,
	Description = "Counter Kick",
	MaxLevel = 7,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	NumberOfHits: -3,
	Requirements = {
		SPCost = {
			[1] = 14,
			[2] = 12,
			[3] = 10,
			[4] = 8,
			[5] = 6,
			[6] = 4,
			[7] = 2,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "TK_DODGE" ] = {
	Id = 420,
	Description = "Tumbling",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 1
	}
},
[ "TK_JUMPKICK" ] = {
	Id = 421,
	Description = "Flying Kick",
	MaxLevel = 7,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits: -3,
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 60,
			[3] = 50,
			[4] = 40,
			[5] = 30,
			[6] = 20,
			[7] = 10,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "TK_HPTIME" ] = {
	Id = 422,
	Description = "Peaceful Break",
	MaxLevel = 10,
	SplashRange = 1,
	NumberOfHits = 0
},
[ "TK_SPTIME" ] = {
	Id = 423,
	Description = "Happy Break",
	MaxLevel = 10,
	SplashRange = 1,
	NumberOfHits = 0,
	SkillData1 = 1800000,
	FixedCastTime = 0
},
[ "TK_POWER" ] = {
	Id = 424,
	Description = "Kihop",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "TK_SEVENWIND" ] = {
	Id = 425,
	Description = "Mild Wind",
	MaxLevel = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = {
		[1] = Element.Earth,
		[2] = Element.Wind,
		[3] = Element.Water,
		[4] = Element.Fire,
		[5] = Element.Ghost,
		[6] = Element.Dark,
		[7] = Element.Holy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 300000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 20,
			[3] = 20,
			[4] = 20,
			[5] = 50,
			[6] = 50,
			[7] = 50,
			[8] = 50,
			[9] = 50,
			[10] = 50
		}
	}
},
[ "TK_HIGHJUMP" ] = {
	Id = 426,
	Description = "Taekwon Jump",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 2500,
		[2] = 2000,
		[3] = 1500,
		[4] = 1000,
		[5] = 500,
		[6] = 500,
		[7] = 500,
		[8] = 500,
		[9] = 500,
		[10] = 500
	},
	FixedCastTime = {
		[1] = 2500,
		[2] = 2000,
		[3] = 1500,
		[4] = 1000,
		[5] = 500,
		[6] = 500,
		[7] = 500,
		[8] = 500,
		[9] = 500,
		[10] = 500
	},
	Requirements = {
		SPCost = 50
	}
},
[ "SG_FEEL" ] = {
	Id = 427,
	Description = "Feeling the Sun Moon and Stars",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	FixedCastTime = 3000,
	Requirements = {
		SPCost = 100
	}
},
[ "SG_SUN_WARM" ] = {
	Id = 428,
	Description = "Warmth of the Sun",
	MaxLevel = 3,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	InterruptCast = true,
	KnockBackTiles = 2,
	SkillData1 = {
		[1] = 10000,
		[2] = 20000,
		[3] = 60000,
		[4] = 60000,
		[5] = 60000,
		[6] = 60000,
		[7] = 60000,
		[8] = 60000,
		[9] = 60000,
		[10] = 60000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20
	},
	Placement = {
		Id = 0x86,
		Range = 1,
		Interval = 100,
		Target = "Enemy"
	}
},
[ "SG_MOON_WARM" ] = {
	Id = 429,
	Description = "Warmth of the Moon",
	MaxLevel = 3,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	InterruptCast = true,
	KnockBackTiles = 2,
	SkillData1 = {
		[1] = 10000,
		[2] = 20000,
		[3] = 60000,
		[4] = 60000,
		[5] = 60000,
		[6] = 60000,
		[7] = 60000,
		[8] = 60000,
		[9] = 60000,
		[10] = 60000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 20
	},
	Placement = {
		Id = 0x86,
		Range = 1,
		Interval = 100,
		Target = "Enemy"
	}
},
[ "SG_STAR_WARM" ] = {
	Id = 430,
	Description = "Warmth of the Stars",
	MaxLevel = 3,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	InterruptCast = true,
	KnockBackTiles = 2,
	SkillData1 = {
		[1] = 10000,
		[2] = 20000,
		[3] = 60000,
		[4] = 60000,
		[5] = 60000,
		[6] = 60000,
		[7] = 60000,
		[8] = 60000,
		[9] = 60000,
		[10] = 60000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	},
	Placement = {
		Id = 0x86,
		Range = 1,
		Interval = 100,
		Target = "Enemy"
	}
},
[ "SG_SUN_COMFORT" ] = {
	Id = 431,
	Description = "Comfort of the Sun",
	MaxLevel = 4,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 80000,
		[2] = 160000,
		[3] = 240000,
		[4] = 320000,
		[5] = 400000,
		[6] = 480000,
		[7] = 560000,
		[8] = 640000,
		[9] = 720000,
		[10] = 800000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 60,
			[3] = 50,
			[4] = 40,
			[5] = 30,
			[6] = 20,
			[7] = 10,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SG_MOON_COMFORT" ] = {
	Id = 432,
	Description = "Comfort of the Moon",
	MaxLevel = 4,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 80000,
		[2] = 160000,
		[3] = 240000,
		[4] = 320000,
		[5] = 400000,
		[6] = 480000,
		[7] = 560000,
		[8] = 640000,
		[9] = 720000,
		[10] = 800000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 60,
			[3] = 50,
			[4] = 40,
			[5] = 30,
			[6] = 20,
			[7] = 10,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SG_STAR_COMFORT" ] = {
	Id = 433,
	Description = "Comfort of the Stars",
	MaxLevel = 4,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 80000,
		[2] = 160000,
		[3] = 240000,
		[4] = 320000,
		[5] = 400000,
		[6] = 480000,
		[7] = 560000,
		[8] = 640000,
		[9] = 720000,
		[10] = 800000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 60,
			[3] = 50,
			[4] = 40,
			[5] = 30,
			[6] = 20,
			[7] = 10,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SG_HATE" ] = {
	Id = 434,
	Description = "Hatred of the Sun Moon and Stars",
	MaxLevel = 3,
	Range = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	FixedCastTime = 3000,
	Requirements = {
		SPCost = 100
	}
},
[ "SG_SUN_ANGER" ] = {
	Id = 435,
	Description = "Anger of the Sun",
	MaxLevel = 3,
	NumberOfHits = 0
},
[ "SG_MOON_ANGER" ] = {
	Id = 436,
	Description = "Anger of the Moon",
	MaxLevel = 3,
	NumberOfHits = 0
},
[ "SG_STAR_ANGER" ] = {
	Id = 437,
	Description = "Anger of the Stars",
	MaxLevel = 3,
	NumberOfHits = 0
},
[ "SG_SUN_BLESS" ] = {
	Id = 438,
	Description = "Blessing of the Sun",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "SG_MOON_BLESS" ] = {
	Id = 439,
	Description = "Blessing of the Moon",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "SG_STAR_BLESS" ] = {
	Id = 440,
	Description = "Blessing of the Stars",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "SG_DEVIL" ] = {
	Id = 441,
	Description = "Demon of the Sun Moon and Stars",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "SG_FRIEND" ] = {
	Id = 442,
	Description = "Friend of the Sun Moon and Stars",
	MaxLevel = 3,
	NumberOfHits = 0,
	SkillData1 = 10000,
	FixedCastTime = 0
},
[ "SG_KNOWLEDGE" ] = {
	Id = 443,
	Description = "Knowledge of the Sun Moon and Stars",
	MaxLevel = 10,
	NumberOfHits = 0,
	SkillData1 = 600000,
	FixedCastTime = 0
},
[ "SG_FUSION" ] = {
	Id = 444,
	Description = "Union of the Sun Moon and Stars",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 600000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 100
	}
},
[ "SL_ALCHEMIST" ] = {
	Id = 445,
	Description = "Spirit of the Alchemist",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "AM_BERSERKPITCHER" ] = {
	Id = 446,
	Description = "Aid Berserk Potion",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.LearntFromBuff,
		SkillBehavior.OnlyParty,
		SkillBehavior.OnlyGuild
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 10,
		SPRateCost = 8,
		Items = {
			Item[ "Berserk_Potion" ] = 2
		}
	}
},
[ "SL_MONK" ] = {
	Id = 447,
	Description = "Spirit of the Monk",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_STAR" ] = {
	Id = 448,
	Description = "Spirit of the Star Gladiator",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 800,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 200,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_SAGE" ] = {
	Id = 449,
	Description = "Spirit of the Sage",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_CRUSADER" ] = {
	Id = 450,
	Description = "Spirit of the Crusader",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_SUPERNOVICE" ] = {
	Id = 451,
	Description = "Spirit of the Supernovice",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_KNIGHT" ] = {
	Id = 452,
	Description = "Spirit of the Knight",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_WIZARD" ] = {
	Id = 453,
	Description = "Spirit of the Wizard",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_PRIEST" ] = {
	Id = 454,
	Description = "Spirit of the Priest",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_BARDDANCER" ] = {
	Id = 455,
	Description = "Spirit of the Artist",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_ROGUE" ] = {
	Id = 456,
	Description = "Spirit of the Rogue",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_ASSASIN" ] = {
	Id = 457,
	Description = "Spirit of the Assasin",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_BLACKSMITH" ] = {
	Id = 458,
	Description = "Spirit of the Blacksmith",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "BS_ADRENALINE2" ] = {
	Id = 459,
	Description = "Advanced Adrenaline Rush",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromBuff
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	KnockBackTiles = 0,
	SkillData1 = 150000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 64,
		WeaponTypes = {
			WeaponType.Fist,
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar
		}
	}
},
[ "SL_HUNTER" ] = {
	Id = 460,
	Description = "Spirit of the Hunter",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_SOULLINKER" ] = {
	Id = 461,
	Description = "Spirit of the Soul Linker",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_KAIZEL" ] = {
	Id = 462,
	Description = "Kaizel",
	MaxLevel = 7,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 3600,
		[2] = 3200,
		[3] = 2800,
		[4] = 2400,
		[5] = 2000,
		[6] = 2000,
		[7] = 2000,
		[8] = 2000,
		[9] = 2000,
		[10] = 2000
	},
	SkillData1 = 1800000,
	SkillData2 = 2000,
	FixedCastTime = {
		[1] = 900,
		[2] = 800,
		[3] = 700,
		[4] = 600,
		[5] = 500,
		[6] = 500,
		[7] = 500,
		[8] = 500,
		[9] = 500,
		[10] = 500
	},
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex
	},
	Requirements = {
		SPCost = {
			[1] = 120,
			[2] = 110,
			[3] = 100,
			[4] = 90,
			[5] = 80,
			[6] = 70,
			[7] = 60,
			[8] = 50,
			[9] = 40,
			[10] = 30
		}
	}
},
[ "SL_KAAHI" ] = {
	Id = 463,
	Description = "Kaahi",
	MaxLevel = 7,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 1800000,
	SkillData2 = 500,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 30
	}
},
[ "SL_KAUPE" ] = {
	Id = 464,
	Description = "Kaupe",
	MaxLevel = 3,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 400,
	SkillData1 = 600000,
	FixedCastTime = 100,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 30,
			[3] = 40,
			[4] = 50,
			[5] = 60,
			[6] = 70,
			[7] = 80,
			[8] = 90,
			[9] = 100,
			[10] = 110
		}
	}
},
[ "SL_KAITE" ] = {
	Id = 465,
	Description = "Kaite",
	MaxLevel = 7,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 4800,
		[2] = 4400,
		[3] = 4000,
		[4] = 3600,
		[5] = 3200,
		[6] = 2800,
		[7] = 2400,
		[8] = 2400,
		[9] = 2400,
		[10] = 2400
	},
	SkillData1 = {
		[1] = 60000,
		[2] = 120000,
		[3] = 180000,
		[4] = 240000,
		[5] = 300000,
		[6] = 360000,
		[7] = 600000,
		[8] = 600000,
		[9] = 600000,
		[10] = 600000
	},
	FixedCastTime = {
		[1] = 1200,
		[2] = 1100,
		[3] = 1000,
		[4] = 900,
		[5] = 800,
		[6] = 700,
		[7] = 600,
		[8] = 600,
		[9] = 600,
		[10] = 600
	},
	Requirements = {
		SPCost = 70
	}
},
[ "SL_KAINA" ] = {
	Id = 466,
	Description = "Kaina",
	MaxLevel = 7,
	AttackType = AttackType.Magic,
	NumberOfHits = 0,
	InterruptCast = true
},
[ "SL_STIN" ] = {
	Id = 467,
	Description = "Estin",
	MaxLevel = 7,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.EndowedElement,
	KnockBackTiles = 2,
	CastTime = 80,
	AfterCastActDelay = 500,
	FixedCastTime = 20,
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 20,
			[3] = 22,
			[4] = 24,
			[5] = 26,
			[6] = 28,
			[7] = 30,
			[8] = 32,
			[9] = 34,
			[10] = 36
		}
	}
},
[ "SL_STUN" ] = {
	Id = 468,
	Description = "Estun",
	MaxLevel = 7,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.EndowedElement,
	CastTime = 80,
	AfterCastActDelay = 500,
	SkillData1 = 2000,
	FixedCastTime = 20,
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 20,
			[3] = 22,
			[4] = 24,
			[5] = 26,
			[6] = 28,
			[7] = 30,
			[8] = 32,
			[9] = 34,
			[10] = 36
		}
	}
},
[ "SL_SMA" ] = {
	Id = 469,
	Description = "Esma",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.EndowedElement,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = 1600,
	AfterCastActDelay = 500,
	SkillData1 = 3000,
	FixedCastTime = 400,
	Requirements = {
		SPCost = {
			[1] = 8,
			[2] = 16,
			[3] = 24,
			[4] = 32,
			[5] = 40,
			[6] = 48,
			[7] = 56,
			[8] = 64,
			[9] = 72,
			[10] = 80
		}
	}
},
[ "SL_SWOO" ] = {
	Id = 470,
	Description = "Eswoo",
	MaxLevel = 7,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 800,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 1000,
		[2] = 2000,
		[3] = 3000,
		[4] = 4000,
		[5] = 5000,
		[6] = 6000,
		[7] = 7000,
		[8] = 8000,
		[9] = 9000,
		[10] = 10000
	},
	FixedCastTime = 200,
	Requirements = {
		SPCost = {
			[1] = 75,
			[2] = 65,
			[3] = 55,
			[4] = 45,
			[5] = 35,
			[6] = 25,
			[7] = 15,
			[8] = 5,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_SKE" ] = {
	Id = 471,
	Description = "Eske",
	MaxLevel = 3,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 2400,
		[2] = 1600,
		[3] = 800,
		[4] = 800,
		[5] = 800,
		[6] = 800,
		[7] = 800,
		[8] = 800,
		[9] = 800,
		[10] = 800
	},
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 10000,
		[2] = 20000,
		[3] = 30000,
		[4] = 40000,
		[5] = 50000,
		[6] = 60000,
		[7] = 70000,
		[8] = 80000,
		[9] = 90000,
		[10] = 100000
	},
	SkillData2 = 3000,
	FixedCastTime = {
		[1] = 600,
		[2] = 400,
		[3] = 200,
		[4] = 200,
		[5] = 200,
		[6] = 200,
		[7] = 200,
		[8] = 200,
		[9] = 200,
		[10] = 200
	},
	Requirements = {
		SPCost = {
			[1] = 55,
			[2] = 35,
			[3] = 15,
			[4] = 1,
			[5] = 1,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SL_SKA" ] = {
	Id = 472,
	Description = "Eska",
	MaxLevel = 3,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 2400,
		[2] = 1600,
		[3] = 800,
		[4] = 800,
		[5] = 800,
		[6] = 800,
		[7] = 800,
		[8] = 800,
		[9] = 800,
		[10] = 800
	},
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 10000,
		[2] = 20000,
		[3] = 30000,
		[4] = 40000,
		[5] = 50000,
		[6] = 60000,
		[7] = 70000,
		[8] = 80000,
		[9] = 90000,
		[10] = 100000
	},
	FixedCastTime = {
		[1] = 600,
		[2] = 400,
		[3] = 200,
		[4] = 200,
		[5] = 200,
		[6] = 200,
		[7] = 200,
		[8] = 200,
		[9] = 200,
		[10] = 200
	},
	Requirements = {
		SPCost = {
			[1] = 100,
			[2] = 80,
			[3] = 60,
			[4] = 40,
			[5] = 20,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SM_SELFPROVOKE" ] = {
	Id = 473,
	Description = "Provoke Self",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	SkillData1 = 30000
},
[ "NPC_EMOTION_ON" ] = {
	Id = 474,
	Description = "Emotion ON",
	MaxLevel = 10,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "ST_PRESERVE" ] = {
	Id = 475,
	Description = "Preserve",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 600000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 30
	}
},
[ "ST_FULLSTRIP" ] = {
	Id = 476,
	Description = "Divest All",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 75000,
		[2] = 90000,
		[3] = 105000,
		[4] = 120000,
		[5] = 135000,
		[6] = 150000,
		[7] = 165000,
		[8] = 180000,
		[9] = 195000,
		[10] = 210000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 24,
			[3] = 26,
			[4] = 28,
			[5] = 30,
			[6] = 32,
			[7] = 34,
			[8] = 36,
			[9] = 38,
			[10] = 40
		}
	}
},
[ "WS_WEAPONREFINE" ] = {
	Id = 477,
	Description = "Upgrade Weapon",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 5
	}
},
[ "CR_SLIMPITCHER" ] = {
	Id = 478,
	Description = "Aid Condensed Potion",
	MaxLevel = 10,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 30,
		Items = {
			Item[ "Red_Slim_Potion" ] = 1,
			Item[ "Red_Slim_Potion" ] = 1,
			Item[ "Red_Slim_Potion" ] = 1,
			Item[ "Red_Slim_Potion" ] = 1,
			Item[ "Red_Slim_Potion" ] = 1,
			Item[ "Yellow_Slim_Potion" ] = 1,
			Item[ "Yellow_Slim_Potion" ] = 1,
			Item[ "Yellow_Slim_Potion" ] = 1,
			Item[ "Yellow_Slim_Potion" ] = 1,
			Item[ "White_Slim_Potion" ] = 1
		}
	}
},
[ "CR_FULLPROTECTION" ] = {
	Id = 479,
	Description = "Full Protection",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 120000,
		[2] = 240000,
		[3] = 360000,
		[4] = 480000,
		[5] = 600000,
		[6] = 720000,
		[7] = 840000,
		[8] = 960000,
		[9] = 1080000,
		[10] = 1200000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 40,
		Items = {
			Item[ "Coating_Bottle" ] = 1
		}
	}
},
[ "PA_SHIELDCHAIN" ] = {
	Id = 480,
	Description = "Shield Chain",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 5,
	CastTime = 800,
	AfterCastActDelay = 1000,
	FixedCastTime = 200,
	Requirements = {
		SPCost = {
			[1] = 28,
			[2] = 31,
			[3] = 34,
			[4] = 37,
			[5] = 40,
			[6] = 43,
			[7] = 46,
			[8] = 49,
			[9] = 52,
			[10] = 55
		},
		State = PlayerState.Equipped_Shield
	}
},
[ "HP_MANARECHARGE" ] = {
	Id = 481,
	Description = "Mana Recharge",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "PF_DOUBLECASTING" ] = {
	Id = 482,
	Description = "Double Casting",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 1600,
	SkillData1 = 90000,
	FixedCastTime = 400,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex
	},
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		}
	}
},
[ "HW_GANBANTEIN" ] = {
	Id = 483,
	Description = "Ganbantein",
	MaxLevel = 1,
	Range = 16,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	AfterCastActDelay = 5000,
	FixedCastTime = 3000,
	Requirements = {
		SPCost = 40,
		Items = {
			Item[ "Yellow_Gemstone" ] = 1,
			Item[ "Blue_Gemstone" ] = 1
		}
	}
},
[ "HW_GRAVITATION" ] = {
	Id = 484,
	Description = "Gravitation Field",
	MaxLevel = 5,
	Range = 18,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Misc,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		IgnoreElement = true,
		IgnoreDefCards = true
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 5000,
		[2] = 6000,
		[3] = 7000,
		[4] = 8000,
		[5] = 9000,
		[6] = 10000,
		[7] = 11000,
		[8] = 12000,
		[9] = 13000,
		[10] = 14000
	},
	FixedCastTime = 5000,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 40,
			[3] = 60,
			[4] = 80,
			[5] = 100,
			[6] = 120,
			[7] = 140,
			[8] = 160,
			[9] = 180,
			[10] = 200
		},
		Items = {
			Item[ "Blue_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = 0xb8,
		Layout = 2,
		Interval = 500,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.AffectOnContact
		}
	}
},
[ "WS_CARTTERMINATION" ] = {
	Id = 485,
	Description = "Cart Termination",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.Ignore_Equip_Atk
	},
	SkillData2 = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15,
		ZenyCost = {
			[1] = 600,
			[2] = 700,
			[3] = 800,
			[4] = 900,
			[5] = 1000,
			[6] = 1100,
			[7] = 1200,
			[8] = 1300,
			[9] = 1400,
			[10] = 1500
		},
		WeaponTypes = {
			WeaponType.Fist,
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar,
			WeaponType.Revolver,
			WeaponType.Rifle,
			WeaponType.GatlingGun,
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher,
			WeaponType.FuumaShuriken
		},
		State = PlayerState.Cart_Boost
	}
},
[ "WS_OVERTHRUSTMAX" ] = {
	Id = 486,
	Description = "Maximum Power Thrust",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 180000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15,
		ZenyCost = {
			[1] = 3000,
			[2] = 3500,
			[3] = 4000,
			[4] = 4500,
			[5] = 5000,
			[6] = 5500,
			[7] = 6000,
			[8] = 6500,
			[9] = 7000,
			[10] = 7500
		},
		WeaponTypes = {
			WeaponType.Fist,
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar,
			WeaponType.Revolver,
			WeaponType.Rifle,
			WeaponType.GatlingGun,
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher,
			WeaponType.FuumaShuriken
		}
	}
},
[ "CG_LONGINGFREEDOM" ] = {
	Id = 487,
	Description = "Longing for Freedom",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 180000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15
	}
},
[ "CG_HERMODE" ] = {
	Id = 488,
	Description = "Wand of Hermode",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.EnsembleSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 1,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	SkillData2 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 30,
			[3] = 40,
			[4] = 50,
			[5] = 60,
			[6] = 70,
			[7] = 80,
			[8] = 90,
			[9] = 100,
			[10] = 110
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	},
	Placement = {
		Id = 0xb9,
		Layout = 3,
		Interval = -1,
		Target = "All",
		Behavior = {
			PlacementBehavior.Immovable
		}
	}
},
[ "CG_TAROTCARD" ] = {
	Id = 489,
	Description = "Tarot Card of Fate",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.IgnoreFlee
	},
	CastTime = 500,
	AfterCastActDelay = 3000,
	SkillData2 = 30000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = 40
	}
},
[ "CR_ACIDDEMONSTRATION" ] = {
	Id = 490,
	Description = "Acid Demonstration",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	NumberOfHits = {
		[1] = -1,
		[2] = -2,
		[3] = -3,
		[4] = -4,
		[5] = -5,
		[6] = -6,
		[7] = -7,
		[8] = -8,
		[9] = -9,
		[10] = -10
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 30,
		Items = {
			Item[ "Fire_Bottle" ] = 1,
			Item[ "Acid_Bottle" ] = 1
		}
	}
},
[ "CR_CULTIVATION" ] = {
	Id = 491,
	Description = "Plant Cultivation",
	MaxLevel = 2,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 300000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Mushroom_Spore" ] = 1,
			Item[ "Stem" ] = 1
		}
	}
},
[ "ITEM_ENCHANTARMS" ] = {
	Id = 492,
	Description = "Weapon Enchantment",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	Element = {
		[1] = Element.Neutral,
		[2] = Element.Water,
		[3] = Element.Earth,
		[4] = Element.Fire,
		[5] = Element.Wind,
		[6] = Element.Poison,
		[7] = Element.Holy,
		[8] = Element.Dark,
		[9] = Element.Ghost,
		[10] = Element.Undead
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 180000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 1
	}
},
[ "TK_MISSION" ] = {
	Id = 493,
	Description = "Taekwon Mission",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 10
	}
},
[ "SL_HIGH" ] = {
	Id = 494,
	Description = "Spirit of Rebirth",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 150000,
		[2] = 200000,
		[3] = 250000,
		[4] = 300000,
		[5] = 350000,
		[6] = 400000,
		[7] = 450000,
		[8] = 500000,
		[9] = 550000,
		[10] = 600000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 460,
			[2] = 360,
			[3] = 260,
			[4] = 160,
			[5] = 60,
			[6] = 1,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "KN_ONEHAND" ] = {
	Id = 495,
	Description = "Onehand Quicken",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromBuff
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 300000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 100,
		WeaponTypes = {
			WeaponType.OneHandedSword
		}
	}
},
[ "AM_TWILIGHT1" ] = {
	Id = 496,
	Description = "Twilight Alchemy 1",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromBuff
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	FixedCastTime = 3000,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex
	},
	Requirements = {
		SPCost = 200,
		Items = {
			Item[ "Medicine_Bowl" ] = 200
		}
	}
},
[ "AM_TWILIGHT2" ] = {
	Id = 497,
	Description = "Twilight Alchemy 2",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromBuff
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	FixedCastTime = 3000,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex
	},
	Requirements = {
		SPCost = 200,
		Items = {
			Item[ "Medicine_Bowl" ] = 200
		}
	}
},
[ "AM_TWILIGHT3" ] = {
	Id = 498,
	Description = "Twilight Alchemy 3",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromBuff
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	FixedCastTime = 3000,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex
	},
	Requirements = {
		SPCost = 200,
		Items = {
			Item[ "Medicine_Bowl" ] = 200
		}
	}
},
[ "HT_POWER" ] = {
	Id = 499,
	Description = "Beast Strafing",
	MaxLevel = 1,
	Range: -9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromBuff
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 2,
	AfterCastActDelay = 100,
	SkillData1 = 100,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 12,
		WeaponTypes = {
			WeaponType.Bow
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	}
},
[ "GS_GLITTERING" ] = {
	Id = 500,
	Description = "Flip the Coin",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	SkillData1 = 600000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 2,
		ZenyCost = 1
	}
},
[ "GS_FLING" ] = {
	Id = 501,
	Description = "Fling",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Misc,
	Element = Element.WeaponElement,
	DamageBehavior = {
		IgnoreElement = true,
		DamageBehavior.IgnoreFlee
	},
	SkillData1 = 30000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		SpiritSphereCost = 5
	}
},
[ "GS_TRIPLEACTION" ] = {
	Id = 502,
	Description = "Triple Action",
	MaxLevel = 1,
	Range: -9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 3,
	Requirements = {
		SPCost = 20,
		AmmoTypes = "All",
		AmmoAmount = 1,
		SpiritSphereCost = 1
	}
},
[ "GS_BULLSEYE" ] = {
	Id = 503,
	Description = "Bulls Eye",
	MaxLevel = 1,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.Ignore_Equip_Atk
	},
	CastTime = 800,
	AfterCastActDelay = 1000,
	FixedCastTime = 200,
	Requirements = {
		SPCost = 30,
		AmmoTypes = "All",
		AmmoAmount = 1,
		SpiritSphereCost = 1
	}
},
[ "GS_MADNESSCANCEL" ] = {
	Id = 504,
	Description = "Madness Canceller",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 1600,
	AfterCastActDelay = 3000,
	SkillData1 = 15000,
	FixedCastTime = 400,
	Requirements = {
		SPCost = 30,
		SpiritSphereCost = 4
	}
},
[ "GS_ADJUSTMENT" ] = {
	Id = 505,
	Description = "AdJustment",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 800,
	AfterCastActDelay = 2000,
	SkillData1 = 30000,
	FixedCastTime = 200,
	Requirements = {
		SPCost = 15,
		SpiritSphereCost = 2
	}
},
[ "GS_INCREASING" ] = {
	Id = 506,
	Description = "Increasing Accuracy",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData1 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 30,
		SpiritSphereCost = 4
	}
},
[ "GS_MAGICALBULLET" ] = {
	Id = 507,
	Description = "Magical Bullet",
	MaxLevel = 1,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Ghost,
	Requirements = {
		SPCost = 7,
		SpiritSphereCost = 1
	}
},
[ "GS_CRACKER" ] = {
	Id = 508,
	Description = "Cracker",
	MaxLevel = 1,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData2 = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		AmmoTypes = "All",
		AmmoAmount = 1,
		SpiritSphereCost = 1
	}
},
[ "GS_SINGLEACTION" ] = {
	Id = 509,
	Description = "Single Action",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "GS_SNAKEEYE" ] = {
	Id = 510,
	Description = "Snake Eye",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "GS_CHAINACTION" ] = {
	Id = 511,
	Description = "Chain Action",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_MULTIHIT",
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 2
},
[ "GS_TRACKING" ] = {
	Id = 512,
	Description = "Tracking",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	InterruptCast = true,
	CastTime = {
		[1] = 600,
		[2] = 700,
		[3] = 800,
		[4] = 900,
		[5] = 1000,
		[6] = 1100,
		[7] = 1200,
		[8] = 1300,
		[9] = 1400,
		[10] = 1500
	},
	AfterCastActDelay = 1500,
	FixedCastTime = {
		[1] = 600,
		[2] = 700,
		[3] = 800,
		[4] = 900,
		[5] = 1000,
		[6] = 1100,
		[7] = 1200,
		[8] = 1300,
		[9] = 1400,
		[10] = 1500
	},
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffects
	},
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 20,
			[3] = 25,
			[4] = 30,
			[5] = 35,
			[6] = 40,
			[7] = 45,
			[8] = 50,
			[9] = 55,
			[10] = 60
		},
		WeaponTypes = {
			WeaponType.Revolver,
			WeaponType.Rifle
		},
		AmmoTypes = {
			AmmoType.Bullet
		},
		AmmoAmount = 1
	}
},
[ "GS_DISARM" ] = {
	Id = 513,
	Description = "Disarm",
	MaxLevel = 5,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	CastTime = 1600,
	AfterCastActDelay = 1000,
	SkillData1 = 30000,
	FixedCastTime = 400,
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 20,
			[3] = 25,
			[4] = 30,
			[5] = 35,
			[6] = 40,
			[7] = 45,
			[8] = 50,
			[9] = 55,
			[10] = 60
		},
		WeaponTypes = {
			WeaponType.Revolver,
			WeaponType.Rifle
		},
		AmmoTypes = {
			AmmoType.Bullet
		},
		AmmoAmount = 1
	}
},
[ "GS_PIERCINGSHOT" ] = {
	Id = 514,
	Description = "Piercing Shot",
	MaxLevel = 5,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.Ignore_Soft_Def
	},
	CastTime = 1200,
	AfterCastActDelay = 500,
	SkillData2 = 120000,
	FixedCastTime = 300,
	Requirements = {
		SPCost = {
			[1] = 11,
			[2] = 12,
			[3] = 13,
			[4] = 14,
			[5] = 15,
			[6] = 16,
			[7] = 17,
			[8] = 18,
			[9] = 19,
			[10] = 20
		},
		WeaponTypes = {
			WeaponType.Revolver,
			WeaponType.Rifle
		},
		AmmoTypes = {
			AmmoType.Bullet
		},
		AmmoAmount = 1
	}
},
[ "GS_RAPIDSHOWER" ] = {
	Id = 515,
	Description = "Rapid Shower",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 5,
	AfterCastActDelay = 1500,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 24,
			[3] = 26,
			[4] = 28,
			[5] = 30,
			[6] = 32,
			[7] = 34,
			[8] = 36,
			[9] = 38,
			[10] = 40
		},
		WeaponTypes = {
			WeaponType.Revolver
		},
		AmmoTypes = {
			AmmoType.Bullet
		},
		AmmoAmount = 5
	}
},
[ "GS_DESPERADO" ] = {
	Id = 516,
	Description = "Desperado",
	MaxLevel = 10,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	AfterCastActDelay = 1000,
	AfterCastWalkDelay = 1000,
	SkillData1 = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 32,
			[2] = 34,
			[3] = 36,
			[4] = 38,
			[5] = 40,
			[6] = 42,
			[7] = 44,
			[8] = 46,
			[9] = 48,
			[10] = 50
		},
		WeaponTypes = {
			WeaponType.Revolver
		},
		AmmoTypes = {
			AmmoType.Bullet
		},
		AmmoAmount = 10
	},
	Placement = {
		Id = 0x86,
		Layout = 3,
		Interval = 100,
		Target = "Enemy"
	}
},
[ "GS_GATLINGFEVER" ] = {
	Id = 517,
	Description = "Gatling Fever",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 800,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	FixedCastTime = 200,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 32,
			[3] = 34,
			[4] = 36,
			[5] = 38,
			[6] = 40,
			[7] = 42,
			[8] = 44,
			[9] = 46,
			[10] = 48
		},
		WeaponTypes = {
			WeaponType.GatlingGun
		}
	}
},
[ "GS_DUST" ] = {
	Id = 518,
	Description = "Dust",
	MaxLevel = 10,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	KnockBackTiles = 5,
	CastTime = 1200,
	AfterCastActDelay = 1000,
	FixedCastTime = 300,
	Requirements = {
		SPCost = {
			[1] = 3,
			[2] = 6,
			[3] = 9,
			[4] = 12,
			[5] = 15,
			[6] = 18,
			[7] = 21,
			[8] = 24,
			[9] = 27,
			[10] = 30
		},
		WeaponTypes = {
			WeaponType.Shotgun
		},
		AmmoTypes = {
			AmmoType.Bullet
		},
		AmmoAmount = 1
	}
},
[ "GS_FULLBUSTER" ] = {
	Id = 519,
	Description = "Full Buster",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	InterruptCast = true,
	CastTime = 800,
	AfterCastActDelay = {
		[1] = 1200,
		[2] = 1400,
		[3] = 1600,
		[4] = 1800,
		[5] = 2000,
		[6] = 2200,
		[7] = 2400,
		[8] = 2600,
		[9] = 2800,
		[10] = 3000
	},
	SkillData2 = 10000,
	FixedCastTime = 200,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		},
		WeaponTypes = {
			WeaponType.Shotgun
		},
		AmmoTypes = {
			AmmoType.Bullet
		},
		AmmoAmount = {
			[1] = 2,
			[2] = 2,
			[3] = 4,
			[4] = 4,
			[5] = 6,
			[6] = 6,
			[7] = 8,
			[8] = 8,
			[9] = 10,
			[10] = 10
		}
	}
},
[ "GS_SPREADATTACK" ] = {
	Id = 520,
	Description = "Spread Attack",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 1,
		[4] = 2,
		[5] = 2,
		[6] = 2,
		[7] = 3,
		[8] = 3,
		[9] = 3,
		[10] = 4
	},
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 20,
			[3] = 25,
			[4] = 30,
			[5] = 35,
			[6] = 40,
			[7] = 45,
			[8] = 50,
			[9] = 55,
			[10] = 60
		},
		WeaponTypes = {
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher
		},
		AmmoTypes = {
			AmmoType.Bullet
		},
		AmmoAmount = 5
	}
},
[ "GS_GROUNDDRIFT" ] = {
	Id = 521,
	Description = "Ground Drift",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 1,
	KnockBackTiles = 3,
	CastTime = 800,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 3000,
		[2] = 6000,
		[3] = 9000,
		[4] = 12000,
		[5] = 15000,
		[6] = 18000,
		[7] = 21000,
		[8] = 24000,
		[9] = 27000,
		[10] = 30000
	},
	SkillData2 = 10000,
	FixedCastTime = 200,
	Requirements = {
		SPCost = {
			[1] = 4,
			[2] = 8,
			[3] = 12,
			[4] = 16,
			[5] = 20,
			[6] = 24,
			[7] = 28,
			[8] = 32,
			[9] = 36,
			[10] = 40
		},
		WeaponTypes = {
			WeaponType.GrenadeLauncher
		},
		AmmoTypes = {
			AmmoType.Grenade
		},
		AmmoAmount = 1
	},
	Placement = {
		Id = 0xbe,
		Range = 1,
		Interval = 1000,
		Target = "Enemy"
	}
},
[ "NJ_TOBIDOUGU" ] = {
	Id = 522,
	Description = "Shuriken Training",
	MaxLevel = 10,
	AttackType = AttackType.Weapon
},
[ "NJ_SYURIKEN" ] = {
	Id = 523,
	Description = "Throw Shuriken",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	Requirements = {
		SPCost = 2,
		AmmoTypes = {
			AmmoType.Shuriken
		},
		AmmoAmount = 1
	}
},
[ "NJ_KUNAI" ] = {
	Id = 524,
	Description = "Throw Kunai",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	NumberOfHits = 3,
	AfterCastActDelay = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 25,
			[3] = 20,
			[4] = 15,
			[5] = 10,
			[6] = 5,
			[7] = 1,
			[8] = 1,
			[9] = 1,
			[10] = 1
		},
		AmmoTypes = {
			AmmoType.Kunai
		},
		AmmoAmount = 1
	}
},
[ "NJ_HUUMA" ] = {
	Id = 525,
	Description = "Throw Huuma Shuriken",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	NumberOfHits = {
		[1] = -3,
		[2] = -3,
		[3] = -4,
		[4] = -4,
		[5] = -5,
		[6] = -5,
		[7] = -6,
		[8] = -6,
		[9] = -7,
		[10] = -7
	},
	CastTime = {
		[1] = 2400,
		[2] = 2400,
		[3] = 2400,
		[4] = 2400,
		[5] = 2400,
		[6] = 2400,
		[7] = 2400,
		[8] = 2400,
		[9] = 2400,
		[10] = 2400
	},
	AfterCastActDelay = 2000,
	SkillData1 = 100,
	FixedCastTime = 600,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		},
		WeaponTypes = {
			WeaponType.FuumaShuriken
		}
	},
	Placement = {
		Id = 0x86,
		Range = 2,
		Interval = 100,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "NJ_ZENYNAGE" ] = {
	Id = 526,
	Description = "Throw Zeny",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		IgnoreElement = true,
		DamageBehavior.IgnoreFlee
	},
	AfterCastActDelay = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 50,
		ZenyCost = {
			[1] = 500,
			[2] = 1000,
			[3] = 1500,
			[4] = 2000,
			[5] = 2500,
			[6] = 3000,
			[7] = 3500,
			[8] = 4000,
			[9] = 4500,
			[10] = 5000
		}
	}
},
[ "NJ_TATAMIGAESHI" ] = {
	Id = 527,
	Description = "Improvised Defense",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	KnockBackTiles = 4,
	AfterCastActDelay = 3000,
	SkillData1 = 3000,
	SkillData2 = 3000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15
	},
	Placement = {
		Id = 0xbc,
		Layout = -1,
		Interval = 2000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "NJ_KASUMIKIRI" ] = {
	Id = 528,
	Description = "Vanishing Slash",
	MaxLevel = 10,
	Range = -1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 30000,
		[2] = 60000,
		[3] = 90000,
		[4] = 120000,
		[5] = 150000,
		[6] = 180000,
		[7] = 210000,
		[8] = 240000,
		[9] = 270000,
		[10] = 300000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15
	}
},
[ "NJ_SHADOWJUMP" ] = {
	Id = 529,
	Description = "Shadow Leap",
	MaxLevel = 5,
	Range = {
		[1] = 7,
		[2] = 9,
		[3] = 11,
		[4] = 13,
		[5] = 15,
		[6] = 17,
		[7] = 19,
		[8] = 21,
		[9] = 23,
		[10] = 25
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		State = PlayerState.Hiding
	}
},
[ "NJ_KIRIKAGE" ] = {
	Id = 530,
	Description = "Shadow Slash",
	MaxLevel = 5,
	Range = {
		[1] = 7,
		[2] = 9,
		[3] = 11,
		[4] = 13,
		[5] = 15,
		[6] = 17,
		[7] = 19,
		[8] = 21,
		[9] = 23,
		[10] = 25
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = 10,
		State = PlayerState.Hiding
	}
},
[ "NJ_UTSUSEMI" ] = {
	Id = 531,
	Description = "Cicada Skin Sheeding",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	KnockBackTiles = 7,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 15,
			[3] = 18,
			[4] = 21,
			[5] = 24,
			[6] = 27,
			[7] = 30,
			[8] = 33,
			[9] = 36,
			[10] = 39
		}
	}
},
[ "NJ_BUNSINJYUTSU" ] = {
	Id = 532,
	Description = "Mirror Image",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 3200,
		[2] = 2800,
		[3] = 2400,
		[4] = 2000,
		[5] = 1600,
		[6] = 1200,
		[7] = 800,
		[8] = 800,
		[9] = 800,
		[10] = 800
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 60000,
		[2] = 80000,
		[3] = 100000,
		[4] = 120000,
		[5] = 140000,
		[6] = 160000,
		[7] = 180000,
		[8] = 200000,
		[9] = 220000,
		[10] = 240000
	},
	FixedCastTime = {
		[1] = 800,
		[2] = 700,
		[3] = 600,
		[4] = 500,
		[5] = 400,
		[6] = 300,
		[7] = 200,
		[8] = 200,
		[9] = 200,
		[10] = 200
	},
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 32,
			[3] = 34,
			[4] = 36,
			[5] = 38,
			[6] = 40,
			[7] = 42,
			[8] = 44,
			[9] = 46,
			[10] = 48
		},
		Items = {
			Item[ "Shadow_Orb" ] = 1
		}
	}
},
[ "NJ_NINPOU" ] = {
	Id = 533,
	Description = "Spirit of the Blade",
	MaxLevel = 10,
	NumberOfHits = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "NJ_KOUENKA" ] = {
	Id = 534,
	Description = "Crimson Fire Petal",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = {
		[1] = 560,
		[2] = 1120,
		[3] = 1680,
		[4] = 2240,
		[5] = 2800,
		[6] = 3360,
		[7] = 3840,
		[8] = 4480,
		[9] = 5040,
		[10] = 5600
	},
	FixedCastTime = {
		[1] = 140,
		[2] = 280,
		[3] = 420,
		[4] = 560,
		[5] = 700,
		[6] = 840,
		[7] = 960,
		[8] = 1120,
		[9] = 1260,
		[10] = 1400
	},
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 20,
			[3] = 22,
			[4] = 24,
			[5] = 26,
			[6] = 28,
			[7] = 30,
			[8] = 32,
			[9] = 34,
			[10] = 36
		}
	}
},
[ "NJ_KAENSIN" ] = {
	Id = 535,
	Description = "Crimson Fire Formation",
	MaxLevel = 10,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	InterruptCast = true,
	CastTime = {
		[1] = 4800,
		[2] = 4400,
		[3] = 4000,
		[4] = 3600,
		[5] = 3200,
		[6] = 2800,
		[7] = 2400,
		[8] = 2000,
		[9] = 1600,
		[10] = 1200
	},
	AfterCastActDelay = 1000,
	SkillData1 = 20000,
	FixedCastTime = {
		[1] = 1200,
		[2] = 1100,
		[3] = 1000,
		[4] = 900,
		[5] = 800,
		[6] = 700,
		[7] = 600,
		[8] = 500,
		[9] = 400,
		[10] = 300
	},
	Requirements = {
		SPCost = 25,
		Items = {
			Item[ "Flame_Stone" ] = 1
		}
	},
	Placement = {
		Id = 0xbd,
		Layout = -1,
		Interval = 20,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "NJ_BAKUENRYU" ] = {
	Id = 536,
	Description = "Raging Fire Dragon",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	NumberOfHits = 3,
	InterruptCast = true,
	CastTime = 2400,
	AfterCastActDelay = 2000,
	FixedCastTime = 600,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		},
		Items = {
			Item[ "Flame_Stone" ] = 1
		}
	}
},
[ "NJ_HYOUSENSOU" ] = {
	Id = 537,
	Description = "Spear of Ice",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	NumberOfHits = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	InterruptCast = true,
	CastTime = {
		[1] = 560,
		[2] = 1120,
		[3] = 1680,
		[4] = 2240,
		[5] = 2800,
		[6] = 3360,
		[7] = 3840,
		[8] = 4480,
		[9] = 5040,
		[10] = 5600
	},
	FixedCastTime = {
		[1] = 140,
		[2] = 280,
		[3] = 420,
		[4] = 560,
		[5] = 700,
		[6] = 840,
		[7] = 960,
		[8] = 1120,
		[9] = 1260,
		[10] = 1400
	},
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 18,
			[3] = 21,
			[4] = 24,
			[5] = 27,
			[6] = 30,
			[7] = 33,
			[8] = 36,
			[9] = 39,
			[10] = 42
		}
	}
},
[ "NJ_SUITON" ] = {
	Id = 538,
	Description = "Hidden Water",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2400,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 15000,
		[2] = 20000,
		[3] = 25000,
		[4] = 30000,
		[5] = 35000,
		[6] = 40000,
		[7] = 45000,
		[8] = 50000,
		[9] = 55000,
		[10] = 60000
	},
	SkillData2 = {
		[1] = 15000,
		[2] = 20000,
		[3] = 25000,
		[4] = 30000,
		[5] = 35000,
		[6] = 40000,
		[7] = 45000,
		[8] = 50000,
		[9] = 55000,
		[10] = 60000
	},
	FixedCastTime = 600,
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 18,
			[3] = 21,
			[4] = 24,
			[5] = 27,
			[6] = 30,
			[7] = 33,
			[8] = 36,
			[9] = 39,
			[10] = 42
		},
		Items = {
			Item[ "Ice_Stone" ] = 1
		}
	},
	Placement = {
		Id = 0xbb,
		Layout = {
			[1] = 1,
			[2] = 1,
			[3] = 1,
			[4] = 2,
			[5] = 2,
			[6] = 2,
			[7] = 3,
			[8] = 3,
			[9] = 3,
			[10] = 4
		},
		Interval = -1,
		Target = "All",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "NJ_HYOUSYOURAKU" ] = {
	Id = 539,
	Description = "Ice Meteor",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	InterruptCast = true,
	CastTime = {
		[1] = 1600,
		[2] = 2000,
		[3] = 2400,
		[4] = 2800,
		[5] = 3200,
		[6] = 3200,
		[7] = 3200,
		[8] = 3200,
		[9] = 3200,
		[10] = 3200
	},
	AfterCastActDelay = 2000,
	SkillData2 = {
		[1] = 10000,
		[2] = 11000,
		[3] = 12000,
		[4] = 13000,
		[5] = 14000,
		[6] = 15000,
		[7] = 16000,
		[8] = 17000,
		[9] = 18000,
		[10] = 19000
	},
	FixedCastTime = {
		[1] = 400,
		[2] = 500,
		[3] = 600,
		[4] = 700,
		[5] = 800,
		[6] = 800,
		[7] = 800,
		[8] = 800,
		[9] = 800,
		[10] = 800
	},
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		},
		Items = {
			Item[ "Ice_Stone" ] = 1
		}
	}
},
[ "NJ_HUUJIN" ] = {
	Id = 540,
	Description = "Wind Blade",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 2,
		[4] = 3,
		[5] = 3,
		[6] = 4,
		[7] = 4,
		[8] = 5,
		[9] = 5,
		[10] = 6
	},
	InterruptCast = true,
	CastTime = {
		[1] = 800,
		[2] = 1200,
		[3] = 1600,
		[4] = 2000,
		[5] = 2400,
		[6] = 2800,
		[7] = 3200,
		[8] = 3600,
		[9] = 4000,
		[10] = 4400
	},
	AfterCastActDelay = 1000,
	FixedCastTime = {
		[1] = 200,
		[2] = 300,
		[3] = 400,
		[4] = 500,
		[5] = 600,
		[6] = 700,
		[7] = 800,
		[8] = 900,
		[9] = 1000,
		[10] = 1100
	},
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		}
	}
},
[ "NJ_RAIGEKISAI" ] = {
	Id = 541,
	Description = "Lightning Strike of Destruction",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 2,
		[3] = 3,
		[4] = 3,
		[5] = 4,
		[6] = 4,
		[7] = 5,
		[8] = 5,
		[9] = 6,
		[10] = 6
	},
	InterruptCast = true,
	CastTime = 3200,
	SkillData1 = 100,
	FixedCastTime = 800,
	Requirements = {
		SPCost = {
			[1] = 16,
			[2] = 20,
			[3] = 24,
			[4] = 28,
			[5] = 32,
			[6] = 36,
			[7] = 40,
			[8] = 44,
			[9] = 48,
			[10] = 52
		},
		Items = {
			Item[ "Wind_Stone" ] = 1
		}
	},
	Placement = {
		Id = 0x86,
		Range = {
			[1] = 3,
			[2] = 3,
			[3] = 4,
			[4] = 4,
			[5] = 5,
			[6] = 5,
			[7] = 6,
			[8] = 6,
			[9] = 7,
			[10] = 7
		},
		Interval = 100,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "NJ_KAMAITACHI" ] = {
	Id = 542,
	Description = "Kamaitachi",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	SplashRange = 3,
	InterruptCast = true,
	SkillInstances = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	CastTime = 3200,
	FixedCastTime = 800,
	Requirements = {
		SPCost = {
			[1] = 24,
			[2] = 28,
			[3] = 32,
			[4] = 36,
			[5] = 40,
			[6] = 44,
			[7] = 48,
			[8] = 52,
			[9] = 56,
			[10] = 60
		},
		Items = {
			Item[ "Wind_Stone" ] = 1
		}
	}
},
[ "NJ_NEN" ] = {
	Id = 543,
	Description = "Soul",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 4000,
		[2] = 3200,
		[3] = 2400,
		[4] = 1600,
		[5] = 800,
		[6] = 800,
		[7] = 800,
		[8] = 800,
		[9] = 800,
		[10] = 800
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	FixedCastTime = {
		[1] = 1000,
		[2] = 800,
		[3] = 600,
		[4] = 400,
		[5] = 200,
		[6] = 200,
		[7] = 200,
		[8] = 200,
		[9] = 200,
		[10] = 200
	},
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 30,
			[3] = 40,
			[4] = 50,
			[5] = 60,
			[6] = 70,
			[7] = 80,
			[8] = 90,
			[9] = 100,
			[10] = 110
		},
		HPRateCost: -5
	}
},
[ "NJ_ISSEN" ] = {
	Id = 544,
	Description = "Final Strike",
	MaxLevel = 10,
	Range: -5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	Requirements = {
		SPCost = {
			[1] = 55,
			[2] = 60,
			[3] = 65,
			[4] = 70,
			[5] = 75,
			[6] = 80,
			[7] = 85,
			[8] = 90,
			[9] = 95,
			[10] = 100
		}
	}
},
[ "NPC_EARTHQUAKE" ] = {
	Id = 653,
	Description = "Earthquake",
	MaxLevel = 10,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.IgnoreLandProtector,
		SkillBehavior.ShowSkillScale
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.SplitBetweenTargets,
		DamageBehavior.Ignore_Soft_Def
	},
	SplashRange = {
		[1] = 5,
		[2] = 7,
		[3] = 9,
		[4] = 11,
		[5] = 13,
		[6] = 5,
		[7] = 7,
		[8] = 9,
		[9] = 11,
		[10] = 13
	},
	SkillData1 = 900,
	FixedCastTime = -1,
	Placement = {
		Id = 0xc6,
		Range = {
			[1] = 5,
			[2] = 7,
			[3] = 9,
			[4] = 11,
			[5] = 13,
			[6] = 5,
			[7] = 7,
			[8] = 9,
			[9] = 11,
			[10] = 13
		},
		Interval = 300,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "NPC_FIREBREATH" ] = {
	Id = 654,
	Description = "Fire Breath",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire,
	SplashRange = 5,
	SkillInstances = 14
},
[ "NPC_ICEBREATH" ] = {
	Id = 655,
	Description = "Ice Breath",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Water,
	SplashRange = 5,
	SkillInstances = 14,
	SkillData2 = 12000,
	FixedCastTime = -1
},
[ "NPC_THUNDERBREATH" ] = {
	Id = 656,
	Description = "Thunder Breath",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Wind,
	SplashRange = 5,
	SkillInstances = 14
},
[ "NPC_ACIDBREATH" ] = {
	Id = 657,
	Description = "Acid Breath",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Poison,
	SplashRange = 5,
	SkillInstances = 14,
	SkillData2 = 60000,
	FixedCastTime = -1
},
[ "NPC_DARKNESSBREATH" ] = {
	Id = 658,
	Description = "Darkness Breath",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Dark,
	SplashRange = 5,
	SkillInstances = 14
},
[ "NPC_DRAGONFEAR" ] = {
	Id = 659,
	Description = "Dragon Fear",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 5,
		[3] = 8,
		[4] = 11,
		[5] = 14,
		[6] = 17,
		[7] = 20,
		[8] = 23,
		[9] = 26,
		[10] = 29
	},
	SkillData2 = {
		[1] = 5000,
		[2] = 30000,
		[3] = 30000,
		[4] = 120000,
		[5] = 120000,
		[6] = 120000,
		[7] = 120000,
		[8] = 120000,
		[9] = 120000,
		[10] = 120000
	},
	FixedCastTime = -1
},
[ "NPC_BLEEDING" ] = {
	Id = 660,
	Description = "Bleeding",
	MaxLevel = 5,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SkillData2 = 120000,
	FixedCastTime = -1
},
[ "NPC_PULSESTRIKE" ] = {
	Id = 661,
	Description = "Pulse Strike",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 7,
	KnockBackTiles = 7
},
{
	Id = 662,
	Name = "NPC_HELLJUDGEMENT",
	Description = "Hell's Judgement",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 14,
	SkillData2 = 30000,
	FixedCastTime = -1
},
[ "NPC_WIDESILENCE" ] = {
	Id = 663,
	Description = "Wide Silence",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 5,
		[3] = 8,
		[4] = 11,
		[5] = 14,
		[6] = 17,
		[7] = 20,
		[8] = 23,
		[9] = 26,
		[10] = 29
	},
	SkillData2 = 30000,
	FixedCastTime = -1
},
[ "NPC_WIDEFREEZE" ] = {
	Id = 664,
	Description = "Wide Freeze",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 5,
		[3] = 8,
		[4] = 11,
		[5] = 14,
		[6] = 17,
		[7] = 20,
		[8] = 23,
		[9] = 26,
		[10] = 29
	},
	SkillData2 = 12000,
	FixedCastTime = -1
},
[ "NPC_WIDEBLEEDING" ] = {
	Id = 665,
	Description = "Wide Bleeding",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 5,
		[3] = 8,
		[4] = 11,
		[5] = 14,
		[6] = 17,
		[7] = 20,
		[8] = 23,
		[9] = 26,
		[10] = 29
	},
	SkillData2 = 120000,
	FixedCastTime = -1
},
[ "NPC_WIDESTONE" ] = {
	Id = 666,
	Description = "Wide Petrify",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 5,
		[3] = 8,
		[4] = 11,
		[5] = 14,
		[6] = 17,
		[7] = 20,
		[8] = 23,
		[9] = 26,
		[10] = 29
	},
	SkillData2 = 20000,
	FixedCastTime = -1
},
[ "NPC_WIDECONFUSE" ] = {
	Id = 667,
	Description = "Wide Confusion",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 5,
		[3] = 8,
		[4] = 11,
		[5] = 14,
		[6] = 17,
		[7] = 20,
		[8] = 23,
		[9] = 26,
		[10] = 29
	},
	SkillData2 = 30000,
	FixedCastTime = -1
},
[ "NPC_WIDESLEEP" ] = {
	Id = 668,
	Description = "Wide Sleep",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 5,
		[3] = 8,
		[4] = 11,
		[5] = 14,
		[6] = 17,
		[7] = 20,
		[8] = 23,
		[9] = 26,
		[10] = 29
	},
	SkillData2 = 30000,
	FixedCastTime = -1
},
[ "NPC_WIDESIGHT" ] = {
	Id = 669,
	Description = "Wide Sight",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 5,
	SkillData1 = 10000,
	FixedCastTime = -1
},
[ "NPC_EVILLAND" ] = {
	Id = 670,
	Description = "Evil Land",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	AttackType = AttackType.Magic,
	Element = Element.Dark,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		IgnoreElement = true,
		IgnoreDefCards = true
	},
	SkillData1 = 30000,
	SkillData2 = 30000,
	FixedCastTime = -1,
	Placement = {
		Id = 0xc7,
		Layout = 1,
		Range = {
			[1] = 4,
			[2] = 7,
			[3] = 10,
			[4] = 13,
			[5] = 16,
			[6] = 19,
			[7] = 22,
			[8] = 25,
			[9] = 28,
			[10] = 31
		},
		Interval = 1000,
		Target = "All",
		Behavior = {
			PlacementBehavior.CannotOverlap
		}
	}
},
[ "NPC_MAGICMIRROR" ] = {
	Id = 671,
	Description = "Magic Mirror",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 30000,
	FixedCastTime = -1
},
[ "NPC_SLOWCAST" ] = {
	Id = 672,
	Description = "Slow Cast",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 5,
		[3] = 8,
		[4] = 11,
		[5] = 14,
		[6] = 17,
		[7] = 20,
		[8] = 23,
		[9] = 26,
		[10] = 29
	},
	SkillData2 = 30000,
	FixedCastTime = -1
},
[ "NPC_CRITICALWOUND" ] = {
	Id = 673,
	Description = "Critical Wounds",
	MaxLevel = 5,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SkillData2 = 30000,
	FixedCastTime = -1
},
[ "NPC_EXPULSION" ] = {
	Id = 674,
	Description = "Expulsion",
	MaxLevel = 1,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "NPC_STONESKIN" ] = {
	Id = 675,
	Description = "Stone Skin",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 30000,
	FixedCastTime = -1
},
[ "NPC_ANTIMAGIC" ] = {
	Id = 676,
	Description = "Anti Magic",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 30000,
	FixedCastTime = -1
},
[ "NPC_WIDECURSE" ] = {
	Id = 677,
	Description = "Wide Curse",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 5,
		[3] = 8,
		[4] = 11,
		[5] = 14,
		[6] = 17,
		[7] = 20,
		[8] = 23,
		[9] = 26,
		[10] = 29
	},
	SkillData2 = 30000,
	FixedCastTime = -1
},
[ "NPC_WIDESTUN" ] = {
	Id = 678,
	Description = "Wide Stun",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 5,
		[3] = 8,
		[4] = 11,
		[5] = 14,
		[6] = 17,
		[7] = 20,
		[8] = 23,
		[9] = 26,
		[10] = 29
	},
	SkillData2 = 5000,
	FixedCastTime = -1
},
[ "NPC_VAMPIRE_GIFT" ] = {
	Id = 679,
	Description = "Vampire Gift",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 5,
		[2] = 7,
		[3] = 9,
		[4] = 11,
		[5] = 13,
		[6] = 13,
		[7] = 13,
		[8] = 13,
		[9] = 13,
		[10] = 13
	}
},
[ "NPC_WIDESOULDRAIN" ] = {
	Id = 680,
	Description = "Wide Soul Drain",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill,
		SkillBehavior.ShowSkillScale
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 5,
		[2] = 7,
		[3] = 9,
		[4] = 11,
		[5] = 13,
		[6] = 13,
		[7] = 13,
		[8] = 13,
		[9] = 13,
		[10] = 13
	}
},
[ "ALL_INCCARRY" ] = {
	Id = 681,
	Description = "Increase Weight Limit R",
	MaxLevel = 10,
	SkillInfo = {
		SkillBehavior.LearntFromQuest
	},
	NumberOfHits = 0
},
[ "NPC_TALK" ] = {
	Id = 682,
	Description = "Talk",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	}
},
[ "NPC_HELLPOWER" ] = {
	Id = 683,
	Description = "Hell Power",
	MaxLevel = 1,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.NPC_Skill
	},
	Element = Element.WeaponElement,
	SkillData2 = 300000,
	FixedCastTime = -1
},
[ "NPC_WIDEHELLDIGNITY" ] = {
	Id = 684,
	Description = "Hell Dignity",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	SkillData2 = 300000,
	FixedCastTime = -1
},
[ "NPC_INVINCIBLE" ] = {
	Id = 685,
	Description = "Invincible",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1
},
[ "NPC_INVINCIBLEOFF" ] = {
	Id = 686,
	Description = "Invincible off",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 60000,
	FixedCastTime = -1
},
[ "NPC_ALLHEAL" ] = {
	Id = 687,
	Description = "Full Heal",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true
},
[ "GM_SANDMAN" ] = {
	Id = 688,
	Description = "GM Sandman",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	Requirements = {
		SPCost = 1
	}
},
[ "CASH_BLESSING" ] = {
	Id = 689,
	Description = "Party Blessing",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	InterruptCast = true,
	SkillData1 = {
		[1] = 60000,
		[2] = 80000,
		[3] = 100000,
		[4] = 120000,
		[5] = 140000,
		[6] = 160000,
		[7] = 180000,
		[8] = 200000,
		[9] = 220000,
		[10] = 240000
	},
	FixedCastTime = -1
},
[ "CASH_INCAGI" ] = {
	Id = 690,
	Description = "Party Increase AGI",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	InterruptCast = true,
	SkillData1 = {
		[1] = 60000,
		[2] = 80000,
		[3] = 100000,
		[4] = 120000,
		[5] = 140000,
		[6] = 160000,
		[7] = 180000,
		[8] = 200000,
		[9] = 220000,
		[10] = 240000
	},
	FixedCastTime = -1
},
[ "CASH_ASSUMPTIO" ] = {
	Id = 691,
	Description = "Party Assumptio",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	InterruptCast = true,
	SkillData1 = {
		[1] = 20000,
		[2] = 40000,
		[3] = 60000,
		[4] = 80000,
		[5] = 100000,
		[6] = 120000,
		[7] = 140000,
		[8] = 160000,
		[9] = 180000,
		[10] = 200000
	},
	FixedCastTime = -1
},
[ "ALL_CATCRY" ] = {
	Id = 692,
	Description = "Cat Cry",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 50
	}
},
[ "ALL_PARTYFLEE" ] = {
	Id = 693,
	Description = "Party Flee",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	InterruptCast = true
},
{
	Id = 694,
	Name = "ALL_ANGEL_PROTECT",
	Description = "Angel's Protection",
	MaxLevel = 1,
	Range = 6,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.NPC_Skill,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	SkillData1 = 30000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "ALL_DREAM_SUMMERNIGHT" ] = {
	Id = 695,
	Description = "Summer Night Dream",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 12000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "ALL_REVERSEORCISH" ] = {
	Id = 697,
	Description = "Reverse Orcish",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 1200000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "ALL_WEWISH" ] = {
	Id = 698,
	Description = "Christmas Carol",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.NPC_Skill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 20000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "KN_CHARGEATK" ] = {
	Id = 1001,
	Description = "Charge Attack",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	CastTime = 250,
	FixedCastTime = 250,
	Requirements = {
		SPCost = 40
	}
},
[ "CR_SHRINK" ] = {
	Id = 1002,
	Description = "Shrink",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	KnockBackTiles = 2,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 15,
		State = PlayerState.Equipped_Shield
	}
},
[ "AS_SONICACCEL" ] = {
	Id = 1003,
	Description = "Sonic Acceleration",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "AS_VENOMKNIFE" ] = {
	Id = 1004,
	Description = "Throw Venom Knife",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.Ignore_Equip_Atk
	},
	SkillData2 = {
		[1] = 15000,
		[2] = 20000,
		[3] = 25000,
		[4] = 30000,
		[5] = 35000,
		[6] = 40000,
		[7] = 45000,
		[8] = 50000,
		[9] = 55000,
		[10] = 60000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = 15,
		AmmoTypes = {
			AmmoType.Throwable_Dagger
		},
		AmmoAmount = 1
	}
},
[ "RG_CLOSECONFINE" ] = {
	Id = 1005,
	Description = "Close Confine",
	MaxLevel = 1,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 25
	}
},
[ "WZ_SIGHTBLASTER" ] = {
	Id = 1006,
	Description = "Sight Blaster",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	SplashRange = 1,
	InterruptCast = true,
	KnockBackTiles = 3,
	CastTime = 1280,
	SkillData1 = 120000,
	FixedCastTime = 320,
	Requirements = {
		SPCost = 40
	}
},
[ "SA_CREATECON" ] = {
	Id = 1007,
	Description = "Create Elemental Converter",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	Requirements = {
		SPCost = 30
	}
},
[ "SA_ELEMENTWATER" ] = {
	Id = 1008,
	Description = "Elemental Change Water",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 1800000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 30,
		Items = {
			Item[ "Elemental_Water" ] = 1
		}
	}
},
[ "HT_PHANTASMIC" ] = {
	Id = 1009,
	Description = "Phantasmic Arrow",
	MaxLevel = 1,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	KnockBackTiles = 3,
	Requirements = {
		SPCost = 10,
		WeaponTypes = {
			WeaponType.Bow
		}
	}
},
[ "BA_PANGVOICE" ] = {
	Id = 1010,
	Description = "Pang Voice",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	CastTime = 800,
	AfterCastActDelay = 2000,
	SkillData1 = 17000,
	FixedCastTime = 200,
	Requirements = {
		SPCost = 20
	}
},
[ "DC_WINKCHARM" ] = {
	Id = 1011,
	Description = "Wink of Charm",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	CastTime = 800,
	AfterCastActDelay = 2000,
	SkillData1 = 10000,
	SkillData2 = 17000,
	FixedCastTime = 200,
	Requirements = {
		SPCost = 40
	}
},
[ "BS_UNFAIRLYTRICK" ] = {
	Id = 1012,
	Description = "Unfair Trick",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "BS_GREED" ] = {
	Id = 1013,
	Description = "Greed",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	NumberOfHits = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "PR_REDEMPTIO" ] = {
	Id = 1014,
	Description = "Redemptio",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 14,
	NumberOfHits = 0,
	InterruptCast = true,
	CastTime = 3200,
	FixedCastTime = 800,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex
	},
	Requirements = {
		SPCost = 400
	}
},
[ "MO_KITRANSLATION" ] = {
	Id = 1015,
	Description = "Ki Translation",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.LearntFromQuest,
		SkillBehavior.OnlyParty,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = 600000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 40,
		SpiritSphereCost = 1
	}
},
[ "MO_BALKYOUNG" ] = {
	Id = 1016,
	Description = "Ki Explosion",
	MaxLevel = 1,
	Range = -1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	KnockBackTiles = 5,
	AfterCastActDelay = 2000,
	SkillData2 = 5000,
	FixedCastTime = -1,
	Requirements = {
		HPCost = 10,
		SPCost = 20
	}
},
[ "SA_ELEMENTGROUND" ] = {
	Id = 1017,
	Description = "Elemental Change Earth",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 1800000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 30,
		Items = {
			Item[ "Elemental_Earth" ] = 1
		}
	}
},
[ "SA_ELEMENTFIRE" ] = {
	Id = 1018,
	Description = "Elemental Change Fire",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 1800000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 30,
		Items = {
			Item[ "Elemental_Fire" ] = 1
		}
	}
},
[ "SA_ELEMENTWIND" ] = {
	Id = 1019,
	Description = "Elemental Change Wind",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 1800000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 30,
		Items = {
			Item[ "Elemental_Wind" ] = 1
		}
	}
},
[ "RK_ENCHANTBLADE" ] = {
	Id = 2001,
	Description = "Enchant Blade",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		}
	}
},
[ "RK_SONICWAVE" ] = {
	Id = 2002,
	Description = "Sonic Wave",
	MaxLevel = 5,
	Range = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = 1000,
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 35,
			[3] = 40,
			[4] = 45,
			[5] = 50,
			[6] = 55,
			[7] = 60,
			[8] = 65,
			[9] = 70,
			[10] = 75
		}
	}
},
[ "RK_DEATHBOUND" ] = {
	Id = 2003,
	Description = "Death Bound",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	KnockBackTiles = 3,
	AfterCastActDelay = 2000,
	SkillData1 = 2000,
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 28,
			[2] = 31,
			[3] = 34,
			[4] = 37,
			[5] = 40,
			[6] = 43,
			[7] = 46,
			[8] = 49,
			[9] = 52,
			[10] = 55
		}
	}
},
[ "RK_HUNDREDSPEAR" ] = {
	Id = 2004,
	Description = "Hundred Spear",
	MaxLevel = 10,
	Range = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -5,
	CastTime = {
		[1] = 1000,
		[2] = 900,
		[3] = 800,
		[4] = 700,
		[5] = 600,
		[6] = 500,
		[7] = 400,
		[8] = 300,
		[9] = 200,
		[10] = 100
	},
	AfterCastActDelay = 500,
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 60,
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "RK_WINDCUTTER" ] = {
	Id = 2005,
	Description = "Wind Cutter",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	KnockBackTiles = 3,
	SkillData1 = 15000,
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 24,
			[3] = 28,
			[4] = 32,
			[5] = 36,
			[6] = 40,
			[7] = 44,
			[8] = 48,
			[9] = 52,
			[10] = 56
		},
		WeaponTypes = {
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "RK_IGNITIONBREAK" ] = {
	Id = 2006,
	Description = "Ignition Break",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 5,
	CastTime = 1000,
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 35,
			[2] = 40,
			[3] = 45,
			[4] = 50,
			[5] = 55,
			[6] = 60,
			[7] = 65,
			[8] = 70,
			[9] = 75,
			[10] = 80
		},
		WeaponTypes = {
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "RK_DRAGONTRAINING" ] = {
	Id = 2007,
	Description = "Dragon Training",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "RK_DRAGONBREATH" ] = {
	Id = 2008,
	Description = "Dragon Breath",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 1,
		[4] = 2,
		[5] = 2,
		[6] = 2,
		[7] = 3,
		[8] = 3,
		[9] = 4,
		[10] = 4
	},
	CastTime = {
		[1] = 0,
		[2] = 0,
		[3] = 0,
		[4] = 1000,
		[5] = 1000,
		[6] = 1000,
		[7] = 1500,
		[8] = 1500,
		[9] = 2000,
		[10] = 2000
	},
	AfterCastActDelay = 2000,
	SkillData1 = 10000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 35,
			[3] = 40,
			[4] = 45,
			[5] = 50,
			[6] = 55,
			[7] = 60,
			[8] = 65,
			[9] = 70,
			[10] = 75
		},
		State = PlayerState.MountedDragon
	}
},
[ "RK_DRAGONHOWLING" ] = {
	Id = 2009,
	Description = "Dragon Howling",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	InterruptCast = true,
	SkillData1 = 15000,
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 30,
		State = PlayerState.MountedDragon
	}
},
[ "RK_RUNEMASTERY" ] = {
	Id = 2010,
	Description = "Rune Mastery",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "RK_MILLENNIUMSHIELD" ] = {
	Id = 2011,
	Description = "Millenium Shield",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 180000,
	SkillData2 = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "RK_CRUSHSTRIKE" ] = {
	Id = 2012,
	Description = "Crush Strike",
	MaxLevel = 1,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SplashRange = 0,
	InterruptCast = true,
	SkillData1 = 180000,
	SkillData2 = 30000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 1
	}
},
[ "RK_REFRESH" ] = {
	Id = 2013,
	Description = "Refresh",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 60000,
	SkillData2 = 120000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 1
	}
},
[ "RK_GIANTGROWTH" ] = {
	Id = 2014,
	Description = "Giant Growth",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 180000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 1
	}
},
[ "RK_STONEHARDSKIN" ] = {
	Id = 2015,
	Description = "Stone Hard Skin",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 180000,
	SkillData2 = 10000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 1
	}
},
[ "RK_VITALITYACTIVATION" ] = {
	Id = 2016,
	Description = "Vitality Activation",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 180000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "RK_STORMBLAST" ] = {
	Id = 2017,
	Description = "Storm Blast",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	KnockBackTiles = 7,
	CastTime = 2000,
	AfterCastActDelay = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "RK_FIGHTINGSPIRIT" ] = {
	Id = 2018,
	Description = "Fighting Spirit",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	InterruptCast = true,
	SkillData1 = 180000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "RK_ABUNDANCE" ] = {
	Id = 2019,
	Description = "Abundance",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 180000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "RK_PHANTOMTHRUST" ] = {
	Id = 2020,
	Description = "Phantom Thrust",
	MaxLevel = 5,
	Range = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	InterruptCast = true,
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 18,
			[3] = 21,
			[4] = 24,
			[5] = 27,
			[6] = 30,
			[7] = 33,
			[8] = 36,
			[9] = 39,
			[10] = 42
		},
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "GC_VENOMIMPRESS" ] = {
	Id = 2021,
	Description = "Venom Impress",
	MaxLevel = 5,
	Range = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = {
		[1] = 3000,
		[2] = 2500,
		[3] = 2000,
		[4] = 1500,
		[5] = 1000,
		[6] = 500,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData1 = {
		[1] = 10000,
		[2] = 20000,
		[3] = 30000,
		[4] = 40000,
		[5] = 50000,
		[6] = 60000,
		[7] = 70000,
		[8] = 80000,
		[9] = 90000,
		[10] = 100000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 16,
			[3] = 20,
			[4] = 24,
			[5] = 28,
			[6] = 32,
			[7] = 36,
			[8] = 40,
			[9] = 44,
			[10] = 48
		}
	}
},
[ "GC_CROSSIMPACT" ] = {
	Id = 2022,
	Description = "Cross Impact",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -7,
	AfterCastActDelay = {
		[1] = 2500,
		[2] = 2000,
		[3] = 1500,
		[4] = 1000,
		[5] = 500,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = 25,
		State = PlayerState.Moveable
	}
},
[ "GC_DARKILLUSION" ] = {
	Id = 2023,
	Description = "Dark Illusion",
	MaxLevel = 5,
	Range = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = 1500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		}
	}
},
[ "GC_RESEARCHNEWPOISON" ] = {
	Id = 2024,
	Description = "Research New Poison",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "GC_CREATENEWPOISON" ] = {
	Id = 2025,
	Description = "Create New Poison",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 10
	}
},
[ "GC_ANTIDOTE" ] = {
	Id = 2026,
	Description = "Antidote",
	MaxLevel = 1,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Guillotine_Antidote" ] = 1
		}
	}
},
[ "GC_POISONINGWEAPON" ] = {
	Id = 2027,
	Description = "Poisoning Weapon",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 60000,
		[2] = 120000,
		[3] = 180000,
		[4] = 240000,
		[5] = 300000,
		[6] = 360000,
		[7] = 420000,
		[8] = 480000,
		[9] = 540000,
		[10] = 600000
	},
	SkillData2 = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 24,
			[3] = 28,
			[4] = 32,
			[5] = 36,
			[6] = 40,
			[7] = 44,
			[8] = 48,
			[9] = 52,
			[10] = 56
		}
	}
},
[ "GC_WEAPONBLOCKING" ] = {
	Id = 2028,
	Description = "Weapon Blocking",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 2000,
	SkillData1 = 180000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 36,
			[3] = 32,
			[4] = 28,
			[5] = 24,
			[6] = 20,
			[7] = 16,
			[8] = 12,
			[9] = 8,
			[10] = 4
		}
	}
},
[ "GC_COUNTERSLASH" ] = {
	Id = 2029,
	Description = "Counter Slash",
	MaxLevel = 5,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	KnockBackTiles = 3,
	AfterCastActDelay = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 5,
			[2] = 8,
			[3] = 11,
			[4] = 14,
			[5] = 17,
			[6] = 20,
			[7] = 23,
			[8] = 26,
			[9] = 29,
			[10] = 32
		}
	}
},
[ "GC_WEAPONCRUSH" ] = {
	Id = 2030,
	Description = "Weapon Crush",
	MaxLevel = 5,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData1 = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 20
	}
},
[ "GC_VENOMPRESSURE" ] = {
	Id = 2031,
	Description = "Venom Pressure",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 40,
			[3] = 50,
			[4] = 60,
			[5] = 70,
			[6] = 80,
			[7] = 90,
			[8] = 100,
			[9] = 110,
			[10] = 120
		},
		State = PlayerState.PoisonedWeapon
	}
},
[ "GC_POISONSMOKE" ] = {
	Id = 2032,
	Description = "Poison Smoke",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 1,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 6000,
		[2] = 8000,
		[3] = 10000,
		[4] = 12000,
		[5] = 14000,
		[6] = 16000,
		[7] = 18000,
		[8] = 20000,
		[9] = 22000,
		[10] = 24000
	},
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 40,
		State = PlayerState.PoisonedWeapon
	},
	Placement = {
		Id = 0xe1,
		Layout = 2,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "GC_CLOAKINGEXCEED" ] = {
	Id = 2033,
	Description = "Cloaking Exceed",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 45
	}
},
[ "GC_PHANTOMMENACE" ] = {
	Id = 2034,
	Description = "Phantom Menace",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	AfterCastActDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 30
	}
},
[ "GC_HALLUCINATIONWALK" ] = {
	Id = 2035,
	Description = "Hallucination Walk",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 35000,
		[3] = 40000,
		[4] = 45000,
		[5] = 50000,
		[6] = 55000,
		[7] = 60000,
		[8] = 65000,
		[9] = 70000,
		[10] = 75000
	},
	SkillData2 = 25000,
	CoolDown = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 100
	}
},
[ "GC_ROLLINGCUTTER" ] = {
	Id = 2036,
	Description = "Rolling Cutter",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 1,
		[4] = 1,
		[5] = 2,
		[6] = 2,
		[7] = 2,
		[8] = 2,
		[9] = 2,
		[10] = 2
	},
	AfterCastActDelay = 200,
	SkillData1 = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 5,
		WeaponTypes = {
			WeaponType.Katar
		}
	}
},
[ "GC_CROSSRIPPERSLASHER" ] = {
	Id = 2037,
	Description = "Cross Ripper Slasher",
	MaxLevel = 5,
	Range = {
		[1] = 9,
		[2] = 10,
		[3] = 11,
		[4] = 12,
		[5] = 13,
		[6] = 14,
		[7] = 15,
		[8] = 16,
		[9] = 17,
		[10] = 18
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 24,
			[3] = 28,
			[4] = 32,
			[5] = 36,
			[6] = 40,
			[7] = 44,
			[8] = 48,
			[9] = 52,
			[10] = 56
		},
		WeaponTypes = {
			WeaponType.Katar
		},
		State = PlayerState.PerformingRollingCutter
	}
},
[ "AB_JUDEX" ] = {
	Id = 2038,
	Description = "Judex",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	NumberOfHits: -3,
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 500,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 23,
			[3] = 26,
			[4] = 29,
			[5] = 32,
			[6] = 35,
			[7] = 38,
			[8] = 41,
			[9] = 44,
			[10] = 47
		}
	}
},
[ "AB_ANCILLA" ] = {
	Id = 2039,
	Description = "Ancilla",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 30,
		SPRateCost: -30
	}
},
[ "AB_ADORAMUS" ] = {
	Id = 2040,
	Description = "Adoramus",
	MaxLevel = 10,
	Range = 11,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	NumberOfHits: -10,
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 6000,
		[2] = 7000,
		[3] = 8000,
		[4] = 9000,
		[5] = 10000,
		[6] = 11000,
		[7] = 12000,
		[8] = 13000,
		[9] = 14000,
		[10] = 15000
	},
	SkillData2 = {
		[1] = 15000,
		[2] = 20000,
		[3] = 25000,
		[4] = 30000,
		[5] = 35000,
		[6] = 40000,
		[7] = 45000,
		[8] = 50000,
		[9] = 55000,
		[10] = 60000
	},
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 24,
			[3] = 28,
			[4] = 32,
			[5] = 36,
			[6] = 40,
			[7] = 44,
			[8] = 48,
			[9] = 52,
			[10] = 56
		},
		Items = {
			Item[ "Blue_Gemstone" ] = 1
		}
	}
},
[ "AB_CLEMENTIA" ] = {
	Id = 2041,
	Description = "Crementia",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 3,
		[2] = 7,
		[3] = 15,
		[4] = 15,
		[5] = 15,
		[6] = 15,
		[7] = 15,
		[8] = 15,
		[9] = 15,
		[10] = 15
	},
	InterruptCast = true,
	CastTime = 3000,
	SkillData1 = {
		[1] = 120000,
		[2] = 180000,
		[3] = 240000,
		[4] = 300000,
		[5] = 360000,
		[6] = 420000,
		[7] = 480000,
		[8] = 540000,
		[9] = 600000,
		[10] = 660000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 280,
			[2] = 320,
			[3] = 360,
			[4] = 400,
			[5] = 440,
			[6] = 480,
			[7] = 520,
			[8] = 560,
			[9] = 600,
			[10] = 640
		}
	}
},
[ "AB_CANTO" ] = {
	Id = 2042,
	Description = "Canto Candidus",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 3,
		[2] = 7,
		[3] = 15,
		[4] = 15,
		[5] = 15,
		[6] = 15,
		[7] = 15,
		[8] = 15,
		[9] = 15,
		[10] = 15
	},
	InterruptCast = true,
	CastTime = 3000,
	SkillData1 = {
		[1] = 120000,
		[2] = 180000,
		[3] = 240000,
		[4] = 300000,
		[5] = 360000,
		[6] = 420000,
		[7] = 480000,
		[8] = 540000,
		[9] = 600000,
		[10] = 660000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 200,
			[2] = 220,
			[3] = 240,
			[4] = 260,
			[5] = 280,
			[6] = 300,
			[7] = 320,
			[8] = 340,
			[9] = 360,
			[10] = 380
		}
	}
},
[ "AB_CHEAL" ] = {
	Id = 2043,
	Description = "Coluceo Heal",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 3,
		[2] = 7,
		[3] = 15,
		[4] = 15,
		[5] = 15,
		[6] = 15,
		[7] = 15,
		[8] = 15,
		[9] = 15,
		[10] = 15
	},
	InterruptCast = true,
	CastTime = 3000,
	CoolDown = 2000,
	FixedCastTime = {
		[1] = 1000,
		[2] = 500,
		[3] = -1,
		[4] = -1,
		[5] = -1,
		[6] = -1,
		[7] = -1,
		[8] = -1,
		[9] = -1,
		[10] = -1
	},
	Requirements = {
		SPCost = {
			[1] = 200,
			[2] = 220,
			[3] = 240,
			[4] = 260,
			[5] = 280,
			[6] = 300,
			[7] = 320,
			[8] = 340,
			[9] = 360,
			[10] = 380
		}
	}
},
[ "AB_EPICLESIS" ] = {
	Id = 2044,
	Description = "Epiclesis",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 1,
	CastTime = {
		[1] = 2000,
		[2] = 2500,
		[3] = 3000,
		[4] = 3500,
		[5] = 4000,
		[6] = 4500,
		[7] = 5000,
		[8] = 5500,
		[9] = 6000,
		[10] = 6500
	},
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 18000,
		[2] = 21000,
		[3] = 24000,
		[4] = 27000,
		[5] = 30000,
		[6] = 33000,
		[7] = 36000,
		[8] = 39000,
		[9] = 42000,
		[10] = 45000
	},
	CoolDown = 60000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 300,
		Items = {
			Item[ "Ansila" ] = 1,
			Item[ "Holy_Water" ] = 1
		}
	},
	Placement = {
		Id = 0xca,
		Range = 2,
		Interval = 1000,
		Target = "All",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "AB_PRAEFATIO" ] = {
	Id = 2045,
	Description = "Praefatio",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 15,
	InterruptCast = true,
	CastTime = 2000,
	SkillData1 = 120000,
	CoolDown = {
		[1] = 13000,
		[2] = 16000,
		[3] = 19000,
		[4] = 22000,
		[5] = 25000,
		[6] = 28000,
		[7] = 31000,
		[8] = 34000,
		[9] = 37000,
		[10] = 40000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 90,
			[2] = 100,
			[3] = 110,
			[4] = 120,
			[5] = 130,
			[6] = 140,
			[7] = 150,
			[8] = 160,
			[9] = 170,
			[10] = 180
		}
	}
},
[ "AB_ORATIO" ] = {
	Id = 2046,
	Description = "Oratio",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 15,
	InterruptCast = true,
	CastTime = 4000,
	SkillData1 = 30000,
	CoolDown = 2000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 35,
			[2] = 38,
			[3] = 41,
			[4] = 44,
			[5] = 47,
			[6] = 50,
			[7] = 53,
			[8] = 56,
			[9] = 59,
			[10] = 62
		}
	}
},
[ "AB_LAUDAAGNUS" ] = {
	Id = 2047,
	Description = "Lauda Agnus",
	MaxLevel = 4,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 15,
	InterruptCast = true,
	CastTime = 1000,
	SkillData1 = 60000,
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 50,
			[2] = 60,
			[3] = 70,
			[4] = 80,
			[5] = 90,
			[6] = 100,
			[7] = 110,
			[8] = 120,
			[9] = 130,
			[10] = 140
		}
	}
},
[ "AB_LAUDARAMUS" ] = {
	Id = 2048,
	Description = "Lauda Ramus",
	MaxLevel = 4,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 15,
	InterruptCast = true,
	CastTime = 1000,
	SkillData1 = 60000,
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 50,
			[2] = 60,
			[3] = 70,
			[4] = 80,
			[5] = 90,
			[6] = 100,
			[7] = 110,
			[8] = 120,
			[9] = 130,
			[10] = 140
		}
	}
},
[ "AB_EUCHARISTICA" ] = {
	Id = 2049,
	Description = "Eucharistica",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "AB_RENOVATIO" ] = {
	Id = 2050,
	Description = "Renovatio",
	MaxLevel = 1,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 3000,
	SkillData1 = 90000,
	CoolDown = 1000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 70
	}
},
[ "AB_HIGHNESSHEAL" ] = {
	Id = 2051,
	Description = "Highness Heal",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.Ignore_Soft_Def
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 100,
			[3] = 130,
			[4] = 160,
			[5] = 190,
			[6] = 220,
			[7] = 250,
			[8] = 280,
			[9] = 310,
			[10] = 340
		}
	}
},
[ "AB_CLEARANCE" ] = {
	Id = 2052,
	Description = "Clearance",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 4000,
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 54,
			[2] = 60,
			[3] = 66,
			[4] = 72,
			[5] = 78,
			[6] = 84,
			[7] = 90,
			[8] = 96,
			[9] = 102,
			[10] = 108
		}
	}
},
[ "AB_EXPIATIO" ] = {
	Id = 2053,
	Description = "Expiatio",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	SkillData1 = {
		[1] = 150000,
		[2] = 180000,
		[3] = 210000,
		[4] = 240000,
		[5] = 270000,
		[6] = 300000,
		[7] = 330000,
		[8] = 360000,
		[9] = 390000,
		[10] = 420000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 35,
			[2] = 40,
			[3] = 45,
			[4] = 50,
			[5] = 55,
			[6] = 60,
			[7] = 65,
			[8] = 70,
			[9] = 75,
			[10] = 80
		}
	}
},
[ "AB_DUPLELIGHT" ] = {
	Id = 2054,
	Description = "Duple Light",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 90000,
		[2] = 120000,
		[3] = 150000,
		[4] = 180000,
		[5] = 210000,
		[6] = 240000,
		[7] = 270000,
		[8] = 300000,
		[9] = 330000,
		[10] = 360000
	},
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 55,
			[2] = 60,
			[3] = 65,
			[4] = 70,
			[5] = 75,
			[6] = 80,
			[7] = 85,
			[8] = 90,
			[9] = 95,
			[10] = 100
		}
	}
},
[ "AB_DUPLELIGHT_MELEE" ] = {
	Id = 2055,
	Description = "Duple Light Melee",
	MaxLevel = 10,
	Range = -1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = 1
	}
},
[ "AB_DUPLELIGHT_MAGIC" ] = {
	Id = 2056,
	Description = "Duple Light Magic",
	MaxLevel = 10,
	Range = -1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Requirements = {
		SPCost = 1
	}
},
[ "AB_SILENTIUM" ] = {
	Id = 2057,
	Description = "Silentium",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 4,
		[2] = 5,
		[3] = 6,
		[4] = 7,
		[5] = 8,
		[6] = 9,
		[7] = 10,
		[8] = 11,
		[9] = 12,
		[10] = 13
	},
	InterruptCast = true,
	CastTime = 4000,
	SkillData1 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	CoolDown = 15000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 64,
			[2] = 68,
			[3] = 72,
			[4] = 76,
			[5] = 80,
			[6] = 84,
			[7] = 88,
			[8] = 92,
			[9] = 96,
			[10] = 100
		}
	}
},
[ "WL_WHITEIMPRISON" ] = {
	Id = 2201,
	Description = "White Imprison",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	InterruptCast = true,
	SkillData1 = {
		[1] = 6000,
		[2] = 8000,
		[3] = 10000,
		[4] = 12000,
		[5] = 14000,
		[6] = 16000,
		[7] = 18000,
		[8] = 20000,
		[9] = 22000,
		[10] = 24000
	},
	SkillData2 = 15000,
	CoolDown = 4000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 50,
			[2] = 55,
			[3] = 60,
			[4] = 65,
			[5] = 70,
			[6] = 75,
			[7] = 80,
			[8] = 85,
			[9] = 90,
			[10] = 95
		}
	}
},
[ "WL_SOULEXPANSION" ] = {
	Id = 2202,
	Description = "Soul Expansion",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Ghost,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 1,
		[4] = 2,
		[5] = 2,
		[6] = 2,
		[7] = 2,
		[8] = 2,
		[9] = 2,
		[10] = 2
	},
	NumberOfHits: -2,
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 35,
			[3] = 40,
			[4] = 45,
			[5] = 50,
			[6] = 55,
			[7] = 60,
			[8] = 65,
			[9] = 70,
			[10] = 75
		}
	}
},
[ "WL_FROSTMISTY" ] = {
	Id = 2203,
	Description = "Frosty Misty",
	MaxLevel = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 13,
	NumberOfHits = {
		[1] = -3,
		[2] = -4,
		[3] = -5,
		[4] = -6,
		[5] = -7,
		[6] = -8,
		[7] = -9,
		[8] = -10,
		[9] = -11,
		[10] = -12
	},
	InterruptCast = true,
	CastTime = {
		[1] = 2000,
		[2] = 2500,
		[3] = 3000,
		[4] = 3500,
		[5] = 4000,
		[6] = 4500,
		[7] = 5000,
		[8] = 5500,
		[9] = 6000,
		[10] = 6500
	},
	AfterCastActDelay = 1000,
	SkillData1 = 40000,
	CoolDown = 4000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 48,
			[3] = 56,
			[4] = 64,
			[5] = 72,
			[6] = 80,
			[7] = 88,
			[8] = 96,
			[9] = 104,
			[10] = 112
		}
	}
},
[ "WL_JACKFROST" ] = {
	Id = 2204,
	Description = "Jack Frost",
	MaxLevel = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 13,
	NumberOfHits: -5,
	InterruptCast = true,
	CastTime = {
		[1] = 2000,
		[2] = 2500,
		[3] = 3000,
		[4] = 3500,
		[5] = 4000,
		[6] = 4500,
		[7] = 5000,
		[8] = 5500,
		[9] = 6000,
		[10] = 6500
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 50,
			[2] = 60,
			[3] = 70,
			[4] = 80,
			[5] = 90,
			[6] = 100,
			[7] = 110,
			[8] = 120,
			[9] = 130,
			[10] = 140
		}
	}
},
[ "WL_MARSHOFABYSS" ] = {
	Id = 2205,
	Description = "Marsh of Abyss",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 30000,
	CoolDown = {
		[1] = 2500,
		[2] = 3000,
		[3] = 3500,
		[4] = 4000,
		[5] = 4500,
		[6] = 5000,
		[7] = 5500,
		[8] = 6000,
		[9] = 6500,
		[10] = 7000
	},
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 42,
			[3] = 44,
			[4] = 46,
			[5] = 48,
			[6] = 50,
			[7] = 52,
			[8] = 54,
			[9] = 56,
			[10] = 58
		}
	}
},
[ "WL_RECOGNIZEDSPELL" ] = {
	Id = 2206,
	Description = "Recognized Spell",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 60000,
		[2] = 90000,
		[3] = 120000,
		[4] = 150000,
		[5] = 180000,
		[6] = 210000,
		[7] = 240000,
		[8] = 270000,
		[9] = 300000,
		[10] = 330000
	},
	CoolDown = {
		[1] = 50000,
		[2] = 80000,
		[3] = 110000,
		[4] = 140000,
		[5] = 170000,
		[6] = 200000,
		[7] = 230000,
		[8] = 260000,
		[9] = 290000,
		[10] = 320000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 100,
			[2] = 120,
			[3] = 140,
			[4] = 160,
			[5] = 180,
			[6] = 200,
			[7] = 220,
			[8] = 240,
			[9] = 260,
			[10] = 280
		}
	}
},
[ "WL_SIENNAEXECRATE" ] = {
	Id = 2207,
	Description = "Sienna Execrate",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 2,
		[3] = 2,
		[4] = 3,
		[5] = 3,
		[6] = 4,
		[7] = 4,
		[8] = 5,
		[9] = 5,
		[10] = 6
	},
	NumberOfHits = 0,
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 10000,
		[2] = 12000,
		[3] = 14000,
		[4] = 16000,
		[5] = 18000,
		[6] = 20000,
		[7] = 22000,
		[8] = 24000,
		[9] = 26000,
		[10] = 28000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 32,
			[2] = 34,
			[3] = 36,
			[4] = 38,
			[5] = 40,
			[6] = 42,
			[7] = 44,
			[8] = 46,
			[9] = 48,
			[10] = 50
		},
		Items = {
			Item[ "Red_Gemstone" ] = 2
		}
	}
},
[ "WL_RADIUS" ] = {
	Id = 2208,
	Description = "Radius",
	MaxLevel = 3,
	NumberOfHits = 0
},
[ "WL_STASIS" ] = {
	Id = 2209,
	Description = "Stasis",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 9,
		[2] = 10,
		[3] = 11,
		[4] = 12,
		[5] = 13,
		[6] = 14,
		[7] = 15,
		[8] = 16,
		[9] = 17,
		[10] = 18
	},
	InterruptCast = true,
	CastTime = 3000,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	SkillData2 = 1000,
	CoolDown = {
		[1] = 180000,
		[2] = 190000,
		[3] = 200000,
		[4] = 210000,
		[5] = 220000,
		[6] = 230000,
		[7] = 240000,
		[8] = 250000,
		[9] = 260000,
		[10] = 270000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 50,
			[2] = 60,
			[3] = 70,
			[4] = 80,
			[5] = 90,
			[6] = 100,
			[7] = 110,
			[8] = 120,
			[9] = 130,
			[10] = 140
		}
	}
},
[ "WL_DRAINLIFE" ] = {
	Id = 2210,
	Description = "Drain Life",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	InterruptCast = true,
	CastTime = 4000,
	CoolDown = 2000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 24,
			[3] = 28,
			[4] = 32,
			[5] = 36,
			[6] = 40,
			[7] = 44,
			[8] = 48,
			[9] = 52,
			[10] = 56
		}
	}
},
[ "WL_CRIMSONROCK" ] = {
	Id = 2211,
	Description = "Crimson Rock",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	NumberOfHits: -7,
	InterruptCast = true,
	KnockBackTiles = 3,
	CastTime = 5000,
	AfterCastActDelay = 2000,
	SkillData1 = 5000,
	CoolDown = 5000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 70,
			[3] = 80,
			[4] = 90,
			[5] = 100,
			[6] = 110,
			[7] = 120,
			[8] = 130,
			[9] = 140,
			[10] = 150
		}
	}
},
[ "WL_HELLINFERNO" ] = {
	Id = 2212,
	Description = "Hell Inferno",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	InterruptCast = true,
	CastTime = 3000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 35,
			[2] = 40,
			[3] = 45,
			[4] = 50,
			[5] = 55,
			[6] = 60,
			[7] = 65,
			[8] = 70,
			[9] = 75,
			[10] = 80
		}
	}
},
[ "WL_COMET" ] = {
	Id = 2213,
	Description = "Comet",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	NumberOfHits: -20,
	InterruptCast = true,
	KnockBackTiles = 2,
	CastTime = {
		[1] = 10000,
		[2] = 11000,
		[3] = 12000,
		[4] = 13000,
		[5] = 14000,
		[6] = 15000,
		[7] = 16000,
		[8] = 17000,
		[9] = 18000,
		[10] = 19000
	},
	SkillData1 = 100,
	SkillData2 = 42000,
	CoolDown = 60000,
	FixedCastTime = {
		[1] = 1000,
		[2] = 1500,
		[3] = 2000,
		[4] = 2500,
		[5] = 3000,
		[6] = 3500,
		[7] = 4000,
		[8] = 4500,
		[9] = 5000,
		[10] = 5500
	},
	Requirements = {
		SPCost = {
			[1] = 480,
			[2] = 560,
			[3] = 640,
			[4] = 720,
			[5] = 800,
			[6] = 880,
			[7] = 960,
			[8] = 1040,
			[9] = 1120,
			[10] = 1200
		},
		Items = {
			Item[ "Red_Gemstone" ] = 2
		}
	},
	Placement = {
		Id = 0x86,
		Range = 8,
		Interval = 100,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "WL_CHAINLIGHTNING" ] = {
	Id = 2214,
	Description = "Chain Lightning",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	SplashRange = 3,
	InterruptCast = true,
	CastTime = {
		[1] = 3500,
		[2] = 4000,
		[3] = 4500,
		[4] = 5000,
		[5] = 5500,
		[6] = 6000,
		[7] = 6500,
		[8] = 7000,
		[9] = 7500,
		[10] = 8000
	},
	SkillData1 = 100,
	CoolDown = 3000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 90,
			[3] = 100,
			[4] = 110,
			[5] = 120,
			[6] = 130,
			[7] = 140,
			[8] = 150,
			[9] = 160,
			[10] = 170
		}
	}
},
[ "WL_CHAINLIGHTNING_ATK" ] = {
	Id = 2215,
	Description = "Chain Lightning Attack",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	Requirements = {
		SPCost = 1
	}
},
[ "WL_EARTHSTRAIN" ] = {
	Id = 2216,
	Description = "Earth Strain",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	NumberOfHits = {
		[1] = -6,
		[2] = -7,
		[3] = -8,
		[4] = -9,
		[5] = -10,
		[6] = -11,
		[7] = -12,
		[8] = -13,
		[9] = -14,
		[10] = -15
	},
	InterruptCast = true,
	CastTime = {
		[1] = 2000,
		[2] = 3000,
		[3] = 4000,
		[4] = 5000,
		[5] = 6000,
		[6] = 7000,
		[7] = 8000,
		[8] = 9000,
		[9] = 10000,
		[10] = 11000
	},
	AfterCastActDelay = 1000,
	SkillData1 = 100,
	SkillData2 = {
		[1] = 75000,
		[2] = 90000,
		[3] = 105000,
		[4] = 120000,
		[5] = 135000,
		[6] = 150000,
		[7] = 165000,
		[8] = 180000,
		[9] = 195000,
		[10] = 210000
	},
	CoolDown = 10000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 78,
			[3] = 86,
			[4] = 94,
			[5] = 102,
			[6] = 110,
			[7] = 118,
			[8] = 126,
			[9] = 134,
			[10] = 142
		}
	},
	Placement = {
		Id = 0xcb,
		Layout = -1,
		Interval = 100,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "WL_TETRAVORTEX" ] = {
	Id = 2217,
	Description = "Tetra Vortex",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	InterruptCast = true,
	CastTime = {
		[1] = 5000,
		[2] = 6000,
		[3] = 7000,
		[4] = 8000,
		[5] = 9000,
		[6] = 10000,
		[7] = 11000,
		[8] = 12000,
		[9] = 13000,
		[10] = 14000
	},
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 15000,
		[2] = 120000,
		[3] = 40000,
		[4] = 5000,
		[5] = 5000,
		[6] = 5000,
		[7] = 5000,
		[8] = 5000,
		[9] = 5000,
		[10] = 5000
	},
	CoolDown = 15000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 120,
			[2] = 150,
			[3] = 180,
			[4] = 210,
			[5] = 240,
			[6] = 270,
			[7] = 300,
			[8] = 330,
			[9] = 360,
			[10] = 390
		}
	}
},
[ "WL_TETRAVORTEX_FIRE" ] = {
	Id = 2218,
	Description = "Tetra Vortex Fire",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	Requirements = {
		SPCost = 1
	}
},
[ "WL_TETRAVORTEX_WATER" ] = {
	Id = 2219,
	Description = "Tetra Vortex Water",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	Requirements = {
		SPCost = 1
	}
},
[ "WL_TETRAVORTEX_WIND" ] = {
	Id = 2220,
	Description = "Tetra Vortex Wind",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	Requirements = {
		SPCost = 1
	}
},
[ "WL_TETRAVORTEX_GROUND" ] = {
	Id = 2221,
	Description = "Tetra Vortex Earth",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	Requirements = {
		SPCost = 1
	}
},
[ "WL_SUMMONFB" ] = {
	Id = 2222,
	Description = "Summon Fire Ball",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	SkillData1 = {
		[1] = 120000,
		[2] = 160000,
		[3] = 200000,
		[4] = 240000,
		[5] = 280000,
		[6] = 320000,
		[7] = 360000,
		[8] = 400000,
		[9] = 440000,
		[10] = 480000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 12,
			[3] = 14,
			[4] = 16,
			[5] = 18,
			[6] = 20,
			[7] = 22,
			[8] = 24,
			[9] = 26,
			[10] = 28
		}
	}
},
[ "WL_SUMMONBL" ] = {
	Id = 2223,
	Description = "Summon Lightning Ball",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	SkillData1 = {
		[1] = 120000,
		[2] = 160000,
		[3] = 200000,
		[4] = 240000,
		[5] = 280000,
		[6] = 320000,
		[7] = 360000,
		[8] = 400000,
		[9] = 440000,
		[10] = 480000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 12,
			[3] = 14,
			[4] = 16,
			[5] = 18,
			[6] = 20,
			[7] = 22,
			[8] = 24,
			[9] = 26,
			[10] = 28
		}
	}
},
[ "WL_SUMMONWB" ] = {
	Id = 2224,
	Description = "Summon Water Ball",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	SkillData1 = {
		[1] = 120000,
		[2] = 160000,
		[3] = 200000,
		[4] = 240000,
		[5] = 280000,
		[6] = 320000,
		[7] = 360000,
		[8] = 400000,
		[9] = 440000,
		[10] = 480000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 12,
			[3] = 14,
			[4] = 16,
			[5] = 18,
			[6] = 20,
			[7] = 22,
			[8] = 24,
			[9] = 26,
			[10] = 28
		}
	}
},
[ "WL_SUMMON_ATK_FIRE" ] = {
	Id = 2225,
	Description = "Summon Attack Fire",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	SkillInstances = 1,
	Requirements = {
		SPCost = 1
	}
},
[ "WL_SUMMON_ATK_WIND" ] = {
	Id = 2226,
	Description = "Summon Attack Wind",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	SkillInstances = 1,
	Requirements = {
		SPCost = 1
	}
},
[ "WL_SUMMON_ATK_WATER" ] = {
	Id = 2227,
	Description = "Summon Attack Water",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	SkillInstances = 1,
	Requirements = {
		SPCost = 1
	}
},
[ "WL_SUMMON_ATK_GROUND" ] = {
	Id = 2228,
	Description = "Summon Attack Earth",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	SkillInstances = 1,
	Requirements = {
		SPCost = 1
	}
},
[ "WL_SUMMONSTONE" ] = {
	Id = 2229,
	Description = "Summon Stone",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	SkillData1 = {
		[1] = 120000,
		[2] = 160000,
		[3] = 200000,
		[4] = 240000,
		[5] = 280000,
		[6] = 320000,
		[7] = 360000,
		[8] = 400000,
		[9] = 440000,
		[10] = 480000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 12,
			[3] = 14,
			[4] = 16,
			[5] = 18,
			[6] = 20,
			[7] = 22,
			[8] = 24,
			[9] = 26,
			[10] = 28
		}
	}
},
[ "WL_RELEASE" ] = {
	Id = 2230,
	Description = "Release",
	MaxLevel = 2,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	InterruptCast = true,
	Requirements = {
		SPCost = {
			[1] = 3,
			[2] = 20,
			[3] = 37,
			[4] = 54,
			[5] = 71,
			[6] = 88,
			[7] = 105,
			[8] = 122,
			[9] = 139,
			[10] = 156
		}
	}
},
[ "WL_READING_SB" ] = {
	Id = 2231,
	Description = "Reading Spellbook",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 5000,
	AfterCastActDelay = 500,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 40
	}
},
[ "WL_FREEZE_SP" ] = {
	Id = 2232,
	Description = "Freeze Spell",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "RA_ARROWSTORM" ] = {
	Id = 2233,
	Description = "Arrow Storm",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 3,
		[2] = 3,
		[3] = 3,
		[4] = 3,
		[5] = 3,
		[6] = 4,
		[7] = 4,
		[8] = 4,
		[9] = 4,
		[10] = 5
	},
	NumberOfHits: -3,
	InterruptCast = true,
	CastTime = {
		[1] = 2000,
		[2] = 2200,
		[3] = 2400,
		[4] = 2600,
		[5] = 2800,
		[6] = 3000,
		[7] = 3200,
		[8] = 3400,
		[9] = 3600,
		[10] = 3800
	},
	CoolDown = {
		[1] = 5000,
		[2] = 4800,
		[3] = 4600,
		[4] = 4400,
		[5] = 4200,
		[6] = 4000,
		[7] = 3800,
		[8] = 3600,
		[9] = 3400,
		[10] = 3200
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 32,
			[3] = 34,
			[4] = 36,
			[5] = 38,
			[6] = 40,
			[7] = 42,
			[8] = 44,
			[9] = 46,
			[10] = 48
		},
		WeaponTypes = {
			WeaponType.Bow
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 10
	}
},
[ "RA_FEARBREEZE" ] = {
	Id = 2234,
	Description = "Fear Breeze",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 60000,
		[2] = 90000,
		[3] = 120000,
		[4] = 150000,
		[5] = 180000,
		[6] = 210000,
		[7] = 240000,
		[8] = 270000,
		[9] = 300000,
		[10] = 330000
	},
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 55,
			[2] = 60,
			[3] = 65,
			[4] = 70,
			[5] = 75,
			[6] = 80,
			[7] = 85,
			[8] = 90,
			[9] = 95,
			[10] = 100
		},
		WeaponTypes = {
			WeaponType.Bow
		}
	}
},
[ "RA_RANGERMAIN" ] = {
	Id = 2235,
	Description = "Ranger Main",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "RA_AIMEDBOLT" ] = {
	Id = 2236,
	Description = "Aimed Bolt",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	InterruptCast = true,
	CastTime = 4000,
	AfterCastActDelay = 1000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 32,
			[3] = 34,
			[4] = 36,
			[5] = 38,
			[6] = 40,
			[7] = 42,
			[8] = 44,
			[9] = 46,
			[10] = 48
		},
		WeaponTypes = {
			WeaponType.Bow
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	}
},
[ "RA_DETONATOR" ] = {
	Id = 2237,
	Description = "Detonator",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	SkillData1 = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 15
	}
},
[ "RA_ELECTRICSHOCKER" ] = {
	Id = 2238,
	Description = "Electric Shocker",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	SkillInstances = 3,
	SkillData1 = 15000,
	SkillData2 = {
		[1] = 20000,
		[2] = 22000,
		[3] = 24000,
		[4] = 26000,
		[5] = 28000,
		[6] = 30000,
		[7] = 32000,
		[8] = 34000,
		[9] = 36000,
		[10] = 38000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = 35,
		Items = {
			Item[ "Special_Alloy_Trap" ] = 1
		}
	},
	Placement = {
		Id = 0xd8,
		Range = 2,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "RA_CLUSTERBOMB" ] = {
	Id = 2239,
	Description = "Cluster Bomb",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 3,
	SkillInstances = 3,
	SkillData1 = 15000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 20,
		Items = {
			Item[ "Special_Alloy_Trap" ] = 1
		}
	},
	Placement = {
		Id = 0xd9,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "RA_WUGMASTERY" ] = {
	Id = 2240,
	Description = "Warg Mastery",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AfterCastActDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 5,
		Items = {
			Item[ "Wolfs_Flute" ] = 0
		}
	}
},
[ "RA_WUGRIDER" ] = {
	Id = 2241,
	Description = "Warg Rider",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AfterCastActDelay = 500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 2
	}
},
[ "RA_WUGDASH" ] = {
	Id = 2242,
	Description = "Warg Dash",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	NumberOfHits = 0,
	Requirements = {
		SPCost = 4,
		State = PlayerState.Moveable
	}
},
[ "RA_WUGSTRIKE" ] = {
	Id = 2243,
	Description = "Warg Strike",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 22,
			[3] = 24,
			[4] = 26,
			[5] = 28,
			[6] = 30,
			[7] = 32,
			[8] = 34,
			[9] = 36,
			[10] = 38
		}
	}
},
[ "RA_WUGBITE" ] = {
	Id = 2244,
	Description = "Warg Bite",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 1000,
		[2] = 2000,
		[3] = 3000,
		[4] = 4000,
		[5] = 5000,
		[6] = 6000,
		[7] = 7000,
		[8] = 8000,
		[9] = 9000,
		[10] = 10000
	},
	CoolDown = {
		[1] = 4000,
		[2] = 6000,
		[3] = 8000,
		[4] = 10000,
		[5] = 12000,
		[6] = 14000,
		[7] = 16000,
		[8] = 18000,
		[9] = 20000,
		[10] = 22000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 42,
			[3] = 44,
			[4] = 46,
			[5] = 48,
			[6] = 50,
			[7] = 52,
			[8] = 54,
			[9] = 56,
			[10] = 58
		},
		State = PlayerState.Has_Warg
	}
},
[ "RA_TOOTHOFWUG" ] = {
	Id = 2245,
	Description = "Tooth of Warg",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "RA_SENSITIVEKEEN" ] = {
	Id = 2246,
	Description = "Sensitive Keen",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	AfterCastActDelay = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 12,
		State = PlayerState.Has_Warg
	}
},
[ "RA_CAMOUFLAGE" ] = {
	Id = 2247,
	Description = "Camouflage",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 40
	}
},
[ "RA_RESEARCHTRAP" ] = {
	Id = 2248,
	Description = "Research Trap",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "RA_MAGENTATRAP" ] = {
	Id = 2249,
	Description = "Magenta Trap",
	MaxLevel = 1,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill,
		SkillBehavior.IgnoreTargetPlayers
	},
	AttackType = AttackType.Misc,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 2,
	SkillInstances = 1,
	AfterCastActDelay = 2000,
	SkillData1 = 15000,
	SkillData2 = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Special_Alloy_Trap" ] = 1,
			Item[ "Boody_Red" ] = 1
		}
	},
	Placement = {
		Id = 0xd2,
		Range = 2,
		Interval = 1000,
		Target = "Enemy"
	}
},
[ "RA_COBALTTRAP" ] = {
	Id = 2250,
	Description = "Cobalt Trap",
	MaxLevel = 1,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill,
		SkillBehavior.IgnoreTargetPlayers
	},
	AttackType = AttackType.Misc,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 2,
	SkillInstances = 1,
	AfterCastActDelay = 2000,
	SkillData1 = 15000,
	SkillData2 = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Special_Alloy_Trap" ] = 1,
			Item[ "Crystal_Blue" ] = 1
		}
	},
	Placement = {
		Id = 0xd3,
		Range = 2,
		Interval = 1000,
		Target = "Enemy",
	}
},
[ "RA_MAIZETRAP" ] = {
	Id = 2251,
	Description = "Maize Trap",
	MaxLevel = 1,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill,
		SkillBehavior.IgnoreTargetPlayers
	},
	AttackType = AttackType.Misc,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 2,
	SkillInstances = 1,
	AfterCastActDelay = 2000,
	SkillData1 = 15000,
	SkillData2 = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Special_Alloy_Trap" ] = 1,
			Item[ "Yellow_Live" ] = 1
		}
	},
	Placement = {
		Id = 0xd4,
		Range = 2,
		Interval = 1000,
		Target = "Enemy",
	}
},
[ "RA_VERDURETRAP" ] = {
	Id = 2252,
	Description = "Verdure Trap",
	MaxLevel = 1,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill,
		SkillBehavior.IgnoreTargetPlayers
	},
	AttackType = AttackType.Misc,
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 2,
	SkillInstances = 1,
	AfterCastActDelay = 2000,
	SkillData1 = 15000,
	SkillData2 = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Special_Alloy_Trap" ] = 1,
			Item[ "Wind_Of_Verdure" ] = 1
		}
	},
	Placement = {
		Id = 0xd5,
		Range = 2,
		Interval = 1000,
		Target = "Enemy"
	}
},
[ "RA_FIRINGTRAP" ] = {
	Id = 2253,
	Description = "Firing Trap",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Misc,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 2,
	SkillInstances = 2,
	SkillData1 = 15000,
	SkillData2 = 40000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Special_Alloy_Trap" ] = 1
		}
	},
	Placement = {
		Id = 0xd6,
		Range = 1,
		Interval = 1000,
		Target = "Enemy"
	}
},
[ "RA_ICEBOUNDTRAP" ] = {
	Id = 2254,
	Description = "Icebound Trap",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Misc,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 2,
	SkillInstances = 2,
	SkillData1 = 15000,
	SkillData2 = 20000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		Items = {
			Item[ "Special_Alloy_Trap" ] = 1
		}
	},
	Placement = {
		Id = 0xd7,
		Range = 1,
		Interval = 1000,
		Target = "Enemy"
	}
},
[ "NC_MADOLICENCE" ] = {
	Id = 2255,
	Description = "Mado License",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "NC_BOOSTKNUCKLE" ] = {
	Id = 2256,
	Description = "Boost Knuckle",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	CastTime = {
		[1] = 200,
		[2] = 400,
		[3] = 600,
		[4] = 800,
		[5] = 1000,
		[6] = 1200,
		[7] = 1400,
		[8] = 1600,
		[9] = 1800,
		[10] = 2000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 3,
			[2] = 6,
			[3] = 9,
			[4] = 12,
			[5] = 15,
			[6] = 18,
			[7] = 21,
			[8] = 24,
			[9] = 27,
			[10] = 30
		},
		State = "MadoGear"
	}
},
[ "NC_PILEBUNKER" ] = {
	Id = 2257,
	Description = "Pile Bunker",
	MaxLevel = 3,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = 2000,
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 50,
		State = "MadoGear",
		Items = {
			Item[ "Pilebuncker" ] = 0,
			Item[ "Pilebuncker_S" ] = 0,
			Item[ "Pilebuncker_P" ] = 0,
			Item[ "Pilebuncker_T" ] = 0
		}
	}
},
[ "NC_VULCANARM" ] = {
	Id = 2258,
	Description = "Vulcan Arm",
	MaxLevel = 3,
	Range = 13,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	AfterCastActDelay = {
		[1] = 300,
		[2] = 200,
		[3] = 100,
		[4] = 1,
		[5] = 1,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 2,
			[2] = 4,
			[3] = 6,
			[4] = 8,
			[5] = 10,
			[6] = 12,
			[7] = 14,
			[8] = 16,
			[9] = 18,
			[10] = 20
		},
		State = "MadoGear",
		Items = {
			Item[ "Vulcan_Bullet" ] = 1
		}
	}
},
[ "NC_FLAMELAUNCHER" ] = {
	Id = 2259,
	Description = "Flame Launcher",
	MaxLevel = 3,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire,
	SplashRange = 2,
	SkillInstances = 5,
	CastTime = {
		[1] = 500,
		[2] = 1000,
		[3] = 1500,
		[4] = 2000,
		[5] = 2500,
		[6] = 3000,
		[7] = 3500,
		[8] = 4000,
		[9] = 4500,
		[10] = 5000
	},
	AfterCastActDelay = {
		[1] = 1500,
		[2] = 1000,
		[3] = 500,
		[4] = 1,
		[5] = 1,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData1 = {
		[1] = 7000,
		[2] = 14000,
		[3] = 21000,
		[4] = 28000,
		[5] = 35000,
		[6] = 42000,
		[7] = 49000,
		[8] = 56000,
		[9] = 63000,
		[10] = 70000
	},
	FixedCastTime = 500,
	Requirements = {
		SPCost = 20,
		State = "MadoGear",
		Items = {
			Item[ "Flame_Thrower" ] = 0,
			Item[ "Magic_Gear_Fuel" ] = 1
		}
	}
},
[ "NC_COLDSLOWER" ] = {
	Id = 2260,
	Description = "Cold Slower",
	MaxLevel = 3,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 3,
		[3] = 4,
		[4] = 5,
		[5] = 6,
		[6] = 7,
		[7] = 8,
		[8] = 9,
		[9] = 10,
		[10] = 11
	},
	CastTime = 1000,
	AfterCastActDelay = {
		[1] = 1000,
		[2] = 2000,
		[3] = 3000,
		[4] = 4000,
		[5] = 5000,
		[6] = 6000,
		[7] = 7000,
		[8] = 8000,
		[9] = 9000,
		[10] = 10000
	},
	SkillData1 = {
		[1] = 7000,
		[2] = 14000,
		[3] = 21000,
		[4] = 28000,
		[5] = 35000,
		[6] = 42000,
		[7] = 49000,
		[8] = 56000,
		[9] = 63000,
		[10] = 70000
	},
	SkillData2 = 40000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 20,
		State = "MadoGear",
		Items = {
			Item[ "Magic_Gear_Fuel" ] = 1,
			Item[ "Liquid_Condensed_Bullet" ] = 1
		}
	}
},
[ "NC_ARMSCANNON" ] = {
	Id = 2261,
	Description = "Arm Cannon",
	MaxLevel = 3,
	Range = {
		[1] = 9,
		[2] = 11,
		[3] = 13,
		[4] = 15,
		[5] = 17,
		[6] = 19,
		[7] = 21,
		[8] = 23,
		[9] = 25,
		[10] = 27
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = {
		[1] = 3,
		[2] = 2,
		[3] = 1,
		[4] = 1,
		[5] = 1,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	CastTime = {
		[1] = 1400,
		[2] = 1600,
		[3] = 1800,
		[4] = 2000,
		[5] = 2200,
		[6] = 2400,
		[7] = 2600,
		[8] = 2800,
		[9] = 3000,
		[10] = 3200
	},
	AfterCastActDelay = {
		[1] = 500,
		[2] = 1000,
		[3] = 2000,
		[4] = 2000,
		[5] = 2000,
		[6] = 2000,
		[7] = 2000,
		[8] = 2000,
		[9] = 2000,
		[10] = 2000
	},
	FixedCastTime = {
		[1] = 600,
		[2] = 400,
		[3] = 200,
		[4] = 1,
		[5] = 1,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		},
		AmmoTypes = {
			AmmoType.CannonBall
		},
		AmmoAmount = 1,
		State = "MadoGear",
		Items = {
			Item[ "Magic_Gear_Fuel" ] = 1
		}
	}
},
[ "NC_ACCELERATION" ] = {
	Id = 2262,
	Description = "Acceleration",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 60000,
		[2] = 90000,
		[3] = 120000,
		[4] = 150000,
		[5] = 180000,
		[6] = 210000,
		[7] = 240000,
		[8] = 270000,
		[9] = 300000,
		[10] = 330000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 40,
			[3] = 60,
			[4] = 80,
			[5] = 100,
			[6] = 120,
			[7] = 140,
			[8] = 160,
			[9] = 180,
			[10] = 200
		},
		State = "MadoGear",
		Items = {
			Item[ "Accelerator" ] = 0,
			Item[ "Magic_Gear_Fuel" ] = 1
		}
	}
},
[ "NC_HOVERING" ] = {
	Id = 2263,
	Description = "Hovering",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 90000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 25,
		State = "MadoGear",
		Items = {
			Item[ "Hovering_Booster" ] = 0,
			Item[ "Magic_Gear_Fuel" ] = 1
		}
	}
},
{
	Id = 2264,
	Name = "NC_F_SIDESLIDE",
	Description = "Front-Side Slide",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	KnockBackTiles = 7,
	AfterCastActDelay = 500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 5,
		State = "MadoGear",
		Items = {
			Item[ "Magic_Gear_Fuel" ] = 1
		}
	}
},
{
	Id = 2265,
	Name = "NC_B_SIDESLIDE",
	Description = "Back-Side Slide",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	KnockBackTiles = 7,
	AfterCastActDelay = 500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 5,
		State = "MadoGear",
		Items = {
			Item[ "Magic_Gear_Fuel" ] = 1
		}
	}
},
[ "NC_MAINFRAME" ] = {
	Id = 2266,
	Description = "Mainframe Restructure",
	MaxLevel = 4,
	NumberOfHits = 0
},
[ "NC_SELFDESTRUCTION" ] = {
	Id = 2267,
	Description = "Self Destruction",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Misc,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee,
		IgnoreDefCards = true
	},
	SplashRange = {
		[1] = 2,
		[2] = 3,
		[3] = 4,
		[4] = 5,
		[5] = 6,
		[6] = 7,
		[7] = 8,
		[8] = 9,
		[9] = 10,
		[10] = 11
	},
	KnockBackTiles = 5,
	CastTime = {
		[1] = 2000,
		[2] = 1500,
		[3] = 1000,
		[4] = 500,
		[5] = 1,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	CoolDown = 300000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = 1,
		State = "MadoGear",
		Items = {
			Item[ "Suicidal_Device" ] = 0,
			Item[ "Magic_Gear_Fuel" ] = 3
		}
	}
},
[ "NC_SHAPESHIFT" ] = {
	Id = 2268,
	Description = "Shape Shift",
	MaxLevel = 4,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 2000,
	SkillData1 = 300000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = 100,
		State = "MadoGear",
		Items = {
			Item[ "Scarlet_Pts" ] = 1,
			Item[ "Lime_Green_Pts" ] = 1,
			Item[ "Yellow_Wish_Pts" ] = 1,
			Item[ "Indigo_Pts" ] = 1,
			Item[ "Magic_Gear_Fuel" ] = 2,
			Item[ "Shape_Shifter" ] = 0
		}
	}
},
[ "NC_EMERGENCYCOOL" ] = {
	Id = 2269,
	Description = "Emergency Cool",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 500,
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 20,
		State = "MadoGear",
		Items = {
			Item[ "Cooling_Device" ] = 0,
			Item[ "Magic_Gear_Fuel" ] = 1
		}
	}
},
[ "NC_INFRAREDSCAN" ] = {
	Id = 2270,
	Description = "Infrared Scan",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 7,
	InterruptCast = true,
	AfterCastActDelay = 500,
	SkillData1 = 3000,
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 45,
		State = "MadoGear"
	}
},
[ "NC_ANALYZE" ] = {
	Id = 2271,
	Description = "Analyze",
	MaxLevel = 3,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 20000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = 30,
		State = "MadoGear",
		Items = {
			Item[ "Magic_Gear_Fuel" ] = 1
		}
	}
},
[ "NC_MAGNETICFIELD" ] = {
	Id = 2272,
	Description = "Magnetic Field",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	InterruptCast = true,
	SkillData1 = {
		[1] = 4000,
		[2] = 6000,
		[3] = 8000,
		[4] = 10000,
		[5] = 12000,
		[6] = 14000,
		[7] = 16000,
		[8] = 18000,
		[9] = 20000,
		[10] = 22000
	},
	CoolDown = {
		[1] = 20000,
		[2] = 15000,
		[3] = 10000,
		[4] = 5000,
		[5] = 1,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 70,
			[3] = 80,
			[4] = 90,
			[5] = 100,
			[6] = 110,
			[7] = 120,
			[8] = 130,
			[9] = 140,
			[10] = 150
		},
		State = "MadoGear",
		Items = {
			Item[ "Mag_Field_Generator" ] = 0,
			Item[ "Magic_Gear_Fuel" ] = 2
		}
	}
},
[ "NC_NEUTRALBARRIER" ] = {
	Id = 2273,
	Description = "Neutral Barrier",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	CoolDown = 90000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 90,
			[3] = 100,
			[4] = 110,
			[5] = 120,
			[6] = 130,
			[7] = 140,
			[8] = 150,
			[9] = 160,
			[10] = 170
		},
		State = "MadoGear",
		Items = {
			Item[ "Barrier_Builder" ] = 0,
			Item[ "Magic_Gear_Fuel" ] = 1
		}
	},
	Placement = {
		Id = 0xe2,
		Layout = 2,
		Interval = 500,
		Target = "Friend"
	}
},
[ "NC_STEALTHFIELD" ] = {
	Id = 2274,
	Description = "Stealth Field",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 15000,
		[2] = 20000,
		[3] = 25000,
		[4] = 30000,
		[5] = 35000,
		[6] = 40000,
		[7] = 45000,
		[8] = 50000,
		[9] = 55000,
		[10] = 60000
	},
	CoolDown = {
		[1] = 20000,
		[2] = 15000,
		[3] = 10000,
		[4] = 5000,
		[5] = 1,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 100,
			[3] = 120,
			[4] = 140,
			[5] = 160,
			[6] = 180,
			[7] = 200,
			[8] = 220,
			[9] = 240,
			[10] = 260
		},
		State = "MadoGear",
		Items = {
			Item[ "Camouflage_Generator" ] = 0,
			Item[ "Magic_Gear_Fuel" ] = 2
		}
	},
	Placement = {
		Id = 0xe3,
		Layout = 2,
		Interval = 500,
		Target = "All"
	}
},
[ "NC_REPAIR" ] = {
	Id = 2275,
	Description = "Repair",
	MaxLevel = 5,
	Range = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 200,
		[2] = 300,
		[3] = 400,
		[4] = 500,
		[5] = 600,
		[6] = 700,
		[7] = 800,
		[8] = 900,
		[9] = 1000,
		[10] = 1100
	},
	AfterCastActDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 25,
			[2] = 30,
			[3] = 35,
			[4] = 40,
			[5] = 45,
			[6] = 50,
			[7] = 55,
			[8] = 60,
			[9] = 65,
			[10] = 70
		},
		State = "MadoGear",
		Items = {
			Item[ "Repair_Kit" ] = 0
		}
	}
},
[ "NC_TRAININGAXE" ] = {
	Id = 2276,
	Description = "Axe Training",
	MaxLevel = 10,
	NumberOfHits = 0
},
{
	Id = 2277,
	Name = "NC_RESEARCHFE",
	Description = "Research Fire/Earth",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "NC_AXEBOOMERANG" ] = {
	Id = 2278,
	Description = "Axe Boomerang",
	MaxLevel = 5,
	Range = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	KnockBackTiles = {
		[1] = 2,
		[2] = 3,
		[3] = 4,
		[4] = 5,
		[5] = 6,
		[6] = 7,
		[7] = 8,
		[8] = 9,
		[9] = 10,
		[10] = 11
	},
	CoolDown = {
		[1] = 5000,
		[2] = 4500,
		[3] = 4000,
		[4] = 3500,
		[5] = 3000,
		[6] = 2500,
		[7] = 2000,
		[8] = 1500,
		[9] = 1000,
		[10] = 500
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 22,
			[3] = 24,
			[4] = 26,
			[5] = 28,
			[6] = 30,
			[7] = 32,
			[8] = 34,
			[9] = 36,
			[10] = 38
		},
		WeaponTypes = {
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe
		}
	}
},
[ "NC_POWERSWING" ] = {
	Id = 2279,
	Description = "Power Swing",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = 1000,
	SkillData1 = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 22,
			[3] = 24,
			[4] = 26,
			[5] = 28,
			[6] = 30,
			[7] = 32,
			[8] = 34,
			[9] = 36,
			[10] = 38
		}
	}
},
[ "NC_AXETORNADO" ] = {
	Id = 2280,
	Description = "Axe Tornado",
	MaxLevel = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 2,
		[3] = 3,
		[4] = 3,
		[5] = 3,
		[6] = 3,
		[7] = 3,
		[8] = 3,
		[9] = 3,
		[10] = 3
	},
	NumberOfHits: -3,
	AfterCastActDelay = 500,
	CoolDown = {
		[1] = 4000,
		[2] = 3500,
		[3] = 3000,
		[4] = 2500,
		[5] = 2000,
		[6] = 1500,
		[7] = 1000,
		[8] = 500,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = -1,
	Requirements = {
		HPCost = {
			[1] = 20,
			[2] = 40,
			[3] = 60,
			[4] = 80,
			[5] = 100,
			[6] = 120,
			[7] = 140,
			[8] = 160,
			[9] = 180,
			[10] = 200
		},
		SPCost = {
			[1] = 18,
			[2] = 20,
			[3] = 22,
			[4] = 24,
			[5] = 26,
			[6] = 28,
			[7] = 30,
			[8] = 32,
			[9] = 34,
			[10] = 36
		},
		WeaponTypes = {
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe
		}
	}
},
{
	Id = 2281,
	Name = "NC_SILVERSNIPER",
	Description = "FAW - Silver Sniper",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 2,
	SkillData1 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	FixedCastTime = {
		[1] = 1800,
		[2] = 1600,
		[3] = 1400,
		[4] = 1200,
		[5] = 1000,
		[6] = 800,
		[7] = 600,
		[8] = 400,
		[9] = 200,
		[10] = 1
	},
	Requirements = {
		SPCost = {
			[1] = 25,
			[2] = 30,
			[3] = 35,
			[4] = 40,
			[5] = 45,
			[6] = 50,
			[7] = 55,
			[8] = 60,
			[9] = 65,
			[10] = 70
		},
		Items = {
			Item[ "Portable_Furnace" ] = 0,
			Item[ "Oridecon_Hammer" ] = 0,
			Item[ "Iron" ] = 1,
			Item[ "Steel" ] = 2
		}
	}
},
{
	Id = 2282,
	Name = "NC_MAGICDECOY",
	Description = "FAW - Magic Decoy",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 2,
	SkillData1 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	FixedCastTime = {
		[1] = 1800,
		[2] = 1600,
		[3] = 1400,
		[4] = 1200,
		[5] = 1000,
		[6] = 800,
		[7] = 600,
		[8] = 400,
		[9] = 200,
		[10] = 1
	},
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		},
		Items = {
			Item[ "Portable_Furnace" ] = 0,
			Item[ "Oridecon_Hammer" ] = 0,
			Item[ "Iron" ] = 2,
			Item[ "Brigan" ] = 1
		}
	}
},
[ "NC_DISJOINT" ] = {
	Id = 2283,
	Description = "FAW Removal",
	MaxLevel = 1,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 15,
		Items = {
			Item[ "Monkey_Wrench" ] = 1
		}
	}
},
[ "SC_FATALMENACE" ] = {
	Id = 2284,
	Description = "Fatal Menace",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	AfterCastActDelay = 500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		}
	}
},
[ "SC_REPRODUCE" ] = {
	Id = 2285,
	Description = "Reproduce",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData1 = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		}
	}
},
[ "SC_AUTOSHADOWSPELL" ] = {
	Id = 2286,
	Description = "Auto Shadow Spell",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 4000,
		[2] = 3600,
		[3] = 3200,
		[4] = 2800,
		[5] = 2400,
		[6] = 2000,
		[7] = 1600,
		[8] = 1200,
		[9] = 800,
		[10] = 400
	},
	SkillData1 = {
		[1] = 60000,
		[2] = 80000,
		[3] = 100000,
		[4] = 120000,
		[5] = 140000,
		[6] = 160000,
		[7] = 180000,
		[8] = 200000,
		[9] = 220000,
		[10] = 300000
	},
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		}
	}
},
[ "SC_SHADOWFORM" ] = {
	Id = 2287,
	Description = "Shadow Form",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 30000,
		[2] = 40000,
		[3] = 50000,
		[4] = 60000,
		[5] = 70000,
		[6] = 80000,
		[7] = 90000,
		[8] = 100000,
		[9] = 110000,
		[10] = 120000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 50,
			[3] = 60,
			[4] = 70,
			[5] = 80,
			[6] = 90,
			[7] = 100,
			[8] = 110,
			[9] = 120,
			[10] = 130
		}
	}
},
[ "SC_TRIANGLESHOT" ] = {
	Id = 2288,
	Description = "Triangle Shot",
	MaxLevel = 10,
	Range = {
		[1] = 7,
		[2] = 7,
		[3] = 7,
		[4] = 9,
		[5] = 9,
		[6] = 9,
		[7] = 9,
		[8] = 11,
		[9] = 11,
		[10] = 11
	},
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -3,
	InterruptCast = true,
	KnockBackTiles = 3,
	CastTime = 1000,
	AfterCastActDelay = 500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 24,
			[3] = 26,
			[4] = 28,
			[5] = 30,
			[6] = 32,
			[7] = 34,
			[8] = 36,
			[9] = 38,
			[10] = 40
		},
		WeaponTypes = {
			WeaponType.Bow
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 3
	}
},
[ "SC_BODYPAINT" ] = {
	Id = 2289,
	Description = "Body Painting",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 5000,
		[2] = 7000,
		[3] = 9000,
		[4] = 11000,
		[5] = 13000,
		[6] = 15000,
		[7] = 17000,
		[8] = 19000,
		[9] = 21000,
		[10] = 23000
	},
	SkillData2 = 10000,
	CoolDown = 2000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 15,
			[3] = 20,
			[4] = 25,
			[5] = 30,
			[6] = 35,
			[7] = 40,
			[8] = 45,
			[9] = 50,
			[10] = 55
		},
		Items = {
			Item[ "Paint_Brush" ] = 0,
			Item[ "Surface_Paint" ] = 1
		}
	}
},
[ "SC_INVISIBILITY" ] = {
	Id = 2290,
	Description = "Invisibility",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = 60000,
	CoolDown = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = 100
	}
},
[ "SC_DEADLYINFECT" ] = {
	Id = 2291,
	Description = "Deadly Infect",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 44,
			[3] = 48,
			[4] = 52,
			[5] = 56,
			[6] = 60,
			[7] = 64,
			[8] = 68,
			[9] = 72,
			[10] = 76
		}
	}
},
{
	Id = 2292,
	Name = "SC_ENERVATION",
	Description = "Masquerade - Enervation",
	MaxLevel = 3,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 40,
			[3] = 50,
			[4] = 60,
			[5] = 70,
			[6] = 80,
			[7] = 90,
			[8] = 100,
			[9] = 110,
			[10] = 120
		},
		Items = {
			Item[ "Face_Paint" ] = 1,
			Item[ "Makeover_Brush" ] = 0
		}
	}
},
{
	Id = 2293,
	Name = "SC_GROOMY",
	Description = "Masquerade - Gloomy",
	MaxLevel = 3,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 40,
			[3] = 50,
			[4] = 60,
			[5] = 70,
			[6] = 80,
			[7] = 90,
			[8] = 100,
			[9] = 110,
			[10] = 120
		},
		Items = {
			Item[ "Face_Paint" ] = 1,
			Item[ "Makeover_Brush" ] = 0
		}
	}
},
{
	Id = 2294,
	Name = "SC_IGNORANCE",
	Description = "Masquerade - Ignorance",
	MaxLevel = 3,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 40,
			[3] = 50,
			[4] = 60,
			[5] = 70,
			[6] = 80,
			[7] = 90,
			[8] = 100,
			[9] = 110,
			[10] = 120
		},
		Items = {
			Item[ "Face_Paint" ] = 1,
			Item[ "Makeover_Brush" ] = 0
		}
	}
},
{
	Id = 2295,
	Name = "SC_LAZINESS",
	Description = "Masquerade - Laziness",
	MaxLevel = 3,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 40,
			[3] = 50,
			[4] = 60,
			[5] = 70,
			[6] = 80,
			[7] = 90,
			[8] = 100,
			[9] = 110,
			[10] = 120
		},
		Items = {
			Item[ "Face_Paint" ] = 1,
			Item[ "Makeover_Brush" ] = 0
		}
	}
},
{
	Id = 2296,
	Name = "SC_UNLUCKY",
	Description = "Masquerade - Unlucky",
	MaxLevel = 3,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 40,
			[3] = 50,
			[4] = 60,
			[5] = 70,
			[6] = 80,
			[7] = 90,
			[8] = 100,
			[9] = 110,
			[10] = 120
		},
		Items = {
			Item[ "Face_Paint" ] = 1,
			Item[ "Makeover_Brush" ] = 0
		}
	}
},
{
	Id = 2297,
	Name = "SC_WEAKNESS",
	Description = "Masquerade - Weakness",
	MaxLevel = 3,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 40,
			[3] = 50,
			[4] = 60,
			[5] = 70,
			[6] = 80,
			[7] = 90,
			[8] = 100,
			[9] = 110,
			[10] = 120
		},
		Items = {
			Item[ "Face_Paint" ] = 1,
			Item[ "Makeover_Brush" ] = 0
		}
	}
},
[ "SC_STRIPACCESSARY" ] = {
	Id = 2298,
	Description = "Strip Accessory",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 60000,
		[2] = 70000,
		[3] = 80000,
		[4] = 90000,
		[5] = 100000,
		[6] = 110000,
		[7] = 120000,
		[8] = 130000,
		[9] = 140000,
		[10] = 150000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 18,
			[3] = 21,
			[4] = 24,
			[5] = 27,
			[6] = 30,
			[7] = 33,
			[8] = 36,
			[9] = 39,
			[10] = 42
		}
	}
},
[ "SC_MANHOLE" ] = {
	Id = 2299,
	Description = "Man Hole",
	MaxLevel = 3,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 3,
	CastTime = 1000,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 5000,
		[2] = 10000,
		[3] = 15000,
		[4] = 20000,
		[5] = 25000,
		[6] = 30000,
		[7] = 35000,
		[8] = 40000,
		[9] = 45000,
		[10] = 50000
	},
	SkillData2 = {
		[1] = 5000,
		[2] = 10000,
		[3] = 15000,
		[4] = 20000,
		[5] = 25000,
		[6] = 30000,
		[7] = 35000,
		[8] = 40000,
		[9] = 45000,
		[10] = 50000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		},
		Items = {
			Item[ "Paint_Brush" ] = 0,
			Item[ "Surface_Paint" ] = 1
		}
	},
	Placement = {
		Id = 0xcc,
		Range = 1,
		Interval = 1000,
		Target = "All",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "SC_DIMENSIONDOOR" ] = {
	Id = 2300,
	Description = "Dimension Door",
	MaxLevel = 3,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 1,
	CastTime = 1000,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 4000,
		[2] = 8000,
		[3] = 12000,
		[4] = 16000,
		[5] = 20000,
		[6] = 24000,
		[7] = 28000,
		[8] = 32000,
		[9] = 36000,
		[10] = 40000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 36,
			[3] = 42,
			[4] = 48,
			[5] = 54,
			[6] = 60,
			[7] = 66,
			[8] = 72,
			[9] = 78,
			[10] = 84
		},
		Items = {
			Item[ "Paint_Brush" ] = 0,
			Item[ "Surface_Paint" ] = 1
		}
	},
	Placement = {
		Id = 0xcd,
		Range = 1,
		Interval = 1000,
		Target = "All",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "SC_CHAOSPANIC" ] = {
	Id = 2301,
	Description = "Chaos Panic",
	MaxLevel = 3,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 2,
	InterruptCast = true,
	SkillInstances = 1,
	CastTime = 2000,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 5000,
		[2] = 10000,
		[3] = 15000,
		[4] = 20000,
		[5] = 25000,
		[6] = 30000,
		[7] = 35000,
		[8] = 40000,
		[9] = 45000,
		[10] = 50000
	},
	SkillData2 = {
		[1] = 4000,
		[2] = 8000,
		[3] = 12000,
		[4] = 16000,
		[5] = 20000,
		[6] = 24000,
		[7] = 28000,
		[8] = 32000,
		[9] = 36000,
		[10] = 40000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 36,
			[3] = 42,
			[4] = 48,
			[5] = 54,
			[6] = 60,
			[7] = 66,
			[8] = 72,
			[9] = 78,
			[10] = 84
		},
		Items = {
			Item[ "Paint_Brush" ] = 0,
			Item[ "Surface_Paint" ] = 2
		}
	},
	Placement = {
		Id = 0xce,
		Layout = 2,
		Interval = -1,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget,
			PlacementBehavior.CannotOverlap
		}
	}
},
[ "SC_MAELSTROM" ] = {
	Id = 2302,
	Description = "Maelstrom",
	MaxLevel = 3,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 2,
	InterruptCast = true,
	SkillInstances = 1,
	CastTime = 2000,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 7000,
		[2] = 14000,
		[3] = 21000,
		[4] = 28000,
		[5] = 35000,
		[6] = 42000,
		[7] = 49000,
		[8] = 56000,
		[9] = 63000,
		[10] = 70000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 50,
			[2] = 55,
			[3] = 60,
			[4] = 65,
			[5] = 70,
			[6] = 75,
			[7] = 80,
			[8] = 85,
			[9] = 90,
			[10] = 95
		},
		Items = {
			Item[ "Paint_Brush" ] = 0,
			Item[ "Surface_Paint" ] = 2
		}
	},
	Placement = {
		Id = 0xcf,
		Layout = 2,
		Interval = -1,
		Target = "All"
	}
},
[ "SC_BLOODYLUST" ] = {
	Id = 2303,
	Description = "Bloody Lust",
	MaxLevel = 3,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 5000,
		[2] = 10000,
		[3] = 15000,
		[4] = 20000,
		[5] = 25000,
		[6] = 30000,
		[7] = 35000,
		[8] = 40000,
		[9] = 45000,
		[10] = 50000
	},
	CoolDown = 180000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 70,
			[3] = 80,
			[4] = 90,
			[5] = 100,
			[6] = 110,
			[7] = 120,
			[8] = 130,
			[9] = 140,
			[10] = 150
		},
		Items = {
			Item[ "Paint_Brush" ] = 0,
			Item[ "Surface_Paint" ] = 2
		}
	},
	Placement = {
		Id = 0xd0,
		Layout = 3,
		Interval = -1,
		Target = "All",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath
		}
	}
},
[ "SC_FEINTBOMB" ] = {
	Id = 2304,
	Description = "Feint Bomb",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	CastTime = 1000,
	SkillData1 = 1000,
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 24,
			[2] = 28,
			[3] = 32,
			[4] = 36,
			[5] = 40,
			[6] = 44,
			[7] = 48,
			[8] = 52,
			[9] = 56,
			[10] = 60
		},
		Items = {
			Item[ "Paint_Brush" ] = 0,
			Item[ "Surface_Paint" ] = 1
		}
	},
	Placement = {
		Id = 0xd1,
		Range = 2,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "LG_CANNONSPEAR" ] = {
	Id = 2307,
	Description = "Cannon Spear",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SplashRange = 2,
	SkillInstances = 10,
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 16,
			[3] = 20,
			[4] = 24,
			[5] = 28,
			[6] = 32,
			[7] = 36,
			[8] = 40,
			[9] = 44,
			[10] = 48
		},
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "LG_BANISHINGPOINT" ] = {
	Id = 2308,
	Description = "Banishing Point",
	MaxLevel = 10,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 20,
			[3] = 20,
			[4] = 20,
			[5] = 20,
			[6] = 25,
			[7] = 25,
			[8] = 25,
			[9] = 25,
			[10] = 25
		},
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "LG_TRAMPLE" ] = {
	Id = 2309,
	Description = "Trample",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	AfterCastActDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 45,
			[3] = 60,
			[4] = 75,
			[5] = 90,
			[6] = 105,
			[7] = 120,
			[8] = 135,
			[9] = 150,
			[10] = 165
		}
	}
},
[ "LG_SHIELDPRESS" ] = {
	Id = 2310,
	Description = "Shield Press",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	SkillData1 = {
		[1] = 5500,
		[2] = 6000,
		[3] = 6500,
		[4] = 7000,
		[5] = 7500
	},
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 12,
			[3] = 14,
			[4] = 16,
			[5] = 18,
			[6] = 20,
			[7] = 22,
			[8] = 24,
			[9] = 26,
			[10] = 28
		},
		State = PlayerState.Equipped_Shield
	}
},
[ "LG_REFLECTDAMAGE" ] = {
	Id = 2311,
	Description = "Reflect Damage",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 80,
			[3] = 100,
			[4] = 120,
			[5] = 140,
			[6] = 160,
			[7] = 180,
			[8] = 200,
			[9] = 220,
			[10] = 240
		},
		State = PlayerState.Equipped_Shield
	}
},
[ "LG_PINPOINTATTACK" ] = {
	Id = 2312,
	Description = "Pinpoint Attack",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = 1000,
	SkillData1 = 5000,
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 50,
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "LG_FORCEOFVANGUARD" ] = {
	Id = 2313,
	Description = "Force of Vanguard",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 30
	}
},
[ "LG_RAGEBURST" ] = {
	Id = 2314,
	Description = "Rage Burst",
	MaxLevel = 1,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	AfterCastActDelay = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 150
	}
},
[ "LG_SHIELDSPELL" ] = {
	Id = 2315,
	Description = "Shield Spell",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	Element = {
		[1] = Element.Neutral,
		[2] = Element.Holy,
		[3] = Element.Neutral
	},
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	InterruptCast = true,
	KnockBackTiles = {
		[1] = 2,
		[2] = 0,
		[3] = 0,
		[4] = 0,
		[5] = 0,
		[6] = 0,
		[7] = 0,
		[8] = 0,
		[9] = 0,
		[10] = 0
	},
	CastTime = 1000,
	AfterCastActDelay = 1000,
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 50,
		State = PlayerState.Equipped_Shield
	}
},
[ "LG_EXEEDBREAK" ] = {
	Id = 2316,
	Description = "Exceed Break",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 5000,
		[2] = 5500,
		[3] = 6000,
		[4] = 6500,
		[5] = 7000,
		[6] = 7500,
		[7] = 8000,
		[8] = 8500,
		[9] = 9000,
		[10] = 9500
	},
	AfterCastActDelay = 1000,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 32,
			[3] = 44,
			[4] = 56,
			[5] = 68,
			[6] = 80,
			[7] = 92,
			[8] = 104,
			[9] = 116,
			[10] = 128
		}
	}
},
[ "LG_OVERBRAND" ] = {
	Id = 2317,
	Description = "Over Brand",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	InterruptCast = true,
	CastTime = 500,
	AfterCastActDelay = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 30,
			[3] = 40,
			[4] = 50,
			[5] = 60,
			[6] = 70,
			[7] = 80,
			[8] = 90,
			[9] = 100,
			[10] = 110
		},
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "LG_PRESTIGE" ] = {
	Id = 2318,
	Description = "Prestige",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	CoolDown = 60000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 75,
			[2] = 80,
			[3] = 85,
			[4] = 90,
			[5] = 95,
			[6] = 100,
			[7] = 105,
			[8] = 110,
			[9] = 115,
			[10] = 120
		}
	}
},
[ "LG_BANDING" ] = {
	Id = 2319,
	Description = "Banding",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 3,
	SkillData1 = -1,
	SkillData2 = {
		[1] = 2000,
		[2] = 4000,
		[3] = 6000,
		[4] = 8000,
		[5] = 10000,
		[6] = 12000,
		[7] = 14000,
		[8] = 16000,
		[9] = 18000,
		[10] = 20000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 36,
			[3] = 42,
			[4] = 48,
			[5] = 54,
			[6] = 60,
			[7] = 66,
			[8] = 72,
			[9] = 78,
			[10] = 84
		}
	},
	Placement = {
		Id = 0xec,
		Range = 3,
		Interval = 5000,
		Target = "All"
	}
},
[ "LG_MOONSLASHER" ] = {
	Id = 2320,
	Description = "Moon Slasher",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	CoolDown = {
		[1] = 6000,
		[2] = 5000,
		[3] = 4000,
		[4] = 3000,
		[5] = 2000,
		[6] = 1000,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 24,
			[3] = 28,
			[4] = 32,
			[5] = 36,
			[6] = 40,
			[7] = 44,
			[8] = 48,
			[9] = 52,
			[10] = 56
		},
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "LG_RAYOFGENESIS" ] = {
	Id = 2321,
	Description = "Ray of Genesis",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 5,
	NumberOfHits: -7,
	InterruptCast = true,
	CastTime = {
		[1] = 2000,
		[2] = 2500,
		[3] = 3000,
		[4] = 3500,
		[5] = 4000,
		[6] = 4500,
		[7] = 5000,
		[8] = 5500,
		[9] = 6000,
		[10] = 6500
	},
	AfterCastActDelay = 2000,
	SkillData1 = 10000,
	CoolDown = 5000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 65,
			[3] = 70,
			[4] = 75,
			[5] = 80,
			[6] = 85,
			[7] = 90,
			[8] = 95,
			[9] = 100,
			[10] = 105
		}
	}
},
[ "LG_PIETY" ] = {
	Id = 2322,
	Description = "Piety",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	InterruptCast = true,
	CastTime = {
		[1] = 3000,
		[2] = 2500,
		[3] = 2000,
		[4] = 1500,
		[5] = 1000,
		[6] = 500,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData1 = {
		[1] = 60000,
		[2] = 80000,
		[3] = 100000,
		[4] = 120000,
		[5] = 140000,
		[6] = 160000,
		[7] = 180000,
		[8] = 200000,
		[9] = 220000,
		[10] = 240000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		},
		Items = {
			Item[ "Holy_Water" ] = 2
		}
	}
},
[ "LG_EARTHDRIVE" ] = {
	Id = 2323,
	Description = "Earth Drive",
	MaxLevel = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 2,
		[4] = 2,
		[5] = 3,
		[6] = 3,
		[7] = 4,
		[8] = 4,
		[9] = 5,
		[10] = 5
	},
	NumberOfHits: -5,
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 3000,
		[2] = 6000,
		[3] = 9000,
		[4] = 12000,
		[5] = 15000,
		[6] = 18000,
		[7] = 21000,
		[8] = 24000,
		[9] = 27000,
		[10] = 30000
	},
	CoolDown = {
		[1] = 7000,
		[2] = 6000,
		[3] = 5000,
		[4] = 4000,
		[5] = 3000,
		[6] = 2000,
		[7] = 1000,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 52,
			[2] = 60,
			[3] = 68,
			[4] = 76,
			[5] = 84,
			[6] = 92,
			[7] = 100,
			[8] = 108,
			[9] = 116,
			[10] = 124
		},
		State = PlayerState.Equipped_Shield
	}
},
[ "LG_HESPERUSLIT" ] = {
	Id = 2324,
	Description = "Hesperus Lit",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 3,
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 3000,
	CoolDown = 20000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 90,
			[3] = 100,
			[4] = 110,
			[5] = 120,
			[6] = 130,
			[7] = 140,
			[8] = 150,
			[9] = 160,
			[10] = 170
		},
		WeaponTypes = {
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear
		}
	}
},
[ "LG_INSPIRATION" ] = {
	Id = 2325,
	Description = "Inspiration",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	CoolDown = {
		[1] = 540000,
		[2] = 480000,
		[3] = 420000,
		[4] = 360000,
		[5] = 300000,
		[6] = 240000,
		[7] = 180000,
		[8] = 120000,
		[9] = 60000,
		[10] = 1
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 90,
			[3] = 100,
			[4] = 110,
			[5] = 120,
			[6] = 130,
			[7] = 140,
			[8] = 150,
			[9] = 160,
			[10] = 170
		}
	}
},
[ "LG_OVERBRAND_BRANDISH" ] = {
	Id = 2519,
	Description = "Over Brand",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	InterruptCast = true,
	KnockBackTiles = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	}
},
[ "SR_DRAGONCOMBO" ] = {
	Id = 2326,
	Description = "Dragon Combo",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -2,
	SkillData1 = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 3,
			[2] = 4,
			[3] = 5,
			[4] = 6,
			[5] = 7,
			[6] = 8,
			[7] = 9,
			[8] = 10,
			[9] = 11,
			[10] = 12
		}
	}
},
[ "SR_SKYNETBLOW" ] = {
	Id = 2327,
	Description = "Sky Net Blow",
	MaxLevel = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	NumberOfHits: -3,
	KnockBackTiles = 3,
	AfterCastActDelay = 500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 8,
			[2] = 9,
			[3] = 10,
			[4] = 11,
			[5] = 12,
			[6] = 13,
			[7] = 14,
			[8] = 15,
			[9] = 16,
			[10] = 17
		}
	}
},
[ "SR_EARTHSHAKER" ] = {
	Id = 2328,
	Description = "Earth Shaker",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	SkillData1 = {
		[1] = 1000,
		[2] = 2000,
		[3] = 2000,
		[4] = 3000,
		[5] = 3000
	},
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 36,
			[2] = 40,
			[3] = 44,
			[4] = 48,
			[5] = 52,
			[6] = 56,
			[7] = 60,
			[8] = 64,
			[9] = 68,
			[10] = 72
		},
		SpiritSphereCost = 1
	}
},
[ "SR_FALLENEMPIRE" ] = {
	Id = 2329,
	Description = "Fallen Empire",
	MaxLevel = 5,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -2,
	SkillData1 = {
		[1] = 500,
		[2] = 1000,
		[3] = 1500,
		[4] = 2000,
		[5] = 2500,
		[6] = 3000,
		[7] = 3500,
		[8] = 4000,
		[9] = 4500,
		[10] = 5000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 30,
			[3] = 40,
			[4] = 50,
			[5] = 60,
			[6] = 70,
			[7] = 80,
			[8] = 90,
			[9] = 100,
			[10] = 110
		},
		SpiritSphereCost = 2
	}
},
[ "SR_TIGERCANNON" ] = {
	Id = 2330,
	Description = "Tiger Cannon",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 1,
		[4] = 1,
		[5] = 1,
		[6] = 2,
		[7] = 2,
		[8] = 2,
		[9] = 2,
		[10] = 2
	},
	InterruptCast = true,
	CastTime = {
		[1] = 1100,
		[2] = 1200,
		[3] = 1300,
		[4] = 1400,
		[5] = 1500,
		[6] = 1600,
		[7] = 1700,
		[8] = 1800,
		[9] = 1900,
		[10] = 2000
	},
	AfterCastActDelay = 1000,
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 1,
			[2] = 2,
			[3] = 3,
			[4] = 4,
			[5] = 5,
			[6] = 6,
			[7] = 7,
			[8] = 8,
			[9] = 9,
			[10] = 10
		},
		HPRateCost = {
			[1] = -12,
			[2] = -14,
			[3] = -16,
			[4] = -18,
			[5] = -20,
			[6] = -22,
			[7] = -24,
			[8] = -26,
			[9] = -28,
			[10] = -30
		},
		SPRateCost = {
			[1] = -6,
			[2] = -7,
			[3] = -8,
			[4] = -9,
			[5] = -10,
			[6] = -11,
			[7] = -12,
			[8] = -13,
			[9] = -14,
			[10] = -15
		},
		State = PlayerState.CriticalExplosion,
		SpiritSphereCost = 2
	}
},
[ "SR_HELLGATE" ] = {
	Id = 2331,
	Description = "Hell Gate",
	MaxLevel = 10,
	NumberOfHits = 0,
	Requirements = {
		SPCost = 1
	}
},
[ "SR_RAMPAGEBLASTER" ] = {
	Id = 2332,
	Description = "Rampage Blaster",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	AfterCastActDelay = 1000,
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 150
	}
},
[ "SR_CRESCENTELBOW" ] = {
	Id = 2333,
	Description = "Crescent Elbow",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 3000,
		[2] = 4000,
		[3] = 5000,
		[4] = 6000,
		[5] = 7000,
		[6] = 8000,
		[7] = 9000,
		[8] = 10000,
		[9] = 11000,
		[10] = 12000
	},
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 80,
		SpiritSphereCost = 2
	}
},
[ "SR_CURSEDCIRCLE" ] = {
	Id = 2334,
	Description = "Cursed Circle",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 2,
		[4] = 2,
		[5] = 3,
		[6] = 3,
		[7] = 4,
		[8] = 4,
		[9] = 5,
		[10] = 5
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 3000,
		[2] = 4000,
		[3] = 5000,
		[4] = 6000,
		[5] = 7000,
		[6] = 8000,
		[7] = 9000,
		[8] = 10000,
		[9] = 11000,
		[10] = 12000
	},
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 60,
			[3] = 80,
			[4] = 100,
			[5] = 120,
			[6] = 140,
			[7] = 160,
			[8] = 180,
			[9] = 200,
			[10] = 220
		},
		HPRateCost = {
			[1] = -1,
			[2] = -2,
			[3] = -3,
			[4] = -4,
			[5] = -5,
			[6] = -6,
			[7] = -7,
			[8] = -8,
			[9] = -9,
			[10] = -10
		}
	}
},
[ "SR_LIGHTNINGWALK" ] = {
	Id = 2335,
	Description = "Lightning Walk",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 5000,
		[2] = 6000,
		[3] = 7000,
		[4] = 8000,
		[5] = 9000,
		[6] = 10000,
		[7] = 11000,
		[8] = 12000,
		[9] = 13000,
		[10] = 14000
	},
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 70,
			[3] = 60,
			[4] = 50,
			[5] = 40,
			[6] = 30,
			[7] = 20,
			[8] = 10,
			[9] = 1,
			[10] = 1
		},
		HPRateCost = {
			[1] = -5,
			[2] = -4,
			[3] = -3,
			[4] = -2,
			[5] = -1,
			[6] = 0,
			[7] = 1,
			[8] = 2,
			[9] = 3,
			[10] = 4
		}
	}
},
[ "SR_KNUCKLEARROW" ] = {
	Id = 2336,
	Description = "Knuckle Arrow",
	MaxLevel = 5,
	Range = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	KnockBackTiles = {
		[1] = 2,
		[2] = 3,
		[3] = 4,
		[4] = 5,
		[5] = 6,
		[6] = 7,
		[7] = 8,
		[8] = 9,
		[9] = 10,
		[10] = 11
	},
	AfterCastActDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 15,
			[3] = 20,
			[4] = 25,
			[5] = 30,
			[6] = 35,
			[7] = 40,
			[8] = 45,
			[9] = 50,
			[10] = 55
		},
		SpiritSphereCost = 1
	}
},
[ "SR_WINDMILL" ] = {
	Id = 2337,
	Description = "Windmill",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 500,
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 45
	}
},
[ "SR_RAISINGDRAGON" ] = {
	Id = 2338,
	Description = "Raising Dragon",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	CoolDown = 30000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 120
	}
},
[ "SR_GENTLETOUCH" ] = {
	Id = 2339,
	Description = "Gentle Touch",
	MaxLevel = 5,
	Requirements = {
		SPCost = 1
	}
},
[ "SR_ASSIMILATEPOWER" ] = {
	Id = 2340,
	Description = "Assimilate Power",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	AfterCastActDelay = 1000,
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 10
	}
},
[ "SR_POWERVELOCITY" ] = {
	Id = 2341,
	Description = "Power Velocity",
	MaxLevel = 1,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1500,
	FixedCastTime = 500,
	Requirements = {
		SPCost = 50,
		SpiritSphereCost = 5
	}
},
[ "SR_CRESCENTELBOW_AUTOSPELL" ] = {
	Id = 2342,
	Description = "Crescent Elbow Autospell",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.Ignore_Soft_Def
	},
	KnockBackTiles = 7,
	Requirements = {
		SPCost = 1
	}
},
[ "SR_GATEOFHELL" ] = {
	Id = 2343,
	Description = "Gate of Hell",
	MaxLevel = 10,
	Range = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 3,
		[5] = 4,
		[6] = 4,
		[7] = 5,
		[8] = 5,
		[9] = 6,
		[10] = 7
	},
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	NumberOfHits: -7,
	InterruptCast = true,
	CastTime = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	AfterCastActDelay = {
		[1] = 100,
		[2] = 200,
		[3] = 300,
		[4] = 400,
		[5] = 500,
		[6] = 600,
		[7] = 700,
		[8] = 800,
		[9] = 900,
		[10] = 1000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 11,
			[2] = 12,
			[3] = 13,
			[4] = 14,
			[5] = 15,
			[6] = 16,
			[7] = 17,
			[8] = 18,
			[9] = 19,
			[10] = 20
		},
		SPRateCost = {
			[1] = -11,
			[2] = -12,
			[3] = -13,
			[4] = -14,
			[5] = -15,
			[6] = -16,
			[7] = -17,
			[8] = -18,
			[9] = -19,
			[10] = -20
		},
		SpiritSphereCost = 5
	}
},
{
	Id = 2344,
	Name = "SR_GENTLETOUCH_QUIET",
	Description = "Gentle Touch - Quiet",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SkillData1 = {
		[1] = 5000,
		[2] = 7000,
		[3] = 9000,
		[4] = 11000,
		[5] = 13000,
		[6] = 15000,
		[7] = 17000,
		[8] = 19000,
		[9] = 21000,
		[10] = 23000
	},
	CoolDown = {
		[1] = 1000,
		[2] = 1500,
		[3] = 2000,
		[4] = 2500,
		[5] = 3000,
		[6] = 3500,
		[7] = 4000,
		[8] = 4500,
		[9] = 5000,
		[10] = 5500
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		}
	}
},
{
	Id = 2345,
	Name = "SR_GENTLETOUCH_CURE",
	Description = "Gentle Touch - Cure",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	CoolDown = {
		[1] = 1000,
		[2] = 1500,
		[3] = 2000,
		[4] = 2500,
		[5] = 3000,
		[6] = 3500,
		[7] = 4000,
		[8] = 4500,
		[9] = 5000,
		[10] = 5500
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 50,
			[3] = 60,
			[4] = 70,
			[5] = 80,
			[6] = 90,
			[7] = 100,
			[8] = 110,
			[9] = 120,
			[10] = 130
		},
		SpiritSphereCost = {
			[1] = 1,
			[2] = 2,
			[3] = 3,
			[4] = 4,
			[5] = 5,
			[6] = 6,
			[7] = 7,
			[8] = 8,
			[9] = 9,
			[10] = 10
		}
	}
},
{
	Id = 2346,
	Name = "SR_GENTLETOUCH_ENERGYGAIN",
	Description = "Gentle Touch - Energy Gain",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = 240000,
	FixedCastTime = {
		[1] = 1000,
		[2] = 1500,
		[3] = 2000,
		[4] = 2500,
		[5] = 3000,
		[6] = 3500,
		[7] = 4000,
		[8] = 4500,
		[9] = 5000,
		[10] = 5500
	},
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 50,
			[3] = 60,
			[4] = 70,
			[5] = 80,
			[6] = 90,
			[7] = 100,
			[8] = 110,
			[9] = 120,
			[10] = 130
		},
		HPRateCost = {
			[1] = -1,
			[2] = -2,
			[3] = -3,
			[4] = -4,
			[5] = -5,
			[6] = -6,
			[7] = -7,
			[8] = -8,
			[9] = -9,
			[10] = -10
		}
	}
},
{
	Id = 2347,
	Name = "SR_GENTLETOUCH_CHANGE",
	Description = "Gentle Touch - Change",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = 240000,
	CoolDown = {
		[1] = 200000,
		[2] = 180000,
		[3] = 160000,
		[4] = 140000,
		[5] = 120000,
		[6] = 100000,
		[7] = 80000,
		[8] = 60000,
		[9] = 40000,
		[10] = 20000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 50,
			[3] = 60,
			[4] = 70,
			[5] = 80,
			[6] = 90,
			[7] = 100,
			[8] = 110,
			[9] = 120,
			[10] = 130
		},
		HPRateCost = {
			[1] = -2,
			[2] = -4,
			[3] = -6,
			[4] = -8,
			[5] = -10,
			[6] = -12,
			[7] = -14,
			[8] = -16,
			[9] = -18,
			[10] = -20
		},
		SpiritSphereCost = {
			[1] = 1,
			[2] = 2,
			[3] = 3,
			[4] = 4,
			[5] = 5,
			[6] = 6,
			[7] = 7,
			[8] = 8,
			[9] = 9,
			[10] = 10
		}
	}
},
{
	Id = 2348,
	Name = "SR_GENTLETOUCH_REVITALIZE",
	Description = "Gentle Touch - Revitalize",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = 240000,
	CoolDown = {
		[1] = 200000,
		[2] = 180000,
		[3] = 160000,
		[4] = 140000,
		[5] = 120000,
		[6] = 100000,
		[7] = 80000,
		[8] = 60000,
		[9] = 40000,
		[10] = 20000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 50,
			[3] = 60,
			[4] = 70,
			[5] = 80,
			[6] = 90,
			[7] = 100,
			[8] = 110,
			[9] = 120,
			[10] = 130
		},
		SpiritSphereCost = {
			[1] = 1,
			[2] = 2,
			[3] = 3,
			[4] = 4,
			[5] = 5,
			[6] = 6,
			[7] = 7,
			[8] = 8,
			[9] = 9,
			[10] = 10
		}
	}
},
[ "WA_SWING_DANCE" ] = {
	Id = 2350,
	Description = "Swing Dance",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 2000,
	SkillData1 = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 96,
			[2] = 112,
			[3] = 128,
			[4] = 144,
			[5] = 160,
			[6] = 176,
			[7] = 192,
			[8] = 208,
			[9] = 224,
			[10] = 240
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WA_SYMPHONY_OF_LOVER" ] = {
	Id = 2351,
	Description = "Symphony of Lovers",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 2000,
	SkillData1 = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 69,
			[3] = 78,
			[4] = 87,
			[5] = 96,
			[6] = 105,
			[7] = 114,
			[8] = 123,
			[9] = 132,
			[10] = 141
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WA_MOONLIT_SERENADE" ] = {
	Id = 2352,
	Description = "Moonlit Serenade",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 2000,
	SkillData1 = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 84,
			[2] = 96,
			[3] = 108,
			[4] = 120,
			[5] = 134,
			[6] = 134,
			[7] = 134,
			[8] = 134,
			[9] = 134,
			[10] = 134
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "MI_RUSH_WINDMILL" ] = {
	Id = 2381,
	Description = "Windmill Rush Attack",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 2000,
	SkillData1 = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 82,
			[2] = 88,
			[3] = 94,
			[4] = 100,
			[5] = 106,
			[6] = 112,
			[7] = 118,
			[8] = 124,
			[9] = 130,
			[10] = 136
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "MI_ECHOSONG" ] = {
	Id = 2382,
	Description = "Echo Song",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 2000,
	SkillData1 = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 86,
			[2] = 92,
			[3] = 98,
			[4] = 104,
			[5] = 110,
			[6] = 116,
			[7] = 122,
			[8] = 128,
			[9] = 134,
			[10] = 140
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "MI_HARMONIZE" ] = {
	Id = 2383,
	Description = "Harmonize",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = 60000,
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 75,
			[3] = 80,
			[4] = 85,
			[5] = 90,
			[6] = 95,
			[7] = 100,
			[8] = 105,
			[9] = 110,
			[10] = 115
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WM_LESSON" ] = {
	Id = 2412,
	Description = "Lesson",
	MaxLevel = 10,
	NumberOfHits = 0
},
[ "WM_METALICSOUND" ] = {
	Id = 2413,
	Description = "Metallic Sound",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.WeaponElement,
	NumberOfHits = {
		[1] = -2,
		[2] = -2,
		[3] = -3,
		[4] = -3,
		[5] = -4,
		[6] = -4,
		[7] = -5,
		[8] = -5,
		[9] = -6,
		[10] = -6
	},
	InterruptCast = true,
	CastTime = {
		[1] = 1000,
		[2] = 1500,
		[3] = 2000,
		[4] = 2500,
		[5] = 3000,
		[6] = 3500,
		[7] = 4000,
		[8] = 4500,
		[9] = 5000,
		[10] = 5500
	},
	AfterCastActDelay = 1000,
	CoolDown = {
		[1] = 2000,
		[2] = 2500,
		[3] = 3000,
		[4] = 3500,
		[5] = 4000,
		[6] = 4500,
		[7] = 5000,
		[8] = 5500,
		[9] = 6000,
		[10] = 6500
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 64,
			[2] = 68,
			[3] = 72,
			[4] = 76,
			[5] = 80,
			[6] = 84,
			[7] = 88,
			[8] = 92,
			[9] = 96,
			[10] = 100
		}
	}
},
[ "WM_REVERBERATION" ] = {
	Id = 2414,
	Description = "Reverberation",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
		SkillBehavior.AllowReplicate
	},
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SplashRange = 1,
	InterruptCast = true,
	CastTime = {
		[1] = 1100,
		[2] = 1200,
		[3] = 1300,
		[4] = 1400,
		[5] = 1500,
		[6] = 1600,
		[7] = 1700,
		[8] = 1800,
		[9] = 1900,
		[10] = 2000
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 9000,
		[2] = 10000,
		[3] = 11000,
		[4] = 12000,
		[5] = 13000,
		[6] = 14000,
		[7] = 15000,
		[8] = 16000,
		[9] = 17000,
		[10] = 18000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 28,
			[2] = 32,
			[3] = 38,
			[4] = 42,
			[5] = 48,
			[6] = 52,
			[7] = 58,
			[8] = 62,
			[9] = 68,
			[10] = 72
		}
	},
	Placement = {
		Id = 0xda,
		Interval = -1,
		Target = "Enemy"
	}
},
[ "WM_REVERBERATION_MELEE" ] = {
	Id = 2415,
	Description = "Reverberation Melee",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = 1
	}
},
[ "WM_REVERBERATION_MAGIC" ] = {
	Id = 2416,
	Description = "Reverberation Magic",
	MaxLevel = 5,
	AttackType = AttackType.Magic,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = 1
	}
},
[ "WM_DOMINION_IMPULSE" ] = {
	Id = 2417,
	Description = "Dominion Impulse",
	MaxLevel = 1,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 5,
	AfterCastActDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 10
	}
},
[ "WM_SEVERE_RAINSTORM" ] = {
	Id = 2418,
	Description = "Severe Rainstorm",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 1500,
		[2] = 2000,
		[3] = 2500,
		[4] = 3000,
		[5] = 3500,
		[6] = 4000,
		[7] = 4500,
		[8] = 5000,
		[9] = 5500,
		[10] = 6000
	},
	AfterCastActDelay = 1000,
	SkillData1 = 3400,
	CoolDown = {
		[1] = 5000,
		[2] = 5500,
		[3] = 6000,
		[4] = 6500,
		[5] = 7000,
		[6] = 7500,
		[7] = 8000,
		[8] = 8500,
		[9] = 9000,
		[10] = 9500
	},
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 90,
			[3] = 100,
			[4] = 110,
			[5] = 120,
			[6] = 130,
			[7] = 140,
			[8] = 150,
			[9] = 160,
			[10] = 170
		},
		WeaponTypes = {
			WeaponType.Bow
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 20
	},
	Placement = {
		Id = 0xdb,
		Range = 5,
		Interval = 300,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AffectOnContact
		}
	}
},
[ "WM_POEMOFNETHERWORLD" ] = {
	Id = 2419,
	Description = "Poem of The Netherworld",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	InterruptCast = true,
	SkillInstances = 5,
	CastTime = 3000,
	SkillData1 = {
		[1] = 9000,
		[2] = 11000,
		[3] = 13000,
		[4] = 15000,
		[5] = 17000,
		[6] = 19000,
		[7] = 21000,
		[8] = 23000,
		[9] = 25000,
		[10] = 27000
	},
	SkillData2 = {
		[1] = 8000,
		[2] = 10000,
		[3] = 12000,
		[4] = 14000,
		[5] = 16000,
		[6] = 18000,
		[7] = 20000,
		[8] = 22000,
		[9] = 24000,
		[10] = 26000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 16,
			[3] = 20,
			[4] = 24,
			[5] = 28,
			[6] = 32,
			[7] = 36,
			[8] = 40,
			[9] = 44,
			[10] = 48
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		},
		Items = {
			Item[ "Protect_Neck_Candy" ] = 1
		}
	},
	Placement = {
		Id = 0xde,
		Range = 1,
		Interval = 1000,
		Target = "All",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "WM_VOICEOFSIREN" ] = {
	Id = 2420,
	Description = "Voice of Siren",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 3,
		[3] = 4,
		[4] = 5,
		[5] = 6,
		[6] = 7,
		[7] = 8,
		[8] = 9,
		[9] = 10,
		[10] = 11
	},
	InterruptCast = true,
	CastTime = {
		[1] = 2000,
		[2] = 2200,
		[3] = 2400,
		[4] = 2600,
		[5] = 2800,
		[6] = 3000,
		[7] = 3200,
		[8] = 3400,
		[9] = 3600,
		[10] = 3800
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 15000,
		[2] = 18000,
		[3] = 21000,
		[4] = 24000,
		[5] = 27000,
		[6] = 30000,
		[7] = 33000,
		[8] = 36000,
		[9] = 39000,
		[10] = 42000
	},
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 48,
			[2] = 56,
			[3] = 64,
			[4] = 72,
			[5] = 80,
			[6] = 88,
			[7] = 96,
			[8] = 104,
			[9] = 112,
			[10] = 120
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WM_DEADHILLHERE" ] = {
	Id = 2421,
	Description = "Valley of Death",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 3000,
		[2] = 2500,
		[3] = 2000,
		[4] = 1500,
		[5] = 1000,
		[6] = 500,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	AfterCastActDelay = 1000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 50,
			[2] = 53,
			[3] = 56,
			[4] = 59,
			[5] = 62,
			[6] = 65,
			[7] = 68,
			[8] = 71,
			[9] = 74,
			[10] = 77
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		},
		Items = {
			Item[ "Heartbroken_Tears" ] = 1
		}
	}
},
[ "WM_LULLABY_DEEPSLEEP" ] = {
	Id = 2422,
	Description = "Deep Sleep Lullaby",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 12000,
		[2] = 14000,
		[3] = 16000,
		[4] = 18000,
		[5] = 20000,
		[6] = 22000,
		[7] = 24000,
		[8] = 26000,
		[9] = 28000,
		[10] = 30000
	},
	CoolDown = 10000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 90,
			[3] = 100,
			[4] = 110,
			[5] = 120,
			[6] = 130,
			[7] = 140,
			[8] = 150,
			[9] = 160,
			[10] = 170
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
{
	Id = 2423,
	Name = "WM_SIRCLEOFNATURE",
	Description = "Circle of Nature's Sound",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 1000,
	SkillData1 = 60000,
	CoolDown = 15000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 42,
			[2] = 46,
			[3] = 50,
			[4] = 54,
			[5] = 58,
			[6] = 62,
			[7] = 66,
			[8] = 70,
			[9] = 74,
			[10] = 78
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WM_RANDOMIZESPELL" ] = {
	Id = 2424,
	Description = "Improvised Song",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		}
	}
},
[ "WM_GLOOMYDAY" ] = {
	Id = 2425,
	Description = "Gloomy Day",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	CoolDown = 10000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 75,
			[3] = 90,
			[4] = 105,
			[5] = 120,
			[6] = 135,
			[7] = 150,
			[8] = 165,
			[9] = 180,
			[10] = 195
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WM_GREAT_ECHO" ] = {
	Id = 2426,
	Description = "Great Echo",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.RequiresPartner
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 3,
		[3] = 3,
		[4] = 4,
		[5] = 4,
		[6] = 5,
		[7] = 5,
		[8] = 6,
		[9] = 6,
		[10] = 7
	},
	InterruptCast = true,
	CastTime = {
		[1] = 2000,
		[2] = 2200,
		[3] = 2400,
		[4] = 2600,
		[5] = 2800,
		[6] = 3000,
		[7] = 3200,
		[8] = 3400,
		[9] = 3600,
		[10] = 3800
	},
	AfterCastActDelay = 1000,
	CoolDown = 10000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 90,
			[3] = 100,
			[4] = 110,
			[5] = 120,
			[6] = 130,
			[7] = 140,
			[8] = 150,
			[9] = 160,
			[10] = 170
		},
		Items = {
			Item[ "Protect_Neck_Candy" ] = 1
		}
	}
},
[ "WM_SONG_OF_MANA" ] = {
	Id = 2427,
	Description = "Song of Mana",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.RequiresPartner
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 30000,
		[2] = 60000,
		[3] = 90000,
		[4] = 120000,
		[5] = 150000,
		[6] = 180000,
		[7] = 210000,
		[8] = 240000,
		[9] = 270000,
		[10] = 300000
	},
	CoolDown = 90000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 120,
			[2] = 140,
			[3] = 160,
			[4] = 180,
			[5] = 200,
			[6] = 220,
			[7] = 240,
			[8] = 260,
			[9] = 280,
			[10] = 300
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WM_DANCE_WITH_WUG" ] = {
	Id = 2428,
	Description = "Dance With A Warg",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.RequiresPartner
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	InterruptCast = true,
	CastTime = {
		[1] = 1500,
		[2] = 2000,
		[3] = 2500,
		[4] = 3000,
		[5] = 3500,
		[6] = 4000,
		[7] = 4500,
		[8] = 5000,
		[9] = 5500,
		[10] = 6000
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 30000,
		[2] = 60000,
		[3] = 90000,
		[4] = 120000,
		[5] = 150000,
		[6] = 180000,
		[7] = 210000,
		[8] = 240000,
		[9] = 270000,
		[10] = 300000
	},
	CoolDown = 90000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 120,
			[2] = 140,
			[3] = 160,
			[4] = 180,
			[5] = 200,
			[6] = 220,
			[7] = 240,
			[8] = 260,
			[9] = 280,
			[10] = 300
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WM_SOUND_OF_DESTRUCTION" ] = {
	Id = 2429,
	Description = "Sound of Destruction",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.RequiresPartner
	},
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = {
		[1] = 4,
		[2] = 4,
		[3] = 5,
		[4] = 5,
		[5] = 6,
		[6] = 6,
		[7] = 7,
		[8] = 7,
		[9] = 8,
		[10] = 8
	},
	InterruptCast = true,
	CastTime = {
		[1] = 0,
		[2] = 500,
		[3] = 1000,
		[4] = 1500,
		[5] = 2000,
		[6] = 2500,
		[7] = 3000,
		[8] = 3500,
		[9] = 4000,
		[10] = 4500
	},
	AfterCastActDelay = 1000,
	SkillData1 = 5000,
	CoolDown = {
		[1] = 6000,
		[2] = 7000,
		[3] = 8000,
		[4] = 9000,
		[5] = 10000,
		[6] = 11000,
		[7] = 12000,
		[8] = 13000,
		[9] = 14000,
		[10] = 15000
	},
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 50,
			[2] = 60,
			[3] = 70,
			[4] = 80,
			[5] = 90,
			[6] = 100,
			[7] = 110,
			[8] = 120,
			[9] = 130,
			[10] = 140
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WM_SATURDAY_NIGHT_FEVER" ] = {
	Id = 2430,
	Description = "Saturday Night Fever",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.RequiresPartner
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	InterruptCast = true,
	CastTime = {
		[1] = 1000,
		[2] = 2000,
		[3] = 3000,
		[4] = 4000,
		[5] = 5000,
		[6] = 6000,
		[7] = 7000,
		[8] = 8000,
		[9] = 9000,
		[10] = 10000
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	SkillData2 = 3000,
	CoolDown = 180000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 150,
			[2] = 160,
			[3] = 170,
			[4] = 180,
			[5] = 190,
			[6] = 200,
			[7] = 210,
			[8] = 220,
			[9] = 230,
			[10] = 240
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
{
	Id = 2431,
	Name = "WM_LERADS_DEW",
	Description = "Lerad's Dew",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.RequiresPartner
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 5,
		[2] = 5,
		[3] = 6,
		[4] = 6,
		[5] = 7,
		[6] = 7,
		[7] = 8,
		[8] = 8,
		[9] = 9,
		[10] = 9
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	CoolDown = 180000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 120,
			[2] = 130,
			[3] = 140,
			[4] = 150,
			[5] = 160,
			[6] = 170,
			[7] = 180,
			[8] = 190,
			[9] = 200,
			[10] = 210
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WM_MELODYOFSINK" ] = {
	Id = 2432,
	Description = "Melody of Sink",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.RequiresPartner
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 5,
		[2] = 5,
		[3] = 6,
		[4] = 6,
		[5] = 7,
		[6] = 7,
		[7] = 8,
		[8] = 8,
		[9] = 9,
		[10] = 9
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	CoolDown = 180000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 120,
			[2] = 130,
			[3] = 140,
			[4] = 150,
			[5] = 160,
			[6] = 170,
			[7] = 180,
			[8] = 190,
			[9] = 200,
			[10] = 210
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WM_BEYOND_OF_WARCRY" ] = {
	Id = 2433,
	Description = "Warcry of Beyond",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.RequiresPartner
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 5,
		[2] = 5,
		[3] = 6,
		[4] = 6,
		[5] = 7,
		[6] = 7,
		[7] = 8,
		[8] = 8,
		[9] = 9,
		[10] = 9
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	CoolDown = 180000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 120,
			[2] = 130,
			[3] = 140,
			[4] = 150,
			[5] = 160,
			[6] = 170,
			[7] = 180,
			[8] = 190,
			[9] = 200,
			[10] = 210
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "WM_UNLIMITED_HUMMING_VOICE" ] = {
	Id = 2434,
	Description = "Unlimited Humming Voice",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.RequiresPartner
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 5,
		[2] = 5,
		[3] = 6,
		[4] = 6,
		[5] = 7,
		[6] = 7,
		[7] = 8,
		[8] = 8,
		[9] = 9,
		[10] = 9
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 60000,
		[2] = 90000,
		[3] = 120000,
		[4] = 150000,
		[5] = 180000,
		[6] = 210000,
		[7] = 240000,
		[8] = 270000,
		[9] = 300000,
		[10] = 330000
	},
	CoolDown = {
		[1] = 110000,
		[2] = 120000,
		[3] = 130000,
		[4] = 140000,
		[5] = 150000,
		[6] = 160000,
		[7] = 170000,
		[8] = 180000,
		[9] = 190000,
		[10] = 200000
	},
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 120,
			[2] = 130,
			[3] = 140,
			[4] = 150,
			[5] = 160,
			[6] = 170,
			[7] = 180,
			[8] = 190,
			[9] = 200,
			[10] = 210
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		}
	}
},
[ "SO_FIREWALK" ] = {
	Id = 2443,
	Description = "Fire Walk",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	InterruptCast = true,
	SkillInstances = {
		[1] = 8,
		[2] = 10,
		[3] = 12,
		[4] = 14,
		[5] = 16,
		[6] = 18,
		[7] = 20,
		[8] = 22,
		[9] = 24,
		[10] = 26
	},
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = 12000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 34,
			[3] = 38,
			[4] = 42,
			[5] = 46,
			[6] = 50,
			[7] = 54,
			[8] = 58,
			[9] = 62,
			[10] = 66
		}
	},
	Placement = {
		Id = 0xdc,
		Interval = 300,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap
		}
	}
},
[ "SO_ELECTRICWALK" ] = {
	Id = 2444,
	Description = "Electric Walk",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	InterruptCast = true,
	SkillInstances = {
		[1] = 8,
		[2] = 10,
		[3] = 12,
		[4] = 14,
		[5] = 16,
		[6] = 18,
		[7] = 20,
		[8] = 22,
		[9] = 24,
		[10] = 26
	},
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = 12000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 34,
			[3] = 38,
			[4] = 42,
			[5] = 46,
			[6] = 50,
			[7] = 54,
			[8] = 58,
			[9] = 62,
			[10] = 66
		}
	},
	Placement = {
		Id = 0xdd,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap
		}
	}
},
[ "SO_SPELLFIST" ] = {
	Id = 2445,
	Description = "Spell Fist",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 20000,
		[2] = 25000,
		[3] = 30000,
		[4] = 35000,
		[5] = 40000,
		[6] = 45000,
		[7] = 50000,
		[8] = 55000,
		[9] = 60000,
		[10] = 65000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 44,
			[3] = 48,
			[4] = 52,
			[5] = 56,
			[6] = 60,
			[7] = 64,
			[8] = 68,
			[9] = 72,
			[10] = 76
		}
	}
},
[ "SO_EARTHGRAVE" ] = {
	Id = 2446,
	Description = "Earth Grave",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	NumberOfHits: -3,
	InterruptCast = true,
	CastTime = {
		[1] = 2200,
		[2] = 2400,
		[3] = 2600,
		[4] = 2800,
		[5] = 3000,
		[6] = 3200,
		[7] = 3400,
		[8] = 3600,
		[9] = 3800,
		[10] = 4000
	},
	AfterCastActDelay = 1000,
	SkillData1 = 500,
	SkillData2 = {
		[1] = 8000,
		[2] = 11000,
		[3] = 14000,
		[4] = 17000,
		[5] = 20000,
		[6] = 23000,
		[7] = 26000,
		[8] = 29000,
		[9] = 32000,
		[10] = 35000
	},
	CoolDown = 5000,
	FixedCastTime = {
		[1] = 1800,
		[2] = 1600,
		[3] = 1400,
		[4] = 1200,
		[5] = 1000,
		[6] = 800,
		[7] = 600,
		[8] = 400,
		[9] = 200,
		[10] = 1
	},
	Requirements = {
		SPCost = {
			[1] = 62,
			[2] = 70,
			[3] = 78,
			[4] = 86,
			[5] = 94,
			[6] = 102,
			[7] = 110,
			[8] = 118,
			[9] = 126,
			[10] = 134
		}
	},
	Placement = {
		Id = 0x86,
		Range = {
			[1] = 3,
			[2] = 3,
			[3] = 3,
			[4] = 4,
			[5] = 4,
			[6] = 4,
			[7] = 4,
			[8] = 4,
			[9] = 4,
			[10] = 4
		},
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SO_DIAMONDDUST" ] = {
	Id = 2447,
	Description = "Diamond Dust",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	NumberOfHits: -5,
	InterruptCast = true,
	CastTime = {
		[1] = 5000,
		[2] = 5500,
		[3] = 6000,
		[4] = 6500,
		[5] = 7000,
		[6] = 7500,
		[7] = 8000,
		[8] = 8500,
		[9] = 9000,
		[10] = 9500
	},
	AfterCastActDelay = 1000,
	SkillData1 = 500,
	SkillData2 = {
		[1] = 12000,
		[2] = 14000,
		[3] = 16000,
		[4] = 18000,
		[5] = 20000,
		[6] = 22000,
		[7] = 24000,
		[8] = 26000,
		[9] = 28000,
		[10] = 30000
	},
	CoolDown = 5000,
	FixedCastTime = {
		[1] = 800,
		[2] = 600,
		[3] = 400,
		[4] = 200,
		[5] = -1,
		[6] = -1,
		[7] = -1,
		[8] = -1,
		[9] = -1,
		[10] = -1
	},
	Requirements = {
		SPCost = {
			[1] = 50,
			[2] = 56,
			[3] = 62,
			[4] = 68,
			[5] = 74,
			[6] = 80,
			[7] = 86,
			[8] = 92,
			[9] = 98,
			[10] = 104
		}
	},
	Placement = {
		Id = 0x86,
		Range = {
			[1] = 3,
			[2] = 3,
			[3] = 3,
			[4] = 4,
			[5] = 4,
			[6] = 4,
			[7] = 4,
			[8] = 4,
			[9] = 4,
			[10] = 4
		},
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SO_POISON_BUSTER" ] = {
	Id = 2448,
	Description = "Poison Buster",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Poison,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 1,
		[4] = 1,
		[5] = 2,
		[6] = 2,
		[7] = 2,
		[8] = 2,
		[9] = 2,
		[10] = 2
	},
	InterruptCast = true,
	CastTime = {
		[1] = 2200,
		[2] = 3400,
		[3] = 4600,
		[4] = 5800,
		[5] = 6000,
		[6] = 6000,
		[7] = 6000,
		[8] = 6000,
		[9] = 6000,
		[10] = 6000
	},
	AfterCastActDelay = 1000,
	CoolDown = 2000,
	FixedCastTime = {
		[1] = 800,
		[2] = 600,
		[3] = 400,
		[4] = 200,
		[5] = -1,
		[6] = -1,
		[7] = -1,
		[8] = -1,
		[9] = -1,
		[10] = -1
	},
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 90,
			[3] = 110,
			[4] = 130,
			[5] = 150,
			[6] = 170,
			[7] = 190,
			[8] = 210,
			[9] = 230,
			[10] = 250
		}
	}
},
[ "SO_PSYCHIC_WAVE" ] = {
	Id = 2449,
	Description = "Psychic Wave",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	InterruptCast = true,
	CastTime = {
		[1] = 8000,
		[2] = 9000,
		[3] = 10000,
		[4] = 11000,
		[5] = 12000,
		[6] = 13000,
		[7] = 14000,
		[8] = 15000,
		[9] = 16000,
		[10] = 17000
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 1200,
		[2] = 1700,
		[3] = 2200,
		[4] = 2700,
		[5] = 3200,
		[6] = 3700,
		[7] = 4200,
		[8] = 4700,
		[9] = 5200,
		[10] = 5700
	},
	CoolDown = 5000,
	FixedCastTime = {
		[1] = 1000,
		[2] = 900,
		[3] = 800,
		[4] = 700,
		[5] = 600,
		[6] = 500,
		[7] = 400,
		[8] = 300,
		[9] = 200,
		[10] = 100
	},
	Requirements = {
		SPCost = {
			[1] = 48,
			[2] = 56,
			[3] = 64,
			[4] = 70,
			[5] = 78,
			[6] = 78,
			[7] = 78,
			[8] = 78,
			[9] = 78,
			[10] = 78
		}
	},
	Placement = {
		Id = 0xdf,
		Range = {
			[1] = 3,
			[2] = 3,
			[3] = 4,
			[4] = 4,
			[5] = 5,
			[6] = 5,
			[7] = 6,
			[8] = 6,
			[9] = 7,
			[10] = 7
		},
		Interval = 500,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SO_CLOUD_KILL" ] = {
	Id = 2450,
	Description = "Cloud Kill",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Poison,
	InterruptCast = true,
	CastTime = {
		[1] = 2300,
		[2] = 2500,
		[3] = 2700,
		[4] = 2900,
		[5] = 3100,
		[6] = 3300,
		[7] = 3500,
		[8] = 3700,
		[9] = 3900,
		[10] = 4100
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 8000,
		[2] = 10000,
		[3] = 12000,
		[4] = 14000,
		[5] = 16000,
		[6] = 18000,
		[7] = 20000,
		[8] = 22000,
		[9] = 24000,
		[10] = 26000
	},
	SkillData2 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 5000,
	FixedCastTime = {
		[1] = 700,
		[2] = 500,
		[3] = 300,
		[4] = 100,
		[5] = -1,
		[6] = -1,
		[7] = -1,
		[8] = -1,
		[9] = -1,
		[10] = -1
	},
	Requirements = {
		SPCost = {
			[1] = 48,
			[2] = 56,
			[3] = 64,
			[4] = 70,
			[5] = 78,
			[6] = 78,
			[7] = 78,
			[8] = 78,
			[9] = 78,
			[10] = 78
		},
		Items = {
			Item[ "Red_Gemstone" ] = 2
		}
	},
	Placement = {
		Id = 0xe0,
		Layout = 3,
		Interval = 500,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SO_STRIKING" ] = {
	Id = 2451,
	Description = "Striking",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = 60000,
	CoolDown = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 50,
			[2] = 55,
			[3] = 60,
			[4] = 65,
			[5] = 70,
			[6] = 75,
			[7] = 80,
			[8] = 85,
			[9] = 90,
			[10] = 95
		}
	}
},
[ "SO_WARMER" ] = {
	Id = 2452,
	Description = "Warmer",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 2200,
		[2] = 2400,
		[3] = 2600,
		[4] = 2800,
		[5] = 3000,
		[6] = 3200,
		[7] = 3400,
		[8] = 3600,
		[9] = 3800,
		[10] = 4000
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 40000,
		[2] = 45000,
		[3] = 50000,
		[4] = 55000,
		[5] = 60000,
		[6] = 65000,
		[7] = 70000,
		[8] = 75000,
		[9] = 80000,
		[10] = 85000
	},
	SkillData2 = 30000,
	CoolDown = {
		[1] = 35000,
		[2] = 40000,
		[3] = 45000,
		[4] = 50000,
		[5] = 55000,
		[6] = 60000,
		[7] = 65000,
		[8] = 70000,
		[9] = 75000,
		[10] = 80000
	},
	FixedCastTime = {
		[1] = 1800,
		[2] = 1600,
		[3] = 1400,
		[4] = 1200,
		[5] = 1000,
		[6] = 800,
		[7] = 600,
		[8] = 400,
		[9] = 200,
		[10] = 1
	},
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 52,
			[3] = 64,
			[4] = 76,
			[5] = 88,
			[6] = 100,
			[7] = 112,
			[8] = 124,
			[9] = 136,
			[10] = 148
		}
	},
	Placement = {
		Id = 0xe4,
		Range = 3,
		Interval = 3000,
		Target = "All",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SO_VACUUM_EXTREME" ] = {
	Id = 2453,
	Description = "Vacuum Extreme",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 1000,
		[2] = 1500,
		[3] = 2000,
		[4] = 2500,
		[5] = 3000,
		[6] = 3500,
		[7] = 4000,
		[8] = 4500,
		[9] = 5000,
		[10] = 5500
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 4000,
		[2] = 6000,
		[3] = 8000,
		[4] = 10000,
		[5] = 12000,
		[6] = 14000,
		[7] = 16000,
		[8] = 18000,
		[9] = 20000,
		[10] = 22000
	},
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 34,
			[2] = 42,
			[3] = 50,
			[4] = 58,
			[5] = 66,
			[6] = 74,
			[7] = 82,
			[8] = 90,
			[9] = 98,
			[10] = 106
		}
	},
	Placement = {
		Id = 0xeb,
		Range = {
			[1] = 1,
			[2] = 1,
			[3] = 2,
			[4] = 2,
			[5] = 3,
			[6] = 3,
			[7] = 4,
			[8] = 4,
			[9] = 5,
			[10] = 5
		},
		Interval = 500,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SO_VARETYR_SPEAR" ] = {
	Id = 2454,
	Description = "Varetyr Spear",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 2,
		[4] = 2,
		[5] = 3,
		[6] = 3,
		[7] = 4,
		[8] = 4,
		[9] = 5,
		[10] = 5
	},
	InterruptCast = true,
	CastTime = {
		[1] = 2200,
		[2] = 2400,
		[3] = 2600,
		[4] = 2800,
		[5] = 3000,
		[6] = 3200,
		[7] = 3400,
		[8] = 3600,
		[9] = 3800,
		[10] = 4000
	},
	AfterCastActDelay = 1000,
	SkillData2 = {
		[1] = 2200,
		[2] = 2400,
		[3] = 2600,
		[4] = 2800,
		[5] = 3000,
		[6] = 3200,
		[7] = 3400,
		[8] = 3600,
		[9] = 3800,
		[10] = 4000
	},
	CoolDown = 2000,
	FixedCastTime = {
		[1] = 1800,
		[2] = 1600,
		[3] = 1400,
		[4] = 1200,
		[5] = 1000,
		[6] = 800,
		[7] = 600,
		[8] = 400,
		[9] = 200,
		[10] = 1
	},
	Requirements = {
		SPCost = {
			[1] = 55,
			[2] = 62,
			[3] = 69,
			[4] = 76,
			[5] = 83,
			[6] = 90,
			[7] = 97,
			[8] = 104,
			[9] = 111,
			[10] = 118
		}
	}
},
[ "SO_ARRULLO" ] = {
	Id = 2455,
	Description = "Arrullo",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 2,
		[4] = 2,
		[5] = 3,
		[6] = 3,
		[7] = 4,
		[8] = 4,
		[9] = 5,
		[10] = 5
	},
	InterruptCast = true,
	CastTime = {
		[1] = 2200,
		[2] = 2400,
		[3] = 2600,
		[4] = 2800,
		[5] = 3000,
		[6] = 3200,
		[7] = 3400,
		[8] = 3600,
		[9] = 3800,
		[10] = 4000
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 8000,
		[2] = 10000,
		[3] = 12000,
		[4] = 14000,
		[5] = 16000,
		[6] = 18000,
		[7] = 20000,
		[8] = 22000,
		[9] = 24000,
		[10] = 26000
	},
	CoolDown = {
		[1] = 5000,
		[2] = 6000,
		[3] = 7000,
		[4] = 8000,
		[5] = 9000,
		[6] = 10000,
		[7] = 11000,
		[8] = 12000,
		[9] = 13000,
		[10] = 14000
	},
	FixedCastTime = {
		[1] = 800,
		[2] = 600,
		[3] = 400,
		[4] = 200,
		[5] = -1,
		[6] = -1,
		[7] = -1,
		[8] = -1,
		[9] = -1,
		[10] = -1
	},
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 35,
			[3] = 40,
			[4] = 45,
			[5] = 50,
			[6] = 55,
			[7] = 60,
			[8] = 65,
			[9] = 70,
			[10] = 75
		},
		Items = {
			Item[ "Yellow_Gemstone" ] = 1
		}
	}
},
[ "SO_EL_CONTROL" ] = {
	Id = 2456,
	Description = "Spirit Control",
	MaxLevel = 4,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	CoolDown = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10,
		State = PlayerState.HasElementalSpirit
	}
},
[ "SO_SUMMON_AGNI" ] = {
	Id = 2457,
	Description = "Summon Fire Spirit Agni",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 1000,
		[2] = 2000,
		[3] = 3000,
		[4] = 4000,
		[5] = 5000,
		[6] = 6000,
		[7] = 7000,
		[8] = 8000,
		[9] = 9000,
		[10] = 10000
	},
	SkillData1 = {
		[1] = 600000,
		[2] = 900000,
		[3] = 1200000,
		[4] = 1500000,
		[5] = 1800000,
		[6] = 2100000,
		[7] = 2400000,
		[8] = 2700000,
		[9] = 3000000,
		[10] = 3300000
	},
	CoolDown = 60000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 100,
			[2] = 150,
			[3] = 200,
			[4] = 250,
			[5] = 300,
			[6] = 350,
			[7] = 400,
			[8] = 450,
			[9] = 500,
			[10] = 550
		},
		Items = {
			Item[ "Boody_Red" ] = 3,
			Item[ "Boody_Red" ] = 6,
			Item[ "Flame_Heart" ] = 1
		}
	}
},
[ "SO_SUMMON_AQUA" ] = {
	Id = 2458,
	Description = "Summon Water Spirit Aqua",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 1000,
		[2] = 2000,
		[3] = 3000,
		[4] = 4000,
		[5] = 5000,
		[6] = 6000,
		[7] = 7000,
		[8] = 8000,
		[9] = 9000,
		[10] = 10000
	},
	SkillData1 = {
		[1] = 600000,
		[2] = 900000,
		[3] = 1200000,
		[4] = 1500000,
		[5] = 1800000,
		[6] = 2100000,
		[7] = 2400000,
		[8] = 2700000,
		[9] = 3000000,
		[10] = 3300000
	},
	CoolDown = 60000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 100,
			[2] = 150,
			[3] = 200,
			[4] = 250,
			[5] = 300,
			[6] = 350,
			[7] = 400,
			[8] = 450,
			[9] = 500,
			[10] = 550
		},
		Items = {
			Item[ "Crystal_Blue" ] = 3,
			Item[ "Crystal_Blue" ] = 6,
			Item[ "Mistic_Frozen" ] = 1
		}
	}
},
[ "SO_SUMMON_VENTUS" ] = {
	Id = 2459,
	Description = "Summon Wind Spirit Ventus",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 1000,
		[2] = 2000,
		[3] = 3000,
		[4] = 4000,
		[5] = 5000,
		[6] = 6000,
		[7] = 7000,
		[8] = 8000,
		[9] = 9000,
		[10] = 10000
	},
	SkillData1 = {
		[1] = 600000,
		[2] = 900000,
		[3] = 1200000,
		[4] = 1500000,
		[5] = 1800000,
		[6] = 2100000,
		[7] = 2400000,
		[8] = 2700000,
		[9] = 3000000,
		[10] = 3300000
	},
	CoolDown = 60000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 100,
			[2] = 150,
			[3] = 200,
			[4] = 250,
			[5] = 300,
			[6] = 350,
			[7] = 400,
			[8] = 450,
			[9] = 500,
			[10] = 550
		},
		Items = {
			Item[ "Wind_Of_Verdure" ] = 3,
			Item[ "Wind_Of_Verdure" ] = 6,
			Item[ "Rough_Wind" ] = 1
		}
	}
},
[ "SO_SUMMON_TERA" ] = {
	Id = 2460,
	Description = "Summon Earth Spirit Tera",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = {
		[1] = 1000,
		[2] = 2000,
		[3] = 3000,
		[4] = 4000,
		[5] = 5000,
		[6] = 6000,
		[7] = 7000,
		[8] = 8000,
		[9] = 9000,
		[10] = 10000
	},
	SkillData1 = {
		[1] = 600000,
		[2] = 900000,
		[3] = 1200000,
		[4] = 1500000,
		[5] = 1800000,
		[6] = 2100000,
		[7] = 2400000,
		[8] = 2700000,
		[9] = 3000000,
		[10] = 3300000
	},
	CoolDown = 60000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 100,
			[2] = 150,
			[3] = 200,
			[4] = 250,
			[5] = 300,
			[6] = 350,
			[7] = 400,
			[8] = 450,
			[9] = 500,
			[10] = 550
		},
		Items = {
			Item[ "Yellow_Live" ] = 3,
			Item[ "Yellow_Live" ] = 6,
			Item[ "Great_Nature" ] = 1
		}
	}
},
[ "SO_EL_ACTION" ] = {
	Id = 2461,
	Description = "Elemental Action",
	MaxLevel = 1,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CoolDown = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 50,
		State = PlayerState.HasElementalSpirit
	}
},
[ "SO_EL_ANALYSIS" ] = {
	Id = 2462,
	Description = "Four Spirit Analysis",
	MaxLevel = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 20,
			[3] = 30,
			[4] = 40,
			[5] = 50,
			[6] = 60,
			[7] = 70,
			[8] = 80,
			[9] = 90,
			[10] = 100
		}
	}
},
[ "SO_EL_SYMPATHY" ] = {
	Id = 2463,
	Description = "Spirit Sympathy",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "SO_EL_CURE" ] = {
	Id = 2464,
	Description = "Spirit Recovery",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 10,
		State = PlayerState.HasElementalSpirit
	}
},
[ "SO_FIRE_INSIGNIA" ] = {
	Id = 2465,
	Description = "Fire Insignia",
	MaxLevel = 3,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 1,
	CastTime = 1000,
	SkillData1 = 60000,
	CoolDown = 60000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 30,
			[3] = 38,
			[4] = 46,
			[5] = 54,
			[6] = 62,
			[7] = 70,
			[8] = 78,
			[9] = 86,
			[10] = 94
		},
		Items = {
			Item[ "Scarlet_Pts" ] = 1,
			Item[ "Scarlet_Pts" ] = 2,
			Item[ "Scarlet_Pts" ] = 3
		}
	},
	Placement = {
		Id = 0xf1,
		Range = 1,
		Interval = 1000,
		Target = "All",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SO_WATER_INSIGNIA" ] = {
	Id = 2466,
	Description = "Water Insignia",
	MaxLevel = 3,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 1,
	CastTime = 1000,
	SkillData1 = 60000,
	CoolDown = 60000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 30,
			[3] = 38,
			[4] = 46,
			[5] = 54,
			[6] = 62,
			[7] = 70,
			[8] = 78,
			[9] = 86,
			[10] = 94
		},
		Items = {
			Item[ "Indigo_Pts" ] = 1,
			Item[ "Indigo_Pts" ] = 2,
			Item[ "Indigo_Pts" ] = 3
		}
	},
	Placement = {
		Id = 0xf2,
		Range = 1,
		Interval = 1000,
		Target = "All",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SO_WIND_INSIGNIA" ] = {
	Id = 2467,
	Description = "Wind Insignia",
	MaxLevel = 3,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 1,
	CastTime = 1000,
	SkillData1 = 60000,
	CoolDown = 60000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 30,
			[3] = 38,
			[4] = 46,
			[5] = 54,
			[6] = 62,
			[7] = 70,
			[8] = 78,
			[9] = 86,
			[10] = 94
		},
		Items = {
			Item[ "Yellow_Wish_Pts" ] = 1,
			Item[ "Yellow_Wish_Pts" ] = 2,
			Item[ "Yellow_Wish_Pts" ] = 3
		}
	},
	Placement = {
		Id = 0xf3,
		Range = 1,
		Interval = 1000,
		Target = "All",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SO_EARTH_INSIGNIA" ] = {
	Id = 2468,
	Description = "Earth Insignia",
	MaxLevel = 3,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 1,
	CastTime = 1000,
	SkillData1 = 60000,
	CoolDown = 60000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 30,
			[3] = 38,
			[4] = 46,
			[5] = 54,
			[6] = 62,
			[7] = 70,
			[8] = 78,
			[9] = 86,
			[10] = 94
		},
		Items = {
			Item[ "Lime_Green_Pts" ] = 1,
			Item[ "Lime_Green_Pts" ] = 2,
			Item[ "Lime_Green_Pts" ] = 3
		}
	},
	Placement = {
		Id = 0xf4,
		Range = 1,
		Interval = 1000,
		Target = "All",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "GN_TRAINING_SWORD" ] = {
	Id = 2474,
	Description = "Sword Training",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "GN_REMODELING_CART" ] = {
	Id = 2475,
	Description = "Cart Remodeling",
	MaxLevel = 5,
	NumberOfHits = 0
},
[ "GN_CART_TORNADO" ] = {
	Id = 2476,
	Description = "Cart Tornado",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	KnockBackTiles = 2,
	AfterCastActDelay = 500,
	SkillData1 = 5000,
	CoolDown = {
		[1] = 0,
		[2] = 500,
		[3] = 1000,
		[4] = 1500,
		[5] = 2000,
		[6] = 2500,
		[7] = 3000,
		[8] = 3500,
		[9] = 4000,
		[10] = 4500
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = 30,
		State = PlayerState.HasCart
	}
},
[ "GN_CARTCANNON" ] = {
	Id = 2477,
	Description = "Cart Cannon",
	MaxLevel = 5,
	Range = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 2,
		[4] = 2,
		[5] = 3,
		[6] = 3,
		[7] = 4,
		[8] = 4,
		[9] = 5,
		[10] = 5
	},
	InterruptCast = true,
	CastTime = {
		[1] = 1000,
		[2] = 1500,
		[3] = 2000,
		[4] = 2500,
		[5] = 3000,
		[6] = 3500,
		[7] = 4000,
		[8] = 4500,
		[9] = 5000,
		[10] = 5500
	},
	AfterCastActDelay = 500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 42,
			[3] = 44,
			[4] = 46,
			[5] = 48,
			[6] = 50,
			[7] = 52,
			[8] = 54,
			[9] = 56,
			[10] = 58
		},
		AmmoTypes = {
			AmmoType.CannonBall
		},
		AmmoAmount = 1,
		State = PlayerState.HasCart
	}
},
[ "GN_CARTBOOST" ] = {
	Id = 2478,
	Description = "Cart Boost",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1500,
	AfterCastActDelay = 500,
	SkillData1 = 90000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 24,
			[3] = 28,
			[4] = 32,
			[5] = 36,
			[6] = 40,
			[7] = 44,
			[8] = 48,
			[9] = 52,
			[10] = 56
		},
		State = PlayerState.HasCart
	}
},
[ "GN_THORNS_TRAP" ] = {
	Id = 2479,
	Description = "Thorn Trap",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Misc,
	InterruptCast = true,
	SkillInstances = 5,
	CastTime = 1500,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 10000,
		[2] = 12000,
		[3] = 14000,
		[4] = 16000,
		[5] = 18000,
		[6] = 20000,
		[7] = 22000,
		[8] = 24000,
		[9] = 26000,
		[10] = 28000
	},
	SkillData2 = 20000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 26,
			[3] = 30,
			[4] = 34,
			[5] = 38,
			[6] = 42,
			[7] = 46,
			[8] = 50,
			[9] = 54,
			[10] = 58
		},
		Items = {
			Item[ "Seed_Of_Horny_Plant" ] = 1
		}
	},
	Placement = {
		Id = 0xe5,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "GN_BLOOD_SUCKER" ] = {
	Id = 2480,
	Description = "Blood Sucker",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 3,
	CastTime = 1500,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 20000,
		[2] = 22000,
		[3] = 24000,
		[4] = 26000,
		[5] = 28000,
		[6] = 30000,
		[7] = 32000,
		[8] = 34000,
		[9] = 36000,
		[10] = 38000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 35,
			[3] = 40,
			[4] = 45,
			[5] = 50,
			[6] = 55,
			[7] = 60,
			[8] = 65,
			[9] = 70,
			[10] = 75
		},
		Items = {
			Item[ "Bloodsuck_Plant_Seed" ] = 1
		}
	}
},
[ "GN_SPORE_EXPLOSION" ] = {
	Id = 2481,
	Description = "Spore Explosion",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = 1500,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 2000,
		[2] = 2000,
		[3] = 3000,
		[4] = 3000,
		[5] = 4000,
		[6] = 4000,
		[7] = 5000,
		[8] = 5000,
		[9] = 6000,
		[10] = 6000
	},
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 55,
			[2] = 60,
			[3] = 65,
			[4] = 70,
			[5] = 75,
			[6] = 80,
			[7] = 85,
			[8] = 90,
			[9] = 95,
			[10] = 100
		},
		Items = {
			Item[ "Bomb_Mushroom_Spore" ] = 1
		}
	}
},
[ "GN_WALLOFTHORN" ] = {
	Id = 2482,
	Description = "Wall of Thorns",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = -1,
	InterruptCast = true,
	SkillInstances = 1,
	KnockBackTiles = 2,
	CastTime = 1500,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 10000,
		[2] = 11000,
		[3] = 12000,
		[4] = 13000,
		[5] = 14000,
		[6] = 15000,
		[7] = 16000,
		[8] = 17000,
		[9] = 18000,
		[10] = 19000
	},
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 50,
			[3] = 60,
			[4] = 70,
			[5] = 80,
			[6] = 90,
			[7] = 100,
			[8] = 110,
			[9] = 120,
			[10] = 130
		},
		Items = {
			Item[ "Seed_Of_Horny_Plant" ] = 1
		}
	},
	Placement = {
		Id = { 0xe6, 0x7f },
		Layout = -1,
		Range = 2,
		Interval = -1,
		Target = "All"
	}
},
[ "GN_CRAZYWEED" ] = {
	Id = 2483,
	Description = "Crazy Weed",
	MaxLevel = 10,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 4,
	InterruptCast = true,
	CastTime = {
		[1] = 3000,
		[2] = 3500,
		[3] = 4000,
		[4] = 4500,
		[5] = 5000,
		[6] = 5500,
		[7] = 6000,
		[8] = 6500,
		[9] = 7000,
		[10] = 7500
	},
	AfterCastActDelay = 500,
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 24,
			[2] = 28,
			[3] = 32,
			[4] = 36,
			[5] = 40,
			[6] = 44,
			[7] = 48,
			[8] = 52,
			[9] = 56,
			[10] = 60
		},
		Items = {
			Item[ "Seed_Of_Horny_Plant" ] = 1
		}
	}
},
[ "GN_CRAZYWEED_ATK" ] = {
	Id = 2484,
	Description = "Crazy Weed Attack",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.IgnoreTargetSkills
	},
	AttackType = AttackType.Weapon,
	Element = Element.Earth,
	SkillData1 = 100,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	},
	Placement = {
		Id = 0x86,
		Range = 2,
		Interval = 100,
		Target = "Enemy"
	}
},
[ "GN_DEMONIC_FIRE" ] = {
	Id = 2485,
	Description = "Demonic Fire",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.IgnoreTargetSkills
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	InterruptCast = true,
	CastTime = {
		[1] = 3000,
		[2] = 3500,
		[3] = 4000,
		[4] = 4500,
		[5] = 5000,
		[6] = 5500,
		[7] = 6000,
		[8] = 6500,
		[9] = 7000,
		[10] = 7500
	},
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 10000,
		[2] = 12000,
		[3] = 14000,
		[4] = 16000,
		[5] = 18000,
		[6] = 20000,
		[7] = 22000,
		[8] = 24000,
		[9] = 26000,
		[10] = 28000
	},
	SkillData2 = {
		[1] = 8000,
		[2] = 16000,
		[3] = 24000,
		[4] = 32000,
		[5] = 40000,
		[6] = 48000,
		[7] = 56000,
		[8] = 64000,
		[9] = 72000,
		[10] = 80000
	},
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 24,
			[2] = 28,
			[3] = 32,
			[4] = 36,
			[5] = 40,
			[6] = 44,
			[7] = 48,
			[8] = 52,
			[9] = 56,
			[10] = 60
		},
		Items = {
			Item[ "Fire_Bottle" ] = 1
		}
	},
	Placement = {
		Id = 0xe7,
		Range = 3,
		Interval = 2000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "GN_FIRE_EXPANSION" ] = {
	Id = 2486,
	Description = "Fire Expansion",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 35,
			[3] = 40,
			[4] = 45,
			[5] = 50,
			[6] = 55,
			[7] = 60,
			[8] = 65,
			[9] = 70,
			[10] = 75
		},
		Items = {
			Item[ "Oil_Bottle" ] = 1,
			Item[ "Explosive_Powder" ] = 1,
			Item[ "Smoke_Powder" ] = 1,
			Item[ "Tear_Gas" ] = 1,
			Item[ "Acid_Bottle" ] = 1
		}
	}
},
[ "GN_FIRE_EXPANSION_SMOKE_POWDER" ] = {
	Id = 2487,
	Description = "Fire Expansion Smoke Powder",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	SkillData1 = {
		[1] = 10000,
		[2] = 12000,
		[3] = 14000,
		[4] = 16000,
		[5] = 18000,
		[6] = 20000,
		[7] = 22000,
		[8] = 24000,
		[9] = 26000,
		[10] = 28000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	},
	Placement = {
		Id = 0xe8,
		Range = 3,
		Interval = 1000,
		Target = "Enemy"
	}
},
[ "GN_FIRE_EXPANSION_TEAR_GAS" ] = {
	Id = 2488,
	Description = "Fire Expansion Tear Gas",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	SkillData1 = {
		[1] = 10000,
		[2] = 12000,
		[3] = 14000,
		[4] = 16000,
		[5] = 18000,
		[6] = 20000,
		[7] = 22000,
		[8] = 24000,
		[9] = 26000,
		[10] = 28000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	},
	Placement = {
		Id = 0xe9,
		Range = 3,
		Interval = 1000,
		Target = "Enemy"
	}
},
[ "GN_FIRE_EXPANSION_ACID" ] = {
	Id = 2489,
	Description = "Fire Expansion Acid",
	MaxLevel = 10,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	Requirements = {
		SPCost = 1
	}
},
{
	Id = 2490,
	Name = "GN_HELLS_PLANT",
	Description = "Hell's Plant",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
		SkillBehavior.AllowReplicate
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	InterruptCast = true,
	SkillInstances = {
		[1] = 2,
		[2] = 3,
		[3] = 4,
		[4] = 5,
		[5] = 6,
		[6] = 7,
		[7] = 8,
		[8] = 9,
		[9] = 10,
		[10] = 11
	},
	CastTime = {
		[1] = 3000,
		[2] = 3500,
		[3] = 4000,
		[4] = 4500,
		[5] = 5000,
		[6] = 5500,
		[7] = 6000,
		[8] = 6500,
		[9] = 7000,
		[10] = 7500
	},
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 14000,
		[2] = 21000,
		[3] = 28000,
		[4] = 35000,
		[5] = 42000,
		[6] = 49000,
		[7] = 56000,
		[8] = 63000,
		[9] = 70000,
		[10] = 77000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		},
		Items = {
			Item[ "MenEater_Plant_Bottle" ] = 1
		}
	},
	Placement = {
		Id = 0xea,
		Range = 1,
		Interval = 1000,
		Target = "All"
	}
},
{
	Id = 2491,
	Name = "GN_HELLS_PLANT_ATK",
	Description = "Hell's Plant Attack",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee,
		IgnoreDefCards = true
	},
	SkillData1 = 20000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "GN_MANDRAGORA" ] = {
	Id = 2492,
	Description = "Howling of Mandragora",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 5,
		[2] = 6,
		[3] = 6,
		[4] = 7,
		[5] = 7,
		[6] = 8,
		[7] = 8,
		[8] = 9,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		},
		Items = {
			Item[ "Mandragora_Flowerpot" ] = 1
		}
	}
},
[ "GN_SLINGITEM" ] = {
	Id = 2493,
	Description = "Sling Item",
	MaxLevel = 1,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CoolDown = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 4,
		AmmoTypes = {
			AmmoType.ThrowableItem
		},
		AmmoAmount = 1
	}
},
[ "GN_CHANGEMATERIAL" ] = {
	Id = 2494,
	Description = "Change Material",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 5
	}
},
[ "GN_MIX_COOKING" ] = {
	Id = 2495,
	Description = "Mix Cooking",
	MaxLevel = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = {
			[1] = 5,
			[2] = 40,
			[3] = 75,
			[4] = 110,
			[5] = 145,
			[6] = 180,
			[7] = 215,
			[8] = 250,
			[9] = 285,
			[10] = 320
		}
	}
},
[ "GN_MAKEBOMB" ] = {
	Id = 2496,
	Description = "Create Bomb",
	MaxLevel = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = {
			[1] = 5,
			[2] = 40,
			[3] = 75,
			[4] = 110,
			[5] = 145,
			[6] = 180,
			[7] = 215,
			[8] = 250,
			[9] = 285,
			[10] = 320
		}
	}
},
[ "GN_S_PHARMACY" ] = {
	Id = 2497,
	Description = "Special Pharmacy",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 12
	}
},
[ "GN_SLINGITEM_RANGEMELEEATK" ] = {
	Id = 2498,
	Description = "Sling Item Attack",
	MaxLevel = 1,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	SkillData1 = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "AB_SECRAMENT" ] = {
	Id = 2515,
	Description = "Secrament",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 500,
	SkillData1 = {
		[1] = 60000,
		[2] = 90000,
		[3] = 120000,
		[4] = 150000,
		[5] = 180000,
		[6] = 210000,
		[7] = 240000,
		[8] = 270000,
		[9] = 300000,
		[10] = 330000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 100,
			[2] = 120,
			[3] = 140,
			[4] = 160,
			[5] = 180,
			[6] = 200,
			[7] = 220,
			[8] = 240,
			[9] = 260,
			[10] = 280
		}
	}
},
[ "WM_SEVERE_RAINSTORM_MELEE" ] = {
	Id = 2516,
	Description = "Severe Rainstorm Melee",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 5
},
[ "SR_HOWLINGOFLION" ] = {
	Id = 2517,
	Description = "Howling of Lion",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	CastTime = 1000,
	SkillData1 = {
		[1] = 12000,
		[2] = 14000,
		[3] = 16000,
		[4] = 18000,
		[5] = 20000,
		[6] = 22000,
		[7] = 24000,
		[8] = 26000,
		[9] = 28000,
		[10] = 30000
	},
	CoolDown = 10000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		},
		SpiritSphereCost = {
			[1] = 1,
			[2] = 2,
			[3] = 3,
			[4] = 4,
			[5] = 5,
			[6] = 6,
			[7] = 7,
			[8] = 8,
			[9] = 9,
			[10] = 10
		}
	}
},
[ "SR_RIDEINLIGHTNING" ] = {
	Id = 2518,
	Description = "Ride In Lightening",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.AllowReplicate
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 2,
		[3] = 3,
		[4] = 3,
		[5] = 4,
		[6] = 4,
		[7] = 5,
		[8] = 5,
		[9] = 6,
		[10] = 6
	},
	CastTime = {
		[1] = 1000,
		[2] = 2000,
		[3] = 3000,
		[4] = 4000,
		[5] = 5000,
		[6] = 6000,
		[7] = 7000,
		[8] = 8000,
		[9] = 9000,
		[10] = 10000
	},
	AfterCastActDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 50,
			[3] = 60,
			[4] = 70,
			[5] = 80,
			[6] = 90,
			[7] = 100,
			[8] = 110,
			[9] = 120,
			[10] = 130
		},
		SpiritSphereCost = {
			[1] = 1,
			[2] = 2,
			[3] = 3,
			[4] = 4,
			[5] = 5,
			[6] = 6,
			[7] = 7,
			[8] = 8,
			[9] = 9,
			[10] = 10
		}
	}
},
[ "RETURN_TO_ELDICASTES" ] = {
	Id = 2534,
	Description = "Return To Eldicastes",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	CastTime = 3000,
	CoolDown = 300000,
	FixedCastTime = 0,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	SkillDelayOptions = {
		SkillDelayOptions.IgnoreDex,
		SkillDelayOptions.IgnoreStatusEffect,
		SkillDelayOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = 1
	}
},
[ "ALL_BUYING_STORE" ] = {
	Id = 2535,
	Description = "Open Buying Store",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	Requirements = {
		SPCost = 1,
		Items = {
			Item[ "Buy_Market_Permit" ] = 1
		}
	}
},
{
	Id = 2536,
	Name = "ALL_GUARDIAN_RECALL",
	Description = "Guardian's Recall",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	CastTime = 3000,
	CoolDown = 300000,
	FixedCastTime = 0,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	SkillDelayOptions = {
		SkillDelayOptions.IgnoreDex,
		SkillDelayOptions.IgnoreStatusEffect,
		SkillDelayOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = 1
	}
},
{
	Id = 2537,
	Name = "ALL_ODINS_POWER",
	Description = "Odin's Power",
	MaxLevel = 2,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 100,
			[3] = 130,
			[4] = 160,
			[5] = 190,
			[6] = 220,
			[7] = 250,
			[8] = 280,
			[9] = 310,
			[10] = 340
		}
	}
},
[ "MC_CARTDECORATE" ] = {
	Id = 2544,
	Description = "Change Cart 2",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.LearntFromQuest
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 40,
		State = PlayerState.HasCart
	}
},
[ "RL_GLITTERING_GREED" ] = {
	Id = 2551,
	Description = "Flip The Coin Greed",
	MaxLevel = 10,
	NumberOfHits = 0,
	Requirements = {
		SPCost = 1
	}
},
{
	Id = 2552,
	Name = "RL_RICHS_COIN",
	Description = "Rich's Coin",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 10
	}
},
[ "RL_MASS_SPIRAL" ] = {
	Id = 2553,
	Description = "Mass Spiral",
	MaxLevel = 5,
	Range = 15,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 84,
			[3] = 88,
			[4] = 92,
			[5] = 96,
			[6] = 100,
			[7] = 104,
			[8] = 108,
			[9] = 112,
			[10] = 116
		}
	}
},
[ "RL_BANISHING_BUSTER" ] = {
	Id = 2554,
	Description = "Banishing Buster",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	Requirements = {
		SPCost = {
			[1] = 55,
			[2] = 60,
			[3] = 65,
			[4] = 70,
			[5] = 75,
			[6] = 80,
			[7] = 85,
			[8] = 90,
			[9] = 95,
			[10] = 100
		}
	}
},
[ "RL_B_TRAP" ] = {
	Id = 2555,
	Description = "Bind Trap",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillInstances = 3,
	CoolDown = {
		[1] = 10000,
		[2] = 11000,
		[3] = 12000,
		[4] = 13000,
		[5] = 14000,
		[6] = 15000,
		[7] = 16000,
		[8] = 17000,
		[9] = 18000,
		[10] = 19000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 32,
			[3] = 34,
			[4] = 36,
			[5] = 38,
			[6] = 40,
			[7] = 42,
			[8] = 44,
			[9] = 46,
			[10] = 48
		}
	},
	Placement = {
		Id = 0x104,
		Range = {
			[1] = 1,
			[2] = 2,
			[3] = 2,
			[4] = 3,
			[5] = 3,
			[6] = 4,
			[7] = 4,
			[8] = 5,
			[9] = 5,
			[10] = 6
		},
		Interval = 500,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "RL_FLICKER" ] = {
	Id = 2556,
	Description = "Flicker",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	Requirements = {
		SPCost = 2
	}
},
[ "RL_S_STORM" ] = {
	Id = 2557,
	Description = "Shatter Storm",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	Requirements = {
		SPCost = {
			[1] = 55,
			[2] = 60,
			[3] = 65,
			[4] = 70,
			[5] = 75,
			[6] = 80,
			[7] = 85,
			[8] = 90,
			[9] = 95,
			[10] = 100
		}
	}
},
[ "RL_E_CHAIN" ] = {
	Id = 2558,
	Description = "Eternal Chain",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 45
	}
},
[ "RL_QD_SHOT" ] = {
	Id = 2559,
	Description = "Quick Draw Shot",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = 5
	}
},
[ "RL_C_MARKER" ] = {
	Id = 2560,
	Description = "Crimson Marker",
	MaxLevel = 1,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillInstances = 3,
	Requirements = {
		SPCost = 10
	}
},
[ "RL_FIREDANCE" ] = {
	Id = 2561,
	Description = "Fire Dance",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 15,
			[3] = 20,
			[4] = 25,
			[5] = 30,
			[6] = 35,
			[7] = 40,
			[8] = 45,
			[9] = 50,
			[10] = 55
		}
	}
},
[ "RL_H_MINE" ] = {
	Id = 2562,
	Description = "Howling Mine",
	MaxLevel = 5,
	Range = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = {
			[1] = 45,
			[2] = 50,
			[3] = 55,
			[4] = 60,
			[5] = 65,
			[6] = 70,
			[7] = 75,
			[8] = 80,
			[9] = 85,
			[10] = 90
		}
	}
},
[ "RL_P_ALTER" ] = {
	Id = 2563,
	Description = "Platinum Alter",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 24,
			[3] = 28,
			[4] = 32,
			[5] = 36,
			[6] = 40,
			[7] = 44,
			[8] = 48,
			[9] = 52,
			[10] = 56
		}
	}
},
[ "RL_FALLEN_ANGEL" ] = {
	Id = 2564,
	Description = "Fallen Angel",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 90
	}
},
[ "RL_R_TRIP" ] = {
	Id = 2565,
	Description = "Round Trip",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 3,
		[3] = 4,
		[4] = 5,
		[5] = 6,
		[6] = 7,
		[7] = 8,
		[8] = 9,
		[9] = 10,
		[10] = 11
	},
	KnockBackTiles = 3,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		}
	}
},
[ "RL_D_TAIL" ] = {
	Id = 2566,
	Description = "Dragon Tail",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 70,
			[3] = 80,
			[4] = 90,
			[5] = 100,
			[6] = 110,
			[7] = 120,
			[8] = 130,
			[9] = 140,
			[10] = 150
		}
	}
},
[ "RL_FIRE_RAIN" ] = {
	Id = 2567,
	Description = "Fire Rain",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = 70
	}
},
[ "RL_HEAT_BARREL" ] = {
	Id = 2568,
	Description = "Heat Barrel",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 40,
			[3] = 50,
			[4] = 60,
			[5] = 70,
			[6] = 80,
			[7] = 90,
			[8] = 100,
			[9] = 110,
			[10] = 120
		}
	}
},
{
	Id = 2569,
	Name = "RL_AM_BLAST",
	Description = "Anti-Material Blast",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 84,
			[3] = 88,
			[4] = 92,
			[5] = 96,
			[6] = 100,
			[7] = 104,
			[8] = 108,
			[9] = 112,
			[10] = 116
		}
	}
},
[ "RL_SLUGSHOT" ] = {
	Id = 2570,
	Description = "Slug Shot",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	KnockBackTiles = 6,
	Requirements = {
		SPCost = {
			[1] = 55,
			[2] = 60,
			[3] = 65,
			[4] = 70,
			[5] = 75,
			[6] = 80,
			[7] = 85,
			[8] = 90,
			[9] = 95,
			[10] = 100
		}
	}
},
[ "RL_HAMMER_OF_GOD" ] = {
	Id = 2571,
	Description = "Hammer of God",
	MaxLevel = 5,
	Range = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 80,
			[3] = 90,
			[4] = 100,
			[5] = 110,
			[6] = 120,
			[7] = 130,
			[8] = 140,
			[9] = 150,
			[10] = 160
		}
	}
},
[ "RL_R_TRIP_PLUSATK" ] = {
	Id = 2572,
	Description = "Round Trip Plus Attack",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	Requirements = {
		SPCost = 1
	}
},
[ "RL_B_FLICKER_ATK" ] = {
	Id = 2573,
	Description = "Bind Flicker Attack",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = 1
	}
},
[ "RL_GLITTERING_GREED_ATK" ] = {
	Id = 2574,
	Description = "Flip The Coin Greed Attack",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = 1
	}
},
[ "KO_YAMIKUMO" ] = {
	Id = 3001,
	Description = "Yamikumo",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	SkillData1 = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 10
	}
},
[ "KO_RIGHT" ] = {
	Id = 3002,
	Description = "Right Hand Mastery",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "KO_LEFT" ] = {
	Id = 3003,
	Description = "Left Hand Mastery",
	MaxLevel = 5,
	AttackType = AttackType.Weapon,
	NumberOfHits = 0
},
[ "KO_JYUMONJIKIRI" ] = {
	Id = 3004,
	Description = "Cross Strike",
	MaxLevel = 5,
	Range = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -2,
	AfterCastActDelay = 500,
	SkillData1 = 3000,
	CoolDown = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 12,
			[3] = 14,
			[4] = 16,
			[5] = 18,
			[6] = 20,
			[7] = 22,
			[8] = 24,
			[9] = 26,
			[10] = 28
		},
		WeaponTypes = {
			DWWeaponType.Dagger,
			DWSwords = true,
			DWDaggerSword = true
		}
	}
},
[ "KO_SETSUDAN" ] = {
	Id = 3005,
	Description = "Soul Sever",
	MaxLevel = 5,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 16,
			[3] = 20,
			[4] = 24,
			[5] = 28,
			[6] = 32,
			[7] = 36,
			[8] = 40,
			[9] = 44,
			[10] = 48
		}
	}
},
[ "KO_BAKURETSU" ] = {
	Id = 3006,
	Description = "Bakuretsu Kunai",
	MaxLevel = 5,
	Range = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	NumberOfHits = 0,
	CastTime = {
		[1] = 1000,
		[2] = 1400,
		[3] = 1800,
		[4] = 2200,
		[5] = 2600,
		[6] = 3000,
		[7] = 3400,
		[8] = 3800,
		[9] = 4200,
		[10] = 4600
	},
	AfterCastActDelay = 1000,
	SkillData1 = 100,
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 5,
			[2] = 6,
			[3] = 7,
			[4] = 8,
			[5] = 9,
			[6] = 10,
			[7] = 11,
			[8] = 12,
			[9] = 13,
			[10] = 14
		},
		Items = {
			Item[ "Explosive_Kunai" ] = 1
		}
	},
	Placement = {
		Id = 0x86,
		Range = 2,
		Interval = 100,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "KO_HAPPOKUNAI" ] = {
	Id = 3007,
	Description = "Happo Kunai",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Misc,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = {
		[1] = 4,
		[2] = 4,
		[3] = 4,
		[4] = 4,
		[5] = 5,
		[6] = 5,
		[7] = 5,
		[8] = 5,
		[9] = 5,
		[10] = 5
	},
	NumberOfHits = 0,
	AfterCastActDelay = 500,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 8,
			[2] = 9,
			[3] = 10,
			[4] = 11,
			[5] = 12,
			[6] = 13,
			[7] = 14,
			[8] = 15,
			[9] = 16,
			[10] = 17
		},
		AmmoTypes = {
			AmmoType.Kunai
		},
		AmmoAmount = 8
	}
},
[ "KO_MUCHANAGE" ] = {
	Id = 3008,
	Description = "Mucha Nage",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		IgnoreElement = true
	},
	SplashRange = 2,
	NumberOfHits: -10,
	CastTime = 1000,
	SkillData1 = 100,
	CoolDown = 10000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 50,
		ZenyCost = {
			[1] = 10000,
			[2] = 20000,
			[3] = 30000,
			[4] = 40000,
			[5] = 50000,
			[6] = 60000,
			[7] = 70000,
			[8] = 80000,
			[9] = 90000,
			[10] = 100000
		}
	},
	Placement = {
		Id = 0x86,
		Range = 2,
		Interval = 100,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "KO_HUUMARANKA" ] = {
	Id = 3009,
	Description = "Huuma Shuriken Ranka",
	MaxLevel = 5,
	Range = {
		[1] = 9,
		[2] = 10,
		[3] = 11,
		[4] = 12,
		[5] = 13,
		[6] = 14,
		[7] = 15,
		[8] = 16,
		[9] = 17,
		[10] = 18
	},
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	NumberOfHits: -5,
	CastTime = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	AfterCastActDelay = 1000,
	SkillData1 = 100,
	CoolDown = 3000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 24,
			[2] = 28,
			[3] = 32,
			[4] = 36,
			[5] = 40,
			[6] = 44,
			[7] = 48,
			[8] = 52,
			[9] = 56,
			[10] = 60
		},
		WeaponTypes = {
			WeaponType.FuumaShuriken
		}
	},
	Placement = {
		Id = 0x86,
		Range = 3,
		Interval = 100,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "KO_MAKIBISHI" ] = {
	Id = 3010,
	Description = "Makibishi",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SkillData1 = {
		[1] = 12000,
		[2] = 14000,
		[3] = 16000,
		[4] = 18000,
		[5] = 20000,
		[6] = 22000,
		[7] = 24000,
		[8] = 26000,
		[9] = 28000,
		[10] = 30000
	},
	SkillData2 = 10000,
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 9,
			[2] = 12,
			[3] = 15,
			[4] = 18,
			[5] = 21,
			[6] = 24,
			[7] = 27,
			[8] = 30,
			[9] = 33,
			[10] = 36
		},
		Items = {
			Makibishi = {
				[1] = 3,
				[2] = 4,
				[3] = 5,
				[4] = 6,
				[5] = 7
			}
		}
	},
	Placement = {
		Id = 0xfc,
		Interval = 5000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "KO_MEIKYOUSISUI" ] = {
	Id = 3011,
	Description = "Meikyo Shisui",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	InterruptCast = true,
	CastTime = 3000,
	SkillData1 = 10000,
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 100
	}
},
[ "KO_ZANZOU" ] = {
	Id = 3012,
	Description = "Zanzou",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	SkillInstances = 1,
	KnockBackTiles = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 30000,
		[2] = 27000,
		[3] = 24000,
		[4] = 21000,
		[5] = 18000,
		[6] = 15000,
		[7] = 12000,
		[8] = 9000,
		[9] = 6000,
		[10] = 3000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 44,
			[3] = 48,
			[4] = 52,
			[5] = 56,
			[6] = 60,
			[7] = 64,
			[8] = 68,
			[9] = 72,
			[10] = 76
		}
	}
},
[ "KO_KYOUGAKU" ] = {
	Id = 3013,
	Description = "Kyougaku",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	CastTime = {
		[1] = 3000,
		[2] = 2500,
		[3] = 2000,
		[4] = 1500,
		[5] = 1000,
		[6] = 500,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 12000,
		[2] = 14000,
		[3] = 16000,
		[4] = 18000,
		[5] = 20000,
		[6] = 22000,
		[7] = 24000,
		[8] = 26000,
		[9] = 28000,
		[10] = 30000
	},
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 44,
			[3] = 48,
			[4] = 52,
			[5] = 56,
			[6] = 60,
			[7] = 64,
			[8] = 68,
			[9] = 72,
			[10] = 76
		}
	}
},
[ "KO_JYUSATSU" ] = {
	Id = 3014,
	Description = "Jyusatsu",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	CastTime = {
		[1] = 3000,
		[2] = 2500,
		[3] = 2000,
		[4] = 1500,
		[5] = 1000,
		[6] = 500,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 8000,
		[2] = 10000,
		[3] = 12000,
		[4] = 14000,
		[5] = 16000,
		[6] = 18000,
		[7] = 20000,
		[8] = 22000,
		[9] = 24000,
		[10] = 26000
	},
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 44,
			[3] = 48,
			[4] = 52,
			[5] = 56,
			[6] = 60,
			[7] = 64,
			[8] = 68,
			[9] = 72,
			[10] = 76
		}
	}
},
[ "KO_KAHU_ENTEN" ] = {
	Id = 3015,
	Description = "Kahu Enten",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 2000,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 20,
		Items = {
			Item[ "Charm_Fire" ] = 1
		}
	}
},
[ "KO_HYOUHU_HUBUKI" ] = {
	Id = 3016,
	Description = "Hyouhu Hubuki",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 2000,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 20,
		Items = {
			Item[ "Charm_Ice" ] = 1
		}
	}
},
[ "KO_KAZEHU_SEIRAN" ] = {
	Id = 3017,
	Description = "Kazehu Seiran",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	Element = Element.Wind,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 2000,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 20,
		Items = {
			Item[ "Charm_Wind" ] = 1
		}
	}
},
[ "KO_DOHU_KOUKAI" ] = {
	Id = 3018,
	Description = "Dohu Koukai",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 2000,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 20,
		Items = {
			Item[ "Charm_Earth" ] = 1
		}
	}
},
[ "KO_KAIHOU" ] = {
	Id = 3019,
	Description = "Technique Kaihou",
	MaxLevel = 5,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	NumberOfHits = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "KO_ZENKAI" ] = {
	Id = 3020,
	Description = "Zenkai",
	MaxLevel = 1,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	NumberOfHits = 3,
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 10000,
	SkillData2 = 10000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 30
	},
	Placement = {
		Id = 0xf8,
		Range = 3,
		Interval = 500,
		Target = "All",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "KO_GENWAKU" ] = {
	Id = 3021,
	Description = "Genwaku",
	MaxLevel = 5,
	Range = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 3000,
		[2] = 2500,
		[3] = 2000,
		[4] = 1500,
		[5] = 1000,
		[6] = 500,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	AfterCastActDelay = 1000,
	SkillData1 = 5000,
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 44,
			[3] = 48,
			[4] = 52,
			[5] = 56,
			[6] = 60,
			[7] = 64,
			[8] = 68,
			[9] = 72,
			[10] = 76
		}
	}
},
[ "KO_IZAYOI" ] = {
	Id = 3022,
	Description = "Izayoi",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	CoolDown = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 75,
			[3] = 80,
			[4] = 85,
			[5] = 90,
			[6] = 95,
			[7] = 100,
			[8] = 105,
			[9] = 110,
			[10] = 115
		}
	}
},
[ "KG_KAGEHUMI" ] = {
	Id = 3023,
	Description = "Kagehumi",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 3,
		[3] = 4,
		[4] = 5,
		[5] = 6,
		[6] = 7,
		[7] = 8,
		[8] = 9,
		[9] = 10,
		[10] = 11
	},
	NumberOfHits = 0,
	SkillData1 = {
		[1] = 5000,
		[2] = 6000,
		[3] = 7000,
		[4] = 8000,
		[5] = 9000,
		[6] = 10000,
		[7] = 11000,
		[8] = 12000,
		[9] = 13000,
		[10] = 14000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 65,
			[3] = 70,
			[4] = 75,
			[5] = 80,
			[6] = 85,
			[7] = 90,
			[8] = 95,
			[9] = 100,
			[10] = 105
		}
	}
},
[ "KG_KYOMU" ] = {
	Id = 3024,
	Description = "Kyomu",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 20000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 50,
		Items = {
			Item[ "Shadow_Orb" ] = 1
		}
	}
},
[ "KG_KAGEMUSYA" ] = {
	Id = 3025,
	Description = "Kagemusha",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 60000,
		[2] = 90000,
		[3] = 120000,
		[4] = 150000,
		[5] = 180000,
		[6] = 210000,
		[7] = 240000,
		[8] = 270000,
		[9] = 300000,
		[10] = 330000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 25,
			[2] = 30,
			[3] = 35,
			[4] = 40,
			[5] = 45,
			[6] = 50,
			[7] = 55,
			[8] = 60,
			[9] = 65,
			[10] = 70
		},
		Items = {
			Item[ "Shadow_Orb" ] = 1
		}
	}
},
[ "OB_ZANGETSU" ] = {
	Id = 3026,
	Description = "Zangetsu",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 1000,
		[2] = 1500,
		[3] = 2000,
		[4] = 2500,
		[5] = 3000,
		[6] = 3500,
		[7] = 4000,
		[8] = 4500,
		[9] = 5000,
		[10] = 5500
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 60000,
		[2] = 75000,
		[3] = 90000,
		[4] = 105000,
		[5] = 120000,
		[6] = 135000,
		[7] = 150000,
		[8] = 165000,
		[9] = 180000,
		[10] = 195000
	},
	CoolDown = 30000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 70,
			[3] = 80,
			[4] = 90,
			[5] = 100,
			[6] = 110,
			[7] = 120,
			[8] = 130,
			[9] = 140,
			[10] = 150
		}
	}
},
[ "OB_OBOROGENSOU" ] = {
	Id = 3027,
	Description = "Oboro Gensou",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 15000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 55,
			[2] = 60,
			[3] = 65,
			[4] = 70,
			[5] = 75,
			[6] = 80,
			[7] = 85,
			[8] = 90,
			[9] = 95,
			[10] = 100
		}
	}
},
[ "OB_OBOROGENSOU_TRANSITION_ATK" ] = {
	Id = 3028,
	Description = "Hazy Moonlight Illusion Transition Attack",
	MaxLevel = 1,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3
},
[ "OB_AKAITSUKI" ] = {
	Id = 3029,
	Description = "Akaitsuki",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	CastTime = {
		[1] = 1000,
		[2] = 1500,
		[3] = 2000,
		[4] = 2500,
		[5] = 3000,
		[6] = 3500,
		[7] = 4000,
		[8] = 4500,
		[9] = 5000,
		[10] = 5500
	},
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	CoolDown = 30000,
	FixedCastTime = 2000,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 30,
			[3] = 40,
			[4] = 50,
			[5] = 60,
			[6] = 70,
			[7] = 80,
			[8] = 90,
			[9] = 100,
			[10] = 110
		}
	}
},
[ "ECL_SNOWFLIP" ] = {
	Id = 3031,
	Description = "Snow Flip",
	MaxLevel = 1,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CoolDown = 5000,
	FixedCastTime = 0
},
[ "ECL_PEONYMAMY" ] = {
	Id = 3032,
	Description = "Peony Mamy",
	MaxLevel = 1,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CoolDown = 5000,
	FixedCastTime = 0
},
[ "ECL_SADAGUI" ] = {
	Id = 3033,
	Description = "Sadagui",
	MaxLevel = 1,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CoolDown = 5000,
	FixedCastTime = 0
},
[ "ECL_SEQUOIADUST" ] = {
	Id = 3034,
	Description = "Sequoia Dust",
	MaxLevel = 1,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CoolDown = 5000,
	FixedCastTime = 0
},
[ "ECLAGE_RECALL" ] = {
	Id = 3035,
	Description = "Return To Eclage",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CoolDown = 300000,
	FixedCastTime = 3000
},
[ "GC_DARKCROW" ] = {
	Id = 5001,
	Description = "Dark Claw",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 3,
	AfterCastActDelay = 1500,
	SkillData1 = 5000,
	CoolDown = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 34,
			[3] = 46,
			[4] = 58,
			[5] = 70,
			[6] = 82,
			[7] = 94,
			[8] = 106,
			[9] = 118,
			[10] = 130
		}
	}
},
[ "RA_UNLIMIT" ] = {
	Id = 5002,
	Description = "Unlimited",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 500,
	SkillData1 = 60000,
	CoolDown = 300000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 100,
			[2] = 120,
			[3] = 140,
			[4] = 160,
			[5] = 180,
			[6] = 200,
			[7] = 220,
			[8] = 240,
			[9] = 260,
			[10] = 280
		}
	}
},
[ "GN_ILLUSIONDOPING" ] = {
	Id = 5003,
	Description = "Illusion Doping",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 4,
		[2] = 5,
		[3] = 6,
		[4] = 7,
		[5] = 8,
		[6] = 9,
		[7] = 10,
		[8] = 11,
		[9] = 12,
		[10] = 13
	},
	SkillData1 = 10000,
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 70,
			[3] = 80,
			[4] = 90,
			[5] = 100,
			[6] = 110,
			[7] = 120,
			[8] = 130,
			[9] = 140,
			[10] = 150
		},
		Items = {
			Item[ "Alchol" ] = 1
		}
	}
},
{
	Id = 5004,
	Name = "RK_DRAGONBREATH_WATER",
	Description = "Dragon Breath - Water",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 1,
		[4] = 2,
		[5] = 2,
		[6] = 2,
		[7] = 3,
		[8] = 3,
		[9] = 4,
		[10] = 4
	},
	CastTime = {
		[1] = 0,
		[2] = 0,
		[3] = 0,
		[4] = 1000,
		[5] = 1000,
		[6] = 1000,
		[7] = 1500,
		[8] = 1500,
		[9] = 2000,
		[10] = 2000
	},
	AfterCastActDelay = 2000,
	SkillData1 = 10000,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 35,
			[3] = 40,
			[4] = 45,
			[5] = 50,
			[6] = 55,
			[7] = 60,
			[8] = 65,
			[9] = 70,
			[10] = 75
		},
		State = PlayerState.MountedDragon
	}
},
[ "RK_LUXANIMA" ] = {
	Id = 5005,
	Description = "Lux Anima",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	SkillData1 = 60000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "NC_MAGMA_ERUPTION" ] = {
	Id = 5006,
	Description = "Magma Eruption",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Misc,
	Element = Element.Fire,
	SkillInstances = 3,
	CastTime = 1000,
	SkillData1 = 10000,
	SkillData2 = 42000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 70,
			[3] = 80,
			[4] = 90,
			[5] = 100,
			[6] = 110,
			[7] = 120,
			[8] = 130,
			[9] = 140,
			[10] = 150
		}
	},
	Placement = {
		Id = 0x101,
		Range = 3,
		Interval = 2000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
{
	Id = 5007,
	Name = "WM_FRIGG_SONG",
	Description = "Frigg's Song",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	SkillData1 = 60000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 200,
			[2] = 230,
			[3] = 260,
			[4] = 290,
			[5] = 320,
			[6] = 350,
			[7] = 380,
			[8] = 410,
			[9] = 440,
			[10] = 470
		},
		WeaponTypes = {
			WeaponType.MusicalInstrument,
			WeaponType.Whip
		},
		Items = {
			Item[ "Heartbroken_Tears" ] = 1
		}
	}
},
[ "SO_ELEMENTAL_SHIELD" ] = {
	Id = 5008,
	Description = "Elemental Shield",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 15,
	CastTime = 1000,
	SkillData1 = 10000,
	CoolDown = 10000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 120,
		State = PlayerState.HasElementalSpirit,
		Items = {
			Item[ "Blue_Gemstone" ] = 1
		}
	},
	Placement = {
		Id = 0x7e,
		Interval = -1,
		Target = "All"
	}
},
[ "SR_FLASHCOMBO" ] = {
	Id = 5009,
	Description = "Flash Combo",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 4000,
	SkillData1 = 4000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 65,
		SpiritSphereCost = {
			[1] = 5,
			[2] = 5,
			[3] = 4,
			[4] = 4,
			[5] = 3,
			[6] = 3,
			[7] = 2,
			[8] = 2,
			[9] = 1,
			[10] = 1
		}
	}
},
[ "SC_ESCAPE" ] = {
	Id = 5010,
	Description = "Emergency Escape",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 1000,
	CoolDown = 15000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 26,
			[3] = 22,
			[4] = 18,
			[5] = 14,
			[6] = 10,
			[7] = 6,
			[8] = 2,
			[9] = 1,
			[10] = 1
		},
		Items = {
			Item[ "Special_Alloy_Trap" ] = 1
		}
	},
	Placement = {
		Id = 0xfe,
		Range = 2,
		Interval = -1,
		Target = "Enemy"
	}
},
[ "AB_OFFERTORIUM" ] = {
	Id = 5011,
	Description = "Offertorium",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 4000,
	SkillData1 = 90000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 60,
			[3] = 90,
			[4] = 120,
			[5] = 150,
			[6] = 180,
			[7] = 210,
			[8] = 240,
			[9] = 270,
			[10] = 300
		}
	}
},
[ "WL_TELEKINESIS_INTENSE" ] = {
	Id = 5012,
	Description = "Intense Telekinesis",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 1000,
	SkillData1 = 60000,
	CoolDown = 300000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 100,
			[2] = 150,
			[3] = 200,
			[4] = 250,
			[5] = 300,
			[6] = 350,
			[7] = 400,
			[8] = 450,
			[9] = 500,
			[10] = 550
		}
	}
},
{
	Id = 5013,
	Name = "LG_KINGS_GRACE",
	Description = "King's Grace",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 5,
	CastTime = 1000,
	SkillData1 = 5000,
	CoolDown = {
		[1] = 100000,
		[2] = 90000,
		[3] = 80000,
		[4] = 70000,
		[5] = 60000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 200,
			[2] = 180,
			[3] = 160,
			[4] = 140,
			[5] = 120,
			[6] = 100,
			[7] = 80,
			[8] = 60,
			[9] = 40,
			[10] = 20
		}
	}
},
[ "ALL_FULL_THROTTLE" ] = {
	Id = 5014,
	Description = "Full Throttle",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 10000,
		[2] = 15000,
		[3] = 20000,
		[4] = 25000,
		[5] = 30000,
		[6] = 35000,
		[7] = 40000,
		[8] = 45000,
		[9] = 50000,
		[10] = 55000
	},
	SkillData2 = 10000,
	CoolDown = 1800000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "SU_BASIC_SKILL" ] = {
	Id = 5018,
	Description = "New Basic Skill",
	MaxLevel = 1,
	NumberOfHits = 0
},
[ "SU_BITE" ] = {
	Id = 5019,
	Description = "Bite",
	MaxLevel = 1,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "SU_HIDE" ] = {
	Id = 5020,
	Description = "Hide",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = -1,
	CoolDown = 15000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 30
	}
},
[ "SU_SCRATCH" ] = {
	Id = 5021,
	Description = "Scratch",
	MaxLevel = 3,
	Range = 2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 10000,
	CoolDown = {
		[1] = 3000,
		[2] = 2000,
		[3] = 1000,
		[4] = 1,
		[5] = 1,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		}
	}
},
[ "SU_STOOP" ] = {
	Id = 5022,
	Description = "Stoop",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 6000,
	CoolDown = 15000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "SU_LOPE" ] = {
	Id = 5023,
	Description = "Lope",
	MaxLevel = 3,
	Range = {
		[1] = 6,
		[2] = 10,
		[3] = 14,
		[4] = 18,
		[5] = 22,
		[6] = 26,
		[7] = 30,
		[8] = 34,
		[9] = 38,
		[10] = 42
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 500,
	AfterCastActDelay = 1000,
	CoolDown = {
		[1] = 2000,
		[2] = 4000,
		[3] = 6000,
		[4] = 8000,
		[5] = 10000,
		[6] = 12000,
		[7] = 14000,
		[8] = 16000,
		[9] = 18000,
		[10] = 20000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 30,
			[3] = 30,
			[4] = 30,
			[5] = 30,
			[6] = 30,
			[7] = 30,
			[8] = 30,
			[9] = 30,
			[10] = 30
		}
	}
},
[ "SU_SPRITEMABLE" ] = {
	Id = 5024,
	Description = "Spirit Marble",
	MaxLevel = 1,
	NumberOfHits = 0
},
[ "SU_POWEROFLAND" ] = {
	Id = 5025,
	Description = "Power of Land",
	MaxLevel = 1,
	NumberOfHits = 0
},
[ "SU_SV_STEMSPEAR" ] = {
	Id = 5026,
	Description = "Silvervine Stem Spear",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = {
		[1] = Element.Earth,
		[2] = Element.Fire,
		[3] = Element.Water,
		[4] = Element.Wind,
		[5] = Element.Ghost
	},
	InterruptCast = true,
	CastTime = 2500,
	AfterCastActDelay = 1000,
	SkillData1 = 10000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 40,
			[3] = 40,
			[4] = 40,
			[5] = 40,
			[6] = 40,
			[7] = 40,
			[8] = 40,
			[9] = 40,
			[10] = 40
		}
	}
},
[ "SU_CN_POWDERING" ] = {
	Id = 5027,
	Description = "Catnip Powdering",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 3,
		[2] = 3,
		[3] = 5,
		[4] = 5,
		[5] = 7
	},
	InterruptCast = true,
	SkillInstances = 1,
	CastTime = 1500,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 3000,
		[2] = 4000,
		[3] = 5000,
		[4] = 6000,
		[5] = 7000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 36,
			[3] = 32,
			[4] = 28,
			[5] = 24
		},
		Items = {
			Item[ "Catnip_Fruit" ] = 1
		}
	},
	Placement = {
		Id = 0x106,
		Layout = {
			[1] = 1,
			[2] = 1,
			[3] = 2,
			[4] = 2,
			[5] = 3
		},
		Interval = -1,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath
		}
	}
},
[ "SU_CN_METEOR" ] = {
	Id = 5028,
	Description = "Catnip Meteor",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	SplashRange = {
		[1] = 3,
		[2] = 3,
		[3] = 5,
		[4] = 5,
		[5] = 7
	},
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5
	},
	InterruptCast = true,
	CastTime = 6000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 1500,
		[2] = 2000,
		[3] = 2500,
		[4] = 3000,
		[5] = 3500
	},
	SkillData2 = 20000,
	CoolDown = {
		[1] = 2000,
		[2] = 3000,
		[3] = 4000,
		[4] = 5000,
		[5] = 6000

	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 35,
			[3] = 50,
			[4] = 65,
			[5] = 80
		},
		Items = {
			Item[ "Catnip_Fruit" ] = 1
		}
	},
	Placement = {
		Id = 0x86,
		Range = 1,
		Interval = 500,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SU_SV_ROOTTWIST" ] = {
	Id = 5029,
	Description = "Silvervine Root Twist",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillInstances = 1,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 7000,
		[2] = 9000,
		[3] = 11000,
		[4] = 13000,
		[5] = 15000,
		[6] = 17000,
		[7] = 19000,
		[8] = 21000,
		[9] = 23000,
		[10] = 25000
	},
	CoolDown = 3000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 12,
			[3] = 14,
			[4] = 16,
			[5] = 18,
			[6] = 20,
			[7] = 22,
			[8] = 24,
			[9] = 26,
			[10] = 28
		}
	},
	Placement = {
		Id = 0x107,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "SU_SV_ROOTTWIST_ATK" ] = {
	Id = 5030,
	Description = "Silver Vine Root Twist Attack",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Poison,
	DamageBehavior = {
		IgnoreElement = true,
		DamageBehavior.Ignore_Soft_Def
	},
	SkillInstances = 1,
	AfterCastActDelay = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 1
	}
},
[ "SU_POWEROFLIFE" ] = {
	Id = 5031,
	Description = "Power of Life",
	MaxLevel = 1,
	NumberOfHits = 0
},
[ "SU_SCAROFTAROU" ] = {
	Id = 5032,
	Description = "Scar of Tarou",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	InterruptCast = true,
	CastTime = 500,
	AfterCastActDelay = 1000,
	SkillData1 = 9000,
	SkillData2 = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 14,
			[3] = 18,
			[4] = 22,
			[5] = 26,
			[6] = 30,
			[7] = 34,
			[8] = 38,
			[9] = 42,
			[10] = 46
		}
	}
},
[ "SU_PICKYPECK" ] = {
	Id = 5033,
	Description = "Picky Peck",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -5,
	InterruptCast = true,
	CastTime = 2500,
	AfterCastActDelay = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 19,
			[3] = 28,
			[4] = 37,
			[5] = 46,
			[6] = 55,
			[7] = 64,
			[8] = 73,
			[9] = 82,
			[10] = 91
		}
	}
},
[ "SU_PICKYPECK_DOUBLE_ATK" ] = {
	Id = 5034,
	Description = "Picky Peck Double Attack",
	MaxLevel = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits: -5,
	InterruptCast = true,
	AfterCastActDelay = 1000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 1
	}
},
[ "SU_ARCLOUSEDASH" ] = {
	Id = 5035,
	Description = "Arclouse Dash",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2500,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 60000,
		[2] = 70000,
		[3] = 80000,
		[4] = 90000,
		[5] = 100000,
		[6] = 110000,
		[7] = 120000,
		[8] = 130000,
		[9] = 140000,
		[10] = 150000
	},
	CoolDown = 10000,
	FixedCastTime = 0,
 	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 20,
			[3] = 28,
			[4] = 36,
			[5] = 44,
			[6] = 52,
			[7] = 60,
			[8] = 68,
			[9] = 76,
			[10] = 84
		}
	}
},
[ "SU_LUNATICCARROTBEAT" ] = {
	Id = 5036,
	Description = "Lunatic Carrot Beat",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 2,
		[4] = 2,
		[5] = 3,
		[6] = 3,
		[7] = 4,
		[8] = 4,
		[9] = 5,
		[10] = 5
	},
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	InterruptCast = true,
	CastTime = 3000,
	AfterCastActDelay = 1000,
	SkillData1 = 1000,
	CoolDown = 8000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 25,
			[3] = 35,
			[4] = 45,
			[5] = 55,
			[6] = 65,
			[7] = 75,
			[8] = 85,
			[9] = 95,
			[10] = 105
		}
	}
},
[ "SU_POWEROFSEA" ] = {
	Id = 5037,
	Description = "Power of Sea",
	MaxLevel = 1,
	NumberOfHits = 0
},
[ "SU_TUNABELLY" ] = {
	Id = 5038,
	Description = "Tuna Belly",
 	MaxLevel = 5,
	Range = 9,
 	Hit = "BDT_SKILL",
 	Behavior = {
		SkillBehavior.UseOnFriend
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 1000,
	CoolDown = {
		[1] = 8000,
		[2] = 10000,
		[3] = 12000,
		[4] = 14000,
		[5] = 16000,
		[6] = 18000,
		[7] = 20000,
		[8] = 22000,
		[9] = 24000,
		[10] = 26000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 30,
			[3] = 40,
			[4] = 50,
			[5] = 60,
			[6] = 70,
			[7] = 80,
			[8] = 90,
			[9] = 100,
			[10] = 110
		}
	}
},
[ "SU_TUNAPARTY" ] = {
	Id = 5039,
	Description = "Tuna Party",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
 	DamageBehavior = {
 		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 30000,
	CoolDown = 20000,
	FixedCastTime = 0,
 	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 30,
			[3] = 40,
			[4] = 50,
			[5] = 60,
			[6] = 70,
			[7] = 80,
			[8] = 90,
			[9] = 100,
			[10] = 110
		}
	}
},
[ "SU_BUNCHOFSHRIMP" ] = {
	Id = 5040,
	Description = "Bunch of Shrimp",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 60000,
		[2] = 90000,
		[3] = 120000,
		[4] = 150000,
		[5] = 180000,
		[6] = 210000,
		[7] = 240000,
		[8] = 270000,
		[9] = 300000,
		[10] = 330000
	},
	CoolDown = 10000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 44,
			[2] = 48,
			[3] = 52,
			[4] = 56,
			[5] = 60,
			[6] = 64,
			[7] = 68,
			[8] = 72,
			[9] = 76,
			[10] = 80
		},
		Items = {
			Item[ "Prawn" ] = 1
		}

	}
},
[ "SU_FRESHSHRIMP" ] = {
	Id = 5041,
	Description = "Fresh Shrimp",
 	MaxLevel = 5,
	Range = 9,
 	Hit = "BDT_SKILL",
 	Behavior = {
		SkillBehavior.UseOnFriend
	},
 	DamageBehavior = {
 		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	InterruptCast = true,
	AfterCastActDelay = 1000,
	SkillData1 = 120000,
	CoolDown = 7000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 24,
			[3] = 26,
			[4] = 28,
			[5] = 30,
			[6] = 32,
			[7] = 34,
			[8] = 36,
			[9] = 38,
			[10] = 40
		}
	}
},
{
	Id = 5042,
	Name = "SU_CN_METEOR_ATK",
	Description = "",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.RequiresPartner
	},
	AttackType = AttackType.Magic,
	InterruptCast = true,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 35,
			[3] = 50,
			[4] = 65,
			[5] = 80
		},
		Items = {
			Item[ "Catnip_Fruit" ] = 1
		}
	}
},
[ "SU_LUNATICCARROTBEAT2" ] = {
	Id = 5043,
	Description = "Lunatic Carrot Beat 2",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.RequiresPartner
	},
	AttackType = AttackType.Weapon,
	InterruptCast = true,
 	Requirements = {
 		SPCost = 1
	}
},
[ "HLIF_HEAL" ] = {
	Id = 8001,
	Description = "Healing Touch",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 13,
			[2] = 16,
			[3] = 19,
			[4] = 22,
			[5] = 25,
			[6] = 28,
			[7] = 31,
			[8] = 34,
			[9] = 37,
			[10] = 40
		},
		Items = {
			Item[ "Red_Slim_Potion" ] = 1
		}
	}
},
[ "HLIF_AVOID" ] = {
	Id = 8002,
	Description = "Avoid",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	AfterCastActDelay = 35000,
	SkillData1 = {
		[1] = 40000,
		[2] = 35000,
		[3] = 30000,
		[4] = 25000,
		[5] = 20000,
		[6] = 15000,
		[7] = 10000,
		[8] = 5000,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		}
	}
},
[ "HLIF_BRAIN" ] = {
	Id = 8003,
	Description = "Brain Surgery",
	MaxLevel = 5,
	SplashRange = 1,
	NumberOfHits = 0
},
[ "HLIF_CHANGE" ] = {
	Id = 8004,
	Description = "Change",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	AfterCastActDelay = {
		[1] = 600000,
		[2] = 900000,
		[3] = 1200000,
		[4] = 1500000,
		[5] = 1800000,
		[6] = 2100000,
		[7] = 2400000,
		[8] = 2700000,
		[9] = 3000000,
		[10] = 3300000
	},
	SkillData1 = {
		[1] = 60000,
		[2] = 120000,
		[3] = 180000,
		[4] = 240000,
		[5] = 300000,
		[6] = 360000,
		[7] = 420000,
		[8] = 480000,
		[9] = 540000,
		[10] = 600000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = 100
	}
},
[ "HAMI_CASTLE" ] = {
	Id = 8005,
	Description = "Castling",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	CoolDown = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 10
	}
},
[ "HAMI_DEFENCE" ] = {
	Id = 8006,
	Description = "Defense",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	SkillData1 = {
		[1] = 40000,
		[2] = 35000,
		[3] = 30000,
		[4] = 25000,
		[5] = 20000,
		[6] = 15000,
		[7] = 10000,
		[8] = 5000,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		}
	}
},
[ "HAMI_SKIN" ] = {
	Id = 8007,
	Description = "Adamantium Skin",
	MaxLevel = 5,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0
},
[ "HAMI_BLOODLUST" ] = {
	Id = 8008,
	Description = "Bloodlust",
	MaxLevel = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	SkillData1 = {
		[1] = 60000,
		[2] = 180000,
		[3] = 300000,
		[4] = 420000,
		[5] = 540000,
		[6] = 660000,
		[7] = 780000,
		[8] = 900000,
		[9] = 1020000,
		[10] = 1140000
	},
	SkillData2 = {
		[1] = 300000,
		[2] = 600000,
		[3] = 900000,
		[4] = 1200000,
		[5] = 1500000,
		[6] = 1800000,
		[7] = 2100000,
		[8] = 2400000,
		[9] = 2700000,
		[10] = 3000000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = 120
	}
},
[ "HFLI_MOON" ] = {
	Id = 8009,
	Description = "Moonlight",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	NumberOfHits = {
		[1] = -1,
		[2] = -2,
		[3] = -2,
		[4] = -2,
		[5] = -3,
		[6] = -3,
		[7] = -3,
		[8] = -3,
		[9] = -3,
		[10] = -3
	},
	AfterCastWalkDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 4,
			[2] = 8,
			[3] = 12,
			[4] = 16,
			[5] = 20,
			[6] = 24,
			[7] = 28,
			[8] = 32,
			[9] = 36,
			[10] = 40
		}
	}
},
[ "HFLI_FLEET" ] = {
	Id = 8010,
	Description = "Fleeting Move",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	SkillData1 = {
		[1] = 60000,
		[2] = 55000,
		[3] = 50000,
		[4] = 45000,
		[5] = 40000,
		[6] = 35000,
		[7] = 30000,
		[8] = 25000,
		[9] = 20000,
		[10] = 15000
	},
	SkillData2 = {
		[1] = 60000,
		[2] = 70000,
		[3] = 80000,
		[4] = 90000,
		[5] = 120000,
		[6] = 120000,
		[7] = 120000,
		[8] = 120000,
		[9] = 120000,
		[10] = 120000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 40,
			[3] = 50,
			[4] = 60,
			[5] = 70,
			[6] = 80,
			[7] = 90,
			[8] = 100,
			[9] = 110,
			[10] = 120
		}
	}
},
[ "HFLI_SPEED" ] = {
	Id = 8011,
	Description = "Speed",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	InterruptCast = true,
	SkillData1 = {
		[1] = 60000,
		[2] = 55000,
		[3] = 50000,
		[4] = 45000,
		[5] = 40000,
		[6] = 35000,
		[7] = 30000,
		[8] = 25000,
		[9] = 20000,
		[10] = 15000
	},
	SkillData2 = {
		[1] = 60000,
		[2] = 70000,
		[3] = 80000,
		[4] = 90000,
		[5] = 120000,
		[6] = 120000,
		[7] = 120000,
		[8] = 120000,
		[9] = 120000,
		[10] = 120000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 40,
			[3] = 50,
			[4] = 60,
			[5] = 70,
			[6] = 80,
			[7] = 90,
			[8] = 100,
			[9] = 110,
			[10] = 120
		}
	}
},
{
	Id = 8012,
	Name = "HFLI_SBR44",
	Description = "S.B.R.44",
	MaxLevel = 3,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	NumberOfHits = 0,
	Requirements = {
		SPCost = 1
	}
},
[ "HVAN_CAPRICE" ] = {
	Id = 8013,
	Description = "Caprice",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	NumberOfHits = {
		[1] = 1,
		[2] = 2,
		[3] = 3,
		[4] = 4,
		[5] = 5,
		[6] = 6,
		[7] = 7,
		[8] = 8,
		[9] = 9,
		[10] = 10
	},
	AfterCastActDelay = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 22,
			[2] = 24,
			[3] = 26,
			[4] = 28,
			[5] = 30,
			[6] = 32,
			[7] = 34,
			[8] = 36,
			[9] = 38,
			[10] = 40
		}
	}
},
[ "HVAN_CHAOTIC" ] = {
	Id = 8014,
	Description = "Benediction of Chaos",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	AfterCastActDelay = 1000,
	AfterCastWalkDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 40
	}
},
[ "HVAN_INSTRUCT" ] = {
	Id = 8015,
	Description = "Instruct",
	MaxLevel = 5,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0
},
[ "HVAN_EXPLOSION" ] = {
	Id = 8016,
	Description = "Bio Explosion",
	MaxLevel = 3,
	Range = 4,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Misc,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		IgnoreElement = true,
		DamageBehavior.IgnoreFlee,
		IgnoreDefCards = true
	},
	SplashRange = 4,
	AfterCastWalkDelay = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "MH_SUMMON_LEGION" ] = {
	Id = 8018,
	Description = "Summon Legion",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 1600,
		[2] = 1400,
		[3] = 1200,
		[4] = 1000,
		[5] = 800,
		[6] = 600,
		[7] = 400,
		[8] = 200,
		[9] = 1,
		[10] = 1
	},
	SkillData1 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	FixedCastTime = {
		[1] = 400,
		[2] = 600,
		[3] = 800,
		[4] = 1000,
		[5] = 1200,
		[6] = 1400,
		[7] = 1600,
		[8] = 1800,
		[9] = 2000,
		[10] = 2200
	},
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 80,
			[3] = 100,
			[4] = 120,
			[5] = 140,
			[6] = 160,
			[7] = 180,
			[8] = 200,
			[9] = 220,
			[10] = 240
		}
	}
},
[ "MH_NEEDLE_OF_PARALYZE" ] = {
	Id = 8019,
	Description = "Needle of Paralyze",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Poison,
	CastTime = {
		[1] = 1000,
		[2] = 1100,
		[3] = 1200,
		[4] = 1300,
		[5] = 1400,
		[6] = 1500,
		[7] = 1600,
		[8] = 1700,
		[9] = 1800,
		[10] = 1900
	},
	SkillData1 = {
		[1] = 12000,
		[2] = 14000,
		[3] = 16000,
		[4] = 18000,
		[5] = 20000,
		[6] = 22000,
		[7] = 24000,
		[8] = 26000,
		[9] = 28000,
		[10] = 30000
	},
	FixedCastTime = {
		[1] = 500,
		[2] = 400,
		[3] = 300,
		[4] = 200,
		[5] = 100,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	Requirements = {
		SPCost = {
			[1] = 48,
			[2] = 60,
			[3] = 72,
			[4] = 84,
			[5] = 96,
			[6] = 108,
			[7] = 120,
			[8] = 132,
			[9] = 144,
			[10] = 156
		}
	}
},
[ "MH_POISON_MIST" ] = {
	Id = 8020,
	Description = "Poison Mist",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	Element = Element.Poison,
	SkillInstances = 1,
	CastTime = {
		[1] = 500,
		[2] = 700,
		[3] = 900,
		[4] = 1100,
		[5] = 1300,
		[6] = 1500,
		[7] = 1700,
		[8] = 1900,
		[9] = 2100,
		[10] = 2300
	},
	SkillData1 = {
		[1] = 12000,
		[2] = 14000,
		[3] = 16000,
		[4] = 18000,
		[5] = 20000,
		[6] = 22000,
		[7] = 24000,
		[8] = 26000,
		[9] = 28000,
		[10] = 30000
	},
	SkillData2 = {
		[1] = 4000,
		[2] = 6000,
		[3] = 8000,
		[4] = 10000,
		[5] = 12000,
		[6] = 14000,
		[7] = 16000,
		[8] = 18000,
		[9] = 20000,
		[10] = 22000
	},
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 65,
			[2] = 75,
			[3] = 85,
			[4] = 95,
			[5] = 105,
			[6] = 115,
			[7] = 125,
			[8] = 135,
			[9] = 145,
			[10] = 155
		}
	},
	Placement = {
		Id = 0xf5,
		Range = 3,
		Interval = 2300,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "MH_PAIN_KILLER" ] = {
	Id = 8021,
	Description = "Pain Killer",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	SkillData1 = {
		[1] = 20000,
		[2] = 30000,
		[3] = 40000,
		[4] = 50000,
		[5] = 60000,
		[6] = 70000,
		[7] = 80000,
		[8] = 90000,
		[9] = 100000,
		[10] = 110000
	},
	FixedCastTime = {
		[1] = 1000,
		[2] = 800,
		[3] = 600,
		[4] = 400,
		[5] = 200,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	Requirements = {
		SPCost = {
			[1] = 48,
			[2] = 52,
			[3] = 56,
			[4] = 60,
			[5] = 64,
			[6] = 68,
			[7] = 72,
			[8] = 76,
			[9] = 80,
			[10] = 84
		}
	}
},
[ "MH_LIGHT_OF_REGENE" ] = {
	Id = 8022,
	Description = "Light of Regene",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	SplashRange = 0,
	SkillData1 = {
		[1] = 360000,
		[2] = 420000,
		[3] = 480000,
		[4] = 540000,
		[5] = 600000,
		[6] = 660000,
		[7] = 720000,
		[8] = 780000,
		[9] = 840000,
		[10] = 900000
	},
	FixedCastTime = {
		[1] = 1600,
		[2] = 1400,
		[3] = 1200,
		[4] = 1000,
		[5] = 800,
		[6] = 600,
		[7] = 400,
		[8] = 200,
		[9] = 1,
		[10] = 1
	},
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 50,
			[3] = 60,
			[4] = 70,
			[5] = 80,
			[6] = 90,
			[7] = 100,
			[8] = 110,
			[9] = 120,
			[10] = 130
		}
	}
},
[ "MH_OVERED_BOOST" ] = {
	Id = 8023,
	Description = "Overed Boost",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	SplashRange = 0,
	CastTime = {
		[1] = 800,
		[2] = 700,
		[3] = 600,
		[4] = 500,
		[5] = 400,
		[6] = 300,
		[7] = 200,
		[8] = 100,
		[9] = 1,
		[10] = 1
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	FixedCastTime = {
		[1] = 200,
		[2] = 300,
		[3] = 400,
		[4] = 500,
		[5] = 600,
		[6] = 700,
		[7] = 800,
		[8] = 900,
		[9] = 1000,
		[10] = 1100
	},
	Requirements = {
		SPCost = {
			[1] = 70,
			[2] = 90,
			[3] = 110,
			[4] = 130,
			[5] = 150,
			[6] = 170,
			[7] = 190,
			[8] = 210,
			[9] = 230,
			[10] = 250
		}
	}
},
[ "MH_ERASER_CUTTER" ] = {
	Id = 8024,
	Description = "Eraser Cutter",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = {
		[1] = Element.Wind,
		[2] = Element.Neutral,
		[3] = Element.Wind,
		[4] = Element.Neutral,
		[5] = Element.Wind
	},
	NumberOfHits: -6,
	InterruptCast = true,
	CastTime = {
		[1] = 1000,
		[2] = 1500,
		[3] = 2000,
		[4] = 2500,
		[5] = 3000,
		[6] = 3500,
		[7] = 4000,
		[8] = 4500,
		[9] = 5000,
		[10] = 5500
	},
	AfterCastActDelay = 2000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 25,
			[2] = 30,
			[3] = 35,
			[4] = 40,
			[5] = 45,
			[6] = 50,
			[7] = 55,
			[8] = 60,
			[9] = 65,
			[10] = 70
		}
	}
},
[ "MH_XENO_SLASHER" ] = {
	Id = 8025,
	Description = "Xeno Slasher",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Magic,
	Element = {
		[1] = Element.Wind,
		[2] = Element.Neutral,
		[3] = Element.Wind,
		[4] = Element.Neutral,
		[5] = Element.Wind
	},
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 2,
		[2] = 2,
		[3] = 3,
		[4] = 3,
		[5] = 4,
		[6] = 4,
		[7] = 5,
		[8] = 5,
		[9] = 6,
		[10] = 6
	},
	NumberOfHits: -6,
	CastTime = {
		[1] = 1500,
		[2] = 2500,
		[3] = 3500,
		[4] = 4500,
		[5] = 5500,
		[6] = 6500,
		[7] = 7500,
		[8] = 8500,
		[9] = 9500,
		[10] = 10500
	},
	AfterCastActDelay = 5000,
	SkillData1 = 500,
	FixedCastTime = 500,
	Requirements = {
		SPCost = {
			[1] = 90,
			[2] = 100,
			[3] = 110,
			[4] = 120,
			[5] = 130,
			[6] = 140,
			[7] = 150,
			[8] = 160,
			[9] = 170,
			[10] = 180
		}
	},
	Placement = {
		Id = 0x86,
		Range = {
			[1] = 2,
			[2] = 2,
			[3] = 3,
			[4] = 3,
			[5] = 4,
			[6] = 4,
			[7] = 5,
			[8] = 5,
			[9] = 6,
			[10] = 6
		},
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "MH_SILENT_BREEZE" ] = {
	Id = 8026,
	Description = "Silent Breeze",
	MaxLevel = 5,
	Range = {
		[1] = 5,
		[2] = 5,
		[3] = 7,
		[4] = 7,
		[5] = 9,
		[6] = 9,
		[7] = 11,
		[8] = 11,
		[9] = 13,
		[10] = 13
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	SkillData1 = {
		[1] = 9000,
		[2] = 12000,
		[3] = 15000,
		[4] = 18000,
		[5] = 21000,
		[6] = 24000,
		[7] = 27000,
		[8] = 30000,
		[9] = 33000,
		[10] = 36000
	},
	FixedCastTime = {
		[1] = 1000,
		[2] = 800,
		[3] = 600,
		[4] = 400,
		[5] = 200,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	Requirements = {
		SPCost = {
			[1] = 45,
			[2] = 54,
			[3] = 63,
			[4] = 72,
			[5] = 81,
			[6] = 90,
			[7] = 99,
			[8] = 108,
			[9] = 117,
			[10] = 126
		}
	}
},
[ "MH_STYLE_CHANGE" ] = {
	Id = 8027,
	Description = "Style Change",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 35
	}
},
[ "MH_SONIC_CRAW" ] = {
	Id = 8028,
	Description = "Sonic Claw",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		},
		State = PlayerState.MHEleanorIsFighting
	}
},
[ "MH_SILVERVEIN_RUSH" ] = {
	Id = 8029,
	Description = "Silver Bain Rush",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 15,
			[3] = 20,
			[4] = 25,
			[5] = 30,
			[6] = 35,
			[7] = 40,
			[8] = 45,
			[9] = 50,
			[10] = 55
		},
		SpiritSphereCost = 1
	}
},
[ "MH_MIDNIGHT_FRENZY" ] = {
	Id = 8030,
	Description = "Midnight Frenzy",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Requirements = {
		SPCost = {
			[1] = 8,
			[2] = 16,
			[3] = 24,
			[4] = 32,
			[5] = 40,
			[6] = 48,
			[7] = 56,
			[8] = 64,
			[9] = 72,
			[10] = 80
		},
		SpiritSphereCost = 2
	}
},
[ "MH_STAHL_HORN" ] = {
	Id = 8031,
	Description = "Steel Horn",
	MaxLevel = 5,
	Range = {
		[1] = 5,
		[2] = 6,
		[3] = 7,
		[4] = 8,
		[5] = 9,
		[6] = 10,
		[7] = 11,
		[8] = 12,
		[9] = 13,
		[10] = 14
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	KnockBackTiles = 3,
	CastTime = {
		[1] = 800,
		[2] = 600,
		[3] = 400,
		[4] = 200,
		[5] = 0,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData1 = 5000,
	FixedCastTime = {
		[1] = 200,
		[2] = 400,
		[3] = 600,
		[4] = 800,
		[5] = 1000,
		[6] = 1200,
		[7] = 1400,
		[8] = 1600,
		[9] = 1800,
		[10] = 2000
	},
	Requirements = {
		SPCost = {
			[1] = 40,
			[2] = 45,
			[3] = 50,
			[4] = 55,
			[5] = 60,
			[6] = 65,
			[7] = 70,
			[8] = 75,
			[9] = 80,
			[10] = 85
		}
	}
},
[ "MH_GOLDENE_FERSE" ] = {
	Id = 8032,
	Description = "Golden Heel",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 1000,
		[2] = 1200,
		[3] = 1400,
		[4] = 1600,
		[5] = 1800,
		[6] = 2000,
		[7] = 2200,
		[8] = 2400,
		[9] = 2600,
		[10] = 2800
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 65,
			[3] = 70,
			[4] = 75,
			[5] = 80,
			[6] = 85,
			[7] = 90,
			[8] = 95,
			[9] = 100,
			[10] = 105
		}
	}
},
[ "MH_STEINWAND" ] = {
	Id = 8033,
	Description = "Stone Wall",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = 1000,
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 80,
			[2] = 90,
			[3] = 100,
			[4] = 110,
			[5] = 120,
			[6] = 130,
			[7] = 140,
			[8] = 150,
			[9] = 160,
			[10] = 170
		}
	},
	Placement = {
		Id = 0x7e,
		Interval = -1,
		Target = "All"
	}
},
[ "MH_HEILIGE_STANGE" ] = {
	Id = 8034,
	Description = "Holy Pole",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Holy,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 1,
		[4] = 1,
		[5] = 2,
		[6] = 2,
		[7] = 2,
		[8] = 2,
		[9] = 2,
		[10] = 2
	},
	CastTime = {
		[1] = 200,
		[2] = 400,
		[3] = 600,
		[4] = 800,
		[5] = 1000,
		[6] = 1200,
		[7] = 1400,
		[8] = 1600,
		[9] = 1800,
		[10] = 2000
	},
	FixedCastTime = {
		[1] = 1800,
		[2] = 1600,
		[3] = 1400,
		[4] = 1200,
		[5] = 1000,
		[6] = 800,
		[7] = 600,
		[8] = 400,
		[9] = 200,
		[10] = 1
	},
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 68,
			[3] = 76,
			[4] = 84,
			[5] = 100,
			[6] = 100,
			[7] = 100,
			[8] = 100,
			[9] = 100,
			[10] = 100
		}
	}
},
[ "MH_ANGRIFFS_MODUS" ] = {
	Id = 8035,
	Description = "Attack Mode",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 200,
		[2] = 400,
		[3] = 600,
		[4] = 800,
		[5] = 1000,
		[6] = 1200,
		[7] = 1400,
		[8] = 1600,
		[9] = 1800,
		[10] = 2000
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	FixedCastTime = -1,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 65,
			[3] = 70,
			[4] = 75,
			[5] = 80,
			[6] = 85,
			[7] = 90,
			[8] = 95,
			[9] = 100,
			[10] = 105
		}
	}
},
[ "MH_TINDER_BREAKER" ] = {
	Id = 8036,
	Description = "Tinder Breaker",
	MaxLevel = 5,
	Range = {
		[1] = 3,
		[2] = 4,
		[3] = 5,
		[4] = 6,
		[5] = 7,
		[6] = 8,
		[7] = 9,
		[8] = 10,
		[9] = 11,
		[10] = 12
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 25,
			[3] = 30,
			[4] = 35,
			[5] = 40,
			[6] = 45,
			[7] = 50,
			[8] = 55,
			[9] = 60,
			[10] = 65
		},
		State = PlayerState.MHEleanorIsGrappling,
		SpiritSphereCost = 1
	}
},
[ "MH_CBC" ] = {
	Id = 8037,
	Description = "Continual Break Combo",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Requirements = {
		SPCost = {
			[1] = 10,
			[2] = 20,
			[3] = 30,
			[4] = 40,
			[5] = 50,
			[6] = 60,
			[7] = 70,
			[8] = 80,
			[9] = 90,
			[10] = 100
		},
		SpiritSphereCost = 1
	}
},
[ "MH_EQC" ] = {
	Id = 8038,
	Description = "Eternal Quick Combo",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.WithoutSelf
	},
	AttackType = AttackType.Weapon,
	Requirements = {
		SPCost = {
			[1] = 24,
			[2] = 28,
			[3] = 32,
			[4] = 36,
			[5] = 40,
			[6] = 44,
			[7] = 48,
			[8] = 52,
			[9] = 56,
			[10] = 60
		},
		SpiritSphereCost = 2
	}
},
[ "MH_MAGMA_FLOW" ] = {
	Id = 8039,
	Description = "Magma Flow",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = {
		[1] = 1,
		[2] = 1,
		[3] = 1,
		[4] = 2,
		[5] = 2,
		[6] = 2,
		[7] = 2,
		[8] = 2,
		[9] = 2,
		[10] = 2
	},
	CastTime = {
		[1] = 2000,
		[2] = 2500,
		[3] = 3000,
		[4] = 3500,
		[5] = 4000,
		[6] = 4500,
		[7] = 5000,
		[8] = 5500,
		[9] = 6000,
		[10] = 6500
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	FixedCastTime = {
		[1] = 2000,
		[2] = 1500,
		[3] = 1000,
		[4] = 500,
		[5] = -1,
		[6] = -1,
		[7] = -1,
		[8] = -1,
		[9] = -1,
		[10] = -1
	},
	Requirements = {
		SPCost = {
			[1] = 34,
			[2] = 38,
			[3] = 42,
			[4] = 46,
			[5] = 50,
			[6] = 54,
			[7] = 58,
			[8] = 62,
			[9] = 66,
			[10] = 70
		}
	}
},
[ "MH_GRANITIC_ARMOR" ] = {
	Id = 8040,
	Description = "Granitic Armor",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 6000,
		[2] = 5500,
		[3] = 5000,
		[4] = 4500,
		[5] = 4000,
		[6] = 3500,
		[7] = 3000,
		[8] = 2500,
		[9] = 2000,
		[10] = 1500
	},
	SkillData1 = 60000,
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 54,
			[2] = 58,
			[3] = 62,
			[4] = 66,
			[5] = 70,
			[6] = 74,
			[7] = 78,
			[8] = 82,
			[9] = 86,
			[10] = 90
		}
	}
},
[ "MH_LAVA_SLIDE" ] = {
	Id = 8041,
	Description = "Lava Slide",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SkillInstances = 1,
	CastTime = {
		[1] = 6000,
		[2] = 5500,
		[3] = 5000,
		[4] = 4500,
		[5] = 4000,
		[6] = 3500,
		[7] = 3000,
		[8] = 2500,
		[9] = 2000,
		[10] = 1500
	},
	SkillData1 = {
		[1] = 12000,
		[2] = 14000,
		[3] = 16000,
		[4] = 18000,
		[5] = 20000,
		[6] = 22000,
		[7] = 24000,
		[8] = 26000,
		[9] = 28000,
		[10] = 30000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 30,
			[2] = 35,
			[3] = 40,
			[4] = 45,
			[5] = 50,
			[6] = 55,
			[7] = 60,
			[8] = 65,
			[9] = 70,
			[10] = 75
		}
	},
	Placement = {
		Id = 0xf6,
		Layout = {
			[1] = 1,
			[2] = 1,
			[3] = 2,
			[4] = 2,
			[5] = 3,
			[6] = 3,
			[7] = 4,
			[8] = 4,
			[9] = 5,
			[10] = 5
		},
		Interval = 2000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "MH_PYROCLASTIC" ] = {
	Id = 8042,
	Description = "Pyroclastic",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	CastTime = {
		[1] = 5000,
		[2] = 4500,
		[3] = 4000,
		[4] = 3500,
		[5] = 3000,
		[6] = 2500,
		[7] = 2000,
		[8] = 1500,
		[9] = 1000,
		[10] = 500
	},
	SkillData1 = {
		[1] = 60000,
		[2] = 90000,
		[3] = 120000,
		[4] = 150000,
		[5] = 180000,
		[6] = 210000,
		[7] = 240000,
		[8] = 270000,
		[9] = 300000,
		[10] = 330000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 28,
			[3] = 36,
			[4] = 44,
			[5] = 52,
			[6] = 60,
			[7] = 68,
			[8] = 76,
			[9] = 84,
			[10] = 92
		}
	}
},
[ "MH_VOLCANIC_ASH" ] = {
	Id = 8043,
	Description = "Volcanic Ash",
	MaxLevel = 5,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillInstances = 3,
	CastTime = {
		[1] = 5000,
		[2] = 4500,
		[3] = 4000,
		[4] = 3500,
		[5] = 3000,
		[6] = 2500,
		[7] = 2000,
		[8] = 1500,
		[9] = 1000,
		[10] = 500
	},
	SkillData1 = {
		[1] = 12000,
		[2] = 14000,
		[3] = 16000,
		[4] = 18000,
		[5] = 20000,
		[6] = 22000,
		[7] = 24000,
		[8] = 26000,
		[9] = 28000,
		[10] = 30000
	},
	FixedCastTime = 1000,
	Requirements = {
		SPCost = {
			[1] = 60,
			[2] = 65,
			[3] = 70,
			[4] = 75,
			[5] = 80,
			[6] = 85,
			[7] = 90,
			[8] = 95,
			[9] = 100,
			[10] = 105
		}
	},
	Placement = {
		Id = 0xf7,
		Layout = 1,
		Interval = -1,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath
		}
	}
},
[ "MS_BASH" ] = {
	Id = 8201,
	Description = "Bash",
	MaxLevel = 10,
	Range = -1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	Requirements = {
		SPCost = {
			[1] = 8,
			[2] = 8,
			[3] = 8,
			[4] = 8,
			[5] = 8,
			[6] = 15,
			[7] = 15,
			[8] = 15,
			[9] = 15,
			[10] = 15
		},
		WeaponTypes = {
			WeaponType.Fist,
			WeaponType.Dagger,
			WeaponType.OneHandedSword,
			WeaponType.TwoHandedSword,
			WeaponType.OneHandedSpear,
			WeaponType.TwoHandedSpear,
			WeaponType.OneHandedAxe,
			WeaponType.TwoHandedAxe,
			WeaponType.OneHandedMace,
			WeaponType.TwoHandedMace,
			WeaponType.OneHandedStaff,
			WeaponType.Knuckle,
			WeaponType.MusicalInstrument,
			WeaponType.Whip,
			WeaponType.Book,
			WeaponType.Katar,
			WeaponType.Revolver,
			WeaponType.Rifle,
			WeaponType.GatlingGun,
			WeaponType.Shotgun,
			WeaponType.GrenadeLauncher,
			WeaponType.FuumaShuriken
		}
	}
},
[ "MS_MAGNUM" ] = {
	Id = 8202,
	Description = "Magnum_Break",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	KnockBackTiles = 2,
	AfterCastActDelay = 1500,
	AfterCastWalkDelay = 2000,
	SkillData1 = 2000,
	SkillData2 = 10000,
	FixedCastTime = 0,
	Requirements = {
		HPCost = {
			[1] = 20,
			[2] = 20,
			[3] = 19,
			[4] = 19,
			[5] = 18,
			[6] = 18,
			[7] = 17,
			[8] = 17,
			[9] = 16,
			[10] = 16
		},
		SPCost = 30
	}
},
[ "MS_BOWLINGBASH" ] = {
	Id = 8203,
	Description = "Bowling_Bash",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 1,
	KnockBackTiles = 1,
	CastTime = 700,
	AfterCastActDelay = 2500,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 13,
			[2] = 14,
			[3] = 15,
			[4] = 16,
			[5] = 17,
			[6] = 18,
			[7] = 19,
			[8] = 20,
			[9] = 21,
			[10] = 22
		}
	}
},
[ "MS_PARRYING" ] = {
	Id = 8204,
	Description = "Parry",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 15000,
		[2] = 20000,
		[3] = 25000,
		[4] = 30000,
		[5] = 35000,
		[6] = 40000,
		[7] = 45000,
		[8] = 50000,
		[9] = 55000,
		[10] = 60000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 50
	}
},
[ "MS_REFLECTSHIELD" ] = {
	Id = 8205,
	Description = "Shield_Reflect",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	SkillData1 = 300000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 35,
			[2] = 40,
			[3] = 45,
			[4] = 50,
			[5] = 55,
			[6] = 60,
			[7] = 65,
			[8] = 70,
			[9] = 75,
			[10] = 80
		}
	}
},
[ "MS_BERSERK" ] = {
	Id = 8206,
	Description = "Frenzy",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 300000,
	SkillData2 = 15000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 100
	}
},
[ "MA_DOUBLE" ] = {
	Id = 8207,
	Description = "Double_Strafe",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 2,
	AfterCastActDelay = 1000,
	SkillData1 = 100,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 12,
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	}
},
[ "MA_SHOWER" ] = {
	Id = 8208,
	Description = "Arrow_Shower",
	MaxLevel = 10,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.IgnoreLandProtector,
		SkillBehavior.IgnoreTargetSkills
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	KnockBackTiles = 2,
	AfterCastActDelay = 1200,
	SkillData1 = 100,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 15,
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	},
	Placement = {
		Id = 0x86,
		Range = 2,
		Interval = 1000,
		Target = "Enemy"
	}
},
[ "MA_SKIDTRAP" ] = {
	Id = 8209,
	Description = "Skid_Trap",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	KnockBackTiles = {
		[1] = 6,
		[2] = 7,
		[3] = 8,
		[4] = 9,
		[5] = 10,
		[6] = 11,
		[7] = 12,
		[8] = 13,
		[9] = 14,
		[10] = 15
	},
	SkillData1 = {
		[1] = 300000,
		[2] = 240000,
		[3] = 180000,
		[4] = 120000,
		[5] = 60000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	},
	Placement = {
		Id = 0x90,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "MA_LANDMINE" ] = {
	Id = 8210,
	Description = "Land_Mine",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	Element = Element.Earth,
	DamageBehavior = {
		DamageBehavior.IgnoreFlee
	},
	SkillData1 = {
		[1] = 200000,
		[2] = 160000,
		[3] = 120000,
		[4] = 80000,
		[5] = 40000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData2 = 5000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	},
	Placement = {
		Id = 0x93,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "MA_SANDMAN" ] = {
	Id = 8211,
	Description = "Sandman",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 2,
	SkillData1 = {
		[1] = 150000,
		[2] = 120000,
		[3] = 90000,
		[4] = 60000,
		[5] = 30000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData2 = {
		[1] = 12000,
		[2] = 14000,
		[3] = 16000,
		[4] = 18000,
		[5] = 20000,
		[6] = 22000,
		[7] = 24000,
		[8] = 26000,
		[9] = 28000,
		[10] = 30000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 12
	},
	Placement = {
		Id = 0x95,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "MA_FREEZINGTRAP" ] = {
	Id = 8212,
	Description = "Freezing_Trap",
	MaxLevel = 5,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnPlace,
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Weapon,
	Element = Element.Water,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect,
		DamageBehavior.IgnoreFlee
	},
	SplashRange = 1,
	SkillData1 = {
		[1] = 150000,
		[2] = 120000,
		[3] = 90000,
		[4] = 60000,
		[5] = 30000,
		[6] = 1,
		[7] = 1,
		[8] = 1,
		[9] = 1,
		[10] = 1
	},
	SkillData2 = {
		[1] = 3000,
		[2] = 6000,
		[3] = 9000,
		[4] = 12000,
		[5] = 15000,
		[6] = 18000,
		[7] = 21000,
		[8] = 24000,
		[9] = 27000,
		[10] = 30000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	},
	Placement = {
		Id = 0x97,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.AllowPlacementOnTarget
		}
	}
},
[ "MA_REMOVETRAP" ] = {
	Id = 8213,
	Description = "Remove_Trap",
	MaxLevel = 1,
	Range = 2,
	Hit = "BDT_SKILL",
	SkillType = {
		SkillBehavior.TrapSkill
	},
	AttackType = AttackType.Misc,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 5
	}
},
[ "MA_CHARGEARROW" ] = {
	Id = 8214,
	Description = "Arrow_Repel",
	MaxLevel = 1,
	Range: -9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy,
		SkillBehavior.LearntFromQuest
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.AreaOfEffect
	},
	KnockBackTiles = 6,
	CastTime = 750,
	AfterCastActDelay = 1000,
	FixedCastTime = 750,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = 15,
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	}
},
[ "MA_SHARPSHOOTING" ] = {
	Id = 8215,
	Description = "Focused_Arrow_Strike",
	MaxLevel = 5,
	Range = 9,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	SplashRange = 2,
	InterruptCast = true,
	SkillInstances = 13,
	CastTime = 1000,
	AfterCastActDelay = 2500,
	FixedCastTime = 1000,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 21,
			[3] = 24,
			[4] = 27,
			[5] = 30,
			[6] = 33,
			[7] = 36,
			[8] = 39,
			[9] = 42,
			[10] = 45
		},
		AmmoTypes = {
			AmmoType.Arrow
		},
		AmmoAmount = 1
	}
},
[ "ML_PIERCE" ] = {
	Id = 8216,
	Description = "Pierce",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 3,
	Requirements = {
		SPCost = 7
	}
},
[ "ML_BRANDISH" ] = {
	Id = 8217,
	Description = "Brandish_Spear",
	MaxLevel = 10,
	Range: -2,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	KnockBackTiles = 3,
	CastTime = 350,
	AfterCastActDelay = 1200,
	FixedCastTime = 350,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = 12
	}
},
[ "ML_SPIRALPIERCE" ] = {
	Id = 8218,
	Description = "Spiral_Pierce",
	MaxLevel = 5,
	Range = 5,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	DamageBehavior = {
		DamageBehavior.Ignore_Soft_Def
	},
	NumberOfHits = 5,
	CastTime = {
		[1] = 150,
		[2] = 250,
		[3] = 350,
		[4] = 450,
		[5] = 500,
		[6] = 500,
		[7] = 500,
		[8] = 500,
		[9] = 500,
		[10] = 500
	},
	AfterCastActDelay = 2500,
	SkillData2 = 1000,
	FixedCastTime = {
		[1] = 150,
		[2] = 250,
		[3] = 350,
		[4] = 450,
		[5] = 500,
		[6] = 500,
		[7] = 500,
		[8] = 500,
		[9] = 500,
		[10] = 500
	},
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = {
			[1] = 18,
			[2] = 21,
			[3] = 24,
			[4] = 27,
			[5] = 30,
			[6] = 33,
			[7] = 36,
			[8] = 39,
			[9] = 42,
			[10] = 45
		}
	}
},
[ "ML_DEFENDER" ] = {
	Id = 8219,
	Description = "Defending_Aura",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	AfterCastActDelay = 800,
	SkillData1 = 180000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 30,
		State = PlayerState.Equipped_Shield
	}
},
[ "ML_AUTOGUARD" ] = {
	Id = 8220,
	Description = "Guard",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 300000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 12,
			[2] = 14,
			[3] = 16,
			[4] = 18,
			[5] = 20,
			[6] = 22,
			[7] = 24,
			[8] = 26,
			[9] = 28,
			[10] = 30
		}
	}
},
[ "ML_DEVOTION" ] = {
	Id = 8221,
	Description = "Sacrifice",
	MaxLevel = 5,
	Range = {
		[1] = 7,
		[2] = 8,
		[3] = 9,
		[4] = 10,
		[5] = 11,
		[6] = 12,
		[7] = 13,
		[8] = 14,
		[9] = 15,
		[10] = 16
	},
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		SkillBehavior.WithoutSelf,
		SkillBehavior.OnlyParty
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1500,
	SkillData2 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	FixedCastTime = 1500,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = 25
	}
},
[ "MER_MAGNIFICAT" ] = {
	Id = 8222,
	Description = "Magnificat",
	MaxLevel = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = -1,
	InterruptCast = true,
	CastTime = 3200,
	AfterCastActDelay = 2000,
	SkillData1 = {
		[1] = 30000,
		[2] = 45000,
		[3] = 60000,
		[4] = 75000,
		[5] = 90000,
		[6] = 105000,
		[7] = 120000,
		[8] = 135000,
		[9] = 150000,
		[10] = 165000
	},
	FixedCastTime = 800,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = 40
	}
},
{
	Id = 8223,
	Name = "MER_QUICKEN",
	Description = "Two-Hand_Quicken",
	MaxLevel = 10,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = {
		[1] = 30000,
		[2] = 60000,
		[3] = 90000,
		[4] = 120000,
		[5] = 150000,
		[6] = 180000,
		[7] = 210000,
		[8] = 240000,
		[9] = 270000,
		[10] = 300000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 14,
			[2] = 18,
			[3] = 22,
			[4] = 26,
			[5] = 30,
			[6] = 34,
			[7] = 38,
			[8] = 42,
			[9] = 46,
			[10] = 50
		}
	}
},
[ "MER_SIGHT" ] = {
	Id = 8224,
	Description = "Sight",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 3,
	InterruptCast = true,
	SkillData1 = 10000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = 10
	}
},
[ "MER_CRASH" ] = {
	Id = 8225,
	Description = "Crash",
	MaxLevel = 5,
	Range = 1,
	Hit = "BDT_MULTIHIT",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.WeaponElement,
	NumberOfHits = 3,
	CastTime = 1000,
	AfterCastActDelay = 2000,
	SkillData2 = 5000,
	FixedCastTime = 0,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = 10
	}
},
[ "MER_REGAIN" ] = {
	Id = 8226,
	Description = "Regain",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		NoEnemy = true
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 10
	}
},
[ "MER_TENDER" ] = {
	Id = 8227,
	Description = "Tender",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		NoEnemy = true
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 10
	}
},
[ "MER_BENEDICTION" ] = {
	Id = 8228,
	Description = "Benediction",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		NoEnemy = true
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 10
	}
},
[ "MER_RECUPERATE" ] = {
	Id = 8229,
	Description = "Recuperate",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		NoEnemy = true
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 10
	}
},
[ "MER_MENTALCURE" ] = {
	Id = 8230,
	Description = "Mental_Cure",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		NoEnemy = true
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 10
	}
},
[ "MER_COMPRESS" ] = {
	Id = 8231,
	Description = "Compress",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend,
		NoEnemy = true
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 10
	}
},
[ "MER_PROVOKE" ] = {
	Id = 8232,
	Description = "Provoke",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 30000,
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 4,
			[2] = 5,
			[3] = 6,
			[4] = 7,
			[5] = 8,
			[6] = 9,
			[7] = 10,
			[8] = 11,
			[9] = 12,
			[10] = 13
		}
	}
},
[ "MER_AUTOBERSERK" ] = {
	Id = 8233,
	Description = "Berserk",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 5
	}
},
[ "MER_DECAGI" ] = {
	Id = 8234,
	Description = "Decrease_AGI",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 800,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 40000,
		[2] = 50000,
		[3] = 60000,
		[4] = 70000,
		[5] = 80000,
		[6] = 90000,
		[7] = 100000,
		[8] = 110000,
		[9] = 120000,
		[10] = 130000
	},
	FixedCastTime = 200,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = {
			[1] = 15,
			[2] = 17,
			[3] = 19,
			[4] = 21,
			[5] = 23,
			[6] = 25,
			[7] = 27,
			[8] = 29,
			[9] = 31,
			[10] = 33
		}
	}
},
[ "MER_SCAPEGOAT" ] = {
	Id = 8235,
	Description = "Scapegoat",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 3000,
	FixedCastTime = 0,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = 10,
		HPRateCost = 100
	}
},
[ "MER_LEXDIVINA" ] = {
	Id = 8236,
	Description = "Lex_Divina",
	MaxLevel = 10,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	NumberOfHits = 0,
	InterruptCast = true,
	AfterCastActDelay = 3000,
	SkillData1 = {
		[1] = 30000,
		[2] = 35000,
		[3] = 40000,
		[4] = 45000,
		[5] = 50000,
		[6] = 60000,
		[7] = 60000,
		[8] = 60000,
		[9] = 60000,
		[10] = 60000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 20,
			[3] = 20,
			[4] = 20,
			[5] = 20,
			[6] = 18,
			[7] = 16,
			[8] = 14,
			[9] = 12,
			[10] = 10
		}
	}
},
[ "MER_ESTIMATION" ] = {
	Id = 8237,
	Description = "Sense",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	Requirements = {
		SPCost = 10
	}
},
[ "MER_KYRIE" ] = {
	Id = 8238,
	Description = "Kyrie Eleison",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 2000,
	AfterCastActDelay = 2000,
	SkillData1 = 120000,
	FixedCastTime = 0,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = {
			[1] = 20,
			[2] = 20,
			[3] = 20,
			[4] = 25,
			[5] = 25,
			[6] = 25,
			[7] = 30,
			[8] = 30,
			[9] = 30,
			[10] = 35
		}
	}
},
[ "MER_BLESSING" ] = {
	Id = 8239,
	Description = "Blessing",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	SkillData1 = {
		[1] = 60000,
		[2] = 80000,
		[3] = 100000,
		[4] = 120000,
		[5] = 140000,
		[6] = 160000,
		[7] = 180000,
		[8] = 200000,
		[9] = 220000,
		[10] = 240000
	},
	FixedCastTime = 0,
	Requirements = {
		SPCost = {
			[1] = 28,
			[2] = 32,
			[3] = 36,
			[4] = 40,
			[5] = 44,
			[6] = 48,
			[7] = 52,
			[8] = 56,
			[9] = 60,
			[10] = 64
		}
	}
},
[ "MER_INCAGI" ] = {
	Id = 8240,
	Description = "Increase Agility",
	MaxLevel = 10,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnFriend
	},
	AttackType = AttackType.Magic,
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	InterruptCast = true,
	CastTime = 1000,
	AfterCastActDelay = 1000,
	SkillData1 = {
		[1] = 60000,
		[2] = 80000,
		[3] = 100000,
		[4] = 120000,
		[5] = 140000,
		[6] = 160000,
		[7] = 180000,
		[8] = 200000,
		[9] = 220000,
		[10] = 240000
	},
	FixedCastTime = 0,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		HPCost = 15,
		SPCost = {
			[1] = 18,
			[2] = 21,
			[3] = 24,
			[4] = 27,
			[5] = 30,
			[6] = 33,
			[7] = 36,
			[8] = 39,
			[9] = 42,
			[10] = 45
		}
	}
},
[ "EL_CIRCLE_OF_FIRE" ] = {
	Id = 8401,
	Description = "Circle of Fire",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire,
	KnockBackTiles = 2,
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 40
	}
},
[ "EL_FIRE_CLOAK" ] = {
	Id = 8402,
	Description = "Fire Cloak",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 60
	}
},
[ "EL_FIRE_MANTLE" ] = {
	Id = 8403,
	Description = "Fire Mantle",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	SkillInstances = 3,
	KnockBackTiles = 2,
	SkillData1 = 15000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 80
	},
	Placement = {
		Id = 0xed,
		Layout = -1,
		Range = 1,
		Interval = 1000,
		Target = "Enemy",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath,
		}
	}
},
[ "EL_WATER_SCREEN" ] = {
	Id = 8404,
	Description = "Water Screen",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 40
	}
},
[ "EL_WATER_DROP" ] = {
	Id = 8405,
	Description = "Water Drop",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 60
	}
},
[ "EL_WATER_BARRIER" ] = {
	Id = 8406,
	Description = "Water Barrier",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 15000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 80
	},
	Placement = {
		Id = 0xee,
		Layout = 1,
		Interval = -1,
		Target = "Friend",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath
		}
	}
},
[ "EL_WIND_STEP" ] = {
	Id = 8407,
	Description = "Wind Step",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	KnockBackTiles = 5,
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 40
	}
},
[ "EL_WIND_CURTAIN" ] = {
	Id = 8408,
	Description = "Wind Curtain",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 60
	}
},
[ "EL_ZEPHYR" ] = {
	Id = 8409,
	Description = "Zephyr",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 15000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 80
	},
	Placement = {
		Id = 0xef,
		Range = 1,
		Interval = -1,
		Target = "Friend",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath
		}
	}
},
[ "EL_SOLID_SKIN" ] = {
	Id = 8410,
	Description = "Solid Skin",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	Requirements = {
		SPCost = 40
	}
},
[ "EL_STONE_SHIELD" ] = {
	Id = 8411,
	Description = "Stone Shield",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 60
	}
},
[ "EL_POWER_OF_GAIA" ] = {
	Id = 8412,
	Description = "Power of Gaia",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = 15000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 80
	},
	Placement = {
		Id = 0xf0,
		Range = 1,
		Interval = -1,
		Target = "Friend",
		Behavior = {
			PlacementBehavior.CannotOverlap,
			PlacementBehavior.CheckObstructionInPath
		}
	}
},
[ "EL_PYROTECHNIC" ] = {
	Id = 8413,
	Description = "Pyrotechnic",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_HEATER" ] = {
	Id = 8414,
	Description = "Heater",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_TROPIC" ] = {
	Id = 8415,
	Description = "Tropic",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_AQUAPLAY" ] = {
	Id = 8416,
	Description = "Aqua Play",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_COOLER" ] = {
	Id = 8417,
	Description = "Cooler",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_CHILLY_AIR" ] = {
	Id = 8418,
	Description = "Cool Air",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_GUST" ] = {
	Id = 8419,
	Description = "Gust",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_BLAST" ] = {
	Id = 8420,
	Description = "Blast",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_WILD_STORM" ] = {
	Id = 8421,
	Description = "Wild Storm",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_PETROLOGY" ] = {
	Id = 8422,
	Description = "Petrology",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_CURSED_SOIL" ] = {
	Id = 8423,
	Description = "Cursed Soil",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_UPHEAVAL" ] = {
	Id = 8424,
	Description = "Upheaval",
	MaxLevel = 1,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnSelf
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive
	},
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_FIRE_ARROW" ] = {
	Id = 8425,
	Description = "Fire Arrow",
	MaxLevel = 1,
	Range = 6,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	Requirements = {
		SPCost = 40
	}
},
[ "EL_FIRE_BOMB" ] = {
	Id = 8426,
	Description = "Fire Bomb",
	MaxLevel = 1,
	Range = 6,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	SplashRange = 1,
	Requirements = {
		SPCost = 60
	}
},
[ "EL_FIRE_BOMB_ATK" ] = {
	Id = 8427,
	Description = "Fire Bomb Attack",
	MaxLevel = 1,
	Range = 6,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire,
	SplashRange = 1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_FIRE_WAVE" ] = {
	Id = 8428,
	Description = "Fire Wave",
	MaxLevel = 1,
	Range = 6,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Fire,
	SplashRange = 1,
	Requirements = {
		SPCost = 80
	}
},
[ "EL_FIRE_WAVE_ATK" ] = {
	Id = 8429,
	Description = "Fire Wave Attack",
	MaxLevel = 1,
	Range = 6,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Fire,
	SplashRange = 1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_ICE_NEEDLE" ] = {
	Id = 8430,
	Description = "Ice Needle",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	Requirements = {
		SPCost = 40
	}
},
[ "EL_WATER_SCREW" ] = {
	Id = 8431,
	Description = "Water Screw",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Water,
	SplashRange = 1,
	Requirements = {
		SPCost = 60
	}
},
[ "EL_WATER_SCREW_ATK" ] = {
	Id = 8432,
	Description = "Water Screw Attack",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Water,
	SplashRange = 1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_TIDAL_WEAPON" ] = {
	Id = 8433,
	Description = "Tidal Weapon",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Water,
	SplashRange = 1,
	SkillData1 = -1,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 80
	}
},
[ "EL_WIND_SLASH" ] = {
	Id = 8434,
	Description = "Wind Slasher",
	MaxLevel = 1,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Wind,
	CastTime = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 40
	}
},
[ "EL_HURRICANE" ] = {
	Id = 8435,
	Description = "Hurricane Rage",
	MaxLevel = 1,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Wind,
	SplashRange = 1,
	CastTime = 1000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 60
	}
},
[ "EL_HURRICANE_ATK" ] = {
	Id = 8436,
	Description = "Hurricane Rage Attack",
	MaxLevel = 1,
	Range = 7,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_TYPOON_MIS" ] = {
	Id = 8437,
	Description = "Typhoon Missile",
	MaxLevel = 1,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Wind,
	SplashRange = 1,
	CastTime = 1000,
	SkillData1 = 15000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 80
	}
},
[ "EL_TYPOON_MIS_ATK" ] = {
	Id = 8438,
	Description = "Typhoon Missile Attack",
	MaxLevel = 1,
	Range = 11,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Wind,
	SplashRange = 1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_STONE_HAMMER" ] = {
	Id = 8439,
	Description = "Stone Hammer",
	MaxLevel = 1,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Earth,
	SkillData1 = 5000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 40
	}
},
[ "EL_ROCK_CRUSHER" ] = {
	Id = 8440,
	Description = "Rock Launcher",
	MaxLevel = 1,
	Range = 3,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Earth,
	SplashRange = 1,
	SkillData1 = 15000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 60
	}
},
[ "EL_ROCK_CRUSHER_ATK" ] = {
	Id = 8441,
	Description = "Rock Launcher Attack",
	MaxLevel = 1,
	Range = 5,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Magic,
	Element = Element.Earth,
	SplashRange = 1,
	SkillData1 = 15000,
	FixedCastTime = -1,
	Requirements = {
		SPCost = 1
	}
},
[ "EL_STONE_RAIN" ] = {
	Id = 8442,
	Description = "Stone Rain",
	MaxLevel = 1,
	Range = 9,
	Hit = "BDT_SKILL",
	Behavior = {
		SkillBehavior.UseOnEnemy
	},
	AttackType = AttackType.Weapon,
	Element = Element.Earth,
	SplashRange = 1,
	NumberOfHits: -5,
	Requirements = {
		SPCost = 80
	}
},
[ "GD_APPROVAL" ] = {
	Id = 10000,
	Description = "Official Guild Approval",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.GuildSkill
	},
	NumberOfHits = 0
},
[ "GD_KAFRACONTRACT" ] = {
	Id = 10001,
	Description = "Kafra Contract",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.GuildSkill
	},
	NumberOfHits = 0
},
[ "GD_GUARDRESEARCH" ] = {
	Id = 10002,
	Description = "Guardian Research",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.GuildSkill
	},
	NumberOfHits = 0
},
[ "GD_GUARDUP" ] = {
	Id = 10003,
	Description = "Strengthen Guardians",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.GuildSkill
	},
	NumberOfHits = 0
},
[ "GD_EXTENSION" ] = {
	Id = 10004,
	Description = "Guild Extension",
	MaxLevel = 10,
	SkillInfo = {
		SkillBehavior.GuildSkill
	},
	NumberOfHits = 0
},
{
	Id = 10005,
	Name = "GD_GLORYGUILD",
	Description = "Guild's Glory",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.GuildSkill,
		SkillBehavior.IgnoreTargetMobs
	},
	NumberOfHits = 0
},
[ "GD_LEADERSHIP" ] = {
	Id = 10006,
	Description = "Great Leadership",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.GuildSkill
	},
	SplashRange = 2,
	NumberOfHits = 0,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Placement = {
		Id = 0xc1,
		Layout = 2,
		Interval = -1,
		Target = "Sameguild"
	}
},
[ "GD_GLORYWOUNDS" ] = {
	Id = 10007,
	Description = "Glorious Wounds",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.GuildSkill,
		SkillBehavior.IgnoreTargetMobs
	},
	SplashRange = 2,
	NumberOfHits = 0,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Placement = {
		Id = 0xc2,
		Layout = 2,
		Interval = -1,
		Target = "Sameguild",
	}
},
[ "GD_SOULCOLD" ] = {
	Id = 10008,
	Description = "Cold Heart",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.GuildSkill,
		SkillBehavior.IgnoreTargetMobs
	},
	SplashRange = 2,
	NumberOfHits = 0,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Placement = {
		Id = 0xc3,
		Layout = 2,
		Interval = -1,
		Target = "Sameguild"
	}
},
[ "GD_HAWKEYES" ] = {
	Id = 10009,
	Description = "Sharp Gaze",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.GuildSkill,
		SkillBehavior.IgnoreTargetMobs
	},
	SplashRange = 2,
	NumberOfHits = 0,
	SkillData1 = 300000,
	FixedCastTime = -1,
	Placement = {
		Id = 0xc4,
		Layout = 2,
		Interval = -1,
		Target = "Sameguild"
	}
},
[ "GD_BATTLEORDER" ] = {
	Id = 10010,
	Description = "Battle Orders",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.GuildSkill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 15,
	NumberOfHits = 0,
	InterruptCast = true,
	SkillData1 = 180000,
	SkillData2 = 300000,
	FixedCastTime = -1,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffects
	},
	Requirements = {
		SPCost = 1
	}
},
[ "GD_REGENERATION" ] = {
	Id = 10011,
	Description = "Regeneration",
	MaxLevel = 3,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.GuildSkill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 15,
	NumberOfHits = 0,
	InterruptCast = true,
	SkillData1 = 60000,
	SkillData2 = 300000,
	FixedCastTime = -1,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffects
	},
	Requirements = {
		SPCost = 1
	}
},
[ "GD_RESTORE" ] = {
	Id = 10012,
	Description = "Restoration",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.GuildSkill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	SplashRange = 15,
	NumberOfHits = 0,
	InterruptCast = true,
	SkillData2 = 300000,
	FixedCastTime = 10000,
	CastTimeOptions = {
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = 1
	}
},
[ "GD_EMERGENCYCALL" ] = {
	Id = 10013,
	Description = "Urgent Call",
	MaxLevel = 1,
	Behavior = {
		SkillBehavior.UseOnSelf,
		SkillBehavior.GuildSkill
	},
	DamageBehavior = {
		DamageBehavior.NonOffensive,
		DamageBehavior.AreaOfEffect
	},
	NumberOfHits = 0,
	InterruptCast = true,
	SkillData2 = 300000,
	FixedCastTime = 5000,
	CastTimeOptions = {
		CastTimeOptions.IgnoreDex,
		CastTimeOptions.IgnoreStatusEffect,
		CastTimeOptions.IgnoreItemBonus
	},
	Requirements = {
		SPCost = 1
	}
},
[ "GD_DEVELOPMENT" ] = {
	Id = 10014,
	Description = "Permanent Development",
	MaxLevel = 1,
	SkillInfo = {
		SkillBehavior.GuildSkill
	},
	NumberOfHits = 0
}
}
