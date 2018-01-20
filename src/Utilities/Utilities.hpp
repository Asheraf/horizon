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

#ifndef HORIZON_UTILITIES_H
#define HORIZON_UTILITIES_H

inline uint32_t getMSTime()
{
	using namespace std::chrono;

	static const steady_clock::time_point ApplicationStartTime = steady_clock::now();

	return uint32_t(duration_cast<milliseconds>(steady_clock::now() - ApplicationStartTime).count());
}

inline uint32_t getMSTimeDiff(uint32_t oldMSTime, uint32_t newMSTime)
{
	// getMSTime() have limited data range and this is case when it overflow in this tick
	if (oldMSTime > newMSTime)
		return (0xFFFFFFFF - oldMSTime) + newMSTime;
	else
		return newMSTime - oldMSTime;
}

inline uint32_t GetMSTimeDiffToNow(uint32_t oldMSTime)
{
	return getMSTimeDiff(oldMSTime, getMSTime());
}

inline const char *TimeStamp2String(char *str, size_t size, time_t timestamp, const char *format)
{
	size_t len = 0;

	if (str == nullptr)
		return nullptr;

	len = strftime(str, size, format, localtime(&timestamp));

	memset(str + len, '\0', size - len);

	return str;
}

#endif //HORIZON_UTILITIES_H
