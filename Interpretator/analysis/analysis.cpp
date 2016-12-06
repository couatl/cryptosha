#include "analysis.h"

using namespace cry;

namespace cryptosha
{
	string_t analysis::gretest_potentional(element_ptr obj, const string_t & diff, const bitset_pool & input)
	{
		bitset_count potentionals;
		bitset_pool buf;
		string_t res;

		for (size_t i = 0; i < input.size(); i++)
		{
			for (size_t j = i + 1; j < input.size(); j++)
			{
				//bitset_t d = input[j] - input[i];
				if (foo::bitset_to_hex(input[j] ^ input[i]) == diff)
				{

					obj->set_input(input[i]);
					bitset_t buf1 = obj->run();
					obj->set_input(input[j]);
					bitset_t buf2 = obj->run();
					buf.add(buf1 ^ buf2);

					potentionals[buf1 ^ buf2] = 0;
				}
			}
		}
		//std::cout << count << std::endl;
		std::cout << buf << std::endl;
		for (size_t i = 0; i < buf.size(); i++)
			potentionals[buf[i]]++;

		for (auto i = potentionals.begin(); i != potentionals.end(); ++i)
		{
			std::cout << i->first << "->" << i->second << std::endl;
		}

		bitset_t w = max_element(potentionals.begin(), potentionals.end(),
			[&](pair_bitset_num i, pair_bitset_num j)->bool {return (i.second < j.second); })->first;

		std::cout << "max: " << w << std::endl;

		res = foo::bitset_to_hex(max_element(potentionals.begin(), potentionals.end(),
			[&](pair_bitset_num i, pair_bitset_num j)->bool {return (i.second < j.second); })->first);

		return res;
	}

	cipher_scheme::layer_bitsets_type analysis::run_layer(cipher_scheme::layer_type layer, const bitset_pool & input)
	{
		size_type k = 0;
		cipher_scheme::layer_bitsets_type res;
		for (auto i = layer.begin(); i != layer.end(); ++i)
		{
			i->second->set_input(input[k]);
			res[i->first] = i->second->run();
		}
		return res;
	}

	bitset_pool analysis::run_scheme(xScheme_ptr scheme, const bitset_pool & input)
	{
		bitset_pool res;
		for (size_t i = 0; i < input.size(); i++)
		{
			scheme->set_input(input[i]);
			//pairs[input[i]] = scheme->run();
			res.add(scheme->run());
		}
		//std::cout << *this << std::endl;
		return res;
	}

	bitset_pool analysis::run_element(element_ptr obj, const bitset_pool & input)	//need to be added size control
	{
		bitset_pool res;
		for (size_t i = 0; i < input.size(); i++)
		{
			obj->set_input(input[i]);
			//pairs[input[i]] = obj->run();
			res.add(obj->run());
		}
		//std::cout << *this << std::endl;
		return res;
	}

}