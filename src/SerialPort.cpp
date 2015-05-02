/*
=============================================================================
  Name: SerialPort.cpp
  Author: Emilio Garcia-Fidalgo
  Date: 05/10/06 14:37
  Description: Class for a RS232 Communication.
=============================================================================
*/

#include "SerialPort.h"

// Constructor

SerialPort::SerialPort(char* Name, BitRate br, DataBits db, Parity par, StopBits sb, int timeout, bool hs)
    :
      port_(io_, Name)
{
    setBitRate(br);
    setParity(par);
    setDataBits(db);
    setStopBits(sb);

    serial_port_base::flow_control FLOW(serial_port_base::flow_control::none);
    port_.set_option(FLOW);
}

// Destructor

SerialPort::~SerialPort()
{
    port_.close();
}

// Return port´s bit rate
unsigned long SerialPort::getBitRate(void)
{
    return br;
}

// Set port´s bit rate
void SerialPort::setBitRate(BitRate br_)
{
    br = br_;

    serial_port_base::baud_rate BAUD(br);
    port_.set_option(BAUD);
}

// Return port´s data bits
DataBits SerialPort::getDataBits(void)
{
    return db;
}

// Set port´s data bits
void SerialPort::setDataBits(DataBits db_)
{
    db = db_;

    serial_port_base::character_size CSZ(db_);
    port_.set_option(CSZ);
}

// Return port´s parity
Parity SerialPort::getParity(void)
{
    return par;
}

// Set port´s parity
void SerialPort::setParity(Parity par_)
{
    par = par_;

    serial_port_base::parity PAR(serial_port_base::parity::none);
    port_.set_option(PAR);
}

// Return port´s stop bits
StopBits SerialPort::getStopBits(void)
{
    return sb;
}

// Set port´s stop bits
void SerialPort::setStopBits(StopBits sb_)
{
    sb = sb;

    serial_port_base::stop_bits SBITS(serial_port_base::stop_bits::one);
    port_.set_option(SBITS);
}

// Read a character from serial port.
unsigned char SerialPort::read(void)
{
    unsigned char c;
    boost::asio::read(port_, boost::asio::buffer(&c, 1));
    return c;
}

// Write a character to serial port.
void SerialPort::write(unsigned char ch)
{
    unsigned char c = ch;
    boost::asio::write(port_, boost::asio::buffer(&c, 1));
}

// Read 'nch' bytes from port and store them in 'buffer'
unsigned long SerialPort::read(unsigned char *buffer, int nch)
{
    return boost::asio::read(port_, boost::asio::buffer(buffer, nch));
}
