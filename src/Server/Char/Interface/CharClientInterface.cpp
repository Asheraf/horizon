/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
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

#include "CharClientInterface.hpp"

#include "Libraries/Argon2/Argon2.hpp"
#include "Server/Common/SQL/GameAccount.hpp"
#include "Server/Common/SQL/SessionData.hpp"
#include "Server/Common/SQL/Character/Character.hpp"
#include "Server/Common/SQL/Character/Status.hpp"
#include "Server/Common/SQL/Character/Inventory.hpp"

#include "Server/Char/Char.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Server/Char/Packets/TransmittedPackets.hpp"

#include "Server/Common/SQL/GameAccount.hpp"

#include <date/date.h>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/functions.h>
#include <sqlpp11/insert.h>


#include <memory>

using namespace Horizon::Char;

CharClientInterface::CharClientInterface(std::shared_ptr<CharSession> s)
: ClientInterface(s)
{
	
}

CharClientInterface::~CharClientInterface()
{
}

std::string CharClientInterface::ip_addr() { return get_session()->get_socket()->remote_ip_address(); }

bool CharClientInterface::authorize_new_connection(uint32_t account_id, uint32_t auth_code, uint32_t account_level, uint8_t gender)
{
	SQL::TableSessionData tsd;
	SQL::TableGameAccounts tga;
	
	std::shared_ptr<sqlpp::mysql::connection> conn = sChar->get_db_connection();
	
	HLog(warning) << "A new connection has been established from I.P. " << ip_addr();
	
	auto sres = (*conn)(select(all_of(tsd)).from(tsd).where(tsd.game_account_id == account_id));

	if (sres.empty()) {
		HC_REFUSE_ENTER hcre(get_session());
		HLog(warning) << "Invalid connection for account with ID " << account_id << ", session wasn't found.";
		hcre.deliver(CHAR_ERR_REJECTED_FROM_SERVER);
		return false;
	}
	
	auto gres = (*conn)(select(all_of(tga)).from(tga).where(tga.id == account_id));
	
	if (gres.empty()) {
		HC_REFUSE_ENTER hcre(get_session());
		HLog(error) << "Game Account with ID " << account_id << " does not exist.";
		hcre.deliver(CHAR_ERR_REJECTED_FROM_SERVER);
		return false;
	}
	
	HC_ACCOUNT_ID hcad(account_id, get_session());
	HC_ACCEPT_ENTER2 hcae2(get_session());
	HC_ACCEPT_ENTER hcae(get_session());
	HC_BLOCK_CHARACTER hcbc(get_session());
	
	hcad.deliver();
	hcae2.deliver(gres.front().character_slots, MAX_CHARACTER_SLOTS - gres.front().character_slots);
	hcae.prepare_and_deliver(account_id, MAX_CHARACTER_SLOTS, gres.front().character_slots, MAX_CHARACTER_SLOTS - gres.front().character_slots);
	hcbc.deliver();
	
	s_session_data sd;
	sd._account_id = account_id;
	sd._auth_id = auth_code;
	sd._group_id = account_level;
	sd._connect_time = std::chrono::system_clock::now();
	sd._character_slots = gres.front().character_slots;
	get_session()->set_session_data(sd);
	
	{ // Pin-code related
	  // Session data is updated here after being set prior.
		std::string pincode = gres.front().pincode;
		std::time_t pexp_t = gres.front().pincode_expiry;

		HC_SECOND_PASSWD_LOGIN hcspl(get_session());

		if (pincode.size() == 0)
			hcspl.deliver(PINCODE_REQUEST_NEW);
		else if (std::time(0) > pexp_t)
			hcspl.deliver(PINCODE_REQUEST_CHANGE);
		else
			hcspl.deliver(PINCODE_REQUEST_PIN);
	}
	
	(*conn)(update(tsd).set(tsd.current_server = "C").where(tsd.game_account_id == account_id));
	
	// update with auth code.
	return true;
}

