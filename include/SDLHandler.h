#ifndef SDLHANDLER_H
#define SDLHANDLER_H

#include "SDL2/SDL.h"
#include "../include/StateMachine.h"

typedef struct SDL_State {
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_State;

SDL_State *init_sdl(char *window_name, int32_t, int32_t);

State  sdl_handle_event(SDL_Event *e);

#endif
