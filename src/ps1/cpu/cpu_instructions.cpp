#include "ps1/cpu/cpu.hpp"

#include <stdio.h>

#include "utils/error.hpp"

int Cpu::dispatchInstruction(uint32_t instruction) {
    uint8_t opcode = instruction >> 26; // 6 bits

    switch (opcode) {
		case 0x10: { // COP0
			return cop0.decodeInstruction(instruction);
		}

		case 0x12: { // COP2
			return cop2.decodeCommand(instruction);
		}

		default: { // CPU
			return decodeInstruction(instruction);
		}
	}
}

// Instructions

int Cpu::ADD() {
	int64_t result = (int64_t)(int32_t)GPR[operand->rs] + (int64_t)(int32_t)GPR[operand->rt];

	if (result > INT32_MAX || result < INT32_MIN) {
        raiseException(Exception::ArithmeticOverflow);
        return ERR_OK;
	}

	GPR[operand->rd] = (uint32_t)result;

	printf("Value: %08X\n", GPR[operand->rd]);
	printf("CPU instruction ADD done\n");

	return ERR_OK;
}

int Cpu::ADDI() {
	int64_t result = (int64_t)(int32_t)GPR[operand->rs] + (int64_t)(int32_t)signExtend(operand->immediate, 16);

    if (result > INT32_MAX || result < INT32_MIN) {
        raiseException(Exception::ArithmeticOverflow);
        return ERR_OK;
    }

    GPR[operand->rt] = (uint32_t)result;

    printf("Value: %08X\n", GPR[operand->rt]);
    printf("CPU instruction ADDI done\n");

    return ERR_OK;
}

int Cpu::ADDIU() {
    int64_t result = (int64_t)(int32_t)GPR[operand->rs] + (int64_t)(int32_t)signExtend(operand->immediate, 16);

    GPR[operand->rt] = (uint32_t)result;

    printf("Value: %08X\n", GPR[operand->rt]);
    printf("CPU instruction ADDIU done\n");

    return ERR_OK;
}

int Cpu::ADDU() {
    int64_t result = (int64_t)(int32_t)GPR[operand->rs] + (int64_t)(int32_t)GPR[operand->rt];

    GPR[operand->rd] = (uint32_t)result;

	printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction ADDU done\n");

    return ERR_OK;
}

int Cpu::AND() {
    GPR[operand->rd] = GPR[operand->rs] & GPR[operand->rt];

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction AND done\n");

    return ERR_OK;
}

int Cpu::ANDI() {
    GPR[operand->rt] = (uint32_t)operand->immediate & GPR[operand->rs];

    printf("Value: %08X\n", GPR[operand->rt]);
    printf("CPU instruction ANDI done\n");

    return ERR_OK;
}

int Cpu::BEQ() {
    int32_t offset = signExtend(operand->immediate, 16);
    int32_t target = offset << 2;

	nextPC = instructionPC + 8; // default

    if (GPR[operand->rs] == GPR[operand->rt])
        nextPC = instructionPC + 4 + target;

    inDelaySlot = 1;

    printf("CPU instruction BEQ done\n");

    return ERR_OK;
}

int Cpu::BNE() {
    int32_t offset = signExtend(operand->immediate, 16);
    int32_t target = offset << 2;

	nextPC = instructionPC + 8; // default

    printf("BNE: rs=$%d = %08X, rt=$%d = %08X\n", operand->rs, GPR[operand->rs], operand->rt, GPR[operand->rt]);

	if (GPR[operand->rs] != GPR[operand->rt]) {
	    nextPC = instructionPC + 4 + target;
	}

    inDelaySlot = 1;

    printf("CPU instruction BNE done\n");

    return ERR_OK;
}

int Cpu::BREAK() {
    Cpu::raiseException(Exception::Breakpoint);
    printf("CPU instruction BREAK done\n");
    return ERR_OK;
}

int Cpu::DIV(){
    LO = (int32_t)GPR[operand->rs] / (int32_t)GPR[operand->rt];
    HI = (int32_t)GPR[operand->rs] % (int32_t)GPR[operand->rt];

	printf("HI value: %08X, LO value: %08X\n", HI, LO);
    printf("CPU instruction DIV done\n");

    return ERR_OK;
}

