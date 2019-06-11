#include "stack.h"
#include <cstring>
#include <iostream>
using namespace std;

SqStack<char> optr,opnd;
SqStack<double> oprd;

char sign[8]="+-*/()#";   //�������飨��Ӧ�±꣩
//�����������ȼ�������
int p[8][8]={{1,1,-1,-1,-1,1,1},{1,1,-1,-1,-1,1,1},{1,1,1,1,-1,1,1},{1,1,1,1,-1,1,1},{-1,-1,-1,-1,-1,0,-2},{1,1,1,1,-2,1,1},{-1,-1,-1,-1,-1,-2,1}};
//�������ݵ��㷨
double Combine()
{
	int front=0;
	opnd.Push('\0');
	char *sss;
	sss=opnd.base;
	if(sss[0]=='-') front=1;
	int point=(int)strlen(sss); 
	int i;
	for(i=0;i<(int)strlen(sss);i++)
		if(sss[i]=='.')
		{point=i;break;}
	double s=0;
	double t=1;
	for(i=point-1;i>=front;i--)
	{
		s+=(sss[i]-48)*t;
		t*=10;
	}
	t=1;
	for(i=point+1;i<(int)strlen(sss);i++)
	{
		t/=10;
		s+=(sss[i]-48)*t;
	}
	while(!opnd.Empty())
		opnd.Pop();
	return (!front)?s:s*(-1);
}

//����ƥ������㷨��
bool Match(char x[])
{ 
	int i;
	bool p=true;
	SqStack<char> s;
	if(x[(int)strlen(x)-1]!='#')
		return false;
	for(i=0;i<strlen(x);i++)
	{
		if(x[i]=='(')
			s.Push(x[i]);
		if(s.Empty()&&x[i]==')')
		return false;
		if(x[i]==')'&&s.GetTop()!='(')
		{p=false;break;}
		if(x[i]==')')
			s.Pop();
	}
	return p;
}
//���ȼ������㷨
int Precede(char a,char b)
{
	int i;
	int Sp,Sq;
	for(i=0;i<8;i++)
	{
		if(a==sign[i])
			Sp=i;
		if(b==sign[i])
			Sq=i;
	}
	return p[Sp][Sq];
}
//�ж�c�Ƿ�Ϊ�����
bool In(char c)
{
	int i;
	bool p=false;
	for(i=0;i<4;i++)
		if(c==sign[i])
		{p=true;break;}
	return p;
}
//���㶨���㷨����
double Operate(double num1,char oper,double num2)
{
	switch(oper)
	{
	case '+':return num1+num2;
	case '-':return num1-num2;
	case '*':return num1*num2;
	case '/':
		{
			if(num2==0)
				throw num2;
			return num1/num2;
		}
	default:
		{
			cout<<"���ִ���"<<endl;
			exit(0);
		}
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	int i;
	char exprition[100];
	bool exit=false;;
	while(1)    //ע�⣺��fget�����ʱ����ȡһ�У����仰˵���л��з���
	{
		cout<<"��������һ���Ϸ����ʽ����#�������ʽ�����룬�����г��ָ������뽫����д��()�ڡ�ע�⣬��������������end"<<endl;;
		cout<<"��������һ�����ʽ:";
		scanf("%s",exprition);
		if(exprition[0]=='e'&&exprition[1]=='n'&&exprition[2]=='d')
		{cout<<"��л����ʹ��!"<<endl;return 0;}
		while(!Match(exprition))
		{
			cout<<"������ı��ʽ���������������롣"<<endl;
			scanf("%s",exprition);
			if(exprition[0]=='e'&&exprition[1]=='n'&&exprition[2]=='d')
			{cout<<"��л����ʹ��!"<<endl;return 0;}
		}
		exprition[strlen(exprition)]='\0';
		optr.Push('#');
		for(i=0;i<strlen(exprition);i++)
		{
			if(exprition[i]>='0'&&exprition[i]<='9'||exprition[i]=='.')
				opnd.Push(exprition[i]);
			else
			{
				if(In(exprition[i])&&!opnd.Empty())
					oprd.Push(Combine());
				if(Precede(optr.GetTop(),exprition[i])==-1)
				{
					if(exprition[i]=='-'&&exprition[i-1]=='(')
					{opnd.Push(exprition[i]);continue;}
					optr.Push(exprition[i]);
				}
				else if(Precede(optr.GetTop(),exprition[i])==1)
				{
					if(!In(exprition[i])&&!opnd.Empty())
						oprd.Push(Combine());
					double num1,num2;
					char oper;
					num1=oprd.GetTop();
					oprd.Pop();
					if(oprd.Empty())
					{cout<<"���ʽ��ֵΪ��"<<num1<<endl;continue;}
					num2=oprd.GetTop();
					oprd.Pop();
					oper=optr.GetTop();
					optr.Pop();
					try{
						oprd.Push(Operate(num2,oper,num1));
					}
					catch(double)
					{
						cout<<"������ѧ��ʦ�������𣬳�������Ϊ0��"<<endl;
						break;
					}
					if(exprition[i]!='#'&&exprition[i]!=')')
						optr.Push(exprition[i]);
					while(exprition[i]==')'&&optr.GetTop()=='(')
						optr.Pop();
					if(exprition[i]=='#'&&optr.GetTop()!='#')
						i--;
				}
				else if(Precede(optr.GetTop(),exprition[i])==0)
				{
					if(optr.GetTop()=='('&&exprition[i]==')')
						optr.Pop();
				}
			}
			if(optr.GetTop()=='#'&&exprition[i]=='#')
			{cout<<"���ʽ��ֵΪ��"<<oprd.GetTop()<<endl;break;}
		}
		cout<<"�밴���������..."<<endl;
		getchar();getchar();
	}
	return 0;
}
