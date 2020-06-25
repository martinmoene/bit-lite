#include "nonstd/bit.hpp"
#include <iostream>

using namespace nonstd;

int main()
{
    std::cout
        << "Consecutive ones at the right in 0x17: " << countr_one( 0x17u )
        << "\nBit width of 0x13: " << bit_width( 0x13u ) << '\n';
}

// g++ -Wall -I../include -o 01-basic.exe 01-basic.cpp && 01-basic.exe