int Cpu::DIVU() {
    LO = GPR[operand->rs] / GPR[operand->rt];
    HI = GPR[operand->rs] % GPR[operand->rt];

    printf("HI value: %08X, LO value: %08X\n", HI, LO);
    printf("CPU instruction DIVU done\n");

    return ERR_OK;
}

int Cpu::J() {
    uint32_t target = operand->target << 2;
    uint32_t tempPC = instructionPC & 0xF0000000;

    nextPC = tempPC | target;
    inDelaySlot = 1;

    printf("Jump to address: %08X\n", nextPC);
    printf("CPU instruction J done\n");

    return ERR_OK;
}

int Cpu::JAL() {
    uint32_t target = operand->target << 2;
    uint32_t tempPC = instructionPC & 0xF0000000;

    GPR[31] = instructionPC + 4;

    nextPC = tempPC | target;
    inDelaySlot = 1;

    printf("Jump to address: %08X\n", nextPC);
    printf("CPU instruction JAL done\n");

    return ERR_OK;
}

int Cpu::JALR() {
    uint32_t target = GPR[operand->rs];

    if (target & 0x3) {
		printf("Target missaligned on address: %08X\n", target);
        cop0.setBadVaddr(target);
        raiseException(Exception::LoadAddressError);
        return ERR_OK;
    }

    GPR[operand->rd] = instructionPC + 4;

    nextPC = target;
    inDelaySlot = 1;

    printf("Jump to address: %08X\n", nextPC);
    printf("CPU instruction JALR done\n");

    return ERR_OK;
}

int Cpu::JR() {
    uint32_t target = GPR[operand->rs];

    if (target & 0x3) {
        cop0.setBadVaddr(target);
        raiseException(Exception::LoadAddressError);
        return ERR_OK;
    }

    nextPC = target;
    inDelaySlot = 1;

    printf("Jump to address: %08X\n", nextPC);
    printf("CPU instruction JR done\n");

    return ERR_OK;
}

int Cpu::LUI() {
	GPR[operand->rt] = (uint32_t)(operand->immediate << 16);

	printf("Value: %08X\n", GPR[operand->rt]);
    printf("CPU instruction LUI done\n");

	return ERR_OK;
}

int Cpu::MFHI() {
    GPR[operand->rd] = HI;

    printf("GPR[%d] value: %08X\n", operand->rd, GPR[operand->rd]);
    printf("CPU instruction MFHI done\n");

    return ERR_OK;
}

int Cpu::MTHI() {
    HI = GPR[operand->rs];

    printf("HI value: %08X\n", HI);
    printf("CPU instruction MTHI done\n");

    return ERR_OK;
}

int Cpu::MFLO() {
    GPR[operand->rd] = LO;

    printf("GPR[%d] value: %08X\n", operand->rd, GPR[operand->rd]);
    printf("CPU instruction MFLO done\n");

    return ERR_OK;
}

int Cpu::MTLO() {
    LO = GPR[operand->rs];

    printf("LO value: %08X\n", LO);
    printf("CPU instruction MTLO done\n");

    return ERR_OK;
}

int Cpu::MULT() {
    int64_t res = (int64_t)(int32_t)GPR[operand->rs] * (int64_t)(int32_t)GPR[operand->rt];

    LO = (uint32_t)res;
    HI = (uint32_t)(res >> 32);

    printf("HI value: %08X, LO value: %08X\n", HI, LO );
    printf("CPU instruction MULT done\n");
    return ERR_OK;
}

int Cpu::MULTU() {
    uint64_t res = (uint64_t)GPR[operand->rs] * (uint64_t)GPR[operand->rt];

    LO = (uint32_t)res;
    HI = (uint32_t)(res >> 32);

    printf("HI value: %08X, LO value: %08X\n", HI, LO );
    printf("CPU instruction MULTU done\n");

    return ERR_OK;
}

int Cpu::NOP() {
    printf("CPU instruction NOP done\n");

	return ERR_OK;
}

int Cpu::NOR() {
    GPR[operand->rd] = ~(GPR[operand->rs] | GPR[operand->rt]);

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction NOR done\n");

    return ERR_OK;
}

int Cpu::OR() {
    GPR[operand->rd] = GPR[operand->rs] | GPR[operand->rt];

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction OR done\n");

    return ERR_OK;
}

