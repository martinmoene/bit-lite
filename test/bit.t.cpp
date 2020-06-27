//
// Copyright (c) 2020-2020 Martin Moene
//
// https://github.com/martinmoene/bit-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "bit-main.t.hpp"

#include <climits>      // CHAR_BIT, when bit_USES_STD_BIT
#include <iostream>

#define dimension_of(a)  ( sizeof(a) / sizeof(0[a]) )

#if bit_CPP11_90
# include <cstdint>
    using std::uint8_t;
    using std::uint16_t;
    using std::uint32_t;
    using std::uint64_t;
#else
    typedef unsigned char      uint8_t;
    typedef unsigned short int uint16_t;
    typedef unsigned       int uint32_t;
    typedef unsigned long long uint64_t;
#endif

#if bit_USES_STD_BIT
namespace std {
#else
namespace nonstd { namespace bit {
#endif

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

#if bit_USES_STD_BIT
} // namespace std
#else
}} // namespace nonstd::bit
#endif

template< typename T >
inline T bitmask( int i )
{
    return static_cast<T>( T(1) << i );
}

using namespace nonstd;

//
// bit_cast<>()
//

// nonstd::bit_cast is not const_expr:

#define no_constexpr /*constexpr*/

CASE( "bit_cast<>(): succesfully roundtrips uint64_t via double" " [bit.cast]" )
{
    const uint64_t v = 0x3fe9000000000000ull;

    EXPECT( v == bit_cast<uint64_t>( bit_cast<double>(v) ) );
}

CASE( "has_single_bit(): single bit yields false for no bits set" " [bit.pow.two]" )
{
    EXPECT_NOT( has_single_bit( 0u ) );
}

CASE( "has_single_bit(): single bit yields true for single bits set" " [bit.pow.two]" )
{
    typedef unsigned long type;
    const int N = CHAR_BIT * sizeof(type);

    for( int i = 0; i < N; ++i )
    {
        // std::cout << "i:" << i << " mask:" << std::hex << bitmask<type>(i) << std::dec << '\n';
        EXPECT( has_single_bit( bitmask<type>(i) ) );
    }
}

CASE( "has_single_bit(): single bit yields false for mutiple bits set" " [bit.pow.two]" )
{
    typedef unsigned long type;
    const int N = CHAR_BIT * sizeof(type);

    for( int i = 0; i < N; ++i )
    {
        const int Ni1 = N-i-1;

        if ( i != Ni1 )
        {
            EXPECT_NOT( has_single_bit( static_cast<type>(bitmask<type>(i) | bitmask<type>(Ni1)) ) );
        }
    }
}

#include <bitset>

// avoid ambiguous overload resolution for VS2010 (VC10):

template< typename T >
std::bitset<8> bin( T v )
{
#if defined( _MSC_VER ) && _MSC_VER <= 1600
    return std::bitset<8>( static_cast<int>(v) );
#else
    return std::bitset<8>( v );
#endif
}

CASE( "bit_ceil(): let N be the smallest power of 2 greater than or equal to x" " [bit.pow.two]" )
{
    EXPECT( bin( bit_ceil( 0u ) ) == bin( 1u ) );
    EXPECT( bin( bit_ceil( 1u ) ) == bin( 1u ) );
    EXPECT( bin( bit_ceil( 2u ) ) == bin( 2u ) );
    EXPECT( bin( bit_ceil( 3u ) ) == bin( 4u ) );
    EXPECT( bin( bit_ceil( 4u ) ) == bin( 4u ) );
    EXPECT( bin( bit_ceil( 5u ) ) == bin( 8u ) );
    EXPECT( bin( bit_ceil( 6u ) ) == bin( 8u ) );
    EXPECT( bin( bit_ceil( 7u ) ) == bin( 8u ) );
    EXPECT( bin( bit_ceil( 8u ) ) == bin( 8u ) );
    EXPECT( bin( bit_ceil( 9u ) ) == bin(16u ) );
}

