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

void QueueV2_add(QueueV2* q, Vector2 val)
{
    printf("Adding...\n");
    //NodeV2* add = (NodeV2*)malloc(sizeof(NodeV2));
    //q->tail = (q->tail->next = add);
    q->length++;
    printf("Added\n");
}

Vector2 QueueV2_pop(QueueV2* q)
{
    Vector2 ret = (q->head->val);
    NodeV2* temp = q->head;
    q->head = q->head->next;
    q->length--;
    free(temp);
    return ret;
}