int Cpu::ORI() {
    GPR[operand->rt] = (uint32_t)operand->immediate | GPR[operand->rs];

    printf("Value: %08X\n", GPR[operand->rt]);
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

    printf("Value: %08X\n", GPR[operand->rd]);
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

    printf("Value: %08X\n", GPR[operand->rt]);
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

    printf("Value: %08X\n", GPR[operand->rt]);
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

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction SLTU done\n");

    return ERR_OK;
}

int Cpu::SLL() {
    GPR[operand->rd] = (uint32_t)(GPR[operand->rt] << operand->shamt);

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction SLL done\n");

    return ERR_OK;
}

int Cpu::SLLV() {
    GPR[operand->rd] = (uint32_t)(GPR[operand->rt] << (GPR[operand->rs] & 0x1F));

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction SLLV done\n");

    return ERR_OK;
}

int Cpu::SRA() {
    int32_t value = signExtend(GPR[operand->rt], 32);

    GPR[operand->rd] = (uint32_t)(value >> operand->shamt);

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction SRA done\n");

    return ERR_OK;
}

int Cpu::SRAV() {
    int32_t value = signExtend(GPR[operand->rt], 32);
    uint32_t shift = GPR[operand->rs] & 0x1F;

    GPR[operand->rd] = (uint32_t)(value >> shift);

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction SRAV done\n");

    return ERR_OK;
}

int Cpu::SRL() {
    GPR[operand->rd] = (uint32_t)(GPR[operand->rt] >> operand->shamt);

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction SRL done\n");

    return ERR_OK;
}

int Cpu::SRLV() {
    GPR[operand->rd] = (uint32_t)(GPR[operand->rt] >> (GPR[operand->rs] & 0x1F));

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction SRLV done\n");

    return ERR_OK;
}

int Cpu::SUB() {
    GPR[operand->rd] = (int)GPR[operand->rs] - (int)GPR[operand->rt];

    printf("GPR[%d] value : %08X\n", operand->rd, GPR[operand->rd]);
    printf("CPU instruction SUB done\n");
    return ERR_OK;
}

int Cpu::SUBU() {
    int64_t result = (int64_t)GPR[operand->rs] - (int64_t)GPR[operand->rt];

    GPR[operand->rd] = (uint32_t)result;

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction SUBU done\n");

    return ERR_OK;
}

int Cpu::SW() {
    int32_t address = signExtend(operand->immediate, 16) + GPR[operand->rs];

    if (address & 3) {
        cop0.setBadVaddr(address);
        raiseException(Exception::StoreAddressError);
        return ERR_OK;
    }

	bus->write(address, GPR[operand->rt]);

    int error = bus->getBusError();

    if (error != ERR_OK) { 
        return handleErrorOnRW(error, address);
    }

	printf("Address: %08X\n", address);
    printf("CPU instruction SW done\n");

    return ERR_OK;
}

int Cpu::SYSCALL() {
    raiseException(Exception::Syscall);
    printf("CPU instruction SYSCALL done\n");
    return ERR_OK;
}

int Cpu::XOR() {
    GPR[operand->rd] = GPR[operand->rs] ^ GPR[operand->rt];

    printf("Value: %08X\n", GPR[operand->rd]);
    printf("CPU instruction XOR done\n");

    return ERR_OK;
}

int Cpu::XORI() {
    GPR[operand->rt] = (uint32_t)operand->immediate ^ GPR[operand->rs];

    printf("Value: %08X\n", GPR[operand->rt]);
    printf("CPU instruction XORI done\n");

    return ERR_OK;
}

int Cpu::BLEZ(){
    int32_t offset = signExtend(operand->immediate, 16);
	int32_t target = offset << 2;

	nextPC = instructionPC + 8; // default

	if ((int)GPR[operand->rs] <= 0)
		nextPC = instructionPC + 4 + target;

	inDelaySlot = 1;

    printf("CPU instruction BLEZ done\n");

    return ERR_OK;
}

int Cpu::BGTZ(){
    int32_t offset = signExtend(operand->immediate, 16);
	int32_t target = offset << 2;

	nextPC = instructionPC + 8; // default

	if ((int)GPR[operand->rs] > 0)
		nextPC = instructionPC + 4 + target;

	inDelaySlot = 1;

    printf("CPU instruction BGTZ done\n");

    return ERR_OK;
}

