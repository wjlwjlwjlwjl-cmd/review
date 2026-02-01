#include <initializer_list>
#include <iostream>
#include <cassert>
#include <limits.h>

template <class T>
class ListNode
{
public:
    T data = INT_MIN;
    struct ListNode* _prev = nullptr;
    struct ListNode* _next = nullptr;

    ListNode(const T& val = T())
        : data(val)
    {}
};

template<class T, class Ref, class Ptr>
class list_iterator
{
public:  
    typedef ListNode<T> Node;
    typedef list_iterator<T, Ref, Ptr> Self;
    Node* _node;

    list_iterator() = default;

    list_iterator(Node* node)
    {
        _node = node;
    }

    Ref operator*()
    {
        return _node->data;
    }

    Ptr operator->()
    {
        return _node->data;
    }

    Self& operator++()
    {
        _node = _node->_next;
        return *this;
    }

    Self operator++(int)
    {
        Self tmp(*this);
        _node = _node->_next;
        return tmp;
    }

    Self& operator--()
    {
        _node = _node->_prev;
        return *this;
    }

    Self operator--(int)
    {
        Self tmp(*this);
        _node = _node->_prev;
        return tmp;
    }

    bool operator!=(const Self& s)
    {
        return s._node != _node;
    }

    Self& operator+(int val)
    {
        _node = _node->_next;
        return *this;
    }

    Self& operator-(int val)
    {
        _node = _node->_next;
        return *this;
    }
};

template<class T>
class list
{
public:    
    typedef ListNode<T> Node;
    typedef list_iterator<T, T&, T*> iterator;
    typedef list_iterator<T, const T&, const T*> const_iterator;

    list()
        : _size(0)
        , _head(new Node)
    {}

    list(const list& lt)
        : _size(0)
        , _head(new Node)
    {
        for(auto e: lt)
        {
            push_back(e);
        }
    }

    list(const std::initializer_list<T> lt)
        : _size(0)
        , _head(new Node)
    {
        for(auto& e: lt)
        {
            push_back(e);
        }
    }

    iterator begin()
    {
        return _head->_next;
    }

    iterator end()
    {
        return _head;
    }

    const_iterator begin() const 
    {
        return _head->_next;
    }

    const_iterator end() const
    {
        return _head;
    }

    bool empty()
    {
        return _head->_next == nullptr;
    }

    iterator front()
    {
        return _head->_next;
    }

    iterator back()
    {
        return _head->_prev;
    }

    void insert(int pos, int val)
    {
        if(pos == 0 || _size == 0)
        {
            push_front(val);
            return;
        }
        if(pos >= _size)
        {
            push_back(val);
            return;
        }
        Node* cur = _head->_next;
        while(pos--)
        {
            cur = cur->_next;
        }
        Node* prev = cur->_prev;
        Node* newNode = new Node(val);
        prev->_next = newNode;
        newNode->_prev = prev;
        newNode->_next = cur;
        cur->_prev = newNode;
    }

    void push_front(const T& val)
    {
        Node* newNode = new Node(val);
        if(_head->_next == nullptr)
        {
            _head->_next = _head->_prev = newNode;
            newNode->_next = newNode->_prev = _head;
        }
        else
        {
            Node* old = _head->_next;
            _head->_next = newNode;
            newNode->_next = old;
            newNode->_prev = _head;
            old->_prev = newNode;
        }
        _size++;
    }

    void push_back(const T& val)
    {
        Node* newNode = new Node(val);
        if(_size == 0)
        {
            _head->_next = _head->_prev = newNode;
            newNode->_prev = newNode->_next = _head;
            _size++;
        }
        else
        {
            _head->_prev->_next = newNode;
            newNode->_prev = _head->_prev;
            newNode->_next = _head;
            _head->_prev = newNode;
            _size++;
       }
    }

    void erase(iterator pos)
    {
        if(empty())
        {
            return;
        }
        Node* prev = pos._node->_prev;
        Node* next = pos._node->_next;
        prev->_next = next;
        next->_prev = prev;
        free(pos._node);
    }

    void pop_back()
    {
        if(empty())
        {
            return;
        }
        Node* newtail = _head->_prev->_prev;
        free(_head->_prev);
        newtail->_next = _head;
        _head->_prev = newtail;
    }

    void pop_front()
    {
        if(empty())
        {
            return;
        }
        Node* newhead = _head->_next->_next;
        free(_head->_next);
        newhead->_prev = _head;
        _head->_next = newhead;
    }

    ~list()
    {
        if(_head->_next)
        {
            Node* cur = _head->_next;
            Node* next = cur->_next;
            while(next != _head)
            {
                next = cur->_next;
                free(cur);
                cur = cur->_next;
            }
        }
        free(_head);
    }
private:
    int _size = 0;
    Node* _head;
};
