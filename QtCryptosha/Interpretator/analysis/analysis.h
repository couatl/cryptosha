#pragma once
#include "bitset_pool.h"
#include "../../xElements/graphic_scheme.h"

using namespace cry;
using namespace elements;



//using bitset_to_bitset = std::map<bitset_t, bitset_t>;


class cryptosha::analysis
{
public:

	using bitset_map = std::map<bitset_t, bitset_t>;
	using bitset_count = std::map<bitset_t, size_type>;
	using pair_bitset_num = std::pair<bitset_t, size_type>;
	using layer_t = cipher_scheme::circuit_t::value_type;

	analysis(scheme_ptr);

	bitset_map run_element(element_ptr obj, const bitset_pool & input);

	bitset_map run_scheme(const bitset_pool & input);

	cipher_scheme::id_bitset run_layer(layer_t layer, const bitset_pool & input);

	bitset_count gretest_potentional(element_ptr obj, const string_t & diff, const bitset_pool & input);

	~analysis() {}

	

private:
	scheme_ptr scheme;
};
