## Semi-quine

Let's make a Better Enum compose its own definition. It won't be literally as
defined, since we will lose some information about initializers, but we will be
able to preserve their numeric values. We will reserve the memory buffers at
compile time.

There are actually better ways to do this than shown here. You could define a
macro that expands to an `ENUM` declaration and also stringizes it. The point
here is to show some of the reflective capabilities of Better Enums, so you can
adapt them for cases where a macro is not sufficient.

    #include <cassert>
    #include <cstdio>
    #include <iostream>

    #ifndef BETTER_ENUMS_CONSTEXPR_TO_STRING
    #define BETTER_ENUMS_CONSTEXPR_TO_STRING
    #endif

    #include <enum.h>

    #define HIGH_COLOR  0

    ENUM(Channel, int, Red, Green, Blue)
    ENUM(Depth, int, TrueColor = 1, HighColor = HIGH_COLOR)

First, we need to be able to get the length of each definition above. We will
assume that the underlying type is always `int`, and that the spacing convention
is followed as above. This allows us to write:

    constexpr size_t value_length(int n, int bound = 10, size_t digits = 1)
    {
        return
            n < bound ? digits : value_length(n, bound * 10, digits + 1);
    }

    constexpr size_t string_length(const char *s, size_t index = 0)
    {
        return s[index] == '\0' ? index : string_length(s, index + 1);
    }

    template <typename Enum>
    constexpr size_t constants_length(size_t index = 0, size_t accumulator = 0)
    {
        return
            index >= Enum::_size ? accumulator :

            constants_length<Enum>(
                index + 1, accumulator
                            + string_length(", ")
                            + string_length(Enum::_names()[index])
                            + string_length(" = ")
                            + value_length(
                                Enum::_values()[index]._to_integral()));
    }

    template <typename Enum>
    constexpr size_t declaration_length()
    {
        return
            string_length("ENUM(")
            + string_length(Enum::_name())
            + string_length(", int")
            + constants_length<Enum>()
            + string_length(")");
    }

Now, we can declare:

    char    channel_definition[declaration_length<Channel>() + 1];
    char    depth_definition[declaration_length<Depth>() + 1];

And finally, the formatting function:

    template <typename Enum>
    size_t format(char *buffer)
    {
        size_t  offset = 0;

        offset += std::sprintf(buffer, "ENUM(%s, int", Enum::_name());

        for (Enum value : Enum::_values()) {
            offset +=
                std::sprintf(buffer + offset,
                             ", %s = %i",
                             value._to_string(), value._to_integral());
        }

        offset += std::sprintf(buffer + offset, ")");

        return offset;
    }

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

This outputs:

~~~comment
ENUM(Channel, int, Red = 0, Green = 1, Blue = 2)
ENUM(Depth, int, TrueColor = 1, HighColor = 0)
~~~

This does have the advantage of not depending on anything else defined in the
program, which isn't as easy to achieve with stringization.
