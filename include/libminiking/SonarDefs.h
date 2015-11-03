/*
=============================================================================
  Name: SonarDefs.h
  Author: Emilio Garcia-Fidalgo
  Date: 09/10/06 16:38
  Description: Header that includes some Sonar´s definitions and macros.
=============================================================================
*/

#ifndef _SONARDEFS_H
#define _SONARDEFS_H

// Macros

#define INITCHAR '@'     // Initial character of each packet
#define ENDCHAR 0x0A     // End of packet
#define PCADDR 0xFF      // User Program´s address in serial or air interface
#define SNADDR 0x02      // Sonar´s address. Default: Imaging Sonar

// Data type

typedef unsigned char BYTE;

// Message and Command types

typedef enum {

    mtSendVersion  = 0x17,
    mtVersionData  = 0x01,
    mtSendBBUser   = 0x18,
    mtBBUserData   = 0x06,
    mtReboot       = 0x10,
    mtHeadCommand  = 0x13,
    mtAlive        = 0x04,
    mtSendData     = 0x19,
    mtHeadData     = 0x02,
    errorPacket    = 0
} PacketType;

// Possible frequecies in sonar

typedef enum {
    f0 = 0,
    f325 = 325,
    f580 = 580,
    f675 = 675,
    f795 = 795,
    f935 = 935,
    f1210 = 1210,
    f200 = 200,
    f1700 = 1700,
    f2000 = 2000,
    f500 = 500,
    f1500 = 1500,
    f295 = 295
} Frequency;

// Different Board Types

typedef enum { 

    AIF = 0,
    Sonar = 0x01,
    Bathy = 0x02,
    Others = 0x03,
} BoardType;

// Possible LAN Bit Rates

typedef enum {      

    lb25,
    lb125,
    lb625,
    lb312,
    lb156,
    lb78,
} LANBitRate;

// LAN Sensitivity

typedef enum {      

    Increase,
    Decrease,
    Neutral
} LANSensitivity;

// Sonar Types

typedef enum {      

    ImagingSonar    = 0x02,
    SidescanSonar   = 0x03,
    ProfilingSonar  = 0x05
} SonarType;

// Posible Scan Line Resolution

typedef enum {       

    Low = 0x20,
    Medium = 0x10,
    High = 0x08,
    Ultimate = 0x04
} Resolution;

// Sonar configuration parameters

typedef struct {

    bool hdctrlbits[16];      // Bits of 'hdctrl' field
    SonarType sonartype;      // Sonar Type
    Frequency frequency;      // Channel Frequency
    int rangescale;           // Maximum distance to scan in metres
    int leftlim;              // Left Limit for a Sector Scan in Gradians
    int rightlim;             // Right Limit for a Sector Scan in Gradians
    int adspan;               // Controls sonar´s sensitive
    int adlow;                // Controls sonar´s sensitive
    int gain;                 // Initial Gain
    Resolution resolution;    // Step Angle Size
    int bins;                 // Number of bins for each ping
} Config;

// Store structure for version data

typedef struct {

    Frequency fr;
    BoardType bt;
    int serialnumber;
    int programlength;
    int checksum;
} VersionData;

// Sweep Code Types

typedef enum {

    ScanningNormal = 0,
    ScanLeftLimit = 0x01,
    ScanRightLimit = 0x02,
    RESERVED1,
    RESERVED2,
    ScanCentre = 0x05
} SweepCode;

// General System Information

typedef struct {  

    BYTE surfacectrl;                   // Default: 255
    BYTE d1;
    BYTE ck[2];                         // Clock
    BYTE userbbln[2];                   // Total number of bytes in 'syb', 'bbb' and 'snb'
} SystemBBBlock;

// Telemetry information

typedef struct {  

    // LAN Settings

    BYTE lanbaudlow[2];                 // Bit Rate Low
    BYTE lanbaudhigh[2];                // Bit Rate High
    BYTE lansensitivitylow[2];          // Sensitivity Low
    BYTE lansensitivityhigh[2];         // Sensitivity High
    BYTE lantimeout[2];                 // Timeout, should be '3'

    // RS232 Port

    BYTE a0baudlow[2];                  // Bit Rate Low
    BYTE a0baudhigh[2];                 // Bit Rate High
    BYTE a0paritylow[2];                // Parity Low
    BYTE a0parityhigh[2];               // Parity High
    BYTE a0databitslow[2];              // Data Bits Low
    BYTE a0databitshigh[2];             // Data Bits High

    // AUX Port

    BYTE a1baudlow[2];                  // Bit Rate Low
    BYTE a1baudhigh[2];                 // Bit Rate High
    BYTE a1paritylow[2];                // Parity Low
    BYTE a1parityhigh[2];               // Parity High
    BYTE a1databitslow[2];              // Data Bits Low
    BYTE a1databitshigh[2];             // Data Bits High
} BaudBBBlock;

// General Head Information

typedef struct {

    BYTE hasmotor;
    BYTE d1;
    BYTE hasaux;
    BYTE d2;
    BYTE hasrollsensor;
    BYTE d3;
    BYTE rollmultiplier[2];
    BYTE rolldivisor[2];
    BYTE rolloffset[2];
    BYTE haspresure;
    BYTE d4;
    BYTE pressmultiplier[2];
    BYTE pressdivisor[2];
    BYTE pressoffset[2];
    BYTE tempmultiplier[2];
    BYTE tempdivisor[2];
    BYTE tempoffset[2];
    BYTE fireboth;
    BYTE d5;
    BYTE emulatev18;
    BYTE d6;
    BYTE boardrevision;
    BYTE d7;
    BYTE emulatev18node[2];
    BYTE aux1sec;
    BYTE d10;
    BYTE dualaxis;
    BYTE d11;
    BYTE compassstabilised;
    BYTE d12;
    BYTE rs485;
    BYTE d13;
    BYTE tx1[2];
    BYTE tx2[2];
    BYTE rx1[2];
    BYTE rx2[2];
    BYTE slope1[2];
    BYTE slope2[2];
    BYTE prftimecal1[2];
    BYTE prftimecal2[2];
    BYTE sontimecal1[2];
    BYTE sontimecal2[2];
    BYTE v4mode;
    BYTE d14;
    BYTE motorpanconstant[2];
    BYTE maxspeedpan[2];
    BYTE mechllpan[2];
    BYTE mechrlpan[2];
    BYTE motortiltconstant[2];
    BYTE maxspeedtilt[2];
    BYTE mechlltilt[2];
    BYTE mechrltilt[2];
    BYTE txdcr1chan1[12];
    BYTE txdcr1chan2[12];
    BYTE txdcr2chan1[12];
    BYTE txdcr2chan2[12];
    BYTE elscancode[2];
    BYTE dualsynth;
    BYTE d15;
    BYTE specials[8];
} SonarBlock;

#endif
