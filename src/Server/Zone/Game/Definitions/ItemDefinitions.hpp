/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_GAME_ITEM_DEFINITIONS
#define HORIZON_ZONE_GAME_ITEM_DEFINITIONS

#include <cstring>
#include <iostream>
#include <cstdlib>

enum weapon_type
{
	WT_FIST,      ///< Bare hands
	WT_DAGGER,    //1
	WT_1HSWORD,   //2
	WT_2HSWORD,   //3
	WT_1HSPEAR,   //4
	WT_2HSPEAR,   //5
	WT_1HAXE,     //6
	WT_2HAXE,     //7
	WT_1HMACE,      //8
	WT_2HMACE,    //9 (unused)
	WT_STAFF,     //10
	WT_BOW,       //11
	WT_KNUCKLE,   //12
	WT_MUSICAL,   //13
	WT_WHIP,      //14
	WT_BOOK,      //15
	WT_KATAR,     //16
	WT_REVOLVER,  //17
	WT_RIFLE,     //18
	WT_GATLING,   //19
	WT_SHOTGUN,   //20
	WT_GRENADE,   //21
	WT_HUUMA,     //22
	WT_2HSTAFF,   //23
	WT_SHIELD,    //24
	WT_MAX
};

enum item_gender_types
{
	IT_GENDER_FEMALE = 0,
	IT_GENDER_MALE   = 1,
	IT_GENDER_ANY    = 2
};

//Equip position constants
enum item_equip_location_mask {
	EQP_NONE               = 0x000000,
	EQP_HEAD_LOW           = 0x000001,
	EQP_HEAD_MID           = 0x000200, //512
	EQP_HEAD_TOP           = 0x000100, //256
	EQP_HAND_R             = 0x000002, //2
	EQP_HAND_L             = 0x000020, //32
	EQP_ARMOR              = 0x000010, //16
	EQP_SHOES              = 0x000040, //64
	EQP_GARMENT            = 0x000004, //4
	EQP_ACC_L              = 0x000008, //8
	EQP_ACC_R              = 0x000080, //128
	EQP_COSTUME_HEAD_TOP   = 0x000400, //1024
	EQP_COSTUME_HEAD_MID   = 0x000800, //2048
	EQP_COSTUME_HEAD_LOW   = 0x001000, //4096
	EQP_COSTUME_GARMENT    = 0x002000, //8192
	//UNUSED_COSTUME_FLOOR = 0x004000, //16384
	EQP_AMMO               = 0x008000, //32768
	EQP_SHADOW_ARMOR       = 0x010000, //65536
	EQP_SHADOW_WEAPON      = 0x020000, //131072
	EQP_SHADOW_SHIELD      = 0x040000, //262144
	EQP_SHADOW_SHOES       = 0x080000, //524288
	EQP_SHADOW_ACC_R       = 0x100000, //1048576
	EQP_SHADOW_ACC_L       = 0x200000, //2097152

	// Composites
	EQP_WEAPON             = EQP_HAND_R,
	EQP_SHIELD             = EQP_HAND_L,
	EQP_ARMS               = EQP_HAND_R | EQP_HAND_L,
	EQP_HELM               = EQP_HEAD_LOW | EQP_HEAD_MID | EQP_HEAD_TOP,
	EQP_ACC                = EQP_ACC_L | EQP_ACC_R,
	EQP_COSTUME            = EQP_COSTUME_HEAD_TOP | EQP_COSTUME_HEAD_MID | EQP_COSTUME_HEAD_LOW | EQP_COSTUME_GARMENT,
	EQP_SHADOW_ACC         = EQP_SHADOW_ACC_R | EQP_SHADOW_ACC_L,
	EQP_SHADOW_ARMS        = EQP_SHADOW_WEAPON | EQP_SHADOW_SHIELD
};

enum item_trade_restriction_mask {
	ITRMASK_NONE                   = 0x0000, ///< No restrictions
	ITRMASK_NO_DROP                = 0x0001, ///< Item can't be dropped
	ITRMASK_NO_TRADE               = 0x0002, ///< Item can't be traded (nor vended)
	ITRMASK_CAN_TRADEWPARTNER      = 0x0004, ///< Wedded partner can override ITR_NOTRADE restriction
	ITRMASK_NO_SELL_TO_NPC         = 0x0008, ///< Item can't be sold to NPCs
	ITRMASK_NO_CART                = 0x0010, ///< Item can't be placed in the cart
	ITRMASK_NO_STORAGE             = 0x0020, ///< Item can't be placed in the storage
	ITRMASK_NO_GSTORAGE            = 0x0040, ///< Item can't be placed in the guild storage
	ITRMASK_NO_MAIL                = 0x0080, ///< Item can't be attached to mail messages
	ITRMASK_NO_AUCTION             = 0x0100, ///< Item can't be auctioned
	ITRMASK_NO_BUYING_STORE        = 0x0200, ///< Item can't be listed in the buying store.
	ITRMASK_ALL                    = 0x03ff  ///< Sum of all the above values
};

