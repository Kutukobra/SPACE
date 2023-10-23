#include <stdio.h>  
#include "raylib.h"
#include "raymath.h"
#include <math.h>

#include "data_structures.h"
#include "game_functions.h"
#include "inputs.h"

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;
const int gridSize = 40;
const int offset = 2;

Sound alhm;
Music wadimor;
void Background();

// Snake (head) Controllable
Object Snake = {
    {0x60, 0xFF, 0x60, 0xFF},
    {0, 0}, 
    {0, 0},
    {0, 0}
};
int SCORE = 5;
Vector2 pastpos;

QueueV2 tails;

// Apple 
Object Apple = {
    {0xF4, 0x60, 0x60, 0xFF},
    {0, 0},
    {0, 0},
    {0, 0}
};

// Setting Up 
void Setup()
{
    alhm = LoadSound("../assets/al.mp3");
    SetSoundPitch(alhm, 0.98);
    SetSoundVolume(alhm, 1.3);

    wadimor = LoadMusicStream("../assets/wadimor.mp3");
    SetMusicVolume(wadimor, 0.25);
    PlayMusicStream(wadimor);

    // Initializing tails
    QV2_Init(&tails);

    // Apple Starting position
    MoveRandom(&Apple);

    // Snake Starting position
    MoveRandom(&Snake);
    Snake.rpos = Snake.pos;
    pastpos = Snake.pos;

    QV2_add(&tails, Snake.pos);
    QV2_add(&tails, Snake.pos);
}

// Repeat Every Frame
void Update()
{
    //UpdateMusicStream(wadimor);

    // Updating Snake Position
    Snake.rpos = Vector2Add(Snake.rpos, Snake.vel);

     // Snake bounds on grid
    if (Snake.rpos.x >= GRID_WIDTH) Snake.rpos.x = 0;
    if (Snake.rpos.x < 0) Snake.rpos.x = GRID_WIDTH - 1;
    if (Snake.rpos.y >= GRID_HEIGHT) Snake.rpos.y = 0;
    if (Snake.rpos.y < 0) Snake.rpos.y = GRID_HEIGHT - 1;

    // Rounding for grid
    Snake.pos = (Vector2){floor(Snake.rpos.x), floor(Snake.rpos.y)};

    //printf("%p\n", tails.head->next);
    // Check for collision with tail
    TransverseNodes(tails.head, CheckTailHead);

    // Check if Snake head is on the same position with apple on the grid
    if (Vector2Equals(Snake.pos, Apple.pos))
    {
        SCORE++;
        PlaySound(alhm);
        MoveRandom(&Apple);
    }


    if (!Vector2Equals(Snake.pos, pastpos))
    {
        QV2_add(&tails, Snake.pos);
    }

    // Removing Excess
    while (tails.length > SCORE)
    {
        QV2_pop(&tails);
    }
    pastpos = Snake.pos;
}

// Drawing
void Draw()
{
    Background();
    TransverseNodes(tails.head, DrawTailGrid);
    DrawObjectGrid(&Apple);
}

void Background()
{
    ClearBackground((Color){0x20, 0x20, 0x20, 0xFF});
    for (int i = 0; i < GRID_HEIGHT; i++)
    for (int j = 0; j < GRID_WIDTH; j++)
    {
        DrawRectangle(j * gridSize + offset, i * gridSize + offset, gridSize - offset, gridSize - offset, BLACK);
    }
    DrawObjectGrid(&Snake);
}