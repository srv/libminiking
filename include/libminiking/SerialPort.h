/*
=============================================================================
  Name: SerialPort.h
  Author: Emilio Garcia-Fidalgo
  Date: 05/10/06 14:00
  Description: Class for a RS232 Communication.
=============================================================================
*/

#ifndef _SERIALPORT_H
#define _SERIALPORT_H

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

using namespace std;
using namespace boost::asio;

// Parity

typedef enum
{
    None = 0,
    Odd,
    Even,
    Mark,
    Space
} Parity;

// Data Bits

typedef enum
{
    db4 = 4,
    db5,
    db6,
    db7,
    db8
} DataBits;

// Stop Bits
typedef enum
{
    sb1 = 0,
    sb15,
    sb2
} StopBits;

// Bit Rates

typedef enum
{
    brdefault = 0,
    br110 = 110,
    br300 = 300,
    br600 = 600,
    br1200 = 1200,
    br2400 = 2400,
    br4800 = 4800,
    br9600 = 9600,
    br19200 = 19200,
    br38400 = 38400,
    br56000 = 56000,
    br57600 = 57600,
    br115200 = 115200,
    br256000 = 256000
} BitRate;

class SerialPort
{

private:
    BitRate br;
    DataBits db;
    Parity par;
    StopBits sb;

    // Port handle objects
    io_service io_;
    serial_port port_;

public:

    // Contructor & Destructor
    SerialPort(char* , BitRate, DataBits, Parity, StopBits, int, bool);
    ~SerialPort();

    // General functions

    unsigned long getBitRate(void);
    void setBitRate(BitRate);

    DataBits getDataBits(void);
    void setDataBits(DataBits);

    Parity getParity(void);
    void setParity(Parity);

    StopBits getStopBits(void);
    void setStopBits(StopBits);

    // I/O functions

    unsigned char read(void);
    unsigned long read(unsigned char *, int ch);
    void write(unsigned char);
};

#endif
