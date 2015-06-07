# Better Enums

Reflective compile-time C++ enum library with clean syntax, in a single header
file. For example:

    #include <enum.h>
    ENUM(Channel, uint8_t, Red = 1, Green, Blue)

defines a type `Channel`. You can then do natural things such as:

```cpp
Channel channel = Channel::Green;

channel._to_string();           // Results in the string "Green"
Channel::_from_string("Red");   // Results in Channel::Red

Channel::_from_integral(3);     // Checked cast, Channel::Blue

Channel::_size;                 // Number of channels (3)
Channel::_values()[0];          // Get the first channel

for (Channel channel : Channel::_values()) {
    process(channel);           // Iterate over all channels
}

// Natural switch, compiler checks the cases
switch (channel) {
    case Channel::Red:   break;
    case Channel::Green: break;
    case Channel::Blue:  break;
}
```

...and more.

In C++11, *everything* is available at compile time. You can convert your enums,
loop over them, [find their max][max],
[statically enforce conventions][enforce], and pass along the results as
template arguments or to `constexpr` functions. All the reflection is available
for your metaprogramming needs.

The interface is the same for C++98 &mdash; you just have to use most of it at
run time only. This library does provide scoped and sized enums, something not
built into C++98.

See the [project page][project] for full documentation and [here][tutorial] for
a simple working program.

[max]:      http://aantron.github.io/better-enums/demo/BitSets.html
[enforce]:  http://aantron.github.io/better-enums/demo/SpecialValues.html
[project]:  http://aantron.github.io/better-enums
[tutorial]: http://aantron.github.io/better-enums/tutorial/HelloWorld.html

## Installation

Simply add `enum.h` to your project &mdash; that's it.

Then, include it and use the `ENUM` macro. Your compiler will generate the rich
enums that are missing from standard C++.

## Additional features

- No dependencies and no external build tools. Uses only standard C++, though,
  for C++98, variadic macro support is required.
- Supported and tested on clang, gcc, and msvc.
- Fast compilation. You have to declare a few dozen enums to slow down your
  compiler as much as [just including `iostream` does][performance].
- Use any initializers and sparse ranges, just like with a built-in enum.
- Guaranteed size and alignment &mdash; you choose the representation type.

[performance]: http://aantron.github.io/better-enums/Performance.html

## Limitations

The biggest current limitation is that the `ENUM` macro can't be used inside a
class. This seems difficult to remove, but I am looking into it. In the
meantime, there is a workaround with a `typedef` (or `using`):

```cpp
ENUM(UniquePrefix_Color, uint8_t, Red, Green, Blue)

struct triplet {
    typedef UniquePrefix_Color      Color;
    Color                           r, g, b;
};

triplet::Color  color;
```

You can, however, use `ENUM` inside a namespace.

## Contact

Don't hesitate to contact me about features or bugs:
[antonbachin@yahoo.com][email], Twitter [@better_enums][twitter], or open an
issue on GitHub.

[email]:   mailto:antonbachin@yahoo.com
[twitter]: https://twitter.com/better_enums

## License and history

Better Enums is released under the BSD 2-clause license. See
[LICENSE](https://github.com/aantron/better-enums/blob/master/LICENSE).

The library was originally developed by the author in the winter of 2012-2013 at
Hudson River Trading, as a replacement for an older generator called
`BETTER_ENUM`.