int Cpu::BLTZAL(){
    int32_t offset = signExtend(operand->immediate, 16);
	int32_t target = offset << 2;

	nextPC = instructionPC + 8; // default

	GPR[31] = instructionPC + 4;
	if ((int)GPR[operand->rs] < 0)
		nextPC = instructionPC + 4 + target;

	inDelaySlot = 1;

    printf("CPU instruction BLTZAL done\n");

    return ERR_OK;
}

int Cpu::BGEZAL(){
    int32_t offset = signExtend(operand->immediate, 16);
	int32_t target = offset << 2;

	nextPC = instructionPC + 8; // default

	GPR[31] = instructionPC + 4;
	if ((int)GPR[operand->rs] >= 0)
		nextPC = instructionPC + 4 + target;

	inDelaySlot = 1;

    printf("CPU instruction BGEZAL done\n");

    return ERR_OK;
}

int Cpu::LB(){
    uint32_t address = GPR[operand->rs] + signExtend(operand->immediate, 16); // any number
    int miniOffset = address % 4;
	uint32_t temp = bus->read(address - miniOffset); // multiple of 4

    int error = bus->getBusError();

	if (error != ERR_OK) { 
        return handleErrorOnRW(error, address);
    }

    // reversed because of little endian
    switch (miniOffset){
        case 0: GPR[operand->rt] = signExtend(temp & 0xFF, 8); break;
        case 1: GPR[operand->rt] = signExtend((temp >> 8) & 0xFF, 8); break;
        case 2: GPR[operand->rt] = signExtend((temp >> 16) & 0xFF, 8); break;
        case 3: GPR[operand->rt] = signExtend((temp >> 24) & 0xFF, 8); break;
    }

    printf("%08X loaded from address %08X to register %08X\n", GPR[operand->rt], address, operand->rt);
    printf("CPU instruction LB done\n");

    return ERR_OK;
}

int Cpu::LH(){
    uint32_t address = GPR[operand->rs] + signExtend(operand->immediate, 16); // multiple of 2

    if ((address & 1) != 0){
        cop0.setBadVaddr(address);
        return raiseException(Exception::LoadAddressError);
    }

    int miniOffset = address % 4;
    uint32_t temp = bus->read(address - miniOffset) ; // multiple of 4

    int error = bus->getBusError();

    if (error != ERR_OK) { 
        return handleErrorOnRW(error, address);
    }

    // reversed because of little endian
    switch(miniOffset){
        case 0: GPR[operand->rt] = signExtend(temp & 0xFFFF, 16); break;
        case 2: GPR[operand->rt] = signExtend(temp >> 16, 16); break;
		default: return ERR_READ_ADDRESS_NOT_ALIGNED;
    }

    printf("%08X loaded from address %08X to register %08X\n", (int)GPR[operand->rt], address, operand->rt);
    printf("CPU instruction LH done\n");

    return ERR_OK;
}

int Cpu::LWL(){
    return ERR_OK;
}

int Cpu::LWR(){
    return ERR_OK;
}

int Cpu::LW(){
    uint32_t address = GPR[operand->rs] + signExtend(operand->immediate, 16);

	if ((address & 0b11) != 0) { // multiple of 4
        cop0.setBadVaddr(address);
        return raiseException(Exception::LoadAddressError);
    }

	uint32_t value = bus->read(address);

    int error = bus->getBusError();

    if (error != ERR_OK) { 
        return handleErrorOnRW(error, address);
    }

	GPR[operand->rt] = value;

	printf("%08X loaded from address %08X to register %08X\n", GPR[operand->rt], address, operand->rt);
    printf("CPU instruction LW done\n");

	return ERR_OK;
}

int Cpu::LBU(){
    uint32_t address = GPR[operand->rs] + signExtend(operand->immediate, 16); // any number
    int miniOffset = address % 4;
    uint32_t temp = bus->read(address - miniOffset); // multiple of 4

    int error = bus->getBusError();

    if (error != ERR_OK) { 
        return handleErrorOnRW(error, address);
    }

    // reversed because of little endian
    switch (miniOffset){
        case 0: GPR[operand->rt] = temp & 0xFF; break;
        case 1: GPR[operand->rt] = (temp >> 8) & 0xFF; break;
        case 2: GPR[operand->rt] = (temp >> 16) & 0xFF; break;
        case 3: GPR[operand->rt] = (temp >> 24) & 0xFF; break;
    }

    printf("%08X loaded from address %08X to register %08X\n", GPR[operand->rt], address, operand->rt);
    printf("CPU instruction LBU done\n");

    return ERR_OK;
}

