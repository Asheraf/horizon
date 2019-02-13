
#ifndef HORIZON_ZONE_GAME_ENTITY_DEFINITIONS
#define HORIZON_ZONE_GAME_ENTITY_DEFINITIONS

#include <stdint.h>
#include <cstring>
#include "Server/Common/Client.hpp"

enum player_notifier_types
{
	GRID_NOTIFY_AREA,               // area
	GRID_NOTIFY_AREA_WOS,           // area, without self
	GRID_NOTIFY_AREA_WOC,           // area, without chatrooms
	GRID_NOTIFY_AREA_WOSC,          // area, without own chatrooms
	GRID_NOTIFY_AREA_CHAT_WOC,      // hearable area, without chatrooms
	GRID_NOTIFY_AREA_DEAD,          // area, for clear unit (monster death)
	GRID_NOTIFY_CHAT,               // current chatroom
	GRID_NOTIFY_CHAT_WOS,           // current chatroom, without self
	GRID_NOTIFY_PARTY,
	GRID_NOTIFY_PARTY_WOS,
	GRID_NOTIFY_PARTY_AREA,
	GRID_NOTIFY_PARTY_AREA_WOS,
	GRID_NOTIFY_GUILD,
	GRID_NOTIFY_GUILD_WOS,
	GRID_NOTIFY_GUILD_AREA,
	GRID_NOTIFY_GUILD_AREA_WOS,
	GRID_NOTIFY_GUILD_NOBG,
	GRID_NOTIFY_DUEL,
	GRID_NOTIFY_DUEL_WOS,
	GRID_NOTIFY_SELF
};

enum entity_types : char
{
	ENTITY_PLAYER      = 0x0,
	ENTITY_NPC         = 0x1,
	ENTITY_ITEM        = 0x2,
	ENTITY_SKILL       = 0x3,
	ENTITY_UNKNOWN     = 0x4,
	ENTITY_MONSTER     = 0x5,
	ENTITY_EVENT       = 0x6,
	ENTITY_PET         = 0x7,
	ENTITY_HOMUNCULUS  = 0x8,
	ENTITY_MERCENARY   = 0x9,
	ENTITY_ELEMENTAL   = 0xA,
};

enum entity_type_mask
{
	ENTITY_MASK_PLAYER    = 0x000,
	ENTITY_MASK_NPC       = 0x001,
	ENTITY_MASK_ITEM      = 0x002,
	ENTITY_MASK_SKILL     = 0x004,
	ENTITY_MASK_UNKNOWN   = 0x008,
	ENTITY_MASK_MONSTER   = 0x010,
	ENTITY_MASK_EVENT     = 0x020,
	ENTITY_MASK_PET       = 0x040,
	ENTITY_MASK_HOMNUCLUS = 0x080,
	ENTITY_MASK_MERCNARY  = 0x0100,
	ENTITY_MASK_ELEMENTAL = 0x0200,
	ENTITY_MASK_ALL       = 0x0FFF
};

enum directions : short
{
	DIR_NORTH      = 0,
	DIR_NORTH_WEST = 1,
	DIR_WEST       = 2,
	DIR_SOUTH_WEST = 3,
	DIR_SOUTH      = 4,
	DIR_SOUTH_EAST = 5,
	DIR_EAST       = 6,
	DIR_NORTH_EAST = 7
};

