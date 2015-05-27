## Opt-in features

Better Enums has a few opt-in features that affect how enums are generated. The
default configuration is suitable for general use, but you might have more
stringent requirements. This page describes the optional features and how to
enable them.

### Strict conversions

Each Better Enum is implicitly convertible to its member `enum _enumerated`
type. This is meant to support usage of Better Enums directly in `switch`
statements. When you write

    switch (channel) {
        ...
    }

the compiler applies the implicit conversion, and is also able to do case
exhaustiveness checking. Unfortunately, `_enumerated` is always a regular $cxx98
enum type, meaning that it has standard conversions to integral types. The end
result is `channel` is implicitly convertible all the way to `int` &mdash;
behavior that is often considered a violation of type safety.

In $cxx11, you can force Better Enums to declare an internal `enum class` type
to use for `switch` statements. Each enum will then be only convertible to its
`enum class`, and won't be implicitly convertible to integers. This is done by
defining `BETTER_ENUMS_STRICT_CONVERSION` before including `enum.h`. You would
typically do this on the compiler's command line.

The reason strict conversions aren't enabled by default in $cxx11 is that doing
so would break compatibility with the $cxx98 interface.

  - The "weaker" incompatibility is that you could write a bunch of $cxx98 code
    that relies on implicit integer conversions, and then try to switch to
    $cxx11. The code would then fail to compile. An example where implicit
    conversions are an "advantage" is when using Better Enums as arguments to
    the methods of `std::bitset`. I could have ignored this problem by declaring
    usage of implicit integer conversions unsupported, but in light of the next
    issue, I decided not to do that.
  - The "stronger" incompatibility is a difference in how `switch` cases must be
    written. The syntaxes for the two variants, implicitly-converting and
    strict, are mutually exclusive.

Here they are:

    // Default variant
    switch (channel) {
        case Channel::Red:   break;
        case Channel::Green: break;
        case Channel::Blue:  break;
    }

    // Strict variant
    switch (channel) {
        case +Channel::Red:   break;
        case +Channel::Green: break;
        case +Channel::Blue:  break;
    }

I would be very happy to make conversion to `enum class` the default whenever
`enum class` is available, but how to do so without breaking compatibility is so
far an open problem.

### Compile-time name trimming

Better Enums is able to do all of its work at compile time. There is one task,
however, at which my current method is pretty slow on modern compilers. The
performance is still reasonable, but it makes enums take about four times longer
to compile, compared to deferring the task to program startup. The task is
trimming stringized constant names.

The problem arises when the preprocessor stringizes an initializer. For example,

    ENUM(Channel, int, Red = 1, Green, Blue);

results in an internal array, somewhere inside the generated Better Enum, that
looks like

    names = {"Red = 1", "Green", "Blue"}

Before the name of `Channel::Red` can be returned to the user, the initializer
` = 1` must be trimmed off. This is the part that is slow to compile, and is
deferred to startup by default.

If you want to enable it at compile time, you have two options. The first is to
use an alternative `SLOW_ENUM` macro to declare your enum. It will enable
compile-time trimming for that enum only. If you only do this for a few enums,
you probably won't notice the difference in compilation time.

You can also enable compile-time trimming globally for all enums by defining
`BETTER_ENUMS_CONSTEXPR_TO_STRING` before including `enum.h`. Typically, you
would do this by supplying a command-line argument to your compiler.

The result of doing either one is that `_to_string` and `_names` will become
`constexpr` for your compile-time enjoyment.

The reason this option is not enabled by default when avaialble, besides the
fact that the current implementation is slow, is that I don't believe most users
need it most of the time.

As a note, the performance is not *that* bad. You still have to define on the
order of 10+ slow enums in order to slow compilation down as much as merely
including `iostream` does. However, it is shockingly slower than the faster
implementation, where you have the leeway to define 40+ enums before you reach
the same level of slowdown as `iostream` gives you.

There are enough other problems with slow enums, however, like potential symbol
pollution in the final binaries, that I decided to leave them as an opt-in
feature until they improve to the point where they can be the default.
