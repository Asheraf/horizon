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

#include "GRF.hpp"
#include "Server/Common/Utilities/Utilities.hpp"
#include "Server/Common/Utilities/StrUtils.hpp"

#include <iostream>
#include <zlib.h>
#include <sys/stat.h>
#include <vector>
#include <sstream>
#include <codecvt>

#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/locale.hpp>
#include <thread>
#include <fstream>

GRF::GRF()
{
	//
}

int GRF::unpack(void *dest, unsigned long *dest_len, const void *source, unsigned long source_len)
{
	return uncompress((Bytef *) dest, dest_len, (const Bytef *) source, source_len);
}

int GRF::pack(void *dest, unsigned long *dest_len, const void *source, unsigned long source_len, int level)
{
	if (*dest_len == 0)
		*dest_len = compressBound(source_len);
	
	if (dest == NULL) {
		dest = new unsigned char[*dest_len];
	}
	
	return compress2((Bytef *) dest, dest_len, (const Bytef *) source, source_len, level);
}

/**
 * Substitutes some specific values for others, leaves rest intact. Obfuscation.
 * NOTE: Operation is symmetric (calling it twice gives back the original input).
 * @param[in] in    the byte needed to be swapped.
 * @return the substitute or itself if none.
 */
uint8_t GRF::substituteObfuscatedByte(uint8_t in)
{
	uint8_t out;

	switch (in) {
		case 0x00: out = 0x2B; break;
		case 0x2B: out = 0x00; break;
		case 0x6C: out = 0x80; break;
		case 0x01: out = 0x68; break;
		case 0x68: out = 0x01; break;
		case 0x48: out = 0x77; break;
		case 0x60: out = 0xFF; break;
		case 0x77: out = 0x48; break;
		case 0xB9: out = 0xC0; break;
		case 0xC0: out = 0xB9; break;
		case 0xFE: out = 0xEB; break;
		case 0xEB: out = 0xFE; break;
		case 0x80: out = 0x6C; break;
		case 0xFF: out = 0x60; break;
		default:   out = in;   break;
	}

	return out;
}

/**
 * Substitutes some specific values for others, leaves rest intact. Obfuscation.
 * NOTE: Operation is symmetric (calling it twice gives back the original input).
 * @param[in|out] src   source to be decoded.
 */
void GRF::decodeShuffledBytes(BIT64 *src)
{
	BIT64 out;

	out.b[0] = src->b[3];
	out.b[1] = src->b[4];
	out.b[2] = src->b[6];
	out.b[3] = src->b[0];
	out.b[4] = src->b[1];
	out.b[5] = src->b[2];
	out.b[6] = src->b[5];
	out.b[7] = substituteObfuscatedByte(src->b[7]);

	*src = out;
}

void GRF::decodeHeader(unsigned char* buf, size_t len)
{
	BIT64* p = (BIT64 *) buf;
	size_t nblocks = len / sizeof(BIT64);
	size_t i;

	DES *des = new DES();

	// first 20 blocks are all des-encrypted
	for (i = 0; i < 20 && i < nblocks; ++i)
		des->decryptBlock(&p[i]);

	// the rest is plaintext, done.
}

void GRF::decodeFull(unsigned char* buf, size_t len, int cycle)
{
	BIT64 *p = (BIT64 *)buf;
	size_t nblocks = len / sizeof(BIT64);
	int dcycle, scycle;
	size_t i, j;

	DES des;

	// first 20 blocks are all des-encrypted
	for (i = 0; i < 20 && i < nblocks; ++i)
		des.decryptBlock(&p[i]);

	// after that only one of every 'dcycle' blocks is des-encrypted
	dcycle = cycle;

	// and one of every 'scycle' plaintext blocks is shuffled (starting from the 0th but skipping the 0th)
	scycle = 7;

	// so decrypt/de-shuffle periodically
	j = -1; // 0, adjusted to fit the ++j step
	for (i = 20; i < nblocks; ++i) {
		if (i % dcycle == 0) { // decrypt block
			des.decryptBlock(&p[i]);
			continue;
		}

		++j;

		if (j % scycle == 0 && j != 0) { // de-shuffle block
			decodeShuffledBytes(&p[i]);
			continue;
		}
		// plaintext, do nothing.
	}
}