enum item_usage_restriction_mask {
	IURMASK_NONE    = 0x0, ///< No restrictions
	IURMASK_SITTING = 0x1, ///< Item can't be used while sitting
	IURMASK_ALL     = 0x1  ///< Sum of all the above values
};

enum item_types {
	IT_TYPE_HEALING              = 0,
	IT_TYPE_UNKNOWN              = 1,
	IT_TYPE_USABLE               = 2,
	IT_TYPE_ETC                  = 3,
	IT_TYPE_WEAPON               = 4,
	IT_TYPE_ARMOR                = 5,
	IT_TYPE_CARD                 = 6,
	IT_TYPE_PET_EGG              = 7,
	IT_TYPE_PET_ARMOR            = 8,
	IT_TYPE_UNKNOWN2             = 9,
	IT_TYPE_AMMO                 = 10,
	IT_TYPE_CONSUMPTION_DELAY    = 11,
	IT_TYPE_CASH                 = 18,
	IT_TYPE_MAX
};

enum item_ammunition_types {
	AMMO_TYPE_NONE               = 0,
	AMMO_TYPE_ARROW              = 1,
	AMMO_TYPE_DAGGER             = 2,
	AMMO_TYPE_BULLET             = 3,
	AMMO_TYPE_SHELL              = 4,
	AMMO_TYPE_GRENADE            = 5,
	AMMO_TYPE_SHURIKEN           = 6,
	AMMO_TYPE_KUNAI              = 7,
	AMMO_TYPE_CANNONBALL         = 8,
	AMMO_TYPE_THROWABLE_WEAPON   = 9,
	AMMO_TYPE_MAX
};

struct item_data
{
	std::string name{""}, aegis_name{""};

	int32_t value_buy{0};
	int32_t value_sell{0};
	
	int type{0};

	union {
		int weapon_t;
		int ammo_t;
	} sub_type{0};

	uint64_t equip_location_mask{0};      ///< @see equip_location_mask type.
	uint32_t weight{0};
	int32_t attack{0};
	int32_t defense{0};
	int8_t attack_range{0};
	int8_t card_slot_count{0};
	uint32_t sprite_id{0};

	union {
		int8_t armor;
		int8_t weapon;
	} level{0};

	int32_t magic_atk{0};
	struct {
		int32_t max_lv{0};
		int32_t min_lv{0};
		int32_t job_mask{0};
		item_gender_types gender{IT_GENDER_ANY};
	} requirements{0};

	int drop_effect_mode{0};

	int delay{0};

	std::string default_script{""}; ///< Default script for everything.
	std::string equip_script{""};   ///< Script executed once when equipping.
	std::string unequip_script{""}; ///< Script executed once when unequipping.

	struct {
		unsigned available : 1;
		unsigned refineable : 1;
		unsigned consumption_delay : 1;         ///< Signifies items that are not consumed immediately upon double-click
		unsigned trade_restriction : 9;         ///< Item trade restrictions mask (@see enum item_trade_restrictions_mask)
		unsigned bind_on_equip : 1;
		unsigned allow_item_options: 1;            ///< disallows use of item options on the item. (non-equippable items are automatically flagged)
		unsigned drop_announce : 1;             ///< Official Drop Announce
		unsigned show_drop_effect : 1;          ///< Shows Drop Effect.
		struct {
			unsigned short max_amount{0};          ///< Max amount per stack.
			unsigned int inventory    : 1;
			unsigned int cart         : 1;
			unsigned int storage      : 1;
			unsigned int guildstorage : 1;
		} stack{0};
		struct {
			unsigned int mask{0};                  ///< Item nouse restriction mask (@see enum ItemNouseRestrictions)
		} usage_restriction{0};
	} config{0};
};

#define ITEM_NAME_LENGTH 50
#define UNKNOWN_ITEM_ID 512 // Apple

#endif /* HORIZON_ZONE_GAME_ITEM_DEFINITIONS */