CASE( "bit_floor(): x == 0, 0; otherwise the maximal value y such that has_single_bit(y) is true and y <= x" " [bit.pow.two]" )
{
    EXPECT( bin( bit_floor( 0u ) ) == bin( 0u ) );
    EXPECT( bin( bit_floor( 1u ) ) == bin( 1u ) );
    EXPECT( bin( bit_floor( 2u ) ) == bin( 2u ) );
    EXPECT( bin( bit_floor( 3u ) ) == bin( 2u ) );
    EXPECT( bin( bit_floor( 4u ) ) == bin( 4u ) );
    EXPECT( bin( bit_floor( 5u ) ) == bin( 4u ) );
    EXPECT( bin( bit_floor( 6u ) ) == bin( 4u ) );
    EXPECT( bin( bit_floor( 7u ) ) == bin( 4u ) );
    EXPECT( bin( bit_floor( 8u ) ) == bin( 8u ) );
    EXPECT( bin( bit_floor( 9u ) ) == bin( 8u ) );
}

CASE( "bit_width: x == 0, 0; otherwise one plus the base-2 logarithm of x, with any fractional part discarded" " [bit.pow.two]" )
{
    EXPECT( bit_width( 0u ) == 0u );
    EXPECT( bit_width( 1u ) == 1u );
    EXPECT( bit_width( 2u ) == 2u );
    EXPECT( bit_width( 3u ) == 2u );
    EXPECT( bit_width( 4u ) == 3u );
    EXPECT( bit_width( 5u ) == 3u );
    EXPECT( bit_width( 6u ) == 3u );
    EXPECT( bit_width( 7u ) == 3u );
    EXPECT( bit_width( 8u ) == 4u );
}

CASE( "rotl(): r is 0, x; if r is positive, (x << r) | (x >> (N - r)); if r is negative, rotr(x, -r)" " [bit.rotate]" )
{
    uint8_t i = 29; // 0b00011101;

    EXPECT( bin(      i     ) == bin(  i ) );
    EXPECT( bin( rotl(i, 0) ) == bin( 29u) );
    EXPECT( bin( rotl(i, 1) ) == bin( 58u) );
    EXPECT( bin( rotl(i, 4) ) == bin(209u) );
    EXPECT( bin( rotl(i, 9) ) == bin( 58u) );
    EXPECT( bin( rotl(i,-1) ) == bin(142u) );
}

CASE( "rotr(): r is 0, x; if r is positive, (x >> r) | (x << (N - r)); if r is negative, rotl(x, -r)" " [bit.rotate]" )
{
    uint8_t i = 29; // 0b00011101;

    EXPECT( bin(      i     ) == bin(  i ) );
    EXPECT( bin( rotr(i, 0) ) == bin( 29u) );
    EXPECT( bin( rotr(i, 1) ) == bin(142u) );
    EXPECT( bin( rotr(i, 4) ) == bin(209u) );
    EXPECT( bin( rotr(i, 9) ) == bin(142u) );
    EXPECT( bin( rotr(i,-1) ) == bin( 58u) );

}

CASE( "countl_zero(): the number of consecutive 0 bits in the value of x, starting from the most significant bit" " [bit.count]" )
{
    EXPECT( countl_zero( uint8_t(0x80u) ) == 0 );
    EXPECT( countl_zero( uint8_t(0x40u) ) == 1 );
    EXPECT( countl_zero( uint8_t(0x20u) ) == 2 );
    EXPECT( countl_zero( uint8_t(0x10u) ) == 3 );
    EXPECT( countl_zero( uint8_t(0x08u) ) == 4 );
    EXPECT( countl_zero( uint8_t(0x04u) ) == 5 );
    EXPECT( countl_zero( uint8_t(0x02u) ) == 6 );
    EXPECT( countl_zero( uint8_t(0x01u) ) == 7 );

    EXPECT( countl_zero( uint8_t(   0u) ) ==  8 );
    EXPECT( countl_zero( uint16_t(  0u) ) == 16 );
    EXPECT( countl_zero( uint32_t(  0u) ) == 32 );
    EXPECT( countl_zero( uint64_t(  0u) ) == 64 );

    EXPECT( countl_zero( 0u ) == static_cast<int>( CHAR_BIT * sizeof(unsigned) ) );
}

