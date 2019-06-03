#include<stdio.h>
#include <malloc.h>  
#include <stdlib.h>
#define MaxSize 100
#include "rbtree.h"

#define MinDegree 4
#define MAX_VER_NUM 50
#define LeftChild(i) (2 * (i) + 1)

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)

#define CHECK_INSERT 0    // "����"�����ļ�⿪��(0���رգ�1����)
#define CHECK_DELETE 0    // "ɾ��"�����ļ�⿪��(0���رգ�1����)
#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )
/**************************��*****************************************************************************************/
typedef int ElementType;
int arr1[11]={0,2,87,39,49,34,62,53,6,44,98};


void Swap(int* a,int* b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}


void PercDown(int  A[], int i, int N)
{
    int child;
    ElementType Tmp;

    for (Tmp = A[i]; 2*i+1 < N; i = child){
        child = 2*i+1; //ע�������±��Ǵ�0��ʼ�ģ��������ӵ��󷢲���2*i
        if (child != N - 1 && A[child + 1] > A[child])
            ++child;                //�ҵ����Ķ��ӽڵ�
        if (Tmp < A[child])
            A[i] = A[child];
        else
            break;
    }
    A[i] = Tmp;
}

void HeapSort(int A[], int N)
{
    int i;
    for (i = N / 2; i >= 0; --i)
        PercDown(A, i, N);    //�����
    for(i=N-1;i>0;--i)
    {
        Swap(&A[0],&A[i]);        //�����Ԫ�أ�����������ĩβԪ�ؽ������Ӷ�ɾ�����Ԫ�أ����¹����
        PercDown(A, 0, i);
    }
}

void Print(int A[],int N)
{
    int i;
    for(i=0;i<N;i++)
    {
        printf(" %d ",A[i]);
    }
}
void heap()
{
    int arr[10];
    int n;
    printf("�������10��������\n" );
    for(n=0;n<10;n++){
    	scanf("%d",&arr[n]);
    }
    Print(arr,10);
    printf("\n");
    HeapSort(arr,10);
    Print(arr,10);
    printf("\n");

}
 
/****************************************************************************************************/

/**************************ջ**************************************************************************/ 
//����ջ

typedef struct stack

{

    char data[MaxSize];//����ʵ��ջ��Ԫ�ض�λ

    int top;//��Ϊ�����±�

    int buttom;

} stack;

 

//����һ����ջ

stack * CreateStack()

{

    stack * st = (stack*)malloc(sizeof(stack));

    if(st == NULL)

        return false;//����ռ�ʧ��

    st->top = st->buttom = 0;

    return st;

}

 

//��ջ

void Push(stack * st, char data)

{

    st->data[st->top]= data;

    st->top++;

}

 

//��ջ

void Pop(stack * st, char data)

{

    int n = st->top;

    while(n != st->buttom)//�ж��Ƿ��ǿ�ջ

    {

        if(st->data[n-1] == data)

        {

            st->top = n-1;

            break;

        }

        n--;

    }

}

 

//��ӡջԪ��

void Display(stack * st)

{

    int n = st->top;

    while(n != st->buttom)

    {

        printf("%c  ",st->data[n-1]);

        n--;

    }

    printf("\n");

 

}

void stack1()
{

    int i=5,j=5;

    stack * st;

    st = CreateStack();

    printf("��ʼ��ջ��\n");

    while(i--)

    {

        Push(st,'A'+i);

        printf("%c��ջ��,ջ��Ԫ��Ϊ�� ",'A'+i);

        Display(st);

    }

    printf("��ʼ��ջ��\n");

    while(j--)

    {

 

        Pop(st,'E'-j);

        printf("%c��ջ��,ջ��Ԫ��Ϊ�� ",'E'-j);

        Display(st);

    }
    free(st); 


}
/****************************************************************************************************/
/************����***************************************************************************************/

//    ���������еĽڵ�  
typedef struct node  
{  
    int member;                //    �ڵ��еĳ�Ա  
    struct node *pNext;        //    ָ����һ���ڵ��ָ��  
}*pNode;  
  
//    ��������  
pNode CreateList();                 //  ����������  
void TraverseList(pNode );            //  ����������  
bool Insert_Node(pNode ,int ,int);    //    ����ڵ���뺯��,��һ��������ͷ�ڵ㣬�ڶ���������Ҫ�ڵڼ����ڵ�ǰ���룬������������Ҫ���������  
int Del_Node(pNode,int );        //    ɾ������ڵ�,��һ��������ͷ�ڵ㣬�ڶ���������ɾ���ڼ����ڵ㣬��������Ϊ  
void list1()  
{  
    pNode pHead = NULL;                //  �����ʼ��ͷ�ڵ㣬�ȼ��� struct Node *pHead == NULL  
    int data;                        // ��ΪInsert_Node�����ĵ���������  
    int num;                        //    ��ΪInset_Node�����ڶ�������  
    int choose;      
    int return_val;  
    pHead = CreateList();            //  ����һ����ѭ�������������������ͷ���ĵ�ַ����pHead  
    printf("������������ǣ�");  
    TraverseList(pHead);    //  ���ñ���������  
    printf("�Ƿ�Ҫ�������²�����\n");  
    printf("1.��������      2.ɾ������\n");  
    printf("�����룺");  
    scanf("%d",&choose);  
    switch (choose)  
    {  
        case 1:  
            {  
                printf("������Ҫ�ڵڼ����ڵ�ǰ�������ݣ�");  
                scanf("%d",&num);  
                printf("������Ҫ��������ݣ�");  
                scanf("%d",&data);  
                if(Insert_Node(pHead,num,data) == true)  
                {  
                    printf("����ɹ�\n�����������ǣ�\n");  
                    TraverseList(pHead);  
                }  
                else  
                {  
                    printf("����ʧ��\n");  
                }  
                printf("������ɺ�������ǣ�");  
                TraverseList(pHead);  
                break;  
            }  
        case 2:  
            {  
                printf("������Ҫɾ���ڼ����ڵ�����ݣ�");  
                scanf("%d",&num);  
                return_val = Del_Node(pHead,num);  
                if (return_val == 0)  
                {  
                    printf("ɾ��ʧ�ܡ�\n");  
                }  
                else  
                {  
                    printf("ɾ���ɹ���ɾ����Ԫ���ǣ�%d\n",return_val);  
                }  
                printf("������ɺ�������ǣ�");  
                TraverseList(pHead);  
            }  
        default:printf("�������\n");
    }  
    free(pHead); 

}  
  
