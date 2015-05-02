/*
=============================================================================
  Name: Command.h
  Author: Emilio Garcia-Fidalgo
  Date: 09/10/06 19:22
  Description: Abstract class Command
=============================================================================
*/

#ifndef _COMMAND_H
#define _COMMAND_H

#include "Packet.h"
#include "SerialPort.h"

class Command : public Packet {

protected:
    void base256(BYTE *, int, int);           // Pass an integer to Hexadecimal
    virtual void send(SerialPort *) = 0;         // Send through a Serial port
};

#endif
