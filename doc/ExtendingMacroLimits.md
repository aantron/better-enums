## Extending macro limits

The `ENUM` macro makes heavy use of the preprocessor. The preprocessor can't
perform intelligent operations on sequences of tokens with arbitrary lengths
&mdash; the operations must be bounded. The result is that there are two size
limits: on the number of constants that a Better Enum can have, and on the
maximum length of a constant name under certain conditions. If you run into
either of these limits, follow the steps on this page to increase them.

The conditions for the constant name length limit rarely apply. They are:

  - you are compiling an enum with compile-time string trimming, a.k.a. a
    "slow enum", which is only enabled when you do [this](), and
  - you have a constant with an initializer.

Constants without initializers can always have arbitrarily-long names.

The default limits are 64 constants and 23 characters for names of slow enum
constants that have initializers. To extend these limits:

  1. Pick your desired limits. I will use 512 constants and 63 characters as an
     example. Add 1 to the number of characters to account for the null
     terminator &mdash; our numbers are now 512 and 64.
  2. Get `make_macros.py` from your copy of the Better Enums distribution or
     from [GitHub]().
  3. You will run this script to generate a header file containing some
     replacement macros for `enum.h` to use. Pick a name for this file and a
     location somewhere in your include path. I will assume that this file is
     `common/enum_macros.h`.
  4. Run `python make_macros.py 512 64 > common/enum_macros.h`.
  5. Define `BETTER_ENUMS_MACRO_FILE <common/enum_macros.h>` before including
     `enum.h`. This is typically done by supplying extra flags to the compiler
     on the command line:

     - For g++ and clang++, `-DBETTER_ENUMS_MACRO_FILE='<common/enum_macros.h>'`
     - For VC++, `\DBETTER_ENUMS_MACRO_FILE='<common/enum_macros.h>'`

  6. Enjoy the looser limits. Just watch out &mdash; increasing the second
     number can really slow down compilation of compile-time trimming enums.
  7. You don't need `make_macros.py` anymore. It's not part of your build
     process and you can delete it.
