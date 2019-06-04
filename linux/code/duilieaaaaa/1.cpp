//    队列的单链表实现
//    头节点：哨兵作用，不存放数据，用来初始化队列时使队头队尾指向的地方
//    首节点：头节点后第一个节点，存放数据

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int Elementype;        //    定义数据类型
//    定义节点结构
typedef struct Node {
    Elementype Element;        //    数据域
    struct Node * Next;
}NODE, *PNODE;

//    定义队列结构体
typedef struct QNode {
    PNODE Front, Rear;        //    队列头，尾指针
} Queue, *PQueue;

//    声明函数体
void InitQueue(PQueue);    //    创建队列函数
bool IsEmptyQueue(PQueue);    //    判断队列是否为空函数
void InsertQueue(PQueue, int val);    //    入队函数
void DeleteQueue(PQueue,int * val);    //    出队函数
void DestroyQueue(PQueue);    //    摧毁队列函数
void TraverseQueue(PQueue);    //    遍历队列函数
void ClearQueue(PQueue);    //    清空队列函数
int LengthQueue(PQueue);    //    求队列长度函数

//    主函数
int main() {
    int val = 0;    //    定义临时变量
    Queue queue;    //    创建队列变量
    InitQueue(&queue);    //    调用初始化队列函数
    IsEmptyQueue(&queue);    //    调用判断队列是否为空函数
    InsertQueue(&queue, 100);    //调用入队函数
    InsertQueue(&queue, 200);
    InsertQueue(&queue, 300);
    InsertQueue(&queue, 400);
    InsertQueue(&queue, 500);
    InsertQueue(&queue, 600);
    IsEmptyQueue(&queue);
    TraverseQueue(&queue);    //    调用队列遍历函数
    DeleteQueue(&queue, &val);    //    调用出队函数
    TraverseQueue(&queue);
    ClearQueue(&queue);        //    调用清空队列函数
    IsEmptyQueue(&queue);
    DestroyQueue(&queue);    //    调用摧毁队列函数

    return 0;
}

//    定义队列初始化函数
void InitQueue(PQueue queue) {
    queue->Front = queue->Rear = (PNODE)malloc(sizeof(NODE));    //    动态创建头节点，使队头，队尾指向该节点
    //头节点相当于哨兵节点的作用，不存储数据（区别于首节点）
    if (queue->Front == NULL) {        //    判断内存是否分配成功
        printf("创建队列，无法分配所需内存...");
        exit(-1);
    }
    queue->Front->Next = NULL;    //    初始队列头节点指针指向为空
    printf("创建队列成功...\n");
}

//    定义判断队列是否为空函数
bool IsEmptyQueue(PQueue queue) {
    if (queue->Front == queue->Rear) {
        printf("队列为空...\n");
        return true;
    }
    else {
        //printf("队列不为空...\n");
        return false;
    }
        
}
//    定义入队函数
//    从队列尾部插入数据val
void InsertQueue(PQueue queue,int val) {
    PNODE P = (PNODE)malloc(sizeof(NODE));    //    创建一个新节点用于存放插入的元素
    if (P == NULL) {
        printf("内存分配失败，无法插入数据%d...", val);
        exit(-1);
    }
    P->Element = val;    //    把要插入的数据放到节点数据域
    P->Next = NULL;        //    新节点指针指向为空
    queue->Rear->Next = P;    //    使上一个队列尾部的节点指针指向新建的节点
    queue->Rear = P;    //    更新队尾指针，使其指向队列最后的节点
    printf("插入数据 %d 成功...\n", val);
}

//    定义出队函数
//    从队列的首节点开始出队
//    若出队成功，用val返回其值
void DeleteQueue(PQueue queue,int* val) {
    if (IsEmptyQueue(queue)) {
        printf("队列已经空，无法出队...\n");
        exit(-1);
    }
    PNODE  P= queue->Front->Next;    //    临时指针
    *val = P->Element;    //    保存其值
    queue->Front->Next = P->Next;        //    更新头节点
    if (queue->Rear==P)
        queue->Rear = queue->Front;
    free(P);    //    释放头队列
    P = NULL;    //    防止产生野指针
    printf("出栈成功，出栈值为 %d\n", *val);
}
//    定义队列遍历函数
void TraverseQueue(PQueue queue) {
    
    if (IsEmptyQueue(queue)) {
        exit(-1);
    }        
    PNODE P = queue->Front->Next;    //从队列首节点开始遍历（非头节点，注意区分）
    printf("遍历队列结果为：");
    while (P != NULL) {
        printf("%d ", P->Element);
        P = P->Next;
    }
    printf("\n");
}
//    定义队列的摧毁函数
//    删除整个队列，包括头节点
void DestroyQueue(PQueue queue) {
    //从头节点开始删除
    while (queue->Front != NULL) {
        queue->Rear = queue->Front->Next;
        free(queue->Front);
        queue->Front = queue->Rear;
    }
    printf("摧毁队列成功...\n");
}
//    定义清空队列函数
void ClearQueue(PQueue queue) {
    PNODE P = queue->Front->Next;    //    临时指针
    PNODE Q = NULL;        //    临时指针
    queue->Rear = queue->Front;        //    使队尾指针指向头节点
    queue->Front->Next = NULL;
    //    从首节点开始清空
    while (P != NULL) {
        Q = P;
        P = P->Next;
        free(Q);
    }
    printf("清空队列成功...\n");

}
