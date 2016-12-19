# Cryptosha
---------------------------------------------------
### ~~Собирай~~ пиши схемы!
![image](https://pp.vk.me/c837629/v837629581/13f4b/aLmICJP6wTE.jpg)
----------------------------------------------------



> [Введение](#Введение)

> [Актуальность проекта](#Актуальность-проекта)

> [Задачи проекта](#)

> [Выбор языка программирования, библиотек, фреймворков и среды разработки](https://github.com/Alex-Kuz/cryptosha/blob/master/report.md#Выбор-языка-программирования-библиотек-фреймворков-и-среды-разработки)

> Немного о функциональных элементах (только для дайверов)

> Структура проекта как библиотеки

>> [Регулирующий файл](#Регулирующий-файл)

>> [Базовый элемент](#Базовый-элемент)

>> [Унарные операции](#Унарные-операции)

>> Бинарные операции

>> [Схема шифрования](#Схема-шифрования)

>> Графическая схема

>> [Утилиты для линейного/дифференциального криптоанализа](#Утилиты-для-линейногодифференциального-криптоанализа)

>> [Синтаксический анализатор](#Синтаксический-анализатор)

>> Интерпретатор

>> Язык программирования схем

>

> Структура приложения

> Способы использования Cryptosha в сторонних проектах

> Способы расширения проекта

>> Добавление нового функционального элемента

>> Изменение синтаксиса языка

>> Добавление команд

> [Графический интерфейс](#Графический-интерфейс)

> Пример работы приложения 

> Вывод 




## Введение 
Cryptosha - проект, предназначенный для работы с блочными схемами шифрования, а именно сборка схемы, прогон значений через нее и криптоанализ этой схемы. 
Ключевой момент проекта заключается в способе выполнения всех этих операций - они осуществляются с помощью кода. Теперь пользователь может построить схему, 
написав программный код, запустить ее всего одной строкой. Не собирайте схемы - пишите их. 

## Актуальность проекта 
Есть огромное количество подобных проектов с подобным функционалом, но ни один из них не закроет нам семестр по АЯ.

## Выбор языка программирования, библиотек, фреймворков и среды разработки 
Графический интерфейс проекта Cryptosha выполнен в среде разработки Qt.

Этот выбор был сделан по причине удобства и широкого функционала данной среды. Также, так как код программы написан на C++, его без проблем можно использовать в Qt. WxWidgets было решено не использовать, так как работа с графическим дизайнером возможна только в Code::Blocks, где это неудобно устроено. Графический дизайнер позволяет существенно сократить написание программы путем уменьшения написанного вручную кода.


## Структура проекта как библиотеки
### Регулирующий файл

Все необходимые для функционирования библиотеки типы, функции и константы содержатся в файле settings.h. Так как изначально проект делился на 3 части:
- система виртуальных функциональных элементов и схемы
- разработка необходимых утилит для дифференциального и линейного криптоанализов (далее будем говорить просто - криптоанализ)
- разработка синтаксического анализатора и интерпретатора 
Для избежания большинства конфликтов типов и методов, а так же расположения объектов в пространствах имен, был создан этот регулирующий файл. Таким образом, он позволяет быстрее разрабатывать интерфейсы, предоставляемые каждым модулем, так как он уже практически описан в этом файле. Если представлять весь проект как сеть заголовочных файлов, то settings.h - исток сети.

В этом же файле сразу показана общая структура проекта, выражающаяся в 2-х namespace'ах - cry и cryptosha.
```c++
namespace cryptosha {

	using scheme = cry::elements::graphic_scheme; // класс - схема, реализующая блочный шифр

	class console_reader;     // синтаксический анализатор
	class interpretator;      // интерпретатор програмного кода

	class analysis;           // класс, предоставляющий интерфейс для криптоанализа
}
```

Смысл пространствоа имен `cryptosha` - в отсутствии ненужных пользователю типов, функций и тд. Все, что нужно для надпроекта - интерпретатор и графические схемы (о них отдельно и позже).
Все, что требуется для контроля проекта содержится в пространстве имен `cry` (лишь за несколько дней до дедлайна это имя стало говорящим, а вообще - сокращение от названия проекта).
Так как в разработке проекта принимало участие (и скорее всего будет принимать участие) только три человека, то было легко договориться о названии типов для того же упрощения разработки интерфейсов.
Если тип простой, то к литералам названия этого типа прибавляется `_t` :
```c++
namespace cryptosha{
	
	using      any_t = boost::any;
	using   bitset_t = boost::dynamic_bitset<>;
	using  size_type = std::size_t;
	using    ulong_t = unsigned long;
	using       id_t = std::size_t;
	using     mark_t = unsigned long;
	
	using   string_t = std::string;
	using   report_t = string_t;
	using     name_t = string_t;
	using expression_t = string_t;
	

	using istream_t = std::istream;
	using ostream_t = std::ostream;
	using ifstream_t = std::ifstream;
	using ofstream_t = std::ofstream;

	using exception_t = std::invalid_argument;
	
	using  int_t = decltype(calculator::calculate("0").asInt());
	using vars_t = TokenMap;

	using index_t = int_t;

	struct iosize_t;
	struct gsize_t;
}
```

### Базовый элемент

```c++

class elements::basic_element 
{

public ctors:
	explicit basic_element(iosize_t::type size_in, iosize_t::type size_out);

	explicit basic_element(const basic_element&) = default;
//	explicit basic_element(basic_element&&) = default;

public methods:
	basic_element& set_input(const bitset_t& input_bitset);
	basic_element& set_input(bitset_t&& input_bitset);
	basic_element& set_input(const string_t& input_bitstr);
	basic_element& set_input(string_t&& input_bitstr);
	basic_element& set_input(int_t value);

	basic_element& set_null();

	virtual bitset_t run() = 0;

	
	bitset_t input() const;
	bitset_t output() const;

	bitset_t& input_ref();
	bitset_t& output_ref();

	bool input(size_type bit);
	bool output(size_type bit);

	
	iosize_t size()  const;
	iosize_t::type osize() const;
	iosize_t::type isize() const;

	inline static size_type get_element_count();

	dtor virtual ~basic_element();

protected data:
	iosize_t  m_size;

	bitset_t  m_input;
	bitset_t  m_output;

protected states:
	state_t m_state;

private static_data:
	static size_type  g_obj_count;

private methods:	
	inline void _ctor();

};
```

### Унарные операции

В Cryptosha пользователь может оперировать следующими унарными элементами:
- инвертор
- буфер
- циклический сдвиг влево/вправо
- s-box
- p-block




### Схема шифрования

```c++
class elements::cipher_scheme : public elements::basic_element
{
public:

	cipher_scheme(size_type text_size, size_type key_size, size_type out_size);

	id_t add_element(const factory_package& element_package);

	cipher_scheme& delete_element(const full_name_t& full_name);
	
	cipher_scheme& add_connection_fast(const full_name_t& sender_name, pin_t pin_out, \
		const full_name_t& receiver_name, pin_t pin_in);
	cipher_scheme& delete_connection(const full_name_t& sender_name, size_type pin_out, \
		const full_name_t& receiver_name, size_type pin_in);

	cipher_scheme& set_key(const string_t& key_vector);
	cipher_scheme& set_key(const int_t& key_value);
	cipher_scheme& set_text(const string_t& text_vector);
	cipher_scheme& set_text(const int_t& text_value);

	cipher_scheme& assembly();
	
	virtual bitset_t run() override;

	id_bitset run(const id_pool_t& element_pool);

	virtual ~cipher_scheme() = default;

protected:
	names_id_t  m_name_id;
	wires_t     m_wires;
	circuit_t   m_circuit;
	elements_t  m_elements;

	bitset_t    m_key;
	bitset_t    m_text;

	size_type   m_key_size;
	size_type   m_text_size;
};
```
Конструктор для создания схемы по размерам входного текста, ключа и выходного текста:
```c++ 
	cipher_scheme(size_type text_size, size_type key_size, size_type out_size);
```

Функция добавления элемента в схему, принимающая публичный пакет`*`:
```c++
	id_t add_element(const factory_package& element_package);
```

Методы установления значений ключа и входного текста:
```c++
	cipher_scheme& set_key(const string_t& key_vector);
	cipher_scheme& set_key(const int_t& key_value);
	cipher_scheme& set_text(const string_t& text_vector);
	cipher_scheme& set_text(const int_t& text_value);
```

Во время разработки схемы рассматривались несколько концепций ее логического устройства. В итоге была принята концепция несвязных структурных данных (элементы, провода и т.д.), позволяющих собрать в каком-то виде виртуальную схему.
```c++
	cipher_scheme& assembly();
```
В схеме каждый элемент регистрируется под уникальным числом - `id_t`. 

### Утилиты для линейного/дифференциального криптоанализа
В проекте присутствует класс `cryptosha::analysis`, предоставляющий возможность пользователю проводить криптоанализ над шифром. На данный момент в нем несколько методов: прогон множества бинарных наборов через элемент схемы, слой или всю схему, а также нахождение наиболее вероятного дифференциала наборов при заданном дифференциале входных наборов после прогона через элемент.

Методы прогона похожи по названию и сигнатуре: 
```c++
	bitset_map & run_element(element_ptr obj, const bitset_pool & input);
```

Она принимает в параметрах указатель на элемент схемы и множество наборов, которые необходимо прогнать.
```с++
	bitset_map run_scheme(xScheme_ptr scheme, const bitset_pool & input);
```

Аналогично с run_element, только передается указатель на схему, а не элемент.
```c++
	cipher_scheme::id_bitset run_layer(layer_t layer,const bitset_pool & input);
```

Этот метод прогоняет слой схемы и возвращает объект типа cipher_scheme::id_bitset, который определен как `std::map<id_t, bitset_t>`, где id_t – это id элемента, а bitset_t – битсет.
А метод для нахождения наиболее вероятного набора имеет такую сигнатуру.
```c++
	string_t gretest_potentional(element_ptr obj, const string_t & diff, const bitset_pool & input);
```

Она принимает указатель на элемент схемы, дифференциал входных наборов и само множество наборов, из которых и берутся значения для прогона.
Данные методы существенно упростят проведение криптоанализа, в особенности на больших схемах.

### Синтаксический анализатор

Для синтаксического анализа вводимых пользователем строк используется класс console_reader .  
В качестве полей этот класс содержит в себе : 
•	стек для хранения блоков кода - `std::stack<stack_elem> ns_stack`,
•	стек для строк - `std::stack<string_t> input_stack`, 
•	поток ввода - `std::reference_wrapper<std::istream> input`, 
•	поток вывода - `std::reference_wrapper<std::ostream> output`,
•	список псевдокода - `code::code_type code`.

Основными методами класса являются private – методы.
private – методы класса:
```c++
	code::simple_command console_reader::simple_cmd_handle(string_t input_str, string_t condition = "") 
```
Эта функция принимает в качестве параметров исходную строку и условие на ее выполнение (требуется для поддержки if, while). Путем анализа строки с помощью регулярных выражений, реализованных с помощью класса std::regex, выделяются основные синтаксические конструкции и преобразовываются в элемент псевдокода.
```c++
	void console_reader::str_to_cmd(string_t input_str)
```
Эта функция отвечает за работу с блоками или отдельными командами(в этом случае используется функция simple_cmd_handle). Заполняет поле `code::code_type code`.
public – методы класса:
```c++
	code::code_type console_reader::read()
```
Эта функция позволяет считать одну строку или блок и преобразовать их в псевдокод.

Также имеются функции для задания или, наоборот, получения потока ввода-вывода.
Особого внимания заслуживает функция  `str_to_cmd`. В зависимости от строки, функция кладет в стек элемент под кодовым словом. По нему происходит распознание, относится ли элемент к обычным блоками или к циклу `for`. Весь псевдокод записывается соответственно в верхний элемент стека по итератору. Если была встречена закрывающаяся скобка(для элемента for - конец строки), элемент стека сворачивается в предыдущий(весь код этого элемента записывается в предыдущий по его итератору). Когда стек становится пуст, в `code::code_type code` записывается список псевдокода последнего элемента.


## Графический интерфейс 

