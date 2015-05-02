/*
=============================================================================
  Name: MtHeadCommand.cpp
  Author: Emilio Garcia-Fidalgo
  Date: 12/10/06 15:29
  Description: Implementation of 'mtHeadCommand' command
=============================================================================
*/

#include "MtHeadCommand.h"
#include <cmath>

// Constructor

MtHeadCommand::MtHeadCommand(Config *cfg) {

    // Header

    hdr = INITCHAR;

    // Hexadecimal length

    hexln[0] = 0x30;
    hexln[1] = 0x30;
    hexln[2] = 0x33;
    hexln[3] = 0x43;

    // Binary length

    binln[0] = 0x3C;
    binln[1] = 0x00;

    // Addresses

    sid = PCADDR;
    did = SNADDR;

    // Message Field Count

    countmsg = 0x37;

    // Message Field

    ptype = mtHeadCommand;
    sequence = 0x80;
    node = SNADDR;

    // Head Command type

    mtheadcommandtype = 0x01;

    // Configuration structure

    cf = cfg;

    // Footer

    lfeed = ENDCHAR;
}

// Shows information contained in packet´s fields

void MtHeadCommand::printPacket(bool complete) {

    cout << endl << "--mtHeadCommand-- Packet" << endl << endl;

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
        printf("Head Command Type: %02X\n\n", mtheadcommandtype);
        printf("Hdctrl: %02X %02X\n", hpi.hdctrl[0], hpi.hdctrl[1]);
        printf("HdType: %02X\n", hpi.hdtype);
        printf("Tx Ch1: %02X %02X %02X %02X\n", hpi.tx1[0], hpi.tx1[1], hpi.tx1[2], hpi.tx1[3]);
        printf("Tx Ch2: %02X %02X %02X %02X\n", hpi.tx2[0], hpi.tx2[1], hpi.tx2[2], hpi.tx2[3]);
        printf("Rx Ch1: %02X %02X %02X %02X\n", hpi.rx1[0], hpi.rx1[1], hpi.rx1[2], hpi.rx1[3]);
        printf("Rx Ch2: %02X %02X %02X %02X\n", hpi.rx2[0], hpi.rx2[1], hpi.rx2[2], hpi.rx2[3]);
        printf("Pulse Length: %02X %02X\n", hpi.txpulselen[0], hpi.txpulselen[1]);
        printf("Range Scale: %02X %02X\n", hpi.rangescale[0], hpi.rangescale[1]);
        printf("Left Lim: %02X %02X\n", hpi.leftlim[0], hpi.leftlim[1]);
        printf("Right Lim: %02X %02X\n", hpi.rightlim[0], hpi.rightlim[1]);
        printf("ADSpan: %02X\n", hpi.adspan);
        printf("ADLow: %02X\n", hpi.adlow);
        printf("Gain 1: %02X\n", hpi.igain1);
        printf("Gain 2: %02X\n", hpi.igain2);
        printf("Slope Ch1: %02X %02X\n", hpi.slope1[0], hpi.slope1[1]);
        printf("Slope Ch2: %02X %02X\n", hpi.slope2[0], hpi.slope2[1]);
        printf("MoTime: %02X\n", hpi.motime);
        printf("Step Size: %02X\n", hpi.stepsize);
        printf("ADInterval: %02X %02X\n", hpi.adinterval[0], hpi.adinterval[1]);
        printf("NBins: %02X %02X\n", hpi.nbins[0], hpi.nbins[1]);
        printf("MAX AD Buff: %02X %02X\n", hpi.maxadbuff[0], hpi.maxadbuff[1]);
        printf("Lockout: %02X %02X\n", hpi.lockout[0], hpi.lockout[1]);
        printf("Minor Axis Dir: %02X %02X\n", hpi.minoraxis[0], hpi.minoraxis[1]);
        printf("Major Axis Pan: %02X\n", hpi.majaxispan);
        printf("Ctl2: %02X\n", hpi.ctl2);
        printf("ScanZ: %02X %02X\n", hpi.scanz[0], hpi.scanz[1]);

        cout << endl << "--Line Feed--" << endl;
    }
}

// Rounds a double to integer

int roundNumber(double number) {
    
    return int(number + 0.5);
}