enum status_point_types
{
	STATUS_SPEED            =    0,
	STATUS_BASEEXP          =    1,
	STATUS_JOBEXP           =    2,
	STATUS_KARMA            =    3,
	STATUS_MANNER           =    4,
	STATUS_HP               =    5,
	STATUS_MAXHP            =    6,
	STATUS_SP               =    7,
	STATUS_MAXSP            =    8,
	STATUS_STATUSPOINT      =    9,
	STATUS_0a               =   10,
	STATUS_BASELEVEL        =   11,
	STATUS_SKILLPOINT       =   12,
	STATUS_STR              =   13,
	STATUS_AGI              =   14,
	STATUS_VIT              =   15,
	STATUS_INT              =   16,
	STATUS_DEX              =   17,
	STATUS_LUK              =   18,
	STATUS_CLASS            =   19,
	STATUS_ZENY             =   20,
	STATUS_SEX              =   21,
	STATUS_NEXTBASEEXP      =   22,
	STATUS_NEXTJOBEXP       =   23,
	STATUS_WEIGHT           =   24,
	STATUS_MAXWEIGHT        =   25,
	STATUS_1a               =   26,
	STATUS_1b               =   27,
	STATUS_1c               =   28,
	STATUS_1d               =   29,
	STATUS_1e               =   30,
	STATUS_1f               =   31,
	STATUS_USTR             =   32,
	STATUS_UAGI             =   33,
	STATUS_UVIT             =   34,
	STATUS_UINT             =   35,
	STATUS_UDEX             =   36,
	STATUS_ULUK             =   37,
	STATUS_26               =   38,
	STATUS_27               =   39,
	STATUS_28               =   40,
	STATUS_ATK1             =   41,
	STATUS_ATK2             =   42,
	STATUS_MATK1            =   43,
	STATUS_MATK2            =   44,
	STATUS_DEF1             =   45,
	STATUS_DEF2             =   46,
	STATUS_MDEF1            =   47,
	STATUS_MDEF2            =   48,
	STATUS_HIT              =   49,
	STATUS_FLEE1            =   50,
	STATUS_FLEE2            =   51,
	STATUS_CRITICAL         =   52,
	STATUS_ASPD             =   53,
	STATUS_36               =   54,
	STATUS_JOBLEVEL         =   55,
	STATUS_UPPER            =   56,
	STATUS_PARTNER          =   57,
	STATUS_CART             =   58,
	STATUS_FAME             =   59,
	STATUS_UNBREAKABLE      =   60,
	STATUS_CARTINFO         =   99,
	STATUS_BASEJOB          =  119,
	STATUS_BASECLASS        =  120,
	STATUS_KILLERRID        =  121,
	STATUS_KILLEDRID        =  122,
	STATUS_SLOTCHANGE       =  123,
	STATUS_CHARRENAME       =  124,
	STATUS_MOD_EXP          =  125,
	STATUS_MOD_DROP         =  126,
	STATUS_MOD_DEATH        =  127,
	STATUS_BANKVAULT        =  128,
	STATUS_MERCFLEE         =  165,
	STATUS_MERCKILLS        =  189,
	STATUS_MERCFAITH        =  190,
	STATUS_ATTACKRANGE      =  1000
};

enum entity_posture_types : char
{
	POSTURE_STANDING  = 0,
	POSTURE_DEAD      = 1,
	POSTURE_SITTING   = 2,
};

