#include <stdlib.h>
#include "raylib.h"

struct NodeV2
{
    Vector2 val;
    NodeV2* next;
}*head = NULL;
typedef struct NodeV2 NodeV2;

typedef struct QueueV2
{
    NodeV2* head;
    NodeV2* tail;
} QueueV2, QV2;

void QueueV2_add(QueueV2* q, Vector2 val)
{
    NodeV2* add = (NodeV2*)malloc(sizeof(NodeV2));
    q->tail = q->tail->next = add;
}

Vector2 QueueV2_pop(QueueV2* q)
{
    Vector2 ret = (q->head->val);
    NodeV2* temp = q->head;
    if (q->head->next != NULL)
    {
        q->head = q->head->next;
    }
    free(temp);
}