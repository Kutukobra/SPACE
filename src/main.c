#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Game.h"
#include "data_structures.h"

#define FPS 60
#define WINDOW_HEIGHT 801
#define WINDOW_WIDTH 961

// Highscore bin file to store highscore
FILE *_HIGHSCORE;

// Highscore, modified at Game.c
extern int HIGHSCORE;


int main(void)
{
    // Open highscore bin
    _HIGHSCORE = fopen("../assets/highscore.bin", "rb+");
    // Reading from bin, past high score (pending)
    fread(&HIGHSCORE, sizeof(int), 1, _HIGHSCORE);
    printf("LOADED HIGHSCORE: %d\n", HIGHSCORE);

    // Init random function
    srand(time(NULL));
    
    // Init raylib functionalities
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ULAR KADUT SASTRA ARAB");
    InitAudioDevice();
    SetTargetFPS(FPS);

    // Executed before loop
    Setup();
    printf("SETUP COMPLETED!\n");
    
    // Game loop
    while (!WindowShouldClose())
    {
        // Inputs
        Inputs();

        // Looped block
        Update();

        // Drawing block
        BeginDrawing();
        Draw();
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
    printf("WINDOW CLOSED!\n");

    // Update highscore bin (it works, but everything else about this doesn't)
    fwrite(&HIGHSCORE, sizeof(int), 1, _HIGHSCORE);
    printf("WRITTEN TO FILE: %d\n", HIGHSCORE);
    fclose(_HIGHSCORE);
    return 0;
}