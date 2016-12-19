#include "graphic_scheme.h"


using namespace cry;



elements::graphic_scheme::graphic_scheme(size_type text_size, size_type key_size, size_type cipher_size)
		: cipher_scheme(text_size, key_size, cipher_size) 
{
	auto id = element_id(scheme::names::text);
	
	g_info ginfo = { element_keys::buffer, { 50, 50 } , { 80, 5 } };

	id_to_graphic.insert({ id, ginfo });

	//***
	id = element_id(scheme::names::key);
	
	ginfo.position.x += ginfo.size.x + 50;

	id_to_graphic.insert({ id, ginfo });

	//***
	id = element_id(scheme::names::cipher);

	ginfo = { element_keys::buffer,{ 50, 50 + 200 } ,{ 80, 5 } };

	id_to_graphic.insert({ id, ginfo });

}

elements::graphic_scheme& elements::graphic_scheme::add_element(const factory_package & element_package)
{
	auto id = cipher_scheme::add_element(element_package);
	
	id_to_graphic.insert({ id, g_info(element_package.element_key,
		element_package.scheme_options.position,
		element_package.scheme_options.graphic_size ) });

	return *this;
}

elements::graphic_scheme::graphic_info
	elements::graphic_scheme::graphic_information(const full_name_t& name)
{
	return graphic_information(element_id(name));
}


elements::graphic_scheme::graphic_info
	elements::graphic_scheme::graphic_information(const id_t& id)
{
	graphic_info ret(id_to_graphic.at(id), element(id)->size());

	for (auto& name_id : m_name_id)
	{
		if (name_id.second == id){
			ret.name = name_id.first.name +"[ " + std::to_string(name_id.first.index) + " ]";
			break;
		}
	}

	return ret;
}

elements::graphic_scheme::g_info&
	elements::graphic_scheme::info_ref(const id_t & id)
{
	return id_to_graphic.at(id);
}

bool elements::graphic_scheme::is_true(const id_t element_id, size_type out_pin) 
{
	return this->element(element_id)->output()[out_pin];
}



