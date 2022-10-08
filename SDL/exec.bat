@echo off
REM gcc main.c -O3 -Wall -Wextra -pedantic -Werror -Wconversion -std=c99 -o tests.exe
REM gcc main.c -O3 -Wall -Wextra -pedantic -Wconversion -I%SDL2_DIR%\include -L%SDL2_DIR%\lib -lSDL2 -std=c99 -o tests.exe
gcc main.c -O3 -Wall -I%SDL2_DIR%\include -L%SDL2_DIR%\lib -lSDL2 -mwindows -o snake.exe
