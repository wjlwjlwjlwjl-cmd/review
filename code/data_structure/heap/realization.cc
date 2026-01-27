#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#define HDataType int
#define INITSIZE 4

typedef struct heap
{
    HDataType* data;
    int size; //max size
    int capacity; //current size
}heap;

void AdjustUp(heap* hp, int child)
{
    int parent = (child - 1) / 2;
    while(parent >= 0)
    {
        if(hp->data[child] < hp->data[parent])
        {
            std::swap(hp->data[child], hp->data[child]);
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
    int child = parent * 2 + 1;//assume the left is the smaller
    while(child < n)
    {
        printf("value of the child %d, the parent %d\n", child, parent);
        if(hp->data[child] > hp->data[child + 1])
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
        printf("parent %d adjust down\n", i);
        AdjustDown(hp, i, sz);
    }
}

void heap_print(heap* hp)
{
    for(int i = 0; i < hp->capacity; i++)
    {
        printf("%d ", hp->data[i]);
    }
    printf("\n");
}

void heap_destroy(heap* hp)
{
    free(hp->data);
    hp->capacity = 0;
    hp->size = 0;
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

    heap_destroy(&heap);

    return 0;
}
