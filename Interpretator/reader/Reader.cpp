#include "Reader.h"





namespace funcs
{

	code::types::assigning assinging(string_t str)
	{
		code::types::assigning cmd;
		std::smatch res;
		std::regex_search(str, res, syntax::regs::assinging);
		cmd.left_part = cryptosha::space_free(res[1].str());
		cmd.expression = cryptosha::space_free(res[2].str());		
		return cmd;
	}

	code::types::delete_element del(string_t str)
	{
		code::types::delete_element cmd;
		std::smatch res;
		std::regex_search(str, res, syntax::regs::del);
		cmd.element_name = res[1].str();
		return cmd;
	}

	code::types::connect connect(string_t str)
	{
		code::types::connect cmd;
		std::smatch res;
		std::regex_search(str, res, syntax::regs::connect);
		cmd.sender_name = res[1].str();
		cmd.pins_of_sender = cryptosha::str_to_int_vec(res[2].str());
		cmd.receiver_name = res[3].str();
		cmd.pins_of_receiver = cryptosha::str_to_int_vec(res[4].str());
		
	
		return cmd;
	}

	code::types::script script(string_t str)
	{
		code::types::script cmd;
		std::smatch res;
		std::regex_search(str, res, syntax::regs::script);
		cmd.ofstream = res[1].str();
	
		return cmd;
	}
	code::types::add_element add(string_t str)
	{
		code::types::add_element cmd;
		std::smatch res;
		std::regex_search(str, res, syntax::regs::add);
		cmd.element_name = res[2].str();
		cmd.element_key = code::name_to_element_key.at(res[1].str());
		cmd.iosize = iosize_t(stoi(res[3].str()), stoi(res[4].str()));
		if (res[5].str().size())
		{
			cmd.graphic_x = res[6].str();
			cmd.graphic_y = res[7].str();
		}
		else
		{
			cmd.graphic_x = string_t("");
			cmd.graphic_y = string_t("");
		}
		if (res[7].str().size())
		{
			cmd.graphic_width = res[9].str();
			cmd.graphic_height = res[10].str();
		}
		else
		{
			cmd.graphic_width = string_t("");
			cmd.graphic_height = string_t("");
		}
	

		return cmd;
	}

	code::types::add_element add_s_p(string_t str)
	{
		code::types::add_element cmd;
		std::smatch res;
		std::regex_search(str, res, syntax::regs::add_s_p);
		cmd.element_name = res[2].str();
		cmd.element_key = code::name_to_element_key.at(res[1].str());
		cmd.iosize = iosize_t(stoi(res[3].str()), stoi(res[4].str()));
		cmd.extra_options.insert({ code::types::add_element::keys::p_vector, cryptosha::str_to_int_vec(res[6].str(), res[5].str()) });
		/*cmd.insert({ code::keys::element, code::name_to_element_type.at(res[1].str()) });
		cmd.insert({ code::keys::name, res[2].str() });
		cmd.insert({ code::keys::iosize, iosize_t(stoi(res[3].str()), stoi(res[4].str())) });
		cmd.insert({ code::keys::int_vector, cryptosha::str_to_int_vec(res[6].str(), res[5].str()) });*/
		return cmd;
	}
}


namespace output
{
	string_t err_str("incorrect input");
	string_t begin_str(">>>> ");
	string_t tab_str("   ");
	string_t begin_tab_str("     ");
}


namespace cryptosha
{
	int sys_transfer(string_t str, string_t mod)
	{
		int numb = 0;
		int res = 0;
		if (mod == "d")
		{
			res = stoi(str);
		}
		else if (mod == "b")
		{
			string_t source("01");
			auto it = --str.end();
			for (; it != str.begin(); --it)
			{
				res += source.find(*it) * pow(2.0, (double)numb);
				++numb;
			}
			res += source.find(*it) * pow(2.0, (double)numb);
		}
		else if (mod == "h")
		{
			string_t source("0123456789abcdef");
			auto it = --str.end();
			for (; it != str.begin(); --it)
			{
				res += source.find(*it) * pow(16.0, (double)numb);
				++numb;
			}
			res += source.find(*it) * pow(16.0, (double)numb);
		}
		return res;
	}

