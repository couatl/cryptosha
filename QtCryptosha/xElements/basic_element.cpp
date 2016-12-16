#include "basic_element.h"

using namespace cry::elements;


size_type basic_element::g_obj_count = 0;


void basic_element::_ctor()
{
	++g_obj_count;
}


basic_element::basic_element(iosize_t::type in_size, iosize_t::type out_size) : m_size{ in_size, out_size },
	m_state(state_t::nulled), m_input(in_size), m_output(out_size)
{
	_ctor();
}



basic_element& basic_element::set_input(const bitset_t& input)
{
	if (m_size.in != input.size()) {
		throw exception_t(error_messages::inv_input);
	}

	m_input = input;

	return *this;
}
basic_element& basic_element::set_input(bitset_t&& input)
{
	if (m_size.in != input.size()) {
		throw exception_t(error_messages::inv_input);
	}

	m_input = std::move(input);

	return *this;
}
basic_element& basic_element::set_input(const string_t& str)
{
	return set_input(foo::str_to_bitset(str, m_size.in));
}
basic_element& basic_element::set_input(string_t&& str)
{
	return set_input(foo::str_to_bitset(str, m_size.in));
}
basic_element& basic_element::set_input(int_t value)
{
	m_input = bitset_t(m_size.in, value);
	return *this;
}

basic_element& basic_element::set_null()
{
	m_input = bitset_t(m_size.in, 0);
	return *this;
}


bitset_t basic_element:: input() const
{
	return m_input;
}
bitset_t basic_element::output() const
{
	return m_output;
}

bitset_t& basic_element::input_ref()
{
	return m_input;
}

bitset_t& elements::basic_element::output_ref()
{
	return m_output;
}

bool elements::basic_element::input(size_type bit)
{
	return m_input[bit];
}

bool elements::basic_element::output(size_type bit)
{
	return m_output[bit];
}


iosize_t basic_element::size() const
{
	return m_size;
}
iosize_t::type basic_element::osize() const
{
	return m_size.out;
}
iosize_t::type basic_element::isize() const
{
	return m_size.in;
}

inline size_type basic_element::get_element_count()
{
	return g_obj_count;
}

basic_element::~basic_element()
{
	--g_obj_count;
}

std::ostream& operator<<(std::ostream& ostr, const basic_element& element_names)
{
	ostr
		<< "[ "
		<< element_names.input()
		<< " -> "
		<< element_names.output()
		<< " ]";
	return ostr;
}
