#include <stdio.h>
#include <malloc.h>   //malloc,realloc
#include <math.h>     //含有overflow
#include <iostream>

using namespace std;

#define STACK_INIT_SIZE 100   //栈的初始空间大小
#define STACKINCREAMENT 10    //增加空间
#define OVERFLOW -1           //溢出
/*数据类型定义*/
typedef int SElemType;
typedef struct{
	SElemType *base; //栈底
	SElemType *top;  //栈顶
	int stacksize;
}SqStack;

//----------------函数声明--------------
void InitStack(SqStack &S);//初始化空栈
bool StackEmpty(SqStack S);//判空
void GetTop(SqStack S, SElemType &e);//获得栈顶元素
void Push(SqStack &S, SElemType e);//进栈
void Pop(SqStack &S, SElemType &e);//出栈
void convert(SqStack &S, int N, int n);//十进制转N进制

/*构造一个空栈*/
void InitStack(SqStack &S)
{
	S.base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if (!S.base)
		exit(OVERFLOW);   //存储分配失败
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
}

/*栈的判空函数*/
bool StackEmpty(SqStack S)
{
	if (S.base == S.top)
		return true;
	else
		return false;
}

/*获得栈顶元素*/
void GetTop(SqStack S, SElemType &e)
{
	if (S.top == S.base) return;
	else
		e = *(S.top - 1);
}

/*进栈*/
void Push(SqStack &S, SElemType e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (SElemType*)realloc(S.base,(S.stacksize+STACKINCREAMENT)*sizeof(SElemType));
		if (!S.base)
			exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREAMENT;
	}
	*S.top++ = e;   //注意：相当于*S.top =e;S.top++;
}

/*出栈*/
void Pop(SqStack &S, SElemType &e)
{
	if (S.top == S.base) return;
	e = *--S.top;   //注意：相当于--S.top;S.top =e;
}

/*数制的转换函数*/
void convert(SqStack &S, int N, int n)
{
	InitStack(S);
	while (N)
	{
		Push(S, N % n);
		N = N / n;
	}
	cout << "转换为" << n << "进制之后的数为:";
	while (!StackEmpty(S))
	{
		SElemType e;
		Pop(S, e);
		cout << e;
	}
	cout << endl;
}

int main()
{
	/*数制的转换过程*/
	int n, N;//要转换成的进制数和要转换的数
	SqStack s;
	InitStack(s);//初始化空栈
	cout << "请输入需要十进制数：";
	cin >> N;
	cout << endl;
	cout << "请输入需要转换的进制数：";
	cin >> n;
	cout << endl;
	convert(s, N, n);
}

