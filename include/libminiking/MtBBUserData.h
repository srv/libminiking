/*
=============================================================================
  Name: MtBBUserData.h
  Author: Emilio Garcia-Fidalgo
  Date: 14/10/06 13:46
  Description: Implementation of 'mtBBUserData' Message
=============================================================================
*/

#ifndef _MTBBUSERDATA_H
#define _MTBBUSERDATA_H

#include "libminiking/Message.h"

class MtBBUserData : public Message {

protected:
    SystemBBBlock  syb;         // General features
    BaudBBBlock    bbb;         // Telemetry settings
    SonarBlock     snb;         // Sonar Profiler Block
    friend class MiniKing;      // To access SonarBlock
public:
    void printPacket(bool);
    void receive(SerialPort *);

    // Access Functions

    // System

    int getHeadClock(void);
    int getBlocksLength(void);

    // Telemetry

    // LAN

    LANBitRate getLanBaudLow(void);
    LANBitRate getLanBaudHigh(void);

    LANSensitivity getSensitivityLow(void);
    LANSensitivity getSensitivityHigh(void);

    int getLanTimeout(void);

    // RS232 Port

    BitRate getA0BaudLow(void);
    BitRate getA0BaudHigh(void);

    Parity getA0ParityLow(void);
    Parity getA0ParityHigh(void);

    DataBits getA0DataBitsLow(void);
    DataBits getA0DataBitsHigh(void);

    // AUX Port

    BitRate getA1BaudLow(void);
    BitRate getA1BaudHigh(void);

    Parity getA1ParityLow(void);
    Parity getA1ParityHigh(void);

    DataBits getA1DataBitsLow(void);
    DataBits getA1DataBitsHigh(void);

    // General Sonar Options

    bool hasMotor(void);
    bool hasAux(void);
    bool hasRollSensor(void);
};

#endif
