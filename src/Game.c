#include <stdio.h>  
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stdlib.h>

#include "data_structures.h"
#include "game_functions.h"
#include "inputs.h"

#define GRID_WIDTH  20
#define GRID_HEIGHT 20
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

    QV2_Init(&tails);

    MoveRandom(&Apple);
}

// Repeat Every Frame
void Update()
{
    UpdateMusicStream(wadimor);

    // Check for collision with tail
    TransverseNodes(tails.head, CheckTailHead);


    //QueueV2_Print(&tail);
    QV2_add(&tails, Snake.pos);

    // Removing Excess
    while (tails.length > SCORE)
    {
        QV2_pop(&tails);
    }

    // Updating Snake Position
    Snake.rpos = Vector2Add(Snake.rpos, Snake.vel);
    //printf("%f %f : %f %f\n", Snake.rpos.x , Snake.rpos.y, Snake.pos.x, Snake.pos.y);

    // Snake bounds on grid
    if (Snake.pos.x >= GRID_WIDTH) Snake.rpos.x = 0;
    if (Snake.pos.x < 0) Snake.rpos.x = GRID_WIDTH - 1;
    if (Snake.pos.y >= GRID_HEIGHT) Snake.rpos.y = 0;
    if (Snake.pos.y < 0) Snake.rpos.y = GRID_HEIGHT - 1;

    Snake.pos = (Vector2){round(Snake.rpos.x), round(Snake.rpos.y)};

    // Check if Snake head is on the same position with apple on the grid
    if (Vector2Equals(Snake.pos, Apple.pos))
    {
        SCORE++;
        PlaySound(alhm);
        MoveRandom(&Apple);
    }
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