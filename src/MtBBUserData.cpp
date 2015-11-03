/*
=============================================================================
  Name: MtBBUserData.cpp
  Author: Emilio Garcia-Fidalgo
  Date: 15/10/06 1:04
  Description: Implementation of 'MtBBUserData' Message
=============================================================================
*/

#include "libminiking/MtBBUserData.h"

// Shows information contained in packet´s fields

void MtBBUserData::printPacket(bool complete) {

    cout << endl << "--mtBBUserData-- Packet" << endl << endl;

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
        printf("CK: %02X %02X\n", syb.ck[0], syb.ck[1]);
        printf("UserBBLen: %02X %02X\n\n", syb.userbbln[0], syb.userbbln[1]);
        printf("RS232 Baud Low: %02X %02X\n", bbb.a0baudlow[0], bbb.a0baudlow[1]);
        printf("RS232 Baud High: %02X %02X\n", bbb.a0baudhigh[0], bbb.a0baudhigh[1]);
        printf("RS232 Parity Low: %02X %02X\n", bbb.a0paritylow[0], bbb.a0paritylow[1]);
        printf("RS232 Parity High: %02X %02X\n", bbb.a0parityhigh[0], bbb.a0parityhigh[1]);
        printf("RS232 Data Bits Low: %02X %02X\n", bbb.a0databitslow[0], bbb.a0databitslow[1]);
        printf("RS232 Data Bits High: %02X %02X\n", bbb.a0databitshigh[0], bbb.a0databitshigh[1]);
        printf("Has Motor: %02X\n", snb.hasmotor);
        printf("Has Aux: %02X\n", snb.hasaux);
        printf("Has Roll Sensor: %02X\n", snb.hasrollsensor);

        cout << endl << "--Line Feed--" << endl;
    }
}

// Receive and store 'MtBBUserData' Message

void MtBBUserData::receive(SerialPort *cport) {

    try {

        // System BB Block

        syb.surfacectrl = cport->read();
        syb.d1 = cport->read();
        cport->read(syb.ck,2);
        cport->read(syb.userbbln,2);

        for (int i = 0; i < 6; i++)
            cport->read();

        // Baud Block

        cport->read(bbb.lanbaudlow, 2);
        cport->read(bbb.lanbaudhigh, 2);
        cport->read(bbb.lansensitivitylow, 2);
        cport->read(bbb.lansensitivityhigh, 2);
        cport->read(bbb.lantimeout, 2);

        cport->read(bbb.a0baudlow, 2);
        cport->read(bbb.a0baudhigh, 2);
        cport->read(bbb.a0paritylow, 2);
        cport->read(bbb.a0parityhigh, 2);
        cport->read(bbb.a0databitslow, 2);
        cport->read(bbb.a0databitshigh, 2);

        cport->read(bbb.a1baudlow, 2);
        cport->read(bbb.a1baudhigh, 2);
        cport->read(bbb.a1paritylow, 2);
        cport->read(bbb.a1parityhigh, 2);
        cport->read(bbb.a1databitslow, 2);
        cport->read(bbb.a1databitshigh, 2);

        // Sonar Block

        snb.hasmotor = cport->read();
        snb.d1 = cport->read();
        snb.hasaux = cport->read();
        snb.d2 = cport->read();
        snb.hasrollsensor = cport->read();
        snb.d3 = cport->read();

        cport->read(snb.rollmultiplier, 2);
        cport->read(snb.rolldivisor, 2);
        cport->read(snb.rolloffset, 2);

        snb.haspresure = cport->read();
        snb.d4 = cport->read();

        cport->read(snb.pressmultiplier, 2);
        cport->read(snb.pressdivisor, 2);
        cport->read(snb.pressoffset, 2);

        cport->read(snb.tempmultiplier, 2);
        cport->read(snb.tempdivisor, 2);
        cport->read(snb.tempoffset, 2);

        snb.fireboth = cport->read();
        snb.d5 = cport->read();
        snb.emulatev18 = cport->read();
        snb.d6 = cport->read();
        snb.boardrevision = cport->read();
        snb.d7 = cport->read();
        cport->read(snb.emulatev18node, 2);
        snb.aux1sec = cport->read();
        snb.d10 = cport->read();
        snb.dualaxis = cport->read();
        snb.d11 = cport->read();
        snb.compassstabilised = cport->read();
        snb.d12 = cport->read();
        snb.rs485 = cport->read();
        snb.d13 = cport->read();

        cport->read(snb.tx1, 2);
        cport->read(snb.tx2, 2);
        cport->read(snb.rx1, 2);
        cport->read(snb.rx2, 2);
        cport->read(snb.slope1, 2);
        cport->read(snb.slope2, 2);
        cport->read(snb.prftimecal1, 2);
        cport->read(snb.prftimecal2, 2);
        cport->read(snb.sontimecal1, 2);
        cport->read(snb.sontimecal2, 2);

        snb.v4mode = cport->read();
        snb.d14 = cport->read();

        cport->read(snb.motorpanconstant, 2);
        cport->read(snb.maxspeedpan, 2);
        cport->read(snb.mechllpan, 2);
        cport->read(snb.mechrlpan, 2);

        cport->read(snb.motortiltconstant, 2);
        cport->read(snb.maxspeedtilt, 2);
        cport->read(snb.mechlltilt, 2);
        cport->read(snb.mechrltilt, 2);

        cport->read(snb.txdcr1chan1, 12);
        cport->read(snb.txdcr1chan2, 12);
        cport->read(snb.txdcr2chan1, 12);
        cport->read(snb.txdcr2chan2, 12);

        cport->read(snb.elscancode, 2);

        snb.dualsynth = cport->read();
        snb.d15 = cport->read();

        cport->read(snb.specials, 8);

        for (int i = 0; i < 64; i++)
            cport->read();

        // Line Feed

        lfeed = cport->read();
    }
    catch (runtime_error &e) {        // Error in timeouts or bytes
        cout << e.what() << endl;
    }
}