//    ����������  
pNode CreateList()  
{  
    int i;                                            //    ��������ѭ��  
    int len;                                        //    ���������Ч�ڵ������  
    int val;                                        //    ������ʱ����û����������  
    pNode pHead = (pNode)malloc(sizeof(Node));        //  ����һ���������Ч���ݵ�ͷ���  
    pNode pTail = pHead;                            //    ��������һ���ڵ�  
    pTail->pNext = NULL;                            //    ���һ���ڵ��ָ����Ϊ��  
    printf("������ڵ������");  
    scanf("%d",&len);  
    for(i = 0; i < len; i++)  
    {  
        printf("�� %d ���ڵ����ֵ��",i+1);  
        scanf("%d",&val);  
        pNode pNew = (pNode)malloc(sizeof(Node));    //    Ϊ�ڵ����ռ�  
        pNew->member = val;                            //���û���������ݸ����ڵ�ĳ�Ա  
        pTail->pNext = pNew;                        //�����һ���ڵ��ָ��ָ����һ���µĽڵ�  
        pNew->pNext = NULL;                            //���½ڵ��е�ָ����Ϊ��  
        pTail = pNew;                                //���½ڵ㸳������һ���ڵ�  
    }  
    return pHead;                                    //����ͷ�ڵ�  
  
}  
  
//    ����������  
void TraverseList(pNode pHead)  
{  
    pNode p = pHead->pNext;                            //��ͷ�ڵ��ָ�������ʱ�ڵ�p  
    while(NULL != p)                                //�ڵ�p��Ϊ�գ�ѭ��      
    {  
        printf("%d ",p->member);                      
        p = p->pNext;                                  
    }  
    printf("\n");  
    return ;  
}  
  
//    ����ڵ���뺯��  
//    ��һ��������ͷ�ڵ㣬�ڶ���������Ҫ�ڵڼ����ڵ�ǰ���룬������������Ҫ���������  
bool Insert_Node(pNode pHead, int front,int data)  
{  
    int i = 0;  
    pNode _node = pHead;  
    pNode pSwap;                                //    ���ڽ���  
    if ((front < 1) && (NULL != _node))        //�ж��û�����������Ƿ���ڵ���1,��_node�Ƿ�Ϊ��  
    {  
        return false;  
    }  
    while (i < front - 1)                    //ͨ��ѭ��ʹָ��ָ��Ҫ�����ĸ��ڵ�ǰ�Ľڵ㡣˵���Լ��������ˣ����ǿ������ͼ�ɡ�      
    {  
        _node = _node->pNext;  
        ++i;  
    }  
    pNode pNew = (pNode)malloc(sizeof(Node));  
  
    pNew->member = data;                        //    ����������ݸ���Ҫ����Ľڵ�  
    pSwap = _node->pNext;                        //    ����һ���ڵ�ĵ�ַ�������ڽ�����pSwap  
    _node->pNext = pNew;                        //    ��Ҫ����Ľڵ�ĵ�ַ�����ϸ��ڵ��ָ����  
    pNew->pNext = pSwap;                        //    �Ѳ���ڵ����һ���ڵ�ĵ�ַ��������ڵ��ָ����  
    return true;  
  
}  
  
//    ɾ������ڵ㺯��  
//    ��һ��������ͷ�ڵ㣬�ڶ���������Ҫɾ���ڼ����ڵ㡤������������������Ĳ��뺯���ǲ��Ǻ���  
int Del_Node(pNode pHead,int back)  
{  
    int i = 0;  
    int data;  
    pNode _node = pHead;  
    pNode pSwap;  
    if ((back < 1) && (NULL == _node->pNext))  
    {  
        printf("ɾ��ʧ�ܣ�\n");  
        return 0;  
    }  
    while(i < back-1)  
    {  
        _node = _node->pNext;  
        ++i;  
    }  
    pSwap = _node->pNext;  
    data = pSwap->member;  
    _node->pNext = _node->pNext->pNext;  
    free(pSwap);  
    return data;}
/*****************************************************************************************************/
/**********ͼ*************************************/
typedef char VertexType;

typedef enum

{

	DG,UDG

}GraphType;

typedef struct

{

	VertexType vexs[MAX_VER_NUM];        //��������

	int arcs[MAX_VER_NUM][MAX_VER_NUM];  //�ڽӾ���

	int vexnum,arcnum;                   //ͼ�ĵ�ǰ�������ͻ���

	GraphType type;                      //ͼ�������־

}MGraph; 

 

