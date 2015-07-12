## Scope and safety

This tutorial shows some of the safety features of Better Enums: scope, how to
control conversions, and the lack of a default constructor.

$internal_toc

### Scope

You have probably noticed by now that Better Enums are scoped: when you declare

    #include <cassert>
    <em>#include <enum.h></em>

    <em>ENUM</em>(<em>Channel</em>, <em>int</em>, <em>Red</em> = <em>1</em>, <em>Green</em>, <em>Blue</em>)

you don't get names such as `Red` in the global namespace. Instead, you get
`Channel`, and `Red` is accessible as `Channel::Red`. This is no big deal in
$cxx11, which has `enum class`. In $cxx98, however, this typically requires
effort. Better Enums brings scope uniformly to both variants. So, despite the
above declaration, you can safely declare

    <em>ENUM</em>(<em>Node</em>, <em>char</em>, <em>Red</em>, <em>Black</em>)

and everything will work as expected.

    int main()
    {
        assert((+<em>Channel::Red</em>)._to_integral() <em>!=</em> (+<em>Node::Red</em>)._to_integral());

### Implicit conversion

A major complaint in $cxx98 is that `enums` are implicitly convertible to
integers. Unfortunately, that is also true of Better Enums, and I haven't found
a way to forbid the conversions and still have switch case checking.

Better Enums can be made as safe as `enum class` in $cxx11, however. If your
compiler supports `enum class` and you define
`BETTER_ENUMS_STRICT_CONVERSION` before including `enum.h`, the following code
will not compile:

~~~comment
    Channel     channel = Channel::Red;
    int         n = channel;
~~~

The reason this is not enabled by default is explained in the reference page on
[strict conversions](${prefix}OptInFeatures.html#StrictConversions).

### Default constructor

Better Enums don't have a default constructor, for three reasons.

  - Better Enums is a library that can't know what your application would like
    the default value to be for each enum, or whether you even want one.
  - I chose not to leave the default value undefined, because the idea is to
    encourage the convention that whenever a Better Enum exists, it has a valid
    value. This is borrowed from typed functional programming.
  - Better Enums is still under development, and this option is the most
    future-proof.

So, if you uncomment this code, the file won't compile:

~~~comment
    Channel      channel;
~~~

This may be too strict, and I may relax it in the future. In the meantime, the
solution sketched in the [special values demo](${prefix}demo/SpecialValues.html)
can replace default constructors for some purposes, and in a more flexible way.
I may eventually have the default constructor calling a template function like
the one in that demo.

---

        return 0;
    }

%% description = Better Enums type safety features and limitations.
