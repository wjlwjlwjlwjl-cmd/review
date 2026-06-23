public class Test {
    public static void main(String[] args) {
        char[] strs = { 'a', 'b', 'c' };
        strs[0] = 'g';
        String str1 = new String(strs);
        String str2 = new String(strs);
        System.out.println(str1);
        System.out.println(str2);
    }
}
