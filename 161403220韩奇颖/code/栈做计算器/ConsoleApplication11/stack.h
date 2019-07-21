#pragma once
#ifndef STACK_H//Ԥ������  
#define STACK_H  

#include <iostream>  
using namespace std;

const int maxlen = 100;//ջ�����洢��  

template <typename elementType>
class stack {
public:
	stack();//���캯�������ڳ�ʼ����C++11�����Կ�������������г�ʼ��������  
	bool empty();//�ж�ջ�Ƿ�Ϊ��  
	bool full();//�ж�ջ�Ƿ�Ϊ��  
	bool get_top(elementType &x);//ȡջ��Ԫ��  
	bool push(elementType x);//Ԫ����ջ  
	bool pop();//ɾ��ջ��  
private:
	int count;//Ԫ�صļ�����  
	elementType data[maxlen];//˳��洢�ṹ  
};

template <typename elementType>
stack<elementType>::stack() {
	count = 0;
}

template <typename elementType>
bool stack<elementType>::empty() {
	if (count == 0)
		return true;
	return false;
}

template <typename elementType>
bool stack<elementType>::full() {
	if (count == maxlen)
		return true;
	return false;
}

template <typename elementType>
bool stack<elementType>::get_top(elementType &x) {
	if (!empty()) {
		x = data[count - 1];
		return true;
	}
	return false;
}

template <typename elementType>
bool stack<elementType>::push(elementType x) {
	if (!full()) {
		data[count++] = x;
		return true;
	}
	return false;
}

template <typename elementType>
bool stack<elementType>::pop() {
	if (!empty()) {
		--count;
		return true;
	}
	return false;
}
#endif 