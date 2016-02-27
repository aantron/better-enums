# Invoked automatically by the Makefile.

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project("Better Enums Testing" CXX)


# Detect compiler feature support.

list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_constexpr CONSTEXPR_INDEX)
if(CONSTEXPR_INDEX EQUAL -1)
    set(SUPPORTS_CONSTEXPR 0)
else()
    set(SUPPORTS_CONSTEXPR 1)
endif()

list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_relaxed_constexpr
     RELAXED_CONSTEXPR_INDEX)
if(RELAXED_CONSTEXPR_INDEX EQUAL -1)
    set(SUPPORTS_RELAXED_CONSTEXPR 0)
else()
    set(SUPPORTS_RELAXED_CONSTEXPR 1)
endif()

# Current versions of CMake report VS2015 as supporting constexpr. However, the
# support is too buggy to build Better Enums. Avoid trying to build constexpr
# configurations on MSVC.
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(SUPPORTS_CONSTEXPR 0)
    set(SUPPORTS_RELAXED_CONSTEXPR 0)
endif()

list(FIND CMAKE_CXX_COMPILE_FEATURES cxx_strong_enums ENUM_CLASS_INDEX)
if(ENUM_CLASS_INDEX EQUAL -1)
    set(SUPPORTS_ENUM_CLASS 0)
else()
    set(SUPPORTS_ENUM_CLASS 1)
endif()

# Not supporting C++11 usage on g++46 due to buggy constexpr.

if(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.7)
    set(SUPPORTS_CONSTEXPR 0)
    set(SUPPORTS_ENUM_CLASS 0)
endif()

# Not supporting C++14 testing on clang++34 due to buggy library installed in
# Travis Ubuntu image.

if(CMAKE_CXX_COMPILER_ID STREQUAL Clang
   AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.5)
    set(SUPPORTS_RELAXED_CONSTEXPR 0)
endif()


# Select standard based on the requested configuration. If the compiler does not
# support the requested configuration, write a message and generate a no-op
# build. This condition is not a failure.
#
# If no configuration is explicitly requested, default to compiling with no
# special flags, with the latest standard supported by the compiler.

set(DO_NOT_TEST_FILE "${CMAKE_BINARY_DIR}/do-not-test")

if(CONFIGURATION STREQUAL CONSTEXPR)
    if(SUPPORTS_CONSTEXPR)
        set(CMAKE_CXX_STANDARD 11)
    else()
        message(WARNING "This compiler does not support constexpr")
        file(WRITE "${DO_NOT_TEST_FILE}")
        return()
    endif()
elseif(CONFIGURATION STREQUAL FULL_CONSTEXPR)
    if(SUPPORTS_CONSTEXPR)
        set(CMAKE_CXX_STANDARD 11)
        add_definitions(-DBETTER_ENUMS_CONSTEXPR_TO_STRING)
    else()
        message(WARNING "This compiler does not support constexpr")
        file(WRITE "${DO_NOT_TEST_FILE}")
        return()
    endif()
elseif(CONFIGURATION STREQUAL STRICT_CONVERSION)
    if(SUPPORTS_ENUM_CLASS)
        set(CMAKE_CXX_STANDARD 11)
        add_definitions(-DBETTER_ENUMS_STRICT_CONVERSION)
    else()
        message(WARNING "This compiler does not support enum class")
        file(WRITE "${DO_NOT_TEST_FILE}")
        return()
    endif()
elseif(CONFIGURATION STREQUAL CXX98)
    set(CMAKE_CXX_STANDARD 98)
elseif(CONFIGURATION STREQUAL CXX14)
    if(SUPPORTS_RELAXED_CONSTEXPR)
        set(CMAKE_CXX_STANDARD 14)
    else()
        message(WARNING "This compiler does not support relaxed constexpr")
        file(WRITE "${DO_NOT_TEST_FILE}")
        return()
    endif()
else()
    set(CMAKE_CXX_STANDARD 11)
endif()


# Basic tests.

add_executable(cxxtest cxxtest/tests.cc)
add_executable(linking linking/helper.cc linking/main.cc)