	int_vector str_to_int_vec(string_t str, string_t mod)
	{
		str = str.substr(1, str.size() - 2);
		int_vector buf;
		if (str == "")
			return buf;
		size_type k = 0;
		for (size_t i = 0; i < str.length(); i++)
		{
			if (str[i] == ' ')
			{
				if (str[k] != ' ')
				{
					buf.push_back(sys_transfer(str.substr(k, i - k), mod));
				}

				k = i + 1;
				continue;
			}
			if (i == str.length() - 1)
			{
				buf.push_back(sys_transfer(str.substr(k, i - k + 1), mod));
			}
		}
		return buf;
	}


	void console_reader::stack_close()
	{
		--num;
		if (ns_stack.empty())
		{
			output.get() << output::err_str << std::endl;
			return;
		}
		code::code_type code_st_el = ns_stack.top().simple_command_list;
		ns_stack.pop();
		if (ns_stack.empty())
		{
			code = code_st_el;
		}
		else 
			ns_stack.top().simple_command_list.insert(ns_stack.top().it, code_st_el.begin(), code_st_el.end());
	}


	string_t space_free(string_t input_str)
	{
		for (auto it = input_str.begin(); it != input_str.end();)
		{
			if (*it == ' ')
			{
				input_str.erase(it);
			}
			else 
				++it;
		}
		return input_str;
	}


	std::list<string_t> simple_str_to_vec(string_t input_str, const string_t divider1)
	{
		std::list<string_t> vec;
		size_t prev = 0;
		size_t next;
		size_t delta = divider1.length();

		while ((next = input_str.find(divider1, prev)) != string_t::npos)
		{
			string_t tmp = input_str.substr(prev, next - prev);
			if (input_str.substr(prev, next - prev).size())
				vec.push_back(input_str.substr(prev, next - prev));
			vec.push_back(divider1);
			prev = next + delta;
		}
		string_t tmp = input_str.substr(prev);
		vec.push_back(input_str.substr(prev));
		return vec;
	}


	std::list<string_t> console_reader::str_to_list(string_t input_str, const string_t divider1 = syntax::keywords::c_open, const string_t divider2 = syntax::keywords::c_close)
	{
		std::list<string_t> list_of_strs;
		std::list<string_t> vec;
		
		list_of_strs = simple_str_to_vec(input_str, divider1);
		
		auto last = list_of_strs.begin();
		auto first = last++;

		while (first != list_of_strs.end())
		{
			vec = simple_str_to_vec(*first, divider2);
			list_of_strs.insert(last, vec.begin(), vec.end());
			list_of_strs.erase(first);
			first = last;
			if (last != list_of_strs.end())
				++last;
		}

		return list_of_strs;
	}


	string_t console_reader::input_handle()
	{
		string_t result = string_t("");
		string_t str;
		std::list<string_t> list;
		do{
			getline(input.get(), str);
			list = str_to_list(str, syntax::keywords::c_open, syntax::keywords::c_close);
			str.clear();
		
			for (auto &it : list)
			{
				if (it == syntax::keywords::c_open_m)
				{
					input_stack.push(syntax::keywords::c_open_m);
					result = result + it;
				}
				else if (it == syntax::keywords::c_close_m)
				{
					if (input_stack.empty())
					{
						output.get() << output::err_str << std::endl;
						return string_t("");
					}
					else
					{
						input_stack.pop();
						result = result + it;
					}
				}
				else
					result = result + it;
			}
		} while (!input_stack.empty());

		return result;

	}


	code::simple_command console_reader::simple_cmd_handle(string_t input_str, string_t condition = "")
	{
		std::smatch res;
	
		code::simple_command code_element;

		if (std::regex_match(input_str, syntax::regs::assinging))
		{
			code_element.keyword = code::keyword_t::assinging;
			code_element.command = funcs::assinging(input_str);
			code_element.condition = condition;
			code_element.mark = mark_number++;
		}
		if (std::regex_match(input_str, syntax::regs::assembly))
		{
			code_element.keyword = code::keyword_t::assembly;
			code_element.condition = condition;
			code_element.mark = mark_number++;
		}
		if (std::regex_match(input_str, syntax::regs::run))
		{
			code_element.keyword = code::keyword_t::run;
			code_element.condition = condition;
			code_element.mark = mark_number++;
		}
		else if (std::regex_match(input_str, syntax::regs::del))
		{
			
			code_element.command = funcs::del(input_str);
			code_element.condition = condition;
			code_element.mark = mark_number++;
		}
		else if (std::regex_match(input_str, syntax::regs::connect))
		{
		
			code_element.command = funcs::connect(input_str);
			code_element.condition = condition;
			code_element.mark = mark_number++;
		}
		else if (std::regex_match(input_str, syntax::regs::add))
		{
			code_element.command = funcs::add(input_str);
			code_element.condition = condition;
			code_element.mark = mark_number++;
		}
		else if (std::regex_match(input_str, syntax::regs::add_s_p))
		{
			code_element.command = funcs::add_s_p(input_str);
			code_element.condition = condition;
			code_element.mark = mark_number++;
		}
		else if (std::regex_match(input_str, syntax::regs::script))
		{
			code_element.command = funcs::script(input_str);
			code_element.condition = condition;
			code_element.mark = mark_number++;
		}
		
		
		return code_element;
	}


