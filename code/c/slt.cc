#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define SLTDataType int

typedef struct SListNode
{
    SLTDataType data;
    struct SListNode* next;
}SLTNode;

SLTNode* SLTBuyNode(SLTDataType x)
{
    SLTNode* newNode = (SLTNode*)malloc(sizeof(SLTNode));
    newNode->data = x;
    newNode->next = NULL; 
    return newNode;
}

void SLTPrint(SLTNode* head)
{
    SLTNode* cur = head;
    while(cur)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void SLTPushBack(SLTNode** pphead, SLTDataType val)
{
    assert(pphead != NULL);
    SLTNode* newNode = SLTBuyNode(val);
    if(*pphead == NULL)
    {
        *pphead = newNode;
    }
    else
    {
        SLTNode* ptail = *pphead;
        while(ptail->next)
        {
            ptail = ptail->next;
        }
        ptail->next = newNode;
    }
}

void SLTPushfFront(SLTNode** pphead, SLTDataType val)
{
    SLTNode* node = 
    if(*pphead == NULL)
    {
        
    }
}

int main()
{
    SLTNode* phead = NULL;
    SLTPushBack(&phead, 1);
    SLTPushBack(&phead, 2);
    SLTPushBack(&phead, 3);
    SLTPushBack(&phead, 4);

    SLTPrint(phead);
    return 0;
}
