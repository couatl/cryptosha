#pragma once
#include <string>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <map>
#include <utility>
#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <boost/bimap.hpp>
#include <boost/any.hpp>
#include <fstream>
#include <stack>
#include <regex>
#include <thread>

#include "Interpretator/cparse/shunting-yard.h"



namespace cry {

	//types

	template< class T1, class T2>
	using bimap_t = boost::bimap<T1, T2>;

	using      any_t = boost::any;
	using   bitset_t = boost::dynamic_bitset<>;
	using  size_type = std::size_t;
	using    ulong_t = unsigned long;
	using       id_t = std::size_t;
	using     mark_t = unsigned long;
	
	using int_vector = std::vector<uint32_t>;

	using   string_t = std::string;
	using   report_t = string_t;
	using     name_t = string_t;
	using expression_t = string_t;
	using expressions = std::list<expression_t>;

	using istream_t = std::istream;
	using ostream_t = std::ostream;
	using ifstream_t = std::ifstream;
	using ofstream_t = std::ofstream;

	using exception_t = std::invalid_argument;
	using bad_any_cast = boost::bad_any_cast;


	using  int_t = decltype(calculator::calculate("0").asInt());
	using vars_t = TokenMap;

	using index_t = int_t;

	struct iosize_t {
		using type = ulong_t;

		type in;
		type out;

		iosize_t() = default;
		iosize_t(type in_, type out_) : in(in_), out(out_) {};
	};
	struct gsize_t {
		using type = ulong_t;

		type x;
		type y;

		gsize_t() = default;
		gsize_t(type x_, type y_) : x(x_), y(y_) {};
	};


	//and functions
	using boost::any_cast;


	/// all elements type
	enum class element_keys {
		buffer,       ///< buffer(x) = x
		invertor,     ///< invertor(x) = ~x
		shift_left,      ///< shift bit vector by k bits to the left
		shift_right,     ///< shift bit vector by k bits to the right
		cycle_shift_left,  ///< cyclic shift bitvector by k bits to the left
		cycle_shift_right, ///< cyclic shift bitvector by k bits to the right
		p_block,             ///< permutation of the input bit vector

		conjunctor,          ///< conjunctor(x,y) = x/\y = xy
		disjunctor,          ///< disjunctor(x,y) = x\/y 
		xor,                 ///< xor(x,y) = x (+) y
		nor,	             ///< nor(x,y) = ~(x\/y)
		nand,                ///< nand(x,y) = x|y
		sum,				 ///< sum[n](x,y) = x + y (mod n)
		equality,            ///< equality(x,y) = x (+) y (+) i, i = (11....1)

		simple_sbox,         ///< bijective relation on the set of weights of the Boolean cube, simple_sbox[f](x) = y, where  f(|x|) = |y| 
		complex_sbox,        ///< general concept of Sbox

		custom               ///< custom component for a plug-in
	};

	namespace elements {

		class base_interface;

		class basic_element;

		class unary;
		template<class func> class binary;

		class buffer;
		class invertor;
		class shift_left;
		class shift_right;
		class cycle_shift_left;
		class cycle_shift_right;
		class permutation_block;

		class conjunctor;
		class disjunctor;
		class xor;
		class nor;
		class nand;
		class sum;
		class equality;

		class simple_sbox;
		class complex_sbox;

		class custom;

		class simple_scheme;
		class cipher_scheme;
		class graphic_scheme;
	}

	using element_ptr = std::shared_ptr<elements::basic_element>;
	using scheme_ptr = std::shared_ptr<elements::graphic_scheme>;

	namespace syntax {

		namespace keywords {
			static const string_t add("add");
			static const string_t del("delete");
			static const string_t disconnect("disconnect");
			static const string_t connect("connect");
			static const string_t create("create");
			static const string_t run("run");

			static const string_t c_for("for");
			static const string_t c_if("if");
			static const string_t c_while("while");
			static const string_t c_open("{");
			static const string_t c_close("}");
			static const string_t c_open_l("[");
			static const string_t c_close_l("]");
			static const string_t c_open_m("(");
			static const string_t c_close_m(")");

			static const string_t free("free");
			static const string_t show("show");
			static const string_t list("list");
			static const string_t draw("draw");

			static const char c_open_circle = '(';
			static const char c_close_circle = ')';

			static const char c_open_square = '[';
			static const char c_close_square = ']';

			static const char el_name_begin = '@';

			static const char name_divider = '_';
			static const char null_part = '0';

			static const string_t op_assigning("="); // but i'd prefer "<-" to "=" 
		}

		namespace element_names {
			static const string_t buffer("buffer");
			static const string_t invertor("invertor");
			static const string_t shift_left("shift<<");
			static const string_t shift_right("shift>>");
			static const string_t cycle_shift_left("<<shift<<");
			static const string_t cycle_shift_right(">>shift>>");
			static const string_t p_block("p-block");

