#pragma once

#include "./basic_element.h"

using namespace cry;

template<class F>
class elements::binary : public elements::basic_element
{
	 F baseFunction;
public:
	explicit binary(size_type vector_size) : basic_element(vector_size * 2, vector_size) {} ;
	virtual ~binary() = default;
	bitset_t run() override
	{
		auto half_size = m_input.size() / 2;
		
		auto left  = bitset_t(half_size);
		auto right = bitset_t(half_size);

		for (size_t i = 0; i < half_size; ++i)
		{
			left[i]  = m_input[i];
			right[i] = m_input[i + half_size];
		}

		m_output = baseFunction(left, right);

		return m_output;
	}


};


namespace bf {

	using _bit_t = bitset_t;
	using std_bin_func_bits = std::binary_function
		<
		_bit_t,
		_bit_t,
		_bit_t
		>;

	struct xor :
		std_bin_func_bits
	{
		_bit_t operator()(_bit_t a, _bit_t b) const
		{
			return a ^ b;
		}
	};

	struct or :
		std_bin_func_bits
	{
		_bit_t operator()(_bit_t a, _bit_t b) const
		{
			return (a | b);
		}
	};

	struct and :
		std_bin_func_bits
	{
		_bit_t operator()(_bit_t a, _bit_t b) const
		{
			return a & b;
		}
	};

	struct nand :
		std_bin_func_bits
	{
		_bit_t operator()(_bit_t a, _bit_t b) const
		{
			return (a & b).flip();
		}
	};

	struct nor :
		std_bin_func_bits
	{
		_bit_t operator()(_bit_t a, _bit_t b) const
		{
			return (a | b).flip();
		}
	};

	struct equal :
		std_bin_func_bits
	{
		_bit_t operator()(_bit_t a, _bit_t b) const
		{
			return (a ^ b).flip();
		}
	};

	struct sum :
		std_bin_func_bits
	{
		_bit_t operator()(_bit_t a, _bit_t b) const
		{
			return _bit_t(a.to_ulong() + b.to_ulong(), a.size());
		}
	};
}


class elements::conjunctor : public elements::binary<bf::and>
{
public : explicit conjunctor(size_type vector_size) : binary<bf::and>(vector_size) {};
};

class elements::disjunctor : public elements::binary<bf::or>
{
public: explicit disjunctor(size_type vector_size) : binary<bf::or>(vector_size) {};
};

class elements::xor : public elements::binary<bf::xor>
{
public: explicit xor(size_type vector_size) : binary<bf::xor>(vector_size) {};
};

class elements::nor : public elements::binary<bf::nor>
{
public: explicit nor(size_type vector_size) : binary<bf::nor>(vector_size) {};
};

class elements::nand : public elements::binary<bf::nand>
{
public: explicit nand(size_type vector_size) : binary<bf::nand>(vector_size) {};
};

class elements::equality : public elements::binary<bf::equal>
{
public: explicit equality(size_type vector_size) : binary<bf::equal>(vector_size) {};
};

class elements::sum : public elements::binary<bf::sum>
{
public: explicit sum(size_type vector_size) : binary<bf::sum>(vector_size) {};
};