CASE( "countl_one(): the number of consecutive 1 bits in the value of x, starting from the most significant bit" " [bit.count]" )
{
    EXPECT( countl_one( uint8_t(0x00u) ) == 0 );
    EXPECT( countl_one( uint8_t(0x80u) ) == 1 );
    EXPECT( countl_one( uint8_t(0xc0u) ) == 2 );
    EXPECT( countl_one( uint8_t(0xe0u) ) == 3 );
    EXPECT( countl_one( uint8_t(0xf0u) ) == 4 );
    EXPECT( countl_one( uint8_t(0xf8u) ) == 5 );
    EXPECT( countl_one( uint8_t(0xfcu) ) == 6 );
    EXPECT( countl_one( uint8_t(0xfeu) ) == 7 );
    EXPECT( countl_one( uint8_t(0xffu) ) == 8 );

    EXPECT( countl_one( uint8_t(   -1) ) ==  8 );
    EXPECT( countl_one( uint16_t(  -1) ) == 16 );
    EXPECT( countl_one( uint32_t(  -1) ) == 32 );
    EXPECT( countl_one( uint64_t(  -1) ) == 64 );

    EXPECT( countl_one( unsigned(-1) ) == static_cast<int>( CHAR_BIT * sizeof(unsigned) ) );
}

CASE( "countr_zero(): the number of consecutive 0 bits in the value of x, starting from the least significant bit" " [bit.count]" )
{
    EXPECT( countr_zero( uint8_t(0x01u) ) == 0 );
    EXPECT( countr_zero( uint8_t(0x02u) ) == 1 );
    EXPECT( countr_zero( uint8_t(0x04u) ) == 2 );
    EXPECT( countr_zero( uint8_t(0x08u) ) == 3 );
    EXPECT( countr_zero( uint8_t(0x10u) ) == 4 );
    EXPECT( countr_zero( uint8_t(0x20u) ) == 5 );
    EXPECT( countr_zero( uint8_t(0x40u) ) == 6 );
    EXPECT( countr_zero( uint8_t(0x80u) ) == 7 );

    EXPECT( countr_zero( uint8_t(   0u) ) ==  8 );
    EXPECT( countr_zero( uint16_t(  0u) ) == 16 );
    EXPECT( countr_zero( uint32_t(  0u) ) == 32 );
    EXPECT( countr_zero( uint64_t(  0u) ) == 64 );

    EXPECT( countr_zero( 0u ) == static_cast<int>( CHAR_BIT * sizeof(unsigned) ) );
}

CASE( "countr_one(): the number of consecutive 1 bits in the value of x, starting from the least significant bit" " [bit.count]" )
{
    EXPECT( countr_one( uint8_t(0x00u) ) == 0 );
    EXPECT( countr_one( uint8_t(0x01u) ) == 1 );
    EXPECT( countr_one( uint8_t(0x03u) ) == 2 );
    EXPECT( countr_one( uint8_t(0x07u) ) == 3 );
    EXPECT( countr_one( uint8_t(0x0fu) ) == 4 );
    EXPECT( countr_one( uint8_t(0x1fu) ) == 5 );
    EXPECT( countr_one( uint8_t(0x3fu) ) == 6 );
    EXPECT( countr_one( uint8_t(0x7fu) ) == 7 );
    EXPECT( countr_one( uint8_t(0xffu) ) == 8 );

    EXPECT( countr_one( uint8_t(   -1) ) ==  8 );
    EXPECT( countr_one( uint16_t(  -1) ) == 16 );
    EXPECT( countr_one( uint32_t(  -1) ) == 32 );
    EXPECT( countr_one( uint64_t(  -1) ) == 64 );

    EXPECT( countr_one( unsigned(-1) ) == static_cast<int>( CHAR_BIT * sizeof(unsigned) ) );
}

CASE( "popcount(): the number of 1 bits in the value of x" " [bit.count]" )
{
    EXPECT( popcount( uint8_t(0x00u) ) == 0 );
    EXPECT( popcount( uint8_t(0x01u) ) == 1 );
    EXPECT( popcount( uint8_t(0x81u) ) == 2 );
    EXPECT( popcount( uint8_t(0x83u) ) == 3 );
    EXPECT( popcount( uint8_t(0xc3u) ) == 4 );
    EXPECT( popcount( uint8_t(0xc7u) ) == 5 );
    EXPECT( popcount( uint8_t(0xe7u) ) == 6 );
    EXPECT( popcount( uint8_t(0xefu) ) == 7 );
    EXPECT( popcount( uint8_t(0xffu) ) == 8 );

    EXPECT( popcount( unsigned(-1) ) == static_cast<int>( CHAR_BIT * sizeof(unsigned) ) );
}

