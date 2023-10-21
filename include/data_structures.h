#ifndef DTS
#define DTS

#include <stdlib.h>
#include "raylib.h"

typedef struct
{
    Vector2 val;
    struct NodeV2* next;
} NodeV2;

NodeV2* NV2_Init(Vector2 val);

void NV2_Print(NodeV2* n);
void TransverseNodes(NodeV2* n, void (*f)(NodeV2* p));

typedef struct
{
    NodeV2* head;
    NodeV2* tail;
    int length;
} QueueV2;

void QV2_Print(QueueV2* q);
QueueV2* QV2_Init();

bool QV2_isEmpty(QueueV2* q);

void QV2_add(QueueV2* q, Vector2 val);

Vector2 QV2_pop(QueueV2* q);
#endif