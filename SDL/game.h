#ifndef __GAME__
#define __GAME__

#include <SDL2/SDL.h>

#define R_POS(UPP) (rand() % (UPP + 1)) 

typedef struct object {
    float x, y;
} obj;

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define ROWS 60
#define COLUMNS 60

#define TILE_W SCREEN_WIDTH / COLUMNS
#define TILE_H SCREEN_HEIGHT / ROWS

#define SPEED_X TILE_W
#define SPEED_Y TILE_H

#define TITLE "Snake"

#define SNAKE_COLOR 0, 255, 0
#define FOOD_COLOR 255, 0, 0

unsigned long long snake_memory = 20, length = 1;
float prev_x, prev_y, s_prev_x, s_prev_y;
Sint32 input;
obj* snake, *head, food;
short speed_x = 0, speed_y = 0;

int update(void){
    int i;
    switch(input){
        case SDLK_w:
        case SDLK_UP:
            if(speed_y == SPEED_Y) break;
            speed_x = 0; speed_y = -SPEED_Y;
            break;
        case SDLK_a:
        case SDLK_LEFT:
            if(speed_x == SPEED_X) break;
            speed_x = -SPEED_X; speed_y = 0;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            if(speed_y == -SPEED_Y) break;
            speed_x = 0; speed_y = SPEED_Y;
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            if(speed_x == -SPEED_X) break;
            speed_x = SPEED_X; speed_y = 0;
            break;
        default:
            break;
    }

    prev_x = head->x; prev_y = head->y;
    head->x += speed_x; head->y += speed_y;

    if(head->x == food.x && head->y == food.y){
        if(length++ == snake_memory){
            snake = (obj*) realloc(snake, sizeof(obj) * (snake_memory*=2)); head = &snake[0];
        }
        snake[length-1].x = snake[length-2].x - speed_x; snake[length-1].y = snake[length-2].y - speed_y;
        food.x = R_POS(COLUMNS) * TILE_W; food.y = R_POS(ROWS) * TILE_H;
    }
    
    for(i = 1; i < length; ++i) {
        if(head->x == snake[i].x && head->y == snake[i].y) return 1;
        s_prev_x = snake[i].x; s_prev_y = snake[i].y;
        snake[i].x = prev_x; snake[i].y = prev_y;
        prev_x = s_prev_x; prev_y = s_prev_y;
    }

    if(head->x < 0 || head->x > (SCREEN_WIDTH - TILE_H) || head->y < 0 || head->y > (SCREEN_HEIGHT-TILE_W))
        return 1;
    return 0;
}

void draw(SDL_Window* window, SDL_Renderer* renderer){
    int i;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, SNAKE_COLOR, 255);
    SDL_Rect rect = {0, 0, TILE_W, TILE_H};
    for(i=0; i < length; ++i){
        rect.x = snake[i].x; rect.y = snake[i].y;
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, FOOD_COLOR, 255);
    rect.x = food.x; rect.y = food.y;
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    rect.w = (int) TILE_W/5; rect.h = (int) TILE_W/5;
    rect.x = head->x+2; rect.y = head->y+2; 
    SDL_RenderFillRect(renderer, &rect);
    rect.x = head->x+6; rect.y = head->y+2; 
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
    SDL_Delay(100);
}

#endif