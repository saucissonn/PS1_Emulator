#include "ps1/io/memory_control/memory_control3.hpp"

#include "utils/error.hpp"

void MemoryControl3::setScratchpadEnable1(uint8_t value){
    cacheControl &= ~(0b1 << 3); // Clear area
    cacheControl |= (uint32_t)((value & 1) << 3);
}

void MemoryControl3::setScratchpadEnable2(uint8_t value){
    cacheControl &= ~(0b1 << 7); // Clear area
    cacheControl |= (uint32_t)((value & 1) << 7);
}

void MemoryControl3::setCrash(uint8_t value){
    cacheControl &= ~(0b1 << 9); // Clear area
    cacheControl |= (uint32_t)((value & 1) << 9);
}

void MemoryControl3::setCodeCacheEnable(uint8_t value){
    cacheControl &= ~(0b1 << 11); // Clear area
    cacheControl |= (uint32_t)((value & 1) << 11);
}


bool MemoryControl3::getScratchpadEnable1(){
    return (cacheControl >> 3) & 1;
}

bool MemoryControl3::getScratchpadEnable2(){
    return (cacheControl >> 7) & 1;
}

bool MemoryControl3::getCrash(){
    return (cacheControl >> 9) & 1;
}

bool MemoryControl3::getCodeCacheEnable(){
    return (cacheControl >> 11) & 1;
}
