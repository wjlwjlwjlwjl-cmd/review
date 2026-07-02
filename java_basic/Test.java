import java.util.List;
import java.util.ArrayList;
import java.util.Queue;

public class Test {
    public static void main(String[] args) {
        char[] strs = { 'a', 'b', 'c' };
        strs[0] = 'g';
        String str1 = new String(strs);
        String str2 = new String(strs);
        System.out.println(str1);
        System.out.println(str2);
        System.out.println(str1 + str2);
        System.gc();
    }
}

class Node {
    public int val;
    public List<Node> children;

    public Node() {
    }

    public Node(int _val) {
        val = _val;
    }

    public Node(int _val, List<Node> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
    private List<List<Integer>> ret;
    private Queue<Node> q;

    public List<List<Integer>> levelOrder(Node root) {
        ret = new ArrayList<>();
        bfs(root);
        return ret;
    }

    private void bfs(Node root) {
        int n = root.children.size();
        int cnt = 0;
        for (Node node : root.children) {
            q.offer(node);
            cnt++;
        }
        List<Integer> tmp = new ArrayList<>();
        while (!q.isEmpty()) {
            while (cnt-- != 0) {
                tmp.add(q.peek().val);
                q.poll();
            }
            ret.add(tmp);
            cnt = q.size();
        }
    }
}
