#pragma once

#include <cstdint>

struct SPUVoice {
    uint16_t volumeLeft;
    uint16_t volumeRight;
    uint16_t sampleRate;
    uint16_t startAddress;
    uint16_t adsrAttackDecaySustain;
    uint16_t adsrRelease;
    uint16_t currentVolume;
    uint16_t repeatAddress;
};

struct SPUReverb {
    uint16_t dAPF1;
    uint16_t dAPF2;
    uint16_t vIIR;
    uint16_t vCOMB1;
    uint16_t vCOMB2;
    uint16_t vCOMB3;
    uint16_t vCOMB4;
    uint16_t vWALL;
    uint16_t vAPF1;
    uint16_t vAPF2;

    uint32_t mSAME;
    uint32_t mCOMB1;
    uint32_t mCOMB2;
    uint32_t dSAME;
    uint32_t mDIFF;
    uint32_t mCOMB3;
    uint32_t mCOMB4;
    uint32_t dDIFF;
    uint32_t mAPF1;
    uint32_t mAPF2;
    uint32_t vIN;
};

class Spu {
    public:
        Spu();
        ~Spu();

        uint16_t read(uint32_t address);
		int write(uint32_t address, uint16_t value);

    private:
        SPUVoice voices[24];
        SPUReverb reverb;

        uint16_t mainVolumeLeft;
        uint16_t mainVolumeRight;
        uint16_t reverbVolumeLeft;
        uint16_t reverbVolumeRight;

        uint32_t keyOn;
        uint32_t keyOff;
        uint32_t channelFm;
        uint32_t channelNoise;
        uint32_t channelReverb;
        uint32_t channelStatus;

        uint16_t reverbWorkArea;
        uint16_t irqAddress;
        uint16_t transferAddress;
        uint16_t transferFifo;
        uint16_t control;
        uint16_t transferControl;
        uint16_t status;

        uint16_t cdVolumeLeft;
        uint16_t cdVolumeRight;
        uint16_t externalVolumeLeft;
        uint16_t externalVolumeRight;
        uint16_t currentMainVolumeLeft;
        uint16_t currentMainVolumeRight;

        uint16_t unknown;

        uint32_t internalVolume[24];
        uint8_t internalUnknown[0x20];
        uint8_t internalUnknown2[0x180];
};
