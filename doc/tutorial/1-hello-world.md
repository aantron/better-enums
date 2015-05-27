## Hello, World!

Download <a $download>enum.h</a>, then build this program with it:

    #include <iostream>
    <em>#include "enum.h"</em>

    <em>ENUM(Word, int, Hello, World)</em>

    int main()
    {
        std::cout << <em>(+Word::Hello)._to_string()</em> << ", "
                  << <em>(+Word::World)._to_string()</em> << "!"
                  << std::endl;

        return 0;
    }

Run it, and you should see the output "Hello, World!"

Congratulations, you have just created your first Better Enum!
