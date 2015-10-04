## Stream operators

These work *almost* as you'd expect. First, make sure you include `iostream`
before `enum.h` in any translation unit in which you intend to use the
operators:

    #include <iostream>
    #include <enum.h>

    <em>BETTER_ENUM(Channel, int, Red, Green, Blue)</em>

    int main()
    {
        std::cout << <em>+Channel::Red</em> << std::endl;
        return 0;
    }

The thing to watch for is the `+`: without it, `Channel::Red` is a value of type
`Channel::_enumerated`, a $cxx98 enum type, so writing that to `cout` will
output an integer. `+Channel::Red`, however, is a value of type `Channel`, and
writing *that* instead will output the string `"Red"`.

Input is also supported:

~~~comment
Channel     channel = Channel::Blue;
std::cin >> channel;    // Expects input such as "Green".
~~~

---

Only `char` streams are supported for the time being.

%% description = Using Better Enums with stream input and output operators.
