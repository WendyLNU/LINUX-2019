package RBTree;

import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Queue;

public class RBTree<K extends Comparable<K>, V> {

    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private Node root;

    private class Node {
        private K key;
        private V value;
        private Node left, right;
        private boolean color;
        private int N;

        public Node(K key, V value, boolean color, int N) {
            this.key = key;
            this.value = value;
            this.color = color;
            this.N = N;
        }

    }

    public RBTree() {

    }

    /**
     * �սڵ�Ĭ�϶��Ǻ�ɫ�ڵ�
     * 
     * @param x
     * @return
     */
    private boolean isRed(Node x) {
        if (x == null)
            return false;
        return x.color == RED;
    }

    /**
     * ������XΪ���������Ľڵ���Ŀ
     * 
     * @param x
     * @return
     */
    private int size(Node x) {
        if (x == null)
            return 0;
        return x.N;
    }

    /**
     * �����������Ľڵ���Ŀ
     * 
     * @return
     */
    public int size() {
        return size(root);
    }

    public boolean isEmpty() {
        return root == null;
    }

    /**
     * ����key���в���
     * 
     * @param key
     * @return
     */
    public V get(K key) {
        if (key == null) {
            throw new NullPointerException("key����Ϊ��");
        }
        return get(root, key);
    }

    private V get(Node x, K key) {
        while (x != null) {
            int cmp = key.compareTo(x.key);
            if (cmp < 0) {
                x = x.left;
            } else if (cmp > 0) {
                x = x.right;
            } else {
                return x.value;
            }
        }
        return null;
    }

    /**
     * �ж������Ƿ��������Ϊkey�ļ�
     * 
     * @param key
     * @return
     */
    public boolean contains(K key) {
        return get(key) != null;
    }

    /**
     * ����ת�� ��������б�ĺ����ӱ�Ϊ������б
     * 
     * @param h
     * @return
     */
    private Node rotateRight(Node h) {
        // assert (h != null) && isRed(h.left);
        Node x = h.left;
        h.left = x.right;
        x.right = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = size(h.left) + size(h.right) + 1;
        return x;
    }

    /**
     * ����ת��������ת�෴
     * 
     * @param h
     * @return
     */
    private Node rotateLeft(Node h) {
        // assert (h != null) && isRed(h.right);
        Node x = h.right;
        h.right = x.left;
        x.left = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = size(h.left) + size(h.right) + 1;
        return x;
    }

    /**
     * ��ɫ��ת��ע�⣺h�������������ӽڵ���ɫ�෴
     * 
     * @param h
     */
    private void flipColors(Node h) {
        // assert (h != null) && (h.left != null) && (h.right != null);
        // assert (!isRed(h) && isRed(h.left) && isRed(h.right))
        // || (isRed(h) && !isRed(h.left) && !isRed(h.right));
        h.color = !h.color;
        h.left.color = !h.left.color;
        h.right.color = !h.right.color;
    }

    /**
     * ���h�ڵ��Ǻ�ɫ�ڵ㣬 ���� h.right��h.right.left�Ǻ�ɫ����h.right������ĳ���ӽڵ��Ϊ��ɫ
     * 
     * @param h
     * @return
     */
    private Node moveRedRight(Node h) {
        // assert (h != null);
        // assert isRed(h) && !isRed(h.right) && !isRed(h.right.left);
        flipColors(h);
        if (isRed(h.left.left)) {
            h = rotateRight(h);
            flipColors(h);
        }
        return h;
    }

    /**
     * ���h�ڵ��Ǻ�ɫ�ڵ㣬���� h.left��h.left.left�Ǻ�ɫ���� h.left������ĳ���ӽڵ��Ϊ��ɫ
     * 
     * @param h
     * @return
     */
    private Node moveRedLeft(Node h) {
        // assert (h != null);
        // assert isRed(h) && !isRed(h.left) && !isRed(h.left.left);

        flipColors(h);
        if (isRed(h.right.left)) {
            h.right = rotateRight(h.right);
            h = rotateLeft(h);
            flipColors(h);
        }
        return h;
    }

