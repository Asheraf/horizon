/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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

#include "SubAttributes.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/Entities/Traits/Attributes.hpp"
#include "Server/Zone/Game/Entities/Player/Assets/Inventory.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"

#include <time.h>
#include <random>

using namespace Horizon::Zone::Entities::Traits;

uint32_t MaxWeight::compute()
{
	if (get_entity() == nullptr || _str.expired())
		return 0;

	std::shared_ptr<const job_db_data> job = JobDB->get(get_entity()->job_id());
	std::shared_ptr<Strength> str = _str.lock();

	return job->max_weight + str->get_base() * 300;
}

uint32_t StatusATK::compute()
{
	uint32_t blvl = 1, str = 1, dex = 1, luk = 1;

	std::shared_ptr<BaseLevel> sblvl = _blvl.lock();
	std::shared_ptr<Strength> sstr = _str.lock();
	std::shared_ptr<Dexterity> sdex = _dex.lock();
	std::shared_ptr<Luck> sluk = _luk.lock();

	if (sblvl != nullptr)
		blvl = sblvl->get_base();

	if (sstr != nullptr)
		str = sstr->total();

	if (sdex != nullptr)
		dex = sdex->total();

	if (sluk != nullptr)
		luk = sluk->total();

	// Ranged: floor[(BaseLevel ÷ 4) + (Str ÷ 5) + Dex + (Luk ÷ 3)]
	if (((1ULL << _weapon_type) & IT_WTM_RANGED) & ~(1ULL<<IT_WT_FIST))
		return dex + (blvl / 4) + (str / 5) + (luk / 3);

	// Melee: floor[(BaseLevel ÷ 4) + Str + (Dex ÷ 5) + (Luk ÷ 3)]
	return str + (blvl / 4) + (dex / 5) + (luk / 3);
}

uint32_t StatusMATK::compute()
{
	uint32_t blvl = 1, int_ = 1, dex = 1, luk = 1;

	std::shared_ptr<BaseLevel> sblvl = _blvl.lock();
	std::shared_ptr<Intelligence> sint = _int.lock();
	std::shared_ptr<Dexterity> sdex = _dex.lock();
	std::shared_ptr<Luck> sluk = _luk.lock();

	if (sblvl != nullptr)
		blvl = sblvl->get_base();
	if (sint != nullptr)
		int_ = sint->total();
	if (sdex != nullptr)
		dex = sdex->total();
	if (sluk != nullptr)
		luk = sluk->total();

	// floor[floor[BaseLevel ÷ 4] + Int + floor[Int ÷ 2] + floor[Dex ÷ 5] + floor[Luk ÷ 3]]
	return int_ + (blvl / 4) + (int_ / 2) + (dex / 5) + (luk / 3);
}

uint32_t SoftDEF::compute()
{
	uint32_t vit = 1;

	std::shared_ptr<Vitality> svit = _vit.lock();

	if (svit != nullptr)
		vit = svit->total();

	// (VIT ÷ 2) + Max[(VIT × 0.3), (VIT ^ 2 ÷ 150) − 1]
	return (vit / 2) + std::max((vit * 0.3), (std::pow(vit, 2) / 150) - 1);
}

uint32_t SoftMDEF::compute()
{
	uint32_t blvl = 1, int_ = 1, dex = 1, vit = 1;

	std::shared_ptr<BaseLevel> sblvl = _blvl.lock();
	std::shared_ptr<Intelligence> sint = _int.lock();
	std::shared_ptr<Dexterity> sdex = _dex.lock();
	std::shared_ptr<Vitality> svit = _vit.lock();

	if (sblvl != nullptr)
		blvl = sblvl->get_base();
	if (sint != nullptr)
		int_ = sint->total();
	if (sdex != nullptr)
		dex = sdex->total();
	if (svit != nullptr)
		vit = svit->total();

	// INT + VIT ÷ 5 + DEX ÷ 5 + BaseLv ÷ 4
	return int_ + (vit / 5) + (dex / 5) + (blvl / 4);
}

