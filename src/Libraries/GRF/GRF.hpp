/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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

#ifndef HORIZON_LIBRARIES_GRF_GRF_HPP
#define HORIZON_LIBRARIES_GRF_GRF_HPP

#include "DES.hpp"

#include <cstdlib>
#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>

enum datafile_type
{
	DATAFILE_TYPE_FILE          = 0x01, // entry is a file
	DATAFILE_TYPE_DES_MIXED     = 0x02, // encryption mode 0 (header DES + periodic DES/shuffle)
	DATAFILE_TYPE_DES_HEADER    = 0x04, // encryption mode 1 (header DES only)
};

enum grf_load_result_type
{
	GRF_LOAD_OK                  = 0,
	GRF_LOAD_PATH_ERROR          = 1,
	GRF_LOAD_INCOMPLETE_HEADER   = 2,
	GRF_LOAD_MAGIC_ERROR         = 3,
	GRF_LOAD_FORMAT_ERROR        = 4,
	GRF_LOAD_INVALID_VERSION     = 5,
	GRF_LOAD_HEADER_READ_ERROR   = 6,
	GRF_LOAD_ILLEGAL_DATA_FORMAT = 7,
	GRF_LOAD_READ_ERROR          = 8,
};

enum grf_file_error_type
{
	GRF_FILE_ERROR_NONE          = 0,
	GRF_FILE_ERROR_NAME_TOO_LONG = 1
};

enum grf_read_error_type
{
	GRE_OK                       = 0,
	GRE_NOT_FOUND                = 1,
	GRE_READ_ERROR               = 2,
	GRE_DECOMPRESS_SIZE_MISMATCH = 3,
};

struct DataFile
{
	int compressed_size; // compressed size
	int compressed_aligned_size;
	int original_size; // original size
	int entry_position; // position of entry in grf
	int hash_table_position; // position in hash table.
	int next_hash_collision; // index of next DataFile entry with same hash (-1: end of entry chain)
	char type;
	char file_name[128 - 4 * 5]; // file name
};

class GRF
{
	typedef std::unordered_map<std::string, std::shared_ptr<DataFile>> FileMapType;
	typedef std::unordered_map<std::string, grf_file_error_type> FileErrorMapType;
public:
	GRF();
	grf_load_result_type load();
	void extractAllFiles();
	void extractFile(std::string file_name, std::string output_path, clock_t begin_time);
	std::pair<grf_read_error_type, uint8_t *> read(const char *in_name, int *size);
	void decode(unsigned char *buf, size_t len, char entry_type, int entry_len);
	void decodeFull(unsigned char *buf, size_t len, int cycle);
	void decodeHeader(unsigned char *buf, size_t len);
	void decodeShuffledBytes(BIT64 *src);
	uint8_t substituteObfuscatedByte(uint8_t in);

	uint8_t get_id() { return _id; }
	void set_id(uint8_t id) { _id = id; }

	/* Path */
	const boost::filesystem::path &getGRFPath() const { return _path; }
	void setGRFPath(std::string const &path) { _path = path; }
	/* Size */
	std::size_t getGRFSize() const { return _grf_size; }
	void setGRFSize(std::size_t const &size) { _grf_size = size; }
	/* Version */
	int getGRFVersion() const { return _grf_version; }
	void setGRFVersion(int version) { _grf_version = version; }
	/* Total Files */
	int getTotalFiles() const { return _total_files; }
	void setTotalFiles(int total) { _total_files = total; }

	FileMapType &getFileMap() { return _file_map; }
	FileErrorMapType &getFileErrorMap() { return _file_error_map; }

private:
	int _id;
	boost::filesystem::path _path;
	std::size_t _grf_size;
	int _grf_version;
	int _total_files;
	FileMapType _file_map;
	FileErrorMapType _file_error_map;
};


#endif // HORIZON_LIBRARIES_GRF_GRF_HPP
