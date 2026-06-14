#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int STDataType;
typedef struct stack stack;

#define INITSIZE 4

struct stack
{
    STDataType* data;
    int capacity;//当前容量
    int size;//总容量
};

void init(stack* st)
{
    st->data = (STDataType*)malloc(sizeof(STDataType) * INITSIZE);
    if(st->data == NULL)
    {
        perror("malloc");
        return;
    }
    st->capacity = 0;
    st->size = INITSIZE;
}

void destroy(stack* st)
{
    st->size = 0;
    st->capacity = 0;
    free(st->data);
}

void enlarge(stack* st)
{
    st->data = (STDataType*)realloc(st->data, sizeof(STDataType) * (st->size) * 2);
    st->size = st->size * 2;
}

void push(stack* st, STDataType val)
{
    if(st->capacity + 1 == st->size)
    {
        enlarge(st);       
    }
    printf("%d\n", st->capacity);
    st->data[st->capacity] = val;
    st->capacity++;
}

void print(stack* st)
{
    for(int i = 0; i < st->capacity; i++)
    {
        printf("%d ", st->data[i]);
    }
    printf("\n");
}

void pop(stack* st)
{
    if(st->capacity == 0)
    {
        printf("already empty\n");
        return;
    }
    st->capacity--;
}

STDataType top(stack* st)
{
    return st->data[st->capacity - 1];
}

int capacity(stack* st)
{
    return st->capacity;
}

int empty(stack* st)
{
    return st->capacity;
}

int main()
{
    stack st;
    init(&st);

    printf("%d\n", st.capacity);

    push(&st, 1);
    push(&st, 2);
    push(&st, 3);
    push(&st, 4);
    print(&st);

    pop(&st);
    print(&st);

    printf("element at the top: %d\n", top(&st));
    printf("numsber of the elements of the stack: %d\n", capacity(&st));

    printf("%d\n", st.capacity);

    destroy(&st);
    return 0;
}
