#include "ps1/cpu/cop2.hpp"

#include "utils/error.hpp"

int32_t Cop2::saturateIR(int64_t value, uint8_t index, bool lm) {
    const int32_t IR_MAX = 0x7FFF;
    const int32_t IR_MIN = lm ? 0 : -0x8000;

    if (value > IR_MAX) {
        uint32_t flag = getFLAG();
        flag |= 1u << (24 - index);
        setFLAG(flag);
        return IR_MAX;
    }

    if (value < IR_MIN) {
        uint32_t flag = getFLAG();
        flag |= 1u << (24 - index);
        setFLAG(flag);
        return IR_MIN;
    }

    return (int32_t)value;
}

int32_t Cop2::saturateIR0(int64_t value) {
    const int32_t IR0_MAX = 0x1000;
    const int32_t IR0_MIN = 0;

    if (value > IR0_MAX) {
        uint32_t flag = getFLAG();
        flag |= 1u << 12;
        setFLAG(flag);
        return IR0_MAX;
    }

    if (value < IR0_MIN) {
        uint32_t flag = getFLAG();
        flag |= 1u << 12;
        setFLAG(flag);
        return IR0_MIN;
    }

    return (int32_t)(value);
}

uint16_t Cop2::saturateSZ(int64_t value) {
    const int64_t SZ_MAX = 0xFFFF;
    const int64_t SZ_MIN = 0;

    if (value > SZ_MAX) {
        uint32_t flag = getFLAG();
        flag |= 1u << 18;
        setFLAG(flag);
        return SZ_MAX;
    }

    if (value < SZ_MIN) {
        uint32_t flag = getFLAG();
        flag |= 1u << 18;
        setFLAG(flag);
        return SZ_MIN;
    }

    return (uint16_t)(value);
}

uint16_t Cop2::saturateOTZ(int64_t value) {
    return saturateSZ(value);
}

int32_t Cop2::saturateSX(int64_t value) {
    const int32_t SX_MAX = 0x3FF;
    const int32_t SX_MIN = -0x400;

    if (value > SX_MAX) {
        uint32_t flag = getFLAG();
        flag |= 1u << 14;
        setFLAG(flag);
        return SX_MAX;
    }

    if (value < SX_MIN) {
        uint32_t flag = getFLAG();
        flag |= 1u << 14;
        setFLAG(flag);
        return SX_MIN;
    }

    return (int32_t)(value);
}

int32_t Cop2::saturateSY(int64_t value) {
    const int32_t SY_MAX = 0x3FF;
    const int32_t SY_MIN = -0x400;

    if (value > SY_MAX) {
        uint32_t flag = getFLAG();
        flag |= 1u << 13;
        setFLAG(flag);
        return SY_MAX;
    }

    if (value < SY_MIN) {
        uint32_t flag = getFLAG();
        flag |= 1u << 13;
        setFLAG(flag);
        return SY_MIN;
    }

    return (int32_t)(value);
}

void Cop2::checkMAC(int64_t value, uint8_t index) {
    int64_t MAC_MAX = 0x7FFFFFFFFFFLL;
    int64_t MAC_MIN = -0x80000000000LL;

    uint32_t flag = getFLAG();

    if (value > MAC_MAX) {
        flag |= (1u << (31 - index)); // 30, 29, 28
    }
    else if (value < MAC_MIN) {
        flag |= (1u << (28 - index)); // 27, 26, 25
    }

    setFLAG(flag);
}

void Cop2::checkMAC0(int64_t value) {
    uint32_t flag = getFLAG();

    if (value > INT32_MAX) {
        flag |= (1u << 16);
    }
    else if (value < INT32_MIN) {
        flag |= (1u << 15);
    }

    setFLAG(flag);
}

// Colors

