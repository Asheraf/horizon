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
#include "Core/Database/MySqlConnection.hpp"

namespace Horizon
{
namespace Models
{
namespace Character
{
class Position
{
public:
	Position() {}
	~Position() {}

	Position(std::string const &start_map, uint16_t start_x, uint16_t start_y)
	: _saved_map(start_map), _saved_x(start_x), _saved_y(start_y)
	{
		//
	}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT * FROM `character_position_data` WHERE `id` = ?";
		auto sql = server->MySQLBorrow();
		bool ret = false;

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, char_id);
			sql::ResultSet *res = pstmt->executeQuery();

			if (res != nullptr && res->next()) {
				/**
				 * Create Game Account Data
				 */
				setCharacterID(char_id);
				setCurrentMap(res->getString("current_map"));
				setCurrentX((uint16_t) res->getInt("current_x"));
				setCurrentY((uint16_t) res->getInt("current_y"));
				setSavedMap(res->getString("saved_map"));
				setSavedX((uint16_t) res->getInt("saved_x"));
				setSavedY((uint16_t) res->getInt("saved_y"));

				ret = true;
			}

			delete res;
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("Models::Character::Misc::LoadFromDatabase: {}", e.what());
		}

		server->MySQLUnborrow(sql);

		return ret;
	}

	/**
	 * @brief Save this model to the database in its current state.
	 * @param[in|out] server   instance of the server object used to borrow mysql connections.
	 */
	void save(Server *server)
	{
		auto sql = server->MySQLBorrow();

		std::string query = "REPLACE INTO `character_position_data` "
			"(`id`, `current_map`, `current_x`, `current_y`, `saved_map`, `saved_x`, `saved_y`) "
			"VALUES (?, ?, ?, ?, ?, ?, ?);";

		try {
			sql::PreparedStatement *pstmt = sql->getConnection()->prepareStatement(query);
			pstmt->setInt(1, getCharacterID());
			pstmt->setString(2, getCurrentMap());
			pstmt->setInt(3, getCurrentX());
			pstmt->setInt(4, getCurrentY());
			pstmt->setString(5, getSavedMap());
			pstmt->setInt(6, getSavedX());
			pstmt->setInt(7, getSavedY());
			pstmt->executeUpdate();
			delete pstmt;
		} catch (sql::SQLException &e) {
			DBLog->error("SQLException: {}", e.what());
		}

		server->MySQLUnborrow(sql);
	}

	/* Character ID */
	uint32_t getCharacterID() const { return _character_id; }
	void setCharacterID(uint32_t id) { _character_id = id; }
	/* Current Map */
	const std::string &getCurrentMap() const { return _current_map; }
	void setCurrentMap(const std::string &map) { _current_map = map; }
	/* Current X */
	uint16_t getCurrentX() const { return _current_x; }
	void setCurrentX(uint16_t current_x) { _current_x = current_x; }
	/* Current Y */
	uint16_t getCurrentY() const { return _current_y; }
	void setCurrentY(uint16_t current_y) { _current_y = current_y; }
	/* Saved Map */
	const std::string &getSavedMap() const { return _saved_map; }
	void setSavedMap(const std::string &saved_map) { _saved_map = saved_map; }
	/* Saved X */
	uint16_t getSavedX() const { return _saved_x; }
	void setSavedX(uint16_t saved_x) { _saved_x = saved_x; }
	/* Saved Y */
	uint16_t getSavedY() const { return _saved_y; }
	void setSavedY(uint16_t saved_y) { _saved_y = saved_y; }

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