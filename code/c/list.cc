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

void push_front(ListNode* phead, SLDataType val)
{
    ListNode* newNode = BuyNode(val);
    if(phead->next == NULL)
    {
        phead->next = newNode;
    }
    else
    {
        newNode->next = phead->next;
        phead->next->prev = newNode;
        phead->next = newNode;
        newNode->prev = phead;
    }
}

void pop_front(ListNode* phead)
{
    if(phead->next == NULL)
    {
        return;
    }
    else
    {
        ListNode* del = phead->next;
        phead->next = phead->next->next;
        phead->next->prev = phead;
        free(del);
    }
}

void insert(ListNode* phead, int pos,SLDataType x)
{
    ListNode* newNode = BuyNode(x);
    if(phead->next == NULL)
    {
        phead->next = newNode;
    }
    else
    {
        ListNode* prev = NULL;
        ListNode* cur = phead->next;
        while(pos--)
        {
            prev = cur;
            cur = cur->next;
        }
        cur->prev = newNode;        
        newNode->next = cur;
        newNode->prev = prev;
        prev->next = newNode;
    }
}

void erase(ListNode* phead, int pos)
{
    if(phead->next == NULL)
    {
        return;
    }
    else
    {
        ListNode* cur = phead->next;
        while(pos--)
        {
            cur = cur->next;
        }
        cur->next->prev = cur->prev;
        cur->prev->next = cur->next;
        free(cur);
    }
}

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
    push_front(phead, 1);
    Print(phead);
    pop_front(phead);
    Print(phead);
    insert(phead, 1, 100);
    Print(phead);
    erase(phead, 1);
    Print(phead);
    Destroy(phead);
    return 0;
}
