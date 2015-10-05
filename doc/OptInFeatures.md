## Opt-in features

Better Enums has two opt-in features. They are both "good," but they either hurt
compilation time or break compatibility with $cxx98, so they are disabled by
default. Read this page if you want to enable them.

$internal_toc

### Default constructors

Better Enums generate with inaccessible (private or deleted) default
constructors. This is meant to help control where in your program Better Enums
values are introduced, and thus ensure that only valid, properly initialized
enum values are ever created.

If you want Better Enums to have a default constructor, you can do something
like the following:

~~~
<em>#define</em> <em>BETTER_ENUMS_DEFAULT_CONSTRUCTOR</em>(<em>Enum</em>) \
  <em>public</em>:                                      \
    <em>Enum()</em> = <em>default</em>;

<em>#include</em> <<em>enum.h</em>>
~~~

You can put this in its own header file, and include that header file instead of
including `enum.h` directly.

### Compile-time name trimming

This makes `_to_string` and `_names` `constexpr`, i.e. "full" `constexpr` mode.
To enable this for all enums, define `BETTER_ENUMS_CONSTEXPR_TO_STRING` before
including `enum.h`. Typically, you would pass an option to your compiler to do
this.

You can also enable this feature for individual enums instead, by declaring them
using the alternative `SLOW_ENUM` macro.

The feature is disabled because it increases compilation times by a factor of
about 4. Compilation is still relatively fast &mdash; you need about a dozen
slow enums to get the same penalty as including `iostream` &mdash; but it is
a steep penalty nonetheless. I don't think most people need this feature most of
the time, so it's too high a price to pay. If I improve compilation times to the
point where compile-time name trimming can be the default, I will simply
redefine `SLOW_ENUM` as `BETTER_ENUM` and deprecate it, so your code will still
work.

### Strict conversions

This disables implicit conversions to underlying integral types. At the moment,
you can only enable this globally for all enums, by defining
`BETTER_ENUMS_STRICT_CONVERSION` before including `enum.h`.

The reason Better Enums have implicit conversions to integral types in the first
place is that in $cxx98, Better Enums have to be implicitly convertible to their
member [`_enumerated`](${prefix}ApiReference.html#Typedef_enumerated) types to
be [usable](${prefix}tutorial/SafeSwitch.html) in `switch` statements. It is
possible to avoid this in $cxx11 and convert to `enum class` types instead, but
at the cost of breaking interface compatibility with $cxx98.

  - The "weaker" incompatibility is that you could write a bunch of $cxx98 code
    that relies on implicit integer conversions, and then try to switch to
    $cxx11. The code would then fail to compile. An example where implicit
    conversions are an "advantage" is when using Better Enums as arguments to
    the methods of `std::bitset`. I could have ignored this problem by declaring
    usage of implicit integer conversions unsupported, but in light of the next
    issue, I decided not to do that.
  - The "stronger" incompatibility is a difference in how `switch` cases must be
    written. The syntaxes for the two variants, implicitly-converting and
    strict, are mutually exclusive. They differ by a `+` character.

Here they are:

    // Default variant
    <em>switch</em> (<em>channel</em>) {
        case Channel::Red:   break;
        case Channel::Green: break;
        case Channel::Blue:  break;
    }

    // Strict variant
    <em>switch</em> (<em>channel</em>) {
        case <em>+</em>Channel::Red:   break;
        case <em>+</em>Channel::Green: break;
        case <em>+</em>Channel::Blue:  break;
    }

%% description = Optional Better Enums features, disabled by default for
performance or compatibility reasons.
