#include "BTreeNode.h"

template<typename Type> class BTree{
public:
    BTree(int size): m_nMaxSize(size), m_proot(NULL){}
    ~BTree();
    Triple<Type> Search(const Type item);
    int Size();
    int Size(BTreeNode<Type> *root);
    bool Insert(const Type item);   //insert item
    bool Remove(const Type item);   //delete item
    void Print();                   //print the BTree
    BTreeNode<Type> *GetParent(const Type item);

private:
    //insert the pright and item to pinsert in the nth place;
    void InsertKey(BTreeNode<Type> *pinsert, int n, const Type item, BTreeNode<Type> *pright);

    void PreMove(BTreeNode<Type> *root, int n); //move ahead

    //merge the child tree
    void Merge(BTreeNode<Type> *pleft, BTreeNode<Type> *pparent, BTreeNode<Type> *pright, int n);

    //adjust with the parent and the left child tree
    void LeftAdjust(BTreeNode<Type> *pright, BTreeNode<Type> *pparent, int min, int n);

    //adjust with the parent and the left child tree
    void RightAdjust(BTreeNode<Type> *pleft, BTreeNode<Type> *pparent, int min, int n);

    void Print(BTreeNode<Type> *start, int n = 0);

private:
    BTreeNode<Type> *m_proot;
    const int m_nMaxSize;
};


template<typename Type> BTree<Type>::~BTree(){
    m_proot->Destroy(m_proot);
}
template<typename Type> Triple<Type> BTree<Type>::Search(const Type item){
    Triple<Type> result;
    BTreeNode<Type> *pmove = m_proot, *parent = NULL;
    int i = 0;
    while (pmove){
        i = -1;
        while (item > pmove->m_pkey[++i]); //find the suit position
        if (pmove->m_pkey[i] == item){
            result.m_pfind = pmove;
            result.m_nfind = i;
            result.m_ntag = 1;
            return result;
        }
        parent = pmove;
        pmove = pmove->m_ptr[i];    //find in the child tree
    }
    result.m_pfind = parent;
    result.m_nfind = i;
    result.m_ntag = 0;
    return result;
}

template<typename Type> void BTree<Type>::InsertKey(BTreeNode<Type> *pinsert, int n, const Type item, BTreeNode<Type> *pright){
    pinsert->m_nsize++;
    for (int i=pinsert->m_nsize; i>n; i--){
        pinsert->m_pkey[i] = pinsert->m_pkey[i-1];
        pinsert->m_ptr[i+1] = pinsert->m_ptr[i];
    }
    pinsert->m_pkey[n] = item;
    pinsert->m_ptr[n+1] = pright;

    if (pinsert->m_ptr[n+1]){       //change the right child tree's parent
        pinsert->m_ptr[n+1]->m_pparent = pinsert;
        for (int i=0; i<=pinsert->m_ptr[n+1]->m_nsize; i++){
            if (pinsert->m_ptr[n+1]->m_ptr[i]){
                pinsert->m_ptr[n+1]->m_ptr[i]->m_pparent = pinsert->m_ptr[n+1];
            }
        }
    }

}
template<typename Type> bool BTree<Type>::Insert(const Type item){
    if (NULL == m_proot){       //insert the first node
        m_proot = new BTreeNode<Type>(m_nMaxSize);
        m_proot->m_nsize = 1;
        m_proot->m_pkey[1] = m_proot->m_pkey[0];
        m_proot->m_pkey[0] = item;
        m_proot->m_ptr[0] = m_proot->m_ptr[1] =NULL;
        return 1;
    }
    Triple<Type> find = this->Search(item); //search the position
    if (find.m_ntag){
        cerr << "The item is exist!" << endl;
        return 0;
    }
    BTreeNode<Type> *pinsert = find.m_pfind, *newnode;
    BTreeNode<Type> *pright = NULL, *pparent;
    Type key = item;
    int n = find.m_nfind;

    while (1){
        if (pinsert->m_nsize < pinsert->m_nMaxSize-1){  //There is some space
            InsertKey(pinsert, n, key, pright);
            return 1;
        }

        int m = (pinsert->m_nsize + 1) / 2;     //get the middle item
        InsertKey(pinsert, n, key, pright);     //insert first, then break up
        newnode = new BTreeNode<Type>(this->m_nMaxSize);//create the newnode for break up

        //break up
        for (int i=m+1; i<=pinsert->m_nsize; i++){
            newnode->m_pkey[i-m-1] = pinsert->m_pkey[i];
            newnode->m_ptr[i-m-1] = pinsert->m_ptr[i];
            pinsert->m_pkey[i] = pinsert->m_Infinity;
            pinsert->m_ptr[i] = NULL;
        }
        newnode->m_nsize = pinsert->m_nsize - m - 1;
        pinsert->m_nsize = m;

        for (int i=0; i<=newnode->m_nsize; i++){    //change the parent
            if (newnode->m_ptr[i]){
                newnode->m_ptr[i]->m_pparent = newnode;
                for (int j=0; j<=newnode->m_ptr[i]->m_nsize; j++){
                    if (newnode->m_ptr[i]->m_ptr[j]){
                        newnode->m_ptr[i]->m_ptr[j]->m_pparent = newnode->m_ptr[i];
                    }
                }
            }
        }
        for (int i=0; i<=pinsert->m_nsize; i++){    //change the parent
            if (pinsert->m_ptr[i]){
                pinsert->m_ptr[i]->m_pparent = pinsert;
                for (int j=0; j<=pinsert->m_nsize; j++){
                    if (pinsert->m_ptr[i]->m_ptr[j]){
                        pinsert->m_ptr[i]->m_ptr[j]->m_pparent = pinsert->m_ptr[i];
                    }
                }
            }
        }
        //break up over

        key = pinsert->m_pkey[m];
        pright = newnode;
        if (pinsert->m_pparent){    //insert the key to the parent
            pparent = pinsert->m_pparent;
            n = -1;
            pparent->m_pkey[pparent->m_nsize] = pparent->m_Infinity;
            while (key > pparent->m_pkey[++n]);
            newnode->m_pparent = pinsert->m_pparent;
            pinsert = pparent;
        }
        else {              //create new root
            m_proot = new BTreeNode<Type>(this->m_nMaxSize);
            m_proot->m_nsize = 1;
            m_proot->m_pkey[1] = m_proot->m_pkey[0];
            m_proot->m_pkey[0] = key;
            m_proot->m_ptr[0] = pinsert;
            m_proot->m_ptr[1] = pright;
            newnode->m_pparent = pinsert->m_pparent = m_proot;
            return 1;
        }
    }
}

