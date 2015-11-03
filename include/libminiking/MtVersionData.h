/*
=============================================================================
  Name: MtVersionData.h
  Author: Emilio Garcia-Fidalgo
  Date: 13/10/06 17:05
  Description: Implementation of 'mtVersionData' Message
=============================================================================
*/

#ifndef _MTVERSIONDATA_H
#define _MTVERSIONDATA_H

#include "libminiking/Message.h"

// CPUID fields

typedef struct { 

    BYTE frequencies;
    BYTE boardtype;
    BYTE serialnumber[2];
} CPUID;

class MtVersionData : public Message {

protected:
    CPUID cpuid;         // Information about Sonar
    BYTE programln[4];   // Version
    BYTE checksum[2];    // Checksum
    BYTE nodeid;         // Node ID
public:
    void printPacket(bool);
    void receive(SerialPort *);

    // Access Functions

    Frequency getFrequency(void); // Returns Packet Frequency
    BoardType getBoardType(void); // Return BoardType
    int getSerialNumber(void);    // Returns CPU Serial Number in sonar
    int getProgramLength(void);   // Returns Program Length
    int getChecksum(void);        // Returns Checksum
};

#endif
