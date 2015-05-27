## API reference

Table of contents

### Overview

The following declaration

    #include <enum.h>
    ENUM(Enum, underlying_type, A, B, C, ...);

generates a new type `Enum`. It is notionally similar to the type created by
this $cxx11 declaration:

    enum class Enum : underlying_type {A, B, C, ...};

that is, `Enum` is a scoped enumerated type with constants `Enum::A`, `Enum::B`,
`Enum::C`, and so on, with memory representation the same as `underlying_type`.
It is possible to supply initializers for any of the constants:

    ENUM(Enum, underlying_type, A = 1, B = constant_expression, C, ...);

The initializers have the same meaning and constraints as in an `enum class`
declaration.

The principal differences between the types declared by the `ENUM` macro and
`enum class` are:

  - `ENUM` is available for $cxx98 for compilers supporting `__VA_ARGS__`,
  - the `ENUM` type is implicitly convertible to integral types, though this can
    be disabled when using $cxx11, [How]() and
  - the `ENUM` type supports a set of reflective operations, detailed in the
    rest of this reference.

The types produced by the `ENUM` macro are sometimes called Better Enums in the
rest of this reference, and the running example declaration is

    ENUM(Enum, int, A, B, C);

For the purposes of argument passing, Better Enums should be thought of as
equivalent to their underlying type. This means that Better Enums are typically
integers that fit into a register or a stack word, and should be passed by
value.

All names declared in the scope of a Better Enum are prefixed with an underscore
in order to avoid conflicts with potential constant names.



### General

#### typedef _enumerated

An internal type used to declare constants. `ENUM` generates something similar
to

    struct Enum {
        enum _enumerated : int { A, B, C };
        // ...
    };

The user needs to be aware of this type in only one situation. A literal constant
such as `Enum::A` is an expression of type `Enum::_enumerated`, not `Enum`. It
is not possible to directly call a method on the value, as in
`Enum::A._to_string()`. This problem is addressed by operator `+` below.

#### non-member constexpr Enum unary operator +(_enumerated)

Forces promotion of `Enum::_enumerated` to `Enum`. Provided to solve the problem
described under `_enumerated` above. So, for example, it is necessary to write
`(+Enum::A)._to_string()` instead of `Enum::A._to_string`.

#### constexpr implicit constructor Enum(_enumerated)

A constructor that performs implicit conversions of `Enum::_enumerated` to
`Enum`. This allows code to use a literal constant where `Enum` is expected in
most situations &mdash; those where the compiler can do an implicit conversion.
For example, if there is a function `void output(Enum)`, it can be called as
`output(Enum::A)`, without having to write `output(+Enum::A)`. This constructor
is also used for the typical initialization

    Enum    value = Enum::A;

The other constructors of `Enum` are the implicitly-generated copy and move
constructors. There is no default constructor.

#### static constexpr size_t _size

The number of constants declared. `Enum::_size == 3`.

#### typedef _value_iterable

Type of object that permits iteration over the constants. Has at least
`constexpr` `begin()`, `end()`, and `size()` methods, and `operator[]`.
Iteration visits each declared constant, even if multiple constants have the
same value, and visits them in order of declaration. See usage examples under
`_values`.

#### typedef _value_iterator

Random-access iterator type for `_value_iterable`. Most operations, including
dereferencing, are `constexpr`. The exceptions are mutating operators such as
`operator++`. In `constexpr` code, that can be replaced with addition of `1`.

#### static constexpr _value_iterable _values()

`constexpr` access to the collection of declared constants. For example:

    for (size_t index = 0; index < Enum::_values().size(); ++index)
        output(Enum::_values()[index]);

or, using iterators:

    for (Enum::_value_iterator iterator = Enum::_values().begin();
         iterator != Enum::_values().end(); ++iterator) {

        output(*iterator);
    }

or, in $cxx11:

    for (Enum value : Enum::_values())
        output(value);

#### non-member struct better_enums::optional<Enum>

Optional `Enum` value. An optional value `maybe` can be in one of two states:

  - `(bool)maybe == true`, meaning that there is `Enum` value, and `*maybe`
    evaluates to it, and
  - `(bool)maybe == false`, meaning no `Enum` value is available.

This type is referred to as simply `optional` in the rest of the reference, as
if `using better_enums::optional;` has been entered.



### Strings

#### member constexpr? const char* _to_string() const

