#include<stdio.h> 
#include <stdlib.h>
#include <malloc.h>             // 申请内存
#include <ctype.h>              // 内含isdigit()函数
#include <assert.h>             // 断言函数
#include <string.h>             // 内含字符串处理函数

//二叉搜索树--------------------------------------------------- 
struct tnode
{
	int data;
	struct tnode *lchild;
	struct tnode *rchild;
};
struct tnode * tree_insert(struct tnode *root,int data)//插入二叉搜索树的节点 
{
	struct tnode *s;
	//构造要插入的节点
	s=(struct tnode *)malloc(sizeof(struct tnode));
	s->data=data;
	s->lchild=NULL;
	s->rchild=NULL;
	if(root==NULL)
	{
		root=s;
	} 
	else
	{
		if(root->data==s->data)
			return root;
		else
		{
			if(s->data>root->data)
				//tree_insert(root->rchild,s->data); 这样写是错误的，因为不能将根节点和子节点连接在一块。 仔细想一下递归过程。 
				root->rchild=tree_insert(root->rchild,s->data);
			else
				//tree_insert(root->lchild,s->data); 这样写是错误的，因为不能将根节点和子节点连接在一块。
				root->lchild=tree_insert(root->lchild,s->data);
		}
	}
	return root;
}
void tree_scaner(struct tnode *root)
{
	if(root==NULL)
		return;
	
//	printf("%d ",root->data);
	tree_scaner(root->lchild);
	printf("%d ",root->data);
	tree_scaner(root->rchild);
}
int tree_search(struct tnode* root,int data)
{
	if(root==NULL)
		return 0; //return -1程序出错，if语句认为-1不是FALSE。而0是FALSE。 
	else
	{
		if(root->data==data)
			return 1;
		else if(root->data<data)
			return tree_search(root->rchild,data);
		else
			 return tree_search(root->lchild,data);
			
	}
	//return 0; 
}
 
int tree_delete(struct tnode* root,int data)
{
	struct tnode *p,*pf,*t,*s,*sf;
	//找到要删除的节点 
	t=root;
	int flag=0; 
	if(t->data==data)
	{
		p=root;
		flag=1;
	}
	//出现的一个错误，就是下面的while循环里面，全都是if，而不是if-else，这样是不对的，因为程序的本意是一次循环只执行三种情况的一种。 
	while(t!=NULL)  
	{
		if(t->data>data)
		{
			pf=t;
			t=t->lchild;
		}
		else if(t->data<data)
		{
			pf=t;
			t=t->rchild;
		}
		else if(t->data==data)
		{
			p=t;
			flag=1;
			break;
		}
	}
	//找到要删除的节点
	
	//根据三种不同情况删除节点
	if(flag==0)
	{
		printf("this node not in the tree!");
	} 
	//出现的一个错误，三种情况全用if，而不是if-else，这样是不对的，因为程序的本意是一次循环只执行三种情况的一种。 
	if(p->lchild==NULL&&p->rchild==NULL)
	{
		if(p==root)
		{
			root=NULL;
		}
		else
		{
			//不能这样写<span style="font-family: Arial, Helvetica, sans-serif;">p=NULL;</span>
			if(pf->lchild==p)
				pf->lchild=NULL;
			else
				pf->rchild=NULL;//体会这两种写法的不同。 
		}
	}
	else if((p->lchild==NULL&&p->rchild!=NULL)||(p->lchild!=NULL&&p->rchild==NULL))
	{
		if(p==root)
		{
			if(p->lchild==NULL) 
				root=p->rchild;
			else
				root=p->lchild;
		}
		else
		{
			if(p->lchild==NULL) 
			{
				if(pf->rchild==p)
				{
					pf->rchild=p->rchild;
				}
				else
				{
					pf->lchild=p->rchild;
				}
			}
			else
			{
				if(pf->rchild==p)
				{
					pf->rchild=p->lchild;
				}
				else
				{
					pf->lchild=p->rchild;
				}
			}
		}
	}
	
	else if(p->lchild!=NULL&&p->rchild!=NULL)
	{
		s=p->rchild;
		while(s->lchild!=NULL)
		{
			sf=s;
			s=s->lchild;
		}
		p->data=s->data;
		sf->lchild=s->rchild;
	} 
	
}
int searchtree(void)
{
	struct tnode *root;
	int data,i;
	int tree[12]={15,16,20,18,23,5,12,13,3,10,6,7};
//	root=(struct tnode *)malloc(sizeof(struct tnode));
//构建二叉搜索树 
	root=NULL;//need or not?必须要赋NULL值，因为当节点为空时就把改节点当成根节点。 
	//while(scanf("%d",&data)!=EOF)
	for(i=0;i<12;++i)
	{
		data=tree[i];
		root=tree_insert(root,data);
	}
	//构建二叉搜索树
	tree_scaner(root);//遍历二叉搜索树 
	//在二叉搜索树种查找某个节点
	printf("search a key:");
	scanf("%d",&data);
	if(tree_search(root,data)) 
	{
		printf("yes\n");
	}
	else
	{
		printf("failed\n");
	}
		printf("insert key:");
	scanf("%d",&data);
	tree_insert(root,data);
	printf("delete key:");
	scanf("%d",&data);
	tree_delete(root,data);
	tree_scaner(root);

	
}
//栈解析算术表达式------------------------------------------------- 

#define STACK_INIT_SIZE 100     // 栈容量
#define STACK_INCREMENT 10      // 栈增量

 
typedef float DATATYPE;
typedef char SYMBOLTYPE;
 
