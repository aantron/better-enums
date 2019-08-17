# Better Enums &nbsp; [![version 0.11.2][version]][releases] [![Try online][wandbox-img]][wandbox] [![Travis status][travis-img]][travis] [![AppVeyor status][appveyor-img]][appveyor]

[version]:      https://img.shields.io/badge/version-0.11.2-blue.svg
[releases]:     https://github.com/aantron/better-enums/releases
[wandbox]:      http://melpon.org/wandbox/permlink/2QCi3cwQnplAToge
[wandbox-img]:  https://img.shields.io/badge/try%20it-online-blue.svg
[appveyor]:     https://ci.appveyor.com/project/aantron/better-enums/branch/master
[travis]:       https://travis-ci.org/aantron/better-enums/branches
[travis-img]:   https://img.shields.io/travis/aantron/better-enums/master.svg?label=travis
[appveyor-img]: https://img.shields.io/appveyor/ci/aantron/better-enums/master.svg?label=appveyor
[license-img]:  https://img.shields.io/badge/license-BSD-lightgrey.svg

Reflective compile-time enum library with clean syntax, in a single header
file, and without dependencies.

![Better Enums code overview][sample]

[sample]: https://raw.githubusercontent.com/aantron/better-enums/master/doc/image/sample.gif

**Note**: consider [**magic_enum**](https://github.com/Neargye/magic_enum) (if using GCC, requires at least GCC 9.0).

In C++11, *everything* can be used at compile time. You can convert your enums,
loop over them, [find their max][max],
[statically enforce conventions][enforce], and pass along the results as
template arguments or to `constexpr` functions. All the reflection is available
for your metaprogramming needs.

The interface is the same for C++98 &mdash; you just have to use most of it at
run time only. This library does provide scoped and sized enums, something not
built into C++98.

See the [project page][project] for full documentation.

[max]:      http://aantron.github.io/better-enums/demo/BitSets.html
[enforce]:  http://aantron.github.io/better-enums/demo/SpecialValues.html
[project]:  http://aantron.github.io/better-enums

<br/>

## Installation

Simply add `enum.h` to your project.

<br/>

## Additional features

- Uses only standard C++, though, for C++98, variadic macro support is required
  (major compilers have it).
- Supported and tested on [clang, gcc, and msvc][testing].
- Fast compilation. You have to declare a few dozen enums to slow down your
  compiler as much as [only including `iostream` does][performance].
- Use any initializers and sparse ranges, just like with a built-in enum.
- Control over size and alignment &mdash; you choose the representation type.
- Stream operators.
- Does not use the heap and can be compiled with exceptions disabled, for use in
  minimal freestanding environments.

[testing]:     http://aantron.github.io/better-enums/CompilerSupport.html
[performance]: http://aantron.github.io/better-enums/Performance.html

<br/>

## Limitations

1. The biggest limitation is that the `BETTER_ENUM` macro can't be used inside a
class. This seems [difficult to remove][nested]. There is a workaround with
`typedef` (or C++11 `using`):

    ```c++
    BETTER_ENUM(SomePrefix_Color, uint8_t, Red, Green, Blue)

    struct triplet {
        typedef SomePrefix_Color    Color;
        Color                       r, g, b;
    };

    triplet::Color  color;
    ```

    You can, however, use `BETTER_ENUM` inside a namespace.

2. The macro has a soft limit of 64 declared constants. You can extend it by
following [these instructions][extend]. Ultimately, the number of constants is
limited by your compiler's maximum macro argument count.

3. In some cases, it is necessary to prefix constants such as `Channel::Red` with a
`+` to explicitly promote them to type `Channel`. For example, if you are doing
a comparison:

    ```c++
    channel == +Channel::Red
    ```

4. On msvc, you may need to enable [warning C4062][C4062] to get `switch` case exhaustiveness checking.

[nested]: http://aantron.github.io/better-enums/DesignDecisionsFAQ.html#NoEnumInsideClass
[extend]: http://aantron.github.io/better-enums/ExtendingLimits.html
[C4062]: https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4062

<br/>

## Contact and development

Don't hesitate to contact me about features or bugs:
[antonbachin@yahoo.com][email], or open an issue on GitHub.

If you'd like to help develop Better Enums, see [`CONTRIBUTING`][contributing].
One area that could use fresh ideas is finding a compile-time data structure
that both compiles quickly and allows lookup in sub-linear time.

[email]:        mailto:antonbachin@yahoo.com
[contributing]: https://github.com/aantron/better-enums/blob/master/doc/CONTRIBUTING.md

<br/>

## History

The original version of the library was developed by the author in the winter of
2012-2013 at Hudson River Trading, as a replacement for an older generator
called `BETTER_ENUM`.
