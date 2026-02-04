#include <iostream>
using namespace std;
//这里实现的是不支持插入重复值的版本

template <class T>
class BSNode
{
public:  
    BSNode(const T& val = T())
        : _val(val)
        , _left(nullptr)
        , _right(nullptr)
    {}

    BSNode* _left;
    BSNode* _right;
    T _val;
};

template <class T>
class BSTree
{
public:  
    bool insert(const T& val)
    {
        if(!_root)
        {
            _root = new BSNode(val);
            return true;
        }

        BSNode<T>* prev = nullptr;
        BSNode<T>* cur = _root;
        while(cur)
        {
            prev = cur;
            if(cur->_val < val)
            {
                cur = cur->_right;
                if(!cur)
                {
                    BSNode<T>* newNode = new BSNode(val);
                    prev->_right = newNode;
                }
            }
            else if(cur->_val > val)
            {
                cur = cur->_left;
                if(!cur)
                {
                    BSNode<T>* newNode = new BSNode(val);
                    prev->_left = newNode;
                }
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    bool Find(const T& val = T())
    {
        BSNode<T>* prev = nullptr, *cur = _root;
        while(cur)
        {
            prev = cur;
            if(cur->_val == val)
            {
                return true;
            }
            else if(cur->_val > val)
            {
                cur = cur->_left;
            }
            else
            {
                cur = cur->_right;
            }
        }
        return false;
    }

    bool Erase(const T& val = T())
    {
        BSNode<T>* cur = _root, *prev = nullptr;
        while(cur)
        {
            if(cur->_val < val)
            {
                prev = cur;
                cur = cur->_right;
            }
            else if(cur->_val > val)
            {
                prev = cur;
                cur = cur->_left;
            }
            else
            {
                if(cur->_left == nullptr)                
                {
                    if(prev->_left == cur)
                    {
                        prev->_left = cur->_right;
                        delete cur;
                        return true;
                    }
                    else
                    {
                        prev->_right = cur->_right;
                        delete cur;
                        return true;
                    }
                }
                else if(cur->_right == nullptr)
                {
                    if(prev->_left == cur)
                    {
                        prev->_left = cur->_left;
                        delete cur;
                        return true;
                    }
                    else
                    {
                        prev->_right = cur->_left;
                        delete cur;
                        return true;
                    }
                }
                else
                {
                    //这里实现的是找左边的最大值，分为两种情况，一种是叶子节点的最大值，两一种是没有右子树时根节点时最大值
                    BSNode<T>* cmax = cur->_left, *pmax = cur;
                    while(cmax->_right)
                    {
                        pmax = cmax;
                        cmax = cmax->_right;
                    }
                    cur->_val = cmax->_val;
                    if(pmax->_right == cmax)
                    {
                        pmax->_right = cmax->_right;
                    }
                    else
                    {
                        pmax->_left = cmax->_left;
                    }
                    delete cmax;
                    return true;
                }
            }
        }
        return false;
    }

    void inOrder()
    {
        _inOrder(_root);
    }
private:
    void _inOrder(BSNode<T>* root)
    {
        if(root == nullptr)
        {
            return;
        }
        _inOrder(root->_left);
        cout << root->_val << " " << endl;
        _inOrder(root->_right);
    }

    BSNode<T>* _root = nullptr;
};

int main()
{
    BSTree<int> bst;
    for(int i = 0; i < 10; i++)
    {
        bst.insert(i);
    }
    bst.inOrder();
    cout << endl;
    bst.Erase(6);
    bst.inOrder();
    return 0;
}
