#include "fabric.h"


cry::element_ptr get_element(const factory_package& package)
{


	switch (package.element_key)
	{
	case element_keys::buffer: {

			return element_ptr(new elements::buffer(package.iosize.out));

		}break;

	case element_keys::invertor: {

			return element_ptr(new elements::invertor(package.iosize.out));

		}break;

	case element_keys::shift_left: {

			auto shift_size = any_cast<factory_package::shift_size>(package.extra_options.at(factory_package::keys::shift_size));
			return element_ptr(new elements::shift_left(package.iosize.out, shift_size));

		}break;

	case element_keys::shift_right:	{

			auto shift_size = any_cast<factory_package::shift_size>(package.extra_options.at(factory_package::keys::shift_size));
			return element_ptr(new elements::shift_right(package.iosize.out, shift_size));

		}break;

	case element_keys::p_block:	{

			auto p_vector = any_cast<factory_package::p_vector>(package.extra_options.at(factory_package::keys::p_vector));
			return element_ptr(new elements::permutation_block(p_vector));

		}break;

	case element_keys::conjunctor: {

			return element_ptr(new elements::conjunctor(package.iosize.out));

		}break;

	case element_keys::disjunctor: {
			
			return element_ptr(new elements::disjunctor(package.iosize.out));

		}break;

	case element_keys::xor: {

			return element_ptr(new elements::xor(package.iosize.out));

		}break;

	case element_keys::nor: {

			return element_ptr(new elements::nor(package.iosize.out));

		}break;

	case element_keys::nand: {

			return element_ptr(new elements::nand(package.iosize.out));

		}break;

	case element_keys::sum: {

			return element_ptr(new elements::sum(package.iosize.out));
		
		}break;

	case element_keys::equality: {

			return element_ptr(new elements::equality(package.iosize.out));
		
		}break;
	
	case element_keys::simple_sbox: {
			auto s_vector = any_cast<factory_package::s_vector>(package.extra_options.at(factory_package::keys::s_vector));
			return element_ptr(new elements::simple_sbox(s_vector));

		}break;

	case element_keys::complex_sbox:
		break;

	case element_keys::custom:
		break;

	default:
		break;
	}

	return element_ptr(nullptr);
}
