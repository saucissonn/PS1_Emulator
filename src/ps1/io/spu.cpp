#include "ps1/io/spu.hpp"

Spu::Spu() {
    for (int i = 0; i < 24; i++) {
        voices[i].volumeLeft = 0;
        voices[i].volumeRight = 0;
        voices[i].sampleRate = 0;
        voices[i].startAddress = 0;
        voices[i].adsrAttackDecaySustain = 0;
        voices[i].adsrRelease = 0;
        voices[i].currentVolume = 0;
        voices[i].repeatAddress = 0;

        internalVolume[i] = 0;
    }

    reverb.dAPF1 = 0;
    reverb.dAPF2 = 0;
    reverb.vIIR = 0;
    reverb.vCOMB1 = 0;
    reverb.vCOMB2 = 0;
    reverb.vCOMB3 = 0;
    reverb.vCOMB4 = 0;
    reverb.vWALL = 0;
    reverb.vAPF1 = 0;
    reverb.vAPF2 = 0;

    reverb.mSAME = 0;
    reverb.mCOMB1 = 0;
    reverb.mCOMB2 = 0;
    reverb.dSAME = 0;
    reverb.mDIFF = 0;
    reverb.mCOMB3 = 0;
    reverb.mCOMB4 = 0;
    reverb.dDIFF = 0;
    reverb.mAPF1 = 0;
    reverb.mAPF2 = 0;
    reverb.vIN = 0;

    mainVolumeLeft = 0;
    mainVolumeRight = 0;
    reverbVolumeLeft = 0;
    reverbVolumeRight = 0;

    keyOn = 0;
    keyOff = 0;
    channelFm = 0;
    channelNoise = 0;
    channelReverb = 0;
    channelStatus = 0;

    reverbWorkArea = 0;
    irqAddress = 0;
    transferAddress = 0;
    transferFifo = 0;
    control = 0;
    transferControl = 0;
    status = 0;

    cdVolumeLeft = 0;
    cdVolumeRight = 0;
    externalVolumeLeft = 0;
    externalVolumeRight = 0;
    currentMainVolumeLeft = 0;
    currentMainVolumeRight = 0;

    unknown = 0;

    for (int i = 0; i < 0x20; i++) {
        internalUnknown[i] = 0;
    }

    for (int i = 0; i < 0x180; i++) {
        internalUnknown2[i] = 0;
    }
}

Spu::~Spu() {
    return;
}

