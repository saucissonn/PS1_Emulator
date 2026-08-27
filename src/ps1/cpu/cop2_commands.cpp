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

int Cop2::RTPS() { // Real command 0x01, fake command 0x01
	// Step 1
//	int64_t V0X = (int64_t)getV0X();
//	int64_t V1X = (int64_t)getV1X();
//	int64_t V2X = (int64_t)getV2X();

    printf("COP2 command RTPS done\n");

    return ERR_OK;
}

int Cop2::NCLIP() { // Real command 0x06, fake command 0x14
	// Factorized with less operations so it's faster
	int64_t MAC0 =
		(int64_t)getSX0() * (getSY1() - getSY2()) +
		(int64_t)getSX1() * (getSY2() - getSY0()) +
		(int64_t)getSX2() * (getSY0() - getSY1());

	checkMAC0(MAC0);

	setMAC0((int32_t)MAC0);

	printf("COP2 command NCLIP done\n");

	return ERR_OK;
}

int Cop2::OP() { // Real command 0x0C, fake command 0x17
    int64_t MAC1 = (int64_t)getIR3() * getRT22() - (int64_t)getIR2() * getRT33();
    checkMAC(MAC1, 1);

    int64_t MAC2 = (int64_t)getIR1() * getRT33() - (int64_t)getIR3() * getRT11();
    checkMAC(MAC2, 2);

    int64_t MAC3 = (int64_t)getIR2() * getRT11() - (int64_t)getIR1() * getRT22();
    checkMAC(MAC3, 3);

    if (operand->sf) { // SAR
        MAC1 >>= 12;
        MAC2 >>= 12;
        MAC3 >>= 12;
    }

    setIR1(saturateIR(MAC1, 1, operand->lm));
    setIR2(saturateIR(MAC2, 2, operand->lm));
    setIR3(saturateIR(MAC3, 3, operand->lm));

    setMAC1((int32_t)MAC1);
    setMAC2((int32_t)MAC2);
    setMAC3((int32_t)MAC3);

    printf("COP2 command OP done\n");

    return ERR_OK;
}

int Cop2::DPCS() { // Real command 0x10, fake command 0x07
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

    // Step 1
	RGBColor *color = RGBColors[0]; // First color in the color FIFO

    int64_t MAC1 = (int64_t)color->r << 16;
    checkMAC(MAC1, 1);
	setMAC1((int32_t)MAC1);

    int64_t MAC2 = (int64_t)color->g << 16;
    checkMAC(MAC2, 2);
	setMAC2((int32_t)MAC2);

    int64_t MAC3 = (int64_t)color->b << 16;
    checkMAC(MAC3, 3);
	setMAC3((int32_t)MAC3);

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
    int64_t IR1 = (int64_t)getIR1();
    int64_t IR2 = (int64_t)getIR2();
    int64_t IR3 = (int64_t)getIR3();

    int64_t MAC1 = IR1 << 12;
    checkMAC(MAC1, 1);
	setMAC1((int32_t)MAC1);

    int64_t MAC2 = IR2 << 12;
    checkMAC(MAC2, 2);
	setMAC2((int32_t)MAC2);

    int64_t MAC3 = IR3 << 12;
    checkMAC(MAC3, 3);
	setMAC3((int32_t)MAC3);

    // Step 2
    interpolateColor();

    // Step 3
    shiftMac(sf);

    // Step 4
    pushColorFifo();

    printf("COP2 command INTPL done\n");

    return ERR_OK;
}

