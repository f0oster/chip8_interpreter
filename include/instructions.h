#ifndef instructions_h
#define instructions_h

#include "chip8.h"

void init_instruction_tables(CHIP8 *chip8);

void instr_00EE(CHIP8 *chip8, uint16_t opcode);
void instr_1NNN(CHIP8 *chip8, uint16_t opcode);
void instr_2NNN(CHIP8 *chip8, uint16_t opcode);
void instr_3xkk(CHIP8 *chip8, uint16_t opcode);
void instr_4xkk(CHIP8 *chip8, uint16_t opcode);
void instr_5xy0(CHIP8 *chip8, uint16_t opcode);
void instr_6xkk(CHIP8 *chip8, uint16_t opcode);
void instr_7xkk(CHIP8 *chip8, uint16_t opcode);
void instr_8xy0(CHIP8 *chip8, uint16_t opcode);
void instr_8xy1(CHIP8 *chip8, uint16_t opcode);
void instr_8xy2(CHIP8 *chip8, uint16_t opcode);
void instr_8xy3(CHIP8 *chip8, uint16_t opcode);
void instr_8xy4(CHIP8 *chip8, uint16_t opcode);
void instr_8xy5(CHIP8 *chip8, uint16_t opcode);
void instr_8xy6(CHIP8 *chip8, uint16_t opcode);
void instr_8xy7(CHIP8 *chip8, uint16_t opcode);
void instr_8xyE(CHIP8 *chip8, uint16_t opcode);
void instr_aNNN(CHIP8 *chip8, uint16_t opcode);



#endif
