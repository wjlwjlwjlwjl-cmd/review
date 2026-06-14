#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define HDataType int

typedef struct heap
{
    HDataType* data;
    int size; //max size
    int capacity; //current size
}heap;

void heap_print(heap* hp)
{
    for(int i = 0; i < hp->capacity; i++)
    {
        printf("%d ", hp->data[i]);
    }
    printf("\n");
}

void AdjustUp(heap* hp, int child)
{
    int parent = (child - 1) / 2;
    while(parent >= 0)
    {
        if(hp->data[child] < hp->data[parent])
        {
            std::swap(hp->data[parent], hp->data[child]);
            child = parent;
            parent = (child - 1) / 2;;
        }
        else
        {
            break;
        }
    }
}

void AdjustDown(heap*hp, int parent, int n)
{
    printf("adjustdown\n");
    heap_print(hp);
    printf("the capacity is %d\n", n);
    int child = parent * 2 + 1;//assume the left is the smaller
    while(child < n)
    {
        if(child + 1 < n && hp->data[child] > hp->data[child + 1])
        {
            child++;
        }
        if(hp->data[parent] > hp->data[child])
        {
            std::swap(hp->data[parent], hp->data[child]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break;
        }
    }
}

void heap_init(heap* hp, HDataType* data, int sz)
{
    //small-root heap
    hp->data = data;
    hp->size = sz;
    hp->capacity = sz;

    //create the structure of the heap
    for(int i = (sz - 1 - 1) / 2; i >= 0; i--)
    {
        AdjustDown(hp, i, sz);
    }
}


void heap_destroy(heap* hp)
{
    free(hp->data);
    hp->capacity = 0;
    hp->size = 0;
}

void heap_push(heap* hp, HDataType x)
{
    if(hp->capacity == hp->size)
    {
        hp->data = (HDataType*)realloc(hp->data, hp->size * 2);
    }
    hp->data[hp->capacity] = x;
    hp->capacity += 1;
    AdjustUp(hp, hp->capacity - 1);
}

void heap_pop(heap* hp)
{
    std::swap(hp->data[0], hp->data[hp->capacity - 1]);
    hp->capacity--;
    heap_print(hp);

    AdjustDown(hp, 0, hp->capacity);
}

HDataType heap_top(heap* hp)
{
    return hp->data[0];
}

int heap_size(heap* hp)
{
    return hp->capacity;
}

int empty(heap* hp)
{
    return hp->size;
}

int main()
{
    heap heap;
    int* heap_data = (int*)malloc(sizeof(int) * 7);
    heap_data[0] = 9;
    heap_data[1] = 1;
    heap_data[2] = 3;
    heap_data[3] = 4;
    heap_data[4] = 2;
    heap_data[5] = 7;
    heap_data[6] = 8;

    heap_init(&heap, heap_data, 7);
    heap_print(&heap);

    heap_push(&heap, 5);
    heap_push(&heap, 1);
    heap_print(&heap);

    heap_pop(&heap);
    heap_print(&heap);

    heap_destroy(&heap);

    return 0;
}
