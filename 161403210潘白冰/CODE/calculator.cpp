#include "stack.h"
#include <cstring>
#include <iostream>
using namespace std;

SqStack<char> optr,opnd;
SqStack<double> oprd;

char sign[8]="+-*/()#";   //符号数组（对应下标）
//表征符号优先级的数组
int p[8][8]={{1,1,-1,-1,-1,1,1},{1,1,-1,-1,-1,1,1},{1,1,1,1,-1,1,1},{1,1,1,1,-1,1,1},{-1,-1,-1,-1,-1,0,-2},{1,1,1,1,-2,1,1},{-1,-1,-1,-1,-1,-2,1}};
//构造数据的算法
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

//括号匹配检验算法。
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
//优先级检验算法
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
//判断c是否为运算符
bool In(char c)
{
	int i;
	bool p=false;
	for(i=0;i<4;i++)
		if(c==sign[i])
		{p=true;break;}
	return p;
}
//运算定义算法函数
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
			cout<<"出现错误"<<endl;
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
	while(1)    //注意：用fget读入的时候会读取一行，换句话说会有换行符。
	{
		cout<<"请您输入一个合法表达式，以#结束表达式的输入，若其中出现负数，请将负数写在()内。注意，结束程序请输入end"<<endl;;
		cout<<"请您输入一个表达式:";
		scanf("%s",exprition);
		if(exprition[0]=='e'&&exprition[1]=='n'&&exprition[2]=='d')
		{cout<<"感谢您的使用!"<<endl;return 0;}
		while(!Match(exprition))
		{
			cout<<"您输入的表达式有误，请您重新输入。"<<endl;
			scanf("%s",exprition);
			if(exprition[0]=='e'&&exprition[1]=='n'&&exprition[2]=='d')
			{cout<<"感谢您的使用!"<<endl;return 0;}
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
					{cout<<"表达式的值为："<<num1<<endl;continue;}
					num2=oprd.GetTop();
					oprd.Pop();
					oper=optr.GetTop();
					optr.Pop();
					try{
						oprd.Push(Operate(num2,oper,num1));
					}
					catch(double)
					{
						cout<<"您的数学老师还活着吗，除数不能为0。"<<endl;
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
			{cout<<"表达式的值为："<<oprd.GetTop()<<endl;break;}
		}
		cout<<"请按任意键继续..."<<endl;
		getchar();getchar();
	}
	return 0;
}
