#include "ps1/io/expansion.hpp"
#include <algorithm>

ExpansionRegion1::ExpansionRegion1() {
    dataSize = 0x80000;
	data = (uint8_t *)calloc(dataSize, sizeof(uint8_t));
}

ExpansionRegion1::~ExpansionRegion1() {
	free(data);

    return;
}

uint8_t ExpansionRegion1::read(uint32_t address) {
    if (address >= 0x1F000000 && address < 0x1F080000) {
        return data[address - 0x1F000000];
    }

    return 0;
}

void ExpansionRegion1::write(uint32_t address, uint8_t value) {
    if (address >= 0x1F000000 && address < 0x1F080000) {
        data[address - 0x1F000000] = value;
    }
}


ExpansionRegion2::ExpansionRegion2() {
    std::fill(data, data + 0x80, 0);

    modeA = 0;
    statusA = 0;
    clockA = 0;
    commandA = 0;
    rxA = 0;
    txA = 0;

    modeB = 0;
    statusB = 0;
    clockB = 0;
    commandB = 0;
    rxB = 0;
    txB = 0;

    interruptStatus = 0;
    interruptMask = 0;
    counter = 0;
    counterReload = 0;

    inputPort = 0;
    outputConfig = 0;

    atconsStatus = 0;
    atconsData = 0;
    unknown004 = 0;
    irqFlags = 0;
    irqControl = 0;
    dip = 0;
    post = 0;
    postLed = 0;
    post2 = 0;

    emuEnable1 = 0;
    emuEnable2 = 0;
    emuHalt = 0;
    emuTurbo = 0;
}

ExpansionRegion2::~ExpansionRegion2() {
    return;
}

uint8_t ExpansionRegion2::read(uint32_t address) {
    switch (address) {
        case 0x1F802000:
            return atconsStatus;

        case 0x1F802002:
            return atconsData;

        case 0x1F802004:
            return unknown004 & 0xFF;

        case 0x1F802030:
            return irqFlags;

        case 0x1F802032:
            return irqControl;

        case 0x1F802040:
            return dip;

        case 0x1F802041:
            return post;

        case 0x1F802042:
            return postLed;

        case 0x1F802060:
            return 'E';

        case 0x1F802061:
            return 'X';

        case 0x1F802062:
            return 'P';

        case 0x1F802063:
            return 0x01;

        case 0x1F802064:
            return emuEnable1;

        case 0x1F802065:
            return emuEnable2;

        case 0x1F802066:
            return emuHalt;

        case 0x1F802067:
            return emuTurbo;

        case 0x1F802070:
            return post2;

        case 0x1F802020:
            return modeA;

        case 0x1F802021:
            return statusA;

        case 0x1F802022:
            return 0;

        case 0x1F802023:
            return rxA;

        case 0x1F802024:
            return inputPort;

        case 0x1F802025:
            return interruptStatus;

        case 0x1F802026:
            return counter >> 8;

        case 0x1F802027:
            return counter & 0xFF;

        case 0x1F802028:
            return modeB;

        case 0x1F802029:
            return statusB;

        case 0x1F80202A:
            return 0;

        case 0x1F80202B:
            return rxB;

        case 0x1F80202D:
            return inputPort;

        case 0x1F80202E:
        case 0x1F80202F:
            return 0;
    }

    if (address >= 0x1F802000 && address < 0x1F802080) {
        return data[address - 0x1F802000];
    }

    return 0;
}

void ExpansionRegion2::write(uint32_t address, uint8_t value) {
    switch (address) {
        case 0x1F802002:
            atconsData = value;
            return;

        case 0x1F802004:
            unknown004 = (unknown004 & 0xFF00) | value;
            return;

        case 0x1F802030:
            irqFlags = value;
            return;

        case 0x1F802032:
            irqControl = value;
            return;

        case 0x1F802041:
            post = value;
            return;

        case 0x1F802042:
            postLed = value;
            return;

        case 0x1F802064:
            emuEnable1 = value;
            return;

        case 0x1F802065:
            emuEnable2 = value;
            return;

        case 0x1F802067:
            emuTurbo = value;
            return;

        case 0x1F802020:
            modeA = value;
            return;

        case 0x1F802021:
            clockA = value;
            return;

        case 0x1F802022:
            commandA = value;
            return;

        case 0x1F802023:
            txA = value;
            return;

        case 0x1F802024:
            outputConfig = value;
            return;

        case 0x1F802025:
            interruptMask = value;
            return;

        case 0x1F802026:
            counterReload = (counterReload & 0x00FF) | ((uint16_t)value << 8);
            return;

        case 0x1F802027:
            counterReload = (counterReload & 0xFF00) | value;
            return;

        case 0x1F802028:
            modeB = value;
            return;

        case 0x1F802029:
            clockB = value;
            return;

        case 0x1F80202A:
            commandB = value;
            return;

        case 0x1F80202B:
            txB = value;
            return;

        case 0x1F80202D:
            outputConfig = value;
            return;

        case 0x1F80202E:
        case 0x1F80202F:
            return;
    }

    if (address >= 0x1F802000 && address < 0x1F802080) {
        data[address - 0x1F802000] = value;
    }
}


ExpansionRegion3::ExpansionRegion3() {
    post = 0;
}

ExpansionRegion3::~ExpansionRegion3() {
    return;
}

uint8_t ExpansionRegion3::read(uint32_t address) {
    switch (address) {
        case 0x1FA00000:
            return post;
    }

    return 0;
}

void ExpansionRegion3::write(uint32_t address, uint8_t value) {
    switch (address) {
        case 0x1FA00000:
            post = value;
            return;
    }
}
