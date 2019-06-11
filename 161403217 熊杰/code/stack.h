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
	//���캯��
	SqStack(){
		base=new ElemType[MAXSIZE];
		if(!base) exit(OVERFLOW);
			top=base;
		stacksize=MAXSIZE;
	}
	//˳��ջ����ջ����
	void Push(ElemType e){
		if(top-base==stacksize) {cout<<"ERROR"<<endl;return;}
		*top++=e;
	}
	//˳��ջ�ĳ�ջ����
	void Pop(){
		if(top==base) {cout<<"ERROR"<<endl;return;}
		--top;
	}
	//ȡջ��Ԫ��
	ElemType GetTop(){
		if(top==base) exit(1);
			return *(top-1);
	}
	//�ж�ջ�Ƿ�Ϊ��
	bool Empty(){
		if(base==top) return true;
		return false;
	}
	//�ж�ջ�Ƿ�����
	bool Full(){
		if(top-base==stacksize) return true;
		return false;
	}
};