template<typename Type> void BTree<Type>::PreMove(BTreeNode<Type> *root, int n){
    root->m_pkey[root->m_nsize] = root->m_Infinity;
    for (int i=n; i<root->m_nsize; i++){
        root->m_pkey[i] = root->m_pkey[i+1];
        root->m_ptr[i+1] = root->m_ptr[i+2];
    }

    root->m_nsize--;
}

template<typename Type> void BTree<Type>::Merge(BTreeNode<Type> *pleft, BTreeNode<Type> *pparent, BTreeNode<Type> *pright, int n){
    pleft->m_pkey[pleft->m_nsize] = pparent->m_pkey[n];
    BTreeNode<Type> *ptemp;

    for (int i=0; i<=pright->m_nsize; i++){ //merge the two child tree and the parent
        pleft->m_pkey[pleft->m_nsize+i+1] = pright->m_pkey[i];
        pleft->m_ptr[pleft->m_nsize+i+1] = pright->m_ptr[i];
        ptemp = pleft->m_ptr[pleft->m_nsize+i+1];
        if (ptemp){         //change thd right child tree's parent
            ptemp->m_pparent = pleft;
            for (int j=0; j<=ptemp->m_nsize; j++){
                if (ptemp->m_ptr[j]){
                    ptemp->m_ptr[j]->m_pparent = ptemp;
                }
            }
        }
    }

    pleft->m_nsize = pleft->m_nsize + pright->m_nsize + 1;
    delete pright;
    PreMove(pparent, n);
//    this->Print();
}

template<typename Type> void BTree<Type>::LeftAdjust(BTreeNode<Type> *pright, BTreeNode<Type> *pparent, int min, int n){
    BTreeNode<Type> *pleft = pparent->m_ptr[n-1], *ptemp;
    if (pleft->m_nsize > min-1){
        for (int i=pright->m_nsize+1; i>0; i--){
            pright->m_pkey[i] = pright->m_pkey[i-1];
            pright->m_ptr[i] = pright->m_ptr[i-1];
        }
        pright->m_pkey[0] = pparent->m_pkey[n-1];

        pright->m_ptr[0] = pleft->m_ptr[pleft->m_nsize];
        ptemp = pright->m_ptr[0];
        if (ptemp){     //change the tree's parent which is moved
            ptemp->m_pparent = pright;
            for (int i=0; i<ptemp->m_nsize; i++){
                if (ptemp->m_ptr[i]){
                    ptemp->m_ptr[i]->m_pparent = ptemp;
                }
            }
        }
        pparent->m_pkey[n-1] = pleft->m_pkey[pleft->m_nsize-1];
        pleft->m_pkey[pleft->m_nsize] = pleft->m_Infinity;
        pleft->m_nsize--;
        pright->m_nsize++;
    }
    else {
        Merge(pleft, pparent, pright, n-1);
    }
//       this->Print();
}

