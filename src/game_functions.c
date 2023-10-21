#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "data_structures.h"

extern const int gridSize, offset, GRID_WIDTH, GRID_HEIGHT;

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

extern Object Snake;
// Randomize Apple Position
void MoveRandom(Object *o)
{
    o->pos.x = (rand() % GRID_WIDTH);
    o->pos.y = (rand() % GRID_HEIGHT);
}
// Drawing Rectangles
// Floor to fit grid
void DrawObjectGrid(Object *a)
{
    DrawRectangle(a->pos.x * gridSize + offset, a->pos.y * gridSize + offset, gridSize - offset, gridSize - offset, a->color);
}

// Drawing Transversed Linkedlist
void DrawTailGrid(NodeV2 *i)
{
    DrawRectangle(i->val.x * gridSize + offset, i->val.y * gridSize + offset, gridSize - offset, gridSize - offset, Snake.color);
}

extern int SCORE;
// Check tail-head transversed
void CheckTailHead(NodeV2 *t)
{
    //printf("%.2f %.2f\n", t->val.x, t->val.y);
    if (Vector2Equals(t->val, Snake.pos) && !(t->next == NULL))
    {
        printf("HIT:\n");
        SCORE = 5;
    }
}