/// Decodes grf data.
/// @param buf data to decode (in-place)
/// @param len length of the data
/// @param entry_type flags associated with the data
/// @param entry_len true (unaligned) length of the data
void GRF::decode(unsigned char *buf, size_t len, char entry_type, int entry_len)
{
	if (entry_type & DATAFILE_TYPE_DES_MIXED) { // fully encrypted
		int digits;
		int cycle;
		int i;

		// compute number of digits of the entry length
		digits = 1;
		for( i = 10; i <= entry_len; i *= 10 )
			++digits;

		// choose size of gap between two encrypted blocks
		// digits:  0  1  2  3  4  5  6  7  8  9 ...
		//  cycle:  1  1  1  4  5 14 15 22 23 24 ...
		cycle = ( digits < 3 ) ? 1
				: ( digits < 5 ) ? digits + 1
					: ( digits < 7 ) ? digits + 9
						: digits + 15;

		decodeFull(buf, len, cycle);
	} else if (entry_type & DATAFILE_TYPE_DES_HEADER) { // header encrypted
		decodeHeader(buf, len);
	}
}

grf_load_result_types GRF::load()
{
	unsigned char grf_header[0x2e];
	std::ifstream grf_ifs(getGRFPath().c_str(), std::ios::in | std::ios::binary);

	/**
	 * Set the file pointer.
	 */
	if (!grf_ifs.good())
		return GRF_LOAD_PATH_ERROR;

	// Devise the number of bytes.
	grf_ifs.seekg(0, grf_ifs.end);
	_grf_size = grf_ifs.tellg();
	grf_ifs.seekg(0, grf_ifs.beg);

	if (!grf_ifs.read((char *) grf_header, 0x2e))
		return GRF_LOAD_INCOMPLETE_HEADER;

	if (std::strcmp((const char *) grf_header, "Master of Magic") != 0)
		return GRF_LOAD_MAGIC_ERROR;

	if (!grf_ifs.seekg(GetLong(grf_header + 0x1e), grf_ifs.cur))
		return GRF_LOAD_FORMAT_ERROR;

	// Set GRF Version.
	setGRFVersion((GetLong(grf_header + 0x2a) >> 8));

	if (getGRFVersion() != 0x02)
		return GRF_LOAD_INVALID_VERSION;

	unsigned char eheader[8];

	if (!grf_ifs.read((char *) eheader, 8))
		return GRF_LOAD_HEADER_READ_ERROR;

	unsigned long compressed_size = GetULong(eheader);	// Read Size
	unsigned long decompressed_size = GetULong(eheader + 4);	// Extend Size

	if (compressed_size > (unsigned long) (getGRFSize() - grf_ifs.tellg()))
		return GRF_LOAD_ILLEGAL_DATA_FORMAT;

	uint8_t *compressed_buf = new uint8_t[compressed_size];	// Get a Read Size
	uint8_t *decompressed_buf = new uint8_t[decompressed_size];	// Get a Extend Size

	if (!grf_ifs.read((char *) compressed_buf, compressed_size))
		return GRF_LOAD_READ_ERROR;

	unpack(decompressed_buf, &decompressed_size, compressed_buf, compressed_size);

	delete[] compressed_buf;

	setTotalFiles((GetLong(grf_header + 0x26) - 7));

	for (int entry = 0, ofs = 0; entry < getTotalFiles(); ++entry) {
		std::shared_ptr<DataFile> data_file = std::make_shared<DataFile>();
		char *fname = (char *) (decompressed_buf + ofs);
		int ofs2 = ofs + (int) strlen(fname) + 1;
		int type = decompressed_buf[ofs2 + 12];

		ofs = ofs2 + 17;

		if (strlen(fname) > sizeof(data_file->file_name) - 1) {
			getFileErrorMap().insert(std::make_pair(fname, GRF_FILE_ERROR_NAME_TOO_LONG));
			continue;
		}

		if (type & DATAFILE_TYPE_FILE) {// file
			data_file->compressed_size = GetLong(decompressed_buf + ofs2 + 0);
			data_file->compressed_aligned_size = GetLong(decompressed_buf + ofs2 + 4);
			data_file->original_size = GetLong(decompressed_buf + ofs2 + 8);
			data_file->entry_position = GetLong(decompressed_buf + ofs2 + 13) + 0x2E;
			data_file->type = type;
			std::memcpy(&data_file->file_name, fname, sizeof(data_file->file_name));
			getFileMap().insert(std::pair<std::string, std::shared_ptr<DataFile>>(data_file->file_name, data_file));
		}
	}

	delete[] decompressed_buf;

	return GRF_LOAD_OK;
}

