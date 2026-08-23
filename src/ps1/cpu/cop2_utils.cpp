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