			static const string_t and("and");
			static const string_t or("or");
			static const string_t xor("xor");
			static const string_t nor("nor");
			static const string_t nand("nand");
			static const string_t sum("sum");
			static const string_t equal("equal");

			static const string_t simple_sbox("sbox");
			static const string_t complex_sbox("Sbox");
			static const string_t custom("custom");
		}

		/*namespace regs_str {
			static const string_t assinging = string_t("\\s*(.+)\\s*") + keywords::op_assigning + string_t("\\s*(.+)\\s*");
			static const string_t add = string_t \
				("\\s*add\\s+(\\w+)\\s+@(.+)\\s+(\\d+)\\s*->\\s*(\\d+)\\s+\p(\\(\\s*(.+)\\s*\\,\\s*(.+)\\s*\\))?\\s*\s(\\(\\s*(.+)\\s*\\,\\s*(.+)\\s*\\))?\\s*");
			static const string_t del = string_t("\\s*del\\s+@(\\w+)\\s*");
			static const string_t assembly = string_t("\\s*assembly\\s*");
			static const string_t run = string_t("\\s*run\\s*");
			static const string_t script = string_t("\\s*script\\s+(\\w+\\.txt)\\s*");
			static const string_t connect = string_t("\\s*connect\\s+@(\\w+)\\s+(\\[[\\s*\\d+\\s+]+\\])\\s*@(\\w+)\\s*(\\[[\\s*\\d+\\s+]+\\])\\s*");
			static const string_t m_for = string_t("\\s*for\\s*\\(\\s*(.+)\\s*;\\s*(.+)\\s*;\\s*(.+)\\s*\\)\\s*");
			static const string_t add_s_p = string_t("\\s*add\\s+(\\w+)\\s+@(\\w+)\\s+(\\d+)\\s*->\\s*(\\d+)\\s+(\\w)(\\[[\\s*\\d+\\s+]+\\])\\s*");

		}
		*/

		namespace regs_str {

			static const string_t assinging = string_t("\\s*(.+)\\s*") + keywords::op_assigning + string_t("\\s*(.+)\\s*");
			static const string_t add = string_t \
				("\\s*add\\s*\\(\\s*(\\w+)\\s*\,\\s*@(.+)\\s*\,\\s*(\\d+)\\s*\,\\s*(\\d+)\\s*\,\\s*(\<\\s*(.+)\\s*\\,\\s*(.+)\\s*\>)?\\s*\,\\s*(\<\\s*(.+)\\s*\,\\s*(.+)\\s*\>)?\\s*\\)\\s*");
			static const string_t del = string_t("\\s*del\\s*\\(\\s*@(.+)\\s*\\)\\s*");
			static const string_t assembly = string_t("\\s*assembly\\s*");
			static const string_t run = string_t("\\s*run\\s*");
			static const string_t script = string_t("\\s*script\\s*\\((\\w+\\.txt)\\s*\\)\\s*");
			static const string_t connect = string_t("\\s*connect\\s*\\(\\s*@(.+)\\s*\,\\s*\<\\s*(.+)\\s*\>\\s*\,\\s*@(.+)\\s*\,\\s*\<\\s*(.+)\\s*\>\\s*\\)\\s*");
			static const string_t m_for = string_t("\\s*for\\s*\\(\\s*(.+)\\s*;\\s*(.+)\\s*;\\s*(.+)\\s*\\)\\s*");
			static const string_t add_s_p = string_t("\\s*add\\s*\\(\\s*(\\w+)\\s*\,\\s*@(.+)\\s*\,\\s*(\\d+)\\s*\,\\s*(\\d+)\\s*\,\\s*(\\w)(\<[\\s*\\d+\\s+]+\>)\\s*\\)\\s*");
		
		}

		namespace regs
		{
			static const std::regex add(regs_str::add);
			static const std::regex assembly(regs_str::assembly);
			static const std::regex run(regs_str::run);
			static const std::regex del(regs_str::del);
			static const std::regex script(regs_str::script);
			static const std::regex connect(regs_str::connect);
			static const std::regex assinging(regs_str::assinging);
			static const std::regex m_for(regs_str::m_for);
			static const std::regex add_s_p(regs_str::add_s_p);
		}
	}

	namespace code {

		enum class keyword_t {
			script,
			assinging,
			goto_after,
			free,

			add_element,
			delete_element,
			assembly,
			run,
			connect,
			disconnect,

			show,
			draw,
			ls
		};
		
		static const std::map<string_t, element_keys> name_to_element_key = {

			{ syntax::element_names::buffer, element_keys::buffer },
			{ syntax::element_names::invertor, element_keys::invertor },
			{ syntax::element_names::shift_left, element_keys::shift_left },
			{ syntax::element_names::shift_right, element_keys::shift_right },
			{ syntax::element_names::cycle_shift_left, element_keys::cycle_shift_left },
			{ syntax::element_names::cycle_shift_right, element_keys::cycle_shift_right },
			{ syntax::element_names::p_block, element_keys::p_block },

			{ syntax::element_names::and, element_keys::conjunctor },
			{ syntax::element_names::or, element_keys::disjunctor },
			{ syntax::element_names::xor, element_keys::xor },
			{ syntax::element_names::nor, element_keys::nor },
			{ syntax::element_names::nand, element_keys::nand },
			{ syntax::element_names::sum, element_keys::sum },
			{ syntax::element_names::equal, element_keys::equality },

			{ syntax::element_names::simple_sbox, element_keys::simple_sbox },
			{ syntax::element_names::complex_sbox, element_keys::complex_sbox },

			{ syntax::element_names::custom, element_keys::custom },
		};

