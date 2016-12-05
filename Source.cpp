
#include "./settings.h"


int main()
{

	auto bs = cry::foo::str_to_bitset(cry::string_t("1011 0011 0001 0001"), 16);
	auto b1 = cry::foo::is_invertible(cry::int_vector({ 1, 3, 4, 0, 2 }));
	auto b2 = cry::foo::is_invertible(cry::int_vector({ 1, 3, 4, 0, 2, 6 }));

	system("pause");
	return 0;
}