    private Node balance(Node h) {
        // assert (h != null);

        if (isRed(h.right)) {
            h = rotateLeft(h);
        }
        if (isRed(h.left) && isRed(h.left.left)) {
            h = rotateRight(h);
        }
        if (isRed(h.left) && isRed(h.right)) {
            flipColors(h);
        }

        h.N = size(h.left) + size(h.right) + 1;
        return h;
    }

    /**
     * �����ֵ��
     * 
     * @param key
     * @param value
     */
    public void put(K key, V value) {
        if (key == null) {
            throw new NullPointerException("key����Ϊ��");
        }
        if (value == null) {
            delete(key);
            return;
        }

        root = put(root, key, value);
        root.color = BLACK;
        assert check();
    }

    /**
     * ����hΪ���ڵ�������в����ֵ��
     * 
     * @param h
     * @param key
     * @param value
     * @return
     */
    private Node put(Node h, K key, V value) {
        if (h == null) {
            return new Node(key, value, RED, 1);
        }

        int cmp = key.compareTo(h.key);
        if (cmp < 0) {
            h.left = put(h.left, key, value);
        } else if (cmp > 0) {
            h.right = put(h.right, key, value);
        } else {
            h.value = value;
        }

        // ��������������б�ĺ�����
        if (isRed(h.right) && !isRed(h.left)) {
            h = rotateLeft(h);
        }
        if (isRed(h.left) && isRed(h.left.left)) {
            h = rotateRight(h);
        }
        if (isRed(h.left) && isRed(h.right)) {
            flipColors(h);
        }
        h.N = size(h.left) + size(h.right) + 1;

        return h;
    }

    public void deleteMin() {
        if (isEmpty()) {
            throw new NoSuchElementException("�ú����Ϊ��,�޷�ɾ��������");
        }

        if (!isRed(root.left) && !isRed(root.right)) {
            root.color = RED;
        }

        root = deleteMin(root);
        if (!isEmpty()) {
            root.color = BLACK;
        }
        assert check();
    }

    private Node deleteMin(Node h) {
        if (h.left == null) {
            return null;
        }

        if (!isRed(h.left) && !isRed(h.left.left)) {
            h = moveRedLeft(h);
        }

        h.left = deleteMin(h.left);
        return balance(h);
    }

    public void deleteMax() {
        if (isEmpty()) {
            throw new NoSuchElementException("�ú����Ϊ��, �޷�ɾ��������");
        }

        // if both children of root are black, set root to red
        if (!isRed(root.left) && !isRed(root.right)) {
            root.color = RED;
        }

        root = deleteMax(root);
        if (!isEmpty()) {
            root.color = BLACK;
        }
        assert check();
    }

    private Node deleteMax(Node h) {
        if (isRed(h.left)) {
            h = rotateRight(h);
        }

        if (h.right == null) {
            return null;
        }

        if (!isRed(h.right) && !isRed(h.right.left)) {
            h = moveRedRight(h);
        }

        h.right = deleteMax(h.right);

        return balance(h);
    }

    public void delete(K key) {
        if (key == null) {
            throw new NullPointerException("key����Ϊ��");
        }
        if (!contains(key)) {
            return;
        }

        // ��������ӽڵ����ɫ��Ϊ��ɫ������root�ڵ�Ϊ��ɫ
        if (!isRed(root.left) && !isRed(root.right)) {
            root.color = RED;
        }

        root = delete(root, key);
        if (!isEmpty()) {
            root.color = BLACK;
        }
        assert check();
    }

