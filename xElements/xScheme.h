#pragma once

#include "./fabric.h"


#define myKeyWords

#ifdef myKeyWords
#define methods
#define states
#define ctors
#define dtor
#define data
#define static_data
#endif // myKeyWords


enum class scheme_status {
	modified,          
	assembled
};

using namespace cry;

class elements::cipher_scheme : public elements::basic_element
{
public:
	using pin_t = size_type;

	struct	pin_pair_t {
		pin_t pin1;
		pin_t pin2;

		pin_pair_t(pin_t pin_1, pin_t pin_2) : pin1(pin_1), pin2(pin_2) {}

		auto tie() const
		{
			return std::tie(pin1, pin2);
		}

		pin_pair_t get_reverse()
		{
			pin_pair_t(pin2, pin1);
		}
	};
	struct	id_pair_t {
		id_t id1;
		id_t id2;

		id_pair_t(id_t id_1, id_t id_2) : id1(id_1), id2(id_2) {}

		auto tie() const
		{
			return std::tie(id1, id2);
		}

		id_pair_t get_reverse()
		{
			id_pair_t(id2, id1);
		}

		bool operator< (const id_pair_t& rhs)
		{
			return tie() < rhs.tie();
		}

	};
	struct full_name_t {

		name_t  name;
		index_t index;

		full_name_t(name_t name_, index_t index_ = 0) : name(name_), index(index_) {}
		
		auto tie() const
		{
			return std::tie(name, index);
		}

	};

	using id_pool_t  = std::set<id_t>;
	using circuit_t  = std::list<id_pool_t>;
	using wires_t    = std::multimap< 
							id_pair_t,
							pin_pair_t,
							std::function<bool(const id_pair_t&, const id_pair_t&)>
						>;
	
protected:
	using names_id_t = std::map< 
							full_name_t,
							id_t,
							std::function<bool(const full_name_t&, const full_name_t&)>
						>;

	using elements_t = std::map<id_t, element_ptr>;
	

public:
	using id_bitset = std::map<id_t, bitset_t>;

public:
	cipher_scheme() = delete;

	cipher_scheme(size_type text_size, size_type key_size, size_type out_size);

	id_t add_element(const factory_package& element_package);

	cipher_scheme& delete_element(const full_name_t& full_name);
	
	cipher_scheme& add_connection_fast(const full_name_t& sender_name, pin_t pin_out, \
		const full_name_t& receiver_name, pin_t pin_in);
	cipher_scheme& delete_connection(const full_name_t& sender_name, size_type pin_out, \
		const full_name_t& receiver_name, size_type pin_in);

	cipher_scheme& set_key(const string_t& key_vector);
	cipher_scheme& set_key(const int_t& key_value);
	cipher_scheme& set_text(const string_t& text_vector);
	cipher_scheme& set_text(const int_t& text_value);
	
	id_t  element_id(const full_name_t& name);
	element_ptr element(const full_name_t& name);
	element_ptr element(const id_t& id);

	const wires_t&   wires();
	const circuit_t& circuit();

	cipher_scheme& get_wires_to(wires_t& wires);
	cipher_scheme& get_circuit_to(circuit_t& circuit);

	cipher_scheme& get_wires_from(wires_t&& wires);
	cipher_scheme& get_circuit_from(circuit_t&& circuit);

	cipher_scheme& assembly();
	
	virtual bitset_t run() override;

	id_bitset run(const id_pool_t& element_pool);

	

	virtual ~cipher_scheme() = default;

protected:
	names_id_t  m_name_id;
	wires_t     m_wires;
	circuit_t   m_circuit;
	elements_t  m_elements;

	bitset_t    m_key;
	bitset_t    m_text;

	size_type   m_key_size;
	size_type   m_text_size;

private:
	id_t g_next_id;
	id_t get_id();

	scheme_status m_status;
	

private methods:
	id_pool_t _find_all_ids() const;
	id_pool_t _find_next_layer_ids(const id_pool_t&, const id_pool_t&) const;
	id_pool_t _find_next_layer_ids(id_t, const id_pool_t&) const;
	id_pool_t _intersection(const id_pool_t&, const id_pool_t&);
	id_pool_t _remove_dependent_el_id_from_pool(id_pool_t&);
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

