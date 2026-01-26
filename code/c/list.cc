#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int SLDataType;

typedef struct ListNode
{
    struct ListNode* prev;
    struct ListNode* next;
    SLDataType data;
}ListNode;

ListNode* BuyNode(SLDataType x)
{
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if(newNode == NULL)
    {
        perror("malloc");
        return NULL;
    }
    newNode->data = x;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

//带有哨兵位
ListNode* Init()
{
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    if(head == NULL)
    {
        perror("malloc");
        return NULL;
    }
    head->prev = NULL;
    head->next = NULL;
    return head;
}

void Destroy(ListNode* phead)
{
    ListNode* cur = phead;
    ListNode* prev = NULL;
    while(cur)
    {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
}

void Print(ListNode* phead)
{
    ListNode* cur = phead->next;
    while(cur)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

bool Empty(ListNode* phead)
{
    if(phead->next == NULL)
    {
        return true;
    }
    return false;
}

void push_back(ListNode* phead, int val)
{
    ListNode* newNode = BuyNode(val);
    if(phead->next == NULL)
    {
        phead->next = newNode;
        return;
    }
    else
    {
        ListNode* cur = phead->next;
        while(cur->next)
        {
            cur = cur->next;
        }
        cur->next = newNode;
        newNode->prev = cur;
    }
}

void pop_back(ListNode* phead)
{
    if(phead->next == NULL)
    {
        return;
    }
    ListNode* prev = NULL;
    ListNode* cur = phead->next;
    while(cur->next)
    {
        prev = cur;
        cur = cur->next;
    }
    prev->next = NULL;
    free(cur);
}

void push_front(ListNode* phead, SLDataType)

int main()
{
    ListNode* phead = Init();
    push_back(phead, 1);
    push_back(phead, 2);
    push_back(phead, 3);
    push_back(phead, 4);
    Print(phead);
    pop_back(phead);
    Print(phead);
    Destroy(phead);
    return 0;
}
