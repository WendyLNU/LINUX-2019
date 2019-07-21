//
//  BPlusTree.c
//  BPlusTree
//
//  Created by Wuyixin on 2017/8/4.
//  Copyright ? 2017�� Coding365. All rights reserved.
//
 
#include "BTreePlus1.h"
 
static KeyType Unavailable = INT_MIN;  //INT-MIN��ֵ��ʲô��
						//��limits.h�ж����ֵ����С����-2147483648
 
/* ����һ���ڵ㲢��ʼ�� */
static BPlusTree MallocNewNode(){
    BPlusTree NewNode;
    int i;
    NewNode = (struct BPlusNode *)malloc(sizeof(struct BPlusNode)); //����BPlusNode���͵��ڴ�ռ�
    if (NewNode == NULL)
        exit(EXIT_FAILURE);//0��ʾ�����������ޣ�1��ʾ�������ڷ���
    i = 0;
    while (i < M + 1){
        NewNode->Key[i] = Unavailable;
        NewNode->Children[i] = NULL;
        i++;
    }
    NewNode->Next = NULL;
    NewNode->KeyNum = 0;
    
    return NewNode;
}
 
/* ��ʼ�� */
extern BPlusTree Initialize(){
    
    BPlusTree T;
    if (M < (3)){
        printf("M��С����3��");
        exit(EXIT_FAILURE);
    }
    /* ����� */
    T = MallocNewNode();
    
    return T;
}

// ��λ���ýڵ�P������ߣ���С������
static Position FindMostLeft(Position P){

    Position Tmp;
    
    Tmp = P;
    
    while (Tmp != NULL && Tmp->Children[0] != NULL) {
        Tmp = Tmp->Children[0];
    }
    return Tmp;
}
 
// ��λ���ýڵ�P�����ұߣ���󣩵ĺ���
static Position FindMostRight(Position P){
    Position Tmp;
    
    Tmp = P;
    
    while (Tmp != NULL && Tmp->Children[Tmp->KeyNum - 1] != NULL) {
        Tmp = Tmp->Children[Tmp->KeyNum - 1];
		//��Ϊ�ؼ��ָ�������0��ʼ���ģ��������һ��ӦΪKeyNum-1
    }
    return Tmp;
}
 
/* Ѱ��һ���ֵܽڵ㣬��洢�Ĺؼ���δ�������򷵻�NULL */
static Position FindSibling(Position Parent,int i){
	//���i������ʲô
	//�����Ǹýڵ����丸�ڵ�ĵڼ�(0...KeyNum)������
    Position Sibling;
    int Limit;
    
    Limit = M;
    
    Sibling = NULL;
    if (i == 0){
        if (Parent->Children[1]->KeyNum < Limit)
            Sibling = Parent->Children[1];
    }
	//�ȿ���ߵ��ֵܽڵ�ؼ�����û��
    else if (Parent->Children[i - 1]->KeyNum < Limit)
        Sibling = Parent->Children[i - 1];
	//�������ֵܹؼ���û�����ٿ��ұߵ��ֵ�
    else if (i + 1 < Parent->KeyNum && Parent->Children[i + 1]->KeyNum < Limit)
        Sibling = Parent->Children[i + 1];
    return Sibling;
}
 
/* �����ֵܽڵ㣬��ؼ���������M/2��û�з���NULL*/
static Position FindSiblingKeyNum_M_2(Position Parent,int i,int *j){

	//*j������ʲô

    int Limit;
    Position Sibling;
    Sibling = NULL;
    
    Limit = LIMIT_M_2;
    
    if (i == 0){
        if (Parent->Children[1]->KeyNum > Limit){
            Sibling = Parent->Children[1];
            *j = 1;
        }
    }
    else{
        if (Parent->Children[i - 1]->KeyNum > Limit){
            Sibling = Parent->Children[i - 1];
            *j = i - 1;
        }
        else if (i + 1 < Parent->KeyNum && Parent->Children[i + 1]->KeyNum > Limit){
            Sibling = Parent->Children[i + 1];
            *j = i + 1;
        }
        
    }
    
    return Sibling;
}

