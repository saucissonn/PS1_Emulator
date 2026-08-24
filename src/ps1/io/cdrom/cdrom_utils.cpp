#include "ps1/io/cdrom/cdrom.hpp"

#include "utils/error.hpp"

uint8_t Cdrom::readData() {
    if (data.empty())
        return 0;

    uint8_t value = data.front();
    data.pop();

    return value;
}

uint8_t Cdrom::readResponse() {
    if (response.empty())
        return 0;

    uint8_t value = response.front();
    response.pop();

    return value;
}

uint8_t Cdrom::incrementBcd(uint8_t value) {
    if ((value & 0x0F) == 0x09)
        return (value & 0xF0) + 0x10;

    return value + 1;
}

void Cdrom::incrementPosition() {
    targetFrame = incrementBcd(targetFrame);

    if (targetFrame == 0x75) {
        targetFrame = 0x00;
        targetSecond = incrementBcd(targetSecond);

        if (targetSecond == 0x60) {
            targetSecond = 0x00;
            targetMinute = incrementBcd(targetMinute);
        }
    }
}

uint8_t Cdrom::bcdToInt(uint8_t value) {
    return (value >> 4) * 10 + (value & 0x0F);
}

uint8_t Cdrom::intToBcd(uint8_t value) {
    return ((value / 10) << 4) | (value % 10);
}

uint32_t Cdrom::positionToAddress() {
	return bcdToInt(targetMinute) * (60 * 75) + bcdToInt(targetSecond) * 75 + bcdToInt(targetFrame);
}

void Cdrom::addressToPosition(uint32_t address) {
    uint32_t minutes = address / (60 * 75);
    address %= 60 * 75;

    uint32_t seconds = address / 75;
    uint32_t frames = address % 75;

    targetMinute = intToBcd(minutes);
    targetSecond = intToBcd(seconds);
    targetFrame = intToBcd(frames);
}

uint32_t Cdrom::getMaxAddress() {
	return disc.getMaxAddress();
}

Track *Cdrom::getCurrentTrack() {
	return disc.getCurrentTrack();
}

void Cdrom::pushReport() {
    response.push(status);

	Track *currentTrack = getCurrentTrack();
    response.push(currentTrack->id);
    response.push(currentTrack->index);

    if (targetFrame % 0x20 == 0) { // Absolute position
		response.push(targetMinute);
        response.push(targetSecond);
        response.push(targetFrame);
    }
    else { // Relative position
		response.push(targetMinute - currentTrack->minute);
        response.push((targetSecond - currentTrack->second) | 0x80);
        response.push(targetFrame - currentTrack->frame);
    }

	response.push(0); // No peak for now
	response.push(0);
	//response.push(peak & 0xFF);
	//response.push((peak >> 8) & 0xFF);
}
