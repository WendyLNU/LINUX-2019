#ifndef BPlusTree_h
#define BPlusTree_h

 

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

 

#define M (4)
#define LIMIT_M_2 (M % 2 ? (M + 1)/2 : M/2)



typedef struct BPlusNode *BPlusTree,*Position;
typedef int KeyType;
struct BPlusNode{
    int KeyNum;
    KeyType Key[M + 1];
    BPlusTree Children[M + 1];
    BPlusTree Next;

};

/* ��ʼ�� */
extern BPlusTree Initialize();
/* ���� */
extern BPlusTree Insert(BPlusTree T,KeyType Key);
/* ɾ�� */
extern BPlusTree Remove(BPlusTree T,KeyType Key);
/* ���� */
extern BPlusTree Destroy(BPlusTree T);
/* �����ڵ� */
extern void Travel(BPlusTree T);
/* ������Ҷ�ڵ������ */
extern void TravelData(BPlusTree T);

#endif /* BPlusTree_h */
