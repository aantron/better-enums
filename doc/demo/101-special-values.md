## Special values

Suppose your project has a convention where each enum has special *invalid* and
*default* values &mdash; for example, `Enum::Invalid` is *invalid*, and the
first valid constant is *default*. With Better Enums, you can get the compiler
to enforce the convention. At the end of this demo, we will have defined
functions and templates that allow us to write:

~~~comment
<em>Channel     channel</em> = <em>default_</em>;
<em>Channel     channel</em> = <em>invalid</em>;

void do_something(<em>Channel channel</em>);

do_something(<em>default_</em>);
do_something(<em>invalid</em>);
~~~

The compiler will compute default and invalid values automatically, but the
programmer will also be able to override the choice. Obviously, the syntax above
is very legible and maintainable &mdash; the intent is clear and your code base
will respond automatically to changes in enum definitions.

$internal_toc

### Invalid values

Let's start by defining the invalid values.

    #include <iostream>
    #include <stdexcept>
    <em>#include <enum.h></em>

Perhaps the convention is that the invalid value is usually called `Invalid`,
but not for all enums. We will encode that using a template function. The
unspecialized version will encode the default policy:

    <em>template</em> <<em>typename Enum</em>>
    constexpr <em>Enum invalid_impl</em>() { return <em>Enum::Invalid</em>; }

A macro allows us to override the invalid value by specializing the template:

    <em>#define OVERRIDE_INVALID</em>(<em>Enum</em>, <em>Value</em>)                 \
    template<>                                            \
    constexpr <em>Enum invalid_impl</em><<em>Enum</em>>() { return <em>Enum::Value</em>; }

Now, we can declare enums like these:

    BETTER_ENUM(<em>Channel</em>, int, Red, Green, Blue, <em>Invalid</em>)
    // Invalid is the invalid value by default

    BETTER_ENUM(<em>Compression</em>, int, <em>Undefined</em>, None, Huffman)
    OVERRIDE_INVALID(<em>Compression</em>, <em>Undefined</em>)

and use them:

    static_assert(<em>invalid_impl</em><<em>Channel</em>>() == +<em>Channel::Invalid</em>, "");
    static_assert(<em>invalid_impl</em><<em>Compression</em>>() == +<em>Compression::Undefined</em>, "");

This even supports enums that don't have an invalid value at all. As long as
they don't have a constant called `Invalid`, you will get a compile-time error
if you try to call `invalid_impl<>()` on them &mdash; as you probably should!

### Default values

Perhaps here the convention is the first value that is not invalid is default,
unless, again, overridden by the programmer. This can be encoded using only a
slightly more complex template function for the general case:

    <em>template</em> <<em>typename Enum</em>>
    constexpr <em>Enum default_imp</em>l()
    {
        return
            <em>Enum::_size() < 2 ?
                throw std::logic_error("enum has no valid constants") :
            Enum::_values()[0] == invalid_impl<Enum>() ?
                Enum::_values()[1] :
                Enum::_values()[0]</em>;
    }

The above code gives us the first value if it is not invalid, otherwise the
second value.

The companion macro for overriding the choice of default value is almost the
same as it was for invalid. The difference is that we do an extra sanity check
to make sure the programmer doesn't declare the invalid value to be the default.
If the sanity check fails, we produce a nice error message. Again, we are
assuming that this is dictated by policy.

    <em>#define OVERRIDE_DEFAULT</em>(<em>Enum</em>, <em>Value</em>)                  \
    static_assert(<em>Enum::Value</em> != <em>Enum::Invalid</em>,            \
                  <em>#Enum ": default cannot equal invalid"</em>); \
    template<>                                             \
    constexpr <em>Enum default_impl</em><<em>Enum</em>>() { return <em>Enum::Value</em>; }

And, as before, the usage:

    static_assert(<em>default_impl</em><<em>Channel</em>>() == +<em>Channel::Red</em>, "");
    static_assert(<em>default_impl</em><<em>Compression</em>>() == +<em>Compression::None</em>, "");

And, if you do

    BETTER_ENUM(<em>Answer</em>, int, Yes, No, <em>Invalid</em>)
    // OVERRIDE_DEFAULT(<em>Answer</em>, <em>Invalid</em>)

you will get a helpful compile-time error saying
`Answer: default cannot equal invalid`.

### Making the syntax nicer

At this point, our policy is encoded by the ugly-looking functions
`invalid_impl` and `default_impl`. We want a nicer syntax. The main reason we
don't just use these functions directly is that the compiler wouldn't infer
their template arguments from the context. For example, we would have to write
things like

~~~comment
Channel     channel = invalid_impl<Channel>();
~~~

which is unfortunate, because it results in repetition.

In this section, we introduce two global objects called `invalid` and `default_`
that will implicitly convert to any Better Enum type, and provide the invalid
or default value, respectively, when they do so. They will act as new
"keywords".

    <em>struct invalid_t</em> {
        template <<em>typename To</em>>
        constexpr <em>operator To</em>() const { return <em>invalid_impl<To>()</em>; }
    };

    <em>struct default_t</em> {
        template <<em>typename To</em>>
        constexpr <em>operator To</em>() const { return <em>default_impl<To>()</em>; }
    };

    constexpr <em>invalid_t     invalid</em>{};
    constexpr <em>default_t     default_</em>{};

As you can see, both of these provide the families of implicit conversions that
we need. Now, we can test:

    static_assert(+<em>Channel::Invalid</em> == <em>invalid</em>, "");
    static_assert(+<em>Compression::Undefined</em> == <em>invalid</em>, "");

    static_assert(+<em>Channel::Red</em> == <em>default_</em>, "");
    static_assert(+<em>Compression::None</em> == <em>default_</em>, "");

Finally, we can have nice code such as this:

    void dump(<em>Channel channel</em>)
    {
        std::cout << channel._to_string() << std::endl;
    }

    int main()
    {
        dump(<em>invalid</em>);

        <em>Channel     channel</em> = <em>default_</em>;
        dump(channel);

        return 0;
    }

---

There are many possible variations of these policies, but I think most of them
can be encoded in a reasonable fashion using the tools Better Enums provides.
Enjoy!

%% description = An example that uses Better Enums compile-time reflection to
create invalid and default values for each enum, enforced statically by the
compiler, for readability and maintainability.
