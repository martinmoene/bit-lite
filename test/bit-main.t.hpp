//
// Copyright (c) 2020-2025 Martin Moene
//
// https://github.com/martinmoene/bit-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TEST_BIT_LITE_H_INCLUDED
#define TEST_BIT_LITE_H_INCLUDED

#include "nonstd/bit.hpp"

// Compiler warning suppression for usage of lest:

#ifdef __clang__
# pragma clang diagnostic ignored "-Wstring-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-template"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
# pragma GCC   diagnostic ignored "-Wunused-function"
#endif

#include "lest_cpp03.hpp"

#define CASE( name ) lest_CASE( specification(), name )

// Attribute externally visible for -fwhole-program:

#if defined(__GNUC__) && !defined(__clang__)
# define bit_ATTRIBUTE_EXT_VIS  __attribute__((externally_visible))
#else
# define bit_ATTRIBUTE_EXT_VIS
#endif

extern lest::tests & specification() bit_ATTRIBUTE_EXT_VIS;

#endif // TEST_BIT_LITE_H_INCLUDED

// end of file
