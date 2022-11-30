# bit-lite - C++20 bit operations for C++98 and later in a single-file header-only library.

[![Language](https://img.shields.io/badge/C%2B%2B-98/11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://github.com/martinmoene/bit-lite/actions/workflows/ci.yml/badge.svg)](https://github.com/martinmoene/bit-lite/actions/workflows/ci.yml) [![Build Status](https://travis-ci.org/martinmoene/bit-lite.svg?branch=master)](https://travis-ci.org/martinmoene/bit-lite) [![Build status](https://ci.appveyor.com/api/projects/status/gpmw4gt271itoy2n?svg=true)](https://ci.appveyor.com/project/martinmoene/bit-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Fbit-lite.svg)](https://github.com/martinmoene/bit-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://raw.githubusercontent.com/martinmoene/bit-lite/master/include/nonstd/bit.hpp) [![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://conan.io/center/bit-lite) [![Try it online](https://img.shields.io/badge/on-wandbox-blue.svg)](https://wandbox.org/permlink/ZwnY4c9dZUAynUac) [![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](https://godbolt.org/z/1IPvn7)

**Contents**  

- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Synopsis](#synopsis)
- [Features](#features)
- [Reported to work with](#reported-to-work-with)
- [Building the tests](#building-the-tests)
- [Other implementations of bit](#other-implementations-of-bit)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)

## Example usage

```Cpp
#include "nonstd/bit.hpp"
#include <iostream>

using namespace nonstd;

int main()
{
    std::cout
        << "Consecutive ones at the right in 0x17: " << countr_one( 0x17u )
        << "\nBit width of 0x13: " << bit_width( 0x13u ) << '\n';
}
```

### Compile and run

```Text
prompt> g++ -Wall -I../include -o 01-basic.exe 01-basic.cpp && 01-basic.exe
Consecutive ones at the right in 0x17: 3
Bit width of 0x13: 5
```

## In a nutshell

**bit lite** is a single-file header-only library to provide the tools from the C++20 header [`<bit>`](https://en.cppreference.com/w/cpp/header/bit) for use with C++98 and later. If available, the standard header is used, unless [configured](#configuration) otherwise.

**Features and properties of bit lite** are ease of installation (single header), freedom of dependencies other than the standard library.

**Limitations of bit lite** are ... .

## License

*bit lite* is distributed under the [Boost Software License](https://github.com/martinmoene/bit-lite/blob/master/LICENSE.txt).

## Dependencies

*bit lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).

## Installation

*bit lite* is a single-file header-only library. Put `bit.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## Synopsis

**Contents**  

[Documentation of standard header `<bit>`](#documentation-of-stdbit)  
[Non-standard extensions](#non-standard-extensions)  
[Configuration](#configuration)  

### Documentation of standard header `<bit>`

Depending on the compiler and C++-standard used, *bit lite* behaves less or more like C++20 standard `<bit>`. To get an idea of the capabilities of *bit lite* with your configuration, look at the output of the [tests](test/bit.t.cpp), issuing `bit-main.t --pass @`. For C++20 standard `<bit>`, see its [documentation at cppreference](https://en.cppreference.com/w/cpp/header/bit).  

### Non-standard extensions

| Kind               | Extension type or function | Notes |
|--------------------|----------------------------|-------|
| **Type**           | **big_endian_type**        | type based on endian::big    |
| &nbsp;             | **little_endian_type**     | type based on endian::little |
| &nbsp;             | **native_endian_type**     | type based on endian::native |
| &nbsp;             | &nbsp; |&nbsp;|
| **Free function**  | template&lt;class T><br>T **to_big_endian**(T v) | <br>convert unconditionally |
| &nbsp;             | template&lt;class T, class EN><br>T **to_big_endian**(T v, EN) | convert if EN is little_endian_type<br>*EN specifies endianness of v* |
| &nbsp;             | template&lt;class T><br>T **to_little_endian**(T v) | <br>convert unconditionally |
| &nbsp;             | template&lt;class T, class EN><br>T **to_little_endian**(T v, EN) | convert if EN is big_endian_type<br>*EN specifies endianness of v* |
| &nbsp;             | template&lt;class T><br>T **to_native_endian**(T v) | <br>identity |
| &nbsp;             | template&lt;class T, class EN><br>T **to_native_endian**(T v, EN) | convert if EN represents<br> non-native endianness for v |
| &nbsp;             | &nbsp; |&nbsp;|
| &nbsp;             | template&lt;class T><br>T **as_big_endian**(T v) | <br>convert if native is little endian |
| &nbsp;             | template&lt;class T><br>T **as_little_endian**(T v) | <br>convert if native is big endian |
| &nbsp;             | template&lt;class T><br>T **as_native_endian**(T v) | <br>identity |

### Configuration

#### Standard selection macro

\-D<b>bit\_CPLUSPLUS</b>=199711L  
Define this macro to override the auto-detection of the supported C++ standard, if your compiler does not set the `__cplusplus` macro correctly.

#### Select C++20 standard `<bit>` or nonstd `<bit>`

At default, *bit lite* uses the C++20 standard header `<bit>` if it is available and lets you use it via namespace `nonstd`. You can however override this default and explicitly request to use the standard C++20 header or *bit lite*'s header via the following macros.

-D<b>bit\_CONFIG\_SELECT\_BIT</b>=bit_BIT_DEFAULT  
Define this to `bit_BIT_STD` to select C++20 standard header `<bit>`. Define this to `bit_BIT_NONSTD` to select *bit lite*. Default is undefined, which has the same effect as defining to `bit_BIT_DEFAULT`.

#### Strict C++20 mode

-D<b>bit\_CONFIG\_STRICT</b>=1  
Define this to `1` to omit the non C++20 standard extensions. Default is undefined, which has the same effect as `0`, non-strict mode.

## Reported to work with

TBD

## Building the tests

TBD

## Other implementations of `<bit>`

TBD

## Notes and references

*Interface and specification*

- Cppreference. [Header &lt;bit&gt;](https://en.cppreference.com/w/cpp/header/bit)
- Cppreference. [bit_cast](https://en.cppreference.com/w/cpp/numeric/bit_cast)
- Cppreference. [enum class endian](https://en.cppreference.com/w/cpp/types/endian)

*Proposals*

- [p0463 - endendian, Just endian](https://wg21.link/P0463). Howard E. Hinnant. 2017.
- [p0476 - Bit-casting object representations](https://wg21.link/P0476). JF Bastien. 2017.
- [p0553 - Bit operations](https://wg21.link/P0553). Jens Maurer. 2019.

*Articles*

- Overload 160. [What is the Strict Aliasing Rule and Why Do We Care?](https://accu.org/journals/overload/28/160/anonymous/). Anonymous. December 2020.

## Appendix

The [test program](test/bit.t.cpp) provides information on the compiler, the C++ language and library capabilities and the tests performed.

### A.1 Compile-time information

The version of *bit lite* is available via tag `[.version]`. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

### A.2 Bit lite test specification

```Text
bit_cast<>(): successfully roundtrips uint64_t via double [bit.cast]
has_single_bit(): single bit yields false for no bits set [bit.pow.two]
has_single_bit(): single bit yields true for single bits set [bit.pow.two]
has_single_bit(): single bit yields false for multiple bits set [bit.pow.two]
bit_ceil(): let N be the smallest power of 2 greater than or equal to x [bit.pow.two]
bit_floor(): x == 0, 0; otherwise the maximal value y such that has_single_bit(y) is true and y <= x [bit.pow.two]
bit_width: x == 0, 0; otherwise one plus the base-2 logarithm of x, with any fractional part discarded [bit.pow.two]
rotl(): r is 0, x; if r is positive, (x << r) | (x >> (N - r)); if r is negative, rotr(x, -r) [bit.rotate]
rotr(): r is 0, x; if r is positive, (x >> r) | (x << (N - r)); if r is negative, rotl(x, -r) [bit.rotate]
countl_zero(): the number of consecutive 0 bits in the value of x, starting from the most significant bit [bit.count]
countl_one(): the number of consecutive 1 bits in the value of x, starting from the most significant bit [bit.count]
countr_zero(): the number of consecutive 0 bits in the value of x, starting from the least significant bit [bit.count]
countr_one(): the number of consecutive 1 bits in the value of x, starting from the least significant bit [bit.count]
popcount(): the number of 1 bits in the value of x [bit.count]
endian: little differs from big (corner-case when all scalars have size of 1 byte) [bit.endian]
to_big_endian(): convert native, or little or big endian specified unsigned to big endian [bit.endian.extension]
to_little_endian(): convert native, or little or big endian specified unsigned to little endian [bit.endian.extension]
to_native_endian(): convert native, or little or big endian specified unsigned to native endian [bit.endian.extension]
as_big_endian(): provide native unsigned as big endian [bit.endian.extension]
as_little_endian(): provide native unsigned as little endian [bit.endian.extension]
as_native_endian(): provide native unsigned as native endian (identity) [bit.endian.extension]
```
