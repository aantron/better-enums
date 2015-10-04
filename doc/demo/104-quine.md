## Semi-quine

Let's make a Better Enum assemble its own definition in memory. It won't be
literally as defined, since we will lose the exact initializer expressions, but
we will be able to preserve the numeric values. We will reserve the memory
buffer for the definition at compile time.

Ok, so it's not really a quine, because we won't be writing all the code needed
to generate the definition to the buffer as well. And, there are better ways to
dump the definition than shown here. You could simply define a macro that
expands to an `BETTER_ENUM` declaration and also stringizes it.

But that's not the point here. The point of this page is to show some of the
reflective capabilities of Better Enums, so you can adapt them for cases where a
macro is not sufficient :)

$internal_toc

---

    #include <cassert>
    #include <cstdio>
    #include <iostream>

---

First, we will need
[full compile-time reflection](${prefix}OptInFeatures.html#CompileTimeNameTrimming),
since we will be calling `_to_string`. Let's make sure it's enabled by defining
`BETTER_ENUMS_CONSTEXPR_TO_STRING` before including `enum.h`:

    #ifndef <em>BETTER_ENUMS_CONSTEXPR_TO_STRING</em>
    #define <em>BETTER_ENUMS_CONSTEXPR_TO_STRING</em>
    #endif

    <em>#include <enum.h></em>

Now, let's declare some enums to dump later:

    BETTER_ENUM(<em>Channel</em>, int, Red, Green, Blue)
    BETTER_ENUM(<em>Depth</em>, int, TrueColor = 1, HighColor = 0)



### Computing the size of the buffer

First, we need to be able to get the length of each declaration above. We will
assume that the underlying type is always `int`, and that the spacing convention
is followed as above.

First, let's get the lengths of basic components:

    // Returns the length of the string representation of the number n
    constexpr <em>size_t value_length</em>(int <em>n</em>, int bound = 10, size_t digits = 1)
    {
        return
            <em>n < bound ? digits : value_length(n, bound * 10, digits + 1)</em>;
    }

    // Returns the length of s
    constexpr <em>size_t string_length</em>(const char *<em>s</em>, size_t index = 0)
    {
        return <em>s[index] == '\0' ? index : string_length(s, index + 1)</em>;
    }

Now, the length of the constant declaration. Here is where we lose information
about initializers. We are going to format the constant declarations like this:

~~~comment
Red = 0, Green = 1, Blue = 2
TrueColor = 1, HighColor = 0
~~~

This is because Better Enums doesn't provide a way to know what the exact
initializer was or whether there even was one &mdash; just the numeric value of
each constant. If we were trying to be clever, we could avoid formatting
initializers for sequential values, but I won't go through this exercise here.

    // Returns the length of the constants portion of the declaration of Enum,
    // as described above.
    template <<em>typename Enum</em>>
    constexpr <em>size_t constants_length</em>(size_t index = 0, size_t accumulator = 0)
    {
        return
            <em>index >= Enum::_size() ? accumulator :
            constants_length<Enum>(
                index + 1, accumulator
                            + string_length(", ")
                            + string_length(Enum::_names()[index])
                            + string_length(" = ")
                            + value_length(
                                Enum::_values()[index]._to_integral()))</em>;
    }

Finally, we can combine these to get the length of the formatted declaration of
the whole enum:

    // Returns the length of the whole declaration of Enum, assuming the
    // underlying type is int, and the constants are initialized as assumed by
    // constants_length() above.
    template <<em>typename Enum</em>>
    constexpr <em>size_t declaration_length</em>()
    {
        return
            <em>string_length("BETTER_ENUM(")
            + string_length(Enum::_name())
            + string_length(", int")
            + constants_length<Enum>()
            + string_length(")")</em>;
    }



### Formatting the enums

Now, we can declare the buffers. The memory will be reserved at load time by the
binary's loader. The extra one byte in each buffer is for the null terminator.

    <em>char</em>    channel_definition[<em>declaration_length<Channel>() + 1</em>];
    <em>char</em>    depth_definition[<em>declaration_length<Depth>() + 1</em>];

Let's also create the formatting function. This is executed at run time, but we
will be giving it pointers to our statically-allocated buffers. It will format
the enum declaration and then return the number of bytes it wrote to the buffer,
so that we can do a sanity check on it.

    template <<em>typename Enum</em>>
    <em>size_t format</em>(char *<em>buffer</em>)
    {
        size_t  offset = 0;

        offset += std::sprintf(buffer, <em>"BETTER_ENUM(%s, int", Enum::_name()</em>);

        <em>for</em> (<em>Enum value</em> : <em>Enum::_values()</em>) {
            offset +=
                std::sprintf(buffer + offset,
                             <em>", %s = %i",
                             value._to_string(), value._to_integral()</em>);
        }

        offset += std::sprintf(buffer + offset, <em>")"</em>);

        return <em>offset</em>;
    }



### Checking our work

Now, we can write and run this code.

    int main()
    {
        size_t  channel_length = <em>format<Channel></em>(channel_definition);
        assert(channel_length + 1 == sizeof(channel_definition));

        size_t  depth_length = <em>format<Depth></em>(depth_definition);
        assert(depth_length + 1 == sizeof(depth_definition));

        std::cout << <em>channel_definition</em> << std::endl;
        std::cout << <em>depth_definition</em> << std::endl;

        return 0;
    }

It prints:

~~~comment
BETTER_ENUM(Channel, int, Red = 0, Green = 1, Blue = 2)
BETTER_ENUM(Depth, int, TrueColor = 1, HighColor = 0)
~~~

%% description = Have a Better Enum print its own definition. Shows how to
compute the amount of memory necessary from the reflective information provided
by a Better Enum.
