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

namespace lest {

inline std::string to_string( nonstd::endian const & e )
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

inline std::ostream & operator<<( std::ostream & os, nonstd::endian const & e )
{
    return os << to_string( e );
}
} // namespace lest

//
// bit_cast<>()
//

// nonstd::bit_cast is not const_expr:

#define no_constexpr /*constexpr*/

CASE( "bit_cast: ..." )
{
    no_constexpr double f64v = 19880124.0;
    no_constexpr std11::uint64_t u64v = nonstd::bit_cast<std11::uint64_t>(f64v);

    no_constexpr std11::uint64_t u64v2 = 0x3fe9000000000000ull;
    no_constexpr double  f64v2 = nonstd::bit_cast<double>(u64v2);

    std::cout
        << std::fixed << f64v << ": f64.to_bits() == 0x"
        << std::hex   << u64v << ": u64\n" << std::dec;

    std::cout
        << std::hex   << "f64::from_bits(0x" << u64v2 << "u64) == " << std::dec
        << std::fixed << f64v2 << "f64\n";

    EXPECT( true );
}

CASE( "has_single_bit: implement" )
{
    EXPECT( !!"has_single_bit: implement" );
}

CASE( "bit_ceil: implement" )
{
    EXPECT( !!"bit_ceil: implement" );
}

CASE( "bit_floor: implement" )
{
    EXPECT( !!"bit_floor: implement" );
}

CASE( "bit_width: implement" )
{
    EXPECT( !!"bit_width: implement" );
}

CASE( "rotl: implement" )
{
    EXPECT( !!"rotl: implement" );
}

CASE( "rotr: implemen" )
{
    EXPECT( !!"rotr: implement" );
}

CASE( "countl_zero: implement" )
{
    EXPECT( !!"countl_zero: implement" );
}

CASE( "countl_one: implement" )
{
    EXPECT( !!"countl_one: implement" );
}

CASE( "countr_zero: implement" )
{
    EXPECT( !!"countr_zero: implement" );
}

CASE( "countr_one: implement" )
{
    EXPECT( !!"countr_one: implement" );
}

CASE( "popcount: implement" )
{
    EXPECT( !!"popcount: implement" );
}

CASE( "endian: little differs from big (corner-case when all scalars have size of 1 byte)" )
{
    EXPECT( nonstd::endian::little != nonstd::endian::big );
}

// g++ -std=c++11 -I../include -o bit.t.exe bit.t.cpp && bit.t.exe
// cl -EHsc -I../include bit.t.cpp && bit.t.exe
