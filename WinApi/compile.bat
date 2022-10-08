@echo off
cls
REM -nostdlib -lkernel32 -luser32 -lucrt
C:\Users\giuse\Downloads\Downloads\gcc\bin\x86_64-w64-mingw32-gcc.exe -Wall -fno-math-errno -municode .\main.c -s -static -o snake.exe -lgdi32 -Oz -ffunction-sections -fdata-sections -Wl,--gc-sections -flto -ftree-vectorize -funroll-all-loops
REM C:\Users\giuse\Downloads\Downloads\gcc\bin\x86_64-w64-mingw32-gcc.exe -Wall -fno-math-errno -municode .\main.c -s -static -o snake.exe -lgdi32 -Oz -ffunction-sections -fdata-sections -Wl,--gc-sections,-ewWinMain -flto -ftree-vectorize -funroll-all-loops -nostdlib -luser32 -lucrt -lkernel32 