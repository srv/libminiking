/*
=============================================================================
  Name: MtHeadCommand.h
  Author: Emilio Garcia-Fidalgo
  Date: 11/10/06 19:02
  Description: Implementation of 'mtHeadCommand' command
=============================================================================
*/

#ifndef _MTHEADCOMMAND_H
#define _MTHEADCOMMAND_H

#include "libminiking/Command.h"

// This structure stores all parameter information

typedef struct { 

    BYTE hdctrl[2];            // Controlling head operation
    BYTE hdtype;               // Device or Head type. Default: Imaging Sonar
    BYTE tx1[4];               // Channel 1 Transmit Frequency
    BYTE tx2[4];               // Channel 2 Transmit Frequency
    BYTE rx1[4];               // Channel 1 Receive Frecuency
    BYTE rx2[4];               // Channel 2 Receive Frecuency
    BYTE txpulselen[2];        // Length of the sonar trasmit pulse
    BYTE rangescale[2];        // Maximun distance
    BYTE leftlim[2];           // Left Limit
    BYTE rightlim[2];          // Right Limit
    BYTE adspan;               // Control the mapping of the received sonar echo amplitude
    BYTE adlow;                // Control the mapping of the received sonar echo amplitude
    BYTE igain1;               // Initial Gain of the receiver, Channel 1
    BYTE igain2;               // Initial Gain of the receiver, Channel 2
    BYTE slope1[2];            // Compensation in channel 1
    BYTE slope2[2];            // Compensation in channel 2
    BYTE motime;               // High speed limit of scanning motor in unit of 10 nanosecs
    BYTE stepsize;             // Sonar Resolution
    BYTE adinterval[2];        // Define the sampling interval of each Range Bin
    BYTE nbins[2];             // Number of bin to create response packet
    BYTE maxadbuff[2];         // Default Value
    BYTE lockout[2];           // Blankig Time
    BYTE minoraxis[2];         // Default Value
    BYTE majaxispan;           // Default Value
    BYTE ctl2;                 // Additional sonar control functions
    BYTE scanz[2];             // For special devices
} HeadParameterInfo;

class MtHeadCommand : public Command {

protected:
    BYTE mtheadcommandtype;   // Specifies wheter packet includes a V3B Block
    HeadParameterInfo hpi;    // Structure that contains all parameters
    Config *cf;               // Configuration to send

public:
    MtHeadCommand(Config *);
    void printPacket(bool);
    void send(SerialPort *);
    void setConfig(Config *); // Sets the 'Config' structure where get the data
};

#endif