    private Node delete(Node h, K key) {
        // assert get(h, key) != null;

        if (key.compareTo(h.key) < 0) {
            if (!isRed(h.left) && !isRed(h.left.left)) {
                h = moveRedLeft(h);
            }
            h.left = delete(h.left, key);
        } else {
            if (isRed(h.left)) {
                h = rotateRight(h);
            }
            if (key.compareTo(h.key) == 0 && (h.right == null)) {
                return null;
            }
            if (!isRed(h.right) && !isRed(h.right.left)) {
                h = moveRedRight(h);
            }
            if (key.compareTo(h.key) == 0) {
                Node x = min(h.right);
                h.key = x.key;
                h.value = x.value;
                // h.val = get(h.right, min(h.right).key);
                // h.key = min(h.right).key;
                h.right = deleteMin(h.right);
            } else {
                h.right = delete(h.right, key);
            }
        }
        return balance(h);
    }

    /**
     * �������ĸ߶�
     * 
     * @return
     */
    public int height() {
        return height(root);
    }

    private int height(Node x) {
        if (x == null) {
            return -1;
        }
        return 1 + Math.max(height(x.left), height(x.right));
    }

    /**
     * ������С��
     * 
     * @return
     */
    public K min() {
        if (isEmpty()) {
            throw new NoSuchElementException("�ú����Ϊ�գ�û���κνڵ�");
        }
        return min(root).key;
    }

    private Node min(Node x) {
        // assert x != null;
        if (x.left == null) {
            return x;
        } else {
            return min(x.left);
        }
    }

    public K max() {
        if (isEmpty()) {
            throw new NoSuchElementException("�ú����Ϊ�գ�û���κνڵ�");
        }
        return max(root).key;
    }

    /**
     * ������xΪ���ڵ�������е�����key
     * 
     * @param x
     * @return
     */
    private Node max(Node x) {
        // assert x != null;
        if (x.right == null) {
            return x;
        } else {
            return max(x.right);
        }
    }

    public K floor(K key) {
        if (key == null) {
            throw new NullPointerException("key����Ϊ��");
        }
        if (isEmpty()) {
            throw new NoSuchElementException("�ú����Ϊ�գ�û���κνڵ�");
        }
        Node x = floor(root, key);
        if (x == null) {
            return null;
        } else {
            return x.key;
        }
    }

    /**
     * ���ش�������xΪ���ڵ�������еģ� ����ֵС�ڻ����key������
     * 
     * @param x
     * @param key
     * @return
     */
    private Node floor(Node x, K key) {
        if (x == null) {
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp == 0) {
            return x;
        }
        if (cmp < 0) {
            return floor(x.left, key);
        }
        Node t = floor(x.right, key);
        if (t != null) {
            return t;
        } else {
            return x;
        }
    }

    public K ceiling(K key) {
        if (key == null) {
            throw new NullPointerException("key����Ϊ��");
        }
        if (isEmpty()) {
            throw new NoSuchElementException("�ú����Ϊ�գ�û���κνڵ�");
        }
        Node x = ceiling(root, key);
        if (x == null) {
            return null;
        } else {
            return x.key;
        }
    }

    /**
     * ������xΪ���ڵ�������У� ���ڻ����key����С��
     * 
     * @param x
     * @param key
     * @return
     */
    private Node ceiling(Node x, K key) {
        if (x == null) {
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp == 0) {
            return x;
        }
        if (cmp > 0) {
            return ceiling(x.right, key);
        }
        Node t = ceiling(x.left, key);
        if (t != null) {
            return t;
        } else {
            return x;
        }
    }

    public K select(int k) {
        if (k < 0 || k >= size()) {
            throw new IllegalArgumentException();
        }
        Node x = select(root, k);
        return x.key;
    }

    /**
     * ������xΪ���ڵ�������У� ��С��������С���������Ҳ����������Ϊk�Ľڵ�
     * 
     * @param x
     * @param k
     * @return
     */
    private Node select(Node x, int k) {
        // assert x != null;
        // assert k >= 0 && k < size(x);
        int t = size(x.left);
        if (t > k) {
            return select(x.left, k);
        } else if (t < k) {
            return select(x.right, k - t - 1);
        } else {
            return x;
        }
    }

    public int rank(K key) {
        if (key == null) {
            throw new NullPointerException("key����Ϊ��");
        }
        return rank(key, root);
    }

