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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#include "Utility.hpp"

#ifndef WIN32
#include <sys/time.h>
#else
#include <Windows.h>
#include <MMSystem.h>
#endif

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

int64_t get_sys_time()
{
#ifdef WIN32
	// Windows: GetTickCount/GetTickCount64: Return the number of
	//   milliseconds that have elapsed since the system was started.

	// TODO: GetTickCount/GetTickCount64 has a resolution of only 10~15ms.
	//       Ai4rei recommends that we replace it with either performance
	//       counters or multimedia timers if we want it to be more accurate.
	//       I'm leaving this for a future follow-up patch.

	// GetTickCount64 is only available in Windows Vista / Windows Server
	//   2008 or newer. Since we still support older versions, this runtime
	//   check is required in order not to crash.
	// http://msdn.microsoft.com/en-us/library/windows/desktop/ms724411%28v=vs.85%29.aspx
	static bool first = true;
	static ULONGLONG(WINAPI *pGetTickCount64)(void) = nullptr;

	if (first) {
		HMODULE hlib = GetModuleHandle(TEXT("KERNEL32.DLL"));
		if (hlib != nullptr)
			pGetTickCount64 = (ULONGLONG(WINAPI *)(void))GetProcAddress(hlib, "GetTickCount64");
		first = false;
	}
	if (pGetTickCount64)
		return (int64_t)pGetTickCount64();
	// 32-bit fall back. Note: This will wrap around every ~49 days since system startup!!!
	return (int64_t)GetTickCount();
#elif defined(CLOCK_MONOTONIC)
	// Monotonic clock: Implementation-defined.
	//   Clock that cannot be set and represents monotonic time since some
	//   unspecified starting point.  This clock is not affected by
	//   discontinuous jumps in the system time (e.g., if the system
	//   administrator manually changes the  clock),  but  is  affected by
	//   the  incremental adjustments performed by adjtime(3) and NTP.
	struct timespec tval;
	clock_gettime(CLOCK_MONOTONIC, &tval);
	// int64 cast to avoid overflows on platforms where time_t is 32 bit
	return (int64_t) (tval.tv_sec * 1000 + tval.tv_nsec / 1000000);
#else
	// Fall back, regular clock: Number of milliseconds since epoch.
	//   The time returned by gettimeofday() is affected by discontinuous
	//   jumps in the system time (e.g., if the system  administrator
	//   manually  changes  the system time).  If you need a monotonically
	//   increasing clock, see clock_gettime(2).
	struct timeval tval;
	gettimeofday(&tval, nullptr);
	// int64 cast to avoid overflows on platforms where time_t is 32 bit
	return (int64_t)tval.tv_sec * 1000 + tval.tv_usec / 1000;
#endif
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
