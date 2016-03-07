/*
=============================================================================
  Name: MiniKing.h
  Author: Emilio Garcia-Fidalgo
  Date: 30/10/06 18:22
  Description: Main Library class
=============================================================================
*/

#include "libminiking/MiniKing.h"

MiniKing::MiniKing(char *port, int timeout) :
    cp(port, br115200, db8, None, sb1, timeout, false),
    mtheadcommand(&conf),
    mtreboot(),
    mtsenddata(),
    mtsendversion(),
    mtsendbbuser(),
    mtversiondata(),
    mtalive(),
    mtbbuserdata(),
    mtheaddata1(),
    mtheaddata2() {

    // Default Settings

    setDefaultConfig();

    // Need send 'MtSendData' command

    needData = true;

    // To receive mtHeadData Packets

    allReceived = true;

    // Verbose Mode

    verbose = false;
}

// Configuration access functions

void MiniKing::set8Bits(bool op) { conf.hdctrlbits[0] = op; }

bool MiniKing::get8Bits(void) { return conf.hdctrlbits[0]; }

void MiniKing::setContinuous(bool op) { conf.hdctrlbits[1] = op; }

bool MiniKing::getContinuous(void) { return conf.hdctrlbits[1]; }

void MiniKing::setInverted(bool op) { conf.hdctrlbits[3] = op; }

bool MiniKing::getInverted(void) { return conf.hdctrlbits[3]; }

void MiniKing::setMotorDisabled(bool op) { conf.hdctrlbits[4] = op; }

bool MiniKing::getMotorDisabled(void) { return conf.hdctrlbits[4]; }

void MiniKing::setTransmitDisabled(bool op) { conf.hdctrlbits[5] = op; }

bool MiniKing::getTransmitDisabled(void) { return conf.hdctrlbits[5]; }

void MiniKing::setApplyOffset(bool op) { conf.hdctrlbits[10] = op;}

bool MiniKing::getApplyOffset(void) { return conf.hdctrlbits[10]; }

void MiniKing::setStare(bool op) { conf.hdctrlbits[12] = op;}

bool MiniKing::getStare(void) { return conf.hdctrlbits[12]; }

void MiniKing::setSonarType(SonarType st) { conf.sonartype = st; }

SonarType MiniKing::getSonarType(void) { return conf.sonartype; }

void MiniKing::setFrequency(Frequency freq) { conf.frequency = freq; }

Frequency MiniKing::getFrequency(void) { return conf.frequency; }

void MiniKing::setRange(int range) { conf.rangescale = range; }

int MiniKing::getRange(void) { return conf.rangescale; }

void MiniKing::setLeftLim(int lim) { conf.leftlim = (lim * 10) / 9; }

float MiniKing::getLeftLim(void) { return (conf.leftlim * 9.0) / 10.0; }

void MiniKing::setRightLim(int lim) { conf.rightlim = (lim * 10) / 9; }

float MiniKing::getRightLim(void) { return (conf.rightlim * 9.0) / 10.0; }

void MiniKing::setADSpan(int ads) { conf.adspan = ads; }

int MiniKing::getADSpan(void) { return conf.adspan; }

void MiniKing::setADLow(int adl) { conf.adlow = adl; }

int MiniKing::getADLow(void) { return conf.adlow; }

void MiniKing::setGain(int gn) { conf.gain = gn; }

int MiniKing::getGain(void) { return conf.gain; }

void MiniKing::setResolution(Resolution rs) { conf.resolution = rs; }

Resolution MiniKing::getResolution(void) { return conf.resolution; }

void MiniKing::setBins(int bn) { conf.bins = bn; }

int MiniKing::getBins(void) { return conf.bins; }

// Version data access functions

BoardType MiniKing::getBoardType(void) { return vd.bt; }

int MiniKing::getSerialNumber(void) { return vd.serialnumber; }

int MiniKing::getProgramLength(void) { return vd.programlength; }

int MiniKing::getChecksum(void) { return vd.checksum; }

// 'MtAlive' access functions

bool MiniKing::hasParams(void) { return mtalive.hasParams(); }

int MiniKing::getHeadTime(void) { return mtalive.getHeadTime(); }

float MiniKing::getMotorPos(void) { return (((mtalive.getMotorPos() / 16.0) * 9.0) / 10.0); } // In grads

bool MiniKing::isCentering(void) { return mtalive.isCentering(); }

bool MiniKing::isCentred(void) { return mtalive.isCentred(); }

bool MiniKing::isMotoring(void) { return mtalive.isMotoring(); }

bool MiniKing::isMotorOn(void) { return mtalive.isMotorOn(); }

bool MiniKing::isDir(void) { return mtalive.isDir(); }

bool MiniKing::isScan(void) { return mtalive.isScan(); }

bool MiniKing::configReceived(void) { return mtalive.paramsReceived(); }

// 'MtBBUserData' access functions

LANBitRate MiniKing::getLanBaudLow(void) { return mtbbuserdata.getLanBaudLow(); }

