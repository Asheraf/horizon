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

#include "Utilities.hpp"

#include <chrono>
#include <cstring>

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

// Reorders bytes from network to little endian (Windows).
// Necessary for sending port numbers to the RO client until Gravity notices that they forgot ntohs() calls.
uint16_t ntows(uint16_t netshort)
{
	return (uint16_t) (((netshort & 0xFF) << 8) | ((netshort & 0xFF00) >> 8));
}


inline void PackPosition(uint8_t *p, short x, short y, unsigned char dir) {
	p[0] = (uint8_t) (x >> 2);
	p[1] = (uint8_t) ((x << 6) | ((y >> 4) & 0x3f));
	p[2] = (uint8_t) ((y << 4) | (dir & 0xf));
}


// little endian char array to uint conversion
unsigned int GetULong(unsigned char* p)
{
	return (p[0] << 0 | p[1] << 8 | p[2] << 16 | p[3] << 24);
}

// Reads a float (32 bits) from the buffer
float GetFloat(const unsigned char* buf)
{
	uint32_t val = GetULong((unsigned char *) buf);
	return *((float *) (void *) &val);
}

// Converts an int16 from current machine order to little-endian
int16_t MakeShortLE(int16_t val)
{
	unsigned char buf[2];
	buf[0] = (unsigned char)( (val & 0x00FF)         );
	buf[1] = (unsigned char)( (val & 0xFF00) >> 0x08 );
	return *((int16_t *)buf);
}

// Converts an int32 from current machine order to little-endian
int32_t MakeLongLE(int32_t val)
{
	unsigned char buf[4];
	buf[0] = (unsigned char)( (val & 0x000000FF)         );
	buf[1] = (unsigned char)( (val & 0x0000FF00) >> 0x08 );
	buf[2] = (unsigned char)( (val & 0x00FF0000) >> 0x10 );
	buf[3] = (unsigned char)( (val & 0xFF000000) >> 0x18 );
	return *((int32_t *)buf);
}

// Reads an uint16 in little-endian from the buffer
uint16_t GetUShort(const unsigned char* buf)
{
	return (((uint16_t) (buf[0]))) | (((uint16_t)(buf[1])) << 0x08);
}

// Reads an uint32 in little-endian from the buffer
uint32_t GetULong(const unsigned char* buf)
{
	return (((uint32_t) (buf[0])))
	| (((uint32_t)(buf[1])) << 0x08)
	| (((uint32_t)(buf[2])) << 0x10)
	| (((uint32_t)(buf[3])) << 0x18);
}

// Reads an int32 in little-endian from the buffer
int32_t GetLong(const unsigned char *buf)
{
	return (int32_t) GetULong(buf);
}
