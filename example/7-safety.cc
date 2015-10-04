// This file was generated automatically.

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

BETTER_ENUM(Channel, int, Red = 1, Green, Blue)

// you don't get names such as Red in the global namespace. Instead, you get
// Channel, and Red is accessible as Channel::Red. This is no big deal in C++11,
// which has enum class. In C++98, however, this typically requires effort.
// Better Enums brings scope uniformly to both variants. So, despite the above
// declaration, you can safely declare

BETTER_ENUM(Node, char, Red, Black)

// and everything will work as expected.

int main()
{
    assert((+Channel::Red)._to_integral() != (+Node::Red)._to_integral());

// Implicit conversion
//
// A major complaint in C++98 is that enums are implicitly convertible to
// integers. Unfortunately, that is also true of Better Enums, and I haven't
// found a way to forbid the conversions and still have switch case checking.
//
// Better Enums can be made as safe as enum class in C++11, however. If your
// compiler supports enum class and you define BETTER_ENUMS_STRICT_CONVERSION
// before including enum.h, the following code will not compile:
//
//     Channel     channel = Channel::Red;
//     int         n = channel;
//
// The reason this is not enabled by default is explained in the reference page
// on strict conversions.
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
//
//     Channel      channel;
//
// This may be too strict, and I may relax it in the future. In the meantime,
// the solution sketched in the special values demo can replace default
// constructors for some purposes, and in a more flexible way. I may eventually
// have the default constructor calling a template function like the one in that
// demo.


    return 0;
}
