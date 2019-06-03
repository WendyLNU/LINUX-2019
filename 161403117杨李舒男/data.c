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

#define CHECK_INSERT 0    // "插入"动作的检测开关(0，关闭；1，打开)
#define CHECK_DELETE 0    // "删除"动作的检测开关(0，关闭；1，打开)
#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )
/**************************堆*****************************************************************************************/
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
        child = 2*i+1; //注意数组下标是从0开始的，所以左孩子的求发不是2*i
        if (child != N - 1 && A[child + 1] > A[child])
            ++child;                //找到最大的儿子节点
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
        PercDown(A, i, N);    //构造堆
    for(i=N-1;i>0;--i)
    {
        Swap(&A[0],&A[i]);        //将最大元素（根）与数组末尾元素交换，从而删除最大元素，重新构造堆
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
    printf("随机输入10个整数：\n" );
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

/**************************栈**************************************************************************/ 
//定义栈

typedef struct stack

{

    char data[MaxSize];//数组实现栈内元素定位

    int top;//作为数组下标

    int buttom;

} stack;

 

//创建一个空栈

stack * CreateStack()

{

    stack * st = (stack*)malloc(sizeof(stack));

    if(st == NULL)

        return false;//分配空间失败

    st->top = st->buttom = 0;

    return st;

}

 

//入栈

void Push(stack * st, char data)

{

    st->data[st->top]= data;

    st->top++;

}

 

//出栈

void Pop(stack * st, char data)

{

    int n = st->top;

    while(n != st->buttom)//判断是否是空栈

    {

        if(st->data[n-1] == data)

        {

            st->top = n-1;

            break;

        }

        n--;

    }

}

 

//打印栈元素

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

    printf("开始进栈：\n");

    while(i--)

    {

        Push(st,'A'+i);

        printf("%c入栈后,栈内元素为： ",'A'+i);

        Display(st);

    }

    printf("开始出栈：\n");

    while(j--)

    {

 

        Pop(st,'E'-j);

        printf("%c出栈后,栈内元素为： ",'E'-j);

        Display(st);

    }
    free(st); 


}
/****************************************************************************************************/
/************链表***************************************************************************************/

//    定义链表中的节点  
typedef struct node  
{  
    int member;                //    节点中的成员  
    struct node *pNext;        //    指向下一个节点的指针  
}*pNode;  
  
//    函数声明  
pNode CreateList();                 //  创建链表函数  
void TraverseList(pNode );            //  遍历链表函数  
bool Insert_Node(pNode ,int ,int);    //    链表节点插入函数,第一个参数是头节点，第二个参数是要在第几个节点前插入，第三个参数是要插入的数据  
int Del_Node(pNode,int );        //    删除链表节点,第一个参数是头节点，第二个参数是删除第几个节点，第三个作为  
void list1()  
{  
    pNode pHead = NULL;                //  定义初始化头节点，等价于 struct Node *pHead == NULL  
    int data;                        // 作为Insert_Node函数的第三个参数  
    int num;                        //    作为Inset_Node函数第二个参数  
    int choose;      
    int return_val;  
    pHead = CreateList();            //  创建一个非循环单链表，并将该链表的头结点的地址付给pHead  
    printf("你输入的数据是：");  
    TraverseList(pHead);    //  调用遍历链表函数  
    printf("是否还要进行如下操作：\n");  
    printf("1.插入数据      2.删除数据\n");  
    printf("请输入：");  
    scanf("%d",&choose);  
    switch (choose)  
    {  
        case 1:  
            {  
                printf("请输入要在第几个节点前插入数据：");  
                scanf("%d",&num);  
                printf("请输入要插入的数据：");  
                scanf("%d",&data);  
                if(Insert_Node(pHead,num,data) == true)  
                {  
                    printf("插入成功\n插入后的数据是：\n");  
                    TraverseList(pHead);  
                }  
                else  
                {  
                    printf("插入失败\n");  
                }  
                printf("操作完成后的数据是：");  
                TraverseList(pHead);  
                break;  
            }  
        case 2:  
            {  
                printf("请输入要删除第几个节点的数据：");  
                scanf("%d",&num);  
                return_val = Del_Node(pHead,num);  
                if (return_val == 0)  
                {  
                    printf("删除失败。\n");  
                }  
                else  
                {  
                    printf("删除成功。删除的元素是：%d\n",return_val);  
                }  
                printf("操作完成后的数据是：");  
                TraverseList(pHead);  
            }  
        default:printf("输入错误！\n");
    }  
    free(pHead); 

}  
  
