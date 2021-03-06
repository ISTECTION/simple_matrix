# МАТРИЧНАЯ БИБЛИОТЕКА

Библиотека С++ для работы с матрицами

## Возможности библиотеки
Данная библиотека включает в себя представленные функции

- Детерминант квадратной матрицы любого размера

- Адъюгированние и транспонирование матрицы

- Решение СЛАУ методом Крамера

- Нахождение обратной матрицы

- Матрица миноров

- Подматрицы

- След

## Использование библиотеки
Все библиотечные функции, классы и константы определены в пространстве имен `simple`, оно может быть импортировано через

```cpp
using namespace simple;
```

## Установка вспомогательных средств создания документации

Для генерации документации в данном проекте используется утилита под названием - **Doxygen** - которую можно скачать с [официального сайта](https://doxygen.nl/download.html) или с репозитория [GitHub](https://github.com/doxygen/doxygen) и скомпилировать самым удобным для Вас способом.

> **Doxygen** — это кроссплатформенная система документирования исходных текстов, которая поддерживает C++, Си, Objective-C, Python, Java, IDL, PHP, C#, Фортран, VHDL и, частично, D.

Во время документирования, Doxygen, генерирует граф связей класса, делая это не лучшим образом, создавая изображения в формате `png`, которое плохо маштабируется и ужасно выглядит на больших экранах.

Для улучшения качества изображений, c [официального сайта **Graphviz**](https://graphviz.org/) можно установить пакет утилит для автоматической визуализации графов, в который входит инструмент под названием - **DOT**, который в свою очередь использует **Doxygen**.

> **Graphviz** — это программное обеспечение для визуализации графиков с открытым исходным кодом. Визуализация графов - это способ представления структурной информации в виде диаграмм абстрактных графов и сетей.

После установки данного пакета, требуется добавить путь к бинарным файлам в `Переменные среды` вашего ПК, для этого:

- Нажмите сочетание клавиш `Win` + `S`
- Наберите в поисковой строке `Изменение системных переменных среды`
- Нажмите на `Переменные среды`
- Выберите переменную с навзание `Path` и нажмите `Изменить`
- После чего допишите в конец абсолютный путь подкатолога `bin` только что установленного пакета

Теперь **Doxygen** будет пользоваться утилитой `DOT` и генерировать изображения в формате `svg`.

## Создание вектора
Чтобы создать целочисленный вектор, заполненный нулями, рамером `_count`
```cpp
vector<int> _vec(_count);
```


## Создание матрицы
Мы можем создать матрицу размером `_rows` на `_cols`, заполненную нулями

```cpp
matrix<int> _mtx(_rows, _cols);
```

## Вывод матрицы на консоль

Объект матрицы может быть просто выведен в любой выходной поток

```cpp
matrix<int> _mtx = {
    { 5, 4, 3 },
    { 1, 2, 3 },
    { 6, 4, 5 } };
std::cout << _mtx << std::endl;
```
```
┌─         ─┐
│  5  4  3  │
│  1  2  3  │
│  6  4  5  │
└─         ─┘
```

## Сложение и вычитание
Мы можем сложить или вычесть 2 матрицы строго одинакового размера
```cpp
matrix<int> A = {
    { 5, 4, 3 },
    { 1, 2, 3 },
    { 6, 4, 5 } };
matrix<int> B = {
    { 3, 8, 8 },
    { 1, 7, 3 },
    { 4, 3, 6 } };
```
Любым из представленных способов:
```cpp
matrix<int> C = A + B;
```
```cpp
A += B;
```
Аналогично `matrix<int> C = A - B` или `A -= B`

## Скалярное произведение
Мы можем умножить все элементы матрицы на одну и ту же константу

```cpp
matrix<int> A = {
    { 5, 4, 3 },
    { 1, 2, 3 },
    { 6, 4, 5 } };
double c = 5;
```
Одним из нижеперечисленных способов:
```cpp
matrix<int> B = A * c;
```
```cpp
matrix<int> B = c * A;
```
```cpp
A *= c;
```

## Матричное умножение
Если количество столбцов матрицы A равно количеству строк матрицы B, то мы можем произвести вычисление `A * B` ( (`R`, `E`) * (`E`, `C`) = (`R`, `C`) )

Для функции `assert` нужно подключить следующую библиотеку
```cpp
#include <cassert>
```

```cpp
matrix<int> A, B;

assert(A.size_collumns() == B.size_rows()); ///< LINE 18
```
```cpp
matrix<int> C = A * B;                      ///< LINE 20
```
```cpp
A *= B;                                     ///< LINE 20
```

Если перемножение невозможно, то на 18 строке возникнет исключение и программа прекратит своё выполнение, при этом оповестив пользователя следующим сообщением

```
File: main.cpp, Line 18

Expression: A.size_collumns() == B.size_rows()
```

## Получение и установка элемента

Доступ к отдельным элементам можно получить при помощи `setter/getter` функций. Предположим, что у нас есть следующая матрица

```cpp
matrix<int> _mtx = {
    { 5, 4, 3 },
    { 1, 2, 3 },
    { 6, 4, 5 } };
```

Мы можем получить любой элемент матрицы, просто указав его позицию в квадратных скобках

```cpp
int _elem = _mtx[0][0];
```
> { **5**, 4, 3 }
> {   1,   2, 3 }
> {   6,   4, 5 }

```cpp
int _elem = _mtx[0][2];
```
> { 5, 4, **3** }
> { 1, 2,   3   }
> { 6, 4,   5   }

```cpp
int _elem = _mtx[2][2];
```
> { 5, 4,   3   }
> { 1, 2,   3   }
> { 6, 4, **5** }

Также мы можем установить любое значение в любую из позиций матрицы

```cpp
_mtx[0][0] = 9;
```
> { **9**, 4, 3 }
> {   1,   2, 3 }
> {   6,   4, 5 }

## Получение и установка строк и столбцов

Мы можем получить и установить отдельные строки и столбцы аналогично элементам.

Предположим, что у нас есть следующая матрица:

```cpp
matrix<int> _mtx = {
    { 1, 2, 3, 4 },
    { 2, 2, 2, 4 },
    { 4, 5, 6, 4 },
    { 7, 8, 9, 4 } };
```
```
┌─            ─┐
│  4  2  3  4  │
│  4  2  2  4  │
│  4  5  6  4  │
│  4  8  9  4  │
└─            ─┘
```

Тогда мы можем получить любую строку этой матрицы, просто обратившись к функции `get_row` и передав в неё индекс нужной строки

```cpp
vector<int> _vec = _mtx.get_row(1);
```
```
┌─            ─┐
│  2  2  2  4  │
└─            ─┘
```
Если мы хотим получить `j-й` столбец матрицы, то следует обратиться к функции `get_collumn`

```cpp
vector<int> _vec = _mtx.get_collumn(3);
```
```
┌─            ─┐
│  4  4  4  4  │
└─            ─┘
```

Аналогичным образом можно установить строку или столбец, обратившись к функциям `set_row/set_collumn`, и в качестве второго аргумента передать вектор

В качестве примера установим, ранее полученный вектор, но только на другую позицию
```cpp
_mtx.set_collumn(0, _vec);
```
Тогда начальная матрица А приобретёт следующий вид
```
┌─            ─┐
│  4  2  3  4  │
│  4  2  2  4  │
│  4  5  6  4  │
│  4  8  9  4  │
└─            ─┘
```

## Детерминант

> В линейной алгебре определи́тель (или детермина́нт) — это скалярная величина, которая обозначает ориентированное «растяжение» или «сжатие» многомерного евклидового пространства после преобразования матрицей

> Детерминант имеет смысл только для квадратных матриц

Мы можем просто и эффективно вычислить определитель матрицы обратившись к функции `determinant`. Так же мы можем проверить является ли матрица квадратной при помощи функции `is_square`, которая возратит значение `TRUE` в случае успеха

```cpp
matrix<int> _mtx;

assert(_mtx.is_square());       ///< LINE 3
auto _det = _mtx.determinant();
```

Если матрица окажется не квадратной, то пользователя оповестят следующим предупреждением

```
File: main.cpp, Line 3

Expression: _mtx.is_square()
```
Подробнее о вычислении детерминанта можно узнать [здесь](http://www.mathprofi.ru/kak_vychislit_opredelitel.html)


## Транспонирование

> Транспонирование — в линейной алгебре это операция над матрицами в результате которой матрица поворачивается относительно своей главной диагонали

Мы можем транспонировать матрицу обратившись к функции `transpose`

```cpp
matrix<int> _mtx = {
    { 5, 4, 3 },
    { 1, 2, 6 } };

matrix<int> _mtxT = _mtx.transpose()

std::cout << _mtx  << std::endl;
std::cout << _mtxT << std::endl;
```

```
┌─         ─┐
│  5  4  3  │
│  1  2  6  │
└─         ─┘
┌─      ─┐
│  5  1  │
│  4  2  │
│  3  6  │
└─      ─┘
```

## Обратная матрица

> Обратная матрица — такая матрица, при умножении на которую исходная матрица A даёт в результате единичную матрицу E

Мы просто можем обратиться к функции `invert`, чтобы получить обратную матрицу

```cpp
matrix<int> _mtx = {
    { 1, 9, 2 },
    { 8, 3, 7 },
    { 4, 6, 5 } };

std::cout << _mtx          << std::endl;
std::cout << _mtx.invert() << std::endl;

matrix<int> _mtxE = _mtx * _mtx.invert();

std::cout << _mtxE << std::endl;
```

```
┌─         ─┐
│  1  9  2  │
│  8  3  7  │
│  4  6  5  │
└─         ─┘
┌─                                 ─┐
│   0.428571   0.52381   -0.904762  │
│   0.190476   0.047619  -0.142857  │
│  -0.571429   -0.47619   1.09524   │
└─                                 ─┘
┌─         ─┐
│  1  0  0  │
│  0  1  0  │
│  0  0  1  │
└─         ─┘
```

Имейте в виду, что матрицу можно инвертировать только в том случае, если она квадратная и если определитель матрицы не равен нулю. Если матрица не квадратная, будет выдано исключение типа `exception::TYPE::NOT_SQUARE`. Если определитель равен нулю, будет выдано исключение типа `exception::TYPE::NOT_INVERTIBLE`

Подробнее о вычислении обратной матрицы можно узнать [здесь](http://www.mathprofi.ru/kak_naiti_obratnuyu_matricu.html)


## Адъюгированная матрица

> Адъюгированная матрица из А является транспонированным из кофактора матрицы C из A

Такую матрицу мы можем получить вызвав функцию `adj`

```cpp
matrix<int> _mtx;

matrix<int> _mtx_adj = _mtx.adj();
```
Подробнее о вычислении адъюгированной матрицы можно узнать [здесь](https://ru.abcdef.wiki/wiki/Adjugate_matrix)


## Подматрицы

> Подматрица, также известна как матрица удаления, представляет собой матрицу, которая создается путем удаления строк и столбцов исходной матрицы

> Если матрица была размером `M * N`, то её подматрица будет размерами `(M - 1) * (N - 1)`

Предположим, что у нас есть следующая матрица:

```
    ┌─            ─┐
0 > │  3  2  5  4  │
1 > │  2  3  8  7  │
2 > │  4  2  6  1  │
3 > │  5  1  9  6  │
    └─            ─┘
       ^  ^  ^  ^
       0  1  2  3
```

Тогда следующий вызов -
```cpp
std::cout << A.submatrix(1, 2) << std::endl;
```
Повлекет за собой вывод данной подматрицы:

```
┌─         ─┐
│  3  2  4  │
│  4  2  1  │
│  5  1  6  │
└─         ─┘
```

## Кофакторная матрица

> Матрица, образованная всеми кофакторами квадратной матрицы A, называется кофакторной матрицей (также называемой матрицей кофакторов)

Предположим, что у нас есть следующая матрица:

```
┌─            ─┐
│   1   4   7  │
│   3   0   5  │
│  -1   9  11  │
└─            ─┘
```

Мы можем найти любой кофактор матрицы, просто вызвав функцию `cofactor` и передав в неё позицию элемента

```cpp
std::cout << _mtx.cofactor(1, 2) << std::endl;
```
```
-13
```

Но так же мы можем найти всю матрицу кофакторов, просто вызвав функцию `cofactor_matrix`

```cpp
std::cout << _mtx.cofactor_matrix() << std::endl;
```
```
┌─               ─┐
│  -45  -38   27  │
│   19   18  -13  │
│   20   16  -12  │
└─               ─┘
```

Подробнее о вычислении кофактора и кофакторной матрицы можно узнать [здесь](https://forma-slova.com/ru/articles/3978-calculating-the-cofactor-the-cofactor-in-the-calculation-of)

## Полезные ссылки

- [Макросы препроцессора](https://en.cppreference.com/w/User:D41D8CD98F/feature_testing_macros)


<!-- ___
<b id="f1">1:</b> ПЧ — Правая Часть [↩](#a1) -->