// This file was generated automatically

// Scope and safety
//
// This tutorial shows some of the safety features of Better Enums: scope, how
// to control conversions, and the lack of a default constructor.
//
// Scope
//
// You have probably noticed by now that Better Enums are scoped: when you
// declare

#include <cassert>
#include <enum.h>

ENUM(Channel, int, Red = 1, Green, Blue)

// you don't get names such as Red in the global namespace. Instead, you get
// Channel, and Red is accessible as Channel::Red. This is no big deal in
// $cxx11, which has enum class. In $cxx98, however, this typically requires
// effort. Better Enums brings scope uniformly to both variants. So, despite the
// above declaration, you can safely declare

ENUM(Node, char, Red, Black)

// and everything will work as expected.

int main()
{
    assert((+Channel::Red)._to_integral() != (+Node::Red)._to_integral());

// Implicit conversion
//
// A major complaint in $cxx98 is that enums are implicitly convertible to
// integers. Unfortunately, that is also true of Better Enums, and I haven't
// found a way to forbid the conversions and still have switch case checking.
//
// Better Enums can be made as safe as enum class in $cxx11, however. If your
// compiler supports enum class and you define BETTER_ENUMS_STRICT_CONVERSION
// before including enum.h, the following code will not compile:
//
//     Channel     channel = Channel::Red;
//     int         n = channel;
//
// The reason you have to opt into this feature with a macro is because it
// breaks compatibility with the $cxx98 version of Better Enums. Specifically,
// when writing a switch statement, you now have to do
//
//     switch (channel) {
//         case +Channel::Red:   return 13;
//         case +Channel::Green: return 37;
//         case +Channel::Blue:  return 42;
//     }
//
// The difference is the explicit promotion with +. And, of course, if you had a
// bunch of code that relies on implicitly converting $cxx98 Better Enums to
// integers, it would break when switching to $cxx11 if strict conversions were
// the default.
//
// Default constructor
//
// Better Enums don't have a default constructor, for three reasons.
//
//   1. Better Enums is a library that can't know what your application would
//      like the default value to be for each enum, or whether you even want
//      one.
//   2. I chose not to leave the default value undefined, because the idea is to
//      encourage the convention that whenever a Better Enum exists, it has a
//      valid value. This is borrowed from typed functional programming.
//   3. Better Enums is still under development, and this option is the most
//      future-proof.
//
// So, if you uncomment this code, the file won't compile:

    // Channel      channel;

// This may seem very strict, and I may relax it in the future. However, my
// guess is that there are few places where a default constructor is truly
// needed.
//
//   1. If you want to opt in to a notion of default values, you can encode your
//      project's policy into $cxx templates with ease, using building blocks
//      Better Enums provides. The solution sketched <a
//      href="${prefix}demo/SpecialValues.html">here</a> is arguably more
//      flexible than any fixed choice Better Enums could impose on you.
//   2. If a Better Enum value is the result of a large sequence of statements,
//      you may be able to move those statements into a separate function that
//      returns the value, and call it to initialize the Better Enum.
//   3. If you need to reserve memory for a Better Enum before it is created,
//      you can do so by declaring a value of type Enum::_integral, as described
//      in the <a href="${prefix}tutorial/RepresentationAndAlignment.html">next
//      tutorial</a>.
//   4. I may add an ability to extend Better Enums, in which case you could add
//      a default constructor on a per-type or global basis and have it do
//      anything you want. I'd be glad to hear any feedback about your actual
//      usage and needs.
//   5. Finally, Better Enums is under the BSD license so you can fork it and
//      change it directly, though of course this can have some administration
//      overhead.

}
