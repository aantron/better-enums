## Compile-time usage

When used with $cxx11, Better Enums are generated entirely during compilation.
All the data is available for use by your own `constexpr` functions. The
examples in *this* tutorial aren't very useful, but read the following tutorials
to get an idea of what can be done. Here, you will see the basics.

    #include <iostream>

    #ifndef BETTER_ENUMS_CONSTEXPR_TO_STRING
    #define BETTER_ENUMS_CONSTEXPR_TO_STRING
    #endif

    <em>#include <enum.h></em>

    <em>ENUM(Channel, int, Red = 1, Green = 2, Blue = 3)</em>

    <em>constexpr</em> Channel      channel = Channel::Green;
    <em>constexpr</em> int          value = <em>channel._to_integral()</em>;

    <em>constexpr</em> const char   *name = <em>channel._to_string()</em>;
    <em>constexpr</em> Channel      parsed = <em>Channel::_from_string("Red")</em>;

All of the above are computed during compilation. You can do apparently useless
things such as:

    <em>constexpr size_t length</em>(<em>const char *s</em>, <em>size_t index = 0</em>)
    {
        return <em>s[index] == '\0'</em> ? <em>index</em> : <em>length(s, index + 1)</em>;
    }

    <em>constexpr</em> size_t    <em>length_of_name_of_second_constant</em> =
        <em>length(Channel::_names()[1])</em>;

    int main()
    {
        std::cout << <em>length_of_name_of_second_constant</em> << std::endl;

        return 0;
    }

Which prints "5", the length of "Green". That 5 was also computed during
compilation.
