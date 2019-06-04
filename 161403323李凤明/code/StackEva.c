/*
该程序完成了个位数的各类表达式求值
运用了数据结构中的栈及对栈操作的各类函数，操作全用指针完成
如输入 2+3*（3+3*1）#  输出结果为 20
经测试个位数的表达式运算结果均正确
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STACK_INIT_SIZE 1000

typedef struct             //建造一个空栈
{
 char *base;
 char *top;
 int stacksize;
}SqStack;

int InitStack(SqStack *s)       //给栈分配空间，初始化栈
{
    (*s).base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!((*s).base))
        exit(0);
    s->top=s->base;
    s->stacksize=STACK_INIT_SIZE;
    return 1;
}

int Push(SqStack *s,char *ch)    //把接收到的第一个元素压入栈
{
  if(s->top-s->base>=STACK_INIT_SIZE)
    return 0;
     *((*s).top)=*ch;
    (*s).top++;
    return 1;
}

void  Pop(SqStack *s,char *ch){      //删除栈顶元素
    s->top--;
	*ch=*(s->top);
}

char* Gettop(SqStack *s)            //得到栈顶元素
{
if(s->top!=s->base)
	return (*s).top-1;
}
int In(char *c)          //判断吸收的数据是不是字符
{
    switch(*c)
    {
    case'+':
    case'-':
    case'*':
    case'/':
    case'(':
    case')':
    case'#':return 1;
    default:return 0;
    }
}
char *Operate(char *a,char *theta,char *b)   //弹出栈的元素进行运算
{
	char *c;
	*a=*a-48;
	*b=*b-48;
	c=(char *)malloc(sizeof(char));
    switch(*theta)
    {
    case'+':
        *c=*a+*b+48;
        break;
    case'-':
        *c=*a-*b+48;
        break;
    case'*':
        *c=(*a)*(*b)+48;
        break;
    case'/':
    	*c=(*a)/(*b)+48;
    	break;
    }
    return c;
}
char Precede(char *ch1,char *ch2)     //判断运算符的先后顺序
{
     if(*ch1=='+')
     {
		 if(*ch2=='+')return '>';
		 if(*ch2=='-')return '>';
		 if(*ch2=='*')return '<';
		 if(*ch2=='/')return '<';
		 if(*ch2=='(')return '<';
		 if(*ch2==')')return '>';
		 if(*ch2=='#')return '>';
     }
     if(*ch1=='-')
     {
		 if(*ch2=='+')return '>';
		 if(*ch2=='-')return '>';
		 if(*ch2=='*')return '<';
		 if(*ch2=='/')return '<';
		 if(*ch2=='(')return '<';
		 if(*ch2==')')return '>';
		 if(*ch2=='#')return '>';
     }
     if(*ch1=='*')
     {
		 if(*ch2=='+')return '>';
		 if(*ch2=='-')return '>';
		 if(*ch2=='*')return '>';
		 if(*ch2=='/')return '>';
		 if(*ch2=='(')return '<';
		 if(*ch2==')')return '>';
		 if(*ch2=='#')return '>';
     }
     if(*ch1=='/')
     {
		 if(*ch2=='+')return '>';
		 if(*ch2=='-')return '>';
		 if(*ch2=='*')return '>';
		 if(*ch2=='/')return '>';
		 if(*ch2=='(')return '<';
		 if(*ch2==')')return '>';
		 if(*ch2=='#')return '>';
     }
     if(*ch1=='(')
     {
		 if(*ch2=='+')return '<';
		 if(*ch2=='-')return '<';
		 if(*ch2=='*')return '<';
		 if(*ch2=='/')return '<';
		 if(*ch2=='(')return '<';
		 if(*ch2==')')return '=';
     }
     if(*ch1==')')
     {
		 if(*ch2=='+')return '>';
		 if(*ch2=='-')return '>';
		 if(*ch2=='*')return '>';
		 if(*ch2=='/')return '>';
		 if(*ch2==')')return '>';
		 if(*ch2=='#')return '>';
     }
     if(*ch1=='#')
     {
		 if(*ch2=='+')return '<';
		 if(*ch2=='-')return '<';
		 if(*ch2=='*')return '<';
		 if(*ch2=='/')return '<';
		 if(*ch2=='(')return '<';
		 if(*ch2=='#')return '=';
     }
}
int main()
{
    char *theta,*ch,*x,*c;
    char *a,*b;
    SqStack OPND;
    SqStack OPTR;
    InitStack(&OPND);    //创作一个存数字的栈
    InitStack(&OPTR);     //创作一个存运算符和括号的栈
    c=(char *)malloc(sizeof(char));   //分配内存
    ch=(char *)malloc(sizeof(char));
    x=(char *)malloc(sizeof(char));
    theta=(char *)malloc(sizeof(char));
    a=(char *)malloc(sizeof(char));
    b=(char *)malloc(sizeof(char));
    *c='#';
    Push(&OPTR,c);
    printf("请输入以#结尾的表达式\n");
    *ch=getchar();
    printf("\n");
    while((*ch)!='#'||(*(Gettop(&OPTR)))!='#'){  //运算结束停止条件
        if(!In(ch)){
            Push(&OPND,ch);
            printf("压入OPND栈  %d\n",*ch);
            *ch=getchar();
        }
        else{
            switch(Precede(Gettop(&OPTR),ch))     //通过比较接收的字符来进行运算
		    {
			case'<':
				Push(&OPTR,ch);
				printf("压入OPTR栈   %c\n",*ch);
				*ch=getchar();
				break;
			case'>':
				Pop(&OPTR,theta);
				printf("压入前%d %d\n",*b,*a);
				Pop(&OPND,b);
				Pop(&OPND,a);
				printf("删除后OPND的头%d %d\n",*b,*a);
				Push(&OPND,Operate(a,theta,b));
				printf("运算后 %d\n",*theta);
				break;
			case'=':
				Pop(&OPTR,x);
				*ch=getchar();
				break;
			}
		}
    }
    printf("\n");
    printf("运算结果=%d\n",(*Gettop(&OPND)-48));
} 
