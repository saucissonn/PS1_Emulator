#include "ps1/cpu/cpu.hpp"

#include <stdio.h>

#include "utils/error.hpp"

// Instructions

int Cpu::ADD() {
	int64_t result = (int64_t)GPR[operand->rs] + (int64_t)GPR[operand->rt];

	if (result > INT32_MAX || result < INT32_MIN) {
        raiseException(Exception::IntegerOverflow);
        return ERR_OK;
	}

	GPR[operand->rd] = (uint32_t)result;

	printf("Value: %8X\n", GPR[operand->rd]);
	printf("CPU instruction ADD done\n");

	return ERR_OK;
}

int Cpu::ADDI() {
	int64_t result = (int64_t)GPR[operand->rs] + (int64_t)signExtend(operand->immediate, 16);

    if (result > INT32_MAX || result < INT32_MIN) {
        raiseException(Exception::IntegerOverflow);
        return ERR_OK;
    }

    GPR[operand->rt] = (uint32_t)result;

    printf("Value: %8X\n", GPR[operand->rt]);
    printf("CPU instruction ADDI done\n");

    return ERR_OK;
}

int Cpu::ADDIU() {
    int64_t result = (int64_t)GPR[operand->rs] + (int64_t)signExtend(operand->immediate, 16);

    GPR[operand->rt] = (uint32_t)result;

    printf("Value: %8X\n", GPR[operand->rt]);
    printf("CPU instruction ADDIU done\n");

    return ERR_OK;
}

int Cpu::ADDU() {
    int64_t result = (int64_t)GPR[operand->rs] + (int64_t)GPR[operand->rt];

    GPR[operand->rd] = (uint32_t)result;

	printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction ADDU done\n");

    return ERR_OK;
}

int Cpu::AND() {
    GPR[operand->rd] = GPR[operand->rs] & GPR[operand->rt];

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction AND done\n");

    return ERR_OK;
}

int Cpu::ANDI() {
    GPR[operand->rt] = (uint32_t)operand->immediate & GPR[operand->rs];

    printf("Value: %8X\n", GPR[operand->rt]);
    printf("CPU instruction ANDI done\n");

    return ERR_OK;
}

int Cpu::BEQ() {
	int32_t offset = signExtend(operand->immediate, 16);
	int32_t target = offset << 2;

	if (GPR[operand->rs] == GPR[operand->rt])
		nextPC = PC + target;

	inDelaySlot = 1;

    printf("CPU instruction BEQ done\n");

    return ERR_OK;
}

int Cpu::BNE() {
    int32_t offset = signExtend(operand->immediate, 16);
    int32_t target = offset << 2;

    if (GPR[operand->rs] != GPR[operand->rt])
        nextPC = PC + target;

    inDelaySlot = 1;

    printf("CPU instruction BNE done\n");

    return ERR_OK;
}

int Cpu::J() {
    uint32_t temp = operand->target << 2;
	uint32_t tempPC = instructionPC & 0xF0000000;

	nextPC = tempPC | temp;

    inDelaySlot = 1;

    printf("CPU instruction J done\n");

    return ERR_OK;
}

int Cpu::JAL() {
    uint32_t temp = operand->target << 2;
    uint32_t tempPC = instructionPC & 0xF0000000;

	GPR[31] = instructionPC + 8;

    nextPC = tempPC | temp;

    inDelaySlot = 1;

    printf("CPU instruction JAL done\n");

    return ERR_OK;
}

int Cpu::JALR() {
    uint32_t target = GPR[operand->rs];

    if (target & 0x3) {
        raiseException(Exception::LoadAddressError);
        return ERR_OK;
    }

    GPR[operand->rd] = instructionPC + 8;

    nextPC = target;
    inDelaySlot = 1;

    printf("CPU instruction JALR done\n");

    return ERR_OK;
}

int Cpu::JR() {
    uint32_t target = GPR[operand->rs];

	if (target & 3) {
		raiseException(Exception::LoadAddressError);
		return ERR_OK;
	}

    nextPC = target;
    inDelaySlot = 1;

    printf("CPU instruction JR done\n");

    return ERR_OK;
}

