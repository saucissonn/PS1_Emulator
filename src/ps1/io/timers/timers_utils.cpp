#include "ps1/io/timers/timers.hpp"

#include "utils/error.hpp"

uint16_t Timers::getCounter(uint8_t timer) {
    return timers[timer].counter;
}

uint16_t Timers::getMode(uint8_t timer) {
    return timers[timer].mode;
}

uint16_t Timers::getTarget(uint8_t timer) {
    return timers[timer].target;
}

bool Timers::getSynchronizationEnable(uint8_t timer) {
    return (timers[timer].mode >> 0) & 0x01;
}

uint8_t Timers::getSynchronizationMode(uint8_t timer) {
    return (timers[timer].mode >> 1) & 0x03;
}

bool Timers::getResetMode(uint8_t timer) {
    return (timers[timer].mode >> 3) & 0x01;
}

bool Timers::getIrqTargetEnable(uint8_t timer) {
    return (timers[timer].mode >> 4) & 0x01;
}

bool Timers::getIrqOverflowEnable(uint8_t timer) {
    return (timers[timer].mode >> 5) & 0x01;
}

bool Timers::getIrqRepeat(uint8_t timer) {
    return (timers[timer].mode >> 6) & 0x01;
}

bool Timers::getIrqToggle(uint8_t timer) {
    return (timers[timer].mode >> 7) & 0x01;
}

uint8_t Timers::getClockSource(uint8_t timer) {
    return (timers[timer].mode >> 8) & 0x03;
}

bool Timers::getInterruptRequest(uint8_t timer) {
    return (timers[timer].mode >> 10) & 0x01;
}

bool Timers::getReachedTarget(uint8_t timer) {
    return (timers[timer].mode >> 11) & 0x01;
}

bool Timers::getReachedOverflow(uint8_t timer) {
    return (timers[timer].mode >> 12) & 0x01;
}


void Timers::setCounter(uint8_t timer, uint16_t value) {
    timers[timer].counter = value;
}

void Timers::setMode(uint8_t timer, uint16_t value) {
    timers[timer].mode = value;
}

void Timers::setTarget(uint8_t timer, uint16_t value) {
    timers[timer].target = value;
}

void Timers::setSynchronizationEnable(uint8_t timer, bool value) {
    timers[timer].mode = (timers[timer].mode & ~(0x01 << 0)) | ((value & 0x01) << 0);
}

void Timers::setSynchronizationMode(uint8_t timer, uint8_t value) {
    timers[timer].mode = (timers[timer].mode & ~(0x03 << 1)) | ((value & 0x03) << 1);
}

void Timers::setResetMode(uint8_t timer, bool value) {
    timers[timer].mode = (timers[timer].mode & ~(0x01 << 3)) | ((value & 0x01) << 3);
}

void Timers::setIrqTargetEnable(uint8_t timer, bool value) {
    timers[timer].mode = (timers[timer].mode & ~(0x01 << 4)) | ((value & 0x01) << 4);
}

void Timers::setIrqOverflowEnable(uint8_t timer, bool value) {
    timers[timer].mode = (timers[timer].mode & ~(0x01 << 5)) | ((value & 0x01) << 5);
}

void Timers::setIrqRepeat(uint8_t timer, bool value) {
    timers[timer].mode = (timers[timer].mode & ~(0x01 << 6)) | ((value & 0x01) << 6);
}

void Timers::setIrqToggle(uint8_t timer, bool value) {
    timers[timer].mode = (timers[timer].mode & ~(0x01 << 7)) | ((value & 0x01) << 7);
}

void Timers::setClockSource(uint8_t timer, uint8_t value) {
    timers[timer].mode = (timers[timer].mode & ~(0x03 << 8)) | ((value & 0x03) << 8);
}

void Timers::setInterruptRequest(uint8_t timer, bool value) {
    timers[timer].mode = (timers[timer].mode & ~(0x01 << 10)) | ((value & 0x01) << 10);
}

void Timers::setReachedTarget(uint8_t timer, bool value) {
    timers[timer].mode = (timers[timer].mode & ~(0x01 << 11)) | ((value & 0x01) << 11);
}

void Timers::setReachedOverflow(uint8_t timer, bool value) {
    timers[timer].mode = (timers[timer].mode & ~(0x01 << 12)) | ((value & 0x01) << 12);
}
