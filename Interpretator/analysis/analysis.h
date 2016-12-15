#pragma once
#include "bitset_pool.h"
#include "../../xElements/xScheme.h"

using namespace cry;
using namespace elements;



//using bitset_to_bitset = std::map<bitset_t, bitset_t>;


class cryptosha::analysis
{
public:

	using bitset_count = std::map<bitset_t, size_type>;
	using pair_bitset_num = std::pair<bitset_t, size_type>;

	analysis(scheme_ptr);

	bitset_pool run_element(element_ptr obj, const bitset_pool & input);	//need to be added size control

	bitset_pool run_scheme(const bitset_pool & input);

	cipher_scheme::id_bitset run_layer(cipher_scheme::circuit_t::value_type layer, const bitset_pool & input);

	bitset_count gretest_potentional(element_ptr obj, const string_t & diff, const bitset_pool & input);

	~analysis() {}

	

private:
	scheme_ptr scheme;
};