int Cpu::LUI() {
	GPR[operand->rt] = (uint32_t)(operand->immediate << 16);

	printf("Value: %8X\n", GPR[operand->rt]);
    printf("CPU instruction LUI done\n");

	return ERR_OK;
}

int Cpu::NOP() {
    printf("CPU instruction NOP done\n");

	return ERR_OK;
}

int Cpu::NOR() {
    GPR[operand->rd] = ~(GPR[operand->rs] | GPR[operand->rt]);

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction NOR done\n");

    return ERR_OK;
}

int Cpu::OR() {
    GPR[operand->rd] = GPR[operand->rs] | GPR[operand->rt];

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction OR done\n");

    return ERR_OK;
}

int Cpu::ORI() {
    GPR[operand->rt] = (uint32_t)operand->immediate | GPR[operand->rs];

    printf("Value: %8X\n", GPR[operand->rt]);
    printf("CPU instruction ORI done\n");

	return ERR_OK;
}

int Cpu::SLT() {
    if ((int32_t)GPR[operand->rs] < (int32_t)GPR[operand->rt]) {
        GPR[operand->rd] = 1;
    }
    else {
        GPR[operand->rd] = 0;
    }

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction SLT done\n");

    return ERR_OK;
}

int Cpu::SLTI() {
	if ((int32_t)GPR[operand->rs] < signExtend(operand->immediate, 16)) {
		GPR[operand->rt] = 1;
	}
	else {
        GPR[operand->rt] = 0;
	}

    printf("Value: %8X\n", GPR[operand->rt]);
    printf("CPU instruction SLTI done\n");

    return ERR_OK;
}

int Cpu::SLTIU() {
    if (GPR[operand->rs] < (uint32_t)signExtend(operand->immediate, 16)) {
        GPR[operand->rt] = 1;
    }
    else {
        GPR[operand->rt] = 0;
    }

    printf("Value: %8X\n", GPR[operand->rt]);
    printf("CPU instruction SLTIU done\n");

    return ERR_OK;
}

int Cpu::SLTU() {
    if (GPR[operand->rs] < GPR[operand->rt]) {
        GPR[operand->rd] = 1;
    }
    else {
        GPR[operand->rd] = 0;
    }

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction SLTU done\n");

    return ERR_OK;
}

int Cpu::SLL() {
    GPR[operand->rd] = (uint32_t)(GPR[operand->rt] << operand->shamt);

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction SLL done\n");

    return ERR_OK;
}

int Cpu::SLLV() {
    GPR[operand->rd] = (uint32_t)(GPR[operand->rt] << (GPR[operand->rs] & 0x1F));

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction SLLV done\n");

    return ERR_OK;
}

int Cpu::SRA() {
    GPR[operand->rd] = signExtend(GPR[operand->rt] >> operand->shamt, 32);

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction SRA done\n");

    return ERR_OK;
}

int Cpu::SRAV() {
    GPR[operand->rd] = signExtend(GPR[operand->rt] >> (GPR[operand->rs] & 0x1F), 32);

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction SRAV done\n");

    return ERR_OK;
}

int Cpu::SRL() {
    GPR[operand->rd] = (uint32_t)(GPR[operand->rt] >> operand->shamt);

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction SRL done\n");

    return ERR_OK;
}

int Cpu::SRLV() {
    GPR[operand->rd] = (uint32_t)(GPR[operand->rt] >> (GPR[operand->rs] & 0x1F));

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction SRLV done\n");

    return ERR_OK;
}

int Cpu::SUBU() {
    int64_t result = (int64_t)GPR[operand->rs] - (int64_t)GPR[operand->rt];

    GPR[operand->rd] = (uint32_t)result;

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction SUBU done\n");

    return ERR_OK;
}

int Cpu::XOR() {
    GPR[operand->rd] = GPR[operand->rs] ^ GPR[operand->rt];

    printf("Value: %8X\n", GPR[operand->rd]);
    printf("CPU instruction XOR done\n");

    return ERR_OK;
}

int Cpu::XORI() {
    GPR[operand->rt] = (uint32_t)operand->immediate ^ GPR[operand->rs];

    printf("Value: %8X\n", GPR[operand->rt]);
    printf("CPU instruction XORI done\n");

    return ERR_OK;
}

