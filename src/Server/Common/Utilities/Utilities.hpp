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

#ifndef HORIZON_UTILITIES_UTILITIES_HPP
#define HORIZON_UTILITIES_UTILITIES_HPP

#include <cstdint>
#include <ctime>

inline uint32_t getMSTime();
inline uint32_t getMSTimeDiff(uint32_t oldMSTime, uint32_t newMSTime);
inline uint32_t GetMSTimeDiffToNow(uint32_t oldMSTime);
inline const char *TimeStamp2String(char *str, std::size_t size, time_t timestamp, const char *format);
// Reorders bytes from network to little endian (Windows).
// Necessary for sending port numbers to the RO client until Gravity notices that they forgot ntohs() calls.
uint16_t ntows(uint16_t netshort);
inline void PackPosition(uint8_t *p, short x, short y, unsigned char dir);
// little endian char array to uint conversion
unsigned int GetULong(unsigned char* p);
// Reads a float (32 bits) from the buffer
float GetFloat(const unsigned char* buf);
// Converts an int16 from current machine order to little-endian
int16_t MakeShortLE(int16_t val);
// Converts an int32 from current machine order to little-endian
int32_t MakeLongLE(int32_t val);
// Reads an uint16 in little-endian from the buffer
uint16_t GetUShort(const unsigned char* buf);
// Reads an uint32 in little-endian from the buffer
uint32_t GetULong(const unsigned char* buf);
// Reads an int32 in little-endian from the buffer
int32_t GetLong(const unsigned char *buf);

#endif // HORIZON_UTILITIES_HPP
