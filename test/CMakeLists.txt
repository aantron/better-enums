# Define catch as an interface target
add_library(catch INTERFACE)
target_include_directories(catch INTERFACE catch/single_include)

###################################################################################
##
###################################################################################
macro( _parse_target_args prefix )
    set( OPTIONS
    )

    set( ONE_VALUE_KEYWORDS
    )

    set( MULTI_VALUE_KEYWORDS
        SOURCE_FILES
        DEPENDENCIES
    )

    CMAKE_PARSE_ARGUMENTS(
        ${prefix}
        "${OPTIONS}"
        "${ONE_VALUE_KEYWORDS}"
        "${MULTI_VALUE_KEYWORDS}"
        ${ARGN}
    )
endmacro()

###################################################################################
##
###################################################################################
function(define_target target_name target_type)
    _parse_target_args(DT ${ARGN})
    
    if(NOT DT_SOURCE_FILES)
        message(SEND_ERROR "Target ${target_name} defined with no source files")
    endif()
    
    if(target_type STREQUAL "EXECUTABLE")
        add_executable(${target_name} ${DT_SOURCE_FILES})
    else()
        # @todo Add support for shared & static libraries later, if needed
        message(FATAL_ERROR "Unknown target type specified: ${target_type}")
    endif()
    
    if(DT_DEPENDENCIES)
        target_link_libraries(${target_name} ${DT_DEPENDENCIES})
    endif()
endfunction()

###################################################################################
##
###################################################################################
function(define_test test_name)
    set(test_files ${ARGN})
    
    define_target(${test_name} EXECUTABLE
        SOURCE_FILES ${test_files}
        DEPENDENCIES catch ${project_name}
    )
    
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

###################################################################################
##
###################################################################################
function(define_multiple_tests)
    foreach(test_file ${ARGN})
        get_filename_component(filename ${test_file} NAME_WE)
        #string( REPLACE "test_" "" filename ${filename} )
        define_test(${filename} ${test_file})
    endforeach()
endfunction()


# Detect compiler feature support
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

set(test_files
    source/test_enum.cpp
)

define_multiple_tests(${test_files})
