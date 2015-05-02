/*
=============================================================================
  Name: MtSendVersion.h
  Author: Emilio Garcia-Fidalgo
  Date: 10/10/06 18:29
  Description: Implementation of 'mtSendVersion' command
=============================================================================
*/

#ifndef _MTSENDVERSION_H
#define _MTSENDVERSION_H

#include "Command.h"

class MtSendVersion : public Command {

public:
    MtSendVersion();
    void printPacket(bool);
    void send(SerialPort *);
};

#endif
