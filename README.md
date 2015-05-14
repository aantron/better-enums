# Better Enums

Generator-free reflective C++11 enum library with clean syntax. For example:

    ENUM(Channel, int, Red = 1, Green, Blue);

defines a type `Channel`. You can then do natural things like:

    Channel channel = Channel::Green;

    channel.to_string();            // Results in the string "Green"
    channel.to_integral();          // Results in the integer 2

    Channel::_from_string("Red");   // Results in Channel::Red
    Channel::_from_int(3)           // Results in Channel::Blue

    for (Channel channel : Channel::_values) {
        // Iterate over all channels
    }

...and more. See the
[examples](https://github.com/aantron/better-enums/tree/master/example) for a
tutorial.

## Installation

Simply add `enum.h` and `enum_preprocessor_map.h` to your project. The current
version can be found at
[https://github.com/aantron/better-enums/releases](https://github.com/aantron/better-enums/releases).

`enum_preprocessor_map.h` can handle enums with up to 256 constants. If you have
more, re-generate it by running something like:

    ./pp_map_gen.py enum_preprocessor_map.h 512

This only needs to be done once when the constant limit is exceeded. You don't
need to do this on every build. I hope to remove the need for this completely in
a future version.

## Features

- Generated at compile time by `constexpr` functions and the preprocessor.
  `pp_map_gen.py` is only needed if you have an enum with more than 256
  constants.
- Safe conversions between enums and integers and strings.
  [1-basic.cc](https://github.com/aantron/better-enums/blob/master/example/1-basic.cc)
- Iterable collections of constants and names.
  [2-iterate.cc](https://github.com/aantron/better-enums/blob/master/example/2-iterate.cc)
- Range information, such as the number of constants defined and the maximum
  constant.
  [2-iterate.cc](https://github.com/aantron/better-enums/blob/master/example/2-iterate.cc)
- Switch case checking.
  [3-switch.cc](https://github.com/aantron/better-enums/blob/master/example/3-switch.cc)
- Almost all operations are `constexpr` and can be used at compile time in your
  own `constexpr` code.
  [4-constexpr.cc](https://github.com/aantron/better-enums/blob/master/example/4-constexpr.cc)
- Constant values can be set (`Red = 1`) and aliased (`Favorite = Green`), just
  like with built-in enums.
- Generating a large number of enums is faster than including a typical standard
  header like `iostream` – performance test included.
- Explicit choice of underlying representation type.
- Header-only.
- No dependencies besides the standard library.
- Tested on gcc 4.9 and clang 3.6.

The library compiles only with gcc and clang due to use of weak symbols and due
to lagging C++11 support in msvc. It should ultimately be portable to msvc,
since msvc has its own version of weak symbols. Everything else in the library
is standard C++.

## Contact

Don't hesitate to contact me about features (or bugs!):
<a href="mailto:antonbachin@yahoo.com">antonbachin@yahoo.com</a>

## Explanation

The `ENUM` macro specializes a template based around a regular `enum`
declaration, though it is more similar to `enum class` in the degree of type
safety. The following are spiritually equivalent:

    ENUM(Channel, int, Red = 1, Green, Blue);
    enum class Channel : int {Red = 1, Green, Blue};

    ENUM(Depth, char, Indexed8Bit, HighColor, TrueColor);
    enum class Depth : char {Indexed8Bit, HighColor, TrueColor};

See the full [documentation](http://aantron.github.io/better-enums).

## Development plan

There are several areas that still need improvement.

- I will try to eliminate the need for `pp_map_gen.py`. The library will then
  consist of one file, `enum.h`.
- `to_string` can be made `constexpr`, like most of the rest of the code.
- Iterators over defined constants should be made random-access. This would
  allow `constexpr` functions to use them by adding 1 – the only way to advance
  them now is by mutating increment.
- Some enum types might have a sensible choice for a default constructor. The
  library should allow it to be customized.
- All safety checks are currently done by linear scans. This may be a
  performance problem for enum types with many constants.
- Better diagnostics for empty enums or too many constants.
- Conversions from integers and strings that don't throw exceptions, but
  indicate failure by some other means.

## License

Better Enums is released under the BSD 2-clause license. See
[LICENSE](https://github.com/aantron/better-enums/blob/master/LICENSE).

## History

The library was originally developed by the author in the winter of 2012-2013 at
Hudson River Trading, as a replacement for an older generator called
`BETTER_ENUM`.
