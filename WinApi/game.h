#pragma once
#define R_POS(UPP) (rand() % (UPP+1))

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

const wchar_t TITLE[] = L"Snake";

#define SNAKE_COLOR 0x00FF00
#define FOOD_COLOR 0x0000FF

unsigned long long snake_memory = 20, length = 1, input = 0;
obj* snake, *head, food;
short speed_x = 0, speed_y = 0;
BOOL paused = TRUE;
HBRUSH black, food_c, snake_c;
HANDLE heap;

#include "winhelper.h"

int update(){
    int i = 0;
    float prev_x=0, prev_y=0, s_prev_x=0, s_prev_y=0;
    process_input();

    prev_x = head->x; prev_y = head->y;
    head->x += speed_x; head->y += speed_y;

    if(head->x == food.x && head->y == food.y){
        if(length++ == snake_memory){
            snake = (obj*) HeapReAlloc(heap, 0, snake, sizeof(obj) * (snake_memory*=2)); head = &snake[0];
        }
        snake[length-1].x = snake[length-2].x - speed_x; snake[length-1].y = snake[length-2].y - speed_y;
        
        food.x = R_POS(COLUMNS-1) * TILE_W; food.y = R_POS(ROWS-1) * TILE_H;
    }
        
    if(head->x < 0 || head->x > (SCREEN_WIDTH - TILE_W) || head->y < 0 || head->y > (SCREEN_HEIGHT - TILE_H)){
        return 1;
    }

    if(!speed_x && !speed_y) return 0;

    for(i = 1; i < length; ++i) {
        if(head->x == snake[i].x && head->y == snake[i].y) return 1;
        s_prev_x = snake[i].x; s_prev_y = snake[i].y;
        snake[i].x = prev_x; snake[i].y = prev_y;
        prev_x = s_prev_x; prev_y = s_prev_y;
    }

    return 0;
}

RECT rect;
void draw_r(HDC hdc, obj object, HBRUSH color){
    rect.left = object.x; rect.top = object.y;
    rect.right = object.x+TILE_W; rect.bottom = object.y+TILE_H;
    FillRect(hdc, &rect, color);
}

void draw(HDC hdc){
    int i;
    for(i = 0; i < length; ++i)
        draw_r(hdc, snake[i], snake_c);
    draw_r(hdc, food, food_c);
}