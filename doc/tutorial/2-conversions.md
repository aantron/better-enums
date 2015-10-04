## Conversions

Let's begin by including `enum.h` and declaring our enum:

    #include <cassert>
    #include <iostream>

    <em>#include <enum.h></em>

    <em>BETTER_ENUM</em>(<em>Channel</em>, <em>int</em>, <em>Cyan</em> = <em>1</em>, <em>Magenta</em>, <em>Yellow</em>, <em>Black</em>)

We now have an `int`-sized enum with four constants.

There are three groups of conversion functions: for strings, case-insensitive
strings, and integers. They all follow the same pattern, so I'll explain the
string functions in detail, and the rest can be understood by analogy.

$internal_toc

### Strings

There are three functions:

  1. `._to_string`
  2. `::_from_string`
  3. `::_from_string_nothrow`


    int main()
    {
        <em>Channel     channel = Channel::Cyan</em>;
        std::cout << <em>channel._to_string()</em> << " ";

As you'd expect, the code above prints "Cyan".

If `channel` is invalid &mdash; for example, if you simply cast the number "42"
to `Channel` &mdash; then the result of `to_string` is undefined.

---

        channel = <em>Channel::_from_string("Magenta")</em>;
        std::cout << channel._to_string() << " ";

This is also straightforward. If you pass a string which is not the name of a
declared value, `_from_string` throws `std::runtime_error`.

---

If you don't want an exception, there is `_from_string_nothrow`:

        <em>better_enums::optional<Channel></em> maybe_channel =
            <em>Channel::_from_string_nothrow("Yellow")</em>;

        if (<em>!maybe_channel</em>)
            std::cout << "error";
        else
            std::cout << <em>maybe_channel-></em>_to_string() << " ";

This returns an *optional value*, in the style of
[`boost::optional`](http://www.boost.org/doc/libs/1_58_0/libs/optional/doc/html/index.html)
or the proposed
[`std::optional`](http://en.cppreference.com/w/cpp/experimental/optional).

What that means for the above code is:

  - if the conversion succeeds, `maybe_channel` converts to `true` and
    `*maybe_channel` is the converted value of type `Channel`,
  - if the conversion fails, `maybe_channel` converts to `false`.

In $cxx11, you can use `auto` to avoid writing out the optional type:

~~~comment
    <em>auto</em>        maybe_channel = <em>Channel::_from_string_nothrow("Yellow")</em>;
    if (<em>!maybe_channel</em>)
        std::cout << "error";
    else
        std::cout << <em>maybe_channel-></em>_to_string() << " ";
~~~

### Case-insensitive strings

The "`_nocase`" string conversions follow the same pattern, except for the lack
of a "`to_string_nocase`".

  1. `::_from_string_nocase`
  2. `::_from_string_nocase_nothrow`


        channel = <em>Channel::_from_string_nocase("cYaN")</em>;
        std::cout << channel._to_string() << " ";

        maybe_channel = <em>Channel::_from_string_nocase_nothrow("rEeD")</em>;
        assert(!maybe_channel);

### Integers

And, it is similar with the *representation type* `int`:

  1. `._to_integral`
  2. `::_from_integral`
  3. `::_from_integral_nothrow`
  4. `::_from_integral_unchecked`


        channel = Channel::Cyan;
        std::cout << <em>channel._to_integral()</em> << " ";

        channel = <em>Channel::_from_integral(2)</em>;
        std::cout << channel._to_string() << " ";

        maybe_channel = <em>Channel::_from_integral_nothrow(0)</em>;
        assert(<em>!maybe_channel</em>);

That prints "1 Magenta".

`_from_integral_unchecked` is a no-op unchecked cast of integers to enums, so
use it carefully.

        channel = <em>Channel::_from_integral_unchecked(0)</em>;
        // <em>Invalid</em> - better not to try converting it to string!

### Validity checking

For completeness, Better Enums also provides three validity checking functions,
one for each of the groups of conversions &mdash; string, case-insensitive
string, and integer:

        assert(<em>Channel::_is_valid(3)</em>);
        assert(<em>Channel::_is_valid("Magenta")</em>);
        assert(<em>Channel::_is_valid_nocase("cYaN")</em>);

---

Almost done.

There is one unfortunate wrinkle. You cannot convert a literal constant such as
`Channel::Cyan` directly to, for example, a string. You have to prefix it with
`+`:

        std::cout << (<em>+Channel::Cyan</em>)._to_string();

This is due to some type gymnastics in the implementation of Better Enums. The
reference has a
[full explanation](${prefix}ApiReference.html#HelperFunctionsAndTypes).

---

        std::cout << std::endl;
        return 0;
    }

%% description = Better Enums conversion functions. Converting to string, from
string, to int, from int, and validation, both case-sensitive and
case-insensitive. Exception-throwing and non-throwing variants presented.
