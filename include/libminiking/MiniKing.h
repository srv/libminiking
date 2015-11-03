/*
=============================================================================
  Name: MiniKing.h
  Author: Emilio Garcia-Fidalgo
  Date: 30/10/06 16:40
  Description: Main Library class
=============================================================================

Default Configuration for Sonar:
        Imaging Sonar
        Frequency: 675 Khz
        Range Scale: 30 Metres
        Scan Limits: Left = 0 ; Right = 0 (in gradians)
        ADSpan = 12 Db
        ADLow = 13 Db
        Initial Gain: 40%
        Resolution: Medium
        Bins: 300
        8 Data Bits
        Scan continuous
        Clockwise
        Normal mounted
        Motor Enabled
        Transmitter Enabled
        Only One Channel Operation
        Sonar has scanning motor
        Do not apply offsets
        Not pingpong, only one channel
        Don´t stare in a fixed direction
        Don´t ignore sensor
*/

#ifndef _MINIKING_H
#define _MINIKING_H

#include "libminiking/SonarDefs.h"
#include "libminiking/SerialPort.h"
#include "libminiking/IncludePackets.h"
#include "libminiking/Message.h"
#include "libminiking/Command.h"

class MiniKing {

private:
    SerialPort cp;              // RS232 Sonar Communication
    Config conf;             // Configuration sonar parameters
    VersionData vd;          // Version Data Information
    bool needData;           // Determine if it´s needed send an MtSendData command
    bool verbose;            // Shows all information about receiving and sending packets
    bool allReceived;        // To receive data in head1 or head2

    // Packets

    // Commands

    MtHeadCommand mtheadcommand;
    MtReboot mtreboot;
    MtSendData mtsenddata;
    MtSendVersion mtsendversion;
    MtSendBBUser mtsendbbuser;

    // Messages

    MtVersionData mtversiondata;
    MtAlive mtalive;
    MtBBUserData mtbbuserdata;
    MtHeadData mtheaddata1;
    MtHeadData mtheaddata2;
    PacketType receive(SerialPort *cp);      // General receive

public:
    MiniKing(char *, int);            // Constructor

    // Configuration Access functions

    void set8Bits(bool);             // Data bits of responses
    bool get8Bits(void);

    void setContinuous(bool);       // Sector Scan or Continuous
    bool getContinuous(void);

    void setInverted(bool);         // When sonar head is mounted inverted
    bool getInverted(void);

    void setMotorDisabled(bool);    // Disable motor
    bool getMotorDisabled(void);

    void setTransmitDisabled(bool); // Disable sonar trasmitter
    bool getTransmitDisabled(void);

    void setApplyOffset(bool);      // Direction is dinamically modified
    bool getApplyOffset(void);

    void setStare(bool);            // Stare in a fixed direction, marked as 'LeftLim'
    bool getStare(void);

    void setSonarType(SonarType);   // Imaging, Sidescan or Profiling
    SonarType getSonarType(void);

    void setFrequency(Frequency);   // Frequency in Khz
    Frequency getFrequency(void);

    void setRange(int);             // Sets Range Scale value in metres
    int getRange(void);

    void setLeftLim(int);           // Sets Left Limit for a Sector Scan
    float getLeftLim(void);

    void setRightLim(int);          // Sets Right Limit for a Sector Scan
    float getRightLim(void);

    void setADSpan(int);            // Parameter in DB
    int getADSpan(void);            // Parameter in DB

    void setADLow(int);             // Parameter in DB
    int getADLow(void);             // Parameter in DB

    void setGain(int);              // Set Initial gain head. In percentage (%)
    int getGain(void);

    void setResolution(Resolution); // Head Step Angle Size
    Resolution getResolution(void);

    void setBins(int);              // Number of Bins for each ping
    int getBins(void);

    // Version data access functions

    BoardType getBoardType(void);   // Return BoardType
    int getSerialNumber(void);      // Returns CPU Serial Number in sonar
    int getProgramLength(void);     // Returns Program Length
    int getChecksum(void);          // Returns Checksum

    // 'MtAlive' access functions

    bool hasParams(void);
    int getHeadTime(void);
    float getMotorPos(void);          // In degrees
    bool isCentering(void);
    bool isCentred(void);
    bool isMotoring(void);
    bool isMotorOn(void);
    bool isDir(void);
    bool isScan(void);
    bool configReceived(void);

    // 'MtBBUserData' access functions

    // LAN

    LANBitRate getLanBaudLow(void);
    LANBitRate getLanBaudHigh(void);

    LANSensitivity getSensitivityLow(void);
    LANSensitivity getSensitivityHigh(void);

    int getLanTimeout(void);

    // RS232 Telemetry

    BitRate getCOMBaudLow(void);
    BitRate getCOMBaudHigh(void);

    Parity getCOMParityLow(void);
    Parity getCOMParityHigh(void);

    DataBits getCOMDataBitsLow(void);
    DataBits getCOMDataBitsHigh(void);

    // AUX Telemetry

    BitRate getAUXBaudLow(void);
    BitRate getAUXBaudHigh(void);

    Parity getAUXParityLow(void);
    Parity getAUXParityHigh(void);

    DataBits getAUXDataBitsLow(void);
    DataBits getAUXDataBitsHigh(void);

    bool hasMotor(void);
    bool hasAux(void);
    bool hasRollSensor(void);

    SonarBlock *otherInfo(void);        // Access to another information of Sonar

    // 'MtHeadData access functions

    float getPosition(void);            // Return Sonar´s orientation
    int getDataLength(void);            // Return Number of Information Bytes

    // General

    void setDefaultConfig(void);        // Set sonar parametres to default
    void initSonar(void);               // Basic initialization procedure
    void reboot(void);                  // Reboots sonar
    void updateConfig(void);            // Update sonar´s parametres
    BYTE *getScanLine(void);            // Get a data scan
    void setVerboseMode(bool);          // Enables / Disables verbose mode

    bool isLeftLimit(void);             // Returns true if position is the left limit
    bool isRightLimit(void);            // Returns true if position is the right limit
};

#endif