LANBitRate MiniKing::getLanBaudHigh(void) { return mtbbuserdata.getLanBaudHigh(); }

LANSensitivity MiniKing::getSensitivityLow(void) { return mtbbuserdata.getSensitivityLow(); }

LANSensitivity MiniKing::getSensitivityHigh(void) { return mtbbuserdata.getSensitivityHigh(); }

int MiniKing::getLanTimeout(void) { return mtbbuserdata.getLanTimeout(); }

BitRate MiniKing::getCOMBaudLow(void) { return mtbbuserdata.getA0BaudLow(); }

BitRate MiniKing::getCOMBaudHigh(void) { return mtbbuserdata.getA0BaudHigh(); }

Parity MiniKing::getCOMParityLow(void) { return mtbbuserdata.getA0ParityLow(); }

Parity MiniKing::getCOMParityHigh(void) { return mtbbuserdata.getA0ParityHigh(); }

DataBits MiniKing::getCOMDataBitsLow(void) { return mtbbuserdata.getA0DataBitsLow(); }

DataBits MiniKing::getCOMDataBitsHigh(void) { return mtbbuserdata.getA0DataBitsHigh(); }

BitRate MiniKing::getAUXBaudLow(void) { return mtbbuserdata.getA1BaudLow(); }

BitRate MiniKing::getAUXBaudHigh(void) { return mtbbuserdata.getA1BaudHigh(); }

Parity MiniKing::getAUXParityLow(void) { return mtbbuserdata.getA1ParityLow(); }

Parity MiniKing::getAUXParityHigh(void) { return mtbbuserdata.getA1ParityHigh(); }

DataBits MiniKing::getAUXDataBitsLow(void) { return mtbbuserdata.getA1DataBitsLow(); }

DataBits MiniKing::getAUXDataBitsHigh(void) { return mtbbuserdata.getA1DataBitsHigh(); }

bool MiniKing::hasMotor(void) { return mtbbuserdata.hasMotor(); }

bool MiniKing::hasAux(void) { return mtbbuserdata.hasAux(); }

bool MiniKing::hasRollSensor(void) { return mtbbuserdata.hasRollSensor(); }

SonarBlock *MiniKing::otherInfo(void) { return &(mtbbuserdata.snb); }

// 'MtHeadData' access functions

float MiniKing::getPosition(void) {

    if (needData)
        return ((((float)mtheaddata2.getBearing() / 16.0) * 9.0) / 10.0);      // In grads
    else
        return ((((float)mtheaddata1.getBearing() / 16.0) * 9.0) / 10.0);      // In grads
}

int MiniKing::getDataLength(void) {

    if (needData)
        return mtheaddata2.getDataLength();
    else
        return mtheaddata1.getDataLength();
}

// General functions

void MiniKing::setDefaultConfig() { // Need updateConfig() after to take effect

    // Hdctrl bits

    conf.hdctrlbits[0] = true;    // 8 Data Bits
    conf.hdctrlbits[1] = true;    // Scan continuous
    conf.hdctrlbits[2] = true;    // Clockwise
    conf.hdctrlbits[3] = false;   // Normal mounted
    conf.hdctrlbits[4] = false;   // Motor Enabled
    conf.hdctrlbits[5] = false;   // Transmitter Enabled
    conf.hdctrlbits[6] = false;   // Default, Always 0
    conf.hdctrlbits[7] = false;   // Only One Channel Operation
    conf.hdctrlbits[8] = true;    // Default, Always 1
    conf.hdctrlbits[9] = true;    // Sonar has scanning motor
    conf.hdctrlbits[10] = false;  // Do not apply offsets
    conf.hdctrlbits[11] = false;  // Not pingpong, only one channel
    conf.hdctrlbits[12] = false;  // Don´t stare in a fixed direction
    conf.hdctrlbits[13] = true;   // Default, Always 1
    conf.hdctrlbits[14] = false;  // Default, Always 0
    conf.hdctrlbits[15] = false;  // Don´t ignore sensor

    // Head Type

    conf.sonartype = ImagingSonar;

    // Head Frequency

    conf.frequency = f675;

    // Range Scale

    conf.rangescale = 30;

    // Scan Limits

    conf.leftlim = 0;
    conf.rightlim = 0;

    // ADSpan and ADLow (in Db´s)

    conf.adspan = 12;
    conf.adlow = 13;

    // Initial Gain

    conf.gain = 40;

    // Resolution

    conf.resolution = Medium;

    // Number of Range Bins for each ping

    conf.bins = 300;
}

