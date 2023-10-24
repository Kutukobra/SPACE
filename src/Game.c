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
int GAME_WIDTH;
int GAME_HEIGHT;

Vector2 SCOREBOARD;
Image _desert;
Texture2D desert;
Sound alhm;
Music wadimor;
extern FILE *_HIGHSCORE;
int HIGHSCORE;
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

void Inits()
{
    // Init Game window size
    GAME_WIDTH = GRID_WIDTH * gridSize;
    GAME_HEIGHT = GRID_HEIGHT * gridSize;

    // Init Scoreboard position
    SCOREBOARD = (Vector2){(float)(GAME_WIDTH + 6), (float)(300)};

    alhm = LoadSound("../assets/al.mp3");
    SetSoundPitch(alhm, 0.98);
    SetSoundVolume(alhm, 1.3);

    wadimor = LoadMusicStream("../assets/wadimor.mp3");
    SetMusicVolume(wadimor, 0.25);
    PlayMusicStream(wadimor);

    _desert = LoadImage("../assets/desert.png");
    ImageResize(&_desert, GAME_WIDTH, GAME_HEIGHT);
    desert = LoadTextureFromImage(_desert);
    UnloadImage(_desert);

    // Initializing tails
    QV2_Init(&tails);
}

// Setting Up 
void Setup()
{
    Inits();

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
    DrawObjectGrid(&Snake);
    TransverseNodes(tails.head, DrawTailGrid);
    DrawObjectGrid(&Apple);
}

void Background()
{
    // Overall background 
    ClearBackground(GRAY);
    
    static char scoreText[20];
    sprintf(scoreText, "SCORE: %d\n", SCORE - 5);

    static char hiScoreText[20];
    sprintf(hiScoreText, "HI: %d\n", HIGHSCORE);
    // Scoreboard
    DrawText(scoreText, SCOREBOARD.x, SCOREBOARD.y, 30, WHITE);
    DrawText(hiScoreText, SCOREBOARD.x, SCOREBOARD.y + 30, 30, WHITE);
    
    DrawTexture(desert, 0, 0, WHITE);
    // Play grid (Darkened)
    //DrawRectangle(0, 0, GAME_WIDTH, GAME_HEIGHT, (Color){0, 0, 0, 0x30});
    for (int i = 0; i < GRID_HEIGHT; i++)
    for (int j = 0; j < GRID_WIDTH; j++)
    {
        //DrawRectangle(j * gridSize + offset, i * gridSize + offset, gridSize - offset, gridSize - offset, (Color){0, 0, 0, 0x30});
    }
}