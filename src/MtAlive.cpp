/*
=============================================================================
  Name: MtAlive.cpp
  Author: Emilio Garcia-Fidalgo
  Date: 13/10/06 19:04
  Description: Implementation of 'mtAlive' Message
=============================================================================
*/

#include "libminiking/MtAlive.h"

// Shows information contained in packet´s fields

void MtAlive::printPacket(bool complete) {

    cout << endl << "--mtAlive-- Packet" << endl << endl;

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
        printf("Params: %02X\n", willsend);
        printf("Head Time: %02X %02X %02X %02X\n", headtime[0], headtime[1], headtime[2], headtime[3]);
        printf("Motor Pos: %02X %02X\n", motorpos[0], motorpos[1]);
        printf("Head Info: %02X\n", headinf);

        cout << endl << "--Line Feed--" << endl;
    }
}

// Receive and store 'MtAlive' Message

void MtAlive::receive(SerialPort *cport) {

    try {

        // Params

        willsend = cport->read();

        // Head Time

        cport->read(headtime, 4);

        // Motor Position

        cport->read(motorpos, 2);

        // Information about Motor

        headinf = cport->read();

        // Line Feed

        lfeed = cport->read();
    }
    catch (runtime_error &e) {        // Error in timeouts or bytes
        cout << e.what() << endl;
    }
}

bool MtAlive::hasParams(void) {

    if (willsend == 0)
        return true;
    else
        return false;
}

int MtAlive::getHeadTime(void) {
    
    return base10(headtime, 4);
}

int MtAlive::getMotorPos(void) {
    
    return base10(motorpos, 2);
}

bool MtAlive::isCentering(void) {

    if ((headinf & 0x01) == 0)
        return false;
    else
        return true;
}

bool MtAlive::isCentred(void) {

    if ((headinf & 0x02) == 0)
        return false;
    else
        return true;
}

bool MtAlive::isMotoring(void) {

    if ((headinf & 0x04) == 0)
        return false;
    else
        return true;
}

bool MtAlive::isMotorOn(void) {

    if ((headinf & 0x08) == 0)
        return false;
    else
        return true;
}

bool MtAlive::isDir(void) {

    if ((headinf & 0x10) == 0)
        return false;
    else
        return true;
}

bool MtAlive::isScan(void) {

    if ((headinf & 0x20) == 0)
        return false;
    else
        return true;
}

bool MtAlive::noParams(void) {

    if ((headinf & 0x40) == 0)
        return false;
    else
        return true;
}

bool MtAlive::paramsReceived(void) {

    if ((headinf & 0x80) == 0)
        return false;
    else
        return true;
}
