

## Зависимости

| Зависимость           | Минимальная версия    | Назначение                                    |
|-----------------------|-----------------------|-----------------------------------------------|
| **GCC / Clang**       | GCC 10 / Clang 11     | Компиляция C++20 кода                         |
| **CMake**             | 3.12                  | Сборка проекта и зависимостей                 |
| **libfmt-dev**        | 8.1.1                 | Парсинг форматных строк                       |
| **graphviz**          | 2.43.0                | Графический дамп                              |
| **Boost**             | 1.84                  | Рассчёт распределений                         |



### Установка зависимомтей на Ubuntu
* libfmt
```zsh
sudo apt install libfmt-dev
```

* graphviz
```zsh
sudo apt install graphviz
```

* Boost
```zsh
wget https://archives.boost.io/release/1.84.0/source/boost_1_84_0.tar.gz
tar -xzf boost_1_84_0.tar.gz -C ~/
```