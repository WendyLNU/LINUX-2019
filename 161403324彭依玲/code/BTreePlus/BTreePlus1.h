//  BPlusTree
//
//  Created by Wuyixin on 2017/8/4.
// Copyright ? 2017�� Coding365. All rights reserved.
// What happened?
// 
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
    int KeyNum;		//�����ؼ��ֵĸ���
    KeyType Key[M + 1];		//�ýڵ��еĹؼ��֣�����Ϊʲô��M+1��
    BPlusTree Children[M + 1];    //�ýڵ�ĺ��ӽڵ�ָ�룬����ͬ��
    BPlusTree Next;		//Next��ʲô��
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