void MtHeadCommand::send(SerialPort *cport) {

    BYTE frame[66];

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

    // MtHeadCommand Type

    frame[13] = mtheadcommandtype;

    // Calculate 'hdtrl' value

    int total = 0;
    for (int i = 0; i < 16; i++)
        total += cf->hdctrlbits[i] * (int)pow(2.0,i);

    base256(&frame[14], total, 2);
    base256(hpi.hdctrl, total, 2);

    // Sonar Type

    frame[16] = hpi.hdtype = cf->sonartype;

    // TxN and RxN parameters

    double constant = pow(2.0,32) / 32e6;

    int txn = roundNumber(cf->frequency * 1000 * constant);
    int rxn = roundNumber(((cf->frequency * 1000) + 455000) * constant);

    base256(&frame[17], txn, 4);
    base256(&frame[21], txn, 4);
    base256(&frame[25], rxn, 4);
    base256(&frame[29], rxn, 4);

    base256(hpi.tx1, txn, 4);
    base256(hpi.tx2, txn, 4);
    base256(hpi.rx1, rxn, 4);
    base256(hpi.rx2, rxn, 4);

    // Tx Pulse Length Value

    int plen = ((cf->rangescale + 10) * 25) / 10;

    base256(&frame[33], plen, 2);

    base256(hpi.txpulselen, plen, 2);

    // Range Scale

    base256(&frame[35], cf->rangescale * 10, 2);

    base256(hpi.rangescale, cf->rangescale * 10, 2);

    // LeftLim and RighLim

    base256(&frame[37], cf->leftlim * 16, 2);

    base256(hpi.leftlim, cf->leftlim * 16, 2);

    base256(&frame[39], cf->rightlim * 16, 2);

    base256(hpi.rightlim, cf->rightlim * 16, 2);

    // ADSpan and ADLow

    BYTE adsp = roundNumber(cf->adspan * 255) / 80;
    BYTE adlw = roundNumber(cf->adlow * 255) / 80;

    frame[41] = adsp;
    frame[42] = adlw;

    hpi.adspan = adsp;
    hpi.adlow  = adlw;

    // Initial Gain

    BYTE gn = roundNumber((cf->gain * 210) / 100);

    frame[43] = gn;
    frame[44] = gn;

    hpi.igain1 = gn;
    hpi.igain2 = gn;

    // Slope Settings

    int slp;
    switch (cf->frequency) {
    case f200:
        slp = 70;
        break;
    case f325:
        slp = 90;
        break;
    case f580:
        slp = 110;
        break;
    case f675:
        slp = 125;
        break;
    case f795:
        slp = 130;
        break;
    case f935:
        slp = 140;
        break;
    case f1210:
        slp = 150;
        break;
    case f2000:
        slp = 180;
        break;
    default:
        slp = 0;
        break;
    }

    base256(&frame[45], slp, 2);
    base256(&frame[47], slp, 2);

    base256(hpi.slope1, slp, 2);
    base256(hpi.slope2, slp, 2);

    // MoTime

    frame[49] = 0x19;
    hpi.motime = 0x19;

    // Resolution

    frame[50] = cf->resolution;
    hpi.stepsize = cf->resolution;

    // ADInterval

    double adint = (cf->rangescale * 2.0) / 1500.0;
    adint /= cf->bins;
    adint /= 640e-9;

    base256(&frame[51], roundNumber(adint), 2);
    base256(hpi.adinterval, roundNumber(adint), 2);

    // NBins

    base256(&frame[53], cf->bins, 2);
    base256(hpi.nbins, cf->bins, 2);

    // MaxADBuff

    base256(&frame[55], 1000, 2);
    base256(hpi.maxadbuff, 1000, 2);

    // Lockout

    base256(&frame[57], 100, 2);
    base256(hpi.lockout, 100, 2);

    // Minor Axis

    base256(&frame[59], 1600, 2);
    base256(hpi.minoraxis, 1600, 2);

    // Major Axis Pan

    frame[61] = 0x01;
    hpi.majaxispan = 0x01;

    // Ctrl2

    frame[62] = 0;
    hpi.ctl2 = 0;

    // ScanZ

    base256(&frame[63], 0, 2);
    base256(hpi.scanz, 0 ,2);

    // Footer

    frame[65] = lfeed;

    for (int i = 0; i < 66; i++)
        cport->write(frame[i]);
}

// Changes configuration structure associated with MtHeadCommand

void MtHeadCommand::setConfig(Config *cfg) { cf = cfg; }
