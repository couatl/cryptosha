#pragma once 

#include "analysis/analysis.h"
#include "reader/Reader.h"

namespace cryptosha {	

	namespace anaconda {

		static const string_t this_scheme_name{ "this scheme" };
		static const char     name_divider = '_';
		static const string_t null_part = "0";

		using  ::cry::scheme_ptr;
		using  ::cry::element_ptr;

		class calculator
		{
			struct name_type
			{
				using parsed_t = std::list<std::pair<string_t, string_t>>;
				using key_t = std::string;

				key_t       key;
				string_t    name;
				parsed_t    parsed;

				static auto to_parsed(const string_t& name)->parsed_t;
				static auto to_key(const parsed_t& name)->key_t;


				explicit name_type(const string_t& str_name) : name(str_name)
				{
					parsed = to_parsed(str_name);
					key = to_key(parsed);
				}

				friend bool operator == (const name_type& name, const string_t str) 
				{
					return name.name == str;
				}
			};

			using unknown_value = exception_t;

			using nameslist_t = std::list<name_type>;

		
			static auto get_names(const string_t& expression) -> nameslist_t;

			static auto get_values(const vars_t& vars, scheme_ptr& scheme, const nameslist_t& names)->vars_t;

			static auto fix_name_in_expr(const string_t& expression, const nameslist_t& names)->string_t;

			static auto get_value(scheme_ptr& scheme, name_type::parsed_t& parsed_name) -> int_t;			
			
			static auto calculate_simple(const string_t expression, vars_t& vars) -> int_t;

		public:
			static auto space_free(const string_t& str)->string_t;

			static auto calculate(const string_t& expression, vars_t& vars, scheme_ptr& scheme_ptr) -> int_t;

			static auto calculate_left(const string_t& expression, vars_t& vars, scheme_ptr& scheme_ptr) -> name_type;

			static auto set_left(const name_type& name, vars_t& vars, scheme_ptr& scheme, int_t value) -> int_t;

		};

		struct handler_t
		{
			using cursor_type = code::code_type::iterator;
			using name_type = string_t;
			using schemes_t = std::unordered_map<name_type, scheme_ptr>;


			code::code_type       code;
			cursor_type         cursor;
			schemes_t          schemes;
			vars_t           variables;

		};

		namespace operations {

			struct base
			{
				virtual report_t doit(handler_t& handler) = 0;
			};

			struct add_element : public base
			{
				report_t doit(handler_t& handler) override;
			};

			struct add_connection : public base
			{
				report_t doit(handler_t& handler) override;
			};

			struct assigning : public base
			{
				report_t doit(handler_t& handler) override;
			};

			struct goto_after : public base
			{
				report_t doit(handler_t& handler) override;
			};

			struct connect : public base
			{
				report_t doit(handler_t& handler) override;
			};

			struct assembly : public base
			{
				report_t doit(handler_t& handler) override;
			};

			struct run : public base
			{
				report_t doit(handler_t& handler) override;
			};

			struct run_element : public base
			{
				report_t doit(handler_t& handler) override;
			};

			struct run_scheme : public base
			{
				report_t doit(handler_t& handler) override;
			};

			struct clear_scheme : public base
			{
				report_t doit(handler_t& handler) override;
			};

		}


		class interpretator
		{
			using reader_ptr = std::unique_ptr<console_reader>;
			using operation_ptr_t = std::unique_ptr<operations::base>;
			using operations_t = std::map<code::keyword_t, operation_ptr_t>;

		public:
			/*interpretator(size_type text_size, size_type key_size, size_type cipher_size,
				std::basic_istream<char, std::char_traits<char>>& in, 
				std::basic_ostream<char, std::char_traits<char>>& out) 
				 : reader(in, out)
			{
				handler.schemes[this_scheme_name] = scheme_ptr(new scheme(text_size, key_size, cipher_size));

				operations[code::keyword_t::add_element] = std::move(operation_ptr_t(new operations::add_element()));
				operations[code::keyword_t::assinging] = std::move(operation_ptr_t(new operations::assigning()));
				operations[code::keyword_t::goto_after] = std::move(operation_ptr_t(new operations::goto_after()));
				operations[code::keyword_t::connect] = std::move(operation_ptr_t(new operations::connect()));
				operations[code::keyword_t::assembly] = std::move(operation_ptr_t(new operations::assembly()));
				operations[code::keyword_t::run] = std::move(operation_ptr_t(new operations::run()));


			}*/

			interpretator(const string_t& report_file_name,
						   const string_t& in_file_name,
						   const string_t& out_file_name)
			{

				reader = std::move(reader_ptr(new console_reader(in_file_name, out_file_name)));

				handler.schemes[this_scheme_name] = scheme_ptr(new scheme(16,16,16));

				operations[code::keyword_t::add_element] = std::move(operation_ptr_t(new operations::add_element()));
				operations[code::keyword_t::assinging] = std::move(operation_ptr_t(new operations::assigning()));
				operations[code::keyword_t::goto_after] = std::move(operation_ptr_t(new operations::goto_after()));
				operations[code::keyword_t::connect] = std::move(operation_ptr_t(new operations::connect()));
				operations[code::keyword_t::assembly] = std::move(operation_ptr_t(new operations::assembly()));
				operations[code::keyword_t::run] = std::move(operation_ptr_t(new operations::run()));
				operations[code::keyword_t::run_element] = std::move(operation_ptr_t(new operations::run_element()));
				operations[code::keyword_t::run_scheme] = std::move(operation_ptr_t(new operations::run_scheme()));
				operations[code::keyword_t::clear_scheme] = std::move(operation_ptr_t(new operations::clear_scheme()));
			}


			scheme_ptr get_scheme()
			{
				return handler.schemes[this_scheme_name];
			}

			interpretator& update_code(code::code_type&& new_code)
			{
				handler.code = std::move(new_code);
				return *this;
			}

			reports do_code()
			{
				reports reports;

				handler.cursor = handler.code.begin();

				while (handler.cursor != handler.code.end()) {

					reports::value_type rep;

					if (!anaconda::calculator::space_free(handler.cursor->condition).size()) {
						rep = operations[handler.cursor->keyword]->doit(handler);
					}
					else{
						auto scheme = handler.schemes.at(this_scheme_name);
						if (anaconda::calculator::calculate(handler.cursor->condition, handler.variables, scheme)) {
							rep = operations[handler.cursor->keyword]->doit(handler);
						}
					}

					reports.push_back(std::move(rep));

					++handler.cursor;
				}

				return reports;
			}

			interpretator& read()
			{
				handler.code = reader->read();
				return *this;
			}

			interpretator& read(string_t&& simple_cmd)
			{
				handler.code = reader->read(std::move(simple_cmd));
				return *this;
			}

			interpretator& set_new_input(const string_t& input_file_name)
			{

				reader->set_input(input_file_name);

				return *this;
			}

			interpretator& new_scheme(size_type text_size, size_type key_size, size_type out_size)
			{
				handler.schemes[this_scheme_name].reset();
				handler.schemes[this_scheme_name] = scheme_ptr(new scheme(text_size,key_size,out_size));
			}

			bool ifstream_good() const
			{
				return reader->ifstream_good();
			}

			~interpretator() = default;

		private:
			handler_t      handler;
			reader_ptr     reader;
			operations_t   operations;

		};
	}
}