enum job_classes {
	JOB_NOVICE                 = 0,
	JOB_SWORDMAN               = 1,
	JOB_MAGE                   = 2,
	JOB_ARCHER                 = 3,
	JOB_ACOLYTE                = 4,
	JOB_MERCHANT               = 5,
	JOB_THIEF                  = 6,
	JOB_KNIGHT                 = 7,
	JOB_PRIEST                 = 8,
	JOB_WIZARD                 = 9,
	JOB_BLACKSMITH             = 10,
	JOB_HUNTER                 = 11,
	JOB_ASSASSIN               = 12,
	JOB_KNIGHT2                = 13,
	JOB_CRUSADER               = 14,
	JOB_MONK                   = 15,
	JOB_SAGE                   = 16,
	JOB_ROGUE                  = 17,
	JOB_ALCHEMIST              = 18,
	JOB_BARD                   = 19,
	JOB_DANCER                 = 20,
	JOB_CRUSADER2              = 21,
	JOB_WEDDING                = 22,
	JOB_SUPER_NOVICE           = 23,
	JOB_GUNSLINGER             = 24,
	JOB_NINJA                  = 25,
	JOB_XMAS                   = 26,
	JOB_SUMMER                 = 27,
	// 4000-
	JOB_NOVICE_HIGH            = 4001,
	JOB_SWORDMAN_HIGH          = 4002,
	JOB_MAGE_HIGH              = 4003,
	JOB_ARCHER_HIGH            = 4004,
	JOB_ACOLYTE_HIGH           = 4005,
	JOB_MERCHANT_HIGH          = 4006,
	JOB_THIEF_HIGH             = 4007,
	JOB_LORD_KNIGHT            = 4008,
	JOB_HIGH_PRIEST            = 4009,
	JOB_HIGH_WIZARD            = 4010,
	JOB_WHITESMITH             = 4011,
	JOB_SNIPER                 = 4012,
	JOB_ASSASSIN_CROSS         = 4013,
	JOB_LORD_KNIGHT2           = 4014,
	JOB_PALADIN                = 4015,
	JOB_CHAMPION               = 4016,
	JOB_PROFESSOR              = 4017,
	JOB_STALKER                = 4018,
	JOB_CREATOR                = 4019,
	JOB_CLOWN                  = 4020,
	JOB_GYPSY                  = 4021,
	JOB_PALADIN2               = 4022,
	JOB_BABY                   = 4023,
	JOB_BABY_SWORDMAN          = 4024,
	JOB_BABY_MAGE              = 4025,
	JOB_BABY_ARCHER            = 4026,
	JOB_BABY_ACOLYTE           = 4027,
	JOB_BABY_MERCHANT          = 4028,
	JOB_BABY_THIEF             = 4029,
	JOB_BABY_KNIGHT            = 4030,
	JOB_BABY_PRIEST            = 4031,
	JOB_BABY_WIZARD            = 4032,
	JOB_BABY_BLACKSMITH        = 4033,
	JOB_BABY_HUNTER            = 4034,
	JOB_BABY_ASSASSIN          = 4035,
	JOB_BABY_KNIGHT2           = 4036,
	JOB_BABY_CRUSADER          = 4037,
	JOB_BABY_MONK              = 4038,
	JOB_BABY_SAGE              = 4039,
	JOB_BABY_ROGUE             = 4040,
	JOB_BABY_ALCHEMIST         = 4041,
	JOB_BABY_BARD              = 4042,
	JOB_BABY_DANCER            = 4043,
	JOB_BABY_CRUSADER2         = 4044,
	JOB_SUPER_BABY             = 4045,
	JOB_TAEKWON                = 4046,
	JOB_STAR_GLADIATOR         = 4047,
	JOB_STAR_GLADIATOR2        = 4048,
	JOB_SOUL_LINKER            = 4049,
	JOB_GANGSI                 = 4050,
	JOB_DEATH_KNIGHT           = 4051,
	JOB_DARK_COLLECTOR         = 4052,
	// 4053-
	JOB_RUNE_KNIGHT            = 4054,
	JOB_WARLOCK                = 4055,
	JOB_RANGER                 = 4056,
	JOB_ARCH_BISHOP            = 4057,
	JOB_MECHANIC               = 4058,
	JOB_GUILLOTINE_CROSS       = 4059,
	JOB_RUNE_KNIGHT_T          = 4060,
	JOB_WARLOCK_T              = 4061,
	JOB_RANGER_T               = 4062,
	JOB_ARCH_BISHOP_T          = 4063,
	JOB_MECHANIC_T             = 4064,
	JOB_GUILLOTINE_CROSS_T     = 4065,
	JOB_ROYAL_GUARD            = 4066,
	JOB_SORCERER               = 4067,
	JOB_MINSTREL               = 4068,
	JOB_WANDERER               = 4069,
	JOB_SURA                   = 4070,
	JOB_GENETIC                = 4071,
	JOB_SHADOW_CHASER          = 4072,
	JOB_ROYAL_GUARD_T          = 4073,
	JOB_SORCERER_T             = 4074,
	JOB_MINSTREL_T             = 4075,
	JOB_WANDERER_T             = 4076,
	JOB_SURA_T                 = 4077,
	JOB_GENETIC_T              = 4078,
	JOB_SHADOW_CHASER_T        = 4079,
	JOB_RUNE_KNIGHT2           = 4080,
	JOB_RUNE_KNIGHT_T2         = 4081,
	JOB_ROYAL_GUARD2           = 4082,
	JOB_ROYAL_GUARD_T2         = 4083,
	JOB_RANGER2                = 4084,
	JOB_RANGER_T2              = 4085,
	JOB_MECHANIC2              = 4086,
	JOB_MECHANIC_T2            = 4087,
	//4088-4097
	JOB_BABY_RUNE              = 4096,
	JOB_BABY_WARLOCK           = 4097,
	JOB_BABY_RANGER            = 4098,
	JOB_BABY_BISHOP            = 4099,
	JOB_BABY_MECHANIC          = 4100,
	JOB_BABY_CROSS             = 4101,
	JOB_BABY_GUARD             = 4102,
	JOB_BABY_SORCERER          = 4103,
	JOB_BABY_MINSTREL          = 4104,
	JOB_BABY_WANDERER          = 4105,
	JOB_BABY_SURA              = 4106,
	JOB_BABY_GENETIC           = 4107,
	JOB_BABY_CHASER            = 4108,
	JOB_BABY_RUNE2             = 4109,
	JOB_BABY_GUARD2            = 4110,
	JOB_BABY_RANGER2           = 4111,
	JOB_BABY_MECHANIC2         = 4112,
	JOB_SUPER_NOVICE_E         = 4190,
	JOB_SUPER_BABY_E           = 4191,
	JOB_KAGEROU                = 4211,
	JOB_OBORO                  = 4212,
	JOB_REBELLION              = 4215,
	JOB_SUMMONER               = 4218,
	JOB_MAX,
	JOB_INVALID                = JOB_MAX
};

