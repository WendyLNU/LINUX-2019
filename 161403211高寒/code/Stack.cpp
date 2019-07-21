#include<iostream>
#include"Stack.h"
using namespace std;

Stack::Stack()
{
	top = NULL;
	buttom = NULL;
	size = 0;
	cout << "Stack: 这是一个空栈" << endl;
}


void Stack::Push(int data)
{
	Node *temp;
	temp = (Node *)new Node[1];
	temp->data = data;
	temp->next = NULL;
	if (size==0)
	{
		top = (Node *)new Node[1];
		buttom = temp;
	}
	top->next = temp;
	top = temp;
	size++;
	cout << "Push: 入栈成功！" << endl;
}

void Stack::Pop()
{
	if (size == 0)
	{
		cout << "Pop: 空栈无法出栈！" << endl;
		return;
	}
	if (size == 1)
	{
		Node *temp;
		temp = top;
		top = NULL;
		buttom = NULL;
		size--;
		delete temp;
		cout << "Pop: 出栈成功，栈已为空！" << endl;
		return;
	}
	Node *temp1, *temp2;
	temp1 = top;
	temp2 = buttom;
	while (temp2->next!=top)
	{
		temp2 = temp2->next;
	}
	top = temp2;
	size--;
	delete temp1;
	cout << "Pop: 出栈成功！" << endl;
}

void Stack::Print()
{
	if (size==0)
	{
		cout << "Print: 栈为空！" << endl;
		return;
	}
	Node *temp;
	temp = buttom;
	cout << "Print： 栈内元素共"<< size <<"个，分别为： ";
	while (temp!=top)
	{
		cout << temp->data << "，";
		temp = temp->next;
	}
	cout << top->data << endl;
}


