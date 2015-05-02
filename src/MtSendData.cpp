/*
=============================================================================
  Name: MtSendData.cpp
  Author: Emilio Garcia-Fidalgo
  Date: 11/10/06 18:34
  Description: Implementation of 'mtSendData' command
=============================================================================
*/

#include "MtSendData.h"
#include <ctime>

// Constructor

MtSendData::MtSendData() {

    // Header

    hdr = INITCHAR;

    // Hexadecimal length

    hexln[0] = 0x30;
    hexln[1] = 0x30;
    hexln[2] = 0x30;
    hexln[3] = 0x43;

    // Binary length

    binln[0] = 0x0C;
    binln[1] = 0x00;

    // Addresses

    sid = PCADDR;
    did = SNADDR;

    // Message Field Count

    countmsg = 0x07;

    // Message Field

    ptype = mtSendData;
    sequence = 0x80;
    node = SNADDR;

    // Footer

    lfeed = ENDCHAR;
}

// Shows information contained in packet´s fields  

void MtSendData::printPacket(bool complete) {

    cout << endl << "--mtSendData-- Packet" << endl << endl;

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

        cout << endl << "--Line Feed--" << endl;
    }
}

// Sends an mtSendData packet through 'cport'

void MtSendData::send(SerialPort *cport) {

    BYTE frame[18];

    // Header

    frame[0] = hdr;

    // Hexadecimal length

    frame[1] = hexln[0];
    frame[2] = hexln[1];
    frame[3] = hexln[2];
    frame[4] = hexln[3];

    // Binary length

    frame[5] = binln[0];
    frame[6] = binln[1];

    // Addresses

    frame[7] = sid;
    frame[8] = did;

    // Message Field Count

    frame[9] = countmsg;

    // Message Field

    frame[10] = ptype;
    frame[11] = sequence;
    frame[12] = node;

    // Calculate local time in miliseconds

    time_t tt;
    struct tm *thetime;

    tt = time(NULL);
    thetime = localtime(&tt);

    int milisecs = ((thetime->tm_hour * 3600) + (thetime->tm_min * 60) + (thetime->tm_sec)) * 1000;

    // Pass this number to Base 256 and store it in 'frame'

    base256(&frame[13], milisecs, 4);

    // Footer

    frame[17] = lfeed;

    for (int i = 0; i < 18; i++)
        cport->write(frame[i]);
}
