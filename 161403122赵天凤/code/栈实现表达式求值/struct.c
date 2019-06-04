#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STACK_INIT_SIZE 1000
typedef struct
{
 char *base;
 char *top;
 int stacksize;
}SqStack;
int InitStack(SqStack *s)//给栈分配空间，初始化栈
{
    (*s).base=(char*)malloc(STACK_INIT_SIZE*sizeof(char));
    if(!((*s).base))
        exit(0);
    s->top=s->base;
    s->stacksize=STACK_INIT_SIZE;
    return 1;
}
int Push(SqStack *s,char *ch)//把接收的第一个栈
{
  if(s->top-s->base>=STACK_INIT_SIZE)
    return 0;
     *((*s).top)=*ch;
    (*s).top++;
    return 1;
}
void Pop(SqStack *s,char *ch){
    s->top--;
*ch=*(s->top);
}
char* Gettop(SqStack *s)
{
 if(s->top!=s->base)
    return (*s).top-1;
}
int In(char *c)  
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
char *Operate(char *a,char *theta,char *b)
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
char Precede(char *ch1,char *ch2)
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
    InitStack(&OPND);
    InitStack(&OPTR);
    c=(char *)malloc(sizeof(char)); 
    ch=(char *)malloc(sizeof(char));
    x=(char *)malloc(sizeof(char));
    theta=(char *)malloc(sizeof(char));
    a=(char *)malloc(sizeof(char));
    b=(char *)malloc(sizeof(char));
    *c='#';
    Push(&OPTR,c);
    printf("请输入以#结尾的表达式\n");
    *ch=getchar();
    while((*ch)!='#'||(*(Gettop(&OPTR)))!='#'){
        if(!In(ch)){
            Push(&OPND,ch);
        printf("压入OPND栈  %d\n",*ch);
            *ch=getchar();
        }
        else
            switch(Precede(Gettop(&OPTR),ch))
        {
         case'<':
         Push(&OPTR,ch);
         printf("压入OPTR栈   %c\n",*ch);
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
            break;}
    }
    printf("\n\n\n");
    printf("运算结果= %d",(*Gettop(&OPND)-48));
}

