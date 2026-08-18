#include "ps1/expansion.hpp"
#include <algorithm>

#include "utils/error.hpp"

ExpansionRegion1::ExpansionRegion1() {
    dataSize = 0x80000;
	data = (uint8_t *)calloc(dataSize, sizeof(uint8_t));

	connected = 0;
}

ExpansionRegion1::~ExpansionRegion1() {
	free(data);

    return;
}

uint32_t ExpansionRegion1::read(uint32_t address) {
    if (0x1F000000 <= address && address <= 0x1F07FFFF) {
        address -= 0x1F000000;

		uint32_t result = (uint32_t)data[address];
		result |= (uint32_t)data[address + 1] << 8;
		result |= (uint32_t)data[address + 2] << 16;
		result |= (uint32_t)data[address + 3] << 24;

		return result;
    }

    return 0;
}

int ExpansionRegion1::write(uint32_t address, uint32_t value) {
    if (0x1F000000 <= address && address <= 0x1F07FFFF) {
        address -= 0x1F000000;

        data[address] = (uint8_t)(value);
        data[address + 1] = (uint8_t)(value >> 8);
        data[address + 2] = (uint8_t)(value >> 16);
        data[address + 3] = (uint8_t)(value >> 24);

        return ERR_OK;
    }

    return ERR_WRITE_SECTION_NOT_FOUND;
}

int ExpansionRegion1::getConnected() {
	return connected;
}

void ExpansionRegion1::setConnected(int value) {
	connected = value;
}

ExpansionRegion2::ExpansionRegion2() {
    dataSize = 0x80000;
    data = (uint8_t *)calloc(dataSize, sizeof(uint8_t));

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

	connected = 0;
}

ExpansionRegion2::~ExpansionRegion2() {
	free(data);

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

	if (0x1F802000 <= address && address <= 0x1F80207F) {
	    address -= 0x1F802000;

	    return (uint32_t)data[address]
	         | ((uint32_t)data[address + 1] << 8)
	         | ((uint32_t)data[address + 2] << 16)
	         | ((uint32_t)data[address + 3] << 24);
	}

    return 0;
}

int ExpansionRegion2::write(uint32_t address, uint32_t value) {
    switch (address) {
        case 0x1F802002:
            atconsData = value;
            return ERR_OK;

        case 0x1F802004:
            unknown004 = (unknown004 & 0xFF00) | value;
            return ERR_OK;

        case 0x1F802030:
            irqFlags = value;
            return ERR_OK;

        case 0x1F802032:
            irqControl = value;
            return ERR_OK;

        case 0x1F802041:
            post = value;
            return ERR_OK;

        case 0x1F802042:
            postLed = value;
            return ERR_OK;

        case 0x1F802064:
            emuEnable1 = value;
            return ERR_OK;

        case 0x1F802065:
            emuEnable2 = value;
            return ERR_OK;

        case 0x1F802067:
            emuTurbo = value;
            return ERR_OK;

        case 0x1F802020:
            modeA = value;
            return ERR_OK;

        case 0x1F802021:
            clockA = value;
            return ERR_OK;

        case 0x1F802022:
            commandA = value;
            return ERR_OK;

        case 0x1F802023:
            txA = value;
            return ERR_OK;

        case 0x1F802024:
            outputConfig = value;
            return ERR_OK;

        case 0x1F802025:
            interruptMask = value;
            return ERR_OK;

        case 0x1F802026:
            counterReload = (counterReload & 0x00FF) | ((uint16_t)value << 8);
            return ERR_OK;

        case 0x1F802027:
            counterReload = (counterReload & 0xFF00) | value;
            return ERR_OK;

        case 0x1F802028:
            modeB = value;
            return ERR_OK;

        case 0x1F802029:
            clockB = value;
            return ERR_OK;

        case 0x1F80202A:
            commandB = value;
            return ERR_OK;

        case 0x1F80202B:
            txB = value;
            return ERR_OK;

        case 0x1F80202D:
            outputConfig = value;
            return ERR_OK;

        case 0x1F80202E:
			return ERR_OK;

        case 0x1F80202F:
            return ERR_OK;
    }

	if (0x1F802000 <= address && address < 0x1F802080) {
	    address -= 0x1F802000;

	    data[address] = (uint8_t)value;
	    data[address + 1] = (uint8_t)(value >> 8);
	    data[address + 2] = (uint8_t)(value >> 16);
	    data[address + 3] = (uint8_t)(value >> 24);

	    return ERR_OK;
	}

	return ERR_WRITE_SECTION_NOT_FOUND;
}

int ExpansionRegion2::getConnected() {
    return connected;
}

void ExpansionRegion2::setConnected(int value) {
    connected = value;
}

ExpansionRegion3::ExpansionRegion3() {
    post = 0;

	connected = 0;
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

int ExpansionRegion3::write(uint32_t address, uint32_t value) {
    switch (address) {
        case 0x1FA00000:
            post = value;
            return ERR_OK;
    }

	return ERR_WRITE_SECTION_NOT_FOUND;
}

int ExpansionRegion3::getConnected() {
    return connected;
}

void ExpansionRegion3::setConnected(int value) {
    connected = value;
}