int Cop2::applyLightMatrix(uint8_t sf) { // [IR1,IR2,IR3] = [MAC1,MAC2,MAC3] = (LLM*V0) SAR (sf*12)
    int64_t MAC1 = 0;
    int64_t MAC2 = 0;
    int64_t MAC3 = 0;

	int64_t VX = (int64_t)getV0X();
    int64_t VY = (int64_t)getV0Y();
    int64_t VZ = (int64_t)getV0Z();

    bool lm = operand->lm;

	// LLM * V0
	// [[L11*VX, L12*VY, L13*VZ],
	// [L21*VX, L22*VY, L23*VZ],
	// [L31*VX, L32*VY, L33*VZ]]
    // Each IR (1 2 3) and MAC (1 2 3) is a line of this matrix

    // MAC1
    MAC1 = (int64_t)getL11() * VX + (int64_t)getL12() * VY;
    checkMAC(MAC1, 1);

    MAC1 += (int64_t)getL13() * VZ;
    checkMAC(MAC1, 1);

    MAC1 >>= sf;
    setIR1(saturateIR(MAC1, 1, lm));

    setMAC1((int32_t)MAC1);

	// MAC2
	MAC2 = (int64_t)getL21() * VX + (int64_t)getL22() * VY;
	checkMAC(MAC2, 2);

	MAC2 += (int64_t)getL23() * VZ;
	checkMAC(MAC2, 2);

	MAC2 >>= sf;
	setIR2(saturateIR(MAC2, 2, lm));

	setMAC2((int32_t)MAC2);

	// MAC3
	MAC3 = (int64_t)getL31() * VX + (int64_t)getL32() * VY;
	checkMAC(MAC3, 3);

	MAC3 += (int64_t)getL33() * VZ;
	checkMAC(MAC3, 3);

	MAC3 >>= sf;
	setIR3(saturateIR(MAC3, 3, lm));

	setMAC3((int32_t)MAC3);

	return ERR_OK;
}

int Cop2::applyColorMatrix(uint8_t sf) { // [IR1,IR2,IR3] = [MAC1,MAC2,MAC3] = (BK*1000h + LCM*IR) SAR (sf*12)
    int64_t MAC1 = 0;
    int64_t MAC2 = 0;
    int64_t MAC3 = 0;

    // IR values
	int64_t IR1 = (int64_t)getIR1();
    int64_t IR2 = (int64_t)getIR2();
    int64_t IR3 = (int64_t)getIR3();

	bool lm = operand->lm;

    // LCM * IR:
    // [[L11*IR1, L12*IR2, L13*IR3],
    // [L21*IR1, L22*IR2, L23*IR3],
    // [L31*IR1, L32*IR2, L33*IR3]]
    // Each IR (1 2 3) and MAC (1 2 3) is a line of this matrix

	// MAC1
	MAC1 = (int64_t)getRBK() * 0x1000 + (int64_t)getL11() * IR1; // Red
	checkMAC(MAC1, 1);

	MAC1 += (int64_t)getL12() * IR2;
	checkMAC(MAC1, 1);

	MAC1 += (int64_t)getL13() * IR3;
	checkMAC(MAC1, 1);
 
	MAC1 >>= sf;
	setIR1(saturateIR(MAC1, 1, lm));

	setMAC1((int32_t)MAC1);	

	// MAC2
	MAC2 = (int64_t)getGBK() * 0x1000 + (int64_t)getL21() * IR1; // Blue
	checkMAC(MAC2, 2);

	MAC2 += (int64_t)getL22() * IR2;
	checkMAC(MAC2, 2);

	MAC2 += (int64_t)getL23() * IR3;
	checkMAC(MAC2, 2);

	MAC2 >>= sf;
	setIR2(saturateIR(MAC2, 2, lm));

	setMAC2((int32_t)MAC2);

	// MAC3
	MAC3 = (int64_t)getBBK() * 0x1000 + (int64_t)getL31() * IR1; // Green
	checkMAC(MAC3, 3);

	MAC3 += (int64_t)getL32() * IR2;
	checkMAC(MAC3, 3);

	MAC3 += (int64_t)getL33() * IR3;
	checkMAC(MAC3, 3);

	MAC3 >>= sf;
	setIR3(saturateIR(MAC3, 3, lm));

	setMAC3((int32_t)MAC3);

	return ERR_OK;
}

