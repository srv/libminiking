/*
=============================================================================
  Name: MtSendBBUser.cpp
  Author: Emilio Garcia-Fidalgo
  Date: 11/10/06 17:48
  Description: Implementation of 'mtSendBBUser' command
=============================================================================
*/

#include "MtSendBBUser.h"

// Constructor

MtSendBBUser::MtSendBBUser() {

    // Header

    hdr = INITCHAR;

    // Hexadecimal length

    hexln[0] = 0x30;
    hexln[1] = 0x30;
    hexln[2] = 0x30;
    hexln[3] = 0x38;

    // Binary length

    binln[0] = 0x08;
    binln[1] = 0x00;

    // Addresses

    sid = PCADDR;
    did = SNADDR;

    // Message Field Count

    countmsg = 0x03;

    // Message Field

    ptype = mtSendBBUser;
    sequence = 0x80;
    node = SNADDR;

    // Footer

    lfeed = ENDCHAR;
}

// Shows information contained in packet´s fields  

void MtSendBBUser::printPacket(bool complete) {

    cout << endl << "--mtSendBBUser-- Packet" << endl << endl;

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

// Sends an mtSendBBUser packet through 'cport'

void MtSendBBUser::send(SerialPort *cport) {

    BYTE frame[14];

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

    // Footer

    frame[13] = lfeed;

    for (int i = 0; i < 14; i++)
        cport->write(frame[i]);
}
