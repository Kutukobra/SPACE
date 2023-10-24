#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "data_structures.h"

#define FPS 60
#define WINDOW_HEIGHT 801
#define WINDOW_WIDTH 961

FILE *_HIGHSCORE;
extern int HIGHSCORE;


int main(void)
{
    _HIGHSCORE = fopen("highscore.bin", "wb+");
    fread(&HIGHSCORE, sizeof(int), 1, _HIGHSCORE);
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
    fwrite(&HIGHSCORE, sizeof(int), 1, _HIGHSCORE);
    printf("WRITTEN TO FILE: %d\n", HIGHSCORE);
    fclose(_HIGHSCORE);
    return 0;
}