//    创建链表函数  
pNode CreateList()  
{  
    int i;                                            //    用于下面循环  
    int len;                                        //    用来存放有效节点的字数  
    int val;                                        //    用于临时存放用户输入的数据  
    pNode pHead = (pNode)malloc(sizeof(Node));        //  分配一个不存放有效数据的头结点  
    pNode pTail = pHead;                            //    链表的最后一个节点  
    pTail->pNext = NULL;                            //    最后一个节点的指针置为空  
    printf("请输入节点个数：");  
    scanf("%d",&len);  
    for(i = 0; i < len; i++)  
    {  
        printf("第 %d 个节点的数值：",i+1);  
        scanf("%d",&val);  
        pNode pNew = (pNode)malloc(sizeof(Node));    //    为节点分配空间  
        pNew->member = val;                            //将用户输入的数据赋给节点的成员  
        pTail->pNext = pNew;                        //将最后一个节点的指针指向下一个新的节点  
        pNew->pNext = NULL;                            //将新节点中的指针置为空  
        pTail = pNew;                                //将新节点赋给最后的一个节点  
    }  
    return pHead;                                    //返回头节点  
  
}  
  
//    遍历链表函数  
void TraverseList(pNode pHead)  
{  
    pNode p = pHead->pNext;                            //将头节点的指针给予临时节点p  
    while(NULL != p)                                //节点p不为空，循环      
    {  
        printf("%d ",p->member);                      
        p = p->pNext;                                  
    }  
    printf("\n");  
    return ;  
}  
  
//    链表节点插入函数  
//    第一个参数是头节点，第二个参数是要在第几个节点前插入，第三个参数是要插入的数据  
bool Insert_Node(pNode pHead, int front,int data)  
{  
    int i = 0;  
    pNode _node = pHead;  
    pNode pSwap;                                //    用于交换  
    if ((front < 1) && (NULL != _node))        //判断用户输入的数据是否大于等于1,及_node是否为空  
    {  
        return false;  
    }  
    while (i < front - 1)                    //通过循环使指针指向要插入哪个节点前的节点。说的自己都不懂了，还是看下面的图吧。      
    {  
        _node = _node->pNext;  
        ++i;  
    }  
    pNode pNew = (pNode)malloc(sizeof(Node));  
  
    pNew->member = data;                        //    把输入的数据赋给要插入的节点  
    pSwap = _node->pNext;                        //    把下一个节点的地址，给用于交换的pSwap  
    _node->pNext = pNew;                        //    把要插入的节点的地址，给上个节点的指针域  
    pNew->pNext = pSwap;                        //    把插入节点的下一个节点的地址，给插入节点的指针域  
    return true;  
  
}  
  
