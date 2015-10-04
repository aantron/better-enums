## Bit sets

If you want to use `std::bitset` or a similar library to have enums be keys into
a bit set, you need to know the number of bits at compile time. You can easily
automate this with Better Enums, even when constants are not declared in
increasing order.

---

We simply need to find the maximum value of any given enum type.

    #include <bitset>
    #include <iostream>
    <em>#include <enum.h></em>

    template <<em>typename Enum</em>>
    constexpr <em>Enum max_loop</em>(Enum accumulator, size_t index)
    {
        return
            <em>index >= Enum::_size() ? accumulator :
            Enum::_values()[index] > accumulator ?
                max_loop<Enum>(Enum::_values()[index], index + 1) :
                max_loop<Enum>(accumulator, index + 1)</em>;
    }

    template <<em>typename Enum</em>>
    constexpr <em>Enum max</em>()
    {
        return <em>max_loop<Enum>(Enum::_values()[0], 1)</em>;
    }

And use that to declare a bit set template:

    template <<em>typename Enum</em>>
    using <em>EnumSet</em> = <em>std::bitset</em><<em>max<Enum>()._to_integral()</em> + <em>1</em>>;

Now, we can have bit sets that are wide enough to hold whatever range we
declared. We just declare enums, and the numeric values of their constants will
be bit indices. The rest is straightforward.

    BETTER_ENUM(<em>EFLAGS</em>, int,
                <em>Carry</em>, <em>Parity</em> = 2, <em>Adjust</em> = 4, <em>Zero</em>, <em>Sign</em>, <em>Trap</em>, <em>Interrupt</em>, <em>Direction</em>,
                <em>Overflow</em>, <em>NestedTask</em> = 14, <em>Resume</em> = 16, <em>V8086</em>, <em>AlignmentCheck</em>,
                <em>CPUIDPresent</em> = 21)

    int main()
    {
        <em>EnumSet</em><<em>EFLAGS</em>>     eflags = <em>1 << EFLAGS::Carry</em> | <em>1 << EFLAGS::Zero</em>;

        if (eflags.test(<em>EFLAGS::Carry</em>))
            eflags.set(<em>EFLAGS::Trap</em>);

        std::cout << <em>eflags</em> << std::endl;

        return 0;
    }

---

If we want bit sets of fixed known width instead, we can use the code above to
check that we haven't declared any bit indices out of range:

~~~comment
static_assert(max<EFLAGS>()._to_integral() < 32,
              "some bit indices are out of range");
~~~

%% description = Finding the maximum value of a Better Enum for use in declaring
statically-sized bit set types.
