/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#ifndef HORIZON_MODELS_GUILD_AFFILIATIONS_HPP
#define HORIZON_MODELS_GUILD_AFFILIATIONS_HPP

namespace Horizon
{
namespace Models
{
namespace Guild
{
enum affiliation_type
{
	AFFTYPE_ANTAGONIST,
	AFFTYPE_ALLIANCE
};
class Affiliation
{
public:
	Affiliation() { }
	~Affiliation() { }

	/* Guild ID */
	uint32_t get_guild_id() { return _guild_id; }
	void set_guild_id(uint32_t guild_id) { _guild_id = guild_id; }
	/* Affiliation Type */
	void setAntagonist(uint32_t guild_id) { _affiliate_id = guild_id; _type = AFFTYPE_ANTAGONIST; }
	void setAlliance(uint32_t guild_id) { _affiliate_id = guild_id; _type = AFFTYPE_ALLIANCE; }
	bool isAlly() { return _type == AFFTYPE_ALLIANCE; }
	bool isAntagonist() { return _type == AFFTYPE_ANTAGONIST; }
	/* Affiliate */
	uint32_t getAffiliateID() { return _affiliate_id; }
	void setAffiliateID(uint32_t guild_id) { _affiliate_id = guild_id; }

private:
	uint32_t _guild_id;
	affiliation_type _type;
	uint32_t _affiliate_id;
}
}
}
}
#endif /* HORIZON_MODELS_GUILD_AFFILIATIONS_HPP */
