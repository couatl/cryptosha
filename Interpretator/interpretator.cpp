#include "interpretator.h"


namespace ns_c_a = cryptosha::anaconda;

auto ns_c_a::calculator::space_free(const string_t& str) -> string_t
{
	auto input_str = str;

	for (auto it = input_str.begin(); it != input_str.end();)
	{
		if (*it == ' ')
			input_str.erase(it);
		else
			++it;
	}
	return input_str;
}

auto ns_c_a::calculator::name_type::to_parsed(const string_t& name) -> parsed_t
{
	using namespace syntax::keywords;

	string_t      str = name;
	std::regex    e(el_name_begin + string_t("?(\\w+)(\\[\\s*(\\w+-?\\w*)\\])?\\.?"));
	std::smatch   res;

	parsed_t  parce_name;
    
	/*
	if (str[0] == name_divider)
		throw exception_t(error_messages::);*/

	bool is_element_name = (name[0] == el_name_begin);

	while (std::regex_search(str, res, e))
	{
		parsed_t::value_type pair;
		if (is_element_name) {
			is_element_name = false;
			pair.first = string_t(res[1]);
		}
		else {
			pair.first = res[1];
		}
		pair.second = string_t((res[3] != "") ? (res[3]) : (string_t("") + null_part));;
		parce_name.push_back(pair);
		str = res.suffix();
	}

	return parce_name;
}

auto ns_c_a::calculator::name_type::to_key(const parsed_t& name)->key_t
{
	if (!name.size()) {
		return key_t("");
	}
	key_t alter_name;

	std::for_each(name.cbegin(), name.cend(), [&alter_name](name_type::parsed_t::value_type name_part) {
		alter_name = alter_name + name_divider + name_part.first + name_divider + name_part.second;
	});

	alter_name.erase(alter_name.begin());
	if (alter_name.back() == name_divider) {
		alter_name.pop_back();
	}

	return alter_name;
}

auto ns_c_a::calculator::get_names(const string_t& expression) -> nameslist_t
{
	static const string_t digits = "0123456789";
	static const string_t special = "()<>!=-*^+/%";

	nameslist_t names;

	string_t buffer = "";

	auto expr = space_free(expression);

	std::for_each(expr.cbegin(), expr.cend(), [&](string_t::value_type ch)->void {
		if (special.find(ch) != string_t::npos) {
			names.push_back(name_type(buffer));
			buffer.clear();
		}
		else if (digits.find(ch) != string_t::npos) {
			if (buffer.size()) {
				buffer += ch;
			}
			else {
				names.push_back(name_type(buffer));
				buffer.clear();
			}
		}
		else {
			buffer += ch;
		}
	});

	names.push_back(name_type(buffer));
	buffer.clear();

	auto names_end  = std::remove(names.begin(), names.end(), string_t(""));
	auto null_count = std::count(names_end, names.end(), string_t(""));
	while (null_count) {
		--null_count;
		names.pop_back();
	}	

	return names;
}

auto ns_c_a::calculator::get_value(scheme_ptr& scheme, name_type::parsed_t& parsed_name)->int_t
{
	auto it = parsed_name.cbegin();
	auto element_ptr = scheme->element({ it->first, std::stoul(it->second) });
	++it;


	if (it->first == ::cry::scheme::run) {
		return element_ptr->set_input(std::stoull(it->second)).run().to_ulong();
	}
	
	string_t func_part = "";
	for (; it != parsed_name.cend(); ++it)
	{
		func_part += it->first + name_divider + it->second;
	}


	if (it->first == cry::scheme::output && it->second == "0") {
		return element_ptr->output().to_ulong();
	}
	else 
		if (it->first == ::cry::scheme::run) {
			return element_ptr->set_input(std::stoull(it->second)).run().to_ulong();
		}
		else {
			throw unknown_value("unknown_value : " + it->first);
		}
	


	return int_t(0);
}

auto ns_c_a::calculator::get_values(const vars_t& vars, scheme_ptr& scheme, const nameslist_t& names)->vars_t
{
	vars_t variables;
	
	try {
		std::for_each(names.cbegin(), names.cend(),
			[&](nameslist_t::value_type name)
		{
			if (name.name[0] == syntax::keywords::el_name_begin) {
				try {
					variables[name.key] = get_value(scheme, name.parsed);
				}
				catch (std::out_of_range& a) {
					throw unknown_value(name.name);
				}
			}
			else {
				try {
					variables[name.key] = vars.map().at(name.key);
				}
				catch (std::out_of_range& a) {
					throw unknown_value(name.name);
				}
			}
		});

	}
	catch (unknown_value& ex) {
		std::cout << ex.what() << std::endl;
		throw;
	}

	return variables;
}

