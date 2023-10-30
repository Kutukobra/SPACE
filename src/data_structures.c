#include <stdlib.h>
#include "raylib.h"
#include <stdio.h>

// Node for linkedlist
typedef struct NodeV2
{
    Vector2 val;
    struct NodeV2 *next;
} NodeV2;

NodeV2* NV2_Init(Vector2 val)
{
    NodeV2* ret = (NodeV2*)malloc(sizeof(NodeV2));
    ret->val = val;
    ret->next = NULL;
    return ret;
}

void NV2_Print(NodeV2* n)
{
    printf("%lf %lf\n", n->val.x, n->val.y);
}

// Transverse a linked list and operate the function f
void TransverseNodes(NodeV2 *n, void (*f)(NodeV2 *p))
{
    NodeV2* i = n;
    while (i != NULL)
    {
        (*f)(i);
        i = i->next;
    }
}

// Queue as linked list 
// Insert at tail, pop at head
typedef struct QueueV2
{
    NodeV2* head;
    NodeV2* tail;
    int length;
} QueueV2;

void QV2_Print(QueueV2* q)
{
    TransverseNodes(q->head, NV2_Print);
}

QueueV2* QV2_Init()
{
    QueueV2* q = (QueueV2*)malloc(sizeof(QueueV2));
    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
    return q;
}

bool QV2_isEmpty(QueueV2* q)
{
    return q->head == NULL;
}

// Insert value to queue at tail as node
void QV2_add(QueueV2* q, Vector2 val)
{
    NodeV2* add = NV2_Init(val);
    if (QV2_isEmpty(q))
    {
        q->head = add;
    }
    else
    {
        q->tail->next = add;
    }
    q->tail = add;
    q->length++;
}

// Remove value at head
Vector2 QV2_pop(QueueV2* q)
{
    if (QV2_isEmpty(q))
    {
        printf("ERROR: TRIED TO POP AN EMPTY QUEUE\n");
        return (Vector2){-1, -1};
    }

    Vector2 ret = (q->head->val);
    NodeV2* tem = q->head;
    q->head = q->head->next;
    free(tem);
    q->length--;
    return ret;
}