//�������Ƶõ�ָ�������ڶ��㼯���е��±�

//vex ����

//return ����ҵ����򷵻��±꣬���򣬷���0

int getIndexOfVexs(char vex,MGraph *MG)

{

	int i;

	for(i=1;i<=MG->vexnum;i++)

	{

		if(MG->vexs[i]==vex)

		{

			return i;

		}

	}

	return 0;

}

 

//�����ڽӾ���

void create_MG(MGraph *MG)

{

	int i,j,k;

	int v1,v2,type;

	char c1,c2;

	printf("Please input graph type DG(0) or UDG(1):");

	scanf("%d",&type);

	if(type==0)

	{

		MG->type=DG;

	}

	else if(type==1)

	{

		MG->type=UDG;

	}

	else

	{

		printf("Please input correct graph type DG(0) or UDG(1)!");

		return;

	}

	printf("Please input vexnum:");

	scanf("%d",&MG->vexnum);

	printf("Please input arcnum:");

	scanf("%d",&MG->arcnum);

	getchar();

	for(i=1;i<=MG->vexnum;i++)

	{

		printf("Please input %dth vex(char):",i);

		scanf("%c",&MG->vexs[i]);

		getchar();

	}

	//��ʼ���ڽӾ���

	for(i=1;i<=MG->vexnum;i++)

	{

		for (j=1;j<=MG->vexnum;j++)

		{

			MG->arcs[i][j]=0;

		}

	}

	//����ߵ���Ϣ�������ڽӾ���

	for(k=1;k<=MG->arcnum;k++)

	{

		printf("Please input %dth arc v1(char) v2(char):",k);

		scanf("%c %c",&c1,&c2);

		v1=getIndexOfVexs(c1,MG);

		v2=getIndexOfVexs(c2,MG);

		if(MG->type==-1)

		{

			MG->arcs[v1][v2]=MG->arcs[v2][v1]=1;

		}

		else

		{

			MG->arcs[v1][v2]=1;

		}

		getchar();

	}

}

 

//��ӡ�ڽӾ���Ͷ�����Ϣ

void print_MG(MGraph MG)

{

	int i,j;

	if(MG.type==DG)

	{

		printf("Graph type: Direct graph\n");

	}

	else

	{

		printf("Graph type: Undirect graph\n");

	}

	printf("Graph vertex number: %d\n",MG.vexnum);

	printf("Graph arc number: %d\n",MG.arcnum);

	printf("Vertex set:");

	for(i=1;i<=MG.vexnum;i++)

	{

		printf("%c",MG.vexs[i]);

	}

	printf("\nAdjacency Matrix:\n");

	for(i=1;i<=MG.vexnum;i++)

	{

		for(j=1;j<=MG.vexnum;j++)

		{

			printf("%d",MG.arcs[i][j]);

		}

		printf("\n");

	}

}

 

//������

int gp() 

{

	MGraph MG;

	create_MG(&MG);

	print_MG(MG);


}

/***********************************************/
/**********�����*************************************/

/*
 * ���������������"������ĸ�"��
 */
RBRoot* create_rbtree()
{
    RBRoot *root = (RBRoot *)malloc(sizeof(RBRoot));
    root->node = NULL;

    return root;
}

/*
 * ǰ�����"�����"
 */
static void preorder(RBTree tree)
{
    if(tree != NULL)
    {
        printf("%d ", tree->key);
        preorder(tree->left);
        preorder(tree->right);
    }
}
void preorder_rbtree(RBRoot *root) 
{
    if (root)
        preorder(root->node);
}

/*
 * �������"�����"
 */
static void inorder(RBTree tree)
{
    if(tree != NULL)
    {
        inorder(tree->left);
        printf("%d ", tree->key);
        inorder(tree->right);
    }
}

void inorder_rbtree(RBRoot *root) 
{
    if (root)
        inorder(root->node);
}

/*
 * �������"�����"
 */
static void postorder(RBTree tree)
{
    if(tree != NULL)
    {
        postorder(tree->left);
        postorder(tree->right);
        printf("%d ", tree->key);
    }
}

void postorder_rbtree(RBRoot *root)
{
    if (root)
        postorder(root->node);
}

/*
 * (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
 */
