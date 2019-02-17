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
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_MODELS_GUILD_POSITION_HPP
#define HORIZON_MODELS_GUILD_POSITION_HPP

namespace Horizon
{
namespace Models
{
namespace Guild
{
enum permission_mask_types
{
	GPERM_INVITE   = 0x01,
	GPERM_EXPEL    = 0x10,
	GPERM_ALL      = GPERM_INVITE | GPERM_EXPEL,
};
class Position
{
public:
	Position() { }
	~Position() { }

	/* Guild ID */
	uint32_t get_guild_id() { return _guild_id; }
	void set_guild_id(uint32_t guild_id) { _guild_id = guild_id; }
	/* Position ID */
	uint8_t get_id() { return _character_id; }
	void set_id(uint8_t char_id) { _character_id = char_id; }
	/* Position Name */
	std::string &get_name() { return _name; }
	void set_name(std::string const &name) { _name = name; }
	/* Permission Mask */
	uint32_t getPermissionsMask() { return _permission_mask; }
	void setPermissionsMask(uint32_t permissions) { _permission_mask = permissions; }
	/* Tax Percent */
	uint8_t getTaxPercent() { return _tax_percent; }
	void setTaxPercent(uint8_t percent) { _tax_percent = percent; }

private:
	uint32_t _guild_id;
	uint8_t _position_id;
	std::string _name;
	permission_mask_types _permission_mask;
	uint8_t _tax_percent;
}
}
}
}

#endif /* HORIZON_MODELS_GUILD_POSITION_HPP */