/*
   ��Ҫ��X����Key��ʱ��i��X��Parent��λ�ã�j��KeyҪ�����λ��
   ��Ҫ��Parent����X�ڵ��ʱ��i��Ҫ�����λ�ã�Key��j��ֵû����
*/
static Position InsertElement(int isKey, Position Parent,Position X,
							  KeyType Key,int i,int j){

	//isKey��ʾ�ǲ��ǲ���Key������ֵΪ1������Ϊ0

    int k;
    if (isKey){
        /* ����key */
        k = X->KeyNum - 1;
        while (k >= j){
            X->Key[k+1] = X->Key[k]; 
			k--;
        }
        
        X->Key[j] = Key;	
        
        if (Parent != NULL)
            Parent->Key[i] = X->Key[0]; 
			//�ýڵ��ڸ��ڵ��λ�õ�Keyֵ���ڸýڵ�����ڵ��ֵ

        X->KeyNum++;
        
    }else{/* ����ڵ� */
        
        /* ����Ҷ�ڵ�������� */
        if (X->Children[0] == NULL){
            if (i > 0)
                Parent->Children[i - 1]->Next = X;
            X->Next = Parent->Children[i];
        }
        
        k = Parent->KeyNum - 1;
        while (k >= i){
            Parent->Children[k + 1] = Parent->Children[k];
            Parent->Key[k + 1] = Parent->Key[k];
            k--;
        }

        Parent->Key[i] = X->Key[0];
        Parent->Children[i] = X;

        Parent->KeyNum++;
        
    }
    return X;
}

static Position RemoveElement(int isKey, Position Parent,Position X,int i,int j){
    
    int k,Limit;
    
    if (isKey){
        Limit = X->KeyNum;
        /* ɾ��key */
        k = j + 1;
        while (k < Limit){
            X->Key[k - 1] = X->Key[k];k++;
        }
        
        X->Key[X->KeyNum - 1] = Unavailable;
        
        Parent->Key[i] = X->Key[0];
        
        X->KeyNum--;
    }else{
        /* ɾ���ڵ� */
        
        /* �޸���Ҷ�ڵ������ */
        if (X->Children[0] == NULL && i > 0){
            Parent->Children[i - 1]->Next = Parent->Children[i + 1];
        }
        Limit = Parent->KeyNum;
        k = i + 1;
        while (k < Limit){
            Parent->Children[k - 1] = Parent->Children[k];
            Parent->Key[k - 1] = Parent->Key[k];
            k++;
        }
        
        Parent->Children[Parent->KeyNum - 1] = NULL;
        Parent->Key[Parent->KeyNum - 1] = Unavailable;
        
        Parent->KeyNum--;
        
    }
    return X;
}

/* Src��Dst���������ڵĽڵ㣬i��Src��Parent�е�λ�ã�
 ��Src��Ԫ���ƶ���Dst�� ,n���ƶ�Ԫ�صĸ���*/
static Position MoveElement(Position Src,Position Dst,Position Parent,int i,int n){
    KeyType TmpKey;
    Position Child;
    int j,SrcInFront;
    
    SrcInFront = 0;
    
    if (Src->Key[0] < Dst->Key[0])
        SrcInFront = 1;
    
    j = 0;
    /* �ڵ�Src��Dstǰ�� */
    if (SrcInFront){
        if (Src->Children[0] != NULL){
			//�м�ڵ�
            while (j < n) {
                Child = Src->Children[Src->KeyNum - 1];
                RemoveElement(0, Src, Child, Src->KeyNum - 1, Unavailable);
                InsertElement(0, Dst, Child, Unavailable, 0, Unavailable);
                j++;
            }
        }else{
			//Ҷ�ӽڵ�
            while (j < n) {
                TmpKey = Src->Key[Src->KeyNum -1];
                RemoveElement(1, Parent, Src, i, Src->KeyNum - 1);
                InsertElement(1, Parent, Dst, TmpKey, i + 1, 0);
                j++;
            }
            
        }
        
        Parent->Key[i + 1] = Dst->Key[0];
        /* ����Ҷ�ڵ��������� */
        if (Src->KeyNum > 0)
            FindMostRight(Src)->Next = FindMostLeft(Dst);
        
    }else{
        if (Src->Children[0] != NULL){
            while (j < n) {
                Child = Src->Children[0];
                RemoveElement(0, Src, Child, 0, Unavailable);
                InsertElement(0, Dst, Child, Unavailable, Dst->KeyNum, Unavailable);
                j++;
            }
            
        }else{
            while (j < n) {
                TmpKey = Src->Key[0];
                RemoveElement(1, Parent, Src, i, 0);
                InsertElement(1, Parent, Dst, TmpKey, i - 1, Dst->KeyNum);
                j++;
            }
            
        }
        
        Parent->Key[i] = Src->Key[0];
        if (Src->KeyNum > 0)
            FindMostRight(Dst)->Next = FindMostLeft(Src);
        
    }
    
    return Parent;
}

