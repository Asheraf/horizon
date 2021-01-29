#include "LuaDefinitionSync.hpp"

#include "Server/Common/Configuration/Horizon.hpp"
#include "BattleDefinitions.hpp"
#include "EntityDefinitions.hpp"
#include "ItemDefinitions.hpp"
#include "MonsterDefinitions.hpp"
#include "NPCDefinitions.hpp"
#include "SkillDefinitions.hpp"

void sync_battle_definitions(sol::state &state)
{
	state.create_named_table("TargetCheckType",
		"None", (int) BTC_NONE,
		"Self",(int) BTC_SELF,
		"Enemy", (int) BTC_ENEMY,
		"Party", (int) BTC_PARTY,
		"Guild", (int) BTC_GUILD,
		"GuildAlly", (int) BTC_GUILD_ALLY,
		"All", (int) BTC_ALL
	);

	state.create_named_table("AttackType",
		"None", (int) BAT_NONE,
		"Weapon", (int) BAT_WEAPON,
		"Magic", (int) BAT_MAGIC,
		"Misc", (int) BAT_MISC
	);
	state.create_named_table("DamageBehavior",
		"None", (int) DMG_BHVR_NONE,
		"NonOffensive", (int) DMG_BHVR_NON_OFFENSIVE,
		"AreaOfEffect", (int) DMG_BHVR_AOE,
		"SplitBetweenTargets", (int) DMG_BHVR_SPLIT_BW_TARGETS,
		"IgnoreEquipATK", (int) DMG_BHVR_IGNORE_EQUIP_ATK,
		"IgnoreDefElement", (int) DMG_BHVR_IGNORE_DEF_ELE,
		"IgnoreSoftDef", (int) DMG_BHVR_IGNORE_SOFT_DEF,
		"IgnoreFLEE", (int) DMG_BHVR_IGNORE_FLEE,
		"IgnoreEquipDef", (int) DMG_BHVR_IGNORE_EQUIP_DEF
	);
}


