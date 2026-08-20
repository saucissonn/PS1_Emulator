#include "ps1/io/dma.hpp"

uint32_t Dma::getMADR(uint8_t channel) {
    return channels[channel].MADR;
}

uint32_t Dma::getBCR(uint8_t channel) {
    return channels[channel].BCR;
}

uint32_t Dma::getCHCR(uint8_t channel) {
	return channels[channel].CHCR;
}

uint8_t Dma::getChannelTransferDirection(uint8_t channel) {
    return (channels[channel].CHCR >> 0) & 0x01;
}

uint8_t Dma::getChannelMemoryAddressStep(uint8_t channel) {
    return (channels[channel].CHCR >> 1) & 0x01;
}

uint8_t Dma::getChannelChoppingEnable(uint8_t channel) {
    return (channels[channel].CHCR >> 8) & 0x01;
}

uint8_t Dma::getChannelSyncMode(uint8_t channel) {
    return (channels[channel].CHCR >> 9) & 0x03;
}

uint8_t Dma::getChannelChoppingDmaWindowSize(uint8_t channel) {
    return (channels[channel].CHCR >> 16) & 0x07;
}

uint8_t Dma::getChannelChoppingCpuWindowSize(uint8_t channel) {
    return (channels[channel].CHCR >> 20) & 0x07;
}

bool Dma::getChannelStartBusy(uint8_t channel) {
    return (channels[channel].CHCR >> 24) & 0x01;
}

bool Dma::getChannelStartTrigger(uint8_t channel) {
    return (channels[channel].CHCR >> 28) & 0x01;
}

bool Dma::getChannelUnknown29(uint8_t channel) {
    return (channels[channel].CHCR >> 29) & 0x01;
}

bool Dma::getChannelUnknown30(uint8_t channel) {
    return (channels[channel].CHCR >> 30) & 0x01;
}

uint8_t Dma::getDmaPriority(uint8_t channel) {
    return (dpcr >> (channel * 4)) & 0x07;
}

bool Dma::getDmaMasterEnable(uint8_t channel) {
    return (dpcr >> ((channel * 4) + 3)) & 0x01;
}

uint8_t Dma::getDmaUnknownPriority() {
    return (dpcr >> 28) & 0x07;
}

bool Dma::getDmaUnknown31() {
    return (dpcr >> 31) & 0x01;
}

uint8_t Dma::getDicrUnknown() {
    return dicr & 0x3F;
}

bool Dma::getDicrForceIrq() {
    return (dicr >> 15) & 0x01;
}

bool Dma::getDicrIrqEnable(uint8_t channel) {
    return (dicr >> (16 + channel)) & 0x01;
}

bool Dma::getDicrIrqMasterEnable() {
    return (dicr >> 23) & 0x01;
}

bool Dma::getDicrIrqFlag(uint8_t channel) {
    return (dicr >> (24 + channel)) & 0x01;
}

bool Dma::getDicrIrqSignal() {
    return (dicr >> 31) & 0x01;
}


void Dma::setChannelTransferDirection(uint8_t channel, uint8_t value) {
    channels[channel].CHCR &= ~(0x01 << 0);
    channels[channel].CHCR |= (value & 0x01) << 0;
}

void Dma::setChannelMemoryAddressStep(uint8_t channel, uint8_t value) {
    channels[channel].CHCR &= ~(0x01 << 1);
    channels[channel].CHCR |= (value & 0x01) << 1;
}

void Dma::setChannelChoppingEnable(uint8_t channel, uint8_t value) {
    channels[channel].CHCR &= ~(0x01 << 8);
    channels[channel].CHCR |= (value & 0x01) << 8;
}

void Dma::setChannelSyncMode(uint8_t channel, uint8_t value) {
    channels[channel].CHCR &= ~(0x03 << 9);
    channels[channel].CHCR |= (value & 0x03) << 9;
}

void Dma::setChannelChoppingDmaWindowSize(uint8_t channel, uint8_t value) {
    channels[channel].CHCR &= ~(0x07 << 16);
    channels[channel].CHCR |= (value & 0x07) << 16;
}

void Dma::setChannelChoppingCpuWindowSize(uint8_t channel, uint8_t value) {
    channels[channel].CHCR &= ~(0x07 << 20);
    channels[channel].CHCR |= (value & 0x07) << 20;
}

void Dma::setChannelStartBusy(uint8_t channel, bool value) {
    channels[channel].CHCR &= ~(0x01 << 24);
    channels[channel].CHCR |= (value & 0x01) << 24;
}

void Dma::setChannelStartTrigger(uint8_t channel, bool value) {
    channels[channel].CHCR &= ~(0x01 << 28);
    channels[channel].CHCR |= (value & 0x01) << 28;
}

void Dma::setChannelUnknown29(uint8_t channel, bool value) {
    channels[channel].CHCR &= ~(0x01 << 29);
    channels[channel].CHCR |= (value & 0x01) << 29;
}

void Dma::setChannelUnknown30(uint8_t channel, bool value) {
    channels[channel].CHCR &= ~(0x01 << 30);
    channels[channel].CHCR |= (value & 0x01) << 30;
}

void Dma::setDmaPriority(uint8_t channel, uint8_t value) {
    dpcr &= ~(0x07 << (channel * 4));
    dpcr |= (value & 0x07) << (channel * 4);
}

void Dma::setDmaMasterEnable(uint8_t channel, bool value) {
    dpcr &= ~(0x01 << ((channel * 4) + 3));
    dpcr |= (value & 0x01) << ((channel * 4) + 3);
}

void Dma::setDmaUnknownPriority(uint8_t value) {
    dpcr &= ~(0x07 << 28);
    dpcr |= (value & 0x07) << 28;
}

void Dma::setDmaUnknown31(bool value) {
    dpcr &= ~(0x01 << 31);
    dpcr |= (value & 0x01) << 31;
}

void Dma::setDicrUnknown(uint8_t value) {
    dicr &= ~(0x3F);
    dicr |= value & 0x3F;
}

void Dma::setDicrForceIrq(bool value) {
    dicr &= ~(0x01 << 15);
    dicr |= (value & 0x01) << 15;
}

void Dma::setDicrIrqEnable(uint8_t channel, bool value) {
    dicr &= ~(0x01 << (16 + channel));
    dicr |= (value & 0x01) << (16 + channel);
}

void Dma::setDicrIrqMasterEnable(bool value) {
    dicr &= ~(0x01 << 23);
    dicr |= (value & 0x01) << 23;
}

void Dma::setDicrIrqFlag(uint8_t channel, bool value) {
    dicr &= ~(0x01 << (24 + channel));
    dicr |= (value & 0x01) << (24 + channel);
}

void Dma::setDicrIrqSignal(bool value) {
    dicr &= ~(0x01 << 31);
    dicr |= (value & 0x01) << 31;
}
