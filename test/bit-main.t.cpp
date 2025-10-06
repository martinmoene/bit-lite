//
// Copyright (c) 2020-2025 Martin Moene
//
// https://github.com/martinmoene/bit-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "bit-main.t.hpp"

#define bit_PRESENT( x ) \
    std::cout << #x << ": " << (x) << "\n"

#define bit_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "bit-lite version" "[.bit][.version]" )
{
    bit_PRESENT( bit_lite_MAJOR );
    bit_PRESENT( bit_lite_MINOR );
    bit_PRESENT( bit_lite_PATCH );
    bit_PRESENT( bit_lite_VERSION );
}

CASE( "bit-lite configuration" "[.bit][.config]" )
{
    bit_PRESENT( bit_HAVE_STD_BIT );
    bit_PRESENT( bit_USES_STD_BIT );
    bit_PRESENT( bit_BIT_DEFAULT );
    bit_PRESENT( bit_BIT_NONSTD );
    bit_PRESENT( bit_BIT_STD );
    bit_PRESENT( bit_CONFIG_SELECT_BIT );
    // bit_PRESENT( bit_CONFIG_NO_EXCEPTIONS );
    bit_PRESENT( bit_CPLUSPLUS );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    bit_PRESENT( __cplusplus );

#ifdef _MSVC_LANG
    bit_PRESENT( _MSVC_LANG );
#else
    bit_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "Compiler version" "[.compiler]" )
{
#if bit_USES_STD_BIT
    std::cout << "(Compiler version not available: using standard <bit>)\n";
#else
    bit_PRESENT( bit_COMPILER_CLANG_VERSION );
    bit_PRESENT( bit_COMPILER_GNUC_VERSION );
    bit_PRESENT( bit_COMPILER_MSVC_VERSION );
#endif
}

CASE( "Presence of C++ language features" "[.stdlanguage]" )
{
#if bit_USES_STD_BIT
    std::cout << "(Presence of C++ language features not available: using standard <bit>)\n";
#else
//  bit_PRESENT( bit_HAVE_AUTO );
    // bit_PRESENT( bit_HAVE_NULLPTR );
    // bit_PRESENT( bit_HAVE_STATIC_ASSERT );
    // bit_PRESENT( bit_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
//  bit_PRESENT( bit_HAVE_ALIAS_TEMPLATE );
    bit_PRESENT( bit_HAVE_CONSTEXPR_11 );
    bit_PRESENT( bit_HAVE_CONSTEXPR_14 );
    bit_PRESENT( bit_HAVE_ENUM_CLASS );
//  bit_PRESENT( bit_HAVE_ENUM_CLASS_CONSTRUCTION_FROM_UNDERLYING_TYPE );
//  bit_PRESENT( bit_HAVE_EXPLICIT_CONVERSION );
    // bit_PRESENT( bit_HAVE_INITIALIZER_LIST );
//  bit_PRESENT( bit_HAVE_IS_DEFAULT );
//  bit_PRESENT( bit_HAVE_IS_DELETE );
    bit_PRESENT( bit_HAVE_NOEXCEPT );
#endif
}

CASE( "Presence of C++ library features" "[.stdlibrary]" )
{
#if bit_USES_STD_BIT
    std::cout << "(Presence of C++ library features not available: using standard <bit>)\n";
#else
    bit_PRESENT( bit_HAVE_TYPE_TRAITS );
    bit_PRESENT( bit_HAVE_TR1_TYPE_TRAITS );
    bit_PRESENT( bit_HAVE_IS_TRIVIAL );
    bit_PRESENT( bit_HAVE_IS_TRIVIALLY_COPYABLE );
    bit_PRESENT( bit_HAVE_IS_COPY_CONSTRUCTIBLE );
    bit_PRESENT( bit_HAVE_IS_MOVE_CONSTRUCTIBLE );
#endif

#if defined _HAS_CPP0X
    bit_PRESENT( _HAS_CPP0X );
#else
    bit_ABSENT(  _HAS_CPP0X );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o bit-lite.t.exe bit-main.t.cpp && bit-lite.t.exe --pass
g++ -std=c++98 -I../include -o bit-lite.t.exe bit-main.t.cpp && bit-lite.t.exe --pass
g++ -std=c++03 -I../include -o bit-lite.t.exe bit-main.t.cpp && bit-lite.t.exe --pass
g++ -std=c++0x -I../include -o bit-lite.t.exe bit-main.t.cpp && bit-lite.t.exe --pass
g++ -std=c++11 -I../include -o bit-lite.t.exe bit-main.t.cpp && bit-lite.t.exe --pass
g++ -std=c++14 -I../include -o bit-lite.t.exe bit-main.t.cpp && bit-lite.t.exe --pass
g++ -std=c++17 -I../include -o bit-lite.t.exe bit-main.t.cpp && bit-lite.t.exe --pass

cl -EHsc -I../include -Febit-lite.t.exe bit-main.t.cpp && bit-lite.t.exe --pass
#endif

// end of file