void sync_entity_definitions(sol::state &state)
{
	state.create_named_table("EntityType",
		"Player", (int) ENTITY_MASK_PLAYER,
		"NPC", (int) ENTITY_MASK_NPC,
		"Item", (int) ENTITY_MASK_ITEM,
		"Skill", (int) ENTITY_MASK_SKILL,
		"Monster", (int) ENTITY_MASK_MONSTER,
		"Event", (int) ENTITY_MASK_EVENT,
		"Pet", (int) ENTITY_MASK_PET,
		"Homunculus", (int) ENTITY_MASK_HOMNUCLUS,
		"Mercenary", (int) ENTITY_MASK_MERCNARY,
		"Elemental", (int) ENTITY_MASK_ELEMENTAL
	);

	state.create_named_table("Directions",
		"North", (int) DIR_NORTH,
		"NorthWest", (int) DIR_NORTH_WEST,
		"West", (int) DIR_WEST,
		"SouthWest", (int) DIR_SOUTH_WEST,
		"South", (int) DIR_SOUTH,
		"SouthEast", (int) DIR_SOUTH_EAST,
		"East", (int) DIR_EAST,
		"NorthEast", (int) DIR_NORTH_EAST
	);


	state.create_named_table("Posture",
		"Standing", (int) POSTURE_STANDING,
		"Dead", (int) POSTURE_DEAD,
		"Sitting", (int) POSTURE_SITTING
	);

	state.create_named_table("Job",
		"Novice", (int) JOB_NOVICE,
		"Swordman", (int) JOB_SWORDMAN,
		"Magician", (int) JOB_MAGE,
		"Archer", (int) JOB_ARCHER,
		"Acolyte", (int) JOB_ACOLYTE,
		"Merchant", (int) JOB_MERCHANT,
		"Thief", (int) JOB_THIEF,
		"Knight", (int) JOB_KNIGHT,
		"Priest", (int) JOB_PRIEST,
		"Wizard", (int) JOB_WIZARD,
		"Blacksmith", (int) JOB_BLACKSMITH,
		"Hunter", (int) JOB_HUNTER,
		"Assassin", (int) JOB_ASSASSIN,
		//JOB_KNIGHT2
		"Crusader", (int) JOB_CRUSADER,
		"Monk", (int) JOB_MONK,
		"Sage", (int) JOB_SAGE,
		"Rogue", (int) JOB_ROGUE,
		"Alchemist", (int) JOB_ALCHEMIST,
		"Bard", (int) JOB_BARD,
		"Dancer", (int) JOB_DANCER,
		"Wedding", (int) JOB_WEDDING,
		"SuperNovice", (int) JOB_SUPER_NOVICE,
		"Gunslinger", (int) JOB_GUNSLINGER,
		"Ninja", (int) JOB_NINJA,
		"Xmas", (int) JOB_XMAS,
		"Summer", (int) JOB_SUMMER,
		//4000-
		"HighNovice", (int) JOB_NOVICE_HIGH,
		"HighSwordman", (int) JOB_SWORDMAN_HIGH,
		"HighMagician", (int) JOB_MAGE_HIGH,
		"HighArcher", (int) JOB_ARCHER_HIGH,
		"HighAcolyte", (int) JOB_ACOLYTE_HIGH,
		"HighMerchant", (int) JOB_MERCHANT_HIGH,
		"HighThief", (int) JOB_THIEF_HIGH,
		"LordKnight", (int) JOB_LORD_KNIGHT,
		"HighPriest", (int) JOB_HIGH_PRIEST,
		"HighWizard", (int) JOB_HIGH_WIZARD,
		"Whitesmith", (int) JOB_WHITESMITH,
		"Sniper", (int) JOB_SNIPER,
		"AssassinCross", (int) JOB_ASSASSIN_CROSS,
		"Paladin", (int) JOB_PALADIN,
		"Champion", (int) JOB_CHAMPION,
		"Professor", (int) JOB_PROFESSOR,
		"Stalker", (int) JOB_STALKER,
		"Creator", (int) JOB_CREATOR,
		"Clown", (int) JOB_CLOWN,
		"Gypsy", (int) JOB_GYPSY,
		"BabyNovice", (int) JOB_BABY_NOVICE,
		"BabySwordman", (int) JOB_BABY_SWORDMAN,
		"BabyMagician", (int) JOB_BABY_MAGE,
		"BabyArcher", (int) JOB_BABY_ARCHER,
		"BabyAcolyte", (int) JOB_BABY_ACOLYTE,
		"BabyMerchant", (int) JOB_BABY_MERCHANT,
		"BabyThief", (int) JOB_BABY_THIEF,
		"BabyKnight", (int) JOB_BABY_KNIGHT,
		"BabyPriest", (int) JOB_BABY_PRIEST,
		"BabyWizard", (int) JOB_BABY_WIZARD,
		"BabyBlacksmith", (int) JOB_BABY_BLACKSMITH,
		"BabyHunter", (int) JOB_BABY_HUNTER,
		"BabyAssassin", (int) JOB_BABY_ASSASSIN,
		"BabyCrusader", (int) JOB_BABY_CRUSADER,
		"BabyMonk", (int) JOB_BABY_MONK,
		"BabySage", (int) JOB_BABY_SAGE,
		"BabyRogue", (int) JOB_BABY_ROGUE,
		"BabyAlchemist", (int) JOB_BABY_ALCHEMIST,
		"BabyBard", (int) JOB_BABY_BARD,
		"BabyDancer", (int) JOB_BABY_DANCER,
		"SuperBaby", (int) JOB_SUPER_BABY,
		"Taekwon", (int) JOB_TAEKWON,
		"StarGladiator", (int) JOB_STAR_GLADIATOR,
		"SoulLinker", (int) JOB_SOUL_LINKER,
		"Gangsi", (int) JOB_GANGSI,
		"DeathKnight", (int) JOB_DEATH_KNIGHT,
		"DarkCollector", (int) JOB_DARK_COLLECTOR,
		// 4053-
		"RuneKnight", (int) JOB_RUNE_KNIGHT,
		"Warlock", (int) JOB_WARLOCK,
		"Ranger", (int) JOB_RANGER,
		"Archbishop", (int) JOB_ARCH_BISHOP,
		"Mechanic", (int) JOB_MECHANIC,
		"GuillotineCross", (int) JOB_GUILLOTINE_CROSS,
		"RuneKnightTrans", (int) JOB_RUNE_KNIGHT_T,
		"WarlockTrans", (int) JOB_WARLOCK_T,
		"RangerTrans", (int) JOB_RANGER_T,
		"ArchbishopTrans", (int) JOB_ARCH_BISHOP_T,
		"MechanicTrans", (int) JOB_MECHANIC_T,
		"GuillotineCrossTrans", (int) JOB_GUILLOTINE_CROSS_T,
		"RoyalGuard", (int) JOB_ROYAL_GUARD,
		"Sorcerer", (int) JOB_SORCERER,
		"Minstrel", (int) JOB_MINSTREL,
		"Wanderer", (int) JOB_WANDERER,
		"Sura", (int) JOB_SURA,
		"Genetic", (int) JOB_GENETIC,
		"ShadowChaser", (int) JOB_SHADOW_CHASER,
		"RoyalGuardTrans", (int) JOB_ROYAL_GUARD_T,
		"SorcererTrans", (int) JOB_SORCERER_T,
		"MinstrelTrans", (int) JOB_MINSTREL_T,
		"WandererTrans", (int) JOB_WANDERER_T,
		"SuraTrans", (int) JOB_SURA_T,
		"GeneticTrans", (int) JOB_GENETIC_T,
		"ShadowChaserTrans", (int) JOB_SHADOW_CHASER_T,
		//4088-4097
		"BabyRuneKnight", (int) JOB_BABY_RUNE_KNIGHT,
		"BabyWarlock", (int) JOB_BABY_WARLOCK,
		"BabyRanger", (int) JOB_BABY_RANGER,
		"BabyArchbishop", (int) JOB_BABY_ARCH_BISHOP,
		"BabyMechanic", (int) JOB_BABY_MECHANIC,
		"BabyGuillotineCross", (int) JOB_BABY_GUILLOTINE_CROSS,
		"BabyRoyalGuard", (int) JOB_BABY_ROYAL_GUARD,
		"BabySorcerer", (int) JOB_BABY_SORCERER,
		"BabyMinstrel", (int) JOB_BABY_MINSTREL,
		"BabyWanderer", (int) JOB_BABY_WANDERER,
		"BabySura", (int) JOB_BABY_SURA,
		"BabyGenetic", (int) JOB_BABY_GENETIC,
		"BabyShadowChaser", (int) JOB_BABY_SHADOW_CHASER,
		"SuperNoviceExpanded", (int) JOB_SUPER_NOVICE_E,
		"SuperBabyExpanded", (int) JOB_SUPER_BABY_E,
		"Kagerou", (int) JOB_KAGEROU,
		"Oboro", (int) JOB_OBORO,
		"Rebellion", (int) JOB_REBELLION,
		"Summoner", (int) JOB_SUMMONER,
		"StartBase", (int) JOB_BASE_START,
		"EndBase", (int) JOB_BASE_END,
		"Start_2_1", (int) JOB_2_1_START,
		"End_2_1", (int) JOB_2_1_END,
		"Start_2_2", (int) JOB_2_2_START,
		"End_2_2", (int) JOB_2_2_END,
		"StartTransBase", (int) JOB_TRANS_BASE_START,
		"EndTransBase", (int) JOB_TRANS_BASE_END,
		"Start_Trans_2_1", (int) JOB_TRANS_2_1_START,
		"End_Trans_2_1", (int) JOB_TRANS_2_1_END,
		"Start_Trans_2_2", (int) JOB_TRANS_2_2_START,
		"End_Trans_2_2", (int) JOB_TRANS_2_2_END,
		"Start_Baby_Base", (int) JOB_BABY_BASE_START,
		"End_Baby_Base", (int) JOB_BABY_BASE_END,
		"Start_Baby_2_1", (int) JOB_BABY_2_1_START,
		"End_Baby_2_1", (int) JOB_BABY_2_1_END,
		"Start_Baby_2_2", (int) JOB_BABY_2_2_START,
		"End_Baby_2_2", (int) JOB_BABY_2_2_END,
		"Start_3_1", (int) JOB_3_1_START,
		"End_3_1", (int) JOB_3_1_END,
		"Start_3_2", (int) JOB_3_2_START,
		"End_3_2", (int) JOB_3_2_END,
		"Start_Trans_3_1", (int) JOB_TRANS_3_1_START,
		"End_Trans_3_1", (int) JOB_TRANS_3_1_END,
		"Start_Trans_3_2", (int) JOB_TRANS_3_2_START,
		"End_Trans_3_2", (int) JOB_TRANS_3_2_END,
		"Start_Baby_3_1", (int) JOB_BABY_3_1_START,
		"End_Baby_3_1", (int) JOB_BABY_3_1_END,
		"Start_Baby_3_2", (int) JOB_BABY_3_2_START,
		"End_Baby_3_2", (int) JOB_BABY_3_2_END
	);

	state.create_named_table("JobMask",
		"Invalid", (int) JMASK_INVALID,
		"Novice", (int) JMASK_NOVICE,
		"Swordman", (int) JMASK_SWORDMAN,
		"Magician", (int) JMASK_MAGE,
		"Archer", (int) JMASK_ARCHER,
		"Acolyte", (int) JMASK_ACOLYTE,
		"Merchant", (int) JMASK_MERCHANT,
		"Thief", (int) JMASK_THIEF,
		"Gangsi", (int) JMASK_GANGSI,
		"Summoner", (int) JMASK_SUMMONER,
		"Taekwon", (int) JMASK_TAEKWON_BASE,
		"Gunslinger", (int) JMASK_GUNSLINGER_BASE,
		"Ninja", (int) JMASK_NINJA_BASE,
		"BaseClass", (int) JMASK_BASE,
		"Wedding", (int) JMASK_WEDDING,
		"2_1_Class", (int) JMASK_2_1,
		"2_2_Class", (int) JMASK_2_2,
		"BabyBaseClass", (int) JMASK_BABY_BASE,
		"Baby_1_1_Class", (int) JMASK_BABY_1_1,
		"Baby_1_2_Class", (int) JMASK_BABY_1_2,
		"Baby_2_1_Class", (int) JMASK_BABY_2_1,
		"Baby_2_2_Class", (int) JMASK_BABY_2_2,
		"TransBaseClass", (int) JMASK_TRANS_BASE,
		"Trans_1_1_Class", (int) JMASK_TRANS_1_1,
		"Trans_1_2_Class", (int) JMASK_TRANS_1_2,
		"Trans_2_1_Class", (int) JMASK_TRANS_2_1,
		"Trans_2_2_Class", (int) JMASK_TRANS_2_2,
		"3_1_Class", (int) JMASK_3_1,
		"3_2_Class", (int) JMASK_3_2,
		"Trans_3_1_Class", (int) JMASK_TRANS_3_1,
		"Trans_3_2_Class", (int) JMASK_TRANS_3_2,
		"Baby_3_1_Class", (int) JMASK_BABY_3_1,
		"Baby_3_3_Class", (int) JMASK_BABY_3_2,
		"ExpandedClass", (int) JMASK_EXPANDED,
		"ExpandedBabyClass", (int) JMASK_EXPANDED_BABY,
		"Expanded_2_1_Class", (int) JMASK_EXPANDED_2_1,
		"Expanded_2_2_Class", (int) JMASK_EXPANDED_2_2,

		"NormalClass", (int) JMASK_NORMAL,
		"BabyClass", (int) JMASK_BABY,
		"TransClass", (int) JMASK_TRANS,
		"ThirdClass", (int) JMASK_3,
		"TransThirdClass", (int) JMASK_TRANS_3,
		"BabyThirdClass", (int) JMASK_BABY_3,

		// 2-1 Jobs
		"Knight", (int) JMASK_KNIGHT,
		"Wizard", (int) JMASK_WIZARD,
		"Hunter", (int) JMASK_HUNTER,
		"Priest", (int) JMASK_PRIEST,
		"Blacksmith", (int) JMASK_BLACKSMITH,
		"Assassin", (int) JMASK_ASSASSIN,
		"DeathKnight", (int) JMASK_DEATH_KNIGHT,

		// 2-2 Jobs
		"Crusader", (int) JMASK_CRUSADER,
		"Sage", (int) JMASK_SAGE,
		"BardOrDancer", (int) JMASK_BARDDANCER,
		"Monk", (int) JMASK_MONK,
		"Alchemist", (int) JMASK_ALCHEMIST,
		"Rogue", (int) JMASK_ROGUE,
		"DarkCollector", (int) JMASK_DARK_COLLECTOR,

		//Trans Novice And Trans 1-1 J
		"HighNovice", (int) JMASK_NOVICE_HIGH,
		"HighSwordman", (int) JMASK_SWORDMAN_HIGH,
		"HighMagician", (int) JMASK_MAGE_HIGH,
		"HighArcher", (int) JMASK_ARCHER_HIGH,
		"HighAcolyte", (int) JMASK_ACOLYTE_HIGH,
		"HighMerchant", (int) JMASK_MERCHANT_HIGH,
		"HighThief", (int) JMASK_THIEF_HIGH,

		//Trans 2-1 Jobs
		"LordKnight", (int) JMASK_LORD_KNIGHT,
		"HighWizard", (int) JMASK_HIGH_WIZARD,
		"Sniper", (int) JMASK_SNIPER,
		"HighPriest", (int) JMASK_HIGH_PRIEST,
		"Whitesmith", (int) JMASK_WHITESMITH,
		"AssassinCross", (int) JMASK_ASSASSIN_CROSS,

		//Trans 2-2 Jobs
		"Paladin", (int) JMASK_PALADIN,
		"Professor", (int) JMASK_PROFESSOR,
		"ClownOrGypsy", (int) JMASK_CLOWNGYPSY,
		"Champion", (int) JMASK_CHAMPION,
		"Creator", (int) JMASK_CREATOR,
		"Stalker", (int) JMASK_STALKER,

		//Baby Novice And Baby 1-1 Job
		"BabyNovice", (int) JMASK_BABY_NOVICE,
		"BabySwordman", (int) JMASK_BABY_SWORDMAN,
		"BabyMage", (int) JMASK_BABY_MAGE,
		"BabyArcher", (int) JMASK_BABY_ARCHER,
		"BabyAcolyte", (int) JMASK_BABY_ACOLYTE,
		"BabyMerchant", (int) JMASK_BABY_MERCHANT,
		"BabyThief", (int) JMASK_BABY_THIEF,

		//Baby 2-1 Jobs
		"BabyKnight", (int) JMASK_BABY_KNIGHT,
		"BabyWizard", (int) JMASK_BABY_WIZARD,
		"BabyHunter", (int) JMASK_BABY_HUNTER,
		"BabyPriest", (int) JMASK_BABY_PRIEST,
		"BabyBlacksmith", (int) JMASK_BABY_BLACKSMITH,
		"BabyAssassin", (int) JMASK_BABY_ASSASSIN,

		//Baby 2-2 Jobs
		"BabyCrusader", (int) JMASK_BABY_CRUSADER,
		"BabySage", (int) JMASK_BABY_SAGE,
		"BabyBardOrDancer", (int) JMASK_BABY_BARDDANCER,
		"BabyMonk", (int) JMASK_BABY_MONK,
		"BabyAlchemist", (int) JMASK_BABY_ALCHEMIST,
		"BabyRogue", (int) JMASK_BABY_ROGUE,

		//3-1 Jobs
		"RuneKnight", (int) JMASK_RUNE_KNIGHT,
		"Warlock", (int) JMASK_WARLOCK,
		"Ranger", (int) JMASK_RANGER,
		"Archbishop", (int) JMASK_ARCH_BISHOP,
		"Mechanic", (int) JMASK_MECHANIC,
		"GuillotineCross", (int) JMASK_GUILLOTINE_CROSS,

		//3-2 Jobs
		"RoyalGuard", (int) JMASK_ROYAL_GUARD,
		"Sorcerer", (int) JMASK_SORCERER,
		"MinstrelOrWanderer", (int) JMASK_MINSTRELWANDERER,
		"Sura", (int) JMASK_SURA,
		"Genetic", (int) JMASK_GENETIC,
		"ShadowChaser", (int) JMASK_SHADOW_CHASER,

		//Trans 3-1 Jobs
		"RuneKnightTrans", (int) JMASK_RUNE_KNIGHT_T,
		"WarlockTrans", (int) JMASK_WARLOCK_T,
		"RangerTrans", (int) JMASK_RANGER_T,
		"ArchbishopTrans", (int) JMASK_ARCH_BISHOP_T,
		"MechanicTrans", (int) JMASK_MECHANIC_T,
		"GuillotineCrossTrans", (int) JMASK_GUILLOTINE_CROSS_T,

		//Trans 3-2 Jobs
		"RoyalGuardTrans", (int) JMASK_ROYAL_GUARD_T,
		"SorcererTrans", (int) JMASK_SORCERER_T,
		"MinstrelOrWandererTrans", (int) JMASK_MINSTRELWANDERER_T,
		"SuraTrans", (int) JMASK_SURA_T,
		"GeneticTrans", (int) JMASK_GENETIC_T,
		"ShadowChaserTrans", (int) JMASK_SHADOW_CHASER_T,

		//Baby 3-1 Jobs
		"BabyRuneKnight", (int) JMASK_BABY_RUNE_KNIGHT,
		"BabyWarlock", (int) JMASK_BABY_WARLOCK,
		"BabyRanger", (int) JMASK_BABY_RANGER,
		"BabyArchbishop", (int) JMASK_BABY_ARCH_BISHOP,
		"BabyMechanic", (int) JMASK_BABY_MECHANIC,
		"BabyGuillotineCross", (int) JMASK_BABY_GUILLOTINE_CROSS,

		//Baby 3-2 Jobs
		"BabyRoyalGuard", (int) JMASK_BABY_ROYAL_GUARD,
		"BabySorcerer", (int) JMASK_BABY_SORCERER,
		"BabyMinstrelOrWanderer", (int) JMASK_BABY_MINSTRELWANDERER,
		"BabySura", (int) JMASK_BABY_SURA,
		"BabyGenetic", (int) JMASK_BABY_GENETIC,
		"BabyShadowChaser", (int) JMASK_BABY_SHADOW_CHASER,

		// Expanded Jobs
		"Taekwon", (int) JMASK_TAEKWON,
		"StarGladiator", (int) JMASK_STAR_GLADIATOR,
		"SoulLinker", (int) JMASK_SOUL_LINKER,

		"SuperNovice", (int) JMASK_SUPER_NOVICE,
		"SuperNoviceExpanded", (int) JMASK_SUPER_NOVICE_E,

		"SuperBaby", (int) JMASK_SUPER_BABY,
		"SuperBabyExpanded", (int) JMASK_SUPER_BABY_E,

		"Gunslinger", (int) JMASK_GUNSLINGER,
		"Rebellion", (int) JMASK_REBELLION,

		"Ninja", (int) JMASK_NINJA,
		"KagerouOrOboro", (int) JMASK_KAGEROUOBORO,

		"All", (int) JMASK_ALL
	);
}
void sync_item_definitions(sol::state &state)
{
	state.create_named_table("RefineType",
		"Armor", (int) REFINE_TYPE_ARMOR,
		"Weapon1", (int) REFINE_TYPE_WEAPON1,
		"Weapon2", (int) REFINE_TYPE_WEAPON2,
		"Weapon3", (int) REFINE_TYPE_WEAPON3,
		"Weapon4", (int) REFINE_TYPE_WEAPON4,
		"Max", (int) REFINE_TYPE_MAX
	);

	state.create_named_table("RefineChanceType",
		"Normal", (int) REFINE_CHANCE_TYPE_NORMAL,
		"Enriched", (int) REFINE_CHANCE_TYPE_ENRICHED,
		"EventNormal", (int) REFINE_CHANCE_TYPE_E_NORMAL,
		"EventEnriched", (int) REFINE_CHANCE_TYPE_E_ENRICHED,
		"Max", (int) REFINE_CHANCE_TYPE_MAX
	);

	state.create_named_table("WeaponType",
		"Fist", (int) IT_WT_FIST,
		"Dagger", (int) IT_WT_DAGGER,
		"OneHandedSword", (int) IT_WT_1HSWORD,
		"TwoHandedSword", (int) IT_WT_2HSWORD,
		"OneHandedSpear", (int) IT_WT_1HSPEAR,
		"TwoHandedSpear", (int) IT_WT_2HSPEAR,
		"OneHandedAxe", (int) IT_WT_1HAXE,
		"TwoHandedAxe", (int) IT_WT_2HAXE,
		"OneHandedMace", (int) IT_WT_1HMACE,
		"TwoHandedMace", (int) IT_WT_2HMACE,
		"OneHandedStaff", (int) IT_WT_STAFF,
		"Bow", (int) IT_WT_BOW,
		"Knuckle", (int) IT_WT_KNUCKLE,
		"MusicalInstrument", (int) IT_WT_MUSICAL,
		"Whip", (int) IT_WT_WHIP,
		"Book", (int) IT_WT_BOOK,
		"Katar", (int) IT_WT_KATAR,
		"Revolver", (int) IT_WT_REVOLVER,
		"Rifle", (int) IT_WT_RIFLE,
		"GatlingGun", (int) IT_WT_GATLING,
		"Shotgun", (int) IT_WT_SHOTGUN,
		"GrenadeLauncher", (int) IT_WT_GRENADE,
		"FuumaShuriken", (int) IT_WT_HUUMA,
		"TwoHandedStaff", (int) IT_WT_2HSTAFF,
		"Max", (int) IT_WT_MAX
	);

	state.create_named_table("WeaponTypeMask",
		"Ranged", (int) IT_WTM_RANGED,
		"Melee", (int) IT_WTM_MELEE
	);

	state.create_named_table("ItemLevelType",
		"Armor", (int) IT_LVL_ARMOR,
		"Weapon1", (int) IT_LVL_WEAPON1,
		"Weapon2", (int) IT_LVL_WEAPON2,
		"Weapon3", (int) IT_LVL_WEAPON3,
		"Weapon4", (int) IT_LVL_WEAPON4,
		"Max", (int) IT_LVL_MAX
	);

	state.create_named_table("ItemGenderType",
		"Female", (int) IT_GENDER_FEMALE,
		"Male", (int) IT_GENDER_MALE,
		"Any", (int) IT_GENDER_ANY
	);

	state.create_named_table("EquipLocationMask",
		"None", (int) IT_EQPM_NONE,
		"LowerHead", (int) IT_EQPM_HEAD_LOW,
		"RightHand", (int) IT_EQPM_HAND_R,
		"Garment", (int) IT_EQPM_GARMENT,
		"LeftAccessory", (int) IT_EQPM_ACC_L,
		"Armor", (int) IT_EQPM_ARMOR,
		"LeftHand", (int) IT_EQPM_HAND_L,
		"Shoes", (int) IT_EQPM_SHOES,
		"RightAccessory", (int) IT_EQPM_ACC_R,
		"TopHead", (int) IT_EQPM_HEAD_TOP,
		"MidHead", (int) IT_EQPM_HEAD_MID,
		"CostumeTopHead", (int) IT_EQPM_COSTUME_HEAD_TOP,
		"CostumeMidHead", (int) IT_EQPM_COSTUME_HEAD_MID,
		"CostumeLowerHead", (int) IT_EQPM_COSTUME_HEAD_LOW,
		"CostumeGarment", (int) IT_EQPM_COSTUME_GARMENT,
		"Ammunition", (int) IT_EQPM_AMMO,
		"ShadowArmor", (int) IT_EQPM_SHADOW_ARMOR,
		"ShadowWeapon", (int) IT_EQPM_SHADOW_WEAPON,
		"ShadowShield", (int) IT_EQPM_SHADOW_SHIELD,
		"ShadowShoes", (int) IT_EQPM_SHADOW_SHOES,
		"ShadowRightAccessory", (int) IT_EQPM_SHADOW_ACC_R,
		"ShadowLeftAccessory", (int) IT_EQPM_SHADOW_ACC_L,
		"Weapon", (int) IT_EQPM_WEAPON,
		"Shield", (int) IT_EQPM_SHIELD,
		"BothArms", (int) IT_EQPM_ARMS,
		"AllHeadgear", (int) IT_EQPM_HELM,
		"AllAccessory", (int) IT_EQPM_ACC,
		"AllCostume", (int) IT_EQPM_COSTUME,
		"ShadowAccessory", (int) IT_EQPM_SHADOW_ACC,
		"ShadowArms", (int) IT_EQPM_SHADOW_ARMS
	);

	state.create_named_table("EquipLocationIndex",
		"LeftAccessory", (int) IT_EQPI_ACC_L,
		"RightAccessory", (int) IT_EQPI_ACC_R,
		"Shoes", (int) IT_EQPI_SHOES,
		"Garment", (int) IT_EQPI_GARMENT,
		"LowerHead", (int) IT_EQPI_HEAD_LOW,
		"MidHead", (int) IT_EQPI_HEAD_MID,
		"TopHead", (int) IT_EQPI_HEAD_TOP,
		"Armor", (int) IT_EQPI_ARMOR,
		"LeftHand", (int) IT_EQPI_HAND_L,
		"RightHand", (int) IT_EQPI_HAND_R,
		"CostumeTopHead", (int) IT_EQPI_COSTUME_TOP,
		"CostumeMidHead", (int) IT_EQPI_COSTUME_MID,
		"CostumeLowHead", (int) IT_EQPI_COSTUME_LOW,
		"CostumeGarment", (int) IT_EQPI_COSTUME_GARMENT,
		"Ammunition", (int) IT_EQPI_AMMO,
		"ShadowArmor", (int) IT_EQPI_SHADOW_ARMOR,
		"ShadowWeapon", (int) IT_EQPI_SHADOW_WEAPON,
		"ShadowShield", (int) IT_EQPI_SHADOW_SHIELD,
		"ShadowShoes", (int) IT_EQPI_SHADOW_SHOES,
		"ShadowRightAccessory", (int) IT_EQPI_SHADOW_ACC_R,
		"ShadowLeftAccessory", (int) IT_EQPI_SHADOW_ACC_L,
		"Max", (int) IT_EQPI_MAX
	);

	state.create_named_table("ItemTradeMask",
		"None", (int) ITRMASK_NONE,
		"Drop", (int) ITRMASK_DROP,
		"Trade", (int) ITRMASK_TRADE,
		"TradeWithPartner", (int) ITRMASK_TRADEWPARTNER,
		"SellToNPC", (int) ITRMASK_SELL_TO_NPC,
		"StoreInCart", (int) ITRMASK_CART,
		"StoreInStorage", (int) ITRMASK_STORAGE,
		"StoreInGuildStorage", (int) ITRMASK_GSTORAGE,
		"Mail", (int) ITRMASK_MAIL,
		"Auction", (int) ITRMASK_AUCTION,
		"SellInBuyingStore", (int) ITRMASK_BUYING_STORE,
		"AllowAll", (int) ITRMASK_ALL
	);

	state.create_named_table("ItemUsageMask",
		"Sitting", (int) IURMASK_SITTING,
		"All", (int) IURMASK_ALL
	);

	state.create_named_table("ItemType",
		"Healing", (int) IT_TYPE_HEALING,
		"Unknown", (int) IT_TYPE_UNKNOWN,
		"Usable", (int) IT_TYPE_USABLE,
		"Etc", (int) IT_TYPE_ETC,
		"Weapon", (int) IT_TYPE_WEAPON,
		"Armor", (int) IT_TYPE_ARMOR,
		"Card", (int) IT_TYPE_CARD,
		"PetEgg", (int) IT_TYPE_PET_EGG,
		"PetArmor", (int) IT_TYPE_PET_ARMOR,
		"Unknown2", (int) IT_TYPE_UNKNOWN2,
		"Ammunition", (int) IT_TYPE_AMMO,
		"ConsumptionDelay", (int) IT_TYPE_CONSUMPTION_DELAY,
		"Cash", (int) IT_TYPE_CASH,
		"Max", (int) IT_TYPE_MAX
	);

	state.create_named_table("AmmoType",
		"None", (int) IT_AT_NONE,
		"Arrow", (int) IT_AT_ARROW,
		"ThrowableDagger", (int) IT_AT_DAGGER,
		"Bullet", (int) IT_AT_BULLET,
		"Shell", (int) IT_AT_SHELL,
		"Grenade", (int) IT_AT_GRENADE,
		"Shuriken", (int) IT_AT_SHURIKEN,
		"Kunai", (int) IT_AT_KUNAI,
		"CannonBall", (int) IT_AT_CANNONBALL,
		"ThrowableItem", (int) IT_AT_THROWABLE_ITEM,
		"Max", (int) IT_AT_MAX
	);

	state.create_named_table("Element",
		"Neutral", (int) IT_ELE_NEUTRAL,
		"Water", (int) IT_ELE_WATER,
		"Earth", (int) IT_ELE_EARTH,
		"Fire", (int) IT_ELE_FIRE,
		"Wind", (int) IT_ELE_WIND,
		"Poison", (int) IT_ELE_POISON,
		"Holy", (int) IT_ELE_HOLY,
		"Dark", (int) IT_ELE_DARK,
		"Ghost", (int) IT_ELE_GHOST,
		"Undead", (int) IT_ELE_UNDEAD,
		"Max", (int) IT_ELE_MAX,
		"All", (int) IT_ELE_ALL
	);

	state.create_named_table("ItemBindType",
		"None", (int) IT_BIND_NONE,
		"Account", (int) IT_BIND_ACCOUNT,
		"Guild", (int) IT_BIND_GUILD,
		"Party", (int) IT_BIND_PARTY,
		"Character", (int) IT_BIND_CHARACTER,
		"Max", (int) IT_BIND_MAX
	);
}
