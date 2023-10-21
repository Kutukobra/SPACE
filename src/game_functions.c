#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "data_structures.h"
// Game Object Struct: Color, position on grid, real floating position, velocity
typedef struct Object
{
    Color color;
    Vector2 pos;
    Vector2 rpos;
    Vector2 vel;
} Object;

extern Object Snake;
// Randomize Apple Position
void MoveRandom(Object* o)
{
    o->pos.x = (rand() % GetScreenWidth());
    o->pos.y = (rand() % GetScreenHeight());
}

extern const int gridSize, offset;
// Drawing Rectangles
// Floor to fit grid
void DrawObjectGrid(Object* a)
{
    DrawRectangle(a->pos.x * gridSize + offset, a->pos.y * gridSize + offset, gridSize - offset, gridSize - offset, a->color);
}

// Drawing Transversed Linkedlist
void DrawTailGrid(NodeV2* i)
{
    DrawRectangle(i->val.x * gridSize + offset, i->val.y * gridSize + offset, gridSize - offset, gridSize - offset, Snake.color);
}

extern int SCORE;
// Check tail-head transversed
void CheckTailHead(NodeV2* t)
{
    //printf("%.2f %.2f\n", t->val.x, t->val.y);
    if (Vector2Equals(t->val, Snake.pos))
    {
        printf("HIT: %f  %f\n", t->val.x, t->val.y);
        SCORE = 5;
    }
}