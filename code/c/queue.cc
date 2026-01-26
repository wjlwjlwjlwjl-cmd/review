#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int QDataType;

typedef struct QueueNode{
    struct QueueNode* pnext;
    QDataType val;
}QNode;

typedef struct Queue{
    QNode* front;
    QNode* rear;
    int size;
}Queue;

QNode* BuyNode(QDataType val)
{
    QNode* newNode = (QNode*)malloc(sizeof(QNode));
    newNode->pnext = NULL;
    newNode->val = val;
    return newNode;
}

void init(Queue* queue)
{
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

void destroy(Queue* queue)
{
    if(queue->front == NULL)
    {
        return;
    }
    QNode* prev = NULL;
    QNode* cur = queue->front;
    while(cur)
    {
        prev = cur;
        cur = cur->pnext;
        free(prev);
    }
}

void push(Queue* queue, int val)
{
    QNode* newNode = BuyNode(val);
    if(queue->front == NULL)
    {
        queue->front = queue->rear = newNode;
        return;
    }
    else
    {
        queue->rear->pnext = newNode;
        queue->rear = queue->rear->pnext;
    }
}

void print(Queue* queue)
{
    QNode* cur = queue->front;
    while(cur)
    {
        printf("%d ", cur->val);
        cur = cur->pnext;
    }
    printf("\n");
}

void pop(Queue* queue)
{
    if(queue->front == NULL)
    {
        return;
    }
    else
    {
        QNode* head = queue->front;
        queue->front = queue->front->pnext;
        free(head);
    }
}

QDataType front(Queue* queue)
{
    return queue->front->val;
}

QDataType back(Queue* queue)
{
    return queue->rear->val;
}

int size(Queue* queue)
{
    int ret = 0;
    QNode* cur = queue->front;
    while(cur)
    {
        ret++;
        cur = cur->pnext;
    }
    return ret;
}

int empty(Queue* queue)
{
    return size(queue);
}

int main()
{
    Queue queue;
    init(&queue);
    if(!empty(&queue))
    {
        printf("empty!\n");
    }

    push(&queue, 1);
    push(&queue, 2);
    push(&queue, 3);
    push(&queue, 4);
    print(&queue);

    pop(&queue);
    print(&queue);

    printf("elements at the front: %d\n", front(&queue));
    printf("elements at the back: %d\n", back(&queue));
    printf("number of the elements: %d\n", size(&queue));

    destroy(&queue);
    return 0;
}
