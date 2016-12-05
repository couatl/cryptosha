#pragma once

#include "./unary_elements.h"
#include "./binary_element.h"


using factory_package = cry::code::types::add_element;

cry::element_ptr get_element(const factory_package& ctor_parameters);
