#include "ps1/cpu/cop2.hpp"

#include <stdio.h>

#include "ps1/cpu/cpu.hpp"
#include "utils/error.hpp"

void Cop2::transfromCommand(uint32_t command) {
    operand->opcode = command & 0x3F;				// bits 0-5
    operand->lm = (command >> 10) & 0x01;			// bit 10
    operand->mvmva_mv = (command >> 15) & 0x03;		// bits 15-16
    operand->mvmva_mm = (command >> 17) & 0x03;		// bits 17-18
    operand->sf = (command >> 19) & 0x01;			// bit 19
    operand->mvmva_tv = (command >> 13) & 0x03;		// bits 13-14
	operand->fakeOpcode = (command >> 20) & 0x1F;	// bits 20-24
}

// Commands (Sorted by real command)

int Cop2::NCLIP() { // Real command 0x06, fake command 0x14
	// Factorized with less operations so it's faster
	setMAC0(
		getSX0() * (getSY1() - getSY2()) +
		getSX1() * (getSY2() - getSY0()) +
		getSX2() * (getSY0() - getSY1())
	);

	printf("COP2 command NCLIP done\n");

	return ERR_OK;
}

int Cop2::OP() { // Real command 0x0C, fake command 0x17
    int64_t mac1 = (int64_t)getIR3() * getRT22() - (int64_t)getIR2() * getRT33();
    int64_t mac2 = (int64_t)getIR1() * getRT33() - (int64_t)getIR3() * getRT11();
    int64_t mac3 = (int64_t)getIR2() * getRT11() - (int64_t)getIR1() * getRT22();

    if (operand->sf) { // SAR
        mac1 >>= 12;
        mac2 >>= 12;
        mac3 >>= 12;
    }

    setMAC1(mac1);
    setMAC2(mac2);
    setMAC3(mac3);

    setIR1(mac1); // Just a copy
    setIR2(mac2);
    setIR3(mac3);

	printf("COP2 command OP done\n");

	return ERR_OK;
}

int Cop2::DPCS() { // Real command 0x10, fake command 0x07
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

    // Step 1
	RGBColor *color = RGBColors[0]; // First color in the color FIFO

    setMAC1((int32_t)(color->r) << 16); // SHL 16
    setMAC2((int32_t)(color->g) << 16);
    setMAC3((int32_t)(color->b) << 16);

    // Step 2
    interpolateColor();

    // Step 3
    shiftMac(sf);

    // Step 4
    pushColorFifo();

	printf("COP2 command DPCS done\n");

    return ERR_OK;
}

int Cop2::INTPL() { // Real command 0x11, fake command 0x09
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

    // Step 1
    // IR values
    int32_t IR1 = (int32_t)getIR1();
    int32_t IR2 = (int32_t)getIR2();
    int32_t IR3 = (int32_t)getIR3();

    setMAC1(IR1 << 12); // SHL 12
    setMAC2(IR2 << 12);
    setMAC3(IR3 << 12);

    // Step 2
    interpolateColor();

    // Step 3
    shiftMac(sf);

    // Step 4
    pushColorFifo();

    printf("COP2 command INTPL done\n");

    return ERR_OK;
}

int Cop2::NCDS() { // Real command 0x13, fake command 0x0E
    // Step 1 skipped (overwrite)
    // Step 2
    uint8_t sf = operand->sf * 12; // Already multiplied by 12
    applyColorMatrix(sf);

    //Step 3
    modulateColor();

    // Step 4
	shiftMac(sf);

    // Step 5
    pushColorFifo();
    printf("COP2 command NCDS done\n");

    return ERR_OK;
}

int Cop2::CDP() { // Real command 0x14, fake command 0x12
	// Step 1
    uint8_t sf = operand->sf * 12; // Already multiplied by 12
	applyColorMatrix(sf);

    // Step 2
	modulateColor();

    // Step 3
	interpolateColor();

	// Step 4
	shiftMac(sf);

	// Step 5
	pushColorFifo();

	printf("COP2 command CDP done\n");

    return ERR_OK;
}


int Cop2::NCDT() { // Real command 0x16, fake command 0x0F
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

    for (int i = 0; i < 3; i++) {
        // Step 1 skipped (overwrite)
        // Step 2
        applyColorMatrix(sf);

        //Step 3
        modulateColor();

		// Step 4
		interpolateColor();

        // Step 5
        shiftMac(sf);

        // Step 6
        pushColorFifo();
    }

    printf("COP2 command NCDT done\n");

    return ERR_OK;

}

int Cop2::NCCS() { // Real command 0x1B, fake command 0x10
    // Step 1 skipped (overwrite)
    // Step 2
    uint8_t sf = operand->sf * 12; // Already multiplied by 12
    applyColorMatrix(sf);

	//Step 3
	modulateColor();

	// Step 4
	interpolateColor();

	// Step 5
	shiftMac(sf);

    // Step 6
    pushColorFifo();
    printf("COP2 command NCCS done\n");

    return ERR_OK;
}

