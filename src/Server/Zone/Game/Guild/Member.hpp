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

#ifndef HORIZON_MODELS_GUILD_MEMBERS_HPP
#define HORIZON_MODELS_GUILD_MEMBERS_HPP

namespace Horizon
{
namespace Models
{
namespace Guild
{
class Member
{
public:
	Member() { }
	~Member() { }

	/* Guild ID */
	uint32_t get_guild_id() { return _guild_id; }
	void set_guild_id(uint32_t guild_id) { _guild_id = guild_id; }
	/* Character ID */
	uint32_t get_character_id() { return _character_id; }
	void set_character_id(uint32_t char_id) { _character_id = char_id; }
	/* Experience Paid */
	uint64_t getExperiencePaid() { return _experience_paid; }
	void setExperiencePaid(uint32_t exp) { _experience_paid = exp; }
	/* Tax Percent */
	uint8_t getTaxPercent() { return _tax_percent; }
	void setTaxPercent(uint8_t percent) { _tax_percent = percent; }
	/* Position ID */
	uint8_t getPositionID() { return _position_id; }
	void setPositionID(uint8_t pos) { _position_id = pos; }
	
private:
	uint32_t _guild_id;
	uint32_t _character_id;
	uint64_t _experience_paid;
	uint8_t _tax_percent;
	uint8_t _position_id;
}
}
}
}

#endif /* HORIZON_MODELS_GUILD_MEMBERS_HPP */