bool CharClientInterface::make_new_character(std::string name, uint8_t slot, uint32_t hair_color, uint32_t hair_style, uint32_t job_class, uint8_t gender)
{
	SQL::TableCharacters tch;
	SQL::TableCharacterStatus tcs;
	SQL::TableCharacterInventory tci;
	
	HC_REFUSE_MAKECHAR hcref(get_session());
	
	std::shared_ptr<sqlpp::mysql::connection> conn = sChar->get_db_connection();
	
	auto res = (*conn)(select(all_of(tch)).from(tch).where(tch.name == name || tch.deleted_at < std::chrono::system_clock::now()));

	if (!res.empty()) {
		hcref.deliver(HC_CREATE_ERROR_ALREADY_EXISTS);
		HLog(info) << "Character creation denied for already existing character '" << name << "'. (Endpoint: " << ip_addr() << ")";
		return false;
	}
	
	if (slot > get_session()->get_session_data()._character_slots) {
		hcref.deliver(HC_CREATE_ERROR_CHAR_SLOT);
		return false;
	}
	
	std::string new_map = sChar->config().get_start_map();
	uint16_t x = sChar->config().get_start_x(), y = sChar->config().get_start_y();
	
	int c_last_insert_id = (*conn)(insert_into(tch).set(tch.account_id = get_session()->get_session_data()._account_id, tch.slot = slot, tch.name = name,
														 tch.current_map = new_map, tch.current_x = x, tch.current_y = y,
														 tch.saved_map = new_map, tch.saved_x = x, tch.saved_y = y, tch.gender = gender ? "M" : "F"));
	
	(*conn)(insert_into(tcs).set(tcs.id = c_last_insert_id, tcs.job_id = job_class, tcs.hair_color_id = hair_color, tcs.hair_style_id = hair_style));
	
	auto multi_insert = insert_into(tci).columns(tci.char_id, tci.inventory_index, tci.item_id, tci.amount, tci.is_identified);
	int inv_index = 2;
	
	for (int j = 0; j < sChar->config().get_start_item_count(); j++) {
		std::pair<uint32_t, uint32_t> p = sChar->config().get_start_item(j);
		int item = p.first, c = p.second;
		multi_insert.values.add(tci.char_id = c_last_insert_id, tci.inventory_index = inv_index, tci.item_id = item, tci.amount = c, tci.is_identified = 1);
		inv_index++;
	}
	
	uint16_t start_zeny = sChar->config().get_start_zeny();
	
	HC_ACCEPT_MAKECHAR am(get_session());
	am.deliver(c_last_insert_id, start_zeny, new_map, name, slot, hair_color, hair_style, job_class, gender);
	
	HLog(info) << "New character '" << name << "' has been created. (Endpoint: " << ip_addr() << ")";
	return true;
}

bool CharClientInterface::make_new_character(std::string name, uint8_t slot, uint8_t hair_color, uint8_t hair_style)
{
	return make_new_character(name, slot, hair_color, hair_style, 0, 99);
}

character_delete_result CharClientInterface::character_delete_soft(uint32_t character_id)
{
	SQL::TableCharacters tch;
	
	std::shared_ptr<sqlpp::mysql::connection> conn = sChar->get_db_connection();
	
	auto res = (*conn)(select(all_of(tch)).from(tch).where(tch.id == character_id));
	
	if (res.empty())
		return CHAR_DEL_RESULT_DATABASE_ERR;
	
	if (res.front().guild_id > 0)
		return CHAR_DEL_RESULT_GUILD_ERR;
	
	if (res.front().party_id > 0)
		return CHAR_DEL_RESULT_PARTY_ERR;
	
	std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point dt = t + std::chrono::seconds(sChar->config().get_character_deletion_time());
	
	(*conn)(update(tch).set(tch.deleted_at = dt).where(tch.id == character_id));
	
	return CHAR_DEL_RESULT_SUCCESS;
}

bool CharClientInterface::character_delete_email(uint32_t character_id, std::string email)
{
	HC_REFUSE_DELETECHAR rd(get_session());
	HC_ACCEPT_DELETECHAR ad(get_session());
	
	if (character_delete_soft(character_id) != CHAR_DEL_RESULT_SUCCESS) {
		rd.deliver();
		return false;
	}
	
	ad.deliver();
	
	return true;
}

