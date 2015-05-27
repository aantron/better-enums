## Special values

Suppose your project has a convention where each enum has special *invalid* and
*default* values. With Better Enums, you can encode that directly at compile
time, and then access each enum's special values using syntax like
`Channel c = default_` and `Channel c = invalid`. This can make your code adapt
automatically to changes in enum definitions, as well as make it easier to read
and understand its intent.

---

    #include <iostream>
    #include <stdexcept>
    <em>#include <enum.h></em>

### Invalid

Perhaps the invalid value is usually called `Invalid`, but not in all enums. You
can encode that using a function template for the common case, and a macro that
creates specializations:

    <em>template</em> <<em>typename Enum</em>>
    constexpr Enum find_invalid() { return Enum::Invalid; }

    <em>#define OVERRIDE_INVALID</em>(<em>Enum</em>, <em>Value</em>)                 \
    template<>                                            \
    constexpr Enum <em>find_invalid<Enum></em>() { return <em>Enum::Value</em>; }

Now, you can declare enums like these:

    ENUM(<em>Channel</em>, int, Red, Green, Blue, <em>Invalid</em>)

    ENUM(<em>Compression</em>, int, <em>Undefined</em>, None, Huffman)
    <em>OVERRIDE_INVALID</em>(<em>Compression</em>, <em>Undefined</em>)

and use them:

    static_assert(<em>find_invalid</em><<em>Channel</em>>() == <em>+Channel::Invalid</em>, "");
    static_assert(<em>find_invalid</em><<em>Compression</em>>() == <em>+Compression::Undefined</em>, "");

This even supports enums that don't have an invalid value at all. As long as
they don't have a constant called `Invalid`, you will get a compile-time error
if you try to call `invalid()` on them &mdash; as you probably should!

### Default

To encode the policy on default values, we need to do a compile-time check that
the first value is not invalid. Otherwise, the technique is the same.

    template <typename Enum>
    constexpr Enum find_default()
    {
        return
            Enum::_size < 2 ?
                throw std::logic_error("enum has no valid constants") :
            Enum::_values()[0] == find_invalid<Enum>() ?
                Enum::_values()[1] :
                Enum::_values()[0];
    }

    #define OVERRIDE_DEFAULT(Enum, Value)                  \
    static_assert(Enum::Value != Enum::Invalid,            \
                  #Enum ": default cannot equal invalid"); \
    template<>                                             \
    constexpr Enum find_default<Enum>() { return Enum::Value; }

Usage:

    static_assert(find_default<Channel>() == +Channel::Red, "");
    static_assert(find_default<Compression>() == +Compression::None, "");

And, if you do

    ENUM(Answer, int, Yes, No, Invalid)
    // OVERRIDE_DEFAULT(Answer, Invalid)

you will get a helpful compile-time error saying
`Answer: default cannot equal invalid`.

### Making the syntax nicer

For the final touch, we will make the syntax better by introducing new
"keywords" called `default_` and `invalid` in such a way that we cause the
compiler to do type inference:

    template <typename Enum>
    struct assert_enum {
        using check = typename Enum::_enumerated;
        using type = Enum;
    };

    struct invalid_t {
        template <typename To>
        constexpr operator To() const { return find_invalid<To>(); }

        template <typename To>
        constexpr To convert() const { return find_invalid<To>(); }
    };

    struct default_t {
        template <typename To>
        constexpr operator To() const { return find_default<To>(); }
    };

    constexpr invalid_t     invalid{};
    constexpr default_t     default_{};

    static_assert(+Channel::Invalid == invalid, "");
    static_assert(+Compression::Undefined == invalid, "");

    static_assert(+Channel::Red == default_, "");
    static_assert(+Compression::None == default_, "");

We can now have nice code such as this:

    int main()
    {
        Channel     channel = default_;
        std::cout << channel._to_string() << std::endl;

        return 0;
    }

---

There are many possible variations of these policies, but I think most of them
can be encoded in a reasonable fashion using the tools Better Enums provides.
Enjoy!