auto ns_c_a::calculator::fix_name_in_expr(const string_t& expression, const nameslist_t& names) -> string_t
{
	string_t new_expr = expression;

	static const string_t special = "*^<=>!-/+()%";
	
	std::for_each(names.cbegin(), names.cend(),
		[&new_expr](nameslist_t::value_type name) {
			
			for (auto pos = new_expr.find(name.name);
				pos != string_t::npos;
				pos = new_expr.find(name.name, pos))
			{	
				auto ch_l = (pos == 0) ? (special[0]) : (new_expr[pos - 1]);
				auto ch_r = (pos + name.name.size() == new_expr.size() ) ?
					(special[0]):(new_expr[pos + name.name.size()]);

				if (special.find(ch_l) != string_t::npos && special.find(ch_r) != string_t::npos) {
					new_expr.erase(pos, name.name.size());
					new_expr.insert(pos, name.key);
					pos += name.name.size();
				}
				else {
					++pos;
				}
			}
		}
	);

	return new_expr;
}

auto ns_c_a::calculator::calculate_simple(const string_t expression, vars_t& vars) -> int_t
{
	return ::calculator::calculate(expression.c_str(), vars).asInt();
}

auto ns_c_a::calculator::calculate(const string_t& expression, vars_t& vars, scheme_ptr& scheme_ptr)->int_t
{
	using strstack_t = std::stack<string_t>;
	using charsmap_t = std::map<char, char>;

	int_t answer;
	
	strstack_t stacker;
	charsmap_t brackets = {
		{ syntax::keywords::c_close_circle, syntax::keywords::c_open_circle },
		{ syntax::keywords::c_close_square, syntax::keywords::c_open_square }
	};

	auto expr = space_free(expression);
	
	stacker.push("");
	
	try {
		std::for_each(expr.cbegin(), expr.cend(),
			[&brackets, &stacker, &vars, &scheme_ptr](string_t::value_type ch)
		{
			using namespace syntax::keywords;
			auto scope_it = brackets.end();
			string_t buffer = "";

			if (ch == c_open_circle || ch == c_open_square) {
				stacker.top() += ch;
				stacker.push("");
			}
			else if ((scope_it = brackets.find(ch)) != brackets.end()) {
				auto crutch = stacker.top();
				stacker.pop();
				auto last_char = stacker.top().back();
				stacker.push(crutch);
				if (scope_it->second == last_char) {

					buffer = stacker.top();
					stacker.pop();

					auto names = get_names(buffer);
					auto local_vars = get_values(vars, scheme_ptr, names);
					auto e = fix_name_in_expr(buffer, names);
					auto value = calculate_simple(e, local_vars);

					stacker.top() += std::to_string(value) + ch;
				}
				else {
					throw exception_t("Incorrect bracket sequence");
				}
			}
			else {
				stacker.top() += ch;
			}

		}
		);


		if (stacker.size() != 1) {
			throw exception_t("Incorrect bracket sequence");
		}

		auto buffer = stacker.top();

		auto names = get_names(buffer);
		auto local_vars = get_values(vars, scheme_ptr, names);
		auto last_expr = fix_name_in_expr(buffer, names);
		answer = calculate_simple(last_expr, local_vars);

	}
	catch (unknown_value& ex) {
		throw;
	}

	return answer;
}

auto ns_c_a::calculator::calculate_left(const string_t& expression, vars_t& vars, scheme_ptr& scheme_ptr)->name_type
{
	using strstack_t = std::stack<string_t>;
	using charsmap_t = std::map<char, char>;

	int_t answer;

	strstack_t stacker;
	charsmap_t brackets = {
		{ syntax::keywords::c_close_circle, syntax::keywords::c_open_circle },
		{ syntax::keywords::c_close_square, syntax::keywords::c_open_square }
	};

	auto expr = space_free(expression);

	stacker.push("");

	try {
		std::for_each(expr.cbegin(), expr.cend(),
			[&brackets, &stacker, &vars, &scheme_ptr](string_t::value_type ch)
		{
			using namespace syntax::keywords;
			auto scope_it = brackets.end();
			string_t buffer = "";

			if (ch == c_open_circle || ch == c_open_square) {
				stacker.top() += ch;
				stacker.push("");
			}
			else if ((scope_it = brackets.find(ch)) != brackets.end()) {
				auto crutch = stacker.top();
				stacker.pop();
				auto last_char = stacker.top().back();
				stacker.push(crutch);
				if (scope_it->second == last_char) {

					buffer = stacker.top();
					stacker.pop();

					auto names = get_names(buffer);
					auto local_vars = get_values(vars, scheme_ptr, names);
					auto e = fix_name_in_expr(buffer, names);
					auto value = calculate_simple(e, local_vars);

					stacker.top() += std::to_string(value) + ch;
				}
				else {
					throw exception_t("Incorrect bracket sequence");
				}
			}
			else {
				stacker.top() += ch;
			}
		}
		);


		if (stacker.size() != 1) {
			throw exception_t("Incorrect bracket sequence");
		}

		

	}
	catch (unknown_value& ex) {
		throw;
	}

	auto buffer = stacker.top();

	return name_type(buffer);

}

