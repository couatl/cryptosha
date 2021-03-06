#include "xScheme.h"


using namespace cry;






class elements::graphic_scheme : public elements::cipher_scheme
{
	struct g_info
	{
		element_keys element_key;

		gsize_t position;
		gsize_t size;

		g_info() : element_key(element_keys::buffer), position({ 0,0 }), size({ 0,0 }) {};

		g_info(element_keys element__key, gsize_t pos, gsize_t graphic_size)
			: element_key(element__key), position(pos), size(graphic_size) {};
	};

	using id_graphic = std::map<id_t, g_info>;

public:
	struct graphic_info : public g_info
	{
		iosize_t iosize;

		graphic_info(g_info ginfo, iosize_t io_size)
			: g_info(ginfo), iosize(io_size) {};
	};

public:

	graphic_scheme(size_type text_size, size_type key_size, size_type cipher_size);
	
	graphic_scheme& add_element(const factory_package& element_package);
	graphic_scheme& delete_element(const full_name_t& full_name);

	graphic_info graphic_information(const full_name_t& name);
	graphic_info graphic_information(const id_t& id);

	g_info& info_ref(const id_t& id);


	bool is_true(const id_t element_id, size_type out_pin) ;


private:
	id_graphic id_to_graphic;
};