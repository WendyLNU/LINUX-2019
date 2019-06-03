template<typename Type> class BTree;

template<typename Type> class BTreeNode{
public:
    friend BTree<Type>;
    BTreeNode(): m_nMaxSize(0), m_ptr(NULL), m_pparent(NULL){}
    BTreeNode(int size): m_nsize(0), m_nMaxSize(size), m_pparent(NULL){
        m_pkey = new Type[size+1];
        m_ptr = new BTreeNode<Type> *[size+1];
        for (int i=0; i<=size; i++){
            m_ptr[i] = NULL;
            m_pkey[i] = this->m_Infinity;
        }
    }
    void Destroy(BTreeNode<Type> *root);
    ~BTreeNode(){
		if (m_nMaxSize){
			delete[] m_pkey;
			for (int i=0; i<=m_nMaxSize; i++){
				m_ptr[i] = NULL;
			}
		}
    }
    bool IsFull(){
        return m_nsize == m_nMaxSize;
    }
    Type GetKey(int i){
        if (this){
            return this->m_pkey[i];
        }
        return -1;
    }

private:
    int m_nsize;
    int m_nMaxSize;     //the Max Size of key
    Type *m_pkey;
    BTreeNode<Type> *m_pparent;
    BTreeNode<Type> **m_ptr;
    static const Type m_Infinity = 10000;
};

template<typename Type> struct Triple{
    BTreeNode<Type> *m_pfind;
    int m_nfind;
    bool m_ntag;
};

template<typename Type> void BTreeNode<Type>::Destroy(BTreeNode<Type> *root){
    if (NULL == root){
        return;
    }
    for (int i=0; i<root->m_nsize; i++){
        Destroy(root->m_ptr[i]);
    }
    delete root;
}
