## Compiler support

Better Enums aims to support as many compilers as is reasonable. It has been
tested with clang++ and g++, and Visual C++ support is coming in the next few
days.

In principle, Better Enums can be used with any compiler that supports either

  - $cxx11
  - $cxx98 with the variadic macro (`__VA_ARGS__`) extension

This should make it compatible with Visual C++ 2005 and higher/

To ensure that nothing is broken, every release of Better Enums is tested
automatically with a large number of combinations of compiler and configuration.
The full list is given at the end of this page.

The tests include compiling and running unit tests, all the examples in the
demos and tutorials, and a multiple translation unit linking test.

### Tested configurations

~~~comment
clang++36 -std=c++11
clang++36 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
clang++36 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
clang++36 -std=c++98
clang++35 -std=c++11
clang++35 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
clang++35 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
clang++35 -std=c++98
clang++34 -std=c++11
clang++34 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
clang++34 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
clang++34 -std=c++98
clang++33 -std=c++11
clang++33 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
clang++33 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
clang++33 -std=c++98
g++51 -std=c++11
g++51 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
g++51 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
g++51 -std=c++98
g++49 -std=c++11
g++49 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
g++49 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
g++49 -std=c++98
g++48 -std=c++11
g++48 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
g++48 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
g++48 -std=c++98
g++47 -std=c++11
g++47 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
g++47 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
g++47 -std=c++98
g++46 -std=c++0x -DBETTER_ENUMS_NO_CONSTEXPR
g++46 -std=c++0x -DBETTER_ENUMS_NO_CONSTEXPR -DBETTER_ENUMS_STRICT_CONVERSION
g++46 -std=c++98
g++45 -std=c++0x -DBETTER_ENUMS_NO_CONSTEXPR
g++45 -std=c++0x -DBETTER_ENUMS_NO_CONSTEXPR -DBETTER_ENUMS_STRICT_CONVERSION
g++45 -std=c++98
g++44 -std=c++0x -DBETTER_ENUMS_NO_CONSTEXPR
g++44 -std=c++0x -DBETTER_ENUMS_NO_CONSTEXPR -DBETTER_ENUMS_STRICT_CONVERSION
g++44 -std=c++98
g++43 -std=c++0x -DBETTER_ENUMS_NO_CONSTEXPR
g++43 -std=c++98
~~~
