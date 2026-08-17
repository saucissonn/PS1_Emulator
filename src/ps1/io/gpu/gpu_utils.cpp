#include "ps1/io/gpu/gpu.hpp"

int Gpu::resetCommandBuffer() {
    gp0.resetCommandBuffer();

    return 0;
}

uint16_t Gpu::getDisplayStartX() {
	return displayStartX;
}

uint16_t Gpu::getDisplayStartY() {
    return displayStartY;
}

uint16_t Gpu::getDisplayX1() {
    return displayX1;
}

uint16_t Gpu::getDisplayX2() {
    return displayX2;
}

uint16_t Gpu::getDisplayY1() {
    return displayY1;
}

uint16_t Gpu::getDisplayY2() {
    return displayY2;
}

uint32_t Gpu::getGpuread() {
    return gpuread;
}

uint32_t Gpu::getGpustat() {
	return gpustat;
}

uint8_t Gpu::getGpustatPageX() {
    return (gpustat >> 0) & 0x0F;
}

bool Gpu::getGpustatPageY() {
    return (gpustat >> 4) & 0x01;
}

uint8_t Gpu::getGpustatSemiTransparency() {
    return (gpustat >> 5) & 0x03;
}

uint8_t Gpu::getGpustatTexturePageColors() {
    return (gpustat >> 7) & 0x03;
}

bool Gpu::getGpustatDither() {
    return (gpustat >> 9) & 0x01;
}

bool Gpu::getGpustatInterlaceDrawing() {
    return (gpustat >> 10) & 0x01;
}

bool Gpu::getGpustatSetMaskBit() {
    return (gpustat >> 11) & 0x01;
}

bool Gpu::getGpustatDrawPixels() {
    return (gpustat >> 12) & 0x01;
}

bool Gpu::getGpustatInterlaceField() {
    return (gpustat >> 13) & 0x01;
}

bool Gpu::getGpustatReverseflag() {
    return (gpustat >> 14) & 0x01;
}

bool Gpu::getGpustatPageYBit9() {
    return (gpustat >> 15) & 0x01;
}

bool Gpu::getGpustatHorizontalResolution2() {
    return (gpustat >> 16) & 0x01;
}

uint8_t Gpu::getGpustatHorizontalResolution1() {
    return (gpustat >> 17) & 0x03;
}

bool Gpu::getGpustatVerticalResolution() {
    return (gpustat >> 19) & 0x01;
}

bool Gpu::getGpustatVideoMode() {
    return (gpustat >> 20) & 0x01;
}

bool Gpu::getGpustatDisplayAreaColorDepth() {
    return (gpustat >> 21) & 0x01;
}

bool Gpu::getGpustatVerticalInterlace() {
    return (gpustat >> 22) & 0x01;
}

bool Gpu::getGpustatDisplayEnable() {
    return (gpustat >> 23) & 0x01;
}

bool Gpu::getGpustatInterruptRequest() {
    return (gpustat >> 24) & 0x01;
}

bool Gpu::getGpustatDmaDataRequest() {
    return (gpustat >> 25) & 0x01;
}

bool Gpu::getGpustatReadyToReceiveCmdWord() {
    return (gpustat >> 26) & 0x01;
}

bool Gpu::getGpustatReadFifoDataAvailable() {
    return (gpustat >> 27) & 0x01;
}

bool Gpu::getGpustatWriteFifoEmpty() {
    return (gpustat >> 28) & 0x01;
}

uint8_t Gpu::getGpustatDmaDirection() {
    return (gpustat >> 29) & 0x03;
}

bool Gpu::getGpustatDrawingLine() {
    return (gpustat >> 31) & 0x01;
}


void Gpu::setDisplayStartX(uint16_t value) {
	displayStartX = value & 0x4FF;
}

void Gpu::setDisplayStartY(uint16_t value) {
	displayStartY = value & 0x4FF;
}

void Gpu::setDisplayX1(uint16_t value) {
    displayX1 = value & 0x0FFF;
}

void Gpu::setDisplayX2(uint16_t value) {
    displayX2 = value & 0x0FFF;
}

void Gpu::setDisplayY1(uint16_t value) {
    displayY1 = value & 0x03FF;
}

void Gpu::setDisplayY2(uint16_t value) {
    displayY2 = value & 0x03FF;
}