uint32_t HIT::compute()
{
	uint32_t blvl = 1, dex = 1, luk = 1;

	std::shared_ptr<BaseLevel> sblvl = _blvl.lock();
	std::shared_ptr<Dexterity> sdex = _dex.lock();
	std::shared_ptr<Luck> sluk = _luk.lock();

	if (sblvl != nullptr)
		blvl = sblvl->get_base();
	if (sdex != nullptr)
		dex = sdex->total();
	if (sluk != nullptr)
		luk = sluk->total();

	// 175 + BaseLv + DEX + Floor(LUK ÷ 3) + Bonus
	return 175 + blvl + dex + (luk / 3);
}

uint32_t CRIT::compute()
{
	uint32_t luk = 1;

	std::shared_ptr<Luck> sluk = _luk.lock();

	if (sluk != nullptr)
		luk = sluk->total();

	// LUK × 0.3 + Bonus
	return (luk / 3);
}

//! @brief Computes FLEE status based on agility, luck and Base Level.
//! FLEE = 100 + BaseLv + AGI + Floor(LUK ÷ 5)
uint32_t FLEE::compute()
{
	uint32_t blvl = 1, agi = 1, luk = 1;

	std::shared_ptr<Agility> sagi = _agi.lock();
	std::shared_ptr<BaseLevel> sblvl = _blvl.lock();
	std::shared_ptr<Luck> sluk = _luk.lock();

	if (sagi != nullptr)
		agi = sagi->total();
	if (sblvl != nullptr)
		blvl = sblvl->get_base();
	if (sluk != nullptr)
		luk = sluk->total();

	return 100 + blvl + agi + (luk / 5);
}

//! @brief Computes the EquipATK property of physical attacks.
//! EquipATK = floor[((BaseWeaponDamage + Variance + StatBonus + RefinementBonus + OverUpgradeBonus) × SizePenaltyMultiplier]
uint32_t EquipATK::compute()
{
	uint32_t str = 1, dex = 1;
	using namespace Horizon::Zone::Entities;

	if (get_entity() == nullptr || get_entity()->type() != ENTITY_PLAYER)
		return 0;

	std::shared_ptr<Player> player = get_entity()->downcast<Player>();
	std::shared_ptr<Strength> sstr = _str.lock();
	std::shared_ptr<Dexterity> sdex = _dex.lock();

	if (sstr) str = sstr->total();
	if (sdex) dex = sdex->total();

	EquippedItemsArray const &equipments = player->get_inventory()->get_equipments();

	std::shared_ptr<const item_entry_data> lhw = equipments[IT_EQPI_HAND_L].second.lock();
	std::shared_ptr<const item_entry_data> rhw = equipments[IT_EQPI_HAND_R].second.lock();

	if (lhw && lhw->type == IT_TYPE_WEAPON) {
		std::shared_ptr<const item_config_data> lhwd = ItemDB->get_item_by_id(lhw->item_id);
		assert(lhwd);
		// Base Weapon Damage
		_left_hand_val = lhwd->attack;
		// StatBonus = BaseWeaponDamage × (Melee: Str / Ranged: Dex) ÷ 200
		_left_hand_val += (lhwd->attack * (((1ULL<<lhwd->sub_type.weapon_t) & IT_WTM_MELEE) ? str : dex) / 200.00f);
	} else {
		_left_hand_val = 0;
	}

	if (rhw && rhw->type == IT_TYPE_WEAPON) {
		std::shared_ptr<const item_config_data> rhwd = ItemDB->get_item_by_id(rhw->item_id);
		assert(rhwd);
		// Base Weapon Damage
		_right_hand_val = rhwd->attack;
		// StatBonus = BaseWeaponDamage × (Melee: Str / Ranged: Dex) ÷ 200
		_right_hand_val += (rhwd->attack * (((1ULL<<rhwd->sub_type.weapon_t) & IT_WTM_MELEE) ? str : dex) / 200.00f);
	} else {
		_right_hand_val = 0;
	}

	return _left_hand_val + _right_hand_val;
}

