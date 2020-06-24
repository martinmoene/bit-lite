//
// Copyright (c) 2020-2020 Martin Moene
//
// https://github.com/martinmoene/bit-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "bit-main.t.hpp"

#include <iostream>

#if bit_CPP11_90
# include <cstdint>
    namespace std11 { using std::uint64_t; }
#else
    namespace std11 { typedef unsigned long long uint64_t; }
#endif

namespace nonstd { namespace bit {

inline std::string to_string( endian const & e )
{
    using nonstd::endian;

    if ( e == endian::little )
        return "[little endian]";
    else if ( e == endian::big )
        return "[big endian]";
    else if ( e == endian::native )
        return "[native endian (distinct)]";
    else
        return "[??? endian]";
}

inline std::ostream & operator<<( std::ostream & os, endian const & e )
{
    return os << to_string( e );
}
}} // namespace nonstd::bit

using namespace nonstd;

//
// bit_cast<>()
//

// nonstd::bit_cast is not const_expr:

#define no_constexpr /*constexpr*/

CASE( "bit_cast<>(): ..." )
{
    no_constexpr double f64v = 19880124.0;
    no_constexpr ::std11::uint64_t u64v = nonstd::bit_cast< ::std11::uint64_t >(f64v);

    no_constexpr ::std11::uint64_t u64v2 = 0x3fe9000000000000ull;
    no_constexpr double  f64v2 = nonstd::bit_cast<double>(u64v2);

    std::cout
        << std::fixed << f64v << ": f64.to_bits() == 0x"
        << std::hex   << u64v << ": u64\n" << std::dec;

    std::cout
        << std::hex   << "f64::from_bits(0x" << u64v2 << "u64) == " << std::dec
        << std::fixed << f64v2 << "f64\n";

    EXPECT( true );
}

using nonstd::bit::bitmask;

CASE( "has_single_bit(): single bit yields true for single bits set" )
{
    typedef unsigned long type;
    const int N = CHAR_BIT * sizeof(type);

    for( int i = 0; i < N; ++i )
    {
        // std::cout << "i:" << i << " mask:" << std::hex << bitmask<type>(i) << std::dec << '\n';
        EXPECT( has_single_bit( bitmask<type>(i) ) );
    }
}

CASE( "has_single_bit(): single bit yields false for mutiple bits set" )
{
    typedef unsigned long type;
    const int N = CHAR_BIT * sizeof(type);

    for( int i = 0; i < N; ++i )
    {
        if ( i != N-i )
        {
            EXPECT_NOT( has_single_bit( static_cast<type>(bitmask<type>(i) | bitmask<type>(N-i-1)) ) );
        }
    }
}

#include <bitset>

CASE( "bit_ceil(): implement" )
{
    EXPECT( !!"bit_ceil(): implement" );

    typedef std::bitset<8> bin;

    for (unsigned x = 0; x != 10; ++x)
    {
        unsigned const z = nonstd::bit_ceil(x); // `ceil2` before P1956R1

#if bit_BETWEEN( bit_COMPILER_MSVC_VER, 1, 1700 )
        std::cout << "bit_ceil(" << bin(int(x)) << ") = " << bin(int(z)) << '\n';
#else
        std::cout << "bit_ceil(" << bin(x) << ") = " << bin(z) << '\n';
#endif
    }
}

CASE( "bit_floor(): implement" )
{
    EXPECT( !!"bit_floor(): implement" );

    typedef std::bitset<8> bin;

    for (unsigned x = 0; x != 10; ++x)
    {
        unsigned const z = nonstd::bit_floor(x); // `floor2` before P1956R1

#if bit_BETWEEN( bit_COMPILER_MSVC_VER, 1, 1700 )
        std::cout << "bit_floor(" << bin(int(x)) << ") = " << bin(int(z)) << '\n';
#else
        std::cout << "bit_floor(" << bin(x) << ") = " << bin(z) << '\n';
#endif
    }
}

CASE( "bit_width: implement" )
{
    EXPECT( !!"bit_width()(): implement" );

    for (unsigned x = 0; x != 8; ++x)
    {
        std::cout
            << "bit_width( "
#if bit_BETWEEN( bit_COMPILER_MSVC_VER, 1, 1700 )
            << std::bitset<4>(int(x)) << " ) = "
#else
            << std::bitset<4>(x) << " ) = "
#endif
            << nonstd::bit_width(x) << '\n';
    }
}

