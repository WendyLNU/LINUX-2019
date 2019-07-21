#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define SIZE 50
typedef int DATA;  //定义栈元素类型 
#include "biaodashi.h" 


int isOperator(char c)    //检查字符是否为运算符
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
		break;       //字符c是运算符则返回1，，否则返回0 	
	}
}




int PRI(char oper1,char oper2)     //判断两个运算符的优先级
//如果oper1>oper2返回1    如果oper1<oper2返回-1   如果oper1,,oper2是左右符号返回0 
{	int pri;	
	switch(oper2){   //判断优先级			
	case '+':		
	case '-':			
		if(oper1=='('||oper1=='=')  //为左括号 			
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
		if(oper1==')')       //右括号右侧不能马上出现左括号		
		{			
			printf("语法错误\n");	
			exit(0);		
		} else			   
			pri=-1;       //oper1<oper2		
		break;	
	case ')':		
		if(oper1=='(')		
			pri=0;		
		else if(oper1=='=')			
		{			
			printf("括号不匹配\n");			
			exit(0);		
		}
		else
			pri=1;		
		break;
	case '=':		
		if(oper1=='(')	
		{			
			printf("括号不匹配\n");	
			exit(0);		
		}
		else if(oper1=='=')	
			pri=0;  //等号匹配，返回0
		else		
			pri=1;      //oper1>oper2		
		break; 	  
	}	
	return pri;
} 




int Calc(int a,int oper,int b)  //计算两个操作数的结果
{	
	switch(oper)     //根据运算符计算	
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
			printf("除数不能为0!\n");	
			exit(0);	
		}
	}	
} 	
int CalcExp(char exp[])   //表达式计算函数
{		
	seqStack *StackOper,*StackData;   //指向两个栈的指针变量，一个操作符，一个运算数
	int i=0,flag=0;   //flag作为标志，用来处理多位数
	DATA a,b,c,q,x,t,oper;
	StackOper=seqStackInit();	
	StackData=seqStackInit();    //初始化两个栈	
	q=0;  //变量q保存多位数的操作
	x='=';
	seqStackPush(StackOper,x);  //首先把等号=进入操作栈	
	x=seqStackPeek(StackOper); //获取操作栈的首元素 
	c=exp[i++]; 	
	while(c!='='||x!='=')  //循环处理表达式中的每一个字符
	{	
		if(isOperator(c))  //如果是运算符		
		{			
			if(flag){	
				seqStackPush(StackData,q);  //表达式入栈		
				q=0;   //操作数清零 			
				flag=0;   //标志清零，表示操作数已经入栈 	
			}			
			switch(PRI(x,c))   //判断运算符优先级	
			{			
			case -1:				
				seqStackPush(StackOper,c);  //运算符进栈			
				c=exp[i++];				
				break;			
			case 0:				
				c=seqStackPop(StackOper);  //运算符括号，等号出栈，被抛弃		
				c=exp[i++];   //取下一个 字符 				
				break; 			
			case 1:				
				oper=seqStackPop(StackOper);   //运算符出栈	
				b=seqStackPop(StackData);				
				a=seqStackPop(StackData);  //两个操作数出栈			
				t=Calc(a,oper,b);  //计算结果				
				seqStackPush(StackData,t);  //将运算结果入栈 	
				break;				  			
			} 	
		}
		else if(c>='0'&&c<='9')  //如果输出的字符在0到9之间		
		{		
			c-='0';   //把字符转换成数字	
			q=q*10+c;       //多位数的进位处理
			c=exp[i++];  //取出下一位字符			 
			flag=1;  //设置标志，表示操作数未入栈	
		} 	
		else
		{	
			printf("输入错误\n");
			getch();			
			exit(0);	
		}		
		x=seqStackPeek(StackOper);  //获取栈顶操作符 	
	} 
	q=seqStackPop(StackData); 
	seqStackfree(StackOper);  
	seqStackfree(StackData);  //释放内存占用空间
	return q;  //出栈，返回结果 	
 
}
int main()
{
	int c;
	char exp[80];
	printf("请输入需要计算的表达式(以=结束):\n");
	scanf("%s",exp);
	printf("%s%d\n",exp,CalcExp(exp));
	getch();
	return 0;
}