// Decoder

uint32_t Cpu::convertAddress(uint32_t address) {
    if (0x80000000 <= address && address <= 0xBFFFFFFF) { // KSEG0 or KSEG1
        address &= 0x1FFFFFFF;
    }
    else {
        printf("Should use TLB here\n");
    }
    return address;
}

uint32_t Cpu::fetchPC() {
	uint32_t address = convertAddress(instructionPC);

	uint32_t value = bus->read(address);

	return value;
}

void Cpu::transfromRType(uint32_t instruction) {
    operand->rs = (instruction >> 21) & 0x1F; // 5 bits
    operand->rt = (instruction >> 16) & 0x1F; // 5 bits
    operand->rd = (instruction >> 11) & 0x1F; // 5 bits
    operand->shamt = (instruction >> 6) & 0x1F; // 5 bits
}

void Cpu::transfromIType(uint32_t instruction) {
    operand->rs = (instruction >> 21) & 0x1F; // 5 bits
    operand->rt = (instruction >> 16) & 0x1F; // 5 bits
    operand->immediate = instruction & 0xFFFF; // 16 bits
}

void Cpu::transfromJType(uint32_t instruction) {
    operand->target = (instruction << 6) >> 6; // 26 bits
}

int Cpu::decodeInstruction(uint32_t instruction) {
	printf("\nPC: %8X\n", instructionPC);
	printf("Instruction: %8X\n", instruction);
	uint8_t opcode = instruction >> 26; // 6 bits

	printf("Opcode: %2X\n", opcode);

	switch (opcode) {
		case 0x00: { // R-Type
			uint8_t funct = instruction & 0x3F; // 6 bits

			printf("Funct: %2X\n", funct);

			operand->rs = (instruction >> 21) & 0x1F; // 5 bits
            operand->rt = (instruction >> 16) & 0x1F; // 5 bits
            operand->rd = (instruction >> 11) & 0x1F; // 5 bits
            operand->shamt = (instruction >> 6) & 0x1F; // 5 bits

			switch (funct) {
				case 0x00: {
					if (instruction == 0) {
						return NOP();
					}
					return SLL();
				}

				case 0x02: {
					return SRL();
				}

                case 0x03: {
                    return SRA();
                }

                case 0x04: {
                    return SLLV();
                }

                case 0x06: {
                    return SRLV();
                }

                case 0x07: {
                    return SRAV();
                }

                case 0x08: {
                    return JR();
                }

                case 0x09: {
                    return JALR();
                }

				case 0x20: {
					return ADD();
				}

                case 0x21: {
                    return ADDU();
                }

                case 0x23: {
                    return SUBU();
                }

                case 0x24: {
                    return AND();
                }

                case 0x25: {
                    return OR();
                }

                case 0x26: {
                    return XOR();
                }

                case 0x27: {
                    return NOR();
                }

                case 0x2A: {
                    return SLT();
                }

                case 0x2B: {
                    return SLTU();
                }

                case 0x2C: {
                    return SLTU();
                }
			}
			return ERR_CPU_INSTRUCTION_NOT_FOUND;
		}

        case 0x02: {
            transfromJType(instruction);
            return J();
        }

        case 0x03: {
            transfromJType(instruction);
            return JAL();
        }

		case 0x04: {
			transfromIType(instruction);
			return BEQ();
		}

        case 0x05: {
            transfromIType(instruction);
            return BNE();
        }

		case 0x09: {
            transfromIType(instruction);
            return ADDIU();
		}

		case 0x0A: {
            transfromIType(instruction);
            return SLTI();
		}

        case 0x0B: {
            transfromIType(instruction);
            return SLTIU();
        }

        case 0x0C: {
            transfromIType(instruction);
            return ANDI();
        }

        case 0x0D: {
            transfromIType(instruction);
            return ORI();
        }

        case 0x0E: {
            transfromIType(instruction);
            return XORI();
        }

		case 0x0F: {
			transfromIType(instruction);
			return LUI();
		}
	}

	return ERR_CPU_INSTRUCTION_NOT_FOUND;
}