void MiniKing::initSonar(void) {       // Basic initialization procedure

    while (receive(&cp) != mtAlive);

    mtsendversion.send(&cp);
    if (verbose) mtsendversion.printPacket(true);

    while (receive(&cp) != mtVersionData);

    vd.fr = mtversiondata.getFrequency();
    vd.bt = mtversiondata.getBoardType();
    vd.serialnumber = mtversiondata.getSerialNumber();
    vd.programlength = mtversiondata.getProgramLength();
    vd.checksum = mtversiondata.getChecksum();

    mtsendbbuser.send(&cp);
    if (verbose) mtsendversion.printPacket(true);

    while (receive(&cp) != mtBBUserData);

    while (receive(&cp) != mtAlive);

    while (!hasParams()) {

        mtheadcommand.send(&cp);
        if (verbose) mtheadcommand.printPacket(true);
        while (receive(&cp) != mtAlive);
    }
}

void MiniKing::reboot(void) {           // Reboots sonar

    setDefaultConfig();

    mtreboot.send(&cp);
    if (verbose) mtreboot.printPacket(true);
    while (receive(&cp) != mtAlive);

    while (hasParams()) receive(&cp);

    while (!hasParams()) {

        mtheadcommand.send(&cp);
        if (verbose) mtheadcommand.printPacket(true);

        while (receive(&cp) != mtAlive);
    }
}

void MiniKing::updateConfig(void) {     // Update sonar´s parametres

    do {

        mtheadcommand.send(&cp);
        if (verbose) mtheadcommand.printPacket(true);
        while (receive(&cp) != mtAlive);
    } while (!hasParams());
}

BYTE *MiniKing::getScanLine(void) {    // Get a data scan

    if (needData) {

        mtsenddata.send(&cp);
        if (verbose) mtsenddata.printPacket(true);

        while (receive(&cp) != mtHeadData);

        allReceived = false;

        while (receive(&cp) != mtHeadData);

        allReceived = true;

        needData = false;

        return mtheaddata1.getDataBytes();
    }
    else {

        needData = true;

        return mtheaddata2.getDataBytes();
    }
}

void MiniKing::setVerboseMode(bool op) {

    verbose = op;
}

bool MiniKing::isLeftLimit(void) {

    if (needData) {

        if (mtheaddata1.getSweepCode() == ScanLeftLimit)
            return true;
        else
            return false;
    }
    else {

        if (mtheaddata2.getSweepCode() == ScanLeftLimit)
            return true;
        else
            return false;
    }
}

bool MiniKing::isRightLimit(void) {

    if (needData) {

        if (mtheaddata1.getSweepCode() == ScanRightLimit)
            return true;
        else
            return false;
    }
    else {

        if (mtheaddata2.getSweepCode() == ScanRightLimit)
            return true;
        else
            return false;
    }
}

// Waits for Initial Character

BYTE synchronize(SerialPort *cport) {

    BYTE ch;

    try {

        while((ch = cport->read()) != '@');
        return ch;
    }
    catch (runtime_error &e) {        // Error in timeouts or bytes
        cout << e.what() << endl;
        return false;
    }
}

// General receive

PacketType MiniKing::receive(SerialPort *cport) {

    BYTE inchar = synchronize(cport);
    BYTE hdr;
    BYTE hexln[4];
    BYTE binln[2];
    BYTE sid;
    BYTE did;
    BYTE countmsg;
    BYTE ptype;
    BYTE sequence;
    BYTE node;

    if (!inchar) {
        cout << "Can´t receive message" << endl;
    }
    else if (inchar == '@') {
        try {

            // Header

            hdr = inchar;

            // Hex Length

            cport->read(hexln, 4);

            // Bin Length

            cport->read(binln, 2);

            // Source ID and Destination ID

            sid = cport->read();
            did = cport->read();

            // Count Message

            countmsg = cport->read();

            // Packet Type

            ptype = cport->read();

            // Sequence Number

            sequence = cport->read();

            // Copy of Byte 8

            node = cport->read();

            Message *msg = NULL;

            switch (ptype) {
            case mtAlive:
                msg = &mtalive;
                mtalive.receive(&cp);
                break;
            case mtBBUserData:
                msg = &mtbbuserdata;
                mtbbuserdata.receive(&cp);
                break;
            case mtVersionData:
                msg = &mtversiondata;
                mtversiondata.receive(&cp);
                break;
            case mtHeadData:
                if (allReceived) {
                    msg = &mtheaddata1;
                    mtheaddata1.receive(&cp);
                }
                else {
                    msg = &mtheaddata2;
                    mtheaddata2.receive(&cp);
                }
                break;
            default:
                break;
            }
            msg->hdr = inchar;
            for (int i = 0; i < 4; i++)
                msg->hexln[i] = hexln[i];
            for (int i = 0; i < 2; i++)
                msg->binln[i] = binln[i];
            msg->sid = sid;
            msg->did = did;
            msg->countmsg = countmsg;
            msg->ptype = ptype;
            msg->sequence = sequence;
            msg->node = node;
            if (verbose) msg->printPacket(true);
            return (PacketType)ptype;
        }
        catch (runtime_error &e) {        // Error in timeouts or bytes
            cout << e.what() << endl;
        }
    }
    else {
        cout << "Unknown error receiving message" << endl;
    }
    return errorPacket;
}