auto ns_c_a::calculator::set_left(const name_type& name, vars_t& vars, scheme_ptr& scheme, int_t value)->int_t
{

	if (name.name[0] == syntax::keywords::el_name_begin) {
		auto it = name.parsed.begin();
		auto element_ptr = scheme->element({ it->first, \
			std::stoul(it->second) });
		++it;

		if (it->first == ::cry::scheme::input && it->second == "0") {
			element_ptr->set_input(value);
			return value;
		}
	}
	else {
		vars[name.key] = value;
	}

	return value;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

report_t ns_c_a::operations::add_element::doit(handler_t& handler)
{
	auto name_of_scheme = this_scheme_name;

	auto scheme_ptr = handler.schemes.at(name_of_scheme);

	auto option = any_cast<code::types::add_element>(handler.cursor->command);

	auto name = calculator::calculate_left(option.element_name_index, handler.variables, scheme_ptr);

	if (name.parsed.size() != 1) {
		return report_t("invalid name : " + name.name);
	}


	option.scheme_options.element_name  = name.parsed.front().first;
	option.scheme_options.element_index = foo::to_int_t(name.parsed.front().second);

	option.scheme_options.graphic_size.x = calculator::calculate(option.graphic_width , handler.variables, scheme_ptr);
	option.scheme_options.graphic_size.y = calculator::calculate(option.graphic_height, handler.variables, scheme_ptr);
	option.scheme_options.position.x = calculator::calculate(option.graphic_x, handler.variables, scheme_ptr);
	option.scheme_options.position.y = calculator::calculate(option.graphic_y, handler.variables, scheme_ptr);
	
	scheme_ptr->add_element(option);

	return report_t("element is added successfully");
}

report_t ns_c_a::operations::assigning::doit(handler_t& handler)
{
	auto name_of_scheme = this_scheme_name;
	auto scheme_ptr = handler.schemes.at(name_of_scheme);

	auto option = any_cast<code::types::assigning>(handler.cursor->command);

    auto value = cryptosha::anaconda::calculator::calculate(option.expression, handler.variables, scheme_ptr);
	auto namev = cryptosha::anaconda::calculator::calculate_left(option.left_part, handler.variables, scheme_ptr);

	auto res = cryptosha::anaconda::calculator::set_left(namev, handler.variables, scheme_ptr, value);
	

	return report_t(namev.name + " <- " + std::to_string(res));
}

report_t ns_c_a::operations::goto_after::doit(handler_t& handler)
{
	auto it = handler.code.begin();

	auto option = any_cast<code::types::goto_after>(handler.cursor->command);
		

	for (; it != handler.code.end(); ++it)
	{
		if (it->mark == option.mark) {
			handler.cursor = it;
			return report_t("moved to mark " + std::to_string(option.mark));
		}
	}

	return report_t("moing error");
}

report_t ns_c_a::operations::connect::doit(handler_t& handler)
{
	auto& option = any_cast<code::types::connect>(handler.cursor->command);

	if (option.pins_of_receiver.size() != option.pins_of_sender.size()) {
		return report_t("wrong parameters : size(pins_in) != size(pins_out)");
	}

	auto name_of_scheme = this_scheme_name;
	auto scheme_ptr = handler.schemes.at(name_of_scheme);

	auto name_sender = calculator::calculate_left(option.sender_name, handler.variables, scheme_ptr);
	if (name_sender.parsed.size() != 1) {
		return report_t("invalid name : " + name_sender.name);
	}

	auto name_receiver = calculator::calculate_left(option.receiver_name, handler.variables, scheme_ptr);
	if (name_receiver.parsed.size() != 1) {
		return report_t("invalid name : " + name_receiver.name);
	}

	elements::cipher_scheme::full_name sender_full_name = { name_sender.parsed.front().first, foo::to_int_t(name_sender.parsed.front().second) };
	elements::cipher_scheme::full_name receiver_full_name = { name_receiver.parsed.front().first, foo::to_int_t(name_receiver.parsed.front().second) };


	/*auto count = option.pins_of_receiver.size();	
	for (auto i = 0; i < count; ++i)
	{
		scheme_ptr->add_connection_fast(sender_full_name,   option.pins_of_sender[i],
										receiver_full_name, option.pins_of_receiver[i]);

	}*/

	return report_t("wires is added successfully");
}






