//    ���еĵ�����ʵ��
//    ͷ�ڵ㣺�ڱ����ã���������ݣ�������ʼ������ʱʹ��ͷ��βָ��ĵط�
//    �׽ڵ㣺ͷ�ڵ���һ���ڵ㣬�������

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int Elementype;        //    ������������
//    ����ڵ�ṹ
typedef struct Node {
    Elementype Element;        //    ������
    struct Node * Next;
}NODE, *PNODE;

//    ������нṹ��
typedef struct QNode {
    PNODE Front, Rear;        //    ����ͷ��βָ��
} Queue, *PQueue;

//    ����������
void InitQueue(PQueue);    //    �������к���
bool IsEmptyQueue(PQueue);    //    �ж϶����Ƿ�Ϊ�պ���
void InsertQueue(PQueue, int val);    //    ��Ӻ���
void DeleteQueue(PQueue,int * val);    //    ���Ӻ���
void DestroyQueue(PQueue);    //    �ݻٶ��к���
void TraverseQueue(PQueue);    //    �������к���
void ClearQueue(PQueue);    //    ��ն��к���
int LengthQueue(PQueue);    //    ����г��Ⱥ���

//    ������
int main() {
    int val = 0;    //    ������ʱ����
    Queue queue;    //    �������б���
    InitQueue(&queue);    //    ���ó�ʼ�����к���
    IsEmptyQueue(&queue);    //    �����ж϶����Ƿ�Ϊ�պ���
    InsertQueue(&queue, 100);    //������Ӻ���
    InsertQueue(&queue, 200);
    InsertQueue(&queue, 300);
    InsertQueue(&queue, 400);
    InsertQueue(&queue, 500);
    InsertQueue(&queue, 600);
    IsEmptyQueue(&queue);
    TraverseQueue(&queue);    //    ���ö��б�������
    DeleteQueue(&queue, &val);    //    ���ó��Ӻ���
    TraverseQueue(&queue);
    ClearQueue(&queue);        //    ������ն��к���
    IsEmptyQueue(&queue);
    DestroyQueue(&queue);    //    ���ôݻٶ��к���

    return 0;
}

//    ������г�ʼ������
void InitQueue(PQueue queue) {
    queue->Front = queue->Rear = (PNODE)malloc(sizeof(NODE));    //    ��̬����ͷ�ڵ㣬ʹ��ͷ����βָ��ýڵ�
    //ͷ�ڵ��൱���ڱ��ڵ�����ã����洢���ݣ��������׽ڵ㣩
    if (queue->Front == NULL) {        //    �ж��ڴ��Ƿ����ɹ�
        printf("�������У��޷����������ڴ�...");
        exit(-1);
    }
    queue->Front->Next = NULL;    //    ��ʼ����ͷ�ڵ�ָ��ָ��Ϊ��
    printf("�������гɹ�...\n");
}

//    �����ж϶����Ƿ�Ϊ�պ���
bool IsEmptyQueue(PQueue queue) {
    if (queue->Front == queue->Rear) {
        printf("����Ϊ��...\n");
        return true;
    }
    else {
        //printf("���в�Ϊ��...\n");
        return false;
    }
        
}
//    ������Ӻ���
//    �Ӷ���β����������val
void InsertQueue(PQueue queue,int val) {
    PNODE P = (PNODE)malloc(sizeof(NODE));    //    ����һ���½ڵ����ڴ�Ų����Ԫ��
    if (P == NULL) {
        printf("�ڴ����ʧ�ܣ��޷���������%d...", val);
        exit(-1);
    }
    P->Element = val;    //    ��Ҫ��������ݷŵ��ڵ�������
    P->Next = NULL;        //    �½ڵ�ָ��ָ��Ϊ��
    queue->Rear->Next = P;    //    ʹ��һ������β���Ľڵ�ָ��ָ���½��Ľڵ�
    queue->Rear = P;    //    ���¶�βָ�룬ʹ��ָ��������Ľڵ�
    printf("�������� %d �ɹ�...\n", val);
}

//    ������Ӻ���
//    �Ӷ��е��׽ڵ㿪ʼ����
//    �����ӳɹ�����val������ֵ
void DeleteQueue(PQueue queue,int* val) {
    if (IsEmptyQueue(queue)) {
        printf("�����Ѿ��գ��޷�����...\n");
        exit(-1);
    }
    PNODE  P= queue->Front->Next;    //    ��ʱָ��
    *val = P->Element;    //    ������ֵ
    queue->Front->Next = P->Next;        //    ����ͷ�ڵ�
    if (queue->Rear==P)
        queue->Rear = queue->Front;
    free(P);    //    �ͷ�ͷ����
    P = NULL;    //    ��ֹ����Ұָ��
    printf("��ջ�ɹ�����ջֵΪ %d\n", *val);
}
//    ������б�������
void TraverseQueue(PQueue queue) {
    
    if (IsEmptyQueue(queue)) {
        exit(-1);
    }        
    PNODE P = queue->Front->Next;    //�Ӷ����׽ڵ㿪ʼ��������ͷ�ڵ㣬ע�����֣�
    printf("�������н��Ϊ��");
    while (P != NULL) {
        printf("%d ", P->Element);
        P = P->Next;
    }
    printf("\n");
}
//    ������еĴݻٺ���
//    ɾ���������У�����ͷ�ڵ�
void DestroyQueue(PQueue queue) {
    //��ͷ�ڵ㿪ʼɾ��
    while (queue->Front != NULL) {
        queue->Rear = queue->Front->Next;
        free(queue->Front);
        queue->Front = queue->Rear;
    }
    printf("�ݻٶ��гɹ�...\n");
}
//    ������ն��к���
void ClearQueue(PQueue queue) {
    PNODE P = queue->Front->Next;    //    ��ʱָ��
    PNODE Q = NULL;        //    ��ʱָ��
    queue->Rear = queue->Front;        //    ʹ��βָ��ָ��ͷ�ڵ�
    queue->Front->Next = NULL;
    //    ���׽ڵ㿪ʼ���
    while (P != NULL) {
        Q = P;
        P = P->Next;
        free(Q);
    }
    printf("��ն��гɹ�...\n");

}
