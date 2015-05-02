/*
=============================================================================
  Name: Packet.h 
  Author: Emilio Garcia-Fidalgo
  Date: 26/10/06 16:57
  Description: Abstract class Packet
=============================================================================
*/

#include "Packet.h"

BYTE Packet::getHdr(void) { return hdr; }

BYTE *Packet::getHexLn(void) { return hexln; }

BYTE *Packet::getBinLn(void) { return binln; }

BYTE Packet::getSid(void) { return sid; }

BYTE Packet::getDid(void) { return did; }

BYTE Packet::getCountMsg(void) { return countmsg; }

BYTE Packet::getType(void) { return ptype; }

BYTE Packet::getSequence(void) { return sequence; }

BYTE Packet::getNode(void) { return node; }
