// This file was generated automatically.

// Non-integral underlying types
//
// The underlying type of a Better Enum doesn't have to be an integral type. It
// can be any literal type T, as long as you provide a constexpr two-way mapping
// between T and an integral type of your choosing. This also works in C++98 -
// though then, of course, T doesn't have to be literal and the mapping doesn't
// have to be constexpr. In C++98, everything involving T will simply be done by
// Better Enums at run time.
//
// This feature is semi-experimental. I am considering relaxing the requirements
// on T so that it doesn't have to be literal. I can use a reinterpret_cast to
// make a mapping automatically. This will make non-integral underlying types
// easier to use, but will also prevent usage at compile time, which
// unfortunately has structural consequences for the implementation of Better
// Enums, and additional semantic consequences for usage, even at run time.
//
// In the meantime, here's how to have a non-integral underlying type in the
// current version.

#include <iostream>
#include <enum.h>
typedef unsigned char uint8_t;      // <cstdint> not in C++98.



// The underlying type. A color triplet.
struct html_color {
    uint8_t     r, g, b;

    constexpr html_color(uint8_t _r, uint8_t _g, uint8_t _b) :
        r(_r), g(_g), b(_b) { }
};

// The mapping. It just stuffs bits to get the same effect as
// reinterpret_cast, except reinterpret_cast is not available in constexpr
// functions, so we have to write the bit manipulations out. On modern
// C++11 compilers, you don't have to enter the better_enums namespace like
// this - you can just do
// struct ::better_enums::integral_mapping<html_color> { ...
namespace better_enums {

template <>
struct integral_mapping<html_color> {
    using integral_representation = unsigned int;

    constexpr static html_color from_integral(unsigned int i)
        { return html_color(i >> 16 & 0xff, i >> 8 & 0xff, i & 0xff); }

    constexpr static unsigned int to_integral(html_color c)
        { return (unsigned int)c.r << 16 | (unsigned int)c.g << 8 | c.b; }
};

}



// The enum itself.
BETTER_ENUM(Color, html_color,
            darksalmon = 0xc47451, purplemimosa = 0x9e7bff,
            slimegreen = 0xbce954)

// Now, we can do:

int main()
{
    Color   color = Color::darksalmon;

    std::cout << std::hex;
    std::cout << "Red component: "   << (int)color->r << std::endl;
    std::cout << "Green component: " << (int)color->g << std::endl;
    std::cout << "Blue component: "  << (int)color->b << std::endl;

    std::cout << color._to_string() << std::endl;

    switch (color) {
        case Color::darksalmon:   return 0;
        case Color::purplemimosa: return 1;
        case Color::slimegreen:   return 2;
    }

    return 0;
}

// This prints each component, the name of the color ("darksalmon"), and then
// exits from the switch with status 0.
//
// Constructors in initializers
//
// The above declaration used only numbers in initializers, but it is actually
// possible to use constructors of html_color. We have to add a constexpr
// converting operator directly to html_color, however:
//
// struct better_html_color {
//     uint8_t     r, g, b;
//
//     constexpr better_html_color(uint8_t _r, uint8_t _g, uint8_t _b) :
//         r(_r), g(_g), b(_b) { }
//
//     // This is new:
//     constexpr operator unsigned int() const
//         { return (unsigned int)r << 16 | (unsigned int)g << 8 | b; }
// };
//
// namespace better_enums {
//
// template <>
// struct integral_mapping<better_html_color> {
//     using integral_representation = unsigned int;
//
//     constexpr static better_html_color from_integral(unsigned int i)
//     {
//         return better_html_color(i >> 16 & 0xff, i >> 8 & 0xff, i & 0xff);
//     }
//
//     constexpr static unsigned int to_integral(better_html_color c)
//         { return (unsigned int)c.r << 16 | (unsigned int)c.g << 8 | c.b; }
// };
//
// }
//
// This allows:
//
// BETTER_ENUM(BetterColor, better_html_color,
//             darksalmon = 0xc47451, purplemimosa = 0x9e7bff,
//             slimegreen = 0xbce954,
//             celeste = better_html_color(0x50, 0xeb, 0xec))
//
// If you can't edit your literal type to add this converting operator, or don't
// want to for type safety reasons, you can achieve a similar effect by
// declaring an intermediate type U that html_color can convert to, that can
// convert to the integral type. Then, cast your constructor call to U. The type
// U is for declarations only.
//
// Constructors in initializers require C++11. Also, g++ doesn't support this
// before 5.1.
//
// Letting the compiler enumerate your type
//
// Of course, as long as the values are valid, you can let the compiler
// enumerate your type as in a regular enum, by omitting initializers:
//
// BETTER_ENUM(FD, file_descriptor,
//                     STDIN, STDOUT, STDERR, SomePipeYourDaemonHas, ...)
//
// Here, FD::STDIN maps to the integral representation 0, STDOUT to 1, and so
// on.
//
// Discussion
//
// This feature is still semi-experimental, though I expect it to remain stable,
// except perhaps that I will make it possible to infer the type
// integral_representation.
//
// Any opinions are welcome.
//
//   1. The main reason Better Enums needs you to supply and explicit mapping is
//      because it can't just get the "bits" of objects of underlying type in
//      constexpr code. Both reinterpret_cast and union abuse seem to be
//      forbidden in constexpr functions.
//   2. There is currently no way to have two different integral representaitons
//      for the same underlying type in different enums. I don't think that's a
//      major use case at this point, however.
