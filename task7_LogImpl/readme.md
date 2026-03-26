# Задача 7

## Зависимости

| Зависимость            | Минимальная версия    | Назначение                                    |
|------------------------|-----------------------|-----------------------------------------------|
| **GCC / Clang**        | GCC 10 / Clang 11     | Компиляция C++20 кода                         |
| **CMake**              | 3.12                  | Сборка проекта и зависимостей                 |
| **libfmt-dev**         | 8.1.1                 | Парсинг форматных строк                       |
| **graphviz**           | 2.43.0                | Графический дамп                              |
| **MPFR** (on debug)    | 4.1.0-3               | Рассчёт эталонных значений                    |
| **Gnuplot** (on debug) | 5.4                   | Построение графиков                           | 

### Установка зависимомтей на Ubuntu
* $\texttt{libfmt}$
```zsh
sudo apt install libfmt-dev
```

* $\texttt{graphviz}$
```zsh
sudo apt install graphviz
```

* $\texttt{MPFR}$
```zsh
sudo apt install libmpfr-dev libgmp-dev
```

* $\texttt{Gnuplot}$
```zsh
sudo apt install gnuplot
```

