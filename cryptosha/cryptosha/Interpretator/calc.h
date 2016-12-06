/*#pragma once
#include "../settings.h"
#include <iostream>
#include <regex>
#include <string>
#include <list>
#include "../xElements/xScheme.h"
/*
namespace ax {

	class calculator
	{


		using string_t = std::string;
		using name_t = std::list<std::pair<string_t, string_t>>;
		using int_t = int_t;

	public:
		auto operator()(const char * expression, scheme_ptr_t& scheme_ptr)->int_t
		{
			return operator()(string_t(expression), scheme_ptr);
		}
		auto operator()(string_t& expression, scheme_ptr_t& scheme_ptr) -> int_t
		{
			using string_stack = std::stack<string_t>;
			using scope_stack = std::stack<char>;

			string_t buffer = "";
			string_stack stacker;
			scope_stack  scopes;

			stacker.push("");

			auto expr = space_free(expression);

			std::for_each(expr.cbegin(), expr.cend(), [this, &scheme_ptr, &stacker, &scopes](string_t::value_type ch)->void {

				if (ch == c_open_circle || ch == c_open_square) {
					scopes.push(ch);
					stacker.top() += ch;
					stacker.push("");
				}
				else if (ch == c_close_circle || ch == c_close_square) {

					if (ch == c_close_circle && scopes.top() != c_open_circle)
						throw std::invalid_argument("Incorrect bracket sequence");
					if (ch == c_close_square && scopes.top() != c_open_square)
						throw std::invalid_argument("Incorrect bracket sequence");

					scopes.pop();

					auto value = this->calculate_simple(stacker.top(), scheme_ptr);

					stacker.pop();

					stacker.top() += std::to_string(value) + ((ch == c_close_circle) ? (c_close_circle) : (c_close_square));
				}
				else {
					stacker.top() += ch;
				}
			});

			if (scopes.size())
				throw std::invalid_argument("Incorrect bracket sequence");

			return calculate_simple(stacker.top(), scheme_ptr);
		}

	private:
		

		auto get_value(string_t& name, scheme_ptr_t& scheme_ptr)->int_t
		{
			return int_t(0);
		}
		auto set_value(string_t& name, scheme_ptr_t& scheme_ptr, int_t value)->int_t;
		
		
		
		

		auto calculate_simple(string_t& expr, scheme_ptr_t& scheme_ptr) -> int_t
		{
			using strings_t = std::list<string_t>;
			string_t digits = "0123456789";
			string_t special = "()-+/*%";

			int_t value = 0;
			string_t buffer = "";
			strings_t names;
			bool  open_scope_flag = false;

			std::for_each(expr.cbegin(), expr.cend(), [&](string_t::value_type ch)->void {
				if (special.find(ch) != string_t::npos) {
					names.push_back(std::move(buffer));
				}
				else if (digits.find(ch) != string_t::npos) {
					if (buffer.size()) {
						buffer += ch;
					}
					else {
						names.push_back(std::move(buffer));
					}
				}
				else {
					buffer += ch;
				}
			});

			names.push_back(std::move(buffer));

			auto names_end = std::remove(names.begin(), names.end(), string_t(""));

			for (auto i = std::count_if(names_end, names.end(), [](strings_t::value_type str)->bool {return str == ""; }); i > 0; --i)
			{
				names.pop_back();
			}
			std::for_each(names.begin(), names.end(), [](strings_t::value_type str) { std::cout << str << std::endl; });

			TokenMap vars;

			std::for_each(names.begin(), names.end(), [this, &vars, &scheme_ptr, &expr](strings_t::value_type name) {
				size_t pos = 0;
				while ((pos = expr.find(name, pos)) != string_t::npos) {
					expr.erase(pos, name.size());
					expr.insert(pos, get_alter_name(name));
					++pos;
				}
				try {
					vars[get_alter_name(name)] = variables.map().at(get_alter_name(name));
				}
				catch (std::out_of_range) {
					vars[get_alter_name(name)] = get_value(name, scheme_ptr);
				}
			});

			value = ::calculator::calculate(expr.c_str(), vars).asInt();

			return value;
		}
	};

}
*/