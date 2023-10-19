#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "data_structures.h"

#define FPS 60
#define WINDOW_HEIGHT 801
#define WINDOW_WIDTH 801

int main(void)
{
    srand(time(NULL));
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ULAR KADUT SASTRA ARAB");
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