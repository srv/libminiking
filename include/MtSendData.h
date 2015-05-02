/*
=============================================================================
  Name: MtSendData.h
  Author: Emilio Garcia-Fidalgo
  Date: 11/10/06 18:23
  Description: Implementation of 'mtSendData' command
=============================================================================
*/

#ifndef _MTSENDDATA_H
#define _MTSENDDATA_H

#include "Command.h"

class MtSendData : public Command {

public:
    MtSendData();
    void printPacket(bool);
    void send(SerialPort *);
};

#endif
