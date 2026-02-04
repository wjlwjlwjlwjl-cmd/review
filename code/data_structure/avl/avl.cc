#include <iostream>
#include <assert.h>

template <class T, class V>
class AVLNode
{
public:  
    AVLNode(const T& key = T(), const V& val = T())
        : key(key)
        , val(val)
    {}

    T key;
    V val;
    int bf = 0; //平衡因子
    AVLNode* parent = nullptr;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
};

template <class T, class V>
class AVLTree
{
public:  
    typedef AVLNode<T, V> Node;
    bool insert(const T& key = T(), const V& val = V())
    {
        Node* newNode = new Node(key, val);
        if(_root == nullptr)
        {
            _root = newNode;
            return true;
        }

        Node* parent = nullptr, *cur = _root; 
        while(cur)
        {
            if(cur->key < key)
            {
                parent = cur;
                cur = cur->right;
            }
            else if(cur->key > key)
            {
                parent = cur;
                cur = cur->left;
            }
            else
            {
                return false;
            }
        }

        if(key > parent->val)
        {
            parent->right = newNode;
            newNode->parent = parent;
        }
        else
        {
            parent->left = newNode;
            newNode->parent = parent;
        }

        cur = newNode;
        while(parent)
        {
            if(parent->left == cur)
            {
                (parent->bf)--;
            }
            else
            {
                (parent->bf)++;
            }
            if(parent->bf == 0)
            {
                break;
            }
            else if(parent->bf == 1 || parent->bf == -1)
            {
                cur = parent;
                parent = parent->parent;
            }
            else if(parent->bf == 2 || parent->bf == -2)
            {
                //旋转处理
            }
            else
            {
                assert(false);
            }
        }
    }
private:
    Node* _root;
};

int main()
{
    return 0;
}