CASE( "endian: little differs from big (corner-case when all scalars have size of 1 byte)" " [bit.endian]" )
{
    EXPECT( nonstd::endian::little != nonstd::endian::big );
}

//
// Extensions: endian conversions
//

CASE( "to_big_endian(): convert native, or little or big endian specified unsigned to big endian" " [bit.endian.extension]" )
{
#if bit_USES_STD_BIT
    EXPECT( !!"Extension to_big_endian() not available (bit_USES_STD_BIT)" );
#elif bit_CONFIG_STRICT
    EXPECT( !!"Extension to_big_endian() not available (bit_CONFIG_STRICT)" );
#else
    EXPECT( to_big_endian( uint8_t(0x5eu)                       ) == 0x5eu );
    EXPECT( to_big_endian( uint8_t(0x5eu), little_endian_type() ) == 0x5eu );
    EXPECT( to_big_endian( uint8_t(0x5eu), big_endian_type()    ) == 0x5eu );

    EXPECT( to_big_endian( uint16_t(0xabcdu)                       ) == 0xcdabu );
    EXPECT( to_big_endian( uint16_t(0xabcdu), little_endian_type() ) == 0xcdabu );
    EXPECT( to_big_endian( uint16_t(0xabcdu), big_endian_type()    ) == 0xabcdu );

    EXPECT( to_big_endian( uint32_t(0xabcdu)                       ) == 0xcdab0000u );
    EXPECT( to_big_endian( uint32_t(0xabcdu), little_endian_type() ) == 0xcdab0000u );
    EXPECT( to_big_endian( uint32_t(0xabcdu), big_endian_type()    ) == 0xabcdu     );
#endif
}

CASE( "to_little_endian(): convert native, or little or big endian specified unsigned to little endian" " [bit.endian.extension]" )
{
#if bit_USES_STD_BIT
    EXPECT( !!"Extension to_little_endian() not available (bit_USES_STD_BIT)" );
#elif bit_CONFIG_STRICT
    EXPECT( !!"Extension to_little_endian() not available (bit_CONFIG_STRICT)" );
#else
    EXPECT( to_little_endian( uint8_t(0x5eu)                       ) == 0x5eu );
    EXPECT( to_little_endian( uint8_t(0x5eu), little_endian_type() ) == 0x5eu );
    EXPECT( to_little_endian( uint8_t(0x5eu), big_endian_type()    ) == 0x5eu );

    EXPECT( to_little_endian( uint16_t(0xabcdu)                       ) == 0xcdabu );
    EXPECT( to_little_endian( uint16_t(0xabcdu), little_endian_type() ) == 0xabcdu );
    EXPECT( to_little_endian( uint16_t(0xabcdu), big_endian_type()    ) == 0xcdabu );

    EXPECT( to_little_endian( uint32_t(0xabcdu)                       ) == 0xcdab0000u );
    EXPECT( to_little_endian( uint32_t(0xabcdu), little_endian_type() ) == 0xabcdu     );
    EXPECT( to_little_endian( uint32_t(0xabcdu), big_endian_type()    ) == 0xcdab0000u );
#endif
}

CASE( "to_native_endian(): convert native, or little or big endian specified unsigned to native endian" " [bit.endian.extension]" )
{
#if bit_USES_STD_BIT
    EXPECT( !!"Extension to_native_endian() not available (bit_USES_STD_BIT)" );
#elif bit_CONFIG_STRICT
    EXPECT( !!"Extension to_native_endian() not available (bit_CONFIG_STRICT)" );
#else
    EXPECT( to_native_endian( uint8_t(0x5eu)                       ) == 0x5eu );
    EXPECT( to_native_endian( uint8_t(0x5eu), little_endian_type() ) == 0x5eu );
    EXPECT( to_native_endian( uint8_t(0x5eu), big_endian_type()    ) == 0x5eu );

    if (  endian::native == endian::big )
    {
        EXPECT( to_native_endian( uint16_t(0xabcdu)                       ) == 0xabcdu );
        EXPECT( to_native_endian( uint16_t(0xabcdu), little_endian_type() ) == 0xcdabu );
        EXPECT( to_native_endian( uint16_t(0xabcdu), big_endian_type()    ) == 0xabcdu );

        EXPECT( to_native_endian( uint32_t(0xabcdu)                       ) == 0xcdab0000u );
        EXPECT( to_native_endian( uint32_t(0xabcdu), little_endian_type() ) == 0xcdab0000u );
        EXPECT( to_native_endian( uint32_t(0xabcdu), big_endian_type()    ) == 0xabcdu     );
    }
    else if (  endian::native == endian::little )
    {
        EXPECT( to_native_endian( uint16_t(0xabcdu)                       ) == 0xabcdu );
        EXPECT( to_native_endian( uint16_t(0xabcdu), little_endian_type() ) == 0xabcdu );
        EXPECT( to_native_endian( uint16_t(0xabcdu), big_endian_type()    ) == 0xcdabu );

        EXPECT( to_native_endian( uint32_t(0xabcdu)                       ) == 0xabcdu     );
        EXPECT( to_native_endian( uint32_t(0xabcdu), little_endian_type() ) == 0xabcdu     );
        EXPECT( to_native_endian( uint32_t(0xabcdu), big_endian_type()    ) == 0xcdab0000u );
    }
    else
    {
        EXPECT( !!"endian::native is big nor little" );
    }

#endif
}