bool CharClientInterface::character_delete_birthdate(uint32_t character_id, std::string birthdate)
{
	SQL::TableGameAccounts tga;
	SQL::TableCharacters tch;
	SQL::TableCharacterInventory tci;
	SQL::TableCharacterStatus tcs;
	HC_DELETE_CHAR3 dc3(get_session());
	
	std::shared_ptr<sqlpp::mysql::connection> conn = sChar->get_db_connection();
	
	auto res = (*conn)(select(tga.birth_date, tga.character_slots).from(tga).where(tga.id == get_session()->get_session_data()._account_id));
	
	if (res.empty()) {
		HLog(error) << "Attempt to delete character with non-existent game-account. (CID: " << character_id << ", AID:" << get_session()->get_session_data()._account_id << ")";
		dc3.deliver(character_id, CHAR_DEL_ACCEPT_RESULT_SYSTEM_ERR);
		return false;
	}
	
	std::string bd = "000000";
	
	if (!res.front().birth_date.is_null()) {
		std::chrono::system_clock::time_point tp = res.front().birth_date.value();
		bd = date::format("%Y%m%d", tp).substr(2, 7);
	}
	
	if (bd.compare(birthdate) != 0) {
		dc3.deliver(character_id, CHAR_DEL_ACCEPT_RESULT_BIRTHDAY_ERR);
		return false;
	}
	
	if (sChar->config().get_char_hard_delete()) {
		(*conn)(remove_from(tcs).where(tcs.id == character_id));
		(*conn)(remove_from(tci).where(tci.char_id == character_id));
		(*conn)(remove_from(tch).where(tch.id == character_id));
	}
	
	dc3.deliver(character_id, CHAR_DEL_ACCEPT_RESULT_SUCCESS);

	HC_ACK_CHARINFO_PER_PAGE cpp(get_session());
	cpp.prepare_and_deliver();
	
	return true;
}

bool CharClientInterface::character_delete_reserve(uint32_t character_id)
{
	HC_DELETE_CHAR3_RESERVED dc(get_session());
	
	character_delete_result result = character_delete_soft(character_id);
	
	if (result != CHAR_DEL_RESULT_SUCCESS) {
		dc.deliver(character_id, result, 0);
		return false;
	}
	
	std::chrono::system_clock::time_point tp = std::chrono::system_clock::now() + std::chrono::seconds(sChar->config().get_character_deletion_time());
	uint32_t dt = tp.time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
	uint32_t tt = std::chrono::system_clock::now().time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
	
	dc.deliver(character_id, CHAR_DEL_RESULT_SUCCESS, dt - tt);
	
	return true;
}

bool CharClientInterface::character_delete_cancel(uint32_t char_id)
{
	SQL::TableCharacters tch;
	HC_DELETE_CHAR3_CANCEL dcc(get_session());
	
	std::shared_ptr<sqlpp::mysql::connection> conn = sChar->get_db_connection();
	
	auto res = (*conn)(select(tch.deleted_at).from(tch).where(tch.id == char_id));
	
	if (res.empty()) {
		dcc.deliver(char_id, CHAR3_DEL_CANCEL_FAILURE);
		return false;
	}
	
	(*conn)(update(tch).set(tch.deleted_at = sqlpp::null).where(tch.id == char_id));
	dcc.deliver(char_id, CHAR3_DEL_CANCEL_SUCCESS);
	return true;
}

bool CharClientInterface::pincode_create(uint32_t account_id, char *pincode)
{
	SQL::TableGameAccounts tga;
	HC_MAKE_SECOND_PASSWD makestate(get_session());
	HC_SECOND_PASSWD_LOGIN login(get_session());
	
	char decrypted[5] = "\0\0\0\0";
	
	uint32_t seed = get_session()->get_session_data()._pincode_seed;
	pincode_decrypt(seed, pincode, decrypted);
	
	{
		std::shared_ptr<sqlpp::mysql::connection> conn = sChar->get_db_connection();
		std::chrono::system_clock::time_point tp = std::chrono::system_clock::now() + std::chrono::seconds(sChar->config().get_pincode_expiry());
		uint32_t pincode_expiry = tp.time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
		(*conn)(update(tga).set(tga.pincode = decrypted, tga.pincode_expiry = pincode_expiry).where(tga.id == account_id));
	}
	
	strncpy(_pincode_confirm, decrypted, MAX_PINCODE_STRING_LENGTH);
	makestate.deliver(PINCODE_MAKE_SUCCESS);
	login.deliver(PINCODE_REQUEST_PIN);
	return true;
}

