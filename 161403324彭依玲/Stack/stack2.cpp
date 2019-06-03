#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100
typedef int Status;
typedef char SElemType;

typedef struct
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

Status InitStack(SqStack &S)//初始化说
{
	S.base=(SElemType*)malloc(sizeof(SElemType)*MAXSIZE);
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=MAXSIZE;
	return OK;
}

Status Push(SqStack &S,SElemType e)//入栈
{
	if(S.top-S.base==S.stacksize)
		return ERROR;//栈满
	*S.top++=e;//元素e压入栈顶，栈顶指针加1;
	return OK;
 }

Status Pop(SqStack &S,SElemType &e)//出栈
{
	if(S.top==S.base)//栈空
		return ERROR;
	e=*--S.top;//栈顶指针减一，将栈顶元素赋给e;
	return OK;
}

SElemType GetTop(SqStack &S)//取栈顶元素
{
	if(S.top!=S.base)//栈非空
		return *(S.top-1);//返回栈顶元素的值，栈顶指针不变
}

int In(SElemType e)//判断读入字符是否为运算符
{
	if(e=='+'||e=='-'||e=='*'||e=='/'||e=='('||e==')'||e=='#')
	    return 1;//是
	else
	    return 0; //不是
}

SElemType Precede(SElemType a,SElemType b)//比较运算符的优先级 
{
	SElemType f;
	if(a=='+'||a=='-')
	{
		if(b=='+'||b=='-'||b==')'||b=='#')
		    f='>';
		else if(b=='*'||b=='/'||b=='(')
		    f='<';
	}
	else if(a=='*'||a=='/')
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#')
		   f='>';
		else if(b=='(')
		   f='<';
	}
	else if(a=='(')
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b=='(')
		   f='<';
		else if(b==')')
		   f='=';
	}
	else if(a==')')
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b==')'||b=='#')
		   f='>';
       
	}
	else if(a=='#')
	{
		if(b=='+'||b=='-'||b=='*'||b=='/'||b=='(')
		   f='<';
		else if(b=='#')
		   f='=';
	}
	return f;
}

SElemType Operate(SElemType a,SElemType theta,SElemType b)//运算
{
	SElemType c;
	a=a-'0';
	b=b-'0';
	if(theta=='+')
	  c=a+b+'0';
	else if(theta=='-')
	  c=a-b+'0';
	else if(theta=='*')
	  c=a*b+'0';
	else if(theta=='/')
	  c=a/b+'0';
	return c;
}

int EvaluateExpression()	// 
{
	SqStack OPND,OPTR;
	char ch,a,b,theta,x;
	InitStack(OPND);//寄存操作数和运算结果
	InitStack(OPTR);//寄存运算符
	Push(OPTR,'#');
	ch=getchar();
	while(ch!='#'||GetTop(OPTR)!='#')
	{
		if(!In(ch))
		{
			Push(OPND,ch);	
			ch=getchar();
		}
		else
		{
			switch(Precede(GetTop(OPTR),ch)) //拿optr的栈顶元素与输入的符号做比较
			{
				case '<':  //输入符号优先级高，则入栈
					Push(OPTR,ch);
				    ch=getchar();
					break;
				case '>':  //低则出栈，一次出两个数
					Pop(OPTR,theta);
					Pop(OPND,b);
					Pop(OPND,a);
					Push(OPND,Operate(a,theta,b));
					break;
				case '=':
					Pop(OPTR,x);
				    ch=getchar();
					break;
			}
		}
	}
	return GetTop(OPND)-'0';
}

int main()
{
	printf("请输入算术表达式,并以#结束\n");
	printf("结果是: %d\n",EvaluateExpression());
	return 0;
}