int Cpu::LHU(){
    uint32_t address = GPR[operand->rs] + signExtend(operand->immediate, 16); // multiple of 2

    if ((address & 1) != 0){
        cop0.setBadVaddr(address);
        return raiseException(Exception::LoadAddressError);
    }

    int miniOffset = address % 4;
    uint32_t temp = bus->read(address - miniOffset) ; // multiple of 4

    int error = bus->getBusError();

    if (error != ERR_OK) { 
        return handleErrorOnRW(error, address);
    }

    // reversed because of little endian
    switch(miniOffset){
        case 0: GPR[operand->rt] = temp & 0xFFFF; break;
        case 2: GPR[operand->rt] = temp >> 16; break;
		default: return ERR_READ_ADDRESS_NOT_ALIGNED;
    }

    printf("%08X loaded from address %08X to register %08X\n", GPR[operand->rt], address, operand->rt);
    printf("CPU instruction LHU done\n");

    return ERR_OK;
}

int Cpu::SB() {
    uint32_t address = GPR[operand->rs] + signExtend(operand->immediate, 16);

    bus->write8(address, GPR[operand->rt] & 0xFF);

    int error = bus->getBusError();

    if (error != ERR_OK) {
		return handleErrorOnRW(error, address);
	}

    printf("%08X written to %08X\n", GPR[operand->rt] & 0xFF, address);

    printf("CPU instruction SB done\n");

    return ERR_OK;
}

int Cpu::SH(){
    uint32_t address = GPR[operand->rs] + signExtend(operand->immediate, 16); // multiple of 2

    if (address % 2 != 0){
        bus->setBusError(ERR_OK);
        cop0.setBadVaddr(address);
        return raiseException(Exception::StoreAddressError);
    }

	bus->write16(address, GPR[operand->rt] & 0xFFFF);

    int error = bus->getBusError();

    if (error != ERR_OK) { 
        return handleErrorOnRW(error, address);
    }

    printf("%08X written to %08X\n", GPR[operand->rt] & 0xFFFF, address);
    printf("CPU instruction SH done\n");

    return ERR_OK;
}

int Cpu::BGEZ(){
    int32_t offset = signExtend(operand->immediate, 16);
	int32_t target = offset << 2;

	nextPC = instructionPC + 8; // default

	if ((int)GPR[operand->rs] >= 0)
		nextPC = instructionPC + 4 + target;

	inDelaySlot = 1;

    printf("CPU instruction BGEZ done\n");

    return ERR_OK;
}

int Cpu::BLTZ(){
    int32_t offset = signExtend(operand->immediate, 16);
	int32_t target = offset << 2;

	nextPC = instructionPC + 8; // default

	if ((int)GPR[operand->rs] < 0)
		nextPC = instructionPC + 4 + target;

	inDelaySlot = 1;

    printf("CPU instruction BLTZ done\n");

    return ERR_OK;
}
int Cpu::SWL(){
    printf("not supported\n");
    return ERR_OK;
}

int Cpu::SWR(){
    printf("not supported\n");
    return ERR_OK;
}

int Cpu::LWC0(){
    printf("not supported\n");
    return ERR_OK;
}

int Cpu::LWC1(){
    printf("not supported\n");
    return ERR_OK;
}

int Cpu::LWC2(){
    printf("not supported\n");
    return ERR_OK;
}

int Cpu::LWC3(){
    printf("not supported\n");
    return ERR_OK;
}

int Cpu::SWC0(){
    printf("not supported\n");
    return ERR_OK;
}

int Cpu::SWC1(){
    printf("not supported\n");
    return ERR_OK;
}

int Cpu::SWC2(){
    printf("not supported\n");
    return ERR_OK;
}

int Cpu::SWC3(){
    printf("not supported\n");
    return ERR_OK;
}


uint32_t Cpu::fetchPC() { // From the current PC return the value at its address
	uint32_t address = convertAddress(PC);

	uint32_t value = bus->read(address);

    if (bus->getBusError() != ERR_OK) {
        bus->setBusError(ERR_OK);
        cop0.setBadVaddr(address);
        return raiseException(Exception::BusErrorInstruction); // TODO handle this exception
    }

	return value;
}

