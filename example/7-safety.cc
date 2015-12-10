// This file was generated automatically.

// Scope and safety
//
// This tutorial shows some of the safety features of Better Enums: scope, how
// to control conversions, and the lack of a default constructor.
//
// On balance, Better Enums are in one way less type-safe than enum class, and
// in another way more type-safe. The first difference in safety is the presence
// of implicit conversion to integral types. The second difference is the lack
// of a default constructor. Both of these can be toggled, so you can make
// Better Enums strictly safer than enum class, or just as safe.
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
// You can conveniently define the macro on your compiler's command line, or by
// creating a little header file that defines it, and then includes enum.h. You
// can then include this new header file in your project everywhere where you
// would have included enum.h.
//
// Default constructor
//
// Better Enums generate without a default constructor. The purpose is to
// support the convention where if a Better Enum exists, then it has a valid
// value. So, if you uncomment this code, the program won't compile:
//
//     Channel      channel;
//
// If this is too strict for your project, you can relax it as described here.


    return 0;
}