int Cop2::CC() { // Real command 0x1C, fake command 0x13
    // Step 1
    uint8_t sf = operand->sf * 12; // Already multiplied by 12
    applyColorMatrix(sf);

    // Step 2
    modulateColor();

    // Step 3
    shiftMac(sf);

    // Step 4
    pushColorFifo();
	printf("COP2 command CC done\n");

	return ERR_OK;
}

int Cop2::NCS() { // Real command 0x1E, fake command 0x0C
	// Step 1 skipped (overwrite)
	// Step 2
    uint8_t sf = operand->sf * 12; // Already multiplied by 12
    applyColorMatrix(sf);

	// Step 3
    pushColorFifo();

    printf("COP2 command NCS done\n");

    return ERR_OK;
}

int Cop2::NCT() { // Real command 0x20, fake command 0x0D
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

	for (int i = 0; i < 3; i++) {
		// Step 1 skipped (overwrite)
		// Step 2
	    applyColorMatrix(sf);

		// Step 3
        pushColorFifo();
    }

	printf("COP2 command NCT done\n");

    return ERR_OK;
}

int Cop2::SQR() { // Real command 0x28, fake command 0x0A
    int64_t mac1 = (int64_t)getIR1() * getIR1();
    int64_t mac2 = (int64_t)getIR2() * getIR2();
    int64_t mac3 = (int64_t)getIR3() * getIR3();

    if (operand->sf) { // SHR (but it's a squared value so it's the same as a SAR)
        mac1 >>= 12;
        mac2 >>= 12;
        mac3 >>= 12;
    }

    setMAC1(mac1);
    setMAC2(mac2);
    setMAC3(mac3);

    setIR1(std::min(mac1, (int64_t)0x7FFF)); // Saturation (mac is positive here so we just clip the max value)
    setIR2(std::min(mac2, (int64_t)0x7FFF));
    setIR3(std::min(mac3, (int64_t)0x7FFF));

	printf("COP2 command SQR done\n");

    return ERR_OK;
}

int Cop2::DCPL() { // Real command 0x29, fake command 0x06
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

	// Step 1
	modulateColor();

	// Step 2
	interpolateColor();

	// Step 3
	shiftMac(sf);

	// Step 4
	pushColorFifo();

	return ERR_OK;
}

int Cop2::DPCT() { // Real command 0x2A, fake command 0x08
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

    for (int i = 0; i < 3; i++) {
        // Step 1
        RGBColor *color = RGBColors[0]; // First color in the color FIFO

        setMAC1((int32_t)(color->r) << 16); // SHL 16
        setMAC2((int32_t)(color->g) << 16);
        setMAC3((int32_t)(color->b) << 16);

        // Step 2
        interpolateColor();

        // Step 3
        shiftMac(sf);

        // Step 4
        pushColorFifo();
    }

    printf("COP2 command DPCT done\n");

    return ERR_OK;
}

int Cop2::GPF() { // Real command 0x3D, fake command 0x19
    uint8_t sf = operand->sf * 12; // Already multiplied by 12
	
	// Step 1
	setMAC1(0);
    setMAC2(0);
	setMAC3(0);

	// Step 2
	interpolateMac(sf);

	// Step 3
	pushColorFifo();

	printf("COP2 command GPF done\n");

	return ERR_OK;
}

int Cop2::GPL() { // Real command 0x3E, fake command 0x1A
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

    // Step 1
    setMAC1(getMAC1() << sf);
    setMAC2(getMAC2() << sf);
    setMAC3(getMAC3() << sf);

    // Step 2
    interpolateMac(sf);

    // Step 3
    pushColorFifo();

    printf("COP2 command GPL done\n");

    return ERR_OK;
}


int Cop2::NCCT() { // Real command 0x3F, fake command 0x11
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

    for (int i = 0; i < 3; i++) {
        // Step 1 skipped (overwrite)
        // Step 2
        applyColorMatrix(sf);

        //Step 3
        modulateColor();

        // Step 4
        shiftMac(sf);

        // Step 5
        pushColorFifo();
    }

    printf("COP2 command NCCT done\n");

    return ERR_OK;
}

int Cop2::decodeCommand(uint32_t command) { // From a command find and execute it among command functions
    printf("\nPC: %08X\n", cpu->getInstructionPC());
    printf("Command: %08X\n", command);

    transfromCommand(command);

    printf("Opcode: %02X\n", operand->opcode);
    // printf("Fake Opcode: %02X\n", operand->fakeOpcode);

    switch (operand->opcode) {
        case 0x01: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x06: return NCLIP();
        case 0x0C: return OP();
        case 0x10: return DPCS();
        case 0x11: return INTPL();
        case 0x12: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x13: return NCDS();
        case 0x14: return CDP();
        case 0x16: return NCDT();
        case 0x1B: return NCCS();
        case 0x1C: return CC();
        case 0x1E: return NCS();
        case 0x20: return NCT();
        case 0x28: return SQR();
        case 0x29: return DCPL();
        case 0x2A: return DPCT();
        case 0x2D: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x2E: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x30: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x3D: return GPF();
        case 0x3E: return GPL();
        case 0x3F: return NCCT();
    }

    return ERR_COP2_COMMAND_NOT_FOUND;
}
