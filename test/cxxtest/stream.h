#include <cxxtest/TestSuite.h>
#include <iostream>
#include <enum.h>



BETTER_ENUM(Compiler, int, GCC, Clang, MSVC)



class StreamOperatorTests : public CxxTest::TestSuite {
  public:
    void test_output()
    {
        std::stringstream   stream;

        stream << +Compiler::GCC;
        TS_ASSERT_EQUALS(strcmp(stream.str().c_str(), "GCC"), 0);
    }

    void test_input()
    {
        std::stringstream   stream("Clang");
        Compiler            compiler = Compiler::GCC;

        stream >> compiler;
        TS_ASSERT_EQUALS(compiler, +Compiler::Clang);
    }
};
