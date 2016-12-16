#include "xScheme.h"



using namespace cry::elements;

cipher_scheme::cipher_scheme(size_type text_size, size_type key_size, size_type out_size)
	: basic_element(text_size + key_size, out_size), m_key_size(key_size), m_text_size(text_size),
	m_key(key_size), m_text(text_size),
	m_wires([](const id_pair_t& lhs, const id_pair_t& rhs)->bool { return lhs.tie() < rhs.tie(); }),
	m_name_id([](const full_name_t& lhs, const full_name_t& rhs)->bool { return lhs.tie() < rhs.tie(); })
{
	factory_package pack;

	pack.element_key = element_keys::buffer;



	pack.scheme_options.element_name = scheme::names::text;
	pack.scheme_options.element_index = 0;
	pack.iosize = {
					static_cast<iosize_t::type>(text_size),
					static_cast<iosize_t::type>(text_size)
				  };

	add_element(pack);

	pack.scheme_options.element_name = scheme::names::key;
	pack.scheme_options.element_index = 0;
	pack.iosize = {
					static_cast<iosize_t::type>(text_size),
					static_cast<iosize_t::type>(text_size)
				  };

	add_element(pack);

	pack.scheme_options.element_name = scheme::names::cipher;
	pack.scheme_options.element_index = 0;
	pack.iosize = {
					static_cast<iosize_t::type>(text_size),
					static_cast<iosize_t::type>(text_size)
				  };

	add_element(pack);
}


id_t cipher_scheme::add_element(const factory_package& element_package)
{
	
	auto full_name = full_name_t(element_package.scheme_options.element_name, 
								element_package.scheme_options.element_index);

	if (m_name_id.find(full_name) != m_name_id.end())
			throw exception_t(error_messages::el_exists);
	
 	auto current_id = get_id();
			
	m_name_id[full_name] = current_id;

	m_elements[current_id] = std::move(get_element(element_package));

	return current_id;
}

id_t cipher_scheme::get_id()
{
	return g_next_id++;
}

cipher_scheme& cipher_scheme::set_key(const string_t& key_vector)
{
	m_elements[ m_name_id.at(full_name_t(scheme::names::key)) ]->set_input(key_vector);
	return *this;
}
cipher_scheme& cipher_scheme::set_key(const int_t& key_value)
{
	m_elements[m_name_id.at(full_name_t(scheme::names::key))]->set_input(key_value);
	return *this;
}

cipher_scheme& cipher_scheme::set_text(const string_t& text_vector)
{
	m_elements[ m_name_id.at(full_name_t(scheme::names::text)) ]->set_input(text_vector);
	return *this;
}
cipher_scheme& cipher_scheme::set_text(const int_t & text_value)
{
	m_elements[m_name_id.at(full_name_t(scheme::names::text))]->set_input(text_value);
	return *this;
}


id_t cipher_scheme::element_id(const full_name_t & name)
{
	return m_name_id.at(name);
}

element_ptr cipher_scheme::element(const full_name_t& name)
{
	return m_elements.at(m_name_id.at(name));
}
element_ptr cipher_scheme::element(const id_t& id)
{
	return m_elements.at(id);
}

const cipher_scheme::wires_t&   cipher_scheme::wires()
{
	return m_wires;
}
const cipher_scheme::circuit_t& cipher_scheme::circuit()
{
	return m_circuit;
}

cipher_scheme& cipher_scheme::get_wires_to(wires_t & wires)
{
	wires = std::move(m_wires);
	return *this;
}
cipher_scheme& cipher_scheme::get_circuit_to(circuit_t & circuit)
{
	circuit = std::move(m_circuit);
	return *this;
}

cipher_scheme& cipher_scheme::get_wires_from(wires_t&& wires)
{
	m_wires = std::move(wires);
	return *this;
}
cipher_scheme& cipher_scheme::get_circuit_from(circuit_t&& circuit)
{
	m_circuit = std::move(circuit);
	return *this;
}