	void console_reader::str_to_cmd(string_t input_str)
	{
		if (!input_str.size())
			return;
		std::smatch res;
		code::simple_command code_element;
		stack_elem st_el;

		if (std::regex_search(input_str, res, syntax::regs::m_for))
		{
			++num;
			ns_stack.push(st_el);
			ns_stack.top().keyword = stack_kw::m_for;

			code_element = simple_cmd_handle(res[1].str());
			ns_stack.top().simple_command_list.push_back(code_element);

			code_element.mark = mark_number++;
			code_element.condition = res[2].str();
			code_element.command = code::types::goto_after{ mark_number };
			ns_stack.top().simple_command_list.push_back(code_element);


			code_element.mark = mark_number++;
			code_element.condition = "";
			code_element.command = code::types::goto_after{ mark_number + 1};
			ns_stack.top().simple_command_list.push_back(code_element);


			code_element = simple_cmd_handle(res[3].str());
			ns_stack.top().simple_command_list.push_back(code_element);
			ns_stack.top().it = --ns_stack.top().simple_command_list.end();

			code_element.mark = mark_number++;
			code_element.condition = "";
			code_element.command = code::types::goto_after{ mark_number - 5 };
			ns_stack.top().simple_command_list.push_back(code_element);

			return;

		}

		else if (input_str == syntax::keywords::c_open)
		{
			//ind = false;
			++num;
			ns_stack.push(st_el);
			ns_stack.top().keyword = stack_kw::open_scope;
			ns_stack.top().it = ns_stack.top().simple_command_list.begin();
			return;
		}

		else if (input_str == syntax::keywords::c_close)
		{
			if (!ns_stack.empty())
				stack_close();
			else
			{
				output.get() << output::err_str  << std::endl;
				return;
			}
			if (!ns_stack.empty())
			{
				if (ns_stack.top().keyword == stack_kw::m_for)
					stack_close();
			}	
			return;
		}
		
		
		
		code_element = simple_cmd_handle(input_str);
		if (code_element.command.empty())
		{
			output.get() << output::err_str << std::endl;
			return;
		}
		if (ns_stack.empty())
		{
			code.push_back(code_element);
		}
		else if (ns_stack.top().keyword == stack_kw::m_for)
		{
			ns_stack.top().simple_command_list.insert(ns_stack.top().it, code_element);
			stack_close();

		}
		else if (ns_stack.top().keyword == stack_kw::open_scope)
		{
			ns_stack.top().simple_command_list.insert(ns_stack.top().it, code_element);
		}
		
		
	}
	

	void console_reader::list_handle(std::list<string_t> list_of_strs)
	{
		
		for (auto it : list_of_strs) 
		{
			str_to_cmd(it);
		}
	}

	code::code_type console_reader::read()
	{
		output.get() << output::begin_str;
		string_t str = input_handle();
		list_handle(str_to_list(str));
		while (!ns_stack.empty())
		{
			output.get() << output::begin_tab_str;
			for (size_type i = 0; i < num; ++i)
				output.get() << output::tab_str;
			string_t str = input_handle();
			
			list_handle(str_to_list(str));
			

		} 

		code::code_type result =  code;
		code.clear();
		mark_number = 0;
		return result;
	}

	void console_reader::set_input(std::istream& in)
	{
		input = std::ref(in);
	}
	std::istream& console_reader::get_input()
	{
		return input.get();
	}

	void console_reader::set_output(std::ostream& out)
	{
		output = std::ref(out);
	}
	std::ostream& console_reader::get_output()
	{
		return output.get();
	}
	

}