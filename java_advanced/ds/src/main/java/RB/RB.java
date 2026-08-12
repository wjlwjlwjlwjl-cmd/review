package RB;

import java.util.ArrayList;
import java.util.Random;

public class RB {
    public static void main(String[] args){
        long begin = System.currentTimeMillis();
        int[][] testCases = {
                {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
                {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
                {50, 30, 70, 20, 40, 60, 80, 35, 45, 55, 65, 25, 15, 75, 85},
                {50, 20, 80, 10, 30, 70, 90, 25, 35, 65, 75, 5, 15, 85, 95},
                {12, 5, 18, 3, 7, 15, 22, 2, 4, 6, 8, 14, 16, 20, 24, 1, 9, 13, 17, 19, 21, 23, 25},
                {10, 5, 15, 3, 7, 12, 18, 1, 4, 6, 8, 11, 13, 17, 20, 2, 9, 14, 16, 19},
                {100, 50, 150, 25, 75, 125, 175, 10, 40, 60, 90, 110, 140, 160, 190, 30, 70, 80, 120, 130, 170, 180},
                {37, 12, 88, 5, 24, 63, 91, 18, 42, 71, 3, 9, 15, 29, 55, 68, 79, 95, 1, 7, 21, 33, 47, 59, 74, 84, 97},
                {50, 25, 75, 10, 30, 60, 90, 5, 15, 27, 35, 55, 65, 85, 95, 1, 8, 12, 18, 28, 32, 58, 62, 82, 88, 92, 99},
                {64, 32, 96, 16, 48, 80, 112, 8, 24, 40, 56, 72, 88, 104, 120, 4, 12, 20, 28, 36, 44, 52, 60, 68, 76, 84, 92, 100, 108, 116, 124}
        };

        for (int i = 0; i < testCases.length; i++) {
            RBTree tree = new RBTree();
            for (int j = 0; j < testCases[i].length; j++) {
                int val = testCases[i][j];
                tree.insert(val);
                // 每插入一个节点立即检查
                if (!tree.check()) {
                    System.out.println("fixed test error!");
                    System.out.println("case = " + i);
                    System.out.println("insert index = " + j);
                    System.out.println("value = " + val);
                    System.out.println("sequence:");
                    for (int k = 0; k <= j; k++) {
                        System.out.print(testCases[i][k] + " ");
                    }
                    System.out.println();
                    return;
                }
            }

            System.out.println("fixed case " + i + " pass");
        }

        Random r = new Random();
        for (int t = 0; t < 10000; t++) {
            RBTree tree = new RBTree();
            ArrayList<Integer> nums = new ArrayList<>();

            for (int i = 0; i < 1000; i++) {
                int x = r.nextInt(100000);
                // 记录实际插入的数据
                if (tree.insert(x)) {
                    nums.add(x);
                }

                // 每次插入后立即检查
                if (!tree.check()) {
                    System.out.println("random test error!");
                    System.out.println("round = " + t);
                    System.out.println("insert index = " + i);
                    System.out.println("value = " + x);

                    System.out.println("sequence:");
                    System.out.println(nums);
                    return;
                }
            }
        }
        System.out.println("all pass");
        long end = System.currentTimeMillis();
        System.out.println("takes " + (end - begin) + "ms");
    }
}

enum COLOR{
    BLACK,
    RED
}

class Node{
    public Node parent;
    public Node left;
    public Node right;
    public int val;
    public COLOR color;

    public Node(int val){
        this.val = val;
        this.color = COLOR.RED;
    }
}

class RBTree{
    private Node root;

    public void inOrder(){
        _inOrder(root);
    }

    public boolean check()
    {
        if(null == root)
            return true;
        if(root.color != COLOR.BLACK) {
            System.out.println("违反了性质2：根节点不是黑色");
            return false;
        }
        int blackCount = 0; //先计算每条路径上应该有的黑色节点数目
        Node cur = root;
        while(null != cur){
            if(cur.color == COLOR.BLACK)
                blackCount++;
            cur = cur.left;
        }
        return _isValidRBtree(root, 0, blackCount);
    }

    public boolean insert(int val){
        //根节点为黑色
        if(root == null){
            root = new Node(val);
            root.color = COLOR.BLACK;
            return true;
        }

        Node cur = root;
        Node parent = cur.parent;
        while(cur != null){
            parent = cur;
            if(val < cur.val){
                cur = cur.left;
            }
            else if(val > cur.val){
                cur = cur.right;
            }
            else{
                return false;
            }
        }

        cur = new Node(val);
        cur.parent = parent;
        if(val < parent.val){
            parent.left = cur;
        }
        else{
            parent.right = cur;
        }

        if(parent.color == COLOR.BLACK){
            return true;
        }

        while(parent != null && parent.color == COLOR.RED){
            Node grandfather = parent.parent;
            Node uncle;
            if(parent == grandfather.left){
                uncle = grandfather.right;
            }
            else{
                uncle = grandfather.left;
            }

            if(uncle == null || uncle.color == COLOR.BLACK){
                if(parent == grandfather.left){
                    if(cur == parent.left){
                        rotateR(grandfather, parent);
                        parent.color = COLOR.BLACK;
                        grandfather.color = COLOR.RED;
                    }
                    else{
                        rotateLR(grandfather, parent);
                        cur.color = COLOR.BLACK;
                        grandfather.color = COLOR.RED;
                    }
                }
                else{
                    if(cur == parent.right){
                        rotateL(grandfather, parent);
                        parent.color = COLOR.BLACK;
                        grandfather.color = COLOR.RED;
                    }
                    else{
                        rotateRL(grandfather, parent);
                        cur.color = COLOR.BLACK;
                        grandfather.color = COLOR.RED;
                    }
                }
                break;
            }
            else{
                uncle.color = parent.color = COLOR.BLACK;
                grandfather.color = COLOR.RED;
                cur = grandfather;
                parent = grandfather.parent;
            }
        }
        root.color = COLOR.BLACK;
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
    }

    private void rotateLR(Node parent, Node cur) {
        Node subCur = cur.right;
        rotateL(cur, subCur);
        rotateR(parent, subCur);
    }

    private void rotateRL(Node parent, Node cur) {
        Node subCur = cur.left;
        rotateR(cur, subCur);
        rotateL(parent, subCur);
    }

    private void _inOrder(Node root){
        if(root == null){
            return;
        }
        _inOrder(root.left);
        System.out.printf("%d->", root.val);
        _inOrder(root.right);
    }

    private boolean _isValidRBtree(Node root, int pathCount, int blackCount){
        if(null == root)
            return true;
        if(root.color == COLOR.BLACK)
            pathCount++;
        Node parent = root.parent;
        if(parent != null && parent.color == COLOR.RED && root.color == COLOR.RED){
            System.out.println("违反了性质4：有连在一起的红色节点");
            return true;
        }
        if(root.left == null && root.right == null){ //叶子节点，开始检查当前 pathCount 和 blackCount 是否相等
            if(pathCount != blackCount){
                System.out.println("违反了性质5：路径中黑色节点格式不一致");
                return false;
            }
        }
        return _isValidRBtree(root.left, pathCount, blackCount) &&
                _isValidRBtree(root.right, pathCount, blackCount);
    }
}