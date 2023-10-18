#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

#define GRID_SIZE 40
#define GRID_WIDTH  (GetScreenWidth()  / GRID_SIZE)
#define GRID_HEIGHT (GetScreenHeight() / GRID_SIZE)

// Game Object Struct
typedef struct GameObject
{
    Vector2 pos;
    Vector2 vel;
    Color color;
} Object;

// Snake Controllable
Object Snake = {
    {0, 0}, 
    {0, 0}, 
    {0x60, 0xF4, 0x60, 0xFF}
};

// Drawing Rectangles
const int OFFSET = 2;
void DrawObject (Object* a)
{
    DrawRectangle(a->pos.x * GRID_SIZE + OFFSET, a->pos.y * GRID_SIZE + OFFSET, GRID_SIZE -OFFSET, GRID_SIZE - OFFSET, a->color);
}


// Taking Inputs
const float SNAKE_SPEED = 1;
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

}

// Repeat Every Frame
void Update()
{
    // Updating Snake Position
    Snake.pos = Vector2Add(Snake.pos, Snake.vel);

    // 
    if (Snake.pos.x >= GRID_WIDTH) Snake.pos.x = 0;
    if (Snake.pos.x < 0) Snake.pos.x = GRID_WIDTH - 1;
    if (Snake.pos.y >= GRID_HEIGHT) Snake.pos.y = 0;
    if (Snake.pos.y < 0) Snake.pos.y = GRID_HEIGHT - 1;
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
}