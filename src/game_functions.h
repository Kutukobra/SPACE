#ifndef GF
#define GF

#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "data_structures.h"

void Vector2Print(Vector2 *n);

// Game Object Struct: Color, position on grid, real floating position, velocity
typedef struct Object
{
    Color color;
    Vector2 pos;
    Vector2 rpos;
    Vector2 vel;
} Object;

void MoveRandom(Object *o);

// Drawing Rectangles
// Floor to fit grid
void DrawObjectGrid(Object *a);
void DrawTailGrid(NodeV2 *i);
// Check tail-head transversed
void CheckTailHead(NodeV2 *t);


#endif