//
// Created by SagunKho on 22/06/2017.
//

#ifndef HORIZON_TOKENIZER_H
#define HORIZON_TOKENIZER_H

#include <algorithm>
#include <string>
#include <vector>
#include <chrono>

class Tokenizer
{
	public:
	typedef std::vector<char const *> StorageType;

	typedef StorageType::size_type size_type;

	typedef StorageType::const_iterator const_iterator;
	typedef StorageType::reference reference;
	typedef StorageType::const_reference const_reference;

	public:
	Tokenizer(const std::string &src, char const sep, uint32_t vectorReserve = 0, bool keepEmptyStrings = true);
	~Tokenizer() { delete[] m_str; }

	const_iterator begin() const { return m_storage.begin(); }
	const_iterator end() const { return m_storage.end(); }

	size_type size() const { return m_storage.size(); }

	reference operator [] (size_type i) { return m_storage[i]; }
	const_reference operator [] (size_type i) const { return m_storage[i]; }

	private:
	char* m_str;
	StorageType m_storage;
};

#endif //HORIZON_TOKENIZER_H