int Cop2::MVMVA() { // Real command 0x12, fake command 0x04
    uint8_t sf = operand->sf * 12; // Already multiplied by 12
	int64_t MAC1 = 0;
    int64_t MAC2 = 0;
    int64_t MAC3 = 0;
	bool lm = operand->lm;

    // Step 1
	if (operand->mvmva_mv == 2) { // With FC we compute MACs in 2 parts (so we saturate twice the IRs)
		// MAC1 Part 1
		MAC1 = (int64_t)getValueTV(1) * 0x1000 + (int64_t)getValueMM(1, 1) * getValueMV(1, 1);
		checkMAC(MAC1, 1);

		MAC1 >>= sf;
		setIR1(saturateIR(MAC1, 1, false));			

		// Part 2
		MAC1 = (int64_t)getValueMM(1, 2) * getValueMV(2, 1);
		checkMAC(MAC1, 1);

		MAC1 += (int64_t)getValueMM(1, 3) * getValueMV(3, 1);
		checkMAC(MAC1, 1);

		MAC1 >>= sf;
		setIR1(saturateIR(MAC1, 1, lm));

		setMAC1((int32_t)MAC1);

		// MAC2 Part 1
		MAC2 = (int64_t)getValueTV(2) * 0x1000 + (int64_t)getValueMM(2, 1) * getValueMV(1, 2);
		checkMAC(MAC2, 2);
		
		MAC2 >>= sf;
		setIR2(saturateIR(MAC2, 2, false));
		
		// Part 2
		MAC2 = (int64_t)getValueMM(2, 2) * getValueMV(2, 2);
		checkMAC(MAC2, 2);
		
		MAC2 += (int64_t)getValueMM(2, 3) * getValueMV(3, 2);
		checkMAC(MAC2, 2);
		
		MAC2 >>= sf;
		setIR2(saturateIR(MAC2, 2, lm));
		
		setMAC2((int32_t)MAC2);
		
		// MAC3 Part 1
		MAC3 = (int64_t)getValueTV(3) * 0x1000 + (int64_t)getValueMM(3, 1) * getValueMV(1, 3);
		checkMAC(MAC3, 3);
		
		MAC3 >>= sf;
		setIR3(saturateIR(MAC3, 3, false));
		
		// Part 2
		MAC3 = (int64_t)getValueMM(3, 2) * getValueMV(2, 3);
		checkMAC(MAC3, 3);
		
		MAC3 += (int64_t)getValueMM(3, 3) * getValueMV(3, 3);
		checkMAC(MAC3, 3);
		
		MAC3 >>= sf;
		setIR3(saturateIR(MAC3, 3, lm));
		
		setMAC3((int32_t)MAC3);
	}
	else {
        // MAC1
        MAC1 = (int64_t)getValueTV(1) * 0x1000 + (int64_t)getValueMM(1, 1) * getValueMV(1, 1);
        checkMAC(MAC1, 1);

        MAC1 += (int64_t)getValueMM(1, 2) * getValueMV(2, 1);
        checkMAC(MAC1, 1);

        MAC1 += (int64_t)getValueMM(1, 3) * getValueMV(3, 1);
        checkMAC(MAC1, 1);

        MAC1 >>= sf;
        setIR1(saturateIR(MAC1, 1, lm));

        setMAC1((int32_t)MAC1);

		// MAC2
		MAC2 = (int64_t)getValueTV(2) * 0x1000 + (int64_t)getValueMM(2, 1) * getValueMV(1, 2);
		checkMAC(MAC2, 2);
		
		MAC2 += (int64_t)getValueMM(2, 2) * getValueMV(2, 2);
		checkMAC(MAC2, 2);
		
		MAC2 += (int64_t)getValueMM(2, 3) * getValueMV(3, 2);
		checkMAC(MAC2, 2);
		
		MAC2 >>= sf;
		setIR2(saturateIR(MAC2, 2, lm));
		
		setMAC2((int32_t)MAC2);
		
		// MAC3
		MAC3 = (int64_t)getValueTV(3) * 0x1000 + (int64_t)getValueMM(3, 1) * getValueMV(1, 3);
		checkMAC(MAC3, 3);
		
		MAC3 += (int64_t)getValueMM(3, 2) * getValueMV(2, 3);
		checkMAC(MAC3, 3);
		
		MAC3 += (int64_t)getValueMM(3, 3) * getValueMV(3, 3);
		checkMAC(MAC3, 3);
		
		MAC3 >>= sf;
		setIR3(saturateIR(MAC3, 3, lm));
		
		setMAC3((int32_t)MAC3);
	}

    printf("COP2 command MVMVA done\n");

    return ERR_OK;
}


