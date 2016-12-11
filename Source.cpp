
#include "./cryptosha.hpp"


int main()
{
	std::cout << std::boolalpha << cry::foo::is_invertible(int_vector({ 0, 1, 3, 2, 5, 6, 4 })) << std::endl;
	std::cout << std::boolalpha << cry::foo::is_invertible(int_vector({ 0, 1, 3, 2, 5, 7, 4 })) << std::endl;
	std::cout << std::boolalpha << cry::foo::is_invertible(int_vector({ 1, 1, 3, 2, 5, 6, 4 })) << std::endl;
	std::cout << std::boolalpha << cry::foo::is_invertible(int_vector({ 1, 0, 3, 2, 5, 6, 4 })) << std::endl;


	std::ifstream for_file("for.txt");
	
	std::cout << std::boolalpha << for_file.good() << std::endl;

	cryptosha::anaconda::interpretator anaconda(64, 64, 64, for_file, std::cout);

	anaconda.read().do_code();



	system("pause");
	return 0;
}
