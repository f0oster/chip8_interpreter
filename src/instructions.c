#include "../include/instructions.h"
#include "../include/chip8.h"
#include <string.h>

void init_instruction_tables(CHIP8 *chip8) {

    memset(chip8->instr_table, 0, sizeof(chip8->instr_table));
    memset(chip8->sub_tables, 0, sizeof(chip8->sub_tables));
    chip8->instr_table[0] = &instr_00EE; // RET sub
    chip8->instr_table[1] = &instr_1NNN; // JMP to NNN
    chip8->instr_table[2] = &instr_2NNN; // CALL NNN
    chip8->instr_table[3] = &instr_3xkk; // SE Vx == BYTE
    chip8->instr_table[4] = &instr_4xkk; // SNE Vx == BYTE
    chip8->instr_table[5] = &instr_5xy0; // SE Vx == Vy
    chip8->instr_table[6] = &instr_6xkk; // LD Vx, BYTE
    chip8->instr_table[7] = &instr_7xkk; // ADD Vx, BYTE
    chip8->instr_table[0xA] = &instr_aNNN; // LD i NNN

   static void (*instr_table_8xxx[16])(CHIP8*, uint16_t) = {
        &instr_8xy0,
        &instr_8xy1,
        &instr_8xy2,
        &instr_8xy3,
        &instr_8xy4,
        &instr_8xy5,
        &instr_8xy6,
        &instr_8xy7,
        &instr_8xyE,
        [9 ... 15] = NULL
    };

    chip8->sub_tables[8] = &instr_table_8xxx;
}

void instr_00EE(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for 00EE: RET sub\r\n");
    pop_stack(chip8);
    chip8->pc--;
}

void instr_1NNN(CHIP8 *chip8, uint16_t opcode ) {
    printf("executing instruction for 1nnn: JP addr\r\n");
    uint16_t address = (opcode & 0x0FFF);
    printf("jumping to %0x\r\n", address);
    chip8->pc = address;
    chip8->pc -= 2;
}

void instr_2NNN(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for 2nnn: CALL addr\r\n");
    uint16_t address = (opcode & 0x0FFF);
    printf("calling subroutine at address: %0x\r\n", address);
    push_stack(chip8);
    chip8->pc = address;
    chip8->pc -= 2;
}

void instr_3xkk(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for 3xkk: SE Vx, BYTE\r\n");
    uint8_t regidx = (opcode & 0x0F00) >> 8;
    uint8_t value = (opcode & 0x00FF);
    if (get_register(chip8, regidx) == value) {
        printf("SE Vx == kk, skipping 2 instructions\r\n");
        chip8->pc += 2;
    } else {
        printf("SE Vx != kk\r\n");
    }
}

void instr_4xkk(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for 4xkk: SNE Vx != BYTE\r\n");
    uint8_t regidx = (opcode & 0x0F00) >> 8;
    uint8_t value = (opcode & 0x00FF);
    if (get_register(chip8, regidx) != value) {
        printf("SNE Vx != kk, skipping 2 instructions\r\n");
        chip8->pc += 2;
    } else {
        printf("SE Vx == kk\r\n");
    }
}

void instr_5xy0(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for 5xy0: SE Vx == Vy\r\n");
    int regxidx = (opcode & 0x0F00) >> 8;
    int regyidx = (opcode & 0x00F0) >> 4;
    if (get_register(chip8, regxidx) == get_register(chip8, regyidx)) {
        printf("SE Vx == Vy, skipping 2 instructions\r\n");
    } else {
        printf("SE VX != kk\r\n");
    }
}

void instr_6xkk(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for 6xkk: LD Vx, BYTE\r\n");
    uint8_t regidx = (opcode & 0x0F00) >> 8;
    uint8_t value = (opcode & 0x00FF);
    printf("Setting reg V%d to: %0x\r\n", regidx, value);
    set_register(chip8, regidx, value);
}

void instr_7xkk(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for 7xkk: ADD Vx, BYTE \r\n");
    uint8_t regidx = (opcode & 0x0F00) >> 8;
    uint8_t value = (opcode & 0x00FF);
    uint16_t reg_value = get_register(chip8, regidx);
    printf("adding %d to V%d\r\n", value, regidx);
    reg_value += value;
    set_register(chip8, regidx, reg_value);
}

void instr_8xy0(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for 8xy0: LD Vx, Vy\r\n");
    uint8_t regxidx = (opcode & 0x0F00) >> 8;
    uint8_t regyidx = (opcode & 0x00F0) >> 4;
    uint8_t value = get_register(chip8, regyidx);
    printf("storing %d (from V%d) in V%d\r\n",value, regyidx, regxidx);
    set_register(chip8, regyidx, value);
}

void instr_8xy1(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for 8xy1: OR Vx, Vy \r\n");
    uint8_t regxidx = (opcode & 0x0F00) >> 8;
    uint8_t regyidx = (opcode & 0x00F0) >> 4;
    uint16_t regx_value = get_register(chip8, regxidx);
    uint16_t regy_value = get_register(chip8, regyidx);
    uint16_t bor_value = (regx_value | regy_value);
    printf("BOR %d, | %d = %d, storing in V%d\r\n", regx_value, regy_value,
            bor_value, regxidx);
    set_register(chip8, regxidx, bor_value);
}

void instr_8xy2(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for 8xy2: AND Vx, Vy \r\n");
    uint8_t regxidx = (opcode & 0x0F00) >> 8;
    uint8_t regyidx = (opcode & 0x00F0) >> 4;
    uint16_t regx_value = get_register(chip8, regxidx);
    uint16_t regy_value = get_register(chip8, regyidx);
    uint16_t band_value = (regx_value & regy_value);
    printf("BOR %d, | %d = %d, storing in V%d\r\n", regx_value, regy_value,
           band_value, regxidx);
    set_register(chip8, regxidx, band_value);


}

void instr_8xy3(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for \r\n");
}

void instr_8xy4(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for \r\n");
}

void instr_8xy5(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for \r\n");
}

void instr_8xy6(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for \r\n");
}

void instr_8xy7(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for \r\n");
}

void instr_8xyE(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for \r\n");
}

void instr_aNNN(CHIP8 *chip8, uint16_t opcode) {
    printf("executing instruction for annn: LD i, addr \r\n");
    uint16_t address = (opcode & 0x0FFF);
    printf("LD i, addr: %0x\r\n", address);
    chip8->i = address;
}