int MtBBUserData::getHeadClock(void) { return base10(syb.ck, 2); }
int MtBBUserData::getBlocksLength(void) { return base10(syb.userbbln, 2); }                

// Telemetry

LANBitRate MtBBUserData::getLanBaudLow(void) { return (LANBitRate)base10(bbb.lanbaudlow, 2); }
LANBitRate MtBBUserData::getLanBaudHigh(void) { return (LANBitRate)base10(bbb.lanbaudhigh, 2); }

LANSensitivity MtBBUserData::getSensitivityLow(void){ return (LANSensitivity)base10(bbb.lansensitivitylow, 2); }
LANSensitivity MtBBUserData::getSensitivityHigh(void){ return (LANSensitivity)base10(bbb.lansensitivityhigh, 2); }

int MtBBUserData::getLanTimeout(void) { return base10(bbb.lantimeout, 2); }

BitRate MtBBUserData::getA0BaudLow(void){

    switch (base10(bbb.a0baudlow, 2)) {
    case 0x01:
        return br2400;
    case 0x02:
        return br4800;
    case 0x03:
        return br9600;
    case 0x04:
        return br19200;
    case 0x05:
        return br38400;
    case 0x06:
        return br57600;
    case 0x07:
        return br115200;
    default:
        return brdefault;
    }
}

BitRate MtBBUserData::getA0BaudHigh(void){

    switch (base10(bbb.a0baudhigh, 2)) {
    case 0x01:
        return br2400;
    case 0x02:
        return br4800;
    case 0x03:
        return br9600;
    case 0x04:
        return br19200;
    case 0x05:
        return br38400;
    case 0x06:
        return br57600;
    case 0x07:
        return br115200;
    default:
        return brdefault;
    }
}

Parity MtBBUserData::getA0ParityLow(void){ return (Parity)base10(bbb.a0paritylow, 2); }
Parity MtBBUserData::getA0ParityHigh(void){ return (Parity)base10(bbb.a0parityhigh, 2); }

DataBits MtBBUserData::getA0DataBitsLow(void){

    if (base10(bbb.a0databitslow, 2) == 0)
        return db8;
    else
        return db7;
}

DataBits MtBBUserData::getA0DataBitsHigh(void){

    if (base10(bbb.a0databitshigh, 2) == 0)
        return db8;
    else
        return db7;
}

BitRate MtBBUserData::getA1BaudLow(void){ 

    switch (base10(bbb.a1baudlow, 2)) {
    case 0x01:
        return br2400;
    case 0x02:
        return br4800;
    case 0x03:
        return br9600;
    case 0x04:
        return br19200;
    case 0x05:
        return br38400;
    case 0x06:
        return br57600;
    case 0x07:
        return br115200;
    default:
        return brdefault;
    }
}

BitRate MtBBUserData::getA1BaudHigh(void){

    switch (base10(bbb.a1baudhigh, 2)) {
    case 0x01:
        return br2400;
    case 0x02:
        return br4800;
    case 0x03:
        return br9600;
    case 0x04:
        return br19200;
    case 0x05:
        return br38400;
    case 0x06:
        return br57600;
    case 0x07:
        return br115200;
    default:
        return brdefault;
    }
}

Parity MtBBUserData::getA1ParityLow(void){ return (Parity)base10(bbb.a1paritylow, 2); }
Parity MtBBUserData::getA1ParityHigh(void){ return (Parity)base10(bbb.a1parityhigh, 2); }

DataBits MtBBUserData::getA1DataBitsLow(void) { 

    if (base10(bbb.a1databitslow, 2) == 0)
        return db8;
    else
        return db7;
}

DataBits MtBBUserData::getA1DataBitsHigh(void){ 

    if (base10(bbb.a1databitshigh, 2) == 0)
        return db8;
    else
        return db7;
}

// General Sonar Options

bool MtBBUserData::hasMotor(void){ return snb.hasmotor; }
bool MtBBUserData::hasAux(void) { return snb.hasaux; }
bool MtBBUserData::hasRollSensor(void) { return snb.hasrollsensor; } 
