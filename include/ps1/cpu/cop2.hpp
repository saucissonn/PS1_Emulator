#pragma once

#include <cstdint>

#include "ps1/cpu/operand.hpp"

typedef struct { // No alpha
	uint8_t r;
    uint8_t g;
    uint8_t b;
	uint8_t code;
} RGBColor;

class Cpu;

class Cop2 {
    public:
		Cop2(Cpu *cpu_);
		~Cop2();		

        int decodeCommand(uint32_t command);

		// Utils 

		// Data registers
		void setV0X(int16_t value);
		void setV0Y(int16_t value);
		void setV0Z(int16_t value);

		void setV1X(int16_t value);
		void setV1Y(int16_t value);
		void setV1Z(int16_t value);

		void setV2X(int16_t value);
		void setV2Y(int16_t value);
		void setV2Z(int16_t value);

		void setRGBC(uint32_t value);
		void setOTZ(uint16_t value);

		void setIR0(int16_t value);
		void setIR1(int16_t value);
		void setIR2(int16_t value);
		void setIR3(int16_t value);

		void setSXY0(uint32_t value);
		void setSXY1(uint32_t value);
		void setSXY2(uint32_t value);
		void setSXYP(uint32_t value);

		void setSX0(int16_t value);
		void setSX1(int16_t value);
		void setSX2(int16_t value);
		void setSXP(int16_t value);

		void setSY0(int16_t value);
		void setSY1(int16_t value);
		void setSY2(int16_t value);
		void setSYP(int16_t value);

		void setSZ0(uint16_t value);
		void setSZ1(uint16_t value);
		void setSZ2(uint16_t value);
		void setSZ3(uint16_t value);

		void setRGB0(uint32_t value);
		void setRGB1(uint32_t value);
		void setRGB2(uint32_t value);

		void setMAC0(int32_t value);
		void setMAC1(int32_t value);
		void setMAC2(int32_t value);
		void setMAC3(int32_t value);

		void setIRGB(uint16_t value);
		void setORGB(uint16_t value);

		void setLZCS(int32_t value);
		void setLZCR(int32_t value);


		// Data register getters
		int16_t getV0X();
		int16_t getV0Y();
		int16_t getV0Z();

		int16_t getV1X();
		int16_t getV1Y();
		int16_t getV1Z();

		int16_t getV2X();
		int16_t getV2Y();
		int16_t getV2Z();

		uint32_t getRGBC();
		uint16_t getOTZ();

		int16_t getIR0();
		int16_t getIR1();
		int16_t getIR2();
		int16_t getIR3();

		uint32_t getSXY0();
		uint32_t getSXY1();
		uint32_t getSXY2();
		uint32_t getSXYP();

		int16_t getSX0();
		int16_t getSX1();
		int16_t getSX2();
		int16_t getSXP();

		int16_t getSY0();
		int16_t getSY1();
		int16_t getSY2();
		int16_t getSYP();

		uint16_t getSZ0();
		uint16_t getSZ1();
		uint16_t getSZ2();
		uint16_t getSZ3();

		uint32_t getRGB0();
		uint32_t getRGB1();
		uint32_t getRGB2();

		int32_t getMAC0();
		int32_t getMAC1();
		int32_t getMAC2();
		int32_t getMAC3();

		uint16_t getIRGB();
		uint16_t getORGB();

		int32_t getLZCS();
		int32_t getLZCR();


		// Control registers
		void setRT11(int16_t value);
		void setRT12(int16_t value);
		void setRT13(int16_t value);
		void setRT21(int16_t value);
		void setRT22(int16_t value);
		void setRT23(int16_t value);
		void setRT31(int16_t value);
		void setRT32(int16_t value);
		void setRT33(int16_t value);

		void setTRX(int32_t value);
		void setTRY(int32_t value);
		void setTRZ(int32_t value);