int Cop2::modulateColor() { // [MAC1,MAC2,MAC3] = [R*IR1,G*IR2,B*IR3] SHL 4
    RGBColor *color = RGBColors[0]; // First color in the color FIFO

	// IR Values
    int64_t IR1 = (int64_t)getIR1();
    int64_t IR2 = (int64_t)getIR2();
    int64_t IR3 = (int64_t)getIR3();

    int64_t MAC1 = ((int64_t)color->r * IR1) << 4;
    checkMAC(MAC1, 1);

    int64_t MAC2 = ((int64_t)color->g * IR2) << 4;
    checkMAC(MAC2, 2);

    int64_t MAC3 = ((int64_t)color->b * IR3) << 4;
    checkMAC(MAC3, 3);

    setMAC1((int32_t)MAC1);
    setMAC2((int32_t)MAC2);
    setMAC3((int32_t)MAC3);

    return ERR_OK;
}

int Cop2::interpolateColor() { // [MAC1,MAC2,MAC3] = MAC+(FC-MAC)*IR0
    int64_t IR0 = (int64_t)getIR0();

    int64_t MAC1 = (int64_t)getMAC1();
    int64_t MAC2 = (int64_t)getMAC2();
    int64_t MAC3 = (int64_t)getMAC3();

    MAC1 += ((int64_t)getRFC() - MAC1) * IR0; // Maybe not 100% accurate due to the substraction (warning)
    checkMAC(MAC1, 1);
	setMAC1((int32_t)MAC1);

    MAC2 += ((int64_t)getGFC() - MAC2) * IR0;
    checkMAC(MAC2, 2);
	setMAC2((int32_t)MAC2);

    MAC3 += ((int64_t)getBFC() - MAC3) * IR0;
    checkMAC(MAC3, 3);
	setMAC3((int32_t)MAC3);

    return ERR_OK;
}

int Cop2::shiftMac(uint8_t sf) { // [MAC1,MAC2,MAC3] = [MAC1,MAC2,MAC3] SAR (sf*12)
    setMAC1(getMAC1() >> sf); // SAR 12 * sf
    setMAC2(getMAC2() >> sf);
    setMAC3(getMAC3() >> sf);

	return ERR_OK;
}

int Cop2::pushColorFifo() { // Color FIFO = [MAC1/16,MAC2/16,MAC3/16,CODE], [IR1,IR2,IR3] = [MAC1,MAC2,MAC3]
    int32_t MAC1 = getMAC1();
    int32_t MAC2 = getMAC2();
    int32_t MAC3 = getMAC3();

    writeRGBColors(MAC1 / 16, MAC2 / 16, MAC3 / 16, RGBColors[0]->code);

    setIR1(MAC1);
    setIR2(MAC2);
    setIR3(MAC3);

	return ERR_OK;
}

int Cop2::interpolateMac(uint8_t sf) { // [MAC1,MAC2,MAC3] = (([IR1,IR2,IR3] * IR0) + [MAC1,MAC2,MAC3]) SAR (sf*12)
    int64_t IR0 = (int64_t)getIR0();

    int64_t MAC1 = (int64_t)getIR1() * IR0 + (int64_t)getMAC1();
    checkMAC(MAC1, 1);

    int64_t MAC2 = (int64_t)getIR2() * IR0 + (int64_t)getMAC2();
    checkMAC(MAC2, 2);

    int64_t MAC3 = (int64_t)getIR3() * IR0 + (int64_t)getMAC3();
    checkMAC(MAC3, 3);

    MAC1 >>= sf;
    MAC2 >>= sf;
    MAC3 >>= sf;

    setMAC1((int32_t)MAC1);
    setMAC2((int32_t)MAC2);
    setMAC3((int32_t)MAC3);

    return ERR_OK;
}

// Calculation

int32_t Cop2::getValueTV(uint8_t index) {
	switch (operand->mvmva_tv) {
		case 0x00: {
			switch (index) {
				case 0x00: return getTRX();
				case 0x01: return getTRY();
				case 0x02: return getTRZ();
				default: return 0;
			}
		}

		case 0x01: {
			switch (index) {
				case 0x00: return getRBK();
                case 0x01: return getGBK();
                case 0x02: return getBBK();
                default: return 0;
			}
		}

		case 0x02: {
            switch (index) {
				case 0x00: return getRFC();
                case 0x01: return getGFC();
                case 0x02: return getBFC();
				default: return 0;
			}
		}

		default: return 0;
	}
}

