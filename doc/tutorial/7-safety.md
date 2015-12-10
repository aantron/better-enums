## Scope and safety

This tutorial shows some of the safety features of Better Enums: scope, how to
control conversions, and the lack of a default constructor.

On balance, Better Enums are in one way less type-safe than enum class, and in
another way more type-safe. The first difference in safety is the presence of
implicit conversion to integral types. The second difference is the lack of a
default constructor. Both of these can be toggled, so you can make Better Enums
strictly safer than enum class, or just as safe.

$internal_toc

### Scope

You have probably noticed by now that Better Enums are scoped: when you declare

    #include <cassert>
    <em>#include <enum.h></em>

    <em>BETTER_ENUM</em>(<em>Channel</em>, <em>int</em>, <em>Red</em> = <em>1</em>, <em>Green</em>, <em>Blue</em>)

you don't get names such as `Red` in the global namespace. Instead, you get
`Channel`, and `Red` is accessible as `Channel::Red`. This is no big deal in
$cxx11, which has `enum class`. In $cxx98, however, this typically requires
effort. Better Enums brings scope uniformly to both variants. So, despite the
above declaration, you can safely declare

    <em>BETTER_ENUM</em>(<em>Node</em>, <em>char</em>, <em>Red</em>, <em>Black</em>)

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

You can conveniently define the macro on your compiler's command line, or by
creating a little header file that defines it, and then includes
<code>enum.h</code>. You can then include this new header file in your project
everywhere where you would have included <code>enum.h</code>.

### Default constructor

Better Enums generate without a default constructor. The purpose is to support
the convention where if a Better Enum exists, then it has a valid value. So, if
you uncomment this code, the program won't compile:

~~~comment
    Channel      channel;
~~~

If this is too strict for your project, you can relax it as described
[here](${prefix}OptInFeatures.html#DefaultConstructors).

---

        return 0;
    }

%% description = Better Enums type safety features and limitations.
