package BPlusTree;

/**
 * ʵ��B+��
 *
 * @param <T> ָ��ֵ����
 * @param <V> ʹ�÷��ͣ�ָ����������,����ָ������̳�Comparable
 */
public class BPlusTree <T, V extends Comparable<V>>{
    //B+���Ľ�
    private Integer bTreeOrder;
    //B+���ķ�Ҷ�ӽڵ���Сӵ�е��ӽڵ�������ͬʱҲ�Ǽ�����С������
    //private Integer minNUmber;
    //B+���ķ�Ҷ�ӽڵ����ӵ�еĽڵ�������ͬʱҲ�Ǽ������������
    private Integer maxNumber;

    private Node<T, V> root;

    private LeafNode<T, V> left;

    //�޲ι��췽����Ĭ�Ͻ�Ϊ3
    public BPlusTree(){
        this(3);
    }

    //�вι��췽���������趨B+���Ľ�
    public BPlusTree(Integer bTreeOrder){
        this.bTreeOrder = bTreeOrder;
        //this.minNUmber = (int) Math.ceil(1.0 * bTreeOrder / 2.0);
        //��Ϊ����ڵ�����п��ܳ��ֳ������޵����,��������Ҫ��1
        this.maxNumber = bTreeOrder + 1;
        this.root = new LeafNode<T, V>();
        this.left = null;
    }

    //��ѯ
    public T find(V key){
        T t = this.root.find(key);
        if(t == null){
            System.out.println("������");
        }
        return t;
    }

    //����
    public void insert(T value, V key){
        if(key == null)
            return;
        Node<T, V> t = this.root.insert(value, key);
        if(t != null)
            this.root = t;
        this.left = (LeafNode<T, V>)this.root.refreshLeft();

//        System.out.println("�������,��ǰ���ڵ�Ϊ:");
//        for(int j = 0; j < this.root.number; j++) {
//            System.out.print((V) this.root.keys[j] + " ");
//        }
//        System.out.println();
    }


    /**
     * �ڵ㸸�࣬��Ϊ��B+���У���Ҷ�ӽڵ㲻�ô洢��������ݣ�ֻ��Ҫ��������Ϊ���Ϳ�����
     * ����Ҷ�ӽڵ�ͷ�Ҷ�ӽڵ���಻̫һ���������ֻṫ��һЩ������������Node����Ϊ����,
     * ������ΪҪ�������һЩ���з���������ʹ�ó�����
     *
     * @param <T> ͬBPlusTree
     * @param <V>
     */
    abstract class Node<T, V extends Comparable<V>>{
        //���ڵ�
        protected Node<T, V> parent;
        //�ӽڵ�
        protected Node<T, V>[] childs;
        //�����ӽڵ㣩����
        protected Integer number;
        //��
        protected Object keys[];

        //���췽��
        public Node(){
            this.keys = new Object[maxNumber];
            this.childs = new Node[maxNumber];
            this.number = 0;
            this.parent = null;
        }

        //����
        abstract T find(V key);

        //����
        abstract Node<T, V> insert(T value, V key);

        abstract LeafNode<T, V> refreshLeft();
    }


    /**
     * ��Ҷ�ڵ���
     * @param <T>
     * @param <V>
     */

    class BPlusNode <T, V extends Comparable<V>> extends Node<T, V>{

        public BPlusNode() {
            super();
        }

        /**
         * �ݹ����,����ֻ��Ϊ��ȷ��ֵ��������һ��,�����Ĳ��ҵ�Ҷ�ӽڵ�Ż��
         * @param key
         * @return
         */
        @Override
        T find(V key) {
            int i = 0;
            while(i < this.number){
                if(key.compareTo((V) this.keys[i]) <= 0)
                    break;
                i++;
            }
            if(this.number == i)
                return null;
            return this.childs[i].find(key);
        }

        /**
         * �ݹ����,�Ȱ�ֵ���뵽��Ӧ��Ҷ�ӽڵ�,���ս�����Ҷ�ӽڵ�Ĳ�����
         * @param value
         * @param key
         */
        @Override
        Node<T, V> insert(T value, V key) {
            int i = 0;
            while(i < this.number){
                if(key.compareTo((V) this.keys[i]) < 0)
                    break;
                i++;
            }
            if(key.compareTo((V) this.keys[this.number - 1]) >= 0) {
                i--;
//                if(this.childs[i].number + 1 <= bTreeOrder) {
//                    this.keys[this.number - 1] = key;
//                }
            }

//            System.out.println("��Ҷ�ӽڵ����key: " + this.keys[i]);

            return this.childs[i].insert(value, key);
        }

        @Override
        LeafNode<T, V> refreshLeft() {
            return this.childs[0].refreshLeft();
        }

