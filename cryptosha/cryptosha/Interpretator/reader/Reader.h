#pragma once
#include "../../settings.h"


using namespace cry;

namespace cryptosha 
{
	enum class stack_kw
	{
		open_scope,
		m_for
	};

	int_vector str_to_int_vec(string_t str, string_t mod = "d");

	string_t space_free(string_t);

	struct stack_elem
	{
		stack_kw keyword;
		code::code_type simple_command_list;
		code::code_type::iterator it;
	};

	class console_reader
	{
	public:
		console_reader(std::istream& in, std::ostream& out) : input(in), output(out)
		{}
		
		void set_input(std::istream&);
		std::istream& get_input();

		void set_output(std::ostream&);
		std::ostream& get_output();
		
		code::code_type read();

		~console_reader()
		{}
		

		

	private:
		std::list<string_t> str_to_list(string_t, const string_t, const string_t);

		void str_to_cmd(string_t);

		void stack_close();

		code::simple_command simple_cmd_handle(string_t, string_t);

		string_t input_handle();

		void list_handle(std::list<string_t>);

		size_type num = 0;

		mark_t mark_number = 0;

		code::code_type code;

		std::stack<stack_elem> ns_stack;
		std::stack<string_t> input_stack;

		//std::unique_ptr<std::istream> input;
		std::reference_wrapper<std::istream> input;
		std::reference_wrapper<std::ostream> output;
	};
}