int32_t Cop2::getValueMV(uint8_t index, uint8_t IR) {
    switch (operand->mvmva_mv) {
        case 0x00: {
            switch (index) {
                case 0x00: return getV0X();
                case 0x01: return getV0Y();
                case 0x02: return getV0Z();
                default: return 0;
            }
        }

        case 0x01: {
            switch (index) {
                case 0x00: return getV1X();
                case 0x01: return getV1Y();
                case 0x02: return getV1Z();
                default: return 0;
            }
        }

        case 0x02: {
            switch (index) {
                case 0x00: return getV2X();
                case 0x01: return getV2Y();
                case 0x02: return getV2Z();
                default: return 0;
            }
        }

        case 0x03: {
            switch (IR) {
                case 0x01: return getIR1();
                case 0x02: return getIR2();
                case 0x03: return getIR3();
                default: return 0;
            }
        }

        default: return 0;
    }
}

int32_t Cop2::getValueMM(uint8_t y, uint8_t x) {
    switch (operand->mvmva_mm) {
        case 0x00: { // RT
            switch (y) {
                case 0x01: {
					switch (x) {
						case 0x01: return getRT11();
                        case 0x02: return getRT12();
                        case 0x03: return getRT13();
						default: return 0;
					}
				}

                case 0x02: {
                    switch (x) {
                        case 0x01: return getRT21();
                        case 0x02: return getRT22();
                        case 0x03: return getRT23();
                        default: return 0;
                    }
                }

                case 0x03: {
                    switch (x) {
                        case 0x01: return getRT31();
                        case 0x02: return getRT32();
                        case 0x03: return getRT33();
                        default: return 0;
                    }
                }

                default: return 0;
            }
        }

        case 0x01: { // LLM
            switch (y) {
                case 0x01: {
                    switch (x) {
                        case 0x01: return getL11();
                        case 0x02: return getL12();
                        case 0x03: return getL13();
                        default: return 0;
                    }
                }

                case 0x02: {
                    switch (x) {
                        case 0x01: return getL21();
                        case 0x02: return getL22();
                        case 0x03: return getL23();
                        default: return 0;
                    }
                }

                case 0x03: {
                    switch (x) {
                        case 0x01: return getL31();
                        case 0x02: return getL32();
                        case 0x03: return getL33();
                        default: return 0;
                    }
                }

                default: return 0;
            }
        }

        case 0x02: { // LCM
            switch (y) {
                case 0x01: {
                    switch (x) {
                        case 0x01: return getLR1();
                        case 0x02: return getLR2();
                        case 0x03: return getLR3();
                        default: return 0;
                    }
                }

                case 0x02: {
                    switch (x) {
                        case 0x01: return getLG1();
                        case 0x02: return getLG2();
                        case 0x03: return getLG3();
                        default: return 0;
                    }
                }

                case 0x03: {
                    switch (x) {
                        case 0x01: return getLB1();
                        case 0x02: return getLB2();
                        case 0x03: return getLB3();
                        default: return 0;
                    }
                }

                default: return 0;
            }

        }

        case 0x03: { // Garbage matrix
            switch (y) {
                case 0x01: {
                    switch (x) {
                        case 0x01: return -(getRGBC() & 1) * 0x10;
                        case 0x02: return (getRGBC() & 1) * 0x10;
                        case 0x03: return getIR0();
                        default: return 0;
                    }
                }

                case 0x02: {
                    switch (x) {
                        case 0x01: return getRT13();
                        case 0x02: return getRT13();
                        case 0x03: return getRT13();
                        default: return 0;
                    }
                }

                case 0x03: {
                    switch (x) {
                        case 0x01: return getRT22();
                        case 0x02: return getRT22();
                        case 0x03: return getRT22();
                        default: return 0;
                    }
                }

                default: return 0;
            }

        }		

        default: return 0;
    }
}

