## Iteration

Better Enums makes it easy to iterate over the values you have declared. For
example, this:

    #include <iostream>
    #include <enum.h>

    <em>BETTER_ENUM(Channel, int, Red, Green = 2, Blue)</em>

    int main()
    {

        <em>for</em> (<em>size_t index = 0</em>; <em>index < Channel::_size()</em>; <em>++index</em>) {
            Channel     channel = <em>Channel::_values()[index]</em>;
            std::cout << channel._to_integral() << " ";
        }
        std::cout << std::endl;

will print "0 2 3". And this:

        <em>for</em> (<em>size_t index = 0</em>; <em>index < Channel::_size()</em>; <em>++index</em>) {
            const char  *name = <em>Channel::_names()[index]</em>;
            std::cout << name << " ";
        }
        std::cout << std::endl;

will print "Red Green Blue".

---

If you are using $cxx11, you can have much nicer syntax:

~~~comment
    <em>for (Channel channel : Channel::_values())</em>
        std::cout << <em>channel._to_integral()</em> << " ";
    std::cout << std::endl;

    <em>for (const char *name : Channel::_names())</em>
        std::cout << <em>name</em> << " ";
    std::cout << std::endl;
~~~

---

        return 0;
    }

%% description = Using Better Enums to iterate over all the constants of an
enum, as well as over its names. Also shows the same with C++11 for-each syntax.
