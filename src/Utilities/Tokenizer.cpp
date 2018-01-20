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

#include "Tokenizer.hpp"

Tokenizer::Tokenizer(const std::string &src, const char sep, uint32_t vectorReserve /*= 0*/, bool keepEmptyStrings /*= true*/)
{
	m_str = new char[src.length() + 1];
	memcpy(m_str, src.c_str(), src.length() + 1);

	if (vectorReserve)
		m_storage.reserve(vectorReserve);

	char *posold = m_str;
	char *posnew = m_str;

	for (;;) {
		if (*posnew == sep) {
			if (keepEmptyStrings || posold != posnew)
				m_storage.push_back(posold);

			posold = posnew + 1;
			*posnew = '\0';
		} else if (*posnew == '\0') {
			// Hack like, but the old code accepted these kind of broken strings,
			// so changing it would break other things
			if (posold != posnew)
				m_storage.push_back(posold);

			break;
		}

		++posnew;
	}
}