
#include "./cryptosha.hpp"
#include "Interpretator/analysis/analysis.h"


int main()
{
	/*std::ifstream for_file("for.txt");
	
	std::cout << std::boolalpha << for_file.good() << std::endl;

	cryptosha::anaconda::interpretator anaconda(for_file, std::cout);

	anaconda.read().do_code();*/

	cryptosha::analysis a;
	std::cout << a.run_element(cry::element_ptr(new cry::elements::xor(2)), cryptosha::bitset_pool("****"));

	system("pause");
	return 0;
}