typedef struct stack
{
    int *base;         // 基地址
    int *top;          // 栈顶指针
    int stackSize;          // 栈容量
}*Stack;
 
// 栈的初始化
Stack Init_Stack(Stack S)
{
    S=(Stack)malloc(sizeof(Stack));
    if(!S)
        exit(0);
    S->base = (int*)malloc(STACK_INIT_SIZE*sizeof(DATATYPE));
    if(!S->base)
        exit(0);
    S->top = S->base;
    S->stackSize = STACK_INIT_SIZE;
    return S;
}
 
// 判栈空
int IsEmpty(Stack S)
{
    if (S->top == S->base)
    {
        return 1;
    } else
    {
        return 0;
    }
}
 
// 判栈满
int IsFull(Stack S)
{
    if (S->top - S->base == S->stackSize)
    {
        return 1;
    } else
    {
        return 0;
    }
}
 
// 操作数压栈
void Push(Stack S, DATATYPE e)
{
    assert(S);
    if (IsFull(S))
    {
        S->base = (int*)malloc((STACK_INIT_SIZE+STACK_INCREMENT)*sizeof(DATATYPE));
        if (!S->base)
            exit(0);        // 存储分配失败
        S->top = S->base + S->stackSize;
        S->stackSize += STACK_INCREMENT;
    }
    *S->top++ = e;
}
 
// 运算符压栈
void PushSymbol(Stack S, SYMBOLTYPE e)
{
    assert(S);
    if (IsFull(S))
    {
        S->base = (int*)malloc((STACK_INIT_SIZE+STACK_INCREMENT)*sizeof(DATATYPE));
        if (!S->base)
            exit(0);        // 存储分配失败
        S->top = S->base + S->stackSize;
        S->stackSize += STACK_INCREMENT;
    }
    *S->top++ = e;
}
 
// 操作数弹栈
DATATYPE Pop(Stack S)
{
    assert(S);
    if (S->top == S->base)
        return 0;              // 空栈弹出0保证部分负数的正确运算
    else
    {
        return *--S->top;     // *--S->top就是*(--S->top)
    }
}
 
// 运算符弹栈
SYMBOLTYPE PopSymbol(Stack S)
{
    assert(S);
    if (S->top == S->base)
        return 0;
    else
    {
        return *--S->top;
    }
}
 
// 栈的销毁
void DestroyStack(Stack S) {
      free(S->base);
      free(S);
}
 
// 运算符优先级表
char Priority[7][7] =
{           // '+' '-' '*' '/' '(' ')' '#'          行row（左边的）是栈顶运算符，列col（上边的）是入栈运算符
   {/*'+'*/'>','>','<','<','<','>','>'},
    {/*'-'*/'>','>','<','<','<','>','>'},
    {/*'*'*/'>','>','>','>','<','>','>'},
    {/*'/'*/'>','>','>','>','<','>','>'},
    {/*'('*/'<','<','<','<','<','=','0'},
    {/*')'*/'>','>','>','>','0','>','>'},
   {/*'#'*/'<','<','<','<','<','0','='}
};
 
// 确定运算符所在的行数或列数
int Operator(char c)
{
    switch(c)
    {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '(': return 4;
        case ')': return 5;
        case '#': return 6;
        default:  return -1;
    }
}
 
// 计算弹出的两个操作数与弹出栈顶运算符的值
float Calculation(float a, char op, float b)
{
    switch(op)
    {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '/': return a/b;
        default:  return -1;
    }
}
 
// 表达式求值函数
float CalculatingExpression(char *s)
{
    int i;
    strcat(s, "#");                 // 为表达式s串接"#"
    Stack OPND=NULL;
    OPND = Init_Stack(OPND);        // 创建操作数栈
    Stack OPTR=NULL;
    OPTR = Init_Stack(OPTR);        // 创建运算符栈
    PushSymbol(OPTR, '#');          //"#"压栈作为运算符栈的栈底元素
    for (i=0; i<strlen(s); ++i)
    {
        while(s[i]==' ')            // while循环跳过空格
            ++i;
        if (isdigit(s[i]))          // 判断是否是数字
        {
            int j=i;
            ++i;
            while(isdigit(s[i]))        // 确定是几位数
            {
                ++i;
            }
            if (!isdigit(s[i]))     // 将while循环里因判断是否是数字多加的i值减去
                --i;
            char str[10]="";
            for (; j<=i; ++j)           // 将字符串数组下标j到i的数字字符转换为字符串
            {
                char c[2] = {s[j]};
                strcat(str, c);
            }
            float operand = atof(str);  // 将字符串转换为浮点数
            Push(OPND, operand);        // 浮点数压入操作数栈
        }
        else {
            int row = Operator(*(OPTR->top-1)), col = Operator(s[i]);       // 确定栈顶运算符的行数，入栈运算符的列数
            switch(Priority[row][col])              // 确定优先级
            {
                case '<': PushSymbol(OPTR, s[i]); break;
                case '>': Push(OPND, Calculation(Pop(OPND), PopSymbol(OPTR), Pop(OPND))); --i; break;       
                             //Push()参数里右边的Pop先执行；--i是为了下次继续对当前入栈运算符s[i]进行判断
                case '=': PopSymbol(OPTR); break;
                default:  printf("输入错误，请检查数字之间是否有空格，表达式是否正确！\n");
                          DestroyStack(OPTR);
                          DestroyStack(OPND);
                          return 0;           // 运行到这一步，说明表达式错误，直接返回调用函数（主函数）
            }
        }
    }
    DestroyStack(OPTR);
    return Pop(OPND);       // 运行到这一步，说明表达式正确，弹出操作数栈的值即为运算结果
}
 