int Cop2::NCDS() { // Real command 0x13, fake command 0x0E
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

	// Step 1
	applyLightMatrix(sf);

    // Step 2
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
	uint8_t sf = operand->sf * 12; // Already multiplied by 12

	// Step 1
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
        // Step 1
		applyLightMatrix(sf);

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

int Cop2::NCCS() { // Real command 0x1A, fake command 0x10
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

    // Step 1
	applyLightMatrix(sf);

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
    printf("COP2 command NCCS done\n");

    return ERR_OK;
}

int Cop2::CC() { // Real command 0x1C, fake command 0x13
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

    // Step 1
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
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

	// Step 1
	applyLightMatrix(sf);

	// Step 2
    applyColorMatrix(sf);

	// Step 3
    pushColorFifo();

    printf("COP2 command NCS done\n");

    return ERR_OK;
}

int Cop2::NCT() { // Real command 0x20, fake command 0x0D
    uint8_t sf = operand->sf * 12; // Already multiplied by 12

	for (int i = 0; i < 3; i++) {
		// Step 1
		applyLightMatrix(sf);

		// Step 2
	    applyColorMatrix(sf);

		// Step 3
        pushColorFifo();
    }

	printf("COP2 command NCT done\n");

    return ERR_OK;
}

int Cop2::SQR() { // Real command 0x28, fake command 0x0A
    int64_t MAC1 = (int64_t)getIR1() * getIR1();
    checkMAC(MAC1, 1);

    int64_t MAC2 = (int64_t)getIR2() * getIR2();
    checkMAC(MAC2, 2);

    int64_t MAC3 = (int64_t)getIR3() * getIR3();
    checkMAC(MAC3, 3);

    if (operand->sf) { // SAR
        MAC1 >>= 12;
        MAC2 >>= 12;
        MAC3 >>= 12;
    }

    setIR1(saturateIR(MAC1, 1, operand->lm));
    setIR2(saturateIR(MAC2, 2, operand->lm));
    setIR3(saturateIR(MAC3, 3, operand->lm));

    setMAC1((int32_t)MAC1);
    setMAC2((int32_t)MAC2);
    setMAC3((int32_t)MAC3);

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
    uint8_t sf = operand->sf * 12;

    for (int i = 0; i < 3; i++) {
        // Step 1
        RGBColor *color = RGBColors[0];

        int64_t MAC1 = (int64_t)color->r << 16;
        checkMAC(MAC1, 1);
		setMAC1((int32_t)MAC1);

        int64_t MAC2 = (int64_t)color->g << 16;
        checkMAC(MAC2, 2);
		setMAC2((int32_t)MAC2);

        int64_t MAC3 = (int64_t)color->b << 16;
        checkMAC(MAC3, 3);
		setMAC3((int32_t)MAC3);

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

int Cop2::AVSZ3() { // Real command 0x2D, fake command 0x15
    // Step 1
	int64_t MAC0 = (int64_t)(getZSF3() * (getSZ1() + getSZ2() + getSZ3()));
	checkMAC0(MAC0);
	setMAC0((int32_t)MAC0);

	// Step 2
	setOTZ(saturateOTZ(MAC0 / 0x1000));

    printf("COP2 command AVSZ3 done\n");

    return ERR_OK;
}

int Cop2::AVSZ4() { // Real command 0x2E, fake command 0x16
    // Step 1
    int64_t MAC0 = (int64_t)(getZSF4() * (getSZ0() + getSZ1() + getSZ2() + getSZ3()));
    checkMAC0(MAC0);
    setMAC0((int32_t)MAC0);

    // Step 2
    setOTZ(saturateOTZ(MAC0 / 0x1000));

    printf("COP2 command AVSZ4 done\n");

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
	int64_t MAC1 = (int64_t)getMAC1() << sf;
	checkMAC(MAC1, 1);
	setMAC1((int32_t)MAC1);

	int64_t MAC2 = (int64_t)getMAC2() << sf;
	checkMAC(MAC2, 2);
	setMAC2((int32_t)MAC2);

	int64_t MAC3 = (int64_t)getMAC3() << sf;
	checkMAC(MAC3, 3);
	setMAC3((int32_t)MAC3);

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
        // Step 1
		applyLightMatrix(sf);

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
        case 0x12: return MVMVA();
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
        case 0x2D: return AVSZ3();
        case 0x2E: return AVSZ4();
        case 0x30: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x3D: return GPF();
        case 0x3E: return GPL();
        case 0x3F: return NCCT();
    }

    return ERR_COP2_COMMAND_NOT_FOUND;
}
