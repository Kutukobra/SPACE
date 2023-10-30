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
const int offset = 1;
int GAME_WIDTH;
int GAME_HEIGHT;

Vector2 SCOREBOARD;
Image _desert;

Sound death;
Sound alhm;
Music wadimor;
int HIGHSCORE;
void Background();

// Snake (head) Controllable
Object Snake = {
    {0x60, 0xFF, 0x60, 0xFF}, // Color
    {0, 0}, // Position on grid
    {0, 0}, // Actual position
    {0, 1} // Velocity
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

    // Load sounds
    alhm = LoadSound("../assets/al.mp3");
    SetSoundPitch(alhm, 0.98);
    SetSoundVolume(alhm, 1.0);

    wadimor = LoadMusicStream("../assets/wadimor.mp3");
    SetMusicVolume(wadimor, 0.25);
    PlayMusicStream(wadimor);

    death = LoadSound("../assets/death.wav");

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

    // I firgot why but this is required
    QV2_add(&tails, Snake.pos);
    QV2_add(&tails, Snake.pos);
}

// Repeat Every Frame
void Update()
{
    // Update music
    UpdateMusicStream(wadimor);

    // Updating Snake Position
    Snake.rpos = Vector2Add(Snake.rpos, Snake.vel);

     // Snake bounds on grid
    if (Snake.rpos.x >= GRID_WIDTH) Snake.rpos.x = 0;
    if (Snake.rpos.x < 0) Snake.rpos.x = GRID_WIDTH - 1;
    if (Snake.rpos.y >= GRID_HEIGHT) Snake.rpos.y = 0;
    if (Snake.rpos.y < 0) Snake.rpos.y = GRID_HEIGHT - 1;

    // Rounding actual position for grid position
    Snake.pos = (Vector2){round(Snake.rpos.x), round(Snake.rpos.y)};

    // Check for collision with tail
    TransverseNodes(tails.head, CheckTailHead);

    // Check if Snake head is on the same position with apple on the grid
    if (Vector2Equals(Snake.pos, Apple.pos))
    {
        SCORE++;
        PlaySound(alhm);
        MoveRandom(&Apple);
    }

    // Storing tail as a queue of past grid positions
    if (!Vector2Equals(Snake.pos, pastpos))
    {
        QV2_add(&tails, Snake.pos);
    }

    // Removing Excess tails
    while (tails.length > SCORE)
    {
        QV2_pop(&tails);
    }

    // Record position so only push to tail if snake has moved grid
    pastpos = Snake.pos;
}

// Drawing
void Draw()
{
    // Background Function
    Background();

    // Head
    DrawObjectGrid(&Snake);

    // Tail
    TransverseNodes(tails.head, DrawTailGrid);

    // "Eyes"
    DrawRectangle(Snake.pos.x * gridSize + 5, Snake.pos.y * gridSize + 5, gridSize - 10, gridSize - 10, WHITE);
    DrawRectangle(Snake.pos.x * gridSize + 10, Snake.pos.y * gridSize + 10, gridSize - 20, gridSize - 20, BROWN);

    // Apple
    DrawObjectGrid(&Apple);
}

void Background()
{
    // Overall background 
    ClearBackground((Color){100, 100, 100, 100});
    
    // Score text 
    static char scoreText[20];
    sprintf(scoreText, "SCORE: %d\n", SCORE - 5);
    // Highscore text(pending functionality)
    static char hiScoreText[20];
    sprintf(hiScoreText, "HI: %d\n", HIGHSCORE);

    // Scoreboard
    DrawText(scoreText, SCOREBOARD.x, SCOREBOARD.y, 30, WHITE);
    DrawText(hiScoreText, SCOREBOARD.x, SCOREBOARD.y + 30, 30, WHITE);
    
    // Play grid
    DrawRectangle(0, 0, GAME_WIDTH, GAME_HEIGHT, (Color){0, 0, 0, 0x30});
    for (int i = 0; i < GRID_HEIGHT; i++)
    for (int j = 0; j < GRID_WIDTH; j++)
    {
        DrawRectangle(j * gridSize + offset, i * gridSize + offset, gridSize - offset, gridSize - offset, (Color){0, 0, 0, 100});
    }
}