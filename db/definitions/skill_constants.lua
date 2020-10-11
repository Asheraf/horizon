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
--- Skill Constants Database
---------------------------------------------------------------------------
--- This is a database consisting of variables that could be used in skill
--- and battle functionality.
---------------------------------------------------------------------------

SkillBehavior = {
	Passive                 = 0x000000,
	Use_On_Enemy            = 0x000001,
	Use_On_Place            = 0x000002,
	Use_On_Self             = 0x000004,
	Use_On_Friend           = 0x000008,
	Learnt_From_Quest       = 0x000010,
	Learnt_From_NPC         = 0x000020,
	Learnt_From_Wedding     = 0x000040,
	Learnt_From_Buff        = 0x000080,
	Guild_Skill             = 0x000100,
	Song_Dance_Skill        = 0x000200,
	Ensemble_Skill          = 0x000400,
	Set_Trap                = 0x000800,
	Without_Self            = 0x001000,
	PartyOnly               = 0x002000,
	GuildOnly               = 0x004000,
	NoEnemy                 = 0x008000,
	Ignore_Land_Protector   = 0x010000,
	Requires_Partner        = 0x020000,
	Show_Skill_Scale        = 0x040000,
	Allow_Replicate         = 0x080000,
	Ignore_Target_Players   = 0x100000,
	Ignore_Target_Mobs      = 0x200000,
	Ignore_Target_Skills    = 0x400000,
}

SkillDelayOptions = {
	IgnoreDex               = 0x1,
	IgnoreStatusEffect      = 0x2,
	IgnoreItemBonus         = 0x4
}

CastTimeOptions = {
	IgnoreDex               = 0x1,
	IgnoreStatusEffect      = 0x2,
	IgnoreItemBonus         = 0x4
}
