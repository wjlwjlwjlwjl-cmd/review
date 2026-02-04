#include <iostream>
#include <assert.h>
using namespace std;

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
        if(_root == nullptr)
        {
            _root = new Node(key, val);
            return true;
        }

        Node* parent = nullptr;
        Node* cur = _root; 
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

        cur = new Node(key, val);
        if(key > parent->val)
        {
            parent->right = cur;
        }
        else
        {
            parent->left = cur;
        }
        cur->parent = parent;

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
                if(parent->bf == 2 && cur->bf == 1)
                {
                    RotateL(parent);
                }
                else if(parent->bf == 2 && cur->bf == -1)
                {
                    RotateRL(parent);
                }
                else if(parent->bf == -2 && cur->bf == -1)
                {
                    RotateR(parent);
                }
                else if(parent->bf == -2 && cur->bf == 1)
                {
                    RotateLR(parent);
                }
                else
                {
                    assert(false);
                }
                break;
            }
            else
            {
                assert(false);
            }
        }
        return true;
    }

    void RotateR(Node* parent)
    {
        if(parent == nullptr)
        {
            return;
        }
        Node* subL = parent->left;
        Node* subLR = subL->right;
        Node* grandparent = parent->parent;

        if(parent == _root)
        {
            _root = subL;
            subL->parent = nullptr;
        }
        else if(grandparent->right == parent)
        {
            grandparent->right = subL;
        }
        else
        {
            grandparent->left = subL;
        }
        subL->parent = grandparent;
        parent->parent = subL;
        parent->left = subLR;
        subL->right = parent;
        if(subLR)
        {
            subLR->parent = parent;
        }
        subL->bf = 0;
        parent->bf = 0;
    }

    void RotateL(Node* parent)
    {
        if(parent == nullptr)
        {
            return;
        }
        Node* grandparent = parent->parent;
        Node* subR = parent->right;
        Node* subRL = subR->left;

        if(parent == _root)
        {
            _root = subR;
            subR->parent = nullptr;
        }
        else if(grandparent->right == parent)
        {
            grandparent->right = subR;
        }
        else
        {
            grandparent->left = subR;
        }
        subR->parent = grandparent;
        parent->right = subRL;
        if(subRL)
        {
            subRL->parent = parent;
        }
        parent->parent = subR;
        subR->left = parent;

        subR->bf = 0;
        parent->bf = 0;
    }

    void RotateLR(Node* parent)
    {
        if(parent == nullptr)
        {
            return;
        }
        Node* subL = parent->left;
        Node* subLR = subL->right;
        int bf = subLR->bf;

        RotateL(subL);
        RotateR(parent);

        if(bf == 1)
        {
            subL->bf = -1;
            subLR->bf = 0;
            parent->bf = 0;
        }
        else if(bf == -1)
        {
            subL->bf = 0;
            subLR->bf = 0;
            parent->bf = 1;
        }
        else if(bf == 0)
        {
            subL->bf = subLR->bf = parent->bf = 0;
        }
        else
        {
            assert(false);
        }
    }

    void RotateRL(Node* parent)
    {
        if(parent == nullptr)
        {
            return;
        }
        Node* subR = parent->right;
        Node* subRL = subR->left;
        int bf = subRL->bf;

        RotateR(subR);
        RotateL(parent);

        if(bf == 1)
        {
            subR->bf = 0;
            subRL->bf = 0;
            parent->bf = -1;
        }
        else if(bf == -1)
        {
            subR->bf = 1;
            subRL->bf = 0;
            parent->bf = 0;
        }
        else if(bf == 0)
        {
            subR->bf = subRL->bf = parent->bf = 0;
        }
        else
        {
            assert(false);
        }
    }

    Node* root()
    {
        return _root;
    }

    void inOrder()
    {
        _inOrder(_root);
    }
private:
    void _inOrder(Node* root)
    {
        if(root == nullptr)
        {
            return;
        }
        _inOrder(root->left);
        cout << root->key << ":" << root->val << "-" << root->bf << endl;
        _inOrder(root->right);
    }

    Node* _root = nullptr;
};

//检测代码，主要从两个方面检测，一个是高度差，一个是平衡因子是否有效
template<class K, class V>
int Height(AVLNode<K, V>* root)
{
    if(root == nullptr)
    {
        return 0;
    }
    int lh = Height(root->left);
    int rh = Height(root->right);
    return lh > rh ? lh : rh;
}

template<class K, class V>
bool Test(AVLNode<K, V>* root)
{
    if(root == nullptr)
    {
        return true;
    }
    int diff = - Height(root->left) + Height(root->right);
    if(diff != 0 && diff != 1 && diff != -1)
    {
        cout << "error with the height of the tree" << endl;
        return false;
    }
    if(diff != root->bf)
    {
        cout << "error with the bf:" << root->key << endl;
        return false;
    }
    return Test(root->left) && Test(root->right);
}

int main()
{
    AVLTree<int, int> at;
    at.insert(1, 1);
    at.insert(4, 1);
    at.insert(2, 1);
    at.insert(8, 1);
    at.insert(6, 1);
    at.insert(5, 1);
    at.insert(7, 1);
    at.inOrder();
    Test<int, int>(at.root());
    return 0;
}
