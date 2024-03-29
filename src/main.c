#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>

#include "../include/chip8.h"
#include "../include/SDLHandler.h"

void render(SDL_State *sdl_state, CHIP8 *chip8) {

    SDL_SetRenderDrawColor(sdl_state->renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl_state->renderer);

    SDL_SetRenderDrawColor(sdl_state->renderer, 255, 0, 0, 255);
    for (int row = 0; row < SCREEN_HEIGHT; row++) {
       for (int col = 0; col < SCREEN_WIDTH; col++) {
           if (chip8->display[row][col] == 1) {

           SDL_Rect fillRect = {col * 10, row * 10, 10, 10 };
           SDL_RenderFillRect(sdl_state->renderer, &fillRect);
       }
       }
    }
    SDL_RenderPresent(sdl_state->renderer);
}

// TODO: Move to chip8.c?
void emulate_cycle(CHIP8 *chip8) {
    uint16_t opcode = fetch_opcode(chip8);
    execute_instruction(chip8, opcode);
}

void clean_up(CHIP8 *chip8, SDL_State *sdl_state) {
    printf("Cleaning up memory...");

    // Clean up SDL
    SDL_DestroyRenderer(sdl_state->renderer);
    SDL_DestroyWindow(sdl_state->window);
    SDL_Quit();

    // Free memory
    free(sdl_state);
    free(chip8);
}

void update(CHIP8 *chip8, SDL_State *sdl_state) {

}

int main() {

    CHIP8 *chip8;
    SDL_State *sdl_state;

    SDL_Event e;

    State current_state = INIT;

    while (current_state != HALT) {

        switch (current_state) {

            case INIT:
                printf("Initialising...\r\n");
                chip8 = init_chip8();
                sdl_state = init_sdl("Chip8", SCREEN_WIDTH * 10, SCREEN_HEIGHT * 10);
                if (chip8 != NULL && sdl_state != NULL) {
                    printf("Loading ROM into memory...\r\n");
                    load_rom(chip8);
                    printf("Loaded ROM successfully into memory.\r\n");
                    current_state = RUNNING;
                } else {
                    printf("Failed to initialise!\r\n");
                    current_state = HALT;
                }
                break;

            case RUNNING:
                current_state = sdl_handle_event(&e);
                emulate_cycle(chip8);
                render(sdl_state, chip8);
                SDL_Delay(300);
                break;

             case PAUSED:
                printf("Paused, not implemented\r\n");
                break;

            case HALT:
                printf("Received HALT signal...\r\n");
                clean_up(chip8, sdl_state);
                break;

            default:
                printf("ERROR: Unhandled state!\r\n");
                current_state = HALT;
                break;
        }
    }

    printf("HALTED\r\n");

    return 0;

}