void stack1()
{
    char s[100];
    printf("请输入要计算的表达式：\n");
    scanf("%s",s);
    printf("表达式 %s 的值为：\n", s);
    printf("%1.2f", CalculatingExpression(s));
 


}

//红黑树 ---------------------------------------------------------------------- 
const int RED = 0;
const int BLACK = 1;

//---编译条件严格，自己引用自己 需要额外定义一个数据类型 使用typedef关键字
/*  https://tool.lu/coderunner/
struct rb_node_p;
typedef struct rb_node_p rb_node;

struct rb_node_p{
    rb_node* lchild, *rchild, *parent;
    int key, colour;
};
*/

/*  http://www.runoob.com/try/runcode.php?filename=helloworld&type=c
struct rb_node{
    rb_node* lchild, *rchild, *parent;
    int key, colour;
};

*/
//------------------------

struct rb_node{
    rb_node* lchild, *rchild, *parent;
    int key, colour;
};

rb_node* root;

rb_node* get_node( rb_node* parent, int key);
void rb_insert(int key);
rb_node* rb_search(int key);
void rb_delete(int key);
rb_node* clock_wise( rb_node* node);
rb_node* counter_clock_wise( rb_node* node);
void show_rb_tree( rb_node* node);

rb_node* get_node( rb_node* parent, int key){
    rb_node *tmp = (rb_node*)malloc(sizeof(rb_node));
    tmp->key = key;
    tmp->colour = RED;
    tmp->parent = parent;
    tmp->lchild = tmp->rchild = NULL;
    return tmp;
}

rb_node* clock_wise(rb_node* node){
    if(node == NULL || node->lchild == NULL)
        return NULL;

    rb_node *rb_1=node, *rb_2=node->lchild, *rb_3=node->lchild->rchild;
    if(rb_1->parent != NULL){
        if(rb_1->parent->lchild == rb_1)
            rb_1->parent->lchild = rb_2;
        else
            rb_1->parent->rchild = rb_2;
    }else if(rb_1 == root){
        root = rb_2;
    }
    rb_2->parent = rb_1->parent;

    rb_1->parent = rb_2;
    rb_2->rchild = rb_1;

    rb_1->lchild = rb_3;
    if(rb_3 != NULL)rb_3->parent = rb_1;

    return rb_2;    
}

rb_node* counter_clock_wise(rb_node* node){
    if(node == NULL || node->rchild == NULL)
        return NULL;

    rb_node *rb_1=node, *rb_2=node->rchild, *rb_3=node->rchild->lchild;
    if(rb_1->parent != NULL){
        if(rb_1->parent->lchild == rb_1)
            rb_1->parent->lchild = rb_2;
        else 
            rb_1->parent->rchild = rb_2;
    }
    else if(rb_1 == root){
        root = rb_2;
    }
    rb_2->parent = rb_1->parent;

    rb_1->parent = rb_2;
    rb_2->lchild = rb_1;

    rb_1->rchild = rb_3;
    if(rb_3 != NULL)rb_3->parent = rb_1;

    return rb_2;
}

rb_node* rb_search(int key){
    rb_node *p = root;
    while(p != NULL){
        if(key < p->key)
            p = p->lchild;
        else if(key > p->key)
            p = p->rchild;
        else
            break;
    }
    return p;
}

void rb_insert(int key){
    rb_node *p=root, *q=NULL;

    if(root == NULL){
        root = get_node(NULL, key);
        root->colour = BLACK;
        return;
    }

    while(p != NULL){
        q = p;
        if(key < p->key)
            p = p->lchild;
        else if(key > p->key)
            p = p->rchild;
        else return;
    }

    if(key < q->key)
        q->lchild = get_node(q, key);
    else
        q->rchild = get_node(q, key);

    while(q != NULL && q->colour == RED){
        p = q->parent;//p won't null, or BUG.

        if(p->lchild == q){
            if(q->rchild != NULL && q->rchild->colour == RED)
                counter_clock_wise(q);        
            q = clock_wise(p);
            q->lchild->colour = BLACK;
        }
        else{
            if(q->lchild != NULL && q->lchild->colour == RED)
                clock_wise(q);
            q = counter_clock_wise(p);
            q->rchild->colour = BLACK;
        }

        q = q->parent;
    }
    root->colour = BLACK;
}

