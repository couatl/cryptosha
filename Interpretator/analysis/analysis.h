#pragma once
#include "bitset_pool.h"
#include "../../xElements/xScheme.h"

using namespace cry;
using namespace elements;

using xScheme_ptr = std::unique_ptr<cipher_scheme>;
using bitset_count = std::map<bitset_t, size_type>;
using pair_bitset_num = std::pair<bitset_t, size_type>;
//using bitset_to_bitset = std::map<bitset_t, bitset_t>;


class cryptosha::analysis
{
public:

	analysis() {}

	bitset_pool run_element(element_ptr obj, const bitset_pool & input);	//need to be added size control

	bitset_pool run_scheme(xScheme_ptr scheme, const bitset_pool & input);

	cipher_scheme::layer_bitsets_type run_layer(cipher_scheme::layer_type layer, const bitset_pool & input);

	string_t gretest_potentional(element_ptr obj, const string_t & diff, const bitset_pool & input);


	~analysis() {}
};