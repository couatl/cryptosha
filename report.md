# Cryptosha
---------------------------------------------------
### - Морти, смотри, схемы теперь можно писать!
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

>> [Бинарные операции](https://github.com/Alex-Kuz/cryptosha/blob/master/report.md#Бинарные-операции)

>> [Схема шифрования](#Схема-шифрования)

>> Графическая схема

>> [Утилиты для линейного/дифференциального криптоанализа](#Утилиты-для-линейногодифференциального-криптоанализа)

>> [Синтаксический анализатор](#Синтаксический-анализатор)

>> [Интерпретатор](#Принцип-работы-интерпретатора)

>> [Язык программирования схем](#Язык-программирования-схем)

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
Проект Cryptosha сделан на языке программирования C++. Основным конкурентом этого языка являлся Python, так как он поддерживает динамическую типизацию, что очень важно в нашем проекте. Выбор был сделан в пользу С++ по нескольким причинам:   
1. Язык С++ имеет ряд механизмов ЯП, которые позволяют оптимизировать программу и дают более глубокий уровень микроконтроля, чем в Python (прямая передача и move-семантика).  
2. Существует ряд библиотек `boost`, использование которых сильно уменьшило объем кода и позволило сократить время на разработку аналогичных классов.  
3. Существует библиотека [cpp-expression-parcer](https://github.com/cparse/cparse), с помощью которой был разработана вычисляющая часть интерпретатора.  
4. Проблемы с динамической типизацией отчасти удалось решить используя `boost::any`.

Таким образом, мы остановились на языке С++, как на языке разработки.

Графический пользовательский интерфейс (далее GUI) проекта сделан c использованием фреймворка Qt. Этот выбор был сделан по причине удобства и широкого функционала данной среды.

Также рассматривалась система библиотек `wxWidgets`. Однако ее было решено не использовать, так как для нее не предусмотрено графического дизайнера. Графический дизайнер позволяет существенно сократить написание программы путем уменьшения написанного вручную кода. Возникло большое количество проблем, связанных с переносом проекта в среду разработки Qt, которые были успешно решены в сжатые сроки.


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
- сдвиг влево/вправо
- подстановка (s-box)
- перестановка (p-block)

Все элементы унаследованы от базового класса для унарных элементов:
```c++
	class elements::unary : public elements::basic_element
	{
	public:
		explicit unary(iosize_t::type vector_size) : basic_element(vector_size, vector_size) {};
										//vector_size - размер входной последовательности
		virtual ~unary() = default;
	};
```
Инвертор:
```c++
	invertor(size_type vector_size) : unary(vector_size){};
```
Буфер:
```c++
	buffer(size_type vector_size) : unary(vector_size) {};
```
Сдвиг влево/вправо:
```c++
	explicit shift_left(size_type vector_size,size_type shift_size) 
		: unary(vector_size), m_shift_size(shift_size) {};
	//shift_size - размер сдвига
	
	explicit shift_right(size_type vector_size, size_type shift_size) 
		: unary(vector_size), m_shift_size(shift_size) {};
```
S-box:
```c++
	explicit simple_sbox(const vector_t& sbox_vector) 
		: unary(log2(sbox_vector.size())), vector(sbox_vector) {}
			//sbox - вектор подстановок
```
P-block:
```c++
	explicit permutation_block(const vector_t& pblock_vector) 
		: unary(pblock_vector.size()), vector(pblock_vector) {}
			//pbox - вектор перестановок
```

У каждого из данных классов переопределен метод `run()`, который и описывает работу элемента.

### Бинарные операции

В проекте предоставляется доступ к следующим бинарным элементам:
- конъюнкция
- дизъюнкция
- сумма по модулю 2 
- стрелка Пирса (nor)
- штрих Шеффера (nand)
- эквивалентность
- числовая сумма

Все элементы унаследованы от базового абстрактного класса:
```c++
	template<class F>
class elements::binary : public elements::basic_element
{
	 F baseFunction;
public:
	explicit binary(size_type vector_size) : basic_element(vector_size * 2, vector_size) {} ;
								//vector_size - размер выходной последовательности
	virtual ~binary() = default;
	bitset_t run() override;	// метод, выполняющий преобразование последовательности входных битов


};
```


У каждого из данных классов переопределен метод `run()`, который и описывает работу элемента.

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

Функция добавления элемента в схему, принимающая фабричный пакет пакет:
```c++
	id_t add_element(const factory_package& element_package);
```
Фабричный пакет - это специальная структура данных, созданная для предотвращения конфликтов типов входных параметров конструкторов классов, экземпляры которых призводится фабрикой. Подробнее в регулирующем файле `settings.h`. 

Методы установления значений ключа и входного текста:
```c++
	cipher_scheme& set_key(const string_t& key_vector);
	cipher_scheme& set_key(const int_t& key_value);
	cipher_scheme& set_text(const string_t& text_vector);
	cipher_scheme& set_text(const int_t& text_value);
```



####Структура схемы
Во время разработки схемы рассматривались несколько концепций ее логического устройства. В итоге была принята концепция несвязных структурных данных (элементы, провода и т.д.), позволяющих собрать в каком-то виде виртуальную схему. Однако для этого схему нужно обязательно собрать, вызвав метод `assembly()`.
```c++
	cipher_scheme& assembly();
```
Пользователь обращается к элементам по имени. Однако в схеме элементы регистрируются под уникальным идентификатором (`id_t id`). Это не позволяет пользователю создать за все время работы с проектом более 2^64-1 элементов, что, возможно, может его огорчить. Такая замена ключа позволяет переименовывать элементы, не меняя основаной структуры схемы.
Собранная схема представляет собой список множеств идентификаторов, то есть `list<set<id_t>>`. Этот список строится по алгоритму, основаном на алгоритме Демукрона для вычисления порядковой функции сети.
Физически это выглядит как на следующем изображении - слева изображена схема, которую запрограммировал пользователь, а справа виртуальное представление этой же схемы:
![scheme_system](https://pp.vk.me/c837134/v837134121/fb03/Zrvidzljr6E.jpg)

При этом алгоритм сборки схемы запрещает создание триггерных цепей.
![scheme_trigger](https://pp.vk.me/c626319/v626319121/3fbdc/Xx-lRbHrSmQ.jpg)


В дальнейшем это может быть исправлено, если пользователь укажет поведение цепи в таком случае.

Соединения пинов представлено в виде отображения множества пар идентификаторов (источника и приемника) в множество пар номеров пинов (у источника номер выходного пина, у приемника - входного). То есть это поле типа `map<id_pair_t, pin_pair_t>`.
Пример представлен на следующей диаграмме. Следует учесть, что нумерация пинов идет с нуля, нулевым считается самый левый бит.
![scheme_wires](https://pp.vk.me/c638520/v638520547/18ca3/1Q6fpztsZSE.jpg)

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

### Принцип работы интерпретатора

```c++
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

class interpretator
{
  using reader_ptr = std::unique_ptr<console_reader>;        
  using operation_ptr_t = std::unique_ptr<operations::base>;
  using operations_t = std::map<code::keyword_t, operation_ptr_t>;

private:
  handler_t      handler;
  reader_ptr     reader;
  operations_t   operations;
};
```

Все необходимые для работы со схемой данные содержатся в структуре типа `handler_t`. В этой структуре содержатся:
- code - список элементарных команд, который предоставляет синтаксический анализатор.
- cursor - указатель на текущую команду
- schemes - отображение имен (строк) в указательи на схемы. 
    Пока что поддерживается раота только с одной схемой, поэтому полльзователь может работать только с одной схемой.
- variables - контейнер для хранения числовых переменных, не относящихся к схеме. Этот контейнер предоставляется библиотекой сpp-excpression-parser, о которой было сказано выше.

Структура интерпретатора : 
- handler - экземпляр вышеописанной структуры
- reader - указатель на синтаксический анализатор
- operations - отображение из множества ключевых слов (`cry::code::keyword_t`) во множество функторов, которые обрабатывают свою команду из ранее указанного множества (на самом деле по определению это не функторы, так как вместо оператора `operator()` в этих классах присутствует переопределяемый метод `doit()`).

Интерпретатор читает цепочку псевдокода (мы, разработчики, не называем это кодом, чтобы не допустить путаницу), и выполняет ее, вызывая для каждой элементарной команды нужный функтор.
## Язык программирования схем  
В проекте используется разработанный нами язык программирования.
Ниже представлены основные команды:

1. **Добавление элемента**
  ```
		add(type, @name_of_element, num_of_in_pins, num_of_out_pins, mod<svector or pvector>, <x, y>, <width, height>)
  ```

  Где 
  - `type` - ключевое слово (тип элемента пример: xor)
  - `@name_of_element` - имя элемента (может задаваться выражением, например: XOR[5], XOR[i])
  - `num_of_in_pins` - число, num_of_out_pins - число
  - `mod<svector or pvector>` (только для sbox-ов и p-block-ов). mod - символ модификатора системы счисления (b - 2, d - 10, h - 16)
  - `<x, y>` - координаты левого верхнего угла(может задаваться выражением)
  - `<width, height>` - размеры элемента (может задаваться выражением)
2. **Соединение пинов элементов**
  ```
  	connect(@name_of_sender, <out_pins_vector>, @name_of_receiver, <in_pins_vector>)
  ```
  Где
  - `@name_of_sender` - имя элемента
  - `<out_pins_vector>` - вектор выходных пинов (может задаваться выражением)
  - `@name_of_receiver` - имя присоединяемого элемента
  - `<in_pins_vector>` - вектор входных пинов (может задаваться выражением)

3. **Оператор `=`**
  
  ```
  	a = b
  ```
Далее - команды для криптоанализа:  
4. **Прогон множества бинарных наборов через элемент**
 
 ```
	run_element(@name, <bitset_pool>)
  ```
  Где
  - `@name` - имя элемента
  - `<bitset_pool>` - множество бинарных наборов (поддерживаются маски)
5. **Прогон множества бинарных наборов через схему**
  
  ```
	run_scheme(<bitset_pool>)
  ```
  Где
  - `<bitset_pool>` - набор векторов (поддерживаются маски) - прогон нескольких векторов через схему  
6. **Сборка схемы**
 
 ```
	assembly
  ```
7. **Запуск схемы**
  
  ```
	run
  ```

Все параметры в <> указываются через запятую, кроме svector и pvector(они - через пробелы) 

## Графический интерфейс 
Структура приложения проста - в главном окне пользователь видит поле ввода команд и поле вывода. При нажатии кнопки `run code` происходит запуск кода, который написал пользователь. **Код выполнится над уже существующей схемой, а значит будет попытка создать элемент еще раз.** Для того, чтобы обновить схему и отчистить ее, пользователь должен нажать кнопку `new scheme`. В окно вывода выводятся сообщения команд, сообщения сборки и ошибок. При нажатии кнопки `draw` открывается новое окно, в котором и отрисовывается схема. Там же происходит управление над существующей схемой. 


![image1](https://pp.vk.me/c836528/v836528012/18fae/AcLBixALCCE.jpg)  


Основным элементом графической схемы является элемент, описанный в классе **`class Graph_Element : public QObject, public QGraphicsItem`** 

Элемент представляется в виде прямоугольника с текстом, который обозначает его имя и массивом входных и выходных пинов. Каждый пин представляет собой еще один графический элемент и описывается в классе **`class graph_pin : public QgraphicsItem`**.
В конструкторе каждого элемента указывается количество входных и выходных пинов, их относительные координаты вычисляются автоматически. 

В Графическом интерфейсе представлены два вида отрисовки схем : *структурированная* и *неструктурированная*. Для запуска структурированной отрисовки нужно нажать на кнопку `Draw with AI`, для неструктурированной - `Draw`, после чего происходит отрисовка схемы в окне отрисовки.


![image2](https://pp.vk.me/c836528/v836528012/18fa6/A03M5X4gzxM.jpg) 


В случае *структурированной* отрисовки создается список графических слоев, которые, в свою очередь содержат элементы.
Плюсы данной отрисовки в том, что схема в доступном для восприятия виде – элементы расположены на одном уровне и соблюдается структура физических слоев схемы. Соответственно, при данной отрисовке элементы нельзя передвигать по окну отрисовки. 

В случае *неструктурированной* отрисовки создается массив элементов. Они не привязаны к слоям.
Элементы рисуются в координатах, указанных пользователем. Элементы свободно перемещаются вместе со всеми соединениями.
Плюсы данной отрисовки в том, что пользователь сам ставит элементы в тех точках, в которых он хочет. При этом возможна потеря читабельности схемы и ее логичности. 

Таким образом GUI предоставляет возможность написания кода и просмотра получившейся схемы в двух режимах.


 
