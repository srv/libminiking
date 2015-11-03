/*
=============================================================================
  Name: MtVersionData.cpp
  Author: Emilio Garcia-Fidalgo
  Date: 13/10/06 17:55
  Description: Implementation of 'mtVersionData' Message
=============================================================================
*/

#include "libminiking/MtVersionData.h"

// Shows information contained in packet´s fields

void MtVersionData::printPacket(bool complete) {

    cout << endl << "--mtVersionData-- Packet" << endl << endl;

    if (complete) {
        printf("Header: %02X\n", hdr);
        printf("Hex Length: %02X %02X %02X %02X\n", hexln[0], hexln[1], hexln[2], hexln[3]);
        printf("Bin Length: %02X %02X\n", binln[0], binln[1]);
        printf("SID: %02X\n", sid);
        printf("DID: %02X\n", did);
        printf("Count MSG: %02X\n", countmsg);
        printf("Packet Type: %02X\n", ptype);
        printf("Sequence: %02X\n", sequence);
        printf("Node: %02X\n", node);
        printf("CPUID Frequencies: %02X\n", cpuid.frequencies);
        printf("CPUID BoardType: %02X\n", cpuid.boardtype);
        printf("CPUID Serial Number: %02X %02X\n", cpuid.serialnumber[0], cpuid.serialnumber[1]);
        printf("Program Legth: %02X %02X %02X %02X\n", programln[0], programln[1], programln[2], programln[3]);
        printf("Checksum: %02X %02X\n", checksum[0], checksum[1]);
        printf("Node ID: %02X\n", nodeid);

        cout << endl << "--Line Feed--" << endl;
    }
}

// Receive and store 'MtVersionData' Message

void MtVersionData::receive(SerialPort *cport) {

    try {

        cpuid.frequencies = cport->read();

        cpuid.boardtype = cport->read();

        cport->read(cpuid.serialnumber, 2);

        // Program Length

        cport->read(programln, 4);

        // Checksum

        cport->read(checksum, 2);

        // Node ID

        nodeid = cport->read();

        // Line Feed

        lfeed = cport->read();
    }
    catch (runtime_error &e) {        // Error in timeouts or bytes
        cout << e.what() << endl;
    }
}

// Analizes 'frequency' BYTE and returns enumerate type

Frequency MtVersionData::getFrequency(void) {

    switch(cpuid.frequencies) {
    case 0x01:
        return f325;
    case 0x02:
        return f580;
    case 0x03:
        return f675;
    case 0x04:
        return f795;
    case 0x05:
        return f935;
    case 0x06:
        return f1210;
    case 0x07:
        return f200;
    case 0x08:
        return f1700;
    case 0x09:
        return f2000;
    case 0x0A:
        return f500;
    case 0x0B:
        return f1500;
    case 0x0C:
        return f295;
    default:
        return f0;
    }
}

// Analizes 'BoardType' BYTE and returns enumerate

BoardType MtVersionData::getBoardType(void) {

    BYTE mask = 0x0F;
    BYTE res = cpuid.boardtype & mask;

    switch (res) {
    case 0:
        return AIF;
    case 0x01:
        return Sonar;
    case 0x02:
        return Bathy;
    default:
        return Others;
    }
}

int MtVersionData::getSerialNumber(void) { return base10(cpuid.serialnumber, 2); }

int MtVersionData::getProgramLength(void) { return base10(programln, 4); }

int MtVersionData::getChecksum(void) { return base10(checksum, 2); }
