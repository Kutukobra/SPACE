#include <stdlib.h>
#include "raylib.h"
#include <stdio.h>

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

void QueueV2_Init(QueueV2* q)
{
    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
}

void QueueV2_add(QueueV2* q, Vector2 val)
{
    NodeV2* add = malloc(sizeof(NodeV2));
    add->val = val;
    add->next = NULL;
    if (q->head == NULL)
    {
        q->head = add;
    }
    if (q->tail != NULL)
    {
        q->tail->next = add;
    }
    q->tail = add;
    q->length++;
}

Vector2 QueueV2_pop(QueueV2* q)
{
    if (q->length <= 0)
    {
        return (Vector2){1, 0};
    }

    Vector2 ret = (q->head->val);
    NodeV2* rem = q->head;
    q->head = q->head->next;
    free(rem);
    q->length--;
    return ret;
}