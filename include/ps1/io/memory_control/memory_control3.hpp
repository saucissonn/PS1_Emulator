#pragma once

#include <cstdint>

class MemoryControl3 {
    public:
        MemoryControl3();
        ~MemoryControl3();

        uint32_t read(uint32_t address);
        int write(uint32_t address, uint32_t value);

		// Utils

		void setScratchpadEnable1(uint8_t value); // RAM
		void setScratchpadEnable2(uint8_t value); // DS
		void setCrash(uint8_t value);
		void setCodeCacheEnable(uint8_t value);

		bool getScratchpadEnable1();
		bool getScratchpadEnable2();
		bool getCrash();
		bool getCodeCacheEnable();

    private:
        uint32_t cacheControl;
};
