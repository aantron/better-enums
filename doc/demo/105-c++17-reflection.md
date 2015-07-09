## C++17 reflection

Better Enums can be used to approximately implement the enums portion of the
[$cxx17 reflection proposal N4428][n4428] in $cxx11. The implementation is
*approximate* in the following senses:

- It only applies to Better Enums, not built-in enums.
- `enum_traits<E>::enumerators::get<I>::identifier` is a non-`constexpr`
  function rather than a `constexpr` variable. I could make it a `constexpr`
  variable as in the proposal, but that requires
  [compile-time name trimming][slow-enum] to be enabled for the Better Enum
  on which `get` is used. Since that's an opt-in feature, I can't guarantee it.
  I preferred not to write feature-detection code, in order to keep the
  implementation simple.
- The return type of `identifier` is `const char*` instead of the proposed
  `std::string_literal`, because I don't have an implementation of the latter
  available. I'm also ignoring the requirements on encoding, and just taking
  whatever the preprocessor provides.

With that out of the way, we can look at a simple example.

[n4428]: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4428.pdf
[slow-enum]: ${prefix}OptInFeatures.html#CompileTimeNameTrimming

---

The implementation is defined in [`extra/better-enums/n4428.h`][header]. Let's
assume that `extra/` has been added as a directory to search for include files.

    #include <iostream>
    <em>#include</em> <<em>enum.h</em>>
    <em>#include</em> <<em>better-enums/n4428.h</em>>

[header]: https://github.com/aantron/better-enums/blob/$ref/extra/better-enums/n4428.h

---

Let's declare an enum:

    <em>ENUM</em>(<em>Channel</em>, <em>char</em>, <em>Red</em> = <em>1</em>, <em>Green</em>, <em>Blue</em>)

N4428 proposes three `constexpr` traits, of which we have two implemented
exactly &mdash; that is, as `constexpr`:

    <em>constexpr std::size_t   size</em> =
        <em>std</em>::<em>enum_traits</em><<em>Channel</em>>::<em>enumerators</em>::<em>size</em>;

    <em>constexpr Channel       value_0</em> =
        <em>std</em>::<em>enum_traits</em><<em>Channel</em>>::<em>enumerators</em>::<em>get</em><<em>0</em>>::<em>value</em>;
    <em>constexpr Channel       value_1</em> =
        <em>std</em>::<em>enum_traits</em><<em>Channel</em>>::<em>enumerators</em>::<em>get</em><<em>1</em>>::<em>value</em>;

Let's check the results:

    static_assert(<em>size</em> == <em>3</em>, "");

    static_assert(<em>value_0</em> == +<em>Channel::Red</em>, "");
    static_assert(<em>value_1</em> == +<em>Channel::Green</em>, "");

Finally, we can try using `identifier`:

    int main()
    {
        std::cout
            << <em>std</em>::<em>enum_traits</em><<em>Channel</em>>::<em>enumerators</em>::<em>get</em><<em>2</em>>::<em>identifier</em>()
            << std::endl;

        return 0;
    }

That prints `Blue`, as you would expect.

%% description = Approximate implementation of N4428 enum reflection based on
Better Enums.
