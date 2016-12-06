#include "./settings.h"


using namespace cry;


string_t foo::bitset_to_str(const bitset_t& bs, size_type size)
	{
		if (bs.size() != size)
			throw std::invalid_argument(error_messages::inv_input);

		string_t str("");

		for (auto i = bs.size() - 1; i >= 0; --i)
		{
			str.push_back(bs[i] ? '1' : '0');
		}

		return str;
	}

	bitset_t foo::str_to_bitset(const string_t& str_bits, size_type size)
	{
		bitset_t bs(size);

		auto str = str_bits;

		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

		if (str.size() != size)
			throw exception_t(error_messages::inv_input);

		for (size_type i = 0; i < size; ++i)
		{
			char current_bit = str[size - 1 - i];

			if (current_bit != '0' && current_bit != '1')
				throw exception_t(error_messages::inv_input);

			bs[i] = (current_bit == '1');
		}

		return bs;
	}


	std::vector<bitset_t> foo::mask_to_bitset(const string_t & str)
	{
		/*if (str.size() != size)
		throw std::invalid_argument(msg::inv_input);*/


		std::vector<string_t> buff;
		buff.push_back(str);
		int i = 0;
		int flag;
		while (1)
		{
			flag = 0;
			for (size_t j = 0; j < buff[i].length(); j++)
			{
				if (buff[i][j] == '*')
				{
					string_t buff0 = buff[i];
					string_t buff1 = buff[i];
					buff0[j] = '0';
					buff1[j] = '1';
					buff.push_back(buff0);
					buff.push_back(buff1);
					buff.erase(buff.begin());
					flag = 1;
					break;
				}
			}
			if (flag == 0)
				break;

		}

		std::vector<bitset_t> vec;
		for (size_t i = 0; i < buff.size(); i++)
		{
			vec.push_back(bitset_t(buff[i]));
		}
		return vec;
	}



	bitset_t foo::hex_to_bitset(const string_t & str, size_type size)
	{
		string_t buf;

		for (size_t i = 0; i < str.length(); i++)
			buf.append(::cry::foo::hex_in_bin.find(str[i])->second);

		return bitset_t(buf.substr(buf.length() - size, size));
	}

	string_t foo::bitset_to_hex(const bitset_t& bs)
	{
		string_t buf, str, res;
		to_string(bs, str);
		size_type k = 0;
		for (int i = str.length() - 1; i > -1; --i)
		{
			if (k >= 4)
			{
				std::reverse(buf.begin(), buf.end());
				res.push_back(find_if(::cry::foo::hex_in_bin.begin(), ::cry::foo::hex_in_bin.end(), [&](std::pair<char, string_t> i)->bool {return (i.second == buf); })->first);
				buf.clear();
				k = 0;
			}

			if (k < 4)
			{
				buf.push_back(str[i]);
				k++;
			}

		}
		if (buf.size() != 0)
		{
			//std::reverse(buf.begin(), buf.end());
			while (buf.length() < 4)
				buf.push_back('0');
			std::reverse(buf.begin(), buf.end());
			//std::cout << "Buffer: " << buf << std::endl;
			res.push_back(find_if(::cry::foo::hex_in_bin.begin(), ::cry::foo::hex_in_bin.end(), [&](std::pair<char, string_t> i)->bool {return (i.second == buf); })->first);
		}
		std::reverse(res.begin(), res.end());
		return res;
	}


	int_vector foo::get_reverse(const int_vector& vector)
	{
		int_vector reversed(vector.size());

		for (size_type i = 0; i < vector.size(); ++i)
		{
			reversed[vector[i]] = i;
		}

		return reversed;
	}

	bool foo::is_invertible(const int_vector& vector)
	{
		std::set<int_vector::value_type> set(vector.cbegin(), vector.cend());

		if (set.size() != vector.size())
			return false;

		/*std::thread set_clear([&set]() { set.clear(); });
		set_clear.detach();*/


		return (*set.begin() == 0 && *set.rbegin() + 1 == vector.size());
	}


	bool foo::get_bit(const size_type & value, size_type pos)
	{
		return (value & (1 << pos));
	}


