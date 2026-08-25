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

    setIR1(mac1);
    setIR2(mac2);
    setIR3(mac3);

	printf("COP2 command OP done\n");

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

int Cop2::decodeCommand(uint32_t command) { // From a command find and execute it among command functions
    printf("\nPC: %08X\n", cpu->getInstructionPC());
    printf("Command: %08X\n", command);

    transfromCommand(command);

    printf("Opcode: %02X\n", operand->opcode);
    printf("Fake Opcode: %02X\n", operand->fakeOpcode);

    switch (operand->opcode) {
        case 0x01: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x06: return NCLIP();
        case 0x0C: return OP();
        case 0x10: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x11: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x12: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x13: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x14: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x16: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x1B: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x1C: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x1E: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x20: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x28: return SQR();
        case 0x29: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x2A: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x2D: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x2E: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x30: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x3D: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x3E: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x3F: return ERR_COP2_COMMAND_NOT_FOUND;
    }

    switch (operand->fakeOpcode) {
        case 0x01: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x02: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x04: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x06: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x07: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x08: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x09: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x0A: return SQR();
        case 0x0C: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x0D: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x0E: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x0F: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x10: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x11: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x12: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x13: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x14: return NCLIP();
        case 0x15: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x16: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x17: return OP();
        case 0x19: return ERR_COP2_COMMAND_NOT_FOUND;
        case 0x1A: return ERR_COP2_COMMAND_NOT_FOUND;
	}

    return ERR_COP2_COMMAND_NOT_FOUND;
}
