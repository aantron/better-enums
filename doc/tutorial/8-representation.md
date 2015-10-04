## Representation

Let's go over some of the low-level properties of a Better Enum. This time, we
will declare a more unusual enum than the ones we have seen.

    #include <cassert>
    #include <iostream>
    <em>#include <enum.h></em>

    <em>BETTER_ENUM</em>(<em>ContentType</em>, <em>short</em>,
         <em>CompressedVideo</em> = <em>5</em>, <em>PCM</em> = <em>8</em>, <em>Subtitles</em> = <em>17</em>, <em>Comment</em> = <em>44</em>)

This is for a hypothetical multimedia container file format. Perhaps the files
have sections, and each one has a header:

    <em>struct Header</em> {
        <em>ContentType     type</em>;
        short           flags;
        int             offset;
    };

---

Here is what we have.

    int main()
    {
        assert(<em>sizeof(ContentType)</em> == <em>2</em>);

`ContentType` behaves just like a `short`[^*], in fact it simply wraps one. This
makes it possible to lay out structures in a predictable fashion:

        Header      <em>header</em> = {ContentType::PCM, 0, 0};

        assert(<em>sizeof(header)</em> == <em>8</em>);
        assert((size_t)&<em>header.flags -</em> (size_t)&<em>header.type</em> == <em>2</em>);

---

`uint16_t` is called `ContentType`'s *underlying* or *representation* type. If
you want to know the representation type of any enum you have declared, it is
available as the member type `::_integral`:

        <em>ContentType::_integral</em>  untrusted_value = 44;

Use this if you want a sized field to receive untrusted data, but aren't willing
to call it `ContentType` yet because you have not validated it. Your validator
will likely call `::_from_integral_nothrow`, perform any other validation your
application requires, and then return `ContentType`.

        ContentType             type =
            ContentType::_from_integral(untrusted_value);
        std::cout << type._to_string() << std::endl;

---

You have probably noticed the initializers on each of the constants in
`ContentType`. This allows you to declare sparse enums for compatibility with
external protocols or previous versions of your software. The initializers don't
need to be literal integers &mdash; they can be anything that the compiler would
accept in a normal `enum` declaration. If there was a macro called
`BIG_FAT_MACRO` declared above, we could have written
`Subtitles = BIG_FAT_MACRO`. We could also have written
`Subtitles = CompressedVideo`.

---

The in-memory representation of an enum value is simply the number it has been
assigned by the compiler. You should be safe passing enums to functions like
`fread` and `fwrite`, and casting memory blocks known to be safe to `struct`
types containg enums. The enums will behave as expected.

---

        return 0;
    }

[^*]: It should properly be a `uint16_t`, and the rest of the header fields
      should also be explicitly sized. However, this code is trying to be
      compatible with $cxx98, where those names aren't available in a portable
      manner.

%% description = The underlying memory representation of a Better Enum,
including size and alignment.
