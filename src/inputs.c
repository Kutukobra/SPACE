#include "game_functions.h"

extern Object Snake;
// Taking Inputs
// Snake Speed
const float SNAKE_SPEED = 0.3;
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