cipher_scheme& cipher_scheme::assembly()
{
	id_pool_t prev_el_pool = {};
	id_pool_t curr_el_pool = {};
	id_pool_t next_el_pool = _find_all_ids();

	circuit_t circuit;

	prev_el_pool.insert(m_name_id.at(scheme::names::key));
	prev_el_pool.insert(m_name_id.at(scheme::names::text));

	next_el_pool.erase(m_name_id.at(scheme::names::key));
	next_el_pool.erase(m_name_id.at(scheme::names::text));

	circuit.push_front(std::move(prev_el_pool));
	
	for (curr_el_pool = _find_next_layer_ids(circuit.back(), next_el_pool);
			curr_el_pool.size();
		 curr_el_pool = _find_next_layer_ids(circuit.back(), next_el_pool)
		)
	{
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

		circuit.push_back(std::move(curr_el_pool));
		curr_el_pool.clear();		
	}

	m_circuit = std::move(circuit);

	return *this;
}

bitset_t cipher_scheme::run()
{
	auto text_buffer_id = m_name_id.at(scheme::names::text);
	auto key_buffer_id  = m_name_id.at(scheme::names::key);

	if(true){
		auto layer_cit = m_circuit.cbegin();
		for (++layer_cit; layer_cit != m_circuit.cend(); ++layer_cit)
		{
			for (auto pool_cit = layer_cit->cbegin(); pool_cit != layer_cit->cend(); ++pool_cit)
			{
				m_elements[*pool_cit]->set_null();
			}
		}
	}

	for (auto layer_cit = m_circuit.cbegin(); layer_cit != m_circuit.cend(); ++layer_cit)
	{
		for (auto pool_cit = layer_cit->cbegin(); pool_cit != layer_cit->cend(); ++pool_cit)
		{
			auto k = m_elements[*pool_cit]->input().to_ulong();

			m_elements[*pool_cit]->run();


			std::for_each(m_wires.cbegin(), m_wires.cend(), [&pool_cit, this](wires_t::value_type wire){
				if (*pool_cit == wire.first.id1) {
					m_elements[wire.first.id2]->input_ref()[wire.second.pin2] =
						m_elements[wire.first.id1]->output_ref()[wire.second.pin1];
				}
			});
		}
	}

	m_output = m_elements[m_name_id.at(full_name_t(scheme::names::cipher))]->run();

	auto k = m_output.to_ulong();

	return m_output;
}

cipher_scheme::id_bitset cipher_scheme::run(const id_pool_t& element_pool)
{
	id_bitset id_to_bitset;

	std::for_each(element_pool.cbegin(), element_pool.cend(),
		[&id_to_bitset, this](const id_pool_t::value_type& id)
		{
			id_to_bitset.insert({ id, this->element(id)->run() });
		}
	);
	return id_to_bitset;
}





cipher_scheme& cipher_scheme::add_connection_fast(const full_name_t& o_elem_name, pin_t o_pin, const full_name_t& i_elem_name, pin_t i_pin)
{
	auto id_out = m_name_id.at(o_elem_name);
	auto id_in  = m_name_id.at(i_elem_name);

	m_wires.insert({ id_pair_t(id_out, id_in), pin_pair_t( o_pin , i_pin) });

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

cipher_scheme::id_pool_t cipher_scheme::_find_next_layer_ids(const id_pool_t& prev_pool,
															 const id_pool_t& next_pool) const
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
		if (cit->first.id1 == id){
			answer.insert(cit->first.id2);
		}
	}
	return answer;
}

cipher_scheme::id_pool_t cipher_scheme::_intersection(const id_pool_t& poolA, const id_pool_t& poolB)
{
	id_pool_t answer = {};

	/*if (poolA.size() <= poolB.size()) {
		
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

	}*/
	
	std::set_intersection(poolA.begin(), poolA.end(),
					      poolB.begin(), poolB.end(),
		        std::inserter(answer, answer.begin()) 
	);

	return answer;
}

cipher_scheme::id_pool_t cipher_scheme::_remove_dependent_el_id_from_pool(id_pool_t& pool)
{
	id_pool_t pool_next = _find_next_layer_ids(pool, pool);

	for (auto cit = pool_next.cbegin(); cit != pool_next.cend(); ++cit)
	{
		pool.erase(*cit);
	}
	return pool_next;
}