CASE( "rotl(): implement" )
{
    EXPECT( !!"rotl(): implement" );

    typedef unsigned char uint8_t;
    uint8_t i = 29; // 0b00011101;
    std::cout << "i          = " << std::bitset<8>(i) << '\n';
    std::cout << "rotl(i,0)  = " << std::bitset<8>(nonstd::rotl(i,0)) << '\n';
    std::cout << "rotl(i,1)  = " << std::bitset<8>(nonstd::rotl(i,1)) << '\n';
    std::cout << "rotl(i,4)  = " << std::bitset<8>(nonstd::rotl(i,4)) << '\n';
    std::cout << "rotl(i,9)  = " << std::bitset<8>(nonstd::rotl(i,9)) << '\n';
    std::cout << "rotl(i,-1) = " << std::bitset<8>(nonstd::rotl(i,-1)) << '\n';
}

CASE( "rotr(): implement" )
{
    EXPECT( !!"rotr(): implement" );

    typedef unsigned char uint8_t;
    uint8_t i = 29; // 0b00011101;
    std::cout << "i          = " << std::bitset<8>(i) << '\n';
    std::cout << "rotr(i,0)  = " << std::bitset<8>(nonstd::rotr(i,0)) << '\n';
    std::cout << "rotr(i,1)  = " << std::bitset<8>(nonstd::rotr(i,1)) << '\n';
    std::cout << "rotr(i,9)  = " << std::bitset<8>(nonstd::rotr(i,9)) << '\n';
    std::cout << "rotr(i,-1) = " << std::bitset<8>(nonstd::rotr(i,-1)) << '\n';
}

CASE( "countl_zero(): implement" )
{
    EXPECT( !!"countl_zero(): implement" );

    typedef unsigned char type;
    type table[] = { 0u, 255u, 28u };

    for ( int i = 0; i < 3; ++i )
    {
        type x = table[i];

        std::cout
            << "countl_zero(0b" << std::bitset<8>(x) << ") = "
            << nonstd::countl_zero(x) << '\n';
    }
}

CASE( "countl_one(): implement" )
{
    EXPECT( !!"countl_one(): implement" );

    typedef unsigned char type;
    type table[] = { 0u, 255u, 227u };

    for ( int i = 0; i < 3; ++i )
    {
        type x = table[i];
        std::cout
            << "countl_one(0b" << std::bitset<8>(x) << ") = "
            << nonstd::countl_one(x) << '\n';
    }
}

CASE( "countr_zero(): implement" )
{
    EXPECT( !!"countr_zero(): implement" );

    typedef unsigned char type;
    type table[] = { 0u, 255u, 28u };

    for ( int i = 0; i < 3; ++i )
    {
        type x = table[i];

        std::cout
            << "countr_zero(0b" << std::bitset<8>(x) << ") = "
            << nonstd::countr_zero(x) << '\n';
    }
}

CASE( "countr_one(): implement" )
{
    EXPECT( !!"countr_one(): implement" );

    // for (std::uint8_t i : { 0, 0b11111111, 0b11100011 })

    typedef unsigned char type;
    type table[] = { 0u, 255u, 227u };

    for ( int i = 0; i < 3; ++i )
    {
        type x = table[i];

        std::cout
            << "countr_one(0b" << std::bitset<8>(x) << ") = "
            << nonstd::countr_one(x) << '\n';
    }
}

CASE( "popcount(): implement" )
{
    EXPECT( !!"popcount(): implement" );

    // for (std::uint8_t i : { 0, 0b11111111, 0b00011101 })

    typedef unsigned char type;
    type table[] = { 0u, 255u, 29u };

    for ( int i = 0; i < 3; ++i )
    {
        type x = table[i];

        std::cout
            << "popcount(0b" << std::bitset<8>(x) << ") = "
            << nonstd::popcount(x) << '\n';
    }
}

CASE( "endian: little differs from big (corner-case when all scalars have size of 1 byte)" )
{
    EXPECT( nonstd::endian::little != nonstd::endian::big );
}

// g++ -std=c++11 -I../include -o bit.t.exe bit.t.cpp && bit.t.exe
// cl -EHsc -I../include bit.t.cpp && bit.t.exe
