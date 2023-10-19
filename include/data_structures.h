#ifndef DTS
#define DTS

#include "raylib.h"

typedef struct NodeV2
{
    Vector2 val;
    struct NodeV2* next;
} NodeV2;

typedef struct QueueV2
{
    NodeV2* head;
    NodeV2* tail;
    int length;
} QueueV2, QV2;

void QueueV2_add(QueueV2* q, Vector2 val);
Vector2 QueueV2_pop(QueueV2* q);

#endif