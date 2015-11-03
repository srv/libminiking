/*
=============================================================================
  Name: Message.h
  Author: Emilio Garcia-Fidalgo
  Date: 09/10/06 19:44
  Description: Abstract class Message
=============================================================================
*/

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "libminiking/Packet.h"
#include "libminiking/SerialPort.h"

class Message : public Packet {

protected:
    int base10(BYTE *, int);              // Pass an Hexadecimal to integer
    virtual void receive(SerialPort *) = 0;  // Receive from a Serial port
};

#endif