bool CharClientInterface::pincode_change(uint32_t account_id, char *old_pin, char *new_pin)
{
	SQL::TableGameAccounts tga;
	HC_SECOND_PASSWD_LOGIN sp(get_session());
	HC_EDIT_SECOND_PASSWD esp(get_session());
	
	std::shared_ptr<sqlpp::mysql::connection> conn = sChar->get_db_connection();

	char old_decrypted[5] = "\0\0\0\0", new_decrypted[5] = "\0\0\0\0";
	
	uint32_t seed = get_session()->get_session_data()._pincode_seed;
	
	pincode_decrypt(seed, old_pin, old_decrypted);
	pincode_decrypt(seed, new_pin, new_decrypted);
	
	std::cout << old_decrypted << " - " << new_decrypted << std::endl;
	
	auto res = (*conn)(select(tga.pincode).from(tga).where(tga.id == account_id));
	
	std::string s_pincode = res.front().pincode;
	
	if (s_pincode.compare(old_decrypted) != 0) {
		esp.deliver(PINCODE_EDIT_FAILED);
#if CLIENT_TYPE == 'M' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20180131
		sp.deliver(PINCODE_INCORRECT, PINCODE_LOGIN_FLAG_WRONG);
#else
		sp.deliver(PINCODE_INCORRECT);
#endif
		return false;
	}
	
	{
		std::chrono::system_clock::time_point tp = std::chrono::system_clock::now() + std::chrono::seconds(sChar->config().get_pincode_expiry());
		uint32_t pincode_expiry = tp.time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
		(*conn)(update(tga).set(tga.pincode = new_decrypted, tga.pincode_expiry = pincode_expiry).where(tga.id == account_id));
	}
	
	esp.deliver(PINCODE_EDIT_SUCCESS);
	sp.deliver(PINCODE_CORRECT);
	return true;
}

void CharClientInterface::pincode_decrypt(uint32_t seed, char *input, char *output)
{
	int i;
	char tab[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	
	if (input == nullptr || output == nullptr)
		return;
	
	for (i = 1; i < 10; i++) {
		int pos;
		seed = 0x881234 + seed * 0x3498;
		pos = seed % (i + 1);
		if (i != pos) {
			tab[i] ^= tab[pos];
			tab[pos] ^= tab[i];
			tab[i] ^= tab[pos];
		}
	}
	
	for (i = 0; i < 4; i++) {
		if (input[i] < '0' || input[i] > '9')
			input[i] = '0';
		else
			input[i] = tab[input[i] - '0'];
	}
	
	sprintf(output, "%d%d%d%d", input[0], input[1], input[2], input[3]);
}

bool CharClientInterface::pincode_verify(uint32_t account_id, char *pincode)
{
	SQL::TableGameAccounts tga;
	HC_SECOND_PASSWD_LOGIN sp(get_session());
	
	std::shared_ptr<sqlpp::mysql::connection> conn = sChar->get_db_connection();
	
	if (get_session()->get_session_data()._pincode_tries == sChar->config().get_pincode_retry()) {
#if CLIENT_TYPE == 'M' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20180131
		sp.deliver(PINCODE_INCORRECT, PINCODE_LOGIN_FLAG_LOCKED);
#else
		sp.deliver(PINCODE_LOGIN_RESTRICT);
#endif
		return false;
	}
	
	char decrypted[5] = "\0\0\0\0";
	
	uint32_t seed = get_session()->get_session_data()._pincode_seed;
	pincode_decrypt(seed, pincode, decrypted);
	
	auto res = (*conn)(select(tga.pincode).from(tga).where(tga.id == account_id));
	
	std::string s_pincode = res.front().pincode;
	
	if (s_pincode.compare(decrypted) != 0) {
		get_session()->get_session_data()._pincode_tries++;
#if CLIENT_TYPE == 'M' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20180131
		sp.deliver(PINCODE_INCORRECT, PINCODE_LOGIN_FLAG_WRONG);
#else
		sp.deliver(PINCODE_INCORRECT);
#endif
		return false;
	}
	
	sp.deliver(PINCODE_CORRECT);
	return true;
}

bool CharClientInterface::select_character(uint8_t slot)
{
	SQL::TableCharacters tch;
	
	std::shared_ptr<sqlpp::mysql::connection> conn = sChar->get_db_connection();
	
	auto res = (*conn)(select(all_of(tch)).from(tch).where(tch.account_id == get_session()->get_session_data()._account_id and tch.slot == slot));
	
	if (res.empty()) {
		HC_REFUSE_ENTER hre(get_session());
		HLog(error) << "Attempt to select non-existent character in slot " << slot << " for account " << get_session()->get_session_data()._account_id << ".";
		hre.deliver(CHAR_ERR_REJECTED_FROM_SERVER);
		return false;
	}
	
	HC_NOTIFY_ZONESVR hnz(get_session());
	hnz.deliver(res.front().id, std::string(res.front().current_map).append(".gat"), inet_addr(sChar->config().get_zone_server_ip().c_str()), sChar->config().get_zone_server_port());
	
	return true;
}
