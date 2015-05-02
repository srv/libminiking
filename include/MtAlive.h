/*
=============================================================================
  Name: MtAlive.h
  Author: Emilio Garcia-Fidalgo
  Date: 13/10/06 18:53
  Description: Implementation of 'mtAlive' Message
=============================================================================
*/

#ifndef _MTALIVE_H
#define _MTALIVE_H

#include "Message.h"

class MtAlive : public Message {

protected:
    BYTE willsend;            // The device has params or not
    BYTE headtime[4];         // Time in ms since head power on
    BYTE motorpos[2];         // Current position in 1/16 Gradians
    BYTE headinf;             // Information about sonar
public:
    void printPacket(bool);
    void receive(SerialPort *);

    // Access Functions

    bool hasParams(void);     // Returns true if Sonar had params
    int getHeadTime(void);    // Time in sonar
    int getMotorPos(void);    // Motor position

    // Hdctrl info

    bool isCentering(void);     // Returns true if Sonar is in centering operation
    bool isCentred(void);       // Returns true if Sonar is in centre position
    bool isMotoring(void);      // Returns true if Sonar´s motor is in moving
    bool isMotorOn(void);       // Returns true if Sonar´s motor is on
    bool isDir(void);           // Returns true if transducer is off centre
    bool isScan(void);          // Returns true if Sonar is in a scanning operation
    bool noParams(void);        // Returns true if Sonar hasn´t got params
    bool paramsReceived(void);  // Returns true if params has been received by the sonar
};

#endif
