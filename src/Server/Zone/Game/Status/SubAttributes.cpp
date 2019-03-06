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
 * Base Author - Sxyz (sagunxp@gmail.com)
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
#include "Server/Zone/Game/Status/Attributes.hpp"

using namespace Horizon::Zone::Game::Status;

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

	// floor[(BaseLevel ÷ 4) + Str + (Dex ÷ 5) + (Luk ÷ 3)]
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

	// 100 + BaseLv + AGI + Floor(LUK ÷ 5)
	return 100 + blvl + agi + (luk / 5);
}
