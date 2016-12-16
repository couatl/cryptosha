#include "analysis.h"

using namespace cry;

namespace cryptosha
{
	analysis::analysis(scheme_ptr _scheme)
	{
		scheme = _scheme;
	}

	analysis::bitset_count analysis::gretest_potentional(element_ptr obj, const string_t & diff, const bitset_pool & input)
	{
		bitset_count potentionals;
		std::vector<bitset_t> buf;
		string_t res;

		for (size_t i = 0; i < input.size(); i++)
		{
			for (size_t j = i + 1; j < input.size(); j++)
			{
				if (foo::bitset_to_hex(input[j] ^ input[i]) == diff)
				{

					obj->set_input(input[i]);
					bitset_t buf1 = obj->run();
					obj->set_input(input[j]);
					bitset_t buf2 = obj->run();
					buf.push_back(buf1 ^ buf2);

					potentionals[buf1 ^ buf2] = 0;
				}
			}
		}
		
		for (size_t i = 0; i < buf.size(); i++)
			potentionals[buf[i]]++;

		for (auto i = potentionals.begin(); i != potentionals.end(); ++i)
		{
			i->second = i->second / buf.size();
		}

		/*bitset_t w = max_element(potentionals.begin(), potentionals.end(),
			[&](pair_bitset_num i, pair_bitset_num j)->bool {return (i.second < j.second); })->first;

		std::cout << "max: " << w << std::endl;

		res = foo::bitset_to_hex(max_element(potentionals.begin(), potentionals.end(),
			[&](pair_bitset_num i, pair_bitset_num j)->bool {return (i.second < j.second); })->first);*/

		return potentionals;
	}

	cipher_scheme::id_bitset analysis::run_layer(layer_t layer, const bitset_pool & input)
	{
		size_type k = 0;
		cipher_scheme::id_bitset res;
		for (auto it = layer.begin(); it != layer.end(); ++it)
		{
			auto element = scheme->element(*it);
			/*i->second->set_input(input[k]);
			res[i->first] = i->second->run();*/
		}
		return res;
	}

	bitset_pool analysis::run_scheme(const bitset_pool & input)
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

	analysis::bitset_map analysis::run_element(element_ptr obj, const bitset_pool & input)	//need to be added size control
	{
		bitset_map res;
		for (size_t i = 0; i < input.size(); i++)
		{
			res.insert({ input[i] , obj->set_input(input[i]).run() });
		}
		return res;
	}

}