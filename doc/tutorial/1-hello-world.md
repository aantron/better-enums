## Hello, World!

Download <a $download><code>enum.h</code></a>, then compile this program:

    #include <iostream>
    <em>#include "enum.h"</em>

    <em>BETTER_ENUM</em>(<em>Word</em>, <em>int</em>, <em>Hello</em>, <em>World</em>)

    int main()
    {
        std::cout << <em>(+Word::Hello)._to_string()</em> << ", "
                  << <em>(+Word::World)._to_string()</em> << "!"
                  << std::endl;

        return 0;
    }

Run it, and you should see the output "Hello, World!"

Congratulations, you have just created your first Better Enum!

%% description = Introductory Better Enums tutorial - a simple, but complete,
Hello World program.
