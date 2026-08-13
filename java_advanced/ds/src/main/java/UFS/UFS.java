package UFS;

import java.util.Arrays;

public class UFS {
    public static void main(String[] args){
        UnionFindSet ufs = new UnionFindSet(10);
        ufs.union(0, 1);
        ufs.union(0, 2);
        ufs.union(1, 3);
        ufs.union(1, 4);
        ufs.union(4, 5);
        ufs.union(4, 6);
        ufs.union(7, 8);
        ufs.union(7, 9);
        ufs.printSet();
    }
}

class UnionFindSet{
    private int[] elem;

    public UnionFindSet(int n){
        if(n < 0){
            throw new RuntimeException("elem's size incorrect");
        }
        elem = new int[n];
        Arrays.fill(elem, -1);
    }

    public int findRoot(int val){
        if(val < 0 || val >= elem.length){
            throw new RuntimeException("invalid val");
        }
        while(elem[val] >= 0){
            val = elem[val];
        }
        return val;
    }

    public void union(int x1, int x2){
        int index1 = findRoot(x1);
        int index2 = findRoot(x2);
        if(index1 == index2){
            return; //本身就在同一集合中不用合并
        }
        elem[index1] = elem[index1] + elem[index2];
        elem[index2] = index1;
    }

    public boolean isSameSet(int x1, int x2){
        int index1 = findRoot(x1);
        int index2 = findRoot(x2);
        return index1 == index2;
    }

    public int getSetCount(){
        int count = 0;
        for(int i = 0; i < elem.length; i++){
            if(elem[i] < 0){
                count++;
            }
        }
        return count;
    }

    public void printSet(){
        for(int i = 0; i < elem.length; i++){
            System.out.printf("%d ", elem[i]);
        }
        System.out.println();
    }
}
