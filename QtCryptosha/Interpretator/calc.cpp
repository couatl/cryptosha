/*#include "calc.h"

auto calculate_expr::operator()(const char * expression, TokenMap& variables)->int_t
{
	return operator()(string_t(expression), variables);
}
auto calculate_expr::operator()(string_t& expression, TokenMap& variables) -> int_t
{
	using string_stack = std::stack<string_t>;
	using scope_stack = std::stack<char>;

	string_t buffer = "";
	string_stack stacker;
	scope_stack  scopes;

	stacker.push("");

	auto expr = space_free(expression);

	std::for_each(expr.cbegin(), expr.cend(), [this, &variables, &stacker, &scopes](string_t::value_type ch)->void {

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

			auto value = this->calculate_simple(stacker.top(), variables);

			stacker.pop();

			stacker.top() += std::to_string(value) + ((ch == c_close_circle) ? (c_close_circle) : (c_close_square));
		}
		else {
			stacker.top() += ch;
		}
	});

	if (scopes.size())
		throw std::invalid_argument("Incorrect bracket sequence");

	return calculate_simple(stacker.top(), variables);
}

calculate_expr::string_t calculate_expr::space_free(string_t& input_str)
{
	for (auto it = input_str.begin(); it != input_str.end();)
	{
		if (*it == ' ')
			input_str.erase(it);
		else
			++it;
	}
	return input_str;
}
calculate_expr::name_t calculate_expr::parse_name(string_t str)  // thank you, Danchetto!
{
	std::regex e("@?(\\w+)(\\[\\s*(\\w+-?\\w*)\\])?\\.?");
	std::smatch res;
	name_t name;

	while (std::regex_search(str, res, e))
	{
		std::pair<string_t, string_t> pair;
		if (str[0] == '@') {
			pair.first = string_t("_____") + string_t(res[1]);
		}
		else {
			pair.first = res[1];
		}
		pair.second = res[3];
		name.push_back(pair);
		str = res.suffix();
	}

	return name;
}
calculate_expr::string_t calculate_expr::get_alter_name(const string_t& str_name)
{
	auto name = parse_name(str_name);
	string_t alter_name;

	std::for_each(name.cbegin(), name.cend(), [&alter_name](name_t::value_type name_part) {
		alter_name = alter_name + "_" + name_part.first + "_" + name_part.second;
	});

	alter_name.erase(alter_name.begin());
	if (alter_name.back() == '_') {
		alter_name.pop_back();
	}

	return alter_name;
}
calculate_expr::int_t calculate_expr::get_value(string_t& name)
{
	static int_t iii = 0;
	return iii++;
}
auto calculate_expr::calculate_simple(string_t& expr, TokenMap& variables) -> int_t
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

	std::for_each(names.begin(), names.end(), [this, &vars, &variables, &expr](strings_t::value_type name) {
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
			vars[get_alter_name(name)] = get_value(name);
		}
	});

	value = calculator::calculate(expr.c_str(), vars).asInt();

	return value;
}*/