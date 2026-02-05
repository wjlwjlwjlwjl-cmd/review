# AVL 树
## 简介
avl树是一种平衡二叉树，通过“平衡因子”来实现左右两侧高度差的平衡，只允许平衡因子取值为0、1、-1，相对于红黑树，avl树更接近“绝对平衡”，但是对于旋转子树的处理要相对繁琐一些
## 插入方法
1. 如果正好插入在较矮的子树，那么久不需要旋转处理
2. 如果原来两棵子树同样高，那么也不需要旋转处理
3. 如果插入在原来就较高的子树，那么就需要进行旋转处理
* 情况一：根节点的左子树的左子树<br>
```cpp
//       10     ----》    8
//    8     b          a    10
//  a   c                  c  b
```
a是高度为h + 1的子树，其中包含了我们新插入的节点；c子树是高度为h的子树；b是高度为h的子树，此时对于节点10，他的平衡因子是-2，需要进行旋转处理。<br>
左旋之后，高度为h + 1的a子树仍然在左边，右子树的高度为h + 1，这样就实现了平衡，8节点和10节点的平衡因子都被处理为了0
* 情况二：根节点的左子树的右子树
```cpp
//      10      ---->   10   ---->  8 
//   5      b         8   b       5   10    
// a   8            5  d        a c   d b
//    c d         a c
```
这里需要我们将情况一中的c子树进行拆分，也就是上面例子中的以8为根节点的子树。a是高度为h的子树，b、c是高度为h - 1的子树，b是高度为h的子树；情况二又可以根据8节点的平衡因子细分为三种情况，无论哪种情况，区分点在更新平衡因子，在旋转上没有区别
首先对8节点进行左单旋，然后对10节点进行右单旋，这样，就完成了平衡，随后，根据前面说的新的节点的插入位置进行讨论，更新8、5 10节点的平衡因子
* 还有两种情况，完全就是情况一、二的镜像版本，没有任何区别，这里不再过度赘述了
## avl树的验证
从两个方面考虑，一个是绝对高度是否满足左右子树差值不超过1，另一个是平衡因子是否符合实际状况，递归判断即可
## avl插入及验证的实现代码
```cpp
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
```
# 红黑树
## 简介
红黑树也是平衡二叉搜索树的一种实现，比avl树的应用更广一些，c++stl中的map和set都是用的红黑树实现的，虽然实现的没有avl树那么的“平衡”，但是红黑树在最坏情况下dfs的时间复杂度也是2logN，依然和avl树在同一数量级
## 规则
* 每个节点要么是红色，要么是黑色
* 根节点必须是黑色
* 黑色节点可以连接，但是红色节点不能相互链接，而且红色节点的两个子节点（如果有的话）必须是黑色节点
* 从根节点到任意一个叶子节点的路程中，黑色节点的数目都必须是相等的
## 插入方法
1. 由上面的规则不难推导出，插入节点必须是红色节点，否则会导致原来的红黑树第四条规则失效
2. 插入的话，大类其实根据新插入节点父节点的颜色分为两种，一种是原来的节点是黑色，这种情况下插入即可；另一种是插入节点的父节点是红色。在这种情况下，根据叔叔节点的颜色，又可以进行区分<br>
下面先规定以下三种子树：(1)父子树parent，p；(2)爷爷子树，grandparent，g；(3)叔叔子树uncle，u (4)当前子树current，c，包含新插入的节点<br>，
这里和上面只以左右对称的两种情况的其中一种为例子进行演示(为了方便0表示红色，1表示黑色):
* 叔叔节点存在为红色
```cpp
//     g1    ---->   g0 
//   p0  u0        p1   u1
// c0            c0
```
只需要变动父亲节点和叔叔节点颜色即可，但是这里会出现连锁反应，需要继续往上处理，让现在的g子树成为下一次的c子树
* 叔叔节点不存在或者叔叔节点为黑色，这里又可以根据c节点和p节点的相对位置分为两种情况<br>
情况一：c是p的左孩子<br>
```cpp
//     g1  ---->  p1
//   p0  u1     c0   g0
// c0                  u1
```
这种情况下进行一个右单旋即可，随后修改g、p的颜色<br>
情况二：c是p的右孩子
```cpp
//   g1  ---->  g1  ---->  c1
// p0   u1    c0  u1     p0   g0
//  c0      p0                   u1
```
这种情况需要先对c进行左单旋，随后对g1进行右单旋
## 红黑树的验证
从两个方面，一个是红色节点的连接情况，有没有出现两个红色节点相连的情况；另一个是各个节点的黑色节点的数目。依旧与avl树类似，采取递归的方式处理
## 红黑树的插入及验证实现代码
```cpp
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
```