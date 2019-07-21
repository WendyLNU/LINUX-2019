#include "stdio.h"
#include<stdlib.h>
#define maxsize 100
#define overflow 1
#define ok 1	
#define error 1
#define SElemType int
#define Status int
 
typedef struct 
{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;
 
Status InitStack(SqStack &S)                     //顺序栈的初始化
{
	//构造一个空栈S
	S.base=new SElemType[maxsize];				//为顺序栈动态分配一个最大容量为maxsize的数组空间
	if(!S.base) exit(overflow);					//存储分配失败
	S.top=S.base;								//top初始为base，空栈
	S.stacksize=maxsize;						//stacksize置为栈的最大容量maxsize
	return ok;
}
 
Status Push(SqStack &S,SElemType e)				//顺序栈的入栈
{
	//插入元素e为新的栈顶元素
	if(S.top-S.base==S.stacksize)  return error;//栈满
	*S.top++=e;									//元素e压入栈顶，栈顶指针加1
	return ok;
}
 
Status Pop(SqStack &S,SElemType &e)				//顺序栈的出栈
{
	if(S.top==S.base) return error;				//栈空
	e=*--S.top;									//栈顶指针减1,将栈顶元素赋给e
	return ok;
}
 
SElemType GetTop(SqStack S)						//取栈顶元素
{
	//返回S的栈顶元素，不修改栈顶指针
	if(S.top!=S.base)							//栈非空
		return *(S.top-1);						//返回栈顶元素的值，栈顶指针不变
}
int main(int argc, char* argv[])
{
 
	return 0;
}

