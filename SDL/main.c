#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <time.h>
#include "functions.h"
#include "game.h"
#include <stdio.h>

int main(int argc, char* argv[]){
  srand((unsigned int) time(NULL));
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  
  if(init(&window, &renderer, TITLE, SCREEN_WIDTH, SCREEN_HEIGHT)) return 0;
  

  snake = (obj*) malloc(sizeof(obj) * snake_memory); head = &snake[0];
  head->x = (int) SCREEN_WIDTH/2.0; head->y = SCREEN_HEIGHT/2.0;
  food.x = R_POS(COLUMNS) * TILE_W; food.y = R_POS(ROWS) * TILE_H;

  while((input=get_input()) != SDLK_ESCAPE){
    draw(window, renderer);
    if(update()) break;
  }
  
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}