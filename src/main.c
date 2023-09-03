#include "../include/chip8.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    CHIP8 *chip8 = init_chip8();

    printf("Loading ROM into memory...\r\n");
    load_rom(chip8);
    printf("Loaded ROM successfully into memory.\r\n");

    while (chip8->pc < MEMORY_SIZE) {
        sleep(1); // so we can read instructions
        uint16_t opcode = fetch_opcode(chip8);
        execute_instruction(chip8, opcode);
    }

    free(chip8);

    return 0;

}
