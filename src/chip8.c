#include "../include/chip8.h"
#include "../include/instructions.h"
#include <string.h>

CHIP8* init_chip8() {
    CHIP8 *chip8 = calloc(1, sizeof(CHIP8));
    chip8->pc = ROM_MEMORY_REGION_START;
    chip8->sp = 0;
    init_font(chip8);
    init_instruction_tables(chip8);
    return chip8;
}

void init_font(CHIP8 *chip8) {

    uint8_t font_data[] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    memcpy(chip8->memory + 50, font_data, sizeof(font_data));

}

int load_rom(CHIP8 *chip8) {
    FILE *rom = fopen("../c8roms/IBMLogo.ch8", "rb");
    if (rom == NULL) {
        printf("ROM could not be loaded...");
        return -1;
    }

    fread(&chip8->memory[ROM_MEMORY_REGION_START], sizeof(uint8_t),
            MEMORY_SIZE - ROM_MEMORY_REGION_START, rom);
    fclose(rom);

    return 0;
}

uint16_t fetch_opcode(CHIP8 *chip8) {
    uint8_t first_byte = chip8->memory[chip8->pc];
    uint8_t second_byte = chip8->memory[chip8->pc + 1];

    uint16_t opcode = (first_byte << 8) | second_byte;
    printf("OPCODE: %0x\r\n", opcode);
    return opcode;
}

void execute_instruction(CHIP8 *chip8, uint16_t opcode) {
    uint16_t first_nibble = (opcode & 0xF000) >> 12;
    uint16_t last_nibble = (opcode & 0x000F);

    if (chip8->sub_tables[first_nibble] != NULL) {
        (*(chip8->sub_tables[first_nibble]))[last_nibble](chip8, opcode);
    } else if (chip8->instr_table[first_nibble] != NULL) {
        chip8->instr_table[first_nibble](chip8, opcode);
    }

    chip8->pc += 2;

}

void set_register(CHIP8 *chip8, uint8_t registeridx, uint8_t value) {
    if (registeridx >=0 && registeridx <16) {
        chip8->v[registeridx] = value;
    }
}

uint8_t get_register(CHIP8 *chip8, uint8_t registeridx) {
    if (registeridx >=0 && registeridx <16) {
       return chip8->v[registeridx];
    }
    return 0;
}

void push_stack(CHIP8 *chip8) {
    if (chip8->sp < STACK_SIZE) {
        chip8->call_stack[chip8->sp] = chip8->pc;
        printf("pushed %0x onto stack, depth: %d\r\n", chip8->pc, chip8->sp);
        chip8->sp++;
    } // TODO: deal with overflows
}


void pop_stack(CHIP8 *chip8) {
    if (chip8->sp > 0) {
        chip8->sp--;
        chip8->pc = chip8->call_stack[chip8->sp];
        printf("popped %0x off stack, jumping to address: %0x\r\n", chip8->sp,
                chip8->pc);
    } // TODO: deal with underflows
}

