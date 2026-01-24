#include <stdio.h>
#include <stdlib.h>

typedef int SLDataType;
#define INITSIZE 4

typedef struct SeqList
{
    SLDataType* data;
    int capacity;
    int size;
}SL;

//init and destroy
void SLInit(SL* sl)
{
    sl->data = (SLDataType*)malloc(INITSIZE * sizeof(SLDataType));
    sl->size = INITSIZE;
    sl->capacity = 0;
    if(!sl)
    {
        printf("malloc fail/n");
        return;
    }
}

void SLDestroy(SL* sl)
{
    free(sl->data);
}

void SLPrint(SL* sl)
{
    for(int i = 0; i < sl->capacity; i++)
    {
        printf("%d ", sl->data[i]);
    }
    printf("\n");
}

//enlarge the capacity
void SLCheckCapacity(SL* sl)
{
    sl->data = (SLDataType*)realloc(sl->data, sl->size * 2 * sizeof(SLDataType));
    sl->size = sl->size * 2;
}

//adjust elements
void push_back(SL* sl, SLDataType val)
{
    if(sl->capacity + 1 == sl->size)
    {
        SLCheckCapacity(sl);
    }
    sl->data[sl->capacity] = val;
    sl->capacity += 1;
}

void pop_back(SL* sl)
{
    sl->capacity--;
}

void push_front(SL* sl, SLDataType val)
{
    if(sl->capacity + 1 == sl->size)
    {
        SLCheckCapacity(sl);
    }
    int back = sl->capacity, front = back - 1;
    while(front >= 0)
    {
        sl->data[back--] = sl->data[front--];
    }
    sl->data[0] = val;
    sl->capacity++;
}

void pop_front(SL* sl)
{
    if(sl->capacity == 0)
    {
        return;
    }
    else if(sl->capacity == 1)
    {
        sl->capacity--;
    }
    else
    {
        int front = 0, back = front + 1;
        while(back < sl->capacity)
        {
            sl->data[front++] = sl->data[back++];
        }
    }
    sl->capacity--;
}

void SLInsert(SL* sl, int pos, SLDataType val)
{
    if(++sl->capacity == sl->size)
    {
        SLCheckCapacity(sl);
    }
    int back = sl->capacity, front = back - 1;
    while(front >= pos)
    {
        sl->data[back--] = sl->data[front--];
    }
    sl->data[back] = val;
}

void SLErase(SL *sl, int pos)
{
    if(sl->capacity == 0)
    {
        return;
    }
    else if(pos >= sl->capacity)
    {
        return;
    }
    else if(sl->capacity == 1)
    {
        sl->capacity--;
    }
    else
    {
        int front = pos, back = front + 1;
        while(back < sl->capacity)
        {
            sl->data[front++] = sl->data[back++];
        }
    }
    sl->capacity--;
}

bool SLFind(SL* sl, SLDataType val)
{
    for(int i = 0; i < sl->capacity; i++)
    {
        if(sl->data[i] == val)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    SL sl;
    SLInit(&sl);
    for(int i = 0; i < 10; i++)
    {   
        push_back(&sl, i);
    }
    SLPrint(&sl);
    pop_back(&sl);
    SLPrint(&sl);
    push_front(&sl, 10);
    SLPrint(&sl);
    pop_front(&sl);
    SLPrint(&sl);
    SLInsert(&sl, 2, 100);
    SLPrint(&sl);
    SLErase(&sl, 2);
    SLPrint(&sl);
    printf("the result of finding 8: %d\n", SLFind(&sl, 8));
    printf("the result of finding 100: %d\n", SLFind(&sl, 100));
    printf("the size of sl is %d, the capacity is %d\n", sl.size, sl.capacity);
    SLDestroy(&sl); return 0;
}
