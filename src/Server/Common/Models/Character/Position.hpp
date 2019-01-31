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

#ifndef HORIZON_MODELS_CHARACTERS_POSITION_HPP
#define HORIZON_MODELS_CHARACTERS_POSITION_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Server.hpp"

namespace Horizon
{
namespace Models
{
namespace Character
{
class Position
{
public:
	Position(uint32_t char_id)
	: _character_id(char_id)
	{}

	Position(uint32_t char_id, std::string const &start_map, uint16_t start_x, uint16_t start_y)
	: _character_id(char_id), _current_map(start_map), _current_x(start_x), _current_y(start_y),
	_saved_map(start_map), _saved_x(start_x), _saved_y(start_y)
	{
		//
	}

	~Position() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT `current_map`, `current_x`, `current_y`, `saved_map`, `saved_x`, `saved_y` FROM `character_position_data` WHERE `id` = ?";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto record = s.sql(query).bind(char_id).execute().fetchOne();

			if (record) {
				set_character_id(char_id);
				set_current_map(record[0]);
				set_current_x((uint16_t) record[1].get<int>());
				set_current_y((uint16_t) record[2].get<int>());
				set_saved_map(record[3]);
				set_saved_x((uint16_t) record[4].get<int>());
				set_saved_y((uint16_t) record[5].get<int>());
				s.close();
				return true;
			}
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Position::load: {}", e.what());
		}

		return false;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		std::string query = "REPLACE INTO `character_position_data` "
			"(`id`, `current_map`, `current_x`, `current_y`, `saved_map`, `saved_x`, `saved_y`) "
			"VALUES (?, ?, ?, ?, ?, ?, ?)";

		try {
			auto s = server->get_mysql_client()->getSession();
			s.sql(query)
					.bind(get_character_id(),
						  get_current_map(),
						  get_current_x(),
						  get_current_y(),
						  get_saved_map(),
						  get_saved_x(),
						  get_saved_y())
					.execute();
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Position::save: {}", e.what());
		}
	}

	/* Character ID */
	uint32_t get_character_id() const { return _character_id; }
	void set_character_id(uint32_t id) { _character_id = id; }
	/* Current Map */
	const std::string &get_current_map() const { return _current_map; }
	void set_current_map(const std::string &map) { _current_map = map; }
	/* Current X */
	uint16_t get_current_x() const { return _current_x; }
	void set_current_x(uint16_t current_x) { _current_x = current_x; }
	/* Current Y */
	uint16_t get_current_y() const { return _current_y; }
	void set_current_y(uint16_t current_y) { _current_y = current_y; }
	/* Saved Map */
	const std::string &get_saved_map() const { return _saved_map; }
	void set_saved_map(const std::string &saved_map) { _saved_map = saved_map; }
	/* Saved X */
	uint16_t get_saved_x() const { return _saved_x; }
	void set_saved_x(uint16_t saved_x) { _saved_x = saved_x; }
	/* Saved Y */
	uint16_t get_saved_y() const { return _saved_y; }
	void set_saved_y(uint16_t saved_y) { _saved_y = saved_y; }

private:
	uint32_t _character_id{0};
	std::string _current_map{""};
	uint16_t _current_x{0}, _current_y{0};
	std::string _saved_map{""};
	uint16_t _saved_x{0}, _saved_y{0};
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_POSITION_HPP
