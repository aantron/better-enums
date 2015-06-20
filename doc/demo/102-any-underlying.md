## Non-integral underlying types

The underlying type of a Better Enum doesn't have to be an integral type. It can
be any literal type `T`, as long as you provide a `constexpr` two-way mapping
between `T` and an integral type of your choosing. This also works in $cxx98
&mdash; though then, of course, `T` doesn't have to be literal and the mapping
doesn't have to be `constexpr`. In $cxx98, everything involving `T` will simply
be done by Better Enums at run time.

Here's how to do it.

    #include <iostream>
    #include <enum.h>
    typedef unsigned char uint8_t;      // <cstdint> not in C++98.



    // The underlying type. A color triplet.
    <em>struct html_color {
        uint8_t     r, g, b;

        constexpr html_color(uint8_t _r, uint8_t _g, uint8_t _b) :
            r(_r), g(_g), b(_b) { }
    };</em>

    // The mapping. It just stuffs bits to get the same effect as
    // reinterpret_cast, except reinterpret_cast is not available in constexpr
    // functions, so we have to write the bit manipulations out. On modern
    // C++11 compilers, you don't have to enter the better_enums namespace like
    // this - you can just do
    // struct ::better_enums::integral_mapping<html_color> { ...
    namespace better_enums {

    <em>template <>
    struct integral_mapping<html_color> {
        using integral_representation = unsigned int;

        constexpr static html_color from_integral(unsigned int i)
            { return html_color(i >> 16 & 0xff, i >> 8 & 0xff, i & 0xff); }

        constexpr static unsigned int to_integral(html_color c)
            { return (unsigned int)c.r << 16 | (unsigned int)c.g << 8 | c.b; }
    };</em>

    }



    // The enum itself.
    <em>ENUM(Color, html_color,
         darksalmon = 0xc47451, purplemimosa = 0x9e7bff, slimegreen = 0xbce954)</em>

Now, we can do:

    int main()
    {
        <em>Color   color = Color::darksalmon</em>;

        std::cout << std::hex;
        std::cout << "Red component: "   << <em>(int)color->r</em> << std::endl;
        std::cout << "Green component: " << <em>(int)color->g</em> << std::endl;
        std::cout << "Blue component: "  << <em>(int)color->b</em> << std::endl;

        std::cout << <em>color._to_string()</em> << std::endl;

        <em>switch (color)</em> {
            <em>case Color::darksalmon</em>:   return 0;
            <em>case Color::purplemimosa</em>: return 1;
            <em>case Color::slimegreen</em>:   return 2;
        }

        return 0;
    }

This prints each component, the name of the color (`"darksalmon"`), and then
exits from the `switch` with status 0.

### Constructors in initializers

The above declaration used only numbers in initializers, but it is actually
possible to use constructors of `html_color`. We have to add a `constexpr`
converting operator directly to `html_color`, however:

~~~comment
struct better_html_color {
    uint8_t     r, g, b;

    constexpr better_html_color(uint8_t _r, uint8_t _g, uint8_t _b) :
        r(_r), g(_g), b(_b) { }

    <em>// This is new:
    constexpr operator unsigned int() const
        { return (unsigned int)r << 16 | (unsigned int)g << 8 | b; }</em>
};

namespace better_enums {

template <>
struct integral_mapping<better_html_color> {
    using integral_representation = unsigned int;

    constexpr static better_html_color from_integral(unsigned int i)
    {
        return better_html_color(i >> 16 & 0xff, i >> 8 & 0xff, i & 0xff);
    }

    constexpr static unsigned int to_integral(better_html_color c)
        { return (unsigned int)c.r << 16 | (unsigned int)c.g << 8 | c.b; }
};

}
~~~

This allows:

~~~comment
ENUM(BetterColor, better_html_color,
     darksalmon = 0xc47451, purplemimosa = 0x9e7bff, slimegreen = 0xbce954,
     <em>celeste = better_html_color(0x50, 0xeb, 0xec)</em>)
~~~

If you can't edit your literal type to add this converting operator, or don't
want to for type safety reasons, you can achieve a similar effect by declaring
an intermediate type `U` that `html_color` can convert to, that can convert to
the integral type. Then, cast your constructor call to `U`. The type `U` is for
declarations only.

Constructors in initializers require $cxx11. Also, g++ doesn't support this
before 5.1.

### Letting the compiler enumerate your type

Of course, as long as the values are valid, you can let the compiler enumerate
your type as in a regular enum, by omitting initializers:

~~~comment
<em>ENUM(FD, file_descriptor, STDIN, STDOUT, STDERR, SomePipeYourDaemonHas, ...)</em>
~~~

Here, `FD::STDIN` maps to the integral representation 0, `STDOUT` to 1, and so
on.

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
