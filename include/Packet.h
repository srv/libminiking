/*
=============================================================================
  Name: Packet.h
  Author: Emilio Garcia-Fidalgo
  Date: 09/10/06 19:02
  Description: Abstract class Packet
=============================================================================
*/

#include "SonarDefs.h"
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <cstdio>

using namespace std;

#ifndef _PACKET_H
#define _PACKET_H

class Packet {

protected:
    BYTE hdr;          // Character header
    BYTE hexln[4];     // Packet´s length in ASCII
    BYTE binln[2];     // Packet´s length in binary
    BYTE sid;          // Source ID
    BYTE did;          // Destination ID
    BYTE countmsg;     // Length in bytes of MSG
    BYTE ptype;        // Packet´s type
    BYTE sequence;     // Sequence number (for multi-packet mode)
    BYTE node;         // Copy of byte 8 / 9
    BYTE lfeed;        // Packet temination´s character

    virtual void printPacket(bool) = 0;

public:
    // Access functions

    BYTE getHdr(void);
    BYTE *getHexLn(void);
    BYTE *getBinLn(void);
    BYTE getSid(void);
    BYTE getDid(void);
    BYTE getCountMsg(void);
    BYTE getType(void);
    BYTE getSequence(void);
    BYTE getNode(void);
    friend class MiniKing;
};

#endif
