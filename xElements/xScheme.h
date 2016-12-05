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

	typedef struct _pin_t_ {
		id_t el_id;
		size_type   pin;
		_pin_t_(id_t id, size_type pin_number) : el_id(id), pin(pin_number) {}

		auto tie() const
		{
			return std::tie(el_id, pin);
		}

		friend bool operator< (const _pin_t_& a, const _pin_t_& b)
		{
			return a.tie() < b.tie();
		}

	} pin_t;

	using id_pool_t = std::set<id_t>;

	struct full_name_t {

		name_t  name;
		index_t index;

		full_name_t(name_t name_, index_t index_ = 0) : name(name_), index(index_) {}
		
		auto tie() const
		{
			return std::tie(name, index);
		}
		
		friend bool operator< (const full_name_t& a, const full_name_t& b)
		{
			return a.tie() < b.tie();
		}
	};

	using circuit_t  = std::list<id_pool_t>;
	using wires_t    = std::multimap<pin_t, pin_t>;
	using names_id_t = std::map<full_name_t, id_t>;
	using elements_t = std::map<id_t, element_ptr>;

public:
	using layers = circuit_t;
	using element_name = full_name_t;
	using id = id_t;
	using id_bitset = std::map<id_t, bitset_t>;

public:
	cipher_scheme() = delete;

	cipher_scheme(size_type text_size, size_type key_size, size_type out_size);

	cipher_scheme& add_element(const factory_package& element_package);

	cipher_scheme& delete_element(const full_name_t& full_name);
	
	cipher_scheme& add_connection_fast(const full_name_t& sender_name, size_type pin_out, const full_name_t& receiver_name, size_type pin_in);
	cipher_scheme& delete_connection(const full_name_t& sender_name, size_type pin_out, const full_name_t& receiver_name, size_type pin_in);



	cipher_scheme& set_key(const string_t&);
	cipher_scheme& set_key(const int_t&);
	cipher_scheme& set_text(const string_t&);
	cipher_scheme& set_text(const int_t&);

	cipher_scheme& assembly();
	
	bitset_t run() override;

	id_bitset run(id_pool_t& element_pool);

	id_t  get_id(const full_name_t& name);
	element_ptr element(const full_name_t& name);
	element_ptr element(const id_t& id);
	

	virtual ~cipher_scheme() = default;

public:
	names_id_t  m_name_id;
	wires_t     m_wires;
	circuit_t   m_circuit;
	elements_t  m_elements;

	size_type   m_el_count;

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



class ::cryptosha::scheme : public cry::elements::cipher_scheme
{
public: 
	scheme(size_type text_size, size_type key_size, size_type out_size) : cipher_scheme(text_size, key_size, out_size) {} ;

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

