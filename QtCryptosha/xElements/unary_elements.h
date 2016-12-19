#pragma once

#include "basic_element.h"

using namespace cry;



class elements::unary : public elements::basic_element
{
public:
	explicit unary(iosize_t::type vector_size) : basic_element(vector_size, vector_size) {};
	virtual ~unary() = default;
};



class elements::invertor : public elements::unary
{
public: 
	invertor(size_type vector_size) : unary(vector_size){};
	bitset_t run() override
	{
		m_output = m_input;
		m_output.flip();
		return m_output;
	}
};

class elements::buffer : public elements::unary
{
public:
	buffer(size_type vector_size) : unary(vector_size) {};
	
	bitset_t run() override
	{
		m_output = m_input;
		return m_output;
	}
};

class elements::shift_left : public elements::unary
{
	size_type m_shift_size;
public:
	explicit shift_left(size_type vector_size,size_type shift_size) : unary(vector_size), m_shift_size(shift_size) {};
	
	bitset_t run() override
	{
		m_output = m_input << m_shift_size;
		//m_output << m_shift_size;
		return m_output;
	}
};

class elements::shift_right : public elements::unary
{
	size_type m_shift_size;
public:
	explicit shift_right(size_type vector_size, size_type shift_size) : unary(vector_size), m_shift_size(shift_size) {};
	
	bitset_t run() override
	{
		m_output = m_input >> m_shift_size;
		//m_output << m_shift_size;
		return m_output;
	}
};

class elements::simple_sbox : public elements::unary
{
	using vector_t = code::types::add_element::p_vector;

	vector_t vector;
public:
	explicit simple_sbox(const vector_t& sbox_vector) : unary(log2(sbox_vector.size())), vector(sbox_vector) {}
	
	bitset_t run() override
	{
		auto value = vector[m_input.to_ulong()];
		m_output = bitset_t(m_size.out, value);
		auto o = m_output;
		return m_output;
	}

};

class elements::permutation_block : public elements::unary
{
	using vector_t = code::types::add_element::p_vector;

	vector_t vector;
public:
	explicit permutation_block(const vector_t& pblock_vector) : unary(pblock_vector.size()), vector(pblock_vector) {}
	
	bitset_t run() override
	{
		for (size_type i = 0; i < m_size.out; ++i)
		{
			m_output[vector[i]] = m_input[i];
		}
		return m_output;
	}
};
