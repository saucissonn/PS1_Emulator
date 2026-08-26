#include "ps1/cpu/cop2.hpp"

#include "utils/error.hpp"

int Cop2::applyColorMatrix(uint8_t sf) { // [IR1,IR2,IR3] = [MAC1,MAC2,MAC3] = (BK*1000h + LCM*IR) SAR (sf*12)
    // IR values
	int32_t IR1 = (int32_t)getIR1();
    int32_t IR2 = (int32_t)getIR2();
    int32_t IR3 = (int32_t)getIR3();

    // LCM * IR:
    // [[L11*IR1, L12*IR2, L13*IR3],
    // [L21*IR1, L22*IR2, L23*IR3],
    // [L31*IR1, L32*IR2, L33*IR3]]
    // Each IR (1 2 3) is a line of this matrix
    // Normally MAC (1 2 3) also but it's useless in our case because we write over the value just after

    setIR1(
        (getRBK() * 0x1000 + // Red
        getL11() * IR1 +
        getL12() * IR2 +
        getL13() * IR3) >> sf
    );

    setIR2(
        (getGBK() * 0x1000 + // Green
        getL21() * IR1 +
        getL22() * IR2 +
        getL23() * IR3) >> sf
    );

    setIR3(
        (getBBK() * 0x1000 + // Blue
        getL31() * IR1 +
        getL32() * IR2 +
        getL33() * IR3) >> sf
    );

	return ERR_OK;
}

int Cop2::modulateColor() { // [MAC1,MAC2,MAC3] = [R*IR1,G*IR2,B*IR3] SHL 4
    RGBColor *color = RGBColors[0]; // First color in the color FIFO

    // IR values
    int32_t IR1 = (int32_t)getIR1();
    int32_t IR2 = (int32_t)getIR2();
    int32_t IR3 = (int32_t)getIR3();

    setMAC1((color->r * IR1) << 4); // SHL 4
    setMAC2((color->g * IR2) << 4);
    setMAC3((color->b * IR3) << 4);

	return ERR_OK;	
}

int Cop2::interpolateColor() { // [MAC1,MAC2,MAC3] = MAC+(FC-MAC)*IR0 
	int32_t IR0 = (int32_t)getIR0();
    int32_t MAC1 = getMAC1();
    int32_t MAC2 = getMAC2();
    int32_t MAC3 = getMAC3();

    setMAC1(MAC1 + (getRFC() - MAC1) * IR0);
    setMAC2(MAC2 + (getGFC() - MAC2) * IR0);
    setMAC3(MAC3 + (getBFC() - MAC3) * IR0);

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

int Cop2::interpolateMac(uint8_t sf) {
    int32_t IR0 = (int32_t)getIR0();

	setMAC1(((int32_t)getIR1() * IR0 + getMAC1()) >> sf); // SAR
	setMAC2(((int32_t)getIR2() * IR0 + getMAC2()) >> sf);
	setMAC3(((int32_t)getIR3() * IR0 + getMAC3()) >> sf);

	return ERR_OK;
}
