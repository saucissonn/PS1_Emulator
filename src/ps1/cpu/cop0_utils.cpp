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

void Cop0::setStatusRegisterIEc(uint8_t value) {
    GPR[12] &= ~(0b1); // Clear area
    GPR[12] |= (uint32_t)(value & 1);
}

void Cop0::setStatusRegisterKUc(uint8_t value) {
    GPR[12] &= ~(0b10); // Clear area
    GPR[12] |= (uint32_t)((value & 1) << 1);
}

void Cop0::setStatusRegisterIEp(uint8_t value){
    GPR[12] &= ~(0b100); // Clear area
    GPR[12] |= (uint32_t)((value & 1) << 2);
}

void Cop0::setStatusRegisterKUp(uint8_t value){
    GPR[12] &= ~(0b1000); // Clear area
    GPR[12] |= (uint32_t)((value & 1) << 3);
}

void Cop0::setStatusRegisterIEo(uint8_t value){
    GPR[12] &= ~(0b10000); // Clear area
    GPR[12] |= (uint32_t)((value & 1) << 4);
}

void Cop0::setStatusRegisterKUo(uint8_t value){
    GPR[12] &= ~(0b100000); // Clear area
    GPR[12] |= (uint32_t)((value & 1) << 5);

}
void Cop0::setStatusRegisterBEV(uint8_t value){
    GPR[12] &= ~(0b1 << 22); // Clear area
    GPR[12] |= (uint32_t)((value & 1) << 22);
}

void Cop0::setBadVaddr(uint32_t badVaddr){
    GPR[8] = badVaddr;
}


bool Cop0::getStatusRegisterIEc(){
    return GPR[12] & 1;
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

bool Cop0::getStatusRegisterIP2(){
    return (GPR[12] >> 10) & 1;
}

bool Cop0::getStatusRegisterBEV(){
    return (GPR[12] >> 22) & 1;
}
