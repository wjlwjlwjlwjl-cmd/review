package LRU;

import java.util.HashMap;

public class LRU {
    public static void main(String[] args){
        LRUCache lruCache = new LRUCache(10);
        for(int i = 0; i < 10; i++){
            lruCache.put(i, i);
        }
        lruCache.print();
        System.out.println(lruCache.get(0));
        lruCache.print();

        lruCache.put(11, 11);
        lruCache.print();

        lruCache.put(12, 12);
        lruCache.print();

        lruCache.get(3);
        lruCache.print();
    }
}

class Node{
    public Node prev;
    public Node next;
    public int key;
    public int val;

    public Node(){}

    public Node(Node prev, Node next, int key, int val){
        this.prev = prev;
        this.next = next;
        this.val = val;
        this.key = key;
    }
}

class LRUCache{
    //双向链表，解决 O(1) 插入；哈希表，使得双向链表能 O(1) get
    public HashMap<Integer, Node> hash = new HashMap<>(); //下标、Node
    public int capacity; //容量
    public int size; //大小
    public Node head;
    public Node tail;

    public LRUCache(int capacity){
        this.capacity = capacity;
        this.size = 0;
        head = new Node();
        tail = new Node();
        head.next = tail;
        tail.prev = head;
    }

    public void put(int key, int val){
        Node target = hash.get(key);
        if(target != null){ //已存在则更新元素
            target.val = val;
            mvToHead(target);
            return;
        }
        if(size == capacity){
            hash.remove(tail.prev.key);
            tail.prev.prev.next = tail;
            tail.prev = tail.prev.prev;
            size--;
        }
        target = new Node(head, head.next, key, val);
        hash.put(key, target);
        head.next.prev = target;
        head.next = target;
        size++;
    }

    public int get(int key){
        Node target = hash.get(key);
        if(target == null){
            System.out.printf("LRUCache 不存在 key: %d\n", key);
            return -1;
        }
        int value = target.val;

        //将最近查询的元素放到头部
        mvToHead(target);

        return value;
    }

    public void print(){
        Node cur = head.next;
        while(cur != tail){
            System.out.print(cur.val + " ");
            cur = cur.next;
        }
        System.out.println();
    }

    private void mvToHead(Node target){
        target.prev.next = target.next;
        target.next.prev = target.prev;

        target.next = head.next;
        target.prev = head;
        target.next.prev = target;
        target.prev.next = target;
    }
}