import java.util.*;

public class AVL {
    public static void main(String[] args) {
        Random r = new Random();
        for (int t = 0; t < 10000; t++) {
            AVLTree tree = new AVLTree();
            ArrayList<Integer> nums = new ArrayList<>();
            for (int i = 0; i < 100; i++) {
                int x = r.nextInt(10000);
                nums.add(x);
                tree.insert(x);
                if (!tree.check()) {
                    System.out.println("error");
                    System.out.println(nums);
                    return;
                }
            }
        }

        System.out.println("all pass");
    }
}

class Node {
    public Node parent;
    public Node left;
    public Node right;
    public int val;
    public int bf;

    public Node(int val) {
        this.val = val;
        this.bf = 0;
    }
}

class AVLTree {
    private Node root;

    public boolean insert(int val) {
        // 基本插入逻辑
        if (root == null) {
            root = new Node(val);
            return true;
        }
        Node cur = root;
        Node parent = null;

        while (cur != null) {
            parent = cur;
            if (val < cur.val) {
                cur = cur.left;
            } else if (val > cur.val) {
                cur = cur.right;
            } else {
                return false;
            }
        }
        cur = new Node(val);
        if (val < parent.val) {
            parent.left = cur;
        } else {
            parent.right = cur;
        }
        cur.parent = parent;

        while (parent != null) {
            if (cur == parent.left) {
                parent.bf++;
            } else {
                parent.bf--;
            }

            // 处理平衡因子
            if (parent.bf == 0) {
                break;
            } else if (parent.bf == 1 || parent.bf == -1) {
                // 更新平衡因子
                cur = parent;
                parent = cur.parent;
            } else {
                // bf == 2 || bf == -2
                if (parent.bf == 2) {
                    if (cur.bf == 1)
                        rotateR(parent, cur);
                    else
                        rotateLR(parent, cur);
                } else {
                    if (cur.bf == -1)
                        rotateL(parent, cur);
                    else
                        rotateRL(parent, cur);
                }
                break;
            }
        }

        return true;
    }

    private void rotateL(Node parent, Node cur) {
        Node b = cur.left;
        if (parent == root) {
            root = cur;
            cur.parent = null;
            cur.left = parent;
            parent.parent = cur;
            parent.right = b;
            if (b != null) {
                b.parent = parent;
            }
        } else {
            Node pParent = parent.parent;
            if (pParent.left == parent) {
                pParent.left = cur;
            } else {
                pParent.right = cur;
            }
            cur.parent = pParent;
            cur.left = parent;
            parent.parent = cur;
            parent.right = b;
            if (b != null) {
                b.parent = parent;
            }
        }
        parent.bf = cur.bf = 0;
    }

    private void rotateR(Node parent, Node cur) {
        Node b = cur.right;
        if (parent == root) {
            root = cur;
            cur.right = parent;
            cur.parent = null;
            parent.parent = cur;
            parent.left = b;
            if (b != null) {
                b.parent = parent;
            }
        } else {
            Node pParent = parent.parent;
            if (parent == pParent.left) {
                pParent.left = cur;
            } else {
                pParent.right = cur;
            }
            parent.parent = cur;
            cur.parent = pParent;
            cur.right = parent;
            if (b != null) {
                b.parent = parent;
            }
            parent.left = b;
        }
        parent.bf = cur.bf = 0;
    }

    private void rotateLR(Node parent, Node cur) {
        Node subCur = cur.right;
        int bf = subCur.bf;
        rotateL(cur, subCur);
        rotateR(parent, subCur);

        if (bf == 1) {
            cur.bf = 0;
            parent.bf = -1;
            subCur.bf = 0;
        } else if(bf == -1){
            cur.bf = 1;
            parent.bf = 0;
            subCur.bf = 0;
        }
        else{
            cur.bf = parent.bf = subCur.bf = 0;
        }
    }

    private void rotateRL(Node parent, Node cur) {
        Node subCur = cur.left;
        int bf = subCur.bf;
        rotateR(cur, subCur);
        rotateL(parent, subCur);
        if (bf == 1) {
            cur.bf = -1;
            subCur.bf = 0;
            parent.bf = 0;
        } else if(bf == -1){
            cur.bf = 0;
            subCur.bf = 0;
            parent.bf = 1;
        }
        else{
            cur.bf = parent.bf = subCur.bf = 0;
        }
    }

    public void inOrder() {
        _inOrder(root);
    }

    private void _inOrder(Node root) {
        if (root == null) {
            return;
        }
        _inOrder(root.left);
        System.out.print(root.val + "->");
        _inOrder(root.right);
    }

    public boolean check() {
        return _check(root);
    }

    private boolean _check(Node root) {
        if (root == null) {
            return true;
        }
        boolean ret = true;
        int hRight = height(root.right);
        int hLeft = height(root.left);
        if (hLeft - hRight != root.bf) {
            System.out.println("bf");
            ret = false;
        }
        int gap = hLeft - hRight;
        if (gap < -1 || gap > 1) {
            System.out.println("height");
            ret = false;
        }
        return ret && _check(root.left) && _check(root.right);
    }

    private int height(Node root) {
        if (root == null)
            return 0;
        int ret = 1;
        ret += Math.max(height(root.left), height(root.right));
        return ret;
    }
}