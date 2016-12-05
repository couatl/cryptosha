#pragma once
#include "../settings.h"


#define myKeyWords

#ifdef myKeyWords
	#define methods
	#define states
	#define ctors
	#define dtor
	#define data
	#define static_data
#endif // myKeyWords

using namespace cry;

class elements::base_interface
{
	virtual bitset_t run(const bitset_t& input, size_type output_size) = 0;
	virtual element_ptr reverse() const = 0;
};


enum class state_t {
	nulled,           // input value is not set
	updated,          // input value is updated
	calculated        // output value is updated
};

class elements::basic_element 
{

public ctors:
	explicit basic_element(iosize_t::type size_in, iosize_t::type size_out);

	explicit basic_element(const basic_element&) = default;
	explicit basic_element(basic_element&&) = default;

public methods:
	basic_element& set_input(const bitset_t& input_bitset);
	basic_element& set_input(bitset_t&& input_bitset);
	basic_element& set_input(const string_t& input_bitstr);
	basic_element& set_input(string_t&& input_bitstr);
	basic_element& set_input(int_t value);

	basic_element& set_null();

	virtual bitset_t run() = 0;

	
	bitset_t input() const;
	bitset_t output() const;

	bitset_t& input_ref();

	bool output_bit(size_type bit_index);
	
	iosize_t size()  const;
	iosize_t::type osize() const;
	iosize_t::type isize() const;

	inline static size_type get_element_count();

	dtor virtual ~basic_element();

protected data:
	iosize_t  m_size;

	bitset_t  m_input;
	bitset_t  m_output;

protected states:
	state_t m_state;

private static_data:
	static size_type  g_obj_count;

private methods:	
	inline void _ctor();

};



#ifdef myKeyWords
	#undef methods
	#undef states
	#undef flags
	#undef ctors
	#undef dtor
	#undef data
	#undef static_data
	#undef myKeyWords
#endif // !myKeyWords