set(PERFORMANCE_TESTS
    1-simple 2-include_empty 3-only_include_enum 4-declare_enums 5-iostream)

foreach(TEST ${PERFORMANCE_TESTS})
    add_executable(performance-${TEST} performance/${TEST}.cc)
endforeach(TEST)


# Select examples to build.

set(EXAMPLES
    1-hello-world 2-conversions 3-iterate 4-switch 6-iostreams 7-safety
    8-representation 9-constexpr 101-special-values 103-bitset 104-quine
    105-c++17-reflection)

set(SKIPPED_FOR_CXX98
    5-map 9-constexpr 101-special-values 103-bitset 104-quine
    105-c++17-reflection)

set(SKIPPED_FOR_STRICT_CONVERSION 4-switch)

if(CONFIGURATION STREQUAL CXX98 OR NOT SUPPORTS_CONSTEXPR)
    list(REMOVE_ITEM EXAMPLES ${SKIPPED_FOR_CXX98})
endif()

if(CONFIGURATION STREQUAL STRICT_CONVERSION)
    list(REMOVE_ITEM EXAMPLES ${SKIPPED_FOR_STRICT_CONVERSION})
endif()

if(CONFIGURATION STREQUAL CXX14)
    set(EXAMPLES 5-map)
endif()

foreach(EXAMPLE ${EXAMPLES})
    add_executable(example-${EXAMPLE} ../example/${EXAMPLE}.cc)
endforeach(EXAMPLE)


# Add compiler flags.

include_directories(..)
include_directories(../extra)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES Clang)
    include(CheckCXXCompilerFlag)

    macro(add_cxx_flag_if_supported FLAG)
        check_cxx_compiler_flag("${FLAG}" HAVE_FLAG_${FLAG})

        if(HAVE_FLAG_${FLAG})
            add_definitions(${FLAG})
        endif()
    endmacro()

    macro(add_cxx_flag_to_target_if_supported TARGET FLAG)
        string(REPLACE "=" "_equals_" ESCAPED ${FLAG})
        string(REPLACE "+" "_plus_" ESCAPED ${ESCAPED})
        check_cxx_compiler_flag("${FLAG}" HAVE_FLAG_${FLAG})

        if(HAVE_FLAG_${FLAG})
            get_target_property(FLAGS ${TARGET} COMPILE_FLAGS)
            if(${FLAGS} STREQUAL "FLAGS-NOTFOUND")
                set(FLAGS "")
            endif()
            set_target_properties(
                ${TARGET} PROPERTIES COMPILE_FLAGS "${FLAGS} ${FLAG}")
        endif()
    endmacro()

    add_cxx_flag_if_supported("-Wpedantic")
    add_cxx_flag_if_supported("-Wall")
    add_cxx_flag_if_supported("-Wextra")
    add_cxx_flag_if_supported("-Wno-variadic-macros")
    add_cxx_flag_if_supported("-Wno-unused-const-variable")

    add_cxx_flag_to_target_if_supported(linking "-Weverything")
    add_cxx_flag_to_target_if_supported(linking "-Wno-c++98-compat-pedantic")
    add_cxx_flag_to_target_if_supported(linking "-Wno-padded")
    add_cxx_flag_to_target_if_supported(linking "-Wno-global-constructors")
    add_cxx_flag_to_target_if_supported(linking "-Wno-old-style-cast")
    add_cxx_flag_to_target_if_supported(linking "-Wno-missing-prototypes")
    add_cxx_flag_to_target_if_supported(linking "-Wshadow")
    add_cxx_flag_to_target_if_supported(linking "-Weffc++")
    add_cxx_flag_to_target_if_supported(linking "-Wstrict-aliasing")
    add_cxx_flag_to_target_if_supported(linking "-Wformat")
    add_cxx_flag_to_target_if_supported(linking "-Wmissing-include-dirs")
    add_cxx_flag_to_target_if_supported(linking "-Wsync-nand")
    add_cxx_flag_to_target_if_supported(linking "-Wconditionally-supported")
    add_cxx_flag_to_target_if_supported(linking "-Wconversion")
    add_cxx_flag_to_target_if_supported(linking "-Wuseless-cast")

    add_definitions("-Werror")
endif()
