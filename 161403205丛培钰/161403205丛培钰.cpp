#include<stdio.h> 
#include <stdlib.h>
#include <malloc.h>             // �����ڴ�
#include <ctype.h>              // �ں�isdigit()����
#include <assert.h>             // ���Ժ���
#include <string.h>             // �ں��ַ���������

//����������--------------------------------------------------- 
struct tnode
{
	int data;
	struct tnode *lchild;
	struct tnode *rchild;
};
struct tnode * tree_insert(struct tnode *root,int data)//��������������Ľڵ� 
{
	struct tnode *s;
	//����Ҫ����Ľڵ�
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
				//tree_insert(root->rchild,s->data); ����д�Ǵ���ģ���Ϊ���ܽ����ڵ���ӽڵ�������һ�顣 ��ϸ��һ�µݹ���̡� 
				root->rchild=tree_insert(root->rchild,s->data);
			else
				//tree_insert(root->lchild,s->data); ����д�Ǵ���ģ���Ϊ���ܽ����ڵ���ӽڵ�������һ�顣
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
		return 0; //return -1�������if�����Ϊ-1����FALSE����0��FALSE�� 
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
	//�ҵ�Ҫɾ���Ľڵ� 
	t=root;
	int flag=0; 
	if(t->data==data)
	{
		p=root;
		flag=1;
	}
	//���ֵ�һ�����󣬾��������whileѭ�����棬ȫ����if��������if-else�������ǲ��Եģ���Ϊ����ı�����һ��ѭ��ִֻ�����������һ�֡� 
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
	//�ҵ�Ҫɾ���Ľڵ�
	