void Cpu::transfromRType(uint32_t instruction) { // Put R-Type instruction into operand
    operand->rs = (instruction >> 21) & 0x1F; // 5 bits
    operand->rt = (instruction >> 16) & 0x1F; // 5 bits
    operand->rd = (instruction >> 11) & 0x1F; // 5 bits
    operand->shamt = (instruction >> 6) & 0x1F; // 5 bits
}

void Cpu::transfromIType(uint32_t instruction) { // Put R-Type instruction into operand
    operand->rs = (instruction >> 21) & 0x1F; // 5 bits
    operand->rt = (instruction >> 16) & 0x1F; // 5 bits
    operand->immediate = instruction & 0xFFFF; // 16 bits
}

void Cpu::transfromJType(uint32_t instruction) { // Put R-Type instruction into operand
    operand->target = (instruction << 6) >> 6; // 26 bits
}

int Cpu::decodeInstruction(uint32_t instruction) { // From an instruction find and execute it among instruction functions
printf("PC=%08X nextPC=%08X prevPC=%08X delay=%d\n", PC, nextPC, prevPC, inDelaySlot);
	printf("Instruction: %08X\n", instruction);
	uint8_t opcode = instruction >> 26; // 6 bits

	cpuStateUpdate(instruction);

	printf("Opcode: %2X\n", opcode);

	transfromIType(instruction); // most of the instructions are Itype

	switch (opcode) {
		case 0x00: { // R-Type
			uint8_t funct = instruction & 0x3F; // 6 bits

			printf("Funct: %2X\n", funct);

			transfromRType(instruction);

			switch (funct) {
				case 0x00: {
					if (instruction == 0)
						return NOP();
					return SLL();
				}
				case 0x02: return SRL();
				case 0x03: return SRA();
				case 0x04: return SLLV();
				case 0x06: return SRLV();
				case 0x07: return SRAV();
				case 0x08: return JR();
				case 0x09: return JALR();
				case 0x0C: return SYSCALL();
				case 0x0D: return BREAK();
				case 0x10: return MFHI();
				case 0x11: return MTHI();
				case 0x12: return MFLO();
				case 0x13: return MTLO();
				case 0x18: return MULT();
				case 0x19: return MULTU();
				case 0x1A: return DIV();
				case 0x1B: return DIVU();
				case 0x20: return ADD();
				case 0x21: return ADDU();
				case 0x22: return SUB();
				case 0x23: return SUBU();
				case 0x24: return AND();
				case 0x25: return OR();
				case 0x26: return XOR();
				case 0x27: return NOR();
				case 0x2A: return SLT();
				case 0x2B: return SLTU();
			}
			return ERR_CPU_INSTRUCTION_NOT_FOUND;
		}
        case 0x01: {
            if (operand->rt == 0x10)
                return BLTZAL();
            else if (operand->rt == 0x11)
                return BGEZAL();
            else if ((operand->rt & 0x01) == 0)
                return BLTZ();
            else if ((operand->rt & 0x01) == 1)
                return BGEZ();
            break;
        }

        case 0x02: {
            transfromJType(instruction);
            return J();
        }

        case 0x03: {
            transfromJType(instruction);
            return JAL();
        }
		case 0x04: return BEQ();
        case 0x05: return BNE();
        case 0x08: return ADDI();
		case 0x09: return ADDIU();
		case 0x0A: return SLTI();
        case 0x0B: return SLTIU();
        case 0x0C: return ANDI();
        case 0x0D: return ORI();
        case 0x0E: return XORI();
		case 0x0F: return LUI();
		case 0x06: return BLEZ();
		case 0x07: return BGTZ();
		case 0x20: return LB();
//		case 0x21: return LH();
//		case 0x22: return LWL();
		case 0x23: return LW();
		case 0x24: return LBU();
		case 0x25: return LHU();
//		case 0x26: return LWR();
		case 0x28: return SB();
		case 0x29: return SH();
//		case 0x2A: return SWL();
		case 0x2B: return SW();
//		case 0x2E: return SWR();
//		case 0x30: return LWC0();
//		case 0x31: return LWC1();
//		case 0x32: return LWC2();
//		case 0x33: return LWC3();
//		case 0x38: return SWC0();
//		case 0x39: return SWC1();
//		case 0x3A: return SWC2();
//		case 0x3B: return SWC3();
	}
	return ERR_CPU_INSTRUCTION_NOT_FOUND;
}