Returns the string representation of the Better Enum value on which it is
called. For example, if `value == Enum::A`, `value._to_string()` is the same
string as `"A"`.

If two constants have the same numeric representation, and `value` is equal to
one of those constants, then it has that numeric representation, and it is
undefined which constant's name `_to_string` will choose.

If `value` is not equal to the representation of any declared constant, for
example if it was obtained using an unchecked cast such as:

    Enum    value = Enum::_from_integral_unchecked(0xbadc0de);

then the behavior of `value._to_string` is undefined.

Runnig time is linear in the number of declared constants.

This method is not `constexpr` by default because making it so entails a large
slowdown during compilation. [See here]() for how to make it `constexpr` for
some or all Better Enums.

#### static constexpr Enum _from_string(const char*)

If the given string is the exact name of a declared constant, returns its value.
Otherwise, throws `std::runtime_error`. Running time is linear in the number of
declared constants multiplied by the length of the longest constant.

#### static constexpr optional<Enum> _from_string_nothrow(const char*)

The same as `_from_string`, but does not throw an exception on failure. Returns
an [optional]() value instead.

#### static constexpr Enum _from_string_nocase(const char*)

The same as `_from_string`, but comparison is up to case, in the usual sense in
the Latin-1 encoding.

#### static constexpr optional<Enum> _from_string_nocase_nothrow(const char*)

Is to `_from_string_nocase` as `_from_string_nothrow` is to `_from_string`.

#### static constexpr bool _is_valid(const char*)

Evaluates to `true` if and only if the given string is the exact name of a
declared constant. Running time is the same as for `_from_string`.

#### static constexpr bool _is_valid_nocase(const char*)

The same as `_is_valid`, but comparison is done up to case as in
`_from_string_nocase`.

#### static constexpr const char* _name()

Evaluates to the name of the Better Enum type. `Enum::_name()` is the same
string as `"Enum"`.

#### typedef _name_iterable

Type of object that permits iteration over names of declared constants. Has at
least `constexpr` `begin()`, `end()`, and `size()` methods. `operator[]` is also
available, but is `constexpr` if and only if `_to_string` is `constexpr`.
Iteration visits constants in order of declaration. See usage example under
`_names`.

#### typedef _name_iterator

Random-access iterator type for `_name_iterable`. Most operations are
`constexpr`, but dereferencing is `constexpr` if and only if `_to_string` is
`constexpr`. Mutating operators such as `operator++` are not `constexpr` due to
their nature &mdash; adding `1` is a `constexpr` alternative.

#### static constexpr? _name_iterable _names()

Access to the collection of declared constant names. For example:

    for (size_t index = 0; index < Enum::_names().size(); ++index)
        std::cout << Enum::_names()[index] << std::endl;

or, using iterators:

    for (Enum::_name_iterator iterator = Enum::_names().begin();
         iterator != Enum::_names().end(); ++iterator) {

        std::cout << *iterator << std::endl;
    }

or, in $cxx11:

    for (const char *name : Enum::_names())
        std::cout << name << std::endl;

`constexpr` if and only if `_to_string` is `constexpr`.



### Integers

#### typedef _integral

The *underlying* or *representation* type of the Better Enum. For example,
`Enum::_integral` is the same type as `int`. Each Better Enum has the same size
and alignment requirement as its representation type. This is true even under
$cxx98.

#### member constexpr _integral _to_integral() const

No-op conversion of a Better Enum to a value of its representation type. For
example, `(+Enum::C)._to_integral() == 2`.

#### static constexpr Enum _from_integral(_integral)

Checked conversion of an integer to a Better Enum value. The check runs in time
linear in the number of declared constants, but the conversion itself is a
no-op. Throws `std::runtime_error` if the given integer is not the numeric value
of one of the declared constants.

#### static constexpr Enum _from_integral_unchecked(_integral)

No-op unchecked conversion of an integer to a Better Enum value. If the given
integer is not the numeric value of one of the declared constants, the behavior
of all subsequent operations on the Better Enum value is undefined.

#### static constexpr optional<Enum> _from_integral_nothrow(_integral)

Checked conversion as `_from_integral`, but does not throw an exception on
failure. Returns an [optional]() value instead.

#### static constexpr bool _is_valid(_integral)

Evaluates to `true if and only if the given integer is the numeric value of one
of the declared constants.
