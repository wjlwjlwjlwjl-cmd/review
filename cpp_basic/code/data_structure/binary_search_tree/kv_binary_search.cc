#include <iostream>
using namespace std;

template<class K, class V>
class BSNode
{
public:  
    BSNode(const K& key = K(), const V& val = V())
        : _key(key)
        , _val(val)
    {}
    K _key;
    V _val;
    BSNode<K, V>* _left = nullptr;
    BSNode<K, V>* _right = nullptr;
};

template<class K, class V>
class BSTree
{
public:  
    bool insert(const K& key = K(), const V& val = V())
    {
        BSNode<K, V>* newNode = new BSNode(key, val);
        if(_root == nullptr)
        {
            _root = newNode;
            return true;
        }
        BSNode<K, V>* prev = nullptr, *cur = _root;
        while(cur)
        {
            prev = cur;
            if(cur->_key < key)
            {
                cur = cur->_right;
            }
            else if(cur->_key > key)
            {
                cur = cur->_left;
            }
            else
            {
                return false;
            }
        }
        if(key < prev->_key)
        {
            prev->_left = newNode;
        }
        else
        {
            prev->_right = newNode;
        }
        return true;
    }

    bool Find(const V& key = V())
    {
        if(_root == nullptr)
        {
            return false;
        }
        BSNode<K, V> *cur = _root;
        while(cur)
        {
            if(cur->_key < key)
            {
                cur = cur->_right;
            }
            else if(cur->_key > key)
            {
                cur = cur->_left;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    bool Erase(const K& key = K())
    {
        if(_root == nullptr)
        {
            return false;
        }
        BSNode<K, V>* prev = nullptr, *cur = _root;
        while(cur)
        {
            if(cur->_key < key)
            {
                prev = cur;
                cur = cur->_right;
            }
            else if(cur->_key > key)
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
                    if(prev->_right == cur)
                    {
                        prev->_right = cur->_left;
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
                    BSNode<K, V>* pmax = cur, *cmax = cur->_left;
                    while(cmax->_left)
                    {
                        pmax = cmax; 
                        cmax = cmax->_right;
                    }
                    cur->_key = cmax->_key;
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
    void _inOrder(BSNode<K, V>* root)
    {
        if(root == nullptr)
        {
            return;
        }
        _inOrder(root->_left);
        cout << "key" << root->_key << "val" << root->_val << endl;
        _inOrder(root->_right);
    }

    BSNode<K, V>* _root = nullptr;
};

int main()
{
    BSTree<int, int> bst;
    bst.insert(1, 1);
    bst.insert(3, 1);
    bst.insert(5, 1);
    bst.insert(2, 1);
    bst.insert(9, 1);
    bst.insert(7, 1);
    bst.inOrder();

    cout << bst.Find(9) << " " << bst.Find(4) << endl;

    bst.Erase(9);
    bst.Erase(7);

    bst.inOrder();

    return 0;
}
