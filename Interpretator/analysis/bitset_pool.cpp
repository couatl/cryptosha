#include "bitset_pool.h"

using namespace cry;
using namespace cryptosha;

namespace cryptosha
{

	bitset_pool::bitset_pool() : _bitset_len(0)
	{}

	bitset_pool::bitset_pool(size_type len) : _bitset_len(len)
	{}

	bitset_pool::bitset_pool(size_type len, std::initializer_list<bitset_t> values)
	{

		_bitset_len = len;
		for (auto it = values.begin(); it != values.end(); ++it)
		{
			if (it->size() != _bitset_len)
				throw std::invalid_argument("Wrong size of bitset");
			set.push_back(*it);
		}

	}

	bitset_pool::bitset_pool(std::initializer_list<bitset_t> values)
	{

		_bitset_len = values.begin()->size();
		for (auto it = values.begin(); it != values.end(); ++it)
		{
			if (it->size() != _bitset_len)
				throw std::invalid_argument("Wrong size of bitset");
			set.push_back(*it);
		}

	}

	bitset_pool::bitset_pool(const std::vector<bitset_t> & vec)
	{
		_bitset_len = vec[0].size();
		for (size_t i = 0; i < vec.size(); i++)
		{
			if (vec[i].size() != _bitset_len)
				throw std::invalid_argument("Invalid argument");
			set.push_back(vec[i]);
		}
	}

	bitset_pool::bitset_pool(const string_t & mask) : _bitset_len(size_type(mask.length()))
	{
		set = foo::mask_to_bitset(mask);
	}

	bitset_pool::bitset_pool(const bitset_pool & obj) : _bitset_len(obj.bitset_len())
	{
		for (auto it = obj.set.begin(); it != obj.set.end(); ++it)
			set.push_back(*it);
	}

	void bitset_pool::add(bitset_t obj)
	{
		if (size() == 0)
			_bitset_len = obj.size();
		else if (obj.size() != _bitset_len)
			throw std::invalid_argument("Wrong size of bitset");
		set.push_back(obj);
	}

	bitset_t bitset_pool::remove(bitset_t obj)
	{
		bitset_t a;
		for (auto i = set.begin(); i != set.end(); ++i)
		{
			if (*i == obj)
			{
				a = *i;
				set.erase(i);
				return a;
			}
		}
		return a;
	}

	size_type bitset_pool::size() const
	{
		return set.size();
	}

	size_type  bitset_pool::bitset_len() const
	{
		return _bitset_len;
	}

	bitset_pool::~bitset_pool()
	{}

	bitset_pool & bitset_pool::operator=(const bitset_pool & obj)
	{
		if (this == &obj)
			return *this;

		_bitset_len = obj.bitset_len();

		set.clear();

		for (size_t i = 0; i < _bitset_len; i++)
		{
			set.push_back(obj.set[i]);
		}
		return *this;
	}

	bitset_pool & bitset_pool::operator=(std::initializer_list<bitset_t> values)
	{
		for (auto it = values.begin(); it != values.end(); ++it)
		{
			if (it->size() != _bitset_len)
				throw std::invalid_argument("Wrong size of bitset");
			set.push_back(*it);
		}
		return *this;
	}

	bitset_t bitset_pool::operator[](size_type pos) const
	{
		return set[pos];
	}

	bitset_pool & bitset_pool::operator^=(const bitset_pool & obj)
	{
		if (obj.size() != this->size() || obj.bitset_len() != this->bitset_len())
			throw std::invalid_argument("Wrong size");
		for (size_t i = 0; i < obj.size(); i++)
			set[i] ^= obj.set[i];
		return *this;
	}

	bitset_pool & bitset_pool::operator&=(const bitset_pool & obj)
	{
		if (obj.size() != this->size() || obj.bitset_len() != this->bitset_len())
			throw std::invalid_argument("Wrong size");
		for (size_t i = 0; i < obj.size(); i++)
			set[i] &= obj.set[i];
		return *this;
	}

	bitset_pool & bitset_pool::operator|=(const bitset_pool & obj)
	{
		if (obj.size() != this->size() || obj.bitset_len() != this->bitset_len())
			throw std::invalid_argument("Wrong size");
		for (size_t i = 0; i < obj.size(); i++)
			set[i] |= obj.set[i];
		return *this;
	}

	std::ostream & operator<<(std::ostream& out, const bitset_pool & obj)
	{
		for (size_t i = 0; i < obj.size(); i++)
		{
			out << obj.set[i] << ' ';
		}
		out << std::endl;
		return out;
	}
}

bitset_pool operator^(const bitset_pool & obj1, const bitset_pool & obj2)
{
	bitset_pool a(obj1.bitset_len());
	a ^= obj2;
	return a;
}

bitset_pool operator&(const bitset_pool & obj1, const bitset_pool & obj2)
{
	bitset_pool a(obj1.bitset_len());
	a &= obj2;
	return a;
}

bitset_pool operator|(const bitset_pool & obj1, const bitset_pool & obj2)
{
	bitset_pool a(obj1.bitset_len());
	a &= obj2;
	return a;
}