	//�������ֲ�ͬ���ɾ���ڵ�
	if(flag==0)
	{
		printf("this node not in the tree!");
	} 
	//���ֵ�һ�������������ȫ��if��������if-else�������ǲ��Եģ���Ϊ����ı�����һ��ѭ��ִֻ�����������һ�֡� 
	if(p->lchild==NULL&&p->rchild==NULL)
	{
		if(p==root)
		{
			root=NULL;
		}
		else
		{
			//��������д<span style="font-family: Arial, Helvetica, sans-serif;">p=NULL;</span>
			if(pf->lchild==p)
				pf->lchild=NULL;
			else
				pf->rchild=NULL;//���������д���Ĳ�ͬ�� 
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
//�������������� 
	root=NULL;//need or not?����Ҫ��NULLֵ����Ϊ���ڵ�Ϊ��ʱ�ͰѸĽڵ㵱�ɸ��ڵ㡣 
	//while(scanf("%d",&data)!=EOF)
	for(i=0;i<12;++i)
	{
		data=tree[i];
		root=tree_insert(root,data);
	}
	//��������������
	tree_scaner(root);//�������������� 
	//�ڶ����������ֲ���ĳ���ڵ�
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
//ջ�����������ʽ------------------------------------------------- 

#define STACK_INIT_SIZE 100     // ջ����
#define STACK_INCREMENT 10      // ջ����

 
typedef float DATATYPE;
typedef char SYMBOLTYPE;
 
typedef struct stack
{
    int *base;         // ����ַ
    int *top;          // ջ��ָ��
    int stackSize;          // ջ����
}*Stack;
 
// ջ�ĳ�ʼ��
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
 
// ��ջ��
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
 
// ��ջ��
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
 
// ������ѹջ
void Push(Stack S, DATATYPE e)
{
    assert(S);
    if (IsFull(S))
    {
        S->base = (int*)malloc((STACK_INIT_SIZE+STACK_INCREMENT)*sizeof(DATATYPE));
        if (!S->base)
            exit(0);        // �洢����ʧ��
        S->top = S->base + S->stackSize;
        S->stackSize += STACK_INCREMENT;
    }
    *S->top++ = e;
}
 
// �����ѹջ
void PushSymbol(Stack S, SYMBOLTYPE e)
{
    assert(S);
    if (IsFull(S))
    {
        S->base = (int*)malloc((STACK_INIT_SIZE+STACK_INCREMENT)*sizeof(DATATYPE));
        if (!S->base)
            exit(0);        // �洢����ʧ��
        S->top = S->base + S->stackSize;
        S->stackSize += STACK_INCREMENT;
    }
    *S->top++ = e;
}
 
// ��������ջ
DATATYPE Pop(Stack S)
{
    assert(S);
    if (S->top == S->base)
        return 0;              // ��ջ����0��֤���ָ�������ȷ����
    else
    {
        return *--S->top;     // *--S->top����*(--S->top)
    }
}
 
// �������ջ
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
 
// ջ������
void DestroyStack(Stack S) {
      free(S->base);
      free(S);
}
 
// ��������ȼ���
char Priority[7][7] =
{           // '+' '-' '*' '/' '(' ')' '#'          ��row����ߵģ���ջ�����������col���ϱߵģ�����ջ�����
   {/*'+'*/'>','>','<','<','<','>','>'},
    {/*'-'*/'>','>','<','<','<','>','>'},
    {/*'*'*/'>','>','>','>','<','>','>'},
    {/*'/'*/'>','>','>','>','<','>','>'},
    {/*'('*/'<','<','<','<','<','=','0'},
    {/*')'*/'>','>','>','>','0','>','>'},
   {/*'#'*/'<','<','<','<','<','0','='}
};
 
// ȷ����������ڵ�����������
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
 
// ���㵯���������������뵯��ջ���������ֵ
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
 
// ���ʽ��ֵ����
float CalculatingExpression(char *s)
{
    int i;
    strcat(s, "#");                 // Ϊ���ʽs����"#"
    Stack OPND=NULL;
    OPND = Init_Stack(OPND);        // ����������ջ
    Stack OPTR=NULL;
    OPTR = Init_Stack(OPTR);        // ���������ջ
    PushSymbol(OPTR, '#');          //"#"ѹջ��Ϊ�����ջ��ջ��Ԫ��
    for (i=0; i<strlen(s); ++i)
    {
        while(s[i]==' ')            // whileѭ�������ո�
            ++i;
        if (isdigit(s[i]))          // �ж��Ƿ�������
        {
            int j=i;
            ++i;
            while(isdigit(s[i]))        // ȷ���Ǽ�λ��
            {
                ++i;
            }
            if (!isdigit(s[i]))     // ��whileѭ�������ж��Ƿ������ֶ�ӵ�iֵ��ȥ
                --i;
            char str[10]="";
            for (; j<=i; ++j)           // ���ַ��������±�j��i�������ַ�ת��Ϊ�ַ���
            {
                char c[2] = {s[j]};
                strcat(str, c);
            }
            float operand = atof(str);  // ���ַ���ת��Ϊ������
            Push(OPND, operand);        // ������ѹ�������ջ
        }
        else {
            int row = Operator(*(OPTR->top-1)), col = Operator(s[i]);       // ȷ��ջ�����������������ջ�����������
            switch(Priority[row][col])              // ȷ�����ȼ�
            {
                case '<': PushSymbol(OPTR, s[i]); break;
                case '>': Push(OPND, Calculation(Pop(OPND), PopSymbol(OPTR), Pop(OPND))); --i; break;       
                             //Push()�������ұߵ�Pop��ִ�У�--i��Ϊ���´μ����Ե�ǰ��ջ�����s[i]�����ж�
                case '=': PopSymbol(OPTR); break;
                default:  printf("���������������֮���Ƿ��пո񣬱��ʽ�Ƿ���ȷ��\n");
                          DestroyStack(OPTR);
                          DestroyStack(OPND);
                          return 0;           // ���е���һ����˵�����ʽ����ֱ�ӷ��ص��ú�������������
            }
        }
    }
    DestroyStack(OPTR);
    return Pop(OPND);       // ���е���һ����˵�����ʽ��ȷ������������ջ��ֵ��Ϊ������
}
 
void stack1()
{
    char s[100];
    printf("������Ҫ����ı��ʽ��\n");
    scanf("%s",s);
    printf("���ʽ %s ��ֵΪ��\n", s);
    printf("%1.2f", CalculatingExpression(s));
 


}

//����� ---------------------------------------------------------------------- 
const int RED = 0;
const int BLACK = 1;

//---���������ϸ��Լ������Լ� ��Ҫ���ⶨ��һ���������� ʹ��typedef�ؼ���
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
                printf("(|����:%d|����|������:%d|����|���ҽ��:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }
            if(node->lchild->colour == 0 && node->rchild->colour == 1){
                printf("(|����:%d|����|������:%d|����|���ҽ��:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }

            if(node->lchild->colour == 1 && node->rchild->colour == 0){
                printf("(|����:%d|����|������:%d|����|���ҽ��:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }

            if(node->lchild->colour == 1 && node->rchild->colour == 1){
                printf("(|����:%d|����|������:%d|����|���ҽ��:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }
        } else if(node->lchild != NULL && node->rchild == NULL ){

            if(node->lchild->colour == 0 ){
                printf("(|����:%d|����|������:%d|����|�ҿ�|)\n", node->key,node->lchild->key);
            }


            if(node->lchild->colour == 1 && node->rchild->colour == 0){
                printf("(|����:%d|����|������:%d|����|�ҿ�|)\n", node->key,node->lchild->key);
            }

        } else if(node->lchild == NULL && node->rchild != NULL ){

            if(node->rchild->colour == 0 ){
                printf("(|����:%d|����|���|����|���ҽ��:%d|)\n", node->key,node->rchild->key);
            }


            if(node->rchild->colour == 1 ){
                printf("(|����:%d|����|���|����|���ҽ��:%d|)\n", node->key,node->rchild->key);
            }

        } else {
            printf("(|����:%d|����|���|����|�ҿ�|)\n", node->key);
        }
    }
    if(node->colour == 1){
        if(node->lchild != NULL && node->rchild != NULL){
            if(node->lchild->colour == 0 && node->rchild->colour == 0){
                printf("(|�ڽ��:%d|����|������:%d|����|���ҽ��:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }
            if(node->lchild->colour == 0 && node->rchild->colour == 1){
                printf("(|�ڽ��:%d|����|������:%d|����|���ҽ��:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }

            if(node->lchild->colour == 1 && node->rchild->colour == 0){
                printf("(|�ڽ��:%d|����|������:%d|����|���ҽ��:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }

            if(node->lchild->colour == 1 && node->rchild->colour == 1){
                printf("(|�ڽ��:%d|����|������:%d|����|���ҽ��:%d|)\n", node->key,node->lchild->key,node->rchild->key);
            }
        } else if(node->lchild != NULL && node->rchild == NULL ){

            if(node->lchild->colour == 0 ){
                printf("(|�ڽ��:%d|����|������:%d|����|�ҿ�|)\n", node->key,node->lchild->key);
            }


            if(node->lchild->colour == 1 && node->rchild->colour == 0){
                printf("(|�ڽ��:%d|����|������:%d|����|�ҿ�|)\n", node->key,node->lchild->key);
            }

        } else if(node->lchild == NULL && node->rchild != NULL ){

            if(node->rchild->colour == 0 ){
                printf("(|�ڽ��:%d|����|���|����|���ҽ��:%d|)\n", node->key,node->rchild->key);
            }


            if(node->rchild->colour == 1 ){
                printf("(|�ڽ��:%d|����|���|����|���ҽ��:%d|)\n", node->key,node->rchild->key);
            }

        } else {
            printf("(|�ڽ��:%d|����|���|����|�ҿ�|)\n", node->key);
        }
    }
    //---------------------
    if(node->lchild != NULL){
        //printf("�������%d������\n",node->key);
        show_rb_tree(node->lchild);
    }
    if(node->rchild != NULL){
        //printf("�������%d������\n",node->key);
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


//���Ľڵ���롢ɾ�������� 

void rbtree(){
    int i;
    root = NULL;
    int N = 10 ; // ѭ������
    for(i = 1; i <= N; i++){    
        rb_insert(i);
    }
    rb_delete(9);
    rb_delete(3);
    rb_delete(7);
    printf("���ڵ�%d\n",root->key);
    show_rb_tree(root);
    printf("\n");

    printf("ɾ�����ڵ�ڵ�%d��:\n",root->key);
    int  rootValue = root->key ;
    rb_delete(root->key);
    printf("��ǰ���ڵ�%d\n",root->key);
    show_rb_tree(root);
    printf("\n");

    printf("����ԭ���ڵ�� %d:\n",rootValue);
    rb_insert(rootValue);
    printf("��ǰ���ڵ�%d\n",root->key);
    show_rb_tree(root);
    printf("\n");

    for(i = 1; i <= N; i++){
        rb_node* node = rb_search(i);
        if( node != NULL ){
            if(node->colour == 0){
                printf("node%d����ɫ�� ��\n",i);
            }else{
                printf("node%d����ɫ�� ��\n",i);
            }

        } else{
            printf("node%d������\n",i);
        }
    }

  printf("/n");
}
//������ 
#define MAX_SIZE 20
typedef int ElemType; 

// ���������
typedef struct HeapList
{
	ElemType *keys;
	int length;
}HeapList;

// ��ʼ�������
void InitHeapList(HeapList &L)
{
	L.keys = (ElemType*)malloc(MAX_SIZE * sizeof(ElemType));
	L.length = 6;
	int data[] = {38, 11, 9, 27, 96, 83};
	for(int i = 0; i < 6; ++i)
		L.keys[i + 1] = data[i];
}

// ��ӡ�����
void PrintHeapList(HeapList &L)
{
	for(int i = 1; i <= L.length; ++i)
		printf("%5d", L.keys[i]);
	printf("\n");
}

//��ʼ�����
void CreateBigHeap(HeapList &L)
{
	int middle = L.length/2;
	for(int i = middle; i > 0; i--)
	{
		if(((2*i + 1) > L.length) && (2*i <= L.length)) 
		{
			// ��û����������ʱ��ֻ�жϸ��ڵ���������Ĵ�С���е���
			if(L.keys[i] < L.keys[2*i])
			{
				L.keys[0] = L.keys[i];
				L.keys[i] = L.keys[2*i];
				L.keys[2*i] = L.keys[0];
			}
		}
		if((2*i + 1) <= L.length)
		{
			// ������������
			// �ȱȽ����������ĸ����
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

// ��ʼ�����֮��ÿһ�εĶ�ǰN-1�������ٴδ��
void heapfy(HeapList &L, int end)
{
	//��ʱ��ȥroot�ڵ㣬����Ļ��Ƕ����ϴ�ѵģ����Դ�ͷ���������ӽڵ�ԱȽϣ�һֱ�ȵ�û��û�к��ӽ����������ѵ�ʱ��ֹͣ
	for(int i = 1; 2*i <= end; i *=2)
	{
		if(2*i + 1 <= end)
		{
			// �������߶Աȣ�Ȼ���i���µ��滻����Ϊ֮
			int max = 2*i;
			if(L.keys[2*i] < L.keys[2*i + 1])max++;
			// �����������ô�Ѹ��������ڵ�����Ի���
			L.keys[0] = L.keys[i];
			L.keys[i] = L.keys[max];
			L.keys[max] = L.keys[0];
			// �мǣ�����i��λ��
			i = max;
			// ����������if������for����һ��ѭ�����ô�ʱ������i�������������ϲ���
		}
		if(2*i + 1 > end && 2*i <= end)
		{
			// ֻ��������
			if(L.keys[i] < L.keys[2*i])
			{
				L.keys[0] = L.keys[i];
				L.keys[i] = L.keys[2*i];
				L.keys[2*i] = L.keys[0];
			}
		}
	}
}

//  ������

#include<stdio.h>
#include<stdlib.h>
 
/*
arr[start+1...end]�������ѵĶ��壬
��arr[start]���뵽����arr[start+1...end]�У�
����arr[start]��λ�ã�ʹarr[start...end]Ҳ��Ϊ����
ע�����������0��ʼ������ţ�Ҳ���Ƕ���ѵĸ��ڵ����Ϊ0��
������Ϊi�������ӽڵ����ŷֱ�Ϊ2i+1��2i+2
*/
void HeapAdjustDown(int *arr,int start,int end)
{
	int temp = arr[start];	//���浱ǰ�ڵ�
	int i = 2*start+1;		//�ýڵ�������������е�λ�����
	while(i<=end)
	{
		//�ҳ����Һ����������Ǹ�
		if(i+1<=end && arr[i+1]>arr[i])  
			i++;
		//������϶ѵĶ��壬���õ���λ��
		if(arr[i]<=temp)	
			break;
		//�����ӽڵ������ƶ����滻���丸�ڵ�
		arr[start] = arr[i];
		start = i;
		i = 2*start+1;
	}
	arr[start] = temp;
}
 
/*
��������˳��Ϊ��С����
�����Ҫ��������
*/
void Heap_Sort(int *arr,int len)
{
	int i;
	//�����齨��Ϊ����
	//��һ����Ҷ�ӽڵ��λ�����Ϊlen/2-1
	for(i=len/2-1;i>=0;i--)
		HeapAdjustDown(arr,i,len-1);
	//���ж�����
	for(i=len-1;i>0;i--)
	{
		//�Ѷ�Ԫ�غ����һ��Ԫ�ؽ���λ�ã�
		//��������һ��λ�ñ��������������
		//ÿ��ѭ�����ν��δ����ֵ�ڷŽ���ǰ��һ��λ�ã�
		//�����õ���˳����Ǵ�С����
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		//��arr[0...i-1]���µ���Ϊ����
		HeapAdjustDown(arr,0,i-1);
	}
}
 
int heap(void)
{
	int num;
	printf("�����������Ԫ�صĸ�����");
	scanf("%d",&num);
 
	int i;
	int *arr = (int *)malloc(num*sizeof(int));
	printf("������������%d��Ԫ�أ�����Ϊ��������",num);
	for(i=0;i<num;i++)
		scanf("%d",arr+i);
 
	printf("��������˳��");
	Heap_Sort(arr,num);
	for(i=0;i<num;i++)
		printf("%d ",arr[i]);
	printf("\n");
 
	free(arr);
	arr = 0;
}


//����-------------------------------------------------------------------- 

typedef struct queue
{
	int data;
	struct queue *link;
}QUEUE;
void EnQueue(QUEUE **head,QUEUE**tail,int x)
{
 
 
 
	//�Ӷ�βtail����
         QUEUE *p;
	p=(QUEUE*)malloc(sizeof(QUEUE));
	p->data=x;
	p->link=NULL;
 
	if(*head==NULL)
		*head=*tail=p;//*head=p;������tail����ڶ���Ԫ��ʱ�ᱨ��
	else{
		(*tail)->link=p;
		*tail=p;
	}
}
int DeQueue(QUEUE **head,QUEUE**tail,int*cp)
{
	//�Ӷ�ͷhead����
         QUEUE *p;
	p=*head;
	if(*head==NULL)
		return 1;
	*cp=(*head)->data;
	//*head=p->link;��*head=(*head)->link���ǿ��Ե�
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
		printf("%d ",head->data);//������ʾʱ�пհ�λ�� Ҫ����
		head=head->link;
	}
	printf("\n");
}
 
 
 
 
void quene()
{
	QUEUE *head,*tail;
	int op,i;
	head=tail=NULL;//�ն���
	while(1)
	{
		printf("��ѡ�������1������  2������  0���˳�");
		fflush(stdin);
		scanf("%d",&op);
		switch(op)
		{
		case 0:return;
		case 1:
			printf("���������Ԫ�أ�");
			scanf("%d",&i);
			EnQueue(&head,&tail,i);
			printf("����Ԫ��Ϊ�� \n");
			OutputQueue(head);
			break;
		case 2:if(DeQueue(&head,&tail,&i)==0)
			   {
				   printf("����Ԫ��Ϊ��[%d],����Ԫ��Ϊ�� \n",i);
				   OutputQueue(head);
			   }
			   else
				   printf("�ӿ� \n");
			break;
 
		}
	}
}


//����---------------------------------------------

typedef struct List
{
	int  data;
	struct List *next;
}list,*p_list;
 
void creat_list(list **p)//�������Ϊ�գ��򴴽�һ������ָ����ָ���Լ�������Ѱ��β�ڵ㣬��
{						 //��β�ڵ��ָ����ָ������½ڵ㣬�½ڵ��ָ����ָ��ͷ���
	int item;
	list *temp;
	list *target;
	printf("����ڵ��ֵ������0����\n");
	while(1)
	{
		scanf("%d",&item);
		if(item==0)return;
 
		if(*p==NULL)   //�������������ǿա��򴴽�һ���µĽڵ㣬ʹ��nextָ��ָ���Լ�  (*head)->next=*head;
		{
			*p=(list *)malloc(sizeof(list));
			if(!*p)exit(0);
			(*p)->data=item;
			(*p)->next=*p;
		}
		else		//����������ǿյģ�Ѱ�������β�ڵ㣬ʹβ�ڵ��next=�½ڵ㡣�½ڵ��nextָ��ͷ�ڵ�
		{
			for(target=*p;target->next!=*p;target=target->next);//Ѱ��β�ڵ�
 
			temp=(list *)malloc(sizeof(list));
			if(!temp)exit(0);
			temp->data=item;
			temp->next=*p;  //�½ڵ�ָ��ͷ�ڵ�
			target->next=temp;//β�ڵ�ָ���½ڵ�
		}
	}
}
void insert(list **pNode,int place,int num)  //����Ĳ���  
{
	list *temp,*target;
	int i;
	if(place==1)				//��������������1����ʾҪ����ͷ�ڵ㡣Ӧ�����⴦��
	{						//�����ҵ�β�ڵ㣬�ú����½ڵ��nextָ��ͷ�ڵ㣬β�ڵ�ָ���µ�ͷ�ڵ㣬����ͷָ��ָ��temp����Ҫ�ر�ע��
		temp=(list *)malloc(sizeof(list));
		if(!temp)exit(0);
		temp->data=num;
		for(target=*pNode;target->next!=*pNode;target=target->next);
		
		temp->next=*pNode;
		target->next=temp;
		*pNode=temp;/////////�ر�ע��
	}
	
	else			//�������ĵط�����ڵ㡣  ͬ�����ҵ�Ҫ�����λ�ã����λ�ó�������ĳ��ȣ��Զ������β��						tar  new  ԭ����2
	{				//�ҵ�Ҫ����λ�õ�ǰһ���ڵ�target����target->next=temp������ڵ��ǰ��ָ���½ڵ㣬�½ڵ�ָ��target->next�ĵ�ַ  1    2   3  
		for(i=1,target=*pNode;target->next!=*pNode&&i!=place-1;target=target->next,i++);
		temp=(list *)malloc(sizeof(list));
		temp->data=num;
		
		temp->next=target->next;
		target->next=temp;
	}
 
}
 
void Delete(list **pNode,int place)  //ɾ������
{
	list *temp,*target;
	int i;
	temp=*pNode;
	if(temp==NULL)				//�����ж������Ƿ�Ϊ��
	{
		printf("����һ����ָ�� �޷�ɾ��\n");
		return;
	}
	if(place==1)		//���ɾ������ͷ�ڵ�	
	{				//Ӧ�����⴦���ҵ�β�ڵ㣬ʹβ�ڵ��nextָ��ͷ�ڵ����һ���ڵ� rear->next=(*head)->next;Ȼ�����½ڵ���Ϊͷ�ڵ㣬�ͷ�ԭ����ͷ�ڵ�
		for(target=*pNode;target->next!=*pNode;target=target->next);
		temp=*pNode;
		
		*pNode=(*pNode)->next;
		target->next=*pNode;
		free(temp);
	}
	else
	{		//ɾ�������ڵ�
		for(i=1,target=*pNode;target->next!=*pNode&&i!=place-1;target=target->next,i++); //�����ҳ�β�ڵ�
		if(target->next==*pNode)		//�ж�Ҫɾ����λ���Ƿ���������ȣ������������ȣ����⴦��ֱ��ɾ��β�ڵ�
		{
			for(target=*pNode;target->next->next!=*pNode;target=target->next);//�ҳ�β�ڵ�ǰһ���ڵ�
			temp=target->next;												 //	β�ڵ��ǰһ���ڵ�ֱ��ָ��ͷ�ڵ�  �ͷ�ԭ����β�ڵ�									
			target->next=*pNode;
			printf("����̫��ɾ��β��\n");
			free(temp);
		}
		else
		{
			temp=target->next;//  ɾ����ͨ�ڵ�  �ҵ�Ҫɾ���ڵ��ǰһ���ڵ�target��ʹtargetָ��Ҫɾ���ڵ����һ���ڵ�  ת��ɾ���ڵ��ַ
			target->next=temp->next;	//  Ȼ���ͷ�����ڵ�
			free(temp);
		}
	}
}
 
int findval(list *pNode,int val) //Ѱ��ֵ
{
	int i=1;
	list *node;
	node=pNode;
	while(node->data!=val&&node->next!=pNode)
	{
		i++;
		node=node->next;
	}
	if(node->next==pNode&&node->data!=val)//β�ڵ�ָ��ͷ�ڵ����������˻�Ҫ���һ��Ϊ�ڵ��data
	{
		return -1;
	}
	return i;
}
 
 
 
void show(list *p)//������ѭ������ı��������do while��� ����Ϊͷ�ڵ����ֵ
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
	printf("ԭʼ������");
	show(head);
 
	printf("����Ҫɾ����λ�ã�");
	scanf("%d",&place);
	Delete(&head,place);
	show(head);
 
	printf("����Ҫ�����λ�ú������ÿո������");
	scanf("%d %d",&place,&num);
	insert(&head,place,num);
	show(head);
 
	printf("����������ҵ�ֵ:");
	scanf("%d",&num);
	place=findval(head,num);
	if(place!=-1)printf("�ҵ���ֵ��λ����place=%d\n",place);
	else printf("û�ҵ�ֵ \n");
    printf("\n");
}
//ͼ -------------------------------------------------------------------- 


#include<iostream>
#include<iomanip>
using namespace std;
//���Ȩֵ
#define MAXWEIGHT 100
//���ڽӾ���ʵ��ͼ
class Graph
{
private:
	//�Ƿ��Ȩ
	bool isWeighted;
	//�Ƿ�����
	bool isDirected;
	//������
	int numV;
	//����
	int numE;
	//�ڽӾ���
	int **matrix;
public:
	/*
	���췽��
	numV�Ƕ�������isWeighted�Ƿ��Ȩֵ��isDirected�Ƿ��з���
	*/
	Graph(int numV, bool isWeighted = false, bool isDirected = false);
	//��ͼ
	void createGraph();
	//��������
	~Graph();
	//��ȡ������
	int getVerNums()
	{return numV;}
	//��ȡ����
	int getEdgeNums()
	{return numE;}
	//����ָ���ߵ�Ȩֵ
	void setEdgeWeight(int tail, int head, int weight);
	//��ӡ�ڽӾ���
	void printAdjacentMatrix();
	//�������
	bool check(int i, int j, int w = 1);
};
Graph::Graph(int numV, bool isWeighted, bool isDirected)
{
	while (numV <= 0)
	{
		cout << "����Ķ���������ȷ������������ ";
		cin >> numV;
	}
	this->numV = numV;
	this->isWeighted = isWeighted;
	this->isDirected = isDirected;
	matrix = new int*[numV];  //ָ������
	int i, j;
	for (i = 0; i < numV; i++)
		matrix[i] = new int[numV];
	//��ͼ���г�ʼ��
	if (!isWeighted)  //��Ȩͼ
	{
		//����Ȩֵ��ʼ��Ϊ0
		for (i = 0; i < numV; i++)
		for (j = 0; j < numV; j++)
			matrix[i][j] = 0;
	}
	else  //��Ȩͼ
	{
		//����Ȩֵ��ʼ��Ϊ���Ȩֵ
		for (i = 0; i < numV; i++)
		for (j = 0; j < numV; j++)
			matrix[i][j] = MAXWEIGHT;
	}
}
//��ͼ
void Graph::createGraph()
{
	cout << "������� ";
	while (cin >> numE && numE < 0)
		cout << "�������󣡣��������� ";
 
	int i, j, w;
	if (!isWeighted)  //��Ȩͼ
	{
		if (!isDirected)  //����ͼ
		{
			cout << "����ÿ���ߵ������յ㣺\n";
			for (int k = 0; k < numE; k++)
			{
				cin >> i >> j;
				while (!check(i, j))
				{
					cout << "����ı߲��ԣ���������\n";
					cin >> i >> j;
				}
				matrix[i][j] = matrix[j][i] = 1;
			}
		}
		else  //����ͼ
		{
			cout << "����ÿ���ߵ������յ㣺\n";
			for (int k = 0; k < numE; k++)
			{
				cin >> i >> j;
				while (!check(i, j))
				{
					cout << "����ı߲��ԣ���������\n";
					cin >> i >> j;
				}
				matrix[i][j] = 1;
			}
		}
	}
	else  //��Ȩͼ
	{
		if (!isDirected)   //����ͼ
		{
			cout << "����ÿ���ߵ���㡢�յ��Ȩֵ��\n";
			for (int k = 0; k < numE; k++)
			{
				cin >> i >> j >> w;
				while (!check(i, j, w))
				{
					cout << "����ı߲��ԣ���������\n";
					cin >> i >> j >> w;
				}
				matrix[i][j] = matrix[j][i] = w;
			}
		}
		else  //����ͼ
		{
			cout << "����ÿ���ߵ���㡢�յ��Ȩֵ��\n";
			for (int k = 0; k < numE; k++)
			{
				cin >> i >> j >> w;
				while (!check(i, j, w))
				{
					cout << "����ı߲��ԣ���������\n";
					cin >> i >> j >> w;
				}
				matrix[i][j] = w;
			}
		}
	}
}
//��������
Graph::~Graph()
{
	int i = 0;
	for (i = 0; i < numV; i++)
		delete[] matrix[i];
	delete[]matrix;
}
//����ָ���ߵ�Ȩֵ
void Graph::setEdgeWeight(int tail, int head, int weight)
{
	if (isWeighted)
	{
		while (!check(tail, head, weight))
		{
			cout << "���벻��ȷ����������ߵ���㡢�յ��Ȩֵ ";
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
			cout << "���벻��ȷ����������ߵ���㡢�յ� ";
			cin >> tail >> head;
		}
		if (isDirected)
			matrix[tail][head] = 1-matrix[tail][head];
		else
			matrix[tail][head] = matrix[head][tail] = 1 - matrix[tail][head];
	}
}
//������
bool Graph::check(int i, int j, int w)
{
	if (i >= 0 && i < numV && j >= 0 && j < numV && w > 0 && w <= MAXWEIGHT)
		return true;
	else
		return false;
}
//��ӡ�ڽӾ���
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
	cout << "******ʹ���ڽӾ���ʵ��ͼ�ṹ*******" << endl;
	bool isDirected, isWeighted;
	int numV;
	cout << "��ͼ" << endl;
	cout << "���붥���� ";
	cin >> numV;
	cout << "���Ƿ��Ȩֵ��0(����) or 1(��) ";
	cin >> isWeighted;
	cout << "�Ƿ�������ͼ��0(����) or 1(����) ";
	cin >> isDirected;
	Graph graph(numV, isWeighted, isDirected);
	cout << "����һ��";
	isDirected ? cout << "����" : cout << "����";
	isWeighted ? cout << "��Ȩͼ" << endl : cout << "��Ȩͼ" << endl;
	graph.createGraph();
	cout << "��ӡ�ڽӾ���" << endl;
	graph.printAdjacentMatrix();
	cout << endl;
	int tail, head, weight;
	cout << "�޸�ָ���ߵ�Ȩֵ" << endl;
	if (isWeighted)  //�����Ȩͼ
	{
		cout << "����ߵ���㡢�յ��Ȩֵ ";
		cin >> tail >> head >> weight;
		graph.setEdgeWeight(tail, head, weight);
	}
	else  //�����Ȩͼ
	{
		cout << "����ߵ���㡢�յ� ";
		cin >> tail >> head;
		graph.setEdgeWeight(tail, head, 1);
	}
	cout << "�޸ĳɹ���" << endl;
	cout << "��ӡ�ڽӾ���" << endl;
	graph.printAdjacentMatrix();
	system("pause");
}





//main����--------------------------------- 
int main()
{ 
 int x;
 while (1)
 {
  printf("-------------����ѡ��-----------\n");
  	printf("1�����\t\t2����\n");
	printf("3��ջ\t\t4��������\n");
	printf("5������\t\t6������\n");		
    printf("7��ͼ \n");
    printf("8:�˳����� \n");
  printf("--------------------------------\n");
  printf("�밴���ּ�ѡ��Ҫִ�еĲ���: ");
  scanf("%d",&x);
  printf("\n");
 
  //����8����ѭ�����˳�����
  if(x==8)
      break;
   
  switch(x)
  {
  case 1:rbtree();
    break; //����1������switch��䣬������һ��ѭ��
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
  default:  //���������������siwtch��䣬������һ��ѭ��
      printf("��������ֲ���ȷ\n");
      break;
  }
 }
 return 0;
}
