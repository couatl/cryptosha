# Cryptosha
---------------------------------------------------
### ~~Собирай~~ пиши схемы!
----------------------------------------------------



> [Введение](#Введение)

> [Актуальность проекта](#Актуальность-проекта)

> Немного о функциональных элементах (только для дайверов)

> Структура проекта как библиотеки

>> [Регулирующий файл](#Регулирующий-файл)

>> Базовый элемент

>> Унарные операции

>> Бинарные операции

>> Схема шифрования

>> Графическая схема

>> [Утилиты для линейного/дифференциального криптоанализа](#Утилиты-для-линейногодифференциального-криптоанализа)

>> Парсер команд

>> Интерпретатор

>> Язык программирования схем

>

> Структура приложения

> Способы использования Cryptosha в сторонних проектах

> Способы расширения проекта

>> Добавление нового функционального элемента

>> Изменение синтаксиса языка

>> Добавление команд

> Пример работы приложения 

> Вывод 




## Введение 
Cryptosha - проект, предназначенный для работы с блочными схемами шифрования, а именно сборка схемы, прогон значений через нее и криптоанализ этой схемы. 
Ключевой момент проекта заключается в способе выполнения всех этих операций - они осуществляются с помощью кода. Теперь пользователь может построить схему, 
написав программный код, запустить ее всего одной строкой. Не собирайте схемы - пишите их. 

## Актуальность проекта 
Есть огромное количество подобных проектов с подобным функционалом, но ни один из них не закроет нам семестр по АЯ.


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
```с++

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

### Базовый элемент

```
c++

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

### Утилиты для линейного/дифференциального криптоанализа
В проекте присутствует класс `cryptosha::analysis`, предоставляющий возможность пользователю проводить криптоанализ над шифром. На данный момент в нем несколько методов: прогон множества бинарных наборов через элемент схемы, слой или всю схему, а также нахождение наиболее вероятного дифференциала наборов при заданном дифференциале входных наборов после прогона через элемент.

Методы прогона похожи по названию и сигнатуре: 
```c++
	bitset_map & run_element(xElement_ptr obj, const bitset_pool & input);
```

Она принимает в параметрах указатель на элемент схемы и множество наборов, которые необходимо прогнать.
```с++
	bitset_map run_scheme(xScheme_ptr scheme, const bitset_pool & input);
```

Аналогично с run_element, только передается указатель на схему, а не элемент.
```c++
	scheme::layer_bitsets_type run_layer(xScheme::layer_type layer,const bitset_pool & input);
```


Этот метод прогоняет слой схемы и возвращает объект типа layer_bitsets_type, который определен как std::map<full_name_t, bitset_t>, где full_name_t – это тип имени элемента, а bitset_t – тип битсета.
А метод для нахождения наиболее вероятного набора имеет такую сигнатуру:
string_t gretest_potentional(xElement_ptr obj, const string_t & diff, const bitset_pool & input);
Она принимает указатель на элемент схемы, дифференциал входных наборов и само множество наборов, из которых и берутся значения для прогона.
Данные методы существенно упростят проведение криптоанализа, в особенности на больших схемах.