void show_rb_tree(rb_node* node){
    if(node == NULL)
        return;
    if(node->colour == 0){
        if(node->lchild != NULL && node->rchild != NULL){
            if(node->lchild->colour == 0 && node->rchild->colour == 0){
                printf("(|红结点:%d|——|红左结点:%d|——|红右结点:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }
            if(node->lchild->colour == 0 && node->rchild->colour == 1){
                printf("(|红结点:%d|——|红左结点:%d|——|黑右结点:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }

            if(node->lchild->colour == 1 && node->rchild->colour == 0){
                printf("(|红结点:%d|——|黑左结点:%d|——|红右结点:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }

            if(node->lchild->colour == 1 && node->rchild->colour == 1){
                printf("(|红结点:%d|——|黑左结点:%d|——|黑右结点:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }
        } else if(node->lchild != NULL && node->rchild == NULL ){

            if(node->lchild->colour == 0 ){
                printf("(|红结点:%d|——|红左结点:%d|——|右空|)\n", node->key,node->lchild->key);
            }


            if(node->lchild->colour == 1 && node->rchild->colour == 0){
                printf("(|红结点:%d|——|黑左结点:%d|——|右空|)\n", node->key,node->lchild->key);
            }

        } else if(node->lchild == NULL && node->rchild != NULL ){

            if(node->rchild->colour == 0 ){
                printf("(|红结点:%d|——|左空|——|红右结点:%d|)\n", node->key,node->rchild->key);
            }


            if(node->rchild->colour == 1 ){
                printf("(|红结点:%d|——|左空|——|红右结点:%d|)\n", node->key,node->rchild->key);
            }

        } else {
            printf("(|红结点:%d|——|左空|——|右空|)\n", node->key);
        }
    }
    if(node->colour == 1){
        if(node->lchild != NULL && node->rchild != NULL){
            if(node->lchild->colour == 0 && node->rchild->colour == 0){
                printf("(|黑结点:%d|——|红左结点:%d|——|红右结点:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }
            if(node->lchild->colour == 0 && node->rchild->colour == 1){
                printf("(|黑结点:%d|——|红左结点:%d|——|黑右结点:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }

            if(node->lchild->colour == 1 && node->rchild->colour == 0){
                printf("(|黑结点:%d|——|黑左结点:%d|——|红右结点:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }

            if(node->lchild->colour == 1 && node->rchild->colour == 1){
                printf("(|黑结点:%d|——|黑左结点:%d|——|黑右结点:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }
        } else if(node->lchild != NULL && node->rchild == NULL ){

            if(node->lchild->colour == 0 ){
                printf("(|黑结点:%d|——|红左结点:%d|——|右空|)\n", node->key,node->lchild->key);
            }


            if(node->lchild->colour == 1 && node->rchild->colour == 0){
                printf("(|黑结点:%d|——|黑左结点:%d|——|右空|)\n", node->key,node->lchild->key);
            }

        } else if(node->lchild == NULL && node->rchild != NULL ){

            if(node->rchild->colour == 0 ){
                printf("(|黑结点:%d|——|左空|——|红右结点:%d|)\n", node->key,node->rchild->key);
            }


            if(node->rchild->colour == 1 ){
                printf("(|黑结点:%d|——|左空|——|红右结点:%d|)\n", node->key,node->rchild->key);
            }

        } else {
            printf("(|黑结点:%d|——|左空|——|右空|)\n", node->key);
        }
    }
    //---------------------
    if(node->lchild != NULL){
        //printf("遍历结点%d左子树\n",node->key);
        show_rb_tree(node->lchild);
    }
    if(node->rchild != NULL){
        //printf("遍历结点%d右子树\n",node->key);
        show_rb_tree(node->rchild);
    }



    //printf("[0]\n");
}

void rb_delete(int key){
    rb_node *v = rb_search(key), *u, *p, *c, *b;
    int tmp;
    if(v == NULL) return;

    u = v;
    if(v->lchild != NULL && v->rchild != NULL){
        u = v->rchild;
        while(u->lchild != NULL){
            u = u->lchild;
        }
        tmp = u->key;
        u->key = v->key;
        v->key = tmp;
    }

    //u is the node to free.
    if(u->lchild != NULL)
        c = u->lchild;
    else 
        c = u->rchild;

    p = u->parent;
    if(p != NULL){
        //remove u from rb_tree.
        if(p->lchild == u)
            p->lchild = c;
        else
            p->rchild = c;
    }
    else{
        //u is root.
        root = c;
        free((void*)u);
        return;
    }

    //u is not root and u is RED, this will not unbalance.
    if(u->colour == RED){
        free((void*)u);
        return;
    }

    free((void*)u);
    u = c;

    //u is the first node to balance.
    while(u != root){
        if(u != NULL && u->colour == RED){
            //if u is RED, change it to BLACK can finsh.
            u->colour = BLACK;
            return;
        }

        if(u == p->lchild)
            b = p->rchild;
        else 
            b = p->lchild;

        printf("%d\n", b->key);

        //b is borther of u. b can't be null, or the rb_tree is must not balance.
        if(b->colour == BLACK){
            //If b's son is RED, rotate the node.
            if(b->lchild != NULL && b->lchild->colour == RED){
                if(u == p->lchild){
                    b = clock_wise(b);
                    b->colour = BLACK;
                    b->rchild->colour = RED;

                    p = counter_clock_wise(p);
                    p->colour = p->lchild->colour;
                    p->lchild->colour = BLACK;
                    p->rchild->colour = BLACK;
                }
                else{
                    p = clock_wise(p);
                    p->colour = p->rchild->colour;
                    p->rchild->colour = BLACK;
                    p->lchild->colour = BLACK;
                }

                return;
            }
            else if(b->rchild != NULL && b->rchild->colour == RED){
                if(u == p->rchild){
                    b = counter_clock_wise(b);
                    b->colour = BLACK;
                    b->lchild->colour = RED;

                    p = clock_wise(p);
                    p->colour = p->rchild->colour;
                    p->rchild->colour = BLACK;
                    p->lchild->colour = BLACK;
                }
                else{
                    p = counter_clock_wise(p);
                    p->colour = p->lchild->colour;
                    p->lchild->colour = BLACK;
                    p->rchild->colour = BLACK;
                }        
                return;
            }
            else{//if b's sons are BLACK, make b RED and move up u.
                b->colour = RED;
                u = p;
                p = u->parent;
                continue;
            }
        }
        else{
            if(u == p->lchild){
                p = counter_clock_wise(p);
                p->colour = BLACK;
                p->lchild->colour = RED;
                p = p->lchild;
            }
            else{
                p = clock_wise(p);
                p->colour = BLACK;
                p->rchild->colour = RED;
                p = p->rchild;
            }
        }
    }
    root->colour = BLACK;
}


//树的节点插入、删除、搜索 

void rbtree(){
    int i;
    root = NULL;
    int N = 10 ; // 循环次数
    for(i = 1; i <= N; i++){    
        rb_insert(i);
    }
    rb_delete(9);
    rb_delete(3);
    rb_delete(7);
    printf("根节点%d\n",root->key);
    show_rb_tree(root);
    printf("\n");

    printf("删除根节点节点%d后:\n",root->key);
    int  rootValue = root->key ;
    rb_delete(root->key);
    printf("当前根节点%d\n",root->key);
    show_rb_tree(root);
    printf("\n");

    printf("插入原根节点后 %d:\n",rootValue);
    rb_insert(rootValue);
    printf("当前根节点%d\n",root->key);
    show_rb_tree(root);
    printf("\n");

    for(i = 1; i <= N; i++){
        rb_node* node = rb_search(i);
        if( node != NULL ){
            if(node->colour == 0){
                printf("node%d的颜色是 红\n",i);
            }else{
                printf("node%d的颜色是 黑\n",i);
            }

        } else{
            printf("node%d不存在\n",i);
        }
    }

  printf("/n");
}
//堆排序 
#define MAX_SIZE 20
typedef int ElemType; 

// 定义排序表
typedef struct HeapList
{
	ElemType *keys;
	int length;
}HeapList;

// 初始化排序表
void InitHeapList(HeapList &L)
{
	L.keys = (ElemType*)malloc(MAX_SIZE * sizeof(ElemType));
	L.length = 6;
	int data[] = {38, 11, 9, 27, 96, 83};
	for(int i = 0; i < 6; ++i)
		L.keys[i + 1] = data[i];
}

// 打印排序表
void PrintHeapList(HeapList &L)
{
	for(int i = 1; i <= L.length; ++i)
		printf("%5d", L.keys[i]);
	printf("\n");
}

//初始化大堆
void CreateBigHeap(HeapList &L)
{
	int middle = L.length/2;
	for(int i = middle; i > 0; i--)
	{
		if(((2*i + 1) > L.length) && (2*i <= L.length)) 
		{
			// 当没有右字树的时候只判断根节点和左字树的大小进行调换
			if(L.keys[i] < L.keys[2*i])
			{
				L.keys[0] = L.keys[i];
				L.keys[i] = L.keys[2*i];
				L.keys[2*i] = L.keys[0];
			}
		}
		if((2*i + 1) <= L.length)
		{
			// 左右子树都有
			// 先比较左右字树哪个最大
			int max = 2 * i;
			if(L.keys[2*i] < L.keys[2*i + 1])max++;
			if(L.keys[i] < L.keys[max])
			{
				L.keys[0] = L.keys[i];
				L.keys[i] = L.keys[max];
				L.keys[max] = L.keys[0];
			}
		}
	}
}

// 初始化大堆之后，每一次的对前N-1个进行再次大堆
void heapfy(HeapList &L, int end)
{
	//此时出去root节点，其余的还是都符合大堆的，可以从头结点和他的子节点对比较，一直比到没有没有孩子结点或者满足大堆的时候停止
	for(int i = 1; 2*i <= end; i *=2)
	{
		if(2*i + 1 <= end)
		{
			// 还是三者对比，然后把i更新到替换到得为之
			int max = 2*i;
			if(L.keys[2*i] < L.keys[2*i + 1])max++;
			// 右字树最大，那么把该字树根节点和他对换吧
			L.keys[0] = L.keys[i];
			L.keys[i] = L.keys[max];
			L.keys[max] = L.keys[0];
			// 切记，更新i的位置
			i = max;
			// 接下来跳出if，进入for的下一个循环，该此时继续把i的自树进行如上操作
		}
		if(2*i + 1 > end && 2*i <= end)
		{
			// 只有左子树
			if(L.keys[i] < L.keys[2*i])
			{
				L.keys[0] = L.keys[i];
				L.keys[i] = L.keys[2*i];
				L.keys[2*i] = L.keys[0];
			}
		}
	}
}

//  堆排序

#include<stdio.h>
#include<stdlib.h>
 
/*
arr[start+1...end]满足最大堆的定义，
将arr[start]加入到最大堆arr[start+1...end]中，
调整arr[start]的位置，使arr[start...end]也成为最大堆
注：由于数组从0开始计算序号，也就是二叉堆的根节点序号为0，
因此序号为i的左右子节点的序号分别为2i+1和2i+2
*/
void HeapAdjustDown(int *arr,int start,int end)
{
	int temp = arr[start];	//保存当前节点
	int i = 2*start+1;		//该节点的左孩子在数组中的位置序号
	while(i<=end)
	{
		//找出左右孩子中最大的那个
		if(i+1<=end && arr[i+1]>arr[i])  
			i++;
		//如果符合堆的定义，则不用调整位置
		if(arr[i]<=temp)	
			break;
		//最大的子节点向上移动，替换掉其父节点
		arr[start] = arr[i];
		start = i;
		i = 2*start+1;
	}
	arr[start] = temp;
}
 
/*
堆排序后的顺序为从小到大
因此需要建立最大堆
*/
void Heap_Sort(int *arr,int len)
{
	int i;
	//把数组建成为最大堆
	//第一个非叶子节点的位置序号为len/2-1
	for(i=len/2-1;i>=0;i--)
		HeapAdjustDown(arr,i,len-1);
	//进行堆排序
	for(i=len-1;i>0;i--)
	{
		//堆顶元素和最后一个元素交换位置，
		//这样最后的一个位置保存的是最大的数，
		//每次循环依次将次大的数值在放进其前面一个位置，
		//这样得到的顺序就是从小到大
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		//将arr[0...i-1]重新调整为最大堆
		HeapAdjustDown(arr,0,i-1);
	}
}
 
int heap(void)
{
	int num;
	printf("请输入排序的元素的个数：");
	scanf("%d",&num);
 
	int i;
	int *arr = (int *)malloc(num*sizeof(int));
	printf("请依次输入这%d个元素（必须为整数）：",num);
	for(i=0;i<num;i++)
		scanf("%d",arr+i);
 
	printf("堆排序后的顺序：");
	Heap_Sort(arr,num);
	for(i=0;i<num;i++)
		printf("%d ",arr[i]);
	printf("\n");
 
	free(arr);
	arr = 0;
}


//队列-------------------------------------------------------------------- 

typedef struct queue
{
	int data;
	struct queue *link;
}QUEUE;
void EnQueue(QUEUE **head,QUEUE**tail,int x)
{
 
 
 
	//从队尾tail进队
         QUEUE *p;
	p=(QUEUE*)malloc(sizeof(QUEUE));
	p->data=x;
	p->link=NULL;
 
	if(*head==NULL)
		*head=*tail=p;//*head=p;若不加tail插入第二个元素时会报错
	else{
		(*tail)->link=p;
		*tail=p;
	}
}
int DeQueue(QUEUE **head,QUEUE**tail,int*cp)
{
	//从队头head出队
         QUEUE *p;
	p=*head;
	if(*head==NULL)
		return 1;
	*cp=(*head)->data;
	//*head=p->link;和*head=(*head)->link都是可以的
	*head=(*head)->link;
	if(*head==NULL)
		*tail=NULL;
	free(p);
	return 0;
 
}
void OutputQueue(QUEUE *head)
{
	while(head!=NULL)
	{
		printf("%d ",head->data);//控制显示时有空白位置 要留空
		head=head->link;
	}
	printf("\n");
}
 
 
 
 
void quene()
{
	QUEUE *head,*tail;
	int op,i;
	head=tail=NULL;//空队列
	while(1)
	{
		printf("请选择操作。1：进队  2：出队  0：退出");
		fflush(stdin);
		scanf("%d",&op);
		switch(op)
		{
		case 0:return;
		case 1:
			printf("请输入进队元素：");
			scanf("%d",&i);
			EnQueue(&head,&tail,i);
			printf("队内元素为： \n");
			OutputQueue(head);
			break;
		case 2:if(DeQueue(&head,&tail,&i)==0)
			   {
				   printf("出队元素为：[%d],队内元素为： \n",i);
				   OutputQueue(head);
			   }
			   else
				   printf("队空 \n");
			break;
 
		}
	}
}


//链表---------------------------------------------

typedef struct List
{
	int  data;
	struct List *next;
}list,*p_list;
 
void creat_list(list **p)//如果链表为空，则创建一个链表，指针域指向自己，否则寻找尾节点，将
{						 //将尾节点的指针域指向这个新节点，新节点的指针域指向头结点
	int item;
	list *temp;
	list *target;
	printf("输入节点的值，输入0结束\n");
	while(1)
	{
		scanf("%d",&item);
		if(item==0)return;
 
		if(*p==NULL)   //如果输入的链表是空。则创建一个新的节点，使其next指针指向自己  (*head)->next=*head;
		{
			*p=(list *)malloc(sizeof(list));
			if(!*p)exit(0);
			(*p)->data=item;
			(*p)->next=*p;
		}
		else		//输入的链表不是空的，寻找链表的尾节点，使尾节点的next=新节点。新节点的next指向头节点
		{
			for(target=*p;target->next!=*p;target=target->next);//寻找尾节点
 
			temp=(list *)malloc(sizeof(list));
			if(!temp)exit(0);
			temp->data=item;
			temp->next=*p;  //新节点指向头节点
			target->next=temp;//尾节点指向新节点
		}
	}
}
void insert(list **pNode,int place,int num)  //链表的插入  
{
	list *temp,*target;
	int i;
	if(place==1)				//如果输入的数字是1，表示要插入头节点。应该特殊处理
	{						//首先找到尾节点，让后让新节点的next指向头节点，尾节点指向新的头节点，在让头指针指向temp。这要特别注意
		temp=(list *)malloc(sizeof(list));
		if(!temp)exit(0);
		temp->data=num;
		for(target=*pNode;target->next!=*pNode;target=target->next);
		
		temp->next=*pNode;
		target->next=temp;
		*pNode=temp;/////////特别注意
	}
	
	else			//在其他的地方插入节点。  同样先找到要插入的位置，如果位置超出链表的长度，自动插入队尾。						tar  new  原来是2
	{				//找到要插入位置的前一个节点target，让target->next=temp，插入节点的前驱指向新节点，新节点指向target->next的地址  1    2   3  
		for(i=1,target=*pNode;target->next!=*pNode&&i!=place-1;target=target->next,i++);
		temp=(list *)malloc(sizeof(list));
		temp->data=num;
		
		temp->next=target->next;
		target->next=temp;
	}
 
}
 
void Delete(list **pNode,int place)  //删除操作
{
	list *temp,*target;
	int i;
	temp=*pNode;
	if(temp==NULL)				//首先判断链表是否为空
	{
		printf("这是一个空指针 无法删除\n");
		return;
	}
	if(place==1)		//如果删除的是头节点	
	{				//应当特殊处理，找到尾节点，使尾节点的next指向头节点的下一个节点 rear->next=(*head)->next;然后让新节点作为头节点，释放原来的头节点
		for(target=*pNode;target->next!=*pNode;target=target->next);
		temp=*pNode;
		
		*pNode=(*pNode)->next;
		target->next=*pNode;
		free(temp);
	}
	else
	{		//删除其他节点
		for(i=1,target=*pNode;target->next!=*pNode&&i!=place-1;target=target->next,i++); //首先找出尾节点
		if(target->next==*pNode)		//判断要删除的位置是否大于链表长度，若大于链表长度，特殊处理直接删除尾节点
		{
			for(target=*pNode;target->next->next!=*pNode;target=target->next);//找出尾节的前一个节点
			temp=target->next;												 //	尾节点的前一个节点直接指向头节点  释放原来的尾节点									
			target->next=*pNode;
			printf("数字太大删除尾巴\n");
			free(temp);
		}
		else
		{
			temp=target->next;//  删除普通节点  找到要删除节点的前一个节点target，使target指向要删除节点的下一个节点  转存删除节点地址
			target->next=temp->next;	//  然后释放这个节点
			free(temp);
		}
	}
}
 
int findval(list *pNode,int val) //寻找值
{
	int i=1;
	list *node;
	node=pNode;
	while(node->data!=val&&node->next!=pNode)
	{
		i++;
		node=node->next;
	}
	if(node->next==pNode&&node->data!=val)//尾节点指向头节点就跳出，因此还要检测一次为节点的data
	{
		return -1;
	}
	return i;
}
 
 
 
void show(list *p)//遍历，循环链表的遍历最好用do while语句 ，因为头节点就有值
{
	list *temp;
	temp=p;
	do
	{
		printf("%5d",temp->data);
		temp=temp->next;	
	}
	while(temp!=p);
 
	printf("\n");
}
int linklist()
{
	list *head=NULL;
	list *val=NULL;
	int place,num;
	creat_list(&head);
	printf("原始的链表：");
	show(head);
 
	printf("输入要删除的位置：");
	scanf("%d",&place);
	Delete(&head,place);
	show(head);
 
	printf("输入要插入的位置和数据用空格隔开：");
	scanf("%d %d",&place,&num);
	insert(&head,place,num);
	show(head);
 
	printf("输入你想查找的值:");
	scanf("%d",&num);
	place=findval(head,num);
	if(place!=-1)printf("找到的值的位置是place=%d\n",place);
	else printf("没找到值 \n");
    printf("\n");
}
//图 -------------------------------------------------------------------- 


#include<iostream>
#include<iomanip>
using namespace std;
//最大权值
#define MAXWEIGHT 100
//用邻接矩阵实现图
class Graph
{
private:
	//是否带权
	bool isWeighted;
	//是否有向
	bool isDirected;
	//顶点数
	int numV;
	//边数
	int numE;
	//邻接矩阵
	int **matrix;
public:
	/*
	构造方法
	numV是顶点数，isWeighted是否带权值，isDirected是否有方向
	*/
	Graph(int numV, bool isWeighted = false, bool isDirected = false);
	//建图
	void createGraph();
	//析构方法
	~Graph();
	//获取顶点数
	int getVerNums()
	{return numV;}
	//获取边数
	int getEdgeNums()
	{return numE;}
	//设置指定边的权值
	void setEdgeWeight(int tail, int head, int weight);
	//打印邻接矩阵
	void printAdjacentMatrix();
	//检查输入
	bool check(int i, int j, int w = 1);
};
Graph::Graph(int numV, bool isWeighted, bool isDirected)
{
	while (numV <= 0)
	{
		cout << "输入的顶点数不正确！，重新输入 ";
		cin >> numV;
	}
	this->numV = numV;
	this->isWeighted = isWeighted;
	this->isDirected = isDirected;
	matrix = new int*[numV];  //指针数组
	int i, j;
	for (i = 0; i < numV; i++)
		matrix[i] = new int[numV];
	//对图进行初始化
	if (!isWeighted)  //无权图
	{
		//所有权值初始化为0
		for (i = 0; i < numV; i++)
		for (j = 0; j < numV; j++)
			matrix[i][j] = 0;
	}
	else  //有权图
	{
		//所有权值初始化为最大权值
		for (i = 0; i < numV; i++)
		for (j = 0; j < numV; j++)
			matrix[i][j] = MAXWEIGHT;
	}
}
//建图
void Graph::createGraph()
{
	cout << "输入边数 ";
	while (cin >> numE && numE < 0)
		cout << "输入有误！，重新输入 ";
 
	int i, j, w;
	if (!isWeighted)  //无权图
	{
		if (!isDirected)  //无向图
		{
			cout << "输入每条边的起点和终点：\n";
			for (int k = 0; k < numE; k++)
			{
				cin >> i >> j;
				while (!check(i, j))
				{
					cout << "输入的边不对！重新输入\n";
					cin >> i >> j;
				}
				matrix[i][j] = matrix[j][i] = 1;
			}
		}
		else  //有向图
		{
			cout << "输入每条边的起点和终点：\n";
			for (int k = 0; k < numE; k++)
			{
				cin >> i >> j;
				while (!check(i, j))
				{
					cout << "输入的边不对！重新输入\n";
					cin >> i >> j;
				}
				matrix[i][j] = 1;
			}
		}
	}
	else  //有权图
	{
		if (!isDirected)   //无向图
		{
			cout << "输入每条边的起点、终点和权值：\n";
			for (int k = 0; k < numE; k++)
			{
				cin >> i >> j >> w;
				while (!check(i, j, w))
				{
					cout << "输入的边不对！重新输入\n";
					cin >> i >> j >> w;
				}
				matrix[i][j] = matrix[j][i] = w;
			}
		}
		else  //有向图
		{
			cout << "输入每条边的起点、终点和权值：\n";
			for (int k = 0; k < numE; k++)
			{
				cin >> i >> j >> w;
				while (!check(i, j, w))
				{
					cout << "输入的边不对！重新输入\n";
					cin >> i >> j >> w;
				}
				matrix[i][j] = w;
			}
		}
	}
}
//析构方法
Graph::~Graph()
{
	int i = 0;
	for (i = 0; i < numV; i++)
		delete[] matrix[i];
	delete[]matrix;
}
//设置指定边的权值
void Graph::setEdgeWeight(int tail, int head, int weight)
{
	if (isWeighted)
	{
		while (!check(tail, head, weight))
		{
			cout << "输入不正确，重新输入边的起点、终点和权值 ";
			cin >> tail >> head >> weight;
		}
		if (isDirected)
			matrix[tail][head] = weight;
		else
			matrix[tail][head] = matrix[head][tail] = weight;
	}
	else
	{
		while (!check(tail, head, 1))
		{
			cout << "输入不正确，重新输入边的起点、终点 ";
			cin >> tail >> head;
		}
		if (isDirected)
			matrix[tail][head] = 1-matrix[tail][head];
		else
			matrix[tail][head] = matrix[head][tail] = 1 - matrix[tail][head];
	}
}
//输入检查
bool Graph::check(int i, int j, int w)
{
	if (i >= 0 && i < numV && j >= 0 && j < numV && w > 0 && w <= MAXWEIGHT)
		return true;
	else
		return false;
}
//打印邻接矩阵
void Graph::printAdjacentMatrix()
{
	int i, j;
	cout.setf(ios::left);
	cout << setw(4) << " ";
	for (i = 0; i < numV; i++)
		cout << setw(4) << i;
	cout << endl;
	for (i = 0; i < numV; i++)
	{
		cout << setw(4) << i;
		for (j = 0; j < numV; j++)
			cout << setw(4) << matrix[i][j];
		cout << endl;
	}
}
int graph()
{
	cout << "******使用邻接矩阵实现图结构*******" << endl;
	bool isDirected, isWeighted;
	int numV;
	cout << "建图" << endl;
	cout << "输入顶点数 ";
	cin >> numV;
	cout << "边是否带权值，0(不带) or 1(带) ";
	cin >> isWeighted;
	cout << "是否是有向图，0(无向) or 1(有向) ";
	cin >> isDirected;
	Graph graph(numV, isWeighted, isDirected);
	cout << "这是一个";
	isDirected ? cout << "有向、" : cout << "无向、";
	isWeighted ? cout << "有权图" << endl : cout << "无权图" << endl;
	graph.createGraph();
	cout << "打印邻接矩阵" << endl;
	graph.printAdjacentMatrix();
	cout << endl;
	int tail, head, weight;
	cout << "修改指定边的权值" << endl;
	if (isWeighted)  //针对有权图
	{
		cout << "输入边的起点、终点和权值 ";
		cin >> tail >> head >> weight;
		graph.setEdgeWeight(tail, head, weight);
	}
	else  //针对无权图
	{
		cout << "输入边的起点、终点 ";
		cin >> tail >> head;
		graph.setEdgeWeight(tail, head, 1);
	}
	cout << "修改成功！" << endl;
	cout << "打印邻接矩阵" << endl;
	graph.printAdjacentMatrix();
	system("pause");
}





//main函数--------------------------------- 
int main()
{ 
 int x;
 while (1)
 {
  printf("-------------操作选项-----------\n");
  	printf("1红黑树\t\t2、堆\n");
	printf("3、栈\t\t4、搜索树\n");
	printf("5、队列\t\t6、链表\n");		
    printf("7、图 \n");
    printf("8:退出程序 \n");
  printf("--------------------------------\n");
  printf("请按数字键选择要执行的操作: ");
  scanf("%d",&x);
  printf("\n");
 
  //输入8跳出循环，退出程序
  if(x==8)
      break;
   
  switch(x)
  {
  case 1:rbtree();
    break; //输入1，跳出switch语句，进入下一次循环
  case 2:heap();
    break; 
  case 3:stack1();
    break;
  case 4:searchtree();
    break;
  case 5:quene();
    break;
  case 6:linklist(); 
    break;
  case 7:graph();
    break;
  case 8:
    break;
  default:  //数字输入错误，跳出siwtch语句，进入下一次循环
      printf("输入的数字不正确\n");
      break;
  }
 }
 return 0;
}
