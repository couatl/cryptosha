#include "xScheme.h"



using namespace cry::elements;

cipher_scheme::cipher_scheme(size_type text_size, size_type key_size, size_type out_size)
	: basic_element(text_size + key_size, out_size), m_key_size(key_size), m_text_size(text_size),
	m_key(key_size), m_text(text_size)
{
	factory_package pack;
	pack.element_key = element_keys::buffer;

	pack.name_for_scheme = scheme::names::text;
	pack.index_for_scheme = 0;
	pack.iosize = { text_size, text_size };

	add_element(pack);

	pack.name_for_scheme = scheme::names::key;
	pack.index_for_scheme = 0;
	pack.iosize = { key_size, key_size };

	add_element(pack);

	pack.name_for_scheme = scheme::names::cipher;
	pack.index_for_scheme = 0;
	pack.iosize = { out_size, out_size };

	add_element(pack);
}


cipher_scheme& cipher_scheme::add_element(const factory_package& element_package)
{

	auto full_name = full_name_t(element_package.name_for_scheme, element_package.index_for_scheme);

	if (m_name_id.find(full_name) != m_name_id.end())
			throw exception_t(error_messages::el_exists);
	
 	auto current_id = get_id();
			
	m_name_id[full_name] = current_id;

	m_elements[current_id] = std::move(get_element(element_package));
			
	++m_el_count;

	return *this;
}

id_t cipher_scheme::get_id()
{
	return g_next_id++;
}

cipher_scheme & cipher_scheme::set_key(const string_t& key_vector)
{
	m_elements[ m_name_id.at(full_name_t(scheme::names::key)) ]->set_input(key_vector);

	return *this;
}

cipher_scheme & cipher_scheme::set_text(const string_t& text_vector)
{
	m_elements[ m_name_id.at(full_name_t(scheme::names::text)) ]->set_input(text_vector);
	return *this;
}

element_ptr cipher_scheme::element(const full_name_t& name)
{
	return m_elements[ m_name_id.at(name) ];
}

cipher_scheme & cipher_scheme::assembly()
{
	id_pool_t prev_el_pool = {};
	id_pool_t curr_el_pool = {};
	id_pool_t next_el_pool = _find_all_ids();

	m_circuit.clear();

	prev_el_pool.insert(m_name_id.at(scheme::names::key));
	prev_el_pool.insert(m_name_id.at(scheme::names::text));

	next_el_pool.erase(m_name_id.at(scheme::names::key));
	next_el_pool.erase(m_name_id.at(scheme::names::text));

	m_circuit.push_front(std::move(prev_el_pool));
	
	for (curr_el_pool = _find_next_layer_ids(m_circuit.back(), next_el_pool); 
			curr_el_pool.size();
		 curr_el_pool = _find_next_layer_ids(m_circuit.back(), next_el_pool)
		)
	{
		m_name_id;
		m_elements;
		if (_intersection(curr_el_pool, prev_el_pool).size() ) {
			throw exception_t(error_messages::trigger_trying);      //it will be a normal information about the error,\
														 when I become a normal developer, of course.
		}

		auto superfluous_el_id_pool = _remove_dependent_el_id_from_pool(curr_el_pool);

		for (auto cit = curr_el_pool.cbegin(); cit != curr_el_pool.cend(); ++cit)
		{
			next_el_pool.erase(*cit);
			prev_el_pool.insert(*cit);  
		}

		m_circuit.push_back(std::move(curr_el_pool));
		curr_el_pool.clear();		
	}

	return *this;
}


bitset_t cipher_scheme::run()
{
	auto text_buffer_id = m_name_id.at(scheme::names::text);
	auto key_buffer_id  = m_name_id.at(scheme::names::key);

	for (auto layer_cit = m_circuit.cbegin(); layer_cit != m_circuit.cend(); ++layer_cit)
	{
		for (auto pool_cit = layer_cit->cbegin(); pool_cit != layer_cit->cend(); ++pool_cit)
		{
			if (*pool_cit != text_buffer_id && *pool_cit != text_buffer_id) {
				m_elements[*pool_cit]->set_null();
			}
		}
	}

	for (auto layer_cit = m_circuit.cbegin(); layer_cit != m_circuit.cend(); ++layer_cit)
	{
		for (auto pool_cit = layer_cit->cbegin(); pool_cit != layer_cit->cend(); ++pool_cit)
		{
			m_elements[*pool_cit]->run();

			//std::cout << *m_elements[*pool_cit] << std::endl;

			std::for_each(m_wires.cbegin(), m_wires.cend(), [ & ](wires_t::value_type wire){
				if (*pool_cit == wire.first.el_id) {
					m_elements[wire.second.el_id]->input_ref()[wire.second.pin] =
						m_elements[wire.first.el_id]->output_bit(wire.first.pin);
				}
			});
		}
	}

	m_output = m_elements[m_name_id.at(full_name_t(scheme::names::cipher))]->run();

	return m_output;
}





cipher_scheme& cipher_scheme::add_connection_fast(const full_name_t& o_elem_name, size_type o_pin, const full_name_t& i_elem_name, size_type i_pin)
{
	auto id_out = m_name_id.at(o_elem_name);
	auto id_in  = m_name_id.at(i_elem_name);
	m_wires.insert({ pin_t(id_out, o_pin), pin_t( id_in , i_pin) });
				
	return *this;

}

cipher_scheme::id_pool_t cipher_scheme::_find_all_ids() const
{
	id_pool_t pool = {};
	for (auto it = m_elements.cbegin(); it != m_elements.cend(); ++it)
	{
		pool.insert(it->first);
	}
	return pool;
}

cipher_scheme::id_pool_t cipher_scheme::_find_next_layer_ids(const id_pool_t& prev_pool, const id_pool_t& next_pool) const
{
	id_pool_t answer = {};

	for (auto it = prev_pool.cbegin(); it != prev_pool.cend(); ++it)
	{
		auto pool = _find_next_layer_ids(*it,next_pool);
		answer.insert(pool.cbegin(), pool.cend());
	}
	return answer;
}

cipher_scheme::id_pool_t cipher_scheme::_find_next_layer_ids(id_t id, const id_pool_t& next_pool) const
{
	id_pool_t answer = {};

	for (auto cit = m_wires.cbegin(); cit != m_wires.cend(); ++cit)
	{
		if (cit->first.el_id == id){
			answer.insert(cit->second.el_id);
		}
	}
	return answer;
}

cipher_scheme::id_pool_t cipher_scheme::_intersection(const id_pool_t& poolA, const id_pool_t& poolB)
{
	id_pool_t answer = {};

	if (poolA.size() <= poolB.size()) {
		
		for (auto cit = poolA.cbegin(); cit != poolA.cend(); ++cit)
		{
			if (std::find(poolB.cbegin(), poolB.cend(), *cit) != poolB.cend()) {
				answer.insert(*cit);
			}
		}

	}
	else {
		
		for (auto cit = poolB.cbegin(); cit != poolB.cend(); ++cit)
		{
			if (std::find(poolA.cbegin(), poolA.cend(), *cit) != poolA.cend()) {
				answer.insert(*cit);
			}
		}

	}
	
	return answer;
}

cipher_scheme::id_pool_t cipher_scheme::_remove_dependent_el_id_from_pool(id_pool_t& pool)
{
	id_pool_t poolNext = _find_next_layer_ids(pool, pool);

	for (auto cit = poolNext.cbegin(); cit != poolNext.cend(); ++cit)
	{
		pool.erase(*cit);
	}
	return poolNext;
}

