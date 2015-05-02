/*
=============================================================================
  Name: MtHeadData.h
  Author: Emilio Garcia-Fidalgo
  Date: 15/10/06 13:21
  Description: Implementation of 'mtHeadData' Message
=============================================================================
*/

#ifndef _MTHEADDATA_H
#define _MTHEADDATA_H

// Device Params

#include "Message.h"

typedef struct {       

    BYTE totalbytecount[2];
    BYTE devicetype;
    BYTE headstatus;
    BYTE sweepcode;
    BYTE hdctrl[2];
    BYTE rangescale[2];
    BYTE txntransmitter[4];
    BYTE gainsetting;
    BYTE slopesetting[2];
    BYTE adspan;
    BYTE adlow;
    BYTE headingoffset[2];
    BYTE adinterval[2];
    BYTE leftlimit[2];
    BYTE rightlimit[2];
    BYTE stepangle;
    BYTE bearing[2];
    BYTE dbytes[2];
} DevicePars;

class MtHeadData : public Message {

protected:
    DevicePars dp;                     // Copy of Sonar´s Params
    BYTE *rd;                          // Data
public:
    MtHeadData();
    void printPacket(bool);
    void receive(SerialPort *);

    // Access Functions

    SweepCode getSweepCode(void);      // Return Sweep Code about scan
    int getBearing(void);              // Return Sonar´s orientation
    int getDataLength(void);           // Return Number of Information Bytes
    BYTE *getDataBytes(void);          // Return Bytes of Data
};

#endif
