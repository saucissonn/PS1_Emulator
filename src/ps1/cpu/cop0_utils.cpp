#include "ps1/cpu/cop0.hpp"

void Cop0::setCauseRegister(uint32_t value) {
    GPR[13] = value;
}

void Cop0::setCauseRegisterExCode(uint8_t value) {
    GPR[13] &= ~(0b1111100); // Clear area
    GPR[13] |= (uint32_t)((value& 0x1F) << 2);
}

void Cop0::setCauseRegisterIP2(bool value) {
    GPR[13] &= ~(1u << 10); // Clear area
    GPR[13] |= (uint32_t)value << 10;
}

void Cop0::setCauseRegisterBD(uint8_t value) {
    GPR[13] &= ~(0b1 << 31); // Clear area
    GPR[13] |= (uint32_t)((value & 1) << 31);
}

void Cop0::setEPCRegister(uint32_t value) {
    GPR[14] = value;
}

void Cop0::setBadVaddr(uint32_t badVaddr){
    GPR[8] = badVaddr;
}

// COP0r12 - SR - System Status Register

void Cop0::setStatusRegisterIEc(uint8_t value){
    GPR[12] &= ~(0b1 << 0);
    GPR[12] |= (uint32_t)((value & 1) << 0);
}

void Cop0::setStatusRegisterKUc(uint8_t value){
    GPR[12] &= ~(0b1 << 1);
    GPR[12] |= (uint32_t)((value & 1) << 1);
}

void Cop0::setStatusRegisterIEp(uint8_t value){
    GPR[12] &= ~(0b1 << 2);
    GPR[12] |= (uint32_t)((value & 1) << 2);
}

void Cop0::setStatusRegisterKUp(uint8_t value){
    GPR[12] &= ~(0b1 << 3);
    GPR[12] |= (uint32_t)((value & 1) << 3);
}

void Cop0::setStatusRegisterIEo(uint8_t value){
    GPR[12] &= ~(0b1 << 4);
    GPR[12] |= (uint32_t)((value & 1) << 4);
}

void Cop0::setStatusRegisterKUo(uint8_t value){
    GPR[12] &= ~(0b1 << 5);
    GPR[12] |= (uint32_t)((value & 1) << 5);
}

void Cop0::setStatusRegisterIm(uint8_t value){
    GPR[12] &= ~(0xFF << 8);
    GPR[12] |= (uint32_t)((value & 0xFF) << 8);
}

void Cop0::setStatusRegisterIsc(uint8_t value){
    GPR[12] &= ~(0b1 << 16);
    GPR[12] |= (uint32_t)((value & 1) << 16);
}

void Cop0::setStatusRegisterSwc(uint8_t value){
    GPR[12] &= ~(0b1 << 17);
    GPR[12] |= (uint32_t)((value & 1) << 17);
}

void Cop0::setStatusRegisterPZ(uint8_t value){
    GPR[12] &= ~(0b1 << 18);
    GPR[12] |= (uint32_t)((value & 1) << 18);
}

void Cop0::setStatusRegisterCM(uint8_t value){
    GPR[12] &= ~(0b1 << 19);
    GPR[12] |= (uint32_t)((value & 1) << 19);
}

void Cop0::setStatusRegisterPE(uint8_t value){
    GPR[12] &= ~(0b1 << 20);
    GPR[12] |= (uint32_t)((value & 1) << 20);
}

void Cop0::setStatusRegisterTS(uint8_t value){
    GPR[12] &= ~(0b1 << 21);
    GPR[12] |= (uint32_t)((value & 1) << 21);
}

void Cop0::setStatusRegisterBEV(uint8_t value){
    GPR[12] &= ~(0b1 << 22);
    GPR[12] |= (uint32_t)((value & 1) << 22);
}

void Cop0::setStatusRegisterRE(uint8_t value){
    GPR[12] &= ~(0b1 << 25);
    GPR[12] |= (uint32_t)((value & 1) << 25);
}

void Cop0::setStatusRegisterCU0(uint8_t value){
    GPR[12] &= ~(0b1 << 28);
    GPR[12] |= (uint32_t)((value & 1) << 28);
}

void Cop0::setStatusRegisterCU1(uint8_t value){
    GPR[12] &= ~(0b1 << 29);
    GPR[12] |= (uint32_t)((value & 1) << 29);
}

void Cop0::setStatusRegisterCU2(uint8_t value){
    GPR[12] &= ~(0b1 << 30);
    GPR[12] |= (uint32_t)((value & 1) << 30);
}

void Cop0::setStatusRegisterCU3(uint8_t value){
    GPR[12] &= ~(0b1 << 31);
    GPR[12] |= (uint32_t)((value & 1) << 31);
}


bool Cop0::getStatusRegisterIEc(){
    return (GPR[12] >> 0) & 1;
}

bool Cop0::getStatusRegisterKUc(){
    return (GPR[12] >> 1) & 1;
}

bool Cop0::getStatusRegisterIEp(){
    return (GPR[12] >> 2) & 1;
}

bool Cop0::getStatusRegisterKUp(){
    return (GPR[12] >> 3) & 1;
}

bool Cop0::getStatusRegisterIEo(){
    return (GPR[12] >> 4) & 1;
}

bool Cop0::getStatusRegisterKUo(){
    return (GPR[12] >> 5) & 1;
}

uint8_t Cop0::getStatusRegisterIm(){
    return (GPR[12] >> 8) & 0xFF;
}

bool Cop0::getStatusRegisterIP2(){
    return (GPR[12] >> 10) & 1;
}

bool Cop0::getStatusRegisterIsc(){
    return (GPR[12] >> 16) & 1;
}

bool Cop0::getStatusRegisterSwc(){
    return (GPR[12] >> 17) & 1;
}

bool Cop0::getStatusRegisterPZ(){
    return (GPR[12] >> 18) & 1;
}

bool Cop0::getStatusRegisterCM(){
    return (GPR[12] >> 19) & 1;
}

bool Cop0::getStatusRegisterPE(){
    return (GPR[12] >> 20) & 1;
}

bool Cop0::getStatusRegisterTS(){
    return (GPR[12] >> 21) & 1;
}

bool Cop0::getStatusRegisterBEV(){
    return (GPR[12] >> 22) & 1;
}

bool Cop0::getStatusRegisterRE(){
    return (GPR[12] >> 25) & 1;
}

bool Cop0::getStatusRegisterCU0(){
    return (GPR[12] >> 28) & 1;
}

bool Cop0::getStatusRegisterCU1(){
    return (GPR[12] >> 29) & 1;
}

bool Cop0::getStatusRegisterCU2(){
    return (GPR[12] >> 30) & 1;
}

bool Cop0::getStatusRegisterCU3(){
    return (GPR[12] >> 31) & 1;
}