        /**
         * ��Ҷ�ӽڵ����ɹ���ɷֽ�ʱ,�ݹ���򸸽ڵ�����µĽڵ��Ա���ƽ��
         * @param node1
         * @param node2
         * @param key
         */
        Node<T, V> insertNode(Node<T, V> node1, Node<T, V> node2, V key){

//            System.out.println("��Ҷ�ӽڵ�,����key: " + node1.keys[node1.number - 1] + " " + node2.keys[node2.number - 1]);

            V oldKey = null;
            if(this.number > 0)
                oldKey = (V) this.keys[this.number - 1];
            //���ԭ��keyΪnull,˵������ǽڵ��ǿյ�,ֱ�ӷ��������ڵ㼴��
            if(key == null || this.number <= 0){
//                System.out.println("��Ҷ�ӽڵ�,����key: " + node1.keys[node1.number - 1] + " " + node2.keys[node2.number - 1] + "ֱ�Ӳ���");
                this.keys[0] = node1.keys[node1.number - 1];
                this.keys[1] = node2.keys[node2.number - 1];
                this.childs[0] = node1;
                this.childs[1] = node2;
                this.number += 2;
                return this;
            }
            //ԭ�нڵ㲻Ϊ��,��Ӧ����Ѱ��ԭ�нڵ��λ��,Ȼ���µĽڵ���뵽ԭ�нڵ���
            int i = 0;
            while(key.compareTo((V)this.keys[i]) != 0){
                i++;
            }
            //��߽ڵ�����ֵ����ֱ�Ӳ���,�ұߵ�ҪŲһŲ�ٽ��в���
            this.keys[i] = node1.keys[node1.number - 1];
            this.childs[i] = node1;

            Object tempKeys[] = new Object[maxNumber];
            Object tempChilds[] = new Node[maxNumber];

            System.arraycopy(this.keys, 0, tempKeys, 0, i + 1);
            System.arraycopy(this.childs, 0, tempChilds, 0, i + 1);
            System.arraycopy(this.keys, i + 1, tempKeys, 0, this.number - i - 1);
            System.arraycopy(this.childs, i + 1, tempChilds, 0, this.number - i - 1);
            tempKeys[i + 1] = node2.keys[node2.number - 1];
            tempChilds[i + 1] = node2;

            this.number++;

            //�ж��Ƿ���Ҫ���
            //�������Ҫ���,�����鸴�ƻ�ȥ,ֱ�ӷ���
            if(this.number <= bTreeOrder){
                System.arraycopy(tempKeys, 0, this.keys, 0, this.number);
                System.arraycopy(tempChilds, 0, this.childs, 0, this.number);

//                System.out.println("��Ҷ�ӽڵ�,����key: " + node1.keys[node1.number - 1] + " " + node2.keys[node2.number - 1] + ", ����Ҫ���");

                return null;
            }

//            System.out.println("��Ҷ�ӽڵ�,����key: " + node1.keys[node1.number - 1] + " " + node2.keys[node2.number - 1] + ",��Ҫ���");

            //�����Ҫ���,�Ͳ�Ҷ�ӽڵ�ʱ����,���м��
            Integer middle = this.number / 2;

            //�½���Ҷ�ӽڵ�,��Ϊ��ֵ��Ұ벿��
            BPlusNode<T, V> tempNode = new BPlusNode<T, V>();
            //��Ҷ�ڵ��ֺ�Ӧ�ý����ӽڵ�ĸ��ڵ�ָ�����Ϊ��ȷ��ָ��
            tempNode.number = this.number - middle;
            tempNode.parent = this.parent;
            //������ڵ�Ϊ��,���½�һ����Ҷ�ӽڵ���Ϊ���ڵ�,�����ò�ֳɹ���������Ҷ�ӽڵ��ָ��ָ�򸸽ڵ�
            if(this.parent == null) {

//                System.out.println("��Ҷ�ӽڵ�,����key: " + node1.keys[node1.number - 1] + " " + node2.keys[node2.number - 1] + ",�½����ڵ�");

                BPlusNode<T, V> tempBPlusNode = new BPlusNode<>();
                tempNode.parent = tempBPlusNode;
                this.parent = tempBPlusNode;
                oldKey = null;
            }
            System.arraycopy(tempKeys, middle, tempNode.keys, 0, tempNode.number);
            System.arraycopy(tempChilds, middle, tempNode.childs, 0, tempNode.number);
            for(int j = 0; j < tempNode.number; j++){
                tempNode.childs[j].parent = tempNode;
            }
            //��ԭ�з�Ҷ�ӽڵ���Ϊ��߽ڵ�
            this.number = middle;
            this.keys = new Object[maxNumber];
            this.childs = new Node[maxNumber];
            System.arraycopy(tempKeys, 0, this.keys, 0, middle);
            System.arraycopy(tempChilds, 0, this.childs, 0, middle);

            //Ҷ�ӽڵ��ֳɹ���,��Ҫ�������ɵĽڵ���븸�ڵ�
            BPlusNode<T, V> parentNode = (BPlusNode<T, V>)this.parent;
            return parentNode.insertNode(this, tempNode, oldKey);
        }

    }

    /**
     * Ҷ�ڵ���
     * @param <T>
     * @param <V>
     */
    class LeafNode <T, V extends Comparable<V>> extends Node<T, V> {

        protected Object values[];
        protected LeafNode left;
        protected LeafNode right;

