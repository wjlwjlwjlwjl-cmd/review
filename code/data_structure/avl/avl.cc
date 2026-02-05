#include <iostream>
#include <cassert>
using namespace std;

template<class K, class V>
class AVLNode
{
public:  
    AVLNode(pair<K, V>& kv)
        : kv(kv)
        , bf(0)
        , parent(nullptr)
        , right(nullptr)
        , left(nullptr)
    {}
    pair<K, V> kv;
    int bf;
    AVLNode* parent;
    AVLNode* right;
    AVLNode* left;
};

template <class K, class V>
class AVLTree
{
public:    
    typedef AVLNode<K, V> Node;
    bool insert(pair<K, V> kv)
    {
        if(_root == nullptr)
        {
            _root = new Node(kv);
            return true;
        }
        Node* parent = nullptr, *cur = _root;
        while(cur)
        {
            if(cur->kv.first < kv.first)
            {
                parent = cur;
                cur = cur->right;
            }
            else if(cur->kv.first > kv.first)
            {
                parent = cur;
                cur = cur->left;
            }
            else
            {
                return false;
            }
        }

        cur = new Node(kv);
        if(cur->kv.first < parent->kv.first)
        {
            parent->left = cur;
        }
        else
        {
            parent->right = cur;
        }
        cur->parent = parent;

        while(parent)
        {
            if(parent->left == cur)
            {
                parent->bf--;
            }
            else
            {
                parent->bf++;
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
                if(parent->bf == -2 && cur->bf == -1)
                {
                    RotateR(parent);
                }
                else if(parent->bf == -2 && cur->bf == 1)
                {
                    RotateLR(parent);
                }
                else if(parent->bf == 2 && cur->bf == 1)
                {
                    RotateL(parent);
                }
                else if(parent->bf == 2 && cur->bf == -1)
                {
                    RotateRL(parent);
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
        Node* subL = parent->left;
        Node* subLR = subL->right;
        Node* grandparent = parent->parent;

        parent->parent = subL;
        parent->left = subLR;
        if(subLR)
        {
            subLR->parent = parent;
        }
        subL->right = parent;
        if(parent == _root)
        {
            _root = subL;
            subL->parent = nullptr;
        }
        else
        {
            if(grandparent->left == parent)
            {
                grandparent->left = subL;
            }
            else
            {
                grandparent->right = subL;
            }
            subL->parent = grandparent;
        }

        subL->bf = 0;
        parent->bf = 0;
    }

    void RotateL(Node* parent)
    {
        Node* subR = parent->right;
        Node* subRL = subR->left;
        Node* grandparent = parent->parent;

        subR->left = parent;
        parent->parent = subR;
        parent->right = subRL;
        if(subRL)
        {
            subRL->parent = parent;
        }
        if(parent == _root)
        {
            _root = subR;
            subR->parent = nullptr;
        }
        else
        {
            if(grandparent->left == parent)
            {
                grandparent->left = subR;
            }
            else
            {
                grandparent->right = subR;
            }
            subR->parent = grandparent;
        }
        subR->bf = 0;
        parent->bf = 0;
    }

    void RotateLR(Node* parent)
    {
        Node* subL = parent->left;
        Node* subLR = subL->right;
        int bf = subLR->bf;

        RotateL(subL);
        RotateR(parent);

        if(bf == 0)
        {
            subL->bf = 0;
            subLR->bf = 0;
            parent->bf = 0;
        }
        else if(bf == 1)
        {
            subL->bf = -1;
            subLR->bf = 0;
            parent->bf = 0;
        }
        else if(bf == -1)
        {
            subL->bf = 0;
            subLR->bf = 0;
            parent->bf = -1;
        }
        else
        {
            assert(false);
        }
    }

    void RotateRL(Node* parent)
    {
        Node* subR = parent->right;
        Node* subRL = subR->left;
        int bf = subRL->bf;

        RotateR(subR);
        RotateL(parent);

        if(bf == 0)
        {
            subR->bf = 0;
            subRL->bf = 0;
            parent->bf = 0;
        }
        else if(bf == 1)
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
        else
        {
            assert(false);
        }
    }

    void inOrder()
    {
        _inOrder(_root);
    }

    bool test()
    {
        return _test(_root);
    }
private:
    void _inOrder(Node* root)
    {
        if(root == nullptr)
        {
            return;
        }
        _inOrder(root->left);
        cout << root->kv.first << " " << root->kv.second << " " << root->bf << endl;
        _inOrder(root->right);
    }

    int _height(Node* root)
    {
        if(root == nullptr)
        {
            return 0;
        }
        int lh = _height(root->left);
        int rh = _height(root->right);
        return lh > rh ? lh + 1 : rh + 1;
    }

    bool _test(Node* root)
    {
        if(root == nullptr)
        {
            return true;
        }
        int diff = _height(root->right) - _height(root->left);
        if(abs(diff) > 1)
        {
            cout << "bad height: " << root->kv.first << endl;
        }
        if(diff != root->bf)
        {
            cout << "bad bf: " << root->kv.first << endl;
            return false;
        }
        return _test(root->left) && _test(root->right);
    }
    Node* _root = nullptr;
};

int main()
{
    AVLTree<int, int> at;
    at.insert(make_pair(1, 1));
    at.insert(make_pair(8, 1));
    at.insert(make_pair(4, 1));
    at.insert(make_pair(7, 1));
    at.insert(make_pair(6, 1));
    at.insert(make_pair(11, 1));
    at.insert(make_pair(3, 1));
    at.insert(make_pair(9, 1));

    at.inOrder();

    if(at.test())
    {
        cout << "nothing wrong with the avl tree" << endl;
    }
    return 0;
}