template<typename Type> void BTree<Type>::RightAdjust(BTreeNode<Type> *pleft, BTreeNode<Type> *pparent, int min, int n){
    BTreeNode<Type> *pright = pparent->m_ptr[1], *ptemp;
    if (pright && pright->m_nsize > min-1){
        pleft->m_pkey[pleft->m_nsize] = pparent->m_pkey[0];
        pparent->m_pkey[0] = pright->m_pkey[0];
        pleft->m_ptr[pleft->m_nsize+1] = pright->m_ptr[0];
        ptemp = pleft->m_ptr[pleft->m_nsize+1];
        if (ptemp){         //change the tree's parent which is moved
            ptemp->m_pparent = pleft;
            for (int i=0; i<ptemp->m_nsize; i++){
                if (ptemp->m_ptr[i]){
                    ptemp->m_ptr[i]->m_pparent = ptemp;
                }
            }
        }
        pright->m_ptr[0] = pright->m_ptr[1];
        pleft->m_nsize++;
        PreMove(pright,0);
    }
    else {
        Merge(pleft, pparent, pright, 0);
    }
}


template<typename Type> bool BTree<Type>::Remove(const Type item){
    Triple<Type> result = this->Search(item);
    if (!result.m_ntag){
        return 0;
    }
    BTreeNode<Type> *pdel, *pparent, *pmin;
    int n = result.m_nfind;
    pdel = result.m_pfind;

    if (pdel->m_ptr[n+1] != NULL){  //change into delete leafnode
        pmin = pdel->m_ptr[n+1];
        pparent = pdel;
        while (pmin != NULL){
            pparent = pmin;
            pmin = pmin->m_ptr[0];
        }
        pdel->m_pkey[n] = pparent->m_pkey[0];
        pdel = pparent;
        n = 0;
    }

    PreMove(pdel, n); //delete the node

    int min = (this->m_nMaxSize + 1) / 2;
    while (pdel->m_nsize < min-1){  //if it is not a BTree, then adjust
        n = 0;
        pparent = pdel->m_pparent;
        if (NULL == pparent)
        {
            return 1;
        }
        while (n<= pparent->m_nsize && pparent->m_ptr[n]!=pdel){
            n++;
        }
        if (!n){
            RightAdjust(pdel, pparent, min, n); //adjust with the parent and the right child tree
        }
        else {
            LeftAdjust(pdel, pparent, min, n); //adjust with the parent and the left child tree
        }
        pdel = pparent;
        if (pdel == m_proot){
            break;
        }
    }
    if (!m_proot->m_nsize){         //the root is merged
        pdel = m_proot->m_ptr[0];
        delete m_proot;
        m_proot = pdel;
        m_proot->m_pparent = NULL;
        for (int i=0; i<m_proot->m_nsize; i++){
            if (m_proot->m_ptr[i]){
                m_proot->m_ptr[i]->m_pparent = m_proot;
            }
        }
    }
    return 1;
}

template<typename Type> void BTree<Type>::Print(BTreeNode<Type> *start, int n){
    if (NULL == start){
        return;
    }
    if (start->m_ptr[0]){
        Print(start->m_ptr[0], n+1);    //print the first child tree
    }
    else {
        for (int j=0; j<n; j++){
            cout << "     ";
        }
        cout << "NULL" << endl;
    }

    for (int i=0; i<start->m_nsize; i++){   //print the orther child tree
        for (int j=0; j<n; j++){
            cout << "     ";
        }
        cout << start->m_pkey[i] << "--->" <<endl;
        if (start->m_ptr[i+1]){
            Print(start->m_ptr[i+1], n+1);
        }
        else {
            for (int j=0; j<n; j++){
                cout << "     ";
            }
            cout << "NULL" << endl;
        }
    }
}

template<typename Type> void BTree<Type>::Print(){
    Print(m_proot);
}

template<typename Type> int BTree<Type>::Size(BTreeNode<Type> *root){
    if (NULL == root){
        return 0;
    }
    int size=root->m_nsize;
    for (int i=0; i<=root->m_nsize; i++){
        if (root->m_ptr[i]){
            size += this->Size(root->m_ptr[i]);
        }
    }
    return size;
}

template<typename Type> int BTree<Type>::Size(){
    return this->Size(this->m_proot);
}

template<typename Type> BTreeNode<Type>* BTree<Type>::GetParent(const Type item){
    Triple<Type> result = this->Search(item);
    return result.m_pfind->m_pparent;
}
