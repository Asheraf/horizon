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

#ifndef HORIZON_MODELS_GUILD_EXPULSIONLOG_HPP
#define HORIZON_MODELS_GUILD_EXPULSIONLOG_HPP

namespace Horizon
{
namespace Models
{
namespace Guild
{
class ExpulsionLog
{
public:
	ExpulsionLog() { }
	~ExpulsionLog() { }

	/* Guild ID */
	uint32_t getGuildID() { return _guild_id; }
	void setGuildID(uint32_t guild_id) { _guild_id = guild_id; }
	/* Expellee Name */
	std::string &getExpelleeName() { return _expellee_name; }
	void setExpelleeName(std::string const &name) { _expelle_name = name; }
	/* Reason */
	std::string &getReason() { return _reason; }
	void setReason(std::string const &reason) { _reason = reason; }

private:
	uint32_t _guild_id;
	std::string _expellee_name;
	std::string _reason;
}
}
}
}

#endif /* HORIZON_MODELS_GUILD_EXPULSIONLOG_HPP */
