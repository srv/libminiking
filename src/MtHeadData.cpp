/*
=============================================================================
  Name: MtHeadData.cpp
  Author: Emilio Garcia-Fidalgo
  Date: 15/10/06 14:02
  Description: Implementation of 'mtHeadData' Message
=============================================================================
*/

#include "MtHeadData.h"

// Constructor

MtHeadData::MtHeadData() : rd(NULL) {}

// Shows information contained in packet´s fields

void MtHeadData::printPacket(bool complete) {

    cout << endl << "--mtHeadData-- Packet" << endl << endl;

    if (complete) {
        printf("Header: %02X\n", hdr);
        printf("Hex Length: %02X %02X %02X %02X\n", hexln[0], hexln[1], hexln[2], hexln[3]);
        printf("Bin Length: %02X %02X\n", binln[0], binln[1]);
        printf("SID: %02X\n", sid);
        printf("DID: %02X\n", did);
        printf("Start Seq: %02X\n", countmsg);
        printf("Packet Type: %02X\n", ptype);
        printf("Sequence: %02X\n", sequence);
        printf("Node: %02X\n\n", node);
        printf("Total Byte Count: %02X %02X\n", dp.totalbytecount[0], dp.totalbytecount[1]);
        printf("Head Type: %02X\n", dp.devicetype);
        printf("Head Status: %02X\n", dp.headstatus);
        printf("Sweep Code: %02X\n", dp.sweepcode);
        printf("Head Type: %02X\n", dp.devicetype);
        printf("Hdctrl: %02X %02X\n", dp.hdctrl[0], dp.hdctrl[1]);
        printf("Range Scale: %02X %02X\n", dp.rangescale[0], dp.rangescale[1]);
        printf("TxN: %02X %02X %02X %02X\n", dp.txntransmitter[0], dp.txntransmitter[1], dp.txntransmitter[2], dp.txntransmitter[3]);
        printf("Gain: %02X\n", dp.gainsetting);
        printf("Slope: %02X %02X\n", dp.slopesetting[0], dp.slopesetting[1]);
        printf("AdSpan: %02X\n", dp.adspan);
        printf("ADLow: %02X\n", dp.adlow);
        printf("Heading OffSet: %02X %02X\n", dp.headingoffset[0], dp.headingoffset[1]);
        printf("Left Limit: %02X %02X\n", dp.leftlimit[0], dp.leftlimit[1]);
        printf("Right Limit: %02X %02X\n", dp.rightlimit[0], dp.rightlimit[1]);
        printf("Steps: %02X\n", dp.stepangle);
        printf("Bearing: %02X %02X\n", dp.bearing[0], dp.bearing[1]);
        printf("DBytes: %02X %02X\n\n", dp.dbytes[0], dp.dbytes[1]);

        cout << "Data: " << endl;

        int cnt = base10(dp.dbytes, 2);
        for (int i = 0; i < cnt; i++)
            printf("%02X ", *(rd + i));

        cout << endl << endl << "--Line Feed--" << endl;
    }
}

// Receive and store 'MtHeadData' Message

void MtHeadData::receive(SerialPort *cport) {

    try {

        // Params info

        cport->read(dp.totalbytecount, 2);
        dp.devicetype = cport->read();
        dp.headstatus = cport->read();
        dp.sweepcode = cport->read();

        cport->read(dp.hdctrl, 2);
        cport->read(dp.rangescale, 2);
        cport->read(dp.txntransmitter, 4);
        dp.gainsetting = cport->read();
        cport->read(dp.slopesetting, 2);
        dp.adspan = cport->read();
        dp.adlow = cport->read();
        cport->read(dp.headingoffset, 2);
        cport->read(dp.adinterval, 2);
        cport->read(dp.leftlimit, 2);
        cport->read(dp.rightlimit, 2);
        dp.stepangle = cport->read();
        cport->read(dp.bearing, 2);
        cport->read(dp.dbytes, 2);

        // Data Bytes

        int cnt = base10(dp.dbytes, 2);

        if (rd != NULL)
            delete [] rd;

        rd = new BYTE[cnt];
        for (int i = 0; i < cnt; i++)
            rd[i] = cport->read();

        // Line Feed

        lfeed = cport->read();
    }
    catch (runtime_error &e) {        // Error in timeouts or bytes
        cout << e.what() << endl;
    }
}

SweepCode MtHeadData::getSweepCode(void) { return (SweepCode)dp.sweepcode; }

int MtHeadData::getBearing(void) { return base10(dp.bearing, 2); }

int MtHeadData::getDataLength(void) { return base10(dp.dbytes, 2); }

BYTE *MtHeadData::getDataBytes(void) { return rd; }
