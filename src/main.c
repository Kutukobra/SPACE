#include "raylib.h"
#include <stdio.h>
#include "Game.h"

#define FPS 15
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

int main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SNAKE, FAIZ IS A BIT GAY BTW SORRY");
    SetTargetFPS(FPS);

    Setup();
    while (!WindowShouldClose())
    {
        Inputs();

        Update();

        BeginDrawing();
        Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}