## API reference

$internal_toc

### Overview

The declaration

    #include <enum.h>
    <em>BETTER_ENUM</em>(<em>Enum</em>, <em>underlying_type</em>, <em>A</em>, <em>B</em>, <em>C</em>, ...)

generates a new class type `Enum` which is notionally similar to the type
created by this $cxx11 declaration:

~~~comment
<em>enum class Enum</em> : <em>underlying_type</em> {<em>A</em>, <em>B</em>, <em>C</em>, ...};
~~~

That is, `Enum` is a scoped enumerated type with constants `Enum::A`, `Enum::B`,
`Enum::C`, and so on, with memory representation the same as `underlying_type`.
It is possible to supply initializers for any of the constants:

    <em>BETTER_ENUM</em>(Enum, underlying_type, <em>A</em> = <em>1</em>, <em>B</em> = <em>constant_expression</em>, <em>C</em> = <em>A</em>, ...)

The initializers have the same meaning and constraints as in a built-in `enum`
or `enum class` declaration.

---

The principal differences between the types declared by the `BETTER_ENUM` macro
and `enum class` are:

  - `BETTER_ENUM` is available for $cxx98
    [compilers](${prefix}CompilerSupport.html) supporting `__VA_ARGS__` &mdash;
    all major compilers &mdash; while `enum class` is restricted to $cxx11,
  - the `BETTER_ENUM` type is implicitly convertible to integral types, though
    this can be [disabled](${prefix}OptInFeatures.html#StrictConversions) when
    using $cxx11, and
  - the `BETTER_ENUM` type supports a set of reflective operations, detailed in
    the rest of this reference.

---

The types produced by the `BETTER_ENUM` macro are called *Better Enums* in the
rest of this reference.

Better Enums are similar to their underlying type for the purposes of argument
passing. This means that they typically fit into a machine word, and should be
passed by value.

All names declared in the scope of a Better Enum are prefixed with an underscore
in order to avoid conflicts with potential constant names.



### Running example

The rest of this reference uses the following declaration as a running example:

    <em>BETTER_ENUM</em>(<em>Enum</em>, <em>int</em>, <em>A</em>, <em>B</em>, <em>C</em>)



### Helper functions and types

The types and functions described here make it possible to use Better Enums with
the rest of $cxx in a reasonable fashion, or else they are referenced in the
rest of the documentation.

#### <em>typedef _enumerated</em>

An internal type used to declare constants. The `BETTER_ENUM` macro generates
something similar to

~~~comment
<em>struct Enum</em> {
    <em>enum _enumerated</em> : <em>int</em> {<em>A</em>, <em>B</em>, <em>C</em>};
    // ...
};
~~~

The user needs to be aware of `_enumerated` in only one situation. A literal
constant such as `Enum::A` is an expression of type `Enum::_enumerated`, not
`Enum`. It is not possible to directly call a method on the constant, as in
`Enum::A._to_string()`. This problem is addressed by operator `+`
[below](#Operator+).

#### non-member constexpr Enum unary <em>operator +</em>(_enumerated)

Forces promotion of [`Enum::_enumerated`](#Typedef_enumerated) to `Enum`.
Provided to solve the problem described [above](#Typedef_enumerated). So:

    // Does not compile
    <em>Enum::A</em>.<em>_to_string</em>()

    // Compiles
    (<em>+Enum::A</em>).<em>_to_string</em>()

#### constexpr implicit <em>constructor Enum(_enumerated)</em>

A constructor that performs implicit conversions of
[`Enum::_enumerated`](#Typedef_enumerated) to `Enum`. This allows code to use a
literal constant where `Enum` is expected, and the compiler can do an implicit
conversion. For example:

    void <em>do_something</em>(<em>Enum value</em>);

    do_something(<em>+Enum::A</em>);  // Not necessary
    do_something(<em>Enum::A</em>);   // Implicit conversion available

    <em>Enum value</em> = <em>Enum::A</em>;    // Implicit conversion

The other constructors of `Enum` are the implicitly-generated copy and move
constructors. There is no default constructor. If you have comments on what a
default constructor should do, please [let me know](${prefix}Contact.html).

#### non-member <em>struct better_enums::optional</em>&lt;Enum&gt;

An optional `Enum` value. These are returned by the various `_nothrow`
functions, such as [`_from_string_nothrow`](#_from_string_nothrow). This type is
meant to represent the possibility of failure. For example, suppose you have:

    <em>better_enums::optional</em>&lt;<em>Enum</em>&gt;    <em>maybe</em> = <em>_from_string_nothrow</em>(<em>"A"</em>);

An optional value such as `maybe` is convertible to `bool`. If it converts to
`true`, it holds a valid `Enum` value. Otherwise, if it converts to `false`, the
operation that produced the optional value failed. So, you can continue with

    <em>if</em> (<em>maybe</em>) {
        // The string conversion succeeded
        do_something(<em>*maybe</em>);
    }
    <em>else</em> {
        // The string conversion failed
    }

As you can see, `*maybe` evaluates to the `Enum` value, in this case `Enum::A`.

The rest of this reference refers to this type as simply `optional`, as if you
had entered

~~~comment
using <em>optional</em> = <em>better_enums::optional</em>&lt;<em>Enum</em>&gt;;
~~~



### Value count and iteration

The types and members described here have to do with the sequence of constants
declared, i.e. `A`, `B`, `C` in the [running example](#RunningExample).

#### static constexpr size_t <em>_size</em>()

The number of constants declared. `Enum::_size() == 3`.

#### static constexpr const size_t <em>_size_constant</em>

Same as [`_size`](#_size), but a constant instead of a function. This is
provided for use in $cxx98 constant expressions.

#### <em>typedef _value_iterable</em>

Type of object that permits iteration over the constants. Has at least
`constexpr` `begin()`, `end()`, and `size()` methods, and `constexpr`
`operator[]`. Iteration visits each *declared* constant, even if multiple
constants have the same value, and visits them in order of declaration. See
usage examples under [`_values`](#_values).

#### <em>typedef _value_iterator</em>

Random-access iterator type for [`_value_iterable`](#_value_iterable). Most
operations, including dereferencing, are `constexpr`. The exceptions are
mutating operators such as `operator++`. In `constexpr` code, that can be
replaced with addition of `1`. You typically don't have to refer to this type
directly.

#### static constexpr _value_iterable <em>_values</em>()

`constexpr` access to the sequence of declared constants. For example:

    <em>for</em> (size_t index = 0; <em>index</em> < <em>Enum::_values().size()</em>; ++index)
        do_something(<em>Enum::_values()[index]</em>);

or, using iterators:

    <em>for</em> (Enum::_value_iterator iterator = <em>Enum::_values().begin()</em>;
         iterator != <em>Enum::_values().end()</em>; ++iterator) {

        do_something(<em>*iterator</em>);
    }

or, in $cxx11:

    <em>for</em> (Enum value : <em>Enum::_values()</em>)
        do_something(<em>value</em>);



### String conversion and iteration

#### member constexpr? const char* <em>_to_string</em>() const

Returns the string representation a Better Enum value. For example:

    Enum    value = <em>Enum::A</em>;
    value.<em>_to_string</em>();     // Same as "A".

If two or more constants have the same numeric value, it is undefined which name
`_to_string` will choose, but it will choose one of them.

If `value` is not equal to the representation of any declared constant, for
example if it was obtained using an unchecked conversion such as

    Enum    value = <em>Enum::_from_integral_unchecked</em>(<em>0xbadc0de</em>);

then the behavior of `value._to_string` is undefined.

Running time is linear in the number of declared constants.

This method is not `constexpr` by default. Read
[here](${prefix}OptInFeatures.html#CompileTimeNameTrimming) for information
about making it `constexpr`.

#### static constexpr Enum <em>_from_string</em>(const char*)

If the given string is the exact name of a declared constant, returns the
constant. Otherwise, throws `std::runtime_error`. Running time is linear in the
number of declared constants multiplied by the length of the longest constant.

#### static constexpr optional<Enum> <em>_from_string_nothrow</em>(const char*)

Same as [`_from_string`](#_from_string), but does not throw an exception on
failure. Returns an [optional value](#StructBetter_enumsoptional) instead.

#### static constexpr Enum <em>_from_string_nocase</em>(const char*)

Same as [`_from_string`](#_from_string), but comparison is up to case, in the
usual sense in the Latin-1 encoding.

#### static constexpr optional<Enum> <em>_from_string_nocase_nothrow</em>(const char*)

Is to [`_from_string_nocase`](#_from_string_nocase) as
[`_from_string_nothrow`](#_from_string_nothrow) is to
[`_from_string`](#_from_string).

#### static constexpr bool <em>_is_valid(const char*)</em>

Evaluates to `true` if and only if the given string is the exact name of a
declared constant. Running time is the same as for
[`_from_string`](#_from_string).

#### static constexpr bool <em>_is_valid_nocase</em>(const char*)

The same as [`_is_valid`](#_is_validconstChar*), but comparison is done up to
case as in [`_from_string_nocase`](#_from_string_nocase).

#### static constexpr const char* <em>_name</em>()

Evaluates to the name of the Better Enum type. `Enum::_name()` is the same
string as `"Enum"`.

#### <em>typedef _name_iterable</em>

Type of object that permits iteration over names of declared constants. Has at
least `constexpr` `begin()`, `end()`, and `size()` methods. `operator[]` is also
available, but is `constexpr` if and only if [`_to_string`](#_to_string) is
`constexpr`. Iteration visits constants in order of declaration. See usage
example under [`_names`](#_names).

#### <em>typedef _name_iterator</em>

Random-access iterator type for `_name_iterable`. Most operations are
`constexpr`, but dereferencing is `constexpr` if and only if
[`_to_string`](#_to_string) is `constexpr`. Mutating operators such as
`operator++` are not `constexpr` due to their nature &mdash; adding `1` is a
`constexpr` alternative. You typically don't have to refer to this type
directly.

#### static constexpr? _name_iterable <em>_names</em>()

Access to the sequence of declared constant names. For example:

    <em>for</em> (size_t index = 0; <em>index</em> < <em>Enum::_names().size()</em>; ++index)
        std::cout << <em>Enum::_names()[index]</em> << std::endl;

or, using iterators:

    <em>for</em> (Enum::_name_iterator iterator = <em>Enum::_names().begin()</em>;
         iterator != <em>Enum::_names().end()</em>; ++iterator) {

        std::cout << <em>*iterator</em> << std::endl;
    }

or, in $cxx11:

    <em>for</em> (const char *name : <em>Enum::_names()</em>)
        std::cout << <em>name</em> << std::endl;

`constexpr` if and only if [`_to_string`](#_to_string) is `constexpr`.



### Integer conversion

Better Enums are already represented as integers at run time. Values of the
[running example](#RunningExample) type `Enum` are the same as `ints`. However,
`Enum` is a distinct type from `int` during type checking, the main difference
being that its range of valid values is restricted to only the ones you have
declared.

This section describes the various translations between `Enum` and `int` that
are available. Each one translates the type, but at run time, most are no-ops,
or validity checks followed by no-ops.

#### <em>typedef _integral</em>

The *underlying* or *representation* type of the Better Enum. For example,
`Enum::_integral` is the same type as `int`. Each Better Enum has the same size
and alignment requirement as its representation type.

#### member constexpr _integral <em>_to_integral</em>() const

No-op conversion of a Better Enum to a value of its representation type. For
example,

    (+<em>Enum::C</em>)<em>._to_integral</em>() == <em>2</em>

Note that Better Enums are already implicitly convertible to their underlying
integral types [by default](${prefix}OptInFeatures.html#StrictConversions).
You may still want to use this function, however, for clarity, and to ensure
that your code remains compatible if the strict conversions feature is enabled
later.

#### static constexpr Enum <em>_from_integral</em>(_integral)

Checked conversion of an integer to a Better Enum value. The check runs in time
linear in the number of declared constants, but the conversion itself is a
no-op. Throws `std::runtime_error` if the given integer is not the numeric value
of one of the declared constants.

    <em>Enum::_from_integral</em>(<em>2</em>);    // Enum::C
    <em>Enum::_from_integral</em>(<em>42</em>);   // std::runtime_error

#### static constexpr optional<Enum> <em>_from_integral_nothrow</em>(_integral)

Checked conversion as [`_from_integral`](#_from_integral), but does not throw an
exception on failure. Returns an [optional value](#StructBetter_enumsoptional)
instead.

#### static constexpr Enum <em>_from_integral_unchecked</em>(_integral)

No-op unchecked conversion of an integer to a Better Enum value. If the given
integer is not the numeric value of one of the declared constants, the behavior
of all subsequent operations on the Better Enum value is undefined.

This is the direct inverse of [`_to_integral`](#_to_integral). Here are no-op
round trips between `int` and `Enum`:

    <em>Enum::_from_integral_unchecked</em>(value.<em>_to_integral</em>());
    <em>Enum::_from_integral_unchecked</em>(integer).<em>_to_integral</em>();

You should not use this function on untrusted input, however.

#### static constexpr bool <em>_is_valid(_integral)</em>

Evaluates to `true` if and only if the given integer is the numeric value of one
of the declared constants. Running time is linear in the number of declared
constants.



### Stream operators

#### non-member std::ostream& <em>operator <<</em>(std::ostream&, const Enum&)

Formats the given enum to the given stream in the same way as
[`_to_string`](#_to_string).

#### non-member std::istream& <em>operator >></em>(std::istream&, Enum&)

Reads from the given stream and attempts to parse an enum value in the same way
as [`_from_string`](#_from_string). In case of failure, sets the stream's
`failbit`.



%% class = api

%% description = Detailed description of the Better Enums API.
