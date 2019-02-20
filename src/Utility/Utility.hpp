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

#ifndef HORIZON_UTILITIES_UTILITY_HPP
#define HORIZON_UTILITIES_UTILITY_HPP

#include <cstdint>
#include <ctime>
#include <chrono>
#include <cstring>

uint32_t getMSTime();
uint32_t getMSTimeDiff(uint32_t oldMSTime, uint32_t newMSTime);
uint32_t GetMSTimeDiffToNow(uint32_t oldMSTime);

int64_t get_sys_time();

uint32_t rgb2bgr(uint32_t rgb);

const char *TimeStamp2String(char *str, size_t size, time_t timestamp, const char *format);
// Reorders bytes from network to little endian (Windows).
// Necessary for sending port numbers to the RO client until Gravity notices that they forgot ntohs() calls.
uint16_t ntows(uint16_t netshort);

// client-side: x0+=sx0*0.0625-0.5 and y0+=sy0*0.0625-0.5
void PackPosition(int8_t *p, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t sx0, uint8_t sy0);
void PackPosition(int8_t *p, uint16_t x, uint16_t y, uint8_t dir);
void UnpackPosition(const uint8_t *p, uint16_t *x, uint16_t *y, uint8_t *dir);

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

uint32_t Concatenate(uint32_t a, uint32_t b);
#endif // HORIZON_UTILITY_UTILITY_HPP
