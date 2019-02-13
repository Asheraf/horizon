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

#include "Utility.hpp"
#include <sys/time.h>

uint32_t getMSTime()
{
	using namespace std::chrono;

	static const steady_clock::time_point ApplicationStartTime = steady_clock::now();

	return uint32_t(duration_cast<milliseconds>(steady_clock::now() - ApplicationStartTime).count());
}

uint32_t getMSTimeDiff(uint32_t oldMSTime, uint32_t newMSTime)
{
	// getMSTime() have limited data range and this is case when it overflow in this tick
	if (oldMSTime > newMSTime)
		return (0xFFFFFFFF - oldMSTime) + newMSTime;
	else
		return newMSTime - oldMSTime;
}

uint32_t rgb2bgr(uint32_t rgb)
{
	return (((rgb) & 0x0000FF) << 16 | ((rgb) & 0x00FF00) | ((rgb) & 0xFF0000) >> 16);
}

uint32_t GetMSTimeDiffToNow(uint32_t oldMSTime)
{
	return getMSTimeDiff(oldMSTime, getMSTime());
}

uint32_t get_sys_time()
{
	struct timeval tval;

	gettimeofday(&tval, NULL);

	return (uint32_t) (tval.tv_sec * 1000 + tval.tv_usec / 1000);
}

const char *TimeStamp2String(char *str, size_t size, time_t timestamp, const char *format)
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

void PackPosition(int8_t *p, uint16_t x, uint16_t y, uint8_t dir)
{
	p[0] = (int8_t) (x >> 2);
	p[1] = (int8_t) ((x << 6) | ((y >> 4) & 0x3f));
	p[2] = (int8_t) ((y << 4) | (dir & 0xf));
}

void UnpackPosition(const uint8_t *p, uint16_t *x, uint16_t *y, uint8_t *dir)
{
	if (x != nullptr)
		*x = ((p[0] & 0xff) << 2) | (p[1] >> 6);
	if (y != nullptr)
		*y = ((p[1] & 0x3f) << 4) | (p[2] >> 4);
	if (dir != nullptr)
		*dir = (p[2] & 0x0f);
}

// client-side: x0+=sx0*0.0625-0.5 and y0+=sy0*0.0625-0.5
void PackPosition(int8_t *p, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t sx0, uint8_t sy0) {
	p[0] = (int8_t) (x0 >> 2);
	p[1] = (int8_t) ((x0 << 6) | ((y0 >> 4) & 0x3f));
	p[2] = (int8_t) ((y0 << 4) | ((x1 >> 6) & 0x0f));
	p[3] = (int8_t) ((x1 << 2) | ((y1 >> 8) & 0x03));
	p[4] = (int8_t) y1;
	p[5] = (int8_t) ((sx0 << 4) | (sy0 & 0x0f));
}

// little endian char array to uint conversion
unsigned int GetULong(unsigned char *p)
{
	return (p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24);
}

// Reads a float (32 bits) from the buffer
float GetFloat(const unsigned char *buf)
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

uint32_t Concatenate(uint32_t a, uint32_t b)
{
	uint32_t magnitude = 1;
	while(magnitude <= b)
		magnitude *= 10;
	return magnitude * a + b;
}
