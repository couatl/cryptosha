#include "graphic_scheme.h"


using namespace cry;



elements::graphic_scheme& elements::graphic_scheme::add_element(const factory_package & element_package)
{
	auto id = cipher_scheme::add_element(element_package);
	
	id_to_graphic.insert({ id, g_info(element_package.element_key,
		element_package.scheme_options.position,
		element_package.scheme_options.graphic_size ) });

	return *this;
}

elements::graphic_scheme::graphic_info 
	elements::graphic_scheme::graphic_information(const full_name& name)
{
	return graphic_information(element_id(name));
}


elements::graphic_scheme::graphic_info 
	elements::graphic_scheme::graphic_information(const id_t & id)
{
	return graphic_info(id_to_graphic[id], element(id)->size());
}

