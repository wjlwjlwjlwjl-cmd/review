/*
* 1. 根节点必须是黑色
* 2. 每个红节点的节点都必须是黑色
* 3. 从根节点到叶子节点的每条路径上的黑色节点的数目相等
* 推导
* 插入节点必须是红色节点，否则破坏3
*/
#include <iostream>
#include <cassert>
using namespace std;

enum Color
{
    RED,
    BLACK  
};

template <class K, class V>
class RBNode
{
public:  
    RBNode(pair<K, V>& kv, enum Color col = RED)
        : kv(kv)
        , color(col)
    {}
    pair<K, V> kv;
    RBNode* parent = nullptr;
    RBNode* left = nullptr;
    RBNode* right = nullptr;
    Color color;
};

template <class K, class V>
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

        Node* cur = _root, *parent = nullptr;
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
        if(kv.first > parent->kv.first)
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
                    parent->color = uncle->color = BLACK;
                    grandparent->color = RED;
                    cur = grandparent;
                    parent = parent->parent;
                }
                else
                {
                    if(cur == parent->left)
                    {
                        //      g
                        //    p    u 
                        //  c
                        RotateR(grandparent);
                        parent->color = BLACK;
                        grandparent->color = RED;
                        break;
                    }
                    else
                    {
                        //      g
                        //   p     u
                        //     c
                        RotateL(cur);
                        RotateR(parent);
                        cur->color = BLACK;
                        grandparent->color = RED;
                        break;
                    }
                }
            }
            else
            {
                Node* uncle = grandparent->left;
                if(uncle && uncle->color == RED)
                {
                    parent->color = uncle->color = BLACK;
                    grandparent->color = RED;
                    cur = grandparent;
                    parent = cur->parent;
                }
                else
                {
                    if(parent->right == cur)
                    {
                        //     g
                        //   u   p
                        //         c
                        RotateL(grandparent);
                        grandparent->color = RED;
                        parent->color = BLACK;
                        break;
                    }
                    else
                    {
                        //     g
                        //   u   p
                        //      c
                        RotateR(parent);
                        RotateL(grandparent);
                        cur->color = BLACK;
                        grandparent->color = RED;
                        break;
                    }
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

        parent->parent = subL;
        subL->right = parent;
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

        parent->parent = subR;
        subR->left = parent;
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
            if(grandparent->right == parent)
            {
                grandparent->right = subR;
            }
            else
            {
                grandparent->left = subR;
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
        if(isBalance(_root))
        {
            cout << "红黑树经检查无误" << endl;
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
        cout << root->kv.first << " " << root->kv.second << endl;
        _inOrder(root->right);
    }

    bool isBalance(Node* root)
    {
        if(root == nullptr)
        {
            return true;
        }

        if(root->color == RED)
        {
            return false;
        }
        int ref = 0;
        Node* cur = root;
        while(cur)
        {
            if(cur->color == BLACK)
            {
                ref++;
            }
            cur = cur->left;
        }
        cout << ref << "dddd" << endl;
        return check(root, 0, ref);
    }

    bool check(Node* root, int blacknum, int ref)
    {
        if(root == nullptr)
        {
            if(blacknum != ref)
            {
                cout << "黑色节点数目错误 " << blacknum << " " << ref << endl;
                return false;
            }
            return true;
        }

        if(root->color == RED && root->parent->color == RED)
        {
            cout << "连续的红色节点" << endl;
            return false;
        }
        if(root->color == BLACK)
        {
            blacknum++;
        }
        return check(root->left, blacknum, ref) && check(root->right, blacknum, ref);
    }

    Node* _root = nullptr;
};

int main()
{
    RBTree<int, int> rbt;
    rbt.insert(make_pair(1, 1));
    rbt.insert(make_pair(8, 1));
    rbt.insert(make_pair(6, 1));
    rbt.insert(make_pair(9, 1));
    rbt.insert(make_pair(3, 1));
    rbt.insert(make_pair(5, 1));
    rbt.insert(make_pair(4, 1));
    rbt.insert(make_pair(6, 1));

    rbt.inOrder();

    rbt.test();
    return 0;
}
