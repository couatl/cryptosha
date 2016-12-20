

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
