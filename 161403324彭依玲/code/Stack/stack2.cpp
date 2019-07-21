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

Status InitStack(SqStack &S)//��ʼ��˵
{
	S.base=(SElemType*)malloc(sizeof(SElemType)*MAXSIZE);
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=MAXSIZE;
	return OK;
}

Status Push(SqStack &S,SElemType e)//��ջ
{
	if(S.top-S.base==S.stacksize)
		return ERROR;//ջ��
	*S.top++=e;//Ԫ��eѹ��ջ����ջ��ָ���1;
	return OK;
 }

Status Pop(SqStack &S,SElemType &e)//��ջ
{
	if(S.top==S.base)//ջ��
		return ERROR;
	e=*--S.top;//ջ��ָ���һ����ջ��Ԫ�ظ���e;
	return OK;
}

SElemType GetTop(SqStack &S)//ȡջ��Ԫ��
{
	if(S.top!=S.base)//ջ�ǿ�
		return *(S.top-1);//����ջ��Ԫ�ص�ֵ��ջ��ָ�벻��
}

int In(SElemType e)//�ж϶����ַ��Ƿ�Ϊ�����
{
	if(e=='+'||e=='-'||e=='*'||e=='/'||e=='('||e==')'||e=='#')
	    return 1;//��
	else
	    return 0; //����
}

SElemType Precede(SElemType a,SElemType b)//�Ƚ�����������ȼ� 
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

SElemType Operate(SElemType a,SElemType theta,SElemType b)//����
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
	InitStack(OPND);//�Ĵ��������������
	InitStack(OPTR);//�Ĵ������
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
			switch(Precede(GetTop(OPTR),ch)) //��optr��ջ��Ԫ��������ķ������Ƚ�
			{
				case '<':  //����������ȼ��ߣ�����ջ
					Push(OPTR,ch);
				    ch=getchar();
					break;
				case '>':  //�����ջ��һ�γ�������
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
	printf("�������������ʽ,����#����\n");
	printf("�����: %d\n",EvaluateExpression());
	return 0;
}

