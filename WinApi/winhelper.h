#pragma once

#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44
#define VK_P 0x50
void process_input();
#include <windows.h>
#include "game.h"

RECT center_window(HWND parent_window, int width, int height){
    RECT rect;
    GetClientRect(parent_window, &rect);
    rect.left = (rect.right/2) - (width/2);
    rect.top = (rect.bottom/2) - (height/2);
    return rect;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    
    switch (uMsg) {
        case WM_PAINT:{
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, black);

            draw(hdc);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_TIMER:{
            if(update()) goto destroy;
            InvalidateRect(hwnd, NULL, TRUE); 
            return 0;
        }
        case WM_KEYDOWN: {
            switch(wParam){
                case VK_W:
                case VK_UP:
                case VK_A:
                case VK_LEFT:
                case VK_S:
                case VK_DOWN:
                case VK_D:
                case VK_RIGHT:
                case VK_PAUSE:
                case VK_P:
                    input = wParam;
                    return 0;
                case VK_ESCAPE:
                    goto destroy;
            }
        }
        case WM_CREATE:
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    destroy:
        HeapFree(heap, 0, snake);
        PostQuitMessage(0);
        return 0;
}

int last_sx = 0, last_sy = 0;
void process_input(){
    switch(input) {
        case VK_W:
        case VK_UP:
            if(paused || speed_y == SPEED_Y) break;;
            speed_x = 0; speed_y = -SPEED_Y;
            break;;
        case VK_A:
        case VK_LEFT:
            if(paused || speed_x == SPEED_X) break;;
            speed_x = -SPEED_X; speed_y = 0;
            break;;
        case VK_S:
        case VK_DOWN:
            if(paused || speed_y == -SPEED_Y) break;;
            speed_x = 0; speed_y = SPEED_Y;
            break;;
        case VK_D:
        case VK_RIGHT:
            if(paused || speed_x == -SPEED_X) break;;
            speed_x = SPEED_X; speed_y = 0;
            break;
        case VK_PAUSE:
        case VK_P:
            if(paused){
                speed_x=last_sx; speed_y = last_sy;
            }else{
                last_sx = speed_x; last_sy = speed_y;
                speed_x = 0; speed_y = 0;
            }
            paused=!paused;
            break;
        default: 
            break;
    }
    input = 0;
}

HWND create_window(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
    RECT center = center_window(GetDesktopWindow(), SCREEN_WIDTH, SCREEN_HEIGHT);

    WNDCLASS wc = { 
        .lpfnWndProc = WindowProc,
        .hInstance = hInstance,
        .lpszClassName = TITLE 
    };
    if(!RegisterClass(&wc)) return NULL;

    HWND hwnd = CreateWindowEx(
        0, TITLE, TITLE, WS_BORDER,            
        (center.right/2) - (SCREEN_WIDTH/2), (center.bottom/2) - (SCREEN_HEIGHT/2), 
        SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) return NULL;
    SetWindowLong(hwnd, GWL_STYLE, 0);
    ShowWindow(hwnd, nCmdShow);
    return hwnd;  
}