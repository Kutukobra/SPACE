#include "raylib.h"
#include <stdio.h>
#include "Game.h"
#include "data_structures.h"

#define FPS 15
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ULAR KADUT FIB");
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
    printf("WINDOW CLOSED!\n");
    return 0;
}