CASE( "as_big_endian(): provide native unsigned as big endian" " [bit.endian.extension]" )
{
#if bit_USES_STD_BIT
    EXPECT( !!"Extension as_big_endian() not available (bit_USES_STD_BIT)" );
#elif bit_CONFIG_STRICT
    EXPECT( !!"Extension as_big_endian() not available (bit_CONFIG_STRICT)" );
#else
    if (  endian::native == endian::big )
    {
        EXPECT( as_big_endian( uint8_t (0x5eu )  ) == 0x5eu );
        EXPECT( as_big_endian( uint16_t(0xabcdu) ) == 0xabcdu );
        EXPECT( as_big_endian( uint32_t(0xabcdu) ) == 0xabcdu );
    }
    else if (  endian::native == endian::little )
    {
        EXPECT( as_big_endian( uint8_t (0x5eu )  ) == 0x5eu );
        EXPECT( as_big_endian( uint16_t(0xabcdu) ) == 0xcdabu );
        EXPECT( as_big_endian( uint32_t(0xabcdu) ) == 0xcdab0000u );
    }
    else
    {
        EXPECT( !!"endian::native is big nor little" );
    }
#endif
}

CASE( "as_little_endian(): provide native unsigned as little endian" " [bit.endian.extension]" )
{
#if bit_USES_STD_BIT
    EXPECT( !!"Extension as_little_endian() not available (bit_USES_STD_BIT)" );
#elif bit_CONFIG_STRICT
    EXPECT( !!"Extension as_little_endian() not available (bit_CONFIG_STRICT)" );
#else
    if (  endian::native == endian::big )
    {
        EXPECT( as_little_endian( uint8_t (0x5eu )  ) == 0x5eu );
        EXPECT( as_little_endian( uint16_t(0xabcdu) ) == 0xcdabu );
        EXPECT( as_little_endian( uint32_t(0xabcdu) ) == 0xcdab0000u );
    }
    else if (  endian::native == endian::little )
    {
        EXPECT( as_little_endian( uint8_t (0x5eu )  ) == 0x5eu );
        EXPECT( as_little_endian( uint16_t(0xabcdu) ) == 0xabcdu );
        EXPECT( as_little_endian( uint32_t(0xabcdu) ) == 0xabcdu );
    }
    else
    {
        EXPECT( !!"endian::native is big nor little" );
    }
#endif
}

CASE( "as_native_endian(): provide native unsigned as native endian (identity)" " [bit.endian.extension]" )
{
#if bit_USES_STD_BIT
    EXPECT( !!"Extension as_native_endian() not available (bit_USES_STD_BIT)" );
#elif bit_CONFIG_STRICT
    EXPECT( !!"Extension as_native_endian() not available (bit_CONFIG_STRICT)" );
#else
        EXPECT( as_native_endian( uint8_t (0x5eu )  ) == 0x5eu );
        EXPECT( as_native_endian( uint16_t(0xabcdu) ) == 0xabcdu );
        EXPECT( as_native_endian( uint32_t(0xabcdu) ) == 0xabcdu );
#endif
}

// g++ -std=c++11 -I../include -o bit.t.exe bit.t.cpp && bit.t.exe
// cl -EHsc -I../include bit.t.cpp && bit.t.exe
