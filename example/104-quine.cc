// This file was generated automatically.

// Semi-quine
//
// Let's make a Better Enum assemble its own definition in memory. It won't be
// literally as defined, since we will lose the exact initializer expressions,
// but we will be able to preserve the numeric values. We will reserve the
// memory buffer for the definition at compile time.
//
// Ok, so it's not really a quine, because we won't be writing all the code
// needed to generate the definition to the buffer as well. And, there are
// better ways to dump the definition than shown here. You could simply define a
// macro that expands to an BETTER_ENUM declaration and also stringizes it.
//
// But that's not the point here. The point of this page is to show some of the
// reflective capabilities of Better Enums, so you can adapt them for cases
// where a macro is not sufficient :)


#include <cassert>
#include <cstdio>
#include <iostream>


// First, we will need full compile-time reflection, since we will be calling
// _to_string. Let's make sure it's enabled by defining
// BETTER_ENUMS_CONSTEXPR_TO_STRING before including enum.h:

#ifndef BETTER_ENUMS_CONSTEXPR_TO_STRING
#define BETTER_ENUMS_CONSTEXPR_TO_STRING
#endif

#include <enum.h>

// Now, let's declare some enums to dump later:

BETTER_ENUM(Channel, int, Red, Green, Blue)
BETTER_ENUM(Depth, int, TrueColor = 1, HighColor = 0)



// Computing the size of the buffer
//
// First, we need to be able to get the length of each declaration above. We
// will assume that the underlying type is always int, and that the spacing
// convention is followed as above.
//
// First, let's get the lengths of basic components:

// Returns the length of the string representation of the number n
constexpr size_t value_length(int n, int bound = 10, size_t digits = 1)
{
    return
        n < bound ? digits : value_length(n, bound * 10, digits + 1);
}

// Returns the length of s
constexpr size_t string_length(const char *s, size_t index = 0)
{
    return s[index] == '\0' ? index : string_length(s, index + 1);
}

// Now, the length of the constant declaration. Here is where we lose
// information about initializers. We are going to format the constant
// declarations like this:
//
// Red = 0, Green = 1, Blue = 2
// TrueColor = 1, HighColor = 0
//
// This is because Better Enums doesn't provide a way to know what the exact
// initializer was or whether there even was one - just the numeric value of
// each constant. If we were trying to be clever, we could avoid formatting
// initializers for sequential values, but I won't go through this exercise
// here.

// Returns the length of the constants portion of the declaration of Enum,
// as described above.
template <typename Enum>
constexpr size_t constants_length(size_t index = 0, size_t accumulator = 0)
{
    return
        index >= Enum::_size() ? accumulator :
        constants_length<Enum>(
            index + 1, accumulator
                        + string_length(", ")
                        + string_length(Enum::_names()[index])
                        + string_length(" = ")
                        + value_length(
                            Enum::_values()[index]._to_integral()));
}

// Finally, we can combine these to get the length of the formatted declaration
// of the whole enum:

// Returns the length of the whole declaration of Enum, assuming the
// underlying type is int, and the constants are initialized as assumed by
// constants_length() above.
template <typename Enum>
constexpr size_t declaration_length()
{
    return
        string_length("BETTER_ENUM(")
        + string_length(Enum::_name())
        + string_length(", int")
        + constants_length<Enum>()
        + string_length(")");
}



// Formatting the enums
//
// Now, we can declare the buffers. The memory will be reserved at load time by
// the binary's loader. The extra one byte in each buffer is for the null
// terminator.

char    channel_definition[declaration_length<Channel>() + 1];
char    depth_definition[declaration_length<Depth>() + 1];

// Let's also create the formatting function. This is executed at run time, but
// we will be giving it pointers to our statically-allocated buffers. It will
// format the enum declaration and then return the number of bytes it wrote to
// the buffer, so that we can do a sanity check on it.

template <typename Enum>
size_t format(char *buffer)
{
    size_t  offset = 0;

    offset += std::sprintf(buffer, "BETTER_ENUM(%s, int", Enum::_name());

    for (Enum value : Enum::_values()) {
        offset +=
            std::sprintf(buffer + offset,
                         ", %s = %i",
                         value._to_string(), value._to_integral());
    }

    offset += std::sprintf(buffer + offset, ")");

    return offset;
}



// Checking our work
//
// Now, we can write and run this code.

int main()
{
    size_t  channel_length = format<Channel>(channel_definition);
    assert(channel_length + 1 == sizeof(channel_definition));

    size_t  depth_length = format<Depth>(depth_definition);
    assert(depth_length + 1 == sizeof(depth_definition));

    std::cout << channel_definition << std::endl;
    std::cout << depth_definition << std::endl;

    return 0;
}

// It prints:
//
// BETTER_ENUM(Channel, int, Red = 0, Green = 1, Blue = 2)
// BETTER_ENUM(Depth, int, TrueColor = 1, HighColor = 0)