void GRF::extractAllFiles()
{
	const clock_t begin_time = clock();

	int i = 0;
	for (auto &it : getFileMap()) {
		extractFile(it.second->file_name, ".", begin_time);
		i++;
	}
}

static int file_count = 0;
void GRF::extractFile(std::string file_name, std::string /*output_path*/, clock_t begin_time)
{
	auto elem = getFileMap().find(file_name);

	if (elem == getFileMap().end()) {
		return;
	}

	//std::cout << "File '" << elem->first << "' found. Size: " << elem->second->original_size << std::endl;

	std::string utf8_file_path = boost::locale::conv::to_utf<char>(file_name, "Latin1");

	std::vector<std::string> dirs = StrUtils::explode(utf8_file_path, '\\');

	std::string extracted_file_name = (dirs.end() - 1)->c_str();

	utf8_file_path = utf8_file_path.substr(0, std::strstr(utf8_file_path.c_str(), extracted_file_name.c_str()) - utf8_file_path.c_str());

	std::replace(utf8_file_path.begin(), utf8_file_path.end(), '\\', '/');

	try {
		boost::filesystem::path path = utf8_file_path;
		if (!boost::filesystem::is_directory(path))
			boost::filesystem::create_directories(path);
	} catch (boost::filesystem::filesystem_error &e) {
		std::cerr << e.what() << std::endl;
		return;
	}

	FILE *buf = std::fopen(utf8_file_path.append(extracted_file_name).c_str(), "w");

	if (buf == nullptr) {
		std::cout << "Extraction failed." << std::endl;
		return;
	}

	std::pair<grf_read_error_types, uint8_t*> grf_file = read(elem->second->file_name, nullptr);

	if (grf_file.second == nullptr) {
		std::cerr << "Failed to extract '" << elem->second->file_name << "'" <<std::endl;
		return;
	}

	std::fwrite(grf_file.second, elem->second->original_size, 1, buf);

	delete[] grf_file.second;

	std::fclose(buf);

	file_count++;

	std::cout << "Extracted (" << file_count << "/" << getFileMap().size() <<  ") '" << file_name << "' "
			  <<"(" << elem->second->compressed_size << " -> " << elem->second->original_size <<") "
			  << float( clock() - begin_time ) /  CLOCKS_PER_SEC << "s."  << std::endl;
}

/**
 * @brief
 */
std::pair<grf_read_error_types, uint8_t *> GRF::read(const char *in_name, int *size)
{
	std::string file_name = in_name;
	std::shared_ptr<DataFile> entry;
	uint8_t *file_buf = nullptr;

	auto it = getFileMap().find(file_name);

	if (it == getFileMap().end())
		return std::make_pair(GRE_NOT_FOUND, nullptr);

	entry = it->second;

	// Archive[GRF] File Read
	if (entry != nullptr) {
		std::ifstream grf_ifs(getGRFPath().c_str(), std::ios::in | std::ios::binary);
		uint8_t *grf_compressed_buf = new uint8_t[entry->compressed_aligned_size];

		grf_ifs.seekg(entry->entry_position, grf_ifs.beg);

		if (!grf_ifs.read((char *) grf_compressed_buf, entry->compressed_aligned_size)) {
			delete[] grf_compressed_buf;
			return std::make_pair(GRE_READ_ERROR, nullptr);
		}

		file_buf = new uint8_t[entry->original_size + 1];  // +1 for resnametable zero-termination

		if (entry->type & DATAFILE_TYPE_FILE) { // file
			uLongf len;
			decode(grf_compressed_buf, entry->compressed_aligned_size, entry->type, entry->compressed_size);
			len = entry->original_size;
			unpack(file_buf, &len, grf_compressed_buf, entry->compressed_size);
			if (len != (uLong) entry->original_size) {
				delete[] grf_compressed_buf;
				delete[] file_buf;
				return std::make_pair(GRE_DECOMPRESS_SIZE_MISMATCH, nullptr);
			}
		} else { // directory?
			std::memcpy(file_buf, grf_compressed_buf, entry->original_size);
		}

		if (size)
			*size = entry->original_size;

		delete[] grf_compressed_buf;
	}

	return std::make_pair(GRE_OK, file_buf);
}
