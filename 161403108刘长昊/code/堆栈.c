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
 
Status InitStack(SqStack &S)                     //˳��ջ�ĳ�ʼ��
{
	//����һ����ջS
	S.base=new SElemType[maxsize];				//Ϊ˳��ջ��̬����һ���������Ϊmaxsize������ռ�
	if(!S.base) exit(overflow);					//�洢����ʧ��
	S.top=S.base;								//top��ʼΪbase����ջ
	S.stacksize=maxsize;						//stacksize��Ϊջ���������maxsize
	return ok;
}
 
Status Push(SqStack &S,SElemType e)				//˳��ջ����ջ
{
	//����Ԫ��eΪ�µ�ջ��Ԫ��
	if(S.top-S.base==S.stacksize)  return error;//ջ��
	*S.top++=e;									//Ԫ��eѹ��ջ����ջ��ָ���1
	return ok;
}
 
Status Pop(SqStack &S,SElemType &e)				//˳��ջ�ĳ�ջ
{
	if(S.top==S.base) return error;				//ջ��
	e=*--S.top;									//ջ��ָ���1,��ջ��Ԫ�ظ���e
	return ok;
}
 
SElemType GetTop(SqStack S)						//ȡջ��Ԫ��
{
	//����S��ջ��Ԫ�أ����޸�ջ��ָ��
	if(S.top!=S.base)							//ջ�ǿ�
		return *(S.top-1);						//����ջ��Ԫ�ص�ֵ��ջ��ָ�벻��
}
int main(int argc, char* argv[])
{
 
	return 0;
}