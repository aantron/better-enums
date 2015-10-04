## Compile-time usage

When used with $cxx11, Better Enums are generated entirely during compilation.
All the data is available for use by your own `constexpr` functions. The
examples in *this* tutorial aren't very useful, but look at the
[demos](${prefix}index.html#CompileTimeDemos) at the bottom of the main page to
get an idea of what can be done. Here, you will see the basics.

    #include <iostream>

    // The reason for this is explained below.
    #ifndef BETTER_ENUMS_CONSTEXPR_TO_STRING
    #define BETTER_ENUMS_CONSTEXPR_TO_STRING
    #endif

    <em>#include <enum.h></em>

    <em>BETTER_ENUM</em>(<em>Channel</em>, <em>int</em>, <em>Red</em> = <em>1</em>, <em>Green</em> = <em>2</em>, <em>Blue</em> = <em>3</em>)

    <em>constexpr</em> Channel      channel = <em>Channel::_from_integral(2)</em>;
    <em>constexpr</em> int          value = <em>channel._to_integral()</em>;

    <em>constexpr</em> const char   *name = <em>channel._to_string()</em>;
    <em>constexpr</em> Channel      parsed = <em>Channel::_from_string("Red")</em>;

All of the above are computed during compilation. The reason for the macro
definition at the top of the file is explained on the
[opt-in features page](${prefix}OptInFeatures.html#CompileTimeNameTrimming).
Basically, it makes `_to_string` `constexpr`, but slows down compilation.

You can also do things such as:

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

%% description = Better Enums can be used entirely at compile time in C++11. All
conversion functions are available for constexpr functions or templates.