//    删除链表节点函数  
//    第一个参数是头节点，第二个参数是要删除第几个节点·······和上面的插入函数是不是很像  
int Del_Node(pNode pHead,int back)  
{  
    int i = 0;  
    int data;  
    pNode _node = pHead;  
    pNode pSwap;  
    if ((back < 1) && (NULL == _node->pNext))  
    {  
        printf("删除失败！\n");  
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
/**********图*************************************/
typedef char VertexType;

typedef enum

{

	DG,UDG

}GraphType;

typedef struct

{

	VertexType vexs[MAX_VER_NUM];        //顶点向量

	int arcs[MAX_VER_NUM][MAX_VER_NUM];  //邻接矩阵

	int vexnum,arcnum;                   //图的当前顶点数和弧数

	GraphType type;                      //图的种类标志

}MGraph; 

 

//根据名称得到指定顶点在顶点集合中的下标

//vex 顶点

//return 如果找到，则返回下标，否则，返回0

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

 

//创建邻接矩阵

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

	//初始化邻接矩阵

	for(i=1;i<=MG->vexnum;i++)

	{

		for (j=1;j<=MG->vexnum;j++)

		{

			MG->arcs[i][j]=0;

		}

	}

	//输入边的信息，建立邻接矩阵

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

 

//打印邻接矩阵和顶点信息

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

 

//主函数

int gp() 

{

	MGraph MG;

	create_MG(&MG);

	print_MG(MG);


}

/***********************************************/
/**********红黑树*************************************/

/*
 * 创建红黑树，返回"红黑树的根"！
 */
RBRoot* create_rbtree()
{
    RBRoot *root = (RBRoot *)malloc(sizeof(RBRoot));
    root->node = NULL;

    return root;
}

/*
 * 前序遍历"红黑树"
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
 * 中序遍历"红黑树"
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
 * 后序遍历"红黑树"
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
 * (递归实现)查找"红黑树x"中键值为key的节点
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
 * (非递归实现)查找"红黑树x"中键值为key的节点
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
 * 查找最小结点：返回tree为根结点的红黑树的最小结点。
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
 * 查找最大结点：返回tree为根结点的红黑树的最大结点。
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
 * 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
 */
static Node* rbtree_successor(RBTree x)
{
    // 如果x存在右孩子，则"x的后继结点"为 "以其右孩子为根的子树的最小结点"。
    if (x->right != NULL)
        return minimum(x->right);

    // 如果x没有右孩子。则x有以下两种可能：
    // (01) x是"一个左孩子"，则"x的后继结点"为 "它的父结点"。
    // (02) x是"一个右孩子"，则查找"x的最低的父结点，并且该父结点要具有左孩子"，找到的这个"最低的父结点"就是"x的后继结点"。
    Node* y = x->parent;
    while ((y!=NULL) && (x==y->right))
    {
        x = y;
        y = y->parent;
    }

    return y;
}
 
/* 
 * 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
 */
static Node* rbtree_predecessor(RBTree x)
{
    // 如果x存在左孩子，则"x的前驱结点"为 "以其左孩子为根的子树的最大结点"。
    if (x->left != NULL)
        return maximum(x->left);

    // 如果x没有左孩子。则x有以下两种可能：
    // (01) x是"一个右孩子"，则"x的前驱结点"为 "它的父结点"。
    // (01) x是"一个左孩子"，则查找"x的最低的父结点，并且该父结点要具有右孩子"，找到的这个"最低的父结点"就是"x的前驱结点"。
    Node* y = x->parent;
    while ((y!=NULL) && (x==y->left))
    {
        x = y;
        y = y->parent;
    }

    return y;
}

/* 
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y                
 *   /  \      --(左旋)-->           / \                #
 *  lx   y                          x  ry     
 *     /   \                       /  \
 *    ly   ry                     lx  ly  
 *
 *
 */
static void rbtree_left_rotate(RBRoot *root, Node *x)
{
    // 设置x的右孩子为y
    Node *y = x->right;

    // 将 “y的左孩子” 设为 “x的右孩子”；
    // 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    // 将 “x的父亲” 设为 “y的父亲”
    y->parent = x->parent;

    if (x->parent == NULL)
    {
        //tree = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
        root->node = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
        else
            x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
    }
    
    // 将 “x” 设为 “y的左孩子”
    y->left = x;
    // 将 “x的父节点” 设为 “y”
    x->parent = y;
}

/* 
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *            py                               py
 *           /                                /
 *          y                                x                  
 *         /  \      --(右旋)-->            /  \                     #
 *        x   ry                           lx   y  
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 * 
 */
static void rbtree_right_rotate(RBRoot *root, Node *y)
{
    // 设置x是当前节点的左孩子。
    Node *x = y->left;

    // 将 “x的右孩子” 设为 “y的左孩子”；
    // 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    // 将 “y的父亲” 设为 “x的父亲”
    x->parent = y->parent;

    if (y->parent == NULL) 
    {
        //tree = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
        root->node = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
        else
            y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
    }

    // 将 “y” 设为 “x的右孩子”
    x->right = y;

    // 将 “y的父节点” 设为 “x”
    y->parent = x;
}

/*
 * 红黑树插入修正函数
 *
 * 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 插入的结点        // 对应《算法导论》中的z
 */
static void rbtree_insert_fixup(RBRoot *root, Node *node)
{
    Node *parent, *gparent;

    // 若“父节点存在，并且父节点的颜色是红色”
    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);

        //若“父节点”是“祖父节点的左孩子”
        if (parent == gparent->left)
        {
            // Case 1条件：叔叔节点是红色
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

            // Case 2条件：叔叔是黑色，且当前节点是右孩子
            if (parent->right == node)
            {
                Node *tmp;
                rbtree_left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是左孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_right_rotate(root, gparent);
        } 
        else//若“z的父节点”是“z的祖父节点的右孩子”
        {
            // Case 1条件：叔叔节点是红色
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

            // Case 2条件：叔叔是黑色，且当前节点是左孩子
            if (parent->left == node)
            {
                Node *tmp;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是右孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            rbtree_left_rotate(root, gparent);
        }
    }

    // 将根节点设为黑色
    rb_set_black(root->node);
}

/*
 * 添加节点：将节点(node)插入到红黑树中
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 插入的结点        // 对应《算法导论》中的z
 */
static void rbtree_insert(RBRoot *root, Node *node)
{
    Node *y = NULL;
    Node *x = root->node;

    // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
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
            y->left = node;                // 情况2：若“node所包含的值” < “y所包含的值”，则将node设为“y的左孩子”
        else
            y->right = node;            // 情况3：(“node所包含的值” >= “y所包含的值”)将node设为“y的右孩子” 
    }
    else
    {
        root->node = node;                // 情况1：若y是空节点，则将node设为根
    }

    // 2. 设置节点的颜色为红色
    node->color = RED;

    // 3. 将它重新修正为一颗二叉查找树
    rbtree_insert_fixup(root, node);
}

/*
 * 创建结点
 *
 * 参数说明：
 *     key 是键值。
 *     parent 是父结点。
 *     left 是左孩子。
 *     right 是右孩子。
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
    p->color = BLACK; // 默认为黑色

    return p;
}

/* 
 * 新建结点(节点键值为key)，并将其插入到红黑树中
 *
 * 参数说明：
 *     root 红黑树的根
 *     key 插入结点的键值
 * 返回值：
 *     0，插入成功
 *     -1，插入失败
 */
int insert_rbtree(RBRoot *root, Type key)
{
    Node *node;    // 新建结点

    // 不允许插入相同键值的节点。
    // (若想允许插入相同键值的节点，注释掉下面两句话即可！)
    if (search(root->node, key) != NULL)
        return -1;

    // 如果新建结点失败，则返回。
    if ((node=create_rbtree_node(key, NULL, NULL, NULL)) == NULL)
        return -1;

    rbtree_insert(root, node);

    return 0;
}

/*
 * 红黑树删除修正函数
 *
 * 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 待修正的节点
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
                // Case 1: x的兄弟w是红色的  
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rbtree_right_rotate(root, other);
                    other = parent->right;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
                // Case 1: x的兄弟w是红色的  
                rb_set_black(other);
                rb_set_red(parent);
                rbtree_right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    rb_set_black(other->right);
                    rb_set_red(other);
                    rbtree_left_rotate(root, other);
                    other = parent->left;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
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
 * 删除结点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     node 删除的结点
 */
void rbtree_delete(RBRoot *root, Node *node)
{
    Node *child, *parent;
    int color;

    // 被删除节点的"左右孩子都不为空"的情况。
    if ( (node->left!=NULL) && (node->right!=NULL) ) 
    {
        // 被删节点的后继节点。(称为"取代节点")
        // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
        Node *replace = node;

        // 获取后继节点
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        // "node节点"不是根节点(只有根节点不存在父节点)
        if (rb_parent(node))
        {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        } 
        else 
            // "node节点"是根节点，更新根节点。
            root->node = replace;

        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = replace->right;
        parent = rb_parent(replace);
        // 保存"取代节点"的颜色
        color = rb_color(replace);

        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node)
        {
            parent = replace;
        } 
        else
        {
            // child不为空
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
    // 保存"取代节点"的颜色
    color = node->color;

    if (child)
        child->parent = parent;

    // "node节点"不是根节点
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
 * 删除键值为key的结点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     key 键值
 */
void delete_rbtree(RBRoot *root, Type key)
{
    Node *z, *node; 

    if ((z = search(root->node, key)) != NULL)
        rbtree_delete(root, z);
}

/*
 * 销毁红黑树
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
 * 打印"红黑树"
 *
 * tree       -- 红黑树的节点
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
static void rbtree_print(RBTree tree, Type key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            printf("%2d(B) is root\n", tree->key);
        else                // tree是分支节点
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
    printf("== 原始数据: ");
    for(i=0; i<ilen; i++)
        printf("%d ", a[i]);
    printf("\n");

    for(i=0; i<ilen; i++)
    {
        insert_rbtree(root, a[i]);
#if CHECK_INSERT
        printf("== 添加节点: %d\n", a[i]);
        printf("== 树的详细信息: \n");
        print_rbtree(root);
        printf("\n");
#endif
    }

    printf("== 前序遍历: ");
    preorder_rbtree(root);

    printf("\n== 中序遍历: ");
    inorder_rbtree(root);

    printf("\n== 后序遍历: ");
    postorder_rbtree(root);
    printf("\n");

    if (rbtree_minimum(root, &i)==0)
        printf("== 最小值: %d\n", i);
    if (rbtree_maximum(root, &i)==0)
        printf("== 最大值: %d\n", i);
    printf("== 树的详细信息: \n");
    print_rbtree(root);
    printf("\n");

#if CHECK_DELETE
    for(i=0; i<ilen; i++)
    {
        delete_rbtree(root, a[i]);

        printf("== 删除节点: %d\n", a[i]);
        if (root)
        {
            printf("== 树的详细信息: \n");
            print_rbtree(root);
            printf("\n");
        }
    }
#endif

    destroy_rbtree(root);
} 
/**********************************************/
/*******b+树***********************************/

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
	printf("请选择；\n1、红黑树\t\t2、b+树\t\t3、退出\n");
	while(1){
		scanf("%d",&n);
		if(n==3)
			break;
		switch(n)
		{
			case 1:rb1();
			case 2:bplus();
			default:printf("输入错误！请重新输入\n");
		}

	}
}



int main()
{
 
 int x;
 while (1)
 {
  printf("-------------操作选项-----------\n");
  	printf("1、树\t\t2、堆\n");
	printf("3、栈\t\t4、图\n");
	printf("5、链表\n");		
    printf("6:返回菜单 \n");
    printf("7:退出程序 \n");
  printf("--------------------------------\n");
 
  
  printf("按数字键选择要执行的操作: ");
  scanf("%d",&x);
  printf("\n");
 
  //输入2跳出循环，退出程序
  if(x==7)
      break;
   
  switch(x)
  {
  case 1:treemenu();
    break; //输入1，跳出switch语句，进入下一次循环
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
  default:  //数字输入错误，跳出siwtch语句，进入下一次循环
      printf("输入的数字不正确\n");
      break;
  }
  
 }
 return 0;
}