        public LeafNode(){
            super();
            this.values = new Object[maxNumber];
            this.left = null;
            this.right = null;
        }

        /**
         * ���в���,������ֲ���,�����ע��
         * @param key
         * @return
         */
        @Override
        T find(V key) {
            if(this.number <=0)
                return null;

//            System.out.println("Ҷ�ӽڵ����");

            Integer left = 0;
            Integer right = this.number;

            Integer middle = (left + right) / 2;

            while(left < right){
                V middleKey = (V) this.keys[middle];
                if(key.compareTo(middleKey) == 0)
                    return (T) this.values[middle];
                else if(key.compareTo(middleKey) < 0)
                    right = middle;
                else
                    left = middle;
                middle = (left + right) / 2;
            }
            return null;
        }

        /**
         *
         * @param value
         * @param key
         */
        @Override
        Node<T, V> insert(T value, V key) {

//            System.out.println("Ҷ�ӽڵ�,����key: " + key);

            //����ԭʼ���ڸ��ڵ��keyֵ
            V oldKey = null;
            if(this.number > 0)
                oldKey = (V) this.keys[this.number - 1];
            //�Ȳ�������
            int i = 0;
            while(i < this.number){
                if(key.compareTo((V) this.keys[i]) < 0)
                    break;
                    i++;
            }

            //��������,������
            Object tempKeys[] = new Object[maxNumber];
            Object tempValues[] = new Object[maxNumber];
            System.arraycopy(this.keys, 0, tempKeys, 0, i);
            System.arraycopy(this.values, 0, tempValues, 0, i);
            System.arraycopy(this.keys, i, tempKeys, i + 1, this.number - i);
            System.arraycopy(this.values, i, tempValues, i + 1, this.number - i);
            tempKeys[i] = key;
            tempValues[i] = value;

            this.number++;

//            System.out.println("�������,��ǰ�ڵ�keyΪ:");
//            for(int j = 0; j < this.number; j++)
//                System.out.print(tempKeys[j] + " ");
//            System.out.println();

            //�ж��Ƿ���Ҫ���
            //�������Ҫ�����ɸ��ƺ�ֱ�ӷ���
            if(this.number <= bTreeOrder){
                System.arraycopy(tempKeys, 0, this.keys, 0, this.number);
                System.arraycopy(tempValues, 0, this.values, 0, this.number);

                //�п�����Ȼû�нڵ���ѣ�����ʵ���ϲ����ֵ������ԭ�������ֵ���������и��ڵ�ı߽�ֵ��Ҫ���и���
                Node node = this;
                while (node.parent != null){
                    V tempkey = (V)node.keys[node.number - 1];
                    if(tempkey.compareTo((V)node.parent.keys[node.parent.number - 1]) > 0){
                        node.parent.keys[node.parent.number - 1] = tempkey;
                        node = node.parent;
                    }
                }
//                System.out.println("Ҷ�ӽڵ�,����key: " + key + ",����Ҫ���");

                return null;
            }

//            System.out.println("Ҷ�ӽڵ�,����key: " + key + ",��Ҫ���");

            //�����Ҫ���,����м�ѽڵ��ֲ���������
            Integer middle = this.number / 2;

            //�½�Ҷ�ӽڵ�,��Ϊ��ֵ��Ұ벿��
            LeafNode<T, V> tempNode = new LeafNode<T, V>();
            tempNode.number = this.number - middle;
            tempNode.parent = this.parent;
            //������ڵ�Ϊ��,���½�һ����Ҷ�ӽڵ���Ϊ���ڵ�,�����ò�ֳɹ�������Ҷ�ӽڵ��ָ��ָ�򸸽ڵ�
            if(this.parent == null) {

//                System.out.println("Ҷ�ӽڵ�,����key: " + key + ",���ڵ�Ϊ�� �½����ڵ�");

                BPlusNode<T, V> tempBPlusNode = new BPlusNode<>();
                tempNode.parent = tempBPlusNode;
                this.parent = tempBPlusNode;
                oldKey = null;
            }
            System.arraycopy(tempKeys, middle, tempNode.keys, 0, tempNode.number);
            System.arraycopy(tempValues, middle, tempNode.values, 0, tempNode.number);

            //��ԭ��Ҷ�ӽڵ���Ϊ��ֵ���벿��
            this.number = middle;
            this.keys = new Object[maxNumber];
            this.values = new Object[maxNumber];
            System.arraycopy(tempKeys, 0, this.keys, 0, middle);
            System.arraycopy(tempValues, 0, this.values, 0, middle);

            this.right = tempNode;
            tempNode.left = this;

            //Ҷ�ӽڵ��ֳɹ���,��Ҫ�������ɵĽڵ���븸�ڵ�
            BPlusNode<T, V> parentNode = (BPlusNode<T, V>)this.parent;
            return parentNode.insertNode(this, tempNode, oldKey);
        }

        @Override
        LeafNode<T, V> refreshLeft() {
            if(this.number <= 0)
                return null;
            return this;
        }
    }
}