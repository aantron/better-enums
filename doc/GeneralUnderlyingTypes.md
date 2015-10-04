## General underlying types

The underlying type of a Better Enum doesn't have to be an integral type. It can
be any literal type `T`, as long as you provide a `constexpr` two-way mapping
between `T` and an integral type of your choosing. It also works in $cxx98,
though, of course, `T` doesn't have to be literal and the mapping doesn't have
to be `constexpr` &mdash; everything will be done by Better Enums at run time.

Doing this enables the following usage:

    // The type. A color triplet.
    <em>struct html_color {
        uint8_t     r, g, b;

        constexpr html_color(uint8_t _r, uint8_t g, uint8_t b) :
            r(_r), g(_g), b(_b) { }
    };</em>



    // The enum.
    <em>BETTER_ENUM(Color, html_color,
                darksalmon = 0xc47451, purplemimosa = 0x9e7bff,
                slimegreen = 0xbce954)</em>



    // The usage.
    <em>Color   c = Color::darksalmon;

    std::cout << "Red component: " << c->r << std::endl;

    switch (c) {
        case Color::darksalmon:   // ...
        case Color::purplemimosa: // ...
        case Color::slimegreen:   // ...
    }</em>

As you can see, you can have an enumerated set of any literal type, and safely
use the values in `switch`, with the compiler checking exhaustiveness. You can
also access the type's members using the `enum->underlying_member` syntax.

You do have to supply the mapping to an integral type, however. One option is:

    // The mapping. It just stuffs bits.
    <em>template <>
    struct ::better_enums::underlying_traits<html_color> {
        using integral_representation = unsigned int;

        constexpr static html_color from_integral(unsigned int i)
            { return html_color(i >> 16 & 0xff, i >> 8 & 0xff, i & 0xff); }

        constexpr static unsigned int to_integral(html_color c)
            { return (unsigned int)c.r << 16 | (unsigned int)c.g << 8 | c.b; }
    };</em>

### Using constructors in initializers

The declaration above used only numeric initializers. It is possible to use the
type's own constructors, provided the type has a `constexpr` conversion to your
chosen integral type:

    // The type.
    <em>struct html_color {
        uint8_t     r, g, b;

        constexpr html_color(uint8_t _r, uint8_t g, uint8_t b) :
            r(_r), g(_g), b(_b) { }

        </em>// This is new:<em>
        constexpr operator unsigned int() const
            { return (unsigned int)r << 16 | (unsigned int)g << 8 | b; }
    };</em>

    // The enum.
    <em>BETTER_ENUM(Color, html_color,
                darksalmon = 0xc47451, purplemimosa = 0x9e7bff,
                slimegreen = 0xbce954,
                celeste = html_color(0x50, 0xeb, 0xec))</em>

This is not possible at all in $cxx98, however.

### Letting the compiler enumerate your literal type

You don't have to use initializers. For example, as long as your example type
`file_descriptor` knows how to deal with the values, you can have the compiler
generate them in sequence:

    <em>BETTER_ENUM(FD, file_descriptor,
                        STDIN, STDOUT, STDERR, SomePipeYourDaemonHas, ...)</em>

SAMPLE

You can see the code "in action" in the [test case][test]. Be aware that it's
not very "nice," because it uses conditional compilation to run under multiple
compilers. I haven't written a clean sample or documentation yet simply because
this feature is in a very early stage of development.

[test]: $repo/blob/master/test/cxxtest/underlying.h

### Discussion

This feature is still semi-experimental, though I expect it to remain stable,
except perhaps that I will make it possible to infer the type
`integral_representation`.

Any opinions are welcome.

- The main reason Better Enums needs you to supply and explicit mapping is
  because it can't just get the "bits" of objects of underlying type in
  `constexpr` code. Both `reinterpret_cast` and union abuse seem to be forbidden
  in `constexpr` functions.
- There is currently no way to have two different integral representaitons for
  the same underlying type in different enums. I don't think that's a major use
  case at this point, however.

%% description = "Using Better Enums with non-integral underlying types."