    private int rank(K key, Node x) {
        if (x == null) {
            return 0;
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            return rank(key, x.left);
        } else if (cmp > 0) {
            return 1 + size(x.left) + rank(key, x.right);
        } else {
            return size(x.left);
        }
    }

    /**
     * �������ú�����е����м�
     * 
     * @return
     */
    public Iterable<K> keys() {
        if (isEmpty()) {
            return new LinkedList<K>();
        }
        return keys(min(), max());
    }

    /**
     * ����low~high��Χ�ڵļ�
     * 
     * @param low
     * @param high
     * @return
     */
    public Iterable<K> keys(K low, K high) {
        if (low == null)
            throw new NullPointerException("low����Ϊ��");
        if (high == null)
            throw new NullPointerException("high����Ϊ��");

        Queue<K> queue = new LinkedList<K>();
        // if (isEmpty() || lo.compareTo(hi) > 0) return queue;
        keys(root, queue, low, high);
        return queue;
    }

    /**
     * ����xΪ���ڵ�������еģ� ��Χ��low~high֮������м���ӵ������С�
     * �����ǣ������жϽڵ�x��Ӧ��key�ڲ���low~high��Χ�ڣ�������ӵ�������
     * ����������ӡ�Ȼ��ݹ���ã��ж�����ڵ���ҽڵ��ڲ���low~highָ���ķ�Χ�ڡ�
     * 
     * @param x
     * @param queue
     * @param low
     * @param high
     */
    private void keys(Node x, Queue<K> queue, K low, K high) {
        if (x == null) {
            return;
        }
        int cmplo = low.compareTo(x.key);
        int cmphi = high.compareTo(x.key);
        if (cmplo < 0) {
            keys(x.left, queue, low, high);
        }
        if (cmplo <= 0 && cmphi >= 0) {
            queue.add(x.key);
        }
        if (cmphi > 0) {
            keys(x.right, queue, low, high);
        }
    }

    private boolean check() {
        if (!isBST()) {
            System.out.println("������������Ķ���");
        }
        if (!isSizeConsistent()) {
            System.out.println("�ڵ���Ŀ��һ��");
        }
        if (!isRankConsistent()) {
            System.out.println("������һ��");
        }
        if (!is23()) {
            System.out.println("������2-3���Ķ���");
        }
        if (!isBalanced()) {
            System.out.println("������������������ɫƽ��");
        }
        return isBST() && isSizeConsistent() && isRankConsistent() && is23() && isBalanced();
    }

    /**
     * �жϺ�����Ƿ�������������������������Ķ��壨��ڵ�ȵ�ǰ�ڵ�С�� �ҽڵ�ȵ�ǰ�ڵ��
     * 
     * @return
     */
    private boolean isBST() {
        return isBST(root, null, null);
    }

    private boolean isBST(Node x, K min, K max) {
        if (x == null) {
            return true;
        }
        if (min != null && x.key.compareTo(min) <= 0) {
            return false;
        }
        if (max != null && x.key.compareTo(max) >= 0) {
            return false;
        }
        return isBST(x.left, min, x.key) && isBST(x.right, x.key, max);
    }

    /**
     * �ݹ��ж�ÿһ���ڵ�Ĵ�С�ǲ��ǵ��ڣ� size(x.left) + 1 + size(x.right)
     * 
     * @return
     */
    private boolean isSizeConsistent() {
        return isSizeConsistent(root);
    }

    private boolean isSizeConsistent(Node x) {
        if (x == null) {
            return true;
        }
        if (x.N != size(x.left) + size(x.right) + 1) {
            return false;
        }
        return isSizeConsistent(x.left) && isSizeConsistent(x.right);
    }

    /**
     * ͨ��select��rank������֤���������˴��Ķ���������ָ�������
     * 
     * @return
     */
    private boolean isRankConsistent() {
        for (int i = 0; i < size(); i++)
            if (i != rank(select(i))) {
                return false;
            }
        for (K key : keys()) {
            if (key.compareTo(select(rank(key))) != 0) {
                return false;
            }
        }
        return true;
    }

