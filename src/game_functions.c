#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "data_structures.h"

// Defined in Game.c
extern const int gridSize, offset, GRID_WIDTH, GRID_HEIGHT;
extern int HIGHSCORE, SCORE;
extern Sound death;

// Printing Vector2
void Vector2Print(Vector2* n)
{
    printf("%f %f\n", n->x, n->y);
}

// Game Object Struct: Color, position on grid, real floating position, velocity
typedef struct Object
{
    Color color;
    Vector2 pos;
    Vector2 rpos;
    Vector2 vel;
} Object;

// Randomize Object Position, used for apple reset
void MoveRandom(Object *o)
{
    o->pos.x = (rand() % GRID_WIDTH);
    o->pos.y = (rand() % GRID_HEIGHT);
}

// Snake death function
extern Object Snake;
void Die()
{
    // Var SCORE is actually the tail length, default to 5
    if (SCORE > HIGHSCORE) HIGHSCORE = SCORE - 5;
    
    SCORE = 5;
    PlaySound(death);

    // Return to position (optional)
    // Snake.rpos = (Vector2){20, 20};
}

// Drawing as Grids
void DrawObjectGrid(Object *a)
{
    DrawRectangle(a->pos.x * gridSize + offset, a->pos.y * gridSize + offset, gridSize - offset, gridSize - offset, a->color);
}

// Drawing Transversed Tail Linkedlist
void DrawTailGrid(NodeV2 *i)
{
    DrawRectangle(i->val.x * gridSize + offset, i->val.y * gridSize + offset, gridSize - offset, gridSize - offset, Snake.color);
}

// Check tail-head transversed, if same then death
void CheckTailHead(NodeV2 *t)
{
    if (Vector2Equals(t->val, Snake.pos) && !(t->next == NULL))
    {
        Die();
    }
}