//����ڵ�
static BPlusTree SplitNode(Position Parent,Position X,int i){
    int j,k,Limit;
    Position NewNode;
    
    NewNode = MallocNewNode();
    
    k = 0;
    j = X->KeyNum / 2;
    Limit = X->KeyNum;
    while (j < Limit){
        if (X->Children[0] != NULL){
			//X�ĺ��Ӳ�Ϊ�յĻ�����һ��ĺ��Ӹ��½ڵ�
            NewNode->Children[k] = X->Children[j];
            X->Children[j] = NULL;
        }
        NewNode->Key[k] = X->Key[j];	//��һ���Keyֵ���½ڵ�
        X->Key[j] = Unavailable;
        NewNode->KeyNum++;X->KeyNum--;
        j++;k++;
    }
    
    if (Parent != NULL)
		//�����ڵ�����½ڵ�
        InsertElement(0, Parent, NewNode, Unavailable, i + 1, Unavailable);
    else{
        /* �����X�Ǹ�����ô�����µĸ������� */
        Parent = MallocNewNode();
        InsertElement(0, Parent, X, Unavailable, 0, Unavailable);
        InsertElement(0, Parent, NewNode, Unavailable, 1, Unavailable);
        
        return Parent;
    }
    
    return X;
}
 
/* �ϲ��ڵ�,X����M/2�ؼ��֣�S�д��ڻ����M/2���ؼ���*/
static Position MergeNode(Position Parent, Position X,
						  Position S,int i){
    int Limit;
    
    /* S�Ĺؼ�����Ŀ����M/2 */
    if (S->KeyNum > LIMIT_M_2){
        /* ��S���ƶ�һ��Ԫ�ص�X�� */
        MoveElement(S, X, Parent, i,1);
    }else{
        /* ��Xȫ��Ԫ���ƶ���S�У�����Xɾ�� */
        Limit = X->KeyNum;
        MoveElement(X,S, Parent, i,Limit);
        RemoveElement(0, Parent, X, i, Unavailable);
        
        free(X);
        X = NULL;
    }
    
    return Parent;
}

static BPlusTree RecursiveInsert(BPlusTree T,KeyType Key,
								 int i,BPlusTree Parent){
    int j,Limit;
    Position Sibling;
    
    /* ���ҷ�֧ */
    j = 0;
    while (j < T->KeyNum && Key >= T->Key[j]){
        /* �ظ�ֵ������ */
        if (Key == T->Key[j])
            return T;
        j++;
    }
    if (j!=0 && T->Children[0] != NULL) j--;
    
    /* �ڵ�T����Ҷ����ֱ����������� */
    if (T->Children[0] == NULL)
        T = InsertElement(1, Parent, T, Key, i, j);
    
    else
		/* �ڵ�T���ڲ��ڵ㣬��ѭ���ú�����ֱ�����뵽Ҷ�ӽڵ��� */
        T->Children[j] = RecursiveInsert(T->Children[j], Key, j, T);
    
    /* �����ڵ� */
    
    Limit = M;
    
    if (T->KeyNum > Limit){
        /* �� */
        if (Parent == NULL){
            /* ���ѽڵ� */
            T = SplitNode(Parent, T, i);
        }
        else{
            Sibling = FindSibling(Parent, i);
            if (Sibling != NULL){
                /* ��T��һ��Ԫ�أ�Key����Child���ƶ���Sibing�� */
                MoveElement(T, Sibling, Parent, i, 1);
            }else{
                /* ���ѽڵ� */
                T = SplitNode(Parent, T, i);
            }
        }
        
    }
    //���¸��ڵ������ֵ
    if (Parent != NULL)
        Parent->Key[i] = T->Key[0];
    
    return T;
}
 
/* ���� */
extern BPlusTree Insert(BPlusTree T,KeyType Key){
    return RecursiveInsert(T, Key, 0, NULL);
}
 
