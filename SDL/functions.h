#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <stdio.h>
#include <stdlib.h>

int init(SDL_Window** window, SDL_Renderer** renderer, char* title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }

    *window = SDL_CreateWindow(
              title,
              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
              width, height,
              SDL_WINDOW_SHOWN
            );

    if (*window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(*renderer == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

static SDL_Event event;
Sint32 get_input(){
    while(SDL_PollEvent(&event)){
        switch( event.type ){
            case SDL_KEYDOWN:
                return event.key.keysym.sym;
                break;
            default:
                break;
        }
    }
    return 0;
}