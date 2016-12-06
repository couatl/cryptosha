
#include "./cryptosha.hpp"


int main()
{
	std::ifstream for_file("for.txt");
	
	std::cout << std::boolalpha << for_file.good() << std::endl;

	cryptosha::anaconda::interpretator anaconda(for_file, std::cout);

	anaconda.read().do_code();

	system("pause");
	return 0;
}