uint16_t Spu::read(uint32_t address) {
    if (address >= 0x1F801C00 && address <= 0x1F801D7E) {
        uint32_t voice = (address - 0x1F801C00) / 0x10;
        uint32_t offset = (address - 0x1F801C00) % 0x10;

        switch (offset) {
            case 0x0:
                return voices[voice].volumeLeft;

            case 0x2:
                return voices[voice].volumeRight;

            case 0x4:
                return voices[voice].sampleRate;

            case 0x6:
                return voices[voice].startAddress;

            case 0x8:
                return voices[voice].adsrAttackDecaySustain;

            case 0xA:
                return voices[voice].adsrRelease;

            case 0xC:
                return voices[voice].currentVolume;

            case 0xE:
                return voices[voice].repeatAddress;
        }
    }

    switch (address) {
        case 0x1F801D80:
            return mainVolumeLeft;

        case 0x1F801D82:
            return mainVolumeRight;

        case 0x1F801D84:
            return reverbVolumeLeft;

        case 0x1F801D86:
            return reverbVolumeRight;

        case 0x1F801D90:
            return channelFm & 0xFFFF;

        case 0x1F801D92:
            return channelFm >> 16;

        case 0x1F801D94:
            return channelNoise & 0xFFFF;

        case 0x1F801D96:
            return channelNoise >> 16;

        case 0x1F801D98:
            return channelReverb & 0xFFFF;

        case 0x1F801D9A:
            return channelReverb >> 16;

        case 0x1F801D9C:
            return channelStatus & 0xFFFF;

        case 0x1F801D9E:
            return channelStatus >> 16;

        case 0x1F801DA0:
            return unknown;

        case 0x1F801DA2:
            return reverbWorkArea;

        case 0x1F801DA4:
            return irqAddress;

        case 0x1F801DA6:
            return transferAddress;

        case 0x1F801DA8:
            return transferFifo;

        case 0x1F801DAA:
            return control;

        case 0x1F801DAC:
            return transferControl;

        case 0x1F801DAE:
            return status;

        case 0x1F801DB0:
            return cdVolumeLeft;

        case 0x1F801DB2:
            return cdVolumeRight;

        case 0x1F801DB4:
            return externalVolumeLeft;

        case 0x1F801DB6:
            return externalVolumeRight;

        case 0x1F801DB8:
            return currentMainVolumeLeft;

        case 0x1F801DBA:
            return currentMainVolumeRight;

        case 0x1F801DBC:
        case 0x1F801DBE:
            return unknown;
    }

    if (address >= 0x1F801DC0 && address <= 0x1F801DFF) {
        switch (address) {
            case 0x1F801DC0:
                return reverb.dAPF1;

            case 0x1F801DC2:
                return reverb.dAPF2;

            case 0x1F801DC4:
                return reverb.vIIR;

            case 0x1F801DC6:
                return reverb.vCOMB1;

            case 0x1F801DC8:
                return reverb.vCOMB2;

            case 0x1F801DCA:
                return reverb.vCOMB3;

            case 0x1F801DCC:
                return reverb.vCOMB4;

            case 0x1F801DCE:
                return reverb.vWALL;

            case 0x1F801DD0:
                return reverb.vAPF1;

            case 0x1F801DD2:
                return reverb.vAPF2;

            case 0x1F801DD4:
                return reverb.mSAME & 0xFFFF;

            case 0x1F801DD6:
                return reverb.mSAME >> 16;

            case 0x1F801DD8:
                return reverb.mCOMB1 & 0xFFFF;

            case 0x1F801DDA:
                return reverb.mCOMB1 >> 16;

            case 0x1F801DDC:
                return reverb.mCOMB2 & 0xFFFF;

            case 0x1F801DDE:
                return reverb.mCOMB2 >> 16;

            case 0x1F801DE0:
                return reverb.dSAME & 0xFFFF;

            case 0x1F801DE2:
                return reverb.dSAME >> 16;

            case 0x1F801DE4:
                return reverb.mDIFF & 0xFFFF;

            case 0x1F801DE6:
                return reverb.mDIFF >> 16;

            case 0x1F801DE8:
                return reverb.mCOMB3 & 0xFFFF;

            case 0x1F801DEA:
                return reverb.mCOMB3 >> 16;

            case 0x1F801DEC:
                return reverb.mCOMB4 & 0xFFFF;

            case 0x1F801DEE:
                return reverb.mCOMB4 >> 16;

            case 0x1F801DF0:
                return reverb.dDIFF & 0xFFFF;

            case 0x1F801DF2:
                return reverb.dDIFF >> 16;

            case 0x1F801DF4:
                return reverb.mAPF1 & 0xFFFF;

            case 0x1F801DF6:
                return reverb.mAPF1 >> 16;

            case 0x1F801DF8:
                return reverb.mAPF2 & 0xFFFF;

            case 0x1F801DFA:
                return reverb.mAPF2 >> 16;

            case 0x1F801DFC:
                return reverb.vIN & 0xFFFF;

            case 0x1F801DFE:
                return reverb.vIN >> 16;
        }
    }

    if (address >= 0x1F801E00 && address <= 0x1F801E5C) {
        uint32_t voice = (address - 0x1F801E00) / 0x04;
        uint32_t offset = (address - 0x1F801E00) % 0x04;

        uint32_t value = internalVolume[voice];

        if (offset == 0x0)
            return value & 0xFFFF;

        if (offset == 0x2)
            return value >> 16;
    }

    if (address >= 0x1F801E60 && address < 0x1F801E80) {
        return internalUnknown[address - 0x1F801E60] |
               (internalUnknown[address - 0x1F801E60 + 1] << 8);
    }

    return 0;
}

