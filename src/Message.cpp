/*
=============================================================================
  Name: Message.cpp
  Author: Emilio Garcia-Fidalgo
  Date: 09/10/06 19:44
  Description: Implementation of the ´synchronize´ and 'base10' functions
=============================================================================
*/

#include "Message.h"
#include <cmath>

// Pass an Hexadecimal to Integer

int Message::base10(BYTE *buffer, int howmany) {

    int result = 0;
    BYTE *p = buffer;

    for (int i = 0; i < howmany; i++) {
        result += (*p) * (int)pow(256.0, i);
        p++;
    }
    return result;
}
