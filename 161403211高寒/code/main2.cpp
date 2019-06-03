/*
 * main.cpp
 *
 *  Created on: 2019年5月16日
 *      Author: gaohan
 */

#include"Stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
int main()
{
	Stack stack;
	stack.Print();
	stack.Push(1);
	stack.Push(2);
	stack.Push(3);
	stack.Push(4);
	stack.Print();

	cout << "******************" << endl;
	stack.Pop();
	stack.Print();
	cout << "******************" << endl;
	stack.Pop();
	stack.Print();
	cout << "******************" << endl;
	stack.Pop();
	stack.Print();
	cout << "******************" << endl;
	stack.Pop();
	stack.Print();
	cout << "******************" << endl;
	stack.Pop();
	stack.Print();
	cout << "******************" << endl;
	return 0;
}



