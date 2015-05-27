# Better Enums

Reflective compile-time C++ enum library with clean syntax. For example:

    ENUM(Channel, int, Red = 1, Green, Blue)

defines a type `Channel`. You can then do natural things such as:

```cpp
Channel channel = Channel::Green;

channel._to_string();           // Results in the string "Green"
channel._to_integral();         // Results in the int 2

Channel::_from_string("Red");   // Results in Channel::Red
Channel::_from_integral(3);     // Results in Channel::Blue

constexpr auto channel = Channel::_from_integral(3);
                                // Do it at compile time (C++11 only)

for (Channel channel : Channel::_values()) {
    // Iterate over all channels
}
```

...and more. See the [project page](http://aantron.github.io/better-enums).

## Installation

Simply add `enum.h` to your project.

## Features

- Requires no external utility.
- Safe conversions to/from integers and strings.
- Iteration over declared values.
- Switch case checking.
- All operations are `constexpr` and can be used at compile time in your own
  `constexpr` code. See demos on the
  [project page](http://aantron.github.io/better-enums) for how to define
  default values, for example.
- Constant values can be initialized with expressions (`Red = 1`) and aliased
  (`Favorite = Green`), just like with built-in enums.
- Generating a large number of enums is about as fast as including a typical
  standard header like `iostream` – performance test included.
- Explicit choice of underlying representation type.
- Header-only.
- No dependencies besides the standard library.
- Tested on gcc 4.3+ and clang 3.3+.

Visual C++ support coming in the next few days. I am currently porting.

## Contact

Don't hesitate to contact me about features (or bugs!):
<a href="mailto:antonbachin@yahoo.com">antonbachin@yahoo.com</a>

## License

Better Enums is released under the BSD 2-clause license. See
[LICENSE](https://github.com/aantron/better-enums/blob/master/LICENSE).

## History

The library was originally developed by the author in the winter of 2012-2013 at
Hudson River Trading, as a replacement for an older generator called
`BETTER_ENUM`.
