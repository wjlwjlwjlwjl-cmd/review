#include <stdlib.h>

class MyCircularQueue {
public:
    MyCircularQueue(int _k) {
        k = _k;
        arr = (int*)malloc(sizeof(int) * (k + 1));
        start = 0;
        end = 1;
    }
    
    bool enQueue(int value) {
        if(isFull())
        {
            return false;
        }
        else
        {
            arr[end] = value;
            end = (end + 1) % (k + 1);
            return true;
        }
    }
    
    bool deQueue() {
        if(isEmpty())
        {
            return false;
        }
        else
        {
            start = (start + 1) % (k + 1);
            return true;
        }
    }
    
    int Front() {
        if(isEmpty())
        {
            return 1;
        }
        return arr[start];
    }
    
    int Rear() {
        if(isEmpty())
        {
            return -1;
        }
        return arr[end == 0 ? k : end - 1];
    }
    
    bool isEmpty() {
        if(start == end)
        {
            return true;
        }
        return false;
    }
    
    bool isFull() {
        if((end + 1) % (k + 1) == start)
        {
            return true;
        }
        return false;
    }
private:
    int* arr;
    int start, end;
    int k;
};