    /**
     * �ж��Ƿ���������������ߺ�������Ķ��塣ע�⣺������Ƕ�������һ�־���ʵ�֡��������Ķ������Լ���ѯ��
     * 
     * @return
     */
    private boolean is23() {
        return is23(root);
    }

    private boolean is23(Node x) {
        if (x == null) {
            return true;
        }
        if (isRed(x.right)) {
            return false;
        }
        if (x != root && isRed(x) && isRed(x.left)) {
            return false;
        }
        return is23(x.left) && is23(x.right);
    }

    /**
     * �жϴӸ��ڵ㵽Ҷ�ڵ������һ��·���ϵ��\���ӵ������Ƿ���ȣ�Ҳ���ж�23���Ƿ�����������ɫƽ�⣩
     * 
     * @return
     */
    private boolean isBalanced() {
        int black = 0; // number of black links on path from root to min
        Node x = root;
        // whileѭ��������ʱ�򣬿��Լ���ó���������ӵ����ڵ��·���ϵ��\���ӵ�����
        while (x != null) {
            if (!isRed(x)) {
                black++;
            }
            x = x.left;
        }
        return isBalanced(root, black);
    }

    /**
     * @param x
     * @param black
     * @return
     */
    private boolean isBalanced(Node x, int black) {
        if (x == null) {
            return black == 0;
        }
        if (!isRed(x)) {
            black--;
        }
        return isBalanced(x.left, black) && isBalanced(x.right, black);
    }

    public void recursiveInorder() {
        recursiveInorder(root);
    }

    /** �ݹ�ʵ��������� */
    private void recursiveInorder(Node node) {
        if (node != null) {
            recursiveInorder(node.left);
            visit(node);
            recursiveInorder(node.right);
        }
    }

    public void visit(Node node) {
        StringBuffer buff = new StringBuffer();
        if (node != null) {
            buff.append(" " + node.key + "[");
            String left = node.left != null ? node.left.key + "" : "null";
            String right = node.right != null ? node.right.key + "" : "null";
            String color = node.color == RED ? "��" : "��";
            buff.append(left).append(" : ").append(right).append(" - ").append(color).append("] ");
        }
        System.out.print(buff.toString());
    }
    public static void main(String... args) {
        RBTree<Integer, String> st = new RBTree<Integer, String>();
        st.put(1, "       one");
        st.put(2, "                two");
        st.put(3, "           three");
        st.put(4, "           four");
        st.put(5, "           five");
        st.put(6, "           six");
        st.put(7, "           seven");
        st.put(8, "           eight");
        st.put(9, "           nine");
        st.put(10, "               ten");
        st.put(11, "            eleven");
        st.put(21, "              twelve");
        st.put(31, "          thirteen");

// ��Ӻ�õ��ĺ��������ͼ������*�ŵĽڵ��Ǻ�ɫ�ڵ� ����Ӻ�������������ɫƽ���             
//                          8
//                        /   \
//                       /     \
//                      /       \
//                     4*        21
//                    / \       / \
//                   2   6     10* 31
//                  /\   /\    /\
//                 /  \ 5  7  /  \
//                1    3     9   11

        System.out.println("����ֵ��Ĵ�С��" + st.size());
        for (Integer s : st.keys()) {
            System.out.print(st.get(s) + "  ");
        }
        System.out.println();


        st.recursiveInorder();
        System.out.println();
        System.out.println();

        st.delete(8);
        st.delete(10);
        st.delete(5);
        st.delete(3);
        st.delete(4);
        System.out.println("ɾ��ֵ��Ĵ�С��:" + st.size());
        for (Integer s : st.keys()) {
            System.out.print(st.get(s) + "  ");
        }
        System.out.println();

// ɾ����õ��ĺ��������ͼ������*�ŵĽڵ��Ǻ�ɫ�ڵ� ��ɾ����������Ȼ��������ɫƽ���              
//                 9
//              /    \
//             /      \
//            6       21
//           / \     /  \
//          2   7   11  31
//         /
//        1*
        st.recursiveInorder();
    }


}
