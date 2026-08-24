#include "ps1/io/cdrom/cdrom.hpp"

#include "utils/error.hpp"
#include "ps1/io/interrupt_controller.hpp"

// Commands

int Cdrom::raiseInterrupt(CdromInterrupt type) { // Every commands with an INT response should end with that
    interruptFlag = (uint8_t)type;
	interruptController->request(Interrupt::CDROM);
	
	return ERR_OK;
}

int Cdrom::getStat() { // 0x01
	response.push(status);
	return raiseInterrupt(CdromInterrupt::INT3);
}

int Cdrom::setLoc() { // 0x02
	targetMinute = readParameters();
	targetSecond = readParameters();
	targetFrame = readParameters();

    response.push(status);
    return raiseInterrupt(CdromInterrupt::INT3);
}

int Cdrom::play() { // 0x03
	if (!(parameters.empty())) { // One optional parameter
		uint8_t track = readParameters();
		// TODO should use this track in parameter instead of a default track by matching the track value above with IDs in Tracks (in disc)
		pushLongCommandParameters(track); // Set the current position at the beginning of the track
	
		Track *currentTrack = getCurrentTrack();

	    targetMinute = currentTrack->minute;
	    targetSecond = currentTrack->second;
	    targetFrame = currentTrack->frame;
	}

	longCommand = 0x03;

    response.push(status);
    return raiseInterrupt(CdromInterrupt::INT3);
}

int Cdrom::decodeCommand() { // Also execute
    uint8_t count = getParameterCount(command);

    if (parameters.size() < count)
        return ERR_CDROM_NOT_ENOUGH_PARAMETERS;

    switch (command) {
        case 0x00: return ERR_CDROM_COMMAND_NOT_FOUND; // Invalid Command ?
        case 0x01: return getStat();
        case 0x02: return setLoc();
        case 0x03:
			clearLongCommandParameters();
			return play(); // Hard one
        case 0x04: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x05: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x06:
			clearLongCommandParameters();
			return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x07: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x08: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x09: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0A: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0B: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0C: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0D: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0E: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x0F: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x10: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x11: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x12: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x13: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x14: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x15:
			clearLongCommandParameters();
			return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x16:
			clearLongCommandParameters();
			return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x17: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x18: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x19: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x1A: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x1B:
			clearLongCommandParameters();
			return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x1C: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x1D: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x1E: return ERR_CDROM_COMMAND_NOT_FOUND;

        case 0x50: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x51: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x52: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x53: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x54: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x55: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x56: return ERR_CDROM_COMMAND_NOT_FOUND;
        case 0x57: return ERR_CDROM_COMMAND_NOT_FOUND;
    }

    if (0x1F <= command && command <= 0x4F)
        return ERR_CDROM_COMMAND_NOT_FOUND;

    if (0x58 <= command && command <= 0x5F)
        return ERR_CDROM_COMMAND_NOT_FOUND;

    if (0x6F <= command)
        return ERR_CDROM_COMMAND_NOT_FOUND;

    return ERR_CDROM_COMMAND_NOT_FOUND;
}

int Cdrom::writeCommand(uint8_t value) { // Can also write a volume settings
	switch (index) {
		case 0:
			command = value;
			if (getParameterCount(command) == 0) { // If no parameter we directly execute the command
				return decodeCommand();
			}

			return ERR_OK;

		case 1:
			return ERR_OK; // Unknown/unused

		case 2:
			return ERR_OK; // Unknown/unused

		case 3:
			audioVolumeRightToRight = value;
			return ERR_OK;
	}

	return ERR_UNEXPECTED_RESULT;
}

int Cdrom::longCommandPlay() {
	uint32_t address = positionToAddress();

	if (address > getMaxAddress()) {
		longCommand = 0x00;

	    response.push(status);
		status &= ~(1 << 7);

	    return raiseInterrupt(CdromInterrupt::INT4);
	}

	// uint8_t data = disc.read(address); // TODO send to a buffer audio CD-DA

	incrementPosition();

	pushReport();
	return raiseInterrupt(CdromInterrupt::INT1);
}

int Cdrom::decodeLongCommand() {
	switch (longCommand) {
		case 0x03: return longCommandPlay(); // Play
		case 0x06: return ERR_CDROM_COMMAND_NOT_FOUND; // ReadN
		case 0x15: return ERR_CDROM_COMMAND_NOT_FOUND; // SeekL
		case 0x16: return ERR_CDROM_COMMAND_NOT_FOUND; // SeekP
		case 0x1B: return ERR_CDROM_COMMAND_NOT_FOUND; // ReadS
	}

	return ERR_OK; // No long command to execute
}
