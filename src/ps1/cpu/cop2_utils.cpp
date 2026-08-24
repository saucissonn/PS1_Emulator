#include "ps1/cpu/cop2.hpp"

#include <stdio.h>

#include "utils/error.hpp"

void Cop2::setV0X(int16_t value) {
    GPR[0] = (GPR[0] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setV0Y(int16_t value) {
    GPR[0] = (GPR[0] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setV0Z(int16_t value) {
    GPR[1] = (GPR[1] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setV1X(int16_t value) {
    GPR[2] = (GPR[2] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setV1Y(int16_t value) {
    GPR[2] = (GPR[2] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setV1Z(int16_t value) {
    GPR[3] = (GPR[3] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setV2X(int16_t value) {
    GPR[4] = (GPR[4] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setV2Y(int16_t value) {
    GPR[4] = (GPR[4] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setV2Z(int16_t value) {
    GPR[5] = (GPR[5] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setRGBC(uint32_t value) {
    GPR[6] = value & 0xFFFFFFFF;
}

void Cop2::setOTZ(uint16_t value) {
    GPR[7] = value;
}

void Cop2::setIR0(int16_t value) {
    GPR[8] = (GPR[8] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setIR1(int16_t value) {
    GPR[9] = (GPR[9] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setIR2(int16_t value) {
    GPR[10] = (GPR[10] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setIR3(int16_t value) {
    GPR[11] = (GPR[11] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setSXY0(uint32_t value) {
    GPR[12] = value;
}

void Cop2::setSXY1(uint32_t value) {
    GPR[13] = value;
}

void Cop2::setSXY2(uint32_t value) {
    GPR[14] = value;
}

void Cop2::setSXYP(uint32_t value) {
    GPR[15] = value;
}

void Cop2::setSX0(int16_t value) {
    GPR[12] = (GPR[12] & 0xFFFF0000) | ((uint16_t)value);
}

void Cop2::setSX1(int16_t value) {
    GPR[13] = (GPR[13] & 0xFFFF0000) | ((uint16_t)value);
}

void Cop2::setSX2(int16_t value) {
    GPR[14] = (GPR[14] & 0xFFFF0000) | ((uint16_t)value);
}

void Cop2::setSXP(int16_t value) {
    GPR[15] = (GPR[15] & 0xFFFF0000) | ((uint16_t)value);
}

void Cop2::setSY0(int16_t value) {
    GPR[12] = (GPR[12] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setSY1(int16_t value) {
    GPR[13] = (GPR[13] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setSY2(int16_t value) {
    GPR[14] = (GPR[14] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setSYP(int16_t value) {
    GPR[15] = (GPR[15] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setSZ0(uint16_t value) {
    GPR[16] = value;
}

void Cop2::setSZ1(uint16_t value) {
    GPR[17] = value;
}

void Cop2::setSZ2(uint16_t value) {
    GPR[18] = value;
}

void Cop2::setSZ3(uint16_t value) {
    GPR[19] = value;
}

void Cop2::setRGB0(uint32_t value) {
    GPR[20] = value;
}

void Cop2::setRGB1(uint32_t value) {
    GPR[21] = value;
}

void Cop2::setRGB2(uint32_t value) {
    GPR[22] = value;
}

void Cop2::setMAC0(int32_t value) {
    GPR[24] = (uint32_t)value;
}

void Cop2::setMAC1(int32_t value) {
    GPR[25] = (uint32_t)value;
}

void Cop2::setMAC2(int32_t value) {
    GPR[26] = (uint32_t)value;
}

void Cop2::setMAC3(int32_t value) {
    GPR[27] = (uint32_t)value;
}

void Cop2::setIRGB(uint16_t value) {
    GPR[28] = value & 0x7FFF;
}

void Cop2::setORGB(uint16_t value) {
    GPR[29] = value & 0x7FFF;
}

void Cop2::setLZCS(int32_t value) {
    GPR[30] = (uint32_t)value;
}

void Cop2::setLZCR(int32_t value) {
    GPR[31] = (uint32_t)value;
}

int16_t Cop2::getV0X() {
    return (int16_t)(GPR[0] & 0xFFFF);
}

int16_t Cop2::getV0Y() {
    return (int16_t)((GPR[0] >> 16) & 0xFFFF);
}

int16_t Cop2::getV0Z() {
    return (int16_t)(GPR[1] & 0xFFFF);
}

int16_t Cop2::getV1X() {
    return (int16_t)(GPR[2] & 0xFFFF);
}

int16_t Cop2::getV1Y() {
    return (int16_t)((GPR[2] >> 16) & 0xFFFF);
}

int16_t Cop2::getV1Z() {
    return (int16_t)(GPR[3] & 0xFFFF);
}

int16_t Cop2::getV2X() {
    return (int16_t)(GPR[4] & 0xFFFF);
}

int16_t Cop2::getV2Y() {
    return (int16_t)((GPR[4] >> 16) & 0xFFFF);
}

int16_t Cop2::getV2Z() {
    return (int16_t)(GPR[5] & 0xFFFF);
}

uint32_t Cop2::getRGBC() {
    return GPR[6];
}

uint16_t Cop2::getOTZ() {
    return GPR[7] & 0xFFFF;
}

int16_t Cop2::getIR0() {
    return (int16_t)(GPR[8] & 0xFFFF);
}

int16_t Cop2::getIR1() {
    return (int16_t)(GPR[9] & 0xFFFF);
}

int16_t Cop2::getIR2() {
    return (int16_t)(GPR[10] & 0xFFFF);
}

int16_t Cop2::getIR3() {
    return (int16_t)(GPR[11] & 0xFFFF);
}

uint32_t Cop2::getSXY0() {
    return GPR[12];
}

uint32_t Cop2::getSXY1() {
    return GPR[13];
}

uint32_t Cop2::getSXY2() {
    return GPR[14];
}

uint32_t Cop2::getSXYP() {
    return GPR[15];
}

int16_t Cop2::getSX0() {
    return (int16_t)(GPR[12] & 0xFFFF);
}

int16_t Cop2::getSX1() {
    return (int16_t)(GPR[13] & 0xFFFF);
}

int16_t Cop2::getSX2() {
    return (int16_t)(GPR[14] & 0xFFFF);
}

int16_t Cop2::getSXP() {
    return (int16_t)(GPR[15] & 0xFFFF);
}

int16_t Cop2::getSY0() {
    return (int16_t)((GPR[12] >> 16) & 0xFFFF);
}

int16_t Cop2::getSY1() {
    return (int16_t)((GPR[13] >> 16) & 0xFFFF);
}

int16_t Cop2::getSY2() {
    return (int16_t)((GPR[14] >> 16) & 0xFFFF);
}

int16_t Cop2::getSYP() {
    return (int16_t)((GPR[15] >> 16) & 0xFFFF);
}

uint16_t Cop2::getSZ0() {
    return GPR[16] & 0xFFFF;
}

uint16_t Cop2::getSZ1() {
    return GPR[17] & 0xFFFF;
}

uint16_t Cop2::getSZ2() {
    return GPR[18] & 0xFFFF;
}

uint16_t Cop2::getSZ3() {
    return GPR[19] & 0xFFFF;
}

uint32_t Cop2::getRGB0() {
    return GPR[20];
}

uint32_t Cop2::getRGB1() {
    return GPR[21];
}

uint32_t Cop2::getRGB2() {
    return GPR[22];
}

int32_t Cop2::getMAC0() {
    return (int32_t)GPR[24];
}

int32_t Cop2::getMAC1() {
    return (int32_t)GPR[25];
}

int32_t Cop2::getMAC2() {
    return (int32_t)GPR[26];
}

int32_t Cop2::getMAC3() {
    return (int32_t)GPR[27];
}

uint16_t Cop2::getIRGB() {
    return GPR[28] & 0x7FFF;
}

uint16_t Cop2::getORGB() {
    return GPR[29] & 0x7FFF;
}

int32_t Cop2::getLZCS() {
    return (int32_t)GPR[30];
}

int32_t Cop2::getLZCR() {
    return (int32_t)GPR[31];
}


void Cop2::setRT11(int16_t value) {
    GPR[32] = (GPR[32] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setRT12(int16_t value) {
    GPR[32] = (GPR[32] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setRT13(int16_t value) {
    GPR[33] = (GPR[33] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setRT21(int16_t value) {
    GPR[33] = (GPR[33] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setRT22(int16_t value) {
    GPR[34] = (GPR[34] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setRT23(int16_t value) {
    GPR[34] = (GPR[34] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setRT31(int16_t value) {
    GPR[35] = (GPR[35] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setRT32(int16_t value) {
    GPR[35] = (GPR[35] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setRT33(int16_t value) {
    GPR[36] = (GPR[36] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setTRX(int32_t value) {
    GPR[37] = (uint32_t)value;
}

void Cop2::setTRY(int32_t value) {
    GPR[38] = (uint32_t)value;
}

void Cop2::setTRZ(int32_t value) {
    GPR[39] = (uint32_t)value;
}

void Cop2::setL11(int16_t value) {
    GPR[40] = (GPR[40] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setL12(int16_t value) {
    GPR[40] = (GPR[40] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setL13(int16_t value) {
    GPR[41] = (GPR[41] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setL21(int16_t value) {
    GPR[41] = (GPR[41] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setL22(int16_t value) {
    GPR[42] = (GPR[42] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setL23(int16_t value) {
    GPR[42] = (GPR[42] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setL31(int16_t value) {
    GPR[43] = (GPR[43] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setL32(int16_t value) {
    GPR[43] = (GPR[43] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setL33(int16_t value) {
    GPR[44] = (GPR[44] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setRBK(int32_t value) {
    GPR[45] = (uint32_t)value;
}

void Cop2::setGBK(int32_t value) {
    GPR[46] = (uint32_t)value;
}

void Cop2::setBBK(int32_t value) {
    GPR[47] = (uint32_t)value;
}

void Cop2::setLR1(int16_t value) {
    GPR[48] = (GPR[48] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setLR2(int16_t value) {
    GPR[48] = (GPR[48] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setLR3(int16_t value) {
    GPR[49] = (GPR[49] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setLG1(int16_t value) {
    GPR[49] = (GPR[49] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setLG2(int16_t value) {
    GPR[50] = (GPR[50] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setLG3(int16_t value) {
    GPR[50] = (GPR[50] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setLB1(int16_t value) {
    GPR[51] = (GPR[51] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setLB2(int16_t value) {
    GPR[51] = (GPR[51] & 0x0000FFFF) | ((uint32_t)(uint16_t)value << 16);
}

void Cop2::setLB3(int16_t value) {
    GPR[52] = (GPR[52] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setRFC(int32_t value) {
    GPR[53] = (uint32_t)value;
}

void Cop2::setGFC(int32_t value) {
    GPR[54] = (uint32_t)value;
}

void Cop2::setBFC(int32_t value) {
    GPR[55] = (uint32_t)value;
}

void Cop2::setOFX(int32_t value) {
    GPR[56] = (uint32_t)value;
}

void Cop2::setOFY(int32_t value) {
    GPR[57] = (uint32_t)value;
}

void Cop2::setH(uint16_t value) {
    GPR[58] = (GPR[58] & 0xFFFF0000) | value;
}

void Cop2::setDQA(int16_t value) {
    GPR[59] = (GPR[59] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setDQB(int32_t value) {
    GPR[60] = (uint32_t)value;
}

void Cop2::setZSF3(int16_t value) {
    GPR[61] = (GPR[61] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setZSF4(int16_t value) {
    GPR[62] = (GPR[62] & 0xFFFF0000) | (uint16_t)value;
}

void Cop2::setFLAG(uint32_t value) {
    GPR[63] = value;
}

int16_t Cop2::getRT11() {
    return (int16_t)(GPR[32] & 0xFFFF);
}

int16_t Cop2::getRT12() {
    return (int16_t)((GPR[32] >> 16) & 0xFFFF);
}

int16_t Cop2::getRT13() {
    return (int16_t)(GPR[33] & 0xFFFF);
}

int16_t Cop2::getRT21() {
    return (int16_t)((GPR[33] >> 16) & 0xFFFF);
}

int16_t Cop2::getRT22() {
    return (int16_t)(GPR[34] & 0xFFFF);
}

int16_t Cop2::getRT23() {
    return (int16_t)((GPR[34] >> 16) & 0xFFFF);
}

int16_t Cop2::getRT31() {
    return (int16_t)(GPR[35] & 0xFFFF);
}

int16_t Cop2::getRT32() {
    return (int16_t)((GPR[35] >> 16) & 0xFFFF);
}

int16_t Cop2::getRT33() {
    return (int16_t)(GPR[36] & 0xFFFF);
}

int32_t Cop2::getTRX() {
    return (int32_t)GPR[37];
}

int32_t Cop2::getTRY() {
    return (int32_t)GPR[38];
}

int32_t Cop2::getTRZ() {
    return (int32_t)GPR[39];
}

int16_t Cop2::getL11() {
    return (int16_t)(GPR[40] & 0xFFFF);
}

int16_t Cop2::getL12() {
    return (int16_t)((GPR[40] >> 16) & 0xFFFF);
}

int16_t Cop2::getL13() {
    return (int16_t)(GPR[41] & 0xFFFF);
}

int16_t Cop2::getL21() {
    return (int16_t)((GPR[41] >> 16) & 0xFFFF);
}

int16_t Cop2::getL22() {
    return (int16_t)(GPR[42] & 0xFFFF);
}

int16_t Cop2::getL23() {
    return (int16_t)((GPR[42] >> 16) & 0xFFFF);
}

int16_t Cop2::getL31() {
    return (int16_t)(GPR[43] & 0xFFFF);
}

int16_t Cop2::getL32() {
    return (int16_t)((GPR[43] >> 16) & 0xFFFF);
}

int16_t Cop2::getL33() {
    return (int16_t)(GPR[44] & 0xFFFF);
}

int32_t Cop2::getRBK() {
    return (int32_t)GPR[45];
}

int32_t Cop2::getGBK() {
    return (int32_t)GPR[46];
}

int32_t Cop2::getBBK() {
    return (int32_t)GPR[47];
}

int16_t Cop2::getLR1() {
    return (int16_t)(GPR[48] & 0xFFFF);
}

int16_t Cop2::getLR2() {
    return (int16_t)((GPR[48] >> 16) & 0xFFFF);
}

int16_t Cop2::getLR3() {
    return (int16_t)(GPR[49] & 0xFFFF);
}

int16_t Cop2::getLG1() {
    return (int16_t)((GPR[49] >> 16) & 0xFFFF);
}

int16_t Cop2::getLG2() {
    return (int16_t)(GPR[50] & 0xFFFF);
}

int16_t Cop2::getLG3() {
    return (int16_t)((GPR[50] >> 16) & 0xFFFF);
}

int16_t Cop2::getLB1() {
    return (int16_t)(GPR[51] & 0xFFFF);
}

int16_t Cop2::getLB2() {
    return (int16_t)((GPR[51] >> 16) & 0xFFFF);
}

int16_t Cop2::getLB3() {
    return (int16_t)(GPR[52] & 0xFFFF);
}

int32_t Cop2::getRFC() {
    return (int32_t)GPR[53];
}

int32_t Cop2::getGFC() {
    return (int32_t)GPR[54];
}

int32_t Cop2::getBFC() {
    return (int32_t)GPR[55];
}

int32_t Cop2::getOFX() {
    return (int32_t)GPR[56];
}

int32_t Cop2::getOFY() {
    return (int32_t)GPR[57];
}

uint16_t Cop2::getH() {
    return (uint16_t)(GPR[58] & 0xFFFF);
}

int16_t Cop2::getDQA() {
    return (int16_t)(GPR[59] & 0xFFFF);
}

int32_t Cop2::getDQB() {
    return (int32_t)GPR[60];
}

int16_t Cop2::getZSF3() {
    return (int16_t)(GPR[61] & 0xFFFF);
}

int16_t Cop2::getZSF4() {
    return (int16_t)(GPR[62] & 0xFFFF);
}

uint32_t Cop2::getFLAG() {
    return GPR[63];
}