		namespace types {

			namespace invis {

				struct _script {
					string_t ofstream;


				};

				struct _assigning {
					expression_t left_part;
					expression_t expression;


				};

				struct _goto_after {
					mark_t mark;

					
				};

				struct _free {
					expression_t value_name;


				};

				struct _add_element {

					struct scheme_parameters {

						name_t element_name;
						index_t element_index;
						gsize_t graphic_size;
						gsize_t position;

					};

					struct unevaluated_parameters {

						expression_t graphic_width;
						expression_t graphic_height;
						expression_t graphic_x;
						expression_t graphic_y;

					};

					struct types{
						using s_vector = int_vector;
						using p_vector = int_vector;
						using element = element_keys;
						using shift_size = size_type;
					};
					
					enum class keys {
						element_key,
						shift_size,
						p_vector,
						s_vector,
					};

					using s_vector = int_vector;
					using p_vector = int_vector;
					using element = element_keys;
					using shift_size = size_type;
					
					using extra_parameters = std::unordered_map<keys, any_t>;

					expression_t element_name_index;
					
					element_keys element_key = element_keys::buffer;

					iosize_t  iosize;

					expression_t graphic_width;
					expression_t graphic_height;
					expression_t graphic_x;
					expression_t graphic_y;

					extra_parameters  extra_options;
					scheme_parameters scheme_options;

					_add_element() = default;
				};

				struct _delete_element {
					expression_t element_name;

				};
				
				struct _connect {
					expression_t sender_name;
					expression_t receiver_name;

					expressions pins_of_sender;
					expressions pins_of_receiver;
				};

				struct _disconnect {
					expression_t sender_name;
					expression_t receiver_name;

					int_vector pins_of_sender;
					int_vector pins_of_receiver;
				};

				struct _draw {

					using expression_list = std::list<expression_t>;

					expression_list names; ///< if list is empty, Anaconda will draw the whole circuit
				};


			}

			using script = invis::_script;
			using assigning = invis::_assigning;
			using goto_after = invis::_goto_after;
			using free = invis::_free;

			using add_element = invis::_add_element;
			using delete_element = invis::_delete_element;
			using connect = invis::_connect;
			using disconnect = invis::_disconnect;
			using expression = expression_t;

			using draw = invis::_draw;
		}

		struct simple_command {
			using options_t = any_t;

			mark_t    mark;
			string_t  condition;
			keyword_t keyword;
			options_t command;
		};

		using code_type = std::list<simple_command>;
	}

	namespace error_messages {
		static const string_t inv_input("invalid input data");
		static const string_t out_of_range("out of range");
		static const string_t el_exists("element with the same name already exists");
		static const string_t el_dont_exist("element with the same name don't exist");
		static const string_t trigger_trying("nice try to make a trigger");
	}

	namespace foo {

		static const std::map<char, string_t> hex_in_bin = {
			{ '0', "0000" }, { '1', "0001" }, { '2', "0010" }, { '3', "0011" },
			{ '4', "0100" }, { '5', "0101" }, { '6', "0110" }, { '7', "0111" },
			{ '8', "1000" }, { '9', "1001" }, { 'a', "1010" }, { 'b', "1011" },
			{ 'c', "1100" }, { 'd', "1101" }, { 'e', "1110" }, { 'f', "1111" }
		};

		string_t bitset_to_str(const bitset_t& bs, size_type size);
		bitset_t str_to_bitset(const string_t& str, size_type size);

		std::vector<bitset_t> mask_to_bitset(const string_t & str);
		bitset_t hex_to_bitset(const string_t & str, size_type size);
		string_t bitset_to_hex(const bitset_t& bs);

		int_vector get_reverse(const int_vector& vector);
		bool is_invertible(const int_vector& vector);
		
		bool get_bit(const size_type & value, size_type pos);

		int_t to_int_t(const string_t& str);
	}

	namespace scheme {

		namespace names {
			static const string_t text("text");
			static const string_t cipher("cipher");
			static const string_t key("key");
		}

		static const string_t output("out");
		static const string_t input("in");
		static const string_t run("run");
		static const string_t pos("pos");
		static const string_t gsize("gsize");
		static const string_t x("x");
		static const string_t y("y");
		
	}

}

namespace cryptosha {

	using scheme = cry::elements::graphic_scheme;

	class console_reader;
	class interpretator;

	class analysis;
	class bitset_pool;
}