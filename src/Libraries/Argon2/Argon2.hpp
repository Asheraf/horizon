/***************************************************
*       _   _            _                        *
*      | | | |          (_)                       *
*      | |_| | ___  _ __ _ _______  _ __          *
*      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
*      | | | | (_) | |  | |/ / (_) | | | |        *
*      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
***************************************************
* This file is part of Horizon (c).
*
* Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
* Copyright (c) 2019 Horizon Dev Team.
*
* Base Author - Sagun Khosla <sagunxp@gmail.com>
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

#include "argon2.h"

#include <string>

#define HASHLEN 32
#define SALTLEN 16
#define ENCODED_LEN 108
#define PWD "password"

class Argon2Exception : public std::exception
{
public:
    Argon2Exception(std::string message) : _message(message) { }

    const char * what () const throw () {
       return _message.c_str();
    }
    
private:
    std::string _message;
};

class Argon2
{
public:
    Argon2() { }
    ~Argon2() { }

    std::string gen_hash(std::string pwd, std::string salt)
    {
        if (salt.size() > SALTLEN)
            throw Argon2Exception("Salt size exceeds default size of bytes.");

        //
        // ARGON2_PUBLIC int argon2_hash(const uint32_t t_cost, const uint32_t m_cost,
                              // const uint32_t parallelism, const void *pwd,
                              // const size_t pwdlen, const void *salt,
                              // const size_t saltlen, void *hash,
                              // const size_t hashlen, char *encoded,
                              // const size_t encodedlen, argon2_type type,
                              // const uint32_t version);
        int rc = argon2_hash(_t_cost, _m_cost, _parallelism, pwd.c_str(),
             pwd.size(), salt.c_str(), SALTLEN, _hash1, HASHLEN,
             _encoded, ENCODED_LEN, Argon2_i, ARGON2_VERSION_10);
        
        if (rc != ARGON2_OK)
            throw Argon2Exception("Argon2 hash was not created successfully.");
        
		std::string hash;
		for (int i = 0; i < HASHLEN; i++) {
			char fbuf[4];
			snprintf(fbuf, 4, "%02x", _hash1[i]);
			hash.append(1, fbuf[0]);
			hash.append(1, fbuf[1]);
		}
        return hash;
    }
    
    bool verify(std::string hash1, std::string pwd, std::string salt)
    {
        if (salt.size() > SALTLEN)
            throw Argon2Exception("Salt size exceeds default size of bytes.");
        
        std::string hash2 = gen_hash(pwd, salt);
        
        if (memcmp(hash1.data(), hash2.data(), HASHLEN * 2) == 0)
            return true;
        
        return false;
    }
    
private:
    uint8_t _hash1[HASHLEN]{ '\0' };
    uint32_t _t_cost{2},    // 1-pass computation
        _m_cost{(1<<16)},   // 64 megabytes memory usage
        _parallelism{1};    // number of threads and lanes 
    char _encoded[ENCODED_LEN]{ '\0' };
};
