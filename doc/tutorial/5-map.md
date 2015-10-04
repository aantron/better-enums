## Maps

It is possible to create `constexpr` bidirectional maps between Better Enums and
any type. This is currently an experimental feature. Feedback is very much
wanted, but please don't build any mission-critical code on top of this :)

The way it works is you give Better Enums a function &mdash; say,
`const char* describe(Channel)`. The library enumerates it to make a map.

The reason for using a function is that a `switch` statement is, I believe, the
only place where a compiler will check for exhaustiveness. If you forget to
create a case for one of the enum's constants, the compiler can let you know.
Obviously, a `switch` statement is not data, and needs to be inside a function.
It can only be inside a `constexpr` function in $cxx14, so this feature is most
natural in $cxx14. When you pass the function to Better Enums, the library can
build up a lookup data structure at compile time.

Actually, right now, Better Enums doesn't quite do that &mdash; it enumerates
the function *every* time you want to convert to an enum (but not *from* an
enum). It simply does a linear scan every time. This is because I haven't yet
found a data structure whose compile-time generation is fast enough for
practical use.

---

    #include <iostream>
    <em>#include</em> <<em>enum.h</em>>

    <em>BETTER_ENUM</em>(<em>Channel</em>, <em>int</em>, <em>Red</em>, <em>Green</em>, <em>Blue</em>)

We will create a map from this function:

    constexpr <em>const char* describe</em>(<em>Channel channel</em>)
    {
        switch(<em>channel</em>) {
            case <em>Channel::Red</em>:   return <em>"the red channel"</em>;
            case <em>Channel::Green</em>: return <em>"the green channel"</em>;
            case <em>Channel::Blue</em>:  return <em>"the blue channel"</em>;
        }

        return "needed for gcc 5";
    }

Here is the map. The actual type is `better_enums::map<Channel, const char*>`.

    constexpr auto <em>descriptions</em> = <em>better_enums::make_map</em>(<em>describe</em>);

And the usage:

    int main()
    {
        std::cout << <em>descriptions[Channel::Red]</em> << std::endl;

        std::cout << <em>descriptions</em>.<em>from_enum</em>(<em>Channel::Red</em>) << std::endl;
        std::cout << <em>descriptions</em>.<em>to_enum</em>(<em>"the green channel"</em>) << std::endl;

        auto <em>not_a_literal</em> = <em>std::string</em>(<em>"the blue channel"</em>);
        std::cout << <em>descriptions</em>.<em>to_enum</em>(<em>not_a_literal</em>.<em>c_str()</em>) << std::endl;

        return 0;
    }

---

`make_map` above produces a value of type `better_enums::map<E, T>`. The full
signature of the template `better_enums::map` is

~~~comment
<em>template <typename Enum, typename T, typename Compare = map_compare<T>></em>
~~~

`Compare` has to be a class with a static member function
`bool less(const T&, const T&)`. The default implementation
`better_enums::map_compare` simply applies `operator <`, except when `T` is
`const char*`. In that case, it does lexicographic comparison.

%% description = Mapping enums to arbitrary types and vice versa.