		void setL11(int16_t value);
		void setL12(int16_t value);
		void setL13(int16_t value);
		void setL21(int16_t value);
		void setL22(int16_t value);
		void setL23(int16_t value);
		void setL31(int16_t value);
		void setL32(int16_t value);
		void setL33(int16_t value);

		void setRBK(int32_t value);
		void setGBK(int32_t value);
		void setBBK(int32_t value);

		void setLR1(int16_t value);
		void setLR2(int16_t value);
		void setLR3(int16_t value);
		void setLG1(int16_t value);
		void setLG2(int16_t value);
		void setLG3(int16_t value);
		void setLB1(int16_t value);
		void setLB2(int16_t value);
		void setLB3(int16_t value);

		void setRFC(int32_t value);
		void setGFC(int32_t value);
		void setBFC(int32_t value);

		void setOFX(int32_t value);
		void setOFY(int32_t value);

		void setH(uint16_t value);
		void setDQA(int16_t value);
		void setDQB(int32_t value);

		void setZSF3(int16_t value);
		void setZSF4(int16_t value);

		void setFLAG(uint32_t value);


		// Control register getters
		int16_t getRT11();
		int16_t getRT12();
		int16_t getRT13();
		int16_t getRT21();
		int16_t getRT22();
		int16_t getRT23();
		int16_t getRT31();
		int16_t getRT32();
		int16_t getRT33();

		int32_t getTRX();
		int32_t getTRY();
		int32_t getTRZ();

		int16_t getL11();
		int16_t getL12();
		int16_t getL13();
		int16_t getL21();
		int16_t getL22();
		int16_t getL23();
		int16_t getL31();
		int16_t getL32();
		int16_t getL33();

		int32_t getRBK();
		int32_t getGBK();
		int32_t getBBK();

		int16_t getLR1();
		int16_t getLR2();
		int16_t getLR3();
		int16_t getLG1();
		int16_t getLG2();
		int16_t getLG3();
		int16_t getLB1();
		int16_t getLB2();
		int16_t getLB3();

		int32_t getRFC();
		int32_t getGFC();
		int32_t getBFC();

		int32_t getOFX();
		int32_t getOFY();

		uint16_t getH();
		int16_t getDQA();
		int32_t getDQB();

		int16_t getZSF3();
		int16_t getZSF4();

		uint32_t getFLAG();

	private:
		Cpu *cpu;

        uint32_t GPR[32]; // General purpose registers
        Operand *operand; // Current operands
		RGBColor *RGBColors[3]; // Color FIFO

		int initRGBColors();
		int destroyRGBColors();
		int writeRGBColors(uint8_t r, uint8_t g, uint8_t b, uint8_t code);

		// Commands Utils

		int32_t saturateIR(int64_t value, uint8_t index, bool lm);
		int32_t saturateIR0(int64_t value);
		uint16_t saturateSZ(int64_t value);
		uint16_t saturateOTZ(int64_t value);
		int32_t saturateSX(int64_t value);
        int32_t saturateSY(int64_t value);
		void checkMAC(int64_t value, uint8_t index);
		void checkMAC0(int64_t value);

		int applyLightMatrix(uint8_t sf);
		int applyColorMatrix(uint8_t sf);
		int modulateColor();
		int interpolateColor();
		int shiftMac(uint8_t sf);
		int pushColorFifo();
		int interpolateMac(uint8_t sf);

		int32_t getValueTV(uint8_t index);
        int32_t getValueMV(uint8_t index, uint8_t IR);
        int32_t getValueMM(uint8_t y, uint8_t x);

		// Commands (Sorted by real command)

		int RTPS();
		int NCLIP();
		int OP();
		int DPCS();
		int INTPL();
		int MVMVA();
		int NCDS();
		int CDP();
		int NCDT();
		int NCCS();
		int CC();
		int NCS();
		int NCT();
		int SQR();
		int DCPL();
		int DPCT();
		int AVSZ3();
		int AVSZ4();
		int GPF();
		int GPL();
		int NCCT();

		void transfromCommand(uint32_t command);
};
