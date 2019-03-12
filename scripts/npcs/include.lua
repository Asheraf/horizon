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
--- Include NPC Definitions File.
---------------------------------------------------------------------------

definitions = {
	-- Warps
	"scripts/npcs/warps/pvp.lua",
	"scripts/npcs/warps/guildcastles.lua",
	-- Warps: Cities
	"scripts/npcs/warps/cities/ayothaya.lua",
	"scripts/npcs/warps/cities/alberta.lua",
	"scripts/npcs/warps/cities/aldebaran.lua",
	"scripts/npcs/warps/cities/amatsu.lua",
	"scripts/npcs/warps/cities/comodo.lua",
	"scripts/npcs/warps/cities/einbech.lua",
	"scripts/npcs/warps/cities/einbroch.lua",
	"scripts/npcs/warps/cities/geffen.lua",
	"scripts/npcs/warps/cities/gonryun.lua",
	"scripts/npcs/warps/cities/hugel.lua",
	"scripts/npcs/warps/cities/lighthalzen.lua",
	"scripts/npcs/warps/cities/louyang.lua",
	"scripts/npcs/warps/cities/lutie.lua",
	"scripts/npcs/warps/cities/manuk.lua",
	"scripts/npcs/warps/cities/mid_camp.lua",
	"scripts/npcs/warps/cities/morroc.lua",
	"scripts/npcs/warps/cities/moscovia.lua",
	"scripts/npcs/warps/cities/nameless.lua",
	"scripts/npcs/warps/cities/niflheim.lua",
	"scripts/npcs/warps/cities/payon.lua",
	"scripts/npcs/warps/cities/prontera.lua",
	"scripts/npcs/warps/cities/splendide.lua",
	"scripts/npcs/warps/cities/umbala.lua",
	"scripts/npcs/warps/cities/veins.lua",
	"scripts/npcs/warps/cities/yuno.lua",
	-- Warps: Dungeons
	"scripts/npcs/warps/dungeons/ama_dun.lua",
	"scripts/npcs/warps/dungeons/abbey.lua",
	"scripts/npcs/warps/dungeons/abyss.lua",
	"scripts/npcs/warps/dungeons/alde_dun.lua",
	"scripts/npcs/warps/dungeons/anthell.lua",
	"scripts/npcs/warps/dungeons/ayo_dun.lua",
	"scripts/npcs/warps/dungeons/beach_dun.lua",
	"scripts/npcs/warps/dungeons/c_tower.lua",
	"scripts/npcs/warps/dungeons/ein_dun.lua",
	"scripts/npcs/warps/dungeons/gef_dun.lua",
	"scripts/npcs/warps/dungeons/gon_dun.lua",
	"scripts/npcs/warps/dungeons/ice_dun.lua",
	"scripts/npcs/warps/dungeons/in_sphinx.lua",
	"scripts/npcs/warps/dungeons/iz_dun.lua",
	"scripts/npcs/warps/dungeons/juperos.lua",
	"scripts/npcs/warps/dungeons/kh_dun.lua",
	"scripts/npcs/warps/dungeons/lhz_dun.lua",
	"scripts/npcs/warps/dungeons/lou_dun.lua",
	"scripts/npcs/warps/dungeons/mag_dun.lua",
	"scripts/npcs/warps/dungeons/mjo_dun.lua",
	"scripts/npcs/warps/dungeons/moc_pryd.lua",
	"scripts/npcs/warps/dungeons/mosk_dun.lua",
	"scripts/npcs/warps/dungeons/odin.lua",
	"scripts/npcs/warps/dungeons/orcsdun.lua",
	"scripts/npcs/warps/dungeons/pay_dun.lua",
	"scripts/npcs/warps/dungeons/prt_maze.lua",
	"scripts/npcs/warps/dungeons/ra_san.lua",
	"scripts/npcs/warps/dungeons/tha_t.lua",
	"scripts/npcs/warps/dungeons/thor_v.lua",
	"scripts/npcs/warps/dungeons/treasure.lua",
	"scripts/npcs/warps/dungeons/tur_dun.lua",
	"scripts/npcs/warps/dungeons/um_dun.lua",
	"scripts/npcs/warps/dungeons/xmas_dun.lua",
	-- Warps: Fields
	"scripts/npcs/warps/fields/glastheim.lua",
	"scripts/npcs/warps/fields/amatsu_fild.lua",
	"scripts/npcs/warps/fields/ein_fild.lua",
	"scripts/npcs/warps/fields/gefenia.lua",
	"scripts/npcs/warps/fields/jawaii.lua",
	"scripts/npcs/warps/fields/lhalzen_fild.lua",
	"scripts/npcs/warps/fields/lutie_fild.lua",
	"scripts/npcs/warps/fields/man_fild.lua",
	"scripts/npcs/warps/fields/mtmjolnir.lua",
	"scripts/npcs/warps/fields/spl_fild.lua",
	"scripts/npcs/warps/fields/umbala_fild.lua",
	-- Warps: Other
	"scripts/npcs/warps/other/kiel.lua",
	"scripts/npcs/warps/other/god.lua",
	"scripts/npcs/warps/other/jobquests.lua",
	"scripts/npcs/warps/other/arena.lua",
	"scripts/npcs/warps/other/airplane.lua",
	-- Warps: Renewal
	"scripts/npcs/re/warps/guildcastles.lua",
	-- Warps: Renewal: Cities
	"scripts/npcs/re/warps/cities/yggdrasil.lua",
	"scripts/npcs/re/warps/cities/rachel.lua",
	"scripts/npcs/re/warps/cities/malaya.lua",
	"scripts/npcs/re/warps/cities/malangdo.lua",
	"scripts/npcs/re/warps/cities/izlude.lua",
	"scripts/npcs/re/warps/cities/eclage.lua",
	"scripts/npcs/re/warps/cities/dicastes.lua",
	"scripts/npcs/re/warps/cities/dewata.lua",
	"scripts/npcs/re/warps/cities/brasilis.lua",
	-- Warps: Renewal: Dungeons
	"scripts/npcs/re/warps/dungeons/moc_pryd.lua",
	"scripts/npcs/re/warps/dungeons/ecl_dun.lua",
	"scripts/npcs/re/warps/dungeons/dic_dun.lua",
	"scripts/npcs/re/warps/dungeons/bra_dun.lua",
	-- Warps: Renewal: Fields
	"scripts/npcs/re/warps/fields/yuno_fild.lua",
	"scripts/npcs/re/warps/fields/veins_fild.lua",
	"scripts/npcs/re/warps/fields/rachel_fild.lua",
	"scripts/npcs/re/warps/fields/payon_fild.lua",
	"scripts/npcs/re/warps/fields/prontera_fild.lua",
	"scripts/npcs/re/warps/fields/hugel_fild.lua",
	"scripts/npcs/re/warps/fields/morroc_fild.lua",
	"scripts/npcs/re/warps/fields/dic_fild.lua",
	"scripts/npcs/re/warps/fields/geffen_fild.lua",
	"scripts/npcs/re/warps/fields/com_fild.lua",
	"scripts/npcs/re/warps/fields/bra_fild.lua",
	"scripts/npcs/re/warps/fields/bif_fild.lua",
	-- Warps: Renewal: Other
	"scripts/npcs/re/warps/other/sign.lua",
	"scripts/npcs/re/warps/other/s_workshop.lua",
	"scripts/npcs/re/warps/other/jobquests.lua",
	"scripts/npcs/re/warps/other/dimensional_gap.lua",
	"scripts/npcs/re/warps/other/arena.lua"
}