void Gpu::setGpustatPageX(uint8_t value) {
    gpustat &= ~(0x0F << 0);
    gpustat |= (value & 0x0F) << 0;
}

void Gpu::setGpustatPageY(bool value) {
    gpustat &= ~(0x01 << 4);
    gpustat |= (value & 0x01) << 4;
}

void Gpu::setGpustatSemiTransparency(uint8_t value) {
    gpustat &= ~(0x03 << 5);
    gpustat |= (value & 0x03) << 5;
}

void Gpu::setGpustatTexturePageColors(uint8_t value) {
    gpustat &= ~(0x03 << 7);
    gpustat |= (value & 0x03) << 7;
}

void Gpu::setGpustatDither(bool value) {
    gpustat &= ~(0x01 << 9);
    gpustat |= (value & 0x01) << 9;
}

void Gpu::setGpustatInterlaceDrawing(bool value) {
    gpustat &= ~(0x01 << 10);
    gpustat |= (value & 0x01) << 10;
}

void Gpu::setGpustatSetMaskBit(bool value) {
    gpustat &= ~(0x01 << 11);
    gpustat |= (value & 0x01) << 11;
}

void Gpu::setGpustatDrawPixels(bool value) {
    gpustat &= ~(0x01 << 12);
    gpustat |= (value & 0x01) << 12;
}

void Gpu::setGpustatInterlaceField(bool value) {
    gpustat &= ~(0x01 << 13);
    gpustat |= (value & 0x01) << 13;
}

void Gpu::setGpustatReverseflag(bool value) {
    gpustat &= ~(0x01 << 14);
    gpustat |= (value & 0x01) << 14;
}

void Gpu::setGpustatPageYBit9(bool value) {
    gpustat &= ~(0x01 << 15);
    gpustat |= (value & 0x01) << 15;
}

void Gpu::setGpustatHorizontalResolution2(bool value) {
    gpustat &= ~(0x01 << 16);
    gpustat |= (value & 0x01) << 16;
}

void Gpu::setGpustatHorizontalResolution1(uint8_t value) {
    gpustat &= ~(0x03 << 17);
    gpustat |= (value & 0x03) << 17;
}

void Gpu::setGpustatVerticalResolution(bool value) {
    gpustat &= ~(0x01 << 19);
    gpustat |= (value & 0x01) << 19;
}

void Gpu::setGpustatVideoMode(bool value) {
    gpustat &= ~(0x01 << 20);
    gpustat |= (value & 0x01) << 20;
}

void Gpu::setGpustatDisplayAreaColorDepth(bool value) {
    gpustat &= ~(0x01 << 21);
    gpustat |= (value & 0x01) << 21;
}

void Gpu::setGpustatVerticalInterlace(bool value) {
    gpustat &= ~(0x01 << 22);
    gpustat |= (value & 0x01) << 22;
}

void Gpu::setGpustatDisplayEnable(bool value) {
    gpustat &= ~(0x01 << 23);
    gpustat |= (value & 0x01) << 23;
}

void Gpu::setGpustatInterruptRequest(bool value) {
    gpustat &= ~(0x01 << 24);
    gpustat |= (value & 0x01) << 24;
}

void Gpu::setGpustatDmaDataRequest(bool value) {
    gpustat &= ~(0x01 << 25);
    gpustat |= (value & 0x01) << 25;
}

void Gpu::setGpustatReadyToReceiveCmdWord(bool value) {
    gpustat &= ~(0x01 << 26);
    gpustat |= (value & 0x01) << 26;
}

void Gpu::setGpustatReadFifoDataAvailable(bool value) {
    gpustat &= ~(0x01 << 27);
    gpustat |= (value & 0x01) << 27;
}

void Gpu::setGpustatWriteFifoEmpty(bool value) {
    gpustat &= ~(0x01 << 28);
    gpustat |= (value & 0x01) << 28;
}

void Gpu::setGpustatDmaDirection(uint8_t value) {
    gpustat &= ~(0x03 << 29);
    gpustat |= (value & 0x03) << 29;
}

void Gpu::setGpustatDrawingLine(bool value) {
    gpustat &= ~(0x01 << 31);
    gpustat |= (value & 0x01) << 31;
}
