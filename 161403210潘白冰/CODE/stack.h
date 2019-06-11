#include <iostream>
using namespace std;
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define Status int 
template<typename ElemType>
class SqStack
{
	public:
	ElemType *base;
	ElemType *top;
	int stacksize;
	//构造函数
	SqStack(){
		base=new ElemType[MAXSIZE];
		if(!base) exit(OVERFLOW);
			top=base;
		stacksize=MAXSIZE;
	}
	//顺序栈的入栈操作
	void Push(ElemType e){
		if(top-base==stacksize) {cout<<"ERROR"<<endl;return;}
		*top++=e;
	}
	//顺序栈的出栈操作
	void Pop(){
		if(top==base) {cout<<"ERROR"<<endl;return;}
		--top;
	}
	//取栈顶元素
	ElemType GetTop(){
		if(top==base) exit(1);
			return *(top-1);
	}
	//判断栈是否为空
	bool Empty(){
		if(base==top) return true;
		return false;
	}
	//判断栈是否已满
	bool Full(){
		if(top-base==stacksize) return true;
		return false;
	}
};