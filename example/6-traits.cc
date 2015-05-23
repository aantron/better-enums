// Using traits to capture project conventions on enums.

// In this example, a project wants to have a notion of "default value" for all
// enums. Better Enums doesn't provide this, but it can be added easily with a
// traits class, as shown here.

#include <iostream>
#include <enum.h>



// Adopt the convention that the first value in an enum is the default value.
template <typename Enum>
constexpr const Enum default_()
{
    return Enum::_values[0];
}

// Make it possible to override the convention for specific enums.
#define ENUM_DEFAULT(Enum, Default)                                            \
    template <>                                                                \
    constexpr const Enum default_<Enum>()                                      \
    {                                                                          \
        return Enum::Default;                                                  \
    }



// Default will be Red, because it is first.
ENUM(Channel, int, Red, Green, Blue)

// Default will be TrueColor, even though it is not first.
ENUM(Depth, int, HighColor, TrueColor)
ENUM_DEFAULT(Depth, TrueColor)



int main()
{
    // Default construction can now be simulated for some purposes, and the
    // default value is still declared in one place, not all over the program
    // code.
    Depth   depth = default_<Depth>();
    std::cout << depth._to_string() << std::endl;

    std::cout << default_<Channel>()._to_string() << std::endl;
    std::cout << default_<Depth>()._to_string()   << std::endl;

    return 0;
}



// Also works at compile-time.
constexpr auto  value = default_<Channel>();
