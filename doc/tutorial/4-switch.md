## Safe switch

A Better Enum can be used directly in a `switch` statement:

    #include <iostream>
    <em>#include <enum.h></em>

    <em>BETTER_ENUM(Channel, int, Red, Green, Blue)</em>

    int main()
    {
        Channel     channel = Channel::Green;
        int         n;

        <em>switch </em>(<em>channel</em>) {
            <em>case Channel::Red</em>:   n = 13; break;
            <em>case Channel::Green</em>: n = 37; break;
            <em>case Channel::Blue</em>:  n = 42; break;
        }

If you miss a case or add a redundant one, your compiler should be able to give
you a warning &mdash; try it!

---

        std::cout << n << std::endl;
        return 0;
    }

%% description = Better Enums can be used directly in switch statements like
normal enums, making it possible for the compiler to check that all cases are
listed, increasing the safety of your code.