struct entity_viewport_entry
{
	virtual entity_viewport_entry operator = (entity_viewport_entry const &right)
	{
		unit_type = right.unit_type;
		account_id = right.account_id;
		guid = right.guid;
		speed = right.speed;
		body_state = right.body_state;
		health_state = right.health_state;
		effect_state = right.effect_state;
		job_id = right.job_id;
		hair_style_id = right.hair_style_id;
		weapon_id = right.weapon_id;
		headgear_bottom_id = right.headgear_bottom_id;
		headgear_top_id = right.headgear_top_id;
		headgear_mid_id = right.headgear_mid_id;
		hair_color_id = right.hair_color_id;
		cloth_color_id = right.cloth_color_id;
		head_direction = right.head_direction;
		robe_id = right.robe_id;
		guild_id = right.guild_id;
		guild_emblem_version = right.guild_emblem_version;
		honor = right.honor;
		virtue = right.virtue;
		in_pk_mode = right.in_pk_mode;
		gender = right.gender;
		current_x = right.current_x;
		current_y = right.current_y;
		to_x = right.to_x;
		to_y = right.to_y;
		current_dir = right.current_dir;
		x_size = right.x_size;
		y_size = right.y_size;
		posture = right.posture;
		base_level = right.base_level;
		font = right.font;
		max_hp = right.max_hp;
		hp = right.hp;
		is_boss = right.is_boss;
		body_style_id = right.body_style_id;
		std::strncpy(name, right.name, MAX_UNIT_NAME_LENGTH);
		move_start_time = right.move_start_time;
		return *this;
	}

	entity_types unit_type{ENTITY_PLAYER};
	uint32_t account_id{0};
	uint32_t guid{0};
	int16_t speed{150};
	int16_t body_state{0};
	int16_t health_state{0};
	int32_t effect_state{0};
	int16_t job_id{0};
	uint16_t hair_style_id{0};
	uint32_t weapon_id{0};
	uint16_t headgear_bottom_id{0};
	uint16_t headgear_top_id{0};
	uint16_t headgear_mid_id{0};
	int16_t hair_color_id{0};
	int16_t cloth_color_id{0};
	directions head_direction{DIR_NORTH};
	uint16_t robe_id{0};
	uint32_t guild_id{0};
	int16_t guild_emblem_version{0};
	int16_t honor{0};
	int32_t virtue{0};
	uint8_t in_pk_mode{0};
	uint8_t gender{0};
	uint16_t current_x{0}, current_y{0}, current_dir{0};
	uint16_t to_x{0}, to_y{0};
	uint8_t x_size{0};
	uint8_t y_size{0};
	entity_posture_types posture{POSTURE_STANDING};
	int16_t base_level{0};
	int16_t font{0};
	int32_t max_hp{-1};
	int32_t hp{-1};
	uint8_t is_boss{0};
	uint16_t body_style_id{0};
	char name[MAX_UNIT_NAME_LENGTH]{0};
	uint32_t move_start_time;
};

#define MAX_VIEW_RANGE 14
#define DEFAULT_MOVEMENT_SPEED 150

#endif /* HORIZON_ZONE_GAME_ENTITY_DEFINITIONS */
