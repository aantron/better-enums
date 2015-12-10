## C++17 reflection proposal

*You can try this demo [live online][live].*

Better Enums can be used to implement the enums portion of the
[$cxx17 reflection proposal N4428][n4428] in $cxx11. N4428 proposes the
following traits interface:

~~~comment
<em>namespace std {

template <typename E>
struct enum_traits {
    struct enumerators {
        constexpr static size_t         size;

        template <size_t I>
        struct get {
            constexpr string_literal    identifier;
            constexpr static E          value;
        };
    };
};

}</em>
~~~

So, the basic usage would be:

~~~comment
<em>enum class Foo {A, B, C};

constexpr size_t            size =
    std::enum_traits<Foo>::enumerators::size;

constexpr Foo               value_0 =
    std::enum_traits<Foo>::enumerators::get<0>::value;

constexpr string_literal    name_1 =
    std::enum_traits<Foo>::enumerators::get<1>::identifier;</em>
~~~

Resulting in the values `3`, `Foo::A`, and `"B"`, respectively.

---

The interface is implemented in the optional header file
[`extra/better-enums/n4428.h`][header]. There is a necessary difference: the
interface is only available for enums declared through the `BETTER_ENUM` macro.
This is because the macro is what generates the information necessary for
reflection.

### Demo

So, with that out of the way, we can do a little test. Let's assume that
`extra/` has been added as a directory to search for include files.

    #ifndef BETTER_ENUMS_CONSTEXPR_TO_STRING
    #define BETTER_ENUMS_CONSTEXPR_TO_STRING
    #endif

    #include <iostream>
    <em>#include</em> <<em>enum.h</em>>
    <em>#include</em> <<em>better-enums/n4428.h</em>>

---

Let's declare an enum:

    <em>BETTER_ENUM</em>(<em>Channel</em>, <em>char</em>, <em>Red</em> = <em>1</em>, <em>Green</em>, <em>Blue</em>)

...and try N4428:

    constexpr std::size_t   <em>size</em> =
        <em>std</em>::<em>enum_traits</em><<em>Channel</em>>::<em>enumerators</em>::<em>size</em>;

    constexpr Channel       <em>value_0</em> =
        <em>std</em>::<em>enum_traits</em><<em>Channel</em>>::<em>enumerators</em>::<em>get</em><<em>0</em>>::<em>value</em>;

    constexpr Channel       <em>value_1</em> =
        <em>std</em>::<em>enum_traits</em><<em>Channel</em>>::<em>enumerators</em>::<em>get</em><<em>1</em>>::<em>value</em>;

    constexpr const char    *<em>identifier_2</em> =
        <em>std</em>::<em>enum_traits</em><<em>Channel</em>>::<em>enumerators</em>::<em>get</em><<em>2</em>>::<em>identifier</em>;

...and check the results:

    static_assert(<em>size</em> == <em>3</em>, "");

    static_assert(<em>value_0</em> == +<em>Channel::Red</em>, "");
    static_assert(<em>value_1</em> == +<em>Channel::Green</em>, "");

    int main()
    {
        std::cout << <em>identifier_2</em> << std::endl;
        return 0;
    }

That prints `Blue`, as you would expect.

### Quirk

The reason for the `#define` in the code above is that there is one quirk:
the interface above is available only for Better Enums for which
[compile-time name trimming][slow-enum] is enabled &mdash; those declared when
`BETTER_ENUMS_CONSTEXPR_TO_STRING` was defined, or declared with the `SLOW_ENUM`
variant of `BETTER_ENUM`. As mentioned on the linked page, the reason
compile-time name trimming is not the default is that, while still pretty fast,
it is four times slower than program-startup-time name trimming. The latter is
the default.

Despite the above, a variation on the interface is available for enums without
compile-time name trimming:

~~~comment
<em>namespace std {

template <typename E>
struct enum_traits {
    struct enumerators {
        constexpr static size_t         size;

        template <size_t I>
        struct get {
            constexpr const char        *identifier;
            constexpr static E          value;
        };

        </em>// For enums without compile-time name trimming.<em>
        template <size_t I>
        struct get_alt {
            static const char* identifier();
            constexpr static E          value;
        };
    };
};

}</em>
~~~

As you can see, the difference is that `identifier` is a non-`constexpr`
function, and you have to access it through `get_alt<I>`.

~~~comment
// Without compile-time name trimming.
<em>BETTER_ENUM(Depth, int, HighColor, TrueColor)

int main()
{
    std::cout
        << std::enum_traits<Depth>::enumerators::get_alt<1>::identifier()
        << std::endl;

    return 0;
}</em>
~~~

### The future

N4428 is the fourth in a series of revisions: [N3815][n3815], [N4027][n4027],
[N4113][n4113], N4428. If there are more revisions that change the proposal for
enums, I will try to implement those as well.

[n4428]: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4428.pdf
[n4113]: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4113.pdf
[n4027]: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4027.pdf
[n3815]: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3815.html
[slow-enum]: ${prefix}OptInFeatures.html#CompileTimeNameTrimming
[header]: https://github.com/aantron/better-enums/blob/$ref/extra/better-enums/n4428.h
[live]: http://melpon.org/wandbox/permlink/QelcwZNLi4gIx8Ux

%% description = Approximate implementation of N4428 enum reflection based on
Better Enums.
