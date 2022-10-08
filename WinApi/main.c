#include <windows.h>
#include <time.h>
#include "winhelper.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow){
    srand((unsigned int) time(NULL)); 

    HWND window = create_window(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
    if(window == NULL) return EXIT_FAILURE;
    HANDLE heap = GetProcessHeap();

    snake = (obj*) HeapAlloc(heap, 0, sizeof(obj) * snake_memory); head = &snake[0];
    head->x = (int) SCREEN_WIDTH/2.0; head->y = SCREEN_HEIGHT/2.0;
    food.x = R_POS(COLUMNS) * TILE_W; food.y = R_POS(ROWS) * TILE_H;

    snake_c = CreateSolidBrush(SNAKE_COLOR);
    food_c = CreateSolidBrush(FOOD_COLOR);
    black = CreateSolidBrush(0x000000);

    MSG msg;
    SetTimer(window, 0, 100, NULL);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return EXIT_SUCCESS;
}
