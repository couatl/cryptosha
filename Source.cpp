#include "./cryptosha.hpp"


int main()
{
	std::cout << std::boolalpha << cry::foo::is_invertible(int_vector({ 0, 1, 3, 2, 5, 6, 4 })) << std::endl;
	std::cout << std::boolalpha << cry::foo::is_invertible(int_vector({ 0, 1, 3, 2, 5, 7, 4 })) << std::endl;
	std::cout << std::boolalpha << cry::foo::is_invertible(int_vector({ 1, 1, 3, 2, 5, 6, 4 })) << std::endl;
	std::cout << std::boolalpha << cry::foo::is_invertible(int_vector({ 1, 0, 3, 2, 5, 6, 4 })) << std::endl;


	std::ifstream for_file("for.txt");

	std::cout << std::boolalpha << for_file.good() << std::endl;

	cryptosha::anaconda::interpretator anaconda(16, 16, 16, for_file, std::cout);


	anaconda.read().do_code();
	
	//cry::code::code_type code;
	
	/*{
		cry::code::simple_command cmd;
		cmd.condition = "";
		cmd.keyword = cry::code::keyword_t::assembly;
		cmd.mark = 56;
		cmd.command = 42;

	
		code.push_back(std::move(cmd));

		cmd.condition = "";
		cmd.keyword = cry::code::keyword_t::run;
		cmd.mark = 56;
		cmd.command = 42;

		code.push_back(std::move(cmd));

		cmd.condition = "";
		cmd.keyword = cry::code::keyword_t::assinging;
		cmd.mark = 56;
		code::types::assigning assign;
		assign.expression = "@cipher.out";
		assign.left_part = "cipher";
		cmd.command = assign;

		code.push_back(std::move(cmd));
	}*/

	//anaconda.update_code(std::move(code)).do_code();

	system("pause");
	return 0;
}
