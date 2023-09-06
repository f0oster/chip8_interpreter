#include "../include/SDLHandler.h"
#include "../include/StateMachine.h"

SDL_State *init_sdl(char *window_name, int32_t width, int32_t height) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow(window_name,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height,
                                          SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_State *sdl_state = malloc(sizeof(SDL_State));
    sdl_state->window = window;
    sdl_state->renderer = renderer;

    return sdl_state;

}

State sdl_handle_event(SDL_Event *e) {
    while (SDL_PollEvent(e) != 0) {
        if (e->type == SDL_QUIT) {
            printf("SDL_QUIT fired\r\n");
            return HALT;
        }
    }
    return RUNNING;
}
