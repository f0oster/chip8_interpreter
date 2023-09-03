#ifndef chip8_h
#define chip8_h

#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 4096
#define ROM_MEMORY_REGION_START 0x200
#define OPCODE_SIZE 2
#define STACK_SIZE 16
#define REGISTER_COUNT 16

struct CHIP8;

typedef void (*InstructionHandler)(struct CHIP8 *, uint16_t);
typedef InstructionHandler SubTable[16];
typedef SubTable *SubTablePtr;

typedef struct CHIP8 {

    uint16_t pc;

    uint8_t memory[MEMORY_SIZE];

    uint16_t i; // address register
    uint8_t v[REGISTER_COUNT]; // data registers

    uint8_t delay_timer;
    uint8_t sound_timer;

    uint8_t sp; // stack pointer

    uint16_t call_stack[STACK_SIZE];

    // lookup tables
    void (*instr_table[16])(struct CHIP8*, uint16_t);
    SubTablePtr sub_tables[16];

} CHIP8;

// init
CHIP8* init_chip8();

int load_rom(CHIP8 *chip8);

void set_register(CHIP8 *chip8, uint8_t registeridx, uint8_t value);
uint8_t get_register(CHIP8 *chip8, uint8_t registeridx);

void push_stack(CHIP8 *chip8);
void pop_stack(CHIP8 *chip8);

uint16_t fetch_opcode(CHIP8 *chip8);
void execute_instruction(CHIP8 *chip8, uint16_t opcode);

#endif


