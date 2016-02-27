## Compiler support

Better Enums aims to support all major compilers. It is known to work on:

  - clang 3.3 to 3.9
  - gcc 4.3 to 5.3
  - Visual C++ 2008 to 2015.

The library can be used with any compiler that supports either $cxx11, or $cxx98
with the `__VA_ARGS__` extension. This includes every version of gcc and clang I
have ever heard of, and Visual C++ down to 2005.

To ensure that nothing is broken, every release of Better Enums is
[tested]($repo/tree/master/test) in multiple configuratins on the compilers
listed above. Testing includes the code in the tutorials, the unit tests, and a
multiple translation unit linking test. The full list of tested compilers and
configurations is given at [the end of this page](#TestedConfigurations).

### Compile-time reflection configurations

Read this section if:

  - you want to use Better Enums reflection at compile time, and need to know
    exactly what features are supported on your compiler, or
  - Better Enums is choosing the wrong configuration automatically and you need
    to force a different choice.

All features of Better Enums are always available for run-time use. However, for
compile-time use, Better Enums has two main configurations: $cxx98 mode and
`constexpr` mode. Better Enums tries to detect which compiler is compiling it
and select the appropriate mode.

For performance reasons, `constexpr` mode is subdivided into a "fast"
`constexpr` mode and an
[opt-in](${prefix}OptInFeatures.html#CompileTimeNameTrimming) "full" (slow)
`constexpr` mode. The three modes can be ranked, with each next mode including
all the features of the preceding ones:

  - $cxx98
  - fast `constexpr`
  - full `constexpr`

Only `_size` is supported at compile time in $cxx98 mode. Fast `constexpr` mode
adds all other members besides `_to_string` and `_names`. Full `constexpr` mode
supports those at compile time as well.

---

The mode selection code works as follows:

  - First, as of the time of this writing, only clang and gcc support
    `constexpr`. So, if you are using any other compiler, Better Enums is in
    $cxx98 mode.
  - If you are using gcc 4.7 or higher or clang, Better Enums uses those
    compilers' predefined macros to detect whether `constexpr` support is
    enabled with compiler flags. If so, it is in one of the `constexpr` mode.
    Otherwise, it falls back to $cxx98 mode.
  - The default `constexpr` mode is fast `constexpr`. If you want to enable
    full `constexpr` mode for some or all of your enums, follow
    [these](${prefix}OptInFeatures.html#CompileTimeNameTrimming) instructions.

If Better Enums picks the wrong mode, you can force `constexpr` mode by defining
`BETTER_ENUMS_CONSTEXPR` before including `enum.h`, typically by passing an
option to your compiler, or you can force $cxx98 mode by defining
`BETTER_ENUMS_NO_CONSTEXPR`.

If you are using a compiler for which Better Enums makes the wrong choice,
please [let me know](${prefix}Contact.html). I will fix it and you won't have to
define these macros anymore.

### Tested configurations

~~~comment
vc2015 /EHsc
vc2015 /EHsc /DBETTER_ENUMS_STRICT_CONVERSION
vc2013 /EHsc
vc2013 /EHsc /DBETTER_ENUMS_STRICT_CONVERSION
vc2012 /EHsc
vc2010 /EHsc
vc2008 /EHsc
clang++39 -std=c++11
clang++39 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
clang++39 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
clang++39 -std=c++98
clang++38 -std=c++11
clang++38 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
clang++38 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
clang++38 -std=c++98
clang++37 -std=c++11
clang++37 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
clang++37 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
clang++37 -std=c++98
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
clang++33 -std=c++98
g++53 -std=c++11
g++53 -std=c++11 -DBETTER_ENUMS_STRICT_CONVERSION
g++53 -std=c++11 -DBETTER_ENUMS_CONSTEXPR_TO_STRING
g++53 -std=c++98
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
g++46 -std=c++98
g++45 -std=c++98
g++44 -std=c++98
g++43 -std=c++98
~~~

%% description =
Better Enums compiler support, compatibility, feature detection, and automated
testing.
