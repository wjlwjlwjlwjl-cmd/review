#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define SLTDataType int

typedef struct SListNode
{
    SLTDataType data;
    struct SListNode* next;
}SLTNode;

//封装一个产生新节点的函数
SLTNode* SLTBuyNode(SLTDataType x)
{
    SLTNode* newNode = (SLTNode*)malloc(sizeof(SLTNode));
    newNode->data = x;
    newNode->next = NULL; 
    return newNode;
}

void SLTPrint(SLTNode* head)
{
    if(head == NULL)
    {
        return;
    }
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

void SLTPushFront(SLTNode** pphead, SLTDataType val)
{
    assert(pphead != NULL);
    SLTNode* node = SLTBuyNode(val);
    if(*pphead == NULL)
    {
        *pphead = node;
    }
    else
    {
        node->next = *pphead;
        *pphead = node;
    }
}

void SLTPopFront(SLTNode** pphead)
{
    assert(pphead != NULL);
    if((*pphead)->next == NULL)
    {
        free(*pphead);
    }
    else
    {
        SLTNode* oldHead = (*pphead);
        *pphead = (*pphead)->next;
        free(oldHead);
    }
}

void SLTPopBack(SLTNode** pphead)
{
    assert(pphead != NULL);
    if((*pphead)->next == NULL)
    {
        free(*pphead);
    }
    else
    {
        SLTNode* ptail = *pphead;
        SLTNode* newTail = NULL;
        while(ptail->next)
        {
            newTail = ptail;
            ptail = ptail->next;
        }
        free(ptail);
        newTail->next = NULL;
    }
}

SLTNode* SLTFind(SLTNode* phead, SLTDataType x)
{
    assert(phead != NULL);
    SLTNode* cur = phead;
    while(cur)
    {
        if(cur->data == x)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void SLTInsert(SLTNode** pphead, int pos, int x)
{
    assert(pphead != NULL);
    SLTNode* newNode = SLTBuyNode(x);
    if((*pphead) == NULL)
    {
        *pphead = newNode;
    }
    else
    {
        SLTNode* cur = *pphead;
        SLTNode* prev = NULL;
        while(pos-- > 0)
        {
            prev = cur;
            cur = cur->next;
        }
        prev->next = newNode;
        newNode->next = cur;
    }
}

void SLTErase(SLTNode** pphead, int pos)
{
    assert(pphead != NULL);
    if((*pphead)->next == NULL)
    {
        free(*pphead);
    }
    else
    {
        SLTNode* prev = NULL;
        SLTNode* cur = *pphead;
        while(pos-- > 0)
        {
            prev = cur;
            cur = cur->next;
        }
        prev->next = cur->next;
        free(cur);
    }
}

void SLTInsertAfter(SLTNode** pphead, int pos, int val)
{
    SLTInsert(pphead, pos + 1, val);
}

void SLTEraseAfter(SLTNode** pphead, int pos)
{
    SLTErase(pphead, pos + 1);
}

void SLTDestroy(SLTNode** pphead)
{
    assert(pphead != NULL);
    SLTNode* cur = *pphead;
    while(cur)
    {
        SLTNode* prev = cur;
        cur = cur->next;
        printf("delete the node of %d\n", prev->data);
        free(prev);
    }
}

int main()
{
    SLTNode* phead = NULL;
    SLTPushBack(&phead, 1);
    SLTPushBack(&phead, 2);
    SLTPushBack(&phead, 3);
    SLTPushBack(&phead, 4);
    SLTPushFront(&phead, 10);
    SLTPopFront(&phead);

    SLTPrint(phead);
    SLTPopBack(&phead);
    // SLTPrint(phead);
    // printf("find 1: %d\n", SLTFind(phead, 1)->data);
    SLTInsert(&phead, 1, 100);
    SLTPrint(phead);
    SLTErase(&phead, 1);
    SLTPrint(phead);
    SLTInsertAfter(&phead, 1, 100);
    SLTPrint(phead);
    SLTEraseAfter(&phead, 1);
    SLTPrint(phead);
    SLTDestroy(&phead);
    //SLTPrint(phead);
    return 0;
}
