#include <iostream>
using namespace std;

enum Color
{
    RED,
    BLACK
};

template<class K, class V>
class RBNode
{
public:
    RBNode(pair<K, V> kv, enum Color color = RED)
        : kv(kv)
        , color(color)
        , parent(nullptr)
        , left(nullptr)
        , right(nullptr)
    {}
    pair<K, V> kv;
    Color color;
    RBNode* parent;
    RBNode* left;
    RBNode* right;
};

template<class K, class V>
class RBTree
{
public:
    typedef RBNode<K, V> Node;
    bool insert(pair<K, V> kv)
    {
        if(_root == nullptr)
        {
            _root = new Node(kv, BLACK);
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
        if(parent->kv.first < kv.first)
        {
            parent->right = cur;
        }
        else
        {
            parent->left = cur;
        }
        cur->parent = parent;

        while(parent && parent->color == RED)
        {
            Node* grandparent = parent->parent;
            if(grandparent->left == parent)
            {
                Node* uncle = grandparent->right;
                if(uncle && uncle->color == RED)
                {
                    uncle->color = parent->color = BLACK;
                    grandparent->color = RED;
                    cur = grandparent;
                    parent = cur->parent;
                }
                else
                {
                    if(parent->left == cur)
                    {
                        RotateR(grandparent);
                        parent->color = RED;
                        cur->color = BLACK;
                    }
                    else
                    {
                        RotateL(parent);
                        RotateR(grandparent);
                        cur->color = BLACK;
                        grandparent->color = RED;
                    }
                    break;
                }
            }
            else if(grandparent->right == parent)
            {
                Node* uncle = grandparent->left;
                if(uncle && uncle->color == RED)
                {
                    uncle->color = parent->color = BLACK;
                    grandparent->color = RED;
                    cur = grandparent;
                    parent = cur->parent;
                }
                else
                {
                    if(cur == parent->right)
                    {
                        RotateL(grandparent);
                        grandparent->color = RED;
                        parent->color = BLACK;
                    }
                    else
                    {
                        RotateR(parent);
                        RotateL(grandparent);
                        grandparent->color = RED;
                        cur->color = BLACK;
                    }
                    break;
                }
            }
        }
        _root->color = BLACK;
        return true;
    }

    void RotateR(Node* parent)
    {
        Node* subL = parent->left;
        Node* subLR = subL->right;
        Node* grandparent = parent->parent;

        subL->right = parent;
        parent->parent = subL;
        parent->left = subLR;
        if(subLR)
        {
            subLR->parent = parent;
        }
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
    }

    void RotateL(Node* parent)
    {
        Node* subR = parent->right;
        Node* subRL = subR->left;
        Node* grandparent = parent->parent;

        parent->parent = subR;        subR->left = parent;
        parent->right = subRL;
        if(subRL)
        {
            subRL->parent = parent;
        }
        if(_root == parent)
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
    }

    void inOrder()
    {
        _inOrder(_root);
    }

    void test()
    {
        if(_test())
        {
            cout << "nothing wrong with the rbtree" << endl;
        }
    }
private:
    void _inOrder(Node* root)
    {
        if(root == nullptr)
        {
            return;
        }
        _inOrder(root->left);
        cout << root->kv.first << " ";
        _inOrder(root->right);
    }

    bool _check(Node* root, int blacknum, int ref)
    {
        if(root == nullptr)
        {
            if(blacknum != ref)
            {
                cout << "wrong black num" << endl;
                return false;
            }
            return true;
        }
        if(root->color == RED && root->parent->color == RED)
        {
            cout << "two red connected" << endl;
            return false;
        }
        if(root->color == BLACK)
        {
            blacknum++;
        }
        return _check(root->left, blacknum, ref) && _check(root->right, blacknum, ref);
    }

    bool _test()
    {
        if(_root->color == RED)
        {
            cout << "wrong root color" << endl;
            return false;
        }
        int ref = 0;
        Node* cur = _root;
        while(cur)
        {
            if(cur->color == BLACK)
            {
                ref++;
            }
            cur = cur->left;
        }
        return _check(_root, 0, ref);
    }
    Node* _root = nullptr;
};

int main()
{
    RBTree<int, int> rb;
    rb.insert(make_pair(8, 1));
    rb.insert(make_pair(7, 1));
    rb.insert(make_pair(3, 1));
    rb.insert(make_pair(5, 1));
    rb.insert(make_pair(4, 1));
    rb.insert(make_pair(6, 1));
    rb.insert(make_pair(0, 1));
    rb.insert(make_pair(2, 1));

    rb.inOrder();
    rb.test();
    return 0;
}
