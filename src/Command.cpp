/*
=============================================================================
  Name: Command.cpp
  Author: Emilio Garcia-Fidalgo
  Date: 11/10/06 19:46
  Description: Implementation of the ´base 256´ function
=============================================================================
*/

#include "Command.h"

// Pass 'number' to Hexadecimal and store it to 'r'
void Command::base256(BYTE *r, int number, int howmany) {

    int remainder;
    int quotient = number;
    BYTE *p;

    p = r;
    for (int i = 0; i < howmany; i++) {
        remainder = quotient % 256;
        quotient = quotient / 256;
        if (quotient || remainder)
            *p = remainder;
        else
            *p = 0;
        p++;
    }
}
