#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "data_structures.h"

#define FPS 60
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1000

int main(void)
{
    srand(time(NULL));
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ULAR KADUT FIB");
    InitAudioDevice();
    SetTargetFPS(FPS);

    Setup();
    printf("SETUP COMPLETED!\n");
    while (!WindowShouldClose())
    {
        Inputs();

        Update();

        BeginDrawing();
        Draw();
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
    printf("WINDOW CLOSED!\n");
    return 0;
}