#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define SIZE 50
typedef int DATA;  //����ջԪ������ 
#include "biaodashi.h" 


int isOperator(char c)    //����ַ��Ƿ�Ϊ�����
{	
	switch(c){
	case '+':		
	case '-':		
	case '*':		
	case '/':		
	case '(':		
	case ')':		
	case '=':			
		return 1;			
		break;		
	default: 		   
		return 0;		   
		break;       //�ַ�c��������򷵻�1�������򷵻�0 	
	}
}




int PRI(char oper1,char oper2)     //�ж���������������ȼ�
//���oper1>oper2����1    ���oper1<oper2����-1   ���oper1,,oper2�����ҷ��ŷ���0 
{	int pri;	
	switch(oper2){   //�ж����ȼ�			
	case '+':		
	case '-':			
		if(oper1=='('||oper1=='=')  //Ϊ������ 			
			pri=-1;        //oper1<oper2			
		else 			  
			pri=1;       //oper1>oper2		
		break;		
	case '*':	
	case '/':	
		if(oper1=='*'||oper1=='/'||oper1==')')			 
			pri=1;   //oper1>oper2			
		else			 
			pri=-1;     //oper1<oper2		
		break;		
	case '(':		
		if(oper1==')')       //�������Ҳ಻�����ϳ���������		
		{			
			printf("�﷨����\n");	
			exit(0);		
		} else			   
			pri=-1;       //oper1<oper2		
		break;	
	case ')':		
		if(oper1=='(')		
			pri=0;		
		else if(oper1=='=')			
		{			
			printf("���Ų�ƥ��\n");			
			exit(0);		
		}
		else
			pri=1;		
		break;
	case '=':		
		if(oper1=='(')	
		{			
			printf("���Ų�ƥ��\n");	
			exit(0);		
		}
		else if(oper1=='=')	
			pri=0;  //�Ⱥ�ƥ�䣬����0
		else		
			pri=1;      //oper1>oper2		
		break; 	  
	}	
	return pri;
} 




int Calc(int a,int oper,int b)  //���������������Ľ��
{	
	switch(oper)     //�������������	
	{		
	case '+':
		return a+b;				
	case '-':
		return a-b;				
	case '*':
		return a*b;			
	case '/':			
		if(b!=0)			
			return a/b;		
		else			
		{				
			printf("��������Ϊ0!\n");	
			exit(0);	
		}
	}	
} 	
int CalcExp(char exp[])   //���ʽ���㺯��
{		
	seqStack *StackOper,*StackData;   //ָ������ջ��ָ�������һ����������һ��������
	int i=0,flag=0;   //flag��Ϊ��־�����������λ��
	DATA a,b,c,q,x,t,oper;
	StackOper=seqStackInit();	
	StackData=seqStackInit();    //��ʼ������ջ	
	q=0;  //����q�����λ���Ĳ���
	x='=';
	seqStackPush(StackOper,x);  //���ȰѵȺ�=�������ջ	
	x=seqStackPeek(StackOper); //��ȡ����ջ����Ԫ�� 
	c=exp[i++]; 	
	while(c!='='||x!='=')  //ѭ��������ʽ�е�ÿһ���ַ�
	{	
		if(isOperator(c))  //����������		
		{			
			if(flag){	
				seqStackPush(StackData,q);  //���ʽ��ջ		
				q=0;   //���������� 			
				flag=0;   //��־���㣬��ʾ�������Ѿ���ջ 	
			}			
			switch(PRI(x,c))   //�ж���������ȼ�	
			{			
			case -1:				
				seqStackPush(StackOper,c);  //�������ջ			
				c=exp[i++];				
				break;			
			case 0:				
				c=seqStackPop(StackOper);  //��������ţ��Ⱥų�ջ��������		
				c=exp[i++];   //ȡ��һ�� �ַ� 				
				break; 			
			case 1:				
				oper=seqStackPop(StackOper);   //�������ջ	
				b=seqStackPop(StackData);				
				a=seqStackPop(StackData);  //������������ջ			
				t=Calc(a,oper,b);  //������				
				seqStackPush(StackData,t);  //����������ջ 	
				break;				  			
			} 	
		}
		else if(c>='0'&&c<='9')  //���������ַ���0��9֮��		
		{		
			c-='0';   //���ַ�ת��������	
			q=q*10+c;       //��λ���Ľ�λ����
			c=exp[i++];  //ȡ����һλ�ַ�			 
			flag=1;  //���ñ�־����ʾ������δ��ջ	
		} 	
		else
		{	
			printf("�������\n");
			getch();			
			exit(0);	
		}		
		x=seqStackPeek(StackOper);  //��ȡջ�������� 	
	} 
	q=seqStackPop(StackData); 
	seqStackfree(StackOper);  
	seqStackfree(StackData);  //�ͷ��ڴ�ռ�ÿռ�
	return q;  //��ջ�����ؽ�� 	
 
}
int main()
{
	int c;
	char exp[80];
	printf("��������Ҫ����ı��ʽ(��=����):\n");
	scanf("%s",exp);
	printf("%s%d\n",exp,CalcExp(exp));
	getch();
	return 0;
}