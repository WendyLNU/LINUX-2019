#ifndef _BTREE_H
#define _BTREE_H
#define MAXM 10                     //����B�������Ľ���

const int m=4;                      //�趨B���Ľ��� 
const int Max=m-1;                  //�������ؼ������� 
const int Min=(m-1)/2;              //������С�ؼ������� 
typedef int KeyType;                //KeyTypeΪ�ؼ�������

typedef struct node{                //B����B��������� 
    int keynum;                     //���ؼ��ָ���
    KeyType key[MAXM];              //�ؼ������飬key[0]��ʹ�� 
    struct node *parent;            //˫�׽��ָ��
    struct node *ptr[MAXM];         //���ӽ��ָ������ 
}BTNode,*BTree;

typedef struct{                     //B�����ҽ������ 
    BTNode *pt;                     //ָ���ҵ��Ľ��
    int i;                          //�ڽ���еĹؼ���λ��; 
    int tag;                        //���ҳɹ�����־
}Result;

typedef struct LNode{               //��������������� 
    BTree data;                     //������
    struct LNode *next;             //ָ����
}LNode, *LinkList;

typedef enum status{               //ö�����ͣ����ε����� 
    TRUE,
    FALSE,
    OK,
    ERROR,
    OVERFLOW,
    EMPTY
}Status;

Status InitBTree(BTree &t);                                     //��ʼ��B�� 
int SearchBTNode(BTNode *p,KeyType k);                          //�ڽ��p�в��ҹؼ���k�Ĳ���λ��i 
Result SearchBTree(BTree t,KeyType k);                          /*����t�ϲ��ҹؼ���k,���ؽ��(pt,i,tag)�������ҳɹ�,������ֵ
                                                                tag=1,�ؼ���k��ָ��pt��ָ����е�i���ؼ��֣���������ֵtag=0,
                                                                �ؼ���k�Ĳ���λ��Ϊpt���ĵ�i��*/
void InsertBTNode(BTNode *&p,int i,KeyType k,BTNode *q);        //���ؼ���k�ͽ��q�ֱ���뵽p->key[i+1]��p->ptr[i+1]��
void SplitBTNode(BTNode *&p,BTNode *&q);                        //�����p���ѳ��������,ǰһ�뱣��,��һ��������q
void NewRoot(BTNode *&t,KeyType k,BTNode *p,BTNode *q);         //�����µĸ����t,ԭ���p�ͽ��qΪ����ָ��
void InsertBTree(BTree &t,int i,KeyType k,BTNode *p);           /*����t�Ͻ��q��key[i]��key[i+1]֮�����ؼ���k��������
                                                                 ������,����˫�������б�Ҫ�Ľ����ѵ���,ʹt����B��*/
void Remove(BTNode *p,int i);                                   //��p���ɾ��key[i]�����ĺ���ָ��ptr[i]
void Substitution(BTNode *p,int i);                             //���ұ�ɾ�ؼ���p->key[i](�ڷ�Ҷ�ӽ����)�����Ҷ�ӽ��(��������ֵ��С�Ĺؼ���) 
void MoveRight(BTNode *p,int i);                                /*��˫�׽��p�е����һ���ؼ��������ҽ��q��
                                                                ������aq�е����һ���ؼ�������˫�׽��p��*/ 
void MoveLeft(BTNode *p,int i);                                 /*��˫�׽��p�еĵ�һ���ؼ���������aq�У�
                                                                 �����q�еĵ�һ���ؼ�������˫�׽��p��*/
void Combine(BTNode *p,int i);                                  /*��˫�׽��p���ҽ��q�ϲ�������aq��
                                                                ������˫�׽��p�е�ʣ��ؼ��ֵ�λ��*/                                                                 
void AdjustBTree(BTNode *p,int i);                              //ɾ�����p�еĵ�i���ؼ��ֺ�,����B��                                                                
int FindBTNode(BTNode *p,KeyType k,int &i);                     //��ӳ�Ƿ��ڽ��p���Ƿ���ҵ��ؼ���k 
int BTNodeDelete(BTNode *p,KeyType k);                          //�ڽ��p�в��Ҳ�ɾ���ؼ���k
void BTreeDelete(BTree &t,KeyType k);                           //����ɾ����ܣ�ִ��ɾ������ 
void DestroyBTree(BTree &t);                                    //�ݹ��ͷ�B��
Status InitQueue(LinkList &L);                                  //��ʼ������ 
LNode* CreateNode(BTree t);                                     //�½�һ����� 
Status Enqueue(LNode *p,BTree t);                               //Ԫ��q�����
Status Dequeue(LNode *p,BTNode *&q);                            //�����У�����q����ֵ
Status IfEmpty(LinkList L);                                     //�����п� 
void DestroyQueue(LinkList L);                                  //���ٶ��� 
Status Traverse(BTree t,LinkList L,int newline,int sum);        //�ö��б������B�� 
Status PrintBTree(BTree t);                                     //���B�� 
void Test();                                                    //����B�����ܺ��� 
#endif 
