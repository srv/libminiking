/*
=============================================================================
  Name: MtSendBBUser.h
  Author: Emilio Garcia-Fidalgo
  Date: 10/10/06 20:34
  Description: Implementation of 'mtSendBBUser' command
=============================================================================
*/

#ifndef _MTSENDBBUSER_H
#define _MTSENDBBUSER_H

#include "Command.h"

class MtSendBBUser : public Command {

public:
    MtSendBBUser();
    void printPacket(bool);
    void send(SerialPort *);
};

#endif