void Spu::write(uint32_t address, uint16_t value) {
    if (address >= 0x1F801C00 && address <= 0x1F801D7E) {
        uint32_t voice = (address - 0x1F801C00) / 0x10;
        uint32_t offset = (address - 0x1F801C00) % 0x10;

        switch (offset) {
            case 0x0:
                voices[voice].volumeLeft = value;
                return;

            case 0x2:
                voices[voice].volumeRight = value;
                return;

            case 0x4:
                voices[voice].sampleRate = value;
                return;

            case 0x6:
                voices[voice].startAddress = value;
                return;

            case 0x8:
                voices[voice].adsrAttackDecaySustain = value;
                return;

            case 0xA:
                voices[voice].adsrRelease = value;
                return;

            case 0xC:
                voices[voice].currentVolume = value;
                return;

            case 0xE:
                voices[voice].repeatAddress = value;
                return;
        }
    }

    switch (address) {
        case 0x1F801D80:
            mainVolumeLeft = value;
            return;

        case 0x1F801D82:
            mainVolumeRight = value;
            return;

        case 0x1F801D84:
            reverbVolumeLeft = value;
            return;

        case 0x1F801D86:
            reverbVolumeRight = value;
            return;

        case 0x1F801D88:
            keyOn = (keyOn & 0xFFFF0000) | value;
            return;

        case 0x1F801D8A:
            keyOn = (keyOn & 0x0000FFFF) | ((uint32_t)value << 16);
            return;

        case 0x1F801D8C:
            keyOff = (keyOff & 0xFFFF0000) | value;
            return;

        case 0x1F801D8E:
            keyOff = (keyOff & 0x0000FFFF) | ((uint32_t)value << 16);
            return;

        case 0x1F801D90:
            channelFm = (channelFm & 0xFFFF0000) | value;
            return;

        case 0x1F801D92:
            channelFm = (channelFm & 0x0000FFFF) | ((uint32_t)value << 16);
            return;

        case 0x1F801D94:
            channelNoise = (channelNoise & 0xFFFF0000) | value;
            return;

        case 0x1F801D96:
            channelNoise = (channelNoise & 0x0000FFFF) | ((uint32_t)value << 16);
            return;

        case 0x1F801D98:
            channelReverb = (channelReverb & 0xFFFF0000) | value;
            return;

        case 0x1F801D9A:
            channelReverb = (channelReverb & 0x0000FFFF) | ((uint32_t)value << 16);
            return;

        case 0x1F801DA2:
            reverbWorkArea = value;
            return;

        case 0x1F801DA4:
            irqAddress = value;
            return;

        case 0x1F801DA6:
            transferAddress = value;
            return;

        case 0x1F801DA8:
            transferFifo = value;
            return;

        case 0x1F801DAA:
            control = value;
            return;

        case 0x1F801DAC:
            transferControl = value;
            return;

        case 0x1F801DB0:
            cdVolumeLeft = value;
            return;

        case 0x1F801DB2:
            cdVolumeRight = value;
            return;

        case 0x1F801DB4:
            externalVolumeLeft = value;
            return;

        case 0x1F801DB6:
            externalVolumeRight = value;
            return;

        case 0x1F801DBC:
        case 0x1F801DBE:
            unknown = value;
            return;
    }

    if (address >= 0x1F801DC0 && address <= 0x1F801DFF) {
        switch (address) {
            case 0x1F801DC0:
                reverb.dAPF1 = value;
                return;

            case 0x1F801DC2:
                reverb.dAPF2 = value;
                return;

            case 0x1F801DC4:
                reverb.vIIR = value;
                return;

            case 0x1F801DC6:
                reverb.vCOMB1 = value;
                return;

            case 0x1F801DC8:
                reverb.vCOMB2 = value;
                return;

            case 0x1F801DCA:
                reverb.vCOMB3 = value;
                return;

            case 0x1F801DCC:
                reverb.vCOMB4 = value;
                return;

            case 0x1F801DCE:
                reverb.vWALL = value;
                return;

            case 0x1F801DD0:
                reverb.vAPF1 = value;
                return;

            case 0x1F801DD2:
                reverb.vAPF2 = value;
                return;

            case 0x1F801DD4:
                reverb.mSAME = (reverb.mSAME & 0xFFFF0000) | value;
                return;

            case 0x1F801DD6:
                reverb.mSAME = (reverb.mSAME & 0x0000FFFF) | ((uint32_t)value << 16);
                return;

            case 0x1F801DD8:
                reverb.mCOMB1 = (reverb.mCOMB1 & 0xFFFF0000) | value;
                return;

            case 0x1F801DDA:
                reverb.mCOMB1 = (reverb.mCOMB1 & 0x0000FFFF) | ((uint32_t)value << 16);
                return;

            case 0x1F801DDC:
                reverb.mCOMB2 = (reverb.mCOMB2 & 0xFFFF0000) | value;
                return;

            case 0x1F801DDE:
                reverb.mCOMB2 = (reverb.mCOMB2 & 0x0000FFFF) | ((uint32_t)value << 16);
                return;

            case 0x1F801DE0:
                reverb.dSAME = (reverb.dSAME & 0xFFFF0000) | value;
                return;

            case 0x1F801DE2:
                reverb.dSAME = (reverb.dSAME & 0x0000FFFF) | ((uint32_t)value << 16);
                return;

            case 0x1F801DE4:
                reverb.mDIFF = (reverb.mDIFF & 0xFFFF0000) | value;
                return;

            case 0x1F801DE6:
                reverb.mDIFF = (reverb.mDIFF & 0x0000FFFF) | ((uint32_t)value << 16);
                return;

            case 0x1F801DE8:
                reverb.mCOMB3 = (reverb.mCOMB3 & 0xFFFF0000) | value;
                return;

            case 0x1F801DEA:
                reverb.mCOMB3 = (reverb.mCOMB3 & 0x0000FFFF) | ((uint32_t)value << 16);
                return;

            case 0x1F801DEC:
                reverb.mCOMB4 = (reverb.mCOMB4 & 0xFFFF0000) | value;
                return;

            case 0x1F801DEE:
                reverb.mCOMB4 = (reverb.mCOMB4 & 0x0000FFFF) | ((uint32_t)value << 16);
                return;

            case 0x1F801DF0:
                reverb.dDIFF = (reverb.dDIFF & 0xFFFF0000) | value;
                return;

            case 0x1F801DF2:
                reverb.dDIFF = (reverb.dDIFF & 0x0000FFFF) | ((uint32_t)value << 16);
                return;

            case 0x1F801DF4:
                reverb.mAPF1 = (reverb.mAPF1 & 0xFFFF0000) | value;
                return;

            case 0x1F801DF6:
                reverb.mAPF1 = (reverb.mAPF1 & 0x0000FFFF) | ((uint32_t)value << 16);
                return;

            case 0x1F801DF8:
                reverb.mAPF2 = (reverb.mAPF2 & 0xFFFF0000) | value;
                return;

            case 0x1F801DFA:
                reverb.mAPF2 = (reverb.mAPF2 & 0x0000FFFF) | ((uint32_t)value << 16);
                return;

            case 0x1F801DFC:
                reverb.vIN = (reverb.vIN & 0xFFFF0000) | value;
                return;

            case 0x1F801DFE:
                reverb.vIN = (reverb.vIN & 0x0000FFFF) | ((uint32_t)value << 16);
                return;
        }
    }

    if (address >= 0x1F801E00 && address <= 0x1F801E5C) {
        uint32_t voice = (address - 0x1F801E00) / 0x04;
        uint32_t offset = (address - 0x1F801E00) % 0x04;

        if (offset == 0x0) {
            internalVolume[voice] =
                (internalVolume[voice] & 0xFFFF0000) | value;
        }

        if (offset == 0x2) {
            internalVolume[voice] =
                (internalVolume[voice] & 0x0000FFFF) | ((uint32_t)value << 16);
        }

        return;
    }

    if (address >= 0x1F801E60 && address < 0x1F801E80) {
        internalUnknown[address - 0x1F801E60] = value & 0xFF;
        internalUnknown[address - 0x1F801E60 + 1] = value >> 8;
        return;
    }
}