static BPlusTree RecursiveRemove(BPlusTree T,KeyType Key,int i,
								 BPlusTree Parent){
    
    int j,NeedAdjust;
    Position Sibling,Tmp;
    
    Sibling = NULL;
    
    /* ���ҷ�֧ */
    j = 0;
    while (j < T->KeyNum && Key >= T->Key[j]){
        if (Key == T->Key[j])
            break;
        j++;
    }
    
    if (T->Children[0] == NULL){
        /* û�ҵ� */
        if (Key != T->Key[j] || j == T->KeyNum)
            return T;
    }else
        if (j == T->KeyNum || Key < T->Key[j]) j--;
    
 
    /* ��Ҷ */
    if (T->Children[0] == NULL){
        T = RemoveElement(1, Parent, T, i, j);
    }else{
        T->Children[j] = RecursiveRemove(T->Children[j], Key, j, T);
    }
    
    NeedAdjust = 0;
    /* ���ĸ�������һƬ��Ҷ���������������2��M֮�� */
    if (Parent == NULL && T->Children[0] != NULL && T->KeyNum < 2)
        NeedAdjust = 1;
    /* �����⣬���з���Ҷ�ڵ�Ķ�������[M/2]��M֮�䡣(����[]��ʾ����ȡ��) */
    else if (Parent != NULL && T->Children[0] != NULL && T->KeyNum < LIMIT_M_2)
        NeedAdjust = 1;
    /* ���Ǹ�����Ҷ�йؼ��ֵĸ���Ҳ��[M/2]��M֮�� */
    else if (Parent != NULL && T->Children[0] == NULL && T->KeyNum < LIMIT_M_2)
        NeedAdjust = 1;
    
    /* �����ڵ� */
    if (NeedAdjust){
        /* �� */
        if (Parent == NULL){
            if(T->Children[0] != NULL && T->KeyNum < 2){
                Tmp = T;
                T = T->Children[0];
                free(Tmp);
                return T;
            }
        }else{
            /* �����ֵܽڵ㣬��ؼ�����Ŀ����M/2 */
            Sibling = FindSiblingKeyNum_M_2(Parent, i,&j);
            if (Sibling != NULL){
                MoveElement(Sibling, T, Parent, j, 1);
            }else{
                if (i == 0)
                    Sibling = Parent->Children[1];
                else
                    Sibling = Parent->Children[i - 1];
                
                Parent = MergeNode(Parent, T, Sibling, i);
                T = Parent->Children[i];
            }
        }
    }
    return T;
}
 
/* ɾ�� */
extern BPlusTree Remove(BPlusTree T,KeyType Key){
    return RecursiveRemove(T, Key, 0, NULL);
}
 
/* ���� */
extern BPlusTree Destroy(BPlusTree T){
    int i,j;
    if (T != NULL){
        i = 0;
        while (i < T->KeyNum + 1){
            Destroy(T->Children[i]);i++;
        }
        
        printf("Destroy:(");
        j = 0;
        while (j < T->KeyNum)/*  T->Key[i] != Unavailable*/
            printf("%d:",T->Key[j++]);
        printf(")\n");
        free(T);
        T = NULL;
    }
    
    return T;
}
 
static void RecursiveTravel(BPlusTree T,int Level){
    int i;
    if (T != NULL){
        printf("  ");
        printf("[Level:%d]-->",Level);
        printf("(");
        i = 0;
        while (i < T->KeyNum)/*  T->Key[i] != Unavailable*/
            printf("%d  ",T->Key[i++]);
        printf(")\n");
        
        Level++;
        
        i = 0;
        while (i <= T->KeyNum) {
            RecursiveTravel(T->Children[i], Level);
            i++;
        }
    }
}
 
/* ���� ��ȱ���*/
extern void Travel(BPlusTree T){
    RecursiveTravel(T, 0);
    printf("\n");
}
 
/* ������Ҷ�ڵ������*/
extern void TravelData(BPlusTree T){
    Position Tmp;
    int i;
    if (T == NULL)
        return ;
    printf("All Data:");
    Tmp = T;
    while (Tmp->Children[0] != NULL)
        Tmp = Tmp->Children[0];
    /* ��һƬ��Ҷ */
    while (Tmp != NULL){
        i = 0;
        while (i < Tmp->KeyNum)
            printf(" %d",Tmp->Key[i++]);
        Tmp = Tmp->Next;
    }
	printf("\n");
}
