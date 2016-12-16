#pragma once
#include "../../settings.h"

using namespace cry;

class cryptosha::bitset_pool
{

public:

	friend std::ostream & operator<<(std::ostream& out, const bitset_pool &);

	friend bitset_pool operator^(const bitset_pool &, const bitset_pool &);	//xor

	friend bitset_pool operator&(const bitset_pool &, const bitset_pool &);	//conjunctor

	friend bitset_pool operator|(const bitset_pool &, const bitset_pool &);	//disjunctor

	bitset_pool& operator^=(const bitset_pool &);

	bitset_pool& operator&=(const bitset_pool &);

	bitset_pool& operator|=(const bitset_pool &);

	bitset_pool& operator=(const bitset_pool &);

	bitset_pool& operator=(std::initializer_list<bitset_t>);

	bitset_t operator[](size_type) const;

	//_____________________________________________

	bitset_pool();

	bitset_pool(size_type);

	bitset_pool(size_type, std::initializer_list<bitset_t>);

	bitset_pool(std::initializer_list<bitset_t>);

	bitset_pool(const std::vector<bitset_t> &);

	bitset_pool(const strings&);

	bitset_pool(const string_t&);

	bitset_pool(const bitset_pool&);


	void add(bitset_t);

	void add(const bitset_pool &);

	bitset_t remove(bitset_t);

	size_type size() const;

	size_type bitset_len() const;

	~bitset_pool();

private:
	std::set<bitset_t> pool;
	size_type _bitset_len;
};