uint32_t EquipATK::compute_variance(uint8_t weapon_lvl, uint32_t base_weapon_dmg)
{
	using namespace Horizon::Zone::Entities;

	srand(time(0));

	return floor(((rand() % 1000 + (-500)) / 10000.f) * weapon_lvl * base_weapon_dmg);
}

// uint32_t AttackSpeed::compute()
// {
// 	int amotion;
// 	int classidx = pc_class2idx(get_entity()->job_id());

// 	std::shared_ptr<const job_db_data> job = JobDB->get(get_entity()->job_id());

// #ifdef RENEWAL_ASPD
// 	int16 skill_lv, val = 0;
// 	float temp_aspd = 0;

// 	amotion = job->weapon_base_aspd[_weapon_type1]; // Single weapon
	
// 	EquippedItemsArray const &equipments = player->get_inventory()->get_equipments();

// 	std::shared_ptr<const item_entry_data> lhw = equipments[IT_EQPI_HAND_L].second.lock();
// 	std::shared_ptr<const item_entry_data> rhw = equipments[IT_EQPI_HAND_R].second.lock();

// 	if (_weapon_type2 != W_FIST && lhw != rhw)
// 		amotion += job_info[classidx].aspd_base[sd->weapontype2] / 4; // Dual-wield

// 	switch(sd->status.weapon) {
// 		case W_BOW:
// 		case W_MUSICAL:
// 		case W_WHIP:
// 		case W_REVOLVER:
// 		case W_RIFLE:
// 		case W_GATLING:
// 		case W_SHOTGUN:
// 		case W_GRENADE:
// 			temp_aspd = status->dex * status->dex / 7.0f + status->agi * status->agi * 0.5f;
// 			break;
// 		default:
// 			temp_aspd = status->dex * status->dex / 5.0f + status->agi * status->agi * 0.5f;
// 			break;
// 	}
// 	temp_aspd = (float)(sqrt(temp_aspd) * 0.25f) + 0xc4;
// 	if ((skill_lv = pc_checkskill(sd,SA_ADVANCEDBOOK)) > 0 && sd->status.weapon == W_BOOK)
// 		val += (skill_lv - 1) / 2 + 1;
// 	if ((skill_lv = pc_checkskill(sd, SG_DEVIL)) > 0 && ((sd->class_&MAPID_THIRDMASK) == MAPID_STAR_EMPEROR || pc_is_maxjoblv(sd)))
// 		val += 1 + skill_lv;
// 	if ((skill_lv = pc_checkskill(sd,GS_SINGLEACTION)) > 0 && (sd->status.weapon >= W_REVOLVER && sd->status.weapon <= W_GRENADE))
// 		val += ((skill_lv + 1) / 2);
// 	if ((skill_lv = pc_checkskill(sd, RG_PLAGIARISM)) > 0)
// 		val += skill_lv;
// 	if (pc_isriding(sd))
// 		val -= 50 - 10 * pc_checkskill(sd, KN_CAVALIERMASTERY);
// 	else if (pc_isridingdragon(sd))
// 		val -= 25 - 5 * pc_checkskill(sd, RK_DRAGONTRAINING);
// 	amotion = ((int)(temp_aspd + ((float)(status_calc_aspd(&sd->bl, &sd->sc, true) + val) * status->agi / 200)) - min(amotion, 200));
// #else
// 	// Angra Manyu disregards aspd_base and similar
// 	if (pc_checkequip2(sd, ITEMID_ANGRA_MANYU, EQI_ACC_L, EQI_MAX))
// 		return 0;

// 	// Base weapon delay
// 	amotion = (sd->status.weapon < MAX_WEAPON_TYPE)
// 	 ? (job_info[classidx].aspd_base[sd->status.weapon]) // Single weapon
// 	 : (job_info[classidx].aspd_base[sd->weapontype1] + job_info[classidx].aspd_base[sd->weapontype2]) * 7 / 10; // Dual-wield

// 	// Percentual delay reduction from stats
// 	amotion -= amotion * (4 * status->agi + status->dex) / 1000;

// 	// Raw delay adjustment from bAspd bonus
// 	amotion += sd->bonus.aspd_add;
// #endif

//  	return amotion;
// }


