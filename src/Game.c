#include <stdio.h>  
#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stdlib.h>

#include "data_structures.h"

#define GRID_SIZE 40
#define GRID_WIDTH  20
#define GRID_HEIGHT 20
const int OFFSET = 2;

Sound alhm;

// Returns true if 2 Vector2 are equal
bool isSameVector2 (Vector2 a, Vector2 b)
{
    return (a.x == b.x && a.y == b.y);
}

// Game Object Struct: Color, position on grid, real floating position, velocity
typedef struct GameObject
{
    Color color;
    Vector2 pos;
    Vector2 rpos;
    Vector2 vel;
} Object;

// Snake (head) Controllable
Object Snake = {
    {0x60, 0xF4, 0x60, 0xFF},
    {0, 0}, 
    {0, 0},
    {0, 0}
};
int score = 5;
QueueV2 tail;

// Apple 
Object Apple = {
    {0xF4, 0x60, 0x60, 0xFF},
    {0, 0},
    {0, 0},
    {0, 0}
};

// Randomize Apple Position
void MoveApple()
{
    Apple.pos.x = (rand() % GRID_WIDTH);
    Apple.pos.y = (rand() % GRID_HEIGHT);
}

// Drawing Transversed Linkedlist
void DrawTail (NodeV2* i)
{
    DrawRectangle(i->val.x * GRID_SIZE + OFFSET, i->val.y * GRID_SIZE + OFFSET, GRID_SIZE - OFFSET, GRID_SIZE - OFFSET, Snake.color);
}

// Drawing Rectangles
// Floor to fit grid
void DrawObject (Object* a)
{
    DrawRectangle(a->pos.x * GRID_SIZE + OFFSET, a->pos.y * GRID_SIZE + OFFSET, GRID_SIZE -OFFSET, GRID_SIZE - OFFSET, a->color);
}

// Taking Inputs
const float SNAKE_SPEED = 0.25;
void Inputs()
{
    static int LastKeyPressed = 0;
    if (IsKeyPressed(KEY_UP) && LastKeyPressed != KEY_DOWN)
    {
        LastKeyPressed = KEY_UP;
        Snake.vel = (Vector2){0, -SNAKE_SPEED};
    }

    if (IsKeyPressed(KEY_DOWN) && LastKeyPressed != KEY_UP)
    {
        LastKeyPressed = KEY_DOWN;
        Snake.vel = (Vector2){0, SNAKE_SPEED};
    }

    if (IsKeyPressed(KEY_LEFT) && LastKeyPressed != KEY_RIGHT)
    {
        LastKeyPressed = KEY_LEFT;
        Snake.vel = (Vector2){-SNAKE_SPEED, 0};
    }

    if (IsKeyPressed(KEY_RIGHT) && LastKeyPressed != KEY_LEFT)
    {
        LastKeyPressed = KEY_RIGHT;
        Snake.vel = (Vector2){SNAKE_SPEED, 0};
    }
}

// Setting Up 
void Setup()
{
    alhm = LoadSound("../assets/al.mp3");
    QueueV2_Init(&tail);
    MoveApple();
}

// Repeat Every Frame
void Update()
{
    // Removing Excess
    while (tail.length > (score / SNAKE_SPEED))
    {
        QueueV2_pop(&tail);
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
    if (isSameVector2(Snake.pos, Apple.pos))
    {
        score++;
        PlaySound(alhm);
        MoveApple();
    }
    
    // Adding Length
    QueueV2_add(&tail, (Vector2){Snake.pos.x, Snake.pos.y});
}

// Drawing
void Draw()
{
    ClearBackground((Color){0x20, 0x20, 0x20, 0xFF});
    for (int i = 0; i < GRID_HEIGHT; i++)
    for (int j = 0; j < GRID_WIDTH; j++)
    {
        DrawRectangle(j * GRID_SIZE + OFFSET, i * GRID_SIZE + OFFSET, GRID_SIZE - OFFSET, GRID_SIZE - OFFSET, BLACK);
    }
    DrawObject(&Snake);
    TransverseNodes(tail.head, DrawTail);
    DrawObject(&Apple);
}