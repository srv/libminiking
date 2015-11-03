/*
=============================================================================
  Name: MtReboot.h
  Author: Emilio Garcia-Fidalgo
  Date: 11/10/06 17:50
  Description: Implementation of 'mtReboot' command
=============================================================================
*/

#ifndef _MTREBOOT_H
#define _MTREBOOT_H

#include "libminiking/Command.h"

class MtReboot : public Command {

public:
    MtReboot();
    void printPacket(bool);
    void send(SerialPort *);
};

#endif