static Node* search(RBTree x, Type key)
{
    if (x==NULL || x->key==key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}
int rbtree_search(RBRoot *root, Type key)
{
    if (root)
        return search(root->node, key)? 0 : -1;
}

/*
 * (�ǵݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
 */
static Node* iterative_search(RBTree x, Type key)
{
    while ((x!=NULL) && (x->key!=key))
    {
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    return x;
}
int iterative_rbtree_search(RBRoot *root, Type key)
{
    if (root)
        return iterative_search(root->node, key) ? 0 : -1;
}

/* 
 * ������С��㣺����treeΪ�����ĺ��������С��㡣
 */
static Node* minimum(RBTree tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

int rbtree_minimum(RBRoot *root, int *val)
{
    Node *node;

    if (root)
        node = minimum(root->node);

    if (node == NULL)
        return -1;

    *val = node->key;
    return 0;
}
 
/* 
 * ��������㣺����treeΪ�����ĺ����������㡣
 */
static Node* maximum(RBTree tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

int rbtree_maximum(RBRoot *root, int *val)
{
    Node *node;

    if (root)
        node = maximum(root->node);

    if (node == NULL)
        return -1;

    *val = node->key;
    return 0;
}

/* 
 * �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
 */
static Node* rbtree_successor(RBTree x)
{
    // ���x�����Һ��ӣ���"x�ĺ�̽��"Ϊ "�����Һ���Ϊ������������С���"��
    if (x->right != NULL)
        return minimum(x->right);

    // ���xû���Һ��ӡ���x���������ֿ��ܣ�
    // (01) x��"һ������"����"x�ĺ�̽��"Ϊ "���ĸ����"��
    // (02) x��"һ���Һ���"�������"x����͵ĸ���㣬���Ҹø����Ҫ��������"���ҵ������"��͵ĸ����"����"x�ĺ�̽��"��
    Node* y = x->parent;
    while ((y!=NULL) && (x==y->right))
    {
        x = y;
        y = y->parent;
    }

    return y;
}
 
/* 
 * �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
 */
static Node* rbtree_predecessor(RBTree x)
{
    // ���x�������ӣ���"x��ǰ�����"Ϊ "��������Ϊ���������������"��
    if (x->left != NULL)
        return maximum(x->left);

    // ���xû�����ӡ���x���������ֿ��ܣ�
    // (01) x��"һ���Һ���"����"x��ǰ�����"Ϊ "���ĸ����"��
    // (01) x��"һ������"�������"x����͵ĸ���㣬���Ҹø����Ҫ�����Һ���"���ҵ������"��͵ĸ����"����"x��ǰ�����"��
    Node* y = x->parent;
    while ((y!=NULL) && (x==y->left))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

/* 
 * �Ժ�����Ľڵ�(x)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�x��������)��
 *      px                              px
 *     /                               /
 *    x                               y                
 *   /  \      --(����)-->           / \                #
 *  lx   y                          x  ry     
 *     /   \                       /  \
 *    ly   ry                     lx  ly  
 *
 *
 */
static void rbtree_left_rotate(RBRoot *root, Node *x)
{
    // ����x���Һ���Ϊy
    Node *y = x->right;

    // �� ��y�����ӡ� ��Ϊ ��x���Һ��ӡ���
    // ���y�����ӷǿգ��� ��x�� ��Ϊ ��y�����ӵĸ��ס�
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    // �� ��x�ĸ��ס� ��Ϊ ��y�ĸ��ס�
    y->parent = x->parent;

    if (x->parent == NULL)
    {
        //tree = y;            // ��� ��x�ĸ��ס� �ǿսڵ㣬��y��Ϊ���ڵ�
        root->node = y;            // ��� ��x�ĸ��ס� �ǿսڵ㣬��y��Ϊ���ڵ�
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
        else
            x->parent->right = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
    }
    
    // �� ��x�� ��Ϊ ��y�����ӡ�
    y->left = x;
    // �� ��x�ĸ��ڵ㡱 ��Ϊ ��y��
    x->parent = y;
}

/* 
 * �Ժ�����Ľڵ�(y)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�y��������)��
 *            py                               py
 *           /                                /
 *          y                                x                  
 *         /  \      --(����)-->            /  \                     #
 *        x   ry                           lx   y  
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 * 
 */
static void rbtree_right_rotate(RBRoot *root, Node *y)
{
    // ����x�ǵ�ǰ�ڵ�����ӡ�
    Node *x = y->left;

    // �� ��x���Һ��ӡ� ��Ϊ ��y�����ӡ���
    // ���"x���Һ���"��Ϊ�յĻ����� ��y�� ��Ϊ ��x���Һ��ӵĸ��ס�
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    // �� ��y�ĸ��ס� ��Ϊ ��x�ĸ��ס�
    x->parent = y->parent;

    if (y->parent == NULL) 
    {
        //tree = x;            // ��� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
        root->node = x;            // ��� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;    // ��� y�������ڵ���Һ��ӣ���x��Ϊ��y�ĸ��ڵ���Һ��ӡ�
        else
            y->parent->left = x;    // (y�������ڵ������) ��x��Ϊ��x�ĸ��ڵ�����ӡ�
    }

    // �� ��y�� ��Ϊ ��x���Һ��ӡ�
    x->right = y;

    // �� ��y�ĸ��ڵ㡱 ��Ϊ ��x��
    y->parent = x;
}

/*
 * �����������������
 *
 * ���������в���ڵ�֮��(ʧȥƽ��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
 */
static void rbtree_insert_fixup(RBRoot *root, Node *node)
{
    Node *parent, *gparent;

    // �������ڵ���ڣ����Ҹ��ڵ����ɫ�Ǻ�ɫ��
    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);

        //�������ڵ㡱�ǡ��游�ڵ�����ӡ�
        if (parent == gparent->left)
        {
            // Case 1����������ڵ��Ǻ�ɫ
            {
                Node *uncle = gparent->right;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���
            if (parent->right == node)
            {
                Node *tmp;
                rbtree_left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_right_rotate(root, gparent);
        } 
        else//����z�ĸ��ڵ㡱�ǡ�z���游�ڵ���Һ��ӡ�
        {
            // Case 1����������ڵ��Ǻ�ɫ
            {
                Node *uncle = gparent->left;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ�������
            if (parent->left == node)
            {
                Node *tmp;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ��ӡ�
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_left_rotate(root, gparent);
        }
    }

    // �����ڵ���Ϊ��ɫ
    rb_set_black(root->node);
}

/*
 * ��ӽڵ㣺���ڵ�(node)���뵽�������
 *
 * ����˵����
 *     root ������ĸ�
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
 */
static void rbtree_insert(RBRoot *root, Node *node)
{
    Node *y = NULL;
    Node *x = root->node;

    // 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С�
    while (x != NULL)
    {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    rb_parent(node) = y;

    if (y != NULL)
    {
        if (node->key < y->key)
            y->left = node;                // ���2������node��������ֵ�� < ��y��������ֵ������node��Ϊ��y�����ӡ�
        else
            y->right = node;            // ���3��(��node��������ֵ�� >= ��y��������ֵ��)��node��Ϊ��y���Һ��ӡ� 
    }
    else
    {
        root->node = node;                // ���1����y�ǿսڵ㣬��node��Ϊ��
    }

    // 2. ���ýڵ����ɫΪ��ɫ
    node->color = RED;

    // 3. ������������Ϊһ�Ŷ��������
    rbtree_insert_fixup(root, node);
}

/*
 * �������
 *
 * ����˵����
 *     key �Ǽ�ֵ��
 *     parent �Ǹ���㡣
 *     left �����ӡ�
 *     right ���Һ��ӡ�
 */
static Node* create_rbtree_node(Type key, Node *parent, Node *left, Node* right)
{
    Node* p;

    if ((p = (Node *)malloc(sizeof(Node))) == NULL)
        return NULL;
    p->key = key;
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = BLACK; // Ĭ��Ϊ��ɫ

    return p;
}

/* 
 * �½����(�ڵ��ֵΪkey)����������뵽�������
 *
 * ����˵����
 *     root ������ĸ�
 *     key ������ļ�ֵ
 * ����ֵ��
 *     0������ɹ�
 *     -1������ʧ��
 */
int insert_rbtree(RBRoot *root, Type key)
{
    Node *node;    // �½����

    // �����������ͬ��ֵ�Ľڵ㡣
    // (�������������ͬ��ֵ�Ľڵ㣬ע�͵��������仰���ɣ�)
    if (search(root->node, key) != NULL)
        return -1;

    // ����½����ʧ�ܣ��򷵻ء�
    if ((node=create_rbtree_node(key, NULL, NULL, NULL)) == NULL)
        return -1;

    rbtree_insert(root, node);

    return 0;
}

/*
 * �����ɾ����������
 *
 * �ڴӺ������ɾ������ڵ�֮��(�����ʧȥƽ��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node �������Ľڵ�
 */
static void rbtree_delete_fixup(RBRoot *root, Node *node, Node *parent)
{
    Node *other;

    while ((!node || rb_is_black(node)) && node != root->node)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (rb_is_red(other))
            {
                // Case 1: x���ֵ�w�Ǻ�ɫ��  
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    // Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rbtree_right_rotate(root, other);
                    other = parent->right;
                }
                // Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                rbtree_left_rotate(root, parent);
                node = root->node;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (rb_is_red(other))
            {
                // Case 1: x���ֵ�w�Ǻ�ɫ��  
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
                    // Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
                    rb_set_black(other->right);
                    rb_set_red(other);
                    rbtree_left_rotate(root, other);
                    other = parent->left;
                }
                // Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rbtree_right_rotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}

/* 
 * ɾ�����
 *
 * ����˵����
 *     tree ������ĸ����
 *     node ɾ���Ľ��
 */
void rbtree_delete(RBRoot *root, Node *node)
{
    Node *child, *parent;
    int color;

    // ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
    if ( (node->left!=NULL) && (node->right!=NULL) ) 
    {
        // ��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
        // ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
        Node *replace = node;

        // ��ȡ��̽ڵ�
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        // "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
        if (rb_parent(node))
        {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        } 
        else 
            // "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣
            root->node = replace;

        // child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
        // "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
        child = replace->right;
        parent = rb_parent(replace);
        // ����"ȡ���ڵ�"����ɫ
        color = rb_color(replace);

        // "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
        if (parent == node)
        {
            parent = replace;
        } 
        else
        {
            // child��Ϊ��
            if (child)
                rb_set_parent(child, parent);
            parent->left = child;

            replace->right = node->right;
            rb_set_parent(node->right, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
            rbtree_delete_fixup(root, child, parent);
        free(node);

        return ;
    }

    if (node->left !=NULL)
        child = node->left;
    else 
        child = node->right;

    parent = node->parent;
    // ����"ȡ���ڵ�"����ɫ
    color = node->color;

    if (child)
        child->parent = parent;

    // "node�ڵ�"���Ǹ��ڵ�
    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root->node = child;

    if (color == BLACK)
        rbtree_delete_fixup(root, child, parent);
    free(node);
}

/* 
 * ɾ����ֵΪkey�Ľ��
 *
 * ����˵����
 *     tree ������ĸ����
 *     key ��ֵ
 */
void delete_rbtree(RBRoot *root, Type key)
{
    Node *z, *node; 

    if ((z = search(root->node, key)) != NULL)
        rbtree_delete(root, z);
}

/*
 * ���ٺ����
 */
static void rbtree_destroy(RBTree tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        rbtree_destroy(tree->left);
    if (tree->right != NULL)
        rbtree_destroy(tree->right);

    free(tree);
}

void destroy_rbtree(RBRoot *root)
{
    if (root != NULL)
        rbtree_destroy(root->node);

    free(root);
}

/*
 * ��ӡ"�����"
 *
 * tree       -- ������Ľڵ�
 * key        -- �ڵ�ļ�ֵ 
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */
static void rbtree_print(RBTree tree, Type key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree�Ǹ��ڵ�
            printf("%2d(B) is root\n", tree->key);
        else                // tree�Ƿ�֧�ڵ�
            printf("%2d(%s) is %2d's %6s child\n", tree->key, rb_is_red(tree)?"R":"B", key, direction==1?"right" : "left");

        rbtree_print(tree->left, tree->key, -1);
        rbtree_print(tree->right,tree->key,  1);
    }
}

void print_rbtree(RBRoot *root)
{
    if (root!=NULL && root->node!=NULL)
        rbtree_print(root->node, root->node->key, 0);
}

void rb1()
{
    int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
    int i, ilen=LENGTH(a);
    RBRoot *root=NULL;

    root = create_rbtree();
    printf("== ԭʼ����: ");
    for(i=0; i<ilen; i++)
        printf("%d ", a[i]);
    printf("\n");

    for(i=0; i<ilen; i++)
    {
        insert_rbtree(root, a[i]);
#if CHECK_INSERT
        printf("== ��ӽڵ�: %d\n", a[i]);
        printf("== ������ϸ��Ϣ: \n");
        print_rbtree(root);
        printf("\n");
#endif
    }

    printf("== ǰ�����: ");
    preorder_rbtree(root);

    printf("\n== �������: ");
    inorder_rbtree(root);

    printf("\n== �������: ");
    postorder_rbtree(root);
    printf("\n");

    if (rbtree_minimum(root, &i)==0)
        printf("== ��Сֵ: %d\n", i);
    if (rbtree_maximum(root, &i)==0)
        printf("== ���ֵ: %d\n", i);
    printf("== ������ϸ��Ϣ: \n");
    print_rbtree(root);
    printf("\n");

#if CHECK_DELETE
    for(i=0; i<ilen; i++)
    {
        delete_rbtree(root, a[i]);

        printf("== ɾ���ڵ�: %d\n", a[i]);
        if (root)
        {
            printf("== ������ϸ��Ϣ: \n");
            print_rbtree(root);
            printf("\n");
        }
    }
#endif

    destroy_rbtree(root);
} 
/**********************************************/
/*******b+��***********************************/

typedef int ElementType;
typedef int* PtrElementType;

 

enum Bool{
    False = 0,
    True = 1
};
typedef enum Bool BoolType;
typedef struct TreeNode *PtrBpNode;
typedef struct TreeNode BpNode;

struct TreeNode{

    int Num;

    BoolType IsLeaf;

    PtrElementType Key;

    PtrBpNode *Child;

    PtrBpNode Next;

};

 

typedef struct Tree *PtrBp;

struct Tree{

    PtrBpNode Root;

};

 

PtrBpNode BpAllocateNode(BoolType IsLeaf);

void BpSpilitNode(PtrBpNode SpilitNodeP, int ChildIndex);

void BpInsertNonFull(PtrBpNode CurrentNode, ElementType Val);

void BpInsert(PtrBp T, ElementType Val);

void BpMerge(PtrBp T, PtrBpNode CurrentNode, int LeftIndex, int RightIndex);

void BpDelete(PtrBp T, PtrBpNode CurrentNode, ElementType Val);

void ShiftKey(PtrElementType Key, BoolType Direction, int Begin, int End);

void ShiftChild(PtrBpNode *Child, BoolType Direction, int Begin, int End);

int GetIndex(PtrElementType Key, int Size, ElementType Val);

void BpPrintTree(PtrBpNode Root);

void BpCreateTree(PtrBp T);

 

void bplus(){

    PtrBp T = (PtrBp)malloc(sizeof(struct Tree));

    

    T->Root = BpAllocateNode(True);

    BpCreateTree(T);

    

    //printf("B_Tree after delete 11:\n");

    //BTDelete(T, T->Root, 11);

    //BTPrintTree(T->Root);

    printf("Bp_Tree after delete 16:\n");

    BpDelete(T, T->Root, 16);

    BpPrintTree(T->Root);

    printf("Bp_Tree after delete 18:\n");

    BpDelete(T, T->Root, 18);

    BpPrintTree(T->Root);

    printf("Bp_Tree after delete 20:\n");

    BpDelete(T, T->Root, 20);

    BpPrintTree(T->Root);

    printf("Bp_Tree after delete 19:\n");

    BpDelete(T, T->Root, 19);

    BpPrintTree(T->Root);

    printf("Bp_Tree after delete 0:\n");

    BpDelete(T, T->Root, 0);

    BpPrintTree(T->Root);

    printf("Bp_Tree after delete 5:\n");

    BpDelete(T, T->Root, 5);

    BpPrintTree(T->Root);

    printf("Bp_Tree after delete 2:\n");

    BpDelete(T, T->Root, 2);

    BpPrintTree(T->Root);

    
}

 

PtrBpNode BpAllocateNode(BoolType IsLeaf){

    int i;

    PtrBpNode NewNode = (PtrBpNode)malloc(sizeof(BpNode));

    

    NewNode->Num = 0;

    if(True == IsLeaf){

        NewNode->IsLeaf = True;

    }

    else{

        NewNode->IsLeaf = False;

    }

    NewNode->Key = (PtrElementType)malloc(sizeof(ElementType) * (MinDegree * 2 - 1));

    NewNode->Child =(PtrBpNode*)malloc(sizeof(PtrBpNode) * MinDegree * 2);

    for(i = 0; i < MinDegree * 2; i++){

        NewNode->Child[i] = NULL;

    }

    NewNode->Next = NULL;

    

    return NewNode;

}

 

void BpInsert(PtrBp T, ElementType Val){

    PtrBpNode NewNode;

    

    if(MinDegree * 2 - 1 == T->Root->Num){

        NewNode = BpAllocateNode(False);

        NewNode->Child[0] = T->Root;

        T->Root = NewNode;

        BpSpilitNode(NewNode, 0);

    }

    

    BpInsertNonFull(T->Root, Val);

}

 

void BpInsertNonFull(PtrBpNode CurrentNode, ElementType Val){

    int Index = GetIndex(CurrentNode->Key, CurrentNode->Num, Val);

    

    if(True == CurrentNode->IsLeaf){

        ShiftKey(CurrentNode->Key, True, Index, CurrentNode->Num - 1);

        CurrentNode->Key[Index] = Val;

        (CurrentNode->Num)++;

    }

    else{

        if(MinDegree * 2 - 1 == CurrentNode->Child[Index]->Num){

            BpSpilitNode(CurrentNode, Index);

            if(CurrentNode->Key[Index] < Val){

                Index++;

            }

        }

        

        BpInsertNonFull(CurrentNode->Child[Index], Val);

    }

}

 

void BpSpilitNode(PtrBpNode SpilitNodeP, int ChildIndex){

    int i;

    PtrBpNode NewNode, SubNode = SpilitNodeP->Child[ChildIndex];

    

    if(True == SubNode->IsLeaf){

        NewNode = BpAllocateNode(True);

        for(i = 0; i < MinDegree - 1; i++){

            NewNode->Key[i] = SubNode->Key[i + MinDegree];

        }

        NewNode->Num = MinDegree - 1;

        SubNode->Num = MinDegree;

        NewNode->Next = SubNode->Next;

        SubNode->Next = NewNode;

    }

    else{

        NewNode = BpAllocateNode(False);

        for(i = 0; i < MinDegree - 1; i++){

            NewNode->Key[i] = SubNode->Key[i + MinDegree];

        }

        for(i = 0; i < MinDegree; i++){

            NewNode->Child[i] = SubNode->Child[i + MinDegree];

        }

        NewNode->Num = SubNode->Num = MinDegree - 1;

    }

    

    ShiftKey(SpilitNodeP->Key, True, ChildIndex, SpilitNodeP->Num - 1);

    ShiftChild(SpilitNodeP->Child, True, ChildIndex + 1, SpilitNodeP->Num);

    SpilitNodeP->Key[ChildIndex] = SubNode->Key[MinDegree - 1];

    SpilitNodeP->Child[ChildIndex + 1] = NewNode;

    (SpilitNodeP->Num)++;

}

 

void ShiftKey(PtrElementType Key, BoolType Direction, int Begin, int End){

    int i;

    

    if(True == Direction){

        for(i = End; i >= Begin; i--){

            Key[i + 1] = Key[i];

        }

    }

    else{

        for(i = Begin; i <= End; i++){

            Key[i - 1] = Key[i];

        }

    }

}

 

void ShiftChild(PtrBpNode *Child, BoolType Direction, int Begin, int End){

    int i;

    

    if(True == Direction){

        for(i = End; i >= Begin; i--){

            Child[i + 1] = Child[i];

        }

    }

    else{

        for(i = Begin; i <= End; i++){

            Child[i - 1] = Child[i];

        }

    }

}

 

int GetIndex(PtrElementType Key, int Size, ElementType Val){

    int i;

    

    for(i = 0; i < Size; i++){

        if(Key[i] >= Val){

            break;

        }

    }

    

    return i;

}

 

void BpDelete(PtrBp T, PtrBpNode CurrentNode, ElementType Val){

    int Index = GetIndex(CurrentNode->Key, CurrentNode->Num, Val);

    PtrBpNode Precursor, SubNode, Successor;

    

    if(Index < CurrentNode->Num && Val == CurrentNode->Key[Index]){

        

        if(True == CurrentNode->IsLeaf){

            ShiftKey(CurrentNode->Key, False, Index + 1, CurrentNode->Num - 1);

            (CurrentNode->Num)--;

            return;

        }

        else{

            Precursor = CurrentNode->Child[Index];

            Successor = CurrentNode->Child[Index + 1];

            

            if(Precursor->Num >= MinDegree){

                if(True == SubNode->IsLeaf){

                    CurrentNode->Key[Index] = Precursor->Key[SubNode->Num - 2];

                }

                else{

                    CurrentNode->Key[Index] = Precursor->Key[SubNode->Num - 1];

                }

                

                BpDelete(T, Precursor, Precursor->Key[SubNode->Num - 1]);

            }

            else if(Successor->Num >= MinDegree){

                CurrentNode->Key[Index] = Successor->Key[0];

                if(True == SubNode->IsLeaf){

                    SubNode->Key[SubNode->Num - 1] = CurrentNode->Key[Index];

                }

                

                BpDelete(T, Successor, Successor->Key[0]);

            }

            else{

                BpMerge(T, CurrentNode, Index, Index + 1);

                

                BpDelete(T, Precursor, Val);

            }

        }

        

    }

    else{

        

        if(True == CurrentNode->IsLeaf){

            return;

        }

        else{

            if(Index > 0){

                Precursor = CurrentNode->Child[Index - 1];

            }

            SubNode = CurrentNode->Child[Index];

            if(Index < CurrentNode->Num){

                Successor = CurrentNode->Child[Index + 1];

            }

            

            

            if(SubNode->Num >= MinDegree){

                BpDelete(T, SubNode, Val);

            }

            else{

                if(Index > 0 && Precursor->Num >= MinDegree){

                    ShiftKey(SubNode->Key, True, 0, SubNode->Num - 1);

                    SubNode->Key[0] = CurrentNode->Key[Index - 1];

                    

                    if(True == SubNode->IsLeaf){

                        CurrentNode->Key[Index - 1] = Precursor->Key[Precursor->Num - 2];

                    }

                    else{

                        CurrentNode->Key[Index - 1] = Precursor->Key[Precursor->Num - 1];

                        ShiftChild(SubNode->Child, True, 0, SubNode->Num);

                        SubNode->Child[0] = Precursor->Child[Precursor->Num];

                    }

                    (SubNode->Num)++;

                    (Precursor->Num)--;

                    

                    BpDelete(T, SubNode, Val);

                }

                else if(Index < CurrentNode->Num && Successor->Num >= MinDegree){

                    if(True == SubNode->IsLeaf){

                        SubNode->Key[SubNode->Num] = Successor->Key[0];

                    }

                    else{

                        SubNode->Key[SubNode->Num] = CurrentNode->Key[Index];

                    }

                    CurrentNode->Key[Index] = Successor->Key[0];

                    SubNode->Child[SubNode->Num + 1] = Successor->Child[0];

                    (SubNode->Num)++;

                    

                    ShiftKey(Successor->Key, False, 1, Successor->Num - 1);

                    ShiftChild(Successor->Child, False, 1, Successor->Num);

                    (Successor->Num)--;

                    

                    BpDelete(T, SubNode, Val);

                }

                else{

                    if(Index > 0){

                        BpMerge(T, CurrentNode, Index - 1, Index);

                        BpDelete(T, Precursor, Val);

                    }

                    else{

                        BpMerge(T, CurrentNode, Index, Index + 1);

                        BpDelete(T, SubNode, Val);

                    }

                }

            }

        }

        

    }

}

 

void BpMerge(PtrBp T, PtrBpNode CurrentNode, int LeftIndex, int RightIndex){

    int i;

    PtrBpNode LeftNode = CurrentNode->Child[LeftIndex];

    PtrBpNode RightNode = CurrentNode->Child[RightIndex];

    

    if(True == LeftNode->IsLeaf){

        for(i = 0; i < MinDegree - 1; i++){

            LeftNode->Key[i + MinDegree - 1] = RightNode->Key[i];

        }

        LeftNode->Num = MinDegree * 2 - 2;

        LeftNode->Next = RightNode->Next;

    }

    else{

        for(i = 0; i < MinDegree - 1; i++){

            LeftNode->Key[i + MinDegree] = RightNode->Key[i];

        }

        for(i = 0; i < MinDegree; i++){

            LeftNode->Key[i + MinDegree] = RightNode->Key[i];

        }

        LeftNode->Key[MinDegree - 1] = CurrentNode->Key[LeftIndex];

        LeftNode->Num = MinDegree * 2 - 1;

    }

    

    ShiftKey(CurrentNode->Key, False, LeftIndex + 1, CurrentNode->Num - 1);

    ShiftChild(CurrentNode->Child, False, RightIndex + 1, CurrentNode->Num);

    (CurrentNode->Num)--;

    

    if(CurrentNode == T->Root && 0 == CurrentNode->Num){

        T->Root = LeftNode;

    }

}

 

void BpPrintTree(PtrBpNode Root){

    int i;

    

    if(NULL == Root){

        return;

    }

    

    putchar('[');

    for(i = 0; i < Root->Num; i++){

        printf("%d", Root->Key[i]);

        if(i != Root->Num - 1){

            putchar(' ');

        }

    }

    putchar(']');

    printf("%d ", Root->IsLeaf);

    printf("%d", Root->Num);

    putchar('\n');

    

    for(i = 0; i <= Root->Num; i++){

        BpPrintTree(Root->Child[i]);

    }

}

 

void BpCreateTree(PtrBp T){

    int i;

    int a[] = {12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17,20,21,23};

    

    for(i = 0; i < 23; i++){

        BpInsert(T, a[i]);

        BpPrintTree(T->Root);

        printf("The End\n");

    }

}


/**********************************************/
void treemenu(){
	int n;
	char y='n';
	char m;
	printf("��ѡ��\n1�������\t\t2��b+��\t\t3���˳�\n");
	while(1){
		scanf("%d",&n);
		if(n==3)
			break;
		switch(n)
		{
			case 1:rb1();
			case 2:bplus();
			default:printf("�����������������\n");
		}

	}
}



int main()
{
 
 int x;
 while (1)
 {
  printf("-------------����ѡ��-----------\n");
  	printf("1����\t\t2����\n");
	printf("3��ջ\t\t4��ͼ\n");
	printf("5������\n");		
    printf("6:���ز˵� \n");
    printf("7:�˳����� \n");
  printf("--------------------------------\n");
 
  
  printf("�����ּ�ѡ��Ҫִ�еĲ���: ");
  scanf("%d",&x);
  printf("\n");
 
  //����2����ѭ�����˳�����
  if(x==7)
      break;
   
  switch(x)
  {
  case 1:treemenu();
    break; //����1������switch��䣬������һ��ѭ��
  case 2:heap();
    break;  
  case 3:stack1();
    break;
  case 4:gp(); 
    break;
  case 5:list1();
    break;
  case 6:
    break;
  case 7:break;
  default:  //���������������siwtch��䣬������һ��ѭ��
      printf("��������ֲ���ȷ\n");
      break;
  }
  
 }
 return 0;
}
