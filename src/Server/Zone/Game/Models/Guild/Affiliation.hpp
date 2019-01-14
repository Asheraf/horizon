/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_MODELS_GUILD_AFFILIATIONS_HPP
#define HORIZON_MODELS_GUILD_AFFILIATIONS_HPP

namespace Horizon
{
namespace Models
{
namespace Guild
{
enum affiliation_types
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
	affiliation_types _type;
	uint32_t _affiliate_id;
}
}
}
}
#endif /* HORIZON_MODELS_GUILD_AFFILIATIONS_HPP */
