//  BPlusTree
//
//  Created by Wuyixin on 2017/8/4.
// Copyright ? 2017年 Coding365. All rights reserved.
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
    int KeyNum;		//所含关键字的个数
    KeyType Key[M + 1];		//该节点中的关键字，上限为什么是M+1？
    BPlusTree Children[M + 1];    //该节点的孩子节点指针，问题同上
    BPlusTree Next;		//Next是什么？
};
 
/* 初始化 */
extern BPlusTree Initialize();
/* 插入 */
extern BPlusTree Insert(BPlusTree T,KeyType Key);
/* 删除 */
extern BPlusTree Remove(BPlusTree T,KeyType Key);
/* 销毁 */
extern BPlusTree Destroy(BPlusTree T);
/* 遍历节点 */
extern void Travel(BPlusTree T);
/* 遍历树叶节点的数据 */
extern void TravelData(BPlusTree T);
 
#endif /* BPlusTree_h */
